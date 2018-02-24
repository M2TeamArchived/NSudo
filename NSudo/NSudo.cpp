// NSudo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "NSudoVersion.h"

#include "M2DPIScaling.h"
#include "M2MessageDialog.h"
#include "NSudoResourceManagement.h"

#include "M2BaseHelpers.h"

void NSudoPrintMsg(
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ HWND hWnd,
	_In_ LPCWSTR lpContent)
{
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
}

HRESULT NSudoShowAboutDialog(
	_In_ HWND hwndParent)
{
	std::wstring DialogContent =
		g_ResourceManagement.GetLogoText() +
		g_ResourceManagement.GetUTF8WithBOMStringResources(IDR_String_CommandLineHelp) +
		g_ResourceManagement.GetUTF8WithBOMStringResources(IDR_String_Links);

	SetLastError(ERROR_SUCCESS);

	M2MessageDialog(
		g_ResourceManagement.Instance,
		hwndParent,
		MAKEINTRESOURCE(IDI_NSUDO),
		L"NSudo",
		DialogContent.c_str());

	return NSudoGetLastCOMError();
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

void SuGUIRun(
	_In_ HWND hDlg,
	_In_ LPCWSTR szUser,
	_In_ bool bEnableAllPrivileges,
	_In_ LPCWSTR szCMDLine)
{
	if (_wcsicmp(L"", szCMDLine) == 0)
	{
		std::wstring Buffer = g_ResourceManagement.GetMessageString(
			NSUDO_MESSAGE::INVALID_TEXTBOX_PARAMETER);
		NSudoPrintMsg(g_ResourceManagement.Instance, hDlg, Buffer.c_str());
	}
	else
	{
		std::vector<std::wstring> result;

		result.push_back(L"NSudo");

		std::wstring Buffer_TI =
			g_ResourceManagement.GetTranslation("TI");
		std::wstring Buffer_System =
			g_ResourceManagement.GetTranslation("System");
		std::wstring Buffer_CurrentProcess =
			g_ResourceManagement.GetTranslation("CurrentProcess");
		std::wstring Buffer_CurrentUser =
			g_ResourceManagement.GetTranslation("CurrentUser");

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

		NSUDO_MESSAGE message = NSudoCommandLineParser(true, true, result);
		if (NSUDO_MESSAGE::SUCCESS != message)
		{
			std::wstring Buffer = g_ResourceManagement.GetMessageString(
				message);
			NSudoPrintMsg(
				g_ResourceManagement.Instance,
				nullptr,
				Buffer.c_str());
		}
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

		SetWindowTextW(hDlg, g_ResourceManagement.GetVersionText().c_str());

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
			std::wstring Buffer = g_ResourceManagement.GetTranslation(x[i].ID);
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
			std::wstring Buffer = g_ResourceManagement.GetTranslation(UserNameID[i]);
			SendMessageW(this->m_hUserName, CB_INSERTSTRING, 0, (LPARAM)Buffer.c_str());
		}

		//设置默认项"TrustedInstaller"
		SendMessageW(this->m_hUserName, CB_SETCURSEL, 3, 0);

		try
		{
			for (auto it = g_ResourceManagement.ShortCutListV2.begin(); it != g_ResourceManagement.ShortCutListV2.end(); ++it)
			{
				SendMessageW(this->m_hszPath, CB_INSERTSTRING, 0, (LPARAM)M2MakeUTF16String(it.key()).c_str());
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
			NSudoShowAboutDialog(hDlg);
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

	std::vector<std::wstring> command_args = 
		g_ResourceManagement.GetCommandParameters();

	if (command_args.size() == 1)
	{
		CNSudoMainWindow(hInstance).Show();
	}
	else
	{
		NSUDO_MESSAGE message = NSudoCommandLineParser(
			g_ResourceManagement.IsElevated,
			true, 
			command_args);
		if (NSUDO_MESSAGE::NEED_TO_SHOW_COMMAND_LINE_HELP == message)
		{
			NSudoShowAboutDialog(nullptr);
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
	}

	return 0;
}
