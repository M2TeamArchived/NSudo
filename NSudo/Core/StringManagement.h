// NSudo公共库 - 字符串管理(基于Native API)

#pragma once

// PS: 你应该先引用 "ntdll.lib"

// NT字符串结构
typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

// NT字符串管理API
extern "C"
{
	NTSYSAPI VOID NTAPI RtlInitUnicodeString(
		_Out_ PUNICODE_STRING DestinationString,
		_In_opt_ PWSTR SourceString
		);

	NTSYSAPI VOID NTAPI RtlFreeUnicodeString(
		_In_ PUNICODE_STRING UnicodeString
		);
}