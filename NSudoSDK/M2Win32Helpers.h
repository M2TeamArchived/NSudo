/******************************************************************************
Project: M2-Team Common Library
Description: Definition for the Win32 desktop helper functions.
File Name: M2Win32Helpers.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_WIN32_HELPERS_
#define _M2_WIN32_HELPERS_

#include <Windows.h>

// The resource info struct.
typedef struct _M2_RESOURCE_INFO
{
	DWORD Size;
	LPVOID Pointer;
} M2_RESOURCE_INFO, *PM2_RESOURCE_INFO;

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
	_In_ LPCWSTR lpName);

#endif // _M2_WIN32_HELPERS_
