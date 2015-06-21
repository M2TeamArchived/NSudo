//NSudo 3.0 (Build 825)
//(C) 2015 NSudo Team. All rights reserved.

#include "stdafx.h"

#include <windows.h>

#include<Userenv.h>
#pragma comment(lib,"Userenv.lib")

#include "..\\NSudoAPI\\NSudoAPI.h"
#pragma comment(lib,"NSudoAPI.lib")

#define NSudo_Title L"NSudo"
#define NSudo_Version L"3.0 Internal Alpha 1(Build 811)"
#define NSudo_CopyRight L"\xA9 2015 NSudo Team. All rights reserved."

#define ReturnMessage(lpText) MessageBoxW(NULL, (lpText), NSudo_Title, NULL)


#define LOGONID_CURRENT     ((ULONG)-1)
#define SERVERNAME_CURRENT  ((HANDLE)NULL)

typedef	enum _WINSTATIONINFOCLASS
{
	WinStationCreateData,
	WinStationConfiguration,
	WinStationPdParams,
	WinStationWd,
	WinStationPd,
	WinStationPrinter,
	WinStationClient,
	WinStationModules,
	WinStationInformation,
	WinStationTrace,
	WinStationBeep,
	WinStationEncryptionOff,
	WinStationEncryptionPerm,
	WinStationNtSecurity,
	WinStationUserToken,
	WinStationUnused1,
	WinStationVideoData,
	WinStationInitialProgram,
	WinStationCd,
	WinStationSystemTrace,
	WinStationVirtualData,
	WinStationClientData,
	WinStationSecureDesktopEnter,
	WinStationSecureDesktopExit,
	WinStationLoadBalanceSessionTarget,
	WinStationLoadIndicator,
	WinStationShadowInfo,
	WinStationDigProductId,
	WinStationLockedState,
	WinStationRemoteAddress,
	WinStationIdleTime,
	WinStationLastReconnectType,
	WinStationDisallowAutoReconnect,
	WinStationUnused2,
	WinStationUnused3,
	WinStationUnused4,
	WinStationUnused5,
	WinStationReconnectedFromId,
	WinStationEffectsPolicy,
	WinStationType,
	WinStationInformationEx
} WINSTATIONINFOCLASS;

typedef struct _WINSTATIONINFORMATIONW {
	BYTE Reserved2[70];
	ULONG LogonId;
	BYTE Reserved3[1140];
} WINSTATIONINFORMATIONW, *PWINSTATIONINFORMATIONW;

typedef struct _WINSTATIONUSERTOKEN {
	HANDLE ProcessId;
	HANDLE ThreadId;
	HANDLE UserToken;
} WINSTATIONUSERTOKEN,
*PWINSTATIONUSERTOKEN;

BOOLEAN WinStationQueryInformationW(
	_In_   HANDLE hServer,
	_In_   ULONG LogonId,
	_In_   WINSTATIONINFOCLASS WinStationInformationClass,
	_Out_  PVOID pWinStationInformation,
	_In_   ULONG WinStationInformationLength,
	_Out_  PULONG pReturnLength
	)
{
	HINSTANCE hInstWinSta = LoadLibraryW(L"winsta.dll");
	if (hInstWinSta == NULL) return FALSE;

	typedef BOOLEAN(WINAPI * PWINSTATIONQUERYINFORMATIONW)(
		HANDLE, ULONG, WINSTATIONINFOCLASS, PVOID, ULONG, PULONG);

	PWINSTATIONQUERYINFORMATIONW WinStationQueryInformationW =
		(PWINSTATIONQUERYINFORMATIONW)GetProcAddress(hInstWinSta, "WinStationQueryInformationW");

	if (WinStationQueryInformationW == NULL) return FALSE;

	return WinStationQueryInformationW(
		hServer,
		LogonId,
		WinStationInformationClass,
		pWinStationInformation,
		WinStationInformationLength,
		pReturnLength);
}

