//NSudo 3.0 (Build 825)
//(C) 2015 NSudo Team. All rights reserved.

#pragma once

extern "C"
{
	//设置令牌权限
	bool SetTokenPrivilege(HANDLE TokenHandle, LPCWSTR lpName, bool bEnable);

	//设置当前进程令牌权限
	bool SetCurrentProcessPrivilege(LPCWSTR lpName, bool bEnable);

	//一键开启全部权限令牌
	void EnableAllTokenPrivileges(HANDLE TokenHandle);

	//获取System权限令牌(需要Debug特权)
	bool GetSystemToken(PHANDLE hNewToken);

	//获取当前会话ID下winlogon的PID
	DWORD GetWinLogonProcessID();

	//获取TrustedInstaller的PID
	DWORD GetTrustedInstallerProcessID();

	//判断是否在WoW64下运行
	bool IsWoW64();

	//获取当前用户令牌(需要Debug特权)
	bool GetCurrentUserToken(PHANDLE hNewToken);

	//获取TrustedInstaller权限令牌(需要Debug特权)
	bool GetTIToken(PHANDLE hNewToken);

	//一键禁用全部权限令牌
	void DisableAllTokenPrivileges(HANDLE TokenHandle);

	//设置令牌完整性
	bool SetTokenIntegrity(HANDLE hToken, LPCWSTR szIntegritySID);

	//创建和指定进程一样的环境块
	bool CreateEnvironmentBlockFromProcess(DWORD dwPID, LPVOID* lpEnv);
}