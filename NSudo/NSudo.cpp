// NSudo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

HINSTANCE g_hInstance;

std::wstring nsudo_app_path;

nlohmann::json nsudo_config;
nlohmann::json nsudo_shortcut_list_v2;

nlohmann::json NSudo_String_Translations;

#include <Userenv.h>
#pragma comment(lib, "Userenv.lib")

#include "NSudoVersion.h"

#include "NSudoContextMenuManagement.h"
#include "M2DPIScaling.h"
#include "M2MessageDialog.h"
#include "M2ResourceManagement.h"

namespace ProjectInfo
{
	const wchar_t VersionText[] = L"M2-Team NSudo " NSUDO_VERSION_STRING;

	const wchar_t LogoText[] =
		L"M2-Team NSudo " NSUDO_VERSION_STRING L"\r\n"
		L"© M2-Team. All rights reserved.\r\n"
		L"\r\n";
}

std::wstring NSudoGetUTF8WithBOMStringResources(
	_In_ UINT uID)
{
	M2_RESOURCE_INFO ResourceInfo = { 0 };
	if (SUCCEEDED(M2LoadResource(
		&ResourceInfo,
		GetModuleHandleW(nullptr),
		L"String",
		MAKEINTRESOURCEW(uID))))
	{
		std::string RawString(
			reinterpret_cast<const char*>(ResourceInfo.Pointer),
			ResourceInfo.Size);
		// Raw string without the UTF-8 BOM. (0xEF,0xBB,0xBF)	
		return m2_base_utf8_to_utf16(RawString.c_str() + 3);
	}

	return L"";
}

void NSudoPrintMsg(
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ HWND hWnd,
	_In_ LPCWSTR lpContent)
{
	std::wstring DialogContent =
		std::wstring(ProjectInfo::LogoText) +
		lpContent +
		NSudoGetUTF8WithBOMStringResources(IDR_String_Links);

	M2MessageDialog(
		hInstance,
		hWnd,
		MAKEINTRESOURCE(IDI_NSUDO),
		L"NSudo",
		DialogContent.c_str());
}

std::wstring NSudoGetTranslation(
	_In_ const char* Key)
{
	return m2_base_utf8_to_utf16(
		NSudo_String_Translations[Key].get<std::string>());
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
	_Inout_ LPCWSTR lpCommandLine)
{
	STARTUPINFOW StartupInfo = { 0 };
	PROCESS_INFORMATION ProcessInfo = { 0 };

	std::wstring ComSpec(MAX_PATH, L'\0');
	GetEnvironmentVariableW(L"ComSpec", &ComSpec[0], (DWORD)ComSpec.size());
	ComSpec.resize(wcslen(ComSpec.c_str()));

	//生成命令行
	std::wstring final_command_line = L"/c start \"" + ComSpec + L"\" ";

	try
	{
		final_command_line += m2_base_utf8_to_utf16(
			nsudo_shortcut_list_v2[m2_base_utf16_to_utf8(lpCommandLine)].get<std::string>());
	}
	catch (const std::exception&)
	{
		final_command_line += lpCommandLine;
	}

	//设置进程所在桌面
	StartupInfo.lpDesktop = const_cast<LPWSTR>(L"WinSta0\\Default");

	LPVOID lpEnvironment = nullptr;

	BOOL result = FALSE;

	M2::CHandle hCurrentToken;
	if (OpenProcessToken(
		GetCurrentProcess(),
		MAXIMUM_ALLOWED,
		&hCurrentToken))
	{
		if (CreateEnvironmentBlock(&lpEnvironment, hCurrentToken, TRUE))
		{
			//启动进程
			result = CreateProcessAsUserW(
				hToken,
				ComSpec.c_str(),
				&final_command_line[0],
				nullptr,
				nullptr,
				FALSE,
				CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT,
				lpEnvironment,
				nsudo_app_path.c_str(),
				&StartupInfo,
				&ProcessInfo);

			//关闭句柄
			if (result)
			{
				CloseHandle(ProcessInfo.hProcess);
				CloseHandle(ProcessInfo.hThread);
			}

			DestroyEnvironmentBlock(lpEnvironment);
		}
	}

	//返回结果
	return result;
}