void xGetTIToken()
{
	//获取当前会话ID下的winlogon的PID
	DWORD dwTIPID = GetTrustedInstallerProcessID();

	if (dwTIPID == -1)
	{
		ReturnMessage(L"TrustedInstaller.exe进程PID获取失败");
		return;
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwTIPID);
	if (hProc != NULL)
	{
		HANDLE hToken, hDupToken;
		if (OpenProcessToken(hProc, TOKEN_DUPLICATE | TOKEN_QUERY, &hToken))
		{
			if (DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, SecurityIdentification, TokenPrimary, &hDupToken))
			{
				LPVOID lpEnv; //环境块
				if (CreateEnvironmentBlock(&lpEnv, hToken, 1))
				{
					EnableAllTokenPrivileges(hDupToken);

					STARTUPINFOW StartupInfo = { 0 };
					PROCESS_INFORMATION ProcessInfo = { 0 };
					StartupInfo.lpDesktop = L"WinSta0\\Default";
					if (!CreateProcessWithTokenW(
						hDupToken,
						LOGON_WITH_PROFILE,
						NULL,
						L"C:\\Windows\\System32\\cmd.exe",
						CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
						lpEnv,
						NULL,
						&StartupInfo,
						&ProcessInfo))
					{
						if (!CreateProcessAsUserW(hDupToken,
							NULL,
							L"C:\\Windows\\notepad.exe",
							NULL,
							NULL,
							NULL,
							CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
							lpEnv,
							NULL,
							&StartupInfo,
							&ProcessInfo))
						{
							ReturnMessage(L"进程创建失败");
						}
					}
					DestroyEnvironmentBlock(lpEnv);
				}
				else ReturnMessage(L"TrustedInstaller.exe进程环境块创建失败");
				CloseHandle(hDupToken);
			}
			else ReturnMessage(L"TrustedInstaller.exe进程句柄令牌复制失败");
			CloseHandle(hToken);
		}
		else ReturnMessage(L"TrustedInstaller.exe进程句柄令牌打开失败");
		CloseHandle(hProc);
	}
	else ReturnMessage(L"TrustedInstaller.exe进程句柄打开失败");
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (!(SetCurrentProcessPrivilege(SE_ASSIGNPRIMARYTOKEN_NAME, true)
		&& SetCurrentProcessPrivilege(SE_INCREASE_QUOTA_NAME, true)
		&& SetCurrentProcessPrivilege(SE_DEBUG_NAME, true)))
	{
		ReturnMessage(L"进程调试权限获取失败");
		return -1;
	}

	HANDLE hSystemToken;
	if (GetTIToken(&hSystemToken))
	{
		if (ImpersonateLoggedOnUser(hSystemToken))
		{
			DWORD dwTIPID = GetTrustedInstallerProcessID();

			if (dwTIPID == -1)
			{
				ReturnMessage(L"TrustedInstaller.exe进程PID获取失败");
				return 0;
			}

			HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwTIPID);
			if (hProc != NULL)
			{
				HANDLE hToken, hDupToken;
				if (OpenProcessToken(hProc, TOKEN_DUPLICATE | TOKEN_QUERY, &hToken))
				{
					if (DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, SecurityIdentification, TokenPrimary, &hDupToken))
					{
						LPVOID lpEnv; //环境块
						if (CreateEnvironmentBlock(&lpEnv, hToken, 1))
						{
							EnableAllTokenPrivileges(hDupToken);

							STARTUPINFOW StartupInfo = { 0 };
							PROCESS_INFORMATION ProcessInfo = { 0 };
							StartupInfo.lpDesktop = L"WinSta0\\Default";
							if (!CreateProcessWithTokenW(
								hSystemToken,
								LOGON_WITH_PROFILE,
								NULL,
								L"C:\\Windows\\System32\\cmd.exe",
								CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
								lpEnv,
								NULL,
								&StartupInfo,
								&ProcessInfo))
							{
								if (!CreateProcessAsUserW(hSystemToken,
									NULL,
									L"C:\\Windows\\notepad.exe",
									NULL,
									NULL,
									NULL,
									CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
									lpEnv,
									NULL,
									&StartupInfo,
									&ProcessInfo))
								{
									ReturnMessage(L"进程创建失败");
								}
							}
							DestroyEnvironmentBlock(lpEnv);
						}
						else ReturnMessage(L"TrustedInstaller.exe进程环境块创建失败");
						CloseHandle(hDupToken);
					}
					else ReturnMessage(L"TrustedInstaller.exe进程句柄令牌复制失败");
					CloseHandle(hToken);
				}
				else ReturnMessage(L"TrustedInstaller.exe进程句柄令牌打开失败");
				CloseHandle(hProc);
			}
			else ReturnMessage(L"TrustedInstaller.exe进程句柄打开失败");
			RevertToSelf();
		}
		CloseHandle(hSystemToken);
	}
}

void Backup()
{
	HANDLE hSystemToken;
	if (GetSystemToken(&hSystemToken))
	{
		if (ImpersonateLoggedOnUser(hSystemToken))
		{
			WINSTATIONUSERTOKEN WinStaUserToken = { 0 };
			DWORD ccbInfo = NULL;

			WinStationQueryInformationW(SERVERNAME_CURRENT, LOGONID_CURRENT, WinStationUserToken, &WinStaUserToken, sizeof(WINSTATIONUSERTOKEN), &ccbInfo);

			HRESULT hr = GetLastError();

			STARTUPINFOW StartupInfo = { 0 };
			PROCESS_INFORMATION ProcessInfo = { 0 };
			StartupInfo.lpDesktop = L"WinSta0\\Default";

			wchar_t szCMDLine[] = L"cmd /c start cmd";

			if (CreateProcessAsUserW(WinStaUserToken.UserToken, NULL, szCMDLine, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
			{

			}

			/*HANDLE hDupToken;

			if (DuplicateTokenEx(WinStaUserToken.UserToken, TOKEN_ALL_ACCESS, NULL, SecurityIdentification, TokenPrimary, &hDupToken))
			{
			//LPVOID lpEnv; //环境块
			//if (CreateEnvironmentBlock(&lpEnv, hToken, 1))
			//{
			EnableAllTokenPrivileges(hDupToken);

			STARTUPINFOW StartupInfo = { 0 };
			PROCESS_INFORMATION ProcessInfo = { 0 };
			StartupInfo.lpDesktop = L"WinSta0\\Default";
			if (!CreateProcessWithTokenW(
			hDupToken,
			LOGON_WITH_PROFILE,
			NULL,
			L"C:\\Windows\\System32\\cmd.exe",
			CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
			NULL,
			NULL,
			&StartupInfo,
			&ProcessInfo))
			{
			if (!CreateProcessAsUserW(hDupToken,
			NULL,
			L"C:\\Windows\\notepad.exe",
			NULL,
			NULL,
			NULL,
			CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
			NULL,
			NULL,
			&StartupInfo,
			&ProcessInfo))
			{
			ReturnMessage(L"进程创建失败");
			}
			}
			//DestroyEnvironmentBlock(lpEnv);
			//}
			//else ReturnMessage(L"TrustedInstaller.exe进程环境块创建失败");
			CloseHandle(hDupToken);
			}*/

			//GetTIToken();

			RevertToSelf();

			ReturnMessage(L"OK");
		}

		CloseHandle(hSystemToken);
	}
}