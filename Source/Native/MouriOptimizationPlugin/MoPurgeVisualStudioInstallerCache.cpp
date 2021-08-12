/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeVisualStudioInstallerCache.cpp
 * PURPOSE:   Implementation for Purge Visual Studio Installer Cache
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <string>

namespace
{
    static void PurgeVisualStudioInstallerCacheWorker(
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

                //
                // File and directory names need to be kept:
                //
                // _Instances
                // _bootstrapper
                // _package.json
                //
                // Because these names are all beginning with '_', just check
                // it for higher performance.
                //
                if (Information->FileName[0] == L'_')
                {
                    return TRUE;
                }

                std::wstring CurrentPath = Mile::FormatUtf16String(
                    L"%s\\%s",
                    RootPath,
                    Information->FileName);

                if (Information->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    ::PurgeVisualStudioInstallerCacheWorker(
                        Context,
                        CurrentPath.c_str(),
                        UsedSpace);
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

EXTERN_C HRESULT WINAPI MoPurgeVisualStudioInstallerCache(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;
    HANDLE MSIExecuteEvent = nullptr;

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

        std::wstring CachePath = Mile::ExpandEnvironmentStringsW(
            L"%SystemDrive%\\ProgramData\\Microsoft\\VisualStudio\\Packages");

        UINT64 UsedSpace = 0;

        if (::MoPrivateIsFileExist(CachePath.c_str()))
        {
            if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
            {
                ::PurgeVisualStudioInstallerCacheWorker(
                    Context,
                    CachePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::PurgeVisualStudioInstallerCacheWorker(
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
