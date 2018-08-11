/******************************************************************************
Project: M2-Team Common Library
Description: Implementation for the Win32 desktop helper functions.
File Name: M2Win32Helpers.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

#include <Windows.h>
#include <VersionHelpers.h>

#include "M2Win32Helpers.h"
#include "M2MessageDialogResource.h"

// Obtain the best matching resource with the specified type and name in the 
// specified module.
// Parameters:
//   lpResourceInfo: The resource info which contains the pointer and size.
//   hModule: A handle to the module whose portable executable file or an 
//   accompanying MUI file contains the resource. If this parameter is NULL, 
//   the function searches the module used to create the current process.
//   lpType: The resource type. Alternately, rather than a pointer, this 
//   parameter can be MAKEINTRESOURCE(ID), where ID is the integer identifier 
//   of the given resource type. For standard resource types, see Resource 
//   Types. For more information, see the Remarks section below.
//   lpName: The name of the resource. Alternately, rather than a pointer, this
//   parameter can be MAKEINTRESOURCE(ID), where ID is the integer identifier 
//   of the resource. For more information, see the Remarks section below.
// Return value:
//   The function will return HRESULT.
HRESULT M2LoadResource(
	_Out_ PM2_RESOURCE_INFO lpResourceInfo,
	_In_opt_ HMODULE hModule,
	_In_ LPCWSTR lpType,
	_In_ LPCWSTR lpName)
{
	if (nullptr == lpResourceInfo)
		return E_INVALIDARG;

	SetLastError(ERROR_SUCCESS);

	lpResourceInfo->Size = 0;
	lpResourceInfo->Pointer = nullptr;

	HRSRC ResourceFind = FindResourceExW(
		hModule, lpType, lpName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
	if (nullptr != ResourceFind)
	{
		lpResourceInfo->Size = SizeofResource(hModule, ResourceFind);

		HGLOBAL ResourceLoad = LoadResource(hModule, ResourceFind);
		if (nullptr != ResourceLoad)
		{
			lpResourceInfo->Pointer = LockResource(ResourceLoad);
		}
	}

	return __HRESULT_FROM_WIN32(GetLastError());
}

// Enables the Per-Monitor DPI Aware for the specified dialog using the 
// internal API from Windows.
// PS: You need to use this function in Windows 10 Threshold 1 or later.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The function will return a INT. If failed. returns -1.
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

// The parameter struct of the message dialog.
struct DIALOG_BOX_PARAM
{
	HINSTANCE hInstance;
	LPCWSTR lpIconName;
	LPCWSTR lpTitle;
	LPCWSTR lpContent;
};

// The callback function used of the message dialog.
// Parameters:
//   hwndDlg: A handle to the message dialog. 
//   uMsg: The message. 
//   wParam: Additional message-specific information. 
//   lParam: Additional message-specific information. 
// Return value:
//   Typically, the dialog box procedure should return TRUE if it processed the
//   message, and FALSE if it did not. If the dialog box procedure returns 
//   FALSE, the dialog manager performs the default dialog operation in 
//   response to the message.
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
