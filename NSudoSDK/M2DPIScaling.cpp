/******************************************************************************
Project: M2-Team Common Library
Description: Implementation for the DPI scaling.
File Name: M2DPIScaling.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

#include <Windows.h>

#include "M2DPIScaling.h"

// Enables the Per-Monitor DPI Aware for the specified dialog using the 
// internal API from Windows.
// PS: You need to use this function in Windows 10 Threshold 1 or later.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The function will return a INT. If failed. returns -1.
INT M2EnablePerMonitorDialogScaling()
{
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