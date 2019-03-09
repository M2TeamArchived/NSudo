/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2Win32Helpers.cpp
 * PURPOSE:   Implementation for the Win32 desktop helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "stdafx.h"

#include <Windows.h>
#include <VersionHelpers.h>

#include "M2Win32Helpers.h"

/**
 * Obtain the best matching resource with the specified type and name in the
 * specified module.
 *
 * @param lpResourceInfo The resource info which contains the pointer and size.
 * @param hModule A handle to the module whose portable executable file or an
 *                accompanying MUI file contains the resource. If this
 *                parameter is NULL, the function searches the module used to
 *                create the current process.
 * @param lpType The resource type. Alternately, rather than a pointer, this
 *               parameter can be MAKEINTRESOURCE(ID), where ID is the integer
 *               identifier of the given resource type.
 * @param lpName The name of the resource. Alternately, rather than a pointer,
 *               this parameter can be MAKEINTRESOURCE(ID), where ID is the
 *               integer identifier of the resource.
 * @return HRESULT.
 */
HRESULT M2LoadResource(
    _Out_ PM2_RESOURCE_INFO lpResourceInfo,
    _In_opt_ HMODULE hModule,
    _In_ LPCWSTR lpType,
    _In_ LPCWSTR lpName)
{
    if (!lpResourceInfo)
        return E_INVALIDARG;

    lpResourceInfo->Size = 0;
    lpResourceInfo->Pointer = nullptr;

    HRSRC ResourceFind = FindResourceExW(
        hModule, lpType, lpName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    if (!ResourceFind)
        return M2GetLastHRESULTErrorKnownFailedCall();

    lpResourceInfo->Size = SizeofResource(hModule, ResourceFind);

    HGLOBAL ResourceLoad = LoadResource(hModule, ResourceFind);
    if (!ResourceLoad)
        return M2GetLastHRESULTErrorKnownFailedCall();

    lpResourceInfo->Pointer = LockResource(ResourceLoad);

    return S_OK;
}

/**
 * Retrieves the path of the shared Windows directory on a multi-user system.
 *
 * @param WindowsFolderPath The string of the path of the shared Windows
 *                          directory on a multi-user system.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetWindowsDirectory(
    std::wstring& WindowsFolderPath)
{
    HRESULT hr = S_OK;

    do
    {
        UINT Length = GetSystemWindowsDirectoryW(
            nullptr,
            0);
        if (0 == Length)
        {
            hr = M2GetLastHRESULTErrorKnownFailedCall();
            break;
        }

        WindowsFolderPath.resize(Length - 1);

        Length = GetSystemWindowsDirectoryW(
            &WindowsFolderPath[0],
            static_cast<UINT>(Length));
        if (0 == Length)
        {
            hr = M2GetLastHRESULTErrorKnownFailedCall();
            break;
        }
        if (WindowsFolderPath.size() != Length)
        {
            hr = E_UNEXPECTED;
            break;
        }

    } while (false);

    if (FAILED(hr))
    {
        WindowsFolderPath.clear();
    }

    return hr;
}

/**
 * Starts a service if not started and retrieves the current status of the
 * specified service.
 *
 * @param lpServiceName The name of the service to be started. This is the name
 *                      specified by the lpServiceName parameter of the
 *                      CreateService function when the service object was
 *                      created, not the service display name that is shown by
 *                      user interface applications to identify the service.
 *                      The maximum string length is 256 characters. The
 *                      service control manager database preserves the case of
 *                      the characters, but service name comparisons are always
 *                      case insensitive. Forward-slash (/) and backslash ()
 *                      are invalid service name characters.
 * @param lpServiceStatus Contains process status information for a service.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2StartService(
    _In_ LPCWSTR lpServiceName,
    _Out_ LPSERVICE_STATUS_PROCESS lpServiceStatus)
{
    M2::CServiceHandle hSCM;
    M2::CServiceHandle hService;

    DWORD nBytesNeeded = 0;
    DWORD nOldCheckPoint = 0;
    ULONGLONG nLastTick = 0;
    bool bStartServiceWCalled = false;

    hSCM = OpenSCManagerW(
        nullptr,
        nullptr,
        SC_MANAGER_CONNECT);
    if (!hSCM)
        return M2GetLastHRESULTErrorKnownFailedCall();

    hService = OpenServiceW(
        hSCM,
        lpServiceName,
        SERVICE_QUERY_STATUS | SERVICE_START);
    if (!hService)
        return M2GetLastHRESULTErrorKnownFailedCall();

    while (QueryServiceStatusEx(
        hService,
        SC_STATUS_PROCESS_INFO,
        reinterpret_cast<LPBYTE>(lpServiceStatus),
        sizeof(SERVICE_STATUS_PROCESS),
        &nBytesNeeded))
    {
        if (SERVICE_STOPPED == lpServiceStatus->dwCurrentState)
        {
            // Failed if the service had stopped again.
            if (bStartServiceWCalled)
                return E_FAIL;

            if (!StartServiceW(hService, 0, nullptr))
                return M2GetLastHRESULTErrorKnownFailedCall();

            bStartServiceWCalled = true;
        }
        else if (
            SERVICE_STOP_PENDING == lpServiceStatus->dwCurrentState ||
            SERVICE_START_PENDING == lpServiceStatus->dwCurrentState)
        {
            ULONGLONG nCurrentTick = GetTickCount64();

            if (!nLastTick)
            {
                nLastTick = nCurrentTick;
                nOldCheckPoint = lpServiceStatus->dwCheckPoint;

                // Same as the .Net System.ServiceProcess, wait 250ms.
                SleepEx(250, FALSE);
            }
            else
            {
                // Check the timeout if the checkpoint is not increased.
                if (lpServiceStatus->dwCheckPoint <= nOldCheckPoint)
                {
                    ULONGLONG nDiff = nCurrentTick - nLastTick;
                    if (nDiff > lpServiceStatus->dwWaitHint)
                    {
                        return __HRESULT_FROM_WIN32(ERROR_TIMEOUT);
                    }
                }

                // Continue looping.
                nLastTick = 0;
            }
        }
        else
        {
            break;
        }
    }

    return S_OK;
}

/**
 * Loads the specified module with the optimization of the mitigation of DLL
 * preloading attacks into the address space of the calling process safely. The
 * specified module may cause other modules to be loaded.
 *
 * @param ModuleHandle If the function succeeds, this parameter's value is a
 *                     handle to the loaded module. You should read the
 *                     documentation about LoadLibraryEx API for further
 *                     information.
 * @param LibraryFileName A string that specifies the file name of the module
 *                        to load. You should read the documentation about
 *                        LoadLibraryEx API for further information.
 * @param Flags The action to be taken when loading the module. You should read
 *              the documentation about LoadLibraryEx API for further
 *              information.
 * @return HRESULT.
 */
HRESULT M2LoadLibraryEx(
    _Out_ HMODULE& ModuleHandle,
    _In_ LPCWSTR LibraryFileName,
    _In_ DWORD Flags)
{
    ModuleHandle = LoadLibraryExW(LibraryFileName, nullptr, Flags);
    if (!ModuleHandle)
    {
        const size_t BufferLength = 32768;
        wchar_t Buffer[BufferLength];

        if ((Flags & LOAD_LIBRARY_SEARCH_SYSTEM32) &&
            (M2GetLastErrorKnownFailedCall() == ERROR_INVALID_PARAMETER))
        {
            if (!wcschr(LibraryFileName, (wchar_t)'\\'))
            {
                UINT NewLength = GetSystemDirectoryW(
                    Buffer,
                    BufferLength);

                Buffer[NewLength++] = '\\';

                for (; *LibraryFileName; ++LibraryFileName)
                {
                    Buffer[NewLength++] = *LibraryFileName;
                }

                Buffer[NewLength] = L'\0';

                LibraryFileName = Buffer;
            }

            ModuleHandle = LoadLibraryExW(LibraryFileName, nullptr, Flags);
        }
    }

    return ModuleHandle ? S_OK : M2GetLastHRESULTErrorKnownFailedCall();
}

/**
 * Queries the dots per inch (dpi) of a display.
 *
 * @param hmonitor Handle of the monitor being queried.
 * @param dpiType The type of DPI being queried. Possible values are from the
 *                MONITOR_DPI_TYPE enumeration.
 * @param dpiX The value of the DPI along the X axis. This value always refers
 *             to the horizontal edge, even when the screen is rotated.
 * @param dpiY The value of the DPI along the Y axis. This value always refers
 *             to the vertical edge, even when the screen is rotated.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetDpiForMonitor(
    _In_ HMONITOR hmonitor,
    _In_ MONITOR_DPI_TYPE dpiType,
    _Out_ UINT *dpiX,
    _Out_ UINT *dpiY)
{
    HMODULE hModule = nullptr;
    HRESULT hr = M2LoadLibraryEx(
        hModule,
        L"SHCore.dll",
        LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (SUCCEEDED(hr))
    {
        decltype(GetDpiForMonitor)* pFunc = nullptr;
        hr = M2GetProcAddress(pFunc, hModule, "GetDpiForMonitor");
        if (SUCCEEDED(hr))
        {
            hr = pFunc(hmonitor, dpiType, dpiX, dpiY);
        }

        FreeLibrary(hModule);
    }

    return hr;
}
