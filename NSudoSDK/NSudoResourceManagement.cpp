/******************************************************************************
Project: NSudoSDK
Description: Implementation for the Resource Management.
File Name: NSudoResourceManagement.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

#include <Windows.h>
#include <fstream>

#include "M2Win32Helpers.h"

#include "NSudoAPI.h"

#include "M2BaseHelpers.h"

#include "NSudoResourceManagement.h"

#include "ThirdParty\rapidjson\document.h"
#include "ThirdParty\rapidjson\istreamwrapper.h"
#include "ThirdParty\rapidjson\encodedstream.h"

CNSudoResourceManagement g_ResourceManagement;

CNSudoResourceManagement::CNSudoResourceManagement()
{
	this->m_Instance = GetModuleHandleW(nullptr);

	this->m_ExePath = M2GetCurrentProcessModulePath();

	this->m_AppPath = this->m_ExePath;
	wcsrchr(&this->m_AppPath[0], L'\\')[0] = L'\0';
	this->m_AppPath.resize(wcslen(this->m_AppPath.c_str()));

	rapidjson::Document StringTranslationsJSON;

	M2_RESOURCE_INFO ResourceInfo = { 0 };
	if (SUCCEEDED(M2LoadResource(
		&ResourceInfo, 
		GetModuleHandleW(nullptr), 
		L"String",
		MAKEINTRESOURCEW(IDR_String_Translations))))
	{	
		StringTranslationsJSON.Parse(
			reinterpret_cast<const char*>(ResourceInfo.Pointer),
			ResourceInfo.Size);

		for (auto& Item : StringTranslationsJSON["Translations"].GetObject())
		{
			std::string Key = std::string(
				Item.name.GetString(), 
				Item.name.GetStringLength());
			std::string Value = std::string(
				Item.value.GetString(), 
				Item.value.GetStringLength());
			
			this->m_StringTranslations.insert(std::make_pair(
				Key, M2MakeUTF16String(Value)));
		}
	}

	try
	{
		std::ifstream FileStream(this->AppPath + L"\\NSudo.json");
		if (FileStream.is_open())
		{
			using rapidjson::EncodedInputStream;
			using rapidjson::IStreamWrapper;
			using rapidjson::UTF8;

			IStreamWrapper ISW(FileStream);
			EncodedInputStream<UTF8<>, IStreamWrapper> EIS(ISW);

			rapidjson::Document ConfigJSON;
			ConfigJSON.ParseStream(EIS);

			for (auto& Item : ConfigJSON["ShortCutList_V2"].GetObject())
			{
				std::string Key = std::string(
					Item.name.GetString(),
					Item.name.GetStringLength());
				std::string Value = std::string(
					Item.value.GetString(),
					Item.value.GetStringLength());

				this->m_ShortCutList.insert(std::make_pair(
					M2MakeUTF16String(Key),
					M2MakeUTF16String(Value)));
			}
		}
	}
	catch (const std::exception&)
	{

	}

	M2::CHandle CurrentProcessToken;

	if (OpenProcessToken(
		GetCurrentProcess(),
		MAXIMUM_ALLOWED, 
		&CurrentProcessToken))
	{
		if (DuplicateTokenEx(
			CurrentProcessToken,
			MAXIMUM_ALLOWED,
			nullptr,
			SecurityIdentification,
			TokenPrimary,
			&this->m_OriginalCurrentProcessToken))
		{
			this->m_IsElevated = NSudoSetTokenPrivilege(
				CurrentProcessToken,
				SeDebugPrivilege, 
				true);
		}	
	}	
}

CNSudoResourceManagement::~CNSudoResourceManagement()
{
	if (INVALID_HANDLE_VALUE != this->m_OriginalCurrentProcessToken)
	{
		CloseHandle(this->m_OriginalCurrentProcessToken);
	}
}

const std::wstring CNSudoResourceManagement::GetVersionText()
{
	return 
		L"M2-Team NSudo " NSUDO_VERSION_STRING;
}

const std::wstring CNSudoResourceManagement::GetLogoText()
{
	return 
		L"M2-Team NSudo " NSUDO_VERSION_STRING L"\r\n"
		L"© M2-Team. All rights reserved.\r\n"
		L"\r\n";
}

std::wstring CNSudoResourceManagement::GetTranslation(
	_In_ std::string Key)
{
	return this->m_StringTranslations[Key];
}

const char* NSudoMessageTranslationID[] =
{
	"Message.Success",
	"Message.PrivilegeNotHeld",
	"Message.InvalidCommandParameter",
	"Message.InvalidTextBoxParameter",
	"Message.CreateProcessFailed",
	""
};

std::wstring CNSudoResourceManagement::GetMessageString(
	_In_ NSUDO_MESSAGE MessageID)
{
	return this->GetTranslation(NSudoMessageTranslationID[MessageID]);
}

std::wstring CNSudoResourceManagement::GetUTF8WithBOMStringResources(
	_In_ UINT uID)
{
	M2_RESOURCE_INFO ResourceInfo = { 0 };
	if (SUCCEEDED(M2LoadResource(
		&ResourceInfo,
		this->Instance,
		L"String",
		MAKEINTRESOURCEW(uID))))
	{
		std::string RawString(
			reinterpret_cast<const char*>(ResourceInfo.Pointer),
			ResourceInfo.Size);
		// Raw string without the UTF-8 BOM. (0xEF,0xBB,0xBF)	
		return M2MakeUTF16String(RawString.c_str() + 3);
	}

	return L"";
}

// 分割获取的命令行以方便解析
std::vector<std::wstring> NSudoSplitCommandLine(LPCWSTR lpCommandLine)
{
	std::vector<std::wstring> result;

	std::vector<std::wstring> SplitArguments = M2SpiltCommandLine(
		lpCommandLine);

	size_t arg_size = 0;

	for (auto& SplitArgument : SplitArguments)
	{
		// 如果是程序路径或者为命令参数
		if (result.empty() || (SplitArgument[0] == L'-' || SplitArgument[0] == L'/'))
		{
			// 累加长度 (包括空格)
			// 为最后成功保存用户要执行的命令或快捷命令名打基础
			arg_size += SplitArgument.size() + 1;

			// 保存入解析器
			result.push_back(SplitArgument);
		}
		else
		{
			// 获取搜索用户要执行的命令或快捷命令名的位置（大致位置）
			// 对arg_size减1是为了留出空格，保证程序路径没有引号时也能正确解析
			wchar_t* search_start =
				const_cast<wchar_t*>(lpCommandLine) + (arg_size - 1);

			// 获取用户要执行的命令或快捷命令名
			// 搜索第一个参数分隔符（即空格）开始的位置			
			// 最后对结果增1是因为该返回值是空格开始出，而最开始的空格需要排除
			wchar_t* command = wcsstr(search_start, L" ") + 1;

			// 保存入解析器
			result.push_back(std::wstring(command));

			break;
		}
	}

	return result;
}

/*
SuCreateProcess函数创建一个新进程和对应的主线程
The SuCreateProcess function creates a new process and its primary thread.

如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
If the function fails, the return value is NULL. To get extended error
information, call GetLastError.
*/
bool SuCreateProcess(
	_In_opt_ HANDLE hToken,
	_Inout_ LPCWSTR lpCommandLine,
	_In_ DWORD WaitInterval)
{
	//生成命令行
	std::wstring final_command_line;

	std::map<std::wstring, std::wstring>::const_iterator iterator = 
		g_ResourceManagement.ShortCutList.find(lpCommandLine);

	if (g_ResourceManagement.ShortCutList.end() != iterator)
	{
		final_command_line = iterator->second;
	}
	else
	{
		final_command_line = lpCommandLine;
	}

	return NSudoCreateProcess(
		hToken,
		final_command_line.c_str(),
		g_ResourceManagement.AppPath.c_str(),
		WaitInterval);
}

