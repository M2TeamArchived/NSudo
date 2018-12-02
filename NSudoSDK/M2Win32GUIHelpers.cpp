/******************************************************************************
Project: M2-Team Common Library
Description: Implementation for the Win32 desktop GUI helper functions.
File Name: M2Win32GUIHelpers.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

#include <Windows.h>
#include <VersionHelpers.h>

#include "M2Win32GUIHelpers.h"
#include "M2MessageDialogResource.h"

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
INT M2EnablePerMonitorDialogScaling()
{
    // Fix for Windows Vista and Server 2008.
    if (!IsWindows10OrGreater()) return -1;

    typedef INT(WINAPI *PFN_EnablePerMonitorDialogScaling)();

    HMODULE hModule = nullptr;
    PFN_EnablePerMonitorDialogScaling pFunc = nullptr;

    hModule = GetModuleHandleW(L"user32.dll");
    if (!hModule) return -1;

    pFunc = reinterpret_cast<PFN_EnablePerMonitorDialogScaling>(
        GetProcAddress(hModule, (LPCSTR)2577));
    if (!pFunc) return -1;

    return pFunc();
}

/// <summary>
/// The parameter struct of the message dialog.
/// </summary>
struct DIALOG_BOX_PARAM
{
    HINSTANCE hInstance;
    LPCWSTR lpIconName;
    LPCWSTR lpTitle;
    LPCWSTR lpContent;
};

/// <summary>
/// The callback function used of the message dialog.
/// </summary>
/// <param name="hwndDlg">
/// A handle to the message dialog.
/// </param>
/// <param name="uMsg">
/// The message.
/// </param>
/// <param name="wParam">
/// Additional message-specific information.
/// </param>
/// <param name="lParam">
/// Additional message-specific information.
/// </param>
/// <returns>
/// Typically, the dialog box procedure should return TRUE if it processed the
/// message, and FALSE if it did not. If the dialog box procedure returns FALSE,
/// the dialog manager performs the default dialog operation in response to the
/// message.
/// </returns>
INT_PTR CALLBACK M2MessageDialogDialogCallBack(
    _In_ HWND   hwndDlg,
    _In_ UINT   uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    if (WM_INITDIALOG == uMsg)
    {
        HICON hIcon = reinterpret_cast<HICON>(LoadImageW(
            reinterpret_cast<DIALOG_BOX_PARAM*>(lParam)->hInstance,
            reinterpret_cast<DIALOG_BOX_PARAM*>(lParam)->lpIconName,
            IMAGE_ICON,
            256,
            256,
            LR_SHARED));
        if (nullptr != hIcon)
        {
            SendMessageW(
                hwndDlg,
                WM_SETICON,
                ICON_SMALL,
                reinterpret_cast<LPARAM>(hIcon));
            SendMessageW(
                hwndDlg,
                WM_SETICON,
                ICON_BIG,
                reinterpret_cast<LPARAM>(hIcon));
        }

        SetWindowTextW(
            hwndDlg,
            reinterpret_cast<DIALOG_BOX_PARAM*>(lParam)->lpTitle);
        SetWindowTextW(
            GetDlgItem(hwndDlg, IDC_MESSAGE_DIALOG_EDIT),
            reinterpret_cast<DIALOG_BOX_PARAM*>(lParam)->lpContent);

        return (INT_PTR)TRUE;
    }
    else if (
        (WM_CLOSE == uMsg) ||
        (WM_COMMAND == uMsg && IDOK == LOWORD(wParam)))
    {
        EndDialog(hwndDlg, 0);
    }

    return FALSE;
}

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
    _In_ LPCWSTR lpContent)
{
    DIALOG_BOX_PARAM Param = { hInstance, lpIconName,lpTitle,lpContent };

    M2EnablePerMonitorDialogScaling();

    return DialogBoxParamW(
        hInstance,
        MAKEINTRESOURCEW(IDD_MESSAGE_DIALOG),
        hWndParent,
        M2MessageDialogDialogCallBack,
        reinterpret_cast<LPARAM>(&Param));
}
