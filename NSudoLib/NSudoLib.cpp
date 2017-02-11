#include "stdafx.h"

#include "M2.Base.hpp"

#include "M2.NSudoLib.h"

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#endif

#include <WtsApi32.h>
#pragma comment(lib,"WtsApi32.lib")

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

namespace M2
{
	namespace NSudo
	{
		/*
		NSudo库编译属性

		// 禁止NSudo库使用基于未文档化Windows API
		//#define NSUDO_DISABLE_USING_UNDOCUMENT_WINDOWS_API

		*/



		/*
		SuDuplicateToken函数通过现有的访问令牌创建一个主令牌或模仿令牌。
		The SuDuplicateToken function creates a primary token or an impersonation 
		token via an existing access token.

		该函数是DuplicateTokenEx API的一个等价实现。
		This function is an equivalent implementation of DuplicateTokenEx API.
		*/
		HRESULT WINAPI SuDuplicateToken(
			_In_ HANDLE hExistingToken,
			_In_ DWORD dwDesiredAccess,
			_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
			_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
			_In_ TOKEN_TYPE TokenType,
			_Outptr_ PHANDLE phNewToken)
		{
#ifndef NSUDO_DISABLE_USING_UNDOCUMENT_WINDOWS_API
			NTSTATUS status = STATUS_SUCCESS;
			OBJECT_ATTRIBUTES ObjectAttributes;
			SECURITY_QUALITY_OF_SERVICE SQOS;

			M2InitObjectAttributes(
				&ObjectAttributes, nullptr, 0, nullptr, nullptr, &SQOS);
			M2InitSecurityQuailtyOfService(
				&SQOS, ImpersonationLevel, FALSE, FALSE);

			if (lpTokenAttributes &&
				lpTokenAttributes->nLength == sizeof(SECURITY_ATTRIBUTES))
			{
				ObjectAttributes.Attributes =
					(ULONG)(lpTokenAttributes->bInheritHandle ? OBJ_INHERIT : 0);
				ObjectAttributes.SecurityDescriptor =
					lpTokenAttributes->lpSecurityDescriptor;
			}

			// 复制令牌对象
			status = NtDuplicateToken(
				hExistingToken,
				dwDesiredAccess,
				&ObjectAttributes,
				FALSE,
				TokenType,
				phNewToken);

			// 返回运行结果
			return __HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));
#else
			// 复制令牌对象
			DuplicateTokenEx(
				hExistingToken,
				dwDesiredAccess,
				lpTokenAttributes, 
				ImpersonationLevel, 
				TokenType,
				phNewToken);

			// 返回运行结果
			return __HRESULT_FROM_WIN32(GetLastError());
#endif		
		}

		/*
		SuOpenProcess函数打开一个存在的本机进程对象。
		The SuOpenProcess function opens an existing local process object.

		该函数是OpenProcess API的一个等价实现。
		This function is an equivalent implementation of OpenProcess API.
		*/
		HRESULT WINAPI SuOpenProcess(
			_Out_ PHANDLE phProcess,
			_In_ DWORD dwDesiredAccess,
			_In_ BOOL bInheritHandle,
			_In_ DWORD dwProcessId)
		{
#ifndef NSUDO_DISABLE_USING_UNDOCUMENT_WINDOWS_API
			NTSTATUS status = STATUS_SUCCESS;
			OBJECT_ATTRIBUTES ObjectAttributes;
			CLIENT_ID ClientID;

			// 参数初始化

			M2InitObjectAttributes(&ObjectAttributes);
			ObjectAttributes.Attributes = 
				(ULONG)(bInheritHandle ? OBJ_INHERIT : 0);

			M2InitClientID(&ClientID, dwProcessId, 0);
			
			// 打开进程对象
			status = NtOpenProcess(
				phProcess, dwDesiredAccess, &ObjectAttributes, &ClientID);
		
			// 返回运行结果
			return __HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));
#else
			// 打开进程对象
			*phProcess = OpenProcess(
				dwDesiredAccess,
				bInheritHandle,
				dwProcessId);

			// 返回运行结果
			return __HRESULT_FROM_WIN32(GetLastError());
