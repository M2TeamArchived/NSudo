/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsAPIWrappers.h
 * PURPOSE:   Definition for the Windows helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef _M2_WINDOWS_HELPERS_
#define _M2_WINDOWS_HELPERS_

#include <Windows.h>

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#include <ShellScalingApi.h>
#endif

#include <map>
#include <memory>
#include <string>
#include <vector>

#if (defined(__cplusplus) && __cplusplus >= 201703L)
#include <string_view>
#endif

#ifdef CPPWINRT_VERSION
#include <winrt\Windows.ApplicationModel.Core.h>
#include <winrt\Windows.Foundation.Collections.h>
#include <winrt\Windows.UI.Core.h>
#include <winrt\Windows.UI.Xaml.Data.h>
#include <winrt\Windows.UI.Xaml.Interop.h>
#endif

#ifdef __cplusplus_winrt
#include <inspectable.h>
#include <wrl\client.h>
#endif

#pragma region BaseTemplate

/**
 * If the type T is a reference type, provides the member typedef type which is
 * the type referred to by T. Otherwise type is T.
 */ 
template<class T> struct M2RemoveReference { typedef T Type; };
template<class T> struct M2RemoveReference<T&> { typedef T Type; };
template<class T> struct M2RemoveReference<T&&> { typedef T Type; };
#ifdef __cplusplus_winrt
template<class T> struct M2RemoveReference<T^> { typedef T Type; };
#endif

namespace M2
{
    /**
     * Disable C++ Object Copying
     */
    class CDisableObjectCopying
    {
    protected:
        CDisableObjectCopying() = default;
        ~CDisableObjectCopying() = default;

    private:
        CDisableObjectCopying(
            const CDisableObjectCopying&) = delete;
        CDisableObjectCopying& operator=(
            const CDisableObjectCopying&) = delete;
    };

    /**
     * The implementation of smart object.
     */
    template<typename TObject, typename TObjectDefiner>
    class CObject : CDisableObjectCopying
    {
    protected:
        TObject m_Object;
    public:
        CObject(TObject Object = TObjectDefiner::GetInvalidValue()) :
            m_Object(Object)
        {

        }

        ~CObject()
        {
            this->Close();
        }

        TObject* operator&()
        {
            return &this->m_Object;
        }

        TObject operator=(TObject Object)
        {
            if (Object != this->m_Object)
            {
                this->Close();
                this->m_Object = Object;
            }
            return (this->m_Object);
        }

        operator TObject()
        {
            return this->m_Object;
        }

        bool IsInvalid()
        {
            return (this->m_Object == TObjectDefiner::GetInvalidValue());
        }

        TObject Detach()
        {
            TObject Object = this->m_Object;
            this->m_Object = TObjectDefiner::GetInvalidValue();
            return Object;
        }

        void Close()
        {
            if (!this->IsInvalid())
            {
                TObjectDefiner::Close(this->m_Object);
                this->m_Object = TObjectDefiner::GetInvalidValue();
            }
        }

        TObject operator->() const
        {
            return this->m_Object;
        }
    };
}

#pragma endregion

#pragma region BaseRAII

namespace M2
{
    /**
     * The handle definer for HANDLE object.
     */
#pragma region CHandle

    struct CHandleDefiner
    {
        static inline HANDLE GetInvalidValue()
        {
            return INVALID_HANDLE_VALUE;
        }

        static inline void Close(HANDLE Object)
        {
            CloseHandle(Object);
        }
    };

    typedef CObject<HANDLE, CHandleDefiner> CHandle;

#pragma endregion
}

#pragma endregion

#pragma region Error

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastHRESULTError();

/**
 * Retrieves the calling thread's last-error code value if you can be sure that
 * the last call was failed. The last-error code is maintained on a per-thread
 * basis. Multiple threads do not overwrite each other's last-error code.
 *
 * @return The calling thread's last-error code.
 */
DWORD M2GetLastErrorKnownFailedCall();

/**
 * Retrieves the calling thread's last-error code value if you can be sure that
 * the last call was failed. The last-error code is maintained on a per-thread
 * basis. Multiple threads do not overwrite each other's last-error code.
 *
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastHRESULTErrorKnownFailedCall();

#ifdef __cplusplus_winrt

/**
 * Throw the appropriate Platform::Exception for the given HRESULT.
 *
 * @param hr The error HRESULT that is represented by the exception.
 * @return This function does not return a value, but will throw
 *         Platform::Exception.
 */
__declspec(noreturn) void M2ThrowPlatformException(HRESULT hr);

/**
 * Throw the appropriate Platform::Exception for the given HRESULT.
 *
 * @param hr The error HRESULT that is represented by the exception.
 * @return This function does not return a value, but will throw
 *         Platform::Exception if it is a failed HRESULT value.
 */
void M2ThrowPlatformExceptionIfFailed(HRESULT hr);

/**
 * Convert C++/CX exceptions in the callable code into HRESULTs.
 *
 * @return The function will return HRESULT.
 */
HRESULT M2ThrownPlatformExceptionToHResult();

#endif

#pragma endregion

#pragma region String

/**
 * Converts from the UTF-8 string to the UTF-16 string.
 *
 * @param UTF8String The UTF-8 string you want to convert.
 * @return A converted UTF-16 string.
 */
std::wstring M2MakeUTF16String(const std::string& UTF8String);

/**
 * Converts from the UTF-16 string to the UTF-8 string.
 *
 * @param UTF16String The UTF-16 string you want to convert.
 * @return A converted UTF-8 string.
 */
std::string M2MakeUTF8String(const std::wstring& UTF16String);

/**
 * Write formatted data to a string.
 *
 * @param Format Format-control string.
 * @param ... Optional arguments to be formatted.
 * @return A formatted string if successful, "N/A" otherwise.
 */
std::wstring M2FormatString(
    _In_z_ _Printf_format_string_ wchar_t const* const Format,
    ...);

/**
 * Parses a command line string and returns an array of the command line
 * arguments, along with a count of such arguments, in a way that is similar to
 * the standard C run-time.
 *
 * @param CommandLine A string that contains the full command line. If this
 *                    parameter is an empty string the function returns an
 *                    array with only one empty string.
 * @return An array of the command line arguments, along with a count of such
 *         arguments.
 */
std::vector<std::wstring> M2SpiltCommandLine(
    const std::wstring& CommandLine);

/**
 * Parses a command line string and get more friendly result.
 *
 * @param CommandLine A string that contains the full command line. If this
 *                    parameter is an empty string the function returns an
 *                    array with only one empty string.
 * @param OptionPrefixes One or more of the prefixes of option we want to use.
 * @param OptionParameterSeparators One or more of the separators of option we
 *                                  want to use.
 * @param ApplicationName The application name.
 * @param OptionsAndParameters The options and parameters.
 * @param UnresolvedCommandLine The unresolved command line.
 */
void M2SpiltCommandLineEx(
    const std::wstring& CommandLine,
    const std::vector<std::wstring>& OptionPrefixes,
    const std::vector<std::wstring>& OptionParameterSeparators,
    std::wstring& ApplicationName,
    std::map<std::wstring, std::wstring>& OptionsAndParameters,
    std::wstring& UnresolvedCommandLine);

/**
 * Searches a path for a file name.
 *
 * @param Path A pointer to a null-terminated string of maximum length MAX_PATH
 *             that contains the path to search.
 * @return A pointer to the address of the string if successful, or a pointer
 *         to the beginning of the path otherwise.
 */
template<typename CharType>
CharType M2PathFindFileName(CharType Path)
{
    CharType FileName = Path;

    for (size_t i = 0; i < MAX_PATH; ++i)
    {
        if (!(Path && *Path))
            break;

        if (L'\\' == *Path || L'/' == *Path)
            FileName = Path + 1;

        ++Path;
    }

    return FileName;
}

#ifdef CPPWINRT_VERSION

/**
 * Finds a sub string from a source string.
 *
 * @param SourceString The source string.
 * @param SubString The sub string.
 * @param IgnoreCase Determines whether to ignore case.
 * @return Returns true if successful, or false otherwise.
 */
bool M2FindSubString(
    winrt::hstring const& SourceString,
    winrt::hstring const& SubString,
    bool IgnoreCase);

/**
 * Converts a numeric value into a string that represents the number expressed
 * as a size value in byte, bytes, kibibytes, mebibytes, gibibytes, tebibytes,
 * pebibytes or exbibytes, depending on the size.
 *
 * @param ByteSize The numeric byte size value to be converted.
 * @return Returns a winrt::hstring object which represents the converted
 *         string.
 */
winrt::hstring M2ConvertByteSizeToString(
    uint64_t ByteSize);

#endif

#ifdef __cplusplus_winrt

/**
 * Converts from the C++/CX string to the UTF-16 string.
 *
 * @param PlatformString The C++/CX string you want to convert.
 * @return The return value is the UTF-16 string.
 */
std::wstring M2MakeUTF16String(Platform::String^ PlatformString);

/**
 * Converts from the C++/CX string to the UTF-8 string.
 *
 * @param PlatformString The C++/CX string you want to convert.
 * @return The return value is the UTF-8 string.
 */
std::string M2MakeUTF8String(Platform::String^ PlatformString);

/**
 * Converts from the UTF-8 string to the C++/CX string.
 *
 * @param UTF16String The UTF-16 string you want to convert.
 * @return The return value is the C++/CX string.
 */
Platform::String^ M2MakeCXString(const std::wstring& UTF16String);

/**
 * Finds a sub string from a source string.
 *
 * @param SourceString The source string.
 * @param SubString The sub string.
 * @param IgnoreCase Determines whether to ignore case.
 * @return Returns true if successful, or false otherwise.
 */
bool M2FindSubString(
	Platform::String^ SourceString,
	Platform::String^ SubString,
	bool IgnoreCase);

/**
 * Converts a numeric value into a string that represents the number expressed
 * as a size value in byte, bytes, kibibytes, mebibytes, gibibytes, tebibytes,
 * pebibytes or exbibytes, depending on the size.
 *
 * @param ByteSize The numeric byte size value to be converted.
 * @return Returns a Platform::String object which represents the converted
 *         string.
 */
