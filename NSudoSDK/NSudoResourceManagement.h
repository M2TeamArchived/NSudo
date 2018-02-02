/******************************************************************************
Project: NSudoSDK
Description: Definition for the Resource Management.
File Name: NSudoResourceManagement.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _NSUDO_RESOURCE_MANAGEMENT_
#define _NSUDO_RESOURCE_MANAGEMENT_

#include <Windows.h>
#include <string>
#include <vector>

#include "ThirdParty\json.hpp"

#include "M2Object.h"

#include "NSudoVersion.h"
#include "NSudoResourceManagementResource.h"

// The NSudo message enum.
enum NSUDO_MESSAGE
{
	SUCCESS,
	PRIVILEGE_NOT_HELD,
	INVALID_COMMAND_PARAMETER,
	INVALID_TEXTBOX_PARAMETER,
	CREATE_PROCESS_FAILED,
	NEED_TO_SHOW_COMMAND_LINE_HELP
};

class CNSudoResourceManagement
{
private:
	HINSTANCE m_Instance = nullptr;
	std::wstring m_ExePath;
	std::wstring m_AppPath;

	nlohmann::json m_StringTranslations;

	nlohmann::json m_Config;
	nlohmann::json m_ShortCutListV2;

	bool m_IsElevated = false;
	HANDLE m_OriginalCurrentProcessToken;

public:
	CNSudoResourceManagement();
	~CNSudoResourceManagement();

	const HINSTANCE& Instance = this->m_Instance;
	const std::wstring& ExePath = this->m_ExePath;
	const std::wstring& AppPath = this->m_AppPath;

	const nlohmann::json& Config = this->m_Config;
	const nlohmann::json& ShortCutListV2 = this->m_ShortCutListV2;

	const HANDLE& OriginalCurrentProcessToken = 
		this->m_OriginalCurrentProcessToken;
	const bool& IsElevated = this->m_IsElevated;

	const std::wstring GetVersionText();
	const std::wstring GetLogoText();

	std::wstring GetTranslation(
		_In_ const char* Key);
	std::wstring GetMessageString(
		_In_ NSUDO_MESSAGE MessageID);
	std::wstring GetUTF8WithBOMStringResources(
		_In_ UINT uID);

	std::vector<std::wstring> GetCommandParameters();

};

extern CNSudoResourceManagement g_ResourceManagement;

// Ω‚Œˆ√¸¡Ó––
NSUDO_MESSAGE NSudoCommandLineParser(
	_In_ bool bElevated,
	_In_ bool bEnableContextMenuManagement,
	_In_ const std::vector<std::wstring>& args);


#endif // _NSUDO_RESOURCE_MANAGEMENT_
