/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.System.cpp
 * PURPOSE:   System Implementation for Windows
 *
 * LICENSE:   Apache-2.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.Windows.System.h"

LPVOID Mile::Windows::System::AllocateMemory(
    _In_ SIZE_T Size)
{
    return ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
}

LPVOID Mile::Windows::System::ReallocateMemory(
    _In_ PVOID Block,
    _In_ SIZE_T Size)
{
    return ::HeapReAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Block, Size);
}

BOOL Mile::Windows::System::FreeMemory(
    _In_ LPVOID Block)
{
    ::HeapFree(::GetProcessHeap(), 0, Block);
}