Platform::String^ M2ConvertByteSizeToString(uint64 ByteSize);

#endif

#pragma endregion

#pragma region Performance

/**
 * Retrieves the number of milliseconds that have elapsed since the system was
 * started.
 *
 * @return The number of milliseconds.
 */
ULONGLONG M2GetTickCount();

#pragma endregion

#pragma region Thread

/**
 * Creates a thread to execute within the virtual address space of the calling
 * process.
 *
 * @param lpThreadAttributes A pointer to a SECURITY_ATTRIBUTES structure that
 *                           determines whether the returned handle can be
 *                           inherited by child processes.
 * @param dwStackSize The initial size of the stack, in bytes.
 * @param lpStartAddress A pointer to the application-defined function to be
 *                       executed by the thread.
 * @param lpParameter A pointer to a variable to be passed to the thread.
 * @param dwCreationFlags The flags that control the creation of the thread.
 * @param lpThreadId A pointer to a variable that receives the thread
 *                   identifier.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateThread.
 */
HRESULT M2CreateThread(
    _Out_ PHANDLE lpThreadHandle,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ SIZE_T dwStackSize,
    _In_ LPTHREAD_START_ROUTINE lpStartAddress,
    _In_opt_ __drv_aliasesMem LPVOID lpParameter,
    _In_ DWORD dwCreationFlags,
    _Out_opt_ LPDWORD lpThreadId);

/**
 * Retrieves the number of logical processors in the current group.
 *
 * @return The number of logical processors in the current group.
 */
DWORD M2GetNumberOfHardwareThreads();

namespace M2
{
    /**
     * The implementation of thread.
     */
    class CThread
    {
    private:
        CHandle m_Thread;

    public:
        CThread() = default;

        template<class TFunction>
        CThread(
            _In_ TFunction&& workerFunction,
            _In_ DWORD dwCreationFlags = 0)
        {
            auto ThreadFunctionInternal = [](LPVOID lpThreadParameter) -> DWORD
            {
                auto function = reinterpret_cast<TFunction*>(
                    lpThreadParameter);
                (*function)();
                delete function;
                return 0;
            };

            M2CreateThread(
                &this->m_Thread,
                nullptr,
                0,
                ThreadFunctionInternal,
                reinterpret_cast<LPVOID>(
                    new TFunction(std::move(workerFunction))),
                dwCreationFlags,
                nullptr);
        }

        HANDLE Detach()
        {
            return this->m_Thread.Detach();
        }

        DWORD Resume()
        {
            return ResumeThread(this->m_Thread);
        }

        DWORD Suspend()
        {
            return SuspendThread(this->m_Thread);
        }

        DWORD Wait(
            _In_ DWORD dwMilliseconds = INFINITE,
            _In_ BOOL bAlertable = FALSE)
        {
            return WaitForSingleObjectEx(
                this->m_Thread, dwMilliseconds, bAlertable);
        }

    };

    /**
     * Wraps a critical section.
     */
    class CCriticalSection
    {
    private:
        CRITICAL_SECTION m_CriticalSection;

    public:
        CCriticalSection()
        {
            InitializeCriticalSection(&this->m_CriticalSection);
        }

        ~CCriticalSection()
        {
            DeleteCriticalSection(&this->m_CriticalSection);
        }

        _Acquires_lock_(m_CriticalSection) void Lock()
        {
            EnterCriticalSection(&this->m_CriticalSection);
        }

        _Releases_lock_(m_CriticalSection) void Unlock()
        {
            LeaveCriticalSection(&this->m_CriticalSection);
        }

        _When_(return, _Acquires_exclusive_lock_(m_CriticalSection))
            bool TryLock()
        {
            return TryEnterCriticalSection(&this->m_CriticalSection);
        }
    };

    /**
     * Provides automatic locking and unlocking of a critical section.
     *
     * @remarks The AutoLock object must go out of scope before the CritSec.
     */
    class AutoCriticalSectionLock
    {
    private:
        CCriticalSection* m_pCriticalSection;

    public:
        _Acquires_lock_(m_pCriticalSection) AutoCriticalSectionLock(
            CCriticalSection& CriticalSection) :
            m_pCriticalSection(&CriticalSection)
        {
            m_pCriticalSection->Lock();
        }

        _Releases_lock_(m_pCriticalSection) ~AutoCriticalSectionLock()
        {
            m_pCriticalSection->Unlock();
        }
    };

    /**
     * Provides automatic trying to lock and unlocking of a critical section.
     *
     * @remarks The AutoLock object must go out of scope before the CritSec.
     */
    class AutoTryCriticalSectionLock
    {
    private:
        CCriticalSection* m_pCriticalSection;
        bool m_IsLocked = false;

    public:
        _Acquires_lock_(m_pCriticalSection) AutoTryCriticalSectionLock(
            CCriticalSection& CriticalSection) :
            m_pCriticalSection(&CriticalSection)
        {
            this->m_IsLocked = m_pCriticalSection->TryLock();
        }

        _Releases_lock_(m_pCriticalSection) ~AutoTryCriticalSectionLock()
        {
            m_pCriticalSection->Unlock();
        }

        bool IsLocked() const
        {
            return this->m_IsLocked;
        }
    };

    /**
     * Wraps a slim reader/writer (SRW) lock.
     */
    class CSRWLock
    {
    private:
        SRWLOCK m_SRWLock;

    public:
        CSRWLock()
        {
            InitializeSRWLock(&this->m_SRWLock);
        }

        _Acquires_lock_(m_SRWLock) void ExclusiveLock()
        {
            AcquireSRWLockExclusive(&this->m_SRWLock);
        }

        _Acquires_lock_(m_SRWLock) bool TryExclusiveLock()
        {
            return TryAcquireSRWLockExclusive(&this->m_SRWLock);
        }

        _Releases_lock_(m_SRWLock) void ExclusiveUnlock()
        {
            ReleaseSRWLockExclusive(&this->m_SRWLock);
        }

        _Acquires_lock_(m_SRWLock) void SharedLock()
        {
            AcquireSRWLockShared(&this->m_SRWLock);
        }

        _Acquires_lock_(m_SRWLock) bool TrySharedLock()
        {
            return TryAcquireSRWLockShared(&this->m_SRWLock);
        }

        _Releases_lock_(m_SRWLock) void SharedUnlock()
        {
            ReleaseSRWLockShared(&this->m_SRWLock);
        }
    };

    /**
     * Provides automatic exclusive locking and unlocking of a slim
     * reader/writer (SRW) lock.
     *
     * @remarks The AutoLock object must go out of scope before the CritSec.
     */
    class AutoSRWExclusiveLock
    {
    private:
        CSRWLock* m_SRWLock;

    public:
        _Acquires_lock_(m_SRWLock) AutoSRWExclusiveLock(
            CSRWLock& SRWLock) :
            m_SRWLock(&SRWLock)
        {
            m_SRWLock->ExclusiveLock();
        }

        _Releases_lock_(m_SRWLock) ~AutoSRWExclusiveLock()
        {
            m_SRWLock->ExclusiveUnlock();
        }
    };

    /**
     * Provides automatic trying to exclusive lock and unlocking of a slim
     * reader/writer (SRW) lock.
     *
     * @remarks The AutoLock object must go out of scope before the CritSec.
     */
    class AutoTrySRWExclusiveLock
    {
    private:
        CSRWLock* m_SRWLock;
        bool m_IsLocked = false;

    public:
        _Acquires_lock_(m_SRWLock) AutoTrySRWExclusiveLock(
            CSRWLock& SRWLock) :
            m_SRWLock(&SRWLock)
        {
            this->m_IsLocked = m_SRWLock->TryExclusiveLock();
        }

        _Releases_lock_(m_SRWLock) ~AutoTrySRWExclusiveLock()
        {
            m_SRWLock->ExclusiveUnlock();
        }

        bool IsLocked() const
        {
            return this->m_IsLocked;
        }
    };

    /**
     * Provides automatic shared locking and unlocking of a slim
     * reader/writer (SRW) lock.
     *
     * @remarks The AutoLock object must go out of scope before the CritSec.
     */
    class AutoSRWSharedLock
    {
    private:
        CSRWLock* m_SRWLock;

    public:
        _Acquires_lock_(m_SRWLock) AutoSRWSharedLock(
            CSRWLock& SRWLock) :
            m_SRWLock(&SRWLock)
        {
            m_SRWLock->SharedLock();
        }

        _Releases_lock_(m_SRWLock) ~AutoSRWSharedLock()
        {
            m_SRWLock->SharedUnlock();
        }
    };

    /**
     * Provides automatic trying to shared lock and unlocking of a slim
     * reader/writer (SRW) lock.
     *
     * @remarks The AutoLock object must go out of scope before the CritSec.
     */
    class AutoTrySRWSharedLock
    {
    private:
        CSRWLock* m_SRWLock;
        bool m_IsLocked = false;

    public:
        _Acquires_lock_(m_SRWLock) AutoTrySRWSharedLock(
            CSRWLock& SRWLock) :
            m_SRWLock(&SRWLock)
        {
            this->m_IsLocked = m_SRWLock->TrySharedLock();
        }

        _Releases_lock_(m_SRWLock) ~AutoTrySRWSharedLock()
        {
            m_SRWLock->SharedUnlock();
        }

        bool IsLocked() const
        {
            return this->m_IsLocked;
        }
    };

    /**
     * A template for implementing an object which the type is a singleton. I
     * do not need to free the memory of the object because the OS releases all
     * the unshared memory associated with the process after the process is
     * terminated.
     */
    template<class ClassType>
    class CSingleton : CDisableObjectCopying
    {
    private:
        static CCriticalSection m_SingletonCS;
        static ClassType* volatile m_Instance = nullptr;

    protected:
        CSingleton() = default;
        ~CSingleton() = default;

    public:
        static ClassType* Get()
        {
            M2::AutoCriticalSectionLock Lock(this->m_SingletonCS);

            if (!this->m_Instance)
            {
                this->m_Instance = new ClassType();
            }

            return this->m_Instance;
        }
    };
}

#pragma endregion

#pragma region Memory

/**
 * Allocates a block of memory from a heap. The allocated memory is not
 * movable.
 *
 * @param lpNewMem A pointer to the allocated memory block.
 * @param hHeap A handle to the heap from which the memory will be allocated.
 * @param dwFlags The heap allocation options.
 * @param dwBytes The number of bytes to be allocated.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapAlloc.
 */
HRESULT M2HeapAlloc(
    _Out_ PVOID* lpNewMem,
    _In_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ SIZE_T dwBytes);

/**
 * Reallocates a block of memory from a heap. This function enables you to
 * resize a memory block and change other memory block properties. The
 * allocated memory is not movable.
 *
 * @param lpNewMem A pointer to the allocated memory block.
 * @param hHeap A handle to the heap from which the memory is to be
 *              reallocated.
 * @param dwFlags The heap reallocation options.
 * @param lpMem A pointer to the block of memory that the function reallocates.
 * @param dwBytes The new size of the memory block, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 * @remark For more information, see HeapReAlloc.
 */
HRESULT M2HeapReAlloc(
    _Out_ PVOID* lpNewMem,
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem,
    _In_ SIZE_T dwBytes);

/**
 * Frees a memory block allocated from a heap by the M2HeapAlloc and
 * M2HeapReAlloc function.
 *
 * @param hHeap A handle to the heap whose memory block is to be freed.
 * @param dwFlags The heap free options.
 * @param lpMem A pointer to the memory block to be freed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapFree.
 */
HRESULT M2HeapFree(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem);

/**
 * Allocates a block of memory from the default heap of the calling process.
 * The allocated memory will be initialized to zero. The allocated memory is
 * not movable.
 *
 * @param AllocatedMemoryBlock A pointer to the allocated memory block.
 * @param MemoryBlockSize The number of bytes to be allocated.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2AllocMemory(
    _Out_ PVOID* AllocatedMemoryBlock,
    _In_ SIZE_T MemoryBlockSize);

/**
 * Reallocates a block of memory from the default heap of the calling process.
 * If the reallocation request is for a larger size, the additional region of
 * memory beyond the original size be initialized to zero. This function
 * enables you to resize a memory block and change other memory block
 * properties. The allocated memory is not movable.
 *
 * @param NewAllocatedMemoryBlock A pointer to the allocated memory block.
 * @param OldAllocatedMemoryBlock A pointer to the block of memory that the
 *                                function reallocates. This pointer is
 *                                returned by an earlier call to the
 *                                M2AllocMemory or M2ReAllocMemory function.
 * @param NewMemoryBlockSize The new size of the memory block, in bytes. A
 *                           memory block's size can be increased or decreased
 *                           by using this function.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 */
HRESULT M2ReAllocMemory(
    _Out_ PVOID* NewAllocatedMemoryBlock,
    _In_ PVOID OldAllocatedMemoryBlock,
    _In_ SIZE_T NewMemoryBlockSize);

/**
 * Frees a memory block allocated from a heap by the M2AllocMemory and
 * M2ReAllocMemory function.
 *
 * @param AllocatedMemoryBlock A pointer to the memory block to be freed. This
 * pointer is returned by the M2AllocMemory or M2ReAllocMemory function. If
 * this pointer is nullptr, the behavior is undefined.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2FreeMemory(
    _In_ PVOID AllocatedMemoryBlock);

namespace M2
{
    /**
     * The handle definer for memory block.
     */
#pragma region CMemory

    template<typename TMemory>
    struct CMemoryDefiner
    {
        static inline TMemory GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(TMemory Object)
        {
            free(Object);
        }
    };

    template<typename TMemory>
    class CMemory : public CObject<TMemory, CMemoryDefiner<TMemory>>
    {
    public:
        CMemory(TMemory Object = CMemoryDefiner<TMemory>::GetInvalidValue()) :
            CObject<TMemory, CMemoryDefiner<TMemory>>(Object)
        {

        }

        bool Alloc(size_t Size)
        {
            this->Free();
            this->m_Object = reinterpret_cast<TMemory>(malloc(Size));
            return (nullptr != this->m_Object);
        }

        void Free()
        {
            this->Close();
        }
    };

#pragma endregion

    /**
     * The handle definer for memory block allocated by the M2AllocMemory and
     * M2ReAllocMemory function..
     */
#pragma region CM2Memory

    template<typename TMemory>
    struct CM2MemoryDefiner
    {
        static inline TMemory GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(TMemory Object)
        {
            M2FreeMemory(Object);
        }
    };

    template<typename TMemoryBlock>
    class CM2Memory :
        public CObject<TMemoryBlock, CM2MemoryDefiner<TMemoryBlock>>
    {

    };

#pragma endregion
}

#pragma endregion

#pragma region AccessToken

/**
 * Enables or disables privileges in the specified access token. Enabling or
 * disabling privileges in an access token requires TOKEN_ADJUST_PRIVILEGES
 * access.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token. If the
 *                    PreviousState parameter is not NULL, the handle must also
 *                    have TOKEN_QUERY access.
 * @param DisableAllPrivileges Specifies whether the function disables all of
 *                             the token's privileges. If this value is TRUE,
 *                             the function disables all privileges and ignores
 *                             the NewState parameter. If it is FALSE, the
 *                             function modifies privileges based on the
 *                             information pointed to by the NewState
 *                             parameter.
 * @param NewState A pointer to a TOKEN_PRIVILEGES structure that specifies an
 *                 array of privileges and their attributes. If
 *                 DisableAllPrivileges is TRUE, the function ignores this
 *                 parameter.
 * @param BufferLength Specifies the size, in bytes, of the buffer pointed to
 *                     by the PreviousState parameter. This parameter can be
 *                     zero if the PreviousState parameter is NULL.
 * @param PreviousState A pointer to a buffer that the function fills with a
 *                      TOKEN_PRIVILEGES structure that contains the previous
 *                      state of any privileges that the function modifies.
 *                      This parameter can be NULL.
 * @param ReturnLength A pointer to a variable that receives the required size,
 *                     in bytes, of the buffer pointed to by the PreviousState
 *                     parameter. This parameter can be NULL if PreviousState
 *                     is NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see AdjustTokenPrivileges.
 */
HRESULT M2AdjustTokenPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ BOOL DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ DWORD BufferLength,
    _Out_opt_ PTOKEN_PRIVILEGES PreviousState,
    _Out_opt_ PDWORD ReturnLength);

/**
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the function
 *                              retrieves.
 * @param TokenInformation A pointer to a buffer the function fills with the
 *                         requested information.
 * @param TokenInformationLength Specifies the size, in bytes, of the buffer
 *                               pointed to by the TokenInformation parameter.
 * @param ReturnLength A pointer to a variable that receives the number of
 *                     bytes needed for the buffer pointed to by the
 *                     TokenInformation parameter.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
HRESULT M2GetTokenInformation(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_opt_ LPVOID TokenInformation,
    _In_ DWORD TokenInformationLength,
    _Out_ PDWORD ReturnLength);

/**
 * The source type of access token associated with a process.
 */
typedef enum _M2_PROCESS_ACCESS_TOKEN_SOURCE_TYPE
{
    Current,
    Handle,
    ProcessId
} M2_PROCESS_TOKEN_SOURCE_TYPE, * PM2_PROCESS_TOKEN_SOURCE_TYPE;

/**
 * The source information of access token associated with a process.
 */
typedef struct _M2_PROCESS_ACCESS_TOKEN_SOURCE
{
    M2_PROCESS_TOKEN_SOURCE_TYPE Type;

    // When Type == M2_PROCESS_ACCESS_TOKEN_SOURCE::Handle.
    HANDLE ProcessHandle;

    // When Type == M2_PROCESS_ACCESS_TOKEN_SOURCE::PID.
    DWORD ProcessId;

} M2_PROCESS_ACCESS_TOKEN_SOURCE, * PM2_PROCESS_ACCESS_TOKEN_SOURCE;

/**
 * Opens the access token associated with a process.
 *
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @param TokenSource The source information of access token associated with a
 *                    process.
 * @param DesiredAccess Specifies an access mask that specifies the requested
 *                      types of access to the access token. These requested
 *                      access types are compared with the discretionary access
 *                      control list (DACL) of the token to determine which
 *                      accesses are granted or denied.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2OpenProcessToken(
    _Out_ PHANDLE TokenHandle,
    _In_ PM2_PROCESS_ACCESS_TOKEN_SOURCE TokenSource,
    _In_ DWORD DesiredAccess);

/**
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param OutputInformation A pointer to a buffer the function fills with the
 *                          requested information. When you have finished using
 *                          the information, free it by calling the
 *                          M2FreeMemory function. You should also set the
 *                          pointer to NULL.
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the function
 *                              retrieves.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
HRESULT M2GetTokenInformation(
    _Out_ PVOID* OutputInformation,
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass);

/**
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param OutputInformation A pointer to a buffer the function fills with the
 *                          requested information. When you have finished using
 *                          the information, free it by calling the
 *                          M2FreeMemory function. You should also set the
 *                          pointer to NULL.
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the function
 *                              retrieves.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
template<typename InformationType>
HRESULT M2GetTokenInformation(
    _Out_ InformationType& OutputInformation,
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass)
{
    return M2GetTokenInformation(
        reinterpret_cast<PVOID*>(&OutputInformation),
        TokenHandle,
        TokenInformationClass);
}

#pragma endregion

#pragma region SID
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

namespace M2
{
    /**
     * The handle definer for PSID object.
     */
#pragma region CSID

    struct CSIDDefiner
    {
        static inline PSID GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(PSID Object)
        {
            FreeSid(Object);
        }
    };

    typedef CObject<PSID, CSIDDefiner> CSID;

#pragma endregion
}

#endif
#pragma endregion

#pragma region Session
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

namespace M2
{
    /**
     * The handle definer for memory block allocated via WTS API.
     */
#pragma region CWTSMemory

    template<typename TMemoryBlock>
    struct CWTSMemoryDefiner
    {
        static inline TMemoryBlock GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(TMemoryBlock Object)
        {
            WTSFreeMemory(Object);
        }
    };

