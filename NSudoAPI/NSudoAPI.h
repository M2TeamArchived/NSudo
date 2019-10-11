/*
 * PROJECT:   NSudo Shared Library
 * FILE:      NSudoAPI.h
 * PURPOSE:   Definition for NSudo Shared Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef NSUDO_API
#define NSUDO_API

#include "M2.Base.h"

/**
 * Gets the feature level of NSudo Shared Library.
 *
 * @return The feature level of NSudo Shared Library.
 *         Feature Level 0 - NSudo 8.0.0
 */
EXTERN_C DWORD WINAPI NSudoGetFeatureLevel();

/**
 * Enables or disables privileges in the specified access token.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token.
 * @param Privileges A pointer to an array of LUID_AND_ATTRIBUTES structures
 *                   that specifies an array of privileges and their attributes.
 *                   Each structure contains the LUID and attributes of a
 *                   privilege. To get the name of the privilege associated with
 *                   a LUID, call the LookupPrivilegeName function, passing the
 *                   address of the LUID as the value of the lpLuid parameter.
 *                   The attributes of a privilege can be a combination of the
 *                   following values.
 *                   SE_PRIVILEGE_ENABLED
 *                       The function enables the privilege.
 *                   SE_PRIVILEGE_REMOVED
 *                       The privilege is removed from the list of privileges in
 *                       the token.
 *                   None
 *                       The function disables the privilege.
 * @param PrivilegeCount The number of entries in the Privileges array.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see AdjustTokenPrivileges.
 */
EXTERN_C DWORD WINAPI NSudoAdjustTokenPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ PLUID_AND_ATTRIBUTES Privileges,
    _In_ DWORD PrivilegeCount);

/**
 * Contains values that specify the type of mandatory label.
 */
typedef enum _NSUDO_MANDATORY_LABEL_TYPE
{
    UNTRUSTED,
    LOW,
    MEDIUM,
    MEDIUM_PLUS,
    HIGH,
    SYSTEM,
    PROTECTED_PROCESS,
} NSUDO_MANDATORY_LABEL_TYPE, *PNSUDO_MANDATORY_LABEL_TYPE;

/**
 * Allocates and initializes a mandatory label security identifier (SID).
 *
 * @param MandatoryLabelSid A pointer to a variable that receives the pointer to
 *        the allocated and initialized mandatory label SID structure.
 * @param MandatoryLabelType A value from the MANDATORY_LABEL_TYPE enumerated
 *        type that identifies the mandatory label.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark A SID allocated with the NSudoCreateMandatoryLabelSid function must
 *         be freed by using the FreeSid function.
 */
EXTERN_C DWORD WINAPI NSudoCreateMandatoryLabelSid(
    _Out_ PSID* MandatoryLabelSid,
    _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType);

/**
 * Starts a service if not started and retrieves the current status of the
 * specified service.
 *
 * @param ServiceStatus A pointer to the process status information for a
 *                      service.
 * @param ServiceName The name of the service to be started. This is the name
 *                    specified by the lpServiceName parameter of the
 *                    CreateService function when the service object was
 *                    created, not the service display name that is shown by
 *                    user interface applications to identify the service.
 *                    The maximum string length is 256 characters. The service
 *                    control manager database preserves the case of the
 *                    characters, but service name comparisons are always case
 *                    insensitive. Forward-slash (/) and backslash (\) are
 *                    invalid service name characters.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 */
EXTERN_C DWORD WINAPI NSudoStartService(
    _Out_ LPSERVICE_STATUS_PROCESS ServiceStatus,
    _In_ LPCWSTR ServiceName);

/**
 * Opens an existing local process object.
 *
 * @param ProcessHandle A pointer to an open handle to the specified process.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param InheritHandle If this value is TRUE, processes created by this
 *                      process will inherit the handle. Otherwise, the
 *                      processes do not inherit this handle.
 * @param ProcessId The identifier of the local process to be opened.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenProcess.
 */
EXTERN_C DWORD WINAPI NSudoOpenProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ DWORD ProcessId);

