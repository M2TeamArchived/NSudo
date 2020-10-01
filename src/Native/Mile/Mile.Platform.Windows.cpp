/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Platform.Windows.cpp
 * PURPOSE:   Windows Platform Implementation
 *
 * LICENSE:   Apache-2.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.Platform.Windows.h"

LPVOID Mile::HeapMemory::Allocate(
    _In_ SIZE_T Size)
{
    return ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
}

LPVOID Mile::HeapMemory::Reallocate(
    _In_ PVOID Block,
    _In_ SIZE_T Size)
{
    return ::HeapReAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Block, Size);
}

BOOL Mile::HeapMemory::Free(
    _In_ LPVOID Block)
{
    return ::HeapFree(::GetProcessHeap(), 0, Block);
}
