/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsHelpers.cpp
 * PURPOSE:   Implementation for the Windows helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "stdafx.h"

#include "M2WindowsHelpers.h"

#ifdef _M2_WINDOWS_BASE_HELPERS_

#include <assert.h>
#include <process.h>

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
    _Out_opt_ PDWORD ReturnLength)
{
    return M2GetLastHResultError(
        AdjustTokenPrivileges(
            TokenHandle,
            DisableAllPrivileges,
            NewState,
            BufferLength,
            PreviousState,
            ReturnLength),
        TRUE);
}

/**
 * Closes an open object handle.
 *
 * @param hObject A valid handle to an open object.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CloseHandle.
 */
HRESULT M2CloseHandle(
    _In_ HANDLE hObject)
{
    return M2GetLastHResultError(CloseHandle(hObject));
}

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
    _Out_ LPVOID* ppv)
{
    CLSID clsid;
    IID iid;

    HRESULT hr = CLSIDFromString(lpszCLSID, &clsid);
    if (SUCCEEDED(hr))
    {
        hr = IIDFromString(lpszIID, &iid);
        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(clsid, pUnkOuter, dwClsContext, iid, ppv);
        }
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates a thread to execute within the virtual address space of the calling
 * process.
 *
 * @param lpFileHandle The address of the returned handle to the specified
 *                     file.
 * @param lpFileName The name of the file or device to be created or opened.
 *                   You may use either forward slashes (/) or backslashes ()
 *                   in this name.
 * @param dwDesiredAccess The requested access to the file or device, which can
 *                        be summarized as read, write, both or neither zero).
 * @param dwShareMode The requested sharing mode of the file or device, which
 *                    can be read, write, both, delete, all of these, or none
 *                    (refer to the following table). Access requests to
 *                    attributes or extended attributes are not affected by
 *                    this flag.
 * @param lpSecurityAttributes A pointer to a SECURITY_ATTRIBUTES structure
 *                             that contains two separate but related data
 *                             members: an optional security descriptor, and a
 *                             Boolean value that determines whether the
 *                             returned handle can be inherited by child
 *                             processes. This parameter can be NULL.
 * @param dwCreationDisposition An action to take on a file or device that
 *                              exists or does not exist.
 * @param dwFlagsAndAttributes The file or device attributes and flags,
 *                             FILE_ATTRIBUTE_NORMAL being the most common
 *                             default value for files.
 * @param hTemplateFile A valid handle to a template file with the GENERIC_READ
 *                      access right. The template file supplies file
 *                      attributes and extended attributes for the file that is
 *                      being created. This parameter can be NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateFileW.
 */
HRESULT M2CreateFile(
    _Out_ PHANDLE lpFileHandle,
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile)
{
    *lpFileHandle = CreateFileW(
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile);

    return M2GetLastHResultError(INVALID_HANDLE_VALUE != *lpFileHandle);
}

#endif

/**
 * Creates a thread to execute within the virtual address space of the calling
 * process.
 *
 * @param lpThreadHandle The address of the returned handle to the new thread.
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
    _In_opt_ LPVOID lpParameter,
    _In_ DWORD dwCreationFlags,
    _Out_opt_ LPDWORD lpThreadId)
{
    // sanity check for lpThreadId
    assert(sizeof(DWORD) == sizeof(unsigned));

    typedef unsigned(__stdcall * routine_type)(void*);

    // _beginthreadex calls CreateThread which will set the last error
    // value before it returns.
    *lpThreadHandle = reinterpret_cast<HANDLE>(_beginthreadex(
        lpThreadAttributes,
        static_cast<unsigned>(dwStackSize),
        reinterpret_cast<routine_type>(lpStartAddress),
        lpParameter,
        dwCreationFlags,
        reinterpret_cast<unsigned*>(lpThreadId)));

    return M2GetLastHResultError(*lpThreadHandle != nullptr);
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Sends a control code directly to a specified device driver, causing the
 * corresponding device to perform the corresponding operation.
 *
 * @param hDevice A handle to the device on which the operation is to be
 *                performed.
 * @param dwIoControlCode The control code for the operation.
 * @param lpInBuffer A pointer to the input buffer that contains the data
 *                   required to perform the operation. This parameter can be
 *                   NULL if dwIoControlCode specifies an operation that does
 *                   not require input data.
 * @param nInBufferSize The size of the input buffer, in bytes.
 * @param lpOutBuffer A pointer to the output buffer that is to receive the
 *                    data returned by the operation. This parameter can be
 *                    NULL if dwIoControlCode specifies an operation that does
 *                    not return data.
 * @param nOutBufferSize The size of the output buffer, in bytes.
 * @param lpBytesReturned A pointer to a variable that receives the size of
 *                        the data stored in the output buffer, in bytes.
 * @param lpOverlapped A pointer to an OVERLAPPED structure.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see DeviceIoControl.
 */
HRESULT M2DeviceIoControl(
    _In_ HANDLE hDevice,
    _In_ DWORD dwIoControlCode,
    _In_opt_ LPVOID lpInBuffer,
    _In_ DWORD nInBufferSize,
    _Out_opt_ LPVOID lpOutBuffer,
    _In_ DWORD nOutBufferSize,
    _Out_opt_ LPDWORD lpBytesReturned,
    _Inout_opt_ LPOVERLAPPED lpOverlapped)
{
    return M2GetLastHResultError(DeviceIoControl(
        hDevice,
        dwIoControlCode,
        lpInBuffer,
        nInBufferSize,
        lpOutBuffer,
        nOutBufferSize,
        lpBytesReturned,
        lpOverlapped));
}

#endif

/**
 * Frees the loaded dynamic-link library (DLL) module and, if necessary,
 * decrements its reference count. When the reference count reaches zero, the
 * module is unloaded from the address space of the calling process and the
 * handle is no longer valid.
 *
 * @param hLibModule A handle to the loaded library module.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see FreeLibrary.
 */
HRESULT M2FreeLibrary(
    _In_ HMODULE hLibModule)
{
    return M2GetLastHResultError(FreeLibrary(hLibModule));
}

/**
 * Retrieves file information for the specified file.
 *
 * @param hFile A handle to the file that contains the information to be
 *              retrieved. This handle should not be a pipe handle.
 * @param FileInformationClass A FILE_INFO_BY_HANDLE_CLASS enumeration value
 *                             that specifies the type of information to be
 *                             retrieved.
 * @param lpFileInformation A pointer to the buffer that receives the requested
 *                          file information.
 * @param dwBufferSize The size of the lpFileInformation buffer, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetFileInformationByHandleEx.
 */
HRESULT M2GetFileInformation(
    _In_  HANDLE hFile,
    _In_  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    _Out_ LPVOID lpFileInformation,
    _In_  DWORD dwBufferSize)
{
    return M2GetLastHResultError(GetFileInformationByHandleEx(
        hFile,
        FileInformationClass,
        lpFileInformation,
        dwBufferSize));
}

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @param IsLastFunctionCallSucceeded Set this parameter TRUE if you can be
 *                                    sure that the last call was succeeded.
 *                                    Otherwise, set this parameter FALSE.
 * @param UseLastErrorWhenSucceeded Set this parameter TRUE if you want to use
 *                                  last-error code if the last call was
 *                                  succeeded. Otherwise, set this parameter
 *                                  FALSE.
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastHResultError(
    _In_ BOOL IsLastFunctionCallSucceeded,
    _In_ BOOL UseLastErrorWhenSucceeded)
{
    return HRESULT_FROM_WIN32(M2GetLastWin32Error(
        IsLastFunctionCallSucceeded,
        UseLastErrorWhenSucceeded));
}

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @param IsLastFunctionCallSucceeded Set this parameter TRUE if you can be
 *                                    sure that the last call was succeeded.
 *                                    Otherwise, set this parameter FALSE.
 * @param UseLastErrorWhenSucceeded Set this parameter TRUE if you want to use
 *                                  last-error code if the last call was
 *                                  succeeded. Otherwise, set this parameter
 *                                  FALSE.
 * @return The calling thread's last-error code.
 */
DWORD M2GetLastWin32Error(
    _In_ BOOL IsLastFunctionCallSucceeded,
    _In_ BOOL UseLastErrorWhenSucceeded)
{
    if (IsLastFunctionCallSucceeded && !UseLastErrorWhenSucceeded)
        return ERROR_SUCCESS;

    DWORD LastError = GetLastError();

    if (!IsLastFunctionCallSucceeded && ERROR_SUCCESS == LastError)
        return ERROR_FUNCTION_FAILED;

    return LastError;
}

/**
 * Retrieves the number of logical processors in the current group.
 *
 * @return The number of logical processors in the current group.
 */
DWORD M2GetNumberOfHardwareThreads()
{
    SYSTEM_INFO SystemInfo = { 0 };
    GetNativeSystemInfo(&SystemInfo);
    return SystemInfo.dwNumberOfProcessors;
}

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
    _In_ LPCSTR lpProcName)
{
    *lpProcAddress = GetProcAddress(hModule, lpProcName);
    return M2GetLastHResultError(*lpProcAddress != nullptr);
}

/**
 * Retrieves the number of milliseconds that have elapsed since the system was
 * started.
 *
 * @return The number of milliseconds.
 */
ULONGLONG M2GetTickCount()
{
    LARGE_INTEGER Frequency = { 0 }, PerformanceCount = { 0 };

    if (QueryPerformanceFrequency(&Frequency))
    {
        if (QueryPerformanceCounter(&PerformanceCount))
        {
            return (PerformanceCount.QuadPart * 1000 / Frequency.QuadPart);
        }
    }

    return GetTickCount64();
}

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
    _Out_ PDWORD ReturnLength)
{
    return M2GetLastHResultError(GetTokenInformation(
        TokenHandle,
        TokenInformationClass,
        TokenInformation,
        TokenInformationLength,
        ReturnLength));
}

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
    _In_ SIZE_T dwBytes)
{
    *lpNewMem = HeapAlloc(hHeap, dwFlags, dwBytes);
    return *lpNewMem ? S_OK : __HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
}

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
    _In_ LPVOID lpMem)
{
    return M2GetLastHResultError(HeapFree(hHeap, dwFlags, lpMem));
}

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
    _In_ SIZE_T dwBytes)
{
    *lpNewMem = HeapReAlloc(hHeap, dwFlags, lpMem, dwBytes);
    return *lpNewMem ? S_OK : __HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
}

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
    _In_ DWORD dwFlags)
{
    *phLibModule = LoadLibraryExW(lpLibFileName, hFile, dwFlags);
    return M2GetLastHResultError(*phLibModule != nullptr);
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Closes a handle to the specified registry key.
 *
 * @param hKey A handle to the open key to be closed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegCloseKey.
 */
HRESULT M2RegCloseKey(
    _In_ HKEY hKey)
{
    return HRESULT_FROM_WIN32(RegCloseKey(hKey));
}

#endif

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
    _Out_opt_ LPDWORD lpdwDisposition)
{
    return HRESULT_FROM_WIN32(RegCreateKeyExW(
        hKey,
        lpSubKey,
        Reserved,
        lpClass,
        dwOptions,
        samDesired,
        lpSecurityAttributes,
        phkResult,
        lpdwDisposition));
}

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
    _Inout_opt_ LPDWORD lpcbData)
{
    return HRESULT_FROM_WIN32(RegQueryValueExW(
        hKey,
        lpValueName,
        lpReserved,
        lpType,
        lpData,
        lpcbData));
}

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
    _In_ DWORD cbData)
{
    return HRESULT_FROM_WIN32(RegSetValueExW(
        hKey,
        lpValueName,
        Reserved,
        dwType,
        lpData,
        cbData));
}

#endif

/**
 * Sets the file information for the specified file.
 *
 * @param hFile A handle to the file for which to change information. This
 *              handle should not be a pipe handle.
 * @param FileInformationClass A FILE_INFO_BY_HANDLE_CLASS enumeration value
 *                             that specifies the type of information to be
 *                             changed.
 * @param lpFileInformation A pointer to the buffer that contains the
 *                          information to change for the specified file
 *                          information class.
 * @param dwBufferSize The size of the lpFileInformation buffer, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see SetFileInformationByHandle.
 */
HRESULT M2SetFileInformation(
    _In_ HANDLE hFile,
    _In_ FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    _In_ LPVOID lpFileInformation,
    _In_ DWORD dwBufferSize)
{
    return M2GetLastHResultError(SetFileInformationByHandle(
        hFile,
        FileInformationClass,
        lpFileInformation,
        dwBufferSize));
}


#endif // _M2_WINDOWS_BASE_HELPERS_

#ifdef _M2_WINDOWS_BASE_EXTENDED_HELPERS_

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
    _In_ SIZE_T MemoryBlockSize)
{
    return M2HeapAlloc(
        AllocatedMemoryBlock,
        GetProcessHeap(),
        HEAP_ZERO_MEMORY,
        MemoryBlockSize);
}

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
    _In_ SIZE_T NewMemoryBlockSize)
{
    return M2HeapReAlloc(
        NewAllocatedMemoryBlock,
        GetProcessHeap(),
        HEAP_ZERO_MEMORY,
        OldAllocatedMemoryBlock,
        NewMemoryBlockSize);
}

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
    _In_ PVOID AllocatedMemoryBlock)
{
    return M2HeapFree(GetProcessHeap(), 0, AllocatedMemoryBlock);
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
    _Out_ PDWORD FileAttributes)
{
    FILE_BASIC_INFO BasicInfo;

    HRESULT hr = M2GetFileInformation(
        FileHandle,
        FileBasicInfo,
        &BasicInfo,
        sizeof(FILE_BASIC_INFO));

    *FileAttributes = SUCCEEDED(hr)
        ? BasicInfo.FileAttributes
        : INVALID_FILE_ATTRIBUTES;

    return hr;
}

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
    _In_ DWORD FileAttributes)
{
    FILE_BASIC_INFO BasicInfo = { 0 };
    BasicInfo.FileAttributes =
        FileAttributes & (
            FILE_SHARE_READ |
            FILE_SHARE_WRITE |
            FILE_SHARE_DELETE |
            FILE_ATTRIBUTE_ARCHIVE |
            FILE_ATTRIBUTE_TEMPORARY |
            FILE_ATTRIBUTE_OFFLINE |
            FILE_ATTRIBUTE_NOT_CONTENT_INDEXED |
            FILE_ATTRIBUTE_NO_SCRUB_DATA) |
        FILE_ATTRIBUTE_NORMAL;

    return M2SetFileInformation(
        FileHandle,
        FileBasicInfo,
        &BasicInfo,
        sizeof(FILE_BASIC_INFO));
}

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
    _Out_ PULONGLONG FileSize)
{
    FILE_STANDARD_INFO StandardInfo;

    HRESULT hr = M2GetFileInformation(
        FileHandle,
        FileStandardInfo,
        &StandardInfo,
        sizeof(FILE_STANDARD_INFO));

    *FileSize = SUCCEEDED(hr)
        ? static_cast<ULONGLONG>(StandardInfo.EndOfFile.QuadPart)
        : 0;

    return hr;
}

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
    _Out_ PULONGLONG AllocationSize)
{
    FILE_STANDARD_INFO StandardInfo;

    HRESULT hr = M2GetFileInformation(
        FileHandle,
        FileStandardInfo,
        &StandardInfo,
        sizeof(FILE_STANDARD_INFO));

    *AllocationSize = SUCCEEDED(hr)
        ? static_cast<ULONGLONG>(StandardInfo.AllocationSize.QuadPart)
        : 0;

    return hr;
}