/**
 * Opens an existing local process object associated with a service process,
 * the calling application must be running within the context of the
 * Administrator account and have the SE_DEBUG_NAME privilege enabled.
 *
 * @param ProcessHandle A pointer to an open handle to the specified process.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param InheritHandle If this value is TRUE, processes created by this
 *                      process will inherit the handle. Otherwise, the
 *                      processes do not inherit this handle.
 * @param ServiceName The name of the service to be opened. This is the name
 *                    specified by the lpServiceName parameter of the
 *                    CreateService function when the service object was
 *                    created, not the service display name that is shown by
 *                    user interface applications to identify the service.
 *                    The maximum string length is 256 characters. The service
 *                    control manager database preserves the case of the
 *                    characters, but service name comparisons are always case
 *                    insensitive. Forward-slash (/) and backslash (\) are
 *                    invalid service name characters.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenProcess.
 */
EXTERN_C DWORD WINAPI NSudoOpenServiceProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ LPCWSTR ServiceName);

/**
 * Opens the access token associated with a process.
 *
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @param ProcessHandle A handle to the process whose access token is opened.
 *                      The process must have the PROCESS_QUERY_INFORMATION
 *                      access permission.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C DWORD WINAPI NSudoOpenProcessTokenByProcessHandle(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ProcessHandle,
    _In_ DWORD DesiredAccess);

/**
 * Opens the access token associated with the current process.
 *
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C DWORD WINAPI NSudoOpenCurrentProcessToken(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD DesiredAccess);

/**
 * Opens the access token associated with a process.
 *
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @param ProcessId The identifier of the local process to be opened.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C DWORD WINAPI NSudoOpenProcessTokenByProcessId(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD ProcessId,
    _In_ DWORD DesiredAccess);

/**
 * Opens the access token associated with a service process, the calling
 * application must be running within the context of the Administrator account
 * and have the SE_DEBUG_NAME privilege enabled.
 *
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @param ServiceName The name of the service to be opened. This is the name
 *                    specified by the lpServiceName parameter of the
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
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C DWORD WINAPI NSudoOpenServiceProcessToken(
    _Out_ PHANDLE TokenHandle,
    _In_ LPCWSTR ServiceName,
    _In_ DWORD DesiredAccess);

/**
 * Opens an existing local process object associated with the Local Security
 * Authority process, the calling application must be running within the
 * context of the Administrator account and have the SE_DEBUG_NAME privilege
 * enabled.
 *
 * @param ProcessHandle A pointer to an open handle to the specified process.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @param InheritHandle If this value is TRUE, processes created by this
 *                      process will inherit the handle. Otherwise, the
 *                      processes do not inherit this handle.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenProcess.
 */
EXTERN_C DWORD WINAPI NSudoOpenLsassProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle);

/**
 * Opens the access token associated with the Local Security Authority process,
 * the calling application must be running within the context of the
 * Administrator account and have the SE_DEBUG_NAME privilege enabled.
 *
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @param DesiredAccess The access to the process object. This access right is
 *                      checked against the security descriptor for the
 *                      process. This parameter can be one or more of the
 *                      process access rights.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenProcessToken.
 */
EXTERN_C DWORD WINAPI NSudoOpenLsassProcessToken(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD DesiredAccess);

/**
 * Obtains the primary access token of the logged-on user specified by the
 * session ID. To call this function successfully, the calling application must
 * be running within the context of the LocalSystem account and have the
 * SE_TCB_NAME privilege.
 *
 * @param TokenHandle If the function succeeds, receives a pointer to the token
 *                    handle for the logged-on user. Note that you must call
 *                    the CloseHandle function to close this handle.
 * @param SessionId A Remote Desktop Services session identifier. 
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see WTSQueryUserToken.
 */
EXTERN_C DWORD WINAPI NSudoCreateSessionToken(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD SessionId);

/**
 * Allocates a block of memory from the default heap of the calling process.
 * The allocated memory will be initialized to zero. The allocated memory is
 * not movable.
 *
 * @param Block A pointer to the allocated memory block.
 * @param Size The number of bytes to be allocated.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 */
EXTERN_C DWORD WINAPI NSudoAllocMemory(
    _Out_ LPVOID* Block,
    _In_ SIZE_T Size);

/**
 * Frees a memory block allocated from a heap by the NSudoAllocMemory function.
 *
 * @param Block A pointer to the memory block to be freed. This pointer is
 *              returned by the M2AllocMemory or M2ReAllocMemory function. If
 *              this pointer is nullptr, the behavior is undefined.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 */
EXTERN_C DWORD WINAPI NSudoFreeMemory(
    _In_ LPVOID Block);

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
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see GetTokenInformation.
 */