    template<typename TMemoryBlock>
    class CWTSMemory :
        public CObject<TMemoryBlock, CWTSMemoryDefiner<TMemoryBlock>>
    {

    };

#pragma endregion
}

#endif
#pragma endregion

#pragma region COM

/**
 * Creates a single uninitialized object of the class associated with a
 * specified CLSID.
 *
 * @param lpszCLSID The string representation of the CLSID.
 * @param pUnkOuter If NULL, indicates that the object is not being created as
 *                  part of an aggregate. If non-NULL, pointer to the aggregate
 *                  object's IUnknown interface (the controlling IUnknown).
 * @param dwClsContext Context in which the code that manages the newly created
 *                     object will run. The values are taken from the
 *                     enumeration CLSCTX.
 * @param lpszIID A pointer to the string representation of the IID.
 * @param ppv Address of pointer variable that receives the interface pointer
 *            requested in riid. Upon successful return, *ppv contains the
 *            requested interface pointer. Upon failure, *ppv contains NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CoCreateInstance.
 */
HRESULT M2CoCreateInstance(
    _In_ LPCWSTR lpszCLSID,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ LPCWSTR lpszIID,
    _Out_ LPVOID* ppv);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Determines whether the interface id have the correct interface name.
 *
 * @param InterfaceID A pointer to the string representation of the IID.
 * @param InterfaceName A pointer to the interface name string.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2CoCheckInterfaceName(
    _In_ LPCWSTR InterfaceID,
    _In_ LPCWSTR InterfaceName);

#endif

#ifdef CPPWINRT_VERSION

/**
 * Creates a GUID, a unique 128-bit integer used for CLSIDs and interface
 * identifiers.
 *
 * @return The function will return GUID struct.
 */
GUID M2CreateGuid();

#endif

#ifdef __cplusplus_winrt

/**
 * Retrieve the IInspectable interface from the provided C++/CX object.
 *
 * @param object The C++/CX object you want to retrieve the raw pointer.
 * @return Return the IInspectable interface from the provided C++/CX object.
 */
inline IInspectable* M2GetInspectable(Platform::Object^ object)
{
	return reinterpret_cast<IInspectable*>(object);
}

/**
 * Retrieves the raw pointer from the provided IBuffer object.
 *
 * @param Buffer The IBuffer object you want to retrieve the raw pointer.
 * @return If the function succeeds, the return value is the raw pointer from
 *         the provided IBuffer object. If the function fails, the return value
 *         is nullptr.
 * @remark The lifetime of the returned buffer is controlled by the lifetime of
 *         the buffer object that's passed to this method. When the buffer has
 *         been released, the pointer becomes invalid and must not be used.
 */
byte* M2GetPointer(Windows::Storage::Streams::IBuffer^ Buffer);

/**
 * Retrieves the IBuffer object from the provided raw pointer.
 *
 * @param Pointer The raw pointer you want to retrieve the IBuffer object.
 * @param Capacity The size of raw pointer you want to retrieve the IBuffer
 *                 object.
 * @return If the function succeeds, the return value is the IBuffer object
 *         from the provided raw pointer. If the function fails, the return
 *         value is nullptr.
 * @remark The lifetime of the returned IBuffer object is controlled by the
 *         lifetime of the raw pointer that's passed to this method. When the
 *         raw pointer has been released, the IBuffer object becomes invalid
 *         and must not be used.
 */
Windows::Storage::Streams::IBuffer^ M2MakeIBuffer(
	byte* Pointer,
	UINT32 Capacity); 

/**
 * Creates a GUID, a unique 128-bit integer used for CLSIDs and interface
 * identifiers.
 *
 * @return The function will return Platform::Guid object.
 */
Platform::Guid M2CreateGuid();

#endif

namespace M2
{
    /**
     * The handle definer for COM object.
     */
#pragma region CComObject

    template<typename TComObject>
    struct CComObjectDefiner
    {
        static inline TComObject GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(TComObject Object)
        {
            Object->Release();
        }
    };

    template<typename TComObject>
    class CComObject : public CObject<TComObject, CComObjectDefiner<TComObject>>
    {

    };

#pragma endregion
}

#pragma endregion

#pragma region File

/**
 * Retrieves file system attributes for a specified file or directory.
 *
 * @param FileHandle A handle to the file that contains the information to be
 *                   retrieved. This handle should not be a pipe handle.
 * @param FileAttributes The attributes of the specified file or directory.
 *                       For a list of attribute values and their descriptions,
 *                       see File Attribute Constants. If the function fails,
 *                       the return value is INVALID_FILE_ATTRIBUTES.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetFileAttributes(
    _In_ HANDLE FileHandle,
    _Out_ PDWORD FileAttributes);

/**
 * Sets the attributes for a file or directory.
 *
 * @param FileHandle A handle to the file for which to change information. This
 *                   handle must be opened with the appropriate permissions for
 *                   the requested change. This handle should not be a pipe
 *                   handle.
 * @param FileAttributes The file attributes to set for the file. This
 *                       parameter can be one or more values, combined using
 *                       the bitwise - OR operator. However, all other values
 *                       override FILE_ATTRIBUTE_NORMAL. For more information,
 *                       see the SetFileAttributes function.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2SetFileAttributes(
    _In_ HANDLE FileHandle,
    _In_ DWORD FileAttributes);

/**
 * Retrieves the size of the specified file.
 *
 * @param FileHandle A handle to the file that contains the information to be
 *                   retrieved. This handle should not be a pipe handle.
 * @param FileSize A pointer to a ULONGLONG value that receives the file size,
 *                 in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             GENERIC_READ | SYNCHRONIZE,
 *             FILE_SHARE_READ,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2GetFileSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG FileSize);

/**
 * Retrieves the amount of space that is allocated for the file.
 *
 * @param FileHandle A handle to the file that contains the information to be
 *                   retrieved. This handle should not be a pipe handle.
 * @param AllocationSize A pointer to a ULONGLONG value that receives the
 *                       amount of space that is allocated for the file, in
 *                       bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             GENERIC_READ | SYNCHRONIZE,
 *             FILE_SHARE_READ,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2GetFileAllocationSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG AllocationSize);

/**
 * Deletes an existing file.
 *
 * @param FileHandle The handle of the file to be deleted.. This handle must be
 *                   opened with the appropriate permissions for the requested
 *                   change. This handle should not be a pipe handle.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             SYNCHRONIZE | DELETE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
 *             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2DeleteFile(
    _In_ HANDLE FileHandle);

/**
 * Deletes an existing file, even the file have the readonly attribute.
 *
 * @param FileHandle The handle of the file to be deleted.. This handle must be
 *                   opened with the appropriate permissions for the requested
 *                   change. This handle should not be a pipe handle.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             SYNCHRONIZE | DELETE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
 *             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2DeleteFileIgnoreReadonlyAttribute(
    _In_ HANDLE FileHandle);

#pragma endregion

#pragma region Module

/**
 * Retrieves the address of an exported function or variable from the specified
 * dynamic-link library (DLL).
 *
 * @param lpProcAddress The address of the exported function or variable.
 * @param hModule A handle to the DLL module that contains the function or
 *                variable. The LoadLibrary, LoadLibraryEx, LoadPackagedLibrary
 *                or GetModuleHandle function returns this handle. This
 *                function does not retrieve addresses from modules that were
 *                loaded using the LOAD_LIBRARY_AS_DATAFILE flag. For more
 *                information, see LoadLibraryEx.
 * @param lpProcName The function or variable name, or the function's ordinal
 *                   value. If this parameter is an ordinal value, it must be
 *                   in the low-order word; the high-order word must be zero.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetProcAddress(
    _Out_ FARPROC* lpProcAddress,
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName);

/**
 * Retrieves the address of an exported function or variable from the specified
 * dynamic-link library (DLL).
 *
 * @param lpProcAddress The address of the exported function or variable.
 * @param hModule A handle to the DLL module that contains the function or
 *                variable. The LoadLibrary, LoadLibraryEx, LoadPackagedLibrary
 *                or GetModuleHandle function returns this handle. This
 *                function does not retrieve addresses from modules that were
 *                loaded using the LOAD_LIBRARY_AS_DATAFILE flag. For more
 *                information, see LoadLibraryEx.
 * @param lpProcName The function or variable name, or the function's ordinal
 *                   value. If this parameter is an ordinal value, it must be
 *                   in the low-order word; the high-order word must be zero.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
template<typename ProcedureType>
inline HRESULT M2GetProcAddress(
    _Out_ ProcedureType& lpProcAddress,
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName)
{
    return M2GetProcAddress(
        reinterpret_cast<FARPROC*>(&lpProcAddress), hModule, lpProcName);
}

/**
 * Retrieves the path of the executable file of the current process.
 *
 * @return If the function succeeds, the return value is the path of the
 *         executable file of the current process. If the function fails, the
 *         return value is an empty string.
 */
std::wstring M2GetCurrentProcessModulePath();

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Loads the specified module with the optimization of the mitigation of DLL
 * preloading attacks into the address space of the calling process safely. The
 * specified module may cause other modules to be loaded.
 *
 * @param phLibModule A handle to the loaded module.
 * @param lpLibFileName A string that specifies the file name of the module to
 *                      load.
 * @param hFile This parameter is reserved for future use. It must be NULL.
 * @param dwFlags The action to be taken when loading the module.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see LoadLibraryEx.
 */
HRESULT M2LoadLibrary(
    _Out_ HMODULE* phLibModule,
    _In_ LPCWSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags);

/**
 * The resource info struct.
 */
typedef struct _M2_RESOURCE_INFO
{
    DWORD Size;
    LPVOID Pointer;
} M2_RESOURCE_INFO, * PM2_RESOURCE_INFO;