/**
 * Deletes an existing file.
 *
 * @param FileHandle The handle of the file to be deleted. This handle must be
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
    _In_ HANDLE FileHandle)
{
    FILE_DISPOSITION_INFO DispostionInfo;
    DispostionInfo.DeleteFile = TRUE;

    return M2SetFileInformation(
        FileHandle,
        FileDispositionInfo,
        &DispostionInfo,
        sizeof(FILE_DISPOSITION_INFO));
}

/**
 * Deletes an existing file, even the file have the readonly attribute.
 *
 * @param FileHandle The handle of the file to be deleted. This handle must be
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
    _In_ HANDLE FileHandle)
{
    HRESULT hr = S_OK;
    DWORD OldAttribute = 0;

    // Save old attributes.
    hr = M2GetFileAttributes(
        FileHandle,
        &OldAttribute);
    if (!SUCCEEDED(hr)) return hr;

    // Remove readonly attribute.
    hr = M2SetFileAttributes(
        FileHandle,
        OldAttribute & (-1 ^ FILE_ATTRIBUTE_READONLY));
    if (!SUCCEEDED(hr)) return hr;

    // Delete the file.
    hr = M2DeleteFile(FileHandle);
    if (!SUCCEEDED(hr))
    {
        // Restore attributes if failed.
        hr = M2SetFileAttributes(
            FileHandle,
            OldAttribute);
    }

    return hr;
}

/**
 * The internal content of the file enumerator handle.
 */
typedef struct _M2_FILE_ENUMERATOR_OBJECT
{
    HANDLE FileHandle;
    PFILE_ID_BOTH_DIR_INFO CurrentFileInfo;
    BYTE FileInfoBuffer[32768];
} M2_FILE_ENUMERATOR_OBJECT, * PM2_FILE_ENUMERATOR_OBJECT;

