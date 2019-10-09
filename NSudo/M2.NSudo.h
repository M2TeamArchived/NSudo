/*
 * PROJECT:   NSudo
 * FILE:      M2.NSudo.h
 * PURPOSE:   Definition for NSudo Shared Library C++ Wrapper
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef M2_NSUDO
#define M2_NSUDO

#ifndef __cplusplus
#error "[M2.NSudo] You should use a C++ compiler."
#endif

#include "NSudoAPI.h"

#include <map>
#include <string>
#include <vector>

namespace M2
{
    namespace NSudo
    {
        using ::NSudoGetFeatureLevel;
        using ::NSudoAdjustTokenPrivileges;
        using ::NSUDO_MANDATORY_LABEL_TYPE;
        using ::PNSUDO_MANDATORY_LABEL_TYPE;
        using ::NSudoCreateMandatoryLabelSid;
        using ::NSudoStartService;
        using ::NSudoOpenProcess;
        using ::NSudoOpenServiceProcess;
        using ::NSudoOpenProcessTokenByProcessHandle;
        using ::NSudoOpenCurrentProcessToken;
        using ::NSudoOpenProcessTokenByProcessId;
        using ::NSudoOpenServiceProcessToken;
        using ::NSudoOpenLsassProcess;
        using ::NSudoOpenLsassProcessToken;
        using ::NSudoCreateSessionToken;
        using ::NSudoAllocMemory;
        using ::NSudoFreeMemory;
        using ::NSudoGetTokenInformation;
        using ::NSudoGetTokenInformationWithMemory;
        using ::NSudoSetTokenInformation;
        using ::NSudoSetTokenMandatoryLabel;

        /**
         * Enables or disables privileges in the specified access token.
         *
         * @param TokenHandle A handle to the access token that contains the
         *                    privileges to be modified. The handle must have
         *                    TOKEN_ADJUST_PRIVILEGES access to the token.
         * @param Privileges A key value map of privilege name and attributes.
         *                   The attributes of a privilege can be a combination
         *                   of the following values.
         *                   SE_PRIVILEGE_ENABLED
         *                       The function enables the privilege.
         *                   SE_PRIVILEGE_REMOVED
         *                       The privilege is removed from the list of
         *                       privileges in the token.
         *                   None
         *                       The function disables the privilege.
         * @return Standard Win32 Error. If the function succeeds, the return
         *         value is ERROR_SUCCESS.
         * @remark For more information, see AdjustTokenPrivileges.
         */
        DWORD AdjustTokenPrivileges(
            HANDLE TokenHandle,
            std::map<std::wstring, DWORD> const& Privileges);

        /**
         * Retrieves a specified type of information about an access token. The
         * calling process must have appropriate access rights to obtain the
         * information.
         *
         * @param OutputInformation A pointer to a buffer the function fills
         *                          with the requested information. When you
         *                          have finished using the information, free
         *                          it by calling the NSudoFreeMemory function.
         *                          You should also set the pointer to NULL.
         * @param TokenHandle A handle to an access token from which
         *                    information is retrieved.
         * @param TokenInformationClass Specifies a value from the
         *                              TOKEN_INFORMATION_CLASS enumerated type
         *                              to identify the type of information the
         *                              function retrieves.
         * @return Standard Win32 Error. If the function succeeds, the return
         *         value is ERROR_SUCCESS.
         * @remark For more information, see GetTokenInformation.
         */
        template<typename InformationType>
        DWORD GetTokenInformationWithMemory(
            _Out_ InformationType& OutputInformation,
            _In_ HANDLE TokenHandle,
            _In_ TOKEN_INFORMATION_CLASS TokenInformationClass)
        {
            return NSudoGetTokenInformationWithMemory(
                reinterpret_cast<PVOID*>(&OutputInformation),
                TokenHandle,
                TokenInformationClass);
        }
    }
}

#endif
