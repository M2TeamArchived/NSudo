//NSudo 核心库

#include "stdafx.h"

#include "NSudoBase.h"

//创建令牌副本
NTSTATUS WINAPI SuDuplicateToken(
	_In_ HANDLE ExistingToken,
	_Out_ PHANDLE NewTokenHandle)
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

	//复制令牌对象
	return NtDuplicateToken(
		ExistingToken,
		MAXIMUM_ALLOWED,
		&ObjectAttributes,
		FALSE,
		TokenPrimary,
		NewTokenHandle);
}

//获取令牌信息(自动分配所需内存)
NTSTATUS WINAPI SuGetTokenInfo(
	_In_ HANDLE TokenHandle,
	_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
	_Out_ void*& TokenInformation,
	_Out_ PULONG ReturnLength)
{
	//获取大小
	SuTokenGetInfoSize(TokenHandle, TokenInformationClass, ReturnLength);

	//分配内存
	TokenInformation = MemAlloc(*ReturnLength);
	if (!TokenInformation) return STATUS_NO_MEMORY;

	//获取信息
	return NtQueryInformationToken(
		TokenHandle, TokenInformationClass, TokenInformation,
		*ReturnLength, ReturnLength);
}

//获取进程句柄
NTSTATUS SuOpenProcess(
	_In_ DWORD dwProcessId,
	_Out_ PHANDLE ProcessHandle
	)
{
	OBJECT_ATTRIBUTES ObjAttr;
	CLIENT_ID ClientId =
	{
		(HANDLE)dwProcessId, // UniqueProcess;
		NULL // UniqueThread;
	};

	InitObjAttr(&ObjAttr, NULL, NULL, NULL, NULL, NULL);

	return NtOpenProcess(
		ProcessHandle, MAXIMUM_ALLOWED, &ObjAttr, &ClientId);
}

//开启令牌所有特权
NTSTATUS WINAPI SuEnableAllTokenPrivileges(
	_In_ HANDLE TokenHandle)
{
	//定义变量
	NTSTATUS status = NULL;
	DWORD Length = NULL;
	PTOKEN_PRIVILEGES pTPs = NULL;

	//获取特权信息
	status = SuGetTokenInfo(
		TokenHandle, TokenPrivileges, (void*&)pTPs, &Length);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//设置特权信息
	for (DWORD i = 0; i < pTPs->PrivilegeCount; i++)
		pTPs->Privileges[i].Attributes = SE_PRIVILEGE_ENABLED;

	//开启全部特权
	status = NtAdjustPrivilegesToken(
		TokenHandle, FALSE, pTPs, NULL, NULL, NULL);

FuncEnd:
	MemFree(pTPs);

	return status;
}

//获取一个进程的PID
DWORD WINAPI SuGetProcessID(
	_In_ LPCWSTR lpProcessName,
	_In_ bool bUnderCurrentSessionID)
{
	//定义变量
	DWORD dwPID = -1;
	DWORD dwReturnLength = 0;
	PVOID lpBuffer = NULL;
	PSYSTEM_PROCESS_INFORMATION pSPI = NULL;

	//获取大小
	NtQuerySystemInformation(
		SystemProcessInformation, NULL, NULL, &dwReturnLength);

	//分配内存
	lpBuffer = MemAlloc(dwReturnLength);
	if (!lpBuffer) return STATUS_NO_MEMORY;
	pSPI = (PSYSTEM_PROCESS_INFORMATION)lpBuffer;

	//获取进程信息
	if (!NT_SUCCESS(NtQuerySystemInformation(
		SystemProcessInformation, pSPI, dwReturnLength, &dwReturnLength)))
		goto FuncEnd;

	//遍历进程
	while (true)
	{
		if (pSPI->ImageName.Buffer &&
			wcscmp(lpProcessName, pSPI->ImageName.Buffer) == 0)
		{
			if (!(bUnderCurrentSessionID
				&& pSPI->SessionId != USER_SHARED_DATA->ActiveConsoleId))
			{
				dwPID = HandleToUlong(pSPI->UniqueProcessId);
				break;
			}
		}

		if (pSPI->NextEntryOffset != 0)
			pSPI = (PSYSTEM_PROCESS_INFORMATION)((char *)pSPI + pSPI->NextEntryOffset);
	}

FuncEnd:
	MemFree(lpBuffer);
	return dwPID;
}

