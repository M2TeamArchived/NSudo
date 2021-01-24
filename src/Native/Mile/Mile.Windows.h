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
 * Allocates a block of memory from the default heap of the calling process.
 * The allocated memory will be initialized to zero. The allocated memory is
 * not movable.
 *
 * @param Size The number of bytes to be allocated.
 * @param Block A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileAllocMemory(
    _In_ SIZE_T Size,
    _Out_ LPVOID* Block);

/**
 * Reallocates a block of memory from the default heap of the calling process.
 * If the reallocation request is for a larger size, the additional region of
 * memory beyond the original size be initialized to zero. This function
 * enables you to resize a memory block and change other memory block
 * properties. The allocated memory is not movable.
 *
 * @param OldBlock A pointer to the block of memory that the function
 *                 reallocates. This pointer is returned by an earlier call to
 *                 the MileAllocMemory or MileReAllocMemory function.
 * @param NewSize The new size of the memory block, in bytes. A memory block's
 *                size can be increased or decreased by using this function.
 * @param NewBlock A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 */
EXTERN_C HRESULT WINAPI MileReAllocMemory(
    _In_ PVOID OldBlock,
    _In_ SIZE_T NewSize,
    _Out_ LPVOID* NewBlock);

/**
 * Frees a memory block allocated from a heap by the MileAllocMemory or
 * MileReAllocMemory function.
 *
 * @param Block A pointer to the memory block to be freed. This pointer is
 *              returned by the AllocMemory or ReAllocMemory function. If this
 *              pointer is nullptr, the behavior is undefined.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileFreeMemory(
    _In_ LPVOID Block);

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
 * Closes a handle to a service control manager or service object.
 *
 * @param hSCObject A handle to the service control manager object or the
 *                  service object to close.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see CloseServiceHandle.
 */
EXTERN_C HRESULT WINAPI MileCloseServiceHandle(
    _In_ SC_HANDLE hSCObject);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Establishes a connection to the service control manager on the specified
 * computer and opens the specified service control manager database.
 *
 * @param lpMachineName The name of the target computer. If the pointer is
 *                      nullptr or points to an empty string, the function
 *                      connects to the service control manager on the local
 *                      computer.
 * @param lpDatabaseName The name of the service control manager database. This
 *                       parameter should be set to SERVICES_ACTIVE_DATABASE.
 *                       If it is nullptr, the SERVICES_ACTIVE_DATABASE
 *                       database is opened by default.
 * @param dwDesiredAccess The access to the service control manager. For a list
 *                        of access rights, see Service Security and Access
 *                        Rights.
 * @param phSCManager A handle to the specified service control manager
 *                    database.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenSCManagerW.
 */
EXTERN_C HRESULT WINAPI MileOpenSCManager(
    _In_opt_ LPCWSTR lpMachineName,
    _In_opt_ LPCWSTR lpDatabaseName,
    _In_ DWORD dwDesiredAccess,
    _Out_opt_ LPSC_HANDLE phSCManager);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Opens an existing service.
 *
 * @param hSCManager A handle to the service control manager database.
 * @param lpServiceName The name of the service to be opened.
 * @param dwDesiredAccess The access to the service. For a list of access
 *                        rights, see Service Security and Access Rights.
 * @param phService A handle to the service.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see OpenServiceW.
 */
EXTERN_C HRESULT WINAPI MileOpenService(
    _In_ SC_HANDLE hSCManager,
    _In_ LPCWSTR lpServiceName,
    _In_ DWORD dwDesiredAccess,
    _Out_opt_ LPSC_HANDLE phService);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Retrieves the current status of the specified service based on the specified
 * information level.
 *
 * @param hService A handle to the service.
 * @param InfoLevel The service attributes to be returned.
 * @param lpBuffer A pointer to the buffer that receives the status
 *                 information.
 * @param cbBufSize The size of the buffer pointed to by the lpBuffer
 *                  parameter, in bytes.
 * @param pcbBytesNeeded A pointer to a variable that receives the number of
 *                       bytes needed to store all status information, if the
 *                       function fails with ERROR_INSUFFICIENT_BUFFER.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see QueryServiceStatusEx.
 */
