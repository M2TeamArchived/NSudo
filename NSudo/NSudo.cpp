// NSudo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "NSudoBase.h"

HINSTANCE g_hInstance;

HANDLE g_hOut;
HANDLE g_hIn;
HANDLE g_hErr;

wchar_t g_AppPath[260];
wchar_t g_ShortCutListPath[260];

int g_argc;
wchar_t** g_argv;

bool g_GUIMode;
bool g_Elevated;

void SuInitialize()
{
	SetProcessDPIAware();
	
	g_hInstance = GetModuleHandleW(NULL);

	g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	g_hIn = GetStdHandle(STD_INPUT_HANDLE);
	g_hErr = GetStdHandle(STD_ERROR_HANDLE);

	g_argv = CommandLineToArgvW(GetCommandLineW(), &g_argc);

	GetModuleFileNameW(NULL, g_AppPath, 260);
	wcsrchr(g_AppPath, L'\\')[0] = NULL;

	wcscpy_s(g_ShortCutListPath, 260, g_AppPath);
	wcscat_s(g_ShortCutListPath, 260, L"\\ShortCutList.ini");

	g_GUIMode = (g_argc == 1);

	g_Elevated = SuSetCurrentPsPrivilege(
		TokenPrivilegesList::SeDebugPrivilege, true);
}

void SuMUIPrintMsg(
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ HWND hWnd,
	_In_ UINT uID)
{
	DWORD result;
	wchar_t* szBuffer = (wchar_t*)MemAlloc(2048 * sizeof(wchar_t));
	if (szBuffer)
	{
		LoadStringW(hInstance, uID, szBuffer, 2048);
		if (g_GUIMode) MessageBoxW(hWnd, szBuffer, L"NSudo", NULL);
		else WriteConsoleW(g_hOut, szBuffer, wcslen(szBuffer), &result, NULL);
		MemFree(szBuffer);
	}
}

