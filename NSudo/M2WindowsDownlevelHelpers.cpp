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
