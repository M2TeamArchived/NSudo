#include "stdafx.h"

#include "M2.Base.hpp"

#include "M2.NSudoLib.h"

namespace M2
{
	// 复制令牌
	NTSTATUS SuDuplicateToken(
		_Out_ PHANDLE phNewToken,
		_In_ HANDLE hExistingToken,
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType)
	{
		// 变量定义

		OBJECT_ATTRIBUTES ObjAttr;
		SECURITY_QUALITY_OF_SERVICE SQOS;

		// 参数初始化

		M2InitObjectAttributes(
			&ObjAttr, nullptr, 0, nullptr, nullptr, &SQOS);
		M2InitSecurityQuailtyOfService(
			&SQOS, ImpersonationLevel, FALSE, FALSE);

		if (lpTokenAttributes &&
			lpTokenAttributes->nLength == sizeof(SECURITY_ATTRIBUTES))
		{
			ObjAttr.Attributes =
				(ULONG)(lpTokenAttributes->bInheritHandle ? OBJ_INHERIT : 0);
			ObjAttr.SecurityDescriptor =
				lpTokenAttributes->lpSecurityDescriptor;
		}

		// 复制令牌对象并返回运行结果
		return NtDuplicateToken(
			hExistingToken,
			dwDesiredAccess,
			&ObjAttr,
			FALSE,
			TokenType,
			phNewToken);
	}

	// 通过进程ID获取进程句柄
	NTSTATUS SuOpenProcess(
		_Out_ PHANDLE phProcess,
		_In_ DWORD dwProcessID,
		_In_ DWORD DesiredAccess)
	{
		// 变量定义

		OBJECT_ATTRIBUTES ObjAttr;
		CLIENT_ID ClientID;

		// 参数初始化

		M2InitObjectAttributes(&ObjAttr);
		M2InitClientID(&ClientID, dwProcessID, 0);

		// 根据进程ID获取进程句柄并返回运行结果
		return NtOpenProcess(
			phProcess, DesiredAccess, &ObjAttr, &ClientID);
	}

	// 通过进程ID获取进程令牌句柄
	NTSTATUS SuQueryProcessToken(
		_Out_ PHANDLE phProcessToken,
		_In_ DWORD dwProcessID,
		_In_ DWORD DesiredAccess)
	{
		// 变量定义	

		NTSTATUS status = STATUS_SUCCESS;
		HANDLE hProcess = nullptr;

		do
		{
			// 根据进程ID获取进程句柄
			status = SuOpenProcess(&hProcess, dwProcessID);
			if (!NT_SUCCESS(status)) break;

			// 根据进程句柄获取进程令牌句柄
			status = NtOpenProcessToken(
				hProcess, DesiredAccess, phProcessToken);

		} while (false);

		NtClose(hProcess);

		return status;
	}

	// 通过会话ID获取会话令牌
	HRESULT SuQuerySessionToken(
		_Out_ PHANDLE phToken,
		_In_ DWORD dwSessionID)
	{
		// 定义及初始化变量

		WINSTATIONUSERTOKEN WSUT = { 0 };
		DWORD ccbInfo = 0;

		*phToken = nullptr;

		// 通过会话ID获取会话令牌，如果获取失败则返回错误值
		if (!WinStationQueryInformationW(
			SERVERNAME_CURRENT,
			dwSessionID,
			WinStationUserToken,
			&WSUT,
			sizeof(WINSTATIONUSERTOKEN),
			&ccbInfo))
			return __HRESULT_FROM_WIN32(GetLastError());

		// 如果获取成功，则设置返回的会话令牌并返回运行结果
		*phToken = WSUT.UserToken;
		return S_OK;
	}

	// 获取当前进程令牌
	NTSTATUS SuQueryCurrentProcessToken(
		_Out_ PHANDLE phProcessToken,
		_In_ DWORD DesiredAccess)
	{
		return NtOpenProcessToken(
			NtCurrentProcess(), DesiredAccess, phProcessToken);
	}

