/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.h
 * PURPOSE:   Mouri Internal Library Essentials Definition for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS
#define MILE_WINDOWS

#ifndef __cplusplus
#error "[Mile.Windows] You should use a C++ compiler."
#endif // !__cplusplus

#include <Windows.h>

/**
 * Allocates a block of memory from the default heap of the calling process.
 * The allocated memory will be initialized to zero. The allocated memory is
 * not movable.
 *
 * @param Size The number of bytes to be allocated.
 * @param Block A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileAllocMemory(
    _In_ SIZE_T Size,
    _Out_ LPVOID* Block);

/**
 * Reallocates a block of memory from the default heap of the calling process.
 * If the reallocation request is for a larger size, the additional region of
 * memory beyond the original size be initialized to zero. This function
 * enables you to resize a memory block and change other memory block
 * properties. The allocated memory is not movable.
 *
 * @param OldBlock A pointer to the block of memory that the function
 *                 reallocates. This pointer is returned by an earlier call to
 *                 the MileAllocMemory or MileReAllocMemory function.
 * @param NewSize The new size of the memory block, in bytes. A memory block's
 *                size can be increased or decreased by using this function.
 * @param NewBlock A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 */
EXTERN_C HRESULT WINAPI MileReAllocMemory(
    _In_ PVOID OldBlock,
    _In_ SIZE_T NewSize,
    _Out_ PVOID* NewBlock);

/**
 * Frees a memory block allocated from a heap by the MileAllocMemory or
 * MileReAllocMemory function.
 *
 * @param Block A pointer to the memory block to be freed. This pointer is
 *              returned by the AllocMemory or ReAllocMemory function. If this
 *              pointer is nullptr, the behavior is undefined.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileFreeMemory(
    _In_ LPVOID Block);

#endif // !MILE_WINDOWS
