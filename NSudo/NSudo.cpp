// NSudo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace M2;

HINSTANCE g_hInstance;

wchar_t g_ExePath[MAX_PATH];
wchar_t g_AppPath[MAX_PATH];
wchar_t g_ShortCutListPath[MAX_PATH];

/*

*/

namespace ProjectInfo
{
	wchar_t VersionText[] = L"M2-Team NSudo 4.3.1703.25";
}

//HRESULT WINAPI SuExecuteCommandLine(
	//_In_ LPCWSTR CommandLine)
//{

//}

bool SuCreateProcess(
	_In_opt_ HANDLE hToken,
	_Inout_ LPWSTR lpCommandLine)
{
	bool bRet = true;

	STARTUPINFOW StartupInfo = { 0 };
	PROCESS_INFORMATION ProcessInfo = { 0 };
	wchar_t szBuf[512];
	wchar_t szSystemDirectory[MAX_PATH];

	//设置进程所在桌面
	StartupInfo.lpDesktop = L"WinSta0\\Default";

	//获取系统目录
	GetSystemDirectoryW(szSystemDirectory, MAX_PATH);

	//生成命令行	
	wsprintfW(szBuf,
		L"%s\\cmd.exe /c start \"%s\\cmd.exe\" %s",
		szSystemDirectory, szSystemDirectory, lpCommandLine);

	HRESULT hr = SuCreateProcess(
		hToken,
		nullptr,
		szBuf,
		CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT,
		nullptr,
		g_AppPath,
		&StartupInfo,
		&ProcessInfo);

	//启动进程
	bRet = SUCCEEDED(hr);

	//关闭句柄
	if (bRet)
	{
		NtClose(ProcessInfo.hProcess);
		NtClose(ProcessInfo.hThread);
	}

	//返回结果
	return bRet;
}

void SuMUIPrintMsg(
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ HWND hWnd,
	_In_ UINT uID)
{
	CPtr<wchar_t*> szBuffer;
	if (szBuffer.Alloc(2048 * sizeof(wchar_t)))
	{
		LoadStringW(hInstance, uID, szBuffer, 2048);
		TaskDialog(
			hWnd, hInstance, L"NSudo", nullptr, szBuffer, 0, nullptr, nullptr);
	}
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
	bool bRet = false;
	CPtr<wchar_t*> szBuffer;
	if (szBuffer.Alloc(2048 * sizeof(wchar_t)))
	{
		LoadStringW(hInstance, uID, szBuffer, 2048);		
		bRet = (_wcsicmp(szBuffer, lpText) == 0);
	}
	return bRet;
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
		wchar_t *szBuffer = nullptr;

		wchar_t szPath[MAX_PATH];
		GetPrivateProfileStringW(
			szCMDLine, L"CommandLine", L"", szPath, MAX_PATH, g_ShortCutListPath);

		szBuffer = (wcscmp(szPath, L"") != 0 ? szPath : const_cast<wchar_t*>(szCMDLine));

		// 模拟为System权限
		if (NT_SUCCESS(SuImpersonateAsSystem()))
		{
			HANDLE hToken = INVALID_HANDLE_VALUE;

			// 获取用户令牌
			if (SuMUICompare(g_hInstance, IDS_TI, szUser))
			{
				if (NT_SUCCESS(SuGetServiceProcessTokenCopy(
					L"TrustedInstaller",
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken)))
				{
					DWORD dwSessionID = M2GetCurrentSessionID();
					NtSetInformationToken(
						hToken,
						TokenSessionId,
						(PVOID)&dwSessionID,
						sizeof(DWORD));
				}
			}
			else if (SuMUICompare(g_hInstance, IDS_SYSTEM, szUser))
			{
				SuGetSystemTokenCopy(
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken);
			}
			else if (SuMUICompare(g_hInstance, IDS_CURRENTPROCESS, szUser))
			{
				SuOpenCurrentProcessToken(&hToken, MAXIMUM_ALLOWED);
			}
			else if (SuMUICompare(g_hInstance, IDS_CURRENTUSER, szUser))
			{
				SuGetSessionTokenCopy(
					M2GetCurrentSessionID(),
					MAXIMUM_ALLOWED,
					nullptr,
					SecurityIdentification,
					TokenPrimary,
					&hToken);
			}

			// 如果勾选启用全部特权，则对令牌启用全部特权
			if (hToken != INVALID_HANDLE_VALUE && bEnableAllPrivileges)
				SuSetTokenAllPrivileges(hToken, true);	
			
			if (!(hToken != INVALID_HANDLE_VALUE && 
				SuCreateProcess(hToken, szBuffer)))
			{
				SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRSUDO);
			}

			NtClose(hToken);

			SuRevertToSelf();
		}	
	}
}

