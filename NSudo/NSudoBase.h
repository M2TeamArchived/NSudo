//NSudo 核心库

#pragma once

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

// Integrity Level
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

//获取令牌信息大小
#define SuTokenGetInfoSize(Handle, TokenInfoClass, ReturnLength) \
	NtQueryInformationToken(Handle, TokenInfoClass, NULL, NULL, ReturnLength)

//获取进程令牌
#define SuGetPsToken(ProcessHandle, TokenHandle) \
	NtOpenProcessToken(ProcessHandle, MAXIMUM_ALLOWED, TokenHandle)

//获取当前进程令牌
#define SuGetCurrentPsToken(TokenHandle) \
	SuGetPsToken(NtCurrentProcess(), TokenHandle)

//获取进程句柄
NTSTATUS SuOpenProcess(
	_In_ DWORD dwProcessId,
	_Out_ PHANDLE ProcessHandle);

//创建令牌副本
NTSTATUS WINAPI SuDuplicateToken(
	_In_ HANDLE ExistingToken,
	_Out_ PHANDLE NewTokenHandle);

//获取令牌信息(自动分配所需内存)
NTSTATUS WINAPI SuGetTokenInfo(
	_In_ HANDLE TokenHandle,
	_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
	_Out_ void*& TokenInformation,
	_Out_ PULONG ReturnLength);

//开启令牌所有特权
NTSTATUS WINAPI SuEnableAllTokenPrivileges(
	_In_ HANDLE TokenHandle);

//移除大部分令牌特权
#define SuRemoveMaximumTokenPrivileges(ExistingTokenHandle, NewTokenHandle) \
	NtFilterToken(ExistingTokenHandle, \
		DISABLE_MAX_PRIVILEGE, NULL, NULL, NULL, NewTokenHandle)

//获取一个进程的PID
DWORD WINAPI SuGetProcessID(
	_In_ LPCWSTR lpProcessName,
	_In_ bool bUnderCurrentSessionID);

//启动一个服务并返回服务进程ID
DWORD WINAPI SuStartService(
	_In_ LPCWSTR lpServiceName);

//获取System权限令牌(需要SE_DEBUG_NAME特权)
bool SuGetSystemToken(
	_In_ PHANDLE hNewToken);

//模拟当前进程的权限令牌为System权限(如果想取消模拟，可以调用RevertToSelf)
bool SuImpersonateSystemToken();

//获取TrustedInstaller令牌
bool SuGetTrustedInstallerToken(
	_In_ PHANDLE hNewToken);

//获取当前用户的令牌(需要SE_DEBUG_NAME特权)
bool SuGetCurrentUserToken(
	_In_ PHANDLE hNewToken);

//设置令牌完整性
NTSTATUS WINAPI SuSetTokenIL(
	_In_ HANDLE TokenHandle,
	_In_ DWORD IntegrityLabelRID);

//创建一个对应的降权令牌
NTSTATUS WINAPI SuCreateLUAToken(
	_In_ HANDLE ExistingTokenHandle,
	_Out_ PHANDLE NewTokenHandle);

//为令牌设置特权
bool SuSetTokenPrivilege(
	_In_ HANDLE TokenHandle,
	_In_ TokenPrivilegesList Privilege,
	_In_ bool bEnable);

//设置当前进程令牌权限
bool SuSetCurrentPsPrivilege(
	_In_ TokenPrivilegesList Privilege,
	_In_ bool bEnable);