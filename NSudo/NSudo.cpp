// NSudo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// The NSudo message enum.
enum NSUDO_MESSAGE
{
	SUCCESS,
	PRIVILEGE_NOT_HELD,
	INVALID_COMMAND_PARAMETER,
	INVALID_TEXTBOX_PARAMETER,
	CREATE_PROCESS_FAILED,
	NEED_TO_SHOW_COMMAND_LINE_HELP,
	NEED_TO_SHOW_NSUDO_VERSION
};

const char* NSudoMessageTranslationID[] =
{
	"Message.Success",
	"Message.PrivilegeNotHeld",
	"Message.InvalidCommandParameter",
	"Message.InvalidTextBoxParameter",
	"Message.CreateProcessFailed",
	"",
	""
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
	const HINSTANCE& Instance = this->m_Instance;
	const std::wstring& ExePath = this->m_ExePath;
	const std::wstring& AppPath = this->m_AppPath;

	const std::map<std::wstring, std::wstring>& ShortCutList =
		this->m_ShortCutList;

	const HANDLE& OriginalCurrentProcessToken =
		this->m_OriginalCurrentProcessToken;
	const bool& IsElevated = this->m_IsElevated;

public:
	CNSudoResourceManagement()
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

	~CNSudoResourceManagement()
	{
		if (INVALID_HANDLE_VALUE != this->m_OriginalCurrentProcessToken)
		{
			CloseHandle(this->m_OriginalCurrentProcessToken);
		}
	}

	const std::wstring GetVersionText()
	{
		return
			L"M2-Team NSudo " NSUDO_VERSION_STRING;
	}

	const std::wstring GetLogoText()
	{
		return
			L"M2-Team NSudo " NSUDO_VERSION_STRING L"\r\n"
			L"© M2-Team. All rights reserved.\r\n"
			L"\r\n";
	}

	std::wstring GetTranslation(
		_In_ std::string Key)
	{
		return this->m_StringTranslations[Key];
	}

	std::wstring GetMessageString(
		_In_ NSUDO_MESSAGE MessageID)
	{
		return this->GetTranslation(NSudoMessageTranslationID[MessageID]);
	}

	std::wstring GetUTF8WithBOMStringResources(
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
};

CNSudoResourceManagement g_ResourceManagement;

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

typedef struct _NSUDO_CONTEXT_MENU_ITEM
{
	std::wstring ItemName;
	std::wstring ItemDescription;
	std::wstring ItemCommandParameters;
	bool HasLUAShield;
} NSUDO_CONTEXT_MENU_ITEM, *PNSUDO_CONTEXT_MENU_ITEM;

class CNSudoContextMenuManagement
{
private:
	DWORD m_ConstructorError = ERROR_SUCCESS;

	std::wstring m_NSudoPath;
	M2::CHKey m_CommandStoreRoot;

	std::vector<NSUDO_CONTEXT_MENU_ITEM> m_ContextMenuItems;

public:
	CNSudoContextMenuManagement()
	{
		this->m_ConstructorError = M2GetWindowsDirectory(this->m_NSudoPath);		
		if (FAILED(this->m_ConstructorError))
		{
			return;
		}
		this->m_NSudoPath.append(L"\\NSudo.exe");
		
		this->m_ConstructorError = RegOpenKeyExW(
			HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell",
			0,
			KEY_ALL_ACCESS | KEY_WOW64_64KEY,
			&this->m_CommandStoreRoot);
		if (ERROR_SUCCESS != this->m_ConstructorError)
			return;

		rapidjson::Document ContextMenuJSON;

		M2_RESOURCE_INFO ResourceInfo = { 0 };
		if (SUCCEEDED(M2LoadResource(
			&ResourceInfo,
			GetModuleHandleW(nullptr),
			L"Config",
			MAKEINTRESOURCEW(IDR_CONFIG_CONTEXT_MENU))))
		{
			ContextMenuJSON.Parse(
				reinterpret_cast<const char*>(ResourceInfo.Pointer),
				ResourceInfo.Size);

			for (auto& Item : ContextMenuJSON["ContextMenu"].GetArray())
			{
				auto& ItemName = Item["ItemName"];
				auto& ItemDescriptionID = Item["ItemDescriptionID"];
				auto& ItemCommandParameters = Item["ItemCommandParameters"];

				std::string RawItemName = std::string(
					ItemName.GetString(),
					ItemName.GetStringLength());
				std::string RawItemDescriptionID = std::string(
					ItemDescriptionID.GetString(),
					ItemDescriptionID.GetStringLength());
				std::string RawItemCommandParameters = std::string(
					ItemCommandParameters.GetString(),
					ItemCommandParameters.GetStringLength());
				bool HasLUAShield = Item["HasLUAShield"].GetBool();

				NSUDO_CONTEXT_MENU_ITEM ContextMenuItem;

				ContextMenuItem.ItemName = M2MakeUTF16String(RawItemName);

				ContextMenuItem.ItemDescription =
					g_ResourceManagement.GetTranslation(
						RawItemDescriptionID);

				ContextMenuItem.ItemCommandParameters = M2MakeUTF16String(
					RawItemCommandParameters);

				ContextMenuItem.HasLUAShield = HasLUAShield;

				this->m_ContextMenuItems.push_back(ContextMenuItem);
			}
		}
	}

	DWORD Install()
	{
		if (ERROR_SUCCESS != this->m_ConstructorError)
			return this->m_ConstructorError;

		CopyFileW(
			M2GetCurrentProcessModulePath().c_str(),
			this->m_NSudoPath.c_str(),
			FALSE);

		DWORD dwError = ERROR_SUCCESS;

		std::wstring NSudoPathWithQuotation =
			std::wstring(L"\"") + this->m_NSudoPath + L"\"";

		M2::CHKey hNSudoItem;
		std::wstring SubCommands;

		for (NSUDO_CONTEXT_MENU_ITEM Item : this->m_ContextMenuItems)
		{
			std::wstring GeneratedItemCommand =
				NSudoPathWithQuotation +
				L" " + Item.ItemCommandParameters + L" -ShowWindowMode=Hide cmd /c start \"NSudo.ContextMenu.Launcher\" " +
				L"%1";

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

	DWORD Uninstall()
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

};

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

		
		if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"?") ||
			0 == _wcsicmp(OptionAndParameter.first.c_str(), L"H") ||
			0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Help"))
		{
			// 如果选项名是 "?", "H" 或 "Help"，则显示帮助。
			return NSUDO_MESSAGE::NEED_TO_SHOW_COMMAND_LINE_HELP;
		}
		else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Version"))
		{
			// 如果选项名是 "?", "H" 或 "Help"，则显示 NSudo 版本号。
			return NSUDO_MESSAGE::NEED_TO_SHOW_NSUDO_VERSION;
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

	enum class NSudoOptionProcessPriorityValue
	{
		Default,
		Idle,
		BelowNormal,
		Normal,
		AboveNormal,
		High,
		RealTime
	};

	enum class NSudoOptionWindowModeValue
	{
		Default,
		Show,
		Hide,
		Maximize,
		Minimize,
	};

	NSudoOptionUserValue UserMode =
		NSudoOptionUserValue::Default;
	NSudoOptionPrivilegesValue PrivilegesMode =
		NSudoOptionPrivilegesValue::Default;
	NSudoOptionIntegrityLevelValue IntegrityLevelMode =
		NSudoOptionIntegrityLevelValue::Default;
	NSudoOptionProcessPriorityValue ProcessPriorityMode = 
		NSudoOptionProcessPriorityValue::Default;
	NSudoOptionWindowModeValue WindowMode = 
		NSudoOptionWindowModeValue::Default;

	DWORD WaitInterval = 0;
	std::wstring CurrentDirectory = g_ResourceManagement.AppPath;
	DWORD ShowWindowMode = SW_SHOWDEFAULT;
	bool CreateNewConsole = true;

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
			WaitInterval = INFINITE;
		}
		else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Priority"))
		{
			if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Idle"))
			{
				ProcessPriorityMode = NSudoOptionProcessPriorityValue::Idle;
			}
			else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"BelowNormal"))
			{
				ProcessPriorityMode = NSudoOptionProcessPriorityValue::BelowNormal;
			}
			else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Normal"))
			{
				ProcessPriorityMode = NSudoOptionProcessPriorityValue::Normal;
			}
			else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"AboveNormal"))
			{
				ProcessPriorityMode = NSudoOptionProcessPriorityValue::AboveNormal;
			}
			else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"High"))
			{
				ProcessPriorityMode = NSudoOptionProcessPriorityValue::High;
			}
			else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"RealTime"))
			{
				ProcessPriorityMode = NSudoOptionProcessPriorityValue::RealTime;
			}
			else
			{
				bArgErr = true;
				break;
			}
		}
		else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"CurrentDirectory"))
		{
			CurrentDirectory = OptionAndParameter.second;
		}
		else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"ShowWindowMode"))
		{
			if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Show"))
			{
				WindowMode = NSudoOptionWindowModeValue::Show;
			}
			else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Hide"))
			{
				WindowMode = NSudoOptionWindowModeValue::Hide;
			}
			else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Maximize"))
			{
				WindowMode = NSudoOptionWindowModeValue::Maximize;
			}
			else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Minimize"))
			{
				WindowMode = NSudoOptionWindowModeValue::Minimize;
			}
			else
			{
				bArgErr = true;
				break;
			}
		}
		else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"UseCurrentConsole"))
		{
			CreateNewConsole = false;
		}
		else
		{
			bArgErr = true;
			break;
		}
	}

	if (bArgErr || NSudoOptionUserValue::Default == UserMode)
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

	DWORD ProcessPriority = 0;

	if (NSudoOptionProcessPriorityValue::Idle == ProcessPriorityMode)
	{
		ProcessPriority = IDLE_PRIORITY_CLASS;
	}
	else if (NSudoOptionProcessPriorityValue::BelowNormal == ProcessPriorityMode)
	{
		ProcessPriority = BELOW_NORMAL_PRIORITY_CLASS;
	}
	else if (NSudoOptionProcessPriorityValue::Normal == ProcessPriorityMode)
	{
		ProcessPriority = NORMAL_PRIORITY_CLASS;
	}
	else if (NSudoOptionProcessPriorityValue::AboveNormal == ProcessPriorityMode)
	{
		ProcessPriority = ABOVE_NORMAL_PRIORITY_CLASS;
	}
	else if (NSudoOptionProcessPriorityValue::High == ProcessPriorityMode)
	{
		ProcessPriority = HIGH_PRIORITY_CLASS;
	}
	else if (NSudoOptionProcessPriorityValue::RealTime == ProcessPriorityMode)
	{
		ProcessPriority = REALTIME_PRIORITY_CLASS;
	}

	if (NSudoOptionWindowModeValue::Show == WindowMode)
	{
		ShowWindowMode = SW_SHOW;
	}
	else if (NSudoOptionWindowModeValue::Hide == WindowMode)
	{
		ShowWindowMode = SW_HIDE;
	}
	else if (NSudoOptionWindowModeValue::Maximize == WindowMode)
	{
		ShowWindowMode = SW_MAXIMIZE;
	}
	else if (NSudoOptionWindowModeValue::Minimize == WindowMode)
	{
		ShowWindowMode = SW_MINIMIZE;
	}

	if (UnresolvedCommandLine.empty())
	{
		return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
	}

	std::wstring final_command_line;

	std::map<std::wstring, std::wstring>::const_iterator iterator =
		g_ResourceManagement.ShortCutList.find(UnresolvedCommandLine);

	if (g_ResourceManagement.ShortCutList.end() != iterator)
	{
		final_command_line = iterator->second;
	}
	else
	{
		final_command_line = UnresolvedCommandLine;
	}

	if (!NSudoCreateProcessDirect(
		hToken,
		final_command_line.c_str(),
		CurrentDirectory.c_str(),
		WaitInterval, 
		ProcessPriority,
		ShowWindowMode,
		CreateNewConsole))
	{
		return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
	}

	RevertToSelf();

	return NSUDO_MESSAGE::SUCCESS;
}

void NSudoPrintMsg(
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ HWND hWnd,
	_In_ LPCWSTR lpContent)
{
#if defined(NSUDO_CUI_CONSOLE)
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hWnd);

	std::wstring DialogContent =
		g_ResourceManagement.GetLogoText() +
		lpContent +
		g_ResourceManagement.GetUTF8WithBOMStringResources(
			IDR_String_Links);

	DWORD NumberOfCharsWritten = 0;
	WriteConsoleW(
		GetStdHandle(STD_OUTPUT_HANDLE),
		DialogContent.c_str(),
		(DWORD)DialogContent.size(),
		&NumberOfCharsWritten,
		nullptr);
#endif
#if defined(NSUDO_CUI_WINDOWS) || defined(NSUDO_GUI_WINDOWS)
	std::wstring DialogContent =
		g_ResourceManagement.GetLogoText() +
		lpContent +
		g_ResourceManagement.GetUTF8WithBOMStringResources(IDR_String_Links);

	M2MessageDialog(
		hInstance,
		hWnd,
		MAKEINTRESOURCE(IDI_NSUDO),
		L"NSudo",
		DialogContent.c_str());
#endif
}

HRESULT NSudoShowAboutDialog(
	_In_ HWND hwndParent)
{
	std::wstring DialogContent =
		g_ResourceManagement.GetLogoText() +
		g_ResourceManagement.GetUTF8WithBOMStringResources(IDR_String_CommandLineHelp) +
		g_ResourceManagement.GetUTF8WithBOMStringResources(IDR_String_Links);

	SetLastError(ERROR_SUCCESS);

#if defined(NSUDO_CUI_CONSOLE)
	UNREFERENCED_PARAMETER(hwndParent);

	DWORD NumberOfCharsWritten = 0;
	WriteConsoleW(
		GetStdHandle(STD_OUTPUT_HANDLE),
		DialogContent.c_str(),
		(DWORD)DialogContent.size(),
		&NumberOfCharsWritten,
		nullptr);
#endif
#if defined(NSUDO_CUI_WINDOWS) || defined(NSUDO_GUI_WINDOWS)
	M2MessageDialog(
		g_ResourceManagement.Instance,
		hwndParent,
		MAKEINTRESOURCE(IDI_NSUDO),
		L"NSudo",
		DialogContent.c_str());
#endif

	return M2GetLastError();
}

#if defined(NSUDO_GUI_WINDOWS)

#include <ShellScalingApi.h>

inline HRESULT GetDpiForMonitorInternal(
	_In_ HMONITOR hmonitor,
	_In_ MONITOR_DPI_TYPE dpiType,
	_Out_ UINT *dpiX,
	_Out_ UINT *dpiY)
{
	HMODULE hModule = nullptr;
	decltype(GetDpiForMonitor)* pFunc = nullptr;
	HRESULT hr = E_NOINTERFACE;

	hModule = LoadLibraryW(L"SHCore.dll");
	if (!hModule) return M2GetLastError();

	pFunc = reinterpret_cast<decltype(pFunc)>(
		GetProcAddress(hModule, "GetDpiForMonitor"));
	if (!pFunc) return M2GetLastError();

	hr = pFunc(hmonitor, dpiType, dpiX, dpiY);

	FreeLibrary(hModule);

	return hr;
}

#include <atlbase.h>
#include <atlwin.h>

class CNSudoMainWindow : public ATL::CDialogImpl<CNSudoMainWindow>
{
public:
	enum { IDD = IDD_NSudoDlg };

public:
	BEGIN_MSG_MAP(CNSudoMainWindow)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_DPICHANGED, OnDPIChanged)

		COMMAND_ID_HANDLER(IDC_Run, OnRun)
		COMMAND_ID_HANDLER(IDC_About, OnAbout)
		COMMAND_ID_HANDLER(IDC_Browse, OnBrowse)

		MESSAGE_HANDLER(WM_DROPFILES, OnDropFiles)
	END_MSG_MAP()

public:
	CNSudoMainWindow()
	{
		M2EnablePerMonitorDialogScaling();

		ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
		ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); // WM_COPYGLOBALDATA
	}

	~CNSudoMainWindow()
	{

	}

private:
	HICON m_hNSudoIcon = nullptr;
	HICON m_hWarningIcon = nullptr;

	int m_xDPI = USER_DEFAULT_SCREEN_DPI;
	int m_yDPI = USER_DEFAULT_SCREEN_DPI;

	ATL::CWindow m_hUserName;
	ATL::CWindow m_hCheckBox;
	ATL::CWindow m_hszPath;

	LRESULT OnClose(
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL& bHandled)
	{
		UNREFERENCED_PARAMETER(uMsg);
		UNREFERENCED_PARAMETER(wParam);
		UNREFERENCED_PARAMETER(lParam);
		UNREFERENCED_PARAMETER(bHandled);
		
		this->EndDialog(0);
		return 0;
	}

	LRESULT OnInitDialog(
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL& bHandled)
	{
		UNREFERENCED_PARAMETER(uMsg);
		UNREFERENCED_PARAMETER(wParam);
		UNREFERENCED_PARAMETER(lParam);
		UNREFERENCED_PARAMETER(bHandled);

		this->m_hUserName = this->GetDlgItem(IDC_UserName);
		this->m_hCheckBox = this->GetDlgItem(IDC_Check_EnableAllPrivileges);
		this->m_hszPath = this->GetDlgItem(IDC_szPath);

		this->SetWindowTextW(g_ResourceManagement.GetVersionText().c_str());

		struct { const char* ID; ATL::CWindow Control; } x[] =
		{
			{ "EnableAllPrivileges" , this->m_hCheckBox },
			{ "WarningText" , this->GetDlgItem(IDC_WARNINGTEXT) },
			{ "SettingsGroupText" ,this->GetDlgItem(IDC_SETTINGSGROUPTEXT) },
			{ "Static.User",this->GetDlgItem(IDC_STATIC_USER) },
			{ "Static.Open", this->GetDlgItem(IDC_STATIC_OPEN) },
			{ "Button.About", this->GetDlgItem(IDC_About) },
			{ "Button.Browse", this->GetDlgItem(IDC_Browse) },
			{ "Button.Run", this->GetDlgItem(IDC_Run) }
		};

		for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); ++i)
		{
			std::wstring Buffer = g_ResourceManagement.GetTranslation(x[i].ID);
			x[i].Control.SetWindowTextW(Buffer.c_str());
		}

		HRESULT hr = E_FAIL;

		hr = GetDpiForMonitorInternal(
			MonitorFromWindow(this->m_hWnd, MONITOR_DEFAULTTONEAREST),
			MDT_EFFECTIVE_DPI, (UINT*)&this->m_xDPI, (UINT*)&this->m_yDPI);
		if (hr != S_OK)
		{
			this->m_xDPI = GetDeviceCaps(this->GetDC(), LOGPIXELSX);
			this->m_yDPI = GetDeviceCaps(this->GetDC(), LOGPIXELSY);
		}

		this->m_hNSudoIcon = (HICON)LoadImageW(
			g_ResourceManagement.Instance,
			MAKEINTRESOURCE(IDI_NSUDO),
			IMAGE_ICON,
			256,
			256,
			LR_SHARED);

		SendMessageW(this->m_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)this->m_hNSudoIcon);
		SendMessageW(this->m_hWnd, WM_SETICON, ICON_BIG, (LPARAM)this->m_hNSudoIcon);

		this->m_hWarningIcon = (HICON)LoadImageW(
			nullptr,
			IDI_WARNING,
			IMAGE_ICON,
			0,
			0,
			LR_SHARED);

		const char* UserNameID[] = { "TI" ,"System" ,"CurrentProcess" ,"CurrentUser" };
		for (size_t i = 0; i < sizeof(UserNameID) / sizeof(*UserNameID); ++i)
		{
			std::wstring Buffer = g_ResourceManagement.GetTranslation(UserNameID[i]);
			SendMessageW(this->m_hUserName, CB_INSERTSTRING, 0, (LPARAM)Buffer.c_str());
		}

		//设置默认项"TrustedInstaller"
		SendMessageW(this->m_hUserName, CB_SETCURSEL, 3, 0);

		for (std::pair<std::wstring, std::wstring> Item
			: g_ResourceManagement.ShortCutList)
		{
			SendMessageW(
				this->m_hszPath,
				CB_INSERTSTRING,
				0,
				(LPARAM)Item.first.c_str());
		}

		return TRUE;
	}

	LRESULT OnPaint(
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL& bHandled)
	{
		UNREFERENCED_PARAMETER(uMsg);
		UNREFERENCED_PARAMETER(wParam);
		UNREFERENCED_PARAMETER(lParam);
		UNREFERENCED_PARAMETER(bHandled);
		
		PAINTSTRUCT ps;
		HDC hdc = this->BeginPaint(&ps);
		
		RECT rect = { 0 };
		this->GetClientRect(&rect);

		DrawIconEx(
			hdc,
			MulDiv(16, this->m_xDPI, USER_DEFAULT_SCREEN_DPI),
			MulDiv(16, this->m_yDPI, USER_DEFAULT_SCREEN_DPI),
			this->m_hNSudoIcon,
			MulDiv(64, this->m_xDPI, USER_DEFAULT_SCREEN_DPI),
			MulDiv(64, this->m_yDPI, USER_DEFAULT_SCREEN_DPI),
			0,
			nullptr,
			DI_NORMAL | DI_COMPAT);
		DrawIconEx(
			hdc,
			MulDiv(16, this->m_xDPI, USER_DEFAULT_SCREEN_DPI),
			(rect.bottom - rect.top) - MulDiv(40, this->m_yDPI, USER_DEFAULT_SCREEN_DPI),
			this->m_hWarningIcon,
			MulDiv(24, this->m_xDPI, USER_DEFAULT_SCREEN_DPI),
			MulDiv(24, this->m_yDPI, USER_DEFAULT_SCREEN_DPI),
			0,
			nullptr,
			DI_NORMAL | DI_COMPAT);

		this->EndPaint(&ps);

		return 0;
	}

	LRESULT OnDPIChanged(
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL& bHandled)
	{
		UNREFERENCED_PARAMETER(uMsg);
		UNREFERENCED_PARAMETER(lParam);
		UNREFERENCED_PARAMETER(bHandled);

		this->m_xDPI = LOWORD(wParam);
		this->m_yDPI = HIWORD(wParam);

		return 0;
	}

	LRESULT OnRun(
		WORD wNotifyCode,
		WORD wID,
		HWND hWndCtl,
		BOOL& bHandled)
	{
		UNREFERENCED_PARAMETER(wNotifyCode);
		UNREFERENCED_PARAMETER(wID);
		UNREFERENCED_PARAMETER(hWndCtl);
		UNREFERENCED_PARAMETER(bHandled);

		std::wstring UserName(MAX_PATH, L'\0');
		auto UserNameLength = this->m_hUserName.GetWindowTextW(
			&UserName[0],
			static_cast<int>(UserName.size()));
		UserName.resize(UserNameLength);

		bool NeedToEnableAllPrivileges = false;
		if (BST_CHECKED == SendMessageW(this->m_hCheckBox, BM_GETCHECK, 0, 0))
		{
			NeedToEnableAllPrivileges = true;
		}

		std::wstring RawCommandLine(MAX_PATH, L'\0');
		auto RawCommandLineLength = this->m_hszPath.GetWindowTextW(
			&RawCommandLine[0],
			static_cast<int>(RawCommandLine.size()));
		RawCommandLine.resize(RawCommandLineLength);

		if (_wcsicmp(L"", RawCommandLine.c_str()) == 0)
		{
			std::wstring Buffer = g_ResourceManagement.GetMessageString(
				NSUDO_MESSAGE::INVALID_TEXTBOX_PARAMETER);
			NSudoPrintMsg(
				g_ResourceManagement.Instance,
				this->m_hWnd,
				Buffer.c_str());
		}
		else
		{
			std::wstring CommandLine = L"NSudo";

			// 获取用户令牌
			if (0 == _wcsicmp(
				g_ResourceManagement.GetTranslation("TI").c_str(),
				UserName.c_str()))
			{
				CommandLine += L" -U:T";
			}
			else if (0 == _wcsicmp(
				g_ResourceManagement.GetTranslation("System").c_str(), 
				UserName.c_str()))
			{
				CommandLine += L" -U:S";
			}
			else if (0 == _wcsicmp(
				g_ResourceManagement.GetTranslation("CurrentProcess").c_str(), 
				UserName.c_str()))
			{
				CommandLine += L" -U:P";
			}
			else if (0 == _wcsicmp(
				g_ResourceManagement.GetTranslation("CurrentUser").c_str(), 
				UserName.c_str()))
			{
				CommandLine += L" -U:C";
			}

			// 如果勾选启用全部特权，则尝试对令牌启用全部特权
			if (NeedToEnableAllPrivileges)
			{
				CommandLine += L" -P:E";
			}

			CommandLine += L" ";
			CommandLine += RawCommandLine;

			std::wstring ApplicationName;
			std::map<std::wstring, std::wstring> OptionsAndParameters;
			std::wstring UnresolvedCommandLine;

			M2SpiltCommandLineEx(
				CommandLine,
				std::vector<std::wstring>{ L"-", L"/", L"--" },
				std::vector<std::wstring>{ L"=", L":" },
				ApplicationName,
				OptionsAndParameters,
				UnresolvedCommandLine);

			NSUDO_MESSAGE message = NSudoCommandLineParser(
				true,
				true,
				ApplicationName,
				OptionsAndParameters,
				UnresolvedCommandLine);
			if (NSUDO_MESSAGE::SUCCESS != message)
			{
				std::wstring Buffer = g_ResourceManagement.GetMessageString(
					message);
				NSudoPrintMsg(
					g_ResourceManagement.Instance,
					this->m_hWnd,
					Buffer.c_str());
			}
		}

		return 0;
	}

	LRESULT OnAbout(
		WORD wNotifyCode,
		WORD wID,
		HWND hWndCtl,
		BOOL& bHandled)
	{
		UNREFERENCED_PARAMETER(wNotifyCode);
		UNREFERENCED_PARAMETER(wID);
		UNREFERENCED_PARAMETER(hWndCtl);
		UNREFERENCED_PARAMETER(bHandled);

		NSudoShowAboutDialog(this->m_hWnd);

		return 0;
	}

	LRESULT OnBrowse(
		WORD wNotifyCode,
		WORD wID,
		HWND hWndCtl,
		BOOL& bHandled)
	{
		UNREFERENCED_PARAMETER(wNotifyCode);
		UNREFERENCED_PARAMETER(wID);
		UNREFERENCED_PARAMETER(hWndCtl);
		UNREFERENCED_PARAMETER(bHandled);

		std::wstring buffer(MAX_PATH + 2, L'\0');

		buffer[0] = L'\"';

		OPENFILENAME ofn = { 0 };

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = this->m_hWnd;
		ofn.nMaxFile = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrFile = &buffer[1];
		ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

		GetOpenFileNameW(&ofn);

		buffer.resize(wcslen(buffer.c_str()));

		buffer[buffer.size()] = L'\"';

		if (wcslen(buffer.c_str()) > 2)
			this->m_hszPath.SetWindowTextW(buffer.c_str());

		return 0;
	}

	LRESULT OnDropFiles(
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		BOOL& bHandled)
	{
		UNREFERENCED_PARAMETER(uMsg);
		UNREFERENCED_PARAMETER(lParam);
		UNREFERENCED_PARAMETER(bHandled);

		std::wstring buffer(MAX_PATH + 2, L'\0');

		buffer[0] = L'\"';

		auto length = DragQueryFileW(
			(HDROP)wParam, 0, &buffer[1], (int)(buffer.size() - 2));
		buffer.resize(length + 1);

		if (!(GetFileAttributesW(&buffer[1]) & FILE_ATTRIBUTE_DIRECTORY))
		{
			buffer[buffer.size()] = L'\"';
			this->m_hszPath.SetWindowTextW(buffer.c_str());
		}

		DragFinish((HDROP)wParam);

		return 0;
	}
};