void SuMUIInsComboBox(
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ HWND hWnd,
	_In_ UINT uID)
{
	wchar_t* szBuffer = (wchar_t*)MemAlloc(260 * sizeof(wchar_t));
	if (szBuffer)
	{
		LoadStringW(hInstance, uID, szBuffer, 260);
		SendMessageW(hWnd, CB_INSERTSTRING, 0, (LPARAM)szBuffer);
		MemFree(szBuffer);
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
	wchar_t* szBuffer = (wchar_t*)MemAlloc(2048 * sizeof(wchar_t));
	if (szBuffer)
	{
		LoadStringW(hInstance, uID, szBuffer, 2048);		
		bRet = (_wcsicmp(szBuffer, lpText) == 0);
		MemFree(szBuffer);
	}
	return bRet;
}


void SuGUIRun(
	_In_ HWND hDlg,
	_In_ LPCWSTR szUser,
	_In_ LPCWSTR szPrivilege,
	_In_ LPCWSTR szMandatory,
	_In_ LPCWSTR szCMDLine)
{
	if (_wcsicmp(L"", szCMDLine) == 0)
	{
		SuMUIPrintMsg(g_hInstance, hDlg, IDS_ERRTEXTBOX);
	}
	else
	{
		wchar_t szBuffer[512] = { NULL };

		wchar_t szPath[260];
		DWORD dwLength = GetPrivateProfileStringW(szCMDLine, L"CommandLine", L"", szPath, 260, g_ShortCutListPath);

		if (wcscmp(szPath, L"") != 0)
		{
			wcscat_s(szBuffer, 512, szPath);
		}
		else
		{
			wcscat_s(szBuffer, 512, szCMDLine);
		}

		HANDLE hUserToken = INVALID_HANDLE_VALUE;
		HANDLE hTempToken = INVALID_HANDLE_VALUE;

		if (SuMUICompare(g_hInstance,IDS_TI,szUser))
		{
			SuGetTrustedInstallerToken(&hUserToken);
		}
		else if (SuMUICompare(g_hInstance, IDS_SYSTEM, szUser))
		{
			SuGetSystemToken(&hUserToken);
		}
		else if (SuMUICompare(g_hInstance, IDS_CURRENTPROCESS, szUser))
		{
			if (NT_SUCCESS(SuGetCurrentPsToken(&hTempToken)))
			{
				SuDuplicateToken(hTempToken, &hUserToken);
				NtClose(hTempToken);
				hTempToken = NULL;
			}
		}
		else if (SuMUICompare(g_hInstance, IDS_CURRENTUSER, szUser))
		{
			SuGetCurrentUserToken(&hUserToken);
		}
		else if (SuMUICompare(g_hInstance, IDS_CURRENTPROCESSDROP, szUser))
		{
			if (NT_SUCCESS(SuGetCurrentPsToken(&hTempToken)))
			{
				SuCreateLUAToken(hTempToken, &hUserToken);
				NtClose(hTempToken);
				hTempToken = NULL;
			}
		}

		if (SuMUICompare(g_hInstance, IDS_ENABLEALL, szPrivilege))
		{
			SuEnableAllTokenPrivileges(hUserToken);
		}
		else if (SuMUICompare(g_hInstance, IDS_REMOVEMAX, szPrivilege))
		{
			if (NT_SUCCESS(SuRemoveMaximumTokenPrivileges(
				hUserToken, &hTempToken)))
			{
				NtClose(hUserToken);
				hUserToken = hTempToken;
				hTempToken = NULL;
			}
		}

		if (SuMUICompare(g_hInstance, IDS_ILLOW, szMandatory))
		{
			SuSetTokenIL(hUserToken, IntegrityLevel::Low);
		}
		else if (SuMUICompare(g_hInstance, IDS_ILMEDIUM, szMandatory))
		{
			SuSetTokenIL(hUserToken, IntegrityLevel::Medium);
		}
		else if (SuMUICompare(g_hInstance, IDS_ILHIGH, szMandatory))
		{
			SuSetTokenIL(hUserToken, IntegrityLevel::High);
		}
		else if (SuMUICompare(g_hInstance, IDS_ILSYSTEM, szMandatory))
		{
			SuSetTokenIL(hUserToken, IntegrityLevel::System);
		}

		if (SuImpersonateSystemToken())
		{
			STARTUPINFOW StartupInfo = { 0 };
			PROCESS_INFORMATION ProcessInfo = { 0 };
			wchar_t szBuf[512], szSystemDirectory[260];

			//设置进程所在桌面
			StartupInfo.lpDesktop = L"WinSta0\\Default";

			//获取系统目录
			GetSystemDirectoryW(szSystemDirectory, 260);

			//生成命令行	
			wsprintfW(szBuf,
				L"%s\\cmd.exe /c start \"%s\\cmd.exe\" %s",
				szSystemDirectory, szSystemDirectory, szBuffer);

			//启动进程并返回
			if (!CreateProcessAsUserW(
				hUserToken,
				NULL,
				szBuf,
				nullptr,
				nullptr,
				FALSE,
				CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT,
				NULL,
				NULL,
				&StartupInfo,
				&ProcessInfo))
			{
				if (!CreateProcessWithTokenW(
					hUserToken,
					LOGON_WITH_PROFILE,
					NULL,
					szBuf,
					CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT,
					NULL,
					NULL,
					&StartupInfo,
					&ProcessInfo))
				{
					SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRSUDO);
				}
			}

			RevertToSelf();
		}

		CloseHandle(hUserToken);
	}
}


