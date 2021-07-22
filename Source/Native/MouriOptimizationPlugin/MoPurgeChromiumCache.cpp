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

#include "MouriOptimizationPlugin.h"

#include <regex>
#include <vector>
#include <string>

namespace
{
    static const std::vector<std::wregex> g_ChromiumCacheFileInclusionList =
    {
        std::wregex(
            L"(.*)\\\\index",
            std::regex_constants::syntax_option_type::icase),
        std::wregex(
            L"(.*)\\\\data_([0-9A-F]*)",
            std::regex_constants::syntax_option_type::icase),
        std::wregex(
            L"(.*)\\\\f_([0-9A-F]*)",
            std::regex_constants::syntax_option_type::icase),
    };

    static bool IsFileNameMatchedWithRegularExpressionList(
        std::wstring const& FileName,
        std::vector<std::wregex> const& RegularExpressionList)
    {
        for (std::wregex const& RegularExpressionItem : RegularExpressionList)
        {
            if (std::regex_match(FileName, RegularExpressionItem))
            {
                return true;
            }
        }

        return false;
    }

    void PurgeChromiumCacheFilesWorker(
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

                if (!::IsFileNameMatchedWithRegularExpressionList(
                    CurrentPath,
                    g_ChromiumCacheFileInclusionList))
                {
                    return TRUE;
                }

                HANDLE CurrentHandle = ::MoPrivateCreateFile(
                    CurrentPath.c_str(),
                    SYNCHRONIZE |
                    FILE_LIST_DIRECTORY |
                    FILE_READ_DATA |
                    DELETE |
                    FILE_READ_ATTRIBUTES |
                    FILE_WRITE_ATTRIBUTES,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    nullptr,
                    OPEN_EXISTING,
                    FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
                    nullptr);
                if (CurrentHandle == INVALID_HANDLE_VALUE)
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        Mile::HResultFromLastError(FALSE),
                        L"%s(%s)",
                        L"CreateFileW",
                        CurrentPath.c_str());
                }

                if (UsedSpace)
                {
                    UINT64 CurrentFileSize = 0;
                    hr = Mile::GetCompressedFileSizeByHandle(
                        CurrentHandle,
                        &CurrentFileSize);
                    if (hr.IsSucceeded())
                    {
                        *UsedSpace += CurrentFileSize;

                        ::MoPrivateWriteLine(
                            Context,
                            L"Detected - %s.",
                            CurrentPath.c_str());
                    }
                    else
                    {
                        ::MoPrivateWriteErrorMessage(
                            Context,
                            hr,
                            L"%s(%s)",
                            L"Mile::GetCompressedFileSizeByHandle",
                            CurrentPath.c_str());
                    }
                }
                else
                {
                    hr = Mile::DeleteFileByHandleIgnoreReadonlyAttribute(
                        CurrentHandle);
                    if (hr.IsSucceeded())
                    {
                        ::MoPrivateWriteLine(
                            Context,
                            L"Removed - %s.",
                            CurrentPath.c_str());
                    }
                    else
                    {
                        ::MoPrivateWriteErrorMessage(
                            Context,
                            hr,
                            L"%s(%s)",
                            L"Mile::DeleteFileByHandleIgnoreReadonlyAttribute",
                            CurrentPath.c_str());
                    }
                }

                ::CloseHandle(CurrentHandle);

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

    void PurgeChromiumCacheFolderWorker(
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

                bool IsChromiumCacheFolder = false;

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
                    std::uint8_t Signature[4];

                    const DWORD NumberOfBytesToRead =
                        static_cast<DWORD>(sizeof(Signature));
                    DWORD NumberOfBytesRead = 0;

                    hr = Mile::ReadFile(
                        CurrentHandle,
                        Signature,
                        NumberOfBytesToRead,
                        &NumberOfBytesRead);
                    if (hr.IsSucceeded() &&
                        NumberOfBytesRead == NumberOfBytesToRead)
                    {
                        // Chromium Index File Signature: 0xC103CAC3
                        IsChromiumCacheFolder = (
                            Signature[0] == 0xC3 &&
                            Signature[1] == 0xCA &&
                            Signature[2] == 0x03 &&
                            Signature[3] == 0xC1);
                    }

                    ::CloseHandle(CurrentHandle);
                }

                if (IsChromiumCacheFolder)
                {
                    ::PurgeChromiumCacheFilesWorker(
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
