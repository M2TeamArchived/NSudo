/******************************************************************************
Project: M2-Team Common Library
Description: Implementation for the basic helper functions.
File Name: M2BaseHelpers.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

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

		// Get the length of rhe format result.
		size_t nLength = _vscwprintf(Format, ArgList) + 1;

		// Allocate for the format result.
		std::wstring Buffer(nLength + 1, L'\0');

		// Format the string
		int nWritten = _vsnwprintf_s(
			&Buffer[0],
			Buffer.size(),
			nLength,
			Format,
			ArgList);
		if (nWritten > 0)
		{
			// If succeed, resize to fit and return result.
			Buffer.resize(nWritten);
			return Buffer;
		}

		va_end(ArgList);
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