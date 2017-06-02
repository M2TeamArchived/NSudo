/******************************************************************************
项目：M2-SDK
描述：NSudo库
文件名：M2.NSudo.h
基于项目：无
许可协议：看顶层目录的 License.txt
建议的Windows SDK版本：10.0.10586及以后

Project: M2-SDK
Description: NSudo Library
Filename: M2.NSudo.h
License: See License.txt in the top level directory
Recommend Minimum Windows SDK Version: 10.0.10586
******************************************************************************/

#pragma once

#ifndef _M2_NSUDO_
#define _M2_NSUDO_

#ifdef __cplusplus
extern "C" {
	using namespace M2;
#endif

	/*
	SuDuplicateToken函数通过现有的访问令牌创建一个主令牌或模仿令牌。
	The SuDuplicateToken function creates a primary token or an impersonation
	token via an existing access token.

	该函数是DuplicateTokenEx API的一个等价实现。
	This function is an equivalent implementation of DuplicateTokenEx API.
	*/
	static NTSTATUS WINAPI SuDuplicateToken(
		_In_ HANDLE hExistingToken,
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phNewToken)
	{
		SECURITY_QUALITY_OF_SERVICE SQOS;
		OBJECT_ATTRIBUTES ObjectAttributes;
		
		M2InitSecurityQuailtyOfService(
			SQOS, ImpersonationLevel, FALSE, FALSE);
		M2InitObjectAttributes(
			ObjectAttributes, nullptr, 0, nullptr, nullptr, &SQOS);
		
		if (lpTokenAttributes &&
			lpTokenAttributes->nLength == sizeof(SECURITY_ATTRIBUTES))
		{
			ObjectAttributes.Attributes =
				(ULONG)(lpTokenAttributes->bInheritHandle ? OBJ_INHERIT : 0);
			ObjectAttributes.SecurityDescriptor =
				lpTokenAttributes->lpSecurityDescriptor;
		}

		return NtDuplicateToken(
			hExistingToken,
			dwDesiredAccess,
			&ObjectAttributes,
			FALSE,
			TokenType,
			phNewToken);
	}

	/*
	SuOpenProcess函数打开一个存在的本机进程对象。
	The SuOpenProcess function opens an existing local process object.

	该函数是OpenProcess API的一个等价实现。
	This function is an equivalent implementation of OpenProcess API.
	*/
	static NTSTATUS WINAPI SuOpenProcess(
		_Out_ PHANDLE phProcess,
		_In_ DWORD dwDesiredAccess,
		_In_ BOOL bInheritHandle,
		_In_ DWORD dwProcessId)
	{
		OBJECT_ATTRIBUTES ObjectAttributes; 
		CLIENT_ID ClientID;
		
		M2InitClientID(ClientID, dwProcessId, 0);
		M2InitObjectAttributes(ObjectAttributes);

		ObjectAttributes.Attributes =
			(ULONG)(bInheritHandle ? OBJ_INHERIT : 0);

		return NtOpenProcess(
			phProcess, dwDesiredAccess, &ObjectAttributes, &ClientID);
	}

	/*
	SuOpenProcessToken函数根据进程ID打开一个进程的关联令牌。
	The SuOpenProcessToken function opens the access token associated with a
	process via ProcessID.
	*/
	static NTSTATUS WINAPI SuOpenProcessToken(
		_In_ DWORD dwProcessId,
		_In_ DWORD DesiredAccess,
		_Outptr_ PHANDLE TokenHandle)
	{
		NTSTATUS status = STATUS_SUCCESS;
		HANDLE hProcess = nullptr;

		status = SuOpenProcess(
			&hProcess, MAXIMUM_ALLOWED, FALSE, dwProcessId);
		if (NT_SUCCESS(status))
		{
			status = NtOpenProcessToken(
				hProcess, DesiredAccess, TokenHandle);
			NtClose(hProcess);
		}

		return status;
	}

	/*
	SuOpenSessionToken函数根据已登陆的用户的会话ID获取主访问令牌。您需要在
	LocalSystem账户且开启SE_TCB_NAME特权的访问令牌上下文下调用该函数。
	The SuOpenSessionToken function obtains the primary access token of the
	logged-on user specified by the session ID. To call this function
	successfully, the calling application must be running within the context
	of the LocalSystem account and have the SE_TCB_NAME privilege.

	该函数是WTSQueryUserToken API的一个等价实现。
	This function is an equivalent implementation of WTSQueryUserToken API.
	*/
	static HRESULT WINAPI SuOpenSessionToken(
		_In_ ULONG SessionId,
		_Out_ PHANDLE phToken)
	{
		WINSTATIONUSERTOKEN WSUT = { 0 };
		DWORD ReturnLength = 0;

		// 初始化 LastError
		M2SetLastError(ERROR_SUCCESS);

		// 获取线程令牌
		if (WinStationQueryInformationW(
			SERVERNAME_CURRENT,
			SessionId,
			WinStationUserToken,
			&WSUT,
			sizeof(WINSTATIONUSERTOKEN),
			&ReturnLength))
		{
			// 如果执行成功则返回令牌句柄
			*phToken = WSUT.UserToken;
		}	

		return __HRESULT_FROM_WIN32(M2GetLastError());
	}

	/*
	SuStartService函数通过服务名启动服务并返回服务状态。
	The SuStartService function starts a service and return service status via
	service name.
	*/
	static HRESULT WINAPI SuStartService(
		_In_ LPCWSTR lpServiceName,
		_Out_ LPSERVICE_STATUS_PROCESS lpServiceStatus)
	{
		SC_HANDLE hSCM = nullptr;
		SC_HANDLE hService = nullptr;
		DWORD nBytesNeeded = 0;
		DWORD nOldCheckPoint = 0;
		ULONGLONG nCurrentTick = 0;
		ULONGLONG nLastTick = 0;
		bool bStartServiceWCalled = false;
		bool bSleepCalled = false;
		bool bFinished = false;
		bool bSucceed = false;

		// 初始化 LastError
		M2SetLastError(ERROR_SUCCESS);

		hSCM = OpenSCManagerW(
			nullptr,
			nullptr,
			SC_MANAGER_CONNECT);
		if (!hSCM) goto FuncEnd;

		hService = OpenServiceW(
			hSCM,
			lpServiceName,
			SERVICE_QUERY_STATUS | SERVICE_START);
		if (!hService) goto FuncEnd;

		while (QueryServiceStatusEx(
			hService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)lpServiceStatus,
			sizeof(SERVICE_STATUS_PROCESS),
			&nBytesNeeded))
		{
			switch (lpServiceStatus->dwCurrentState)
			{
			case SERVICE_STOPPED:
				if (!bStartServiceWCalled)
				{
					bStartServiceWCalled = true;
					bFinished = (!StartServiceW(hService, 0, nullptr));
				}
				else bFinished = true;
				break;
			case SERVICE_STOP_PENDING:
			case SERVICE_START_PENDING:
				nCurrentTick = NtGetTickCount64();

				if (!bSleepCalled)
				{
					nLastTick = nCurrentTick;
					nOldCheckPoint = lpServiceStatus->dwCheckPoint;

					bSleepCalled = true;

					// 等待250ms（借鉴.Net服务操作类的实现）
					LARGE_INTEGER Interval;
					Interval.QuadPart = 250LL * -10000LL;
					NtDelayExecution(FALSE, &Interval);
				}
				else
				{
					// 如果校验点增加则继续循环，否则检测是否超时
					if (lpServiceStatus->dwCheckPoint > nOldCheckPoint)
					{
						bSleepCalled = false;
					}
					else
					{
						ULONGLONG nDiff = nCurrentTick - nLastTick;
						if (nDiff > lpServiceStatus->dwWaitHint)
						{
							M2SetLastError(ERROR_TIMEOUT);
							bFinished = true;
						}
						else
						{
							// 未超时则继续循环
							bSleepCalled = false;
						}
					}
				}
				break;
			default:
				bSucceed = true;
				bFinished = true;
				break;
			}

			if (bFinished) break;
		}

		// 如果服务启动失败则清空状态信息
		if (!bSucceed)
			memset(lpServiceStatus, 0, sizeof(SERVICE_STATUS_PROCESS));

	FuncEnd:
		if (hService) CloseServiceHandle(hService);
		if (hSCM) CloseServiceHandle(hSCM);
		return __HRESULT_FROM_WIN32(M2GetLastError());
	}

	/*
	SuOpenServiceProcessToken函数根据服务名打开一个服务进程的关联令牌。
	The SuOpenServiceProcessToken function opens the access token associated
	with a service process via service name.
	*/
	static HRESULT WINAPI SuOpenServiceProcessToken(
		_In_ LPCWSTR lpServiceName,
		_In_ DWORD DesiredAccess,
		_Outptr_ PHANDLE TokenHandle)
	{
		HRESULT hr = S_OK;
		NTSTATUS status = STATUS_SUCCESS;
		SERVICE_STATUS_PROCESS ssStatus;

		hr = SuStartService(lpServiceName, &ssStatus);
		if (SUCCEEDED(hr))
		{
			status = SuOpenProcessToken(
				ssStatus.dwProcessId, DesiredAccess, TokenHandle);
			hr = __HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));
		}

		return hr;
	}

	/*
	SuOpenCurrentProcessToken函数打开当前进程的关联令牌。
	The SuOpenCurrentProcessToken function opens the access token associated
	with current process.
	*/
	static NTSTATUS WINAPI SuOpenCurrentProcessToken(
		_Out_ PHANDLE phProcessToken,
		_In_ DWORD DesiredAccess)
	{
		return NtOpenProcessToken(
			NtCurrentProcess(), DesiredAccess, phProcessToken);
	}


	/*
	SuGetCurrentProcessSessionID获取当前进程的会话ID。
	The SuGetCurrentProcessSessionID function obtains the Session ID of the 
	current process.
	*/
	static NTSTATUS SuGetCurrentProcessSessionID(PDWORD SessionID)
	{
		NTSTATUS status = STATUS_SUCCESS;
		HANDLE hToken = INVALID_HANDLE_VALUE;
		DWORD ReturnLength = 0;

		status = SuOpenCurrentProcessToken(&hToken, MAXIMUM_ALLOWED);
		if (NT_SUCCESS(status))
		{
			status = NtQueryInformationToken(
				hToken,
				TokenSessionId, 
				SessionID, 
				sizeof(DWORD), 
				&ReturnLength);
		}

		return status;
	}

	/*
	SuSetThreadToken函数给线程分配一个模拟令牌。该函数还可以使一个线程停止使用
	模拟令牌。
	The SuSetThreadToken function assigns an impersonation token to a thread.
	The function can also cause a thread to stop using an impersonation token.

	该函数是SetThreadToken API的一个等价实现。
	This function is an equivalent implementation of SetThreadToken API.
	*/
	static NTSTATUS WINAPI SuSetThreadToken(
		_In_opt_ PHANDLE phThread,
		_In_ HANDLE hToken)
	{
		return NtSetInformationThread(
			(phThread != nullptr) ? *phThread : NtCurrentThread(),
			ThreadImpersonationToken,
			&hToken,
			sizeof(HANDLE));
	}

	/*
	SuSetCurrentThreadToken函数给当前线程分配一个模拟令牌。该函数还可以使当前线
	程停止使用模拟令牌。
	The SuSetCurrentThreadToken function assigns an impersonation token to the
	current thread. The function can also cause the current thread to stop
	using an impersonation token.
	*/
	static NTSTATUS WINAPI SuSetCurrentThreadToken(
		_In_ HANDLE hToken)
	{
		return SuSetThreadToken(nullptr, hToken);
	}

	/*
	SuRevertToSelf函数终止客户端应用程序模拟。
	The SuRevertToSelf function terminates the impersonation of a client
	application.

	该函数是RevertToSelf API的一个等价实现。
	This function is an equivalent implementation of RevertToSelf API.
	*/
	static NTSTATUS WINAPI SuRevertToSelf()
	{
		return SuSetCurrentThreadToken(nullptr);
	}

	/*
	SuSetTokenPrivileges函数启用或禁用指定的访问令牌特权。启用或禁用一个访问令
	牌的特权需要TOKEN_ADJUST_PRIVILEGES访问权限。
	The SuSetTokenPrivileges function enables or disables privileges in the
	specified access token. Enabling or disabling privileges in an access
	token requires TOKEN_ADJUST_PRIVILEGES access.
	*/
	static NTSTATUS WINAPI SuSetTokenPrivileges(
		_In_ HANDLE TokenHandle,
		_In_opt_ PTOKEN_PRIVILEGES NewState)
	{
		return NtAdjustPrivilegesToken(
			TokenHandle, FALSE, NewState, 0, nullptr, nullptr);
	}

	/*
	访问令牌特权定义
	The definitions of the Token Privileges
	*/
	typedef enum _TOKEN_PRIVILEGES_LIST
	{
		SeMinWellKnownPrivilege = 2,
		SeCreateTokenPrivilege = 2,
		SeAssignPrimaryTokenPrivilege,
		SeLockMemoryPrivilege,
		SeIncreaseQuotaPrivilege,
		SeMachineAccountPrivilege,
		SeTcbPrivilege,
		SeSecurityPrivilege,
		SeTakeOwnershipPrivilege,
		SeLoadDriverPrivilege,
		SeSystemProfilePrivilege,
		SeSystemtimePrivilege,
		SeProfileSingleProcessPrivilege,
		SeIncreaseBasePriorityPrivilege,
		SeCreatePagefilePrivilege,
		SeCreatePermanentPrivilege,
		SeBackupPrivilege,
		SeRestorePrivilege,
		SeShutdownPrivilege,
		SeDebugPrivilege,
		SeAuditPrivilege,
		SeSystemEnvironmentPrivilege,
		SeChangeNotifyPrivilege,
		SeRemoteShutdownPrivilege,
		SeUndockPrivilege,
		SeSyncAgentPrivilege,
		SeEnableDelegationPrivilege,
		SeManageVolumePrivilege,
		SeImpersonatePrivilege,
		SeCreateGlobalPrivilege,
		SeTrustedCredManAccessPrivilege,
		SeRelabelPrivilege,
		SeIncreaseWorkingSetPrivilege,
		SeTimeZonePrivilege,
		SeCreateSymbolicLinkPrivilege,
		SeMaxWellKnownPrivilege = SeCreateSymbolicLinkPrivilege
	} TOKEN_PRIVILEGES_LIST, *PTOKEN_PRIVILEGES_LIST;

	/*
	访问令牌完整性级别定义
	The definitions of the Token Integrity Levels
	*/
	typedef enum _TOKEN_INTEGRITY_LEVELS_LIST
	{
		// S-1-16-0
		UntrustedLevel = SECURITY_MANDATORY_UNTRUSTED_RID,

		// S-1-16-4096
		LowLevel = SECURITY_MANDATORY_LOW_RID,

		// S-1-16-8192
		MediumLevel = SECURITY_MANDATORY_MEDIUM_RID,

		// S-1-16-8448
		MediumPlusLevel = SECURITY_MANDATORY_MEDIUM_PLUS_RID,

		// S-1-16-12288
		HighLevel = SECURITY_MANDATORY_HIGH_RID,

		// S-1-16-16384
		SystemLevel = SECURITY_MANDATORY_SYSTEM_RID, 

		// S-1-16-20480
		ProtectedLevel = SECURITY_MANDATORY_PROTECTED_PROCESS_RID
	} TOKEN_INTEGRITY_LEVELS_LIST, *PTOKEN_INTEGRITY_LEVELS_LIST;

	/*
	SuSetTokenPrivilege函数启用或禁用指定的访问令牌的指定特权。启用或禁用一个访
	问令牌的特权需要TOKEN_ADJUST_PRIVILEGES访问权限。
	The SuSetTokenPrivilege function enables or disables the specified
	privilege in the specified access token. Enabling or disabling privileges
	in an access token requires TOKEN_ADJUST_PRIVILEGES access.
	*/
	static NTSTATUS WINAPI SuSetTokenPrivilege(
		_In_ HANDLE hExistingToken,
		_In_ TOKEN_PRIVILEGES_LIST Privilege,
		_In_ bool bEnable)
	{
		TOKEN_PRIVILEGES TP;
		TP.PrivilegeCount = 1;
		TP.Privileges[0].Luid.LowPart = Privilege;
		TP.Privileges[0].Attributes = (DWORD)(bEnable ? SE_PRIVILEGE_ENABLED : 0);

		return SuSetTokenPrivileges(hExistingToken, &TP);
	}

	/*
	SuSetTokenAllPrivileges函数启用或禁用指定的访问令牌的所有特权。启用或禁用一
	个访问令牌的特权需要TOKEN_ADJUST_PRIVILEGES访问权限。
	The SuSetTokenAllPrivileges function enables or disables all privileges in
	the specified access token. Enabling or disabling privileges in an access
	token requires TOKEN_ADJUST_PRIVILEGES access.
	*/
	static NTSTATUS WINAPI SuSetTokenAllPrivileges(
		_In_ HANDLE hExistingToken,
		_In_ bool bEnable)
	{
		NTSTATUS status = STATUS_SUCCESS;
		PTOKEN_PRIVILEGES pTPs = nullptr;
		DWORD Length = 0;

		// 获取特权信息大小
		NtQueryInformationToken(
			hExistingToken, TokenPrivileges, nullptr, 0, &Length);

		// 分配内存
		status = M2HeapAlloc(Length, pTPs);
		if (NT_SUCCESS(status))
		{
			// 获取特权信息
			status = NtQueryInformationToken(
				hExistingToken,
				TokenPrivileges,
				pTPs,
				Length,
				&Length);
			if (NT_SUCCESS(status))
			{
				// 设置特权信息
				for (DWORD i = 0; i < pTPs->PrivilegeCount; i++)
					pTPs->Privileges[i].Attributes =
					(DWORD)(bEnable ? SE_PRIVILEGE_ENABLED : 0);

				// 开启全部特权
				status = SuSetTokenPrivileges(hExistingToken, pTPs);
			}

			// 释放内存
			M2HeapFree(pTPs);
		}

		return status;
	}

	// SECURITY_NT_AUTHORITY
	static SID_IDENTIFIER_AUTHORITY SIA_NT = SECURITY_NT_AUTHORITY;

	// SECURITY_MANDATORY_LABEL_AUTHORITY
	static SID_IDENTIFIER_AUTHORITY SIA_IL = SECURITY_MANDATORY_LABEL_AUTHORITY;

	/*
	SuSetTokenIntegrityLevel函数为指定的访问令牌设置完整性标签。
	The SuSetTokenIntegrityLevel function sets the integrity level for the
	specified access token.
	*/
	static NTSTATUS WINAPI SuSetTokenIntegrityLevel(
		_In_ HANDLE TokenHandle,
		_In_ TOKEN_INTEGRITY_LEVELS_LIST IL)
	{
		NTSTATUS status = STATUS_SUCCESS;
		TOKEN_MANDATORY_LABEL TML;

		// 初始化SID
		status = RtlAllocateAndInitializeSid(
			&SIA_IL, 1, IL, 0, 0, 0, 0, 0, 0, 0, &TML.Label.Sid);
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

	/*
	SuCreateLUAToken函数从一个现有的访问令牌创建一个新的LUA访问令牌。
	The SuCreateLUAToken function creates a new LUA access token from an
	existing access token.
	*/
	static NTSTATUS WINAPI SuCreateLUAToken(
		_Out_ PHANDLE TokenHandle,
		_In_ HANDLE ExistingTokenHandle)
	{
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
			*TokenHandle, TOKEN_INTEGRITY_LEVELS_LIST::MediumLevel);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 获取令牌对应的用户账户SID信息大小
		status = NtQueryInformationToken(
			*TokenHandle, TokenUser, nullptr, 0, &Length);
		if (status != STATUS_BUFFER_TOO_SMALL) goto FuncEnd;

		// 为令牌对应的用户账户SID信息分配内存
		status = M2HeapAlloc(Length, pTokenUser);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 获取令牌对应的用户账户SID信息
		status = NtQueryInformationToken(
			*TokenHandle, TokenUser, pTokenUser, Length, &Length);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 设置令牌Owner为当前用户
		Owner.Owner = pTokenUser->User.Sid;
		status = NtSetInformationToken(
			*TokenHandle, TokenOwner, &Owner, sizeof(TOKEN_OWNER));
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 获取令牌的DACL信息大小
		status = NtQueryInformationToken(
			*TokenHandle, TokenDefaultDacl, nullptr, 0, &Length);
		if (status != STATUS_BUFFER_TOO_SMALL) goto FuncEnd;

		// 为令牌的DACL信息分配内存
		status = M2HeapAlloc(Length, pTokenDacl);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 获取令牌的DACL信息
		status = NtQueryInformationToken(
			*TokenHandle, TokenDefaultDacl, pTokenDacl, Length, &Length);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 获取管理员组SID
		status = RtlAllocateAndInitializeSid(
			&SIA_NT, 2,
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

	/*
	SuCreateProcess函数创建一个新进程和对应的主线程
	The SuCreateProcess function creates a new process and its primary thread.
	*/
	static HRESULT WINAPI SuCreateProcess(
		_In_opt_ HANDLE hToken,
		_In_opt_ LPCWSTR lpApplicationName,
		_Inout_opt_ LPWSTR lpCommandLine,
		_In_ DWORD dwCreationFlags,
		_In_opt_ LPVOID lpEnvironment,
		_In_opt_ LPCWSTR lpCurrentDirectory,
		_In_ LPSTARTUPINFOW lpStartupInfo,
		_Out_ LPPROCESS_INFORMATION lpProcessInformation)
	{
		HRESULT hr = S_OK;
		
		if (!CreateProcessAsUserW(
			hToken,
			lpApplicationName,
			lpCommandLine,
			nullptr,
			nullptr,
			FALSE,
			dwCreationFlags,
			lpEnvironment,
			lpCurrentDirectory,
			lpStartupInfo,
			lpProcessInformation))
		{
			if (!CreateProcessWithTokenW(
				hToken,
				LOGON_WITH_PROFILE,
				lpApplicationName,
				lpCommandLine,
				dwCreationFlags,
				lpEnvironment,
				lpCurrentDirectory,
				lpStartupInfo,
				lpProcessInformation))
			{
				hr = __HRESULT_FROM_WIN32(M2GetLastError());
			}
		}
		
		return hr;
	}

#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4355) // "this": 用于基成员初始值设定项列表
#endif

	/*
	进程列表遍历迭代器
	Iterator for enumerate the process list

	用法 Usage
	for (auto pSPI : CM2EnumProcess(status)) { }

	status 是初始化遍历返回值（可选）
	status is the return value for initialization (Optional)
	*/
	class CM2EnumProcess
	{
	public:
		class CM2EnumProcessIterator
		{
		private:
			CM2EnumProcess* m_EnumProcess;

		public:
			FORCEINLINE CM2EnumProcessIterator(
				_In_ CM2EnumProcess* FindFile) :
				m_EnumProcess(FindFile)
			{

			}

			FORCEINLINE ~CM2EnumProcessIterator()
			{

			}

			FORCEINLINE void operator++()
			{
				// 如果pSPI和下个结构偏移都存在，则继续循环，否则清零
				if (m_EnumProcess->pSPI && m_EnumProcess->pSPI->NextEntryOffset)
				{
					ULONG_PTR NextSPI = reinterpret_cast<ULONG_PTR>(m_EnumProcess->pSPI);
					NextSPI += m_EnumProcess->pSPI->NextEntryOffset;
					m_EnumProcess->pSPI = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(NextSPI);
				}
				else
				{
					m_EnumProcess->pSPI = nullptr;
				}
			}

			// 根据迭代器循环特性，使用不等于操作符遍历目录
			FORCEINLINE bool operator!=(const CM2EnumProcessIterator& Item)
			{
				UNREFERENCED_PARAMETER(Item);
				return (m_EnumProcess->pSPI != nullptr);
			}

			FORCEINLINE PSYSTEM_PROCESS_INFORMATION operator*()
			{
				return m_EnumProcess->pSPI;
			}
		};

	private:
		CM2EnumProcessIterator Iterator;
		PVOID lpBuffer;
		PSYSTEM_PROCESS_INFORMATION pSPI;

	public:
		// 初始化文件遍历, 不内联考虑到大量使用本迭代器时实现函数复用以节约空间
		DECLSPEC_NOINLINE CM2EnumProcess(
			_Out_ NTSTATUS* InitStatus = nullptr) :
			Iterator(this),
			lpBuffer(nullptr),
			pSPI(nullptr)

		{
			NTSTATUS status = STATUS_SUCCESS;
			DWORD dwLength = 0;

			do
			{
				// 获取进程信息大小
				status = NtQuerySystemInformation(
					SystemProcessInformation,
					nullptr,
					0,
					&dwLength);
				if (status != STATUS_INFO_LENGTH_MISMATCH) break;

				// 为令牌信息分配内存，如果失败则返回
				status = M2HeapAlloc(
					dwLength,
					lpBuffer);
				if (!NT_SUCCESS(status)) break;

				// 获取进程信息
				status = NtQuerySystemInformation(
					SystemProcessInformation,
					lpBuffer,
					dwLength,
					&dwLength);
				if (!NT_SUCCESS(status)) break;

				// 设置遍历开始地址
				pSPI = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(lpBuffer);

			} while (false);

			if (InitStatus) *InitStatus = status;
		}

		FORCEINLINE ~CM2EnumProcess()
		{
			if (lpBuffer) M2HeapFree(lpBuffer);
		}

		FORCEINLINE CM2EnumProcessIterator& begin()
		{
			return Iterator;
		}

		FORCEINLINE CM2EnumProcessIterator& end()
		{
			return Iterator;
		}
	};

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
	
	/*
	SuGetSystemTokenCopy函数获取一个当前会话SYSTEM用户令牌的副本。
	The SuGetSystemTokenCopy function obtains a copy of current session SYSTEM 
	user token.
	*/
	static NTSTATUS WINAPI SuGetSystemTokenCopy(
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phToken)
	{
		NTSTATUS status = STATUS_SUCCESS;
		DWORD dwWinLogonPID = (DWORD)-1;
		DWORD dwSessionID = (DWORD)-1;
		HANDLE hProcessToken = nullptr;

		do
		{
			// 获取当前进程令牌会话ID
			status = SuGetCurrentProcessSessionID(&dwSessionID);
			if (!NT_SUCCESS(status)) break;

			// 遍历进程寻找winlogon进程并获取PID
			for (auto pSPI : CM2EnumProcess(&status))
			{
				if (pSPI->SessionId != dwSessionID) continue;
				if (pSPI->ImageName.Buffer == nullptr) continue;

				if (wcscmp(L"winlogon.exe", pSPI->ImageName.Buffer) == 0)
				{
					dwWinLogonPID = HandleToUlong(pSPI->UniqueProcessId);
					break;
				}
			}

			// 如果初始化进程遍历失败，则返回错误
			if (!NT_SUCCESS(status)) break;

			// 如果没找到进程，则返回错误
			if (dwWinLogonPID == -1)
			{
				status = STATUS_NOT_FOUND;
				break;
			}

			// 获取当前会话winlogon进程令牌
			status = SuOpenProcessToken(
				dwWinLogonPID, MAXIMUM_ALLOWED, &hProcessToken);
			if (!NT_SUCCESS(status)) break;

			// 复制令牌
			status = SuDuplicateToken(
				hProcessToken,
				dwDesiredAccess,
				lpTokenAttributes,
				ImpersonationLevel,
				TokenType,
				phToken);
			if (!NT_SUCCESS(status)) break;

		} while (false);

		NtClose(hProcessToken);

		return status;
	}

	/*
	SuGetServiceProcessTokenCopy函数根据服务名获取一个服务进程令牌的副本。
	The SuGetServiceProcessTokenCopy function obtains a copy of service process
	token via service name.
	*/
	static HRESULT WINAPI SuGetServiceProcessTokenCopy(
		_In_ LPCWSTR lpServiceName,
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phToken)
	{
		HRESULT hr = S_OK;
		NTSTATUS status = STATUS_SUCCESS;
		HANDLE hToken = nullptr;

		// 打开服务进程令牌
		hr = SuOpenServiceProcessToken(
			lpServiceName, MAXIMUM_ALLOWED, &hToken);
		if (SUCCEEDED(hr))
		{
			// 复制令牌
			status = SuDuplicateToken(
				hToken,
				dwDesiredAccess,
				lpTokenAttributes,
				ImpersonationLevel,
				TokenType,
				phToken);
			hr = __HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));

			NtClose(hToken);
		}

		return hr;
	}

	/*
	SuGetSessionTokenCopy函数根据服务名获取一个服务进程令牌的副本。
	The SuGetSessionTokenCopy function obtains a copy of Session token via
	Session ID.
	*/
	static HRESULT WINAPI SuGetSessionTokenCopy(
		_In_ DWORD dwSessionID,
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phToken)
	{
		HRESULT hr = S_OK;
		NTSTATUS status = STATUS_SUCCESS;
		HANDLE hToken = nullptr;

		// 打开会话令牌
		hr = SuOpenSessionToken(dwSessionID, &hToken);
		if (SUCCEEDED(hr))
		{
			// 复制令牌
			status = SuDuplicateToken(
				hToken,
				dwDesiredAccess,
				lpTokenAttributes,
				ImpersonationLevel,
				TokenType,
				phToken);
			hr = __HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));

			NtClose(hToken);
		}

		return hr;
	}

	/*
	SuGetProcessTokenCopy函数根据进程ID获取一个进程令牌的副本。
	The SuGetProcessTokenCopy function obtains a copy of process token via
	Process ID.
	*/
	static NTSTATUS WINAPI SuGetProcessTokenCopy(
		_In_ DWORD dwProcessID,
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phToken)
	{
		NTSTATUS status = STATUS_SUCCESS;
		HANDLE hToken = nullptr;

		// 打开进程令牌
		status = SuOpenProcessToken(dwProcessID, MAXIMUM_ALLOWED, &hToken);
		if (NT_SUCCESS(status))
		{
			// 复制令牌
			status = SuDuplicateToken(
				hToken,
				dwDesiredAccess,
				lpTokenAttributes,
				ImpersonationLevel,
				TokenType,
				phToken);

			NtClose(hToken);
		}

		return status;
	}

	/*
	SuImpersonateAsSystem函数给当前线程分配一个SYSTEM用户模拟令牌。该函数还可以
	使当前线程停止使用模拟令牌。
	The SuImpersonateAsSystem function assigns an SYSTEM user impersonation
	token to the current thread. The function can also cause the current thread
	to stop using an impersonation token.
	*/
	static NTSTATUS WINAPI SuImpersonateAsSystem()
	{
		NTSTATUS status = STATUS_SUCCESS;
		HANDLE hToken = nullptr;

		// 获取当前会话SYSTEM用户令牌副本
		status = SuGetSystemTokenCopy(
			MAXIMUM_ALLOWED,
			nullptr,
			SecurityImpersonation,
			TokenImpersonation,
			&hToken);
		if (NT_SUCCESS(status))
		{
			// 启用令牌全部特权
			status = SuSetTokenAllPrivileges(hToken, true);
			if (NT_SUCCESS(status))
			{
				// 模拟令牌
				status = SuSetCurrentThreadToken(hToken);
			}

			NtClose(hToken);
		}

		return status;
	}

#ifdef __cplusplus
}
#endif

#endif // !_M2_NSUDO_
