// NSudo公共库 - 对象管理(基于Native API)

#pragma once

// PS: 你应该先引用 "ntdll.lib"

// 对象属性有效值

#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_KERNEL_HANDLE       0x00000200L
#define OBJ_FORCE_ACCESS_CHECK  0x00000400L
#define OBJ_VALID_ATTRIBUTES    0x000007F2L

// 对象属性结构
typedef struct _OBJECT_ATTRIBUTES {
	ULONG           Length;
	HANDLE          RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG           Attributes;
	PVOID           SecurityDescriptor;
	PVOID           SecurityQualityOfService;
}  OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

// 初始化OBJECT_ATTRIBUTES结构
#define InitObjAttr(ObjAttr, RootDir, ObjName, Attr, SD, SQOS) \
{ \
	(ObjAttr)->Length = sizeof(OBJECT_ATTRIBUTES); \
	(ObjAttr)->RootDirectory = RootDir; \
	(ObjAttr)->Attributes = Attr; \
	(ObjAttr)->ObjectName = ObjName; \
	(ObjAttr)->SecurityDescriptor = SD; \
	(ObjAttr)->SecurityQualityOfService = SQOS; \
}

// NT对象管理API
extern "C"
{
	NTSYSAPI NTSTATUS NTAPI NtClose(
		_In_ HANDLE Handle
		);
	
	NTSYSAPI NTSTATUS NTAPI NtCreateDirectoryObjectEx(
		_Out_ PHANDLE DirectoryHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_In_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_ HANDLE ShadowDirectoryHandle,
		_In_ ULONG Flags
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtCreateSymbolicLinkObject(
		_Out_ PHANDLE LinkHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_In_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_ PUNICODE_STRING LinkTarget
		);

	NTSYSAPI NTSTATUS NTAPI NtQuerySecurityObject(
		_In_ HANDLE Handle,
		_In_ SECURITY_INFORMATION SecurityInformation,
		_Out_writes_bytes_opt_(Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
		_In_ ULONG Length,
		_Out_ PULONG LengthNeeded
		);

	NTSYSAPI NTSTATUS NTAPI NtSetSecurityObject(
		_In_ HANDLE Handle,
		_In_ SECURITY_INFORMATION SecurityInformation,
		_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
		);
}