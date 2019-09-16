/*
 * PROJECT:   NSudo
 * FILE:      NSudoAPI.h
 * PURPOSE:   Definition for NSudo Shared Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef NSUDO_API
#define NSUDO_API

#include <Windows.h>

/**
 * Enables or disables privileges in the specified access token.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token.
 * @param Privileges A pointer to an array of LUID_AND_ATTRIBUTES structures
 *                   that specifies an array of privileges and their attributes.
 *                   Each structure contains the LUID and attributes of a
 *                   privilege. To get the name of the privilege associated with
 *                   a LUID, call the LookupPrivilegeName function, passing the
 *                   address of the LUID as the value of the lpLuid parameter.
 *                   The attributes of a privilege can be a combination of the
 *                   following values.
 *                   SE_PRIVILEGE_ENABLED
 *                       The function enables the privilege.
 *                   SE_PRIVILEGE_REMOVED
 *                       The privilege is removed from the list of privileges in
 *                       the token.
 *                   None
 *                       The function disables the privilege.
 * @param PrivilegeCount The number of entries in the Privileges array.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see AdjustTokenPrivileges.
 */
EXTERN_C DWORD WINAPI NSudoAdjustTokenPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ PLUID_AND_ATTRIBUTES Privileges,
    _In_ DWORD PrivilegeCount);

/**
 * Contains values that specify the type of mandatory label.
 */
typedef enum _NSUDO_MANDATORY_LABEL_TYPE
{
    UNTRUSTED,
    LOW,
    MEDIUM,
    MEDIUM_PLUS,
    HIGH,
    SYSTEM,
    PROTECTED_PROCESS,
} NSUDO_MANDATORY_LABEL_TYPE, *PNSUDO_MANDATORY_LABEL_TYPE;

/**
 * Allocates and initializes a mandatory label security identifier (SID).
 *
 * @param MandatoryLabelSid A pointer to a variable that receives the pointer to
 *        the allocated and initialized mandatory label SID structure.
 * @param MandatoryLabelType A value from the MANDATORY_LABEL_TYPE enumerated
 *        type that identifies the mandatory label.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark A SID allocated with the NSudoCreateMandatoryLabelSid function must
 *         be freed by using the FreeSid function.
 */
EXTERN_C DWORD WINAPI NSudoCreateMandatoryLabelSid(
    _Out_ PSID* MandatoryLabelSid,
    _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType);

#endif
