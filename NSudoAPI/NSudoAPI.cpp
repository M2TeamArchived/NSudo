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
