/**************************************************************************
描述：NSudo库(对M2.Native, M2.WinSta, M2.Base的封装)
维护者：Mouri_Naruto (M2-Team)
版本：1.6 (2016-12-16)
基于项目：无
协议：The MIT License
用法：直接Include此头文件即可
建议的Windows SDK版本：10.0.10586及以后
***************************************************************************/

#pragma once

#ifndef M2_NSUDO
#define M2_NSUDO

// Windows 头文件
#include <windows.h>

// 基本库
#include "M2.Base.hpp"

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#endif

namespace M2
{
	// 令牌特权列表
	enum TokenPrivilegesList
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
	};

	// 令牌完整性
	enum IntegrityLevel
	{
		Untrusted = SECURITY_MANDATORY_UNTRUSTED_RID, // S-1-16-0
		Low = SECURITY_MANDATORY_LOW_RID, // S-1-16-4096
		Medium = SECURITY_MANDATORY_MEDIUM_RID, // S-1-16-8192
		MediumPlus = SECURITY_MANDATORY_MEDIUM_PLUS_RID, // S-1-16-8448
		High = SECURITY_MANDATORY_HIGH_RID, // S-1-16-12288
		System = SECURITY_MANDATORY_SYSTEM_RID, // S-1-16-16384
		Protected = SECURITY_MANDATORY_PROTECTED_PROCESS_RID // S-1-16-20480
	};

	// 特权设定
	enum PrivilegeOption
	{
		EnableAll,
		RemoveAll,
		RemoveMost
	};

	// 复制令牌
	static NTSTATUS SuDuplicateToken(
		_Out_ PHANDLE phNewToken,
		_In_ HANDLE hExistingToken,
		_In_ DWORD dwDesiredAccess = MAXIMUM_ALLOWED,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes = nullptr,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel = SecurityIdentification,
		_In_ TOKEN_TYPE TokenType = TokenPrimary)
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
	__forceinline NTSTATUS SuOpenProcess(
		_Out_ PHANDLE phProcess,
		_In_ DWORD dwProcessID,
		_In_ DWORD DesiredAccess = MAXIMUM_ALLOWED)
	{
		// 变量定义

		OBJECT_ATTRIBUTES ObjAttr;
		CLIENT_ID ClientID;

		// 参数初始化

		M2InitObjectAttributes(
			&ObjAttr, nullptr, 0, nullptr, nullptr, nullptr);
		M2InitClientID(
			&ClientID, dwProcessID, 0);

		// 根据进程ID获取进程句柄并返回运行结果
		return NtOpenProcess(
			phProcess, DesiredAccess, &ObjAttr, &ClientID);
	}

	// 通过进程ID获取进程令牌句柄
	static NTSTATUS SuQueryProcessToken(
		_Out_ PHANDLE phProcessToken,
		_In_ DWORD dwProcessID,
		_In_ DWORD DesiredAccess = MAXIMUM_ALLOWED)
	{
		// 变量定义	

		NTSTATUS status = 0;
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
	__forceinline HRESULT SuQuerySessionToken(
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
	__forceinline NTSTATUS SuQueryCurrentProcessToken(
		_Out_ PHANDLE phProcessToken,
		_In_ DWORD DesiredAccess = MAXIMUM_ALLOWED)
	{
		return NtOpenProcessToken(
			NtCurrentProcess(), DesiredAccess, phProcessToken);
	}

	// 令牌模拟
	__forceinline NTSTATUS SuImpersonate(
		_In_ HANDLE hExistingImpersonationToken)
	{
		return NtSetInformationThread(
			NtCurrentThread(),
			ThreadImpersonationToken,
			&hExistingImpersonationToken,
			sizeof(HANDLE));
	}

	// 撤销令牌模拟
	__forceinline NTSTATUS SuRevertImpersonate()
	{
		return SuImpersonate(nullptr);
	}

	// 设置单个令牌特权
	__forceinline NTSTATUS SuSetTokenPrivilege(
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
			hExistingToken, FALSE, &TP, NULL, nullptr, nullptr);
	}

	// 设置令牌全部特权
	static NTSTATUS SuSetTokenAllPrivileges(
		_In_ HANDLE hExistingToken,
		_In_ DWORD dwAttributes)
	{
		// 定义变量

		NTSTATUS status = 0;
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

	class CToken
	{
	public:
		// 构造函数
		CToken(
			_In_ HANDLE hToken = INVALID_HANDLE_VALUE)
		{
			m_hToken = hToken;
		}

		// 析构函数
		~CToken()
		{
			this->Close();
		}

		// 从进程句柄打开令牌
		NTSTATUS Open(
			_In_ HANDLE ProcessHandle = NtCurrentProcess(),
			_In_ ACCESS_MASK DesiredAccess = MAXIMUM_ALLOWED)
		{
			if (m_hToken != INVALID_HANDLE_VALUE) this->Close();
			return NtOpenProcessToken(ProcessHandle, DesiredAccess, &m_hToken);
		}

		// 关闭令牌
		void Close()
		{
			if (m_hToken != INVALID_HANDLE_VALUE)
			{
				NtClose(m_hToken);
				m_hToken = INVALID_HANDLE_VALUE;
			}
		}

		// 复制令牌
		NTSTATUS Duplicate(
			_Out_ CToken **ppNewToken,
			_In_ DWORD dwDesiredAccess = MAXIMUM_ALLOWED,
			_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes = nullptr,
			_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel = SecurityIdentification,
			_In_ TOKEN_TYPE TokenType = TokenPrimary)
		{
			
			// 变量定义
			HANDLE hTemp = INVALID_HANDLE_VALUE;

			// 复制令牌对象
			NTSTATUS status = SuDuplicateToken(
				&hTemp,
				m_hToken,
				dwDesiredAccess,
				lpTokenAttributes,
				ImpersonationLevel,
				TokenType);

			// 如果执行成功，则创建新令牌对象
			if (NT_SUCCESS(status)) *ppNewToken = new CToken(hTemp);
			
			// 返回运行结果
			return status;
		}

		// 获取令牌句柄
		operator HANDLE()
		{
			return m_hToken;
		}

		// 获取令牌信息
		NTSTATUS GetInfo(
			_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
			_Out_ PVOID TokenInformation,
			_In_ ULONG TokenInformationLength,
			_Out_ PULONG ReturnLength)
		{
			return NtQueryInformationToken(
				m_hToken,
				TokenInformationClass,
				TokenInformation,
				TokenInformationLength,
				ReturnLength);
		}

		// 获取令牌信息大小
		NTSTATUS GetInfoSize(
			_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
			_Out_ PULONG ReturnLength)
		{
			return NtQueryInformationToken(
				m_hToken, TokenInformationClass, nullptr, 0, ReturnLength);
		}

		// 设置令牌信息
		NTSTATUS SetInfo(
			_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
			_Out_ PVOID TokenInformation,
			_In_ ULONG TokenInformationLength)
		{
			return NtSetInformationToken(
				m_hToken,
				TokenInformationClass,
				TokenInformation,
				TokenInformationLength
			);
		}

		// 以当前令牌模拟
		bool Impersonate()
		{	
			bool bRet = false;
			CToken *pNewToken = nullptr;

			bRet = NT_SUCCESS(this->Duplicate(
				&pNewToken,
				MAXIMUM_ALLOWED, 
				nullptr,
				SecurityImpersonation,
				TokenImpersonation));

			if (bRet)
			{
				bRet = NT_SUCCESS(SuImpersonate(*pNewToken));
				delete pNewToken;
			}
			
			return bRet;
		}

		// 还原原令牌
		bool RevertToSelf()
		{		
			return NT_SUCCESS(SuRevertImpersonate());
		}

		// 制作LUA令牌
		NTSTATUS MakeLUA(
			_Out_ CToken **ppNewToken)
		{
			// 变量定义

			NTSTATUS status;
			HANDLE hTemp = INVALID_HANDLE_VALUE;
			DWORD Length = 0;
			CPtr<PTOKEN_USER> pTokenUser;
			CPtr<PTOKEN_OWNER> pTokenOwner;
			CPtr<PTOKEN_DEFAULT_DACL> pTokenDacl;
			PACL pAcl = nullptr;
			SID_IDENTIFIER_AUTHORITY SIDAuthority = SECURITY_NT_AUTHORITY;
			PSID TempSid = nullptr;
			CPtr<PSID> AdminSid;
			CPtr<PACL> pNewAcl;
			PACCESS_ALLOWED_ACE pTempAce = nullptr;
			TOKEN_DEFAULT_DACL NewTokenDacl = { 0 };
			BOOL EnableTokenVirtualization = TRUE;
			TOKEN_MANDATORY_POLICY policy = { 0 };

			//创建受限令牌

			status = NtFilterToken(
				m_hToken, LUA_TOKEN, nullptr, nullptr, nullptr, &hTemp);
			if (!NT_SUCCESS(status)) goto FuncEnd;
			*ppNewToken = new CToken(hTemp);

			// 以下代码仅适合管理员权限令牌（非强制性要求）
			// ********************************************************************

			// 设置令牌完整性

			if (!NT_SUCCESS((*ppNewToken)->SetIL(Medium)))
				goto FuncEnd;

			// 获取令牌对应的用户账户SID

			(*ppNewToken)->GetInfoSize(TokenUser, &Length);
			if (!pTokenUser.Alloc(Length)) goto FuncEnd;
			if (!NT_SUCCESS(
				(*ppNewToken)->GetInfo(
					TokenUser, pTokenUser, Length, &Length)))
				goto FuncEnd;

			// 设置令牌Owner为当前用户

			if (!pTokenOwner.Alloc(sizeof(TOKEN_OWNER))) goto FuncEnd;
			pTokenOwner->Owner = pTokenUser->User.Sid;
			if (!NT_SUCCESS((*ppNewToken)->SetInfo(
				TokenOwner, pTokenOwner, sizeof(TOKEN_OWNER))))
				goto FuncEnd;

			//获取令牌的DACL

			(*ppNewToken)->GetInfoSize(TokenDefaultDacl, &Length);
			if (!pTokenDacl.Alloc(Length)) goto FuncEnd;
			if (!NT_SUCCESS(
				(*ppNewToken)->GetInfo(
					TokenDefaultDacl, pTokenDacl, Length, &Length)))
				goto FuncEnd;
			pAcl = pTokenDacl->DefaultDacl;

			// 获取管理员组SID

			if (!NT_SUCCESS(RtlAllocateAndInitializeSid(
				&SIDAuthority, 2,
				SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
				0, 0, 0, 0, 0, 0, &TempSid)))
				goto FuncEnd;
			AdminSid = TempSid;
			TempSid = nullptr;

			// 计算新ACL大小

			Length += RtlLengthSid(pTokenUser->User.Sid);
			Length += sizeof(ACCESS_ALLOWED_ACE);

			// 分配ACL结构内存

			if (!pNewAcl.Alloc(Length)) goto FuncEnd;

			// 创建ACL

			if (!NT_SUCCESS(RtlCreateAcl(
				pNewAcl, Length, pAcl->AclRevision)))
				goto FuncEnd;

			// 添加ACE

			if (!NT_SUCCESS(RtlAddAccessAllowedAce(
				pNewAcl, pAcl->AclRevision,
				GENERIC_ALL, pTokenUser->User.Sid)))
				goto FuncEnd;

			// 复制ACE

			for (ULONG i = 0;
				NT_SUCCESS(RtlGetAce(pAcl, i, (PVOID*)&pTempAce));
				i++)
			{
				if (RtlEqualSid(AdminSid, &pTempAce->SidStart)) continue;

				RtlAddAce(pNewAcl, pAcl->AclRevision, 0,
					pTempAce, pTempAce->Header.AceSize);
			}

			// 设置令牌DACL

			Length += sizeof(TOKEN_DEFAULT_DACL);
			NewTokenDacl.DefaultDacl = pNewAcl;
			if (!NT_SUCCESS((*ppNewToken)->SetInfo(
				TokenDefaultDacl, &NewTokenDacl, Length)))
				goto FuncEnd;

			// 打开LUA虚拟化

			if (!NT_SUCCESS((*ppNewToken)->SetInfo(
				TokenVirtualizationEnabled,
				&EnableTokenVirtualization,
				sizeof(BOOL))))
				goto FuncEnd;

			policy.Policy = TOKEN_MANDATORY_POLICY_NO_WRITE_UP | TOKEN_MANDATORY_POLICY_NEW_PROCESS_MIN;

			if (!NT_SUCCESS((*ppNewToken)->SetInfo(
				TokenMandatoryPolicy,
				&policy,
				sizeof(TOKEN_MANDATORY_POLICY))))
				goto FuncEnd;

			// ********************************************************************

			// 扫尾

		FuncEnd:

			return status;
		}

		// 设置令牌完整性
		NTSTATUS SetIL(
			_In_ IntegrityLevel IL)
		{
			// 变量定义
			NTSTATUS status;
			TOKEN_MANDATORY_LABEL TML;
			SID_IDENTIFIER_AUTHORITY SIDAuthority = SECURITY_MANDATORY_LABEL_AUTHORITY;

			// 初始化SID
			status = RtlAllocateAndInitializeSid(
				&SIDAuthority, 1, IL,
				0, 0, 0, 0, 0, 0, 0, &TML.Label.Sid);
			if (!NT_SUCCESS(status)) goto FuncEnd;

			// 初始化TOKEN_MANDATORY_LABEL
			TML.Label.Attributes = SE_GROUP_INTEGRITY;

			// 设置令牌对象
			status = NtSetInformationToken(
				m_hToken, TokenIntegrityLevel, &TML, sizeof(TML));
			if (!NT_SUCCESS(status)) goto FuncEnd;

			// 扫尾

		FuncEnd:
			if (TML.Label.Sid) RtlFreeSid(TML.Label.Sid);

			return status;
		}

		// 设置令牌特权
		bool SetPrivilege(
			_In_ TokenPrivilegesList Privilege,
			_In_ bool bEnable)
		{
			// 设置令牌特权
			NTSTATUS status = SuSetTokenPrivilege(m_hToken, Privilege, bEnable);

			// 返回结果
			return RtlNtStatusToDosError(status) == ERROR_SUCCESS;
		}

		// 设置令牌特权
		bool SetPrivilege(
			_In_ PrivilegeOption Option)
		{
			// 变量定义

			NTSTATUS status;
			bool result = false;
			DWORD Length = 0;
			CPtr<PTOKEN_PRIVILEGES> pTPs;
			HANDLE hTemp = INVALID_HANDLE_VALUE;
			DWORD Attributes = (DWORD)-1;

			// 执行操作
			if (Option == RemoveMost)
			{
				status = NtFilterToken(
					m_hToken, DISABLE_MAX_PRIVILEGE,
					nullptr, nullptr, nullptr, &hTemp);

				result = NT_SUCCESS(status);

				if (result)
				{
					NtClose(m_hToken);
					m_hToken = hTemp;
				}
			}
			else
			{
				this->GetInfoSize(TokenPrivileges, &Length);
				if (!pTPs.Alloc(Length)) return result;

				if (Option == EnableAll) Attributes = SE_PRIVILEGE_ENABLED;
				if (Option == RemoveAll) Attributes = SE_PRIVILEGE_REMOVED;

				// 设置令牌全部特权
				status = SuSetTokenAllPrivileges(m_hToken, Attributes);

				result = NT_SUCCESS(status);
			}

			return result;
		}

	private:
		HANDLE m_hToken = INVALID_HANDLE_VALUE;
	};

	class CProcessSnapshot
	{
	public:
		// 构造函数
		CProcessSnapshot(
			_Out_ PNTSTATUS Status)
		{
			*Status = this->Refresh();
		}

		// 刷新快照
		NTSTATUS Refresh()
		{
			NTSTATUS Status;
			DWORD dwLength = 0;

			// 获取大小
			NtQuerySystemInformation(
				SystemProcessInformation, nullptr, 0, &dwLength);

			// 分配内存
			if (lpBuffer.Alloc(dwLength))
			{
				// 获取进程信息
				Status = NtQuerySystemInformation(
					SystemProcessInformation, lpBuffer, dwLength, &dwLength);
				pTemp = (ULONG_PTR)(PVOID)lpBuffer;
			}
			else Status = STATUS_NO_MEMORY;

			return Status;
		}

		// 遍历
		bool Next(
			_Out_ PSYSTEM_PROCESS_INFORMATION *pSPI)
		{
			// 设置pSPI为pTemp
			*pSPI = (PSYSTEM_PROCESS_INFORMATION)pTemp;

			// 如果*pSPI=0或下个结构偏移=0时则pTemp=0，否则pTemp=下个结构地址
			if (!*pSPI || !(*pSPI)->NextEntryOffset) pTemp = 0;
			else pTemp += (*pSPI)->NextEntryOffset;

			// 返回执行结果
			return (*pSPI != nullptr);
		}

	private:
		CPtr<PVOID> lpBuffer;
		ULONG_PTR pTemp = 0;
	};

	class CProcess
	{
	public:
		// 构造函数
		CProcess(
			_In_ DWORD dwProcessID)
		{
			m_dwProcessId = dwProcessID;
		}

		// 析构函数
		virtual ~CProcess()
		{
			this->Close();
		}

		// 打开进程句柄
		NTSTATUS Open(
			_In_ ACCESS_MASK DesiredAccess = MAXIMUM_ALLOWED)
		{
			if (m_hProcess != INVALID_HANDLE_VALUE) this->Close();

			return SuOpenProcess(
				&m_hProcess, m_dwProcessId, DesiredAccess);
		}

		// 关闭进程句柄
		void Close()
		{
			if (m_hProcess != INVALID_HANDLE_VALUE)
			{
				NtClose(m_hProcess);
				m_hProcess = INVALID_HANDLE_VALUE;
			}
		}

		// 获取进程句柄
		operator HANDLE()
		{
			return m_hProcess;
		}

		// 结束进程
		NTSTATUS Kill(
			_In_ NTSTATUS ExitStatus)
		{
			return NtTerminateProcess(m_hProcess, ExitStatus);
		}

		// 挂起进程
		NTSTATUS Suspend()
		{
			return NtSuspendProcess(m_hProcess);
		}

		// 恢复进程
		NTSTATUS Resume()
		{
			return NtResumeProcess(m_hProcess);
		}

	private:
		DWORD m_dwProcessId = (DWORD)-1;
		HANDLE m_hProcess = INVALID_HANDLE_VALUE;
	};

	class CNSudo
	{
	public:
		// 构造函数
		CNSudo()
		{
			bool bRet = false;
			HANDLE hProcessToken = nullptr;
			NTSTATUS status = 0;

			// 打开当前进程令牌（判断NSudo接口是否可用）
			bRet = NT_SUCCESS(SuQueryCurrentProcessToken(&hProcessToken));
			if (!bRet) return;

			// 初始化当前令牌管理接口
			m_pCurrentToken = new CToken(hProcessToken);
			if (!m_pCurrentToken) return;
			m_dwAvailableLevel++;

			// 开启调试特权（判断是否为管理员）
			bRet = m_pCurrentToken->SetPrivilege(
				TokenPrivilegesList::SeDebugPrivilege, true);
			if (!bRet) return;
			m_dwAvailableLevel++;

			// 获取当前会话ID下的winlogon的PID
			DWORD dwWinLogonPID = (DWORD)-1;

			// 初始化进程遍历
			CProcessSnapshot Snapshot(&status);
			if (!NT_SUCCESS(status)) return;

			// 遍历进程寻找winlogon进程并获取PID
			PSYSTEM_PROCESS_INFORMATION pSPI = nullptr;
			while (Snapshot.Next(&pSPI))
			{
				if (pSPI->SessionId == M2GetCurrentSessionID())
				{
					if (wcscmp(L"winlogon.exe", pSPI->ImageName.Buffer) == 0)
					{
						dwWinLogonPID = HandleToUlong(pSPI->UniqueProcessId);
						break;
					}
				}
			}
			if (dwWinLogonPID == -1) return;

			// 获取winlogon进程令牌并获取其副本
			bRet = GetProcessTokenByProcessID(dwWinLogonPID, &m_SystemToken);
			if (bRet) m_dwAvailableLevel++;
		}

		// 析构函数
		~CNSudo()
		{
			if (m_pCurrentToken) delete m_pCurrentToken;
		}

		// 获取可用等级（-1 不可用, 0 可用, 1 已提升, 2 已获取System令牌）
		long GetAvailableLevel()
		{
			return m_dwAvailableLevel;
		}

		// 根据PID获取对应进程的令牌
		bool GetProcessTokenByProcessID(
			_In_ DWORD dwProcessID,
			_Out_ CToken **NewToken)
		{
			bool bRet = false;
			HANDLE hToken = nullptr;

			if (NT_SUCCESS(SuQueryProcessToken(&hToken, dwProcessID)))
			{
				bRet = NT_SUCCESS(CToken(hToken).Duplicate(NewToken));
			}

			return bRet;
		}

		// 获取当前进程令牌
		bool GetCurrentToken(
			_Out_ CToken **NewToken)
		{
			if (!(m_dwAvailableLevel >= 0)) return false;
			return NT_SUCCESS(m_pCurrentToken->Duplicate(NewToken));
		}

		// 获取System令牌
		bool GetSystemToken(
			_Out_ CToken **NewToken)
		{
			if (!(m_dwAvailableLevel == 2)) return false;
			return NT_SUCCESS(m_SystemToken->Duplicate(NewToken));
		}

		// 模拟System令牌(需要可用等级2，调用RevertToSelf()取消模拟)
		bool ImpersonateAsSystem()
		{
			bool bRet = false;
			CToken *SystemToken = nullptr;
			if (this->GetSystemToken(&SystemToken)) // 获取System权限令牌
			{
				SystemToken->SetPrivilege(EnableAll);
				bRet = SystemToken->Impersonate();
			}
			return bRet;
		}

		// 设置令牌的SessionID
		bool SetTokenSessionID(
			_Inout_ CToken **Token,
			_In_ ULONG SessionId)
		{
			return NT_SUCCESS((*Token)->SetInfo(
				TokenSessionId,
				(PVOID)&SessionId,
				sizeof(DWORD)));
		}

		// 获取当前用户令牌(需要System令牌或者模拟System令牌)
		bool GetCurrentUserToken(
			_In_ ULONG SessionId,
			_Out_ CToken **NewToken)
		{
			HANDLE hToken = nullptr;
			bool bRet = SUCCEEDED(SuQuerySessionToken(&hToken, SessionId));
			if (bRet) *NewToken = new CToken(hToken);
			return bRet;
		}

		// 获取TrustedInstaller令牌(需要System令牌或者模拟System令牌)
		bool GetTrustedInstallerToken(
			_Out_ CToken **NewToken)
		{
			bool bRet = false;

			//启动TrustedInstaller服务并获取SID
			DWORD dwTIPID = M2StartService(L"TrustedInstaller");

			if (dwTIPID != -1)
			{
				// 根据进程PID获取令牌
				if (GetProcessTokenByProcessID(dwTIPID, NewToken))
				{
					// 设置令牌会话为当前用户
					bRet = SetTokenSessionID(
						NewToken, M2GetCurrentSessionID());

					// 如果执行失败释放令牌
					if (!bRet)
					{
						delete *NewToken;
						*NewToken = nullptr;
					}
				}
			}

			return bRet;
		}

		// 还原原令牌
		bool RevertToSelf()
		{
			return NT_SUCCESS(SuRevertImpersonate());
		}

	private:
		long m_dwAvailableLevel = -1;
		CToken *m_pCurrentToken = nullptr;
		CToken *m_SystemToken = nullptr;
	};

	//****************************************************************

	// System令牌模拟
	static NTSTATUS SuImpersonateAsSystem()
	{
		NTSTATUS status = 0;

		// 获取当前会话ID下的winlogon的PID
		DWORD dwWinLogonPID = (DWORD)-1;

		// 初始化进程遍历
		CProcessSnapshot Snapshot(&status);
		if (!NT_SUCCESS(status)) return status;

		// 遍历进程寻找winlogon进程并获取PID
		PSYSTEM_PROCESS_INFORMATION pSPI = nullptr;
		while (Snapshot.Next(&pSPI))
		{
			if (pSPI->SessionId == M2GetCurrentSessionID())
			{
				if (wcscmp(L"winlogon.exe", pSPI->ImageName.Buffer) == 0)
				{
					dwWinLogonPID = HandleToUlong(pSPI->UniqueProcessId);
					break;
				}
			}
		}
		if (dwWinLogonPID == -1) 
			return __HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);

		HANDLE hProcessToken = nullptr;
		HANDLE hDuplicatedToken = nullptr;
		
		do
		{
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

		return status;
	}
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif