/*
 * PROJECT:   NSudo
 * FILE:      NSudoAPI.cpp
 * PURPOSE:   Implementation for NSudo Shared Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "NSudoAPI.h"

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoAdjustTokenPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ PLUID_AND_ATTRIBUTES Privileges,
    _In_ DWORD PrivilegeCount)
{
    DWORD ErrorCode = ERROR_INVALID_PARAMETER;

    if (Privileges && PrivilegeCount)
    {
        DWORD PSize = sizeof(LUID_AND_ATTRIBUTES) * PrivilegeCount;
        DWORD TPSize = PSize + sizeof(DWORD);

        PTOKEN_PRIVILEGES pTP = reinterpret_cast<PTOKEN_PRIVILEGES>(
            ::HeapAlloc(::GetProcessHeap(), 0, TPSize));
        if (pTP)
        {
            pTP->PrivilegeCount = PrivilegeCount;
            memcpy(pTP->Privileges, Privileges, PSize);

            ::AdjustTokenPrivileges(
                TokenHandle, FALSE, pTP, TPSize, nullptr, nullptr);
            ErrorCode = ::GetLastError();

            ::HeapFree(::GetProcessHeap(), 0, pTP);
        }
        else
        {
            ErrorCode = ERROR_NOT_ENOUGH_MEMORY;
        }
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoCreateMandatoryLabelSid(
    _Out_ PSID* MandatoryLabelSid,
    _In_ DWORD MandatoryLabelRid)
{
    SID_IDENTIFIER_AUTHORITY SIA = SECURITY_MANDATORY_LABEL_AUTHORITY;

    if (::AllocateAndInitializeSid(
        &SIA, 1, MandatoryLabelRid, 0, 0, 0, 0, 0, 0, 0, MandatoryLabelSid))
    {
        return ::GetLastError();
    }

    return ERROR_SUCCESS;
}