void NSudoBrowseDialog(
	_In_opt_ HWND hWnd,
	_Out_ wchar_t* szPath)
{
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrFile = szPath;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	GetOpenFileNameW(&ofn);
}

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
	if (!hModule) return NSudoGetLastCOMError();

	pFunc = (decltype(pFunc))GetProcAddress(hModule, "GetDpiForMonitor");
	if (!pFunc) return NSudoGetLastCOMError();

	hr = pFunc(hmonitor, dpiType, dpiX, dpiY);

	FreeLibrary(hModule);

	return hr;
}

class CNSudoMainWindow
{
private:
	static INT_PTR CALLBACK s_DialogProc(
		_In_ HWND hDlg,
		_In_ UINT uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam);

private:
	HICON m_hNSudoIcon = nullptr;
	HICON m_hWarningIcon = nullptr;

	int m_xDPI = USER_DEFAULT_SCREEN_DPI;
	int m_yDPI = USER_DEFAULT_SCREEN_DPI;

	HINSTANCE m_hInstance;

	HWND m_hUserName = nullptr;
	HWND m_hCheckBox = nullptr;
	HWND m_hszPath = nullptr;

private:
	INT_PTR DialogProc(
		_In_ HWND hDlg,
		_In_ UINT uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam);

public:
	CNSudoMainWindow(HINSTANCE hInstance = nullptr);
	~CNSudoMainWindow();

	INT_PTR Show();

	HRESULT ShowAboutDialog(
		_In_ HWND hwndParent);
};

CNSudoMainWindow::CNSudoMainWindow(HINSTANCE hInstance) :
	m_hInstance(hInstance)
{
}

CNSudoMainWindow::~CNSudoMainWindow()
{
}

INT_PTR CNSudoMainWindow::s_DialogProc(
	_In_ HWND hDlg,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	CNSudoMainWindow* pThis = nullptr;

	if (uMsg == WM_INITDIALOG)
	{
		pThis = reinterpret_cast<CNSudoMainWindow*>(lParam);

		SetWindowLongPtrW(hDlg, DWLP_USER,
			reinterpret_cast<LONG_PTR>(pThis));
	}
	else
	{
		pThis = reinterpret_cast<CNSudoMainWindow*>(
			GetWindowLongPtrW(hDlg, DWLP_USER));
	}

	if (pThis)
	{
		return pThis->DialogProc(hDlg, uMsg, wParam, lParam);
	}

	return FALSE;
}

INT_PTR CNSudoMainWindow::Show()
{
	M2EnablePerMonitorDialogScaling();

	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); // WM_COPYGLOBALDATA

	return DialogBoxParamW(
		this->m_hInstance,
		MAKEINTRESOURCEW(IDD_NSudoDlg),
		nullptr,
		this->s_DialogProc,
		reinterpret_cast<LPARAM>(this));
}

