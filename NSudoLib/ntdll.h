#pragma once

#define NT_SUCCESS(status) ((NTSTATUS)(status)>=0) 

#pragma comment(lib,"ntdll.lib")

extern "C"
{
	NTSYSCALLAPI
		NTSTATUS
		NTAPI
		NtFilterToken(
			__in HANDLE ExistingTokenHandle,
			__in ULONG Flags,
			__in_opt PTOKEN_GROUPS SidsToDisable,
			__in_opt PTOKEN_PRIVILEGES PrivilegesToDelete,
			__in_opt PTOKEN_GROUPS RestrictedSids,
			__out PHANDLE NewTokenHandle
			);
}