/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Core.h
 * PURPOSE:   Core Implementation for Windows (Header Only)
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS_CORE
#define MILE_WINDOWS_CORE

#if (defined(__cplusplus) && __cplusplus >= 201703L)
#elif (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#else
#error "[Mile] You should use a C++ compiler with the C++17 standard."
#endif

#include <Windows.h>

#include <string>

namespace Mile
{
    /**
     * @brief Disables C++ class copy construction.
    */
    class DisableCopyConstruction
    {
    protected:
        DisableCopyConstruction() = default;
        ~DisableCopyConstruction() = default;

    private:
        DisableCopyConstruction(
            const DisableCopyConstruction&) = delete;
        DisableCopyConstruction& operator=(
            const DisableCopyConstruction&) = delete;
    };

    /**
     * @brief Disables C++ class move construction.
    */
    class DisableMoveConstruction
    {
    protected:
        DisableMoveConstruction() = default;
        ~DisableMoveConstruction() = default;

    private:
        DisableMoveConstruction(
            const DisableMoveConstruction&&) = delete;
        DisableMoveConstruction& operator=(
            const DisableMoveConstruction&&) = delete;
    };

    /**
     * @brief The template for defining the unique objects.
     * @tparam TraitsType A traits type that specifies the kind of unique
     *                    object being represented.
    */
    template <typename TraitsType>
    class UniqueObject : DisableCopyConstruction
    {
    public:

        /**
         * @brief The object type alias of the unique object.
        */
        using ObjectType = typename TraitsType::Type;

    private:

        /**
         * @brief The raw value of the unique object.
        */
        ObjectType m_Value = TraitsType::Invalid();

    public:

        /**
         * @brief Closes the underlying unique object.
        */
        void Close() noexcept
        {
            if (*this)
            {
                TraitsType::Close(this->m_Value);
                this->m_Value = TraitsType::Invalid();
            }
        }

        /**
         * @brief Returns the underlying unique object value, should you need
         *        to pass it to a function.
         * @return The underlying unique object value represented by the unique
         *         object.
        */
        ObjectType Get() const noexcept
        {
            return this->m_Value;
        }

        /**
         * @brief Returns the address of the unique object value; this function
         *        helps you call methods that return references as out
         *        parameters via a pointer to a unique object.
         * @return The address of the underlying unique object value
         *         represented by the unique object.
        */
        ObjectType* Put() noexcept
        {
            return &this->m_Value;
        }

        /**
         * @brief Attaches to a unique object value, and takes ownership of it.
         * @param Value A unique object value to attach to.
        */
        void Attach(ObjectType Value) noexcept
        {
            this->Close();
            *this->Put() = Value;
        }

        /**
         * @brief Detaches from the underlying unique object value.
         * @return The underlying unique object value formerly represented by
         *         the unique object.
        */
        ObjectType Detach() noexcept
        {
            ObjectType Value = this->m_Value;
            this->m_Value = TraitsType::Invalid();
            return Value;
        }

    public:

        /**
         * @brief Initializes a new instance of the unique object.
        */
        UniqueObject() noexcept = default;

        /**
         * @brief Initializes a new instance of the unique object.
         * @param Value A value that initializes the unique object.
        */
        explicit UniqueObject(ObjectType Value) noexcept :
            m_Value(Value)
        {
        }

        /**
         * @brief Initializes a new instance of the unique object.
         * @param Other Another unique object that initializes the unique
         *        object.
        */
        UniqueObject(UniqueObject&& Other) noexcept :
            m_Value(Other.Detach())
        {
        }

        /**
         * @brief Assigns a value to the unique object.
         * @param Other A unique object value to assign to the unique object.
         * @return A reference to the unique object.
        */
        UniqueObject& operator=(UniqueObject&& Other) noexcept
        {
            if (this != &Other)
            {
                this->Attach(Other.Detach());
            }

            return *this;
        }

