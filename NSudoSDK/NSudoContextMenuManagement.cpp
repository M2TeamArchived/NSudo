/******************************************************************************
Project: NSudoSDK
Description: Implementation for the NSudo Context Menu Management.
File Name: NSudoContextMenuManagement.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

#include <Windows.h>

#include <string>

#include "NSudoAPI.h"

#include "M2BaseHelpers.h"

#include "NSudoContextMenuManagement.h"
#include "NSudoContextMenuManagementResource.h"

#include "M2ResourceManagement.h"
#include "NSudoResourceManagement.h"

#include "ThirdParty\json.hpp"

CNSudoContextMenuManagement::CNSudoContextMenuManagement()
{
	this->m_ConstructorError = RegOpenKeyExW(
		HKEY_LOCAL_MACHINE,
		L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell",
		0,
		KEY_ALL_ACCESS | KEY_WOW64_64KEY,
		&this->m_CommandStoreRoot);
	if (ERROR_SUCCESS != this->m_ConstructorError)
		return;

	nlohmann::json ContextMenuJSON = M2LoadJsonFromResource(
		GetModuleHandleW(nullptr),
		L"Config",
		MAKEINTRESOURCEW(IDR_CONFIG_CONTEXT_MENU))["ContextMenu"];

	for (nlohmann::json& Item : ContextMenuJSON)
	{
		NSUDO_CONTEXT_MENU_ITEM ContextMenuItem;

		ContextMenuItem.ItemName = 
			M2MakeUTF16String(Item["ItemName"].get<std::string>());

		ContextMenuItem.ItemDescription = g_ResourceManagement.GetTranslation(
			Item["ItemDescriptionID"].get<std::string>().c_str());

		ContextMenuItem.ItemCommandParameters = M2MakeUTF16String(
			Item["ItemCommandParameters"].get<std::string>());

		ContextMenuItem.HasLUAShield = Item["HasLUAShield"].get<bool>();

		this->m_ContextMenuItems.push_back(ContextMenuItem);
	}
	
}

DWORD CNSudoContextMenuManagement::Install()
{
	if (ERROR_SUCCESS != this->m_ConstructorError)
		return this->m_ConstructorError;

	CopyFileW(M2GetCurrentModulePath().c_str(), this->m_NSudoPath.c_str(), FALSE);

	DWORD dwError = ERROR_SUCCESS;
	
	std::wstring NSudoPathWithQuotation = 
		std::wstring(L"\"") + this->m_NSudoPath + L"\"";

	M2::CHKey hNSudoItem;
	std::wstring SubCommands;

	for (NSUDO_CONTEXT_MENU_ITEM Item : this->m_ContextMenuItems)
	{
		std::wstring GeneratedItemCommand =
			NSudoPathWithQuotation +
			L" " + Item.ItemCommandParameters + L" " +
			L"\"\"%1\"\"";

		dwError = CreateCommandStoreItem(
			this->m_CommandStoreRoot,
			Item.ItemName.c_str(),
			Item.ItemDescription.c_str(),
			GeneratedItemCommand.c_str(),
			Item.HasLUAShield);
		if (ERROR_SUCCESS != dwError)
			return dwError;

		SubCommands += Item.ItemName + L";";
	}

	dwError = M2RegCreateKey(
		HKEY_CLASSES_ROOT,
		L"*\\shell\\NSudo",
		KEY_ALL_ACCESS | KEY_WOW64_64KEY,
		&hNSudoItem);
	if (ERROR_SUCCESS != dwError)
		return dwError;

	struct
	{
		LPCWSTR lpValueName;
		LPCWSTR lpValueData;
	} ValueList[] =
	{
		{
			L"SubCommands",
			SubCommands.c_str()
		},{
			L"MUIVerb",
			L"NSudo"
		},{
			L"Icon",
			NSudoPathWithQuotation.c_str()
		},{
			L"Position",
			L"1"
		}
	};

	for (size_t i = 0; i < sizeof(ValueList) / sizeof(*ValueList); ++i)
	{
		dwError = M2RegSetStringValue(
			hNSudoItem,
			ValueList[i].lpValueName,
			ValueList[i].lpValueData);
		if (ERROR_SUCCESS != dwError)
			return dwError;

	}

	return dwError;
}

DWORD CNSudoContextMenuManagement::Uninstall()
{
	if (ERROR_SUCCESS != this->m_ConstructorError)
		return this->m_ConstructorError;

	// 首先去除只读，然后删除文件，如果失败，则要求系统重启后删除
	DWORD AttributesBackup = GetFileAttributesW(this->m_NSudoPath.c_str());
	SetFileAttributesW(
		this->m_NSudoPath.c_str(), 
		AttributesBackup & (-1 ^ FILE_ATTRIBUTE_READONLY));
	if (!DeleteFileW(this->m_NSudoPath.c_str()))
	{
		MoveFileExW(
			this->m_NSudoPath.c_str(),
			nullptr,
			MOVEFILE_DELAY_UNTIL_REBOOT);
	}

	DWORD dwError = ERROR_SUCCESS;

	for (NSUDO_CONTEXT_MENU_ITEM Item : this->m_ContextMenuItems)
	{
		dwError = RegDeleteTreeW(
			this->m_CommandStoreRoot,
			Item.ItemName.c_str());
		if (ERROR_SUCCESS != dwError)
			break;
	}

	dwError = RegDeleteTreeW(
		HKEY_CLASSES_ROOT,
		L"*\\shell\\NSudo");

	return dwError;
}