/**
 * Creates a file enumerator handle for searching a directory for a file or
 * subdirectory with a name.
 *
 * @param FileEnumeratorHandle The file enumerator handle.
 * @param FileHandle The handle of the file to be searched a directory for a
 *                   file or subdirectory with a name. This handle must be
 *                   opened with the appropriate permissions for the requested
 *                   change. This handle should not be a pipe handle.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             FILE_LIST_DIRECTORY | SYNCHRONIZE,
 *             FILE_SHARE_READ | FILE_SHARE_WRITE,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2CreateFileEnumerator(
    _Out_ PM2_FILE_ENUMERATOR_HANDLE FileEnumeratorHandle,
    _In_ HANDLE FileHandle)
{
    if ((!FileEnumeratorHandle) || (INVALID_HANDLE_VALUE == FileHandle))
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    *FileEnumeratorHandle = nullptr;

    PM2_FILE_ENUMERATOR_OBJECT Object = nullptr;
    HRESULT hr = M2AllocMemory(
        reinterpret_cast<PVOID*>(&Object),
        sizeof(M2_FILE_ENUMERATOR_OBJECT));
    if (SUCCEEDED(hr))
    {
        Object->FileHandle = FileHandle;

        *FileEnumeratorHandle = Object;
    }

    return hr;
}

/**
 * Closes a created file enumerator handle.
 *
 * @param FileEnumeratorHandle The created file enumerator handle.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2CloseFileEnumerator(
    _In_ M2_FILE_ENUMERATOR_HANDLE FileEnumeratorHandle)
{
    if (!FileEnumeratorHandle)
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    return M2FreeMemory(FileEnumeratorHandle);
}

/**
 * Starts or continues a file search from a created file enumerator handle.
 *
 * @param FileEnumeratorInformation A pointer to the
 *                                  M2_FILE_ENUMERATOR_INFORMATION structure
 *                                  that receives information about a found
 *                                  file or directory.
 * @param FileEnumeratorHandle The created file enumerator handle.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2QueryFileEnumerator(
    _Out_ PM2_FILE_ENUMERATOR_INFORMATION FileEnumeratorInformation,
    _In_ M2_FILE_ENUMERATOR_HANDLE FileEnumeratorHandle)
{
    if ((!FileEnumeratorHandle) || (!FileEnumeratorInformation))
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    HRESULT hr = S_OK;

    PM2_FILE_ENUMERATOR_OBJECT Object =
        reinterpret_cast<PM2_FILE_ENUMERATOR_OBJECT>(FileEnumeratorHandle);

    if (!Object->CurrentFileInfo)
    {
        Object->CurrentFileInfo =
            reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(Object->FileInfoBuffer);

        hr = M2GetFileInformation(
            Object->FileHandle,
            FILE_INFO_BY_HANDLE_CLASS::FileIdBothDirectoryRestartInfo,
            Object->CurrentFileInfo,
            sizeof(Object->FileInfoBuffer));
    }
    else if (!Object->CurrentFileInfo->NextEntryOffset)
    {
        Object->CurrentFileInfo =
            reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(Object->FileInfoBuffer);
        hr = M2GetFileInformation(
            Object->FileHandle,
            FILE_INFO_BY_HANDLE_CLASS::FileIdBothDirectoryInfo,
            Object->CurrentFileInfo,
            sizeof(Object->FileInfoBuffer));
    }
    else
    {
        Object->CurrentFileInfo = reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(
            reinterpret_cast<ULONG_PTR>(Object->CurrentFileInfo)
            + Object->CurrentFileInfo->NextEntryOffset);
    }

    if (SUCCEEDED(hr))
    {
        FileEnumeratorInformation->CreationTime.dwHighDateTime =
            Object->CurrentFileInfo->CreationTime.HighPart;
        FileEnumeratorInformation->CreationTime.dwLowDateTime =
            Object->CurrentFileInfo->CreationTime.LowPart;
        FileEnumeratorInformation->LastAccessTime.dwHighDateTime =
            Object->CurrentFileInfo->LastAccessTime.HighPart;
        FileEnumeratorInformation->LastAccessTime.dwLowDateTime =
            Object->CurrentFileInfo->LastAccessTime.LowPart;
        FileEnumeratorInformation->LastWriteTime.dwHighDateTime =
            Object->CurrentFileInfo->LastWriteTime.HighPart;
        FileEnumeratorInformation->LastWriteTime.dwLowDateTime =
            Object->CurrentFileInfo->LastWriteTime.LowPart;
        FileEnumeratorInformation->ChangeTime.dwHighDateTime =
            Object->CurrentFileInfo->ChangeTime.HighPart;
        FileEnumeratorInformation->ChangeTime.dwLowDateTime =
            Object->CurrentFileInfo->ChangeTime.LowPart;
        FileEnumeratorInformation->FileSize =
            Object->CurrentFileInfo->EndOfFile;
        FileEnumeratorInformation->AllocationSize =
            Object->CurrentFileInfo->AllocationSize;
        FileEnumeratorInformation->FileAttributes =
            Object->CurrentFileInfo->FileAttributes;
        FileEnumeratorInformation->EaSize =
            Object->CurrentFileInfo->EaSize;
        FileEnumeratorInformation->FileId =
            Object->CurrentFileInfo->FileId;
        wcsncpy_s(
            FileEnumeratorInformation->ShortName,
            Object->CurrentFileInfo->ShortName,
            Object->CurrentFileInfo->ShortNameLength / sizeof(wchar_t));
        wcsncpy_s(
            FileEnumeratorInformation->FileName,
            Object->CurrentFileInfo->FileName,
            Object->CurrentFileInfo->FileNameLength / sizeof(wchar_t));
    }

    return hr;
}

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
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass)
{
    *OutputInformation = nullptr;

    DWORD Length = 0;

    HRESULT hr = M2GetTokenInformation(
        TokenHandle,
        TokenInformationClass,
        nullptr,
        0,
        &Length);
    if (hr == __HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
    {
        hr = M2AllocMemory(OutputInformation, Length);
        if (SUCCEEDED(hr))
        {
            hr = M2GetTokenInformation(
                TokenHandle,
                TokenInformationClass,
                *OutputInformation,
                Length,
                &Length);
            if (FAILED(hr))
            {
                hr = M2FreeMemory(*OutputInformation);
            }
        }
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

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
    _In_opt_ LPCWSTR lpValueName)
{
    *lpData = nullptr;

    DWORD cbData = 0;
    HRESULT hr = M2RegQueryValue(
        hKey,
        lpValueName,
        nullptr,
        nullptr,
        nullptr,
        &cbData);
    if (SUCCEEDED(hr))
    {
        hr = M2AllocMemory(reinterpret_cast<PVOID*>(lpData), cbData);
        if (SUCCEEDED(hr))
        {
            DWORD Type = 0;
            hr = M2RegQueryValue(
                hKey,
                lpValueName,
                nullptr,
                &Type,
                reinterpret_cast<LPBYTE>(*lpData),
                &cbData);
            if (SUCCEEDED(hr) && REG_SZ != Type)
                hr = __HRESULT_FROM_WIN32(ERROR_ILLEGAL_ELEMENT_ADDRESS);

            if (FAILED(hr))
                hr = M2FreeMemory(*lpData);
        }
    }

    return hr;
}

#endif

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
    _In_ LPCWSTR InterfaceName)
{
    wchar_t RegistryKeyPath[64];
    if (0 != wcscpy_s(RegistryKeyPath, L"Interface\\"))
        return E_INVALIDARG;
    if (0 != wcscat_s(RegistryKeyPath, InterfaceID))
        return E_INVALIDARG;

    HKEY hKey = nullptr;
    HRESULT hr = M2RegCreateKey(
        HKEY_CLASSES_ROOT,
        RegistryKeyPath,
        0,
        nullptr,
        0,
        KEY_READ,
        nullptr,
        &hKey,
        nullptr);
    if (SUCCEEDED(hr))
    {
        wchar_t* InterfaceTypeName = nullptr;
        hr = M2RegQueryStringValue(&InterfaceTypeName, hKey, nullptr);
        if (SUCCEEDED(hr))
        {
            if (0 != _wcsicmp(InterfaceTypeName, InterfaceName))
            {
                hr = E_NOINTERFACE;
            }

            M2FreeMemory(InterfaceTypeName);
        }

        M2RegCloseKey(hKey);
    }

    return hr;
}

#endif

#endif // !_M2_WINDOWS_BASE_EXTENDED_HELPERS_

#ifdef _M2_WINDOWS_HELPERS_

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#include <VersionHelpers.h>
#endif

#include <strsafe.h>

#ifdef __cplusplus_winrt
#include <wrl\client.h>
#include <wrl\implements.h>
#include <robuffer.h>

#include <windows.foundation.h>
#include <windows.storage.streams.h>

#include <string>

using Microsoft::WRL::ComPtr;
using Microsoft::WRL::MakeAndInitialize;
using Microsoft::WRL::RuntimeClass;
using Microsoft::WRL::RuntimeClassFlags;
using Microsoft::WRL::RuntimeClassType;
#endif

#pragma region Error

#ifdef __cplusplus_winrt

/**
 * Throw the appropriate Platform::Exception for the given HRESULT.
 *
 * @param hr The error HRESULT that is represented by the exception.
 * @return This function does not return a value, but will throw
 *         Platform::Exception.
 */
__declspec(noreturn) void M2ThrowPlatformException(HRESULT hr)
{
    throw Platform::Exception::CreateException(hr);
}

/**
 * Throw the appropriate Platform::Exception for the given HRESULT.
 *
 * @param hr The error HRESULT that is represented by the exception.
 * @return This function does not return a value, but will throw
 *         Platform::Exception if it is a failed HRESULT value.
 */
void M2ThrowPlatformExceptionIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        M2ThrowPlatformException(hr);
    }
}

/**
 * Convert C++/CX exceptions in the callable code into HRESULTs.
 *
 * @return The function will return HRESULT.
 */
HRESULT M2ThrownPlatformExceptionToHResult()
{
    try
    {
        throw;
    }
    catch (Platform::Exception^ ex)
    {
        return ex->HResult;
    }
    catch (std::bad_alloc const&)
    {
        return E_OUTOFMEMORY;
    }
    catch (...)
    {
        return E_UNEXPECTED;
    }
}

#endif

#pragma endregion

#pragma region String

/**
 * Converts from the UTF-8 string to the UTF-16 string.
 *
 * @param UTF8String The UTF-8 string you want to convert.
 * @return A converted UTF-16 string.
 */
std::wstring M2MakeUTF16String(const std::string& UTF8String)
{
    std::wstring UTF16String;

    int UTF16StringLength = MultiByteToWideChar(
        CP_UTF8,
        0,
        UTF8String.data(),
        (int)UTF8String.size(),
        nullptr,
        0);
    if (UTF16StringLength > 0)
    {
        UTF16String.resize(UTF16StringLength);
        MultiByteToWideChar(
            CP_UTF8,
            0,
            UTF8String.data(),
            (int)UTF8String.size(),
            &UTF16String[0],
            UTF16StringLength);
    }

    return UTF16String;
}

/**
 * Converts from the UTF-16 string to the UTF-8 string.
 *
 * @param UTF16String The UTF-16 string you want to convert.
 * @return A converted UTF-8 string.
 */
