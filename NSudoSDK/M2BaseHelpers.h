/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2BaseHelpers.h
 * PURPOSE:   Definition for the basic helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef _M2_BASE_HELPERS_
#define _M2_BASE_HELPERS_

#include <Windows.h>

#include <assert.h>
#include <process.h>

#include <map>
#include <string>
#include <vector>

/**
 * If the type T is a reference type, provides the member typedef type which is
 * the type referred to by T. Otherwise type is T.
 */ 
template<class T> struct M2RemoveReference { typedef T Type; };
template<class T> struct M2RemoveReference<T&> { typedef T Type; };
template<class T> struct M2RemoveReference<T&&> { typedef T Type; };

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
     * The implementation of thread.
     */
    class CThread
    {
    private:
        HANDLE CreateThreadInternal(
            _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
            _In_ SIZE_T dwStackSize,
            _In_ LPTHREAD_START_ROUTINE lpStartAddress,
            _In_opt_ __drv_aliasesMem LPVOID lpParameter,
            _In_ DWORD dwCreationFlags,
            _Out_opt_ LPDWORD lpThreadId)
        {
            // sanity check for lpThreadId
            assert(sizeof(DWORD) == sizeof(unsigned));

            typedef unsigned(__stdcall* routine_type)(void*);

            // _beginthreadex calls CreateThread which will set the last error
            // value before it returns.
            return reinterpret_cast<HANDLE>(_beginthreadex(
                lpThreadAttributes,
                static_cast<unsigned>(dwStackSize),
                reinterpret_cast<routine_type>(lpStartAddress),
                lpParameter,
                dwCreationFlags,
                reinterpret_cast<unsigned*>(lpThreadId)));
        }

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

            this->m_Thread = CreateThreadInternal(
                nullptr,
                0,
                ThreadFunctionInternal,
                reinterpret_cast<void*>(
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

        _Acquires_lock_(m_CriticalSection) bool TryLock()
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
        static ClassType& Get()
        {
            M2::AutoCriticalSectionLock Lock(this->m_SingletonCS);

            if (nullptr == this->m_Instance)
            {
                this->m_Instance = new ClassType();
            }

            return *this->m_Instance;
        }
    };

}

/**
 * Retrieves the number of logical processors in the current group.
 *
 * @return The number of logical processors in the current group.
 */
inline DWORD M2GetNumberOfHardwareThreads()
{
    SYSTEM_INFO SystemInfo = { 0 };
    GetNativeSystemInfo(&SystemInfo);
    return SystemInfo.dwNumberOfProcessors;
}

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
 * Retrieves the number of milliseconds that have elapsed since the system was
 * started.
 *
 * @return The number of milliseconds.
 */
ULONGLONG M2GetTickCount();

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
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastError();

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
    HRESULT M2GetProcAddress(
        _Out_ FARPROC& lpProcAddress,
        _In_ HMODULE hModule,
        _In_ LPCSTR lpProcName);

    return M2GetProcAddress(
        reinterpret_cast<FARPROC&>(lpProcAddress), hModule, lpProcName);
}

/**
 * Retrieves the path of the executable file of the current process.
 *
 * @return If the function succeeds, the return value is the path of the
 *         executable file of the current process. If the function fails, the
 *         return value is an empty string.
 */
std::wstring M2GetCurrentProcessModulePath();

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

#endif // _M2_BASE_HELPERS_