/**
 * Obtain the best matching resource with the specified type and name in the
 * specified module.
 *
 * @param lpResourceInfo The resource info which contains the pointer and size.
 * @param hModule A handle to the module whose portable executable file or an
 *                accompanying MUI file contains the resource. If this
 *                parameter is NULL, the function searches the module used to
 *                create the current process.
 * @param lpType The resource type. Alternately, rather than a pointer, this
 *               parameter can be MAKEINTRESOURCE(ID), where ID is the integer
 *               identifier of the given resource type.
 * @param lpName The name of the resource. Alternately, rather than a pointer,
 *               this parameter can be MAKEINTRESOURCE(ID), where ID is the
 *               integer identifier of the resource.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2LoadResource(
    _Out_ PM2_RESOURCE_INFO lpResourceInfo,
    _In_opt_ HMODULE hModule,
    _In_ LPCWSTR lpType,
    _In_ LPCWSTR lpName);

/**
 * Loads the specified module with the optimization of the mitigation of DLL
 * preloading attacks into the address space of the calling process safely. The
 * specified module may cause other modules to be loaded.
 *
 * @param ModuleHandle If the function succeeds, this parameter's value is a
 *                     handle to the loaded module. You should read the
 *                     documentation about LoadLibraryEx API for further
 *                     information.
 * @param LibraryFileName A string that specifies the file name of the module
 *                        to load. You should read the documentation about
 *                        LoadLibraryEx API for further information.
 * @param Flags The action to be taken when loading the module. You should read
 *              the documentation about LoadLibraryEx API for further
 *              information.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2LoadLibraryEx(
    _Out_ HMODULE* ModuleHandle,
    _In_ LPCWSTR LibraryFileName,
    _In_ DWORD Flags);

#endif

#pragma endregion

#pragma region Registry
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates the specified registry key. If the key already exists, the function
 * opens it. Note that key names are not case sensitive.
 *
 * @param hKey A handle to an open registry key.
 * @param lpSubKey The name of a subkey that this function opens or creates
 * @param Reserved This parameter is reserved and must be zero.
 * @param lpClass The user-defined class type of this key.
 * @param dwOptions This parameter can be one of the following values:
 *                  REG_OPTION_BACKUP_RESTORE, REG_OPTION_CREATE_LINK,
 *                  REG_OPTION_NON_VOLATILE, REG_OPTION_VOLATILE.
 * @param samDesired A mask that specifies the access rights for the key to be
 *                   created.
 * @param lpSecurityAttributes A pointer to a SECURITY_ATTRIBUTES structure
 *                             that determines whether the returned handle can
 *                             be inherited by child processes.
 * @param phkResult A pointer to a variable that receives a handle to the
 *                  opened or created key.
 * @param lpdwDisposition A pointer to a variable that receives one of the
 *                        following disposition values.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegCreateKeyEx.
 */
HRESULT M2RegCreateKey(
    _In_ HKEY hKey,
    _In_ LPCWSTR lpSubKey,
    _Reserved_ DWORD Reserved,
    _In_opt_ LPWSTR lpClass,
    _In_ DWORD dwOptions,
    _In_ REGSAM samDesired,
    _In_opt_ CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _Out_ PHKEY phkResult,
    _Out_opt_ LPDWORD lpdwDisposition);

/**
 * Retrieves the type and data for the specified value name associated with an
 * open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the registry value.
 * @param lpReserved This parameter is reserved and must be NULL.
 * @param lpType A pointer to a variable that receives a code indicating the
 *              type of data stored in the specified value.
 * @param lpData A pointer to a buffer that receives the value's data.
 * @param lpcbData A pointer to a variable that specifies the size of the
 *                 buffer pointed to by the lpData parameter, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegQueryValueEx.
 */
HRESULT M2RegQueryValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ LPDWORD lpReserved,
    _Out_opt_ LPDWORD lpType,
    _Out_opt_ LPBYTE lpData,
    _Inout_opt_ LPDWORD lpcbData);

/**
 * Retrieves the type and data for the specified value name associated with an
 * open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the value to be set.
 * @param Reserved This parameter is reserved and must be zero.
 * @param dwType The type of data pointed to by the lpData parameter.
 * @param lpData The data to be stored.
 * @param cbData The size of the information pointed to by the lpData
 *               parameter, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegSetValueEx.
 */
HRESULT M2RegSetValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ DWORD Reserved,
    _In_ DWORD dwType,
    _In_opt_ CONST BYTE* lpData,
    _In_ DWORD cbData);

/**
 * Retrieves the string type data for the specified value name associated with
 * an open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the registry value.
 * @param lpData A pointer to a buffer that receives the value's data. When you
 *               have finished using the information, free it by calling the
 *               M2FreeMemory function. You should also set the pointer to
 *               NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegQueryValueEx.
 */
HRESULT M2RegQueryStringValue(
    _Out_ LPWSTR* lpData,
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName);

namespace M2
{
    /**
 * The handle definer for HKEY object.
 */
#pragma region CHKey

    struct CHKeyDefiner
    {
        static inline HKEY GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(HKEY Object)
        {
            RegCloseKey(Object);
        }
    };

    typedef CObject<HKEY, CHKeyDefiner> CHKey;

#pragma endregion
}

#endif
#pragma endregion

#pragma region Service
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Starts a service if not started and retrieves the current status of the
 * specified service.
 *
 * @param lpServiceName The name of the service to be started. This is the name
 *                      specified by the lpServiceName parameter of the
 *                      CreateService function when the service object was
 *                      created, not the service display name that is shown by
 *                      user interface applications to identify the service.
 *                      The maximum string length is 256 characters. The
 *                      service control manager database preserves the case of
 *                      the characters, but service name comparisons are always
 *                      case insensitive. Forward-slash (/) and backslash ()
 *                      are invalid service name characters.
 * @param lpServiceStatus Contains process status information for a service.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2StartService(
    _In_ LPCWSTR lpServiceName,
    _Out_ LPSERVICE_STATUS_PROCESS lpServiceStatus);

namespace M2
{
    /**
     * The handle definer for SC_HANDLE object.
     */
#pragma region CServiceHandle

    struct CServiceHandleDefiner
    {
        static inline SC_HANDLE GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(SC_HANDLE Object)
        {
            CloseServiceHandle(Object);
        }
    };

    typedef CObject<SC_HANDLE, CServiceHandleDefiner> CServiceHandle;

#pragma endregion
}

#endif
#pragma endregion

#pragma region Environment

/**
 * Expands environment-variable strings and replaces them with the values
 * defined for the current user.
 *
 * @param ExpandedString The expanded string.
 * @param VariableName The environment-variable string you need to expand.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2ExpandEnvironmentStrings(
    std::wstring& ExpandedString,
    const std::wstring& VariableName);

/**
 * Retrieves the path of the system directory.
 *
 * @param SystemFolderPath The string of the path of the system directory.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetSystemDirectory(
    std::wstring& SystemFolderPath);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Retrieves the path of the shared Windows directory on a multi-user system.
 *
 * @param WindowsFolderPath The string of the path of the shared Windows
 *                          directory on a multi-user system.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetWindowsDirectory(
    std::wstring& WindowsFolderPath);

/**
 * Enables the Per-Monitor DPI Aware for the specified dialog using the
 * internal API from Windows.
 *
 * @return INT. If failed. returns -1.
 * @remarks You need to use this function in Windows 10 Threshold 1 or Windows
 *          10 Threshold 2.
 */
INT M2EnablePerMonitorDialogScaling();

/**
 * Queries the dots per inch (dpi) of a display.
 *
 * @param hmonitor Handle of the monitor being queried.
 * @param dpiType The type of DPI being queried. Possible values are from the
 *                MONITOR_DPI_TYPE enumeration.
 * @param dpiX The value of the DPI along the X axis. This value always refers
 *             to the horizontal edge, even when the screen is rotated.
 * @param dpiY The value of the DPI along the Y axis. This value always refers
 *             to the vertical edge, even when the screen is rotated.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetDpiForMonitor(
    _In_ HMONITOR hmonitor,
    _In_ MONITOR_DPI_TYPE dpiType,
    _Out_ UINT* dpiX,
    _Out_ UINT* dpiY);

#endif

#pragma endregion

#pragma region WinRT

#ifdef CPPWINRT_VERSION

namespace winrt
{
    using Windows::Foundation::IAsyncAction;
    using Windows::Foundation::IInspectable;
    using Windows::Foundation::Collections::IIterable;
    using Windows::Foundation::Collections::IIterator;
    using Windows::Foundation::Collections::IVectorView;
    using Windows::UI::Core::DispatchedHandler;
    using Windows::UI::Xaml::Data::INotifyPropertyChanged;
    using Windows::UI::Xaml::Data::PropertyChangedEventArgs;
    using Windows::UI::Xaml::Data::PropertyChangedEventHandler;
    using Windows::UI::Xaml::Interop::IBindableIterable;
    using Windows::UI::Xaml::Interop::IBindableIterator;
    using Windows::UI::Xaml::Interop::IBindableVectorView;
}

/**
 * Execute function on the UI thread with normal priority.
 *
 * @param agileCallback The function you want to execute.
 * @return The return value is Windows::Foundation::IAsyncAction^.
 */
winrt::IAsyncAction M2ExecuteOnUIThread(
    winrt::DispatchedHandler const& agileCallback);

namespace M2
{
    struct NotifyPropertyChangedBase : winrt::implements<
        NotifyPropertyChangedBase, winrt::INotifyPropertyChanged>
    {
    private:
        winrt::event<winrt::PropertyChangedEventHandler> m_PropertyChanged;

    protected:
        void RaisePropertyChanged(
            std::wstring_view const& PropertyName);

    public:
        NotifyPropertyChangedBase() = default;

        winrt::event_token PropertyChanged(
            winrt::PropertyChangedEventHandler const& value);

        void PropertyChanged(
            winrt::event_token const& token);
    };