std::string M2MakeUTF8String(const std::wstring& UTF16String)
{
    std::string UTF8String;

    int UTF8StringLength = WideCharToMultiByte(
        CP_UTF8,
        0,
        UTF16String.data(),
        (int)UTF16String.size(),
        nullptr,
        0,
        nullptr,
        nullptr);
    if (UTF8StringLength > 0)
    {
        UTF8String.resize(UTF8StringLength);
        WideCharToMultiByte(
            CP_UTF8,
            0,
            UTF16String.data(),
            (int)UTF16String.size(),
            &UTF8String[0],
            UTF8StringLength,
            nullptr,
            nullptr);
    }

    return UTF8String;
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
    ...)
{
    // Check the argument list.
    if (nullptr != Format)
    {
        va_list ArgList = nullptr;
        va_start(ArgList, Format);

        // Get the length of the format result.
        size_t nLength = static_cast<size_t>(_vscwprintf(Format, ArgList)) + 1;

        // Allocate for the format result.
        std::wstring Buffer(nLength + 1, L'\0');

        // Format the string.
        int nWritten = _vsnwprintf_s(
            &Buffer[0],
            Buffer.size(),
            nLength,
            Format,
            ArgList);

        va_end(ArgList);

        if (nWritten > 0)
        {
            // If succeed, resize to fit and return result.
            Buffer.resize(nWritten);
            return Buffer;
        }
    }

    // If failed, return "N/A".
    return L"N/A";
}

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
    const std::wstring& CommandLine)
{
    // Initialize the SplitArguments.
    std::vector<std::wstring> SplitArguments;

    wchar_t c = L'\0';
    int copy_character;                   /* 1 = copy char to *args */
    unsigned numslash;              /* num of backslashes seen */

    std::wstring Buffer;
    Buffer.reserve(CommandLine.size());

    /* first scan the program name, copy it, and count the bytes */
    wchar_t* p = const_cast<wchar_t*>(CommandLine.c_str());

    // A quoted program name is handled here. The handling is much simpler than
    // for other arguments. Basically, whatever lies between the leading
    // double-quote and next one, or a terminal null character is simply
    // accepted. Fancier handling is not required because the program name must
    // be a legal NTFS/HPFS file name. Note that the double-quote characters are
    // not copied, nor do they contribute to character_count.
    bool InQuotes = false;
    do
    {
        if (*p == '"')
        {
            InQuotes = !InQuotes;
            c = *p++;
            continue;
        }

        // Copy character into argument:
        Buffer.push_back(*p);

        c = *p++;
    } while (c != '\0' && (InQuotes || (c != ' ' && c != '\t')));

    if (c == '\0')
    {
        p--;
    }
    else
    {
        Buffer.resize(Buffer.size() - 1);
    }

    // Save te argument.
    SplitArguments.push_back(Buffer);

    InQuotes = false;

    // Loop on each argument
    for (;;)
    {
        if (*p)
        {
            while (*p == ' ' || *p == '\t')
                ++p;
        }

        // End of arguments
        if (*p == '\0')
            break;

        // Initialize the argument buffer.
        Buffer.clear();

        // Loop through scanning one argument:
        for (;;)
        {
            copy_character = 1;

            // Rules: 2N backslashes + " ==> N backslashes and begin/end quote
            // 2N + 1 backslashes + " ==> N backslashes + literal " N
            // backslashes ==> N backslashes
            numslash = 0;

            while (*p == '\\')
            {
                // Count number of backslashes for use below
                ++p;
                ++numslash;
            }

            if (*p == '"')
            {
                // if 2N backslashes before, start/end quote, otherwise copy
                // literally:
                if (numslash % 2 == 0)
                {
                    if (InQuotes && p[1] == '"')
                    {
                        p++; // Double quote inside quoted string
                    }
                    else
                    {
                        // Skip first quote char and copy second:
                        copy_character = 0; // Don't copy quote
                        InQuotes = !InQuotes;
                    }
                }

                numslash /= 2;
            }

            // Copy slashes:
            while (numslash--)
            {
                Buffer.push_back(L'\\');
            }

            // If at end of arg, break loop:
            if (*p == '\0' || (!InQuotes && (*p == ' ' || *p == '\t')))
                break;

            // Copy character into argument:
            if (copy_character)
            {
                Buffer.push_back(*p);
            }

            ++p;
        }

        // Save te argument.
        SplitArguments.push_back(Buffer);
    }

    return SplitArguments;
}

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
    std::wstring& UnresolvedCommandLine)
{
    ApplicationName.clear();
    OptionsAndParameters.clear();
    UnresolvedCommandLine.clear();

    size_t arg_size = 0;
    for (auto& SplitArgument : M2SpiltCommandLine(CommandLine))
    {
        // We need to process the application name at the beginning.
        if (ApplicationName.empty())
        {
            // For getting the unresolved command line, we need to cumulate
            // length which including spaces.
            arg_size += SplitArgument.size() + 1;

            // Save
            ApplicationName = SplitArgument;
        }
        else
        {
            bool IsOption = false;
            size_t OptionPrefixLength = 0;

            for (auto& OptionPrefix : OptionPrefixes)
            {
                if (0 == _wcsnicmp(
                    SplitArgument.c_str(),
                    OptionPrefix.c_str(),
                    OptionPrefix.size()))
                {
                    IsOption = true;
                    OptionPrefixLength = OptionPrefix.size();
                }
            }

            if (IsOption)
            {
                // For getting the unresolved command line, we need to cumulate
                // length which including spaces.
                arg_size += SplitArgument.size() + 1;

                // Get the option name and parameter.

                wchar_t* OptionStart = &SplitArgument[0] + OptionPrefixLength;
                wchar_t* ParameterStart = nullptr;

                for (auto& OptionParameterSeparator
                    : OptionParameterSeparators)
                {
                    wchar_t* Result = wcsstr(
                        OptionStart,
                        OptionParameterSeparator.c_str());
                    if (nullptr == Result)
                    {
                        continue;
                    }

                    Result[0] = L'\0';
                    ParameterStart = Result + OptionParameterSeparator.size();

                    break;
                }

                // Save
                OptionsAndParameters[(OptionStart ? OptionStart : L"")] =
                    (ParameterStart ? ParameterStart : L"");
            }
            else
            {
                // Get the approximate location of the unresolved command line.
                // We use "(arg_size - 1)" to ensure that the program path
                // without quotes can also correctly parse.
                wchar_t* search_start =
                    const_cast<wchar_t*>(CommandLine.c_str()) + (arg_size - 1);

                // Get the unresolved command line. Search for the beginning of
                // the first parameter delimiter called space and exclude the
                // first space by adding 1 to the result.
                wchar_t* command = wcsstr(search_start, L" ") + 1;

                // Omit the space. (Thanks to wzzw.)
                while (command && *command == L' ')
                {
                    ++command;
                }

                // Save
                if (command)
                {
                    UnresolvedCommandLine = command;
                }

                break;
            }
        }
    }
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
    bool IgnoreCase)
{
    return (::FindNLSStringEx(
        nullptr,
        (IgnoreCase ? NORM_IGNORECASE : 0) | FIND_FROMSTART,
        SourceString.c_str(),
        SourceString.size(),
        SubString.c_str(),
        SubString.size(),
        nullptr,
        nullptr,
        nullptr,
        0) >= 0);
}

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
    uint64_t ByteSize)
{
    const wchar_t* Systems[] =
    {
        L"Byte",
        L"Bytes",
        L"KiB",
        L"MiB",
        L"GiB",
        L"TiB",
        L"PiB",
        L"EiB"
    };

    size_t nSystem = 0;
    double result = static_cast<double>(ByteSize);

    if (ByteSize > 1)
    {
        for (
            nSystem = 1;
            nSystem < sizeof(Systems) / sizeof(*Systems);
            ++nSystem)
        {
            if (1024.0 > result)
                break;

            result /= 1024.0;
        }

        result = static_cast<uint64_t>(result * 100) / 100.0;
    }

    return winrt::to_hstring(result) + L" " + Systems[nSystem];
}

