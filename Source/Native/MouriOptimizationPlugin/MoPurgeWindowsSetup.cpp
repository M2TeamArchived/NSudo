/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeWindowsSetup.cpp
 * PURPOSE:   Implementation for Purge Windows Setup
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
    static bool IsMutexExisted(
        _In_ LPCWSTR Name)
    {
        bool Result = true;

        HANDLE MutexHandle = ::OpenMutexW(GENERIC_READ, FALSE, Name);
        if (MutexHandle)
        {
            ::CloseHandle(MutexHandle);
        }
        else if (::GetLastError() != ERROR_FILE_NOT_FOUND)
        {
            Result = false;
        }

        return Result;
    }

    static bool IsWebSetupRunning()
    {
        return ::IsMutexExisted(L"Global\\Microsoft.Windows.Websetup");
    }

    static bool IsSetupRunning()
    {
        return ::IsMutexExisted(L"Global\\Microsoft.Windows.Setup")
            || ::IsMutexExisted(L"Microsoft.Windows.Setup.Local");
    }

    static bool IsSetupInProgress()
    {
        bool Result = false;

        HKEY SystemSetupKeyHandle = nullptr;
        Mile::HResult hr = Mile::HResult::FromWin32(::RegOpenKeyExW(
            HKEY_LOCAL_MACHINE,
            L"System\\Setup",
            0,
            KEY_READ | KEY_WOW64_64KEY,
            &SystemSetupKeyHandle));
        if (hr.IsSucceeded())
        {
            HKEY KeyHandle = nullptr;
            hr = Mile::HResult::FromWin32(::RegOpenKeyExW(
                SystemSetupKeyHandle,
                L"DeploymentInProgress",
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &KeyHandle));
            if (hr.IsSucceeded())
            {
                Result = true;
                ::RegCloseKey(KeyHandle);
            }

            if (!Result)
            {
                DWORD Type = 0;
                DWORD Data = FALSE;
                DWORD Length = sizeof(DWORD);
                hr = Mile::HResult::FromWin32(::RegQueryValueExW(
                    SystemSetupKeyHandle,
                    L"SystemSetupInProgress",
                    nullptr,
                    &Type,
                    reinterpret_cast<LPBYTE>(&Data),
                    &Length));
                if (hr.IsSucceeded() && Type == REG_DWORD)
                {
                    Result = Data;
                }
            }

            ::RegCloseKey(SystemSetupKeyHandle);
        }

        return Result;
    }
}

EXTERN_C HRESULT WINAPI MoPurgeWindowsSetup(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;
    std::vector<std::wstring> PathList;

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

        std::wstring SystemRootPath = Mile::ExpandEnvironmentStringsW(
            L"%SystemDrive%\\");

        PathList.push_back(SystemRootPath + L"Windows.old");

        if ((!::IsSetupRunning()) && (!::IsSetupInProgress()))
        {
            PathList.push_back(SystemRootPath + L"$WINDOWS.~BT");
        }

        PathList.push_back(SystemRootPath + L"$WINDOWS.~Q");
        PathList.push_back(SystemRootPath + L"$INPLACE.~TR");
        PathList.push_back(SystemRootPath + L"$Windows.~LS");

        if (!::IsWebSetupRunning())
        {
            PathList.push_back(SystemRootPath + L"$Windows.~WS");
            PathList.push_back(SystemRootPath + L"ESD\\Windows");
            PathList.push_back(SystemRootPath + L"ESD\\Download");
        }

        PathList.push_back(SystemRootPath + L"Windows\\Panther");

        UINT64 UsedSpace = 0;

        for (std::wstring const& Path : PathList)
        {
            if (::MoPrivateIsFileExist(Path.c_str()))
            {
                if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
                {
                    ::MoPrivateRemoveDirectoryWorker(
                        Context,
                        Path.c_str(),
                        &UsedSpace);
                }
                else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
                {
                    ::MoPrivateRemoveDirectoryWorker(
                        Context,
                        Path.c_str(),
                        nullptr);
                }
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
