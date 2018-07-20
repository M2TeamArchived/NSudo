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
#include <map>

#include "M2BaseHelpers.h"

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

	std::map<std::string, std::wstring> m_StringTranslations;	
	std::map<std::wstring, std::wstring> m_ShortCutList;

	bool m_IsElevated = false;
	HANDLE m_OriginalCurrentProcessToken;

public:
	CNSudoResourceManagement();
	~CNSudoResourceManagement();

	const HINSTANCE& Instance = this->m_Instance;
	const std::wstring& ExePath = this->m_ExePath;
	const std::wstring& AppPath = this->m_AppPath;

	const std::map<std::wstring, std::wstring>& ShortCutList = 
		this->m_ShortCutList;

	const HANDLE& OriginalCurrentProcessToken = 
		this->m_OriginalCurrentProcessToken;
	const bool& IsElevated = this->m_IsElevated;

	const std::wstring GetVersionText();
	const std::wstring GetLogoText();

	std::wstring GetTranslation(
		_In_ std::string Key);
	std::wstring GetMessageString(
		_In_ NSUDO_MESSAGE MessageID);
	std::wstring GetUTF8WithBOMStringResources(
		_In_ UINT uID);

	std::vector<std::wstring> GetCommandParameters();

};

extern CNSudoResourceManagement g_ResourceManagement;

// 解析命令行
NSUDO_MESSAGE NSudoCommandLineParser(
	_In_ bool bElevated,
	_In_ bool bEnableContextMenuManagement,
	_In_ const std::vector<std::wstring>& args);


#endif // _NSUDO_RESOURCE_MANAGEMENT_
