/******************************************************************************
Project:M2-Team Common Library
Description: Implemention for base functions
File Name: m2base.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2BASE_
#define _M2BASE_

// Disabled Warnings
#if _MSC_VER >= 1200
#pragma warning(push)
// 'function' : unreferenced local function has been removed (level 4)
#pragma warning(disable:4505)
#endif

#include <string>
#include <Windows.h>

static std::wstring m2_base_utf8_to_utf16(const std::string& utf8_string)
{
	std::wstring utf16_string;

	int utf16_string_length = MultiByteToWideChar(
		CP_UTF8,
		0,
		utf8_string.data(),
		(int)utf8_string.size(),
		nullptr,
		0);
	if (utf16_string_length > 0)
	{
		utf16_string.resize(utf16_string_length);
		MultiByteToWideChar(
			CP_UTF8,
			0,
			utf8_string.data(),
			(int)utf8_string.size(),
			&utf16_string[0],
			utf16_string_length);
	}

	return utf16_string;
}

static std::string m2_base_utf16_to_utf8(const std::wstring& utf16_string)
{
	std::string utf8_string;

	int utf8_string_length = WideCharToMultiByte(
		CP_UTF8,
		0,
		utf16_string.data(),
		(int)utf16_string.size(),
		nullptr,
		0,
		nullptr,
		nullptr);
	if (utf8_string_length > 0)
	{
		utf8_string.resize(utf8_string_length);
		WideCharToMultiByte(
			CP_UTF8,
			0,
			utf16_string.data(),
			(int)utf16_string.size(),
			&utf8_string[0],
			utf8_string_length,
			nullptr,
			nullptr);
	}

	return utf8_string;
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif