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
    static void PurgeNuGetPackageCacheWorker(
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
                    ::PurgeNuGetPackageCacheWorker(
                        Context,
                        CurrentPath.c_str(),
                        UsedSpace);
                    return TRUE;
                }

                // The cleanable file path in NuGet package folder should be
                // the form of .nuget\packages\[C]\[V]\[C].[V].nupkg.

                if (S_OK != ::PathMatchSpecExW(
                    CurrentPath.c_str(),
                    L"*\\.nuget\\packages\\*\\*\\*.nupkg",
                    PMSF_NORMAL))
                {
                    return TRUE;
                }

                std::vector<std::wstring> SplitResult =
                    ::MoPrivateSplitPathString(CurrentPath);
                std::size_t SplitResultSize = SplitResult.size();
                if (SplitResultSize < 3)
                {
                    return TRUE;
                }

                std::wstring ActualFileName =
                    SplitResult[SplitResultSize - 1];
                std::wstring GuessedFileName =
                    SplitResult[SplitResultSize - 3];
                GuessedFileName += L".";
                GuessedFileName += SplitResult[SplitResultSize - 2];
                GuessedFileName += L".nupkg";

                if (0 != ::_wcsicmp(
                    GuessedFileName.c_str(),
                    ActualFileName.c_str()))
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
}

EXTERN_C HRESULT WINAPI MoPurgeNuGetCache(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;
    std::vector<std::wstring> CachePathList;
    std::vector<std::wstring> PackagePathList;

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
                PackagePathList.push_back(Candidate);
            }
        }
        if (CachePathList.empty() && PackagePathList.empty())
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
                ::MoPrivateRemoveDirectoryWorker(
                    Context,
                    CachePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::MoPrivateRemoveDirectoryWorker(
                    Context,
                    CachePath.c_str(),
                    nullptr);
            }
        }

        for (std::wstring const& PackagePath : PackagePathList)
        {
            if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
            {
                ::PurgeNuGetPackageCacheWorker(
                    Context,
                    PackagePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::PurgeNuGetPackageCacheWorker(
                    Context,
                    PackagePath.c_str(),
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
