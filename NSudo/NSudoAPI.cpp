/*
 * PROJECT:   NSudo
 * FILE:      NSudoAPI.cpp
 * PURPOSE:   Implementation for NSudo Shared Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "NSudoAPI.h"

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
