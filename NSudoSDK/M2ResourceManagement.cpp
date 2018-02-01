/******************************************************************************
Project: M2-Team Common Library
Description: Implementation for the Resource Management.
File Name: M2ResourceManagement.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

#include <Windows.h>
#include "ThirdParty\json.hpp"

#include "M2ResourceManagement.h"

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

// Obtain the json object from the best matching resource with the specified 
// type and name in the specified module.
// Parameters:
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
//   The function will return the json object.
nlohmann::json M2LoadJsonFromResource(
	_In_opt_ HMODULE hModule,
	_In_ LPCWSTR lpType,
	_In_ LPCWSTR lpName)
{
	nlohmann::json result;

	M2_RESOURCE_INFO ResourceInfo = { 0 };
	if (SUCCEEDED(M2LoadResource(&ResourceInfo, hModule, lpType, lpName)))
	{
		std::string RawString(
			reinterpret_cast<const char*>(ResourceInfo.Pointer),
			ResourceInfo.Size);
		result = nlohmann::json::parse(RawString);
	}

	return result;
}
