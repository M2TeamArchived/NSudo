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

namespace
{
    const NTSTATUS NtStatusNotImplemented = static_cast<NTSTATUS>(0xC0000002L);

    static bool IsNtStatusSuccess(NTSTATUS Status)
    {
        return (Status >= 0);
    }

    typedef struct _NtUnicodeString
    {
        USHORT Length;
        USHORT MaximumLength;
        _Field_size_bytes_part_(MaximumLength, Length) PWCH Buffer;
    } NtUnicodeString, *NtUnicodeStringPointer;

    static bool volatile g_IsTrustedLibraryLoaderInitialized = false;
    static bool volatile g_IsSecureLibraryLoaderAvailable = false;
    static FARPROC volatile g_LdrLoadDll = nullptr;
    static FARPROC volatile g_RtlNtStatusToDosError = nullptr;
    static FARPROC volatile g_RtlWow64EnableFsRedirectionEx = nullptr;
    static FARPROC volatile g_RtlInitUnicodeString = nullptr;

    static void InitializeTrustedLibraryLoader()
    {
        if (!g_IsTrustedLibraryLoaderInitialized)
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
                    g_IsSecureLibraryLoaderAvailable = ::GetProcAddress(
                        hModule, "AddDllDirectory");
                }
            }

            {
                HMODULE hModule = ::GetModuleHandleW(L"ntdll.dll");
                if (hModule)
                {
                    g_LdrLoadDll = ::GetProcAddress(
                        hModule, "LdrLoadDll");
                    g_RtlNtStatusToDosError = ::GetProcAddress(
                        hModule, "RtlNtStatusToDosError");
                    g_RtlWow64EnableFsRedirectionEx = ::GetProcAddress(
                        hModule, "RtlWow64EnableFsRedirectionEx");
                    g_RtlInitUnicodeString = ::GetProcAddress(
                        hModule, "RtlInitUnicodeString");
                }
            }

            g_IsTrustedLibraryLoaderInitialized = true;
        }
    }

    static bool IsSecureLibraryLoaderAvailable()
    {
        return g_IsSecureLibraryLoaderAvailable;
    }

    static NTSTATUS NTAPI LdrLoadDllWrapper(
        _In_opt_ PWSTR DllPath,
        _In_opt_ PULONG DllCharacteristics,
        _In_ NtUnicodeStringPointer DllName,
        _Out_ PVOID* DllHandle)
    {
        using ProcType = decltype(::LdrLoadDllWrapper)*;

        ProcType ProcAddress = reinterpret_cast<ProcType>(
            g_LdrLoadDll);

        if (ProcAddress)
        {
            return ProcAddress(
                DllPath,
                DllCharacteristics,
                DllName,
                DllHandle);
        }

        return ::NtStatusNotImplemented;
    }

    static ULONG NTAPI RtlNtStatusToDosErrorWrapper(
        _In_ NTSTATUS Status)
    {
        using ProcType = decltype(::RtlNtStatusToDosErrorWrapper)*;

        ProcType ProcAddress = reinterpret_cast<ProcType>(
            g_RtlNtStatusToDosError);

        if (ProcAddress)
        {
            return ProcAddress(Status);
        }

        return ERROR_PROC_NOT_FOUND;
    }

    static NTSTATUS NTAPI RtlWow64EnableFsRedirectionExWrapper(
        _In_ PVOID Wow64FsEnableRedirection,
        _Out_ PVOID* OldFsRedirectionLevel)
    {
        using ProcType = decltype(::RtlWow64EnableFsRedirectionExWrapper)*;

        ProcType ProcAddress = reinterpret_cast<ProcType>(
            g_RtlWow64EnableFsRedirectionEx);

        if (ProcAddress)
        {
            return ProcAddress(
                Wow64FsEnableRedirection,
                OldFsRedirectionLevel);
        }

        return ::NtStatusNotImplemented;
    }

    static void NTAPI RtlInitUnicodeStringWrapper(
        _Out_ NtUnicodeStringPointer DestinationString,
        _In_opt_ PCWSTR SourceString)
    {
        using ProcType = decltype(::RtlInitUnicodeStringWrapper)*;

        ProcType ProcAddress = reinterpret_cast<ProcType>(
            g_RtlInitUnicodeString);

        if (ProcAddress)
        {
            ProcAddress(
                DestinationString,
                SourceString);
        }
    }
}

/**
 * @remark You can read the definition for this function in
 *         "Mile.Windows.TrustedLibraryLoader.h".
 */
EXTERN_C HMODULE WINAPI MileLoadLibraryFromSystem32(
    _In_ LPCWSTR lpLibFileName)
{
    ::InitializeTrustedLibraryLoader();

    // The secure library loader is available when you using Windows 8 and
    // later, or you have installed the KB2533623 when you using Windows Vista
    // and 7.
    if (::IsSecureLibraryLoaderAvailable())
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
    NTSTATUS RedirectionStatus = ::RtlWow64EnableFsRedirectionExWrapper(
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

    NtUnicodeString ModuleFileName;
    ::RtlInitUnicodeStringWrapper(&ModuleFileName, lpLibFileName);

    HMODULE ModuleHandle = nullptr;
    NTSTATUS Status = ::LdrLoadDllWrapper(
        System32Directory,
        nullptr,
        &ModuleFileName,
        reinterpret_cast<PVOID*>(&ModuleHandle));
    if (!IsNtStatusSuccess(Status))
    {
        ::SetLastError(::RtlNtStatusToDosErrorWrapper(Status));
    }

    // Restore the old status of the WoW64 redirection.
    if (IsNtStatusSuccess(RedirectionStatus))
    {
        ::RtlWow64EnableFsRedirectionExWrapper(
            OldRedirectionLevel,
            &OldRedirectionLevel);
    }

    return ModuleHandle;
}
