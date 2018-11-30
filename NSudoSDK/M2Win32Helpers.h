/******************************************************************************
Project: M2-Team Common Library
Description: Definition for the Win32 desktop helper functions.
File Name: M2Win32Helpers.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_WIN32_HELPERS_
#define _M2_WIN32_HELPERS_

#include "M2BaseHelpers.h"

/// <summary>
/// The resource info struct.
/// </summary>
typedef struct _M2_RESOURCE_INFO
{
	DWORD Size;
	LPVOID Pointer;
} M2_RESOURCE_INFO, *PM2_RESOURCE_INFO;

/// <summary>
/// Obtain the best matching resource with the specified type and name in the
/// specified module.
/// </summary>
/// <param name="lpResourceInfo">
/// The resource info which contains the pointer and size.
/// </param>
/// <param name="hModule">
/// A handle to the module whose portable executable file or an accompanying MUI
/// file contains the resource. If this parameter is NULL, the function searches
/// the module used to create the current process.
/// </param>
/// <param name="lpType">
/// The resource type. Alternately, rather than a pointer, this parameter can be
/// MAKEINTRESOURCE(ID), where ID is the integer identifier of the given
/// resource type.
/// </param>
/// <param name="lpName">
/// The name of the resource. Alternately, rather than a pointer, this parameter
/// can be MAKEINTRESOURCE(ID), where ID is the integer identifier of the
/// resource.
/// </param>
/// <returns>
/// The function will return HRESULT.
/// </returns>
HRESULT M2LoadResource(
	_Out_ PM2_RESOURCE_INFO lpResourceInfo,
	_In_opt_ HMODULE hModule,
	_In_ LPCWSTR lpType,
	_In_ LPCWSTR lpName);
   
/// <summary>
/// Retrieves file system attributes for a specified file or directory.
/// </summary>
/// <param name="hFile">
/// A handle to the file that contains the information to be retrieved. This
/// handle should not be a pipe handle.
/// </param>
/// <returns>
/// If the function succeeds, the return value contains the attributes of the
/// specified file or directory. For a list of attribute values and their
/// descriptions, see File Attribute Constants. If the function fails, the
/// return value is INVALID_FILE_ATTRIBUTES.To get extended error information,
/// call GetLastError.
/// </returns>
DWORD M2GetFileAttributes(
	_In_ HANDLE hFile);
  
/// <summary>
/// Sets the attributes for a file or directory.
/// </summary>
/// <param name="hFile">
/// A handle to the file for which to change information. This handle must be
/// opened with the appropriate permissions for the requested change. This
/// handle should not be a pipe handle.
/// </param>
/// <param name="dwFileAttributes">
/// The file attributes to set for the file. This parameter can be one or more
/// values, combined using the bitwise - OR operator. However, all other values
/// override FILE_ATTRIBUTE_NORMAL. For more information, see the
/// SetFileAttributes function.
/// </param>
/// <returns>
/// The function will return HRESULT. If the function succeeds, the return value
/// is S_OK.
/// </returns>
HRESULT M2SetFileAttributes(
	_In_ HANDLE hFile,
	_In_ DWORD dwFileAttributes);
 
/// <summary>
/// Deletes an existing file.
/// </summary>
/// <param name="lpFileName">
/// The name of the file to be deleted. In the ANSI version of this function,
/// the name is limited to MAX_PATH characters.To extend this limit to 32,767
/// wide characters, call the Unicode version of the function and prepend "\\?\"
/// to the path. For more information, see Naming a File.
/// </param>
/// <param name="bForceDeleteReadOnlyFile">
/// If this parameter is true, the function removes the read-only attribute
/// first.
/// </param>
/// <returns>
/// The function will return HRESULT. If the function succeeds, the return value
/// is S_OK.
/// </returns>
HRESULT M2DeleteFile(
	_In_ LPCWSTR lpFileName,
	_In_ bool bForceDeleteReadOnlyFile);
 
/// <summary>
/// Retrieves the amount of space that is allocated for the file.
/// </summary>
/// <param name="lpFileName">
/// The name of the file. In the ANSI version of this function, the name is
/// limited to MAX_PATH characters.To extend this limit to 32,767 wide
/// characters, call the Unicode version of the function and prepend "\\?\" to
/// the path. For more information, see Naming a File.
/// </param>
/// <param name="lpAllocationSize">
/// A pointer to a ULONGLONG value that receives the amount of space that is
/// allocated for the file, in bytes.
/// </param>
/// <returns>
/// The function will return HRESULT. If the function succeeds, the return value
/// is S_OK.
/// </returns>
HRESULT M2GetFileAllocationSize(
	_In_ LPCWSTR lpFileName,
	_Out_ PULONGLONG lpAllocationSize);
 
/// <summary>
/// Retrieves the size of the specified file.
/// </summary>
/// <param name="lpFileName">
/// The name of the file. In the ANSI version of this function, the name is
/// limited to MAX_PATH characters.To extend this limit to 32,767 wide
/// characters, call the Unicode version of the function and prepend "\\?\" to
/// the path. For more information, see Naming a File.
/// </param>
/// <param name="lpFileSize">
/// A pointer to a ULONGLONG value that receives the file size, in bytes.
/// </param>
/// <returns>
/// The function will return HRESULT. If the function succeeds, the return value
/// is S_OK.
/// </returns>
HRESULT M2GetFileSize(
	_In_ LPCWSTR lpFileName,
	_Out_ PULONGLONG lpFileSize);

namespace M2
{
	/// <summary>
	/// The handle definer for SC_HANDLE object.
	/// </summary>
#pragma region CServiceHandle

	struct CServiceHandleDefiner
	{
		static inline SC_HANDLE GetInvalidValue()
		{
			return nullptr;
		}

		static inline void Close(SC_HANDLE Object)
		{
			CloseServiceHandle(Object);
		}
	};

	typedef CObject<SC_HANDLE, CServiceHandleDefiner> CServiceHandle;

#pragma endregion
 
	/// <summary>
	/// The handle definer for PSID object.
	/// </summary>
#pragma region CSID

	struct CSIDDefiner
	{
		static inline PSID GetInvalidValue()
		{
			return nullptr;
		}

		static inline void Close(PSID Object)
		{
			FreeSid(Object);
		}
	};

	typedef CObject<PSID, CSIDDefiner> CSID;

#pragma endregion
 
	/// <summary>
	/// The handle definer for memory block allocated via WTS API.
	/// </summary>
#pragma region CWTSMemory

	template<typename TMemoryBlock>
	struct CWTSMemoryDefiner
	{
		static inline TMemoryBlock GetInvalidValue()
		{
			return nullptr;
		}

		static inline void Close(TMemoryBlock Object)
		{
			WTSFreeMemory(Object);
		}
	};

	template<typename TMemoryBlock>
	class CWTSMemory : public CObject<TMemoryBlock, CWTSMemoryDefiner<TMemoryBlock>>
	{

	};

#pragma endregion

	/// <summary>
	/// The handle definer for HKEY object.
	/// </summary>
#pragma region CHKey

	struct CHKeyDefiner
	{
		static inline HKEY GetInvalidValue()
		{
			return nullptr;
		}

		static inline void Close(HKEY Object)
		{
			RegCloseKey(Object);
		}
	};

	typedef CObject<HKEY, CHKeyDefiner> CHKey;

#pragma endregion

}
 
/// <summary>
/// Retrieves the path of the shared Windows directory on a multi-user system.
/// </summary>
/// <param name="WindowsFolderPath">
/// The string of the path of the shared Windows directory on a multi-user
/// system.
/// </param>
/// <returns>
/// The function will return HRESULT. If the function succeeds, the return value
/// is S_OK.
/// </returns>
HRESULT M2GetWindowsDirectory(
	std::wstring& WindowsFolderPath);

#endif // _M2_WIN32_HELPERS_