#endif

#ifdef __cplusplus_winrt

/**
 * Converts from the C++/CX string to the UTF-16 string.
 *
 * @param PlatformString The C++/CX string you want to convert.
 * @return The return value is the UTF-16 string.
 */
std::wstring M2MakeUTF16String(Platform::String^ PlatformString)
{
    return std::wstring(PlatformString->Data(), PlatformString->Length());
}

/**
 * Converts from the C++/CX string to the UTF-8 string.
 *
 * @param PlatformString The C++/CX string you want to convert.
 * @return The return value is the UTF-8 string.
 */
std::string M2MakeUTF8String(Platform::String^ PlatformString)
{
    std::string UTF8String;

    int UTF8StringLength = WideCharToMultiByte(
        CP_UTF8,
        0,
        PlatformString->Data(),
        static_cast<int>(PlatformString->Length()),
        nullptr,
        0,
        nullptr,
        nullptr);
    if (UTF8StringLength > 0)
    {
        UTF8String.resize(UTF8StringLength);
        WideCharToMultiByte(
            CP_UTF8,
            0,
            PlatformString->Data(),
            static_cast<int>(PlatformString->Length()),
            &UTF8String[0],
            UTF8StringLength,
            nullptr,
            nullptr);
    }

    return UTF8String;
}

/**
 * Converts from the UTF-8 string to the C++/CX string.
 *
 * @param UTF16String The UTF-16 string you want to convert.
 * @return The return value is the C++/CX string.
 */
Platform::String^ M2MakeCXString(const std::wstring& UTF16String)
{
    return ref new Platform::String(
        UTF16String.c_str(), static_cast<unsigned int>(UTF16String.size()));
}

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
    bool IgnoreCase)
{
    return (::FindNLSStringEx(
        nullptr,
        (IgnoreCase ? NORM_IGNORECASE : 0) | FIND_FROMSTART,
        SourceString->Data(),
        SourceString->Length(),
        SubString->Data(),
        SubString->Length(),
        nullptr,
        nullptr,
        nullptr,
        0) >= 0);
}

/**
 * Converts a numeric value into a string that represents the number expressed
 * as a size value in byte, bytes, kibibytes, mebibytes, gibibytes, tebibytes,
 * pebibytes or exbibytes, depending on the size.
 *
 * @param ByteSize The numeric byte size value to be converted.
 * @return Returns a Platform::String object which represents the converted
 *         string.
 */
Platform::String^ M2ConvertByteSizeToString(uint64 ByteSize)
{
    double result = static_cast<double>(ByteSize);

    if (0.0 == result)
    {
        return L"0 Byte";
    }

    const wchar_t* Systems[] =
    {
        L"Bytes",
        L"KiB",
        L"MiB",
        L"GiB",
        L"TiB",
        L"PiB",
        L"EiB"
    };

    size_t nSystem = 0;
    for (; nSystem < sizeof(Systems) / sizeof(*Systems); ++nSystem)
    {
        if (1024.0 > result)
            break;

        result /= 1024.0;
    }

    Platform::String^ ByteSizeString =
        (static_cast<uint64>(result * 100) / 100.0).ToString();

    return ByteSizeString + Platform::StringReference(Systems[nSystem]);
}

#endif

#pragma endregion

#pragma region AccessToken

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
    _In_ DWORD DesiredAccess)
{
    *TokenHandle = INVALID_HANDLE_VALUE;

    if (!TokenSource)
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

    switch (TokenSource->Type)
    {
    case M2_PROCESS_TOKEN_SOURCE_TYPE::Current:
        ProcessHandle = GetCurrentProcess();
        break;
    case M2_PROCESS_TOKEN_SOURCE_TYPE::Handle:
        ProcessHandle = TokenSource->ProcessHandle;
        break;
    case M2_PROCESS_TOKEN_SOURCE_TYPE::ProcessId:
        ProcessHandle = OpenProcess(
            MAXIMUM_ALLOWED, FALSE, TokenSource->ProcessId);
        if (!ProcessHandle)
            return M2GetLastHResultError();
        break;
    default:
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);
    }

    if (OpenProcessToken(ProcessHandle, DesiredAccess, TokenHandle))
        return S_OK;

    return M2GetLastHResultError();
}

#pragma endregion

#pragma region COM

#ifdef CPPWINRT_VERSION

/**
 * Creates a GUID, a unique 128-bit integer used for CLSIDs and interface
 * identifiers.
 *
 * @return The function will return GUID struct.
 */
GUID M2CreateGuid()
{
    GUID guid = { 0 };
    winrt::check_hresult(CoCreateGuid(&guid));
    return guid;
}

#endif

#ifdef __cplusplus_winrt

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
byte* M2GetPointer(Windows::Storage::Streams::IBuffer^ Buffer)
{
    byte* pBuffer = nullptr;
    Windows::Storage::Streams::IBufferByteAccess* pBufferByteAccess = nullptr;
    IInspectable* pBufferABIObject = M2GetInspectable(Buffer);
    if (SUCCEEDED(pBufferABIObject->QueryInterface(&pBufferByteAccess)))
    {
        pBufferByteAccess->Buffer(&pBuffer);
        pBufferByteAccess->Release();
    }

    return pBuffer;
}

class BufferReference : public RuntimeClass<
    RuntimeClassFlags<RuntimeClassType::WinRtClassicComMix>,
    ABI::Windows::Storage::Streams::IBuffer,
    Windows::Storage::Streams::IBufferByteAccess>
{
private:
    UINT32 m_Capacity;
    UINT32 m_Length;
    byte* m_Pointer;

public:
    virtual ~BufferReference()
    {
    }

    STDMETHODIMP RuntimeClassInitialize(
        byte* Pointer, UINT32 Capacity)
    {
        m_Capacity = Capacity;
        m_Length = Capacity;
        m_Pointer = Pointer;
        return S_OK;
    }

    // IBufferByteAccess::Buffer
    STDMETHODIMP Buffer(byte** value)
    {
        *value = m_Pointer;
        return S_OK;
    }

    // IBuffer::get_Capacity
    STDMETHODIMP get_Capacity(UINT32* value)
    {
        *value = m_Capacity;
        return S_OK;
    }

    // IBuffer::get_Length
    STDMETHODIMP get_Length(UINT32* value)
    {
        *value = m_Length;
        return S_OK;
    }

    // IBuffer::put_Length
    STDMETHODIMP put_Length(UINT32 value)
    {
        if (value > m_Capacity)
            return E_INVALIDARG;
        m_Length = value;
        return S_OK;
    }
};

