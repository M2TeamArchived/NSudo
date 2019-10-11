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

#include <cstdio>
#include <cwchar>

/**
 * The feature level of NSudo Shared Library.
 */
constexpr DWORD NSudoFeatureLevel = 0;

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoGetFeatureLevel()
{
    return NSudoFeatureLevel;
}

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

        PTOKEN_PRIVILEGES pTP = nullptr;
        ErrorCode = NSudoAllocMemory(reinterpret_cast<LPVOID*>(&pTP), TPSize);
        if (ErrorCode == ERROR_SUCCESS)
        {
            pTP->PrivilegeCount = PrivilegeCount;
            memcpy(pTP->Privileges, Privileges, PSize);

            ::AdjustTokenPrivileges(
                TokenHandle, FALSE, pTP, TPSize, nullptr, nullptr);
            ErrorCode = ::GetLastError();

            NSudoFreeMemory(pTP);
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
    _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType)
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
        return ERROR_INVALID_PARAMETER;
    }

    SID_IDENTIFIER_AUTHORITY SIA = SECURITY_MANDATORY_LABEL_AUTHORITY;

    if (!::AllocateAndInitializeSid(
        &SIA, 1, MandatoryLabelRid, 0, 0, 0, 0, 0, 0, 0, MandatoryLabelSid))
    {
        return ::GetLastError();
    }

    return ERROR_SUCCESS;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoStartService(
    _Out_ LPSERVICE_STATUS_PROCESS ServiceStatus,
    _In_ LPCWSTR ServiceName)
{
    DWORD ErrorCode = ERROR_INVALID_PARAMETER;

    if (ServiceStatus && ServiceName)
    {
        ErrorCode = ERROR_SUCCESS;

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
                            ErrorCode = ERROR_INVALID_FUNCTION;
                            break;
                        }

                        if (!::StartServiceW(hService, 0, nullptr))
                        {
                            ErrorCode = ::GetLastError();
                            break;
                        }

                        bStartServiceWCalled = true;
                    }
                    else if (
                        SERVICE_STOP_PENDING == ServiceStatus->dwCurrentState ||
                        SERVICE_START_PENDING == ServiceStatus->dwCurrentState)
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
                            if (ServiceStatus->dwCheckPoint <= nOldCheckPoint)
                            {
                                ULONGLONG nDiff = nCurrentTick - nLastTick;
                                if (nDiff > ServiceStatus->dwWaitHint)
                                {
                                    ErrorCode = ERROR_TIMEOUT;
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
                ErrorCode = ::GetLastError();
            }

            ::CloseServiceHandle(hSCM);
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

    DWORD ErrorCode = NSudoStartService(&ServiceStatus, ServiceName);
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
EXTERN_C DWORD WINAPI NSudoCreateSessionToken(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD SessionId)
{
    if (::WTSQueryUserToken(SessionId, TokenHandle))
    {
        return ERROR_SUCCESS;
    }
    else
    {
        return ::GetLastError();
    }
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoAllocMemory(
    _Out_ LPVOID* Block,
    _In_ SIZE_T Size)
{
    *Block = ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
    return *Block ? ERROR_SUCCESS : ERROR_NOT_ENOUGH_MEMORY;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoFreeMemory(
    _In_ LPVOID Block)
{
    if (::HeapFree(::GetProcessHeap(), 0, Block))
    {
        return ERROR_SUCCESS;
    }
    else
    {
        return ::GetLastError();
    }
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoGetTokenInformation(
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
        return ERROR_SUCCESS;
    }
    else
    {
        return ::GetLastError();
    }
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoGetTokenInformationWithMemory(
    _Out_ PVOID* OutputInformation,
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass)
{
    *OutputInformation = nullptr;

    DWORD Length = 0;

    DWORD ErrorCode = NSudoGetTokenInformation(
        TokenHandle,
        TokenInformationClass,
        nullptr,
        0,
        &Length);
    if (ErrorCode == ERROR_INSUFFICIENT_BUFFER)
    {
        ErrorCode = NSudoAllocMemory(OutputInformation, Length);
        if (ErrorCode == ERROR_SUCCESS)
        {
            ErrorCode = NSudoGetTokenInformation(
                TokenHandle,
                TokenInformationClass,
                *OutputInformation,
                Length,
                &Length);
            if (ErrorCode != ERROR_SUCCESS)
            {
                ErrorCode = NSudoFreeMemory(*OutputInformation);
                *OutputInformation = nullptr;
            }
        }
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoSetTokenInformation(
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
        return ERROR_SUCCESS;
    }
    else
    {
        return ::GetLastError();
    }
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoSetTokenMandatoryLabel(
    _In_ HANDLE TokenHandle,
    _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType)
{
    TOKEN_MANDATORY_LABEL TML;

    DWORD ErrorCode = NSudoCreateMandatoryLabelSid(
        &TML.Label.Sid, MandatoryLabelType);
    if (ErrorCode == ERROR_SUCCESS)
    {
        TML.Label.Attributes = SE_GROUP_INTEGRITY;

        ErrorCode = NSudoSetTokenInformation(
            TokenHandle, TokenIntegrityLevel, &TML, sizeof(TML));

        ::FreeSid(TML.Label.Sid);
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoCreateRestrictedToken(
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
        return ERROR_SUCCESS;
    }
    else
    {
        return ::GetLastError();
    }
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoCreateLUAToken(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ExistingTokenHandle)
{
    DWORD ErrorCode = ERROR_INVALID_PARAMETER;
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

        ErrorCode = NSudoCreateRestrictedToken(
            ExistingTokenHandle,
            LUA_TOKEN,
            0, nullptr,
            0, nullptr,
            0, nullptr,
            TokenHandle);
        if (ErrorCode != ERROR_SUCCESS)
        {
            break;
        }

        ErrorCode = NSudoSetTokenMandatoryLabel(
            *TokenHandle, NSUDO_MANDATORY_LABEL_TYPE::MEDIUM);
        if (ErrorCode != ERROR_SUCCESS)
        {
            break;
        }

        ErrorCode = NSudoGetTokenInformationWithMemory(
            reinterpret_cast<PVOID*>(&pTokenUser),
            *TokenHandle,
            TokenUser);
        if (ErrorCode != ERROR_SUCCESS)
        {
            break;
        }

        Owner.Owner = pTokenUser->User.Sid;
        ErrorCode = NSudoSetTokenInformation(
            *TokenHandle, TokenOwner, &Owner, sizeof(TOKEN_OWNER));
        if (ErrorCode != ERROR_SUCCESS)
        {
            break;
        }

        ErrorCode = NSudoGetTokenInformationWithMemory(
            reinterpret_cast<PVOID*>(&pTokenDacl),
            *TokenHandle,
            TokenDefaultDacl);
        if (ErrorCode != ERROR_SUCCESS)
        {
            break;
        }

        Length = pTokenDacl->DefaultDacl->AclSize;
        Length += ::GetLengthSid(pTokenUser->User.Sid);
        Length += sizeof(ACCESS_ALLOWED_ACE);

        ErrorCode = NSudoAllocMemory(
            reinterpret_cast<PVOID*>(&NewDefaultDacl), Length);
        if (ErrorCode != ERROR_SUCCESS)
        {
            break;
        }
        NewTokenDacl.DefaultDacl = NewDefaultDacl;

        if (!::InitializeAcl(
            NewTokenDacl.DefaultDacl,
            Length,
            pTokenDacl->DefaultDacl->AclRevision))
        {
            ErrorCode = ::GetLastError();
            break;
        }

        if (!::AddAccessAllowedAce(
            NewTokenDacl.DefaultDacl,
            pTokenDacl->DefaultDacl->AclRevision,
            GENERIC_ALL,
            pTokenUser->User.Sid))
        {
            ErrorCode = ::GetLastError();
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
        ErrorCode = NSudoSetTokenInformation(
            *TokenHandle, TokenDefaultDacl, &NewTokenDacl, Length);
        if (ErrorCode != ERROR_SUCCESS)
        {
            break;
        }

        ErrorCode = NSudoSetTokenInformation(
            *TokenHandle,
            TokenVirtualizationEnabled,
            &EnableTokenVirtualization,
            sizeof(BOOL));
        if (ErrorCode != ERROR_SUCCESS)
        {
            break;
        }

    } while (false);

    if (NewDefaultDacl)
    {
        NSudoFreeMemory(NewDefaultDacl);
    }

    if (pTokenDacl)
    {
        NSudoFreeMemory(pTokenDacl);
    }

    if (pTokenUser)
    {
        NSudoFreeMemory(pTokenUser);
    }

    if (ErrorCode != ERROR_SUCCESS)
    {
        ::CloseHandle(TokenHandle);
        *TokenHandle = INVALID_HANDLE_VALUE;
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

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoAdjustTokenAllPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ DWORD Attributes)
{
    PTOKEN_PRIVILEGES pTokenPrivileges = nullptr;

    DWORD ErrorCode = NSudoGetTokenInformationWithMemory(
        reinterpret_cast<PVOID*>(&pTokenPrivileges),
        TokenHandle,
        TokenPrivileges);
    if (ErrorCode == ERROR_SUCCESS)
    {
        for (DWORD i = 0; i < pTokenPrivileges->PrivilegeCount; ++i)
        {
            pTokenPrivileges->Privileges[i].Attributes = Attributes;
        }

        ErrorCode = NSudoAdjustTokenPrivileges(
            TokenHandle,
            pTokenPrivileges->Privileges,
            pTokenPrivileges->PrivilegeCount);

        NSudoFreeMemory(pTokenPrivileges);
    }

    return ErrorCode;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoReAllocMemory(
    _Out_ PVOID* NewBlock,
    _In_ PVOID OldBlock,
    _In_ SIZE_T NewSize)
{
    *NewBlock = ::HeapReAlloc(
        ::GetProcessHeap(), HEAP_ZERO_MEMORY, OldBlock, NewSize);
    return *NewBlock ? ERROR_SUCCESS : ERROR_NOT_ENOUGH_MEMORY;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoSetCurrentThreadToken(
    _In_opt_ HANDLE TokenHandle)
{
    if (!::SetThreadToken(nullptr, TokenHandle))
    {
        return ::GetLastError();
    }

    return ERROR_SUCCESS;
}

/**
 * @remark You can read the definition for this function in "NSudoAPI.h".
 */
EXTERN_C DWORD WINAPI NSudoDuplicateToken(
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
        return ::GetLastError();
    }

    return ERROR_SUCCESS;
}
