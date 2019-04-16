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

#include "M2Win32Helpers.h"

/**
 * Determines whether the interface id have the correct interface name.
 *
 * @param InterfaceID A pointer to the string representation of the IID.
 * @param InterfaceName A pointer to the interface name string.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2CoCheckInterfaceName(
    _In_ LPCWSTR InterfaceID,
    _In_ LPCWSTR InterfaceName)
{
    HKEY hKey = nullptr;
    HRESULT hr = M2RegCreateKey(
        HKEY_CLASSES_ROOT,
        (std::wstring(L"Interface\\") + InterfaceID).c_str(),
        0,
        nullptr,
        0,
        KEY_READ,
        nullptr,
        &hKey,
        nullptr);
    if (SUCCEEDED(hr))
    {
        DWORD Type = 0;
        wchar_t Data[256] = { 0 };
        DWORD cbData = 256;

        hr = M2RegQueryValue(
            hKey,
            nullptr,
            nullptr,
            &Type,
            reinterpret_cast<LPBYTE>(Data),
            &cbData);
        if (SUCCEEDED(hr))
        {
            if (0 != _wcsicmp(Data, InterfaceName))
            {
                hr = E_NOINTERFACE;
            }
        }

        RegCloseKey(hKey);
    }

    return hr;
}