    template <typename Type>
    struct BindableVectorView : winrt::implements<
        BindableVectorView<Type>,
        winrt::IVectorView<Type>,
        winrt::IIterable<Type>,
        winrt::IBindableVectorView,
        winrt::IBindableIterable>
    {
    private:
        std::vector<Type> m_values;

        class WinRTObject
        {
        private:
            Type m_value;

        public:
            WinRTObject(Type value) :
                m_value(value)
            {

            }

            operator Type()
            {
                return this->m_value;
            }

            operator winrt::IInspectable()
            {
                return winrt::box_value(this->m_value);
            }
        };

        struct iterator : winrt::implements<
            iterator,
            winrt::IIterator<Type>,
            winrt::IBindableIterator>
        {
        private:
            winrt::com_ptr<BindableVectorView<Type>> m_owner;
            typename std::vector<Type>::const_iterator m_current;
            typename std::vector<Type>::const_iterator const m_end;

        public:
            explicit iterator(BindableVectorView<Type>* owner) noexcept :
                m_current(owner->m_values.begin()),
                m_end(owner->m_values.end())
            {
                m_owner.copy_from(owner);
            }

            WinRTObject Current() const
            {
                if (m_current == m_end)
                {
                    throw winrt::hresult_out_of_bounds();
                }

                return WinRTObject(*m_current);
            }

            bool HasCurrent() const noexcept
            {
                return m_current != m_end;
            }

            bool MoveNext() noexcept
            {
                if (m_current != m_end)
                {
                    ++m_current;
                }

                return HasCurrent();
            }

            uint32_t GetMany(winrt::array_view<Type> values)
            {
                uint32_t actual = static_cast<uint32_t>(std::distance(m_current, m_end));

                if (actual > values.size())
                {
                    actual = values.size();
                }

                std::copy_n(m_current, actual, values.begin());
                std::advance(m_current, actual);
                return actual;
            }
        };

    public:
        explicit BindableVectorView(std::vector<Type>& values) :
            m_values(values)
        {
        }

        uint32_t Size() const noexcept
        {
            return static_cast<uint32_t>(m_values.size());
        }

        WinRTObject GetAt(uint32_t const index) const
        {
            if (index >= m_values.size())
            {
                throw winrt::hresult_out_of_bounds();
            }

            return WinRTObject(m_values[index]);
        }

        uint32_t GetMany(
            uint32_t const startIndex,
            winrt::array_view<Type> values) const
        {
            if (startIndex >= m_values.size())
            {
                return 0;
            }

            uint32_t actual = static_cast<uint32_t>(
                m_values.size() - startIndex);

            if (actual > values.size())
            {
                actual = values.size();
            }

            std::copy_n(m_values.begin() + startIndex, actual, values.begin());
            return actual;
        }

        bool IndexOf(Type const& value, uint32_t& index) const noexcept
        {
            index = static_cast<uint32_t>(std::find(
                m_values.begin(), m_values.end(), value) - m_values.begin());
            return index < m_values.size();
        }


        class IIteratorCreator
        {
        private:
            BindableVectorView<Type>* m_owner;

        public:
            IIteratorCreator(BindableVectorView<Type>* owner) :
                m_owner(owner)
            {

            }

            operator winrt::IIterator<Type>()
            {
                return winrt::make<iterator>(this->m_owner);
            }

            operator winrt::IBindableIterator()
            {
                return winrt::make<iterator>(this->m_owner).try_as<
                    winrt::IBindableIterator>();
            }
        };

        IIteratorCreator First()
        {
            return IIteratorCreator(this);
        }

        bool IndexOf(
            winrt::IInspectable const& value,
            uint32_t & index) const
        {
            return this->IndexOf(winrt::unbox_value<Type>(value), index);
        }
    };
}

#endif

#ifdef __cplusplus_winrt

/**
 * Set the completed handler function for asynchronous call.
 *
 * @param Async The asynchronous call you want to set.
 * @param Function The completed handler function you want to set.
 */
template<typename TAsync, typename... TFunction>
inline void M2AsyncSetCompletedHandler(
	TAsync Async, const TFunction& ... Function)
{
	Async->Completed =
		ref new typename M2RemoveReference<decltype(Async->Completed)>::Type(
			Function...);
}

/**
 * Set the progress handler function for asynchronous call.
 *
 * @param Async The asynchronous call you want to set.
 * @param Function The progress handler function you want to set.
 */
template<typename TAsync, typename... TFunction>
inline void M2AsyncSetProgressHandler(
	TAsync Async, const TFunction& ... Function)
{
	Async->Progress =
		ref new typename M2RemoveReference<decltype(Async->Progress)>::Type(
			Function...);
}

/**
 * Try to wait asynchronous call.
 *
 * @param Async The asynchronous call you want to wait.
 * @param Timeout The maximum time interval for waiting the asynchronous call,
 *                in milliseconds. A value of -1 indicates that the suspension
 *                should not time out.
 * @return The return value is determined by the asynchronous call. The
 *         function will throw a COM exception if the function fails.
 */
template<typename TAsync>
auto M2AsyncWait(
	TAsync Async, int32 Timeout = -1) -> decltype(Async->GetResults())
{
	HRESULT M2AsyncHandleCompleted(Platform::Object ^ Async);

	using M2::CHandle;
	using Platform::COMException;
	using Windows::Foundation::AsyncStatus;
	using Windows::Foundation::IAsyncInfo;

	HRESULT hr = S_OK;

	// Create an event object for wait the asynchronous call.
	CHandle CompletedEvent(
		CreateEventExW(nullptr, nullptr, 0, EVENT_ALL_ACCESS));
	if (!CompletedEvent.IsInvalid())
	{
		// Set the completed handler.
		M2AsyncSetCompletedHandler(
			Async, [&](IAsyncInfo^ /*asyncInfo*/, AsyncStatus /*asyncStatus*/)
			{
				// Set event signaled to end wait when completed.
				SetEvent(CompletedEvent);
			});

		// Wait event object signaled.
		WaitForSingleObjectEx(CompletedEvent, Timeout, FALSE);

		// Handle the completed asynchronous call.
		hr = M2AsyncHandleCompleted(Async);
	}
	else
	{
		// Get error code if failed to create an event object.
		hr = M2GetLastError();
	}

	// Throw a COM exception if failed.
	M2ThrowPlatformExceptionIfFailed(hr);

	// Return the result of asynchronous call.
	return Async->GetResults();
}

/**
 * Execute function on the UI thread with normal priority.
 *
 * @param Function The function you want to execute.
 * @return The return value is Windows::Foundation::IAsyncAction^.
 */
template<typename... TFunction>
inline Windows::Foundation::IAsyncAction^ M2ExecuteOnUIThread(
	const TFunction& ... Function)
{
	Windows::Foundation::IAsyncAction^ M2ExecuteOnUIThread(
		Windows::UI::Core::DispatchedHandler ^ agileCallback);

	return M2ExecuteOnUIThread(
		ref new Windows::UI::Core::DispatchedHandler(Function...));
}

/**
 * Async Controller Interface
 */
#pragma region M2AsyncCreateInterface

interface class IM2AsyncController
{
	void CancelCurrentTask();

	bool IsTaskCancellationRequested();
};

template<typename ProgressType>
interface class IM2AsyncControllerEx : IM2AsyncController
{
	void ReportProgress(const typename ProgressType& ProgressValue);
};

#pragma endregion

/**
 *  Implementions for M2AsyncCreate function.
 */
namespace M2AsyncCreateInternal
{
	ref class M2EmptyRefClass
	{
	};

	template<typename TProgress, typename TReturn, bool NeedProgressHandler>
	struct M2AsyncType
	{
	};

	using Windows::Foundation::IAsyncOperationWithProgress;
	using Windows::Foundation::AsyncOperationProgressHandler;
	using Windows::Foundation::AsyncOperationWithProgressCompletedHandler;

	template<typename TProgress, typename TReturn>
	struct M2AsyncType<TProgress, TReturn, true>
	{
		using BaseType = IAsyncOperationWithProgress<TReturn, TProgress>;
		using ProgressHandlerType =
			AsyncOperationProgressHandler<TReturn, TProgress>;
		using CompletedHandlerType =
			AsyncOperationWithProgressCompletedHandler<TReturn, TProgress>;

		using ReturnType = TReturn;
		using ProgressType = TProgress;

		static const bool NeedProgressHandler = true;
	};

	using Windows::Foundation::IAsyncOperation;
	using Windows::Foundation::AsyncOperationCompletedHandler;

	template<typename TProgress, typename TReturn>
	struct M2AsyncType<TProgress, TReturn, false>
	{
		using BaseType = IAsyncOperation<TReturn>;
		using ProgressHandlerType = M2EmptyRefClass;
		using CompletedHandlerType = AsyncOperationCompletedHandler<TReturn>;

		using ReturnType = TReturn;
		using ProgressType = TProgress;

		static const bool NeedProgressHandler = false;
	};

	using Windows::Foundation::IAsyncActionWithProgress;
	using Windows::Foundation::AsyncActionProgressHandler;
	using Windows::Foundation::AsyncActionWithProgressCompletedHandler;

	template<typename TProgress>
	struct M2AsyncType<TProgress, void, true>
	{
		using BaseType = IAsyncActionWithProgress<TProgress>;
		using ProgressHandlerType = AsyncActionProgressHandler<TProgress>;
		using CompletedHandlerType =
			AsyncActionWithProgressCompletedHandler<TProgress>;

		using ReturnType = void;
		using ProgressType = TProgress;

		static const bool NeedProgressHandler = true;
	};

	using Windows::Foundation::IAsyncAction;
	using Windows::Foundation::AsyncActionCompletedHandler;

	template<typename TProgress>
	struct M2AsyncType<TProgress, void, false>
	{
		using BaseType = IAsyncAction;
		using ProgressHandlerType = M2EmptyRefClass;
		using CompletedHandlerType = AsyncActionCompletedHandler;

		using ReturnType = void;
		using ProgressType = TProgress;

		static const bool NeedProgressHandler = false;
	};

	enum M2AsyncStatusInternal
	{
		// Client visible states. (Must match AsyncStatus exactly)
		Started = Windows::Foundation::AsyncStatus::Started,
		Completed = Windows::Foundation::AsyncStatus::Completed,
		Canceled = Windows::Foundation::AsyncStatus::Canceled,
		Error = Windows::Foundation::AsyncStatus::Error,

		// Non-client visible internal states.
		Created,
		CancelPending,
		Closed,
		Undefined,
	};

