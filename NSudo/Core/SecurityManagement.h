// NSudo公共库 - 安全管理(基于Native API)

#pragma once

// PS: 你应该先引用 "ntdll.lib"

// NT令牌API
extern "C"
{
	NTSYSAPI NTSTATUS NTAPI NtAdjustPrivilegesToken(
		_In_ HANDLE TokenHandle,
		_In_ BOOLEAN DisableAllPrivileges,
		_In_opt_ PTOKEN_PRIVILEGES NewState,
		_In_ ULONG BufferLength,
		_Out_opt_ PTOKEN_PRIVILEGES PreviousState,
		_Out_opt_ PULONG ReturnLength
		);

	NTSYSAPI NTSTATUS NTAPI NtDuplicateToken(
		_In_ HANDLE ExistingTokenHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_In_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_ BOOLEAN EffectiveOnly,
		_In_ TOKEN_TYPE TokenType,
		_Out_ PHANDLE NewTokenHandle
		);

	NTSYSAPI NTSTATUS NTAPI NtFilterToken(
		_In_ HANDLE ExistingTokenHandle,
		_In_ ULONG Flags,
		_In_opt_ PTOKEN_GROUPS SidsToDisable,
		_In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
		_In_opt_ PTOKEN_GROUPS RestrictedSids,
		_Out_ PHANDLE NewTokenHandle
		);

	NTSYSAPI NTSTATUS NTAPI NtOpenProcessToken(
		_In_ HANDLE ProcessHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_Out_ PHANDLE TokenHandle
		);

	NTSYSAPI NTSTATUS NTAPI NtQueryInformationToken(
		_In_ HANDLE TokenHandle,
		_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
		_Out_ PVOID TokenInformation,
		_In_ ULONG TokenInformationLength,
		_Out_ PULONG ReturnLength
		);

	NTSYSAPI NTSTATUS NTAPI NtSetInformationToken(
		_In_ HANDLE TokenHandle,
		_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
		_In_ PVOID TokenInformation,
		_In_ ULONG TokenInformationLength
		);
}

// NT AppContainer API
extern "C"
{
	typedef struct _LOWBOX_DATA
	{
		HANDLE hContainerDir; //主目录对象句柄
		HANDLE hContainerRpcDir;  //RPC目录对象句柄
		HANDLE hLocalSymLink; //Local对象句柄
		HANDLE hGlobalSymLink; // Global对象句柄
		HANDLE hSessionSymLink; // Session对象句柄
		HANDLE hContainerNamedPipe; //命名管道句柄
	} LOWBOX_DATA, *PLOWBOX_DATA;

	NTSYSAPI NTSTATUS NTAPI NtCreateLowBoxToken(
		_Out_ PHANDLE LowBoxTokenHandle,
		_In_ HANDLE ExistingTokenHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_ PSID AppContainerSid,
		_In_ DWORD CapabilityCount,
		_In_opt_ PSID_AND_ATTRIBUTES Capabilities,
		_In_ DWORD LowBoxDataHandleCount,
		_In_opt_ PLOWBOX_DATA LowBoxData
		);
}

