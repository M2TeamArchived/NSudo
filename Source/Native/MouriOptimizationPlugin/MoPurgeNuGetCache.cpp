/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeNuGetCache.cpp
 * PURPOSE:   Implementation for Purge NuGet Cache
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
    static void PurgeNuGetCacheWorker(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR RootPath,
        _Inout_opt_ PUINT64 UsedSpace)
    {
        HANDLE RootHandle = ::MoPrivateCreateFile(
            RootPath,
            SYNCHRONIZE |
            FILE_LIST_DIRECTORY |
            DELETE |
            FILE_READ_ATTRIBUTES |
            FILE_WRITE_ATTRIBUTES,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
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

                std::wstring CurrentPath = Mile::FormatUtf16String(
                    L"%s\\%s",
                    RootPath,
                    Information->FileName);

                if (Information->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    ::PurgeNuGetCacheWorker(
                        Context,
                        CurrentPath.c_str(),
                        UsedSpace);
                    return TRUE;
                }

                HANDLE CurrentHandle = ::MoPrivateCreateFile(
                    CurrentPath.c_str(),
                    SYNCHRONIZE |
                    FILE_LIST_DIRECTORY |
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
                    return TRUE;
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

            if (UsedSpace)
            {
                ::MoPrivateWriteLine(
                    Context,
                    L"Detected - %s.",
                    RootPath);
            }
            else
            {
                hr = Mile::DeleteFileByHandleIgnoreReadonlyAttribute(
                    RootHandle);
                if (hr.IsSucceeded())
                {
                    ::MoPrivateWriteLine(
                        Context,
                        L"Removed - %s.",
                        RootPath);
                }
                else
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"%s(%s)",
                        L"Mile::DeleteFileByHandleIgnoreReadonlyAttribute",
                        RootPath);
                }
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

EXTERN_C HRESULT WINAPI MoPurgeNuGetCache(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;
    std::vector<std::wstring> CachePathList;

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

        for (std::wstring const& Profile : ::MoPrivateGetProfilePathList())
        {
            std::wstring LocalAppData = Profile + L"\\AppData\\Local";

            std::wstring Candidate;

            Candidate = LocalAppData + L"\\NuGet\\v3-cache";
            if (::MoPrivateIsFileExist(Candidate.c_str()))
            {
                CachePathList.push_back(Candidate);
            }

            Candidate = LocalAppData + L"\\NuGet\\plugins-cache";
            if (::MoPrivateIsFileExist(Candidate.c_str()))
            {
                CachePathList.push_back(Candidate);
            }

            Candidate = LocalAppData + L"\\Temp\\NuGetScratch";
            if (::MoPrivateIsFileExist(Candidate.c_str()))
            {
                CachePathList.push_back(Candidate);
            }

            Candidate = Profile + L"\\.nuget\\packages";
            if (::MoPrivateIsFileExist(Candidate.c_str()))
            {
                CachePathList.push_back(Candidate);
            }
        }
        if (CachePathList.empty())
        {
            hr = E_NOINTERFACE;
            ::MoPrivateWriteErrorMessage(
                Context,
                E_NOINTERFACE,
                L"MoPrivateGetProfilePathList");
            break;
        }

        UINT64 UsedSpace = 0;
        for (std::wstring const& CachePath : CachePathList)
        {
            if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
            {
                ::PurgeNuGetCacheWorker(
                    Context,
                    CachePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::PurgeNuGetCacheWorker(
                    Context,
                    CachePath.c_str(),
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
