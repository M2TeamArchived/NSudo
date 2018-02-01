/******************************************************************************
Project: NSudoSDK
Description: Definition for the NSudo Context Menu Management.
File Name: NSudoContextMenuManagement.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _NSUDO_CONTEXT_MENU_MANAGEMENT_
#define _NSUDO_CONTEXT_MENU_MANAGEMENT_

#include <Windows.h>
#include "NSudoAPI.h"

#include "ThirdParty\json.hpp"

std::wstring NSudoGetTranslation(
	_In_ const char* Key);

class CNSudoContextMenuManagement
{
private:
	DWORD m_ConstructorError = ERROR_SUCCESS;
	std::wstring m_NSudoPath = M2GetWindowsDirectory() + L"\\NSudo.exe";
	M2::CHKey m_CommandStoreRoot;
	nlohmann::json m_ContextMenuItems;

public:
	CNSudoContextMenuManagement();

	DWORD Install();
	DWORD Uninstall();
};

#endif // _NSUDO_CONTEXT_MENU_MANAGEMENT_
