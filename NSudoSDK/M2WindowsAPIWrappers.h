/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsAPIWrappers.h
 * PURPOSE:   Definition for the Windows API wrappers
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef _M2_WINDOWS_API_WRAPPERS_
#define _M2_WINDOWS_API_WRAPPERS_

#include <Windows.h>

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

/**
 * Retrieves the number of milliseconds that have elapsed since the system was
 * started.
 *
 * @return The number of milliseconds.
 */
ULONGLONG M2GetTickCount();

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

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

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

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

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

#endif

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

namespace M2
{
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
}

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

#endif // _M2_WINDOWS_API_WRAPPERS_
