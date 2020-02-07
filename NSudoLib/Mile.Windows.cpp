/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.cpp
 * PURPOSE:   Mouri Internal Library Essentials Implementation for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef __cplusplus
#error "[Mile.Windows] You should use a C++ compiler."
#endif // !__cplusplus

#include "Mile.Windows.h"

#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HANDLE WINAPI MileGetProcessHeap()
{
    return ::GetProcessHeap();
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileHeapAlloc(
    _In_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ SIZE_T dwBytes,
    _Out_ LPVOID* lpNewMem)
{
    *lpNewMem = ::HeapAlloc(hHeap, dwFlags, dwBytes);
    return *lpNewMem ? S_OK : ::HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileHeapReAlloc(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem,
    _In_ SIZE_T dwBytes,
    _Out_ LPVOID* lpNewMem)
{
    *lpNewMem = ::HeapReAlloc(hHeap, dwFlags, lpMem, dwBytes);
    return *lpNewMem ? S_OK : ::HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileHeapFree(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem)
{
    if (!::HeapFree(hHeap, dwFlags, lpMem))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAllocMemory(
    _In_ SIZE_T Size,
    _Out_ LPVOID* Block)
{
    return ::MileHeapAlloc(
        ::MileGetProcessHeap(), HEAP_ZERO_MEMORY, Size, Block);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileReAllocMemory(
    _In_ PVOID OldBlock,
    _In_ SIZE_T NewSize,
    _Out_ LPVOID* NewBlock)
{
    return ::MileHeapReAlloc(
        ::MileGetProcessHeap(), HEAP_ZERO_MEMORY, OldBlock, NewSize, NewBlock);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileFreeMemory(
    _In_ LPVOID Block)
{
    return ::MileHeapFree(
        ::MileGetProcessHeap(), 0, Block);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ BOOL DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ DWORD BufferLength,
    _Out_opt_ PTOKEN_PRIVILEGES PreviousState,
    _Out_opt_ PDWORD ReturnLength)
{
    ::AdjustTokenPrivileges(
        TokenHandle,
        DisableAllPrivileges,
        NewState,
        BufferLength,
        PreviousState,
        ReturnLength);

    return ::HRESULT_FROM_WIN32(::GetLastError());
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetTokenInformation(
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
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetTokenInformation(
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
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetTokenInformationWithMemory(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_ PVOID* OutputInformation)
{
    *OutputInformation = nullptr;

    DWORD Length = 0;

    HRESULT hr = ::MileGetTokenInformation(
        TokenHandle,
        TokenInformationClass,
        nullptr,
        0,
        &Length);
    if (hr == ::HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
    {
        hr = ::MileAllocMemory(Length, OutputInformation);
        if (hr == S_OK)
        {
            hr = ::MileGetTokenInformation(
                TokenHandle,
                TokenInformationClass,
                *OutputInformation,
                Length,
                &Length);
            if (hr != S_OK)
            {
                ::MileFreeMemory(*OutputInformation);
                *OutputInformation = nullptr;
            }
        }
    }

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenPrivilegesSimple(
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

        hr = ::MileAllocMemory(TPSize, reinterpret_cast<LPVOID*>(&pTP));
        if (hr == S_OK)
        {
            pTP->PrivilegeCount = PrivilegeCount;
            ::memcpy(pTP->Privileges, Privileges, PSize);

            hr = ::MileAdjustTokenPrivileges(
                TokenHandle, FALSE, pTP, TPSize, nullptr, nullptr);

            ::MileFreeMemory(pTP);
        }
    }

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenAllPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ DWORD Attributes)
{
    PTOKEN_PRIVILEGES pTokenPrivileges = nullptr;

    HRESULT hr = ::MileGetTokenInformationWithMemory(
        TokenHandle,
        TokenPrivileges,
        reinterpret_cast<PVOID*>(&pTokenPrivileges));
    if (hr == S_OK)
    {
        for (DWORD i = 0; i < pTokenPrivileges->PrivilegeCount; ++i)
        {
            pTokenPrivileges->Privileges[i].Attributes = Attributes;
        }

        hr = ::MileAdjustTokenPrivilegesSimple(
            TokenHandle,
            pTokenPrivileges->Privileges,
            pTokenPrivileges->PrivilegeCount);

        ::MileFreeMemory(pTokenPrivileges);
    }

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetPrivilegeValue(
    _In_ LPCWSTR Name,
    _Out_ PLUID Value)
{
    if (!::LookupPrivilegeValueW(nullptr, Name, Value))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCloseServiceHandle(
    _In_ SC_HANDLE hSCObject)
{
    if (!::CloseServiceHandle(hSCObject))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenSCManager(
    _In_opt_ LPCWSTR lpMachineName,
    _In_opt_ LPCWSTR lpDatabaseName,
    _In_ DWORD dwDesiredAccess,
    _Out_ LPSC_HANDLE phSCManager)
{
    HRESULT hr = E_INVALIDARG;

    if (phSCManager)
    {
        *phSCManager = ::OpenSCManagerW(
            lpMachineName, lpDatabaseName, dwDesiredAccess);
        hr = (*phSCManager) ? S_OK : ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return hr;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenService(
    _In_ SC_HANDLE hSCManager,
    _In_ LPCWSTR lpServiceName,
    _In_ DWORD dwDesiredAccess,
    _Out_ LPSC_HANDLE phService)
{
    HRESULT hr = E_INVALIDARG;

    if (phService)
    {
        *phService = ::OpenServiceW(
            hSCManager, lpServiceName, dwDesiredAccess);
        hr = (*phService) ? S_OK : ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return hr;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileQueryServiceStatus(
    _In_ SC_HANDLE hService,
    _In_ SC_STATUS_TYPE InfoLevel,
    _Out_ LPBYTE lpBuffer,
    _In_ DWORD cbBufSize,
    _Out_ LPDWORD pcbBytesNeeded)
{
    if (!::QueryServiceStatusEx(
        hService, InfoLevel, lpBuffer, cbBufSize, pcbBytesNeeded))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());;
    }

    return S_OK;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileStartService(
    _In_ SC_HANDLE hService,
    _In_ DWORD dwNumServiceArgs,
    _In_ LPCWSTR* lpServiceArgVectors)
{
    if (!::StartServiceW(hService, dwNumServiceArgs, lpServiceArgVectors))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());;
    }

    return S_OK;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C DWORD WINAPI MileSleep(
    _In_ DWORD dwMilliseconds,
    _In_ BOOL bAlertable)
{
    return ::SleepEx(dwMilliseconds, bAlertable);
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileStartServiceSimple(
    _In_ LPCWSTR ServiceName,
    _Out_ LPSERVICE_STATUS_PROCESS ServiceStatus)
{
    HRESULT hr = E_INVALIDARG;

    if (ServiceStatus && ServiceName)
    {
        hr = S_OK;

        ::memset(ServiceStatus, 0, sizeof(LPSERVICE_STATUS_PROCESS));

        SC_HANDLE hSCM = nullptr;
        hr = ::MileOpenSCManager(
            nullptr, nullptr, SC_MANAGER_CONNECT, &hSCM);
        if (hr == S_OK)
        {
            SC_HANDLE hService = nullptr;
            hr = ::MileOpenService(
                hSCM,
                ServiceName,
                SERVICE_QUERY_STATUS | SERVICE_START,
                &hService);
            if (hr == S_OK)
            {
                DWORD nBytesNeeded = 0;
                DWORD nOldCheckPoint = 0;
                ULONGLONG nLastTick = 0;
                bool bStartServiceWCalled = false;

                while (::MileQueryServiceStatus(
                    hService,
                    SC_STATUS_PROCESS_INFO,
                    reinterpret_cast<LPBYTE>(ServiceStatus),
                    sizeof(SERVICE_STATUS_PROCESS),
                    &nBytesNeeded) == S_OK)
                {
                    if (SERVICE_STOPPED == ServiceStatus->dwCurrentState)
                    {
                        // Failed if the service had stopped again.
                        if (bStartServiceWCalled)
                        {
                            hr = S_FALSE;
                            break;
                        }

                        hr = ::MileStartService(hService, 0, nullptr);
                        if (hr != S_OK)
                        {
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
                        ULONGLONG nCurrentTick = ::MileGetTickCount();

                        if (!nLastTick)
                        {
                            nLastTick = nCurrentTick;
                            nOldCheckPoint = ServiceStatus->dwCheckPoint;

                            // Same as the .Net System.ServiceProcess, wait
                            // 250ms.
                            ::MileSleep(250, FALSE);
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
                                    hr = ::HRESULT_FROM_WIN32(ERROR_TIMEOUT);
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

                ::MileCloseServiceHandle(hService);
            }

            ::MileCloseServiceHandle(hSCM);
        }
    }

    return hr;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C ULONGLONG WINAPI MileGetTickCount()
{
    LARGE_INTEGER Frequency, PerformanceCount;

    if (::QueryPerformanceFrequency(&Frequency))
    {
        if (::QueryPerformanceCounter(&PerformanceCount))
        {
            return (PerformanceCount.QuadPart * 1000 / Frequency.QuadPart);
        }
    }

    return ::GetTickCount64();
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCloseHandle(
    _In_ HANDLE hObject)
{
    if (!::CloseHandle(hObject))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());;
    }

    return S_OK;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateSessionToken(
    _In_ DWORD SessionId,
    _Out_ PHANDLE TokenHandle)
{
    if (!::WTSQueryUserToken(SessionId, TokenHandle))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateRestrictedToken(
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

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C BOOL WINAPI MileIsWellKnownSid(
    _In_ PSID pSid,
    _In_ WELL_KNOWN_SID_TYPE WellKnownSidType)
{
    return ::IsWellKnownSid(pSid, WellKnownSidType);
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetLsassProcessId(
    _Out_ PDWORD ProcessId)
{
    HRESULT hr = E_INVALIDARG;

    if (ProcessId)
    {
        hr = ::HRESULT_FROM_WIN32(ERROR_NOT_FOUND);

        *ProcessId = static_cast<DWORD>(-1);

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

                if (!::MileIsWellKnownSid(
                    pProcess->pUserSid,
                    WELL_KNOWN_SID_TYPE::WinLocalSystemSid))
                    continue;

                *ProcessId = pProcess->ProcessId;

                hr = S_OK;
                break;
            }

            ::WTSFreeMemory(pProcesses);
        }
        else
        {
            hr = ::HRESULT_FROM_WIN32(::GetLastError());
        }
    }

    return hr;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAllocateAndInitializeSid(
    _In_ PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,
    _In_ BYTE nSubAuthorityCount,
    _In_ DWORD nSubAuthority0,
    _In_ DWORD nSubAuthority1,
    _In_ DWORD nSubAuthority2,
    _In_ DWORD nSubAuthority3,
    _In_ DWORD nSubAuthority4,
    _In_ DWORD nSubAuthority5,
    _In_ DWORD nSubAuthority6,
    _In_ DWORD nSubAuthority7,
    _Outptr_ PSID* pSid)
{
    if (!::AllocateAndInitializeSid(
        pIdentifierAuthority,
        nSubAuthorityCount,
        nSubAuthority0,
        nSubAuthority1,
        nSubAuthority2,
        nSubAuthority3,
        nSubAuthority4,
        nSubAuthority5,
        nSubAuthority6,
        nSubAuthority7,
        pSid))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C PVOID WINAPI MileFreeSid(
    _In_ PSID pSid)
{
    return ::FreeSid(pSid);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetCurrentThreadToken(
    _In_opt_ HANDLE TokenHandle)
{
    if (!::SetThreadToken(nullptr, TokenHandle))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileDuplicateToken(
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
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenProcess(
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
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HANDLE WINAPI MileGetCurrentProcess()
{
    return ::GetCurrentProcess();
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenThread(
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
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HANDLE WINAPI MileGetCurrentThread()
{
    return ::GetCurrentThread();
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenProcessToken(
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
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenThreadToken(
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
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetPriorityClass(
    _In_ HANDLE hProcess,
    _In_ DWORD dwPriorityClass)
{
    if (!::SetPriorityClass(hProcess, dwPriorityClass))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateMandatoryLabelSid(
    _In_ DWORD MandatoryLabelRid,
    _Out_ PSID* MandatoryLabelSid)
{
    SID_IDENTIFIER_AUTHORITY SIA = SECURITY_MANDATORY_LABEL_AUTHORITY;

    return ::MileAllocateAndInitializeSid(
        &SIA, 1, MandatoryLabelRid, 0, 0, 0, 0, 0, 0, 0, MandatoryLabelSid);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetTokenMandatoryLabel(
    _In_ HANDLE TokenHandle,
    _In_ DWORD MandatoryLabelRid)
{
    TOKEN_MANDATORY_LABEL TML;

    HRESULT hr = ::MileCreateMandatoryLabelSid(
        MandatoryLabelRid, &TML.Label.Sid);
    if (hr == S_OK)
    {
        TML.Label.Attributes = SE_GROUP_INTEGRITY;

        hr = ::MileSetTokenInformation(
            TokenHandle, TokenIntegrityLevel, &TML, sizeof(TML));

        ::MileFreeSid(TML.Label.Sid);
    }

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C DWORD WINAPI MileGetLengthSid(
    _In_ PSID pSid)
{
    return GetLengthSid(pSid);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileInitializeAcl(
    _Out_ PACL pAcl,
    _In_ DWORD nAclLength,
    _In_ DWORD dwAclRevision)
{
    if (!::InitializeAcl(pAcl, nAclLength, dwAclRevision))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAddAccessAllowedAce(
    _Inout_ PACL pAcl,
    _In_ DWORD dwAceRevision,
    _In_ DWORD AccessMask,
    _In_ PSID pSid)
{
    if (!::AddAccessAllowedAce(pAcl, dwAceRevision, AccessMask, pSid))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetAce(
    _In_ PACL pAcl,
    _In_ DWORD dwAceIndex,
    _Out_ LPVOID* pAce)
{
    if (!::GetAce(pAcl, dwAceIndex, pAce))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAddAce(
    _Inout_ PACL pAcl,
    _In_ DWORD dwAceRevision,
    _In_ DWORD dwStartingAceIndex,
    _In_ LPVOID pAceList,
    _In_ DWORD nAceListLength)
{
    if (!::AddAce(
        pAcl,
        dwAceRevision,
        dwStartingAceIndex,
        pAceList,
        nAceListLength))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateLUAToken(
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

        hr = ::MileCreateRestrictedToken(
            ExistingTokenHandle, LUA_TOKEN,
            0, nullptr, 0, nullptr, 0, nullptr, TokenHandle);
        if (hr != S_OK)
        {
            break;
        }

        hr = ::MileSetTokenMandatoryLabel(
            *TokenHandle, SECURITY_MANDATORY_MEDIUM_RID);
        if (hr != S_OK)
        {
            break;
        }

        hr = ::MileGetTokenInformationWithMemory(
            *TokenHandle,
            TokenUser,
            reinterpret_cast<PVOID*>(&pTokenUser));
        if (hr != S_OK)
        {
            break;
        }

        Owner.Owner = pTokenUser->User.Sid;
        hr = ::MileSetTokenInformation(
            *TokenHandle, TokenOwner, &Owner, sizeof(TOKEN_OWNER));
        if (hr != S_OK)
        {
            break;
        }

        hr = ::MileGetTokenInformationWithMemory(
            *TokenHandle,
            TokenDefaultDacl,
            reinterpret_cast<PVOID*>(&pTokenDacl));
        if (hr != S_OK)
        {
            break;
        }

        Length = pTokenDacl->DefaultDacl->AclSize;
        Length += ::MileGetLengthSid(pTokenUser->User.Sid);
        Length += sizeof(ACCESS_ALLOWED_ACE);

        hr = ::MileAllocMemory(
            Length, reinterpret_cast<PVOID*>(&NewDefaultDacl));
        if (hr != S_OK)
        {
            break;
        }
        NewTokenDacl.DefaultDacl = NewDefaultDacl;

        hr = ::MileInitializeAcl(
            NewTokenDacl.DefaultDacl,
            Length,
            pTokenDacl->DefaultDacl->AclRevision);
        if (hr != S_OK)
        {
            break;
        }

        hr = ::MileAddAccessAllowedAce(
            NewTokenDacl.DefaultDacl,
            pTokenDacl->DefaultDacl->AclRevision,
            GENERIC_ALL,
            pTokenUser->User.Sid);
        if (hr != S_OK)
        {
            break;
        }

        for (ULONG i = 0;
            ::MileGetAce(pTokenDacl->DefaultDacl, i, (PVOID*)&pTempAce) == S_OK;
            ++i)
        {
            if (::MileIsWellKnownSid(
                &pTempAce->SidStart,
                WELL_KNOWN_SID_TYPE::WinBuiltinAdministratorsSid))
                continue;

            ::MileAddAce(
                NewTokenDacl.DefaultDacl,
                pTokenDacl->DefaultDacl->AclRevision,
                0,
                pTempAce,
                pTempAce->Header.AceSize);
        }

        Length += sizeof(TOKEN_DEFAULT_DACL);
        hr = ::MileSetTokenInformation(
            *TokenHandle, TokenDefaultDacl, &NewTokenDacl, Length);
        if (hr != S_OK)
        {
            break;
        }

        hr = ::MileSetTokenInformation(
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
        ::MileFreeMemory(NewDefaultDacl);
    }

    if (pTokenDacl)
    {
        ::MileFreeMemory(pTokenDacl);
    }

    if (pTokenUser)
    {
        ::MileFreeMemory(pTokenUser);
    }

    if (hr != S_OK)
    {
        ::MileCloseHandle(TokenHandle);
        *TokenHandle = INVALID_HANDLE_VALUE;
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenServiceProcess(
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ LPCWSTR ServiceName,
    _Out_ PHANDLE ProcessHandle)
{
    SERVICE_STATUS_PROCESS ServiceStatus;

    HRESULT hr = ::MileStartServiceSimple(ServiceName, &ServiceStatus);
    if (hr == S_OK)
    {
        hr = ::MileOpenProcess(
            DesiredAccess,
            InheritHandle,
            ServiceStatus.dwProcessId,
            ProcessHandle);
    }

    return hr;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenLsassProcess(
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _Out_ PHANDLE ProcessHandle)
{
    DWORD dwLsassPID = static_cast<DWORD>(-1);

    HRESULT hr = ::MileGetLsassProcessId(&dwLsassPID);
    if (hr == S_OK)
    {
        hr = ::MileOpenProcess(
            DesiredAccess,
            InheritHandle,
            dwLsassPID,
            ProcessHandle);
    }

    return hr;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenCurrentProcessToken(
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle)
{
    return ::MileOpenProcessToken(
        ::MileGetCurrentProcess(), DesiredAccess, TokenHandle);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenProcessTokenByProcessId(
    _In_ DWORD ProcessId,
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle)
{
    HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

    HRESULT hr = ::MileOpenProcess(
        MAXIMUM_ALLOWED, FALSE, ProcessId, &ProcessHandle);
    if (hr == S_OK)
    {
        hr = ::MileOpenProcessToken(ProcessHandle, DesiredAccess, TokenHandle);

        ::MileCloseHandle(ProcessHandle);
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenServiceProcessToken(
    _In_ LPCWSTR ServiceName,
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle)
{
    HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

    HRESULT hr = ::MileOpenServiceProcess(
        MAXIMUM_ALLOWED, FALSE, ServiceName, &ProcessHandle);
    if (hr == S_OK)
    {
        hr = ::MileOpenProcessToken(
            ProcessHandle, DesiredAccess, TokenHandle);

        ::MileCloseHandle(ProcessHandle);
    }

    return hr;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenLsassProcessToken(
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle)
{
    HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

    HRESULT hr = ::MileOpenLsassProcess(
        MAXIMUM_ALLOWED, FALSE, &ProcessHandle);
    if (hr == S_OK)
    {
        hr = ::MileOpenProcessToken(
            ProcessHandle, DesiredAccess, TokenHandle);

        ::MileCloseHandle(ProcessHandle);
    }

    return hr;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenCurrentThreadToken(
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf,
    _Out_ PHANDLE TokenHandle)
{
    return ::MileOpenThreadToken(
        ::MileGetCurrentThread(), DesiredAccess, OpenAsSelf, TokenHandle);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenThreadTokenByThreadId(
    _In_ DWORD ThreadId,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf,
    _Out_ PHANDLE TokenHandle)
{
    HANDLE ThreadHandle = INVALID_HANDLE_VALUE;

    HRESULT hr = ::MileOpenThread(
        MAXIMUM_ALLOWED, FALSE, ThreadId, &ThreadHandle);
    if (hr == S_OK)
    {
        hr = ::MileOpenThreadToken(
            ThreadHandle, DesiredAccess, OpenAsSelf, TokenHandle);

        ::MileCloseHandle(ThreadHandle);
    }

    return hr;
}
