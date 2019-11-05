/*
 * PROJECT:   NSudo User Experience Library
 * FILE:      DllMain.cpp
 * PURPOSE:   DllMain Implementation for NSudo User Experience Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

EXTERN_C HMODULE g_NSudoUXModule = nullptr;

void NSudoUXInitialize();

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(hModule);
    UNREFERENCED_PARAMETER(lpReserved);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_NSudoUXModule = hModule;
        NSudoUXInitialize();
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
