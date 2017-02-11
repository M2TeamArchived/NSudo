#pragma once

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
	NTSTATUS SuDuplicateToken(
		_Out_ PHANDLE phNewToken,
		_In_ HANDLE hExistingToken,
		_In_ DWORD dwDesiredAccess = MAXIMUM_ALLOWED,
		_In_opt_ LPSECURITY_ATTRIBUTES lpTokenAttributes = nullptr,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel = SecurityIdentification,
		_In_ TOKEN_TYPE TokenType = TokenPrimary);

	// 通过进程ID获取进程句柄
	NTSTATUS SuOpenProcess(
		_Out_ PHANDLE phProcess,
		_In_ DWORD dwProcessID,
		_In_ DWORD DesiredAccess = MAXIMUM_ALLOWED);

	// 通过进程ID获取进程令牌句柄
	NTSTATUS SuQueryProcessToken(
		_Out_ PHANDLE phProcessToken,
		_In_ DWORD dwProcessID,
		_In_ DWORD DesiredAccess = MAXIMUM_ALLOWED);

	// 通过会话ID获取会话令牌
	HRESULT SuQuerySessionToken(
		_Out_ PHANDLE phToken,
		_In_ DWORD dwSessionID);

	// 获取当前进程令牌
	NTSTATUS SuQueryCurrentProcessToken(
		_Out_ PHANDLE phProcessToken,
		_In_ DWORD DesiredAccess = MAXIMUM_ALLOWED);

	// 令牌模拟
	NTSTATUS SuImpersonate(
		_In_ HANDLE hExistingImpersonationToken);

	// 撤销令牌模拟
	NTSTATUS SuRevertImpersonate();

	// 设置单个令牌特权
	NTSTATUS SuSetTokenPrivilege(
		_In_ HANDLE hExistingToken,
		_In_ TokenPrivilegesList Privilege,
		_In_ bool bEnable);

	// 设置令牌全部特权
	NTSTATUS SuSetTokenAllPrivileges(
		_In_ HANDLE hExistingToken,
		_In_ DWORD dwAttributes);

	// SID_IDENTIFIER_AUTHORITY结构长度
	const SIZE_T SidAuth_Length = sizeof(SID_IDENTIFIER_AUTHORITY);

	// SID_IDENTIFIER_AUTHORITY的预定义结构

	static SID_IDENTIFIER_AUTHORITY SidAuth_NT = SECURITY_NT_AUTHORITY;
	static SID_IDENTIFIER_AUTHORITY SidAuth_World = SECURITY_WORLD_SID_AUTHORITY;
	static SID_IDENTIFIER_AUTHORITY SidAuth_App = SECURITY_APP_PACKAGE_AUTHORITY;
	static SID_IDENTIFIER_AUTHORITY SIDAuth_IL = SECURITY_MANDATORY_LABEL_AUTHORITY;

	//判断是否为登录SID
	bool SuIsLogonSid(
		_In_ PSID pSid);

	// 设置内核对象完整性标签
	NTSTATUS SuSetKernelObjectIntegrityLevel(
		_In_ HANDLE Object,
		_In_ IntegrityLevel IL);

	// 设置令牌完整性标签
	NTSTATUS SuSetTokenIntegrityLevel(
		_In_ HANDLE TokenHandle,
		_In_ IntegrityLevel IL);

	// 获取令牌信息（该函数自动分配的内存需要使用M2HeapFree释放）
	template<typename TokenInformationType>
	static NTSTATUS SuQueryInformationToken(
		_In_ HANDLE TokenHandle,
		_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
		_Out_ TokenInformationType &TokenInformation)
	{
		// 定义变量
		NTSTATUS status = STATUS_SUCCESS;
		ULONG ReturnLength = 0;

		// 获取令牌信息大小，如果失败则返回
		status = NtQueryInformationToken(
			TokenHandle,
			TokenInformationClass,
			nullptr,
			0,
			&ReturnLength);
		if (status != STATUS_BUFFER_TOO_SMALL) return status;

		// 为令牌信息分配内存，如果失败则返回
		status = M2HeapAlloc(ReturnLength, TokenInformation);
		if (!NT_SUCCESS(status)) return status;

		// 获取令牌信息，如果失败则释放刚刚分配的内存
		status = NtQueryInformationToken(
			TokenHandle,
			TokenInformationClass,
			TokenInformation,
			ReturnLength,
			&ReturnLength);
		if (!NT_SUCCESS(status)) M2HeapFree(TokenInformation);

		// 返回运行结果
		return status;
	}

	// 根据已提权令牌创建一个降权为标准用户的令牌
	NTSTATUS SuCreateLUAToken(
		_Out_ PHANDLE TokenHandle,
		_In_ HANDLE ExistingTokenHandle);

	// 启动一个服务并返回服务进程ID
	DWORD SuStartService(
		_In_ LPCWSTR lpServiceName);

	// 获取进程信息（该函数自动分配的内存需要使用M2HeapFree释放）
	NTSTATUS SuQuerySystemProcessInformation(
		_Out_ PSYSTEM_PROCESS_INFORMATION *ppSystemProcessInformation);

	// 模仿System令牌
	NTSTATUS SuImpersonateAsSystem();
}