HRESULT CNSudoMainWindow::ShowAboutDialog(
	_In_ HWND hwndParent)
{
	std::wstring DialogContent =
		std::wstring(ProjectInfo::LogoText) +
		NSudoGetUTF8WithBOMStringResources(IDR_String_CommandLineHelp) +
		NSudoGetUTF8WithBOMStringResources(IDR_String_Links);

	SetLastError(ERROR_SUCCESS);

	M2MessageDialog(
		g_hInstance,
		hwndParent,
		MAKEINTRESOURCE(IDI_NSUDO),
		L"NSudo",
		DialogContent.c_str());

	return NSudoGetLastCOMError();
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

// 解析命令行
int NSudoCommandLineParser(
	_In_ bool bElevated,
	_In_ std::vector<std::wstring>& args)
{
	if (2 == args.size())
	{
		// 如果参数不满足条件，则返回错误
		if (!(args[1][0] == L'-' || args[1][0] == L'/'))
		{
			std::wstring Buffer = NSudoGetTranslation("Error.Arg");
			NSudoPrintMsg(g_hInstance, nullptr, Buffer.c_str());
			return -1;
		}

		const wchar_t* arg = args[1].c_str() + 1;

		// 如果参数是 /? 或 -?，则显示帮助
		if (0 == _wcsicmp(arg, L"?"))
		{
			CNSudoMainWindow(g_hInstance).ShowAboutDialog(nullptr);
			return 0;
		}

		CNSudoContextMenuManagement ContextMenuManagement;

		if (0 == _wcsicmp(arg, L"Install"))
		{
			// 如果参数是 /Install 或 -Install，则安装NSudo到系统
			if (ERROR_SUCCESS != ContextMenuManagement.Install())
			{
				ContextMenuManagement.Uninstall();
			}

			return 0;
		}
		else if (0 == _wcsicmp(arg, L"Uninstall"))
		{
			// 如果参数是 /Uninstall 或 -Uninstall，则移除安装到系统的NSudo
			ContextMenuManagement.Uninstall();
			return 0;
		}
		else
		{
			std::wstring Buffer = NSudoGetTranslation("Error.Arg");
			NSudoPrintMsg(g_hInstance, nullptr, Buffer.c_str());
			return -1;
		}
	}

	DWORD dwSessionID = (DWORD)-1;

	// 获取当前进程会话ID
	if (!NSudoGetCurrentProcessSessionID(&dwSessionID))
	{
		std::wstring Buffer = NSudoGetTranslation("Error.Sudo");
		NSudoPrintMsg(g_hInstance, nullptr, Buffer.c_str());
		return 0;
	}

	// 如果未提权或者模拟System权限失败
	if (!(bElevated && NSudoImpersonateAsSystem()))
	{
		std::wstring Buffer = NSudoGetTranslation("Error.NotHeld");
		NSudoPrintMsg(g_hInstance, nullptr, Buffer.c_str());
		return 0;
	}

	bool bArgErr = false;

	bool bGetUser = false;
	bool bGetPrivileges = false;
	bool bGetIntegrityLevel = false;

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
				OpenProcessToken(
					GetCurrentProcess(), MAXIMUM_ALLOWED, &hToken);
			}
			else if (0 == _wcsicmp(arg, L"U:D"))
			{
				if (OpenProcessToken(
					GetCurrentProcess(), MAXIMUM_ALLOWED, &hTempToken))
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
	}

	if (bArgErr)
	{
		std::wstring Buffer = NSudoGetTranslation("Error.Arg");
		NSudoPrintMsg(g_hInstance, nullptr, Buffer.c_str());
		return -1;
	}
	else
	{
		if (!bGetUser)
		{
			if (NSudoDuplicateServiceToken(
				L"TrustedInstaller",
				MAXIMUM_ALLOWED,
				nullptr,
				SecurityIdentification,
				TokenPrimary,
				&hToken))
			{
				if (SetTokenInformation(
					hToken,
					TokenSessionId,
					(PVOID)&dwSessionID,
					sizeof(DWORD)))
				{
					NSudoSetTokenAllPrivileges(hToken, true);
				}
			}
		}

		if (!SuCreateProcess(hToken, args[args.size() - 1].c_str()))
		{
			std::wstring Buffer = NSudoGetTranslation("Error.Sudo");
			NSudoPrintMsg(g_hInstance, nullptr, Buffer.c_str());
		}
	}

	RevertToSelf();

	return 0;
}