EXTERN_C DWORD WINAPI NSudoGetTokenInformation(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_opt_ LPVOID TokenInformation,
    _In_ DWORD TokenInformationLength,
    _Out_ PDWORD ReturnLength);

/**
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param OutputInformation A pointer to a buffer the function fills with the
 *                          requested information. When you have finished using
 *                          the information, free it by calling the
 *                          NSudoFreeMemory function. You should also set the
 *                          pointer to NULL.
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the function
 *                              retrieves.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see GetTokenInformation.
 */
EXTERN_C DWORD WINAPI NSudoGetTokenInformationWithMemory(
    _Out_ PVOID* OutputInformation,
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass);

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
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see SetTokenInformation.
 */
EXTERN_C DWORD WINAPI NSudoSetTokenInformation(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _In_ LPVOID TokenInformation,
    _In_ DWORD TokenInformationLength);

/**
 * Sets mandatory label for a specified access token. The information that this
 * function sets replaces existing information. The calling process must have
 * appropriate access rights to set the information.
 *
 * @param TokenHandle A handle to the access token for which information is to
 *                    be set.
 * @param MandatoryLabelType A value from the MANDATORY_LABEL_TYPE enumerated
 *        type that identifies the mandatory label.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 */
EXTERN_C DWORD WINAPI NSudoSetTokenMandatoryLabel(
    _In_ HANDLE TokenHandle,
    _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType);

/**
 * Creates a new access token that is a restricted version of an existing
 * access token. The restricted token can have disabled security identifiers
 * (SIDs), deleted privileges, and a list of restricting SIDs. For more
 * information, see Restricted Tokens.
 *
 * @param ExistingTokenHandle A handle to a primary or impersonation token. The
 *                            token can also be a restricted token. The handle
 *                            must have TOKEN_DUPLICATE access to the token.
 * @param Flags Specifies additional privilege options. This parameter can be
 *              zero or a combination of the following values.
 *              DISABLE_MAX_PRIVILEGE
 *                  Disables all privileges in the new token except the
 *                  SeChangeNotifyPrivilege privilege. If this value is
 *                  specified, the DeletePrivilegeCount and PrivilegesToDelete
 *                  parameters are ignored.
 *              SANDBOX_INERT
 *                  If this value is used, the system does not check AppLocker
 *                  rules or apply Software Restriction Policies. For AppLocker,
 *                  this flag disables checks for all four rule collections:
 *                  Executable, Windows Installer, Script, and DLL.
 *              LUA_TOKEN
 *                  The new token is a LUA token.
 *              WRITE_RESTRICTED
 *                  The new token contains restricting SIDs that are considered
 *                  only when evaluating write access.
 * @param DisableSidCount Specifies the number of entries in the SidsToDisable
 *                        array.
 * @param SidsToDisable A pointer to an array of SID_AND_ATTRIBUTES structures
 *                      that specify the deny-only SIDs in the restricted token.
 * @param DeletePrivilegeCount Specifies the number of entries in the
 *                             PrivilegesToDelete array.
 * @param PrivilegesToDelete A pointer to an array of LUID_AND_ATTRIBUTES
 *                           structures that specify the privileges to delete
 *                           in the restricted token.
 * @param RestrictedSidCount Specifies the number of entries in the
 *                           SidsToRestrict array.
 * @param SidsToRestrict A pointer to an array of SID_AND_ATTRIBUTES structures
 *                       that specify a list of restricting SIDs for the new
 *                       token.
 * @param NewTokenHandle A pointer to a variable that receives a handle to the
 *                       new restricted token.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see CreateRestrictedToken.
 */
EXTERN_C DWORD WINAPI NSudoCreateRestrictedToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ DWORD Flags,
    _In_ DWORD DisableSidCount,
    _In_opt_ PSID_AND_ATTRIBUTES SidsToDisable,
    _In_ DWORD DeletePrivilegeCount,
    _In_opt_ PLUID_AND_ATTRIBUTES PrivilegesToDelete,
    _In_ DWORD RestrictedSidCount,
    _In_opt_ PSID_AND_ATTRIBUTES SidsToRestrict,
    _Out_ PHANDLE NewTokenHandle);