#endif
		}

		/*
		SuOpenProcessToken函数打开一个进程的关联令牌。
		The SuOpenProcessToken function opens the access token associated with a 
		process.

		该函数是OpenProcessToken API的一个等价实现。
		This function is an equivalent implementation of OpenProcessToken API.
		*/
		HRESULT WINAPI SuOpenProcessToken(
			_In_ HANDLE ProcessHandle,
			_In_ DWORD DesiredAccess,
			_Outptr_ PHANDLE TokenHandle)
		{
#ifndef NSUDO_DISABLE_USING_UNDOCUMENT_WINDOWS_API		
			// 打开进程令牌
			NTSTATUS status = NtOpenProcessToken(
				ProcessHandle, DesiredAccess, TokenHandle);

			// 返回运行结果
			return __HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));
#else
			// 打开进程令牌
			OpenProcessToken(ProcessHandle, DesiredAccess, TokenHandle);

			// 返回运行结果
			return __HRESULT_FROM_WIN32(GetLastError());
#endif			
		}

		/*
		SuOpenProcessToken函数根据进程ID打开一个进程的关联令牌。
		The SuOpenProcessToken function opens the access token associated with a
		process via ProcessID.
		*/
		HRESULT WINAPI SuOpenProcessToken(
			_In_ DWORD dwProcessId,
			_In_ DWORD DesiredAccess,
			_Outptr_ PHANDLE TokenHandle)
		{
#ifndef NSUDO_DISABLE_USING_UNDOCUMENT_WINDOWS_API		
			NTSTATUS status = STATUS_SUCCESS;
			HANDLE hProcess = nullptr;
			OBJECT_ATTRIBUTES ObjectAttributes;
			CLIENT_ID ClientID;

			// 参数初始化

			M2InitObjectAttributes(&ObjectAttributes);
			M2InitClientID(&ClientID, dwProcessId, 0);

			// 打开进程对象
			status = NtOpenProcess(
				&hProcess, MAXIMUM_ALLOWED, &ObjectAttributes, &ClientID);
			if (NT_SUCCESS(status))
			{
				// 打开进程令牌
				status = NtOpenProcessToken(
					hProcess, DesiredAccess, TokenHandle);
				
				// 关闭进程句柄
				NtClose(hProcess);
			}

			// 返回运行结果
			return __HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));
#else
			// 打开进程对象
			HANDLE hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, dwProcessId);
			if (hProcess != nullptr)
			{
				// 打开进程令牌
				OpenProcessToken(ProcessHandle, DesiredAccess, TokenHandle);

				// 关闭进程句柄
				CloseHandle(hProcess);
			}

			// 返回运行结果
			return __HRESULT_FROM_WIN32(GetLastError());
