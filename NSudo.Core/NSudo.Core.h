//NSudo 3.0 (Build 810)
//(C) 2015 NSudo Project. All rights reserved.

#pragma once

extern "C"
{
	//设置令牌权限
	bool SetTokenPrivilege(HANDLE TokenHandle, LPCWSTR lpName, bool bEnable);

	//设置当前进程令牌权限
	bool SetCurrentProcessPrivilege(LPCWSTR lpName, bool bEnable);

	//一键开启全部权限令牌
	void EnableAllTokenPrivileges(HANDLE TokenHandle);
}