void SuGUIRun(
	_In_ HWND hDlg,
	_In_ LPCWSTR szUser,
	_In_ bool bEnableAllPrivileges,
	_In_ LPCWSTR szCMDLine)
{
	if (_wcsicmp(L"", szCMDLine) == 0)
	{
		std::wstring Buffer = NSudoGetTranslation("Error.TextBox");
		NSudoPrintMsg(g_hInstance, hDlg, Buffer.c_str());
	}
	else
	{
		std::vector<std::wstring> result;

		result.push_back(L"NSudo");

		std::wstring Buffer_TI =
			NSudoGetTranslation("TI");
		std::wstring Buffer_System =
			NSudoGetTranslation("System");
		std::wstring Buffer_CurrentProcess =
			NSudoGetTranslation("CurrentProcess");
		std::wstring Buffer_CurrentUser =
			NSudoGetTranslation("CurrentUser");

		// 获取用户令牌
		if (_wcsicmp(Buffer_TI.c_str(), szUser) == 0)
		{
			result.push_back(L"-U:T");
		}
		else if (_wcsicmp(Buffer_System.c_str(), szUser) == 0)
		{
			result.push_back(L"-U:S");
		}
		else if (_wcsicmp(Buffer_CurrentProcess.c_str(), szUser) == 0)
		{
			result.push_back(L"-U:P");
		}
		else if (_wcsicmp(Buffer_CurrentUser.c_str(), szUser) == 0)
		{
			result.push_back(L"-U:C");
		}

		// 如果勾选启用全部特权，则尝试对令牌启用全部特权
		if (bEnableAllPrivileges)
		{
			result.push_back(L"-P:E");
		}

		result.push_back(szCMDLine);

		NSudoCommandLineParser(true, result);
	}
}