//启动一个服务并返回服务进程ID
DWORD WINAPI SuStartService(
	_In_ LPCWSTR lpServiceName)
{
	SERVICE_STATUS_PROCESS ssStatus;
	SC_HANDLE schSCManager, schService;
	//打开SCM管理器句柄
	if ((schSCManager = OpenSCManagerW(NULL, NULL, GENERIC_EXECUTE)) != NULL)
	{
		//打开服务句柄
		if ((schService = OpenServiceW(
			schSCManager,
			lpServiceName,
			SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP)) != NULL)
		{
			DWORD dwBytesNeeded;
			bool bStarted = false;
			//查询状态
			while (QueryServiceStatusEx(
				schService,
				SC_STATUS_PROCESS_INFO,
				(LPBYTE)&ssStatus,
				sizeof(SERVICE_STATUS_PROCESS),
				&dwBytesNeeded))
			{
				//如果服务处于停止状态并且没有调用StartServiceW
				if (ssStatus.dwCurrentState == SERVICE_STOPPED && !bStarted)
				{
					bStarted = true;
					if (StartServiceW(schService, 0, NULL)) continue;
				}
				//如果服务在加载和卸载过程中，你需要等待
				else if (ssStatus.dwCurrentState == SERVICE_START_PENDING
					|| ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
				{
					Sleep(ssStatus.dwWaitHint);
					continue;
				}
				//在其他情况下break
				break;
			}
			CloseServiceHandle(schService); //关闭服务句柄
		}
		CloseServiceHandle(schSCManager); //关闭服务管理器句柄
	}
	//如果服务启用或正在运行，则返回服务对应进程PID，否则返回"-1"
	if (ssStatus.dwCurrentState != SERVICE_STOPPED &&
		ssStatus.dwCurrentState != SERVICE_STOP_PENDING) 
		return ssStatus.dwProcessId;
	else return -1;
}

//获取System权限令牌(需要SE_DEBUG_NAME特权)
bool SuGetSystemToken(
	_In_ PHANDLE hNewToken)
{
	bool bRet = false;

	//获取当前会话ID下的winlogon的PID
	DWORD dwWinLogonPID = SuGetProcessID(L"winlogon.exe", true);
	if (dwWinLogonPID != -1)
	{
		HANDLE hProc;
		if (NT_SUCCESS(SuOpenProcess(dwWinLogonPID, &hProc)))
		{
			HANDLE hToken;
			if (NT_SUCCESS(SuGetPsToken(hProc, &hToken)))
			{
				bRet = NT_SUCCESS(SuDuplicateToken(hToken, hNewToken));
				NtClose(hToken);
			}
			NtClose(hProc);
		}
	}
	return bRet;
}

//模拟当前进程的权限令牌为System权限(如果想取消模拟，可以调用RevertToSelf)
bool SuImpersonateSystemToken()
{
	bool bRet = false;

	HANDLE hSystemToken;
	if (SuGetSystemToken(&hSystemToken)) //获取System权限令牌
	{
		SuEnableAllTokenPrivileges(hSystemToken); //在模拟令牌上开启所有特权
		bRet = ImpersonateLoggedOnUser(hSystemToken); //模拟令牌
		NtClose(hSystemToken);
	}
	return bRet;
}

//获取TrustedInstaller令牌
bool SuGetTrustedInstallerToken(
	_In_ PHANDLE hNewToken)
{
	bool bRet = false;

	if (SuImpersonateSystemToken())
	{
		//启动TrustedInstaller服务并获取SID
		DWORD dwTIPID = SuStartService(L"TrustedInstaller");

		if (dwTIPID != -1)
		{
			HANDLE hProc;
			if (NT_SUCCESS(SuOpenProcess(dwTIPID, &hProc)))
			{
				HANDLE hToken;
				if (NT_SUCCESS(SuGetPsToken(hProc, &hToken)))
				{
					bRet = NT_SUCCESS(SuDuplicateToken(hToken, hNewToken));
					NtClose(hToken);
				}
				NtClose(hProc);
			}
		}

		::RevertToSelf();
	}

	return bRet;
}

//获取当前用户的令牌(需要SE_DEBUG_NAME特权)
bool SuGetCurrentUserToken(
	_In_ PHANDLE hNewToken)
{
	bool bRet = false;

	if (SuImpersonateSystemToken())
	{
		WINSTATIONUSERTOKEN WSUT = { 0 };
		DWORD ccbInfo = NULL;
		if (WinStationQueryInformationW(
			SERVERNAME_CURRENT,
			LOGONID_CURRENT,
			WinStationUserToken,
			&WSUT,
			sizeof(WINSTATIONUSERTOKEN),
			&ccbInfo))
		{
			bRet = NT_SUCCESS(SuDuplicateToken(WSUT.UserToken, hNewToken));
		}
		RevertToSelf();
	}

	return bRet;
}

//设置令牌完整性
NTSTATUS WINAPI SuSetTokenIL(
	_In_ HANDLE TokenHandle,
	_In_ DWORD IntegrityLabelRID)
{
	//定义变量
	NTSTATUS status = NULL;
	TOKEN_MANDATORY_LABEL TML = { 0 };
	SID_IDENTIFIER_AUTHORITY SIDAuthority = SECURITY_MANDATORY_LABEL_AUTHORITY;

	//初始化SID
	status = RtlAllocateAndInitializeSid(
		&SIDAuthority, 1, IntegrityLabelRID,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, &TML.Label.Sid);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//初始化TOKEN_MANDATORY_LABEL
	TML.Label.Attributes = SE_GROUP_INTEGRITY;

	//设置令牌对象
	status = NtSetInformationToken(
		TokenHandle, TokenIntegrityLevel, &TML, sizeof(TML));
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//扫尾
FuncEnd:
	if (TML.Label.Sid) RtlFreeSid(TML.Label.Sid);

	return status;
}

//创建一个对应的降权令牌
NTSTATUS WINAPI SuCreateLUAToken(
	_In_ HANDLE ExistingTokenHandle,
	_Out_ PHANDLE NewTokenHandle)
{
	//定义变量
	NTSTATUS status = NULL;

	DWORD Length = NULL;
	PTOKEN_USER pTokenUser = NULL;
	PTOKEN_OWNER pTokenOwner = NULL;
	PTOKEN_DEFAULT_DACL pTokenDacl = NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuthority = SECURITY_NT_AUTHORITY;
	PSID AdminSid = NULL;
	PACL pAcl = NULL;
	PACL pNewAcl = NULL;
	TOKEN_DEFAULT_DACL NewTokenDacl = { 0 };
	BOOL EnableTokenVirtualization = TRUE;
	PACCESS_ALLOWED_ACE pTempAce = NULL;

	//创建受限令牌
	status = NtFilterToken(
		ExistingTokenHandle, LUA_TOKEN, NULL, NULL, NULL, NewTokenHandle);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//以下代码仅适合管理员权限令牌（非强制性要求）
	//****************************************************************************

	//设置令牌完整性
	SuSetTokenIL(*NewTokenHandle, SECURITY_MANDATORY_MEDIUM_RID);

	//获取令牌对应的用户账户SID
	if (!NT_SUCCESS(SuGetTokenInfo(
		*NewTokenHandle, TokenUser, (void*&)pTokenUser, &Length)))
		goto FuncEnd;

	//设置令牌Owner为当前用户（分配内存）
	pTokenOwner = (PTOKEN_OWNER)MemAlloc(sizeof(TOKEN_OWNER));
	if (!pTokenOwner) goto FuncEnd;

	//设置令牌Owner为当前用户（设置参数）
	pTokenOwner->Owner = pTokenUser->User.Sid;

	//设置令牌Owner为当前用户
	if (!NT_SUCCESS(NtSetInformationToken(*NewTokenHandle,
		TokenOwner, pTokenOwner, sizeof(TOKEN_OWNER))))
		goto FuncEnd;

	//获取令牌的DACL
	if (!NT_SUCCESS(SuGetTokenInfo(
		*NewTokenHandle, TokenDefaultDacl, (void*&)pTokenDacl, &Length)))
		goto FuncEnd;
	pAcl = pTokenDacl->DefaultDacl;

	//获取管理员组SID
	if (!NT_SUCCESS(RtlAllocateAndInitializeSid(
		&SIDAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
		NULL, NULL, NULL, NULL, NULL, NULL, &AdminSid)))
		goto FuncEnd;

	//计算新ACL大小
	Length += RtlLengthSid(pTokenUser->User.Sid);
	Length += sizeof(ACCESS_ALLOWED_ACE);

	//分配ACL结构内存
	pNewAcl = (PACL)MemAlloc(Length);
	if (!pNewAcl) goto FuncEnd;

	//创建ACL
	if (!NT_SUCCESS(RtlCreateAcl(pNewAcl, Length, pAcl->AclRevision)))
		goto FuncEnd;

	//添加ACE
	if (!NT_SUCCESS(RtlAddAccessAllowedAce(
		pNewAcl, pAcl->AclRevision, GENERIC_ALL, pTokenUser->User.Sid)))
		goto FuncEnd;

	//复制ACE
	for (int i = 0; NT_SUCCESS(RtlGetAce(pAcl, i, (PVOID*)&pTempAce)); i++)
	{
		if (RtlEqualSid(AdminSid, &pTempAce->SidStart)) continue;

		RtlAddAce(pNewAcl, pAcl->AclRevision, 0,
			pTempAce, pTempAce->Header.AceSize);
	}

	//设置令牌DACL
	Length += sizeof(TOKEN_DEFAULT_DACL);
	NewTokenDacl.DefaultDacl = pNewAcl;
	if (!NT_SUCCESS(NtSetInformationToken(*NewTokenHandle,
		TokenDefaultDacl, &NewTokenDacl, Length)))
		goto FuncEnd;

	//打开LUA虚拟化
	if (!NT_SUCCESS(NtSetInformationToken(*NewTokenHandle,
		TokenVirtualizationEnabled, &EnableTokenVirtualization, sizeof(BOOL))))
		goto FuncEnd;

	//****************************************************************************

	//扫尾
FuncEnd:
	MemFree(pNewAcl);
	MemFree(AdminSid);
	MemFree(pTokenDacl);
	MemFree(pTokenOwner);
	MemFree(pTokenUser);
	return status;
}

//开启令牌所有特权
NTSTATUS WINAPI SuEnableTokenPrivilege(
	_In_ HANDLE TokenHandle)
{
	//定义变量
	NTSTATUS status = NULL;
	DWORD Length = NULL;
	PTOKEN_PRIVILEGES pTPs = NULL;

	//获取特权信息
	status = SuGetTokenInfo(
		TokenHandle, TokenPrivileges, (void*&)pTPs, &Length);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//设置特权信息
	for (DWORD i = 0; i < pTPs->PrivilegeCount; i++)
		pTPs->Privileges[i].Attributes = SE_PRIVILEGE_ENABLED;

	//开启全部特权
	status = NtAdjustPrivilegesToken(
		TokenHandle, FALSE, pTPs, NULL, NULL, NULL);

FuncEnd:
	MemFree(pTPs);

	return status;
}

//为令牌设置特权
bool SuSetTokenPrivilege(
	_In_ HANDLE TokenHandle,
	_In_ TokenPrivilegesList Privilege,
	_In_ bool bEnable)
{
	NTSTATUS status;
	TOKEN_PRIVILEGES TP = { 0 };
	TP.PrivilegeCount = 1;
	TP.Privileges[0].Luid.LowPart = Privilege;
	TP.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : NULL;

	// Adjust a Privilege in a Token
	status = NtAdjustPrivilegesToken(
		TokenHandle, FALSE, &TP, NULL, NULL, NULL);

	// Return the Result
	return RtlNtStatusToDosError(status) == ERROR_SUCCESS;
}

//设置当前进程令牌权限
bool SuSetCurrentPsPrivilege(
	_In_ TokenPrivilegesList Privilege,
	_In_ bool bEnable)
{
	bool bRet = false;
	HANDLE hCurrentProcessToken;
	if (NT_SUCCESS(SuGetCurrentPsToken(&hCurrentProcessToken)))
	{
		bRet = SuSetTokenPrivilege(hCurrentProcessToken, Privilege, bEnable);
		NtClose(hCurrentProcessToken);
	}
	return bRet;
}