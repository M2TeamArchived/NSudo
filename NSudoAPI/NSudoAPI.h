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

#endif
