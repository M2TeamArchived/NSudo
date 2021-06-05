/*
 * PROJECT:   NSudo Shared Library
 * FILE:      NSudoAPI.cpp
 * PURPOSE:   Implementation for NSudo Shared Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "NSudoAPI.h"

#include <Mile.Windows.h>

#include "M2.Base.h"

#include <cstdio>
#include <cwchar>

#include <string>
#include <type_traits>
#include <utility>

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#include <Userenv.h>
#pragma comment(lib, "Userenv.lib")
#endif

const std::wstring g_NSudoLogSplitter =
    L"****************************************************************\r\n";
static Mile::CriticalSection g_NSudoLogLock;
static std::wstring g_NSudoLog = g_NSudoLogSplitter;

EXTERN_C LPCWSTR WINAPI NSudoReadLog()
{
    Mile::AutoCriticalSectionLock Lock(g_NSudoLogLock);

    return g_NSudoLog.c_str();
}

EXTERN_C VOID WINAPI NSudoWriteLog(
    _In_ LPCWSTR Sender,
    _In_ LPCWSTR Content)
{
    Mile::AutoCriticalSectionLock Lock(g_NSudoLogLock);

    SYSTEMTIME SystemTime = { 0 };
    ::GetLocalTime(&SystemTime);

    g_NSudoLog += Mile::FormatString(
        L"\r\n"
        L"Sender: %s\r\n"
        L"DateTime: %d-%.2d-%.2d %.2d:%.2d:%.2d\r\n"
        L"Process ID: %d\r\n"
        L"Thread ID: %d\r\n"
        L"\r\n"
        L"%s\r\n"
        L"\r\n",
        Sender,
        SystemTime.wYear,
        SystemTime.wMonth,
        SystemTime.wDay,
        SystemTime.wHour,
        SystemTime.wMinute,
        SystemTime.wSecond,
        ::GetCurrentProcessId(),
        ::GetCurrentThreadId(),
        Content);
    g_NSudoLog += g_NSudoLogSplitter;
}

EXTERN_C HRESULT WINAPI NSudoCreateProcess(
    _In_ NSUDO_USER_MODE_TYPE UserModeType,
    _In_ NSUDO_PRIVILEGES_MODE_TYPE PrivilegesModeType,
    _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType,
    _In_ NSUDO_PROCESS_PRIORITY_CLASS_TYPE ProcessPriorityClassType,
    _In_ NSUDO_SHOW_WINDOW_MODE_TYPE ShowWindowModeType,
    _In_ DWORD WaitInterval,
    _In_ BOOL CreateNewConsole,
    _In_ LPCWSTR CommandLine,
    _In_opt_ LPCWSTR CurrentDirectory)
{
    DWORD MandatoryLabelRid;
    switch (MandatoryLabelType)
    {
    case NSUDO_MANDATORY_LABEL_TYPE::UNTRUSTED:
        MandatoryLabelRid = SECURITY_MANDATORY_UNTRUSTED_RID;
        break;
    case NSUDO_MANDATORY_LABEL_TYPE::LOW:
        MandatoryLabelRid = SECURITY_MANDATORY_LOW_RID;
        break;
    case NSUDO_MANDATORY_LABEL_TYPE::MEDIUM:
        MandatoryLabelRid = SECURITY_MANDATORY_MEDIUM_RID;
        break;
    case NSUDO_MANDATORY_LABEL_TYPE::MEDIUM_PLUS:
        MandatoryLabelRid = SECURITY_MANDATORY_MEDIUM_PLUS_RID;
        break;
    case NSUDO_MANDATORY_LABEL_TYPE::HIGH:
        MandatoryLabelRid = SECURITY_MANDATORY_HIGH_RID;
        break;
    case NSUDO_MANDATORY_LABEL_TYPE::SYSTEM:
        MandatoryLabelRid = SECURITY_MANDATORY_SYSTEM_RID;
        break;
    case NSUDO_MANDATORY_LABEL_TYPE::PROTECTED_PROCESS:
        MandatoryLabelRid = SECURITY_MANDATORY_PROTECTED_PROCESS_RID;
        break;
    default:
        return E_INVALIDARG;
    }

    DWORD ProcessPriority;
    switch (ProcessPriorityClassType)
    {
    case NSUDO_PROCESS_PRIORITY_CLASS_TYPE::IDLE:
        ProcessPriority = IDLE_PRIORITY_CLASS;
        break;
    case NSUDO_PROCESS_PRIORITY_CLASS_TYPE::BELOW_NORMAL:
        ProcessPriority = BELOW_NORMAL_PRIORITY_CLASS;
        break;
    case NSUDO_PROCESS_PRIORITY_CLASS_TYPE::NORMAL:
        ProcessPriority = NORMAL_PRIORITY_CLASS;
        break;
    case NSUDO_PROCESS_PRIORITY_CLASS_TYPE::ABOVE_NORMAL:
        ProcessPriority = ABOVE_NORMAL_PRIORITY_CLASS;
        break;
    case NSUDO_PROCESS_PRIORITY_CLASS_TYPE::HIGH:
        ProcessPriority = HIGH_PRIORITY_CLASS;
        break;
    case NSUDO_PROCESS_PRIORITY_CLASS_TYPE::REALTIME:
        ProcessPriority = REALTIME_PRIORITY_CLASS;
        break;
    default:
        return E_INVALIDARG;
    }

    DWORD ShowWindowMode;
    switch (ShowWindowModeType)
    {
    case NSUDO_SHOW_WINDOW_MODE_TYPE::DEFAULT:
        ShowWindowMode = SW_SHOWDEFAULT;
        break;
    case NSUDO_SHOW_WINDOW_MODE_TYPE::SHOW:
        ShowWindowMode = SW_SHOW;
        break;
    case NSUDO_SHOW_WINDOW_MODE_TYPE::HIDE:
        ShowWindowMode = SW_HIDE;
        break;
    case NSUDO_SHOW_WINDOW_MODE_TYPE::MAXIMIZE:
        ShowWindowMode = SW_MAXIMIZE;
        break;
    case NSUDO_SHOW_WINDOW_MODE_TYPE::MINIMIZE:
        ShowWindowMode = SW_MINIMIZE;
        break;
    default:
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;

    DWORD SessionID = static_cast<DWORD>(-1);

    HANDLE CurrentProcessToken = INVALID_HANDLE_VALUE;
    HANDLE DuplicatedCurrentProcessToken = INVALID_HANDLE_VALUE;
    
    HANDLE OriginalSystemToken = INVALID_HANDLE_VALUE;
    HANDLE SystemToken = INVALID_HANDLE_VALUE;

    HANDLE hToken = INVALID_HANDLE_VALUE;
    HANDLE OriginalToken = INVALID_HANDLE_VALUE;

    auto Handler = Mile::ScopeExitTaskHandler([&]()
        {
            if (CurrentProcessToken !=INVALID_HANDLE_VALUE)
            {
                ::CloseHandle(CurrentProcessToken);
            }

            if (DuplicatedCurrentProcessToken != INVALID_HANDLE_VALUE)
            {
                ::CloseHandle(DuplicatedCurrentProcessToken);
            }

            if (OriginalSystemToken != INVALID_HANDLE_VALUE)
            {
                ::CloseHandle(OriginalSystemToken);
            }

            if (SystemToken != INVALID_HANDLE_VALUE)
            {
                ::CloseHandle(SystemToken);
            }

            if (hToken != INVALID_HANDLE_VALUE)
            {
                ::CloseHandle(hToken);
            }

            if (OriginalToken != INVALID_HANDLE_VALUE)
            {
                ::CloseHandle(OriginalToken);
            }

            ::SetThreadToken(nullptr, nullptr);
        });

    hr = Mile::HResultFromLastError(::OpenProcessToken(
        ::GetCurrentProcess(), MAXIMUM_ALLOWED, &CurrentProcessToken));
    if (hr != S_OK)
    {
        return hr;
    }

    hr = Mile::HResultFromLastError(::DuplicateTokenEx(
        CurrentProcessToken,
        MAXIMUM_ALLOWED,
        nullptr,
        SecurityImpersonation,
        TokenImpersonation,
        &DuplicatedCurrentProcessToken));
    if (hr != S_OK)
    {
        return hr;
    }

    LUID_AND_ATTRIBUTES RawPrivilege;

    hr = Mile::HResultFromLastError(::LookupPrivilegeValueW(
        nullptr, SE_DEBUG_NAME, &RawPrivilege.Luid));
    if (hr != S_OK)
    {
        return hr;
    }

    RawPrivilege.Attributes = SE_PRIVILEGE_ENABLED;

    hr = Mile::AdjustTokenPrivilegesSimple(
        DuplicatedCurrentProcessToken,
        &RawPrivilege,
        1);
    if (hr != S_OK)
    {
        return hr;
    }

    hr = Mile::HResultFromLastError(::SetThreadToken(
        nullptr, DuplicatedCurrentProcessToken));
    if (hr != S_OK)
    {
        return hr;
    }

    SessionID = Mile::GetActiveSessionID();
    if (SessionID == static_cast<DWORD>(-1))
    {
        return Mile::HResult::FromWin32(ERROR_NO_TOKEN);
    }

    hr = Mile::CreateSystemToken(MAXIMUM_ALLOWED, &OriginalSystemToken);
    if (hr != S_OK)
    {
        return hr;
    }

    hr = Mile::HResultFromLastError(::DuplicateTokenEx(
        OriginalSystemToken,
        MAXIMUM_ALLOWED,
        nullptr,
        SecurityImpersonation,
        TokenImpersonation,
        &SystemToken));
    if (hr != S_OK)
    {
        return hr;
    }

    hr = Mile::AdjustTokenAllPrivileges(
        SystemToken,
        SE_PRIVILEGE_ENABLED);
    if (hr != S_OK)
    {
        return hr;
    }

    hr = Mile::HResultFromLastError(::SetThreadToken(
        nullptr, SystemToken));
    if (hr != S_OK)
    {
        return hr;
    }

    if (NSUDO_USER_MODE_TYPE::TRUSTED_INSTALLER == UserModeType)
    {
        hr = Mile::OpenServiceProcessToken(
            L"TrustedInstaller",
            MAXIMUM_ALLOWED,
            &OriginalToken);
        if (hr != S_OK)
        {
            return hr;
        }
    }
    else if (NSUDO_USER_MODE_TYPE::SYSTEM == UserModeType)
    {
        hr = Mile::CreateSystemToken(MAXIMUM_ALLOWED, &OriginalToken);
        if (hr != S_OK)
        {
            return hr;
        }
    }
    else if (NSUDO_USER_MODE_TYPE::CURRENT_USER == UserModeType)
    {
        hr = Mile::CreateSessionToken(SessionID, &OriginalToken);
        if (hr != S_OK)
        {
            return hr;
        }
    }
    else if (NSUDO_USER_MODE_TYPE::CURRENT_PROCESS == UserModeType)
    {
        hr = Mile::HResultFromLastError(::OpenProcessToken(
            ::GetCurrentProcess(), MAXIMUM_ALLOWED, &OriginalToken));
        if (hr != S_OK)
        {
            return hr;
        }
    }
    else if (NSUDO_USER_MODE_TYPE::CURRENT_PROCESS_DROP_RIGHT == UserModeType)
    {
        HANDLE hCurrentProcessToken = nullptr;
        hr = Mile::HResultFromLastError(::OpenProcessToken(
            ::GetCurrentProcess(), MAXIMUM_ALLOWED, &hCurrentProcessToken));
        if (hr == S_OK)
        {
            hr = Mile::CreateLUAToken(hCurrentProcessToken, &OriginalToken);

            ::CloseHandle(hCurrentProcessToken);
        }

        if (hr != S_OK)
        {
            return hr;
        }
    }
    else if (NSUDO_USER_MODE_TYPE::CURRENT_USER_ELEVATED == UserModeType)
    {
        HANDLE hCurrentProcessToken = nullptr;
        hr = Mile::CreateSessionToken(SessionID, &hCurrentProcessToken);
        if (hr == S_OK)
        {
            TOKEN_LINKED_TOKEN LinkedToken = { 0 };
            DWORD ReturnLength = 0;

            hr = Mile::HResultFromLastError(::GetTokenInformation(
                hCurrentProcessToken,
                TokenLinkedToken,
                &LinkedToken,
                sizeof(TOKEN_LINKED_TOKEN),
                &ReturnLength));
            if (hr == S_OK)
            {
                hr = Mile::HResultFromLastError(::DuplicateTokenEx(
                    LinkedToken.LinkedToken,
                    MAXIMUM_ALLOWED,
                    nullptr,
                    SecurityIdentification,
                    TokenPrimary,
                    &OriginalToken));

                ::CloseHandle(LinkedToken.LinkedToken);
            }

            ::CloseHandle(hCurrentProcessToken);
        }
    }
    else
    {
        return E_INVALIDARG;
    }

    hr = Mile::HResultFromLastError(::DuplicateTokenEx(
        OriginalToken,
        MAXIMUM_ALLOWED,
        nullptr,
        SecurityIdentification,
        TokenPrimary,
        &hToken));
    if (hr != S_OK)
    {
        return hr;
    }

    hr = Mile::HResultFromLastError(::SetTokenInformation(
        hToken,
        TokenSessionId,
        (PVOID)&SessionID,
        sizeof(DWORD)));
    if (hr != S_OK)
    {
        return hr;
    }

    switch (PrivilegesModeType)
    {
    case NSUDO_PRIVILEGES_MODE_TYPE::ENABLE_ALL_PRIVILEGES:

        hr = Mile::AdjustTokenAllPrivileges(hToken, SE_PRIVILEGE_ENABLED);
        if (hr != S_OK)
        {
            return hr;
        }

        break;
    case NSUDO_PRIVILEGES_MODE_TYPE::DISABLE_ALL_PRIVILEGES:

        hr = Mile::AdjustTokenAllPrivileges(hToken, 0);
        if (hr != S_OK)
        {
            return hr;
        }

        break;
    default:
        break;
    }

    if (NSUDO_MANDATORY_LABEL_TYPE::UNTRUSTED != MandatoryLabelType)
    {
        hr = Mile::SetTokenMandatoryLabel(hToken, MandatoryLabelRid);
        if (hr != S_OK)
        {
            return hr;
        }
    }

    DWORD dwCreationFlags = CREATE_SUSPENDED | CREATE_UNICODE_ENVIRONMENT;

    if (CreateNewConsole)
    {
        dwCreationFlags |= CREATE_NEW_CONSOLE;
    }

    STARTUPINFOW StartupInfo = { 0 };
    PROCESS_INFORMATION ProcessInfo = { 0 };

    StartupInfo.cb = sizeof(STARTUPINFOW);

    StartupInfo.lpDesktop = const_cast<LPWSTR>(L"WinSta0\\Default");

    StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = static_cast<WORD>(ShowWindowMode);

    LPVOID lpEnvironment = nullptr;

    hr = Mile::HResultFromLastError(::CreateEnvironmentBlock(
        &lpEnvironment, hToken, TRUE));
    if (hr == S_OK)
    {
        std::wstring ExpandedString = Mile::ExpandEnvironmentStringsW(
            std::wstring(CommandLine));
        if (hr == S_OK)
        {
            hr = Mile::HResultFromLastError(::CreateProcessAsUserW(
                hToken,
                nullptr,
                const_cast<LPWSTR>(ExpandedString.c_str()),
                nullptr,
                nullptr,
                FALSE,
                dwCreationFlags,
                lpEnvironment,
                CurrentDirectory,
                &StartupInfo,
                &ProcessInfo));
            if (hr == S_OK)
            {
                ::SetPriorityClass(ProcessInfo.hProcess, ProcessPriority);

                ::ResumeThread(ProcessInfo.hThread);

                ::WaitForSingleObjectEx(
                    ProcessInfo.hProcess, WaitInterval, FALSE);

                ::CloseHandle(ProcessInfo.hProcess);
                ::CloseHandle(ProcessInfo.hThread);
            }
        }

        ::DestroyEnvironmentBlock(lpEnvironment);
    }

    return S_OK;
}

//HANDLE UserToken = INVALID_HANDLE_VALUE;
    //if (::LogonUserExW(
    //    L"YoloUser",
    //    L".",
    //    L"123456",
    //    LOGON32_LOGON_INTERACTIVE,
    //    LOGON32_PROVIDER_DEFAULT,
    //    &UserToken,
    //    nullptr,
    //    nullptr,
    //    nullptr,
    //    nullptr))
    //{
    //    //BOOL re = ImpersonateLoggedOnUser(UserToken);
    //    //re = re;

    //    DWORD ReturnLength = 0;
    //    TOKEN_LINKED_TOKEN LinkedToken = { 0 };
    //    hr = g_ResourceManagement.pNSudoClient->GetTokenInformation(UserToken, TokenLinkedToken, &LinkedToken, sizeof(LinkedToken), &ReturnLength);

    //    

    //    PROFILEINFOW ProfileInfo = { 0 };
    //    ProfileInfo.dwSize = sizeof(PROFILEINFOW);
    //    ProfileInfo.lpUserName = L"YoloUser";

    //    if (::LoadUserProfileW(LinkedToken.LinkedToken, &ProfileInfo))
    //    {

    //        //hr = g_ResourceManagement.pNSudoClient->GetTokenInformation(UserToken, TokenLogonSid);

    //        //wchar_t NameBuffer[260];
    //        //DWORD LengthNeeded = 0;
    //        //::GetUserObjectInformationW(
    //        //    //::GetProcessWindowStation(),
    //        //    ::GetThreadDesktop(::GetCurrentThreadId()),
    //        //    UOI_NAME,
    //        //    NameBuffer,
    //        //    sizeof(NameBuffer),
    //        //    &LengthNeeded);

    //        /*DWORD ReturnLength = 0;
    //        hr = g_ResourceManagement.pNSudoClient->GetTokenInformation(
    //            UserToken,
    //            TokenSessionId,
    //            &dwSessionID,
    //            sizeof(DWORD),
    //            &ReturnLength);*/

    //        //::ImpersonateLoggedOnUser(UserToken);
    //        NSudoCreateProcess(
    //            LinkedToken.LinkedToken,
    //            L"E:\\source\\repos\\GUIDemoForLegacyWindows\\Release\\GUIDemoForLegacyWindows.exe",
    //            nullptr,
    //            INFINITE);

    //        HRESULT hr2 = ::GetLastError();
    //        hr2 = hr2;

    //        ::UnloadUserProfile(LinkedToken.LinkedToken, ProfileInfo.hProfile);
    //    }

    //    ::CloseHandle(UserToken);
    //}


    // 0xc0000142