	// 令牌模拟
	NTSTATUS SuImpersonate(
		_In_ HANDLE hExistingImpersonationToken)
	{
		return NtSetInformationThread(
			NtCurrentThread(),
			ThreadImpersonationToken,
			&hExistingImpersonationToken,
			sizeof(HANDLE));
	}

	// 撤销令牌模拟
	NTSTATUS SuRevertImpersonate()
	{
		return SuImpersonate(nullptr);
	}

	// 设置单个令牌特权
	NTSTATUS SuSetTokenPrivilege(
		_In_ HANDLE hExistingToken,
		_In_ TokenPrivilegesList Privilege,
		_In_ bool bEnable)
	{
		// 变量定义

		TOKEN_PRIVILEGES TP;

		// 参数初始化

		TP.PrivilegeCount = 1;
		TP.Privileges[0].Luid.LowPart = Privilege;
		TP.Privileges[0].Attributes = (DWORD)(bEnable ? SE_PRIVILEGE_ENABLED : 0);

		// 设置令牌特权并返回结果
		return NtAdjustPrivilegesToken(
			hExistingToken, FALSE, &TP, 0, nullptr, nullptr);
	}

	// 设置令牌全部特权
	NTSTATUS SuSetTokenAllPrivileges(
		_In_ HANDLE hExistingToken,
		_In_ DWORD dwAttributes)
	{
		// 定义变量

		NTSTATUS status = STATUS_SUCCESS;
		CPtr<PTOKEN_PRIVILEGES> pTPs;
		DWORD Length = 0;

		do
		{
			// 获取特权信息大小
			NtQueryInformationToken(
				hExistingToken,
				TokenPrivileges,
				nullptr,
				0,
				&Length);

			if (!pTPs.Alloc(Length))
			{
				status = STATUS_NO_MEMORY;
				break;
			}

			// 获取特权信息
			status = NtQueryInformationToken(
				hExistingToken,
				TokenPrivileges,
				pTPs,
				Length,
				&Length);
			if (!NT_SUCCESS(status)) break;

			// 设置特权信息
			for (DWORD i = 0; i < pTPs->PrivilegeCount; i++)
				pTPs->Privileges[i].Attributes = dwAttributes;

			// 开启全部特权
			status = NtAdjustPrivilegesToken(
				hExistingToken, FALSE, pTPs, 0, nullptr, nullptr);

		} while (false);

		return status;
	}

	//判断是否为登录SID
	bool SuIsLogonSid(
		_In_ PSID pSid)
	{
		// 获取pSid的SID_IDENTIFIER_AUTHORITY结构
		PSID_IDENTIFIER_AUTHORITY pSidAuth = RtlIdentifierAuthoritySid(pSid);

		// 如果不符合SID_IDENTIFIER_AUTHORITY结构长度，则返回false
		if (!memcmp(pSidAuth, &SidAuth_NT, SidAuth_Length)) return false;

		// 判断SID是否属于Logon SID
		return (*RtlSubAuthorityCountSid(pSid) == SECURITY_LOGON_IDS_RID_COUNT
			&& *RtlSubAuthoritySid(pSid, 0) == SECURITY_LOGON_IDS_RID);
	}
	
