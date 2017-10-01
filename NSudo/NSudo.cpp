// NSudo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

HINSTANCE g_hInstance;

std::wstring nsudo_app_path;

nlohmann::json nsudo_config;
nlohmann::json nsudo_shortcut_list_v2;

#include <Userenv.h>
#pragma comment(lib, "Userenv.lib")

#include "Version.h"

namespace ProjectInfo
{
	wchar_t VersionText[] = L"M2-Team NSudo " NSUDO_VERSION_STRING;
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
	StartupInfo.lpDesktop = L"WinSta0\\Default";

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

void SuMUIPrintMsg(
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ HWND hWnd,
	_In_ UINT uID)
{
	std::wstring buffer(2048, L'\0');

	LoadStringW(hInstance, uID, &buffer[0], 2048);
	TaskDialog(
		hWnd, hInstance, L"NSudo", nullptr, buffer.c_str(), 0, nullptr, nullptr);
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

bool SuMUICompare(
	_In_opt_ HINSTANCE hInstance,
	_In_ UINT uID,
	_In_ LPCWSTR lpText)
{
	std::wstring buffer(2048, L'\0');

	LoadStringW(hInstance, uID, &buffer[0], 2048);

	return (_wcsicmp(buffer.c_str(), lpText) == 0);
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

typedef INT(WINAPI *PFN_EnablePerMonitorDialogScaling)();

/*
EnablePerMonitorDialogScaling函数为指定对话框启用Per-Monitor DPI Aware支
持。
The EnablePerMonitorDialogScaling function enables the Per-Monitor DPI
Aware for the specified dialog.

你需要在Windows 10 Threshold 1 及以后的版本使用该函数。
You need to use this function in Windows 10 Threshold 1 or later.
*/
FORCEINLINE INT EnablePerMonitorDialogScaling()
{
	HMODULE hModule = nullptr;
	PFN_EnablePerMonitorDialogScaling pFunc = nullptr;

	hModule = GetModuleHandleW(L"user32.dll");
	if (!hModule) return -1;

	pFunc = (decltype(pFunc))GetProcAddress(hModule, (LPCSTR)2577);
	if (!pFunc) return -1;

	return pFunc();
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
	EnablePerMonitorDialogScaling();

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
	TASKDIALOGCONFIG config = { 0 };

	config.cbSize = sizeof(config);
	config.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION | TDF_ENABLE_HYPERLINKS;
	config.hwndParent = hwndParent;
	config.hInstance = this->m_hInstance;
	config.pszMainIcon = MAKEINTRESOURCEW(IDI_NSUDO);
	config.pszMainInstruction = ProjectInfo::VersionText;
	config.pszContent = MAKEINTRESOURCE(IDS_ABOUT);
	config.pszWindowTitle = L"NSudo";
	config.pfCallback = [](
		_In_ HWND hwnd,
		_In_ UINT msg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam,
		_In_ LONG_PTR lpRefData)
		-> HRESULT
	{
		UNREFERENCED_PARAMETER(hwnd);
		UNREFERENCED_PARAMETER(wParam);
		UNREFERENCED_PARAMETER(lpRefData);

		if (TDN_HYPERLINK_CLICKED == msg)
		{
			SHELLEXECUTEINFOW ExecInfo = { 0 };
			ExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
			ExecInfo.lpVerb = L"open";
			ExecInfo.nShow = SW_SHOW;

			if (_wcsicmp((LPCWSTR)lParam, L"NSudo://OfficalQQGroupJoinLink") == 0)
			{
				ExecInfo.lpFile = L"http://shang.qq.com/wpa/qunwpa?idkey=29940ed5c8b2363efcf8a1c376f280c4a46c4e356d5533af48541418ff13ada2";
			}
			else
			{
				ExecInfo.lpFile = (LPCWSTR)lParam;
			}

			ShellExecuteExW(&ExecInfo);
		}

		return S_OK;
	};

	return TaskDialogIndirect(&config, nullptr, nullptr, nullptr);
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
	// 如果参数是 /? 或 -?,则显示帮助
	if (args.size() == 2 &&
		(args[1][0] == L'-' || args[1][0] == L'/') &&
		args[1][1] == '?')
	{
		CNSudoMainWindow(g_hInstance).ShowAboutDialog(nullptr);
		return 0;
	}

	DWORD dwSessionID = (DWORD)-1;

	// 获取当前进程会话ID
	if (!NSudoGetCurrentProcessSessionID(&dwSessionID))
	{
		SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRSUDO);
		return 0;
	}

	// 如果未提权或者模拟System权限失败
	if (!(bElevated && NSudoImpersonateAsSystem()))
	{
		SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRNOTHELD);
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
		const wchar_t* arg = args[i].c_str() + 1;

		// 如果参数不满足条件，则返回错误
		if (!(wcslen(arg) == 3 && arg[1] == L':'))
		{
			bArgErr = true;
			break;
		}

		if (!bGetUser && (arg[0] == L'U' || arg[0] == L'u'))
		{
			if (arg[2] == L'T' || arg[2] == L't')
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
			else if (arg[2] == L'S' || arg[2] == L's')
			{
				NSudoDuplicateSystemToken(
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken);
			}
			else if (arg[2] == L'C' || arg[2] == L'c')
			{
				NSudoDuplicateSessionToken(
					dwSessionID,
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken);
			}
			else if (arg[2] == L'P' || arg[2] == L'p')
			{
				OpenProcessToken(
					GetCurrentProcess(), MAXIMUM_ALLOWED, &hToken);
			}
			else if (arg[2] == L'D' || arg[2] == L'd')
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

		if (!bGetPrivileges && (arg[0] == L'P' || arg[0] == L'p'))
		{
			if (arg[2] == L'E' || arg[2] == L'e')
			{
				NSudoSetTokenAllPrivileges(hToken, true);
			}
			else if (arg[2] == L'D' || arg[2] == L'd')
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

		if (!bGetIntegrityLevel && (arg[0] == L'M' || arg[0] == L'm'))
		{
			if (arg[2] == L'S' || arg[2] == L's')
			{
				NSudoSetTokenIntegrityLevel(hToken, SystemLevel);
			}
			else if (arg[2] == L'H' || arg[2] == L'h')
			{
				NSudoSetTokenIntegrityLevel(hToken, HighLevel);
			}
			else if (arg[2] == L'M' || arg[2] == L'm')
			{
				NSudoSetTokenIntegrityLevel(hToken, MediumLevel);
			}
			else if (arg[2] == L'L' || arg[2] == L'l')
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
		SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRARG);
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
			SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRSUDO);
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
		SuMUIPrintMsg(g_hInstance, hDlg, IDS_ERRTEXTBOX);
	}
	else
	{
		std::vector<std::wstring> result;

		result.push_back(L"NSudo");

		M2::CHandle hToken;

		// 获取用户令牌
		if (SuMUICompare(g_hInstance, IDS_TI, szUser))
		{
			result.push_back(L"-U:T");
		}
		else if (SuMUICompare(g_hInstance, IDS_SYSTEM, szUser))
		{
			result.push_back(L"-U:S");
		}
		else if (SuMUICompare(g_hInstance, IDS_CURRENTPROCESS, szUser))
		{
			result.push_back(L"-U:P");
		}
		else if (SuMUICompare(g_hInstance, IDS_CURRENTUSER, szUser))
		{
			result.push_back(L"-U:C");
		}

		// 如果勾选启用全部特权，则尝试对令牌启用全部特权
		if (hToken != INVALID_HANDLE_VALUE && bEnableAllPrivileges)
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

		struct { UINT uID; HWND hWnd; } x[] =
		{
			{ IDS_ENABLEALLPRIVILEGES , this->m_hCheckBox },
			{ IDS_WARNINGTEXT , GetDlgItem(hDlg, IDC_WARNINGTEXT) },
			{ IDS_SETTINGSGROUPTEXT ,GetDlgItem(hDlg, IDC_SETTINGSGROUPTEXT) },
			{ IDS_STATIC_USER,GetDlgItem(hDlg, IDC_STATIC_USER) },
			{ IDS_STATIC_OPEN, GetDlgItem(hDlg, IDC_STATIC_OPEN) },
			{ IDS_BUTTON_ABOUT, GetDlgItem(hDlg, IDC_About) },
			{ IDS_BUTTON_BROWSE, GetDlgItem(hDlg, IDC_Browse) },
			{ IDS_BUTTON_RUN, GetDlgItem(hDlg, IDC_Run) }
		};

		for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); ++i)
		{
			std::wstring buffer(512, L'\0');
			auto length = LoadStringW(this->m_hInstance, x[i].uID, &buffer[0], (int)buffer.size());
			buffer.resize(length);
			SetWindowTextW(x[i].hWnd, buffer.c_str());
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

		UINT y[] = { IDS_TI ,IDS_SYSTEM ,IDS_CURRENTPROCESS ,IDS_CURRENTUSER };

		for (size_t i = 0; i < sizeof(y) / sizeof(y[0]); ++i)
		{
			std::wstring buffer(512, L'\0');
			auto length = LoadStringW(this->m_hInstance, y[i], &buffer[0], (int)buffer.size());
			buffer.resize(length);
			SendMessageW(this->m_hUserName, CB_INSERTSTRING, 0, (LPARAM)buffer.c_str());
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

	std::wstring nsudo_exe_path;

	nsudo_exe_path.resize(MAX_PATH);
	GetModuleFileNameW(nullptr, &nsudo_exe_path[0], MAX_PATH);

	nsudo_app_path = nsudo_exe_path;
	wcsrchr(&nsudo_app_path[0], L'\\')[0] = L'\0';
	nsudo_app_path.resize(wcslen(nsudo_app_path.c_str()));

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
