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
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the
 *                              function retrieves.
 * @param TokenInformation A pointer to a buffer the function fills with the
 *                         requested information.
 * @param TokenInformationLength Specifies the size, in bytes, of the buffer
 *                               pointed to by the TokenInformation parameter.
 * @param ReturnLength A pointer to a variable that receives the number of
 *                     bytes needed for the buffer pointed to by the
 *                     TokenInformation parameter.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
EXTERN_C HRESULT WINAPI MileGetTokenInformation(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_opt_ LPVOID TokenInformation,
    _In_ DWORD TokenInformationLength,
    _Out_ PDWORD ReturnLength);

/**
 * Sets various types of information for a specified access token. The
 * information that this function sets replaces existing information. The
 * calling process must have appropriate access rights to set the information.
 *
 * @param TokenHandle A handle to the access token for which information is to
 *                    be set.
 * @param TokenInformationClass A value from the TOKEN_INFORMATION_CLASS
 *                              enumerated type that identifies the type of
 *                              information the function sets. The valid values
 *                              from TOKEN_INFORMATION_CLASS are described in
 *                              the TokenInformation parameter.
 * @param TokenInformation A pointer to a buffer that contains the information
 *                         set in the access token.
 * @param TokenInformationLength Specifies the length, in bytes, of the buffer
 *                               pointed to by TokenInformation.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see SetTokenInformation.
 */
EXTERN_C HRESULT WINAPI MileSetTokenInformation(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _In_ LPVOID TokenInformation,
    _In_ DWORD TokenInformationLength);

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
 * @param OutputInformation A pointer to a buffer the function fills with the
 *                          requested information. When you have finished using
 *                          the information, free it by calling the
 *                          MileFreeMemory function. You should also set the
 *                          pointer to nullptr.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
EXTERN_C HRESULT WINAPI MileGetTokenInformationWithMemory(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_ PVOID* OutputInformation);

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

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Obtains the primary access token of the logged-on user specified by the
 * session ID. To call this function successfully, the calling application must
 * be running within the context of the LocalSystem account and have the
 * SE_TCB_NAME privilege.
 *
 * @param SessionId A Remote Desktop Services session identifier.
 * @param TokenHandle If the function succeeds, receives a pointer to the token
 *                    handle for the logged-on user. Note that you must call
 *                    the CloseHandle function to close this handle.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see WTSQueryUserToken.
 */
EXTERN_C HRESULT WINAPI MileCreateSessionToken(
    _In_ DWORD SessionId,
    _Out_ PHANDLE TokenHandle);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Gets the identifier of the Local Security Authority process.
 *
 * @param ProcessId The identifier of the Local Security Authority process.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileGetLsassProcessId(
    _Out_ PDWORD ProcessId);

#endif

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
 * Creates a new access token that duplicates an existing token. This function
 * can create either a primary token or an impersonation token.
 *
 * @param ExistingTokenHandle A handle to an access token opened with
 *                            TOKEN_DUPLICATE access.
 * @param DesiredAccess Specifies the requested access rights for the new
 *                      token. To request all access rights that are valid for
 *                      the caller, specify MAXIMUM_ALLOWED.
 * @param TokenAttributes A pointer to a SECURITY_ATTRIBUTES structure that
 *                        specifies a security descriptor for the new token and
 *                        determines whether child processes can inherit the
 *                        token.
 * @param ImpersonationLevel Specifies a value from the
 *                           SECURITY_IMPERSONATION_LEVEL enumeration that
 *                           indicates the impersonation level of the new
 *                           token.
 * @param TokenType Specifies one of the following values from the TOKEN_TYPE
 *                  enumeration.
 *                  TokenPrimary
 *                      The new token is a primary token that you can use in
 *                      the CreateProcessAsUser function.
 *                  TokenImpersonation
 *                      The new token is an impersonation token.
 * @param NewTokenHandle A pointer to a handle variable that receives the new
 *                       token.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see DuplicateTokenEx.
 */
EXTERN_C HRESULT WINAPI MileDuplicateToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ DWORD DesiredAccess,
    _In_opt_ LPSECURITY_ATTRIBUTES TokenAttributes,
    _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
    _In_ TOKEN_TYPE TokenType,
    _Out_ PHANDLE NewTokenHandle);

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
 * Retrieves a pseudo handle for the current process.
 *
 * @return The return value is a pseudo handle to the current process.
 * @remark For more information, see GetCurrentProcess.
 */
