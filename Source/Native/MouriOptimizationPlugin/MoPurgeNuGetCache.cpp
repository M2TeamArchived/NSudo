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
                ::MoPrivateEmptyDirectoryWorker(
                    Context,
                    CachePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::MoPrivateEmptyDirectoryWorker(
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
