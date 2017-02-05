// NTIShell.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace M2;

wchar_t AppTitle[] = L"NTIShell 4.2 (Build 1612)";

bool SuRunCommandShell(
	_In_opt_ HANDLE hToken)
{
	bool bRet = true;

	STARTUPINFOW StartupInfo = { 0 };
	PROCESS_INFORMATION ProcessInfo = { 0 };
	wchar_t szBuf[512], szSystemDir[MAX_PATH];

	//设置进程所在桌面
	StartupInfo.lpDesktop = L"WinSta0\\Default";

	//获取系统目录
	GetSystemDirectoryW(szSystemDir, MAX_PATH);

	//生成命令行
	_swprintf_c(
		szBuf, 512, 
		L"%s\\cmd.exe /k title %s && echo %s && echo (c) 2016 M2-Team. All rights reserved.", 
		szSystemDir, AppTitle, AppTitle);

	//启动进程
	if (!CreateProcessAsUserW(
		hToken,
		nullptr,
		szBuf,
		nullptr,
		nullptr,
		FALSE,
		CREATE_UNICODE_ENVIRONMENT,
		nullptr,
		nullptr,
		&StartupInfo,
		&ProcessInfo))
	{
		if (!CreateProcessWithTokenW(
			hToken,
			LOGON_WITH_PROFILE,
			nullptr,
			szBuf,
			CREATE_UNICODE_ENVIRONMENT,
			nullptr,
			nullptr,
			&StartupInfo,
			&ProcessInfo))
		{
			bRet = false;
		}
	}

	//关闭句柄
	if (bRet)
	{
		NtClose(ProcessInfo.hProcess);
		NtClose(ProcessInfo.hThread);
	}

	//返回结果
	return bRet;
}

// 显示消息
inline void SuMessageBox(
	_In_ LPCWSTR lpText)
{
	MessageBoxW(nullptr, lpText, AppTitle, 0);
}

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	IIntendToIgnoreThisVariable(hInstance);
	IIntendToIgnoreThisVariable(hPrevInstance);
	IIntendToIgnoreThisVariable(lpCmdLine);
	IIntendToIgnoreThisVariable(nShowCmd);

	DWORD dwTIPID = (DWORD)-1;
	DWORD dwSessionID = M2GetCurrentSessionID();
	HANDLE hProcessToken = nullptr;
	HANDLE hDuplicatedToken = nullptr;

	// 模拟上下文令牌为System用户
	if (!NT_SUCCESS(SuImpersonateAsSystem()))
	{
		SuMessageBox(L"SuImpersonateAsSystem() Failed");
		goto FuncEnd;
	}

	//启动TrustedInstaller服务并获取SID
	dwTIPID = SuStartService(L"TrustedInstaller");
	if (dwTIPID == -1)
	{
		SuMessageBox(L"M2StartService() Failed");
		goto FuncEnd;
	}

	// 获取TrustedInstaller进程令牌
	if (!NT_SUCCESS(SuQueryProcessToken(&hProcessToken, dwTIPID)))
	{
		SuMessageBox(L"SuQueryProcessToken() Failed");
		goto FuncEnd;
	}

	// 复制令牌
	if (!NT_SUCCESS(SuDuplicateToken(&hDuplicatedToken, hProcessToken)))
	{
		SuMessageBox(L"SuDuplicateToken() Failed");
		goto FuncEnd;	
	}

	// 设置令牌会话ID
	if (NtSetInformationToken(
		hDuplicatedToken,
		TokenSessionId,
		(PVOID)&dwSessionID, 
		sizeof(DWORD)))
	{
		SuMessageBox(L"NtSetInformationToken() Failed");
		goto FuncEnd;
	}
	
	// 启用令牌全部特权
	if (!NT_SUCCESS(SuSetTokenAllPrivileges(
		hDuplicatedToken, SE_PRIVILEGE_ENABLED)))
	{
		SuMessageBox(L"SuSetTokenAllPrivileges() Failed");
		goto FuncEnd;
	}
	
	if (!SuRunCommandShell(hDuplicatedToken))
	{
		SuMessageBox(L"SuRunCommandShell() Failed");
	}

FuncEnd:
	NtClose(hDuplicatedToken);
	NtClose(hProcessToken);
	SuRevertImpersonate();

	return 0;
}

#ifndef _DEBUG
#pragma comment(linker, "/ENTRY:EntryPoint") 

void EntryPoint()
{
	RtlExitUserProcess((NTSTATUS)wWinMain(
		GetModuleHandleW(nullptr),
		nullptr,
		nullptr,
		SW_SHOWNORMAL));
}

#endif
