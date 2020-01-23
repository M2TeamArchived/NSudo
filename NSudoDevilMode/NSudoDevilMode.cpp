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

#include <stdint.h>

#include "MINT.h"
#include "Detours/detours.h"

namespace FunctionType
{
    enum
    {
        NtCreateKey,
        NtCreateKeyTransacted,
        NtOpenKey,
        NtOpenKeyTransacted,
        NtCreateFile,
        NtOpenFile,

        NtOpenKeyEx,
        NtOpenKeyTransactedEx,

        MaxFunctionType
    };
}

typedef struct _NSUDO_DEVIL_MODE_SHARED_DATA
{
    HANDLE PrivilegedToken;

    PVOID OriginalAddress[FunctionType::MaxFunctionType];
    PVOID DetouredAddress[FunctionType::MaxFunctionType];

} NSUDO_DEVIL_MODE_SHARED_DATA, *PNSUDO_DEVIL_MODE_SHARED_DATA;

static NSUDO_DEVIL_MODE_SHARED_DATA g_SharedData;


NTSTATUS NSudoDevilModeEnterPrivilegedContext(
    _Out_ PHANDLE OriginalTokenHandle)
{
    if (g_SharedData.PrivilegedToken == INVALID_HANDLE_VALUE)
    {
        return STATUS_NOT_SUPPORTED;
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
        &g_SharedData.PrivilegedToken,
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
        g_SharedData.OriginalAddress[FunctionType::NtCreateKey])(
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
        g_SharedData.OriginalAddress[FunctionType::NtCreateKeyTransacted])(
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
        g_SharedData.OriginalAddress[FunctionType::NtOpenKey])(
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
        g_SharedData.OriginalAddress[FunctionType::NtOpenKeyTransacted])(
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
        g_SharedData.OriginalAddress[FunctionType::NtOpenKeyEx])(
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
        g_SharedData.OriginalAddress[FunctionType::NtOpenKeyTransactedEx])(
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
        g_SharedData.OriginalAddress[FunctionType::NtCreateFile])(
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
        g_SharedData.OriginalAddress[FunctionType::NtOpenFile])(
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

/**
 * Initialize the NSudo Devil Mode.
 */
void NSudoDevilModeInitialize()
{
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
            &g_SharedData.PrivilegedToken);

        ::NtClose(CurrentProcessToken);
    }

    if (NT_SUCCESS(Status))
    {
        uint8_t TPBlock[2 * sizeof(LUID_AND_ATTRIBUTES) + sizeof(DWORD)];
        PTOKEN_PRIVILEGES pTP = reinterpret_cast<PTOKEN_PRIVILEGES>(TPBlock);

        pTP->PrivilegeCount = 2;

        pTP->Privileges[0].Luid.LowPart = SE_BACKUP_PRIVILEGE;
        pTP->Privileges[0].Luid.HighPart = 0;
        pTP->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        pTP->Privileges[1].Luid.LowPart = SE_RESTORE_PRIVILEGE;
        pTP->Privileges[1].Luid.HighPart = 0;
        pTP->Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;

        Status = ::NtAdjustPrivilegesToken(
            g_SharedData.PrivilegedToken,
            FALSE,
            pTP,
            sizeof(TPBlock),
            nullptr,
            nullptr);
        if (ERROR_SUCCESS != Status)
        {
            ::NtClose(g_SharedData.PrivilegedToken);
            Status = STATUS_NOT_SUPPORTED;
        }
    }

    if (!NT_SUCCESS(Status))
    {
        g_SharedData.PrivilegedToken = INVALID_HANDLE_VALUE;
    }

    g_SharedData.OriginalAddress[FunctionType::NtCreateKey] =
        ::NtCreateKey;
    g_SharedData.DetouredAddress[FunctionType::NtCreateKey] =
        ::DetouredNtCreateKey;

    g_SharedData.OriginalAddress[FunctionType::NtCreateKeyTransacted] =
        ::NtCreateKeyTransacted;
    g_SharedData.DetouredAddress[FunctionType::NtCreateKeyTransacted] =
        ::DetouredNtCreateKeyTransacted;

    g_SharedData.OriginalAddress[FunctionType::NtOpenKey] =
        ::NtOpenKey;
    g_SharedData.DetouredAddress[FunctionType::NtOpenKey] =
        ::DetouredNtOpenKey;

    g_SharedData.OriginalAddress[FunctionType::NtOpenKeyTransacted] =
        ::NtOpenKeyTransacted;
    g_SharedData.DetouredAddress[FunctionType::NtOpenKeyTransacted] =
        ::DetouredNtOpenKeyTransacted;

    g_SharedData.OriginalAddress[FunctionType::NtCreateFile] =
        ::NtCreateFile;
    g_SharedData.DetouredAddress[FunctionType::NtCreateFile] =
        ::DetouredNtCreateFile;

    g_SharedData.OriginalAddress[FunctionType::NtOpenFile] =
        ::NtOpenFile;
    g_SharedData.DetouredAddress[FunctionType::NtOpenFile] =
        ::DetouredNtOpenFile;

    HMODULE ModuleHandle = ::GetModuleHandleW(L"ntdll.dll");

    if (ModuleHandle)
    {
        g_SharedData.OriginalAddress[FunctionType::NtOpenKeyEx] =
            ::GetProcAddress(ModuleHandle, "NtOpenKeyEx");
        g_SharedData.DetouredAddress[FunctionType::NtOpenKeyEx] =
            ::DetouredNtOpenKeyEx;

        g_SharedData.OriginalAddress[FunctionType::NtOpenKeyTransactedEx] =
            ::GetProcAddress(ModuleHandle, "NtOpenKeyTransactedEx");
        g_SharedData.DetouredAddress[FunctionType::NtOpenKeyTransactedEx] =
            ::DetouredNtOpenKeyTransactedEx;
    }
}

/**
 * Uninitialize the NSudo Devil Mode.
 */
void NSudoDevilModeUninitialize()
{
    if (g_SharedData.PrivilegedToken != INVALID_HANDLE_VALUE)
    {
        ::NtClose(g_SharedData.PrivilegedToken);
    }
}

BOOL APIENTRY DllMain(
    HMODULE Module,
    DWORD  Reason,
    LPVOID Reserved)
{
    UNREFERENCED_PARAMETER(Module);
    UNREFERENCED_PARAMETER(Reserved);

    if (DLL_PROCESS_ATTACH == Reason || DLL_PROCESS_DETACH == Reason)
    {
        if (DLL_PROCESS_ATTACH == Reason)
        {
            NSudoDevilModeInitialize();
        }

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        for (size_t i = 0; i < FunctionType::MaxFunctionType; ++i)
        {
            if (g_SharedData.OriginalAddress[i])
            {
                if (DLL_PROCESS_ATTACH == Reason)
                {
                    DetourAttach(
                        &g_SharedData.OriginalAddress[i],
                        g_SharedData.DetouredAddress[i]);
                }
                else if (DLL_PROCESS_DETACH == Reason)
                {
                    DetourDetach(
                        &g_SharedData.OriginalAddress[i],
                        g_SharedData.DetouredAddress[i]);
                }
            }
        }

        DetourTransactionCommit();

        if (DLL_PROCESS_DETACH == Reason)
        {
            NSudoDevilModeUninitialize();
        }
    }

    return TRUE;
}
