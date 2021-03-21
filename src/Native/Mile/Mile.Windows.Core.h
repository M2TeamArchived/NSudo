/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Core.h
 * PURPOSE:   Core Definition for Windows
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
#include <utility>
namespace Mile
{
#pragma region Definitions and Implementations for All Platforms

    /**
     * @brief Suppresses the "unreferenced parameter" compiler warning by
     *        referencing a variable which is not used.
     * @tparam VariableType The type of the variable which is not used.
     * @param The variable which is not used.
     * @remark For more information, see UNREFERENCED_PARAMETER.
    */
    template<typename VariableType>
    void UnreferencedParameter(VariableType const&)
    {
    }

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
     * @brief The template for defining the task when exit the scope.
     * @tparam TaskHandlerType The type of the task handler.
     * @remark For more information, see ScopeGuard.
    */
    template<typename TaskHandlerType>
    class ScopeExitTaskHandler :
        DisableCopyConstruction,
        DisableMoveConstruction
    {
    private:
        bool m_Canceled;
        TaskHandlerType m_TaskHandler;

    public:

        /**
         * @brief Creates the instance for the task when exit the scope.
         * @param TaskHandler The instance of the task handler.
        */
        explicit ScopeExitTaskHandler(TaskHandlerType&& EventHandler) :
            m_Canceled(false),
            m_TaskHandler(std::forward<TaskHandlerType>(EventHandler))
        {

        }

        /**
         * @brief Executes and uninitializes the instance for the task when
         *        exit the scope.
        */
        ~ScopeExitTaskHandler()
        {
            if (!this->m_Canceled)
            {
                this->m_TaskHandler();
            }
        }

        /**
         * @brief Cancels the task when exit the scope.
        */
        void Cancel()
        {
            this->m_Canceled = true;
        }
    };

#pragma endregion

#pragma region Definitions and Implementations for Windows

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
     * @brief A type representing a converter which converts the calling
     *        thread's last-error code to the HResult object.
    */
    class HResultFromLastError
    {
    private:

        /**
         * @brief Indicates needed the evaluation of the Win32 BOOL value.
        */
        bool m_EvaluateWithWin32Bool;

        /**
         * @brief The Win32 BOOL value.
        */
        BOOL m_Value;

    public:

        /**
         * @brief Initializes a new instance of the HResultFromLastError object
         *        by the calling thread's last-error code.
        */
        HResultFromLastError() :
            m_EvaluateWithWin32Bool(false),
            m_Value(FALSE)
        {
        }

        /**
         * @brief Initializes a new instance of the HResultFromLastError object
         *        by the calling thread's last-error code with the evaluation
         *        of the Win32 BOOL value.
         * @param Result The Win32 BOOL value.
        */
        HResultFromLastError(
            _In_ BOOL Result) :
            m_EvaluateWithWin32Bool(true),
            m_Value(Result)
        {
        }

        /**
         * @brief Converts the calling thread's last-error code to the HResult
         *        object.
        */
        operator HResult()
        {
            // Return if Win32 BOOL value is TRUE.
            // By design, If the this->m_Value is euqal to true,
            // the this->m_EvaluateWithWin32Bool is also euqal to true.
            if (this->m_Value)
            {
                return S_OK;
            }

            HResult hr = HResult::FromWin32(::GetLastError());

            // Set hr failed when hr succeed if it needs the evaluation of the
            // Win32 BOOL value and the Win32 BOOL value is FALSE.
            if (this->m_EvaluateWithWin32Bool && hr == S_OK)
            {
                hr = HResult::FromWin32(ERROR_FUNCTION_FAILED);
            }

            return hr;
        }

