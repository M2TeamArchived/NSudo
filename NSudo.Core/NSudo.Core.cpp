//NSudo 3.0 (Build 810)
//(C) 2015 NSudo Project. All rights reserved.

#include "stdafx.h"

#include "NSudo.Core.h"

extern "C"
{

	//设置令牌权限
	bool SetTokenPrivilege(HANDLE TokenHandle, LPCWSTR lpName, bool bEnable)
	{
		TOKEN_PRIVILEGES TP;

		TP.PrivilegeCount = 1;
		TP.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : NULL;

		if (LookupPrivilegeValueW(NULL, lpName, &TP.Privileges[0].Luid))
		{
			if (AdjustTokenPrivileges(TokenHandle, FALSE, &TP, sizeof(TP), NULL, NULL)) return true;
		}

		return false;
	}

	//设置当前进程令牌权限
	bool SetCurrentProcessPrivilege(LPCWSTR lpName, bool bEnable)
	{
		bool bRet = false;
		HANDLE hCurrentProcessToken;
		if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hCurrentProcessToken))
		{
			if (SetTokenPrivilege(hCurrentProcessToken, lpName, true)) bRet = true;
			CloseHandle(hCurrentProcessToken);
		}
		return bRet;
	}

	//一键开启全部权限令牌
	void EnableAllTokenPrivileges(HANDLE TokenHandle)
	{
		wchar_t *PrivilegeList[] = {
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
			SE_CREATE_SYMBOLIC_LINK_NAME };

		for (int i = 0; i < sizeof(PrivilegeList) / sizeof(wchar_t*); i++)
		{
			SetTokenPrivilege(TokenHandle, PrivilegeList[i], true);
		}
	}

}