EXTERN_C HANDLE WINAPI MileGetCurrentProcess();

/**
 * Opens an existing thread object.
 *
 * @param DesiredAccess The access to the thread object. This access right is
 *                      checked against the security descriptor for the thread.
 *                      This parameter can be one or more of the thread access
 *                      rights.
 * @param InheritHandle If this value is TRUE, processes created by this
 *                      process will inherit the handle. Otherwise, the
 *                      processes do not inherit this handle.
 * @param ThreadId The identifier of the thread to be opened.
 * @param ThreadHandle A pointer to an open handle to the specified thread.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenThread.
 */
EXTERN_C HRESULT WINAPI MileOpenThread(
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ DWORD ThreadId,
    _Out_opt_ PHANDLE ThreadHandle);

/**
 * Retrieves a pseudo handle for the calling thread.
 *
 * @return The return value is a pseudo handle for the current thread.
 * @remark For more information, see GetCurrentThread.
 */
EXTERN_C HANDLE WINAPI MileGetCurrentThread();

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

/**
 * Opens the access token associated with a thread.
 *
 * @param ThreadHandle A handle to the thread whose access token is opened.
 * @param DesiredAccess Specifies an access mask that specifies the requested
 *                      types of access to the access token. These requested
 *                      access types are reconciled against the token's
 *                      discretionary access control list (DACL) to determine
 *                      which accesses are granted or denied.
 * @param OpenAsSelf TRUE if the access check is to be made against the
 *                   process-level security context. FALSE if the access check
 *                   is to be made against the current security context of the
 *                   thread calling the MileOpenThreadToken function.
 * @param TokenHandle A pointer to a variable that receives the handle to the
 *                    newly opened access token.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenThreadToken.
 */
EXTERN_C HRESULT WINAPI MileOpenThreadToken(
    _In_ HANDLE ThreadHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf,
    _Out_ PHANDLE TokenHandle);

/**
 * Sets the priority class for the specified process. This value together with
 * the priority value of each thread of the process determines each thread's
 * base priority level.
 *
 * @param hProcess A handle to the process. The handle must have the
 *                 PROCESS_SET_INFORMATION access right.
 * @param dwPriorityClass The priority class for the process. This parameter
 *                        can be one of the following values.
 *                        ABOVE_NORMAL_PRIORITY_CLASS
 *                        BELOW_NORMAL_PRIORITY_CLASS
 *                        HIGH_PRIORITY_CLASS
 *                        IDLE_PRIORITY_CLASS
 *                        NORMAL_PRIORITY_CLASS
 *                        PROCESS_MODE_BACKGROUND_BEGIN
 *                        PROCESS_MODE_BACKGROUND_END
 *                        REALTIME_PRIORITY_CLASS
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see SetPriorityClass.
 */
EXTERN_C HRESULT WINAPI MileSetPriorityClass(
    _In_ HANDLE hProcess,
    _In_ DWORD dwPriorityClass);

/**
 * Sets mandatory label for a specified access token. The information that
 * this function sets replaces existing information. The calling process
 * must have appropriate access rights to set the information.
 *
 * @param TokenHandle A handle to the access token for which information is
 *                    to be set.
 * @param MandatoryLabelRid The value of the mandatory label for the process.
 *                          This parameter can be one of the following values.
 *                          SECURITY_MANDATORY_UNTRUSTED_RID
 *                          SECURITY_MANDATORY_LOW_RID
 *                          SECURITY_MANDATORY_MEDIUM_RID
 *                          SECURITY_MANDATORY_MEDIUM_PLUS_RID
 *                          SECURITY_MANDATORY_HIGH_RID
 *                          SECURITY_MANDATORY_SYSTEM_RID
 *                          SECURITY_MANDATORY_PROTECTED_PROCESS_RID
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileSetTokenMandatoryLabel(
    _In_ HANDLE TokenHandle,
    _In_ DWORD MandatoryLabelRid);

/**
 * Creates a new access token that is a LUA version of an existing access
 * token.
 *
 * @param ExistingTokenHandle A handle to a primary or impersonation token. The
 *                            token can also be a restricted token. The handle
 *                            must have TOKEN_DUPLICATE access to the token.
 * @param TokenHandle A pointer to a variable that receives a handle to the new
 *                    restricted token.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileCreateLUAToken(
    _In_ HANDLE ExistingTokenHandle,
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

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Opens an existing local process object associated with the Local Security
 * Authority process, the calling application must be running within the
 * context of the Administrator account and have the SE_DEBUG_NAME privilege
 * enabled.
 *
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param InheritHandle If this value is TRUE, processes created by this
 *                      process will inherit the handle. Otherwise, the
 *                      processes do not inherit this handle.
 * @param ProcessHandle A pointer to an open handle to the specified process.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenProcess.
 */