INT_PTR CNSudoMainWindow::DialogProc(
	_In_ HWND hDlg,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (uMsg)
	{
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_INITDIALOG:
	{
		this->m_hUserName = GetDlgItem(hDlg, IDC_UserName);
		this->m_hCheckBox = GetDlgItem(hDlg, IDC_Check_EnableAllPrivileges);
		this->m_hszPath = GetDlgItem(hDlg, IDC_szPath);

		SetWindowTextW(hDlg, ProjectInfo::VersionText);

		struct { const char* ID; HWND hWnd; } x[] =
		{
			{ "EnableAllPrivileges" , this->m_hCheckBox },
		{ "WarningText" , GetDlgItem(hDlg, IDC_WARNINGTEXT) },
		{ "SettingsGroupText" ,GetDlgItem(hDlg, IDC_SETTINGSGROUPTEXT) },
		{ "Static.User",GetDlgItem(hDlg, IDC_STATIC_USER) },
		{ "Static.Open", GetDlgItem(hDlg, IDC_STATIC_OPEN) },
		{ "Button.About", GetDlgItem(hDlg, IDC_About) },
		{ "Button.Browse", GetDlgItem(hDlg, IDC_Browse) },
		{ "Button.Run", GetDlgItem(hDlg, IDC_Run) }
		};

		for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); ++i)
		{
			std::wstring Buffer = NSudoGetTranslation(x[i].ID);
			SetWindowTextW(x[i].hWnd, Buffer.c_str());
		}

		HRESULT hr = E_FAIL;

		hr = GetDpiForMonitorInternal(
			MonitorFromWindow(hDlg, MONITOR_DEFAULTTONEAREST),
			MDT_EFFECTIVE_DPI, (UINT*)&this->m_xDPI, (UINT*)&this->m_yDPI);
		if (hr != S_OK)
		{
			this->m_xDPI = GetDeviceCaps(GetDC(hDlg), LOGPIXELSX);
			this->m_yDPI = GetDeviceCaps(GetDC(hDlg), LOGPIXELSY);
		}

		this->m_hNSudoIcon = (HICON)LoadImageW(
			this->m_hInstance,
			MAKEINTRESOURCE(IDI_NSUDO),
			IMAGE_ICON,
			256,
			256,
			LR_SHARED);

		SendMessageW(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)this->m_hNSudoIcon);
		SendMessageW(hDlg, WM_SETICON, ICON_BIG, (LPARAM)this->m_hNSudoIcon);

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
			std::wstring Buffer = NSudoGetTranslation(UserNameID[i]);
			SendMessageW(this->m_hUserName, CB_INSERTSTRING, 0, (LPARAM)Buffer.c_str());
		}

		//设置默认项"TrustedInstaller"
		SendMessageW(this->m_hUserName, CB_SETCURSEL, 3, 0);

		try
		{
			for (auto it = nsudo_shortcut_list_v2.begin(); it != nsudo_shortcut_list_v2.end(); ++it)
			{
				SendMessageW(this->m_hszPath, CB_INSERTSTRING, 0, (LPARAM)m2_base_utf8_to_utf16(it.key()).c_str());
			}

		}
		catch (const std::exception&)
		{

		}

		return (INT_PTR)TRUE;
	}
	case WM_PAINT:
	{
		HDC hdc = GetDC(hDlg);
		RECT Rect = { 0 };

		GetClientRect(hDlg, &Rect);
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
			(Rect.bottom - Rect.top) - MulDiv(40, this->m_yDPI, USER_DEFAULT_SCREEN_DPI),
			this->m_hWarningIcon,
			MulDiv(24, this->m_xDPI, USER_DEFAULT_SCREEN_DPI),
			MulDiv(24, this->m_yDPI, USER_DEFAULT_SCREEN_DPI),
			0,
			nullptr,
			DI_NORMAL | DI_COMPAT);
		ReleaseDC(hDlg, hdc);

		break;
	}
	case WM_DPICHANGED:
	{
		this->m_xDPI = LOWORD(wParam);
		this->m_yDPI = HIWORD(wParam);

		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_Run:
		{
			std::wstring username(MAX_PATH, L'\0');
			std::wstring cmdline(MAX_PATH, L'\0');

			auto username_length = GetWindowTextW(this->m_hUserName, &username[0], (int)username.size());
			username.resize(username_length);
			auto cmdline_length = GetWindowTextW(this->m_hszPath, &cmdline[0], (int)cmdline.size());
			cmdline.resize(cmdline_length);

			SuGUIRun(
				hDlg,
				username.c_str(),
				(SendMessageW(this->m_hCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED),
				cmdline.c_str());
			break;
		}
		case IDC_About:
			this->ShowAboutDialog(hDlg);
			break;
		case IDC_Browse:
		{
			std::wstring buffer(MAX_PATH + 2, L'\0');

			buffer[0] = L'\"';

			NSudoBrowseDialog(hDlg, &buffer[1]);
			buffer.resize(wcslen(buffer.c_str()));

			buffer[buffer.size()] = L'\"';

			if (wcslen(buffer.c_str()) > 2)
				SetWindowTextW(this->m_hszPath, buffer.c_str());

			break;
		}
		default:
			break;
		}

		break;
	}
	case WM_DROPFILES:
	{
		std::wstring buffer(MAX_PATH + 2, L'\0');

		buffer[0] = L'\"';

		auto length = DragQueryFileW(
			(HDROP)wParam, 0, &buffer[1], (int)(buffer.size() - 2));
		buffer.resize(length + 1);

		if (!(GetFileAttributesW(&buffer[1]) & FILE_ATTRIBUTE_DIRECTORY))
		{
			buffer[buffer.size()] = L'\"';
			SetWindowTextW(this->m_hszPath, buffer.c_str());
		}

		DragFinish((HDROP)wParam);

		break;
	}
	default:
		break;
	}

	return FALSE;
}

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	std::vector<std::wstring> command_args = NSudoSplitCommandLine(GetCommandLineW());

	g_hInstance = hInstance;

	std::wstring nsudo_exe_path = M2GetCurrentModulePath();

	nsudo_app_path = nsudo_exe_path;
	wcsrchr(&nsudo_app_path[0], L'\\')[0] = L'\0';
	nsudo_app_path.resize(wcslen(nsudo_app_path.c_str()));

	NSudo_String_Translations = M2LoadJsonFromResource(
		GetModuleHandleW(nullptr),
		L"String",
		MAKEINTRESOURCEW(IDR_String_Translations))["Translations"];

	try
	{
		std::ifstream fs;
		fs.open(nsudo_app_path + L"\\NSudo.json");

		nsudo_config = nlohmann::json::parse(fs);
		nsudo_shortcut_list_v2 = nsudo_config["ShortCutList_V2"];
	}
	catch (const std::exception&)
	{

	}

	M2::CHandle CurrentToken;

	bool bElevated = false;
	if (OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &CurrentToken))
	{
		bElevated = NSudoSetTokenPrivilege(
			CurrentToken, SeDebugPrivilege, true);
	}

	if (command_args.size() == 1)
	{
		CNSudoMainWindow(hInstance).Show();
	}
	else
	{
		NSudoCommandLineParser(bElevated, command_args);
	}

	return 0;
}
