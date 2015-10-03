#pragma once

#pragma comment(lib,"ntdll.lib")

#include "..\NSudo.Universal\NSudo.Universal.Lib.NativeAPI.Types.h"

extern "C"
{
	NTSYSCALLAPI NTSTATUS WINAPI NtQuerySystemInformation(
		_In_      SYSTEM_INFORMATION_CLASS SystemInformationClass,
		_Inout_   PVOID                    SystemInformation,
		_In_      ULONG                    SystemInformationLength,
		_Out_opt_ PULONG                   ReturnLength
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtClose(
		_In_ HANDLE Handle
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtOpenProcess(
		_Out_ PHANDLE ProcessHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_In_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_opt_ PCLIENT_ID ClientId
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtOpenProcessToken(
		__in HANDLE ProcessHandle,
		__in ACCESS_MASK DesiredAccess,
		__out PHANDLE TokenHandle
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtDuplicateToken(
		_In_ HANDLE ExistingTokenHandle,
		_In_ ACCESS_MASK DesiredAccess,
		_In_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_ BOOLEAN EffectiveOnly,
		_In_ TOKEN_TYPE TokenType,
		_Out_ PHANDLE NewTokenHandle
		);

	NTSYSCALLAPI NTSTATUS NTAPI NtFilterToken(
		__in HANDLE ExistingTokenHandle,
		__in ULONG Flags,
		__in_opt PTOKEN_GROUPS SidsToDisable,
		__in_opt PTOKEN_PRIVILEGES PrivilegesToDelete,
		__in_opt PTOKEN_GROUPS RestrictedSids,
		__out PHANDLE NewTokenHandle
		);

	NTSYSCALLAPI ULONG NTAPI RtlNtStatusToDosError(
		_In_ NTSTATUS Status
		);

	NTSYSCALLAPI LONG NTAPI RtlGetLastWin32Error(
		VOID
		);

	NTSYSCALLAPI VOID NTAPI RtlSetLastWin32Error(
		_In_ LONG Win32Error
		);
}