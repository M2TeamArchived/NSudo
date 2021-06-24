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
        if (hr.IsFailed())
        {
            Context->Write(
                Context,
                Mile::FormatString(
                    L"%s failed, ",
                    FailedPoint).c_str());
        }

        Context->Write(
            Context,
            Mile::GetHResultMessage(hr).c_str());

        if (hr.IsFailed())
        {
            Context->Write(
                Context,
                Mile::FormatString(
                    L" (0x%08lX)",
                    hr).c_str());
        }

        Context->Write(Context, L"\r\n");
    }
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
