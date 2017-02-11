/**************************************************************************
描述：NSudo库(对M2.Native, M2.WinSta, M2.Base的封装)
维护者：Mouri_Naruto (M2-Team)
版本：2.1 (2017-01-05)
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

// NSudo库
#include "M2.NSudoLib.h"
#pragma comment(lib, "NSudoLib.lib")

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#endif

namespace M2
{
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
			NTSTATUS status = STATUS_SUCCESS;
			HANDLE hNewToken = INVALID_HANDLE_VALUE;
					
			status = SuCreateLUAToken(&hNewToken, m_hToken);
			if (NT_SUCCESS(status)) *ppNewToken = new CToken(hNewToken);

			return status;
		}

		// 设置令牌完整性
		NTSTATUS SetIL(
			_In_ IntegrityLevel IL)
		{		
			return SuSetTokenIntegrityLevel(m_hToken, IL);
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
			NTSTATUS status = STATUS_SUCCESS;
			DWORD dwLength = 0;

			// 获取大小
			NtQuerySystemInformation(
				SystemProcessInformation, nullptr, 0, &dwLength);

			// 分配内存
			if (lpBuffer.Alloc(dwLength))
			{
				// 获取进程信息
				status = NtQuerySystemInformation(
					SystemProcessInformation, lpBuffer, dwLength, &dwLength);
				pTemp = (ULONG_PTR)(PVOID)lpBuffer;
			}
			else status = STATUS_NO_MEMORY;

			return status;
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
			DWORD dwTIPID = SuStartService(L"TrustedInstaller");

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

	/*
	const DWORD CapabilitiyTypeRID[] =
	{
	SECURITY_CAPABILITY_INTERNET_CLIENT,
	SECURITY_CAPABILITY_PRIVATE_NETWORK_CLIENT_SERVER,
	SECURITY_CAPABILITY_SHARED_USER_CERTIFICATES,
	SECURITY_CAPABILITY_ENTERPRISE_AUTHENTICATION,
	};

	*/


	//创建沙盒Job对象
	/*static NTSTATUS WINAPI SuCreateSandBoxJobObject(
	_Out_ PHANDLE JobObject)
	{
	//定义变量
	NTSTATUS status = NULL;
	OBJECT_ATTRIBUTES ObjectAttributes =
	{
	sizeof(OBJECT_ATTRIBUTES), // Length
	NULL, // RootDirectory
	NULL, // ObjectName
	OBJ_OPENIF, // Attributes
	NULL, // SecurityDescriptor
	NULL // SecurityQualityOfService
	};
	JOBOBJECT_EXTENDED_LIMIT_INFORMATION JELI = { 0 };

	//创建Job对象
	status = NtCreateJobObject(JobObject, MAXIMUM_ALLOWED, &ObjectAttributes);
	if (!NT_SUCCESS(status)) return status;

	//添加限制并返回
	JELI.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	return NtSetInformationJobObject(
	*JobObject, JobObjectExtendedLimitInformation, &JELI, sizeof(JELI));
	}*/

}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif