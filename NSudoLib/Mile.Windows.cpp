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

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#include <Userenv.h>
#pragma comment(lib, "Userenv.lib")
#endif

#include <assert.h>
#include <process.h>

#include <strsafe.h>

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

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileExpandEnvironmentStrings(
    _In_ LPCWSTR lpSrc,
    _Out_opt_ LPWSTR lpDst,
    _In_ DWORD nSize,
    _Out_opt_ PDWORD pReturnSize)
{
    DWORD ReturnSize = ::ExpandEnvironmentStringsW(lpSrc, lpDst, nSize);
    if (!ReturnSize)
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    if (pReturnSize)
    {
        *pReturnSize = ReturnSize;
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileExpandEnvironmentStringsWithMemory(
    _In_ LPCWSTR Source,
    _Out_ LPWSTR* Destination)
{
    DWORD AllocatedLength = 0;
    DWORD ActualLength = 0;

    HRESULT hr = E_INVALIDARG;

    if (Destination)
    {
        hr = ::MileExpandEnvironmentStrings(
            Source,
            nullptr,
            0,
            &AllocatedLength);
        if (hr == S_OK)
        {
            hr = ::MileAllocMemory(
                AllocatedLength * sizeof(wchar_t),
                reinterpret_cast<PVOID*>(Destination));
            if (hr == S_OK)
            {
                hr = ::MileExpandEnvironmentStrings(
                    Source,
                    *Destination,
                    AllocatedLength,
                    &ActualLength);
                if (hr == S_OK)
                {
                    if (AllocatedLength != ActualLength)
                    {
                        hr = E_UNEXPECTED;
                    }
                }
            }
        }

        if (hr != S_OK)
        {
            ::MileFreeMemory(*Destination);
        }
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateProcessAsUser(
    _In_opt_ HANDLE hToken,
    _In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation)
{
    if (!::CreateProcessAsUserW(
        hToken,
        lpApplicationName,
        lpCommandLine,
        lpProcessAttributes,
        lpThreadAttributes,
        bInheritHandles,
        dwCreationFlags,
        lpEnvironment,
        lpCurrentDirectory,
        lpStartupInfo,
        lpProcessInformation))
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
EXTERN_C HRESULT WINAPI MileCreateEnvironmentBlock(
    _Outptr_ LPVOID* lpEnvironment,
    _In_opt_ HANDLE hToken,
    _In_ BOOL bInherit)
{
    if (!::CreateEnvironmentBlock(lpEnvironment, hToken, bInherit))
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
EXTERN_C HRESULT WINAPI MileDestroyEnvironmentBlock(
    _In_ LPVOID lpEnvironment)
{
    if (!::DestroyEnvironmentBlock(lpEnvironment))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSuspendThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PDWORD PreviousSuspendCount)
{
    DWORD PreviousCount = ::SuspendThread(ThreadHandle);

    if (PreviousSuspendCount)
    {
        *PreviousSuspendCount = PreviousCount;
    }

    if (PreviousCount == static_cast<DWORD>(-1))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PDWORD PreviousSuspendCount)
{
    DWORD PreviousCount = ::ResumeThread(ThreadHandle);

    if (PreviousSuspendCount)
    {
        *PreviousSuspendCount = PreviousCount;
    }

    if (PreviousCount == static_cast<DWORD>(-1))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileWaitForSingleObject(
    _In_ HANDLE hHandle,
    _In_ DWORD dwMilliseconds,
    _In_ BOOL bAlertable,
    _Out_opt_ PDWORD pdwReturn)
{
    DWORD dwReturn = ::WaitForSingleObjectEx(
        hHandle,
        dwMilliseconds,
        bAlertable);

    if (pdwReturn)
    {
        *pdwReturn = dwReturn;
    }

    if (dwReturn == WAIT_FAILED)
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateThread(
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ SIZE_T dwStackSize,
    _In_ LPTHREAD_START_ROUTINE lpStartAddress,
    _In_opt_ LPVOID lpParameter,
    _In_ DWORD dwCreationFlags,
    _Out_opt_ LPDWORD lpThreadId,
    _Out_opt_ PHANDLE lpThreadHandle)
{
    // sanity check for lpThreadId
    assert(sizeof(DWORD) == sizeof(unsigned));

    typedef unsigned(__stdcall* routine_type)(void*);

    // _beginthreadex calls CreateThread which will set the last error
    // value before it returns.
    HANDLE ThreadHandle = reinterpret_cast<HANDLE>(::_beginthreadex(
        lpThreadAttributes,
        static_cast<unsigned>(dwStackSize),
        reinterpret_cast<routine_type>(lpStartAddress),
        lpParameter,
        dwCreationFlags,
        reinterpret_cast<unsigned*>(lpThreadId)));
    if (!lpThreadHandle)
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    if (lpThreadHandle)
    {
        *lpThreadHandle = ThreadHandle;
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C DWORD WINAPI MileGetNumberOfHardwareThreads()
{
    SYSTEM_INFO SystemInfo = { 0 };
    ::GetNativeSystemInfo(&SystemInfo);
    return SystemInfo.dwNumberOfProcessors;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileRegCloseKey(
    _In_ HKEY hKey)
{
    return ::HRESULT_FROM_WIN32(::RegCloseKey(hKey));
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileRegCreateKey(
    _In_ HKEY hKey,
    _In_ LPCWSTR lpSubKey,
    _Reserved_ DWORD Reserved,
    _In_opt_ LPWSTR lpClass,
    _In_ DWORD dwOptions,
    _In_ REGSAM samDesired,
    _In_opt_ CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _Out_ PHKEY phkResult,
    _Out_opt_ LPDWORD lpdwDisposition)
{
    return ::HRESULT_FROM_WIN32(::RegCreateKeyExW(
        hKey,
        lpSubKey,
        Reserved,
        lpClass,
        dwOptions,
        samDesired,
        lpSecurityAttributes,
        phkResult,
        lpdwDisposition));
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileRegQueryValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ LPDWORD lpReserved,
    _Out_opt_ LPDWORD lpType,
    _Out_opt_ LPBYTE lpData,
    _Inout_opt_ LPDWORD lpcbData)
{
    return ::HRESULT_FROM_WIN32(::RegQueryValueExW(
        hKey,
        lpValueName,
        lpReserved,
        lpType,
        lpData,
        lpcbData));
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileRegSetValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ DWORD Reserved,
    _In_ DWORD dwType,
    _In_opt_ CONST BYTE* lpData,
    _In_ DWORD cbData)
{
    return ::HRESULT_FROM_WIN32(::RegSetValueExW(
        hKey,
        lpValueName,
        Reserved,
        dwType,
        lpData,
        cbData));
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetFileInformation(
    _In_  HANDLE hFile,
    _In_  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    _Out_ LPVOID lpFileInformation,
    _In_  DWORD dwBufferSize)
{
    if (!::GetFileInformationByHandleEx(
        hFile,
        FileInformationClass,
        lpFileInformation,
        dwBufferSize))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetFileInformation(
    _In_ HANDLE hFile,
    _In_ FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    _In_ LPVOID lpFileInformation,
    _In_ DWORD dwBufferSize)
{
    if (!::SetFileInformationByHandle(
        hFile,
        FileInformationClass,
        lpFileInformation,
        dwBufferSize))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetFileAttributes(
    _In_ HANDLE FileHandle,
    _Out_ PDWORD FileAttributes)
{
    FILE_BASIC_INFO BasicInfo;

    HRESULT hr = ::MileGetFileInformation(
        FileHandle,
        FILE_INFO_BY_HANDLE_CLASS::FileBasicInfo,
        &BasicInfo,
        sizeof(FILE_BASIC_INFO));

    *FileAttributes = (hr == S_OK)
        ? BasicInfo.FileAttributes
        : INVALID_FILE_ATTRIBUTES;

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetFileAttributes(
    _In_ HANDLE FileHandle,
    _In_ DWORD FileAttributes)
{
    FILE_BASIC_INFO BasicInfo = { 0 };
    BasicInfo.FileAttributes =
        FileAttributes & (
            FILE_SHARE_READ |
            FILE_SHARE_WRITE |
            FILE_SHARE_DELETE |
            FILE_ATTRIBUTE_ARCHIVE |
            FILE_ATTRIBUTE_TEMPORARY |
            FILE_ATTRIBUTE_OFFLINE |
            FILE_ATTRIBUTE_NOT_CONTENT_INDEXED |
            FILE_ATTRIBUTE_NO_SCRUB_DATA) |
        FILE_ATTRIBUTE_NORMAL;

    return ::MileSetFileInformation(
        FileHandle,
        FILE_INFO_BY_HANDLE_CLASS::FileBasicInfo,
        &BasicInfo,
        sizeof(FILE_BASIC_INFO));
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetFileSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG FileSize)
{
    FILE_STANDARD_INFO StandardInfo;

    HRESULT hr = ::MileGetFileInformation(
        FileHandle,
        FILE_INFO_BY_HANDLE_CLASS::FileStandardInfo,
        &StandardInfo,
        sizeof(FILE_STANDARD_INFO));

    *FileSize = (hr == S_OK)
        ? static_cast<ULONGLONG>(StandardInfo.EndOfFile.QuadPart)
        : 0;

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetFileAllocationSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG AllocationSize)
{
    FILE_STANDARD_INFO StandardInfo;

    HRESULT hr = ::MileGetFileInformation(
        FileHandle,
        FILE_INFO_BY_HANDLE_CLASS::FileStandardInfo,
        &StandardInfo,
        sizeof(FILE_STANDARD_INFO));

    *AllocationSize = (hr == S_OK)
        ? static_cast<ULONGLONG>(StandardInfo.AllocationSize.QuadPart)
        : 0;

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileDeleteFile(
    _In_ HANDLE FileHandle)
{
    FILE_DISPOSITION_INFO DispostionInfo;
    DispostionInfo.DeleteFile = TRUE;

    return ::MileSetFileInformation(
        FileHandle,
        FILE_INFO_BY_HANDLE_CLASS::FileDispositionInfo,
        &DispostionInfo,
        sizeof(FILE_DISPOSITION_INFO));
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileDeleteFileIgnoreReadonlyAttribute(
    _In_ HANDLE FileHandle)
{
    HRESULT hr = S_OK;
    DWORD OldAttribute = 0;

    // Save old attributes.
    hr = ::MileGetFileAttributes(
        FileHandle,
        &OldAttribute);
    if (hr == S_OK)
    {
        // Remove readonly attribute.
        hr = ::MileSetFileAttributes(
            FileHandle,
            OldAttribute & (-1 ^ FILE_ATTRIBUTE_READONLY));
        if (hr == S_OK)
        {
            // Delete the file.
            hr = ::MileDeleteFile(FileHandle);
            if (hr != S_OK)
            {
                // Restore attributes if failed.
                hr = ::MileSetFileAttributes(
                    FileHandle,
                    OldAttribute);
            }
        }
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileLoadLibrary(
    _In_ LPCWSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags,
    _Out_opt_ HMODULE* phLibModule)
{
    HMODULE hLibModule = ::LoadLibraryExW(lpLibFileName, hFile, dwFlags);
    if (!hLibModule)
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    if (phLibModule)
    {
        *phLibModule = hLibModule;
    }

    return S_OK;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileFreeLibrary(
    _In_ HMODULE hLibModule)
{
    if (!::FreeLibrary(hLibModule))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetProcAddress(
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName,
    _Out_ FARPROC* lpProcAddress)
{
    *lpProcAddress = ::GetProcAddress(hModule, lpProcName);
    return *lpProcAddress ? S_OK : ::HRESULT_FROM_WIN32(::GetLastError());
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateFile(
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile,
    _Out_opt_ PHANDLE lpFileHandle)
{
    HANDLE FileHandle = ::CreateFileW(
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile);
    if (FileHandle == INVALID_HANDLE_VALUE)
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    if (lpFileHandle)
    {
        *lpFileHandle = FileHandle;
    }

    return S_OK;     
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileDeviceIoControl(
    _In_ HANDLE hDevice,
    _In_ DWORD dwIoControlCode,
    _In_opt_ LPVOID lpInBuffer,
    _In_ DWORD nInBufferSize,
    _Out_opt_ LPVOID lpOutBuffer,
    _In_ DWORD nOutBufferSize,
    _Out_opt_ LPDWORD lpBytesReturned,
    _Inout_opt_ LPOVERLAPPED lpOverlapped)
{
    if (!::DeviceIoControl(
        hDevice,
        dwIoControlCode,
        lpInBuffer,
        nInBufferSize,
        lpOutBuffer,
        nOutBufferSize,
        lpBytesReturned,
        lpOverlapped))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileInitializeCriticalSection(
    _Out_ LPCRITICAL_SECTION lpCriticalSection)
{
    ::InitializeCriticalSection(lpCriticalSection);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileDeleteCriticalSection(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection)
{
    ::DeleteCriticalSection(lpCriticalSection);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileEnterCriticalSection(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection)
{
    ::EnterCriticalSection(lpCriticalSection);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileLeaveCriticalSection(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection)
{
    ::LeaveCriticalSection(lpCriticalSection);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C BOOL WINAPI MileTryEnterCriticalSection(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection)
{
    return ::TryEnterCriticalSection(lpCriticalSection);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileInitializeSRWLock(
    _Out_ PSRWLOCK SRWLock)
{
    ::InitializeSRWLock(SRWLock);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileAcquireSRWLockExclusive(
    _Inout_ PSRWLOCK SRWLock)
{
    ::AcquireSRWLockExclusive(SRWLock);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C BOOL WINAPI MileTryAcquireSRWLockExclusive(
    _Inout_ PSRWLOCK SRWLock)
{
    return ::TryAcquireSRWLockExclusive(SRWLock);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileReleaseSRWLockExclusive(
    _Inout_ PSRWLOCK SRWLock)
{
    ::ReleaseSRWLockExclusive(SRWLock);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileAcquireSRWLockShared(
    _Inout_ PSRWLOCK SRWLock)
{
    ::AcquireSRWLockShared(SRWLock);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C BOOL WINAPI MileTryAcquireSRWLockShared(
    _Inout_ PSRWLOCK SRWLock)
{
    return ::TryAcquireSRWLockShared(SRWLock);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C VOID WINAPI MileReleaseSRWLockShared(
    _Inout_ PSRWLOCK SRWLock)
{
    ::ReleaseSRWLockShared(SRWLock);
}

/**
 * The internal content of the file enumerator handle.
 */
typedef struct _MILE_FILE_ENUMERATOR_OBJECT
{
    HANDLE FileHandle;
    CRITICAL_SECTION CriticalSection;
    PFILE_ID_BOTH_DIR_INFO CurrentFileInfo;
    BYTE FileInfoBuffer[32768];
} MILE_FILE_ENUMERATOR_OBJECT, *PMILE_FILE_ENUMERATOR_OBJECT;

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateFileEnumerator(
    _In_ HANDLE FileHandle,
    _Out_ PMILE_FILE_ENUMERATOR_HANDLE FileEnumeratorHandle)
{
    if ((!FileEnumeratorHandle) || (INVALID_HANDLE_VALUE == FileHandle))
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    *FileEnumeratorHandle = nullptr;

    PMILE_FILE_ENUMERATOR_OBJECT Object = nullptr;
    HRESULT hr = ::MileAllocMemory(
        sizeof(MILE_FILE_ENUMERATOR_OBJECT),
        reinterpret_cast<PVOID*>(&Object));
    if (hr == S_OK)
    {
        Object->FileHandle = FileHandle;
        ::MileInitializeCriticalSection(&Object->CriticalSection);

        *FileEnumeratorHandle = Object;
    }

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCloseFileEnumerator(
    _In_ MILE_FILE_ENUMERATOR_HANDLE FileEnumeratorHandle)
{
    if (!FileEnumeratorHandle)
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    PMILE_FILE_ENUMERATOR_OBJECT Object =
        reinterpret_cast<PMILE_FILE_ENUMERATOR_OBJECT>(FileEnumeratorHandle);

    ::MileDeleteCriticalSection(&Object->CriticalSection);

    return ::MileFreeMemory(Object);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileQueryFileEnumerator(
    _In_ MILE_FILE_ENUMERATOR_HANDLE FileEnumeratorHandle,
    _Out_ PMILE_FILE_ENUMERATOR_INFORMATION FileEnumeratorInformation)
{
    if ((!FileEnumeratorHandle) || (!FileEnumeratorInformation))
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    HRESULT hr = S_OK;

    PMILE_FILE_ENUMERATOR_OBJECT Object =
        reinterpret_cast<PMILE_FILE_ENUMERATOR_OBJECT>(FileEnumeratorHandle);

    ::MileEnterCriticalSection(&Object->CriticalSection);

    if (!Object->CurrentFileInfo)
    {
        Object->CurrentFileInfo =
            reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(Object->FileInfoBuffer);

        hr = ::MileGetFileInformation(
            Object->FileHandle,
            FILE_INFO_BY_HANDLE_CLASS::FileIdBothDirectoryRestartInfo,
            Object->CurrentFileInfo,
            sizeof(Object->FileInfoBuffer));
    }
    else if (!Object->CurrentFileInfo->NextEntryOffset)
    {
        Object->CurrentFileInfo =
            reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(Object->FileInfoBuffer);
        hr = ::MileGetFileInformation(
            Object->FileHandle,
            FILE_INFO_BY_HANDLE_CLASS::FileIdBothDirectoryInfo,
            Object->CurrentFileInfo,
            sizeof(Object->FileInfoBuffer));
    }
    else
    {
        Object->CurrentFileInfo = reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(
            reinterpret_cast<ULONG_PTR>(Object->CurrentFileInfo)
            + Object->CurrentFileInfo->NextEntryOffset);
    }

    if (SUCCEEDED(hr))
    {
        PFILE_ID_BOTH_DIR_INFO CurrentFileInfo = Object->CurrentFileInfo;

        FileEnumeratorInformation->CreationTime.dwLowDateTime =
            CurrentFileInfo->CreationTime.LowPart;
        FileEnumeratorInformation->CreationTime.dwHighDateTime =
            CurrentFileInfo->CreationTime.HighPart;

        FileEnumeratorInformation->LastAccessTime.dwLowDateTime =
            CurrentFileInfo->LastAccessTime.LowPart;
        FileEnumeratorInformation->LastAccessTime.dwHighDateTime =
            CurrentFileInfo->LastAccessTime.HighPart;

        FileEnumeratorInformation->LastWriteTime.dwLowDateTime =
            CurrentFileInfo->LastWriteTime.LowPart;
        FileEnumeratorInformation->LastWriteTime.dwHighDateTime =
            CurrentFileInfo->LastWriteTime.HighPart;

        FileEnumeratorInformation->ChangeTime.dwLowDateTime =
            CurrentFileInfo->ChangeTime.LowPart;
        FileEnumeratorInformation->ChangeTime.dwHighDateTime =
            CurrentFileInfo->ChangeTime.HighPart;

        FileEnumeratorInformation->FileSize =
            CurrentFileInfo->EndOfFile.QuadPart;

        FileEnumeratorInformation->AllocationSize =
            CurrentFileInfo->AllocationSize.QuadPart;

        FileEnumeratorInformation->FileAttributes =
            CurrentFileInfo->FileAttributes;

        FileEnumeratorInformation->EaSize =
            CurrentFileInfo->EaSize;

        FileEnumeratorInformation->FileId =
            CurrentFileInfo->FileId;

        ::StringCbCopyNW(
            FileEnumeratorInformation->ShortName,
            sizeof(FileEnumeratorInformation->ShortName),
            CurrentFileInfo->ShortName,
            CurrentFileInfo->ShortNameLength);

        ::StringCbCopyNW(
            FileEnumeratorInformation->FileName,
            sizeof(FileEnumeratorInformation->FileName),
            CurrentFileInfo->FileName,
            CurrentFileInfo->FileNameLength);
    }

    ::MileLeaveCriticalSection(&Object->CriticalSection);

    return hr;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetCompressedFileSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG CompressedFileSize)
{
    FILE_COMPRESSION_INFO FileCompressionInfo;
    HRESULT hr = ::MileGetFileInformation(
        FileHandle,
        FILE_INFO_BY_HANDLE_CLASS::FileCompressionInfo,
        &FileCompressionInfo,
        sizeof(FILE_COMPRESSION_INFO));
    if (hr == S_OK)
    {
        *CompressedFileSize = static_cast<ULONGLONG>(
            FileCompressionInfo.CompressedFileSize.QuadPart);
    }
    else
    {
        hr = ::MileGetFileSize(FileHandle, CompressedFileSize);
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * The information about the Windows Overlay Filter file provider.
 */
typedef struct _WOF_FILE_PROVIDER_EXTERNAL_INFO
{
    WOF_EXTERNAL_INFO Wof;
    FILE_PROVIDER_EXTERNAL_INFO FileProvider;
} WOF_FILE_PROVIDER_EXTERNAL_INFO, * PWOF_FILE_PROVIDER_EXTERNAL_INFO;

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileRemoveFileWofCompressionAttribute(
    _In_ HANDLE FileHandle)
{
    return ::MileDeviceIoControl(
        FileHandle,
        FSCTL_DELETE_EXTERNAL_BACKING,
        nullptr,
        0,
        nullptr,
        0,
        nullptr,
        nullptr);
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetFileWofCompressionAttribute(
    _In_ HANDLE FileHandle,
    _In_ DWORD CompressionAlgorithm)
{
    switch (CompressionAlgorithm)
    {
    case FILE_PROVIDER_COMPRESSION_XPRESS4K:
    case FILE_PROVIDER_COMPRESSION_LZX:
    case FILE_PROVIDER_COMPRESSION_XPRESS8K:
    case FILE_PROVIDER_COMPRESSION_XPRESS16K:
        break;
    default:
        return E_INVALIDARG;
    }

    WOF_FILE_PROVIDER_EXTERNAL_INFO WofInfo = { 0 };

    WofInfo.Wof.Version = WOF_CURRENT_VERSION;
    WofInfo.Wof.Provider = WOF_PROVIDER_FILE;

    WofInfo.FileProvider.Version = FILE_PROVIDER_CURRENT_VERSION;
    WofInfo.FileProvider.Flags = 0;
    WofInfo.FileProvider.Algorithm = CompressionAlgorithm;

    return ::MileDeviceIoControl(
        FileHandle,
        FSCTL_SET_EXTERNAL_BACKING,
        &WofInfo,
        sizeof(WofInfo),
        nullptr,
        0,
        nullptr,
        nullptr);
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetFileWofCompressionAttribute(
    _In_ HANDLE FileHandle,
    _Out_ PDWORD CompressionAlgorithm)
{
    if (!CompressionAlgorithm)
        return E_INVALIDARG;

    WOF_FILE_PROVIDER_EXTERNAL_INFO WofInfo = { 0 };

    HRESULT hr = ::MileDeviceIoControl(
        FileHandle,
        FSCTL_GET_EXTERNAL_BACKING,
        nullptr,
        0,
        &WofInfo,
        sizeof(WofInfo),
        nullptr,
        nullptr);
    if (hr == S_OK)
    {
        *CompressionAlgorithm = WofInfo.FileProvider.Algorithm;
    }

    return hr;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetFileNtfsCompressionAttribute(
    _In_ HANDLE FileHandle,
    _In_ USHORT CompressionAlgorithm)
{
    switch (CompressionAlgorithm)
    {
    case COMPRESSION_FORMAT_NONE:
    case COMPRESSION_FORMAT_DEFAULT:
    case COMPRESSION_FORMAT_LZNT1:
        break;
    default:
        return E_INVALIDARG;
    }

    return ::MileDeviceIoControl(
        FileHandle,
        FSCTL_SET_COMPRESSION,
        &CompressionAlgorithm,
        sizeof(CompressionAlgorithm),
        nullptr,
        0,
        nullptr,
        nullptr);
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetFileNtfsCompressionAttribute(
    _In_ HANDLE FileHandle,
    _Out_ PUSHORT CompressionAlgorithm)
{
    if (!CompressionAlgorithm)
        return E_INVALIDARG;

    return ::MileDeviceIoControl(
        FileHandle,
        FSCTL_GET_COMPRESSION,
        nullptr,
        0,
        CompressionAlgorithm,
        sizeof(*CompressionAlgorithm),
        nullptr,
        nullptr);
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCoCreateInstance(
    _In_ REFCLSID rclsid,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ REFIID riid,
    _Out_ LPVOID* ppv)
{
    return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCLSIDFromString(
    _In_ LPCOLESTR lpsz,
    _Out_ LPCLSID pclsid)
{
    return ::CLSIDFromString(lpsz, pclsid);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileIIDFromString(
    _In_ LPCOLESTR lpsz,
    _Out_ LPIID lpiid)
{
    return ::IIDFromString(lpsz, lpiid);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCoCreateInstanceByString(
    _In_ LPCWSTR lpszCLSID,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ LPCWSTR lpszIID,
    _Out_ LPVOID* ppv)
{
    HRESULT hr = S_OK;

    do
    {
        CLSID clsid;
        IID iid;

        hr = ::MileCLSIDFromString(lpszCLSID, &clsid);
        if (hr != S_OK)
        {
            break;
        }

        hr = ::MileIIDFromString(lpszIID, &iid);
        if (hr != S_OK)
        {
            break;
        }

        hr = ::MileCoCreateInstance(clsid, pUnkOuter, dwClsContext, iid, ppv);

    } while (false);

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileRegQueryStringValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Out_ LPWSTR* lpData)
{
    *lpData = nullptr;

    DWORD cbData = 0;
    HRESULT hr = ::MileRegQueryValue(
        hKey,
        lpValueName,
        nullptr,
        nullptr,
        nullptr,
        &cbData);
    if (SUCCEEDED(hr))
    {
        hr = ::MileAllocMemory(cbData, reinterpret_cast<PVOID*>(lpData));
        if (SUCCEEDED(hr))
        {
            DWORD Type = 0;
            hr = ::MileRegQueryValue(
                hKey,
                lpValueName,
                nullptr,
                &Type,
                reinterpret_cast<LPBYTE>(*lpData),
                &cbData);
            if (SUCCEEDED(hr) && REG_SZ != Type)
                hr = __HRESULT_FROM_WIN32(ERROR_ILLEGAL_ELEMENT_ADDRESS);

            if (FAILED(hr))
                hr = ::MileFreeMemory(*lpData);
        }
    }

    return hr;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCoCheckInterfaceName(
    _In_ LPCWSTR InterfaceID,
    _In_ LPCWSTR InterfaceName)
{
    wchar_t RegistryKeyPath[64];
    if (0 != ::wcscpy_s(RegistryKeyPath, L"Interface\\"))
        return E_INVALIDARG;
    if (0 != ::wcscat_s(RegistryKeyPath, InterfaceID))
        return E_INVALIDARG;

    HKEY hKey = nullptr;
    HRESULT hr = ::MileRegCreateKey(
        HKEY_CLASSES_ROOT,
        RegistryKeyPath,
        0,
        nullptr,
        0,
        KEY_READ,
        nullptr,
        &hKey,
        nullptr);
    if (SUCCEEDED(hr))
    {
        wchar_t* InterfaceTypeName = nullptr;
        hr = ::MileRegQueryStringValue(hKey, nullptr, &InterfaceTypeName);
        if (SUCCEEDED(hr))
        {
            if (0 != ::_wcsicmp(InterfaceTypeName, InterfaceName))
            {
                hr = E_NOINTERFACE;
            }

            ::MileFreeMemory(InterfaceTypeName);
        }

        ::MileRegCloseKey(hKey);
    }

    return hr;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileGetDpiForMonitor(
    _In_ HMONITOR hmonitor,
    _In_ MONITOR_DPI_TYPE dpiType,
    _Out_ UINT* dpiX,
    _Out_ UINT* dpiY)
{
    HMODULE hModule = nullptr;
    HRESULT hr = ::MileLoadLibrary(
        L"SHCore.dll",
        nullptr,
        LOAD_LIBRARY_SEARCH_SYSTEM32,
        &hModule);
    if (SUCCEEDED(hr))
    {
        decltype(::GetDpiForMonitor)* pFunc = nullptr;
        hr = ::MileGetProcAddress(
            hModule,
            "GetDpiForMonitor",
            reinterpret_cast<FARPROC*>(&pFunc));
        if (SUCCEEDED(hr))
        {
            hr = pFunc(hmonitor, dpiType, dpiX, dpiY);
        }

        ::MileFreeLibrary(hModule);
    }

    return hr;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C BOOL WINAPI MileIsDots(
    _In_ LPCWSTR Name)
{
    return Name[0] == L'.' && (!Name[1] || (Name[1] == L'.' && !Name[2]));
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateFileMapping(
    _In_ HANDLE hFile,
    _In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    _In_ DWORD flProtect,
    _In_ DWORD dwMaximumSizeHigh,
    _In_ DWORD dwMaximumSizeLow,
    _In_opt_ LPCWSTR lpName,
    _Out_ PHANDLE lpFileMappingHandle)
{
    *lpFileMappingHandle = ::CreateFileMappingW(
        hFile,
        lpFileMappingAttributes,
        flProtect,
        dwMaximumSizeHigh,
        dwMaximumSizeLow,
        lpName);

    return *lpFileMappingHandle
        ? S_OK
        : ::HRESULT_FROM_WIN32(::GetLastError());
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileMapViewOfFile(
    _In_ HANDLE hFileMappingObject,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwFileOffsetHigh,
    _In_ DWORD dwFileOffsetLow,
    _In_ SIZE_T dwNumberOfBytesToMap,
    _Out_ LPVOID* lpBaseAddress)
{
    *lpBaseAddress = ::MapViewOfFile(
        hFileMappingObject,
        dwDesiredAccess,
        dwFileOffsetHigh,
        dwFileOffsetLow,
        dwNumberOfBytesToMap);

    return *lpBaseAddress
        ? S_OK
        : ::HRESULT_FROM_WIN32(::GetLastError());
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileUnmapViewOfFile(
    _In_ LPCVOID lpBaseAddress)
{
    if (!::UnmapViewOfFile(lpBaseAddress))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileReadFile(
    _In_ HANDLE hFile,
    _Out_opt_ LPVOID lpBuffer,
    _In_ DWORD nNumberOfBytesToRead,
    _Out_opt_ LPDWORD lpNumberOfBytesRead,
    _Inout_opt_ LPOVERLAPPED lpOverlapped)
{
    if (!::ReadFile(
        hFile,
        lpBuffer,
        nNumberOfBytesToRead,
        lpNumberOfBytesRead,
        lpOverlapped))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileWriteFile(
    _In_ HANDLE hFile,
    _In_opt_ LPCVOID lpBuffer,
    _In_ DWORD nNumberOfBytesToWrite,
    _Out_opt_ LPDWORD lpNumberOfBytesWritten,
    _Inout_opt_ LPOVERLAPPED lpOverlapped)
{
    if (!::WriteFile(
        hFile,
        lpBuffer,
        nNumberOfBytesToWrite,
        lpNumberOfBytesWritten,
        lpOverlapped))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    return S_OK;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileReOpenFile(
    _In_ HANDLE hOriginalFile,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_ DWORD dwFlagsAndAttributes,
    _Out_opt_ PHANDLE lpFileHandle)
{
    HANDLE FileHandle = ::ReOpenFile(
        hOriginalFile,
        dwDesiredAccess,
        dwShareMode,
        dwFlagsAndAttributes);

    if (FileHandle == INVALID_HANDLE_VALUE)
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    if (lpFileHandle)
    {
        *lpFileHandle = FileHandle;
    }

    return S_OK;
}

#endif