EXTERN_C HRESULT WINAPI MileOpenLsassProcess(
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
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

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Opens the access token associated with the Local Security Authority process,
 * the calling application must be running within the context of the
 * Administrator account and have the SE_DEBUG_NAME privilege enabled.
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
EXTERN_C HRESULT WINAPI MileOpenLsassProcessToken(
    _In_ DWORD DesiredAccess,
    _Out_ PHANDLE TokenHandle);

#endif

/**
 * Opens the access token associated with the current thread.
 *
 * @param DesiredAccess Specifies an access mask that specifies the requested
 *                      types of access to the access token. These requested
 *                      access types are reconciled against the token's
 *                      discretionary access control list (DACL) to determine
 *                      which accesses are granted or denied.
 * @param OpenAsSelf TRUE if the access check is to be made against the
 *                   process-level security context. FALSE if the access check
 *                   is to be made against the current security context of the
 *                   thread calling the OpenThreadToken function.
 * @param TokenHandle A pointer to a variable that receives the handle to the
 *                    newly opened access token.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenThreadToken.
 */
EXTERN_C HRESULT WINAPI MileOpenCurrentThreadToken(
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf,
    _Out_ PHANDLE TokenHandle);

/**
 * Opens the access token associated with a thread.
 *
 * @param ThreadId The identifier of the thread to be opened.
 * @param DesiredAccess Specifies an access mask that specifies the requested
 *                      types of access to the access token. These requested
 *                      access types are reconciled against the token's
 *                      discretionary access control list (DACL) to determine
 *                      which accesses are granted or denied.
 * @param OpenAsSelf TRUE if the access check is to be made against the
 *                   process-level security context. FALSE if the access check
 *                   is to be made against the current security context of the
 *                   thread calling the OpenThreadToken function.
 * @param TokenHandle A pointer to a variable that receives the handle to the
 *                    newly opened access token.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenThreadToken.
 */
EXTERN_C HRESULT WINAPI MileOpenThreadTokenByThreadId(
    _In_ DWORD ThreadId,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf,
    _Out_ PHANDLE TokenHandle);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates a new process and its primary thread. The new process runs in the
 * security context of the user represented by the specified token.
 *
 * @param hToken A handle to the primary token that represents a user.
 * @param lpApplicationName The name of the module to be executed.
 * @param lpCommandLine The command line to be executed. The maximum length of
 *                      this string is 32K characters. If lpApplicationName is
 *                      nullptr, the module name portion of lpCommandLine is
 *                      limited to MAX_PATH characters.
 * @param lpProcessAttributes A pointer to a SECURITY_ATTRIBUTES structure that
 *                            specifies a security descriptor for the new
 *                            process object and determines whether child
 *                            processes can inherit the returned handle to the
 *                            process.
 * @param lpThreadAttributes A pointer to a SECURITY_ATTRIBUTES structure that
 *                           specifies a security descriptor for the new thread
 *                           object and determines whether child processes can
 *                           inherit the returned handle to the thread.
 * @param bInheritHandles If this parameter is TRUE, each inheritable handle in
 *                        the calling process is inherited by the new process.
 *                        If the parameter is FALSE, the handles are not
 *                        inherited.
 * @param dwCreationFlags The flags that control the priority class and the
 *                        creation of the process. For a list of values, see
 *                        Process Creation Flags.
 * @param lpEnvironment A pointer to an environment block for the new process.
 * @param lpCurrentDirectory The full path to the current directory for the
 *                           process. The string can also specify a UNC path.
 * @param lpStartupInfo A pointer to a STARTUPINFO or STARTUPINFOEX structure.
 * @param lpProcessInformation A pointer to a PROCESS_INFORMATION structure
 *                             that receives identification information about
 *                             the new process.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateProcessAsUserW.
 */
EXTERN_C HRESULT WINAPI MileCreateProcessAsUser(
    _In_opt_ HANDLE hToken,
    _In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Returns the environment variables for the specified user. This block can
 * then be passed to MileCreateProcessAsUser().
 *
 * @param lpEnvironment Receives a pointer to the new environment block.
 * @param hToken Token for the user. If this parameter is nullptr, the returned
 *               environment block contains system variables only.
 * @param bInherit Inherit from the current process's environment block or
 *                 start from a clean state.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateEnvironmentBlock.
 */
EXTERN_C HRESULT WINAPI MileCreateEnvironmentBlock(
    _Outptr_ LPVOID* lpEnvironment,
    _In_opt_ HANDLE hToken,
    _In_ BOOL bInherit);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Frees environment variables created by the MileCreateEnvironmentBlock.
 *
 * @param lpEnvironment A pointer to the environment block.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see DestroyEnvironmentBlock.
 */
EXTERN_C HRESULT WINAPI MileDestroyEnvironmentBlock(
    _In_ LPVOID lpEnvironment);

#endif

/**
 * Suspends the specified thread.
 *
 * @param ThreadHandle A handle to the thread that is to be suspended.
 * @param PreviousSuspendCount The thread's previous suspend count
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see SuspendThread.
 */
EXTERN_C HRESULT WINAPI MileSuspendThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PDWORD PreviousSuspendCount);

/**
 * Decrements a thread's suspend count. When the suspend count is decremented
 * to zero, the execution of the thread is resumed.
 *
 * @param ThreadHandle A handle to the thread to be restarted.
 * @param PreviousSuspendCount The thread's previous suspend count.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see ResumeThread.
 */
EXTERN_C HRESULT WINAPI MileResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PDWORD PreviousSuspendCount);

