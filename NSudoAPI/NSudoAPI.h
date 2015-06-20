//NSudo 3.0 (Build 810)
//(C) 2015 NSudo Team. All rights reserved.

#pragma once

//#include <Windows.h>

extern "C"
{
	//设置令牌权限
	bool SetTokenPrivilege(HANDLE TokenHandle, LPCWSTR lpName, bool bEnable);

	//设置当前进程令牌权限
	bool SetCurrentProcessPrivilege(LPCWSTR lpName, bool bEnable);

	//一键开启全部权限令牌
	void EnableAllTokenPrivileges(HANDLE TokenHandle);

	//获取System权限令牌
	bool GetSystemToken(PHANDLE hNewToken);

	//获取当前会话ID下winlogon的PID
	DWORD GetWinLogonProcessID();

	//获取TrustedInstaller的PID
	DWORD GetTrustedInstallerProcessID();
}