// NT安全标识符API
extern "C"
{
	NTSYSAPI NTSTATUS NTAPI RtlAllocateAndInitializeSid(
		_In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
		_In_ UCHAR SubAuthorityCount,
		_In_ ULONG SubAuthority0,
		_In_ ULONG SubAuthority1,
		_In_ ULONG SubAuthority2,
		_In_ ULONG SubAuthority3,
		_In_ ULONG SubAuthority4,
		_In_ ULONG SubAuthority5,
		_In_ ULONG SubAuthority6,
		_In_ ULONG SubAuthority7,
		_Outptr_ PSID *Sid
		);

	NTSYSAPI NTSTATUS NTAPI RtlConvertSidToUnicodeString(
		_Inout_ PUNICODE_STRING UnicodeString,
		_In_ PSID Sid,
		_In_ BOOLEAN AllocateDestinationString
		);

	NTSYSAPI PVOID NTAPI RtlFreeSid(
		_In_  PSID Sid
		);

	NTSYSAPI ULONG NTAPI RtlLengthSid(
		_In_ PSID Sid
		);

	NTSYSAPI PSID_IDENTIFIER_AUTHORITY NTAPI RtlIdentifierAuthoritySid(
		_In_ PSID Sid
		);

	NTSYSAPI PULONG NTAPI RtlSubAuthoritySid(
		_In_ PSID Sid,
		_In_ ULONG SubAuthority
		);

	NTSYSAPI PUCHAR NTAPI RtlSubAuthorityCountSid(
		_In_ PSID Sid
		);

	NTSYSAPI BOOLEAN NTAPI RtlEqualSid(
		_In_ PSID Sid1,
		_In_ PSID Sid2
		);
}

// NT访问列表API
extern "C"
{
	NTSYSAPI NTSTATUS NTAPI RtlCreateSecurityDescriptor(
		_Out_ PSECURITY_DESCRIPTOR SecurityDescriptor,
		_In_ ULONG Revision
		);

	NTSYSAPI NTSTATUS NTAPI RtlCreateAcl(
		_Out_ PACL Acl,
		_In_ ULONG AclLength,
		_In_ ULONG AclRevision
		);

	NTSYSAPI NTSTATUS NTAPI RtlAddMandatoryAce(
		_Inout_ PACL Acl,
		_In_ ULONG AceRevision,
		_In_ ULONG AceFlags,
		_In_ PSID Sid,
		_In_ UCHAR AceType,
		_In_ ACCESS_MASK AccessMask
		);

	NTSYSAPI NTSTATUS NTAPI RtlSetSaclSecurityDescriptor(
		_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
		_In_ BOOLEAN SaclPresent,
		_In_opt_ PACL Sacl,
		_In_opt_ BOOLEAN SaclDefaulted
		);

	NTSYSAPI NTSTATUS NTAPI RtlGetDaclSecurityDescriptor(
		_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
		_Out_ PBOOLEAN DaclPresent,
		_Out_ PACL *Dacl,
		_Out_ PBOOLEAN DaclDefaulted
		);

	NTSYSAPI NTSTATUS NTAPI RtlGetAce(
		_In_ PACL Acl,
		_In_ ULONG AceIndex,
		_Outptr_ PVOID *Ace
		);

	NTSYSAPI NTSTATUS NTAPI RtlAddAce(
		_Inout_ PACL Acl,
		_In_ ULONG AceRevision,
		_In_ ULONG StartingAceIndex,
		_In_ PVOID AceList,
		_In_ ULONG AceListLength
		);

	NTSYSAPI NTSTATUS NTAPI RtlAddAccessAllowedAce(
		_Inout_ PACL Acl,
		_In_ ULONG AceRevision,
		_In_ ACCESS_MASK AccessMask,
		_In_ PSID Sid
		);

	NTSYSAPI NTSTATUS NTAPI RtlAddAccessAllowedAceEx(
		_Inout_ PACL Acl,
		_In_ ULONG AceRevision,
		_In_ ULONG AceFlags,
		_In_ ACCESS_MASK AccessMask,
		_In_ PSID Sid
		);

	NTSYSAPI NTSTATUS NTAPI RtlSetDaclSecurityDescriptor(
		_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
		_In_ BOOLEAN DaclPresent,
		_In_opt_ PACL Dacl,
		_In_opt_ BOOLEAN DaclDefaulted
		);

	NTSYSAPI NTSTATUS NTAPI RtlQueryInformationAcl(
		_In_ PACL Acl,
		_Out_ PVOID AclInformation,
		_In_ ULONG AclInformationLength,
		_In_ ACL_INFORMATION_CLASS AclInformationClass
		);
}