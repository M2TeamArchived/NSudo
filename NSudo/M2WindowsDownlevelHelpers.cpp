/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsDownlevelHelpers.cpp
 * PURPOSE:   Implementation for the Windows downlevel helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "M2WindowsDownlevelHelpers.h"

#ifdef _M2_WINDOWS_DOWNLEVEL_HELPERS_

DWORD M2GetLastWin32Error(
    _In_ BOOL IsLastFunctionCallSucceeded,
    _In_ BOOL UseLastErrorWhenSucceeded)
{
    if (IsLastFunctionCallSucceeded && !UseLastErrorWhenSucceeded)
        return ERROR_SUCCESS;

    DWORD LastError = GetLastError();

    if (!IsLastFunctionCallSucceeded && ERROR_SUCCESS == LastError)
        return ERROR_FUNCTION_FAILED;

    return LastError;
}

HRESULT M2GetLastHResultError(
    _In_ BOOL IsLastFunctionCallSucceeded,
    _In_ BOOL UseLastErrorWhenSucceeded)
{
    return HRESULT_FROM_WIN32(M2GetLastWin32Error(
        IsLastFunctionCallSucceeded,
        UseLastErrorWhenSucceeded));
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

HRESULT M2CreateFile(
    _Out_ PHANDLE lpFileHandle,
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile)
{
    *lpFileHandle = CreateFileW(
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile);

    return M2GetLastHResultError(INVALID_HANDLE_VALUE != *lpFileHandle);
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

HRESULT M2LoadLibrary(
    _Out_ HMODULE* phLibModule,
    _In_ LPCWSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags)
{
    *phLibModule = LoadLibraryExW(lpLibFileName, hFile, dwFlags);
    return M2GetLastHResultError(*phLibModule != nullptr);
}

#endif

HRESULT M2FreeLibrary(
    _In_ HMODULE hLibModule)
{
    return M2GetLastHResultError(FreeLibrary(hLibModule));
}

HRESULT M2GetProcAddress(
    _Out_ FARPROC* lpProcAddress,
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName)
{
    *lpProcAddress = GetProcAddress(hModule, lpProcName);
    return M2GetLastHResultError(*lpProcAddress != nullptr);
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

HRESULT M2DeviceIoControl(
    _In_ HANDLE hDevice,
    _In_ DWORD dwIoControlCode,
    _In_opt_ LPVOID lpInBuffer,
    _In_ DWORD nInBufferSize,
    _Out_opt_ LPVOID lpOutBuffer,
    _In_ DWORD nOutBufferSize,
    _Out_opt_ LPDWORD lpBytesReturned,
    _Inout_opt_ LPOVERLAPPED lpOverlapped)
{
    return M2GetLastHResultError(DeviceIoControl(
        hDevice,
        dwIoControlCode,
        lpInBuffer,
        nInBufferSize,
        lpOutBuffer,
        nOutBufferSize,
        lpBytesReturned,
        lpOverlapped));
}

#endif

HRESULT M2CoCreateInstance(
    _In_ LPCWSTR lpszCLSID,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ LPCWSTR lpszIID,
    _Out_ LPVOID* ppv)
{
    CLSID clsid;
    IID iid;

    HRESULT hr = CLSIDFromString(lpszCLSID, &clsid);
    if (SUCCEEDED(hr))
    {
        hr = IIDFromString(lpszIID, &iid);
        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(clsid, pUnkOuter, dwClsContext, iid, ppv);
        }
    }

    return hr;
}

#endif // _M2_WINDOWS_DOWNLEVEL_HELPERS_
