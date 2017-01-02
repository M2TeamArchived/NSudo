/**************************************************************************
描述：NSudo AppContainer库
维护者：Mouri_Naruto (M2-Team)
版本：1.0 (2017-01-01)
基于项目：无
协议：The MIT License
用法：直接Include此头文件即可
建议的Windows SDK版本：10.0.10586及以后
***************************************************************************/

#pragma once

#ifndef M2_NSUDO_APPCONTAINER
#define M2_NSUDO_APPCONTAINER

#include <strsafe.h>

namespace M2
{
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

	// 在AppContainer内核对象目录下创建符号链接
	static NTSTATUS SuCreateAppContainerSymbolicLinks(
		_In_ HANDLE RootDirectory,
		_In_ PUNICODE_STRING LinkTarget,
		_In_ PVOID SecurityDescriptor,
		_Out_ PHANDLE GlobalSymbolicLink,
		_Out_ PHANDLE LocalSymbolicLink, 
		_Out_ PHANDLE SessionSymbolicLink)
	{
		// 定义变量

		UNICODE_STRING usGlobal = RTL_CONSTANT_STRING(L"Global");
		UNICODE_STRING usLocal = RTL_CONSTANT_STRING(L"Local");
		UNICODE_STRING usSession = RTL_CONSTANT_STRING(L"Session");	
		UNICODE_STRING usBNO = RTL_CONSTANT_STRING(L"\\BaseNamedObjects");

		NTSTATUS status = STATUS_SUCCESS;
		OBJECT_ATTRIBUTES ObjectAttributes;

		// 初始化创建Global符号链接的OBJECT_ATTRIBUTES结构
		M2InitObjectAttributes(
			&ObjectAttributes,
			&usGlobal, 
			OBJ_INHERIT | OBJ_OPENIF,
			RootDirectory, 
			SecurityDescriptor, 
			nullptr);

		// 创建Global符号链接
		status = NtCreateSymbolicLinkObject(
			GlobalSymbolicLink,
			SYMBOLIC_LINK_ALL_ACCESS,
			&ObjectAttributes,
			&usBNO);
		if (!NT_SUCCESS(status)) goto Error;
		
		// 初始化创建Local符号链接的OBJECT_ATTRIBUTES结构
		M2InitObjectAttributes(
			&ObjectAttributes,
			&usLocal,
			OBJ_INHERIT | OBJ_OPENIF,
			RootDirectory,
			SecurityDescriptor,
			nullptr);

		// 创建Local符号链接
		status = NtCreateSymbolicLinkObject(
			LocalSymbolicLink,
			SYMBOLIC_LINK_ALL_ACCESS,
			&ObjectAttributes,
			LinkTarget);
		if (!NT_SUCCESS(status)) goto Error;

		// 初始化创建Session符号链接的OBJECT_ATTRIBUTES结构
		M2InitObjectAttributes(
			&ObjectAttributes,
			&usSession,
			OBJ_INHERIT | OBJ_OPENIF,
			RootDirectory,
			SecurityDescriptor,
			nullptr);

		// 创建Session符号链接
		status = NtCreateSymbolicLinkObject(
			SessionSymbolicLink,
			SYMBOLIC_LINK_ALL_ACCESS,
			&ObjectAttributes,
			LinkTarget);
		if (!NT_SUCCESS(status)) goto Error;

		return status;

	Error: // 错误处理
		
		if (INVALID_HANDLE_VALUE != SessionSymbolicLink)
		{
			NtClose(*SessionSymbolicLink);
			*SessionSymbolicLink = INVALID_HANDLE_VALUE;
		}

		if (INVALID_HANDLE_VALUE != LocalSymbolicLink)
		{
			NtClose(*LocalSymbolicLink);
			*LocalSymbolicLink = INVALID_HANDLE_VALUE;
		}
		
		if (INVALID_HANDLE_VALUE != GlobalSymbolicLink)
		{
			NtClose(*GlobalSymbolicLink);
			*GlobalSymbolicLink = INVALID_HANDLE_VALUE;		
		}

		return status;
	}	

	//构建沙盒安全标识符
	static NTSTATUS WINAPI SuBuildAppContainerSecurityDescriptor(
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
				0x5A4D,
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
				0xA0000000,
				RestrictedSid);
			if (!NT_SUCCESS(status)) goto FuncEnd;

