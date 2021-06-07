/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoDefragMemory.cpp
 * PURPOSE:   Implementation for Memory Defragment
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <NSudoContextPlugin.h>

#include <Mile.Windows.h>
#include <MINT.h>

EXTERN_C HRESULT WINAPI MoDefragMemory(
    _In_ PNSUDO_CONTEXT Context,
    _In_ HMODULE ModuleHandle,
    _In_ LPCWSTR CommandLine)
{
    Mile::UnreferencedParameter(ModuleHandle);
    Mile::UnreferencedParameter(CommandLine);

    HANDLE CurrentProcessToken = INVALID_HANDLE_VALUE;

    Mile::HResult hr = Mile::HResultFromLastError(::OpenProcessToken(
        ::GetCurrentProcess(),
        MAXIMUM_ALLOWED,
        &CurrentProcessToken));
    if (hr.IsSucceeded())
    {
        LUID_AND_ATTRIBUTES RawPrivilege;

        hr = Mile::HResultFromLastError(::LookupPrivilegeValueW(
            nullptr,
            SE_PROF_SINGLE_PROCESS_NAME,
            &RawPrivilege.Luid));

        RawPrivilege.Attributes = SE_PRIVILEGE_ENABLED;

        if (hr.IsSucceeded())
        {
            hr = Mile::AdjustTokenPrivilegesSimple(
                CurrentProcessToken,
                &RawPrivilege,
                1);
        }

        ::CloseHandle(CurrentProcessToken);
    }

    if (hr.IsSucceeded())
    {
        // Working Sets -> Modified Page List -> Standby List

        SYSTEM_MEMORY_LIST_COMMAND CommandList[] =
        {
            SYSTEM_MEMORY_LIST_COMMAND::MemoryEmptyWorkingSets,
            SYSTEM_MEMORY_LIST_COMMAND::MemoryFlushModifiedList,
            SYSTEM_MEMORY_LIST_COMMAND::MemoryPurgeStandbyList
        };

        NTSTATUS Status = STATUS_SUCCESS;

        for (size_t i = 0; i < sizeof(CommandList) / sizeof(*CommandList); ++i)
        {
            Status = ::NtSetSystemInformation(
                SystemMemoryListInformation,
                &CommandList[i],
                sizeof(SYSTEM_MEMORY_LIST_COMMAND));
            if (!NT_SUCCESS(Status))
            {
                break;
            }
        }

        hr = Mile::HResult::FromWin32(::RtlNtStatusToDosError(Status));
    }

    Context->PrintMessage(Mile::GetHResultMessage(hr).c_str());

    return hr;
}
