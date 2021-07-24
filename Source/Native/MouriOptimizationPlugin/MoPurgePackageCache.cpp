/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgePackageCache.cpp
 * PURPOSE:   Implementation for Purge Package Cache
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
    static void PurgePackageCacheFolderWorker(
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

                if (::MoPrivateIsFileExist(
                    (CurrentPath + L"\\state.rsm").c_str()))
                {
                    return TRUE;
                }

                ::MoPrivateRemoveDirectoryWorker(
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

EXTERN_C HRESULT WINAPI MoPurgePackageCache(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;
    HANDLE MSIExecuteEvent = nullptr;
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

        // Try to block Windows Installer for bring this implementation more
        // safety.
        MSIExecuteEvent = ::CreateEventExW(
            nullptr,
            L"Global\\_MSIExecute",
            CREATE_EVENT_MANUAL_RESET,
            EVENT_ALL_ACCESS);
        if (!MSIExecuteEvent)
        {
            hr = E_ACCESSDENIED;
            break;
        }

        {
            std::wstring GlobalPath = Mile::ExpandEnvironmentStringsW(
                L"%SystemDrive%\\ProgramData\\Package Cache");
            if (::MoPrivateIsFileExist(GlobalPath.c_str()))
            {
                CachePathList.push_back(GlobalPath);
            }
        }

        for (std::wstring const& Profile : ::MoPrivateGetProfilePathList())
        {
            std::wstring LocalAppData = Profile + L"\\AppData\\Local";

            std::wstring Candidate;

            Candidate = LocalAppData + L"\\Package Cache";
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
                ::PurgePackageCacheFolderWorker(
                    Context,
                    CachePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::PurgePackageCacheFolderWorker(
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

    if (MSIExecuteEvent)
    {
        ::CloseHandle(MSIExecuteEvent);
    }

    if (PreviousContextTokenHandle != INVALID_HANDLE_VALUE)
    {
        ::SetThreadToken(nullptr, PreviousContextTokenHandle);
        ::CloseHandle(PreviousContextTokenHandle);
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