	// This class describes an exception thrown by the M2AsyncGenerator in 
	// order to force the current task to cancel.
	class M2AsyncTaskCanceledException : public std::exception
	{
	public:
		explicit M2AsyncTaskCanceledException(
			_In_z_ const char* _Message) noexcept
			: std::exception(_Message)
		{}

		M2AsyncTaskCanceledException() noexcept
			: exception()
		{}
	};

	// Internal base class implementation for async operations (based on 
	// internal Windows representation for ABI level async operations)
	template<typename AsyncType>
	ref class M2AsyncBase abstract : AsyncType::BaseType, IM2AsyncController
	{
	internal:
		HRESULT volatile m_ErrorCode;
		uint32 volatile m_Id;
		M2AsyncStatusInternal volatile m_Status;
		typename AsyncType::CompletedHandlerType^ volatile m_CompletedHandler;
		long volatile m_CompletedHandlerAssigned;
		long volatile m_CallbackMade;

		// This method is used to check if calls to the AsyncInfo properties
		// (id, status, errorcode) are legal in the current state. It also
		// generates the appropriate error hr to return in the case of an
		// illegal call.
		inline void CheckValidStateForAsyncCall()
		{
			M2AsyncStatusInternal Current = this->m_Status;

			if (Current == M2AsyncStatusInternal::Closed)
			{
				M2ThrowPlatformException(E_ILLEGAL_METHOD_CALL);
			}
			else if (Current == M2AsyncStatusInternal::Created)
			{
				M2ThrowPlatformException(E_ASYNC_OPERATION_NOT_STARTED);
			}
		}

		// This method checks to see if the delegate properties can be
		// modified in the current state and generates the appropriate
		// error hr in the case of violation.
		inline void CheckValidStateForDelegateCall()
		{
			if (this->m_Status == M2AsyncStatusInternal::Closed)
			{
				M2ThrowPlatformException(E_ILLEGAL_METHOD_CALL);
			}
		}

		// This method checks to see if results can be collected in the
		// current state and generates the appropriate error hr in
		// the case of a violation.
		inline void CheckValidStateForResultsCall()
		{
			M2AsyncStatusInternal Current = this->m_Status;

			if (Current == M2AsyncStatusInternal::Error)
			{
				M2ThrowPlatformException(this->m_ErrorCode);
			}

			// Illegal before transition to Completed or Cancelled state
			if (Current != M2AsyncStatusInternal::Completed)
			{
				M2ThrowPlatformException(E_ILLEGAL_METHOD_CALL);
			}
		}

		inline bool IsTerminalState(M2AsyncStatusInternal status)
		{
			return (status == M2AsyncStatusInternal::Error ||
				status == M2AsyncStatusInternal::Canceled ||
				status == M2AsyncStatusInternal::Completed ||
				status == M2AsyncStatusInternal::Closed);
		}

		inline bool IsTerminalState()
		{
			return this->IsTerminalState(this->m_Status);
		}

		inline bool TransitionToState(const M2AsyncStatusInternal NewState)
		{
			M2AsyncStatusInternal Current = this->m_Status;

			// This enforces the valid state transitions of the asynchronous 
			// worker object state machine.
			switch (NewState)
			{
			case M2AsyncStatusInternal::Started:
				if (Current != M2AsyncStatusInternal::Created)
				{
					return false;
				}
				break;
			case M2AsyncStatusInternal::CancelPending:
				if (Current != M2AsyncStatusInternal::Started)
				{
					return false;
				}
				break;

			case M2AsyncStatusInternal::Closed:
				if (!this->IsTerminalState(Current))
				{
					return false;
				}
				break;
			case M2AsyncStatusInternal::Completed:
			case M2AsyncStatusInternal::Canceled:
			case M2AsyncStatusInternal::Error:
				if (Current != M2AsyncStatusInternal::Started &&
					Current != M2AsyncStatusInternal::CancelPending)
				{
					return false;
				}
				break;
			default:
				return false;
				break;
			}

			// attempt the transition to the new state
			// Note: if m_Status == Current, then there was no intervening 
			// write by the async work object and the swap succeeded.
			M2AsyncStatusInternal RetState =
				static_cast<M2AsyncStatusInternal>(_InterlockedCompareExchange(
					reinterpret_cast<volatile LONG*>(&this->m_Status),
					NewState,
					static_cast<LONG>(Current)));

			// ICE returns the former state, if the returned state and the
			// state we captured at the beginning of this method are the same,
			// the swap succeeded.
			return (RetState == Current);
		}

		bool TryTransitionToCompleted()
		{
			return this->TransitionToState(M2AsyncStatusInternal::Completed);
		}

		bool TryTransitionToCancelled()
		{
			return this->TransitionToState(M2AsyncStatusInternal::Canceled);
		}

		bool TryTransitionToError(const HRESULT error)
		{
			_InterlockedCompareExchange(
				reinterpret_cast<volatile LONG*>(&this->m_ErrorCode),
				error,
				S_OK);
			return this->TransitionToState(M2AsyncStatusInternal::Error);
		}

		// This method can be called by derived classes periodically to 
		// determine whether the asynchronous operation should continue 
		// processing or should be halted.
		inline bool ContinueAsyncOperation()
		{
			return (this->m_Status == M2AsyncStatusInternal::Started);
		}

		// Start - this is not externally visible since async operations "hot 
		// start" before returning to the caller.
		void Start()
		{
			if (this->TransitionToState(M2AsyncStatusInternal::Started))
			{
				this->OnStart();
			}
			else
			{
				M2ThrowPlatformException(E_ILLEGAL_STATE_CHANGE);
			}
		}

		void FireCompletion()
		{
			this->TryTransitionToCompleted();

			// we guarantee that completion can only ever be fired once
			if (this->m_CompletedHandler != nullptr &&
				InterlockedIncrement(&this->m_CallbackMade) == 1)
			{
				try
				{
					this->m_CompletedHandler(
						(typename AsyncType::BaseType^)this, this->Status);
					this->m_CompletedHandler = nullptr;
				}
				catch (...)
				{
					// Null out the delegate since something went wrong when 
					// calling it.
					this->m_CompletedHandler = nullptr;
					throw;
				}
			}
		}

		// These three methods are used to allow the async worker 
		// implementation do work on state transitions. No real "work" should 
		// be done in these methods. In other words they should not block for a
		// long time on UI timescales.
		virtual void OnStart() = 0;
		virtual void OnClose() = 0;
		virtual void OnCancel() = 0;

		virtual typename AsyncType::ProgressHandlerType^ GetOnProgress()
		{
			M2ThrowPlatformException(E_UNEXPECTED);
		}

		virtual void PutOnProgress(
			typename AsyncType::ProgressHandlerType ^ ProgressHandler)
		{
			M2ThrowPlatformException(E_UNEXPECTED);
		}

		virtual void PutOnId(uint32 Id)
		{
			this->CheckValidStateForAsyncCall();

			if (Id == 0)
			{
				M2ThrowPlatformException(E_INVALIDARG);
			}
			else if (this->m_Status != M2AsyncStatusInternal::Created)
			{
				M2ThrowPlatformException(E_ILLEGAL_METHOD_CALL);
			}

			this->m_Id = Id;
		}

		M2AsyncBase() :
			m_ErrorCode(S_OK),
			m_Id(1),
			m_Status(M2AsyncStatusInternal::Created),
			m_CompletedHandler(nullptr),
			m_CompletedHandlerAssigned(0),
			m_CallbackMade(0)
		{

		}

	public:
		virtual property Windows::Foundation::HResult ErrorCode
		{
			Windows::Foundation::HResult get()
			{
				this->CheckValidStateForAsyncCall();

				Windows::Foundation::HResult HR;
				HR.Value = this->m_ErrorCode;
				return HR;
			}
		}

		virtual property uint32 Id
		{
			uint32 get()
			{
				this->CheckValidStateForAsyncCall();

				return this->m_Id;
			}
		}

		virtual property Windows::Foundation::AsyncStatus Status
		{
			Windows::Foundation::AsyncStatus get()
			{
				this->CheckValidStateForAsyncCall();

				M2AsyncStatusInternal Current = this->m_Status;

				// Map our internal cancel pending to cancelled. This way 
				// "pending cancelled" looks to the outside as "cancelled" but 
				// can still transition to "completed" if the operation 
				// completes without acknowledging the cancellation request.
				switch (Current)
				{
				case M2AsyncStatusInternal::CancelPending:
					Current = M2AsyncStatusInternal::Canceled;
					break;
				case M2AsyncStatusInternal::Created:
					Current = M2AsyncStatusInternal::Started;
					break;
				default:
					break;
				}

				return static_cast<Windows::Foundation::AsyncStatus>(Current);
			}
		}

		virtual void Cancel()
		{
			if (this->TransitionToState(M2AsyncStatusInternal::CancelPending))
			{
				this->OnCancel();
			}
		}

		virtual void Close()
		{
			if (this->TransitionToState(M2AsyncStatusInternal::Closed))
			{
				this->OnClose();
			}
			else
			{
				// Closed => Closed transition is just ignored
				if (this->m_Status != M2AsyncStatusInternal::Closed)
				{
					M2ThrowPlatformException(E_ILLEGAL_STATE_CHANGE);
				}
			}
		}

		virtual property typename AsyncType::CompletedHandlerType^ Completed
		{
			typename typename AsyncType::CompletedHandlerType^ get()
			{
				this->CheckValidStateForDelegateCall();
				return this->m_CompletedHandler;
			}

			void set(
				typename AsyncType::CompletedHandlerType^ CompletedHandler)
			{
				this->CheckValidStateForDelegateCall();

				// this delegate property is "write once"
				if (InterlockedIncrement(
					&this->m_CompletedHandlerAssigned) == 1)
				{
					this->m_CompletedHandler = CompletedHandler;
					// Guarantee that the write of m_CompletedHandler is 
					// ordered with respect to the read of state below as 
					// perceived from FireCompletion on another thread.
					MemoryBarrier();
					if (this->IsTerminalState())
					{
						this->FireCompletion();
					}
				}
				else
				{
					M2ThrowPlatformException(E_ILLEGAL_DELEGATE_ASSIGNMENT);
				}
			}
		}

		virtual property typename AsyncType::ProgressHandlerType^ Progress
		{
			typename typename AsyncType::ProgressHandlerType^ get()
			{
				return this->GetOnProgress();
			}

			void set(typename AsyncType::ProgressHandlerType^ _ProgressHandler)
			{
				this->PutOnProgress(_ProgressHandler);
			}
		}

		virtual typename AsyncType::ReturnType GetResults()
		{
			M2ThrowPlatformException(E_UNEXPECTED);
		}

		virtual void CancelCurrentTask()
		{
			throw M2AsyncTaskCanceledException();
		}

		virtual bool IsTaskCancellationRequested()
		{
			return (this->m_Status == M2AsyncStatusInternal::CancelPending);
		}
	};