#include "NSudoContextMenuManagement.h"

// 解析命令行
NSUDO_MESSAGE NSudoCommandLineParser(
	_In_ bool bElevated,
	_In_ bool bEnableContextMenuManagement,
	_In_ std::wstring& ApplicationName,
	_In_ std::map<std::wstring, std::wstring>& OptionsAndParameters,
	_In_ std::wstring& UnresolvedCommandLine)
{
	UNREFERENCED_PARAMETER(ApplicationName);

	if (1 == OptionsAndParameters.size() && UnresolvedCommandLine.empty())
	{
		auto OptionAndParameter = *OptionsAndParameters.begin();

		// 如果选项名是 "?", "Help" 或"Version"，则显示帮助。
		if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"?") ||
			0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Help") ||
			0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Version"))
		{
			return NSUDO_MESSAGE::NEED_TO_SHOW_COMMAND_LINE_HELP;
		}
		else
		{
			if (bEnableContextMenuManagement)
			{
				CNSudoContextMenuManagement ContextMenuManagement;

				if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Install"))
				{
					// 如果参数是 /Install 或 -Install，则安装NSudo到系统
					if (ERROR_SUCCESS != ContextMenuManagement.Install())
					{
						ContextMenuManagement.Uninstall();
					}

					return NSUDO_MESSAGE::SUCCESS;
				}
				else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Uninstall"))
				{
					// 如果参数是 /Uninstall 或 -Uninstall，则移除安装到系统的NSudo
					ContextMenuManagement.Uninstall();

					return NSUDO_MESSAGE::SUCCESS;
				}
			}

			return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
		}
	}

	DWORD dwSessionID = (DWORD)-1;

	// 获取当前进程会话ID
	if (!NSudoGetCurrentProcessSessionID(&dwSessionID))
	{
		return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
	}

	// 如果未提权或者模拟System权限失败
	if (!(bElevated && NSudoImpersonateAsSystem()))
	{
		return NSUDO_MESSAGE::PRIVILEGE_NOT_HELD;
	}

	bool bArgErr = false;

	M2::CHandle hToken;
	M2::CHandle hTempToken;

	// 解析参数列表

	enum class NSudoOptionUserValue
	{
		Default,
		TrustedInstaller,
		System,
		CurrentUser,
		CurrentProcess,
		CurrentProcessDropRight
	};

	enum class NSudoOptionPrivilegesValue
	{
		Default,
		EnableAllPrivileges,
		DisableAllPrivileges
	};

	enum class NSudoOptionIntegrityLevelValue
	{
		Default,
		System,
		High,
		Medium,
		Low
	};

	NSudoOptionUserValue UserMode = 
		NSudoOptionUserValue::Default;
	NSudoOptionPrivilegesValue PrivilegesMode = 
		NSudoOptionPrivilegesValue::Default;
	NSudoOptionIntegrityLevelValue IntegrityLevelMode = 
		NSudoOptionIntegrityLevelValue::Default;
	DWORD WaitInterval = 0;

	if (0 == OptionsAndParameters.size())
	{
		UserMode = NSudoOptionUserValue::TrustedInstaller;
		PrivilegesMode = NSudoOptionPrivilegesValue::EnableAllPrivileges;
	}
	else
	{
		for (auto& OptionAndParameter : OptionsAndParameters)
		{
			if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"U"))
			{
				if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"T"))
				{
					UserMode = NSudoOptionUserValue::TrustedInstaller;
				}
				else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"S"))
				{
					UserMode = NSudoOptionUserValue::System;
				}
				else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"C"))
				{
					UserMode = NSudoOptionUserValue::CurrentUser;
				}
				else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"P"))
				{
					UserMode = NSudoOptionUserValue::CurrentProcess;
				}
				else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"D"))
				{
					UserMode = NSudoOptionUserValue::CurrentProcessDropRight;
				}
				else
				{
					bArgErr = true;
					break;
				}
			}
			else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"P"))
			{
				if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"E"))
				{
					PrivilegesMode = NSudoOptionPrivilegesValue::EnableAllPrivileges;
				}
				else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"D"))
				{
					PrivilegesMode = NSudoOptionPrivilegesValue::DisableAllPrivileges;
				}
				else
				{
					bArgErr = true;
					break;
				}
			}
			else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"M"))
			{
				if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"S"))
				{
					IntegrityLevelMode = NSudoOptionIntegrityLevelValue::System;
				}
				else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"H"))
				{
					IntegrityLevelMode = NSudoOptionIntegrityLevelValue::High;
				}
				else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"M"))
				{
					IntegrityLevelMode = NSudoOptionIntegrityLevelValue::Medium;
				}
				else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"L"))
				{
					IntegrityLevelMode = NSudoOptionIntegrityLevelValue::Low;
				}
				else
				{
					bArgErr = true;
					break;
				}
			}
			else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Wait"))
			{
				if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Infinite"))
				{
					WaitInterval = INFINITE;
				}
				else
				{
					if (1 != swscanf_s(OptionAndParameter.second.c_str(), L"%ul", &WaitInterval))
					{
						bArgErr = true;
						break;
					}
				}
			}
		}
	}

	if (bArgErr && NSudoOptionUserValue::Default == UserMode)
	{
		return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
	}

	if (NSudoOptionUserValue::TrustedInstaller == UserMode)
	{
		if (!NSudoDuplicateServiceToken(
			L"TrustedInstaller",
			MAXIMUM_ALLOWED,
			nullptr,
			SecurityIdentification,
			TokenPrimary,
			&hToken))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}

		if (!SetTokenInformation(
			hToken,
			TokenSessionId,
			(PVOID)&dwSessionID,
			sizeof(DWORD)))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else if (NSudoOptionUserValue::System == UserMode)
	{
		if (!NSudoDuplicateSystemToken(
			MAXIMUM_ALLOWED,
			nullptr,
			SecurityIdentification,
			TokenPrimary,
			&hToken))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else if (NSudoOptionUserValue::CurrentUser == UserMode)
	{
		if (!NSudoDuplicateSessionToken(
			dwSessionID,
			MAXIMUM_ALLOWED,
			nullptr,
			SecurityIdentification,
			TokenPrimary,
			&hToken))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else if (NSudoOptionUserValue::CurrentProcess == UserMode)
	{
		if (!DuplicateTokenEx(
			g_ResourceManagement.OriginalCurrentProcessToken,
			MAXIMUM_ALLOWED,
			nullptr,
			SecurityIdentification,
			TokenPrimary,
			&hToken))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else if (NSudoOptionUserValue::CurrentProcessDropRight == UserMode)
	{
		if (!DuplicateTokenEx(
			g_ResourceManagement.OriginalCurrentProcessToken,
			MAXIMUM_ALLOWED,
			nullptr,
			SecurityIdentification,
			TokenPrimary,
			&hTempToken))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}

		if (!NSudoCreateLUAToken(&hToken, hTempToken))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}

	if (NSudoOptionPrivilegesValue::EnableAllPrivileges == PrivilegesMode)
	{
		if (!NSudoSetTokenAllPrivileges(hToken, true))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else if (NSudoOptionPrivilegesValue::DisableAllPrivileges == PrivilegesMode)
	{
		if (!NSudoSetTokenAllPrivileges(hToken, false))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}

	if (NSudoOptionIntegrityLevelValue::System == IntegrityLevelMode)
	{
		if (!NSudoSetTokenIntegrityLevel(hToken, SystemLevel))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else if (NSudoOptionIntegrityLevelValue::High == IntegrityLevelMode)
	{
		if (!NSudoSetTokenIntegrityLevel(hToken, HighLevel))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else if (NSudoOptionIntegrityLevelValue::Medium == IntegrityLevelMode)
	{
		if (!NSudoSetTokenIntegrityLevel(hToken, MediumLevel))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else if (NSudoOptionIntegrityLevelValue::Low == IntegrityLevelMode)
	{
		if (!NSudoSetTokenIntegrityLevel(hToken, LowLevel))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}

	if (!SuCreateProcess(hToken, UnresolvedCommandLine.c_str(), WaitInterval))
	{
		return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
	}

	RevertToSelf();

	return NSUDO_MESSAGE::SUCCESS;
}