			//添加ACE（InheritNone） - Everyone SID
			status = RtlAddAccessAllowedAceEx(
				pNewAcl,
				pAcl->AclRevision,
				OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE | INHERIT_ONLY_ACE,
				0xA0000000,
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

	// 创建AppContainer令牌
	static NTSTATUS WINAPI SuCreateAppContainerToken(
		_Out_ PHANDLE TokenHandle,
		_In_ HANDLE ExistingTokenHandle,
		_In_ PSECURITY_CAPABILITIES SecurityCapabilities)
	{
		// 对象初始化

		NTSTATUS status = STATUS_SUCCESS;
		DWORD ReturnLength = 0;
		DWORD TokenSessionID = 0;
		wchar_t Buffer[MAX_PATH];	
		UNICODE_STRING usBNO = RTL_CONSTANT_STRING(L"\\BaseNamedObjects");
		OBJECT_ATTRIBUTES ObjectAttributes;			
		UNICODE_STRING usACNO = { 0 };	
		UNICODE_STRING usRpcControl = RTL_CONSTANT_STRING(L"\\RPC Control");		
		UNICODE_STRING usRpcControl2 = RTL_CONSTANT_STRING(L"RPC Control");
		UNICODE_STRING usRootDirectory = { 0 };
		PACCESS_ALLOWED_ACE pTempAce = nullptr;
		UNICODE_STRING usNamedPipe = {0};
		IO_STATUS_BLOCK IoStatusBlock;
		UNICODE_STRING usAppContainerSID = { 0 };
		HANDLE hBaseNamedObjects = nullptr;
		PSECURITY_DESCRIPTOR pSD = nullptr;
		PTOKEN_USER pTokenUser = nullptr;
		PSECURITY_DESCRIPTOR pDirectorySD = nullptr;
		PSECURITY_DESCRIPTOR pRpcControlSD = nullptr;
		HANDLE hAppContainerNamedObjects = nullptr;
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

		// 如果SessionID不为0，则生成对应会话的路径
		if (TokenSessionID)
		{
			StringCbPrintfW(
				Buffer, sizeof(Buffer),
				L"\\Sessions\\%ld\\BaseNamedObjects", TokenSessionID);

			RtlInitUnicodeString(&usBNO, Buffer);
		}

		// 初始化打开BaseNamedObjects目录的OBJECT_ATTRIBUTES结构
		M2InitObjectAttributes(
			&ObjectAttributes, &usBNO, 0, nullptr, nullptr, nullptr);

		// 打开BaseNamedObjects目录
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
		NtQueryInformationToken(
			ExistingTokenHandle, TokenUser,
			nullptr, 0, &ReturnLength);

		// 为令牌用户信息分配内存
		status = M2HeapAlloc(ReturnLength, pTokenUser);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 获取令牌用户信息
		status = NtQueryInformationToken(
			ExistingTokenHandle, TokenUser,
			pTokenUser, ReturnLength, &ReturnLength);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 创建AppContainer对象目录安全标识符
		status = SuBuildAppContainerSecurityDescriptor(
			pSD, 
			SecurityCapabilities->AppContainerSid,
			pTokenUser->User.Sid,
			false,
			&pDirectorySD);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 创建AppContainer RPC对象目录安全标识符
		status = SuBuildAppContainerSecurityDescriptor(
			pSD,
			SecurityCapabilities->AppContainerSid, 
			pTokenUser->User.Sid, 
			true,
			&pRpcControlSD);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 初始化AppContainerNamedObjects对象目录路径字符串
		StringCbPrintfW(
			Buffer, sizeof(Buffer),
			L"\\Sessions\\%ld\\AppContainerNamedObjects", TokenSessionID);

		// 初始化AppContainerNamedObjects对象目录路径UNICODE_STRING结构
		RtlInitUnicodeString(&usACNO, Buffer);

		// 初始化打开AppContainerNamedObjects目录的OBJECT_ATTRIBUTES结构
		M2InitObjectAttributes(
			&ObjectAttributes, &usACNO, 0, nullptr, nullptr, nullptr);

		// 打开AppContainerNamedObjects目录
		status = NtOpenDirectoryObject(
			&hAppContainerNamedObjects,
			DIRECTORY_QUERY | DIRECTORY_TRAVERSE |
			DIRECTORY_CREATE_OBJECT | DIRECTORY_CREATE_SUBDIRECTORY,
			&ObjectAttributes);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 初始化创建AppContainer对象目录的OBJECT_ATTRIBUTES结构
		M2InitObjectAttributes(
			&ObjectAttributes,
			&usAppContainerSID,
			OBJ_INHERIT | OBJ_OPENIF,
			hAppContainerNamedObjects,
			pDirectorySD,
			nullptr);

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
		status = SuSetKernelObjectIL(
			HandleList[SuAppContainerHandleList::RootDirectory],
			IntegrityLevel::Low);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 初始化打开RPC Control目录的OBJECT_ATTRIBUTES结构
		M2InitObjectAttributes(
			&ObjectAttributes, &usRpcControl, 0, nullptr, nullptr, nullptr);

		// 打开RPC Control目录
		status = NtOpenDirectoryObject(
			&hRpcControl,
			DIRECTORY_QUERY | DIRECTORY_TRAVERSE,
			&ObjectAttributes);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 初始化创建AppContainer RPC Control目录对象的OBJECT_ATTRIBUTES结构
		M2InitObjectAttributes(
			&ObjectAttributes,
			&usRpcControl2,
			OBJ_INHERIT | OBJ_OPENIF,
			HandleList[SuAppContainerHandleList::RootDirectory],
			pRpcControlSD,
			nullptr);

		// 创建AppContainer RPC Control目录对象
		status = NtCreateDirectoryObjectEx(
			&HandleList[SuAppContainerHandleList::RpcDirectory],
			DIRECTORY_QUERY | DIRECTORY_TRAVERSE |
			DIRECTORY_CREATE_OBJECT | DIRECTORY_CREATE_SUBDIRECTORY,
			&ObjectAttributes,
			hBaseNamedObjects,
			1);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 设置AppContainer RPC Control目录对象完整性标签为低
		status = SuSetKernelObjectIL(
			HandleList[SuAppContainerHandleList::RpcDirectory],
			IntegrityLevel::Low);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		// 初始化AppContainer目录对象字符串
		StringCbPrintfW(
			Buffer, sizeof(Buffer),
			L"\\Sessions\\%d\\AppContainerNamedObjects\\%ws",
			TokenSessionID,
			usAppContainerSID.Buffer, usAppContainerSID.Length);

		// 初始化AppContainer目录对象的UNICODE_STRING结构
		RtlInitUnicodeString(&usRootDirectory, Buffer);

		// 在AppContainer目录对象下创建必须的符号链接
		status = SuCreateAppContainerSymbolicLinks(
			HandleList[SuAppContainerHandleList::RootDirectory],
			&usRootDirectory,
			pDirectorySD,
			&HandleList[SuAppContainerHandleList::GlobalSymbolicLink],
			&HandleList[SuAppContainerHandleList::LocalSymbolicLink],
			&HandleList[SuAppContainerHandleList::SessionSymbolicLink]);
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

			pTempAce->Mask >>= 16;
			pTempAce->Mask <<= 16;

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
			NULL,
			SecurityCapabilities->AppContainerSid,
			SecurityCapabilities->CapabilityCount,
			SecurityCapabilities->Capabilities,
			6,
			HandleList);

	FuncEnd: // 结束处理
		
		for (size_t i = 0; i < 6; ++i) NtClose(HandleList[i]);	
		NtClose(hRpcControl);
		NtClose(hAppContainerNamedObjects);
		M2HeapFree(pRpcControlSD);
		M2HeapFree(pDirectorySD);
		M2HeapFree(pTokenUser);
		M2HeapFree(pSD);
		NtClose(hBaseNamedObjects);
		RtlFreeUnicodeString(&usAppContainerSID);

		return status;
	}

