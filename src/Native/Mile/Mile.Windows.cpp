/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.cpp
 * PURPOSE:   Implementation for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.Windows.h"

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")
#endif

#include <strsafe.h>

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileAllocMemory(
    _In_ SIZE_T Size,
    _Out_ LPVOID* Block)
{
    *Block = Mile::HeapMemory::Allocate(Size);
    return *Block
        ? Mile::HResult(S_OK)
        : Mile::HResult::FromWin32(ERROR_NOT_ENOUGH_MEMORY);
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

    return Mile::HResultFromLastError();
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
    return Mile::HResultFromLastError(
        ::GetTokenInformation(
            TokenHandle,
            TokenInformationClass,
            TokenInformation,
            TokenInformationLength,
            ReturnLength));
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
    return Mile::HResultFromLastError(
        ::SetTokenInformation(
            TokenHandle,
            TokenInformationClass,
            TokenInformation,
            TokenInformationLength));
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
    if (hr == Mile::HResult::FromWin32(ERROR_INSUFFICIENT_BUFFER))
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
                Mile::HeapMemory::Free(*OutputInformation);
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

            Mile::HeapMemory::Free(pTP);
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

        Mile::HeapMemory::Free(pTokenPrivileges);
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
    return Mile::HResultFromLastError(
        ::LookupPrivilegeValueW(nullptr, Name, Value));
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileCreateSessionToken(
    _In_ DWORD SessionId,
    _Out_ PHANDLE TokenHandle)
{
    return Mile::HResultFromLastError(
        ::WTSQueryUserToken(SessionId, TokenHandle));
}

#endif

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
        hr = Mile::HResult::FromWin32(ERROR_NOT_FOUND);

        *ProcessId = static_cast<DWORD>(-1);

        PWTS_PROCESS_INFOW pProcesses = nullptr;
        DWORD dwProcessCount = 0;

        hr = Mile::HResultFromLastError(
            ::WTSEnumerateProcessesW(
                WTS_CURRENT_SERVER_HANDLE,
                0,
                1,
                &pProcesses,
                &dwProcessCount));
        if (hr == S_OK)
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
                    pProcess->pUserSid,
                    WELL_KNOWN_SID_TYPE::WinLocalSystemSid))
                    continue;

                *ProcessId = pProcess->ProcessId;

                hr = S_OK;
                break;
            }

            ::WTSFreeMemory(pProcesses);
        }
    }

    return hr;
}

