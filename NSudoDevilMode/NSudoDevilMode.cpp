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

static HANDLE PrivilegedAccessToken = INVALID_HANDLE_VALUE;


static decltype(NtClose)* g_NtClose = nullptr;
static decltype(NtDeleteKey)* g_NtDeleteKey = nullptr;


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


static PVOID OriginalAddress[FunctionType::MaxFunctionType];


NTSTATUS NTAPI DetouredNtCreateKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition)
{
    decltype(NtCreateKey)* OriginalNtCreateKey =
        reinterpret_cast<decltype(NtCreateKey)*>(
            OriginalAddress[FunctionType::NtCreateKey]);

    return OriginalNtCreateKey(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        TitleIndex,
        Class,
        CreateOptions | REG_OPTION_BACKUP_RESTORE,
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
    decltype(NtCreateKeyTransacted)* OriginalNtCreateKeyTransacted =
        reinterpret_cast<decltype(NtCreateKeyTransacted)*>(
            OriginalAddress[FunctionType::NtCreateKeyTransacted]);

    return OriginalNtCreateKeyTransacted(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        TitleIndex,
        Class,
        CreateOptions | REG_OPTION_BACKUP_RESTORE,
        TransactionHandle,
        Disposition);
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
        g_NtDeleteKey(*KeyHandle);

        g_NtClose(*KeyHandle);
        *KeyHandle = nullptr;

        Status = STATUS_OBJECT_NAME_NOT_FOUND;
    }

    return Status;
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
        g_NtDeleteKey(*KeyHandle);

        g_NtClose(*KeyHandle);
        *KeyHandle = nullptr;

        Status = STATUS_OBJECT_NAME_NOT_FOUND;
    }

    return Status;
}

NTSTATUS NTAPI DetouredNtOpenKeyEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions)
{
    decltype(NtOpenKeyEx)* OriginalNtOpenKeyEx =
        reinterpret_cast<decltype(NtOpenKeyEx)*>(
            OriginalAddress[FunctionType::NtOpenKeyEx]);

    return OriginalNtOpenKeyEx(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        OpenOptions | REG_OPTION_BACKUP_RESTORE);
}

NTSTATUS NTAPI DetouredNtOpenKeyTransactedEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions,
    _In_ HANDLE TransactionHandle)
{
    decltype(NtOpenKeyTransactedEx)* OriginalNtOpenKeyTransactedEx =
        reinterpret_cast<decltype(NtOpenKeyTransactedEx)*>(
            OriginalAddress[FunctionType::NtOpenKeyTransactedEx]);

    return OriginalNtOpenKeyTransactedEx(
        KeyHandle,
        DesiredAccess,
        ObjectAttributes,
        OpenOptions | REG_OPTION_BACKUP_RESTORE,
        TransactionHandle);
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
    decltype(NtCreateFile)* OriginalNtCreateFile =
        reinterpret_cast<decltype(NtCreateFile)*>(
            OriginalAddress[FunctionType::NtCreateFile]);

    return OriginalNtCreateFile(
        FileHandle,
        DesiredAccess,
        ObjectAttributes,
        IoStatusBlock,
        AllocationSize,
        FileAttributes,
        ShareAccess,
        CreateDisposition,
        CreateOptions | FILE_OPEN_FOR_BACKUP_INTENT,
        EaBuffer,
        EaLength);
}

NTSTATUS NTAPI DetouredNtOpenFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG OpenOptions)
{
    decltype(NtOpenFile)* OriginalNtOpenFile =
        reinterpret_cast<decltype(NtOpenFile)*>(
            OriginalAddress[FunctionType::NtOpenFile]);

    return OriginalNtOpenFile(
        FileHandle,
        DesiredAccess,
        ObjectAttributes,
        IoStatusBlock,
        ShareAccess,
        OpenOptions | FILE_OPEN_FOR_BACKUP_INTENT);
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
    /*
    SeBackupPrivilege                         备份文件和目录                     已禁用
    SeRestorePrivilege                        还原文件和目录                     已禁用
    */

    HMODULE ModuleHandle = GetModuleHandleW(L"ntdll.dll");

    if (nullptr != ModuleHandle)
    {
        g_NtClose = reinterpret_cast<decltype(NtClose)*>(
            GetProcAddress(ModuleHandle, "NtClose"));
        g_NtDeleteKey = reinterpret_cast<decltype(NtDeleteKey)*>(
            GetProcAddress(ModuleHandle, "NtDeleteKey"));

        OriginalAddress[FunctionType::NtCreateKey] = GetProcAddress(
            ModuleHandle, "NtCreateKey");
        OriginalAddress[FunctionType::NtCreateKeyTransacted] = GetProcAddress(
            ModuleHandle, "NtCreateKeyTransacted");
        OriginalAddress[FunctionType::NtOpenKey] = GetProcAddress(
            ModuleHandle, "NtOpenKey");
        OriginalAddress[FunctionType::NtOpenKeyTransacted] = GetProcAddress(
            ModuleHandle, "NtOpenKeyTransacted");
        OriginalAddress[FunctionType::NtOpenKeyEx] = GetProcAddress(
            ModuleHandle, "NtOpenKeyEx");
        OriginalAddress[FunctionType::NtOpenKeyTransactedEx] = GetProcAddress(
            ModuleHandle, "NtOpenKeyTransactedEx");

        OriginalAddress[FunctionType::NtCreateFile] = GetProcAddress(
            ModuleHandle, "NtCreateFile");
        OriginalAddress[FunctionType::NtOpenFile] = GetProcAddress(
            ModuleHandle, "NtOpenFile");
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

    CloseHandle(PrivilegedAccessToken);
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
