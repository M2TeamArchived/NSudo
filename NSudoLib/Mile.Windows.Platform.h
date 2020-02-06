/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Platform.h
 * PURPOSE:   Mouri Internal Library Essentials Base Definition for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS_PLATFORM
#define MILE_WINDOWS_PLATFORM

#ifndef __cplusplus
#error "[Mile.Windows.Platform] You should use a C++ compiler."
#endif // !__cplusplus

#include <Windows.h>

/**
 * Retrieves a handle to the default heap of the calling process. This handle
 * can then be used in subsequent calls to the heap functions.
 *
 * @return The handle to the calling process's heap.
 * @remark For more information, see GetProcessHeap.
 */
EXTERN_C HANDLE WINAPI MileGetProcessHeap();

/**
 * Allocates a block of memory from a heap. The allocated memory is not
 * movable.
 *
 * @param hHeap A handle to the heap from which the memory will be allocated.
 * @param dwFlags The heap allocation options.
 * @param dwBytes The number of bytes to be allocated.
 * @param lpNewMem A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapAlloc.
 */
EXTERN_C HRESULT WINAPI MileHeapAlloc(
    _In_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ SIZE_T dwBytes,
    _Out_ LPVOID* lpNewMem);

/**
 * Reallocates a block of memory from a heap. This function enables you to
 * resize a memory block and change other memory block properties. The
 * allocated memory is not movable.
 *
 * @param hHeap A handle to the heap from which the memory is to be
 *              reallocated.
 * @param dwFlags The heap reallocation options.
 * @param lpMem A pointer to the block of memory that the function reallocates.
 *              This pointer is returned by an earlier call to the
 *              MileHeapAlloc or MileHeapReAlloc function.
 * @param dwBytes The new size of the memory block, in bytes. A memory block's
 *                size can be increased or decreased by using this function.
 * @param lpNewMem A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 * @remark For more information, see HeapReAlloc.
 */
EXTERN_C HRESULT WINAPI MileHeapReAlloc(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem,
    _In_ SIZE_T dwBytes,
    _Out_ LPVOID* lpNewMem);

/**
 * Frees a memory block allocated from a heap by the MileHeapAlloc or
 * MileHeapReAlloc function.
 *
 * @param hHeap A handle to the heap whose memory block is to be freed.
 * @param dwFlags The heap free options.
 * @param lpMem A pointer to the memory block to be freed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapFree.
 */
EXTERN_C HRESULT WINAPI MileHeapFree(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem);

#endif // !MILE_WINDOWS_PLATFORM