INT_PTR CALLBACK DialogCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hUserName = GetDlgItem(hDlg, IDC_UserName);
	HWND hTokenPrivilege = GetDlgItem(hDlg, IDC_TokenPrivilege);
	HWND hMandatoryLabel = GetDlgItem(hDlg, IDC_MandatoryLabel);
	HWND hszPath = GetDlgItem(hDlg, IDC_szPath);

	wchar_t szCMDLine[260], szUser[260], szPrivilege[260], szMandatory[260], szBuffer[260];
	
	switch (message)
	{
	case WM_INITDIALOG:
		// Show NSudo Logo
		SendMessageW(
			GetDlgItem(hDlg, IDC_NSudoLogo),
			STM_SETIMAGE,
			IMAGE_ICON,
			LPARAM(LoadImageW(
				g_hInstance,
				MAKEINTRESOURCE(IDI_NSUDO),
				IMAGE_ICON,
				0,
				0,
				LR_COPYFROMRESOURCE)));

		//Show Warning Icon
		SendMessageW(
			GetDlgItem(hDlg, IDC_Icon),
			STM_SETIMAGE,
			IMAGE_ICON,
			LPARAM(LoadIconW(NULL, IDI_WARNING)));

		SuMUIInsComboBox(g_hInstance, hUserName, IDS_TI);
		SuMUIInsComboBox(g_hInstance, hUserName, IDS_SYSTEM);
		SuMUIInsComboBox(g_hInstance, hUserName, IDS_CURRENTPROCESS);
		SuMUIInsComboBox(g_hInstance, hUserName, IDS_CURRENTUSER);
		SuMUIInsComboBox(g_hInstance, hUserName, IDS_CURRENTPROCESSDROP);
		SendMessageW(hUserName, CB_SETCURSEL, 4, 0); //设置默认项"TrustedInstaller"

		SuMUIInsComboBox(g_hInstance, hTokenPrivilege, IDS_DEFAULT);
		SuMUIInsComboBox(g_hInstance, hTokenPrivilege, IDS_ENABLEALL);
		SuMUIInsComboBox(g_hInstance, hTokenPrivilege, IDS_REMOVEMAX);
		SendMessageW(hTokenPrivilege, CB_SETCURSEL, 2, 0); //设置默认项"默认"

		SuMUIInsComboBox(g_hInstance, hMandatoryLabel, IDS_ILLOW);
		SuMUIInsComboBox(g_hInstance, hMandatoryLabel, IDS_ILMEDIUM);
		SuMUIInsComboBox(g_hInstance, hMandatoryLabel, IDS_ILHIGH);
		SuMUIInsComboBox(g_hInstance, hMandatoryLabel, IDS_ILSYSTEM);
		SuMUIInsComboBox(g_hInstance, hMandatoryLabel, IDS_DEFAULT);
		SendMessageW(hMandatoryLabel, CB_SETCURSEL, 0, 0); //设置默认项"默认"

		{
			wchar_t szItem[260], szBuf[32768];
			DWORD dwLength = GetPrivateProfileSectionNamesW(szBuf, 32768, g_ShortCutListPath);

			for (DWORD i = 0, j = 0; i < dwLength; i++, j++)
			{
				if (szBuf[i] != NULL)
				{
					szItem[j] = szBuf[i];
				}
				else
				{
					szItem[j] = NULL;
					SendMessageW(hszPath, CB_INSERTSTRING, 0, (LPARAM)szItem);
					j = -1;
				}
			}
		}
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_Run:
			GetDlgItemTextW(hDlg, IDC_UserName, szUser, sizeof(szUser));
			GetDlgItemTextW(hDlg, IDC_TokenPrivilege, szPrivilege, sizeof(szPrivilege));
			GetDlgItemTextW(hDlg, IDC_MandatoryLabel, szMandatory, sizeof(szMandatory));
			GetDlgItemTextW(hDlg, IDC_szPath, szCMDLine, sizeof(szCMDLine));

			SuGUIRun(hDlg, szUser, szPrivilege, szMandatory, szCMDLine);
			break;
		case IDC_About:
			SuMUIPrintMsg(g_hInstance, hDlg, IDS_ABOUT);
			break;
		case IDC_Browse:
			szBuffer[0] = NULL;
			NSudoBrowseDialog(hDlg, szBuffer);
			SetDlgItemTextW(hDlg, IDC_szPath, szBuffer);		
			break;
		}
		break;
	case WM_SYSCOMMAND:
		switch (LOWORD(wParam))
		{
		case SC_CLOSE:
			PostQuitMessage(0);
			break;
		}
		break;
	}

	return 0;
}


