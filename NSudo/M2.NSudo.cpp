/*
 * PROJECT:   NSudo
 * FILE:      M2.NSudo.cpp
 * PURPOSE:   Implementation for NSudo Shared Library C++ Wrapper
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "M2.NSudo.h"

/**
 * @remark You can read the definition for this function in "M2.NSudo.h".
 */
DWORD M2::NSudo::AdjustTokenPrivileges(
    HANDLE TokenHandle,
    std::map<std::wstring, DWORD> const& Privileges)
{
    std::vector<LUID_AND_ATTRIBUTES> RawPrivileges;

    for (auto const& Privilege : Privileges)
    {
        LUID_AND_ATTRIBUTES RawPrivilege;

        if (!::LookupPrivilegeValueW(
            nullptr, Privilege.first.c_str(), &RawPrivilege.Luid))
        {
            return ::GetLastError();
        }

        RawPrivilege.Attributes = Privilege.second;

        RawPrivileges.push_back(RawPrivilege);
    }

    return NSudoAdjustTokenPrivileges(
        TokenHandle,
        &RawPrivileges[0],
        static_cast<DWORD>(RawPrivileges.size()));
}
