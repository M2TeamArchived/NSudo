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

// Retrieves file system attributes for a specified file or directory.
// Parameters:
//   hFile: A handle to the file that contains the information to be retrieved.
//   This handle should not be a pipe handle.
// Return value:
//   If the function succeeds, the return value contains the attributes of the 
//   specified file or directory. For a list of attribute values and their 
//   descriptions, see File Attribute Constants. If the function fails, the 
//   return value is INVALID_FILE_ATTRIBUTES.To get extended error information,
//   call GetLastError.
DWORD M2GetFileAttributes(
	_In_ HANDLE hFile)
{
	FILE_BASIC_INFO BasicInfo;

	BOOL ret = GetFileInformationByHandleEx(
		hFile,
		FileBasicInfo,
		&BasicInfo,
		sizeof(FILE_BASIC_INFO));

	return ret ? BasicInfo.FileAttributes : INVALID_FILE_ATTRIBUTES;
}

// Sets the attributes for a file or directory.
// Parameters:
//   hFile: A handle to the file for which to change information. This handle 
//   must be opened with the appropriate permissions for the requested change. 
//   For more information, see the Remarks and Example Code sections. This 
//   handle should not be a pipe handle.
//   dwFileAttributes: The file attributes to set for the file. This parameter
//   can be one or more values, combined using the bitwise - OR operator. 
//   However, all other values override FILE_ATTRIBUTE_NORMAL. For more 
//   information, see the SetFileAttributes function.
// Return value:
//   The function will return HRESULT. If the function succeeds, the return 
//   value is S_OK.
HRESULT M2SetFileAttributes(
	_In_ HANDLE hFile,
	_In_ DWORD dwFileAttributes)
{
	FILE_BASIC_INFO BasicInfo = { 0 };
	BasicInfo.FileAttributes =
		dwFileAttributes & (
			FILE_SHARE_READ |
			FILE_SHARE_WRITE |
			FILE_SHARE_DELETE |
			FILE_ATTRIBUTE_ARCHIVE |
			FILE_ATTRIBUTE_TEMPORARY |
			FILE_ATTRIBUTE_OFFLINE |
			FILE_ATTRIBUTE_NOT_CONTENT_INDEXED |
			FILE_ATTRIBUTE_NO_SCRUB_DATA) |
		FILE_ATTRIBUTE_NORMAL;

	BOOL ret = SetFileInformationByHandle(
		hFile,
		FileBasicInfo,
		&BasicInfo,
		sizeof(FILE_BASIC_INFO));

	return ret ? S_OK : M2GetLastError();
}

// Deletes an existing file.
// Parameters:
//   lpFileName: The name of the file to be deleted. In the ANSI version of 
//   this function, the name is limited to MAX_PATH characters.To extend this
//   limit to 32,767 wide characters, call the Unicode version of the function
//   and prepend "\\?\" to the path. For more information, see Naming a File.
//   bForceDeleteReadOnlyFile: If this parameter is true, the function removes 
//   the read-only attribute first. 
// Return value:
//   The function will return HRESULT. If the function succeeds, the return 
//   value is S_OK.
HRESULT M2DeleteFile(
	_In_ LPCWSTR lpFileName,
	_In_ bool bForceDeleteReadOnlyFile)
{
	HRESULT hr = S_OK;

	// Open the file.
	HANDLE hFile = CreateFileW(
		lpFileName,
		SYNCHRONIZE | DELETE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
		nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		hr = M2GetLastError();
		goto Cleanup;
	}

	FILE_DISPOSITION_INFO DispostionInfo;
	DispostionInfo.DeleteFile = TRUE;

	DWORD OldAttribute = 0;

	if (bForceDeleteReadOnlyFile)
	{
		// 保存旧属性值
		OldAttribute = M2GetFileAttributes(hFile);

		// 去除只读
		M2SetFileAttributes(
			hFile,
			OldAttribute & (-1 ^ FILE_ATTRIBUTE_READONLY));
	}

	// Delete the file.
	if (!SetFileInformationByHandle(
		hFile,
		FileDispositionInfo,
		&DispostionInfo,
		sizeof(FILE_DISPOSITION_INFO)))
	{
		hr = M2GetLastError();
	}

	// 如果删除未成功，则恢复原属性
	if (bForceDeleteReadOnlyFile & !SUCCEEDED(hr))
		M2SetFileAttributes(hFile, OldAttribute);

Cleanup:
	CloseHandle(hFile);

	return hr;
}

// Retrieves the amount of space that is allocated for the file.
// Parameters:
//   lpFileName: The name of the file. In the ANSI version of this function, 
//   the name is limited to MAX_PATH characters.To extend this limit to 32,767
//   wide characters, call the Unicode version of the function and prepend 
//   "\\?\" to the path. For more information, see Naming a File.
//   lpAllocationSize: A pointer to a ULONGLONG value that receives the amount 
//   of space that is allocated for the file, in bytes.
// Return value:
//   The function will return HRESULT. If the function succeeds, the return 
//   value is S_OK.
HRESULT M2GetFileAllocationSize(
	_In_ LPCWSTR lpFileName,
	_Out_ PULONGLONG lpAllocationSize)
{
	*lpAllocationSize = 0;

	HRESULT hr = S_OK;

	// Open the file.
	HANDLE hFile = CreateFileW(
		lpFileName,
		GENERIC_READ | SYNCHRONIZE,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
		nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		hr = M2GetLastError();
		goto Cleanup;
	}

	FILE_STANDARD_INFO StandardInfo;

	if (!GetFileInformationByHandleEx(
		hFile,
		FileStandardInfo,
		&StandardInfo,
		sizeof(FILE_STANDARD_INFO)))
	{
		hr = M2GetLastError();
		goto Cleanup;
	}

	*lpAllocationSize = static_cast<ULONGLONG>(
		StandardInfo.AllocationSize.QuadPart);

Cleanup:
	CloseHandle(hFile);

	return hr;
}

// Retrieves the size of the specified file.
// Parameters:
//   lpFileName: The name of the file. In the ANSI version of this function, 
//   the name is limited to MAX_PATH characters.To extend this limit to 32,767
//   wide characters, call the Unicode version of the function and prepend 
//   "\\?\" to the path. For more information, see Naming a File.
//   lpFileSize: A pointer to a ULONGLONG value that receives the file size, in
//   bytes.
// Return value:
//   The function will return HRESULT. If the function succeeds, the return 
//   value is S_OK.
HRESULT M2GetFileSize(
	_In_ LPCWSTR lpFileName,
	_Out_ PULONGLONG lpFileSize)
{
	*lpFileSize = 0;

	HRESULT hr = S_OK;

	// Open the file.
	HANDLE hFile = CreateFileW(
		lpFileName,
		GENERIC_READ | SYNCHRONIZE,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
		nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		hr = M2GetLastError();
		goto Cleanup;
	}

	FILE_STANDARD_INFO StandardInfo;

	if (!GetFileInformationByHandleEx(
		hFile,
		FileStandardInfo,
		&StandardInfo,
		sizeof(FILE_STANDARD_INFO)))
	{
		hr = M2GetLastError();
		goto Cleanup;
	}

	*lpFileSize = static_cast<ULONGLONG>(
		StandardInfo.EndOfFile.QuadPart);

Cleanup:
	CloseHandle(hFile);

	return hr;
}
