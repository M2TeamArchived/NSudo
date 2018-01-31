/******************************************************************************
Project: M2-Team Common Library
Description: Definition for the message dialog.
File Name: M2MessageDialog.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_MESSAGE_DIALOG_
#define _M2_MESSAGE_DIALOG_

#include <Windows.h>

// Creates and shows the message dialog.
// Parameters:
//   hInstance: A handle to the module which contains the message dialog 
//   resource. If this parameter is nullptr, then the current executable is 
//   used.
//   hWndParent: A handle to the window that owns the message dialog. 
//   lpIconName: Pointer that references the icon to be displayed in the 
//   message dialog. If this parameter is nullptr or the hInstance parameter is
//   nullptr, no icon will be displayed. This parameter must be an integer 
//   resource identifier passed to the MAKEINTRESOURCE macro.
//   lpTitle: Pointer to the string to be used for the message dialog title. 
//   This parameter is a null-terminated, Unicode string. 
//   lpContent: Pointer to the string to be used for the message dialog 
//   content. This parameter is a null-terminated, Unicode string. 
// Return value:
//   If the function succeeds, the return value is the value of the nResult
//   parameter specified in the call to the EndDialog function used to 
//   terminate the message dialog.
//   If the function fails because the hWndParent parameter is invalid, the 
//   return value is zero. The function returns zero in this case for 
//   compatibility with previous versions of Windows. If the function fails for
//   any other reason, the return value is –1. To get extended error 
//   information, call GetLastError.
INT_PTR M2MessageDialog(
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ HWND hWndParent,
	_In_opt_ LPCWSTR lpIconName,
	_In_ LPCWSTR lpTitle,
	_In_ LPCWSTR lpContent);

#endif // _M2_MESSAGE_DIALOG_
