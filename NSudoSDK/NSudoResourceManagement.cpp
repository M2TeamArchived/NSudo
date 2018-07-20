/******************************************************************************
Project: NSudoSDK
Description: Implementation for the Resource Management.
File Name: NSudoResourceManagement.cpp
License: The MIT License
******************************************************************************/

#include "stdafx.h"

#include <Windows.h>
#include <fstream>

#include "M2ResourceManagement.h"

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

	this->m_ExePath = M2GetCurrentModulePath();

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

	int argc = 0;
	wchar_t **argv = CommandLineToArgvW(lpCommandLine, &argc);

	size_t arg_size = 0;

	for (int i = 0; i < argc; ++i)
	{
		// 如果是程序路径或者为命令参数
		if (i == 0 || (argv[i][0] == L'-' || argv[i][0] == L'/'))
		{
			std::wstring arg(argv[i]);

			// 累加长度 (包括空格)
			// 为最后成功保存用户要执行的命令或快捷命令名打基础
			arg_size += arg.size() + 1;

			// 保存入解析器
			result.push_back(arg);
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

			std::wstring final_command;

			// 如果最外层有引号则去除，否则直接生成
			if (command[0] == L'\"' || command[0] == L'\'')
			{
				final_command = std::wstring(command + 1);
				final_command.resize(final_command.size() - 1);
			}
			else
			{
				final_command = std::wstring(command);
			}

			// 保存入解析器
			result.push_back(final_command);

			break;
		}
	}

	return result;
}

std::vector<std::wstring> CNSudoResourceManagement::GetCommandParameters()
{
	return NSudoSplitCommandLine(GetCommandLineW());
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
	_In_opt_ bool bWait)
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
		bWait);
}

#include "NSudoContextMenuManagement.h"

// 解析命令行
NSUDO_MESSAGE NSudoCommandLineParser(
	_In_ bool bElevated,
	_In_ bool bEnableContextMenuManagement,
	_In_ const std::vector<std::wstring>& args)
{
	if (2 == args.size())
	{
		// 判断是单个参数还是命令行
		if ((args[1][0] == L'-' || args[1][0] == L'/'))
		{
			const wchar_t* arg = args[1].c_str() + 1;

			// 如果参数是 /? 或 -?，则显示帮助
			if (0 == _wcsicmp(arg, L"?"))
			{
				return NSUDO_MESSAGE::NEED_TO_SHOW_COMMAND_LINE_HELP;
			}
			else
			{
				if (bEnableContextMenuManagement)
				{					
					CNSudoContextMenuManagement ContextMenuManagement;

					if (0 == _wcsicmp(arg, L"Install"))
					{
						// 如果参数是 /Install 或 -Install，则安装NSudo到系统
						if (ERROR_SUCCESS != ContextMenuManagement.Install())
						{
							ContextMenuManagement.Uninstall();
						}

						return NSUDO_MESSAGE::SUCCESS;
					}
					else if (0 == _wcsicmp(arg, L"Uninstall"))
					{
						// 如果参数是 /Uninstall 或 -Uninstall，则移除安装到系统的NSudo
						ContextMenuManagement.Uninstall();
						return NSUDO_MESSAGE::SUCCESS;
					}
				}

				return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
			}
		}
		else
		{
			std::vector<std::wstring> NewArg;

			NewArg.push_back(args[0]);
			NewArg.push_back(L"-U:T");
			NewArg.push_back(L"-P:E");
			NewArg.push_back(args[1]);
		
			return NSudoCommandLineParser(
				bElevated,
				bEnableContextMenuManagement,
				NewArg);
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

	bool bGetUser = false;
	bool bGetPrivileges = false;
	bool bGetIntegrityLevel = false;

	bool bGetWait = false;
	bool bWait = false;

	M2::CHandle hToken;
	M2::CHandle hTempToken;

	// 解析参数，忽略第一项（必定是程序路径）和最后一项（因为必定是命令行）
	for (size_t i = 1; i < args.size() - 1; ++i)
	{
		// 如果参数不满足条件，则返回错误
		if (!(args[i][0] == L'-' || args[i][0] == L'/'))
		{
			bArgErr = true;
			break;
		}

		const wchar_t* arg = args[i].c_str() + 1;






		if (!bGetUser)
		{
			if (0 == _wcsicmp(arg, L"U:T"))
			{
				if (NSudoDuplicateServiceToken(
					L"TrustedInstaller",
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken))
				{
					SetTokenInformation(
						hToken,
						TokenSessionId,
						(PVOID)&dwSessionID,
						sizeof(DWORD));
				}
			}
			else if (0 == _wcsicmp(arg, L"U:S"))
			{
				NSudoDuplicateSystemToken(
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken);
			}
			else if (0 == _wcsicmp(arg, L"U:C"))
			{
				NSudoDuplicateSessionToken(
					dwSessionID,
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken);
			}
			else if (0 == _wcsicmp(arg, L"U:P"))
			{
				DuplicateTokenEx(
					g_ResourceManagement.OriginalCurrentProcessToken,
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken);
			}
			else if (0 == _wcsicmp(arg, L"U:D"))
			{
				if (DuplicateTokenEx(
					g_ResourceManagement.OriginalCurrentProcessToken,
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hTempToken))
				{
					NSudoCreateLUAToken(&hToken, hTempToken);
				}
			}
			else
			{
				bArgErr = true;
				break;
			}

			bGetUser = true;
		}
		else if (!bGetPrivileges)
		{
			if (0 == _wcsicmp(arg, L"P:E"))
			{
				NSudoSetTokenAllPrivileges(hToken, true);
			}
			else if (0 == _wcsicmp(arg, L"P:D"))
			{
				NSudoSetTokenAllPrivileges(hToken, false);
			}
			else
			{
				bArgErr = true;
				break;
			}

			bGetPrivileges = true;
		}
		else if (!bGetIntegrityLevel)
		{
			if (0 == _wcsicmp(arg, L"M:S"))
			{
				NSudoSetTokenIntegrityLevel(hToken, SystemLevel);
			}
			else if (0 == _wcsicmp(arg, L"M:H"))
			{
				NSudoSetTokenIntegrityLevel(hToken, HighLevel);
			}
			else if (0 == _wcsicmp(arg, L"M:M"))
			{
				NSudoSetTokenIntegrityLevel(hToken, MediumLevel);
			}
			else if (0 == _wcsicmp(arg, L"M:L"))
			{
				NSudoSetTokenIntegrityLevel(hToken, LowLevel);
			}
			else
			{
				bArgErr = true;
				break;
			}

			bGetIntegrityLevel = true;
		}
		else if (!bGetWait)
		{
			if (0 == _wcsicmp(arg, L"Wait"))
			{
				bWait = true;
			}

			bGetWait = true;
		}
	}

	if (bGetUser && !bArgErr)
	{
		if (!SuCreateProcess(hToken, args[args.size() - 1].c_str(), bWait))
		{
			return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
		}
	}
	else
	{
		return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
	}

	RevertToSelf();

	return NSUDO_MESSAGE::SUCCESS;
}
