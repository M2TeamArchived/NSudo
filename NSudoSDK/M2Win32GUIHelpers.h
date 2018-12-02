/******************************************************************************
Project: M2-Team Common Library
Description: Definition for the Win32 desktop GUI helper functions.
File Name: M2Win32GUIHelpers.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_WIN32_GUI_HELPERS_
#define _M2_WIN32_GUI_HELPERS_

#include <Windows.h>

/// <summary>
/// Enables the Per-Monitor DPI Aware for the specified dialog using the
/// internal API from Windows.
/// </summary>
/// <returns>
/// The function will return a INT. If failed. returns -1.
/// </returns>
/// <remarks>
/// You need to use this function in Windows 10 Threshold 1 or later.
/// </remarks>
INT M2EnablePerMonitorDialogScaling();

/// <summary>
/// Creates and shows the message dialog.
/// </summary>
/// <param name="hInstance">
/// A handle to the module which contains the message dialog resource. If this
/// parameter is nullptr, then the current executable is used.
/// </param>
/// <param name="hWndParent">
/// A handle to the window that owns the message dialog.
/// </param>
/// <param name="lpIconName">
/// Pointer that references the icon to be displayed in the message dialog. If
/// this parameter is nullptr or the hInstance parameter is nullptr, no icon
/// will be displayed. This parameter must be an integer resource identifier
/// passed to the MAKEINTRESOURCE macro.
/// </param>
/// <param name="lpTitle">
/// Pointer to the string to be used for the message dialog title. This
/// parameter is a null-terminated, Unicode string.
/// </param>
/// <param name="lpContent">
/// Pointer to the string to be used for the message dialog content. This
/// parameter is a null-terminated, Unicode string.
/// </param>
/// <returns>
/// If the function succeeds, the return value is the value of the nResult
/// parameter specified in the call to the EndDialog function used to terminate
/// the message dialog. If the function fails because the hWndParent parameter
/// is invalid, the return value is zero. The function returns zero in this case
/// for compatibility with previous versions of Windows. If the function fails
/// for any other reason, the return value is –1. To get extended error
/// information, call GetLastError.
/// </returns>
INT_PTR WINAPI M2MessageDialog(
    _In_opt_ HINSTANCE hInstance,
    _In_opt_ HWND hWndParent,
    _In_opt_ LPCWSTR lpIconName,
    _In_ LPCWSTR lpTitle,
    _In_ LPCWSTR lpContent);

#endif // _M2_WIN32_GUI_HELPERS_
