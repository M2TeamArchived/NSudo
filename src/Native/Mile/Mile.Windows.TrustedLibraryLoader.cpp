/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.TrustedLibraryLoader.cpp
 * PURPOSE:   Trusted Library Loader Implementation for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef __cplusplus
#error "[Mile.Windows.TrustedLibraryLoader] You should use a C++ compiler."
#endif // !__cplusplus

#include "Mile.Windows.TrustedLibraryLoader.h"

#include <MINT.h>

namespace
{
    /**
     * @brief Trusted Library Loader Helper
    */
    class TrustedLibraryLoaderHelper
    {
    private:

        bool m_IsSecureLibraryLoaderAvailable = false;
        FARPROC m_LdrLoadDll = nullptr;
        FARPROC m_RtlNtStatusToDosError = nullptr;
        FARPROC m_RtlWow64EnableFsRedirectionEx = nullptr;
        FARPROC m_RtlInitUnicodeString = nullptr;

    public:

        TrustedLibraryLoaderHelper()
        {
            // We should check the secure library loader by get the address of
            // some APIs existed when the secure library loader is available.
            // Because some environment will return the ERROR_ACCESS_DENIED
            // instead of ERROR_INVALID_PARAMETER from GetLastError after
            // calling the LoadLibraryEx with using the unsupported flags.
            {
                HMODULE hModule = ::GetModuleHandleW(L"kernel32.dll");
                if (hModule)
                {
                    this->m_IsSecureLibraryLoaderAvailable = ::GetProcAddress(
                        hModule, "AddDllDirectory");
                }
            }

            {
                HMODULE hModule = ::GetModuleHandleW(L"ntdll.dll");
                if (hModule)
                {
                    this->m_LdrLoadDll = ::GetProcAddress(
                        hModule, "LdrLoadDll");
                    this->m_RtlNtStatusToDosError = ::GetProcAddress(
                        hModule, "RtlNtStatusToDosError");
                    this->m_RtlWow64EnableFsRedirectionEx = ::GetProcAddress(
                        hModule, "RtlWow64EnableFsRedirectionEx");
                    this->m_RtlInitUnicodeString = ::GetProcAddress(
                        hModule, "RtlInitUnicodeString");
                }
            }

        }

        ~TrustedLibraryLoaderHelper() = default;

        bool IsSecureLibraryLoaderAvailable()
        {
            return this->m_IsSecureLibraryLoaderAvailable;
        }

        NTSTATUS LdrLoadDll(
            _In_opt_ PWSTR DllPath,
            _In_opt_ PULONG DllCharacteristics,
            _In_ PUNICODE_STRING DllName,
            _Out_ PVOID* DllHandle)
        {
            decltype(::LdrLoadDll)* ProcAddress =
                reinterpret_cast<decltype(::LdrLoadDll)*>(
                    this->m_LdrLoadDll);

            if (ProcAddress)
            {
                return ProcAddress(
                    DllPath,
                    DllCharacteristics,
                    DllName,
                    DllHandle);
            }

            return STATUS_NOT_IMPLEMENTED;
        }

        ULONG RtlNtStatusToDosError(
            _In_ NTSTATUS Status)
        {
            decltype(::RtlNtStatusToDosError)* ProcAddress =
                reinterpret_cast<decltype(::RtlNtStatusToDosError)*>(
                    this->m_RtlNtStatusToDosError);

            if (ProcAddress)
            {
                return ProcAddress(Status);
            }

            return ERROR_PROC_NOT_FOUND;
        }

        NTSTATUS RtlWow64EnableFsRedirectionEx(
            _In_ PVOID Wow64FsEnableRedirection,
            _Out_ PVOID* OldFsRedirectionLevel)
        {
            decltype(::RtlWow64EnableFsRedirectionEx)* ProcAddress =
                reinterpret_cast<decltype(::RtlWow64EnableFsRedirectionEx)*>(
                    this->m_RtlWow64EnableFsRedirectionEx);

            if (ProcAddress)
            {
                return ProcAddress(
                    Wow64FsEnableRedirection,
                    OldFsRedirectionLevel);
            }

            return STATUS_NOT_IMPLEMENTED;
        }

        void RtlInitUnicodeString(
            _Out_ PUNICODE_STRING DestinationString,
            _In_opt_ PCWSTR SourceString)
        {
            decltype(::RtlInitUnicodeString)* ProcAddress =
                reinterpret_cast<decltype(::RtlInitUnicodeString)*>(
                    this->m_RtlInitUnicodeString);

            if (ProcAddress)
            {
                ProcAddress(
                    DestinationString,
                    SourceString);
            }
        }
    };
}

/**
 * @remark You can read the definition for this function in
 *         "Mile.Windows.TrustedLibraryLoader.h".
 */
EXTERN_C HMODULE WINAPI MileLoadLibraryFromSystem32(
    _In_ LPCWSTR lpLibFileName)
{
    // Use static variable to reduce the initialization times.
    // We need a compiler which supports C++11.
    // Reference: https://en.cppreference.com/w/cpp/language/storage_duration
    // If multiple threads attempt to initialize the same static local variable
    // concurrently, the initialization occurs exactly once (similar behavior
    // can be obtained for arbitrary functions with std::call_once).
    // Note: usual implementations of this feature use variants of the
    // double-checked locking pattern, which reduces runtime overhead for
    // already-initialized local statics to a single non-atomic boolean
    // comparison.
    static TrustedLibraryLoaderHelper Helper;

    // The secure library loader is available when you using Windows 8 and
    // later, or you have installed the KB2533623 when you using Windows Vista
    // and 7.
    if (Helper.IsSecureLibraryLoaderAvailable())
    {
        return ::LoadLibraryExW(
            lpLibFileName,
            nullptr,
            LOAD_LIBRARY_SEARCH_SYSTEM32);
    }

    // We should re-enable the WoW64 redirection because Windows 7 RTM or
    // earlier won't re-enable the WoW64 redirection when loading the library.
    // It's vulnerable if someone put the malicious library under the native
    // system directory.
    PVOID OldRedirectionLevel = nullptr;
    NTSTATUS RedirectionStatus = Helper.RtlWow64EnableFsRedirectionEx(
        nullptr,
        &OldRedirectionLevel);

    wchar_t System32Directory[MAX_PATH];
    UINT Length = ::GetSystemDirectoryW(System32Directory, MAX_PATH);
    if (Length == 0 || Length >= MAX_PATH)
    {
        // The length of the system directory path string (%windows%\system32)
        // should be shorter than the MAX_PATH constant.
        ::SetLastError(ERROR_FUNCTION_FAILED);
        return nullptr;
    }

    UNICODE_STRING ModuleFileName;
    Helper.RtlInitUnicodeString(&ModuleFileName, lpLibFileName);

    HMODULE ModuleHandle = nullptr;
    NTSTATUS Status = Helper.LdrLoadDll(
        System32Directory,
        nullptr,
        &ModuleFileName,
        reinterpret_cast<PVOID*>(&ModuleHandle));
    if (!NT_SUCCESS(Status))
    {
        ::SetLastError(Helper.RtlNtStatusToDosError(Status));
    }

    // Restore the old status of the WoW64 redirection.
    if (NT_SUCCESS(RedirectionStatus))
    {
        Helper.RtlWow64EnableFsRedirectionEx(
            OldRedirectionLevel,
            &OldRedirectionLevel);
    }

    return ModuleHandle;
}
