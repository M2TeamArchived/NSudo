/*
 * PROJECT:   NShadow
 * FILE:      NShadow.cpp
 * PURPOSE:   Implementation for NShadow
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "stdafx.h"

#include "NShadow.h"

typedef struct _NSHADOW_ENVIRONMENT_CONFIGURATION
{
    std::wstring CurrentDirectory;
    std::vector<std::wstring> EnvironmentVariables;

    std::wstring TokenIntegrityLevel;
    std::vector<std::wstring> TokenPrivileges;

} NSHADOW_ENVIRONMENT_CONFIGURATION, *PNSHADOW_ENVIRONMENT_CONFIGURATION;


void x(
    /*_In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,

    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation,




    _In_opt_ HANDLE hToken,
    
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    

    //_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    //_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    //_In_ BOOL bInheritHandles,


    _In_        LPCWSTR lpUsername,
    _In_opt_    LPCWSTR lpDomain,
    _In_        LPCWSTR lpPassword,
    _In_        DWORD dwLogonFlags

    //_In_        HANDLE hToken,
    //_In_        DWORD dwLogonFlags*/
)
{
    /*CreateProcessAsUserW;
    CreateProcessW;

    CreateProcessWithLogonW;
    CreateProcessWithTokenW;*/
}
