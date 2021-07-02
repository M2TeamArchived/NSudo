/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MouriOptimizationPlugin.cpp
 * PURPOSE:   Private implementation for Mouri Optimization Plugin
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

void MoPrivatePrintFinalResult(
    _In_ PNSUDO_CONTEXT Context,
    _In_ Mile::HResult const& hr,
    _In_ LPCWSTR FailedPoint)
{
    if (Context)
    {
        if (FailedPoint)
        {
            Context->Write(
                Context,
                Mile::FormatUtf16String(
                    L"%s: ",
                    FailedPoint).c_str());
        }

        Context->Write(
            Context,
            Mile::GetHResultMessage(hr).c_str());

        if (hr.IsFailed())
        {
            Context->Write(
                Context,
                Mile::FormatUtf16String(
                    L" (0x%08lX)",
                    hr).c_str());
        }

        Context->Write(Context, L"\r\n");
    }
}

void MoPrivatePrintPurgeScanResult(
    _In_ PNSUDO_CONTEXT Context,
    _In_ std::uint64_t ByteSize)
{
    if (Context)
    {
        //L"Total amount of disk space you may gain: ";
        //L"或许可获得的磁盘空间总量: ";

        Context->Write(
            Context,
            L"Total amount of disk space you may gain: ");
        Context->Write(
            Context,
            Mile::ConvertByteSizeToUtf16String(ByteSize).c_str());
        Context->Write(
            Context,
            L".\r\n");
    }
}

DWORD MoPrivateParsePurgeMode(
    _In_ PNSUDO_CONTEXT Context)
{
    DWORD Result = 0;

    std::vector<std::wstring> Arguments = Mile::SpiltCommandArguments(
        Context->GetContextPluginCommandArguments(Context));
    for (auto& Argument : Arguments)
    {
        if (0 == ::_wcsicmp(Argument.c_str(), L"/Scan"))
        {
            Result = MO_PRIVATE_PURGE_MODE_SCAN;
            break;
        }
        else if (0 == ::_wcsicmp(Argument.c_str(), L"/Purge"))
        {
            Result = MO_PRIVATE_PURGE_MODE_PURGE;
            break;
        }
    }

    if (Result == 0)
    {
        // TODO: Maybe we should ask for user to choice
    }

    Context->Write(Context, L"Purge Mode: ");

    if (Result == MO_PRIVATE_PURGE_MODE_SCAN)
    {
        Context->Write(Context, L"Scan");
    }
    else if(Result == MO_PRIVATE_PURGE_MODE_PURGE)
    {
        Context->Write(Context, L"Purge");
    }
    else
    {
        Context->Write(Context, L"Canceled");
    }

    Context->Write(
        Context,
        L".\r\n");

    return Result;
}

BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD fdwReason,
    _In_ LPVOID lpvReserved)
{
    UNREFERENCED_PARAMETER(hinstDLL);
    UNREFERENCED_PARAMETER(lpvReserved);

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
