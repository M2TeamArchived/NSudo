/******************************************************************************
项目：NSudoSDK
描述：NSudo库
文件名：NSudoAPI.h
许可协议：The MIT License

Project: NSudoSDK
Description: NSudo Library
File Name: NSudoAPI.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _NSUDOAPI_
#define _NSUDOAPI_

#include <Windows.h>
#include <WtsApi32.h>

#pragma comment(lib,"WtsApi32.lib")

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4505) // 未引用的本地函数已移除(等级 4)
#endif

namespace M2
{
	template<typename TObject, const TObject InvalidValue, typename TCloseFunction, TCloseFunction CloseFunction>
	class CObject
	{
	private:
		TObject m_Object;
	public:
		CObject(TObject Object = InvalidValue) : m_Object(Object)
		{

		}

		~CObject()
		{
			this->Close();
		}

		TObject* operator&()
		{
			return &this->m_Object;
		}

		TObject operator=(TObject Object)
		{
			this->Close();
			return (this->m_Object = Object);
		}

		operator TObject()
		{
			return this->m_Object;
		}

		bool IsInvalid()
		{
			return (this->m_Object == InvalidValue);
		}

		TObject Detach()
		{
			TObject Object = this->m_Object;
			this->m_Object = InvalidValue;
			return Object;
		}

		void Close()
		{
			if (!this->IsInvalid())
			{
				CloseFunction(this->m_Object);
				this->m_Object = InvalidValue;
			}
		}
	};

	typedef CObject<SC_HANDLE, nullptr, decltype(CloseServiceHandle), CloseServiceHandle> CServiceHandle;
	
	typedef CObject<HANDLE, INVALID_HANDLE_VALUE, decltype(CloseHandle), CloseHandle> CHandle;


	class CNSudoInstance
	{
	private:
		DWORD m_SessionID;



	public:
		CNSudoInstance()
			: m_SessionID(-1)
		{

		}
		~CNSudoInstance()
		{

		}

		DWORD get_SessionID()
		{
			return m_SessionID;
		}
	};
}

#ifdef __cplusplus
extern "C" {
#endif

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

	// SECURITY_NT_AUTHORITY
	static SID_IDENTIFIER_AUTHORITY SIA_NT = SECURITY_NT_AUTHORITY;

	// SECURITY_MANDATORY_LABEL_AUTHORITY
	static SID_IDENTIFIER_AUTHORITY SIA_IL = SECURITY_MANDATORY_LABEL_AUTHORITY;

	/*
	NSudoGetLastCOMError函数返回该线程的上个错误码并转换为COM错误码。每个进程维
	护各自的上个错误码。多线程不应该互相覆写其上个错误码值。
	The NSudoGetLastCOMError function retrieves the calling thread's last-error
	code value and convert to COM error code. The last-error code is maintained
	on a per-thread basis. Multiple threads do not overwrite each other's 
	last-error code.
	*/
	FORCEINLINE HRESULT WINAPI NSudoGetLastCOMError()
	{
		return __HRESULT_FROM_WIN32(GetLastError());
	}
	
	/*
	NSudoStartService函数通过服务名启动服务并返回服务状态。
	The NSudoStartService function starts a service and return service status
	via service name.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error 
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoStartService(
		_In_ LPCWSTR lpServiceName,
		_Out_ LPSERVICE_STATUS_PROCESS lpServiceStatus)
	{
		M2::CServiceHandle hSCM;
		M2::CServiceHandle hService;
		
		DWORD nBytesNeeded = 0;
		DWORD nOldCheckPoint = 0;
		ULONGLONG nCurrentTick = 0;
		ULONGLONG nLastTick = 0;
		bool bStartServiceWCalled = false;
		bool bSleepCalled = false;
		bool bFinished = false;
		bool bSucceed = false;

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
				nCurrentTick = GetTickCount64();

				if (!bSleepCalled)
				{
					nLastTick = nCurrentTick;
					nOldCheckPoint = lpServiceStatus->dwCheckPoint;

					bSleepCalled = true;

					// 等待250ms（借鉴.Net服务操作类的实现）
					SleepEx(250, FALSE);
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
							SetLastError(ERROR_TIMEOUT);
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

		return bSucceed;
	}

	/*
	NSudoGetCurrentProcessSessionID获取当前进程的会话ID。
	The NSudoGetCurrentProcessSessionID function obtains the Session ID of the
	current process.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoGetCurrentProcessSessionID(
		_Out_ PDWORD SessionID)
	{
		BOOL result = FALSE;
		HANDLE hToken = INVALID_HANDLE_VALUE;
		DWORD ReturnLength = 0;

		result = OpenProcessToken(
			GetCurrentProcess(),
			MAXIMUM_ALLOWED,
			&hToken);
		if (result)
		{
			result = GetTokenInformation(
				hToken,
				TokenSessionId,
				SessionID,
				sizeof(DWORD),
				&ReturnLength);
		}

		return result;
	}

	/*
	NSudoSetTokenPrivilege函数启用或禁用指定的访问令牌的指定特权。启用或禁用一
	个访问令牌的特权需要TOKEN_ADJUST_PRIVILEGES访问权限。
	The NSudoSetTokenPrivilege function enables or disables the specified
	privilege in the specified access token. Enabling or disabling privileges
	in an access token requires TOKEN_ADJUST_PRIVILEGES access.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoSetTokenPrivilege(
		_In_ HANDLE hExistingToken,
		_In_ TOKEN_PRIVILEGES_LIST Privilege,
		_In_ bool bEnable)
	{
		TOKEN_PRIVILEGES TP;

		TP.PrivilegeCount = 1;
		TP.Privileges[0].Luid.LowPart = Privilege;
		TP.Privileges[0].Attributes = (DWORD)(bEnable ? SE_PRIVILEGE_ENABLED : 0);

		// 设置进程特权
		AdjustTokenPrivileges(hExistingToken, FALSE, &TP, 0, nullptr, nullptr);
		return (GetLastError() == ERROR_SUCCESS);
	}

	/*
	NSudoSetTokenAllPrivileges函数启用或禁用指定的访问令牌的所有特权。启用或禁
	用一个访问令牌的特权需要TOKEN_ADJUST_PRIVILEGES访问权限。
	The NSudoSetTokenAllPrivileges function enables or disables all privileges
	in the specified access token. Enabling or disabling privileges in an
	access token requires TOKEN_ADJUST_PRIVILEGES access.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoSetTokenAllPrivileges(
		_In_ HANDLE hExistingToken,
		_In_ bool bEnable)
	{
		BOOL result = FALSE;
		PTOKEN_PRIVILEGES pTPs = nullptr;
		DWORD Length = 0;

		// 获取特权信息大小
		GetTokenInformation(
			hExistingToken, TokenPrivileges, nullptr, 0, &Length);
		result = (GetLastError() == ERROR_INSUFFICIENT_BUFFER);
		if (result)
		{
			// 分配内存
			pTPs = (PTOKEN_PRIVILEGES)malloc(Length);
			if (pTPs)
			{
				// 获取特权信息
				result = GetTokenInformation(
					hExistingToken, TokenPrivileges, pTPs, Length, &Length);
				if (result)
				{
					// 设置特权信息
					for (DWORD i = 0; i < pTPs->PrivilegeCount; ++i)
						pTPs->Privileges[i].Attributes =
						(DWORD)(bEnable ? SE_PRIVILEGE_ENABLED : 0);

					// 设置进程特权
					AdjustTokenPrivileges(
						hExistingToken, FALSE, pTPs, 0, nullptr, nullptr);
					result = (GetLastError() == ERROR_SUCCESS);
				}

				// 释放内存
				free(pTPs);
			}
			else SetLastError(ERROR_NOT_ENOUGH_MEMORY);
		}

		return result;
	}

	/*
	NSudoSetTokenIntegrityLevel函数为指定的访问令牌设置完整性标签。
	The NSudoSetTokenIntegrityLevel function sets the integrity level for the
	specified access token.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoSetTokenIntegrityLevel(
		_In_ HANDLE TokenHandle,
		_In_ TOKEN_INTEGRITY_LEVELS_LIST IL)
	{
		BOOL result = FALSE;
		TOKEN_MANDATORY_LABEL TML;

		// 初始化SID
		result = AllocateAndInitializeSid(
			&SIA_IL, 1, IL, 0, 0, 0, 0, 0, 0, 0, &TML.Label.Sid);
		if (result)
		{
			// 初始化TOKEN_MANDATORY_LABEL
			TML.Label.Attributes = SE_GROUP_INTEGRITY;

			// 设置令牌对象
			result = SetTokenInformation(
				TokenHandle, TokenIntegrityLevel, &TML, sizeof(TML));

			// 释放SID
			FreeSid(TML.Label.Sid);
		}

		return result;
	}

	/*
	NSudoCreateLUAToken函数从一个现有的访问令牌创建一个新的LUA访问令牌。
	The NSudoCreateLUAToken function creates a new LUA access token from an
	existing access token.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoCreateLUAToken(
		_Out_ PHANDLE TokenHandle,
		_In_ HANDLE ExistingTokenHandle)
	{
		BOOL result = FALSE;
		DWORD Length = 0;
		BOOL EnableTokenVirtualization = TRUE;
		TOKEN_OWNER Owner = { 0 };
		TOKEN_DEFAULT_DACL NewTokenDacl = { 0 };
		PTOKEN_USER pTokenUser = nullptr;
		PTOKEN_DEFAULT_DACL pTokenDacl = nullptr;
		PSID pAdminSid = nullptr;
		PACCESS_ALLOWED_ACE pTempAce = nullptr;

		//创建受限令牌
		result = CreateRestrictedToken(
			ExistingTokenHandle,
			LUA_TOKEN,
			0, nullptr,
			0, nullptr,
			0, nullptr,
			TokenHandle);
		if (!result) goto FuncEnd;

		// 设置令牌完整性
		result = NSudoSetTokenIntegrityLevel(
			*TokenHandle, TOKEN_INTEGRITY_LEVELS_LIST::MediumLevel);
		if (!result) goto FuncEnd;

		// 获取令牌对应的用户账户SID信息大小
		GetTokenInformation(
			*TokenHandle, TokenUser, nullptr, 0, &Length);
		result = (GetLastError() == ERROR_INSUFFICIENT_BUFFER);
		if (!result) goto FuncEnd;

		// 为令牌对应的用户账户SID信息分配内存
		pTokenUser = (PTOKEN_USER)malloc(Length);
		if (!pTokenUser)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			goto FuncEnd;
		}

		// 获取令牌对应的用户账户SID信息
		result = GetTokenInformation(
			*TokenHandle, TokenUser, pTokenUser, Length, &Length);
		if (!result) goto FuncEnd;

		// 设置令牌Owner为当前用户
		Owner.Owner = pTokenUser->User.Sid;
		result = SetTokenInformation(
			*TokenHandle, TokenOwner, &Owner, sizeof(TOKEN_OWNER));
		if (!result) goto FuncEnd;

		// 获取令牌的DACL信息大小
		GetTokenInformation(
			*TokenHandle, TokenDefaultDacl, nullptr, 0, &Length);
		result = (GetLastError() == ERROR_INSUFFICIENT_BUFFER);
		if (!result) goto FuncEnd;

		// 为令牌的DACL信息分配内存
		pTokenDacl = (PTOKEN_DEFAULT_DACL)malloc(Length);
		if (!pTokenDacl)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			goto FuncEnd;
		}

		// 获取令牌的DACL信息
		result = GetTokenInformation(
			*TokenHandle, TokenDefaultDacl, pTokenDacl, Length, &Length);
		if (!result) goto FuncEnd;

		// 获取管理员组SID
		result = AllocateAndInitializeSid(
			&SIA_NT, 2,
			SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0, &pAdminSid);
		if (!result) goto FuncEnd;

		// 计算新ACL大小
		Length = pTokenDacl->DefaultDacl->AclSize;
		Length += GetLengthSid(pTokenUser->User.Sid);
		Length += sizeof(ACCESS_ALLOWED_ACE);

		// 分配ACL结构内存
		NewTokenDacl.DefaultDacl = (PACL)malloc(Length);
		if (!NewTokenDacl.DefaultDacl)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			goto FuncEnd;
		}

		// 创建ACL
		result = InitializeAcl(
			NewTokenDacl.DefaultDacl,
			Length,
			pTokenDacl->DefaultDacl->AclRevision);
		if (!result) goto FuncEnd;

		// 添加ACE
		result = AddAccessAllowedAce(
			NewTokenDacl.DefaultDacl,
			pTokenDacl->DefaultDacl->AclRevision,
			GENERIC_ALL,
			pTokenUser->User.Sid);
		if (!result) goto FuncEnd;

		// 复制ACE
		for (ULONG i = 0;
			GetAce(pTokenDacl->DefaultDacl, i, (PVOID*)&pTempAce);
			++i)
		{
			if (EqualSid(pAdminSid, &pTempAce->SidStart)) continue;

			AddAce(
				NewTokenDacl.DefaultDacl,
				pTokenDacl->DefaultDacl->AclRevision,
				0,
				pTempAce,
				pTempAce->Header.AceSize);
		}

		// 设置令牌DACL
		Length += sizeof(TOKEN_DEFAULT_DACL);
		result = SetTokenInformation(
			*TokenHandle, TokenDefaultDacl, &NewTokenDacl, Length);
		if (!result) goto FuncEnd;

		// 开启LUA虚拟化
		result = SetTokenInformation(
			*TokenHandle,
			TokenVirtualizationEnabled,
			&EnableTokenVirtualization,
			sizeof(BOOL));
		if (!result) goto FuncEnd;

	FuncEnd: // 扫尾

		if (NewTokenDacl.DefaultDacl) free(NewTokenDacl.DefaultDacl);
		if (pAdminSid) free(pAdminSid);
		if (pTokenDacl) free(pTokenDacl);
		if (pTokenUser) free(pTokenUser);
		if (!result)
		{
			CloseHandle(*TokenHandle);
			*TokenHandle = INVALID_HANDLE_VALUE;
		}

		return result;
	}

	/*
	NSudoCreateProcess函数创建一个新进程和对应的主线程
	The NSudoCreateProcess function creates a new process and its primary thread.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoCreateProcess(
		_In_opt_ HANDLE hToken,
		_In_opt_ LPCWSTR lpApplicationName,
		_Inout_opt_ LPWSTR lpCommandLine,
		_In_ DWORD dwCreationFlags,
		_In_opt_ LPVOID lpEnvironment,
		_In_opt_ LPCWSTR lpCurrentDirectory,
		_In_ LPSTARTUPINFOW lpStartupInfo,
		_Out_ LPPROCESS_INFORMATION lpProcessInformation)
	{
		BOOL result = FALSE;

		result = CreateProcessAsUserW(
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
			lpProcessInformation);

		if (!result)
		{
			result = CreateProcessWithTokenW(
				hToken,
				LOGON_WITH_PROFILE,
				lpApplicationName,
				lpCommandLine,
				dwCreationFlags,
				lpEnvironment,
				lpCurrentDirectory,
				lpStartupInfo,
				lpProcessInformation);
		}

		return result;
	}

	/*
	NSudoDuplicateProcessToken函数根据进程ID获取一个进程令牌的副本。
	The NSudoDuplicateProcessToken function obtains a copy of process token via
	Process ID.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoDuplicateProcessToken(
		_In_ DWORD dwProcessID,
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phToken)
	{
		BOOL result = FALSE;
		HANDLE hProcess = nullptr;
		HANDLE hToken = nullptr;

		// 打开进程对象
		hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, dwProcessID);
		if (hProcess)
		{
			// 打开进程令牌
			result = OpenProcessToken(hProcess, MAXIMUM_ALLOWED, &hToken);
			if (result)
			{
				// 复制令牌
				result = DuplicateTokenEx(
					hToken,
					dwDesiredAccess,
					lpTokenAttributes,
					ImpersonationLevel,
					TokenType,
					phToken);

				CloseHandle(hToken);
			}
			CloseHandle(hProcess);
		}

		return result;
	}

	/*
	NSudoDuplicateSystemToken函数获取一个当前会话SYSTEM用户令牌的副本。
	The NSudoDuplicateSystemToken function obtains a copy of current session 
	SYSTEM user token.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoDuplicateSystemToken(
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phToken)
	{
		BOOL result = FALSE;
		DWORD dwWinLogonPID = (DWORD)-1;
		DWORD dwSessionID = (DWORD)-1;

		PWTS_PROCESS_INFOW pProcesses = nullptr;
		DWORD dwProcessCount = 0;

		do
		{
			// 获取当前进程令牌会话ID
			result = NSudoGetCurrentProcessSessionID(&dwSessionID);
			if (!result) break;

			// 遍历进程寻找winlogon进程并获取PID
			if (WTSEnumerateProcessesW(
				WTS_CURRENT_SERVER_HANDLE,
				0,
				1,
				&pProcesses,
				&dwProcessCount))
			{

				for (DWORD i = 0; i < dwProcessCount; ++i)
				{
					PWTS_PROCESS_INFOW pProcess = &pProcesses[i];

					if (pProcess->SessionId != dwSessionID) continue;
					if (pProcess->pProcessName == nullptr) continue;

					if (wcscmp(L"winlogon.exe", pProcess->pProcessName) == 0)
					{
						dwWinLogonPID = pProcess->ProcessId;
						break;
					}
				}

				WTSFreeMemory(pProcesses);
			}

			// 如果没找到进程，则返回错误
			if (dwWinLogonPID == -1)
			{
				SetLastError(ERROR_NOT_FOUND);
				break;
			}

			// 复制进程令牌
			result = NSudoDuplicateProcessToken(
				dwWinLogonPID,
				dwDesiredAccess,
				lpTokenAttributes,
				ImpersonationLevel,
				TokenType,
				phToken);

		} while (false);

		return result;
	}

	/*
	NSudoDuplicateServiceToken函数根据服务名获取一个服务进程令牌的副本。
	The NSudoDuplicateServiceToken function obtains a copy of service process
	token via service name.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoDuplicateServiceToken(
		_In_ LPCWSTR lpServiceName,
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phToken)
	{
		BOOL result = FALSE;
		SERVICE_STATUS_PROCESS ssStatus;

		// 启动服务
		result = NSudoStartService(lpServiceName, &ssStatus);
		if (result)
		{
			// 复制进程令牌
			result = NSudoDuplicateProcessToken(
				ssStatus.dwProcessId,
				dwDesiredAccess,
				lpTokenAttributes,
				ImpersonationLevel,
				TokenType,
				phToken);
		}

		return result;
	}

	/*
	NSudoDuplicateSessionToken函数根据会话ID获取一个服务进程令牌的副本。
	The NSudoDuplicateSessionToken function obtains a copy of Session token via
	Session ID.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static HRESULT WINAPI NSudoDuplicateSessionToken(
		_In_ DWORD dwSessionID,
		_In_ DWORD dwDesiredAccess,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ TOKEN_TYPE TokenType,
		_Outptr_ PHANDLE phToken)
	{
		BOOL result = FALSE;
		HANDLE hToken = nullptr;

		// 打开会话令牌
		result = WTSQueryUserToken(dwSessionID, &hToken);
		if (result)
		{
			// 复制令牌
			result = DuplicateTokenEx(
				hToken,
				dwDesiredAccess,
				lpTokenAttributes,
				ImpersonationLevel,
				TokenType,
				phToken);

			CloseHandle(hToken);
		}

		return result;
	}

	/*
	NSudoImpersonateAsSystem函数给当前线程分配一个SYSTEM用户模拟令牌。该函数还
	可以使当前线程停止使用模拟令牌。
	The NSudoImpersonateAsSystem function assigns an SYSTEM user impersonation
	token to the current thread. The function can also cause the current thread
	to stop using an impersonation token.

	如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
	If the function fails, the return value is NULL. To get extended error
	information, call GetLastError.
	*/
	static BOOL WINAPI NSudoImpersonateAsSystem()
	{
		BOOL result = FALSE;
		HANDLE hToken = nullptr;

		// 获取当前会话SYSTEM用户令牌副本
		result = NSudoDuplicateSystemToken(
			MAXIMUM_ALLOWED,
			nullptr,
			SecurityImpersonation,
			TokenImpersonation,
			&hToken);
		if (result)
		{
			// 启用令牌全部特权
			result = NSudoSetTokenAllPrivileges(hToken, true);
			if (result)
			{
				// 模拟令牌
				result = SetThreadToken(nullptr, hToken);
			}

			CloseHandle(hToken);
		}

		return result;
	}

#ifdef __cplusplus
}
#endif

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif