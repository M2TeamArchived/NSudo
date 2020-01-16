/*
 * PROJECT:   NSudo Devil Mode
 * FILE:      NSudoDevilMode.cpp
 * PURPOSE:   Implementation for NSudo Devil Mode
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#include <vector>

#include "MINT.h"
#include "Detours/detours.h"

NTSTATUS NSudoDevilModeCreatePrivilegedToken(
    _Out_ PHANDLE NewTokenHandle)
{
    *NewTokenHandle = INVALID_HANDLE_VALUE;

    NTSTATUS Status = STATUS_SUCCESS;
    HANDLE CurrentProcessToken = INVALID_HANDLE_VALUE;

    Status = ::NtOpenProcessToken(
        NtCurrentProcess(),
        MAXIMUM_ALLOWED,
        &CurrentProcessToken);
    if (NT_SUCCESS(Status))
    {
        SECURITY_QUALITY_OF_SERVICE SQOS;
        SQOS.Length = sizeof(SECURITY_QUALITY_OF_SERVICE);
        SQOS.ImpersonationLevel = SecurityImpersonation;
        SQOS.ContextTrackingMode = FALSE;
        SQOS.EffectiveOnly = FALSE;

        OBJECT_ATTRIBUTES OA;
        OA.Length = sizeof(OBJECT_ATTRIBUTES);
        OA.RootDirectory = nullptr;
        OA.ObjectName = nullptr;
        OA.Attributes = 0;
        OA.SecurityDescriptor = nullptr;
        OA.SecurityQualityOfService = &SQOS;

        Status = ::NtDuplicateToken(
            CurrentProcessToken,
            MAXIMUM_ALLOWED,
            &OA,
            FALSE,
            TokenImpersonation,
            NewTokenHandle);

        ::NtClose(CurrentProcessToken);
    }

    if (NT_SUCCESS(Status))
    {
        ULONG TPSize = 2 * sizeof(LUID_AND_ATTRIBUTES) + sizeof(DWORD);
        PTOKEN_PRIVILEGES pTP = reinterpret_cast<PTOKEN_PRIVILEGES>(
            ::RtlAllocateHeap(RtlProcessHeap(), HEAP_ZERO_MEMORY, TPSize));
        if (pTP)
        {
            pTP->PrivilegeCount = 2;

            pTP->Privileges[0].Luid.LowPart = SE_BACKUP_PRIVILEGE;
            pTP->Privileges[0].Luid.HighPart = 0;
            pTP->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            pTP->Privileges[1].Luid.LowPart = SE_RESTORE_PRIVILEGE;
            pTP->Privileges[1].Luid.HighPart = 0;
            pTP->Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;

            Status = ::NtAdjustPrivilegesToken(
                *NewTokenHandle,
                FALSE,
                pTP,
                TPSize,
                nullptr,
                nullptr);
            if (ERROR_SUCCESS != Status)
            {
                ::NtClose(*NewTokenHandle);
                *NewTokenHandle = INVALID_HANDLE_VALUE;

                Status = STATUS_NOT_SUPPORTED;
            }

            ::RtlFreeHeap(RtlProcessHeap(), 0, pTP);
        }
    }

    return Status;
}

static NTSTATUS g_CreatePrivilegedTokenStatus = STATUS_SUCCESS;
static HANDLE g_PrivilegedAccessToken = INVALID_HANDLE_VALUE;

NTSTATUS NSudoDevilModeEnterPrivilegedContext(
    _Out_ PHANDLE OriginalTokenHandle)
{
    if (!NT_SUCCESS(g_CreatePrivilegedTokenStatus))
    {
        return g_CreatePrivilegedTokenStatus;
    }

    if (!NT_SUCCESS(::NtOpenThreadToken(
        NtCurrentThread(),
        MAXIMUM_ALLOWED,
        TRUE,
        OriginalTokenHandle)))
    {
        *OriginalTokenHandle = nullptr;
    }

    return ::NtSetInformationThread(
        NtCurrentThread(),
        ThreadImpersonationToken,
        &g_PrivilegedAccessToken,
        sizeof(HANDLE));
}

NTSTATUS NSudoDevilModeLeavePrivilegedContext(
    _Out_ HANDLE OriginalTokenHandle)
{
    NTSTATUS Status = ::NtSetInformationThread(
        NtCurrentThread(),
        ThreadImpersonationToken,
        &OriginalTokenHandle,
        sizeof(HANDLE));

    if (OriginalTokenHandle != nullptr &&
        OriginalTokenHandle != INVALID_HANDLE_VALUE)
    {
        ::NtClose(OriginalTokenHandle);
    }

    return Status;
}

namespace FunctionType
{
    enum
    {
        NtCreateKey,
        NtCreateKeyTransacted,
        NtOpenKey,
        NtOpenKeyTransacted,
        NtOpenKeyEx,
        NtOpenKeyTransactedEx,

        NtCreateFile,
        NtOpenFile,

        MaxFunctionType
    };
}


static PVOID OriginalAddress[FunctionType::MaxFunctionType] =
{
    ::NtCreateKey,
    ::NtCreateKeyTransacted,
    ::NtOpenKey,
    ::NtOpenKeyTransacted,
    nullptr,
    nullptr,
    ::NtCreateFile,
    ::NtOpenFile
};


NTSTATUS NTAPI OriginalNtCreateKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition)
{
    return reinterpret_cast<decltype(NtCreateKey)*>(
        OriginalAddress[FunctionType::NtCreateKey])(
            KeyHandle,
            DesiredAccess,
            ObjectAttributes,
            TitleIndex,
            Class,
            CreateOptions,
            Disposition);
}

NTSTATUS NTAPI DetouredNtCreateKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition)
{
    HANDLE OriginalTokenHandle = INVALID_HANDLE_VALUE;
    NTSTATUS ContextStatus = NSudoDevilModeEnterPrivilegedContext(
        &OriginalTokenHandle);
    if (NT_SUCCESS(ContextStatus))
    {
        CreateOptions |= REG_OPTION_BACKUP_RESTORE;
    }

    NTSTATUS Status = OriginalNtCreateKey(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        TitleIndex,
        Class,
        CreateOptions,
        Disposition);

    if (NT_SUCCESS(ContextStatus))
    {
        NSudoDevilModeLeavePrivilegedContext(OriginalTokenHandle);
    }

    return Status;
}


NTSTATUS NTAPI OriginalNtCreateKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _In_ HANDLE TransactionHandle,
    _Out_opt_ PULONG Disposition)
{
    return reinterpret_cast<decltype(NtCreateKeyTransacted)*>(
        OriginalAddress[FunctionType::NtCreateKeyTransacted])(
            KeyHandle,
            DesiredAccess,
            ObjectAttributes,
            TitleIndex,
            Class,
            CreateOptions,
            TransactionHandle,
            Disposition);
}

NTSTATUS NTAPI DetouredNtCreateKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _In_ HANDLE TransactionHandle,
    _Out_opt_ PULONG Disposition)
{
    HANDLE OriginalTokenHandle = INVALID_HANDLE_VALUE;
    NTSTATUS ContextStatus = NSudoDevilModeEnterPrivilegedContext(
        &OriginalTokenHandle);
    if (NT_SUCCESS(ContextStatus))
    {
        CreateOptions |= REG_OPTION_BACKUP_RESTORE;
    }

    NTSTATUS Status = OriginalNtCreateKeyTransacted(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        TitleIndex,
        Class,
        CreateOptions,
        TransactionHandle,
        Disposition);

    if (NT_SUCCESS(ContextStatus))
    {
        NSudoDevilModeLeavePrivilegedContext(OriginalTokenHandle);
    }

    return Status;
}


NTSTATUS NTAPI OriginalNtOpenKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    return reinterpret_cast<decltype(NtOpenKey)*>(
        OriginalAddress[FunctionType::NtOpenKey])(
            KeyHandle,
            DesiredAccess,
            ObjectAttributes);
}

NTSTATUS NTAPI DetouredNtOpenKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    ULONG Disposition = 0;

    NTSTATUS Status = DetouredNtCreateKey(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        0,
        nullptr,
        0,
        &Disposition);

    if (REG_CREATED_NEW_KEY == Disposition)
    {
        ::NtDeleteKey(*KeyHandle);

        ::NtClose(*KeyHandle);
        *KeyHandle = nullptr;

        Status = STATUS_OBJECT_NAME_NOT_FOUND;
    }

    return Status;
}


NTSTATUS NTAPI OriginalNtOpenKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE TransactionHandle)
{
    return reinterpret_cast<decltype(NtOpenKeyTransacted)*>(
        OriginalAddress[FunctionType::NtOpenKeyTransacted])(
            KeyHandle,
            DesiredAccess,
            ObjectAttributes,
            TransactionHandle);
}

NTSTATUS NTAPI DetouredNtOpenKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE TransactionHandle)
{
    ULONG Disposition = 0;

    NTSTATUS Status = DetouredNtCreateKeyTransacted(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        0,
        nullptr,
        0,
        TransactionHandle,
        &Disposition);

    if (REG_CREATED_NEW_KEY == Disposition)
    {
        ::NtDeleteKey(*KeyHandle);

        ::NtClose(*KeyHandle);
        *KeyHandle = nullptr;

        Status = STATUS_OBJECT_NAME_NOT_FOUND;
    }

    return Status;
}


NTSTATUS NTAPI OriginalNtOpenKeyEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions)
{
    return reinterpret_cast<decltype(NtOpenKeyEx)*>(
        OriginalAddress[FunctionType::NtOpenKeyEx])(
            KeyHandle,
            DesiredAccess,
            ObjectAttributes,
            OpenOptions);
}

NTSTATUS NTAPI DetouredNtOpenKeyEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions)
{
    HANDLE OriginalTokenHandle = INVALID_HANDLE_VALUE;
    NTSTATUS ContextStatus = NSudoDevilModeEnterPrivilegedContext(
        &OriginalTokenHandle);
    if (NT_SUCCESS(ContextStatus))
    {
        OpenOptions |= REG_OPTION_BACKUP_RESTORE;
    }

    NTSTATUS Status = OriginalNtOpenKeyEx(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        OpenOptions);

    if (NT_SUCCESS(ContextStatus))
    {
        NSudoDevilModeLeavePrivilegedContext(OriginalTokenHandle);
    }

    return Status;
}


NTSTATUS NTAPI OriginalNtOpenKeyTransactedEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions,
    _In_ HANDLE TransactionHandle)
{
    return reinterpret_cast<decltype(NtOpenKeyTransactedEx)*>(
        OriginalAddress[FunctionType::NtOpenKeyTransactedEx])(
            KeyHandle,
            DesiredAccess,
            ObjectAttributes,
            OpenOptions,
            TransactionHandle);
}

NTSTATUS NTAPI DetouredNtOpenKeyTransactedEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions,
    _In_ HANDLE TransactionHandle)
{
    HANDLE OriginalTokenHandle = INVALID_HANDLE_VALUE;
    NTSTATUS ContextStatus = NSudoDevilModeEnterPrivilegedContext(
        &OriginalTokenHandle);
    if (NT_SUCCESS(ContextStatus))
    {
        OpenOptions |= REG_OPTION_BACKUP_RESTORE;
    }

    NTSTATUS Status = OriginalNtOpenKeyTransactedEx(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        OpenOptions,
        TransactionHandle);

    if (NT_SUCCESS(ContextStatus))
    {
        NSudoDevilModeLeavePrivilegedContext(OriginalTokenHandle);
    }

    return Status;
}


NTSTATUS NTAPI OriginalNtCreateFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_reads_bytes_opt_(EaLength) PVOID EaBuffer,
    _In_ ULONG EaLength)
{
    return reinterpret_cast<decltype(NtCreateFile)*>(
        OriginalAddress[FunctionType::NtCreateFile])(
            FileHandle,
            DesiredAccess,
            ObjectAttributes,
            IoStatusBlock,
            AllocationSize,
            FileAttributes,
            ShareAccess,
            CreateDisposition,
            CreateOptions,
            EaBuffer,
            EaLength);
}


NTSTATUS NTAPI DetouredNtCreateFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_reads_bytes_opt_(EaLength) PVOID EaBuffer,
    _In_ ULONG EaLength)
{
    HANDLE OriginalTokenHandle = INVALID_HANDLE_VALUE;
    NTSTATUS ContextStatus = NSudoDevilModeEnterPrivilegedContext(
        &OriginalTokenHandle);
    if (NT_SUCCESS(ContextStatus))
    {
        CreateOptions |= FILE_OPEN_FOR_BACKUP_INTENT;
    }

    NTSTATUS Status = OriginalNtCreateFile(
        FileHandle,
        DesiredAccess,
        ObjectAttributes,
        IoStatusBlock,
        AllocationSize,
        FileAttributes,
        ShareAccess,
        CreateDisposition,
        CreateOptions,
        EaBuffer,
        EaLength);

    if (NT_SUCCESS(ContextStatus))
    {
        NSudoDevilModeLeavePrivilegedContext(OriginalTokenHandle);
    }

    return Status;
}


NTSTATUS NTAPI OriginalNtOpenFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG OpenOptions)
{
    return reinterpret_cast<decltype(NtOpenFile)*>(
        OriginalAddress[FunctionType::NtOpenFile])(
            FileHandle,
            DesiredAccess,
            ObjectAttributes,
            IoStatusBlock,
            ShareAccess,
            OpenOptions);
}

NTSTATUS NTAPI DetouredNtOpenFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG OpenOptions)
{
    HANDLE OriginalTokenHandle = INVALID_HANDLE_VALUE;
    NTSTATUS ContextStatus = NSudoDevilModeEnterPrivilegedContext(
        &OriginalTokenHandle);
    if (NT_SUCCESS(ContextStatus))
    {
        OpenOptions |= FILE_OPEN_FOR_BACKUP_INTENT;
    }

    NTSTATUS Status = OriginalNtOpenFile(
        FileHandle,
        DesiredAccess,
        ObjectAttributes,
        IoStatusBlock,
        ShareAccess,
        OpenOptions);

    if (NT_SUCCESS(ContextStatus))
    {
        NSudoDevilModeLeavePrivilegedContext(OriginalTokenHandle);
    }

    return Status;
}


static PVOID DetouredAddress[FunctionType::MaxFunctionType] =
{
    DetouredNtCreateKey,
    DetouredNtCreateKeyTransacted,
    DetouredNtOpenKey,
    DetouredNtOpenKeyTransacted,
    DetouredNtOpenKeyEx,
    DetouredNtOpenKeyTransactedEx,
    DetouredNtCreateFile,
    DetouredNtOpenFile
};

/**
 * Initialize the NSudo Devil Mode.
 */
