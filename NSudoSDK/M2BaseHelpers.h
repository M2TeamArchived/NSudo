/******************************************************************************
Project: M2-Team Common Library
Description: Definition for the basic helper functions.
File Name: M2BaseHelpers.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_BASE_HELPERS_
#define _M2_BASE_HELPERS_

#include <Windows.h>

#include <string>

// Write formatted data to a string. 
// Parameters:
//   Format: Format-control string.
//   ...: Optional arguments to be formatted.
// Return value:
//   Returns a formatted string if successful, or "N/A" otherwise.
std::wstring M2FormatString(
	_In_z_ _Printf_format_string_ wchar_t const* const Format,
	...);

// Retrieves the number of milliseconds that have elapsed since the system was
// started.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The number of milliseconds.
ULONGLONG M2GetTickCount();

// Searches a path for a file name.
// Parameters:
//   Path: A pointer to a null-terminated string of maximum length MAX_PATH 
//   that contains the path to search.
// Return value:
//   Returns a pointer to the address of the string if successful, or a pointer
//   to the beginning of the path otherwise.
template<typename CharType>
CharType M2PathFindFileName(CharType Path)
{
	CharType FileName = Path;

	for (size_t i = 0; i < MAX_PATH; ++i)
	{
		if (!(Path && *Path))
			break;

		if (L'\\' == *Path || L'/' == *Path)
			FileName = Path + 1;

		++Path;
	}

	return FileName;
}

// Converts from the UTF-8 string to the UTF-16 string.
// Parameters:
//   UTF8String: The UTF-8 string you want to convert.
// Return value:
//   The return value is the UTF-16 string.
std::wstring M2MakeUTF16String(const std::string& UTF8String);

// Converts from the UTF-16 string to the UTF-8 string.
// Parameters:
//   UTF16String: The UTF-16 string you want to convert.
// Return value:
//   The return value is the UTF-8 string.
std::string M2MakeUTF8String(const std::wstring& UTF16String);

// Retrieves the calling thread's last-error code value. The last-error code is
// maintained on a per-thread basis. Multiple threads do not overwrite each 
// other's last-error code.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The return value is the calling thread's last-error code which is 
//   converted to an HRESULT value.
HRESULT M2GetLastError();

// Retrieves the address of an exported function or variable from the specified
// dynamic-link library (DLL).
// Parameters:
//   lpProcAddress: The address of the exported function or variable
//   hModule: A handle to the DLL module that contains the function or 
//   variable. The LoadLibrary, LoadLibraryEx, LoadPackagedLibrary, or 
//   GetModuleHandle function returns this handle. This function does not 
//   retrieve addresses from modules that were loaded using the 
//   LOAD_LIBRARY_AS_DATAFILE flag.For more information, see LoadLibraryEx.
//   lpProcName: The function or variable name, or the function's ordinal 
//   value. If this parameter is an ordinal value, it must be in the low-order
//   word; the high-order word must be zero.
// Return value:
//   The function will return HRESULT. If the function succeeds, the return 
//   value is S_OK.
template<typename ProcedureType>
inline HRESULT M2GetProcAddress(
	_Out_ ProcedureType& lpProcAddress,
	_In_ HMODULE hModule,
	_In_ LPCSTR lpProcName)
{
	HRESULT M2GetProcAddress(
		_Out_ FARPROC& lpProcAddress,
		_In_ HMODULE hModule,
		_In_ LPCSTR lpProcName);

	return M2GetProcAddress(
		reinterpret_cast<FARPROC&>(lpProcAddress), hModule, lpProcName);
}

#endif // _M2_BASE_HELPERS_