        /**
         * @brief Converts the calling thread's last-error code to the HRESULT
         *        value.
        */
        operator HRESULT()
        {
            return this->operator Mile::HResult();
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

#pragma endregion

#pragma region Definitions for Windows (Win32 Style)

    /**
     * @brief The definition of the file enumerator handle.
    */
    typedef void* FILE_ENUMERATOR_HANDLE;
    typedef FILE_ENUMERATOR_HANDLE* PFILE_ENUMERATOR_HANDLE;

    /**
     * @brief The information about a found file or directory queried from the
     *        file enumerator.
    */
    typedef struct _FILE_ENUMERATOR_INFORMATION
    {
        FILETIME CreationTime;
        FILETIME LastAccessTime;
        FILETIME LastWriteTime;
        FILETIME ChangeTime;
        UINT64 FileSize;
        UINT64 AllocationSize;
        DWORD FileAttributes;
        DWORD EaSize;
        LARGE_INTEGER FileId;
        WCHAR ShortName[16];
        WCHAR FileName[256];
    } FILE_ENUMERATOR_INFORMATION, *PFILE_ENUMERATOR_INFORMATION;

    /**
     * @brief Sends a control code directly to a specified device driver,
     *        causing the corresponding device to perform the corresponding
     *        operation.
     * @param hDevice A handle to the device on which the operation is to be
     *                performed. The device is typically a volume, directory,
     *                file, or stream. To retrieve a device handle, use the
     *                CreateFile function.
     * @param dwIoControlCode The control code for the operation. This value
     *                        identifies the specific operation to be performed
     *                        and the type of device on which to perform it.
     * @param lpInBuffer A pointer to the input buffer that contains the data
     *                   required to perform the operation. The format of this
     *                   data depends on the value of the dwIoControlCode
     *                   parameter. This parameter can be nullptr if
     *                   dwIoControlCode specifies an operation that does not
     *                   require input data.
     * @param nInBufferSize The size of the input buffer, in bytes.
     * @param lpOutBuffer A pointer to the output buffer that is to receive the
     *                    data returned by the operation. The format of this
     *                    data depends on the value of the dwIoControlCode
     *                    parameter. This parameter can be nullptr if
     *                    dwIoControlCode specifies an operation that does not
     *                    return data.
     * @param nOutBufferSize The size of the output buffer, in bytes.
     * @param lpBytesReturned A pointer to a variable that receives the size of
     *                        the data stored in the output buffer, in bytes.
     *                        If the output buffer is too small to receive any
     *                        data, the call fails, GetLastError returns
     *                        ERROR_INSUFFICIENT_BUFFER, and lpBytesReturned is
     *                        zero. If the output buffer is too small to hold
     *                        all of the data but can hold some entries, some
     *                        drivers will return as much data as fits. In this
     *                        case, the call fails, GetLastError returns
     *                        ERROR_MORE_DATA, and lpBytesReturned indicates
     *                        the amount of data received. Your application
     *                        should call DeviceIoControl again with the same
     *                        operation, specifying a new starting point.
     * @return An HResultFromLastError object An containing the HResult object
     *         containing the error code.
     * @remark For more information, see DeviceIoControl.
    */
    HResultFromLastError DeviceIoControl(
        _In_ HANDLE hDevice,
        _In_ DWORD dwIoControlCode,
        _In_opt_ LPVOID lpInBuffer,
        _In_ DWORD nInBufferSize,
        _Out_opt_ LPVOID lpOutBuffer,
        _In_ DWORD nOutBufferSize,
        _Out_opt_ LPDWORD lpBytesReturned);

    /**
     * @brief Gets the NTFS compression attribute.
     * @param FileHandle A handle to the file or directory on which the
     *                   operation is to be performed. To retrieve a handle,
     *                   use the CreateFile or a similar API.
     * @param CompressionAlgorithm Specifies the compression algorithm that is
     *                             used to compress this file. Currently
     *                             defined algorithms are:
     *                             COMPRESSION_FORMAT_NONE
     *                                 Uncompress the file or directory.
     *                             COMPRESSION_FORMAT_DEFAULT
     *                                 Compress the file or directory, using
     *                                 the default compression format.
     *                             COMPRESSION_FORMAT_LZNT1
     *                                 Compress the file or directory, using
     *                                 the LZNT1 compression format.
     * @return An HResultFromLastError object An containing the HResult object
     *         containing the error code.
    */
    HResultFromLastError GetNtfsCompressionAttribute(
        _In_ HANDLE FileHandle,
        _Out_ PUSHORT CompressionAlgorithm);

    /**
     * @brief Sets the NTFS compression attribute.
     * @param FileHandle A handle to the file or directory on which the
     *                   operation is to be performed. To retrieve a handle,
     *                   use the CreateFile or a similar API.
     * @param CompressionAlgorithm Specifies the compression algorithm that is
     *                             used to compress this file. Currently
     *                             defined algorithms are:
     *                             COMPRESSION_FORMAT_NONE
     *                                 Uncompress the file or directory.
     *                             COMPRESSION_FORMAT_DEFAULT
     *                                 Compress the file or directory, using
     *                                 the default compression format.
     *                             COMPRESSION_FORMAT_LZNT1
     *                                 Compress the file or directory, using
     *                                 the LZNT1 compression format.
     * @return An HResultFromLastError object An containing the HResult object
     *         containing the error code.
    */
    HResultFromLastError SetNtfsCompressionAttribute(
        _In_ HANDLE FileHandle,
        _In_ USHORT CompressionAlgorithm);

    /**
     * @brief Gets the Windows Overlay Filter file compression attribute.
     * @param FileHandle A handle to the file on which the operation is to be
     *                   performed. To retrieve a handle, use the CreateFile or
     *                   a similar API.
     * @param CompressionAlgorithm Specifies the compression algorithm that is
     *                             used to compress this file. Currently
     *                             defined algorithms are:
     *                             FILE_PROVIDER_COMPRESSION_XPRESS4K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 4kb chunks with
     *                                 the XPress algorithm. This algorithm is
     *                                 designed to be computationally
     *                                 lightweight, and provides for rapid
     *                                 access to data.
     *                             FILE_PROVIDER_COMPRESSION_LZX
     *                                 Indicates that the data for the file
     *                                 should be compressed in 32kb chunks with
     *                                 the LZX algorithm. This algorithm is
     *                                 designed to be highly compact, and
     *                                 provides for small footprint for
     *                                 infrequently accessed data.
     *                             FILE_PROVIDER_COMPRESSION_XPRESS8K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 8kb chunks with
     *                                 the XPress algorithm.
     *                             FILE_PROVIDER_COMPRESSION_XPRESS16K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 16kb chunks with
     *                                 the XPress algorithm.
     * @return An HResultFromLastError object An containing the HResult object
     *         containing the error code.
    */
    HResultFromLastError GetWofCompressionAttribute(
        _In_ HANDLE FileHandle,
        _Out_ PDWORD CompressionAlgorithm);

    /**
     * @brief Sets the Windows Overlay Filter file compression attribute.
     * @param FileHandle A handle to the file on which the operation is to be
     *                   performed. To retrieve a handle, use the CreateFile or
     *                   a similar API.
     * @param CompressionAlgorithm Specifies the compression algorithm that is
     *                             used to compress this file. Currently
     *                             defined algorithms are:
     *                             FILE_PROVIDER_COMPRESSION_XPRESS4K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 4kb chunks with
     *                                 the XPress algorithm. This algorithm is
     *                                 designed to be computationally
     *                                 lightweight, and provides for rapid
     *                                 access to data.
     *                             FILE_PROVIDER_COMPRESSION_LZX
     *                                 Indicates that the data for the file
     *                                 should be compressed in 32kb chunks with
     *                                 the LZX algorithm. This algorithm is
     *                                 designed to be highly compact, and
     *                                 provides for small footprint for
     *                                 infrequently accessed data.
     *                             FILE_PROVIDER_COMPRESSION_XPRESS8K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 8kb chunks with
     *                                 the XPress algorithm.
     *                             FILE_PROVIDER_COMPRESSION_XPRESS16K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 16kb chunks with
     *                                 the XPress algorithm.
     * @return An HResultFromLastError object An containing the HResult object
     *         containing the error code.
    */
    HResultFromLastError SetWofCompressionAttribute(
        _In_ HANDLE FileHandle,
        _In_ DWORD CompressionAlgorithm);

    /**
     * @brief Removes the Windows Overlay Filter file compression attribute.
     * @param FileHandle A handle to the file on which the operation is to be
     *                   performed. To retrieve a handle, use the CreateFile or
     *                   a similar API.
     * @return An HResultFromLastError object An containing the HResult object
     *         containing the error code.
    */
    HResultFromLastError RemoveWofCompressionAttribute(
        _In_ HANDLE FileHandle);

    /**
     * @brief Sets the system's compression (Compact OS) state.
     * @param DeploymentState The system's compression (Compact OS) state. If
     *                        this value is TRUE, the system state means
     *                        Compact. If it is FALSE, the system state means
     *                        non Compact.
     * @return An HResult object containing the error code.
    */
    HResult GetCompactOsDeploymentState(
        _Out_ PDWORD DeploymentState);

    /**
     * @brief Gets the system's compression (Compact OS) state.
     * @param DeploymentState The system's compression (Compact OS) state. If
     *                        this value is TRUE, the function sets the system
     *                        state to Compact. If it is FALSE, the function
     *                        sets the system state to non Compact.
     * @return An HResult object containing the error code.
    */
    HResult SetCompactOsDeploymentState(
        _In_ DWORD DeploymentState);

    /**
     * @brief Creates a file enumerator handle for searching a directory for a
     *        file or subdirectory with a name.
     * @param FileEnumeratorHandle The file enumerator handle.
     * @param FileHandle The handle of the file to be searched a directory for
     *                   a file or subdirectory with a name. This handle must
     *                   be opened with the appropriate permissions for the
     *                   requested change. This handle should not be a pipe
     *                   handle.
     * @return An HResult object containing the error code.
    */
    HResult CreateFileEnumerator(
        _Out_ PFILE_ENUMERATOR_HANDLE FileEnumeratorHandle,
        _In_ HANDLE FileHandle);

    /**
     * @brief Closes a file enumerator handle opened by CreateFileEnumerator.
     * @param FileEnumeratorHandle The file enumerator handle.
     * @return An HResultFromLastError object An containing the HResult object
     *         containing the error code.
    */
    HResultFromLastError CloseFileEnumerator(
        _In_ FILE_ENUMERATOR_HANDLE FileEnumeratorHandle);

    /**
     * @brief Starts or continues a file search from a file enumerator handle.
     * @param FileEnumeratorHandle The file enumerator handle.
     * @param FileEnumeratorInformation A pointer to the
     *                                  FILE_ENUMERATOR_INFORMATION structure
     *                                  that receives information about a found
     *                                  file or directory.
     * @return An HResultFromLastError object An containing the HResult object
     *         containing the error code. If the function succeeds, the
     *         FileEnumeratorInformation parameter contains information about
     *         the next file or directory found. If the function fails, the
     *         contents of FileEnumeratorInformation are indeterminate. If the
     *         function fails because no more matching files can be found,
     *         the error code is HRESULT_FROM_WIN32(ERROR_NO_MORE_FILES).
    */
    HResultFromLastError QueryFileEnumerator(
        _In_ FILE_ENUMERATOR_HANDLE FileEnumeratorHandle,
        _Out_ PFILE_ENUMERATOR_INFORMATION FileEnumeratorInformation);

#pragma endregion

#pragma region Definitions for Windows (C++ Style)

    /**
     * @brief Retrieves the message for the error represented by the HResult object.
     * @param Value The HResult object which need to retrieve the message.
     * @return A std::wstring containing the error messsage.
    */
    std::wstring GetHResultMessage(
        HResult const& Value);

    /**
     * @brief Converts from the UTF-8 string to the UTF-16 string.
     * @param Utf8String The UTF-8 string you want to convert.
     * @return A converted UTF-16 string.
    */
    std::wstring ToUtf16String(
        std::string const& Utf8String);

    /**
     * @brief Converts from the UTF-16 string to the UTF-8 string.
     * @param Utf16String The UTF-16 string you want to convert.
     * @return A converted UTF-8 string.
    */
    std::string ToUtf8String(
        std::wstring const& Utf16String);

    /**
     * @brief Retrieves the path of the system directory. The system directory
     *        contains system files such as dynamic-link libraries and drivers.
     * @return The path of the system directory.
    */
    std::wstring GetSystemDirectoryW();

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

    /**
     * @brief Retrieves the path of the shared Windows directory on a
     *        multi-user system.
     * @return The path of the shared Windows directory on a multi-user system.
    */
    std::wstring GetWindowsDirectoryW();

#endif

    /**
     * @brief Expands environment variable strings and replaces them with the
     *        values defined for the current user.
     * @param SourceString The string that contains one or more environment
                           variable strings (in the %variableName% form) you
                           need to expand.
     * @return The result string of expanding the environment variable strings.
    */
    std::wstring ExpandEnvironmentStringsW(
        std::wstring const& SourceString);

#pragma endregion
}

#endif // !MILE_WINDOWS_CORE
