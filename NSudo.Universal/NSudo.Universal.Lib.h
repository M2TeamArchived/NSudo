/*

*/

#pragma once

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <Windows.h>

#include <sddl.h>
#include <AccCtrl.h>
#include <Aclapi.h>

#include <VersionHelpers.h>

#include <UserEnv.h>
#pragma comment(lib,"userenv.lib")


#include "..\NSudo.Universal\NSudo.Universal.Lib.KUserSharedData.h"
#include "..\NSudo.Universal\NSudo.Universal.Lib.NativeAPI.h"
#include "..\NSudo.Universal\NSudo.Universal.Lib.WinSta.h"

//创建一个令牌副本
bool NSudoDuplicateToken(
	_In_ HANDLE hExistingToken,
	_Outptr_ PHANDLE phNewToken)
{
	SECURITY_QUALITY_OF_SERVICE SecurityQualityOfService =
	{
		sizeof(SECURITY_QUALITY_OF_SERVICE), // Length
		SecurityIdentification, // ImpersonationLevel
		FALSE, // ContextTrackingMode
		FALSE // EffectiveOnly
	};
	OBJECT_ATTRIBUTES ObjectAttributes =
	{
		sizeof(OBJECT_ATTRIBUTES), // Length
		NULL, // RootDirectory
		NULL, // ObjectName
		NULL, // Attributes
		NULL, // SecurityDescriptor
		&SecurityQualityOfService // SecurityQualityOfService
	};

	NTSTATUS status = NtDuplicateToken(hExistingToken, TOKEN_ALL_ACCESS, &ObjectAttributes, 0, TokenPrimary, phNewToken);
	if (!NT_SUCCESS(status))
	{
		RtlSetLastWin32Error(RtlNtStatusToDosError(status));
		return false;
	}

	return true;
}

//获取一个进程的PID
DWORD NSudoGetProcessID(LPCWSTR lpProcessName, bool bUnderCurrentSessionID)
{
	DWORD dwPID = -1 /*进程ID*/ /*, dwUserSessionId = 0 */ /*会话ID*/;

	DWORD dwReturnLength = 0;
	NtQuerySystemInformation(SystemProcessInformation, NULL, NULL, &dwReturnLength);
	LPVOID lpBuffer = HeapAlloc(GetProcessHeap(), 0, dwReturnLength);
	if (lpBuffer)
	{
		PSYSTEM_PROCESS_INFORMATION pSPI = (PSYSTEM_PROCESS_INFORMATION)lpBuffer;
		if (NT_SUCCESS(NtQuerySystemInformation(SystemProcessInformation, pSPI, dwReturnLength, &dwReturnLength)))
		{
			while (pSPI->NextEntryOffset != 0)
			{
				if (_wcsicmp(lpProcessName, pSPI->ImageName.Buffer) == 0) //寻找%lpProcessName%进程
				{
					if (bUnderCurrentSessionID && pSPI->SessionId != USER_SHARED_DATA->ActiveConsoleId) continue; //判断是否是当前用户ID
					dwPID = HandleToUlong(pSPI->UniqueProcessId);
					break;
				}
				pSPI = (PSYSTEM_PROCESS_INFORMATION)((char *)pSPI + pSPI->NextEntryOffset);
			}
		}
		HeapFree(GetProcessHeap(), 0, lpBuffer);
	}

	return dwPID;
}

//根据令牌创建进程（对CreateProcess和CreateEnvironmentBlock的封装，可能需要SE_ASSIGNPRIMARYTOKEN_NAME特权）
bool NSudoCreateProcess(HANDLE hToken, LPCWSTR lpCommandLine)
{
	STARTUPINFOW StartupInfo = { 0 };
	PROCESS_INFORMATION ProcessInfo = { 0 };
	StartupInfo.lpDesktop = L"WinSta0\\Default";

	wchar_t szBuffer[512], szSystemDirectory[260];
	GetSystemDirectoryW(szSystemDirectory, 260);
	wsprintfW(szBuffer, L"%s\\cmd.exe /c start \"%s\\cmd.exe\" %s", szSystemDirectory, szSystemDirectory, lpCommandLine);

	return CreateProcessWithTokenW(
		hToken,
		LOGON_WITH_PROFILE,
		NULL,
		szBuffer,
		CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT,
		NULL,
		NULL,
		&StartupInfo,
		&ProcessInfo);
}

