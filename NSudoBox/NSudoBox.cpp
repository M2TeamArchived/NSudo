/**************************************************************************
项目:
M2-Team\\NSudo\\NSudoBox
描述：
NSudoBox（NSudo沙箱）实现
文件名:
\\NSudoBox\\NSudoBox.cpp
许可协议：
The MIT License
维护者列表：
Mouri_Naruto (Mouri_Naruto@Outlook.com)
修订日志：
1.2 (2017-01-14)
1.从NSudo.AppContainer项目fork出来
2.增加 SuCreateSandboxJobObject API

1.1 (2017-01-05)
1.为了解决系统的兼容性问题，从NSudoSDK项目独立出来
2.优化 SuCreateAppContainerToken API
3.增加 SuGenerateAppContainerCapabilities API

1.0 (2017-01-01)
初始版本，原属于NSudoSDK
***************************************************************************/

#include "stdafx.h"

using namespace M2;

// 创建沙盒令牌
#pragma region SuCreateSandboxToken

// AppContainer对象列表
const enum SuAppContainerHandleList
{
	RootDirectory, // 主目录对象
	RpcDirectory,  // RPC目录对象
	GlobalSymbolicLink, // Global符号链接
	LocalSymbolicLink, // Local符号链接
	SessionSymbolicLink, // Session符号链接
	NamedPipe //命名管道
};

