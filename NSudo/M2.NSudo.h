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
        using ::NSudoAdjustTokenPrivileges;

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
    }
}

#endif
