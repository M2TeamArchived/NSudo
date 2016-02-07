// NSudo公共库 - 进程管理(基于Native API)

#pragma once

// PS: 你应该先引用 "ntdll.lib"

// NT进程对象API
extern "C"
{
	typedef struct _CLIENT_ID
	{
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID, *PCLIENT_ID;

	NTSYSAPI NTSTATUS NTAPI NtOpenProcess(
		_Out_ PHANDLE ProcessHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_In_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_opt_ PCLIENT_ID ClientId
		);

	NTSYSAPI VOID NTAPI RtlExitUserProcess(
		_In_ NTSTATUS ExitStatus
		);
}

// NT Job对象API
extern "C"
{
	NTSYSCALLAPI NTSTATUS NTAPI NtCreateJobObject(
		_Out_ PHANDLE JobHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtAssignProcessToJobObject(
		_In_ HANDLE JobHandle,
		_In_ HANDLE ProcessHandle
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationJobObject(
		_In_opt_ HANDLE JobHandle,
		_In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
		_Out_ PVOID JobObjectInformation,
		_In_ ULONG JobObjectInformationLength,
		_Out_opt_ PULONG ReturnLength
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationJobObject(
		_In_ HANDLE JobHandle,
		_In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
		_In_ PVOID JobObjectInformation,
		_In_ ULONG JobObjectInformationLength
		);
}