EXTERN_C void WINAPI NSudoDevilModeInitialize()
{
    g_CreatePrivilegedTokenStatus = NSudoDevilModeCreatePrivilegedToken(
        &g_PrivilegedAccessToken);

    HMODULE ModuleHandle = ::GetModuleHandleW(L"ntdll.dll");

    if (nullptr != ModuleHandle)
    {
        OriginalAddress[FunctionType::NtOpenKeyEx] =
            ::GetProcAddress(ModuleHandle, "NtOpenKeyEx");
        OriginalAddress[FunctionType::NtOpenKeyTransactedEx] =
            ::GetProcAddress(ModuleHandle, "NtOpenKeyTransactedEx");
    }

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    for (size_t i = 0; i < FunctionType::MaxFunctionType; ++i)
    {
        if (nullptr == OriginalAddress[i])
        {
            continue;
        }

        DetourAttach(&OriginalAddress[i], DetouredAddress[i]);
    }

    DetourTransactionCommit();
}

/**
 * Uninitialize the NSudo Devil Mode.
 */
EXTERN_C void WINAPI NSudoDevilModeUninitialize()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    for (size_t i = 0; i < FunctionType::MaxFunctionType; ++i)
    {
        if (nullptr == OriginalAddress[i])
        {
            continue;
        }

        DetourDetach(&OriginalAddress[i], DetouredAddress[i]);
    }

    DetourTransactionCommit();

    if (NT_SUCCESS(g_CreatePrivilegedTokenStatus))
    {
        ::NtClose(g_PrivilegedAccessToken);
    }
}

BOOL APIENTRY DllMain(
    HMODULE Module,
    DWORD  Reason,
    LPVOID Reserved)
{
    UNREFERENCED_PARAMETER(Module);
    UNREFERENCED_PARAMETER(Reserved);

    if (DLL_PROCESS_ATTACH == Reason)
    {
        NSudoDevilModeInitialize();
    }
    else if (DLL_PROCESS_DETACH == Reason)
    {
        NSudoDevilModeUninitialize();
    }

    return TRUE;
}