	// __declspec(no_empty_identity_interface) is used to suppress generation 
	// of WinRT default functions (e.g. QueryInterface, AddRef, etc). 
	// M2AsyncProgressBase is never used directly, so generation of WinRT 
	// functions is not needed and unnecessarily increases generated code size.

	template<typename AsyncType, bool NeedProgressHandler>
	ref class __declspec(no_empty_identity_interface)
		M2AsyncProgressBase abstract :
	M2AsyncBase<AsyncType>
	{
	};

	template<typename AsyncType>
	ref class __declspec(no_empty_identity_interface)
		M2AsyncProgressBase<AsyncType, true> abstract :
		M2AsyncBase<AsyncType>,
		IM2AsyncControllerEx<typename AsyncType::ProgressType>
	{
	internal:
		using AsyncProgressHandlerType =
			typename AsyncType::ProgressHandlerType;
		using AsyncProgressType = typename AsyncType::ProgressType;

		typename AsyncProgressHandlerType^ m_ProgressHandler;

		virtual typename AsyncProgressHandlerType^ GetOnProgress() override
		{
			this->CheckValidStateForDelegateCall();
			return this->m_ProgressHandler;
		}

		virtual void PutOnProgress(
			typename AsyncProgressHandlerType^ ProgressHandler) override
		{
			this->CheckValidStateForDelegateCall();
			this->m_ProgressHandler = ProgressHandler;
		}

		void FireProgress(const typename AsyncProgressType& ProgressValue)
		{
			if (this->m_ProgressHandler != nullptr)
			{
				try
				{
					this->m_ProgressHandler(
						(typename AsyncType::BaseType^)this, ProgressValue);
				}
				catch (...)
				{
					// Null out the delegate since something went wrong when 
					// calling it.
					this->m_ProgressHandler = nullptr;
					throw;
				}
			}
		}

	public:
		M2AsyncProgressBase() :
			M2AsyncBase<AsyncType>(),
			m_ProgressHandler(nullptr)
		{
		}

		virtual void ReportProgress(
			const typename AsyncType::ProgressType& ProgressValue)
		{
			this->FireProgress(ProgressValue);
		}
	};

	template<typename TClass, typename TReturn, typename TArg1>
	TArg1 M2Arg1ClassHelperThunk(TReturn(TClass::*)(TArg1) const);

	template<typename TClass, typename TReturn, typename TArg1>
	TReturn M2ReturnTypeClassHelperThunk(TReturn(TClass::*)(TArg1) const);

	template<typename TProgress>
	struct M2AsyncProgressTypeTraits
	{
		static const bool NeedProgressHandler = false;
		typedef void ProgressType;
	};

	template<typename TProgress>
	struct M2AsyncProgressTypeTraits<IM2AsyncControllerEx<TProgress>^>
	{
		static const bool NeedProgressHandler = true;
		typedef typename TProgress ProgressType;
	};

	template<typename TFunction>
	struct M2AsyncLambdaType
	{
		using ReturnType =
			decltype(M2ReturnTypeClassHelperThunk(&(TFunction::operator())));

		using ControllerType =
			decltype(M2Arg1ClassHelperThunk(&(TFunction::operator())));
		using ProgressTypeTraits = M2AsyncProgressTypeTraits<ControllerType>;
		using ProgressType = typename ProgressTypeTraits::ProgressType;
		static const bool NeedProgressHandler = ProgressTypeTraits::NeedProgressHandler;

		using AsyncType =
			typename M2AsyncType<ProgressType, ReturnType, NeedProgressHandler>;
	};

	template<typename TFunction, typename TReturn>
	class M2AsyncFunction
	{
	private:
		typename TFunction m_Function;
		std::shared_ptr<TReturn> m_Return;

	public:
		M2AsyncFunction() : m_Function(nullptr)
		{

		}

		M2AsyncFunction(const TFunction& Function)
			: m_Function(Function)
		{

		}

		template<typename... TArg>
		void Run(const TArg& ... Arg)
		{
			this->m_Return = std::make_shared<TReturn>(
				this->m_Function(Arg...));
		}

		TReturn Get()
		{
			return *this->m_Return;
		}
	};

	template<typename TFunction>
	class M2AsyncFunction<TFunction, void>
	{
	private:
		typename TFunction m_Function;

	public:
		M2AsyncFunction() : m_Function(nullptr)
		{

		}

		M2AsyncFunction(const TFunction& Function)
			: m_Function(Function)
		{

		}

		template<typename... TArg>
		void Run(const TArg& ... Arg)
		{
			this->m_Function(Arg...);
		}

		void Get()
		{

		}
	};

	// Async Creation Layer
	template<typename TFunction>
	ref class M2AsyncGenerator sealed : M2AsyncProgressBase<
		typename M2AsyncLambdaType<TFunction>::AsyncType,
		M2AsyncLambdaType<TFunction>::AsyncType::NeedProgressHandler>
	{
	internal:
		using AsyncReturnType =
			typename M2AsyncLambdaType<TFunction>::AsyncType::ReturnType;

		M2AsyncFunction<TFunction, AsyncReturnType> m_Function;

		M2AsyncGenerator(const TFunction& Function) : m_Function(Function)
		{
			// Virtual call here is safe as the class is declared 'sealed'
			this->Start();
		}

	public:

		virtual typename AsyncReturnType GetResults() override
		{
			this->CheckValidStateForResultsCall();
			return this->m_Function.Get();
		}

	internal:

		// The only thing we must do different from the base class is we must 
		// spin the hot task on transition from Created->Started. Otherwise, 
		// let the base thunk handle everything.

		virtual void OnStart() override
		{
			// Call the appropriate task generator to actually produce a task 
			// of the expected type. This might adapt the user lambda for 
			// progress reports, wrap the return result in a task, or allow for
			// direct return of a task depending on the form of the lambda.

			M2::CThread([this]()
				{
					// Capture the state.
					try
					{
						// Run the worker function.
						this->m_Function.Run(this);

						this->FireCompletion();
					}
					catch (M2AsyncTaskCanceledException&)
					{
						this->TryTransitionToCancelled();
					}
					catch (...)
					{
						this->TryTransitionToError(
							M2ThrownPlatformExceptionToHResult());
					}
				});
		}

		virtual void OnCancel() override
		{

		}

		virtual void OnClose() override
		{
		}
	};
}

/**
 * Creates a Windows Runtime asynchronous construct based on a user supplied
 * lambda or function object.
 *
 * @param Function The lambda or function object from which to create a Windows
 *                 Runtime asynchronous construct. The lambda type is
 *                 "[Capture]([ControllerType] AsyncController)
 *                 -> ReturnType {}". If you want to return an IAsyncAction^ or
 *                 IAsyncOperation<TResult>^ type, you need to set the
 *                 ControllerType to IM2AsyncController^. If you want to return
 *                 an IAsyncActionWithProgress<TProgress>^ or
 *                 IAsyncOperationWithProgress<TResult, TProgress>^ type, you
 *                 need to set the ControllerType to IM2AsyncControllerEx^.
 * @return An asynchronous construct represented by an IAsyncAction^,
 *         IAsyncActionWithProgress<TProgress>^, IAsyncOperation<TResult>^, or
 *         an IAsyncOperationWithProgress<TResult, TProgress>^. The interface
 *         returned depends on the signature of the lambda passed into the
 * function.
 */
template<typename TFunction>
__declspec(noinline)
M2AsyncCreateInternal::M2AsyncGenerator<TFunction>^ M2AsyncCreate(
	const TFunction& Function)
{
	return ref new M2AsyncCreateInternal::M2AsyncGenerator<TFunction>(
		Function);
}

namespace M2
{
	using Platform::String;
	using Windows::Foundation::IAsyncOperation;
	using Windows::Storage::AccessCache::IStorageItemAccessList;
	using Windows::Storage::IStorageItem;

	class CFutureAccessList
	{
	private:
		IStorageItemAccessList^ m_FutureAccessList = nullptr;

	public:
		/**
		 * Creates a new CFutureAccessList object.
		 *
		 */
		CFutureAccessList()
		{
			using Windows::Storage::AccessCache::StorageApplicationPermissions;
			this->m_FutureAccessList =
				StorageApplicationPermissions::FutureAccessList;
		}

		/**
		 * Adds IStorageItem object to the future access list.
		 *
		 * @param Item The IStorageItem object which you want to add.
		 * @return A token that the app can use later to retrieve the storage
		 *         item.
		 */
		String^ AddItem(IStorageItem^ Item)
		{
			return this->m_FutureAccessList->Add(Item);
		}

		/**
		 * Gets IStorageItem object from the future access list.
		 *
		 * @param Token The token of the IStorageItem object.
		 * @return When this method completes successfully, it returns the item
		 *         (type IStorageItem ) that is associated with the specified
		 *         token.
		 */
		IAsyncOperation<IStorageItem^>^ GetItemAsync(String^ Token)
		{
			return this->m_FutureAccessList->GetItemAsync(Token);
		}

		/**
		 * Gets IStorageItemAccessList object.
		 *
		 * @return Returns an IStorageItemAccessList object.
		 */
		IStorageItemAccessList^ Get()
		{
			return this->m_FutureAccessList;
		}
	};
}

#endif

#pragma endregion

#endif // _M2_WINDOWS_HELPERS_