	// 随机生成一个AppContainer SID
	static void WINAPI SuGenerateRandomAppContainerSid(
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

	// 生成AppContainer能力列表
	static NTSTATUS WINAPI SuGenerateAppContainerCapabilitiy(
		_Out_ PSID_AND_ATTRIBUTES *Capabilities,
		_Out_ PDWORD CapabilityCount)
	{
		//定义变量
		NTSTATUS status = STATUS_SUCCESS;
		SID_IDENTIFIER_AUTHORITY SIDAuthority = SECURITY_APP_PACKAGE_AUTHORITY;
		PSID_AND_ATTRIBUTES CapabilitiesList = nullptr;
		const DWORD CapabilitiyTypeRID[] =
		{
			SECURITY_CAPABILITY_INTERNET_CLIENT,
			SECURITY_CAPABILITY_PRIVATE_NETWORK_CLIENT_SERVER,
			SECURITY_CAPABILITY_SHARED_USER_CERTIFICATES,
			SECURITY_CAPABILITY_ENTERPRISE_AUTHENTICATION,
		};

		//设置参数及分配内存
		*CapabilityCount = 4;
		CapabilitiesList = (PSID_AND_ATTRIBUTES)M2HeapAlloc(
			*CapabilityCount * sizeof(SID_AND_ATTRIBUTES));
		if (!CapabilitiesList) return STATUS_NO_MEMORY;

		//获取能力SID
		for (DWORD i = 0; i < *CapabilityCount; i++)
		{
			CapabilitiesList[i].Attributes = SE_GROUP_ENABLED;
			status = RtlAllocateAndInitializeSid(
				&SIDAuthority,
				SECURITY_BUILTIN_CAPABILITY_RID_COUNT,
				SECURITY_CAPABILITY_BASE_RID, CapabilitiyTypeRID[i],
				NULL, NULL, NULL, NULL, NULL, NULL,
				&CapabilitiesList[i].Sid);
			if (!NT_SUCCESS(status)) goto FuncEnd;
		}
		*Capabilities = CapabilitiesList;

	FuncEnd:
		return status;
	}

	//创建沙盒Job对象
	static NTSTATUS WINAPI SuCreateSandBoxJobObject(
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
	}

}

#endif