// Retrieves the IBuffer object from the provided raw pointer.
// Parameters:
//   Pointer: The raw pointer you want to retrieve the IBuffer object.
//   Capacity: The size of raw pointer you want to retrieve the IBuffer object.
// Return value:
//   If the function succeeds, the return value is the IBuffer object from the 
//   provided raw pointer. If the function fails, the return value is nullptr.
// Warning: 
//   The lifetime of the returned IBuffer object is controlled by the lifetime 
//   of the raw pointer that's passed to this method. When the raw pointer has 
//   been released, the IBuffer object becomes invalid and must not be used.
Windows::Storage::Streams::IBuffer^ M2MakeIBuffer(
    byte* Pointer,
    UINT32 Capacity)
{
    using Windows::Storage::Streams::IBuffer;

    IBuffer^ buffer = nullptr;

    ComPtr<BufferReference> bufferReference;
    if (SUCCEEDED(MakeAndInitialize<BufferReference>(
        &bufferReference, Pointer, Capacity)))
    {
        buffer = reinterpret_cast<IBuffer^>(bufferReference.Get());
    }

    return buffer;
}

/**
 * Creates a GUID, a unique 128-bit integer used for CLSIDs and interface
 * identifiers.
 *
 * @return The function will return Platform::Guid object.
 */
Platform::Guid M2CreateGuid()
{
    GUID guid = { 0 };
    M2ThrowPlatformExceptionIfFailed(CoCreateGuid(&guid));
    return Platform::Guid(guid);
}

#endif

#pragma endregion

#pragma region Module

/**
 * Retrieves the path of the executable file of the current process.
 *
 * @return If the function succeeds, the return value is the path of the
 *         executable file of the current process. If the function fails, the
 *         return value is an empty string.
 */
std::wstring M2GetCurrentProcessModulePath()
{
    std::wstring result(MAX_PATH, L'\0');
    GetModuleFileNameW(nullptr, &result[0], (DWORD)(result.capacity()));
    result.resize(wcslen(result.c_str()));
    return result;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

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
    _In_ LPCWSTR lpName)
{
    if (!lpResourceInfo)
        return E_INVALIDARG;

    lpResourceInfo->Size = 0;
    lpResourceInfo->Pointer = nullptr;

    HRSRC ResourceFind = FindResourceExW(
        hModule, lpType, lpName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    if (!ResourceFind)
        return M2GetLastHResultError();

    lpResourceInfo->Size = SizeofResource(hModule, ResourceFind);

    HGLOBAL ResourceLoad = LoadResource(hModule, ResourceFind);
    if (!ResourceLoad)
        return M2GetLastHResultError();

    lpResourceInfo->Pointer = LockResource(ResourceLoad);

    return S_OK;
}

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
    _In_ DWORD Flags)
{
    HRESULT hr = M2LoadLibrary(ModuleHandle, LibraryFileName, nullptr, Flags);
    if (FAILED(hr))
    {
        if ((Flags & LOAD_LIBRARY_SEARCH_SYSTEM32) &&
            (hr == __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER)))
        {
            // In the Windows API (with some exceptions discussed in the
            // following paragraphs), the maximum length for a path is
            // MAX_PATH, which is defined as 260 characters. A local path is
            // structured in the following order: drive letter, colon,
            // backslash, name components separated by backslashes, and a
            // terminating null character. For example, the maximum path on
            // drive D is "D:\some 256-character path string" where ""
            // represents the invisible terminating null character for the
            // current system codepage.
            // MAX_PATH = 260 = wcslen(L"D:\some 256-character path string")
            // wcslen(L"C:\\Windows\\System32") = 19
            // BufferSize = 19 + 256 + 1 = 276
            // P.S. In the most cases, I don't think the length "System32" path
            // string will bigger than 19.
            const size_t BufferLength = 276;
            wchar_t Buffer[BufferLength];
            if (!wcschr(LibraryFileName, L'\\'))
            {
                if (0 == GetSystemDirectoryW(
                    Buffer,
                    static_cast<UINT>(BufferLength)))
                {
                    hr = M2GetLastHResultError();
                }
                else
                {
                    hr = StringCbCatW(Buffer, BufferLength, LibraryFileName);
                    if (SUCCEEDED(hr))
                    {
                        hr = M2LoadLibrary(
                            ModuleHandle, Buffer, nullptr, Flags);
                    }
                }
            }
        }
    }

    return hr;
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
    _Out_ LPSERVICE_STATUS_PROCESS lpServiceStatus)
{
    memset(lpServiceStatus, 0, sizeof(LPSERVICE_STATUS_PROCESS));

    M2::CServiceHandle hSCM;
    M2::CServiceHandle hService;

    DWORD nBytesNeeded = 0;
    DWORD nOldCheckPoint = 0;
    ULONGLONG nLastTick = 0;
    bool bStartServiceWCalled = false;

    hSCM = OpenSCManagerW(
        nullptr,
        nullptr,
        SC_MANAGER_CONNECT);
    if (!hSCM)
        return M2GetLastHResultError();

    hService = OpenServiceW(
        hSCM,
        lpServiceName,
        SERVICE_QUERY_STATUS | SERVICE_START);
    if (!hService)
        return M2GetLastHResultError();

    while (QueryServiceStatusEx(
        hService,
        SC_STATUS_PROCESS_INFO,
        reinterpret_cast<LPBYTE>(lpServiceStatus),
        sizeof(SERVICE_STATUS_PROCESS),
        &nBytesNeeded))
    {
        if (SERVICE_STOPPED == lpServiceStatus->dwCurrentState)
        {
            // Failed if the service had stopped again.
            if (bStartServiceWCalled)
                return E_FAIL;

            if (!StartServiceW(hService, 0, nullptr))
                return M2GetLastHResultError();

            bStartServiceWCalled = true;
        }
        else if (
            SERVICE_STOP_PENDING == lpServiceStatus->dwCurrentState ||
            SERVICE_START_PENDING == lpServiceStatus->dwCurrentState)
        {
            ULONGLONG nCurrentTick = GetTickCount64();

            if (!nLastTick)
            {
                nLastTick = nCurrentTick;
                nOldCheckPoint = lpServiceStatus->dwCheckPoint;

                // Same as the .Net System.ServiceProcess, wait 250ms.
                SleepEx(250, FALSE);
            }
            else
            {
                // Check the timeout if the checkpoint is not increased.
                if (lpServiceStatus->dwCheckPoint <= nOldCheckPoint)
                {
                    ULONGLONG nDiff = nCurrentTick - nLastTick;
                    if (nDiff > lpServiceStatus->dwWaitHint)
                    {
                        return __HRESULT_FROM_WIN32(ERROR_TIMEOUT);
                    }
                }

                // Continue looping.
                nLastTick = 0;
            }
        }
        else
        {
            break;
        }
    }

    return S_OK;
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
    const std::wstring& VariableName)
{
    HRESULT hr = S_OK;

    do
    {
        DWORD Length = ExpandEnvironmentStringsW(
            VariableName.c_str(),
            nullptr,
            0);
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }

        ExpandedString.resize(Length - 1);

        Length = ExpandEnvironmentStringsW(
            VariableName.c_str(),
            &ExpandedString[0],
            static_cast<DWORD>(ExpandedString.size() + 1));
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }
        if (ExpandedString.size() != Length - 1)
        {
            hr = E_UNEXPECTED;
            break;
        }

    } while (false);

    if (FAILED(hr))
    {
        ExpandedString.clear();
    }

    return hr;
}