        /**
         * @brief Uninitializes the instance of the unique object.
        */
        ~UniqueObject() noexcept
        {
            this->Close();
        }

        /**
         * @brief Checks whether or not the unique object currently represents
         *        a valid unique object value.
         * @return true if the unique object currently represents a valid
         *         unique object value, otherwise false.
        */
        explicit operator bool() const noexcept
        {
            return TraitsType::Invalid() != this->m_Value;
        }

        /**
         * @brief Swaps the contents of the two unique object parameters so
         *        that they contain one another's unique object.
         * @param Left A unique object value whose handle to mutually swap with
         *             that of the other parameter.
         * @param Right A unique object value whose handle to mutually swap
         *              with that of the other parameter.
        */
        friend void swap(UniqueObject& Left, UniqueObject& Right) noexcept
        {
            std::swap(Left.m_Value, Right.m_Value);
        }
    };

    /**
     * @brief A type representing an HRESULT error code.
    */
    class HResult
    {
    public:

        /**
         * @brief The HRESULT error code represented by the HResult object.
        */
        HRESULT Value{ S_OK };

    public:

        /**
         * @brief Initializes a new instance of the HResult object.
         * @return A new instance of the HResult object.
        */
        constexpr HResult() noexcept = default;

        /**
         * @brief Initializes a new instance of the HResult object by an
         *        HRESULT code.
         * @param Value An HRESULT code that initializes the HResult object.
         * @return A new instance of the HResult object.
        */
        constexpr HResult(
            _In_ HRESULT const Value) noexcept : Value(Value)
        {
        }

        /**
         * @brief Initializes a new instance of the HResult object by a system
         *        error code.
         * @param Code The system error code.
         * @return A new instance of the HResult object.
        */
        static HResult FromWin32(
            _In_ DWORD Code) noexcept
        {
            return HResult(::HRESULT_FROM_WIN32(Code));
        }

        /**
         * @brief Initializes a new instance of the HResult object by the
         *        calling thread's last-error code.
         * @return A new instance of the HResult object.
        */
        static HResult FromLastError() noexcept
        {
            return FromWin32(::GetLastError());
        }

        /**
         * @brief Initializes a new instance of the HResult object by the
         *        calling thread's last-error code with the evaluation of the
         *        Win32 BOOL value. 
         * @param Result The Win32 BOOL value.
         * @return A new instance of the HResult object.
        */
        static HResult FromLastError(
            _In_ BOOL Result) noexcept
        {
            HResult hr = S_OK;

            if (!Result)
            {
                hr = FromLastError();
                if (hr == S_OK)
                {
                    hr = FromWin32(ERROR_FUNCTION_FAILED);
                }
            }

            return hr;
        }

    public:

        /**
         * @brief Retrieves the HRESULT error code for the error represented by
         *        the HResult object.
         * @return An HRESULT error code.
        */
        constexpr operator HRESULT() const noexcept
        {
            return this->Value;
        }

        /**
         * @brief Retrieves the message for the error represented by the
         *        HResult object.
         * @return A std::wstring containing the error messsage.
        */
        std::wstring ToMessage() const noexcept
        {
            std::wstring Message{ L"Failed to get formatted message." };

            LPWSTR RawMessage = nullptr;
            DWORD RawMessageSize = ::FormatMessageW(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr,
                this->Value,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                reinterpret_cast<LPTSTR>(&RawMessage),
                0,
                nullptr);
            if (RawMessageSize)
            {
                Message = std::wstring(RawMessage, RawMessageSize);

                ::LocalFree(RawMessage);
            }

            return Message;
        }

        /**
         * @brief Test for success on HRESULT error code represented by the
         *        HResult object.
         * @return The test result.
        */
        bool IsSucceeded() const noexcept
        {
            return SUCCEEDED(this->Value);
        }

        /**
         * @brief Test for failed on HRESULT error code represented by the
         *        HResult object.
         * @return The test result.
        */
        bool IsFailed() const noexcept
        {
            return FAILED(this->Value);
        }