#endif		
		}

		/*
		SuQuerySessionToken函数根据已登陆的用户的会话ID获取主访问令牌。您需要在
		LocalSystem账户且开启SE_TCB_NAME特权的访问令牌上下文下调用该函数。
		The SuQuerySessionToken function obtains the primary access token of 
		the logged-on user specified by the session ID. To call this function 
		successfully, the calling application must be running within the 
		context of the LocalSystem account and have the SE_TCB_NAME privilege.

		该函数是WTSQueryUserToken API的一个等价实现。
		This function is an equivalent implementation of WTSQueryUserToken API.
		*/
		HRESULT WINAPI SuQuerySessionToken(
			_In_ ULONG SessionId,
			_Out_ PHANDLE phToken)
		{
#ifndef NSUDO_DISABLE_USING_UNDOCUMENT_WINDOWS_API		
			WINSTATIONUSERTOKEN WSUT = { 0 };
			DWORD ReturnLength = 0;

			// 获取会话令牌
			WinStationQueryInformationW(
				SERVERNAME_CURRENT,
				SessionId,
				WinStationUserToken,
				&WSUT,
				sizeof(WINSTATIONUSERTOKEN),
				&ReturnLength);
			*phToken = WSUT.UserToken;

			// 返回运行结果
			return __HRESULT_FROM_WIN32(M2GetLastError());
#else
			// 获取会话令牌
			WTSQueryUserToken(SessionId, phToken);

			// 返回运行结果
			return __HRESULT_FROM_WIN32(GetLastError());
#endif			
		}

		/*
		SuOpenCurrentProcessToken函数打开当前进程的关联令牌。
		The SuQueryCurrentProcessToken function opens the access token 
		associated with current process.
		*/
		HRESULT WINAPI SuOpenCurrentProcessToken(
			_In_ DWORD DesiredAccess,
			_Outptr_ PHANDLE TokenHandle)
		{
#ifndef NSUDO_DISABLE_USING_UNDOCUMENT_WINDOWS_API		
			// 打开进程令牌
			return SuOpenProcessToken(
				NtCurrentProcess(), DesiredAccess, TokenHandle);
#else
			// 打开进程令牌
			return SuOpenProcessToken(
				GetCurrentProcess(), DesiredAccess, TokenHandle);
#endif			
		}


	}
	
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

	// 获取进程信息（该函数自动分配的内存需要使用M2HeapFree释放）
	NTSTATUS SuQuerySystemProcessInformation(
		_Out_ PSYSTEM_PROCESS_INFORMATION *ppSystemProcessInformation)
	{
		// 定义变量
		NTSTATUS status = STATUS_SUCCESS;
		DWORD ReturnLength = 0;

		// 获取进程信息大小
		status = NtQuerySystemInformation(
			SystemProcessInformation, 
			nullptr,
			0, 
			&ReturnLength);
		if (status == STATUS_INFO_LENGTH_MISMATCH)
		{
			// 为令牌信息分配内存，如果失败则返回
			status = M2HeapAlloc(
				ReturnLength,
				*ppSystemProcessInformation);
			if (NT_SUCCESS(status))
			{
				// 获取进程信息
				status = NtQuerySystemInformation(
					SystemProcessInformation,
					*ppSystemProcessInformation,
					ReturnLength,
					&ReturnLength);
				if (!NT_SUCCESS(status))
				{
					// 如果获取失败则释放刚刚分配的内存
					M2HeapFree(*ppSystemProcessInformation);
				}
			}
		}

		// 返回运行结果
		return status;
	}

	// 模仿System令牌
	NTSTATUS SuImpersonateAsSystem()
	{
		// 变量定义		
		NTSTATUS status = STATUS_SUCCESS;
		DWORD dwWinLogonPID = (DWORD)-1;
		PSYSTEM_PROCESS_INFORMATION pSPI = nullptr;
		HANDLE hProcessToken = nullptr;
		HANDLE hDuplicatedToken = nullptr;

		do
		{
			// 初始化进程遍历
			status = SuQuerySystemProcessInformation(&pSPI);
			if (!NT_SUCCESS(status)) break;

			// 遍历进程寻找winlogon进程并获取PID
			PSYSTEM_PROCESS_INFORMATION pNextSPI = pSPI;
			do
			{
				if (pNextSPI->SessionId == M2GetCurrentSessionID())
				{
					if (wcscmp(L"winlogon.exe", pNextSPI->ImageName.Buffer) == 0)
					{
						dwWinLogonPID = HandleToUlong(pNextSPI->UniqueProcessId);
						break;
					}
				}

				if (pNextSPI->NextEntryOffset == 0) break;
				((ULONG&)pNextSPI) += pNextSPI->NextEntryOffset;
			} while (true);

			// 如果没找到进程，则返回错误
			if (dwWinLogonPID == -1)
			{
				status = STATUS_NOT_FOUND;
				break;
			}

			// 获取当前会话winlogon进程令牌
			status = SuQueryProcessToken(&hProcessToken, dwWinLogonPID);
			if (!NT_SUCCESS(status)) break;

			// 复制一份模拟令牌
			status = SuDuplicateToken(
				&hDuplicatedToken,
				hProcessToken,
				MAXIMUM_ALLOWED,
				nullptr,
				SecurityImpersonation,
				TokenImpersonation);
			if (!NT_SUCCESS(status)) break;

			// 启用令牌全部特权
			status = SuSetTokenAllPrivileges(
				hDuplicatedToken,
				SE_PRIVILEGE_ENABLED);
			if (!NT_SUCCESS(status)) break;

			// 模拟令牌
			status = SuImpersonate(hDuplicatedToken);

		} while (false);

		NtClose(hDuplicatedToken);
		NtClose(hProcessToken);
		if (pSPI) M2HeapFree(pSPI);

		return status;
	}
}