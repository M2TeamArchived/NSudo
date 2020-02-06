/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.cpp
 * PURPOSE:   Mouri Internal Library Essentials Implementation for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.Windows.h"

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAllocMemory(
    _In_ SIZE_T Size,
    _Out_ LPVOID* Block)
{
    return ::MileHeapAlloc(
        ::MileGetProcessHeap(), HEAP_ZERO_MEMORY, Size, Block);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileReAllocMemory(
    _In_ PVOID OldBlock,
    _In_ SIZE_T NewSize,
    _Out_ LPVOID* NewBlock)
{
    return ::MileHeapReAlloc(
        ::MileGetProcessHeap(), HEAP_ZERO_MEMORY, OldBlock, NewSize, NewBlock);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileFreeMemory(
    _In_ LPVOID Block)
{
    return ::MileHeapFree(
        ::MileGetProcessHeap(), 0, Block);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetTokenInformationWithMemory(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_ PVOID* OutputInformation)
{
    *OutputInformation = nullptr;

    DWORD Length = 0;

    HRESULT hr = ::MileGetTokenInformation(
        TokenHandle,
        TokenInformationClass,
        nullptr,
        0,
        &Length);
    if (hr == ::HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
    {
        hr = ::MileAllocMemory(Length, OutputInformation);
        if (hr == S_OK)
        {
            hr = ::MileGetTokenInformation(
                TokenHandle,
                TokenInformationClass,
                *OutputInformation,
                Length,
                &Length);
            if (hr != S_OK)
            {
                ::MileFreeMemory(*OutputInformation);
                *OutputInformation = nullptr;
            }
        }
    }

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenPrivilegesSimple(
    _In_ HANDLE TokenHandle,
    _In_ PLUID_AND_ATTRIBUTES Privileges,
    _In_ DWORD PrivilegeCount)
{
    HRESULT hr = E_INVALIDARG;

    if (Privileges && PrivilegeCount)
    {
        DWORD PSize = sizeof(LUID_AND_ATTRIBUTES) * PrivilegeCount;
        DWORD TPSize = PSize + sizeof(DWORD);

        PTOKEN_PRIVILEGES pTP = nullptr;

        hr = ::MileAllocMemory(TPSize, reinterpret_cast<LPVOID*>(&pTP));
        if (hr == S_OK)
        {
            pTP->PrivilegeCount = PrivilegeCount;
            ::memcpy(pTP->Privileges, Privileges, PSize);

            hr = ::MileAdjustTokenPrivileges(
                TokenHandle, FALSE, pTP, TPSize, nullptr, nullptr);

            ::MileFreeMemory(pTP);
        }
    }

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenAllPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ DWORD Attributes)
{
    PTOKEN_PRIVILEGES pTokenPrivileges = nullptr;

    HRESULT hr = ::MileGetTokenInformationWithMemory(
        TokenHandle,
        TokenPrivileges,
        reinterpret_cast<PVOID*>(&pTokenPrivileges));
    if (hr == S_OK)
    {
        for (DWORD i = 0; i < pTokenPrivileges->PrivilegeCount; ++i)
        {
            pTokenPrivileges->Privileges[i].Attributes = Attributes;
        }

        hr = ::MileAdjustTokenPrivilegesSimple(
            TokenHandle,
            pTokenPrivileges->Privileges,
            pTokenPrivileges->PrivilegeCount);

        ::MileFreeMemory(pTokenPrivileges);
    }

    return hr;
}
