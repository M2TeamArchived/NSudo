// NSudo公共库 - 内存管理(基于Native API)

#pragma once

// PS: 你应该先引用 "ntdll.lib"

// NT堆管理API
extern "C"
{
	NTSYSAPI PVOID NTAPI RtlAllocateHeap(
		_In_ PVOID HeapHandle,
		_In_opt_ ULONG Flags,
		_In_ SIZE_T Size
		);

	NTSYSAPI BOOLEAN NTAPI RtlFreeHeap(
		_In_ PVOID HeapHandle,
		_In_opt_ ULONG Flags,
		_In_ _Post_invalid_ PVOID BaseAddress
		);
}

// 内存管理宏
#ifdef _AMD64_
#define ProcessHeap *(HANDLE *)(__readgsqword(96) + 48)
#else
#define ProcessHeap *(HANDLE *)(__readfsdword(48) + 24)
#endif	

// 分配内存
#define MemAlloc(Size) RtlAllocateHeap(ProcessHeap, NULL, Size)

// 释放分配内存
#define MemFree(BaseAddress) \
	if (BaseAddress) \
	{ \
		RtlFreeHeap(ProcessHeap, NULL, BaseAddress); \
		BaseAddress = NULL; \
	}