HRESULT SuShowAboutDialog(
	_In_ HWND hwndParent,
	_In_ HINSTANCE hInstance)
{
	TASKDIALOGCONFIG config = { 0 };

	config.cbSize = sizeof(config);
	config.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION | TDF_ENABLE_HYPERLINKS;
	config.hwndParent = hwndParent;
	config.hInstance = hInstance;
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

#include <ShellScalingApi.h>

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4191) // 从“type of expression”到“type required”的不安全转换(等级 3)
#endif

inline HRESULT GetDpiForMonitorInternal(
	_In_ HMONITOR hmonitor,
	_In_ MONITOR_DPI_TYPE dpiType,
	_Out_ UINT *dpiX,
	_Out_ UINT *dpiY)
{
	PVOID pDllHandle = nullptr;
	decltype(GetDpiForMonitor)* pFunc = nullptr;
	HRESULT hr = E_NOINTERFACE;
	
	do
	{
		if (!NT_SUCCESS(M2LoadModule(pDllHandle, L"SHCore.dll")))
			break;

		if (!NT_SUCCESS(M2GetProcedureAddress(
			pFunc, pDllHandle, "GetDpiForMonitor")))
			break;

		hr = pFunc(hmonitor, dpiType, dpiX, dpiY);

	} while (false);

	M2FreeModule(pDllHandle);
	return hr;
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


// 全局变量
int g_xDPI = USER_DEFAULT_SCREEN_DPI;
int g_yDPI = USER_DEFAULT_SCREEN_DPI;

HICON hNSudoIcon = nullptr;
HICON hWarningIcon = nullptr;

INT_PTR CALLBACK DialogCallBack(
	HWND hDlg, 
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	HWND hUserName = GetDlgItem(hDlg, IDC_UserName);
	HWND hCheckBox = GetDlgItem(hDlg, IDC_Check_EnableAllPrivileges);
	HWND hszPath = GetDlgItem(hDlg, IDC_szPath);

	wchar_t szCMDLine[MAX_PATH], szUser[260], szBuffer[512];
	
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_INITDIALOG:
	{
		SetWindowTextW(hDlg, ProjectInfo::VersionText);

		LoadStringW(g_hInstance, IDS_ENABLEALLPRIVILEGES, szBuffer, 512);
		SetWindowTextW(hCheckBox, szBuffer);

		LoadStringW(g_hInstance, IDS_WARNINGTEXT, szBuffer, 512);
		SetWindowTextW(GetDlgItem(hDlg, IDC_WARNINGTEXT), szBuffer);

		LoadStringW(g_hInstance, IDS_SETTINGSGROUPTEXT, szBuffer, 512);
		SetWindowTextW(GetDlgItem(hDlg, IDC_SETTINGSGROUPTEXT), szBuffer);

		LoadStringW(g_hInstance, IDS_STATIC_USER, szBuffer, 512);
		SetWindowTextW(GetDlgItem(hDlg, IDC_STATIC_USER), szBuffer);

		LoadStringW(g_hInstance, IDS_STATIC_OPEN, szBuffer, 512);
		SetWindowTextW(GetDlgItem(hDlg, IDC_STATIC_OPEN), szBuffer);

		LoadStringW(g_hInstance, IDS_BUTTON_ABOUT, szBuffer, 512);
		SetWindowTextW(GetDlgItem(hDlg, IDC_About), szBuffer);

		LoadStringW(g_hInstance, IDS_BUTTON_BROWSE, szBuffer, 512);
		SetWindowTextW(GetDlgItem(hDlg, IDC_Browse), szBuffer);

		LoadStringW(g_hInstance, IDS_BUTTON_RUN, szBuffer, 512);
		SetWindowTextW(GetDlgItem(hDlg, IDC_Run), szBuffer);

		HRESULT hr = E_FAIL;

		hr = GetDpiForMonitorInternal(
			MonitorFromWindow(hDlg, MONITOR_DEFAULTTONEAREST),
			MDT_EFFECTIVE_DPI, (UINT*)&g_xDPI, (UINT*)&g_yDPI);
		if (hr != S_OK)
		{
			g_xDPI = GetDeviceCaps(GetDC(hDlg), LOGPIXELSX);
			g_yDPI = GetDeviceCaps(GetDC(hDlg), LOGPIXELSY);
		}

		hNSudoIcon = (HICON)LoadImageW(
			g_hInstance,
			MAKEINTRESOURCE(IDI_NSUDO),
			IMAGE_ICON,
			256,
			256,
			LR_SHARED);

		SendMessageW(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hNSudoIcon);
		SendMessageW(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hNSudoIcon);

		hWarningIcon = (HICON)LoadImageW(
			nullptr,
			IDI_WARNING,
			IMAGE_ICON,
			0,
			0,
			LR_SHARED);

		LoadStringW(g_hInstance, IDS_TI, szBuffer, 512);
		SendMessageW(hUserName, CB_INSERTSTRING, 0, (LPARAM)szBuffer);

		LoadStringW(g_hInstance, IDS_SYSTEM, szBuffer, 512);
		SendMessageW(hUserName, CB_INSERTSTRING, 0, (LPARAM)szBuffer);

		LoadStringW(g_hInstance, IDS_CURRENTPROCESS, szBuffer, 512);
		SendMessageW(hUserName, CB_INSERTSTRING, 0, (LPARAM)szBuffer);

		LoadStringW(g_hInstance, IDS_CURRENTUSER, szBuffer, 512);
		SendMessageW(hUserName, CB_INSERTSTRING, 0, (LPARAM)szBuffer);

		//设置默认项"TrustedInstaller"
		SendMessageW(hUserName, CB_SETCURSEL, 3, 0);

		wchar_t szItem[260], szBuf[32768];
		DWORD dwLength = GetPrivateProfileSectionNamesW(
			szBuf, 32768, g_ShortCutListPath);

		for (DWORD i = 0, j = 0; i < dwLength; i++, j++)
		{
			if (szBuf[i] != L'\0')
			{
				szItem[j] = szBuf[i];
			}
			else
			{
				szItem[j] = L'\0';
				SendMessageW(hszPath, CB_INSERTSTRING, 0, (LPARAM)szItem);
				j = (DWORD)-1;
			}
		}

		return (INT_PTR)TRUE;
	}	
	case WM_PAINT:
	{
		HDC hdc = GetDC(hDlg);
		RECT Rect = { 0 };

		GetClientRect(hDlg, &Rect);
		DrawIconEx(hdc, MulDiv(16, g_xDPI, USER_DEFAULT_SCREEN_DPI), MulDiv(16, g_yDPI, USER_DEFAULT_SCREEN_DPI), hNSudoIcon, MulDiv(64, g_xDPI, USER_DEFAULT_SCREEN_DPI), MulDiv(64, g_yDPI, USER_DEFAULT_SCREEN_DPI), 0, nullptr, DI_NORMAL | DI_COMPAT);
		DrawIconEx(hdc, MulDiv(16, g_xDPI, USER_DEFAULT_SCREEN_DPI), (Rect.bottom - Rect.top) - MulDiv(40, g_yDPI, USER_DEFAULT_SCREEN_DPI), hWarningIcon, MulDiv(24, g_xDPI, USER_DEFAULT_SCREEN_DPI), MulDiv(24, g_yDPI, USER_DEFAULT_SCREEN_DPI), 0, nullptr, DI_NORMAL | DI_COMPAT);
		ReleaseDC(hDlg, hdc);
		
		break;
	}
	case WM_DPICHANGED:
	{
		g_xDPI = LOWORD(wParam);
		g_yDPI = HIWORD(wParam);

		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_Run:
			GetDlgItemTextW(hDlg, IDC_UserName, szUser, sizeof(szUser));
			GetDlgItemTextW(hDlg, IDC_szPath, szCMDLine, sizeof(szCMDLine));

			SuGUIRun(
				hDlg, 
				szUser, 
				(SendMessageW(hCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED),
				szCMDLine);
			break;
		case IDC_About:
			SuShowAboutDialog(hDlg, g_hInstance);
			break;
		case IDC_Browse:		
			szBuffer[1] = L'\0';
			NSudoBrowseDialog(hDlg, &szBuffer[1]);

			if (szBuffer[1] != L'\0')
			{
				szBuffer[0] = L'\"';
				wcscat_s(szBuffer, 512, L"\"");

				SetDlgItemTextW(hDlg, IDC_szPath, szBuffer);
			}

			break;
		}
		break;
	case WM_DROPFILES:
	{	
		DragQueryFileW(
			(HDROP)wParam,
			0,
			&szBuffer[1], 
			sizeof(szBuffer) - sizeof(wchar_t));

		if (!(GetFileAttributesW(&szBuffer[1]) & FILE_ATTRIBUTE_DIRECTORY))
		{
			szBuffer[0] = L'\"';
			wcscat_s(szBuffer, 512, L"\"");

			SetDlgItemTextW(hDlg, IDC_szPath, szBuffer);
		}

		DragFinish((HDROP)wParam);

		break;
	}
	}

	return 0;
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

	int argc = 0;
	wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	g_hInstance = hInstance;

	GetModuleFileNameW(nullptr, g_ExePath, MAX_PATH);

	wcscpy_s(g_AppPath, MAX_PATH, g_ExePath);
	wcsrchr(g_AppPath, L'\\')[0] = L'\0';

	wcscpy_s(g_ShortCutListPath, MAX_PATH, g_AppPath);
	wcscat_s(g_ShortCutListPath, MAX_PATH, L"\\ShortCutList.ini");

	HANDLE hCurrentToken = INVALID_HANDLE_VALUE;

	bool bElevated = false;
	if (NT_SUCCESS(SuOpenCurrentProcessToken(&hCurrentToken, MAXIMUM_ALLOWED)))
	{
		bElevated = (SuSetTokenPrivilege(
			hCurrentToken, SeDebugPrivilege, true) == STATUS_SUCCESS);
	}

	if (argc == 1)
	{
		if (bElevated)
		{
			EnablePerMonitorDialogScaling();

			ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
			ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); // WM_COPYGLOBALDATA

			DialogBoxParamW(
				g_hInstance,
				MAKEINTRESOURCEW(IDD_NSudoDlg),
				nullptr,
				DialogCallBack,
				0L);
		}
		else
		{				
			SHELLEXECUTEINFOW ExecInfo = { 0 };
			ExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
			ExecInfo.lpFile = g_ExePath;
			ExecInfo.lpVerb = L"runas";
			ExecInfo.nShow = SW_NORMAL;

			ShellExecuteExW(&ExecInfo);

			return (int)M2GetLastError();
		}
	}
	else
	{
		// 如果参数是 /? 或 -?,则显示帮助
		if (argc == 2 && 
			(argv[1][0] == L'-' || argv[1][0] == L'/') && 
			argv[1][1] == '?')
		{
			SuShowAboutDialog(nullptr, g_hInstance);
			return 0;
		}

		// 如果未提权或者模拟System权限失败
		if (!(bElevated && NT_SUCCESS(SuImpersonateAsSystem())))
		{
			SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRNOTHELD);
			return 0;
		}

		bool bCMDLineArgEnable = true;
		bool bArgErr = false;

		wchar_t *szBuffer = nullptr;

		HANDLE hToken = INVALID_HANDLE_VALUE;
		HANDLE hTempToken = INVALID_HANDLE_VALUE;

		for (int i = 1; i < argc; i++)
		{
			//判断是参数还是要执行的命令行或常见任务
			if (argv[i][0] == L'-' || argv[i][0] == L'/')
			{
				switch (argv[i][1])
				{			
				case 'U':
				case 'u':
				{
					if (argv[i][2] == L':')
					{
						switch (argv[i][3])
						{
						case 'T':
						case 't':
							if (NT_SUCCESS(SuGetServiceProcessTokenCopy(
								L"TrustedInstaller",
								MAXIMUM_ALLOWED,
								nullptr,
								SecurityIdentification,
								TokenPrimary,
								&hToken)))
							{
								DWORD dwSessionID = M2GetCurrentSessionID();
								NtSetInformationToken(
									hToken,
									TokenSessionId,
									(PVOID)&dwSessionID,
									sizeof(DWORD));
							}
							break;
						case 'S':
						case 's':
							SuGetSystemTokenCopy(
								MAXIMUM_ALLOWED,
								nullptr,
								SecurityIdentification,
								TokenPrimary,
								&hToken);
							break;
						case 'C':
						case 'c':
							SuGetSessionTokenCopy(
								M2GetCurrentSessionID(),
								MAXIMUM_ALLOWED,
								nullptr,
								SecurityIdentification,
								TokenPrimary,
								&hToken);
							break;
						case 'P':
						case 'p':
							SuOpenCurrentProcessToken(&hToken, MAXIMUM_ALLOWED);
							break;
						case 'D':
						case 'd':
							if (NT_SUCCESS(SuOpenCurrentProcessToken(
								&hTempToken, MAXIMUM_ALLOWED)))
							{
								SuCreateLUAToken(&hToken, hTempToken);
								NtClose(hTempToken);
							}
							break;
						default:
							bArgErr = true;
							break;
						}
					}
					break;
				}
				case 'P':
				case 'p':
				{
					if (hToken != INVALID_HANDLE_VALUE)
					{
						if (argv[i][2] == L':')
						{
							switch (argv[i][3])
							{
							case 'E':
							case 'e':
								SuSetTokenAllPrivileges(hToken, true);
								break;
							case 'D':
							case 'd':
								SuSetTokenAllPrivileges(hToken, false);
								break;
							default:
								bArgErr = true;
								break;
							}
						}
					}
					break;
				}
				case 'M':
				case 'm':
				{
					if (hToken != INVALID_HANDLE_VALUE)
					{
						if (argv[i][2] == L':')
						{
							switch (argv[i][3])
							{
							case 'S':
							case 's':
								SuSetTokenIntegrityLevel(hToken, SystemLevel);
								break;
							case 'H':
							case 'h':
								SuSetTokenIntegrityLevel(hToken, HighLevel);
								break;
							case 'M':
							case 'm':
								SuSetTokenIntegrityLevel(hToken, MediumLevel);
								break;
							case 'L':
							case 'l':
								SuSetTokenIntegrityLevel(hToken, LowLevel);
								break;
							default:
								bArgErr = true;
								break;
							}
						}
					}

					break;
				}
				default:
					bArgErr = true;
					break;
				}
			}
			else
			{
				if (bCMDLineArgEnable)
				{
					wchar_t szPath[MAX_PATH];

					GetPrivateProfileStringW(
						argv[i], L"CommandLine", L"", 
						szPath, MAX_PATH, g_ShortCutListPath);

					wcscmp(szPath, L"") != 0 ?
						szBuffer = szPath : szBuffer = (argv[i]);

					if (szBuffer) bCMDLineArgEnable = false;
				}
			}
		}

		if (hToken == INVALID_HANDLE_VALUE)
		{
			if (NT_SUCCESS(SuGetServiceProcessTokenCopy(
				L"TrustedInstaller",
				MAXIMUM_ALLOWED,
				nullptr,
				SecurityIdentification,
				TokenPrimary,
				&hToken)))
			{
				DWORD dwSessionID = M2GetCurrentSessionID();
				if (NT_SUCCESS(NtSetInformationToken(
					hToken,
					TokenSessionId,
					(PVOID)&dwSessionID,
					sizeof(DWORD))))
				{		
					SuSetTokenAllPrivileges(hToken, true);
				}		
			}
		}

		if (bCMDLineArgEnable || bArgErr)
		{
			SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRARG);
			return -1;
		}
		else
		{
			if (hToken == INVALID_HANDLE_VALUE ||
				!SuCreateProcess(hToken, szBuffer))
			{
				SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRSUDO);
			}
		}

		NtClose(hToken);

		SuRevertToSelf();
	}

	return 0;
}
