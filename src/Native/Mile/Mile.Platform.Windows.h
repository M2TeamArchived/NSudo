/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Platform.Windows.h
 * PURPOSE:   Windows Platform Definition
 *
 * LICENSE:   Apache-2.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_PLATFORM_WINDOWS
#define MILE_PLATFORM_WINDOWS

#if (defined(__cplusplus) && __cplusplus >= 201703L)
#elif (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#else
#error "[Mile] You should use a C++ compiler with the C++17 standard."
#endif

#include "Mile.Platform.h"

#include <Windows.h>

namespace Mile
{
    /**
     * @brief Wraps the Windows heap memory manager.
    */
    class HeapMemory
    {
    public:

        /**
         * @brief Allocates a block of memory from the default heap of the
         *        calling process. The allocated memory will be initialized to
         *        zero. The allocated memory is not movable.
         * @param Size The number of bytes to be allocated.
         * @return If the function succeeds, the return value is a pointer to
         *         the allocated memory block. If the function fails, the
         *         return value is nullptr.
        */
        static LPVOID Allocate(
            _In_ SIZE_T Size) noexcept;

        /**
         * @brief Reallocates a block of memory from the default heap of the
         *        calling process. If the reallocation request is for a larger
         *        size, the additional region of memory beyond the original
         *        size be initialized to zero. This function enables you to
         *        resize a memory block and change other memory block
         *        properties. The allocated memory is not movable.
         * @param Block A pointer to the block of memory that the function
         *              reallocates. This pointer is returned by an earlier
         *              call to Allocate and Reallocate method.
         * @param Size The new size of the memory block, in bytes. A memory
         *             block's size can be increased or decreased by using this
         *             function.
         * @return If the function succeeds, the return value is a pointer to
         *         the reallocated memory block. If the function fails, the
         *         return value is nullptr.
        */
        static LPVOID Reallocate(
            _In_ PVOID Block,
            _In_ SIZE_T Size) noexcept;

        /**
         * @brief Frees a memory block allocated from a heap by the Allocate or
         *        Reallocate method.
         * @param Block A pointer to the memory block to be freed. This pointer
         *              is returned by the Allocate or Reallocate method. If
         *              this pointer is nullptr, the behavior is undefined.
         * @return If the function succeeds, the return value is nonzero. If
         *         the function fails, the return value is zero. An application
         *         can call GetLastError for extended error information.
        */
        static BOOL Free(
            _In_ LPVOID Block) noexcept;
    };

    /**
     * @brief Wraps a critical section object.
    */
    class CriticalSection : DisableCopyConstruction, DisableMoveConstruction
    {
    public:

        /**
         * @brief Initializes a critical section object.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see InitializeCriticalSection.
         */
        static void Initialize(
            _Out_ LPCRITICAL_SECTION lpCriticalSection) noexcept;