/*virtual HRESULT STDMETHODCALLTYPE ExCreateFile()
    {
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE ExRegCreateKey()
    {
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE CreateAppContainer(
        _In_ PCWSTR AppContainerName,
        _In_ PCWSTR DisplayName,
        _In_ PCWSTR Description,
        _In_opt_ PSID_AND_ATTRIBUTES Capabilities,
        _In_ DWORD CapabilityCount,
        _Out_ PSID* AppContainerSid)
    {
        HRESULT hr = S_OK;

        HMODULE Module = ::LoadLibraryExW(
            L"userenv.dll",
            nullptr,
            LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (Module)
        {
            decltype(::CreateAppContainerProfile)* Procedure =
                reinterpret_cast<decltype(::CreateAppContainerProfile)*>(
                    ::GetProcAddress(Module, "CreateAppContainerProfile"));
            if (Procedure)
            {
                hr = Procedure(
                    AppContainerName,
                    DisplayName,
                    Description,
                    Capabilities,
                    CapabilityCount,
                    AppContainerSid);
            }
            else
            {
                hr = ::HRESULT_FROM_WIN32(::GetLastError());
            }

            ::FreeLibrary(Module);
        }
        else
        {
            hr = ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return hr ;
    }

    virtual HRESULT STDMETHODCALLTYPE DeleteAppContainer(
        _In_ PCWSTR AppContainerName)
    {
        HRESULT hr = S_OK;

        HMODULE Module = ::LoadLibraryExW(
            L"userenv.dll",
            nullptr,
            LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (Module)
        {
            decltype(::DeleteAppContainerProfile)* Procedure =
                reinterpret_cast<decltype(::DeleteAppContainerProfile)*>(
                    ::GetProcAddress(Module, "DeleteAppContainerProfile"));
            if (Procedure)
            {
                hr = Procedure(AppContainerName);
            }
            else
            {
                hr = ::HRESULT_FROM_WIN32(::GetLastError());
            }

            ::FreeLibrary(Module);
        }
        else
        {
            hr = ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return hr;
    }

    virtual HRESULT STDMETHODCALLTYPE CreateAppContainerContext()
    {
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE ExExpandEnvironmentStrings()
    {
        return E_NOTIMPL;
    }

    virtual HRESULT STDMETHODCALLTYPE ExCreateProcess()
    {
        return E_NOTIMPL;
    }*/

