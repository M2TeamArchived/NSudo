/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeWindowsEventLog.cpp
 * PURPOSE:   Implementation for Purge Windows Event Log
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <winevt.h>

EXTERN_C HRESULT WINAPI MoPurgeWindowsEventLog(
    _In_ PNSUDO_CONTEXT Context)
{
    using EvtOpenChannelEnumType = decltype(::EvtOpenChannelEnum)*;
    using EvtNextChannelPathType = decltype(::EvtNextChannelPath)*;
    using EvtClearLogType = decltype(::EvtClearLog)*;
    using EvtOpenLogType = decltype(::EvtOpenLog)*;
    using EvtGetLogInfoType = decltype(::EvtGetLogInfo)*;
    using EvtCloseType = decltype(::EvtClose)*;

    Mile::HResult hr = S_OK;
    HMODULE ModuleHandle = nullptr;
    EvtOpenChannelEnumType pEvtOpenChannelEnum = nullptr;
    EvtNextChannelPathType pEvtNextChannelPath = nullptr;
    EvtClearLogType pEvtClearLog = nullptr;
    EvtOpenLogType pEvtOpenLog = nullptr;
    EvtGetLogInfoType pEvtGetLogInfo = nullptr;
    EvtCloseType pEvtClose = nullptr;
    EVT_HANDLE ChannelEnumHandle = nullptr;

    do
    {
        DWORD PurgeMode = ::MoPrivateParsePurgeMode(Context);
        if (PurgeMode == 0)
        {
            hr = Mile::HResult::FromWin32(ERROR_CANCELLED);
            break;
        }

        if (PurgeMode != MO_PRIVATE_PURGE_MODE_SCAN &&
            PurgeMode != MO_PRIVATE_PURGE_MODE_PURGE)
        {
            hr = E_NOINTERFACE;
            break;
        }

        ModuleHandle = Mile::LoadLibraryFromSystem32(L"wevtapi.dll");
        if (!ModuleHandle)
        {
            hr = E_NOINTERFACE;
            break;
        }

        pEvtOpenChannelEnum = reinterpret_cast<EvtOpenChannelEnumType>(
            ::GetProcAddress(ModuleHandle, "EvtOpenChannelEnum"));
        if (!pEvtOpenChannelEnum)
        {
            hr = E_NOINTERFACE;
            break;
        }

        pEvtNextChannelPath = reinterpret_cast<EvtNextChannelPathType>(
            ::GetProcAddress(ModuleHandle, "EvtNextChannelPath"));
        if (!pEvtNextChannelPath)
        {
            hr = E_NOINTERFACE;
            break;
        }

        pEvtClearLog = reinterpret_cast<EvtClearLogType>(
            ::GetProcAddress(ModuleHandle, "EvtClearLog"));
        if (!pEvtClearLog)
        {
            hr = E_NOINTERFACE;
            break;
        }

        pEvtOpenLog = reinterpret_cast<EvtOpenLogType>(
            ::GetProcAddress(ModuleHandle, "EvtOpenLog"));
        if (!pEvtOpenLog)
        {
            hr = E_NOINTERFACE;
            break;
        }

        pEvtGetLogInfo = reinterpret_cast<EvtGetLogInfoType>(
            ::GetProcAddress(ModuleHandle, "EvtGetLogInfo"));
        if (!pEvtGetLogInfo)
        {
            hr = E_NOINTERFACE;
            break;
        }

        pEvtClose = reinterpret_cast<EvtCloseType>(
            ::GetProcAddress(ModuleHandle, "EvtClose"));
        if (!pEvtClose)
        {
            hr = E_NOINTERFACE;
            break;
        }

        ChannelEnumHandle = pEvtOpenChannelEnum(nullptr, 0);
        if (!ChannelEnumHandle)
        {
            hr = Mile::HResultFromLastError(FALSE);
            break;
        }

        UINT64 AllocatedSpace = 0;
        while (true)
        {
            // The event name will save as the registry key name and maximum
            // length of registry key name is 256 with the null terminator.
            const DWORD ChannelBufferMaximumSize = 256;

            wchar_t ChannelBuffer[ChannelBufferMaximumSize];
            DWORD ChannelBufferSize = ChannelBufferMaximumSize;

            if (pEvtNextChannelPath(
                ChannelEnumHandle,
                ChannelBufferSize,
                reinterpret_cast<LPWSTR>(ChannelBuffer),
                &ChannelBufferSize))
            {
                if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
                {
                    EVT_HANDLE LogHandle = pEvtOpenLog(
                        nullptr,
                        ChannelBuffer,
                        EvtOpenChannelPath);
                    if (LogHandle)
                    {
                        EVT_VARIANT FileSize = { 0 };
                        DWORD cbUsed = 0;

                        if (pEvtGetLogInfo(
                            LogHandle,
                            EvtLogFileSize,
                            sizeof(FileSize),
                            &FileSize,
                            &cbUsed))
                        {
                            ::MoPrivateWriteLine(
                                Context,
                                Context->GetTranslation(
                                    Context,
                                    "DetectedText"),
                                ChannelBuffer);

                            // If succeed and the type is OK, return the size.
                            if (EvtVarTypeUInt64 == FileSize.Type)
                                AllocatedSpace += FileSize.UInt64Val;
                        }
                        else
                        {
                            ::MoPrivateWriteErrorMessage(
                                Context,
                                Mile::HResultFromLastError(FALSE),
                                L"%s(%s)",
                                L"EvtGetLogInfo",
                                ChannelBuffer);
                        }

                        pEvtClose(LogHandle);
                    }
                    else
                    {
                        ::MoPrivateWriteErrorMessage(
                            Context,
                            Mile::HResultFromLastError(FALSE),
                            L"%s(%s)",
                            L"EvtOpenLog",
                            ChannelBuffer);
                    }
                }
                else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
                {
                    if (pEvtClearLog(
                        nullptr,
                        reinterpret_cast<LPCWSTR>(ChannelBuffer),
                        nullptr,
                        0))
                    {
                        ::MoPrivateWriteLine(
                            Context,
                            Context->GetTranslation(
                                Context,
                                "ProcessedText"),
                            ChannelBuffer);
                    }
                    else
                    {
                        ::MoPrivateWriteErrorMessage(
                            Context,
                            Mile::HResultFromLastError(FALSE),
                            L"%s(%s)",
                            L"EvtClearLog",
                            ChannelBuffer);
                    }
                }
            }
            else
            {
                Mile::HResult Result = Mile::HResultFromLastError(FALSE);

                if (Result.GetCode() == ERROR_NO_MORE_ITEMS)
                {
                    if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
                    {
                        ::MoPrivatePrintPurgeScanResult(
                            Context,
                            AllocatedSpace);
                    }
                    else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
                    {
                        // Clear System event log again in the end because when
                        // system event log will add new events when clearing
                        // the event log.
                        if (pEvtClearLog(
                            nullptr,
                            L"System",
                            nullptr,
                            0))
                        {
                            ::MoPrivateWriteLine(
                                Context,
                                Context->GetTranslation(
                                    Context,
                                    "ProcessedText"),
                                L"System");
                        }
                        else
                        {
                            ::MoPrivateWriteErrorMessage(
                                Context,
                                Mile::HResultFromLastError(FALSE),
                                L"%s(%s)",
                                L"EvtClearLog",
                                L"System");
                        }
                    }
                }
                else
                {
                    hr = Result;
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"EvtNextChannelPath");
                }

                break;
            }
        }

    } while (false);

    if (ChannelEnumHandle)
    {
        pEvtClose(ChannelEnumHandle);
    }

    if (ModuleHandle)
    {
        ::FreeLibrary(ModuleHandle);
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
