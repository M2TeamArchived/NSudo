/******************************************************************************
Project: M2-Team Common Library
Description: Implementation for the basic helper functions.
File Name: M2BaseHelpers.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

#ifdef _M2_BASE_HELPERS_

#include <Windows.h>

#include "M2BaseHelpers.h"

#include <string>

// Write formatted data to a string. 
// Parameters:
//   Format: Format-control string.
//   ...: Optional arguments to be formatted.
// Return value:
//   Returns a formatted string if successful, or "N/A" otherwise.
std::wstring M2FormatString(
	_In_z_ _Printf_format_string_ wchar_t const* const Format,
	...)
{
	// Check the argument list.
	if (nullptr != Format)
	{
		va_list ArgList = nullptr;
		va_start(ArgList, Format);

		// Get the length of the format result.
		size_t nLength = _vscwprintf(Format, ArgList) + 1;

		// Allocate for the format result.
		std::wstring Buffer(nLength + 1, L'\0');

		// Format the string.
		int nWritten = _vsnwprintf_s(
			&Buffer[0],
			Buffer.size(),
			nLength,
			Format,
			ArgList);

		va_end(ArgList);

		if (nWritten > 0)
		{
			// If succeed, resize to fit and return result.
			Buffer.resize(nWritten);
			return Buffer;
		}
	}

	// If failed, return "N/A".
	return L"N/A";
}

// Retrieves the number of milliseconds that have elapsed since the system was
// started.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The number of milliseconds.
ULONGLONG M2GetTickCount()
{
	LARGE_INTEGER Frequency = { 0 }, PerformanceCount = { 0 };

	if (QueryPerformanceFrequency(&Frequency))
	{
		if (QueryPerformanceCounter(&PerformanceCount))
		{
			return (PerformanceCount.QuadPart * 1000 / Frequency.QuadPart);
		}
	}

	return GetTickCount64();
}

// Converts from the UTF-8 string to the UTF-16 string.
// Parameters:
//   UTF8String: The UTF-8 string you want to convert.
// Return value:
//   The return value is the UTF-16 string.
std::wstring M2MakeUTF16String(const std::string& UTF8String)
{
	std::wstring UTF16String;

	int UTF16StringLength = MultiByteToWideChar(
		CP_UTF8,
		0,
		UTF8String.data(),
		(int)UTF8String.size(),
		nullptr,
		0);
	if (UTF16StringLength > 0)
	{
		UTF16String.resize(UTF16StringLength);
		MultiByteToWideChar(
			CP_UTF8,
			0,
			UTF8String.data(),
			(int)UTF8String.size(),
			&UTF16String[0],
			UTF16StringLength);
	}

	return UTF16String;
}

// Converts from the UTF-16 string to the UTF-8 string.
// Parameters:
//   UTF16String: The UTF-16 string you want to convert.
// Return value:
//   The return value is the UTF-8 string.
std::string M2MakeUTF8String(const std::wstring& UTF16String)
{
	std::string UTF8String;

	int UTF8StringLength = WideCharToMultiByte(
		CP_UTF8,
		0,
		UTF16String.data(),
		(int)UTF16String.size(),
		nullptr,
		0,
		nullptr,
		nullptr);
	if (UTF8StringLength > 0)
	{
		UTF8String.resize(UTF8StringLength);
		WideCharToMultiByte(
			CP_UTF8,
			0,
			UTF16String.data(),
			(int)UTF16String.size(),
			&UTF8String[0],
			UTF8StringLength,
			nullptr,
			nullptr);
	}

	return UTF8String;
}

// Retrieves the calling thread's last-error code value. The last-error code is
// maintained on a per-thread basis. Multiple threads do not overwrite each 
// other's last-error code.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The return value is the calling thread's last-error code which is 
//   converted to an HRESULT value.
HRESULT M2GetLastError()
{
	return __HRESULT_FROM_WIN32(GetLastError());
}

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
HRESULT M2GetProcAddress(
	_Out_ FARPROC& lpProcAddress,
	_In_ HMODULE hModule,
	_In_ LPCSTR lpProcName)
{
	lpProcAddress = GetProcAddress(hModule, lpProcName);
	return (nullptr != lpProcAddress) ? S_OK : M2GetLastError();
}

#endif // _M2_BASE_HELPERS_