#endif

int NSudoMain()
{
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	std::wstring ApplicationName;
	std::map<std::wstring, std::wstring> OptionsAndParameters;
	std::wstring UnresolvedCommandLine;

	M2SpiltCommandLineEx(
		std::wstring(GetCommandLineW()),
		std::vector<std::wstring>{ L"-", L"/", L"--" },
		std::vector<std::wstring>{ L"=", L":" },
		ApplicationName,
		OptionsAndParameters,
		UnresolvedCommandLine);

	if (OptionsAndParameters.empty() && UnresolvedCommandLine.empty())
	{
#if defined(NSUDO_CUI_CONSOLE) || defined(NSUDO_CUI_WINDOWS)
		NSudoShowAboutDialog(nullptr);
#endif
#if defined(NSUDO_GUI_WINDOWS)
		CNSudoMainWindow MainWindow;
		MainWindow.DoModal(nullptr);
#endif
		return 0;
	}

#if defined(NSUDO_CUI_CONSOLE)
	NSUDO_MESSAGE message = NSudoCommandLineParser(
		g_ResourceManagement.IsElevated,
		false,
		ApplicationName,
		OptionsAndParameters,
		UnresolvedCommandLine);
#endif
#if defined(NSUDO_CUI_WINDOWS) || defined(NSUDO_GUI_WINDOWS)
	NSUDO_MESSAGE message = NSudoCommandLineParser(
		g_ResourceManagement.IsElevated,
		true,
		ApplicationName,
		OptionsAndParameters,
		UnresolvedCommandLine);
#endif

	if (NSUDO_MESSAGE::NEED_TO_SHOW_COMMAND_LINE_HELP == message)
	{
		NSudoShowAboutDialog(nullptr);
	}
	else if (NSUDO_MESSAGE::NEED_TO_SHOW_NSUDO_VERSION == message)
	{
		NSudoPrintMsg(
			g_ResourceManagement.Instance,
			nullptr,
			g_ResourceManagement.GetVersionText().c_str());
	}
	else if (NSUDO_MESSAGE::SUCCESS != message)
	{
		std::wstring Buffer = g_ResourceManagement.GetMessageString(
			message);
		NSudoPrintMsg(
			g_ResourceManagement.Instance,
			nullptr,
			Buffer.c_str());
		return -1;
	}

	return 0;
}


#if defined(NSUDO_CUI_CONSOLE)
int main()
#endif
#if defined(NSUDO_CUI_WINDOWS) || defined(NSUDO_GUI_WINDOWS)
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
#endif
{
#if defined(NSUDO_CUI_WINDOWS) || defined(NSUDO_GUI_WINDOWS)
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);
#endif
	
	return NSudoMain();
}