//设置令牌权限
bool SetTokenPrivilege(HANDLE TokenHandle, LPCWSTR lpName, bool bEnable)
{
	TOKEN_PRIVILEGES TP;

	TP.PrivilegeCount = 1;
	TP.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : NULL;

	if (LookupPrivilegeValueW(NULL, lpName, &TP.Privileges[0].Luid))
	{
		AdjustTokenPrivileges(TokenHandle, FALSE, &TP, sizeof(TP), NULL, NULL);
		if (GetLastError() == ERROR_SUCCESS) return true;
	}

	return false;
}

//获取当前进程的令牌
bool NSudoGetCurrentProcessToken(PHANDLE hNewToken)
{
	return OpenProcessToken(NtCurrentProcess(), MAXIMUM_ALLOWED, hNewToken);
}


//设置当前进程令牌权限
bool SetCurrentProcessPrivilege(LPCWSTR lpName, bool bEnable)
{
	bool bRet = false;
	HANDLE hCurrentProcessToken;
	if (NSudoGetCurrentProcessToken(&hCurrentProcessToken))
	{
		bRet = SetTokenPrivilege(hCurrentProcessToken, lpName, bEnable);
		NtClose(hCurrentProcessToken);
	}
	return bRet;
}

//一键开启或关闭所有特权
void NSudoAdjustAllTokenPrivileges(HANDLE TokenHandle, bool bEnable)
{
	wchar_t *PrivilegeList[] =
	{
		SE_CREATE_TOKEN_NAME,
		SE_ASSIGNPRIMARYTOKEN_NAME,
		SE_LOCK_MEMORY_NAME,
		SE_INCREASE_QUOTA_NAME,
		SE_UNSOLICITED_INPUT_NAME,
		SE_MACHINE_ACCOUNT_NAME,
		SE_TCB_NAME,
		SE_SECURITY_NAME,
		SE_TAKE_OWNERSHIP_NAME,
		SE_LOAD_DRIVER_NAME,
		SE_SYSTEM_PROFILE_NAME,
		SE_SYSTEMTIME_NAME,
		SE_PROF_SINGLE_PROCESS_NAME,
		SE_INC_BASE_PRIORITY_NAME,
		SE_CREATE_PAGEFILE_NAME,
		SE_CREATE_PERMANENT_NAME,
		SE_BACKUP_NAME,
		SE_RESTORE_NAME,
		SE_SHUTDOWN_NAME,
		SE_DEBUG_NAME,
		SE_AUDIT_NAME,
		SE_SYSTEM_ENVIRONMENT_NAME,
		SE_CHANGE_NOTIFY_NAME,
		SE_REMOTE_SHUTDOWN_NAME,
		SE_UNDOCK_NAME,
		SE_SYNC_AGENT_NAME,
		SE_ENABLE_DELEGATION_NAME,
		SE_MANAGE_VOLUME_NAME,
		SE_IMPERSONATE_NAME,
		SE_CREATE_GLOBAL_NAME,
		SE_TRUSTED_CREDMAN_ACCESS_NAME,
		SE_RELABEL_NAME,
		SE_INC_WORKING_SET_NAME,
		SE_TIME_ZONE_NAME,
		SE_CREATE_SYMBOLIC_LINK_NAME
	};

	for (int i = 0; i < sizeof(PrivilegeList) / sizeof(wchar_t*); i++)
	{
		SetTokenPrivilege(TokenHandle, PrivilegeList[i], bEnable);
	}
}

//获取System权限令牌(需要SE_DEBUG_NAME特权)
bool NSudoGetSystemToken(PHANDLE hNewToken)
{
	bool bRet = false;

	//获取当前会话ID下的winlogon的PID
	DWORD dwWinLogonPID = NSudoGetProcessID(L"winlogon.exe", true);
	if (dwWinLogonPID != -1)
	{
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwWinLogonPID);
		if (hProc != NULL)
		{
			HANDLE hToken;
			if (OpenProcessToken(hProc, TOKEN_DUPLICATE, &hToken))
			{
				bRet = NSudoDuplicateToken(hToken, hNewToken);
				NtClose(hToken);
			}
			NtClose(hProc);
		}
	}
	return bRet;
}

//模拟当前进程的权限令牌为System权限(如果想取消模拟，可以调用RevertToSelf)
bool NSudoImpersonateSystemToken()
{
	bool bRet = false;

	HANDLE hSystemToken;
	if (NSudoGetSystemToken(&hSystemToken)) //获取System权限令牌
	{
		NSudoAdjustAllTokenPrivileges(hSystemToken, true); //在模拟令牌上开启所有特权
		bRet = ImpersonateLoggedOnUser(hSystemToken); //模拟令牌
		NtClose(hSystemToken);
	}
	return bRet;
}

//获取TrustedInstaller权限令牌(需要SE_DEBUG_NAME特权)
bool NSudoGetTrustedInstallerToken(PHANDLE hNewToken)
{
	bool bRet = false;

	//启动服务代码有Bug

	SC_HANDLE hSC = OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE);
	if (hSC != NULL)
	{
		SC_HANDLE hSvc = OpenServiceW(hSC, L"TrustedInstaller", SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
		if (hSvc != NULL)
		{
			SERVICE_STATUS status;
			if (QueryServiceStatus(hSvc, &status))
			{
				if (status.dwCurrentState == SERVICE_STOPPED)
				{
					// 启动服务
					if (StartServiceW(hSvc, NULL, NULL))
					{
						// 等待服务启动
						int nTry = 0;
						while (status.dwCurrentState == SERVICE_START_PENDING && ++nTry < 80)
						{
							::Sleep(50);
							::QueryServiceStatus(hSvc, &status);
						}
					}
				}
			}
			CloseServiceHandle(hSvc);
		}
		CloseServiceHandle(hSC);
	}

	if (NSudoImpersonateSystemToken())
	{
		//获取当前会话ID下的TrustedInstaller的PID
		DWORD dwTIPID = NSudoGetProcessID(L"TrustedInstaller.exe", false);

		if (dwTIPID != -1)
		{
			HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwTIPID);
			if (hProc != NULL)
			{
				HANDLE hToken;
				if (OpenProcessToken(hProc, TOKEN_DUPLICATE | TOKEN_QUERY, &hToken))
				{
					bRet = NSudoDuplicateToken(hToken, hNewToken);
					NtClose(hToken);
				}
				NtClose(hProc);
			}
		}

		RevertToSelf();
	}

	return bRet;
}

//获取当前用户的令牌(需要SE_DEBUG_NAME特权)
bool NSudoGetCurrentUserToken(PHANDLE hNewToken)
{
	bool bRet = false;

	if (NSudoImpersonateSystemToken())
	{
		WINSTATIONUSERTOKEN WinStaUserToken = { 0 };
		DWORD ccbInfo = NULL;
		if (WinStationQueryInformationW(
			SERVERNAME_CURRENT,
			LOGONID_CURRENT,
			WinStationUserToken,
			&WinStaUserToken,
			sizeof(WINSTATIONUSERTOKEN),
			&ccbInfo))
		{
			bRet = NSudoDuplicateToken(WinStaUserToken.UserToken, hNewToken);
		}
		RevertToSelf();
	}

	return bRet;
}

//设置令牌完整性
bool SetTokenIntegrity(HANDLE hToken, LPCWSTR szIntegritySID)
{
	bool bRet = false;

	TOKEN_MANDATORY_LABEL TokenMandatoryLabel = { 0 };  //令牌完整性结构
	if (ConvertStringSidToSidW(
		szIntegritySID,
		&TokenMandatoryLabel.Label.Sid)) //获取低完整性SID
	{
		TokenMandatoryLabel.Label.Attributes = SE_GROUP_INTEGRITY;

		//设置进程完整性级别
		bRet = SetTokenInformation(
			hToken,
			TokenIntegrityLevel,
			&TokenMandatoryLabel,
			sizeof(TokenMandatoryLabel));

		FreeSid(TokenMandatoryLabel.Label.Sid); //释放低完整性SID
	}

	return bRet;
}

