/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeChromiumCache.cpp
 * PURPOSE:   Implementation for Purge Chromium Cache
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <vector>
#include <string>

namespace
{
    static void PurgeChromiumCacheFilesWorker(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR RootPath,
        _Inout_opt_ PUINT64 UsedSpace)
    {
        HANDLE RootHandle = ::MoPrivateCreateFile(
            RootPath,
            SYNCHRONIZE | FILE_LIST_DIRECTORY,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
            nullptr);
        if (RootHandle != INVALID_HANDLE_VALUE)
        {
            Mile::HResult hr = S_OK;
            hr = Mile::EnumerateFile(
                RootHandle,
                [&](
                    _In_ Mile::PFILE_ENUMERATE_INFORMATION Information) -> BOOL
            {
                if (Mile::IsDotsName(Information->FileName))
                {
                    return TRUE;
                }

                if (Information->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    return TRUE;
                }

                std::wstring CurrentPath = Mile::FormatUtf16String(
                    L"%s\\%s",
                    RootPath,
                    Information->FileName);

                if (0 != ::_wcsicmp(Information->FileName, L"index") &&
                    0 != _wcsnicmp(Information->FileName, L"data_", 5) &&
                    0 != _wcsnicmp(Information->FileName, L"f_", 2))
                {
                    return TRUE;
                }

                ::MoPrivateRemoveFileWorker(
                    Context,
                    CurrentPath.c_str(),
                    UsedSpace); 

                return TRUE;
            });
            if (hr.IsFailed())
            {
                ::MoPrivateWriteErrorMessage(
                    Context,
                    hr,
                    L"%s(%s)",
                    L"Mile::EnumerateFile",
                    RootPath);
            }

            ::CloseHandle(RootHandle);
        }
        else
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                Mile::HResultFromLastError(FALSE),
                L"%s(%s)",
                L"CreateFileW",
                RootPath);
        }
    }

    static void PurgeChromiumCacheFolderWorker(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR RootPath,
        _Inout_opt_ PUINT64 UsedSpace)
    {
        HANDLE RootHandle = ::MoPrivateCreateFile(
            RootPath,
            SYNCHRONIZE | FILE_LIST_DIRECTORY,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
            nullptr);
        if (RootHandle != INVALID_HANDLE_VALUE)
        {
            Mile::HResult hr = S_OK;
            hr = Mile::EnumerateFile(
                RootHandle,
                [&](
                    _In_ Mile::PFILE_ENUMERATE_INFORMATION Information) -> BOOL
            {
                if (Mile::IsDotsName(Information->FileName))
                {
                    return TRUE;
                }

                if (!(Information->FileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    return TRUE;
                }

                std::wstring CurrentPath = Mile::FormatUtf16String(
                    L"%s\\%s",
                    RootPath,
                    Information->FileName);

                ::PurgeChromiumCacheFolderWorker(
                    Context,
                    CurrentPath.c_str(),
                    UsedSpace);

                bool IsChromiumBlockfileCacheFolder = false;
                bool IsChromiumSimpleCacheFolder = false;

                HANDLE CurrentHandle = ::MoPrivateCreateFile(
                    (CurrentPath + L"\\index").c_str(),
                    SYNCHRONIZE | FILE_READ_DATA | FILE_READ_ATTRIBUTES,
                    FILE_SHARE_READ,
                    nullptr,
                    OPEN_EXISTING,
                    FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
                    nullptr);
                if (CurrentHandle != INVALID_HANDLE_VALUE)
                {
                    std::uint8_t Signature[sizeof(std::uint64_t)];

                    DWORD NumberOfBytesRead = 0;
                    hr = Mile::ReadFile(
                        CurrentHandle,
                        Signature,
                        static_cast<DWORD>(sizeof(Signature)),
                        &NumberOfBytesRead);
                    if (hr.IsSucceeded() &&
                        NumberOfBytesRead == sizeof(Signature))
                    {
                        // Blockfile Index File Magic: 0xC103CAC3
                        IsChromiumBlockfileCacheFolder = (
                            Signature[0] == 0xC3 &&
                            Signature[1] == 0xCA &&
                            Signature[2] == 0x03 &&
                            Signature[3] == 0xC1);

                        // Simple Index File Magic: 0xFCFB6D1BA7725C30
                        IsChromiumSimpleCacheFolder = (
                            Signature[0] == 0x30 &&
                            Signature[1] == 0x5C &&
                            Signature[2] == 0x72 &&
                            Signature[3] == 0xA7 &&
                            Signature[4] == 0x1B &&
                            Signature[5] == 0x6D &&
                            Signature[6] == 0xFB &&
                            Signature[7] == 0xFC);
                    }

                    ::CloseHandle(CurrentHandle);
                }

                if (IsChromiumBlockfileCacheFolder)
                {
                    ::PurgeChromiumCacheFilesWorker(
                        Context,
                        CurrentPath.c_str(),
                        UsedSpace);
                }
                else if (IsChromiumSimpleCacheFolder)
                {
                    ::MoPrivateRemoveDirectoryWorker(
                        Context,
                        CurrentPath.c_str(),
                        UsedSpace);
                }

                return TRUE;
            });
            if (hr.IsFailed())
            {
                ::MoPrivateWriteErrorMessage(
                    Context,
                    hr,
                    L"%s(%s)",
                    L"Mile::EnumerateFile",
                    RootPath);
            }

            ::CloseHandle(RootHandle);
        }
        else
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                Mile::HResultFromLastError(FALSE),
                L"%s(%s)",
                L"CreateFileW",
                RootPath);
        }
    }
}

EXTERN_C HRESULT WINAPI MoPurgeChromiumCache(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;
    std::vector<std::wstring> ProfilePathList;

    do
    {
        DWORD PurgeMode = ::MoPrivateParsePurgeMode(Context);
        if (PurgeMode == 0)
        {
            hr = Mile::HResult::FromWin32(ERROR_CANCELLED);
            break;
        }

        if (PurgeMode != MO_PRIVATE_PURGE_MODE_SCAN &&
            PurgeMode != MO_PRIVATE_PURGE_MODE_PURGE)
        {
            hr = E_NOINTERFACE;
            break;
        }

        hr = ::MoPrivateEnableBackupRestorePrivilege(
            &PreviousContextTokenHandle);
        if (hr.IsFailed())
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"MoPrivateEnableBackupRestorePrivilege");
            break;
        }

        ProfilePathList = ::MoPrivateGetProfilePathList();
        if (ProfilePathList.empty())
        {
            hr = E_NOINTERFACE;
            ::MoPrivateWriteErrorMessage(
                Context,
                E_NOINTERFACE,
                L"MoPrivateGetProfilePathList");
            break;
        }

        UINT64 UsedSpace = 0;
        for (std::wstring const& ProfilePath : ProfilePathList)
        {
            if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
            {
                ::PurgeChromiumCacheFolderWorker(
                    Context,
                    ProfilePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::PurgeChromiumCacheFolderWorker(
                    Context,
                    ProfilePath.c_str(),
                    nullptr);
            }
        }

        if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
        {
            ::MoPrivatePrintPurgeScanResult(
                Context,
                UsedSpace);
        }

    } while (false);

    if (PreviousContextTokenHandle != INVALID_HANDLE_VALUE)
    {
        ::SetThreadToken(nullptr, PreviousContextTokenHandle);
        ::CloseHandle(PreviousContextTokenHandle);
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