        /**
         * @brief Test for errors on HRESULT error code represented by the
         *        HResult object.
         * @return The test result.
        */
        bool IsError() const noexcept
        {
            return IS_ERROR(this->Value);
        }

        /**
         * @brief Extracts the facility portion of HRESULT error code
         *        represented by the HResult object.
         * @return The facility portion value of HRESULT error code represented
         *         by the HResult object.
        */
        DWORD GetFacility() const noexcept
        {
            return HRESULT_FACILITY(this->Value);
        }

        /**
         * @brief Extracts the code portion of HRESULT error code represented
         *        by the HResult object.
         * @return The code portion value of HRESULT error code represented by
         *         the HResult object.
        */
        DWORD GetCode() const noexcept
        {
            return HRESULT_CODE(this->Value);
        }
    };

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
            _In_ SIZE_T Size) noexcept
        {
            return ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
        }

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
            _In_ SIZE_T Size) noexcept
        {
            return ::HeapReAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, Block, Size);
        }

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
            _In_ LPVOID Block) noexcept
        {
            return ::HeapFree(::GetProcessHeap(), 0, Block);
        }
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
            _Out_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            ::InitializeCriticalSection(lpCriticalSection);
        }

        /**
         * @brief Releases all resources used by an unowned critical section
         *        object.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see DeleteCriticalSection.
         */
        static void Delete(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            ::DeleteCriticalSection(lpCriticalSection);
        }

        /**
         * @brief Waits for ownership of the specified critical section object.
         *        The function returns when the calling thread is granted
         *        ownership.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see EnterCriticalSection.
         */
        static void Enter(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            ::EnterCriticalSection(lpCriticalSection);
        }

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
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            return FALSE != ::TryEnterCriticalSection(lpCriticalSection);
        }

        /**
         * @brief Releases ownership of the specified critical section object.
         * @param lpCriticalSection A pointer to the critical section object.
         * @remark For more information, see LeaveCriticalSection.
         */
        static void Leave(
            _Inout_ LPCRITICAL_SECTION lpCriticalSection) noexcept
        {
            ::LeaveCriticalSection(lpCriticalSection);
        }

    private:

        /**
         * @brief The raw critical section object.
        */
        CRITICAL_SECTION m_RawObject;

    public:

        /**
         * @brief Initializes the critical section object.
        */
        CriticalSection() noexcept
        {
            Initialize(&this->m_RawObject);
        }

        /**
         * @brief Releases all resources used by the critical section object.
        */
        ~CriticalSection() noexcept
        {
            Delete(&this->m_RawObject);
        }

        /**
         * @brief Waits for ownership of the critical section object. The
         *        function returns when the calling thread is granted ownership.
        */
        void Lock() noexcept
        {
            Enter(&this->m_RawObject);
        }

        /**
         * @brief Attempts to enter the critical section without blocking. If
         *        the call is successful, the calling thread takes ownership of
         *        the critical section.
         * @return If the critical section is successfully entered or the
         *         current thread already owns the critical section, the return
         *         value is true. If another thread already owns the critical
         *         section, the return value is false.
        */
        bool TryLock() noexcept
        {
            return TryEnter(&this->m_RawObject);
        }

        /**
         * @brief Releases ownership of the critical section object.
        */
        void Unlock() noexcept
        {
            Leave(&this->m_RawObject);
        }
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
            CriticalSection& Object) noexcept :
            m_Object(Object)
        {
            this->m_Object.Lock();
        }

        /**
         * @brief Unlock the critical section object.
        */
        ~AutoCriticalSectionLock() noexcept
        {
            this->m_Object.Unlock();
        }
    };

    /**
     * @brief Provides automatic trying to locking and unlocking of a critical
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
            CriticalSection& Object) noexcept :
            m_Object(Object)
        {
            this->m_IsLocked = this->m_Object.TryLock();
        }

        /**
         * @brief Try to unlock the critical section object.
        */
        ~AutoCriticalSectionTryLock() noexcept
        {
            if (this->m_IsLocked)
            {
                this->m_Object.Unlock();
            }
        }

        /**
         * @brief Check the lock status.
         * @return The lock status.
        */
        bool IsLocked() const
        {
            return this->m_IsLocked;
        }
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
            _Out_ PSRWLOCK SRWLock) noexcept
        {
            ::InitializeSRWLock(SRWLock);
        }

        /**
         * @brief Acquires a slim reader/writer (SRW) lock in exclusive mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see AcquireSRWLockExclusive.
         */
        static void AcquireExclusive(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            ::AcquireSRWLockExclusive(SRWLock);
        }

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
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            return FALSE != ::TryAcquireSRWLockExclusive(SRWLock);
        }

        /**
         * @brief Releases a slim reader/writer (SRW) lock that was acquired in
         *        exclusive mode.
         *
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see ReleaseSRWLockExclusive.
         */
        static void ReleaseExclusive(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            ::ReleaseSRWLockExclusive(SRWLock);
        }

        /**
         * @brief Acquires a slim reader/writer (SRW) lock in shared mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see AcquireSRWLockShared.
         */
        static void AcquireShared(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            ::AcquireSRWLockShared(SRWLock);
        }

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
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            return FALSE != ::TryAcquireSRWLockShared(SRWLock);
        }

        /**
         * @brief Releases a slim reader/writer (SRW) lock that was acquired in
         *        shared mode.
         * @param SRWLock A pointer to the SRW lock.
         * @remark For more information, see ReleaseSRWLockShared.
         */
        static void ReleaseShared(
            _Inout_ PSRWLOCK SRWLock) noexcept
        {
            ::ReleaseSRWLockShared(SRWLock);
        }

    private:

        /**
         * @brief The raw slim reader/writer (SRW) lock object.
        */
        SRWLOCK m_RawObject;

    public:

        /**
         * @brief Initialize the slim reader/writer (SRW) lock.
        */
        SRWLock() noexcept
        {
            Initialize(&this->m_RawObject);
        }

        /**
         * @brief Acquires the slim reader/writer (SRW) lock in exclusive mode.
        */
        void LockExclusive() noexcept
        {
            AcquireExclusive(&this->m_RawObject);
        }

        /**
         * @brief Attempts to acquire the slim reader/writer (SRW) lock in
         *        exclusive mode. If the call is successful, the calling thread
         *        takes ownership of the lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
        */
        bool TryLockExclusive() noexcept
        {
            return TryAcquireExclusive(&this->m_RawObject);
        }

        /**
         * @brief Releases the slim reader/writer (SRW) lock that was acquired
         *        in exclusive mode.
        */
        void UnlockExclusive() noexcept
        {
            ReleaseExclusive(&this->m_RawObject);
        }

        /**
         * @brief Acquires the slim reader/writer (SRW) lock in shared mode.
        */
        void LockShared() noexcept
        {
            AcquireShared(&this->m_RawObject);
        }

        /**
         * @brief Attempts to acquire the slim reader/writer (SRW) lock in
         *        shared mode. If the call is successful, the calling thread
         *        takes ownership of the lock.
         * @return If the lock is successfully acquired, the return value is
         *         true. If the current thread could not acquire the lock, the
         *         return value is false.
        */
        bool TryLockShared() noexcept
        {
            return TryAcquireShared(&this->m_RawObject);
        }

        /**
         * @brief Releases the slim reader/writer (SRW) lock that was acquired
         *        in shared mode.
        */
        void UnlockShared() noexcept
        {
            ReleaseShared(&this->m_RawObject);
        }
    };

    /**
     * @brief Provides automatic exclusive locking and unlocking of a slim
     *        reader/writer (SRW) lock.
    */
    class AutoSRWExclusiveLock
    {
    private:

        /**
         * @brief The slim reader/writer (SRW) lock object.
        */
        SRWLock& m_Object;

    public:

        /**
         * @brief Exclusive lock the slim reader/writer (SRW) lock object.
         * @param Object The slim reader/writer (SRW) lock object.
        */
        explicit AutoSRWExclusiveLock(
            SRWLock& Object) noexcept :
            m_Object(Object)
        {
            this->m_Object.LockExclusive();
        }

        /**
         * @brief Exclusive unlock the slim reader/writer (SRW) lock object.
        */
        ~AutoSRWExclusiveLock() noexcept
        {
            this->m_Object.UnlockExclusive();
        }
    };

    /**
     * @brief Provides automatic trying to exclusive locking and unlocking of a
     *        slim reader/writer (SRW) lock.
    */
    class AutoSRWExclusiveTryLock
    {
    private:

        /**
         * @brief The slim reader/writer (SRW) lock object.
        */
        SRWLock& m_Object;

        /**
         * @brief The lock status.
        */
        bool m_IsLocked;

    public:

        /**
         * @brief Try to exclusive lock the slim reader/writer (SRW) lock
         *        object.
         * @param Object The slim reader/writer (SRW) lock object.
        */
        explicit AutoSRWExclusiveTryLock(
            SRWLock& Object) noexcept :
            m_Object(Object)
        {
            this->m_IsLocked = this->m_Object.TryLockExclusive();
        }

        /**
         * @brief Try to exclusive unlock the slim reader/writer (SRW) lock
         *        object.
        */
        ~AutoSRWExclusiveTryLock() noexcept
        {
            if (this->m_IsLocked)
            {
                this->m_Object.UnlockExclusive();
            }
        }

        /**
         * @brief Check the lock status.
         * @return The lock status.
        */
        bool IsLocked() const
        {
            return this->m_IsLocked;
        }
    };

    /**
     * @brief Provides automatic shared locking and unlocking of a slim
     *        reader/writer (SRW) lock.
    */
    class AutoSRWSharedLock
    {
    private:

        /**
         * @brief The slim reader/writer (SRW) lock object.
        */
        SRWLock& m_Object;

    public:

        /**
         * @brief Shared lock the slim reader/writer (SRW) lock object.
         * @param Object The slim reader/writer (SRW) lock object.
        */
        explicit AutoSRWSharedLock(
            SRWLock& Object) noexcept :
            m_Object(Object)
        {
            this->m_Object.LockShared();
        }

        /**
         * @brief Shared unlock the slim reader/writer (SRW) lock object.
        */
        ~AutoSRWSharedLock() noexcept
        {
            this->m_Object.UnlockShared();
        }
    };

    /**
     * @brief Provides automatic trying to shared locking and unlocking of a
     *        slim reader/writer (SRW) lock.
    */
    class AutoSRWSharedTryLock
    {
    private:

        /**
         * @brief The slim reader/writer (SRW) lock object.
        */
        SRWLock& m_Object;

        /**
         * @brief The lock status.
        */
        bool m_IsLocked;

    public:

        /**
         * @brief Try to shared lock the slim reader/writer (SRW) lock object.
         * @param Object The slim reader/writer (SRW) lock object.
        */
        explicit AutoSRWSharedTryLock(
            SRWLock& Object) noexcept :
            m_Object(Object)
        {
            this->m_IsLocked = this->m_Object.TryLockShared();
        }

        /**
         * @brief Try to shared unlock the slim reader/writer (SRW) lock
         *        object.
        */
        ~AutoSRWSharedTryLock() noexcept
        {
            if (this->m_IsLocked)
            {
                this->m_Object.UnlockShared();
            }
        }

        /**
         * @brief Check the lock status.
         * @return The lock status.
        */
        bool IsLocked() const
        {
            return this->m_IsLocked;
        }
    };
}

#endif // !MILE_WINDOWS_CORE