//对当前进程进行降权并获取令牌
bool NSudoCreateLUAToken(PHANDLE hNewToken)
{
	bool bRet = false;

	HANDLE hToken, hToken2, hHeap = GetProcessHeap();
	if (NSudoGetCurrentProcessToken(&hToken))
	{
		if (NT_SUCCESS(NtFilterToken(hToken, LUA_TOKEN, NULL, NULL, NULL, &hToken2))) // 创建受限令牌
		{
			//完整性设置为中（管理员权限需要）
			SetTokenIntegrity(hToken2, L"S-1-16-8192");

			DWORD dwReturnLength;
			bRet = GetTokenInformation(hToken2, TokenUser, 0, 0, &dwReturnLength);

			PTOKEN_USER pTokenUser = (PTOKEN_USER)HeapAlloc(hHeap, 0, dwReturnLength);
			if (pTokenUser)
			{
				GetTokenInformation(hToken2, TokenUser, pTokenUser, dwReturnLength, &dwReturnLength);

				//设置令牌Owner为当前用户（管理员权限需要）
				PTOKEN_OWNER pTokenOwner =
					(PTOKEN_OWNER)HeapAlloc(hHeap, 0, sizeof(TOKEN_OWNER));
				if (pTokenOwner)
				{
					pTokenOwner->Owner = pTokenUser->User.Sid;
					SetTokenInformation(hToken2, TokenOwner, pTokenOwner, 4);
					HeapFree(hHeap, 0, pTokenOwner);
				}

				//设置令牌的ACL（管理员权限需要）
				GetTokenInformation(hToken2, TokenDefaultDacl, 0, 0, &dwReturnLength);

				PTOKEN_DEFAULT_DACL pTokenDefaultDacl =
					(PTOKEN_DEFAULT_DACL)HeapAlloc(hHeap, 0, dwReturnLength);
				if (pTokenDefaultDacl)
				{
					GetTokenInformation(
						hToken2,
						TokenDefaultDacl,
						pTokenDefaultDacl,
						dwReturnLength,
						&dwReturnLength);

					//删除Administrator对于该令牌的权限
					//DeleteAce(pTokenDefaultDacl->DefaultDacl, 0);

					//初始化EXPLICIT_ACCESS结构
					EXPLICIT_ACCESS_W ea;
					ea.grfAccessMode = GRANT_ACCESS;
					ea.grfAccessPermissions = GENERIC_ALL;
					ea.grfInheritance = OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE;
					BuildTrusteeWithSidW(&ea.Trustee, pTokenUser->User.Sid);

					PACL pNewACL = NULL;
					if (ERROR_SUCCESS == SetEntriesInAclW(
						1,
						&ea,
						pTokenDefaultDacl->DefaultDacl,
						&pNewACL))
					{
						pTokenDefaultDacl->DefaultDacl = pNewACL;
						SetTokenInformation(
							hToken2,
							TokenDefaultDacl,
							pTokenDefaultDacl,
							sizeof(pTokenDefaultDacl));
					}
					HeapFree(hHeap, 0, pTokenDefaultDacl);
				}
				HeapFree(hHeap, 0, pTokenUser);
			}

			//复制令牌
			bRet = NSudoDuplicateToken(hToken2, hNewToken);

			NtClose(hToken2);
		}
		NtClose(hToken);
	}
	return bRet;
}

bool NSudoOpenProcessToken(
	_In_ HANDLE ProcessHandle,
	_Outptr_ PHANDLE TokenHandle
	)
{
	NTSTATUS status = NtOpenProcessToken(ProcessHandle, MAXIMUM_ALLOWED, TokenHandle);
	if (!NT_SUCCESS(status))
	{
		RtlSetLastWin32Error(RtlNtStatusToDosError(status));
		return false;
	}

	return true;
}

bool NSudoOpenProcess(
	_In_ DWORD dwProcessId,
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL bInheritHandle,
	_Out_ PHANDLE ProcessHandle
	)
{
	CLIENT_ID ClientId =
	{
		(HANDLE)dwProcessId, // UniqueProcess;
		NULL // UniqueThread;
	};

	OBJECT_ATTRIBUTES ObjectAttributes =
	{
		sizeof(OBJECT_ATTRIBUTES), // Length
		NULL, // RootDirectory
		NULL, // ObjectName
		bInheritHandle != FALSE ? OBJ_INHERIT : 0, // Attributes
		NULL, // SecurityDescriptor
		NULL // SecurityQualityOfService
	};

	NTSTATUS status = NtOpenProcess(ProcessHandle, dwDesiredAccess, &ObjectAttributes, &ClientId);
	if (!NT_SUCCESS(status))
	{
		RtlSetLastWin32Error(RtlNtStatusToDosError(status));
		return false;
	}

	return true;
}