	// 设置内核对象完整性标签
	NTSTATUS SuSetKernelObjectIntegrityLevel(
		_In_ HANDLE Object,
		_In_ IntegrityLevel IL)
	{
		//定义变量

		const size_t AclLength = 88;
		NTSTATUS status = STATUS_SUCCESS;
		PSID pSID = nullptr;
		PACL pAcl = nullptr;
		SECURITY_DESCRIPTOR SD;
		HANDLE hNewHandle = nullptr;

		// 复制句柄
		status = NtDuplicateObject(
			NtCurrentProcess(),
			Object,
			NtCurrentProcess(),
			&hNewHandle,
			DIRECTORY_ALL_ACCESS,
			0,
			0);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		//初始化SID
		status = RtlAllocateAndInitializeSid(
			&SIDAuth_IL, 1, IL, 0, 0, 0, 0, 0, 0, 0, &pSID);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		//分配ACL结构内存
		status = M2HeapAlloc(AclLength, pAcl);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 创建SD
		status = RtlCreateSecurityDescriptor(
			&SD, SECURITY_DESCRIPTOR_REVISION);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 创建ACL
		status = RtlCreateAcl(pAcl, AclLength, ACL_REVISION);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 添加完整性ACE
		status = RtlAddMandatoryAce(
			pAcl, ACL_REVISION, 0, pSID,
			SYSTEM_MANDATORY_LABEL_ACE_TYPE, OBJECT_TYPE_CREATE);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 设置SACL
		status = RtlSetSaclSecurityDescriptor(&SD, TRUE, pAcl, FALSE);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 设置内核对象
		status = NtSetSecurityObject(
			hNewHandle, LABEL_SECURITY_INFORMATION, &SD);

	FuncEnd:
		//释放内存
		M2HeapFree(pAcl);
		RtlFreeSid(pSID);
		NtClose(hNewHandle);

		return status;
	}

	// 设置令牌完整性标签
	NTSTATUS SuSetTokenIntegrityLevel(
		_In_ HANDLE TokenHandle,
		_In_ IntegrityLevel IL)
	{
		// 变量定义
		NTSTATUS status = STATUS_SUCCESS;
		TOKEN_MANDATORY_LABEL TML;

		// 初始化SID
		status = RtlAllocateAndInitializeSid(
			&SIDAuth_IL, 1, IL, 0, 0, 0, 0, 0, 0, 0, &TML.Label.Sid);
		if (NT_SUCCESS(status))
		{
			// 初始化TOKEN_MANDATORY_LABEL
			TML.Label.Attributes = SE_GROUP_INTEGRITY;

			// 设置令牌对象
			status = NtSetInformationToken(
				TokenHandle, TokenIntegrityLevel, &TML, sizeof(TML));

			// 释放SID
			RtlFreeSid(TML.Label.Sid);
		}

		return status;
	}
	