EXTERN_C HRESULT WINAPI MileQueryServiceStatus(
    _In_ SC_HANDLE hService,
    _In_ SC_STATUS_TYPE InfoLevel,
    _Out_ LPBYTE lpBuffer,
    _In_ DWORD cbBufSize,
    _Out_ LPDWORD pcbBytesNeeded);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Starts a service.
 *
 * @param hService A handle to the service.
 * @param dwNumServiceArgs The number of strings in the lpServiceArgVectors
 *                         array. If lpServiceArgVectors is nullptr, this
 *                         parameter can be zero.
 * @param lpServiceArgVectors The null-terminated strings to be passed to the
 *                            ServiceMain function for the service as
 *                            arguments. If there are no arguments, this
 *                            parameter can be nullptr. Otherwise, the first
 *                            argument (lpServiceArgVectors[0]) is the name of
 *                            the service, followed by any additional arguments
 *                            (lpServiceArgVectors[1] through
 *                            lpServiceArgVectors[dwNumServiceArgs-1]). Driver
 *                            services do not receive these arguments.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see StartServiceW.
 */
EXTERN_C HRESULT WINAPI MileStartService(
    _In_ SC_HANDLE hService,
    _In_ DWORD dwNumServiceArgs,
    _In_ LPCWSTR* lpServiceArgVectors);

#endif

/**
 * Suspends the current thread until the specified condition is met.
 *
 * @param dwMilliseconds The time interval for which execution is to be
 *                       suspended, in milliseconds.
 * @param bAlertable If this parameter is FALSE, the function does not return
 *                   until the time-out period has elapsed.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see SleepEx.
 */
EXTERN_C DWORD WINAPI MileSleep(
    _In_ DWORD dwMilliseconds,
    _In_ BOOL bAlertable);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Starts a service if not started and retrieves the current status of the
 * specified service.
 *
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
 * @param ServiceStatus A pointer to the process status information for a
 *                      service.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileStartServiceSimple(
    _In_ LPCWSTR ServiceName,
    _Out_ LPSERVICE_STATUS_PROCESS ServiceStatus);

#endif

/**
 * Retrieves the number of milliseconds that have elapsed since the system was
 * started.
 *
 * @return The number of milliseconds.
 */
EXTERN_C ULONGLONG WINAPI MileGetTickCount();

/**
 * Closes an open object handle.
 *
 * @param hObject A valid handle to an open object.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CloseHandle.
 */
EXTERN_C HRESULT WINAPI MileCloseHandle(
    _In_ HANDLE hObject);

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
 *                    the MileCloseHandle function to close this handle.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see WTSQueryUserToken.
 */
EXTERN_C HRESULT WINAPI MileCreateSessionToken(
    _In_ DWORD SessionId,
    _Out_ PHANDLE TokenHandle);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

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
 *                  rules or apply Software Restriction Policies. For
 *                  AppLocker, this flag disables checks for all four rule
 *                  collections: Executable, Windows Installer, Script, and
 *                  DLL.
 *              LUA_TOKEN
 *                  The new token is a LUA token.
 *              WRITE_RESTRICTED
 *                  The new token contains restricting SIDs that are considered
 *                  only when evaluating write access.
 * @param DisableSidCount Specifies the number of entries in the SidsToDisable
 *                        array.
 * @param SidsToDisable A pointer to an array of SID_AND_ATTRIBUTES structures
 *                      that specify the deny-only SIDs in the restricted
 *                      token.
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
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see CreateRestrictedToken.
 */
EXTERN_C HRESULT WINAPI MileCreateRestrictedToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ DWORD Flags,
    _In_ DWORD DisableSidCount,
    _In_opt_ PSID_AND_ATTRIBUTES SidsToDisable,
    _In_ DWORD DeletePrivilegeCount,
    _In_opt_ PLUID_AND_ATTRIBUTES PrivilegesToDelete,
    _In_ DWORD RestrictedSidCount,
    _In_opt_ PSID_AND_ATTRIBUTES SidsToRestrict,
    _Out_ PHANDLE NewTokenHandle);

#endif

/**
 * Compares a SID to a well-known SID and returns TRUE if they match.
 *
 * @param pSid A pointer to the SID to test.
 * @param WellKnownSidType Member of the WELL_KNOWN_SID_TYPE enumeration to
 *                         compare with the SID at pSid.
 * @return Returns TRUE if the SID at pSid matches the well-known SID indicated
 *         by WellKnownSidType. Otherwise, returns FALSE.
 * @remark For more information, see IsWellKnownSid.
 */
EXTERN_C BOOL WINAPI MileIsWellKnownSid(
    _In_ PSID pSid,
    _In_ WELL_KNOWN_SID_TYPE WellKnownSidType);

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
 * Allocates and initializes a security identifier (SID) with up to eight
 * subauthorities.
 *
 * @param pIdentifierAuthority A pointer to a SID_IDENTIFIER_AUTHORITY
 *                             structure. This structure provides the top-level
 *                             identifier authority value to set in the SID.
 * @param nSubAuthorityCount Specifies the number of subauthorities to place in
 *                           the SID. This parameter also identifies how many
 *                           of the subauthority parameters have meaningful
 *                           values. This parameter must contain a value from 1
 *                           to 8.
 * @param nSubAuthority0 Subauthority value to place in the SID.
 * @param nSubAuthority1 Subauthority value to place in the SID.
 * @param nSubAuthority2 Subauthority value to place in the SID.
 * @param nSubAuthority3 Subauthority value to place in the SID.
 * @param nSubAuthority4 Subauthority value to place in the SID.
 * @param nSubAuthority5 Subauthority value to place in the SID.
 * @param nSubAuthority6 Subauthority value to place in the SID.
 * @param nSubAuthority7 Subauthority value to place in the SID.
 * @param pSid A pointer to a variable that receives the pointer to the
 *             allocated and initialized SID structure.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see AllocateAndInitializeSid.
 */
EXTERN_C HRESULT WINAPI MileAllocateAndInitializeSid(
    _In_ PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,
    _In_ BYTE nSubAuthorityCount,
    _In_ DWORD nSubAuthority0,
    _In_ DWORD nSubAuthority1,
    _In_ DWORD nSubAuthority2,
    _In_ DWORD nSubAuthority3,
    _In_ DWORD nSubAuthority4,
    _In_ DWORD nSubAuthority5,
    _In_ DWORD nSubAuthority6,
    _In_ DWORD nSubAuthority7,
    _Outptr_ PSID* pSid);

/**
 * Frees a security identifier (SID) previously allocated by using the
 * MileAllocateAndInitializeSid function.
 *
 * @param pSid A pointer to the SID structure to free.
 * @return If the function succeeds, the function returns nullptr. If the
 *         function fails, it returns a pointer to the SID structure
 *         represented by the pSid parameter.
 * @remark For more information, see FreeSid.
 */
EXTERN_C PVOID WINAPI MileFreeSid(
    _In_ PSID pSid);

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
 * Allocates and initializes a mandatory label security identifier (SID).
 *
 * @param MandatoryLabelRid The value of the mandatory label for the process.
 *                          This parameter can be one of the following values.
 *                          SECURITY_MANDATORY_UNTRUSTED_RID
 *                          SECURITY_MANDATORY_LOW_RID
 *                          SECURITY_MANDATORY_MEDIUM_RID
 *                          SECURITY_MANDATORY_MEDIUM_PLUS_RID
 *                          SECURITY_MANDATORY_HIGH_RID
 *                          SECURITY_MANDATORY_SYSTEM_RID
 *                          SECURITY_MANDATORY_PROTECTED_PROCESS_RID
 * @param MandatoryLabelSid A pointer to a variable that receives the
 *                          pointer to the allocated and initialized
 *                          mandatory label SID structure.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark A SID allocated with the CreateMandatoryLabelSid method must be
 *         freed by using the FreeSid function.
 */
EXTERN_C HRESULT WINAPI MileCreateMandatoryLabelSid(
    _In_ DWORD MandatoryLabelRid,
    _Out_ PSID* MandatoryLabelSid);

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
 * Returns the length, in bytes, of a valid security identifier (SID).
 *
 * @param pSid A pointer to the SID structure whose length is returned. The
 *             structure is assumed to be valid.
 * @return If the SID structure is valid, the return value is the length, in
 *         bytes, of the SID structure. If the SID structure is not valid, the
 *         return value is undefined.
 * @remark For more information, see GetLengthSid.
 */
EXTERN_C DWORD WINAPI MileGetLengthSid(
    _In_ PSID pSid);

/**
 * Initializes a new ACL structure.
 *
 * @param pAcl A pointer to an ACL structure to be initialized by this
 *             function. Allocate memory for pAcl before calling this function.
 * @param nAclLength The length, in bytes, of the buffer pointed to by the pAcl
 *                   parameter.
 * @param dwAclRevision The revision level of the ACL structure being created.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see InitializeAcl.
 */
EXTERN_C HRESULT WINAPI MileInitializeAcl(
    _Out_ PACL pAcl,
    _In_ DWORD nAclLength,
    _In_ DWORD dwAclRevision);

/**
 * Adds an access-allowed access control entry (ACE) to an access control list
 * (ACL). The access is granted to a specified security identifier (SID).
 *
 * @param pAcl A pointer to an ACL.
 * @param dwAceRevision Specifies the revision level of the ACL being modified.
 * @param AccessMask Specifies the mask of access rights to be granted to the
 *                   specified SID.
 * @param pSid A pointer to the SID representing a user, group, or logon
 *             account being granted access.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see AddAccessAllowedAce.
 */
EXTERN_C HRESULT WINAPI MileAddAccessAllowedAce(
    _Inout_ PACL pAcl,
    _In_ DWORD dwAceRevision,
    _In_ DWORD AccessMask,
    _In_ PSID pSid);

/**
 * Obtains a pointer to an access control entry (ACE) in an access control list
 * (ACL).
 *
 * @param pAcl A pointer to an ACL that contains the ACE to be retrieved.
 * @param dwAceIndex The index of the ACE to be retrieved. A value of zero
 *                   corresponds to the first ACE in the ACL, a value of one to
 *                   the second ACE, and so on.
 * @param pAce A pointer to a pointer that the function sets to the address of
 *             the ACE.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see GetAce.
 */
EXTERN_C HRESULT WINAPI MileGetAce(
    _In_ PACL pAcl,
    _In_ DWORD dwAceIndex,
    _Out_ LPVOID* pAce);

/**
 * Adds one or more access control entries (ACEs) to a specified access control
 * list (ACL).
 *
 * @param pAcl A pointer to an ACL. This function adds an ACE to this ACL.
 * @param dwAceRevision Specifies the revision level of the ACL being modified.
 * @param dwStartingAceIndex Specifies the position in the ACL's list of ACEs
 *                           at which to add new ACEs.
 * @param pAceList A pointer to a list of one or more ACEs to be added to the
 *                 specified ACL. The ACEs in the list must be stored
 *                 contiguously.
 * @paramn AceListLength Specifies the size, in bytes, of the input buffer
 *                       pointed to by the pAceList parameter.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see AddAce.
 */
EXTERN_C HRESULT WINAPI MileAddAce(
    _Inout_ PACL pAcl,
    _In_ DWORD dwAceRevision,
    _In_ DWORD dwStartingAceIndex,
    _In_ LPVOID pAceList,
    _In_ DWORD nAceListLength);

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

/**
 * Expands environment-variable strings and replaces them with the values
 * defined for the current user.
 *
 * @param lpSrc A buffer that contains one or more environment-variable strings
 *              in the form: %variableName%.
 * @param lpDst A pointer to a buffer that receives the result of expanding the
 *              environment variable strings in the lpSrc buffer. Note that
 *              this buffer cannot be the same as the lpSrc buffer.
 * @param nSize The maximum number of characters that can be stored in the
 *              buffer pointed to by the lpDst parameter.
 * @param pReturnSize The number of TCHARs stored in the destination buffer,
 *                    including the terminating null character.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see ExpandEnvironmentStringsW.
 */
EXTERN_C HRESULT WINAPI MileExpandEnvironmentStrings(
    _In_ LPCWSTR lpSrc,
    _Out_opt_ LPWSTR lpDst,
    _In_ DWORD nSize,
    _Out_opt_ PDWORD pReturnSize);

/**
 * Expands environment-variable strings and replaces them with the values
 * defined for the current user.
 *
 * @param Source The environment-variable string you need to expand.
 * @param Destination The expanded string. When you have finished using the
 *                    information, free it by calling the MileFreeMemory
 *                    function. You should also set the pointer to nullptr.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileExpandEnvironmentStringsWithMemory(
    _In_ LPCWSTR Source,
    _Out_ LPWSTR* Destination);

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

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Closes a handle to the specified registry key.
 *
 * @param hKey A handle to the open key to be closed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegCloseKey.
 */
EXTERN_C HRESULT WINAPI MileRegCloseKey(
    _In_ HKEY hKey);

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
EXTERN_C HRESULT WINAPI MileRegCreateKey(
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
EXTERN_C HRESULT WINAPI MileRegQueryValue(
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
EXTERN_C HRESULT WINAPI MileRegSetValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ DWORD Reserved,
    _In_ DWORD dwType,
    _In_opt_ CONST BYTE* lpData,
    _In_ DWORD cbData);

#endif

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
EXTERN_C HRESULT WINAPI MileGetFileInformation(
    _In_  HANDLE hFile,
    _In_  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    _Out_ LPVOID lpFileInformation,
    _In_  DWORD dwBufferSize);

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
EXTERN_C HRESULT WINAPI MileSetFileInformation(
    _In_ HANDLE hFile,
    _In_ FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    _In_ LPVOID lpFileInformation,
    _In_ DWORD dwBufferSize);

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
EXTERN_C HRESULT WINAPI MileGetFileAttributes(
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
EXTERN_C HRESULT WINAPI MileSetFileAttributes(
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
EXTERN_C HRESULT WINAPI MileGetFileSize(
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
EXTERN_C HRESULT WINAPI MileGetFileAllocationSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG AllocationSize);

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
 *             SYNCHRONIZE | DELETE | FILE_READ_ATTRIBUTES
 *             | FILE_WRITE_ATTRIBUTES,
 *             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
EXTERN_C HRESULT WINAPI MileDeleteFile(
    _In_ HANDLE FileHandle);

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
 *             SYNCHRONIZE | DELETE | FILE_READ_ATTRIBUTES
 *             | FILE_WRITE_ATTRIBUTES,
 *             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
EXTERN_C HRESULT WINAPI MileDeleteFileIgnoreReadonlyAttribute(
    _In_ HANDLE FileHandle);

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
EXTERN_C HRESULT WINAPI MileLoadLibrary(
    _In_ LPCWSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags,
    _Out_opt_ HMODULE* phLibModule);

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
EXTERN_C HRESULT WINAPI MileFreeLibrary(
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
EXTERN_C HRESULT WINAPI MileGetProcAddress(
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName,
    _Out_opt_ FARPROC* lpProcAddress);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates or opens a file or I/O device. The most commonly used I/O devices
 * are as follows: file, file stream, directory, physical disk, volume, console
 * buffer, tape drive, communications resource, mailslot, and pipe. The
 * function returns a handle that can be used to access the file or device for
 * various types of I/O depending on the file or device and the flags and
 * attributes specified.
 *
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
 * @param lpFileHandle The address of the returned handle to the specified
 *                     file.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateFileW.
 */
EXTERN_C HRESULT WINAPI MileCreateFile(
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile,
    _Out_opt_ PHANDLE lpFileHandle);

#endif

/**
 * Retrieves the actual number of bytes of disk storage used to store a
 * specified file. If the file is located on a volume that supports
 * compression and the file is compressed, the value obtained is the
 * compressed size of the specified file. If the file is located on a volume
 * that supports sparse files and the file is a sparse file, the value obtained
 * is the sparse size of the specified file.
 *
 * @param FileHandle A handle to the file that contains the information to be
 *                   retrieved. This handle should not be a pipe handle.
 * @param CompressedFileSize A pointer to a ULONGLONG value that receives the
 *                           compressed file size,
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
EXTERN_C HRESULT WINAPI MileGetCompressedFileSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG CompressedFileSize);

/**
 * Creates a single uninitialized object of the class associated with a
 * specified CLSID.
 *
 * @param rclsid The CLSID associated with the data and code that will be used
 *               to create the object.
 * @param pUnkOuter If NULL, indicates that the object is not being created as
 *                  part of an aggregate. If non-NULL, pointer to the aggregate
 *                  object's IUnknown interface (the controlling IUnknown).
 * @param dwClsContext Context in which the code that manages the newly created
 *                     object will run. The values are taken from the
 *                     enumeration CLSCTX.
 * @param riid A reference to the identifier of the interface to be used to
 *             communicate with the object.
 * @param ppv Address of pointer variable that receives the interface pointer
 *            requested in riid. Upon successful return, *ppv contains the
 *            requested interface pointer. Upon failure, *ppv contains NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CoCreateInstance.
 */
EXTERN_C HRESULT WINAPI MileCoCreateInstance(
    _In_ REFCLSID rclsid,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ REFIID riid,
    _Out_ LPVOID* ppv);

/**
 * Converts the CLSID string to the CLSID structure.
 *
 * @param lpsz The string representation of the CLSID.
 * @param pclsid A pointer to the CLSID.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CLSIDFromString.
 */
EXTERN_C HRESULT WINAPI MileCLSIDFromString(
    _In_ LPCOLESTR lpsz,
    _Out_ LPCLSID pclsid);

/**
 * Converts the IID string to the IID structure.
 *
 * @param lpsz A pointer to the string representation of the IID.
 * @param lpiid A pointer to the IID.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see IIDFromString.
 */
EXTERN_C HRESULT WINAPI MileIIDFromString(
    _In_ LPCOLESTR lpsz,
    _Out_ LPIID lpiid);

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

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

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
EXTERN_C HRESULT WINAPI MileGetDpiForMonitor(
    _In_ HMONITOR hmonitor,
    _In_ MONITOR_DPI_TYPE dpiType,
    _Out_ UINT* dpiX,
    _Out_ UINT* dpiY);

#endif

/**
 * Tests for the current directory and parent directory markers while iterating
 * through files.
 *
 * @param Name The name of the file or directory for testing.
 * @return Nonzero if the found file has the name "." or "..", which indicates
 *         that the found file is actually a directory. Otherwise 0.
 */
EXTERN_C BOOL WINAPI MileIsDots(
    _In_ LPCWSTR Name);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates or opens a named or unnamed file mapping object for a specified
 * file.
 *
 * @param hFile A handle to the file from which to create a file mapping
 *              object. If hFile is INVALID_HANDLE_VALUE, the calling process
 *              must also specify a size for the file mapping object in the
 *              dwMaximumSizeHigh and dwMaximumSizeLow parameters.
 * @param lpFileMappingAttributes A pointer to a SECURITY_ATTRIBUTES structure
 *                                that determines whether a returned handle can
 *                                be inherited by child processes. If
 *                                lpFileMappingAttributes is NULL, the handle
 *                                cannot be inherited and the file mapping
 *                                object gets a default security descriptor.
 * @param flProtect Specifies the page protection of the file mapping object.
 *                  All mapped views of the object must be compatible with this
 *                  protection.
 * @param dwMaximumSizeHigh The high-order DWORD of the maximum size of the
 *                          file mapping object.
 * @param dwMaximumSizeLow The low-order DWORD of the maximum size of the file
 *                         mapping object. If this parameter and
 *                         dwMaximumSizeHigh are 0 (zero), the maximum size of
 *                         the file mapping object is equal to the current size
 *                         of the file that hFile identifies.
 * @param lpName The name of the file mapping object. If this parameter matches
 *               the name of an existing mapping object, the function requests
 *               access to the object with the protection that flProtect
 *               specifies. If this parameter is NULL, the file mapping object
 *               is created without a name.
 * @param lpFileMappingHandle The address of the returned handle to the newly
 *                            created file mapping object.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateFileMappingW.
 */
EXTERN_C HRESULT WINAPI MileCreateFileMapping(
    _In_ HANDLE hFile,
    _In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    _In_ DWORD flProtect,
    _In_ DWORD dwMaximumSizeHigh,
    _In_ DWORD dwMaximumSizeLow,
    _In_opt_ LPCWSTR lpName,
    _Out_opt_ PHANDLE lpFileMappingHandle);

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Maps a view of a file mapping into the address space of a calling process.
 *
 * @param hFileMappingObject A handle to a file mapping object.
 * @param dwDesiredAccess The type of access to a file mapping object, which
 *                        determines the page protection of the pages.
 * @param dwFileOffsetHigh A high-order DWORD of the file offset where the view
 *                         begins.
 * @param dwFileOffsetLow A low-order DWORD of the file offset where the view
 *                        is to begin. The combination of the high and low
 *                        offsets must specify an offset within the file
 *                        mapping.
 * @param dwNumberOfBytesToMap The number of bytes of a file mapping to map to
 *                             the view. All bytes must be within the maximum
 *                             size specified by MileCreateFileMapping. If this
 *                             parameter is 0 (zero), the mapping extends from
 *                             the specified offset to the end of the file
 *                             mapping.
 * @param lpBaseAddress The address of the starting address of the mapped view.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see MapViewOfFile.
 */
EXTERN_C HRESULT WINAPI MileMapViewOfFile(
    _In_ HANDLE hFileMappingObject,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwFileOffsetHigh,
    _In_ DWORD dwFileOffsetLow,
    _In_ SIZE_T dwNumberOfBytesToMap,
    _Out_opt_ LPVOID* lpBaseAddress);

#endif

/**
 * Unmaps a mapped view of a file from the calling process's address space.
 *
 * @param lpBaseAddress A pointer to the base address of the mapped view of a
 *                      file that is to be unmapped.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see UnmapViewOfFile.
 */
EXTERN_C HRESULT WINAPI MileUnmapViewOfFile(
    _In_ LPCVOID lpBaseAddress);

/**
 * Reads data from the specified file or input/output (I/O) device. Reads occur
 * at the position specified by the file pointer if supported by the device.
 *
 * @param hFile A handle to the device (for example, a file, file stream,
 *              physical disk, volume, console buffer, tape drive, socket,
 *              communications resource, mailslot, or pipe).
 * @param lpBuffer A pointer to the buffer that receives the data read from a
 *                 file or device. This buffer must remain valid for the
 *                 duration of the read operation. The caller must not use this
 *                 buffer until the read operation is completed.
 * @param nNumberOfBytesToRead The maximum number of bytes to be read.
 * @param lpNumberOfBytesRead A pointer to the variable that receives the
 *                            number of bytes read when using a synchronous
 *                            hFile parameter. MileReadFile sets this value to
 *                            zero before doing any work or error checking. Use
 *                            NULL for this parameter if this is an
 *                            asynchronous operation to avoid potentially
 *                            erroneous results. This parameter can be NULL
 *                            only when the lpOverlapped parameter is not NULL.
 * @param lpOverlapped A pointer to an OVERLAPPED structure is required if the
 *                     hFile parameter was opened with FILE_FLAG_OVERLAPPED,
 *                     otherwise it can be NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see ReadFile.
 */
EXTERN_C HRESULT WINAPI MileReadFile(
    _In_ HANDLE hFile,
    _Out_opt_ LPVOID lpBuffer,
    _In_ DWORD nNumberOfBytesToRead,
    _Out_opt_ LPDWORD lpNumberOfBytesRead,
    _Inout_opt_ LPOVERLAPPED lpOverlapped);

/**
 * Writes data to the specified file or input/output (I/O) device.
 *
 * @param hFile A handle to the device (for example, a file, file stream,
 *              physical disk, volume, console buffer, tape drive, socket,
 *              communications resource, mailslot, or pipe).
 * @param lpBuffer A pointer to the buffer containing the data to be written to
 *                 the file or device. This buffer must remain valid for the
 *                 duration of the write operation. The caller must not use
 *                 this buffer until the write operation is completed.
 * @param nNumberOfBytesToWrite The number of bytes to be written to the file
 *                              or device. A value of zero specifies a null
 *                              write operation. The behavior of a null write
 *                              operation depends on the underlying file system
 *                              or communications technology.
 * @param lpNumberOfBytesWritten A pointer to the variable that receives the
 *                               number of bytes written when using a
 *                               synchronous hFile parameter. MileWriteFile
 *                               sets this value to zero before doing any work
 *                               or error checking. Use NULL for this parameter
 *                               if this is an asynchronous operation to avoid
 *                               potentially erroneous results. This parameter
 *                               can be NULL only when the lpOverlapped
 *                               parameter is not NULL.
 * @param lpOverlapped A pointer to an OVERLAPPED structure is required if the
 *                     hFile parameter was opened with FILE_FLAG_OVERLAPPED,
 *                     otherwise this parameter can be NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see WriteFile.
 */
EXTERN_C HRESULT WINAPI MileWriteFile(
    _In_ HANDLE hFile,
    _In_opt_ LPCVOID lpBuffer,
    _In_ DWORD nNumberOfBytesToWrite,
    _Out_opt_ LPDWORD lpNumberOfBytesWritten,
    _Inout_opt_ LPOVERLAPPED lpOverlapped);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates or opens a file or I/O device. The most commonly used I/O devices
 * are as follows: file, file stream, directory, physical disk, volume, console
 * buffer, tape drive, communications resource, mailslot, and pipe. The
 * function returns a handle that can be used to access the file or device for
 * various types of I/O depending on the file or device and the flags and
 * attributes specified.
 *
 * @param hOriginalFile A handle to the object to be reopened. The object must
 *                      have been created by the MileCreateFile function.
 * @param dwDesiredAccess The requested access to the file or device, which can
 *                        be summarized as read, write, both or neither zero).
 * @param dwShareMode The requested sharing mode of the file or device, which
 *                    can be read, write, both, delete, all of these, or none
 *                    (refer to the following table). Access requests to
 *                    attributes or extended attributes are not affected by
 *                    this flag.
 * @param dwFlagsAndAttributes The file or device attributes and flags.
 * @param lpFileHandle The address of the returned handle to the specified
 *                     file.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see ReOpenFile.
 */
EXTERN_C HRESULT WINAPI MileReOpenFile(
    _In_ HANDLE hOriginalFile,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_ DWORD dwFlagsAndAttributes,
    _Out_opt_ PHANDLE lpFileHandle);

#endif

/**
 * Maps a character string to a UTF-16 (wide character) string. The character
 * string is not necessarily from a multibyte character set.
 *
 * @param CodePage Code page to use in performing the conversion. This
 *                 parameter can be set to the value of any code page that is
 *                 installed or available in the operating system.
 * @param dwFlags Flags indicating the conversion type.
 * @param lpMultiByteStr Pointer to the character string to convert.
 * @param cbMultiByte Size, in bytes, of the string indicated by the
 *                    lpMultiByteStr parameter. Alternatively, this parameter
 *                    can be set to -1 if the string is null-terminated. Note
 *                    that, if cbMultiByte is 0, the function fails.
 * @param lpWideCharStr Pointer to a buffer that receives the converted string.
 * @param cchWideChar Size, in characters, of the buffer indicated by
 *                    lpWideCharStr. If this value is 0, the function returns
 *                    the required buffer size, in characters, including any
 *                    terminating null character, and makes no use of the
 *                    lpWideCharStr buffer.
 * @param pcchReturnWideChar The number of characters written to the buffer
 *                           indicated by lpWideCharStr if successful. If the
 *                           function succeeds and cchWideChar is 0, the return
 *                           value is the required size, in characters, for the
 *                           buffer indicated by lpWideCharStr.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see MultiByteToWideChar.
 */
EXTERN_C HRESULT WINAPI MileMultiByteToWideChar(
    _In_ UINT CodePage,
    _In_ DWORD dwFlags,
    _In_ LPCCH lpMultiByteStr,
    _In_ INT cbMultiByte,
    _Out_opt_ LPWSTR lpWideCharStr,
    _In_ INT cchWideChar,
    _Out_opt_ LPINT pcchReturnWideChar);

/**
 * Maps a UTF-16 (wide character) string to a new character string. The new
 * character string is not necessarily from a multibyte character set.
 *
 * @param CodePage Code page to use in performing the conversion. This
 *                 parameter can be set to the value of any code page that is
 *                 installed or available in the operating system.
 * @param dwFlags Flags indicating the conversion type.
 * @param lpWideCharStr Pointer to the Unicode string to convert.
 * @param cchWideChar Size, in characters, of the string indicated by
 *                    lpWideCharStr. Alternatively, this parameter can be set
 *                    to -1 if the string is null-terminated. If cchWideChar is
 *                    set to 0, the function fails.
 * @param lpMultiByteStr Pointer to a buffer that receives the converted
 *                       string.
 * @param cbMultiByte Size, in bytes, of the buffer indicated by
 *                    lpMultiByteStr. If this parameter is set to 0, the
 *                    function returns the required buffer size for
 *                    lpMultiByteStr and makes no use of the output parameter
 *                    itself.
 * @param lpDefaultChar Pointer to the character to use if a character cannot
 *                      be represented in the specified code page. The
 *                      application sets this parameter to NULL if the function
 *                      is to use a system default value.
 * @param lpUsedDefaultChar Pointer to a flag that indicates if the function
 *                          has used a default character in the conversion.
 * @param pcchReturnMultiByte The number of bytes written to the buffer pointed
 *                            to by lpMultiByteStr. If the function succeeds
 *                            and cbMultiByte is 0, the return value is the
 *                            required size, in bytes, for the buffer indicated
 *                            by lpMultiByteStr.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see WideCharToMultiByte.
 */
EXTERN_C HRESULT WINAPI MileWideCharToMultiByte(
    _In_ UINT CodePage,
    _In_ DWORD dwFlags,
    _In_ LPCWCH lpWideCharStr,
    _In_ INT cchWideChar,
    _Out_opt_ LPSTR lpMultiByteStr,
    _In_ INT cbMultiByte,
    _In_opt_ LPCCH lpDefaultChar,
    _Out_opt_ LPBOOL lpUsedDefaultChar,
    _Out_opt_ LPINT pcchReturnMultiByte);

/**
 * Retrieves the path of the system directory. The system directory contains
 * system files such as dynamic-link libraries and drivers.
 *
 * @param lpBuffer A pointer to the buffer to receive the path. This path does
 *                 not end with a backslash unless the system directory is the
 *                 root directory. For example, if the system directory is
 *                 named Windows\System32 on drive C, the path of the system
 *                 directory retrieved by this function is C:\Windows\System32.
 * @param uSize The maximum size of the buffer, in TCHARs.
 * @param pReturnSize The return value is the length, in TCHARs, of the string
 *                    copied to the buffer, not including the terminating null
 *                    character. If the length is greater than the size of the
 *                    buffer, the return value is the size of the buffer
 *                    required to hold the path, including the terminating null
 *                    character.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetSystemDirectoryW.
 */
EXTERN_C HRESULT WINAPI MileGetSystemDirectory(
    _Out_opt_ LPWSTR lpBuffer,
    _In_ UINT uSize,
    _Out_opt_ LPUINT pReturnSize);

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Retrieves the path of the shared Windows directory on a multi-user system.
 *
 * @param lpBuffer A pointer to the buffer to receive the path. This path does
 *                 not end with a backslash unless the Windows directory is the
 *                 root directory. For example, if the Windows directory is
 *                 named Windows on drive C, the path of the Windows directory
 *                 retrieved by this function is C:\Windows. If the system was
 *                 installed in the root directory of drive C, the path
 *                 retrieved is C:.
 * @param uSize The maximum size of the buffer specified by the lpBuffer
 *              parameter, in TCHARs.
 * @param pReturnSize The length of the string copied to the buffer, in TCHARs,
 *                    not including the terminating null character. If the
 *                    length is greater than the size of the buffer, the return
 *                    value is the size of the buffer required to hold the
 *                    path.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetSystemWindowsDirectoryW.
 */
EXTERN_C HRESULT WINAPI MileGetWindowsDirectory(
    _Out_opt_ LPWSTR lpBuffer,
    _In_ UINT uSize,
    _Out_opt_ LPUINT pReturnSize);

#endif

#endif // !MILE_WINDOWS