#endif

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetCurrentThreadToken(
    _In_opt_ HANDLE TokenHandle)
{
    return Mile::HResultFromLastError(
        ::SetThreadToken(nullptr, TokenHandle));
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
    return Mile::HResultFromLastError(
        ::DuplicateTokenEx(
            ExistingTokenHandle,
            DesiredAccess,
            TokenAttributes,
            ImpersonationLevel,
            TokenType,
            NewTokenHandle));
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenProcess(
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ DWORD ProcessId,
    _Out_opt_ PHANDLE ProcessHandle)
{
    HANDLE RawProcessHandle = ::OpenProcess(
        DesiredAccess, InheritHandle, ProcessId);

    if (ProcessHandle)
    {
        *ProcessHandle = RawProcessHandle;
    }

    return Mile::HResultFromLastError(
        RawProcessHandle != nullptr);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenThread(
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ DWORD ThreadId,
    _Out_opt_ PHANDLE ThreadHandle)
{
    HANDLE RawThreadHandle = ::OpenThread(
        DesiredAccess, InheritHandle, ThreadId);

    if (ThreadHandle)
    {
        *ThreadHandle = RawThreadHandle;    
    }

    return Mile::HResultFromLastError(
        RawThreadHandle != nullptr);
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileOpenProcessToken(
    _In_ HANDLE ProcessHandle,
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle)
{
    return Mile::HResultFromLastError(
        ::OpenProcessToken(ProcessHandle, DesiredAccess, TokenHandle));
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
    return Mile::HResultFromLastError(
        ::OpenThreadToken(
            ThreadHandle,
            DesiredAccess,
            OpenAsSelf,
            TokenHandle));
}

/**
 * @remark You can read the definition for this function in "Mile.Windows.h".
 */
EXTERN_C HRESULT WINAPI MileSetTokenMandatoryLabel(
    _In_ HANDLE TokenHandle,
    _In_ DWORD MandatoryLabelRid)
{
    SID_IDENTIFIER_AUTHORITY SIA = SECURITY_MANDATORY_LABEL_AUTHORITY;

    TOKEN_MANDATORY_LABEL TML;

    HRESULT hr = Mile::HResultFromLastError(::AllocateAndInitializeSid(
        &SIA, 1, MandatoryLabelRid, 0, 0, 0, 0, 0, 0, 0, &TML.Label.Sid));
    if (hr == S_OK)
    {
        TML.Label.Attributes = SE_GROUP_INTEGRITY;

        hr = ::MileSetTokenInformation(
            TokenHandle, TokenIntegrityLevel, &TML, sizeof(TML));

        ::FreeSid(TML.Label.Sid);
    }

    return hr;
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

        hr = Mile::HResultFromLastError(::CreateRestrictedToken(
            ExistingTokenHandle,
            LUA_TOKEN,
            0,
            nullptr,
            0,
            nullptr,
            0,
            nullptr,
            TokenHandle));
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
        Length += ::GetLengthSid(pTokenUser->User.Sid);
        Length += sizeof(ACCESS_ALLOWED_ACE);

        hr = ::MileAllocMemory(
            Length, reinterpret_cast<PVOID*>(&NewDefaultDacl));
        if (hr != S_OK)
        {
            break;
        }
        NewTokenDacl.DefaultDacl = NewDefaultDacl;

        hr = Mile::HResultFromLastError(::InitializeAcl(
            NewTokenDacl.DefaultDacl,
            Length,
            pTokenDacl->DefaultDacl->AclRevision));
        if (hr != S_OK)
        {
            break;
        }

        hr = Mile::HResultFromLastError(::AddAccessAllowedAce(
            NewTokenDacl.DefaultDacl,
            pTokenDacl->DefaultDacl->AclRevision,
            GENERIC_ALL,
            pTokenUser->User.Sid));
        if (hr != S_OK)
        {
            break;
        }

        for (ULONG i = 0;
            ::GetAce(
                pTokenDacl->DefaultDacl,
                i,
                reinterpret_cast<PVOID*>(&pTempAce));
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
        Mile::HeapMemory::Free(NewDefaultDacl);
    }

    if (pTokenDacl)
    {
        Mile::HeapMemory::Free(pTokenDacl);
    }

    if (pTokenUser)
    {
        Mile::HeapMemory::Free(pTokenUser);
    }

    if (hr != S_OK)
    {
        ::CloseHandle(TokenHandle);
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

    HRESULT hr = Mile::StartServiceW(ServiceName, &ServiceStatus);
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
        ::GetCurrentProcess(), DesiredAccess, TokenHandle);
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

        ::CloseHandle(ProcessHandle);
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

        ::CloseHandle(ProcessHandle);
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

        ::CloseHandle(ProcessHandle);
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
        ::GetCurrentThread(), DesiredAccess, OpenAsSelf, TokenHandle);
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

        ::CloseHandle(ThreadHandle);
    }

    return hr;
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

        hr = ::CLSIDFromString(lpszCLSID, &clsid);
        if (hr != S_OK)
        {
            break;
        }

        hr = ::IIDFromString(lpszIID, &iid);
        if (hr != S_OK)
        {
            break;
        }

        hr = ::CoCreateInstance(clsid, pUnkOuter, dwClsContext, iid, ppv);

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
    HRESULT hr = Mile::HResult::FromWin32(::RegQueryValueExW(
        hKey,
        lpValueName,
        nullptr,
        nullptr,
        nullptr,
        &cbData));
    if (SUCCEEDED(hr))
    {
        hr = ::MileAllocMemory(cbData, reinterpret_cast<PVOID*>(lpData));
        if (SUCCEEDED(hr))
        {
            DWORD Type = 0;
            hr = Mile::HResult::FromWin32(::RegQueryValueExW(
                hKey,
                lpValueName,
                nullptr,
                &Type,
                reinterpret_cast<LPBYTE>(*lpData),
                &cbData));
            if (SUCCEEDED(hr) && REG_SZ != Type)
                hr = __HRESULT_FROM_WIN32(ERROR_ILLEGAL_ELEMENT_ADDRESS);

            if (FAILED(hr))
                hr = Mile::HResultFromLastError(
                    Mile::HeapMemory::Free(*lpData));
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
    HRESULT hr = Mile::HResult::FromWin32(::RegCreateKeyExW(
        HKEY_CLASSES_ROOT,
        RegistryKeyPath,
        0,
        nullptr,
        0,
        KEY_READ,
        nullptr,
        &hKey,
        nullptr));
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

            Mile::HeapMemory::Free(InterfaceTypeName);
        }

        ::RegCloseKey(hKey);
    }

    return hr;
}

#endif
