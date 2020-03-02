/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsDownlevelHelpers.h
 * PURPOSE:   Definition for the Windows downlevel helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef _M2_WINDOWS_DOWNLEVEL_HELPERS_
#define _M2_WINDOWS_DOWNLEVEL_HELPERS_

#include <Mile.Windows.h>

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
    _In_ BOOL IsLastFunctionCallSucceeded = FALSE,
    _In_ BOOL UseLastErrorWhenSucceeded = FALSE);

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @param KnownFailed Set this parameter TRUE if you can be sure that the last
 *                    call was failed, Otherwise, set this parameter FALSE.
 * @param LastErrorCode A pointer to a variable that returns the calling
 *                      thread's last-error code. This parameter can be NULL.
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastHResultError(
    _In_ BOOL IsLastFunctionCallSucceeded = FALSE,
    _In_ BOOL UseLastErrorWhenSucceeded = FALSE);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates or opens a file or I/O device. The most commonly used I/O devices
 * are as follows: file, file stream, directory, physical disk, volume, console
 * buffer, tape drive, communications resource, mailslot, and pipe. The
 * function returns a handle that can be used to access the file or device for
 * various types of I/O depending on the file or device and the flags and
 * attributes specified.
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
    _In_opt_ HANDLE hTemplateFile);

#endif

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
    _In_ HMODULE hLibModule);

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
    _Inout_opt_ LPOVERLAPPED lpOverlapped);

#endif

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

#endif // !_M2_WINDOWS_DOWNLEVEL_HELPERS_
