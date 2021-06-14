/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.PiConsole.h
 * PURPOSE:   Definition for Portable Interactive Console (Pi Console)
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_PI_CONSOLE
#define MILE_PI_CONSOLE

#include "Mile.Windows.h"

namespace Mile
{
    /**
     * @brief Creates a Pi Console window.
     * @param InstanceHandle A handle to the instance of the module to be
     *                       associated with the Pi Console window.
     * @param WindowIconHandle A handle to the icon to be associated with the
     *                         Pi Console window.
     * @param WindowTitle The title of the Pi Console window.
     * @param ShowWindowMode Controls how the Pi Console window is to be shown.
     * @return 
    */
    HWND CreatePiConsole(
        _In_ HINSTANCE InstanceHandle,
        _In_ HICON WindowIconHandle,
        _In_ LPCWSTR WindowTitle,
        _In_ DWORD ShowWindowMode);

    /**
     * @brief Prints messages to a Pi Console window.
     * @param WindowHandle The handle of a Pi Console window.
     * @param Content The content of the message you want to print.
    */
    void PrintMessageToPiConsole(
        _In_ HWND WindowHandle,
        _In_ LPCWSTR Content);

    /**
     * @brief Gets input from a Pi Console window.
     * @param WindowHandle The handle of a Pi Console window.
     * @param InputPrompt The prompt you want to notice to the user.
     * @return The user input. If the return value is not nullptr, you should
     *         use Mile::HeapMemory::Free to release.
    */
    LPCWSTR GetInputFromPiConsole(
        _In_ HWND WindowHandle,
        _In_ LPCWSTR InputPrompt);
}

#endif // !MILE_PI_CONSOLE
