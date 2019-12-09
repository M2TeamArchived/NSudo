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

#include "M2.Base.h"

#include <cstdio>
#include <cwchar>

#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")

#include <Userenv.h>
#pragma comment(lib, "Userenv.lib")

/**
 * NSudo Shared Library Memory Manager Interface Implementation
 */
class CNSudoMemoryManager :
    public M2::Base::CComClass<CNSudoMemoryManager, INSudoMemoryManager>
{
public:

    M2_BASE_COM_INTERFACE_MAP_BEGIN;
        M2_BASE_COM_INTERFACE_ENTRY(INSudoMemoryManager);
    M2_BASE_COM_INTERFACE_MAP_END;

    CNSudoMemoryManager() = default;

    virtual ~CNSudoMemoryManager() = default;

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE AllocMemory(
        _In_ SIZE_T Size,
        _Out_ LPVOID* Block)
    {
        *Block = ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
        return *Block ? S_OK : ::HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
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
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE FreeMemory(
        _In_ LPVOID Block)
    {
        if (!::HeapFree(::GetProcessHeap(), 0, Block))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }
};

/**
 * NSudo Shared Library Memory Manager Interface Shared Instance
 */
INSudoMemoryManager* g_pNSudoMemoryManager = nullptr;

/**
 * NSudo Shared Library Client Interface Implementation
 */
class CNSudoClient : public M2::Base::CComClass<CNSudoClient, INSudoClient>
{
public:

    M2_BASE_COM_INTERFACE_MAP_BEGIN;
        M2_BASE_COM_INTERFACE_ENTRY(INSudoClient);
    M2_BASE_COM_INTERFACE_MAP_END;

    CNSudoClient() = default;

    virtual ~CNSudoClient() = default;

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE GetTokenInformation(
        _In_ HANDLE TokenHandle,
        _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
        _Out_opt_ LPVOID TokenInformation,
        _In_ DWORD TokenInformationLength,
        _Out_ PDWORD ReturnLength)
    {
        if (!::GetTokenInformation(
            TokenHandle,
            TokenInformationClass,
            TokenInformation,
            TokenInformationLength,
            ReturnLength))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

    /**
      * @remark You can read the definition for this method in "NSudoAPI.h".
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
            hr = g_pNSudoMemoryManager->AllocMemory(Length, OutputInformation);
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
                    g_pNSudoMemoryManager->FreeMemory(*OutputInformation);
                    *OutputInformation = nullptr;
                }
            }
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE SetTokenInformation(
        _In_ HANDLE TokenHandle,
        _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
        _In_ LPVOID TokenInformation,
        _In_ DWORD TokenInformationLength)
    {
        if (!::SetTokenInformation(
            TokenHandle,
            TokenInformationClass,
            TokenInformation,
            TokenInformationLength))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
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

            hr = g_pNSudoMemoryManager->AllocMemory(
                TPSize, reinterpret_cast<LPVOID*>(&pTP));
            if (hr == S_OK)
            {
                pTP->PrivilegeCount = PrivilegeCount;
                memcpy(pTP->Privileges, Privileges, PSize);

                ::AdjustTokenPrivileges(
                    TokenHandle, FALSE, pTP, TPSize, nullptr, nullptr);
                hr = ::HRESULT_FROM_WIN32(::GetLastError());

                g_pNSudoMemoryManager->FreeMemory(pTP);
            }
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
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

            g_pNSudoMemoryManager->FreeMemory(pTokenPrivileges);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
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
     * @remark You can read the definition for this method in "NSudoAPI.h".
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
     * @remark You can read the definition for this method in "NSudoAPI.h".
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
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE CreateSessionToken(
        _In_ DWORD SessionId,
        _Out_ PHANDLE TokenHandle)
    {
        if (!::WTSQueryUserToken(SessionId, TokenHandle))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
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
        if (!::CreateRestrictedToken(
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
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
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

            hr = g_pNSudoMemoryManager->AllocMemory(
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
            g_pNSudoMemoryManager->FreeMemory(NewDefaultDacl);
        }

        if (pTokenDacl)
        {
            g_pNSudoMemoryManager->FreeMemory(pTokenDacl);
        }

        if (pTokenUser)
        {
            g_pNSudoMemoryManager->FreeMemory(pTokenUser);
        }

        if (hr != S_OK)
        {
            ::CloseHandle(TokenHandle);
            *TokenHandle = INVALID_HANDLE_VALUE;
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
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
     * @remark You can read the definition for this method in "NSudoAPI.h".
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

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenProcess(
        _In_ DWORD DesiredAccess,
        _In_ BOOL InheritHandle,
        _In_ DWORD ProcessId,
        _Out_ PHANDLE ProcessHandle)
    {
        HRESULT hr = E_INVALIDARG;

        if (ProcessHandle)
        {
            *ProcessHandle = ::OpenProcess(
                DesiredAccess, InheritHandle, ProcessId);
            if (*ProcessHandle)
            {
                hr = S_OK;
            }
            else
            {
                hr = ::HRESULT_FROM_WIN32(::GetLastError());
            }
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenServiceProcess(
        _In_ DWORD DesiredAccess,
        _In_ BOOL InheritHandle,
        _In_ LPCWSTR ServiceName,
        _Out_ PHANDLE ProcessHandle)
    {
        SERVICE_STATUS_PROCESS ServiceStatus;

        HRESULT hr = this->StartWindowsService(ServiceName, &ServiceStatus);
        if (hr == S_OK)
        {
            hr = this->OpenProcess(
                DesiredAccess,
                InheritHandle,
                ServiceStatus.dwProcessId,
                ProcessHandle);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenLsassProcess(
        _In_ DWORD DesiredAccess,
        _In_ BOOL InheritHandle,
        _Out_ PHANDLE ProcessHandle)
    {
        HRESULT hr = ::HRESULT_FROM_WIN32(ERROR_NOT_FOUND);

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

                hr = S_OK;
                break;
            }

            ::WTSFreeMemory(pProcesses);
        }
        else
        {
            hr = ::HRESULT_FROM_WIN32(::GetLastError());
        }

        if (hr == S_OK)
        {
            hr = this->OpenProcess(
                DesiredAccess,
                InheritHandle,
                dwLsassPID,
                ProcessHandle);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenProcessTokenByProcessHandle(
        _In_ HANDLE ProcessHandle,
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle)
    {
        if (!::OpenProcessToken(
            ProcessHandle, DesiredAccess, TokenHandle))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenCurrentProcessToken(
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle)
    {
        return this->OpenProcessTokenByProcessHandle(
            ::GetCurrentProcess(), DesiredAccess, TokenHandle);
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenProcessTokenByProcessId(
        _In_ DWORD ProcessId,
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle)
    {
        HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

        HRESULT hr = this->OpenProcess(
            MAXIMUM_ALLOWED, FALSE, ProcessId, &ProcessHandle);
        if (hr == S_OK)
        {
            hr = this->OpenProcessTokenByProcessHandle(
                ProcessHandle, DesiredAccess, TokenHandle);

            ::CloseHandle(ProcessHandle);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenServiceProcessToken(
        _In_ LPCWSTR ServiceName,
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle)
    {
        HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

        HRESULT hr = this->OpenServiceProcess(
            MAXIMUM_ALLOWED, FALSE, ServiceName, &ProcessHandle);
        if (hr == S_OK)
        {
            hr = this->OpenProcessTokenByProcessHandle(
                ProcessHandle, DesiredAccess, TokenHandle);

            ::CloseHandle(ProcessHandle);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenLsassProcessToken(
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle)
    {
        HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

        HRESULT hr = this->OpenLsassProcess(
            MAXIMUM_ALLOWED, FALSE, &ProcessHandle);
        if (hr == S_OK)
        {
            hr = this->OpenProcessTokenByProcessHandle(
                ProcessHandle, DesiredAccess, TokenHandle);

            ::CloseHandle(ProcessHandle);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenThread(
        _In_ DWORD DesiredAccess,
        _In_ BOOL InheritHandle,
        _In_ DWORD ThreadId,
        _Out_ PHANDLE ThreadHandle)
    {
        HRESULT hr = E_INVALIDARG;

        if (ThreadHandle)
        {
            *ThreadHandle = ::OpenThread(
                DesiredAccess, InheritHandle, ThreadId);
            if (*ThreadHandle)
            {
                hr = S_OK;
            }
            else
            {
                hr = ::HRESULT_FROM_WIN32(::GetLastError());
            }
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenThreadTokenByThreadHandle(
        _In_ HANDLE ThreadHandle,
        _In_ DWORD DesiredAccess,
        _In_ BOOL OpenAsSelf,
        _Out_ PHANDLE TokenHandle)
    {
        if (!::OpenThreadToken(
            ThreadHandle, DesiredAccess, OpenAsSelf, TokenHandle))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenCurrentThreadToken(
        _In_ DWORD DesiredAccess,
        _In_ BOOL OpenAsSelf,
        _Out_ PHANDLE TokenHandle)
    {
        return this->OpenThreadTokenByThreadHandle(
            ::GetCurrentThread(), DesiredAccess, OpenAsSelf, TokenHandle);
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE OpenThreadTokenByThreadId(
        _In_ DWORD ThreadId,
        _In_ DWORD DesiredAccess,
        _In_ BOOL OpenAsSelf,
        _Out_ PHANDLE TokenHandle)
    {
        HANDLE ThreadHandle = INVALID_HANDLE_VALUE;

        HRESULT hr = this->OpenThread(
            MAXIMUM_ALLOWED, FALSE, ThreadId, &ThreadHandle);
        if (hr == S_OK)
        {
            hr = this->OpenThreadTokenByThreadHandle(
                ThreadHandle, DesiredAccess, OpenAsSelf, TokenHandle);

            ::CloseHandle(ThreadHandle);
        }

        return hr;
    }

    /**
     * @remark You can read the definition for this method in "NSudoAPI.h".
     */
    virtual HRESULT STDMETHODCALLTYPE GetPrivilegeValue(
        _In_ LPCWSTR Name,
        _Out_ PLUID Value)
    {
        if (!::LookupPrivilegeValueW(nullptr, Name, Value))
        {
            return ::HRESULT_FROM_WIN32(::GetLastError());
        }

        return S_OK;
    }

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
};

/**
 * NSudo Shared Library Client Interface Shared Instance
 */
INSudoClient* g_pNSudoClient = nullptr;

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C void WINAPI NSudoInitialize()
{
    g_pNSudoMemoryManager = new CNSudoMemoryManager();

    g_pNSudoClient = new CNSudoClient();
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C void WINAPI NSudoUninitialize()
{
    g_pNSudoMemoryManager->Release();

    g_pNSudoClient->Release();
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C HRESULT WINAPI NSudoCreateInstance(
    _In_ REFIID InterfaceId,
    _Out_ PVOID* Instance)
{
    IUnknown* pRawInstance = nullptr;

    if (::IsEqualIID(InterfaceId, IID_INSudoMemoryManager))
    {
        pRawInstance = g_pNSudoMemoryManager;
    }
    else if (::IsEqualIID(InterfaceId, IID_INSudoClient))
    {
        pRawInstance = g_pNSudoClient;
    }

    if (!pRawInstance)
    {
        *Instance = nullptr;
        return E_NOINTERFACE;
    }

    pRawInstance->AddRef();
    *Instance = pRawInstance;
    return S_OK;
}