	// 根据已提权令牌创建一个降权为标准用户的令牌
	NTSTATUS SuCreateLUAToken(
		_Out_ PHANDLE TokenHandle,
		_In_ HANDLE ExistingTokenHandle)
	{
		// 变量定义

		NTSTATUS status = STATUS_SUCCESS;
		DWORD Length = 0;
		BOOL EnableTokenVirtualization = TRUE;
		TOKEN_OWNER Owner = { 0 };
		TOKEN_DEFAULT_DACL NewTokenDacl = { 0 };
		PTOKEN_USER pTokenUser = nullptr;
		PTOKEN_DEFAULT_DACL pTokenDacl = nullptr;
		PSID pAdminSid = nullptr;
		PACCESS_ALLOWED_ACE pTempAce = nullptr;

		//创建受限令牌
		status = NtFilterToken(
			ExistingTokenHandle, LUA_TOKEN,
			nullptr, nullptr, nullptr, TokenHandle);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 设置令牌完整性
		status = SuSetTokenIntegrityLevel(
			*TokenHandle, IntegrityLevel::Medium);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 获取令牌对应的用户账户SID
		status = SuQueryInformationToken(
			*TokenHandle, TokenUser, pTokenUser);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 设置令牌Owner为当前用户
		Owner.Owner = pTokenUser->User.Sid;
		status = NtSetInformationToken(
			*TokenHandle, TokenOwner, &Owner, sizeof(TOKEN_OWNER));
		if (!NT_SUCCESS(status)) goto FuncEnd;

		//获取令牌的DACL
		status = SuQueryInformationToken(
			*TokenHandle, TokenDefaultDacl, pTokenDacl);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 获取管理员组SID
		status = RtlAllocateAndInitializeSid(
			&SidAuth_NT, 2,
			SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0, &pAdminSid);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 计算新ACL大小
		Length = pTokenDacl->DefaultDacl->AclSize;
		Length += RtlLengthSid(pTokenUser->User.Sid);
		Length += sizeof(ACCESS_ALLOWED_ACE);

		// 分配ACL结构内存
		status = M2HeapAlloc(Length, NewTokenDacl.DefaultDacl);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 创建ACL
		status = RtlCreateAcl(
			NewTokenDacl.DefaultDacl,
			Length, pTokenDacl->DefaultDacl->AclRevision);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 添加ACE
		status = RtlAddAccessAllowedAce(
			NewTokenDacl.DefaultDacl,
			pTokenDacl->DefaultDacl->AclRevision,
			GENERIC_ALL,
			pTokenUser->User.Sid);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 复制ACE
		for (ULONG i = 0;
			NT_SUCCESS(RtlGetAce(pTokenDacl->DefaultDacl, i, (PVOID*)&pTempAce));
			++i)
		{
			if (RtlEqualSid(pAdminSid, &pTempAce->SidStart)) continue;

			RtlAddAce(
				NewTokenDacl.DefaultDacl,
				pTokenDacl->DefaultDacl->AclRevision, 0,
				pTempAce, pTempAce->Header.AceSize);
		}

		// 设置令牌DACL
		Length += sizeof(TOKEN_DEFAULT_DACL);
		status = NtSetInformationToken(
			*TokenHandle, TokenDefaultDacl, &NewTokenDacl, Length);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 开启LUA虚拟化
		status = NtSetInformationToken(
			*TokenHandle,
			TokenVirtualizationEnabled,
			&EnableTokenVirtualization,
			sizeof(BOOL));
		if (!NT_SUCCESS(status)) goto FuncEnd;

	FuncEnd: // 扫尾

		if (NewTokenDacl.DefaultDacl) M2HeapFree(NewTokenDacl.DefaultDacl);
		if (pAdminSid) RtlFreeSid(pAdminSid);
		if (pTokenDacl) M2HeapFree(pTokenDacl);
		if (pTokenUser) M2HeapFree(pTokenUser);
		if (!NT_SUCCESS(status))
		{
			NtClose(*TokenHandle);
			*TokenHandle = INVALID_HANDLE_VALUE;
		}

		return status;
	}

	// 启动一个服务并返回服务进程ID
	DWORD SuStartService(
		_In_ LPCWSTR lpServiceName)
	{
		DWORD dwPID = (DWORD)-1;
		SERVICE_STATUS_PROCESS ssStatus;
		SC_HANDLE schSCManager = nullptr;
		SC_HANDLE schService = nullptr;
		DWORD dwBytesNeeded;
		bool bStarted = false;

		// 打开SCM管理器句柄
		schSCManager = OpenSCManagerW(nullptr, nullptr, GENERIC_EXECUTE);
		if (!schSCManager) goto FuncEnd;

		// 打开服务句柄
		schService = OpenServiceW(
			schSCManager, lpServiceName,
			SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
		if (!schService) goto FuncEnd;

		// 查询状态
		while (QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssStatus,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded))
		{
			// 如果服务处于停止状态并且没有调用StartServiceW
			if (ssStatus.dwCurrentState == SERVICE_STOPPED && !bStarted)
			{
				bStarted = true;
				if (StartServiceW(schService, 0, nullptr)) continue;
			}
			// 如果服务在加载和卸载过程中，你需要等待
			else if (ssStatus.dwCurrentState == SERVICE_START_PENDING
				|| ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
			{
				Sleep(ssStatus.dwWaitHint);
				continue;
			}
			// 在其他情况下break
			break;
		}

		// 如果服务启用或正在运行，则返回服务对应进程PID
		if (ssStatus.dwCurrentState != SERVICE_STOPPED &&
			ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
			dwPID = ssStatus.dwProcessId;

	FuncEnd: //退出时关闭句柄并返回

		if (schService) CloseServiceHandle(schService);
		if (schSCManager) CloseServiceHandle(schSCManager);
		return dwPID;
	}
}