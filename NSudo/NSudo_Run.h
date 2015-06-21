void NSudo_Run(HWND hDlg , LPCWSTR szUser, LPCWSTR szPrivilege, LPCWSTR szMandatory, LPCWSTR szCMDLine)
{
	if (_wcsicmp(L"", szCMDLine) == 0)
	{
		MessageBoxW(hDlg, L"请在文本框输入你要执行的命令或者选择下拉框里面的常用命令", L"NSudo 3.0 M1", MB_ICONEXCLAMATION);
	}
	else
	{
		wchar_t szBuffer[260];

		GetSystemWindowsDirectoryW(szBuffer, 260); //获取Windows目录

		if (IsWoW64()) //判断是否在WoW64环境下
		{
			wcscat_s(szBuffer, 260, L"\\SysNative\\");  //64命令提示符路径
		}
		else
		{
			wcscat_s(szBuffer, 260, L"\\System32\\");  //32命令提示符路径
		}
		
		if (_wcsicmp(L"命令提示符", szCMDLine) == 0)
		{
			wcscat_s(szBuffer, 260, L"cmd.exe");
		}
		else if (_wcsicmp(L"PowerShell", szCMDLine) == 0)
		{
			wcscat_s(szBuffer, 260, L"WindowsPowerShell\\v1.0\\powershell.exe");
		}
		else if (_wcsicmp(L"PowerShell ISE", szCMDLine) == 0)
		{
			wcscat_s(szBuffer, 260, L"WindowsPowerShell\\v1.0\\powershell_ise.exe");
		}
		else
		{
			wcscpy_s(szBuffer, 260, szCMDLine);
		}

		HANDLE hUserToken = INVALID_HANDLE_VALUE;
		if (_wcsicmp(NSudo_Text_CU, szUser) == 0)
		{
			GetCurrentUserToken(&hUserToken);

			if (_wcsicmp(NSudo_Text_EnableAll, szPrivilege) == 0)
			{
				EnableAllTokenPrivileges(hUserToken);
			}
			else if (_wcsicmp(NSudo_Text_DisableAll, szPrivilege) == 0)
			{
				DisableAllTokenPrivileges(hUserToken);
			}

			if (_wcsicmp(NSudo_Text_Low, szMandatory) == 0)
			{
				SetTokenIntegrity(hUserToken, L"S-1-16-4096");
			}

			STARTUPINFOW StartupInfo = { 0 };
			PROCESS_INFORMATION ProcessInfo = { 0 };
			StartupInfo.lpDesktop = L"WinSta0\\Default";
			if (!CreateProcessAsUserW(hUserToken, NULL, szBuffer, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
			{
				ReturnMessage(L"进程创建失败");
			}

			CloseHandle(hUserToken);
		}
		else if (_wcsicmp(NSudo_Text_CUP, szUser) == 0)
		{
			HANDLE hToken;

			if (OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &hToken)) //打开当前进程令牌
			{
				DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, SecurityIdentification, TokenPrimary, &hUserToken);
				CloseHandle(hToken); // 关闭 hToken 句柄
			}
			
			if (_wcsicmp(NSudo_Text_EnableAll, szPrivilege) == 0)
			{
				EnableAllTokenPrivileges(hUserToken);
			}
			else if (_wcsicmp(NSudo_Text_DisableAll, szPrivilege) == 0)
			{
				DisableAllTokenPrivileges(hUserToken);
			}

			if (_wcsicmp(NSudo_Text_Low, szMandatory) == 0)
			{
				SetTokenIntegrity(hUserToken, L"S-1-16-4096");
			}
			else if (_wcsicmp(NSudo_Text_Medium, szMandatory) == 0)
			{
				SetTokenIntegrity(hUserToken, L"S-1-16-8192");
			}
			
			STARTUPINFOW StartupInfo = { 0 };
			PROCESS_INFORMATION ProcessInfo = { 0 };
			StartupInfo.lpDesktop = L"WinSta0\\Default";
			if (!CreateProcessAsUserW(hUserToken, NULL, szBuffer, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
			{
				ReturnMessage(L"进程创建失败");
			}

			CloseHandle(hUserToken);
		}
		else
		{
			LPVOID lpEnv = NULL;
			if (_wcsicmp(NSudo_Text_Sys, szUser) == 0)
			{
				if (GetSystemToken(&hUserToken))
				{
					DWORD dwWinLogonPID = GetWinLogonProcessID();
					if (dwWinLogonPID != -1)
					{
						CreateEnvironmentBlockFromProcess(dwWinLogonPID, &lpEnv);
					}
				}
			}
			else if (_wcsicmp(NSudo_Text_TI, szUser) == 0)
			{
				if (GetTIToken(&hUserToken))
				{
					DWORD dwTrustedInstallerPID = GetTrustedInstallerProcessID();
					if (dwTrustedInstallerPID != -1)
					{
						CreateEnvironmentBlockFromProcess(dwTrustedInstallerPID, &lpEnv);
					}
				}
			}

			if (_wcsicmp(NSudo_Text_EnableAll, szPrivilege) == 0)
			{
				EnableAllTokenPrivileges(hUserToken);
			}
			else if (_wcsicmp(NSudo_Text_DisableAll, szPrivilege) == 0)
			{
				DisableAllTokenPrivileges(hUserToken);
			}

			if (_wcsicmp(NSudo_Text_Low, szMandatory) == 0)
			{
				SetTokenIntegrity(hUserToken, L"S-1-16-4096");
			}
			else if (_wcsicmp(NSudo_Text_Medium, szMandatory) == 0)
			{
				SetTokenIntegrity(hUserToken, L"S-1-16-8192");
			}
			else if (_wcsicmp(NSudo_Text_High, szMandatory) == 0)
			{
				SetTokenIntegrity(hUserToken, L"S-1-16-12288");
			}
		
			STARTUPINFOW StartupInfo = { 0 };
			PROCESS_INFORMATION ProcessInfo = { 0 };
			StartupInfo.lpDesktop = L"WinSta0\\Default";
			if (!CreateProcessWithTokenW(
				hUserToken,
				LOGON_WITH_PROFILE,
				NULL,
				szBuffer,
				CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
				lpEnv,
				NULL,
				&StartupInfo,
				&ProcessInfo))
			{
				if (!CreateProcessAsUserW(
					hUserToken,
					NULL,
					szBuffer,
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

			CloseHandle(hUserToken);
		}		




		

	}
}