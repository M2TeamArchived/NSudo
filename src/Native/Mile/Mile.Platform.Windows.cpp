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
    _In_ SIZE_T Size) noexcept
{
    return ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
}

LPVOID Mile::HeapMemory::Reallocate(
    _In_ PVOID Block,
    _In_ SIZE_T Size) noexcept
{
    return ::HeapReAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Block, Size);
}

BOOL Mile::HeapMemory::Free(
    _In_ LPVOID Block) noexcept
{
    return ::HeapFree(::GetProcessHeap(), 0, Block);
}

void Mile::CriticalSection::Initialize(
    _Out_ LPCRITICAL_SECTION lpCriticalSection) noexcept
{
    ::InitializeCriticalSection(lpCriticalSection);
}

void Mile::CriticalSection::Delete(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
{
    ::DeleteCriticalSection(lpCriticalSection);
}

void Mile::CriticalSection::Enter(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
{
    ::EnterCriticalSection(lpCriticalSection);
}

bool Mile::CriticalSection::TryEnter(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
{
    return FALSE != ::TryEnterCriticalSection(lpCriticalSection);
}

void Mile::CriticalSection::Leave(
    _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
{
    ::LeaveCriticalSection(lpCriticalSection);
}

Mile::CriticalSection::CriticalSection() noexcept
{
    Initialize(&this->m_RawObject);
}

Mile::CriticalSection::~CriticalSection() noexcept
{
    Delete(&this->m_RawObject);
}

void Mile::CriticalSection::Lock() noexcept
{
    Enter(&this->m_RawObject);
}

bool Mile::CriticalSection::TryLock() noexcept
{
    return TryEnter(&this->m_RawObject);
}

void Mile::CriticalSection::Unlock() noexcept
{
    Leave(&this->m_RawObject);
}

Mile::AutoCriticalSectionLock::AutoCriticalSectionLock(
    CriticalSection& Object) noexcept :
    m_Object(Object)
{
    this->m_Object.Lock();
}

Mile::AutoCriticalSectionLock::~AutoCriticalSectionLock() noexcept
{
    this->m_Object.Unlock();
}

Mile::AutoCriticalSectionTryLock::AutoCriticalSectionTryLock(
    CriticalSection& Object) noexcept :
    m_Object(Object)
{
    this->m_IsLocked = this->m_Object.TryLock();
}

Mile::AutoCriticalSectionTryLock::~AutoCriticalSectionTryLock() noexcept
{
    if (this->m_IsLocked)
    {
        this->m_Object.Unlock();
    }
}

bool Mile::AutoCriticalSectionTryLock::IsLocked() const
{
    return this->m_IsLocked;
}
