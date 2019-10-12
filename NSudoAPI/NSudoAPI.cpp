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

#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")

/**
 * NSudo Shared Library Interface Implementation
 */
class CNSudoClient : public M2::Base::CComClass<CNSudoClient, INSudoClient>
{
private:


public:

    M2_BASE_COM_INTERFACE_MAP_BEGIN;
        M2_BASE_COM_INTERFACE_ENTRY(INSudoClient);
    M2_BASE_COM_INTERFACE_MAP_END;

    CNSudoClient() = default;

    virtual ~CNSudoClient() = default;

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE AllocMemory(
        _In_ SIZE_T Size,
        _Out_ LPVOID* Block)
    {
        *Block = ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
        return *Block ? S_OK : ::HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE ReAllocMemory(
        _In_ PVOID OldBlock,
        _In_ SIZE_T NewSize,
        _Out_ PVOID* NewBlock)
    {
        *NewBlock = ::HeapReAlloc(
            ::GetProcessHeap(), HEAP_ZERO_MEMORY, OldBlock, NewSize);
        return *NewBlock ? S_OK : ::HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE FreeMemory(
        _In_ LPVOID Block)
    {
        if (::HeapFree(::GetProcessHeap(), 0, Block))
        {
            return S_OK;
        }
        else
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE GetTokenInformation(
        _In_ HANDLE TokenHandle,
        _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
        _Out_opt_ LPVOID TokenInformation,
        _In_ DWORD TokenInformationLength,
        _Out_ PDWORD ReturnLength)
    {
        if (::GetTokenInformation(
            TokenHandle,
            TokenInformationClass,
            TokenInformation,
            TokenInformationLength,
            ReturnLength))
        {
            return S_OK;
        }
        else
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }
    }

    /**
      * @remark You can read the definition for this function in "NSudoAPI.h".
      */
    virtual HRESULT STDMETHODCALLTYPE GetTokenInformationWithMemory(
        _In_ HANDLE TokenHandle,
        _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
        _Out_ PVOID* OutputInformation)
    {
        *OutputInformation = nullptr;

        DWORD Length = 0;

        HRESULT hr = this->GetTokenInformation(
            TokenHandle,
            TokenInformationClass,
            nullptr,
            0,
            &Length);
        if (hr == ::HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
        {
            hr = this->AllocMemory(Length, OutputInformation);
            if (hr == S_OK)
            {
                hr = this->GetTokenInformation(
                    TokenHandle,
                    TokenInformationClass,
                    *OutputInformation,
                    Length,
                    &Length);
                if (hr != S_OK)
                {
                    this->FreeMemory(*OutputInformation);
                    *OutputInformation = nullptr;
                }
            }
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE SetTokenInformation(
        _In_ HANDLE TokenHandle,
        _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
        _In_ LPVOID TokenInformation,
        _In_ DWORD TokenInformationLength)
    {
        if (::SetTokenInformation(
            TokenHandle,
            TokenInformationClass,
            TokenInformation,
            TokenInformationLength))
        {
            return S_OK;
        }
        else
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE AdjustTokenPrivileges(
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

            hr = this->AllocMemory(TPSize, reinterpret_cast<LPVOID*>(&pTP));
            if (hr == S_OK)
            {
                pTP->PrivilegeCount = PrivilegeCount;
                memcpy(pTP->Privileges, Privileges, PSize);

                ::AdjustTokenPrivileges(
                    TokenHandle, FALSE, pTP, TPSize, nullptr, nullptr);
                hr = ::HRESULT_FROM_WIN32(::GetLastError());

                this->FreeMemory(pTP);
            }
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE AdjustTokenAllPrivileges(
        _In_ HANDLE TokenHandle,
        _In_ DWORD Attributes)
    {
        PTOKEN_PRIVILEGES pTokenPrivileges = nullptr;

        HRESULT hr = this->GetTokenInformationWithMemory(
            TokenHandle,
            TokenPrivileges,
            reinterpret_cast<PVOID*>(&pTokenPrivileges));
        if (hr == S_OK)
        {
            for (DWORD i = 0; i < pTokenPrivileges->PrivilegeCount; ++i)
            {
                pTokenPrivileges->Privileges[i].Attributes = Attributes;
            }

            hr = this->AdjustTokenPrivileges(
                TokenHandle,
                pTokenPrivileges->Privileges,
                pTokenPrivileges->PrivilegeCount);

            this->FreeMemory(pTokenPrivileges);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE CreateMandatoryLabelSid(
        _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType,
        _Out_ PSID* MandatoryLabelSid)
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

        SID_IDENTIFIER_AUTHORITY SIA = SECURITY_MANDATORY_LABEL_AUTHORITY;

        if (!::AllocateAndInitializeSid(
            &SIA, 1, MandatoryLabelRid, 0, 0, 0, 0, 0, 0, 0, MandatoryLabelSid))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE SetTokenMandatoryLabel(
        _In_ HANDLE TokenHandle,
        _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType)
    {
        TOKEN_MANDATORY_LABEL TML;

        HRESULT hr = this->CreateMandatoryLabelSid(
            MandatoryLabelType, &TML.Label.Sid);
        if (hr == S_OK)
        {
            TML.Label.Attributes = SE_GROUP_INTEGRITY;

            hr = this->SetTokenInformation(
                TokenHandle, TokenIntegrityLevel, &TML, sizeof(TML));

            ::FreeSid(TML.Label.Sid);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE StartWindowsService(
        _In_ LPCWSTR ServiceName,
        _Out_ LPSERVICE_STATUS_PROCESS ServiceStatus)
    {
        HRESULT hr = E_INVALIDARG;

        if (ServiceStatus && ServiceName)
        {
            hr = S_OK;

            memset(ServiceStatus, 0, sizeof(LPSERVICE_STATUS_PROCESS));

            SC_HANDLE hSCM = ::OpenSCManagerW(
                nullptr, nullptr, SC_MANAGER_CONNECT);
            if (hSCM)
            {
                SC_HANDLE hService = ::OpenServiceW(
                    hSCM, ServiceName, SERVICE_QUERY_STATUS | SERVICE_START);
                if (hService)
                {
                    DWORD nBytesNeeded = 0;
                    DWORD nOldCheckPoint = 0;
                    ULONGLONG nLastTick = 0;
                    bool bStartServiceWCalled = false;

                    while (::QueryServiceStatusEx(
                        hService,
                        SC_STATUS_PROCESS_INFO,
                        reinterpret_cast<LPBYTE>(ServiceStatus),
                        sizeof(SERVICE_STATUS_PROCESS),
                        &nBytesNeeded))
                    {
                        if (SERVICE_STOPPED == ServiceStatus->dwCurrentState)
                        {
                            // Failed if the service had stopped again.
                            if (bStartServiceWCalled)
                            {
                                hr = S_FALSE;
                                break;
                            }

                            if (!::StartServiceW(hService, 0, nullptr))
                            {
                                hr = ::HRESULT_FROM_WIN32(::GetLastError());
                                break;
                            }

                            bStartServiceWCalled = true;
                        }
                        else if (
                            SERVICE_STOP_PENDING
                            == ServiceStatus->dwCurrentState ||
                            SERVICE_START_PENDING
                            == ServiceStatus->dwCurrentState)
                        {
                            ULONGLONG nCurrentTick = ::GetTickCount64();

                            if (!nLastTick)
                            {
                                nLastTick = nCurrentTick;
                                nOldCheckPoint = ServiceStatus->dwCheckPoint;

                                // Same as the .Net System.ServiceProcess, wait
                                // 250ms.
                                ::SleepEx(250, FALSE);
                            }
                            else
                            {
                                // Check the timeout if the checkpoint is not
                                // increased.
                                if (ServiceStatus->dwCheckPoint
                                    <= nOldCheckPoint)
                                {
                                    ULONGLONG nDiff = nCurrentTick - nLastTick;
                                    if (nDiff > ServiceStatus->dwWaitHint)
                                    {
                                        hr = ::HRESULT_FROM_WIN32(
                                            ERROR_TIMEOUT);
                                        break;
                                    }
                                }

                                // Continue looping.
                                nLastTick = 0;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    ::CloseServiceHandle(hService);
                }
                else
                {
                    hr = ::HRESULT_FROM_WIN32(::GetLastError());
                }

                ::CloseServiceHandle(hSCM);
            }
            else
            {
                hr = ::HRESULT_FROM_WIN32(::GetLastError());
            }
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE CreateSessionToken(
        _In_ DWORD SessionId,
        _Out_ PHANDLE TokenHandle)
    {
        if (::WTSQueryUserToken(SessionId, TokenHandle))
        {
            return S_OK;
        }
        else
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE CreateRestrictedToken(
        _In_ HANDLE ExistingTokenHandle,
        _In_ DWORD Flags,
        _In_ DWORD DisableSidCount,
        _In_opt_ PSID_AND_ATTRIBUTES SidsToDisable,
        _In_ DWORD DeletePrivilegeCount,
        _In_opt_ PLUID_AND_ATTRIBUTES PrivilegesToDelete,
        _In_ DWORD RestrictedSidCount,
        _In_opt_ PSID_AND_ATTRIBUTES SidsToRestrict,
        _Out_ PHANDLE NewTokenHandle)
    {
        if (::CreateRestrictedToken(
            ExistingTokenHandle,
            Flags,
            DisableSidCount,
            SidsToDisable,
            DeletePrivilegeCount,
            PrivilegesToDelete,
            RestrictedSidCount,
            SidsToRestrict,
            NewTokenHandle))
        {
            return S_OK;
        }
        else
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE CreateLUAToken(
        _In_ HANDLE ExistingTokenHandle,
        _Out_ PHANDLE TokenHandle)
    {
        HRESULT hr = E_INVALIDARG;

        PTOKEN_USER pTokenUser = nullptr;
        TOKEN_OWNER Owner = { 0 };
        PTOKEN_DEFAULT_DACL pTokenDacl = nullptr;
        DWORD Length = 0;
        PACL NewDefaultDacl = nullptr;
        TOKEN_DEFAULT_DACL NewTokenDacl = { 0 };
        PACCESS_ALLOWED_ACE pTempAce = nullptr;
        BOOL EnableTokenVirtualization = TRUE;

        do
        {
            if (!TokenHandle)
            {
                break;
            }

            hr = this->CreateRestrictedToken(
                ExistingTokenHandle, LUA_TOKEN,
                0, nullptr, 0, nullptr, 0, nullptr, TokenHandle);
            if (hr != S_OK)
            {
                break;
            }

            hr = this->SetTokenMandatoryLabel(
                *TokenHandle, NSUDO_MANDATORY_LABEL_TYPE::MEDIUM);
            if (hr != S_OK)
            {
                break;
            }

            hr = this->GetTokenInformationWithMemory(
                *TokenHandle,
                TokenUser,
                reinterpret_cast<PVOID*>(&pTokenUser));
            if (hr != S_OK)
            {
                break;
            }

            Owner.Owner = pTokenUser->User.Sid;
            hr = this->SetTokenInformation(
                *TokenHandle, TokenOwner, &Owner, sizeof(TOKEN_OWNER));
            if (hr != S_OK)
            {
                break;
            }

            hr = this->GetTokenInformationWithMemory(
                *TokenHandle,
                TokenDefaultDacl,
                reinterpret_cast<PVOID*>(&pTokenDacl));
            if (hr != S_OK)
            {
                break;
            }

            Length = pTokenDacl->DefaultDacl->AclSize;
            Length += ::GetLengthSid(pTokenUser->User.Sid);
            Length += sizeof(ACCESS_ALLOWED_ACE);

            hr = this->AllocMemory(
                Length, reinterpret_cast<PVOID*>(&NewDefaultDacl));
            if (hr != S_OK)
            {
                break;
            }
            NewTokenDacl.DefaultDacl = NewDefaultDacl;

            if (!::InitializeAcl(
                NewTokenDacl.DefaultDacl,
                Length,
                pTokenDacl->DefaultDacl->AclRevision))
            {
                hr = ::HRESULT_FROM_WIN32(::GetLastError());
                break;
            }

            if (!::AddAccessAllowedAce(
                NewTokenDacl.DefaultDacl,
                pTokenDacl->DefaultDacl->AclRevision,
                GENERIC_ALL,
                pTokenUser->User.Sid))
            {
                hr = ::HRESULT_FROM_WIN32(::GetLastError());
                break;
            }

            for (ULONG i = 0;
                ::GetAce(pTokenDacl->DefaultDacl, i, (PVOID*)&pTempAce);
                ++i)
            {
                if (::IsWellKnownSid(
                    &pTempAce->SidStart,
                    WELL_KNOWN_SID_TYPE::WinBuiltinAdministratorsSid))
                    continue;

                ::AddAce(
                    NewTokenDacl.DefaultDacl,
                    pTokenDacl->DefaultDacl->AclRevision,
                    0,
                    pTempAce,
                    pTempAce->Header.AceSize);
            }

            Length += sizeof(TOKEN_DEFAULT_DACL);
            hr = this->SetTokenInformation(
                *TokenHandle, TokenDefaultDacl, &NewTokenDacl, Length);
            if (hr != S_OK)
            {
                break;
            }

            hr = this->SetTokenInformation(
                *TokenHandle,
                TokenVirtualizationEnabled,
                &EnableTokenVirtualization,
                sizeof(BOOL));
            if (hr != S_OK)
            {
                break;
            }

        } while (false);

        if (NewDefaultDacl)
        {
            this->FreeMemory(NewDefaultDacl);
        }

        if (pTokenDacl)
        {
            this->FreeMemory(pTokenDacl);
        }

        if (pTokenUser)
        {
            this->FreeMemory(pTokenUser);
        }

        if (hr != S_OK)
        {
            ::CloseHandle(TokenHandle);
            *TokenHandle = INVALID_HANDLE_VALUE;
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE SetCurrentThreadToken(
        _In_opt_ HANDLE TokenHandle)
    {
        if (!::SetThreadToken(nullptr, TokenHandle))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

    /**
     * @remark You can read the definition for this function in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE DuplicateToken(
        _In_ HANDLE ExistingTokenHandle,
        _In_ DWORD DesiredAccess,
        _In_opt_ LPSECURITY_ATTRIBUTES TokenAttributes,
        _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
        _In_ TOKEN_TYPE TokenType,
        _Out_ PHANDLE NewTokenHandle)
    {
        if (!::DuplicateTokenEx(
            ExistingTokenHandle,
            DesiredAccess,
            TokenAttributes,
            ImpersonationLevel,
            TokenType,
            NewTokenHandle))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }
};

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
HRESULT WINAPI NSudoCreateInstance(
    _In_ REFIID InterfaceId,
    _Out_ PVOID* Instance)
{
    if (::IsEqualIID(InterfaceId, IID_INSudoClient))
    {
        *Instance = new CNSudoClient();
        return S_OK;
    }
    else
    {
        *Instance = nullptr;
        return E_NOTIMPL;
    }
}






#include <cstdio>
#include <cwchar>

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ DWORD ProcessId)
{
    DWORD ErrorCode = ERROR_INVALID_PARAMETER;

    if (ProcessHandle)
    {
        *ProcessHandle = ::OpenProcess(
            DesiredAccess, InheritHandle, ProcessId);
        if (*ProcessHandle)
        {
            ErrorCode = ERROR_SUCCESS;
        }
        else
        {
            ErrorCode = ::GetLastError();
        }
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenServiceProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ LPCWSTR ServiceName)
{
    SERVICE_STATUS_PROCESS ServiceStatus;

    DWORD ErrorCode = HRESULT_CODE(CNSudoClient().StartWindowsService(
        ServiceName, &ServiceStatus));
    if (ErrorCode == ERROR_SUCCESS)
    {
        ErrorCode = NSudoOpenProcess(
            ProcessHandle,
            DesiredAccess,
            InheritHandle,
            ServiceStatus.dwProcessId);
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenProcessTokenByProcessHandle(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ProcessHandle,
    _In_ DWORD DesiredAccess)
{
    if (!::OpenProcessToken(
        ProcessHandle, DesiredAccess, TokenHandle))
    {
        return ::GetLastError();
    }

    return ERROR_SUCCESS;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenCurrentProcessToken(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD DesiredAccess)
{
    return NSudoOpenProcessTokenByProcessHandle(
        TokenHandle, ::GetCurrentProcess(), DesiredAccess);
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenProcessTokenByProcessId(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD ProcessId,
    _In_ DWORD DesiredAccess)
{
    HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

    DWORD ErrorCode = NSudoOpenProcess(
        &ProcessHandle, MAXIMUM_ALLOWED, FALSE, ProcessId);
    if (ErrorCode == ERROR_SUCCESS)
    {
        ErrorCode = NSudoOpenProcessTokenByProcessHandle(
            TokenHandle, ProcessHandle, DesiredAccess);

        ::CloseHandle(ProcessHandle);
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenServiceProcessToken(
    _Out_ PHANDLE TokenHandle,
    _In_ LPCWSTR ServiceName,
    _In_ DWORD DesiredAccess)
{
    HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

    DWORD ErrorCode = NSudoOpenServiceProcess(
        &ProcessHandle, MAXIMUM_ALLOWED, FALSE, ServiceName);
    if (ErrorCode == ERROR_SUCCESS)
    {
        ErrorCode = NSudoOpenProcessTokenByProcessHandle(
            TokenHandle, ProcessHandle, DesiredAccess);

        ::CloseHandle(ProcessHandle);
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenLsassProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle)
{
    DWORD ErrorCode = ERROR_NOT_FOUND;

    DWORD dwLsassPID = static_cast<DWORD>(-1);

    PWTS_PROCESS_INFOW pProcesses = nullptr;
    DWORD dwProcessCount = 0;

    if (::WTSEnumerateProcessesW(
        WTS_CURRENT_SERVER_HANDLE,
        0,
        1,
        &pProcesses,
        &dwProcessCount))
    {
        for (DWORD i = 0; i < dwProcessCount; ++i)
        {
            PWTS_PROCESS_INFOW pProcess = &pProcesses[i];

            if (pProcess->SessionId != 0)
                continue;

            if (!pProcess->pProcessName)
                continue;

            if (::_wcsicmp(L"lsass.exe", pProcess->pProcessName) != 0)
                continue;

            if (!pProcess->pUserSid)
                continue;

            if (!::IsWellKnownSid(
                pProcess->pUserSid, WELL_KNOWN_SID_TYPE::WinLocalSystemSid))
                continue;

            dwLsassPID = pProcess->ProcessId;

            ErrorCode = ERROR_SUCCESS;
            break;
        }

        ::WTSFreeMemory(pProcesses);
    }
    else
    {
        ErrorCode = ::GetLastError();
    }

    if (ErrorCode == ERROR_SUCCESS)
    {
        ErrorCode = NSudoOpenProcess(
            ProcessHandle,
            DesiredAccess,
            InheritHandle,
            dwLsassPID);
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenLsassProcessToken(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD DesiredAccess)
{
    HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

    DWORD ErrorCode = NSudoOpenLsassProcess(
        &ProcessHandle, MAXIMUM_ALLOWED, FALSE);
    if (ErrorCode == ERROR_SUCCESS)
    {
        ErrorCode = NSudoOpenProcessTokenByProcessHandle(
            TokenHandle, ProcessHandle, DesiredAccess);

        ::CloseHandle(ProcessHandle);
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ DWORD ThreadId)
{
    DWORD ErrorCode = ERROR_INVALID_PARAMETER;

    if (ThreadHandle)
    {
        *ThreadHandle = ::OpenThread(
            DesiredAccess, InheritHandle, ThreadId);
        if (*ThreadHandle)
        {
            ErrorCode = ERROR_SUCCESS;
        }
        else
        {
            ErrorCode = ::GetLastError();
        }
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenThreadTokenByThreadHandle(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ThreadHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf)
{
    if (!::OpenThreadToken(
        ThreadHandle, DesiredAccess, OpenAsSelf, TokenHandle))
    {
        return ::GetLastError();
    }

    return ERROR_SUCCESS;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenCurrentThreadToken(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf)
{
    return NSudoOpenThreadTokenByThreadHandle(
        TokenHandle, ::GetCurrentThread(), DesiredAccess, OpenAsSelf);
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoOpenThreadTokenByThreadId(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD ThreadId,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf)
{
    HANDLE ThreadHandle = INVALID_HANDLE_VALUE;

    DWORD ErrorCode = NSudoOpenThread(
        &ThreadHandle, MAXIMUM_ALLOWED, FALSE, ThreadId);
    if (ErrorCode == ERROR_SUCCESS)
    {
        ErrorCode = NSudoOpenThreadTokenByThreadHandle(
            TokenHandle, ThreadHandle, DesiredAccess, OpenAsSelf);

        ::CloseHandle(ThreadHandle);
    }

    return ErrorCode;
}