int main()
{
	SuInitialize();

	if (g_GUIMode)
	{
		if (g_Elevated)
		{
			FreeConsole();

			DialogBoxParamW(
				g_hInstance,
				MAKEINTRESOURCEW(IDD_NSudoDlg),
				NULL,
				DialogCallBack,
				0L);
		}
		else
		{
			wchar_t szExePath[260];

			GetModuleFileNameW(NULL, szExePath, 260);

			ShellExecuteW(NULL, L"runas", szExePath, NULL, NULL, SW_SHOW);
			return 0;
		}
	}
	else
	{
		SuMUIPrintMsg(g_hInstance, NULL, IDS_ABOUT);

		bool bUserArgEnable = true;
		bool bCMDLineArgEnable = true;

		wchar_t *szBuffer = NULL;

		HANDLE hUserToken = INVALID_HANDLE_VALUE;
		HANDLE hTempToken = INVALID_HANDLE_VALUE;

		for (int i = 1; i < g_argc; i++)
		{
			//判断是参数还是要执行的命令行或常见任务
			if (g_argv[i][0] == L'-')
			{
				//如果未提权且参数不是显示帮助
				if (!g_Elevated && g_argv[i][1] != '?')
				{
					SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRNOTHELD);
					return 0;
				}
				
				switch (g_argv[i][1])
				{
				case '?':
					SuMUIPrintMsg(g_hInstance, NULL, IDS_HELP);
					return 0;
				case 'U':
				case 'u':
				{
					if (g_argv[i][2] = L':')
					{
						switch (g_argv[i][3])
						{
						case 'T':
						case 't':
							SuGetTrustedInstallerToken(&hUserToken);
							bUserArgEnable = false;
							break;
						case 'S':
						case 's':
							SuGetSystemToken(&hUserToken);
							bUserArgEnable = false;
							break;
						case 'C':
						case 'c':
							SuGetCurrentUserToken(&hUserToken);
							bUserArgEnable = false;
							break;
						case 'P':
						case 'p':
							if (NT_SUCCESS(SuGetCurrentPsToken(&hTempToken)))
							{
								SuDuplicateToken(hTempToken, &hUserToken);
								NtClose(hTempToken);
								hTempToken = NULL;
							}
							bUserArgEnable = false;
							break;
						case 'D':
						case 'd':
							if (NT_SUCCESS(SuGetCurrentPsToken(&hTempToken)))
							{
								SuCreateLUAToken(hTempToken, &hUserToken);
								NtClose(hTempToken);
								hTempToken = NULL;
							}
							bUserArgEnable = false;
							break;
						default:
							break;
						}
					}
					break;
				}
				case 'P':
				case 'p':
				{
					if (g_argv[i][2] = L':')
					{
						switch (g_argv[i][3])
						{
						case 'E':
						case 'e':
							SuEnableAllTokenPrivileges(hUserToken);
							break;
						case 'D':
						case 'd':
							if (NT_SUCCESS(SuRemoveMaximumTokenPrivileges(
								hUserToken, &hTempToken)))
							{
								NtClose(hUserToken);
								hUserToken = hTempToken;
								hTempToken = NULL;
							}
							break;
						default:
							break;
						}
					}
					break;
				}
				case 'M':
				case 'm':
				{
					if (g_argv[i][2] = L':')
					{
						switch (g_argv[i][3])
						{
						case 'S':
						case 's':
							SuSetTokenIL(hUserToken, IntegrityLevel::System);
							break;
						case 'H':
						case 'h':
							SuSetTokenIL(hUserToken, IntegrityLevel::High);
							break;
						case 'M':
						case 'm':
							SuSetTokenIL(hUserToken, IntegrityLevel::Medium);
							break;
						case 'L':
						case 'l':
							SuSetTokenIL(hUserToken, IntegrityLevel::Low);
							break;				 
						default:
							break;
						}
					}
					break;
				}
				default:
					break;
				}
			}
			else 
			{
				if (bCMDLineArgEnable)
				{
					wchar_t szPath[260];

					DWORD dwLength = GetPrivateProfileStringW(g_argv[i],
						L"CommandLine", L"", szPath, 260, g_ShortCutListPath);

					wcscmp(szPath, L"") != 0 ?
						szBuffer = szPath : szBuffer = g_argv[i];

					if (szBuffer) bCMDLineArgEnable = false;
				}				
			}
		}

		if (bUserArgEnable || bCMDLineArgEnable)
		{
			SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRARG);
			return -1;
		}
		else
		{
			if (SuImpersonateSystemToken())
			{
				STARTUPINFOW StartupInfo = { 0 };
				PROCESS_INFORMATION ProcessInfo = { 0 };
				wchar_t szBuf[512], szSystemDirectory[260];

				//设置进程所在桌面
				StartupInfo.lpDesktop = L"WinSta0\\Default";

				//获取系统目录
				GetSystemDirectoryW(szSystemDirectory, 260);

				//生成命令行	
				wsprintfW(szBuf,
					L"%s\\cmd.exe /c \"%s\"",
					szSystemDirectory, szBuffer);

				//启动进程并返回
				if (!CreateProcessAsUserW(
					hUserToken,
					NULL,
					szBuf,
					nullptr,
					nullptr,
					FALSE,
					CREATE_UNICODE_ENVIRONMENT,
					NULL,
					NULL,
					&StartupInfo,
					&ProcessInfo))
				{
					if (!CreateProcessWithTokenW(
						hUserToken,
						LOGON_WITH_PROFILE,
						NULL,
						szBuf,
						CREATE_UNICODE_ENVIRONMENT,
						NULL,
						NULL,
						&StartupInfo,
						&ProcessInfo))
					{
						SuMUIPrintMsg(g_hInstance, NULL, IDS_ERRSUDO);
					}
				}

				RevertToSelf();
			}
		}

		NtClose(hUserToken);		
	}
	
	return 0;
}