/*
 * PROJECT:   NSudo Sweeper
 * FILE:      NSudoSweeper.cpp
 * PURPOSE:   Implementation for NSudo Sweeper
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#include "NSudoSweeperVersion.h"

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    ::MessageBoxW(
        nullptr,
        L"Hello World!",
        L"M2-Team NSudo Sweeper " NSUDO_SWEEPER_VERSION_STRING, 
        MB_ICONINFORMATION);

    return 0;
}