//构建沙盒安全标识符
NTSTATUS WINAPI SuBuildSandboxSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR ExistingSecurityDescriptor,
	_In_ PSID SandBoxSid,
	_In_ PSID UserSid,
	_In_ bool IsRpcControl,
	_Out_ PSECURITY_DESCRIPTOR *NewSecurityDescriptor)
{
	//定义变量
	NTSTATUS status = STATUS_SUCCESS;
	DWORD ReturnLength = 0;
	BOOLEAN DaclPresent = FALSE;
	BOOLEAN DaclDefaulted = FALSE;
	PACL pAcl = nullptr;
	PACL pNewAcl = nullptr;
	PSID AdminSid = nullptr;
	PSID RestrictedSid = nullptr;
	PSID WorldSid = nullptr;
	bool bUserSidExist = false;
	PACCESS_ALLOWED_ACE pTempAce = nullptr;

	//生成受限组SID结构
	status = RtlAllocateAndInitializeSid(
		&SidAuth_NT, 1, SECURITY_RESTRICTED_CODE_RID,
		0, 0, 0, 0, 0, 0, 0, &RestrictedSid);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//生成管理员组SID结构
	status = RtlAllocateAndInitializeSid(
		&SidAuth_NT, 2, SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdminSid);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//生成Everyone组SID结构
	status = RtlAllocateAndInitializeSid(
		&SidAuth_World, 1, SECURITY_WORLD_RID,
		0, 0, 0, 0, 0, 0, 0, &WorldSid);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//获取现有对象的ACL
	status = RtlGetDaclSecurityDescriptor(
		ExistingSecurityDescriptor, &DaclPresent, &pAcl, &DaclDefaulted);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//计算新ACL大小
	ReturnLength = pAcl->AclSize;
	ReturnLength += RtlLengthSid(SandBoxSid) * 2;
	ReturnLength += RtlLengthSid(UserSid) * 2;
	ReturnLength += RtlLengthSid(RestrictedSid);
	ReturnLength += RtlLengthSid(AdminSid);
	ReturnLength += RtlLengthSid(WorldSid);
	ReturnLength += sizeof(ACCESS_ALLOWED_ACE) * 7;

	//分配ACL结构内存
	status = M2HeapAlloc(ReturnLength, pNewAcl);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//创建ACL
	status = RtlCreateAcl(pNewAcl, ReturnLength, pAcl->AclRevision);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//复制ACE
	for (ULONG i = 0; NT_SUCCESS(RtlGetAce(pAcl, i, (PVOID*)&pTempAce)); i++)
	{
		//检测登陆SID并对权限做出修改
		if (SuIsLogonSid(&pTempAce->SidStart)
			&& !(pTempAce->Header.AceFlags & INHERIT_ONLY_ACE))
		{
			pTempAce->Mask = DIRECTORY_ALL_ACCESS;
		}

		//如果不是是rpc句柄则跳过管理员和Everyone的SID添加
		if (!IsRpcControl
			&& (RtlEqualSid(&pTempAce->SidStart, AdminSid)
				|| RtlEqualSid(&pTempAce->SidStart, RestrictedSid)
				|| RtlEqualSid(&pTempAce->SidStart, WorldSid))) continue;

		//如果是用户SID存在则标记
		if (RtlEqualSid(&pTempAce->SidStart, UserSid))
			bUserSidExist = true;

		//添加ACE
		RtlAddAce(pNewAcl, pAcl->AclRevision, 0,
			pTempAce, pTempAce->Header.AceSize);
	}

	//添加ACE（特殊） - 沙盒SID
	status = RtlAddAccessAllowedAce(
		pNewAcl,
		pAcl->AclRevision,
		DIRECTORY_ALL_ACCESS,
		SandBoxSid);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//添加ACE（InheritNone） - 沙盒SID
	status = RtlAddAccessAllowedAceEx(
		pNewAcl,
		pAcl->AclRevision,
		OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE,
		GENERIC_ALL,
		SandBoxSid);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	if (!bUserSidExist)
	{
		//添加ACE（特殊） - 用户SID
		status = RtlAddAccessAllowedAce(
			pNewAcl,
			pAcl->AclRevision,
			DIRECTORY_ALL_ACCESS,
			UserSid);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		//添加ACE（InheritNone） - 用户SID
		status = RtlAddAccessAllowedAceEx(
			pNewAcl,
			pAcl->AclRevision,
			OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE,
			GENERIC_ALL,
			UserSid);
		if (!NT_SUCCESS(status)) goto FuncEnd;
	}

	if (IsRpcControl)
	{
		//添加ACE（InheritNone） - 管理员SID
		status = RtlAddAccessAllowedAceEx(
			pNewAcl,
			pAcl->AclRevision,
			OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE,
			GENERIC_ALL,
			AdminSid);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		//添加ACE（InheritNone） - 受限SID
		status = RtlAddAccessAllowedAceEx(
			pNewAcl,
			pAcl->AclRevision,
			OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE,
			GENERIC_READ | GENERIC_EXECUTE,
			RestrictedSid);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		//添加ACE（InheritNone） - Everyone SID
		status = RtlAddAccessAllowedAceEx(
			pNewAcl,
			pAcl->AclRevision,
			OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE,
			GENERIC_READ | GENERIC_EXECUTE,
			WorldSid);
		if (!NT_SUCCESS(status)) goto FuncEnd;
	}

	//分配SD结构内存
	status = M2HeapAlloc(
		sizeof(SECURITY_DESCRIPTOR), *NewSecurityDescriptor);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//创建SD
	status = RtlCreateSecurityDescriptor(
		*NewSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	//设置SD
	status = RtlSetDaclSecurityDescriptor(
		*NewSecurityDescriptor, DaclPresent, pNewAcl, DaclDefaulted);
	if (!NT_SUCCESS(status)) goto FuncEnd;

FuncEnd:
	RtlFreeSid(WorldSid);
	RtlFreeSid(AdminSid);
	RtlFreeSid(RestrictedSid);
	return status;
}

// 创建沙盒令牌
EXTERN_C NTSTATUS WINAPI SuCreateSandboxToken(
	_Out_ PHANDLE TokenHandle,
	_In_ HANDLE ExistingTokenHandle,
	_In_ PSECURITY_CAPABILITIES SecurityCapabilities)
{
	// 对象初始化

	NTSTATUS status = STATUS_SUCCESS;
	DWORD ReturnLength = 0;
	DWORD TokenSessionID = 0;
	wchar_t Buffer[MAX_PATH];
	UNICODE_STRING usBNO = { 0 };
	OBJECT_ATTRIBUTES ObjectAttributes;
	UNICODE_STRING usRpcControl = RTL_CONSTANT_STRING(L"\\RPC Control");
	UNICODE_STRING usRpcControl2 = RTL_CONSTANT_STRING(L"RPC Control");
	UNICODE_STRING usRootDirectory = { 0 };
	UNICODE_STRING usGlobal = RTL_CONSTANT_STRING(L"Global");
	UNICODE_STRING usLocal = RTL_CONSTANT_STRING(L"Local");
	UNICODE_STRING usSession = RTL_CONSTANT_STRING(L"Session");
	PACCESS_ALLOWED_ACE pTempAce = nullptr;
	UNICODE_STRING usNamedPipe = { 0 };
	IO_STATUS_BLOCK IoStatusBlock;
	UNICODE_STRING usAppContainerSID = { 0 };
	HANDLE hBaseNamedObjects = nullptr;
	PSECURITY_DESCRIPTOR pSD = nullptr;
	PTOKEN_USER pTokenUser = nullptr;
	PSECURITY_DESCRIPTOR pDirectorySD = nullptr;
	PSECURITY_DESCRIPTOR pRpcControlSD = nullptr;
	HANDLE hRpcControl = nullptr;
	HANDLE HandleList[6] = { nullptr };

	// 获取令牌会话ID
	status = NtQueryInformationToken(
		ExistingTokenHandle,
		TokenSessionId,
		&TokenSessionID,
		sizeof(DWORD),
		&ReturnLength);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 把SID转换为Unicode字符串
	status = RtlConvertSidToUnicodeString(
		&usAppContainerSID, SecurityCapabilities->AppContainerSid, TRUE);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 初始化缓冲区
	Buffer[0] = L'\0';

	// 如果SessionID不为0，则加上对应会话的前缀
	if (TokenSessionID)
	{
		StringCbPrintfW(
			Buffer, sizeof(Buffer), L"\\Sessions\\%ld", TokenSessionID);
	}

	// 附加BaseNamedObjects目录路径字符串
	StringCbCatW(Buffer, sizeof(Buffer), L"\\BaseNamedObjects");

	// 初始化用于打开BaseNamedObjects目录对象的UNICODE_STRING结构
	RtlInitUnicodeString(&usBNO, Buffer);

	// 初始化用于打开BaseNamedObjects目录对象的OBJECT_ATTRIBUTES结构
	M2InitObjectAttributes(&ObjectAttributes, &usBNO);

	// 打开BaseNamedObjects目录对象
	status = NtOpenDirectoryObject(
		&hBaseNamedObjects,
		READ_CONTROL | DIRECTORY_QUERY | DIRECTORY_TRAVERSE,
		&ObjectAttributes);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 获取BaseNamedObjects目录安全标识符信息大小
	NtQuerySecurityObject(
		hBaseNamedObjects, DACL_SECURITY_INFORMATION,
		nullptr, 0, &ReturnLength);

	// 为安全标识符分配内存
	status = M2HeapAlloc(ReturnLength, pSD);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 获取BaseNamedObjects目录安全标识符信息
	status = NtQuerySecurityObject(
		hBaseNamedObjects, DACL_SECURITY_INFORMATION,
		pSD, ReturnLength, &ReturnLength);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 获取令牌用户信息大小
	status = NtQueryInformationToken(
		ExistingTokenHandle, TokenUser,
		nullptr, 0, &ReturnLength);
	if (status != STATUS_BUFFER_TOO_SMALL) goto FuncEnd;

	// 为令牌用户信息分配内存
	status = M2HeapAlloc(ReturnLength, pTokenUser);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 获取令牌用户信息
	status = NtQueryInformationToken(
		ExistingTokenHandle, TokenUser,
		pTokenUser, ReturnLength, &ReturnLength);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 创建AppContainer对象目录安全标识符
	status = SuBuildSandboxSecurityDescriptor(
		pSD,
		SecurityCapabilities->AppContainerSid,
		pTokenUser->User.Sid,
		false,
		&pDirectorySD);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 创建AppContainer RPC对象目录安全标识符
	status = SuBuildSandboxSecurityDescriptor(
		pSD,
		SecurityCapabilities->AppContainerSid,
		pTokenUser->User.Sid,
		true,
		&pRpcControlSD);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 初始化AppContainer目录对象字符串
	StringCbPrintfW(
		Buffer, sizeof(Buffer),
		L"\\Sessions\\%d\\AppContainerNamedObjects\\%ws",
		TokenSessionID,
		usAppContainerSID.Buffer, usAppContainerSID.Length);

	// 初始化AppContainer目录对象的UNICODE_STRING结构
	RtlInitUnicodeString(&usRootDirectory, Buffer);

	// 初始化用于创建AppContainer目录对象的OBJECT_ATTRIBUTES结构
	M2InitObjectAttributes(
		&ObjectAttributes,
		&usRootDirectory,
		OBJ_INHERIT | OBJ_OPENIF,
		nullptr,
		pDirectorySD);

	// 创建AppContainer目录对象
	status = NtCreateDirectoryObjectEx(
		&HandleList[SuAppContainerHandleList::RootDirectory],
		DIRECTORY_QUERY | DIRECTORY_TRAVERSE |
		DIRECTORY_CREATE_OBJECT | DIRECTORY_CREATE_SUBDIRECTORY,
		&ObjectAttributes,
		hBaseNamedObjects,
		1);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 设置AppContainer目录对象完整性标签为低
	status = SuSetKernelObjectIntegrityLevel(
		HandleList[SuAppContainerHandleList::RootDirectory],
		IntegrityLevel::Low);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 初始化用于打开RPC Control目录对象的OBJECT_ATTRIBUTES结构
	M2InitObjectAttributes(&ObjectAttributes, &usRpcControl);

	// 打开RPC Control目录对象
	status = NtOpenDirectoryObject(
		&hRpcControl,
		DIRECTORY_QUERY | DIRECTORY_TRAVERSE,
		&ObjectAttributes);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 初始化用于创建AppContainer RPC Control目录对象的OBJECT_ATTRIBUTES结构
	M2InitObjectAttributes(
		&ObjectAttributes,
		&usRpcControl2,
		OBJ_INHERIT | OBJ_OPENIF,
		HandleList[SuAppContainerHandleList::RootDirectory],
		pRpcControlSD);

	// 创建AppContainer RPC Control目录对象
	status = NtCreateDirectoryObjectEx(
		&HandleList[SuAppContainerHandleList::RpcDirectory],
		DIRECTORY_QUERY | DIRECTORY_TRAVERSE |
		DIRECTORY_CREATE_OBJECT | DIRECTORY_CREATE_SUBDIRECTORY,
		&ObjectAttributes,
		hRpcControl,
		1);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 设置AppContainer RPC Control目录对象完整性标签为低
	status = SuSetKernelObjectIntegrityLevel(
		HandleList[SuAppContainerHandleList::RpcDirectory],
		IntegrityLevel::Low);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 初始化用于创建Global符号链接对象的OBJECT_ATTRIBUTES结构
	M2InitObjectAttributes(
		&ObjectAttributes,
		&usGlobal,
		OBJ_INHERIT | OBJ_OPENIF,
		HandleList[SuAppContainerHandleList::RootDirectory],
		pDirectorySD);

	// 在AppContainer目录对象下创建Global目录
	status = NtCreateDirectoryObjectEx(
		&HandleList[SuAppContainerHandleList::GlobalSymbolicLink],
		DIRECTORY_ALL_ACCESS,
		&ObjectAttributes,
		hBaseNamedObjects,
		1);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 初始化用于创建Local符号链接对象的OBJECT_ATTRIBUTES结构
	M2InitObjectAttributes(
		&ObjectAttributes,
		&usLocal,
		OBJ_INHERIT | OBJ_OPENIF,
		HandleList[SuAppContainerHandleList::RootDirectory],
		pDirectorySD);

	// 在AppContainer目录对象下创建Local符号链接对象
	status = NtCreateSymbolicLinkObject(
		&HandleList[SuAppContainerHandleList::LocalSymbolicLink],
		SYMBOLIC_LINK_ALL_ACCESS,
		&ObjectAttributes,
		&usRootDirectory);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 初始化用于创建Session符号链接对象的OBJECT_ATTRIBUTES结构
	M2InitObjectAttributes(
		&ObjectAttributes,
		&usSession,
		OBJ_INHERIT | OBJ_OPENIF,
		HandleList[SuAppContainerHandleList::RootDirectory],
		pDirectorySD);

	// 在AppContainer目录对象下创建Session符号链接对象
	status = NtCreateSymbolicLinkObject(
		&HandleList[SuAppContainerHandleList::SessionSymbolicLink],
		SYMBOLIC_LINK_ALL_ACCESS,
		&ObjectAttributes,
		&usRootDirectory);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 初始化AppContainer命名管道路径字符串
	StringCbPrintfW(
		Buffer, sizeof(Buffer),
		L"\\Device\\NamedPipe\\Sessions\\%d\\AppContainerNamedObjects\\%ws",
		TokenSessionID,
		usAppContainerSID.Buffer, usAppContainerSID.Length);

	for (ULONG i = 0;
		NT_SUCCESS(RtlGetAce(
		((SECURITY_DESCRIPTOR*)pDirectorySD)->Dacl,
			i,
			(PVOID*)&pTempAce));
		++i)
	{
		DWORD LowMask = LOWORD(pTempAce->Mask);

		// 清零pTempAce->Mask低16位
		pTempAce->Mask &= ~0xFFFF;

		if (FILE_CREATE_PIPE_INSTANCE == (LowMask & FILE_CREATE_PIPE_INSTANCE))
			pTempAce->Mask |= SYNCHRONIZE | FILE_WRITE_DATA;

		if (FILE_READ_EA == (LowMask & FILE_READ_EA))
			pTempAce->Mask |= SYNCHRONIZE | FILE_CREATE_PIPE_INSTANCE;
	}

	// 初始化AppContainer命名管道UNICODE_STRING结构
	RtlInitUnicodeString(&usNamedPipe, Buffer);

	// 初始化创建AppContainer命名管道的OBJECT_ATTRIBUTES结构
	M2InitObjectAttributes(
		&ObjectAttributes,
		&usNamedPipe,
		OBJ_INHERIT | OBJ_CASE_INSENSITIVE,
		nullptr,
		pDirectorySD,
		nullptr);

	// 创建AppContainer命名管道
	status = NtCreateFile(
		&HandleList[SuAppContainerHandleList::NamedPipe],
		SYNCHRONIZE | STANDARD_RIGHTS_REQUIRED |
		FILE_WRITE_DATA | FILE_CREATE_PIPE_INSTANCE,
		&ObjectAttributes,
		&IoStatusBlock,
		nullptr,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN_IF,
		FILE_DIRECTORY_FILE,
		nullptr,
		0);
	if (!NT_SUCCESS(status)) goto FuncEnd;

	// 创建AppContainer的令牌
	status = NtCreateLowBoxToken(
		TokenHandle,
		ExistingTokenHandle,
		MAXIMUM_ALLOWED,
		nullptr,
		SecurityCapabilities->AppContainerSid,
		SecurityCapabilities->CapabilityCount,
		SecurityCapabilities->Capabilities,
		6,
		HandleList);

FuncEnd: // 结束处理

	for (size_t i = 0; i < 6; ++i) NtClose(HandleList[i]);
	NtClose(hRpcControl);
	M2HeapFree(pRpcControlSD);
	M2HeapFree(pDirectorySD);
	M2HeapFree(pTokenUser);
	M2HeapFree(pSD);
	NtClose(hBaseNamedObjects);
	RtlFreeUnicodeString(&usAppContainerSID);

	return status;
}

#pragma endregion

// 随机生成一个沙盒SID
#pragma region SuGenerateSandboxSid

// 随机生成一个沙盒SID
EXTERN_C VOID WINAPI SuGenerateSandboxSid(
	_Out_ PSID *RandomAppContainerSid)
{
	// 定义变量
	LARGE_INTEGER PerfCounter, PerfFrequency;

	// 获取性能计数器数值
	NtQueryPerformanceCounter(&PerfCounter, &PerfFrequency);

	//生成种子
	ULONG seed = (ULONG)(PerfCounter.QuadPart - PerfFrequency.QuadPart);

	RtlAllocateAndInitializeSid(
		&SidAuth_App,
		SECURITY_APP_PACKAGE_RID_COUNT,
		SECURITY_APP_PACKAGE_BASE_RID,
		(DWORD)RtlRandomEx(&seed),
		(DWORD)RtlRandomEx(&seed),
		(DWORD)RtlRandomEx(&seed),
		(DWORD)RtlRandomEx(&seed),
		(DWORD)RtlRandomEx(&seed),
		(DWORD)RtlRandomEx(&seed),
		(DWORD)RtlRandomEx(&seed),
		RandomAppContainerSid);
}

#pragma endregion

// 生成沙盒能力列表，生成的能力列表使用M2HeapFree释放
#pragma region SuGenerateSandboxCapabilities

// 生成沙盒能力列表，生成的能力列表使用M2HeapFree释放
EXTERN_C NTSTATUS WINAPI SuGenerateSandboxCapabilities(
	_Out_ PSID_AND_ATTRIBUTES *Capabilities,
	_In_ DWORD *CapabilitiyRIDs,
	_In_ DWORD CapabilityCount)
{
	//定义变量
	NTSTATUS status = STATUS_SUCCESS;

	//设置参数及分配内存
	status = M2HeapAlloc(
		CapabilityCount * sizeof(SID_AND_ATTRIBUTES), *Capabilities);
	if (!NT_SUCCESS(status)) goto Error;

	//获取能力SID
	for (DWORD i = 0; i < CapabilityCount; i++)
	{
		(*Capabilities)[i].Attributes = SE_GROUP_ENABLED;
		status = RtlAllocateAndInitializeSid(
			&SidAuth_App,
			SECURITY_BUILTIN_CAPABILITY_RID_COUNT,
			SECURITY_CAPABILITY_BASE_RID, CapabilitiyRIDs[i],
			0, 0, 0, 0, 0, 0,
			&(*Capabilities)[i].Sid);
		if (!NT_SUCCESS(status)) goto Error;
	}

	return status;

Error: // 错误处理

	if (*Capabilities)
	{
		for (DWORD i = 0; i < CapabilityCount; i++)
			if ((*Capabilities)[i].Sid) RtlFreeSid((*Capabilities)[i].Sid);

		M2HeapFree(*Capabilities);
		*Capabilities = nullptr;
	}

	return status;
}

#pragma endregion

// 创建沙盒的Job Object对象
#pragma region SuCreateSandboxJobObject

// Job Object对象创建选项
typedef struct _JOBOBJECT_OPTIONS
{
	// 限制内存占用，如果值为0则不做限制
	SIZE_T JobMemoryLimit;

	// 限制剪切板
	bool LimitClipBoard;

} JOBOBJECT_OPTIONS, *PJOBOBJECT_OPTIONS;

// 创建沙盒的Job Object对象
EXTERN_C NTSTATUS WINAPI SuCreateSandboxJobObject(
	_Out_ PHANDLE JobObject,
	_In_ JOBOBJECT_OPTIONS JobOptions)
{
	NTSTATUS status = STATUS_SUCCESS;

	JOBOBJECT_EXTENDED_LIMIT_INFORMATION LI = { 0 };
	JOBOBJECT_BASIC_UI_RESTRICTIONS UIR = { 0 };

	// 创建Job对象，如果失败则直接返回
	status = NtCreateJobObject(JobObject, JOB_OBJECT_ALL_ACCESS, nullptr);
	if (NT_SUCCESS(status)) return status;

	// 添加基本限制
	LI.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	
	// 添加UI限制
	UIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_HANDLES;
	UIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_GLOBALATOMS;
	UIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_SYSTEMPARAMETERS;
	UIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_DISPLAYSETTINGS;
	UIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_DESKTOP;
	UIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_EXITWINDOWS;

	// 限制内存占用，如果值为0则不做限制
	if (JobOptions.JobMemoryLimit)
	{
		LI.BasicLimitInformation.LimitFlags |= JOB_OBJECT_LIMIT_JOB_MEMORY;
		LI.JobMemoryLimit = JobOptions.JobMemoryLimit;
	}

	// 限制剪切板
	if (JobOptions.LimitClipBoard)
	{
		UIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_READCLIPBOARD;
		UIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_WRITECLIPBOARD;
	}

	// 添加基本限制
	status = NtSetInformationJobObject(
		*JobObject, 
		JobObjectExtendedLimitInformation, 
		&LI, 
		sizeof(LI));
	if (NT_SUCCESS(status))
	{
		// 添加UI限制
		status = NtSetInformationJobObject(
			*JobObject,
			JobObjectBasicUIRestrictions,
			&UIR,
			sizeof(UIR));
	}

	// 如果执行失败，则关闭Job Object句柄
	if (!NT_SUCCESS(status)) NtClose(*JobObject);

	// 返回运行结果
	return status;
}

#pragma endregion


/*#include <AccCtrl.h>
#include <Aclapi.h>

#include <UserEnv.h>
#pragma comment(lib,"userenv.lib")*/



//设定一个指定目录在指定的AppContainer下完全访问权限
/*bool SetFileGrantAccessInAppContainer(
_In_ PSID pAppContainerSID,
_In_ LPWSTR pObjectName)
{
bool bRet = false;

EXPLICIT_ACCESS ea;

ea.grfAccessMode = GRANT_ACCESS;
ea.grfAccessPermissions = FILE_ALL_ACCESS;
ea.grfInheritance = OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE;
ea.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
ea.Trustee.pMultipleTrustee = NULL;
ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
ea.Trustee.ptstrName = (LPTSTR)pAppContainerSID;

PACL pNewDacl = NULL, pOldDacl = NULL;

// 获取文件(夹)安全对象的DACL列表
if (ERROR_SUCCESS == GetNamedSecurityInfoW(
pObjectName,
SE_FILE_OBJECT, DACL_SECURITY_INFORMATION,
NULL, NULL, &pOldDacl, NULL, NULL))
{
// 创建新的ACL对象(合并已有的ACL对象和刚生成的用户帐户访问控制信息)
if (ERROR_SUCCESS == SetEntriesInAclW(1, &ea, pOldDacl, &pNewDacl))
{
// 设置文件(夹)安全对象的DACL列表
if (ERROR_SUCCESS == SetNamedSecurityInfoW(
pObjectName,
SE_FILE_OBJECT, DACL_SECURITY_INFORMATION,
NULL, NULL, pNewDacl, NULL))
{
bRet = true;
}
LocalFree(pNewDacl);
}
//LocalFree(pOldDacl);
}

return bRet;
}*/

/*
NTSTATUS status = STATUS_SUCCESS;
PVOID pDllModule = nullptr;
PVOID pDllModule2 = nullptr;

typedef NTSTATUS(WINAPI *SuCreateAppContainerTokenFnPtr)(
_Out_ PHANDLE TokenHandle,
_In_ HANDLE ExistingTokenHandle,
_In_ PSECURITY_CAPABILITIES SecurityCapabilities);

typedef VOID(WINAPI *SuGenerateRandomAppContainerSidFnPtr)(
_Out_ PSID *RandomAppContainerSid);

typedef NTSTATUS(WINAPI *SuGenerateAppContainerCapabilitiesFnPtr)(
_Out_ PSID_AND_ATTRIBUTES *Capabilities,
_In_ DWORD *CapabilitiyRIDs,
_In_ DWORD CapabilityCount);

SuCreateAppContainerTokenFnPtr pSuCreateAppContainerToken = nullptr;
SuGenerateRandomAppContainerSidFnPtr pSuGenerateRandomAppContainerSid = nullptr;
SuGenerateAppContainerCapabilitiesFnPtr pSuGenerateAppContainerCapabilities = nullptr;

typedef NTSTATUS(WINAPI *SuCreateSandboxTokenFnPtr)(
_Out_ PHANDLE TokenHandle,
_In_ HANDLE ExistingTokenHandle,
_In_ PSECURITY_CAPABILITIES SecurityCapabilities);

SuCreateSandboxTokenFnPtr pSuCreateSandboxToken = nullptr;

status = M2LoadDll(L"NSudo.AppContainer.dll", pDllModule);
status = M2LoadDll(L"NSudoBox.dll", pDllModule2);

status = M2GetFunc(pDllModule, "SuCreateAppContainerToken", pSuCreateAppContainerToken);
status = M2GetFunc(pDllModule, "SuGenerateRandomAppContainerSid", pSuGenerateRandomAppContainerSid);
status = M2GetFunc(pDllModule, "SuGenerateAppContainerCapabilities", pSuGenerateAppContainerCapabilities);

status = M2GetFunc(pDllModule2, "SuCreateSandboxToken", pSuCreateSandboxToken);

SECURITY_CAPABILITIES SecurityCapabilities = { 0 };

const DWORD CapabilitiyTypeRID[] =
{
SECURITY_CAPABILITY_INTERNET_CLIENT,
SECURITY_CAPABILITY_PRIVATE_NETWORK_CLIENT_SERVER,
SECURITY_CAPABILITY_SHARED_USER_CERTIFICATES,
SECURITY_CAPABILITY_ENTERPRISE_AUTHENTICATION,
};

pSuGenerateRandomAppContainerSid(
&SecurityCapabilities.AppContainerSid);

SecurityCapabilities.CapabilityCount = sizeof(CapabilitiyTypeRID) / sizeof(DWORD);

pSuGenerateAppContainerCapabilities(
&SecurityCapabilities.Capabilities,
(DWORD*)CapabilitiyTypeRID,
SecurityCapabilities.CapabilityCount);




HANDLE hToken = nullptr, hNewToken = nullptr;

SuQueryCurrentProcessToken(&hToken);

status = pSuCreateSandboxToken(&hNewToken, hToken, &SecurityCapabilities);

HRESULT hr = (HRESULT)RtlNtStatusToDosError(status);

wchar_t szCMD[] = L"cmd /k";

STARTUPINFOW StartupInfo = { 0 };
PROCESS_INFORMATION ProcessInfo = { 0 };

if (CreateProcessAsUserW(
	hNewToken, NULL, szCMD, nullptr, nullptr, FALSE,
	CREATE_NEW_CONSOLE,
	nullptr, nullptr, &StartupInfo, &ProcessInfo))
{

}
*/

/*HMODULE hKernelBase = LoadLibraryW(L"KernelBase.dll");
typedef NTSTATUS(WINAPI *PCAT)(HANDLE, LPSECURITY_CAPABILITIES, PHANDLE);
PCAT pcat = (PCAT)GetProcAddress(hKernelBase, "CreateAppContainerToken");
status = pcat(hToken, &SecurityCapabilities, &hNewToken);*/


//*****************************************************************************

// DLL入口点
#pragma region DllMain

//#pragma comment(linker, "/ENTRY:DllMain") 

#pragma comment(linker, "/merge:.pdata=.rdata")
#pragma comment(linker, "/merge:.gfids=.rdata")

// DLL入口点
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#pragma endregion