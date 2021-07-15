/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoDefragMemory.cpp
 * PURPOSE:   Implementation for Memory Defragment
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <MINT.h>

namespace
{
    static HRESULT DefragMemory()
    {
        using NtSetSystemInformationType = decltype(::NtSetSystemInformation)*;
        using RtlNtStatusToDosErrorType = decltype(::RtlNtStatusToDosError)*;

        NtSetSystemInformationType pNtSetSystemInformation = nullptr;
        RtlNtStatusToDosErrorType pRtlNtStatusToDosError = nullptr;

        HMODULE ModuleHandle = ::GetModuleHandleW(L"ntdll.dll");
        if (!ModuleHandle)
        {
            return E_NOINTERFACE;
        }

        pNtSetSystemInformation = reinterpret_cast<NtSetSystemInformationType>(
            ::GetProcAddress(ModuleHandle, "NtSetSystemInformation"));
        if (!pNtSetSystemInformation)
        {
            return E_NOINTERFACE;
        }

        pRtlNtStatusToDosError = reinterpret_cast<RtlNtStatusToDosErrorType>(
            ::GetProcAddress(ModuleHandle, "RtlNtStatusToDosError"));
        if (!pRtlNtStatusToDosError)
        {
            return E_NOINTERFACE;
        }

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
            Status = pNtSetSystemInformation(
                SystemMemoryListInformation,
                &CommandList[i],
                sizeof(SYSTEM_MEMORY_LIST_COMMAND));
            if (!NT_SUCCESS(Status))
            {
                break;
            }
        }

        return Mile::HResult::FromWin32(pRtlNtStatusToDosError(Status));
    }
}

EXTERN_C HRESULT WINAPI MoDefragMemory(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE CurrentProcessToken = INVALID_HANDLE_VALUE;

    if (::OpenProcessToken(
        ::GetCurrentProcess(),
        MAXIMUM_ALLOWED,
        &CurrentProcessToken))
    {
        LUID_AND_ATTRIBUTES RawPrivilege;
        RawPrivilege.Attributes = SE_PRIVILEGE_ENABLED;
        if (::LookupPrivilegeValueW(
            nullptr,
            SE_PROF_SINGLE_PROCESS_NAME,
            &RawPrivilege.Luid))
        {
            hr = Mile::AdjustTokenPrivilegesSimple(
                CurrentProcessToken,
                &RawPrivilege,
                1);
            if (hr.IsSucceeded())
            {
                hr = ::DefragMemory();
                if (hr.IsFailed())
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"DefragMemory");
                }
            }
            else
            {
                ::MoPrivateWriteErrorMessage(
                    Context,
                    hr,
                    L"Mile::AdjustTokenPrivilegesSimple");
            }
        }
        else
        {
            hr = Mile::HResultFromLastError(FALSE);
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"LookupPrivilegeValueW");
        }

        ::CloseHandle(CurrentProcessToken);
    }
    else
    {
        hr = Mile::HResultFromLastError(FALSE);
        ::MoPrivateWriteErrorMessage(
            Context,
            hr,
            L"OpenProcessToken");
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