/**
 * Waits until the specified object is in the signaled state, an I/O completion
 * routine or asynchronous procedure call (APC) is queued to the thread, or the
 * time-out interval elapses.
 *
 * @param hHandle A handle to the object.
 * @param dwMilliseconds The time-out interval, in milliseconds.
 * @param bAlertable If this parameter is TRUE and the thread is in the waiting
 *                   state, the function returns when the system queues an I/O
 *                   completion routine or APC, and the thread runs the routine
 *                   or function. Otherwise, the function does not return, and
 *                   the completion routine or APC function is not executed.
 * @param pdwReturn Indicates the event that caused the function to return.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see WaitForSingleObjectEx.
 */
EXTERN_C HRESULT WINAPI MileWaitForSingleObject(
    _In_ HANDLE hHandle,
    _In_ DWORD dwMilliseconds,
    _In_ BOOL bAlertable,
    _Out_opt_ PDWORD pdwReturn);

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
 * @param lpThreadHandle The address of the returned handle to the new thread.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateThread.
 */
EXTERN_C HRESULT WINAPI MileCreateThread(
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ SIZE_T dwStackSize,
    _In_ LPTHREAD_START_ROUTINE lpStartAddress,
    _In_opt_ LPVOID lpParameter,
    _In_ DWORD dwCreationFlags,
    _Out_opt_ LPDWORD lpThreadId,
    _Out_opt_ PHANDLE lpThreadHandle);

/**
 * Retrieves the number of logical processors in the current group.
 *
 * @return The number of logical processors in the current group.
 */
EXTERN_C DWORD WINAPI MileGetNumberOfHardwareThreads();

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
 * @param lpszIID The string representation of the IID.
 * @param ppv Address of pointer variable that receives the interface pointer
 *            requested in riid. Upon successful return, *ppv contains the
 *            requested interface pointer. Upon failure, *ppv contains NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CoCreateInstance.
 */
EXTERN_C HRESULT WINAPI MileCoCreateInstanceByString(
    _In_ LPCWSTR lpszCLSID,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ LPCWSTR lpszIID,
    _Out_ LPVOID* ppv);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Retrieves the string type data for the specified value name associated with
 * an open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the registry value.
 * @param lpData A pointer to a buffer that receives the value's data. When you
 *               have finished using the information, free it by calling the
 *               MileFreeMemory function. You should also set the pointer to
 *               NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileRegQueryStringValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Out_ LPWSTR* lpData);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Determines whether the interface id have the correct interface name.
 *
 * @param InterfaceID A pointer to the string representation of the IID.
 * @param InterfaceName A pointer to the interface name string.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileCoCheckInterfaceName(
    _In_ LPCWSTR InterfaceID,
    _In_ LPCWSTR InterfaceName);

#endif

#endif // !MILE_WINDOWS