/**
 * Creates a new access token that is a LUA version of an existing access token.
 *
 * @param TokenHandle A pointer to a variable that receives a handle to the new
 *                    restricted token.
 * @param ExistingTokenHandle A handle to a primary or impersonation token. The
 *                            token can also be a restricted token. The handle
 *                            must have TOKEN_DUPLICATE access to the token.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 */
EXTERN_C DWORD WINAPI NSudoCreateLUAToken(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ExistingTokenHandle);

/**
 * Opens an existing thread object.
 *
 * @param ThreadHandle A pointer to an open handle to the specified thread.
 * @param DesiredAccess The access to the thread object. This access right is
 *                      checked against the security descriptor for the thread.
 *                      This parameter can be one or more of the thread access
 *                      rights.
 * @param InheritHandle If this value is TRUE, processes created by this
 *                      process will inherit the handle. Otherwise, the
 *                      processes do not inherit this handle.
 * @param ThreadId The identifier of the thread to be opened.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenThread.
 */
EXTERN_C DWORD WINAPI NSudoOpenThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL InheritHandle,
    _In_ DWORD ThreadId);

/**
 * Opens the access token associated with a thread.
 *
 * @param TokenHandle A pointer to a variable that receives the handle to the
 *                    newly opened access token.
 * @param ThreadHandle A handle to the thread whose access token is opened.
 * @param DesiredAccess Specifies an access mask that specifies the requested
 *                      types of access to the access token. These requested
 *                      access types are reconciled against the token's
 *                      discretionary access control list (DACL) to determine
 *                      which accesses are granted or denied.
 * @param OpenAsSelf TRUE if the access check is to be made against the
 *                   process-level security context. FALSE if the access check
 *                   is to be made against the current security context of the
 *                   thread calling the OpenThreadToken function.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenThreadToken.
 */
EXTERN_C DWORD WINAPI NSudoOpenThreadTokenByThreadHandle(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ThreadHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf);

/**
 * Opens the access token associated with the current thread.
 *
 * @param TokenHandle A pointer to a variable that receives the handle to the
 *                    newly opened access token.
 * @param DesiredAccess Specifies an access mask that specifies the requested
 *                      types of access to the access token. These requested
 *                      access types are reconciled against the token's
 *                      discretionary access control list (DACL) to determine
 *                      which accesses are granted or denied.
 * @param OpenAsSelf TRUE if the access check is to be made against the
 *                   process-level security context. FALSE if the access check
 *                   is to be made against the current security context of the
 *                   thread calling the OpenThreadToken function.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenThreadToken.
 */
EXTERN_C DWORD WINAPI NSudoOpenCurrentThreadToken(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf);

/**
 * Opens the access token associated with a thread.
 *
 * @param TokenHandle A pointer to a variable that receives the handle to the
 *                    newly opened access token.
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
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 * @remark For more information, see OpenThreadToken.
 */
EXTERN_C DWORD WINAPI NSudoOpenThreadTokenByThreadId(
    _Out_ PHANDLE TokenHandle,
    _In_ DWORD ThreadId,
    _In_ DWORD DesiredAccess,
    _In_ BOOL OpenAsSelf);

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
 *                       The privilege is removed from the list of privileges in
 *                       the token.
 *                   None
 *                       The function disables the privilege.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS.
 */
EXTERN_C DWORD WINAPI NSudoAdjustTokenAllPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ DWORD Attributes);

/**
 * Reallocates a block of memory from the default heap of the calling process.
 * If the reallocation request is for a larger size, the additional region of
 * memory beyond the original size be initialized to zero. This function
 * enables you to resize a memory block and change other memory block
 * properties. The allocated memory is not movable.
 *
 * @param NewBlock A pointer to the allocated memory block.
 * @param OldBlock A pointer to the block of memory that the function
 *                 reallocates. This pointer is returned by an earlier call to
 *                 the NSudoAllocMemory or NSudoReAllocMemory function.
 * @param NewSize The new size of the memory block, in bytes. A memory block's
 *                size can be increased or decreased by using this function.
 * @return Standard Win32 Error. If the function succeeds, the return value is
 *         ERROR_SUCCESS. If the function fails, the original memory is not
 *         freed, and the original handle and pointer are still valid.
 */
EXTERN_C DWORD WINAPI NSudoReAllocMemory(
    _Out_ PVOID* NewBlock,
    _In_ PVOID OldBlock,
    _In_ SIZE_T NewSize);

#endif