/**
 * Retrieves the path of the system directory.
 *
 * @param SystemFolderPath The string of the path of the system directory.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetSystemDirectory(
    std::wstring& SystemFolderPath)
{
    HRESULT hr = S_OK;

    do
    {
        UINT Length = GetSystemDirectoryW(
            nullptr,
            0);
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }

        SystemFolderPath.resize(Length - 1);

        Length = GetSystemDirectoryW(
            &SystemFolderPath[0],
            static_cast<UINT>(Length));
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }
        if (SystemFolderPath.size() != Length)
        {
            hr = E_UNEXPECTED;
            break;
        }

    } while (false);

    if (FAILED(hr))
    {
        SystemFolderPath.clear();
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Retrieves the path of the shared Windows directory on a multi-user system.
 *
 * @param WindowsFolderPath The string of the path of the shared Windows
 *                          directory on a multi-user system.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetWindowsDirectory(
    std::wstring& WindowsFolderPath)
{
    HRESULT hr = S_OK;

    do
    {
        UINT Length = GetSystemWindowsDirectoryW(
            nullptr,
            0);
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }

        WindowsFolderPath.resize(Length - 1);

        Length = GetSystemWindowsDirectoryW(
            &WindowsFolderPath[0],
            static_cast<UINT>(Length));
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }
        if (WindowsFolderPath.size() != Length)
        {
            hr = E_UNEXPECTED;
            break;
        }

    } while (false);

    if (FAILED(hr))
    {
        WindowsFolderPath.clear();
    }

    return hr;
}

/**
 * Enables the Per-Monitor DPI Aware for the specified dialog using the
 * internal API from Windows.
 *
 * @return INT. If failed. returns -1.
 * @remarks You need to use this function in Windows 10 Threshold 1 or Windows
 *          10 Threshold 2.
 */
INT M2EnablePerMonitorDialogScaling()
{
    // Fix for Windows Vista and Server 2008.
    if (!IsWindowsVersionOrGreater(10, 0, 0)) return -1;

    typedef INT(WINAPI * PFN_EnablePerMonitorDialogScaling)();

    HMODULE hModule = nullptr;
    PFN_EnablePerMonitorDialogScaling pFunc = nullptr;

    hModule = GetModuleHandleW(L"user32.dll");
    if (!hModule) return -1;

    if (FAILED(M2GetProcAddress(
        reinterpret_cast<FARPROC*>(&pFunc),
        hModule,
        reinterpret_cast<LPCSTR>(2577))))
        return -1;

    return pFunc();
}

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
 * @remark For more information, see GetDpiForMonitor.
 */
HRESULT M2GetDpiForMonitor(
    _In_ HMONITOR hmonitor,
    _In_ MONITOR_DPI_TYPE dpiType,
    _Out_ UINT* dpiX,
    _Out_ UINT* dpiY)
{
    HMODULE hModule = nullptr;
    HRESULT hr = M2LoadLibraryEx(
        &hModule,
        L"SHCore.dll",
        LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (SUCCEEDED(hr))
    {
        decltype(GetDpiForMonitor)* pFunc = nullptr;
        hr = M2GetProcAddress(
            reinterpret_cast<FARPROC*>(&pFunc),
            hModule,
            "GetDpiForMonitor");
        if (SUCCEEDED(hr))
        {
            hr = pFunc(hmonitor, dpiType, dpiX, dpiY);
        }

        FreeLibrary(hModule);
    }

    return hr;
}

#endif

#pragma endregion

#pragma region WinRT

#ifdef CPPWINRT_VERSION

/**
 * Execute function on the UI thread with normal priority.
 *
 * @param agileCallback The function you want to execute.
 * @return The return value is Windows::Foundation::IAsyncAction^.
 */
winrt::IAsyncAction M2ExecuteOnUIThread(
    winrt::DispatchedHandler const& agileCallback)
{
    using winrt::Windows::ApplicationModel::Core::CoreApplication;
    using winrt::Windows::UI::Core::CoreDispatcherPriority;

    return CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(
        CoreDispatcherPriority::Normal, agileCallback);
}

namespace M2
{
    void NotifyPropertyChangedBase::RaisePropertyChanged(
        std::wstring_view const& PropertyName)
    {
        this->m_PropertyChanged(
            *this, winrt::PropertyChangedEventArgs(PropertyName));
    }

    winrt::event_token NotifyPropertyChangedBase::PropertyChanged(
        winrt::PropertyChangedEventHandler const& value)
    {
        return this->m_PropertyChanged.add(value);
    }

    void NotifyPropertyChangedBase::PropertyChanged(
        winrt::event_token const& token)
    {
        this->m_PropertyChanged.remove(token);
    }
}

#endif

#ifdef __cplusplus_winrt

/**
 * Handle the completed asynchronous call.
 *
 * @param Async The completed asynchronous call you want to handle.
 * @return Return the HRESULT determined by the asynchronous call.
 */
HRESULT M2AsyncHandleCompleted(Platform::Object^ Async)
{
    HRESULT hr = S_OK;
    ABI::Windows::Foundation::IAsyncInfo* asyncInfo = nullptr;

    hr = M2GetInspectable(Async)->QueryInterface(&asyncInfo);
    if (SUCCEEDED(hr))
    {
        // Get the error code.
        AsyncStatus asyncStatus;
        hr = asyncInfo->get_Status(&asyncStatus);
        if (SUCCEEDED(hr))
        {
            if (AsyncStatus::Completed == asyncStatus)
            {
                // Just return S_OK if succeeded.
                hr = S_OK;
            }
            else if (AsyncStatus::Started == asyncStatus)
            {
                // Cancel the asynchronous call and return error code if 
                // the status is still Started, the timeout interval has
                // been elapsed.
                hr = asyncInfo->Cancel();
                if (SUCCEEDED(hr)) hr = __HRESULT_FROM_WIN32(ERROR_TIMEOUT);
            }
            else if (AsyncStatus::Canceled == asyncStatus)
            {
                // If the status is Cancelled, return the error code.
                hr = E_ABORT;
            }
            else
            {
                HRESULT hrTemp;

                // If the status is other value, return the error code.	
                hr = asyncInfo->get_ErrorCode(&hrTemp);
                if (SUCCEEDED(hr)) hr = hrTemp;
            }
        }

        asyncInfo->Release();
    }

    return hr;
}

/**
 * Execute function on the UI thread with normal priority.
 *
 * @param agileCallback The function you want to execute.
 * @return The return value is Windows::Foundation::IAsyncAction^.
 */
Windows::Foundation::IAsyncAction^ M2ExecuteOnUIThread(
    Windows::UI::Core::DispatchedHandler^ agileCallback)
{
    using Windows::ApplicationModel::Core::CoreApplication;
    using Windows::UI::Core::CoreDispatcherPriority;

    return CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
        CoreDispatcherPriority::Normal, agileCallback);
}

#endif

#pragma endregion

#endif // _M2_WINDOWS_HELPERS_