        /**
         * @brief Releases all resources used by an unowned critical section
         *        object.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see DeleteCriticalSection.
         */
        static void Delete(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept;

        /**
         * @brief Waits for ownership of the specified critical section object.
         *        The function returns when the calling thread is granted
         *        ownership.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see EnterCriticalSection.
         */
        static void Enter(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept;

        /**
         * @brief Attempts to enter a critical section without blocking. If the
         *        call is successful, the calling thread takes ownership of the
         *        critical section.
         * @param lpCriticalSection A pointer to the critical section object.
         * @return If the critical section is successfully entered or the
         *         current thread already owns the critical section, the return
         *         value is true. If another thread already owns the critical
         *         section, the return value is false.
         * @remark For more information, see TryEnterCriticalSection.
         */
        static bool TryEnter(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept;

        /**
         * @brief Releases ownership of the specified critical section object.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see LeaveCriticalSection.
         */
        static void Leave(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept;

    private:

        /**
         * @brief The raw critical section object.
        */
        CRITICAL_SECTION m_RawObject;

    public:

        /**
         * @brief Initializes the critical section object. 
        */
        CriticalSection() noexcept;

        /**
         * @brief Releases all resources used by the critical section object.
        */
        ~CriticalSection() noexcept;

        /**
         * @brief Waits for ownership of the critical section object. The
         *        function returns when the calling thread is granted ownership.
        */
        void Lock() noexcept;

        /**
         * @brief Attempts to enter the critical section without blocking. If
         *        the call is successful, the calling thread takes ownership of
         *        the critical section.
         * @return If the critical section is successfully entered or the
         *         current thread already owns the critical section, the return
         *         value is true. If another thread already owns the critical
         *         section, the return value is false.
        */
        bool TryLock() noexcept;

        /**
         * @brief Releases ownership of the critical section object.
        */
        void Unlock() noexcept;
    };

    /**
     * @brief Provides automatic locking and unlocking of a critical section.
    */
    class AutoCriticalSectionLock
    {
    private:

        /**
         * @brief The critical section object.
        */
        CriticalSection& m_Object;

    public:

        /**
         * @brief Lock the critical section object.
         * @param Object The critical section object.
        */
        explicit AutoCriticalSectionLock(
            CriticalSection& Object) noexcept;

        /**
         * @brief Unlock the critical section object.
        */
        ~AutoCriticalSectionLock() noexcept;
    };

    /**
     * @brief Provides automatic trying to lock and unlocking of a critical
     *        section.
    */
    class AutoCriticalSectionTryLock
    {
    private:

        /**
         * @brief The critical section object.
        */
        CriticalSection& m_Object;

        /**
         * @brief The lock status.
        */
        bool m_IsLocked;

    public:

        /**
         * @brief Try to lock the critical section object.
         * @param Object The critical section object.
        */
        explicit AutoCriticalSectionTryLock(
            CriticalSection& Object) noexcept;

        /**
         * @brief Try to unlock the critical section object.
        */
        ~AutoCriticalSectionTryLock() noexcept;

        /**
         * @brief Check the lock status.
         * @return The lock status.
        */
        bool IsLocked() const;
    };

    /**
     * @brief Wraps a slim reader/writer (SRW) lock.
    */
    class SRWLock : DisableCopyConstruction, DisableMoveConstruction
    {
    public:

        /**
         * @brief Initialize a slim reader/writer (SRW) lock.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see InitializeSRWLock.
         */
        static void Initialize(
            _Out_ PSRWLOCK SRWLock) noexcept;

        /**
         * @brief Acquires a slim reader/writer (SRW) lock in exclusive mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see AcquireSRWLockExclusive.
         */
        static void AcquireExclusive(
            _Inout_ PSRWLOCK SRWLock) noexcept;

        /**
         * @brief Attempts to acquire a slim reader/writer (SRW) lock in
         *        exclusive mode. If the call is successful, the calling thread
         *        takes ownership of the lock.
         * @param SRWLock A pointer to the SRW lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
         * @remark For more information, see TryAcquireSRWLockExclusive.
         */
        static bool TryAcquireExclusive(
            _Inout_ PSRWLOCK SRWLock) noexcept;

        /**
         * @brief Releases a slim reader/writer (SRW) lock that was acquired in
         *        exclusive mode.
         *
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see ReleaseSRWLockExclusive.
         */
        static void ReleaseExclusive(
            _Inout_ PSRWLOCK SRWLock) noexcept;

        /**
         * @brief Acquires a slim reader/writer (SRW) lock in shared mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see AcquireSRWLockShared.
         */
        static void AcquireShared(
            _Inout_ PSRWLOCK SRWLock) noexcept;

        /**
         * @brief Attempts to acquire a slim reader/writer (SRW) lock in shared
         *        mode. If the call is successful, the calling thread takes
         *        ownership of the lock.
         * @param SRWLock A pointer to the SRW lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
         * @remark For more information, see TryAcquireSRWLockShared.
         */
        static bool TryAcquireShared(
            _Inout_ PSRWLOCK SRWLock) noexcept;

        /**
         * @brief Releases a slim reader/writer (SRW) lock that was acquired in
         *        shared mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see ReleaseSRWLockShared.
         */
        static void ReleaseShared(
            _Inout_ PSRWLOCK SRWLock) noexcept;

    private:

        /**
         * @brief The raw slim reader/writer (SRW) lock object.
        */
        SRWLOCK m_RawObject;

    public:

        /**
         * @brief Initialize the slim reader/writer (SRW) lock.
        */
        SRWLock() noexcept;

        /**
         * @brief Acquires the slim reader/writer (SRW) lock in exclusive mode.
        */
        void LockExclusive() noexcept;

        /**
         * @brief Attempts to acquire the slim reader/writer (SRW) lock in
         *        exclusive mode. If the call is successful, the calling thread
         *        takes ownership of the lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
        */
        bool TryLockExclusive() noexcept;

        /**
         * @brief Releases the slim reader/writer (SRW) lock that was acquired
         *        in exclusive mode.
        */
        void UnlockExclusive() noexcept;

        /**
         * @brief Acquires the slim reader/writer (SRW) lock in shared mode.
        */
        void LockShared() noexcept;

        /**
         * @brief Attempts to acquire the slim reader/writer (SRW) lock in
         *        shared mode. If the call is successful, the calling thread
         *        takes ownership of the lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
        */
        bool TryLockShared() noexcept;

        /**
         * @brief Releases the slim reader/writer (SRW) lock that was acquired
         *        in shared mode.
        */
        void UnlockShared() noexcept;
    };
}

#endif // !MILE_PLATFORM_WINDOWS
