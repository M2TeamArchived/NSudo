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


std::wstring NSudoGetTranslation(
	_In_ const char* Key);

class CNSudoContextMenuManagement
{
private:
	DWORD m_ConstructorError = ERROR_SUCCESS;
	std::wstring m_NSudoPath = M2GetWindowsDirectory() + L"\\NSudo.exe";
	M2::CHKey m_CommandStoreRoot;

	std::wstring m_NSudoPathWithQuotation = std::wstring(L"\"") + this->m_NSudoPath + L"\"";

	std::wstring m_ItemDescription[4] =
	{
		NSudoGetTranslation("ContextMenu.TI"),
		NSudoGetTranslation("ContextMenu.TI.EnableAllPrivileges"),
		NSudoGetTranslation("ContextMenu.System"),
		NSudoGetTranslation("ContextMenu.System.EnableAllPrivileges")
	};

	const wchar_t* m_ItemCommandParameters[4] =
	{ 
		L" -U:T \"\"%1\"\"" ,
		L" -U:T -P:E \"\"%1\"\"",
		L" -U:S \"\"%1\"\"",
		L" -U:S -P:E \"\"%1\"\""
	};

	struct CommandStoreItemsType
	{
		LPCWSTR ItemName;
		bool HasLUAShield;
	} m_CommandStoreItems[4] =
	{
		{
			L"NSudo.RunAs.TrustedInstaller",
			true
		},{
			L"NSudo.RunAs.TrustedInstaller.EnableAllPrivileges",
			true
		},{
			L"NSudo.RunAs.System",
			true
		},{
			L"NSudo.RunAs.System.EnableAllPrivileges",
			true
		}
	};
	const size_t m_CommandStoreItemsSize =
		sizeof(this->m_CommandStoreItems) / sizeof(*this->m_CommandStoreItems);

public:
	CNSudoContextMenuManagement();

	DWORD Install();
	DWORD Uninstall();
};

#endif // _NSUDO_CONTEXT_MENU_MANAGEMENT_
