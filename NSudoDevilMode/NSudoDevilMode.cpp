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

struct DetouredFunction
{
    PVOID Original;
    PVOID Detoured;
};

static LONG dwSlept = 0;


// Target pointer for the uninstrumented Sleep API.
//
static decltype(Sleep)* TrueSleep = Sleep;

// Detour function that replaces the Sleep API.
//
VOID WINAPI TimedSleep(DWORD dwMilliseconds)
{
    // Save the before and after times around calling the Sleep API.
    DWORD dwBeg = GetTickCount();
    TrueSleep(dwMilliseconds);
    DWORD dwEnd = GetTickCount();

    InterlockedExchangeAdd(&dwSlept, dwEnd - dwBeg);
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
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&reinterpret_cast<PVOID&>(TrueSleep), TimedSleep);
        DetourTransactionCommit();
    }
    else if (DLL_PROCESS_DETACH == Reason)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&reinterpret_cast<PVOID&>(TrueSleep), TimedSleep);
        DetourTransactionCommit();
    }

    return TRUE;
}
