/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.h
 * PURPOSE:   Definition for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS
#define MILE_WINDOWS

#include "Mile.Windows.Core.h"

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#include <ShellScalingApi.h>
#endif

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
EXTERN_C HRESULT WINAPI MileAdjustTokenPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ BOOL DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ DWORD BufferLength,
    _Out_opt_ PTOKEN_PRIVILEGES PreviousState,
    _Out_opt_ PDWORD ReturnLength);

/**
 * Enables or disables privileges in the specified access token.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token.
 * @param Privileges A pointer to an array of LUID_AND_ATTRIBUTES structures
 *                   that specifies an array of privileges and their
 *                   attributes. Each structure contains the LUID and
 *                   attributes of a privilege. To get the name of the
 *                   privilege associated with a LUID, call the
 *                   MileGetPrivilegeValue function, passing the address of the
 *                   LUID as the value of the lpLuid parameter. The attributes
 *                   of a privilege can be a combination of the following
 *                   values.
 *                   SE_PRIVILEGE_ENABLED
 *                       The function enables the privilege.
 *                   SE_PRIVILEGE_REMOVED
 *                       The privilege is removed from the list of privileges
 *                       in the token.
 *                   None
 *                       The function disables the privilege.
 * @param PrivilegeCount The number of entries in the Privileges array.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see AdjustTokenPrivileges.
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenPrivilegesSimple(
    _In_ HANDLE TokenHandle,
    _In_ PLUID_AND_ATTRIBUTES Privileges,
    _In_ DWORD PrivilegeCount);

/**
 * Enables or disables all privileges in the specified access token.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token.
 * @param Attributes The attributes of all privileges can be a combination of
 *                   the following values.
 *                   SE_PRIVILEGE_ENABLED
 *                       The function enables the privilege.
 *                   SE_PRIVILEGE_REMOVED
 *                       The privilege is removed from the list of privileges
 *                       in the token.
 *                   None
 *                       The function disables the privilege.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenAllPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ DWORD Attributes);

/**
 * Retrieves the locally unique identifier (LUID) used on the local system to
 * locally represent the specified privilege name.
 *
 * @param Name A pointer to a null-terminated string that specifies the name of
 *             the privilege, as defined in the Winnt.h header file. For
 *             example, this parameter could specify the constant,
 *             SE_SECURITY_NAME, or its corresponding string,
 *             "SeSecurityPrivilege".
 * @param Value A pointer to a variable that receives the LUID by which the
 *              privilege is known on the local system.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see LookupPrivilegeValue.
 */
EXTERN_C HRESULT WINAPI MileGetPrivilegeValue(
    _In_ LPCWSTR Name,
    _Out_ PLUID Value);

/**
 * Assigns an impersonation token to a thread. The function can also cause a
 * thread to stop using an impersonation token.
 *
 * @param TokenHandle A handle to the impersonation token to assign to the
 *                    thread. If TokenHandle is NULL, the function causes the
 *                    thread to stop using an impersonation token.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see SetThreadToken.
 */
EXTERN_C HRESULT WINAPI MileSetCurrentThreadToken(
    _In_opt_ HANDLE TokenHandle);

/**
 * Opens an existing local process object.
 *
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param InheritHandle If this value is TRUE, processes created by this
 *                      process will inherit the handle. Otherwise, the
 *                      processes do not inherit this handle.
 * @param ProcessId The identifier of the local process to be opened.
 * @param ProcessHandle A pointer to an open handle to the specified process.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenProcess.
 */
EXTERN_C HRESULT WINAPI MileOpenProcess(
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ DWORD ProcessId,
    _Out_opt_ PHANDLE ProcessHandle);

/**
 * Opens the access token associated with a process.
 *
 * @param ProcessHandle A handle to the process whose access token is opened.
 *                      The process must have the PROCESS_QUERY_INFORMATION
 *                      access permission.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C HRESULT WINAPI MileOpenProcessToken(
    _In_ HANDLE ProcessHandle,
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Opens an existing local process object associated with a service process,
 * the calling application must be running within the context of the
 * Administrator account and have the SE_DEBUG_NAME privilege enabled.
 *
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param InheritHandle If this value is TRUE, processes created by this
 *                      process will inherit the handle. Otherwise, the
 *                      processes do not inherit this handle.
 * @param ServiceName The name of the service to be started. This is the name
 *                    specified by the ServiceName parameter of the
 *                    CreateService function when the service object was
 *                    created, not the service display name that is shown by
 *                    user interface applications to identify the service. The
 *                    maximum string length is 256 characters. The service
 *                    control manager database preserves the case of the
 *                    characters, but service name comparisons are always case
 *                    insensitive. Forward-slash (/) and backslash (\) are
 *                    invalid service name characters.
 * @param ProcessHandle A pointer to an open handle to the specified process.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenProcess.
 */
EXTERN_C HRESULT WINAPI MileOpenServiceProcess(
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ LPCWSTR ServiceName,
    _Out_ PHANDLE ProcessHandle);

#endif

/**
 * Opens the access token associated with the current process.
 *
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C HRESULT WINAPI MileOpenCurrentProcessToken(
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle);

/**
 * Opens the access token associated with a process.
 *
 * @param ProcessId The identifier of the local process to be opened.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C HRESULT WINAPI MileOpenProcessTokenByProcessId(
    _In_ DWORD ProcessId,
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Opens the access token associated with a service process, the calling
 * application must be running within the context of the Administrator account
 * and have the SE_DEBUG_NAME privilege enabled.
 *
 * @param ServiceName The name of the service to be started. This is the name
 *                    specified by the ServiceName parameter of the
 *                    CreateService function when the service object was
 *                    created, not the service display name that is shown by
 *                    user interface applications to identify the service.
 *                    The maximum string length is 256 characters. The service
 *                    control manager database preserves the case of the
 *                    characters, but service name comparisons are always case
 *                    insensitive. Forward-slash (/) and backslash (\) are
 *                    invalid service name characters.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C HRESULT WINAPI MileOpenServiceProcessToken(
    _In_ LPCWSTR ServiceName,
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle);

#endif

#endif // !MILE_WINDOWS
