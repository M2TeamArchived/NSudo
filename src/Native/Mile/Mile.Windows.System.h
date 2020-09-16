/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.System.h
 * PURPOSE:   System Definition for Windows
 *
 * LICENSE:   Apache-2.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS_SYSTEM
#define MILE_WINDOWS_SYSTEM

#if (defined(__cplusplus) && __cplusplus >= 201703L)
#elif (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#else
#error "[Mile] You should use a C++ compiler with the C++17 standard."
#endif

#include <Windows.h>

namespace Mile::Windows::System
{
    /**
     * @brief Allocates a block of memory from the default heap of the calling
     *        process. The allocated memory will be initialized to zero. The
     *        allocated memory is not movable.
     * @param Size The number of bytes to be allocated.
     * @return If the function succeeds, the return value is a pointer to the
     *         allocated memory block. If the function fails, the return value
     *         is nullptr.
    */
    LPVOID AllocateMemory(
        _In_ SIZE_T Size);

    /**
     * @brief Reallocates a block of memory from the default heap of the
     *        calling process. If the reallocation request is for a larger
     *        size, the additional region of memory beyond the original size be
     *        initialized to zero. This function enables you to resize a memory
     *        block and change other memory block properties. The allocated
     *        memory is not movable.
     * @param Block A pointer to the block of memory that the function
     *              reallocates. This pointer is returned by an earlier call to
     *              AllocateMemory and ReallocateMemory function.
     * @param Size The new size of the memory block, in bytes. A memory block's
     *             size can be increased or decreased by using this function.
     * @return If the function succeeds, the return value is a pointer to the
     *         reallocated memory block. If the function fails, the return
     *         value is nullptr.
    */
    LPVOID ReallocateMemory(
        _In_ PVOID Block,
        _In_ SIZE_T Size);

    /**
     * @brief Frees a memory block allocated from a heap by the AllocateMemory
     *        or ReallocateMemory function.
     * @param Block A pointer to the memory block to be freed. This pointer is
     *              returned by the AllocateMemory or ReallocateMemory
     *              function. If this pointer is nullptr, the behavior is
     *              undefined.
     * @return If the function succeeds, the return value is nonzero. If the
     *         function fails, the return value is zero. An application can
     *         call GetLastError for extended error information.
    */
    BOOL FreeMemory(
        _In_ LPVOID Block);
}

#endif // !MILE_WINDOWS_SYSTEM
