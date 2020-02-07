/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.h
 * PURPOSE:   Mouri Internal Library Essentials Definition for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS
#define MILE_WINDOWS

#include <Windows.h>

/**
 * Retrieves a handle to the default heap of the calling process. This handle
 * can then be used in subsequent calls to the heap functions.
 *
 * @return The handle to the calling process's heap.
 * @remark For more information, see GetProcessHeap.
 */
EXTERN_C HANDLE WINAPI MileGetProcessHeap();

/**
 * Allocates a block of memory from a heap. The allocated memory is not
 * movable.
 *
 * @param hHeap A handle to the heap from which the memory will be allocated.
 * @param dwFlags The heap allocation options.
 * @param dwBytes The number of bytes to be allocated.
 * @param lpNewMem A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapAlloc.
 */
EXTERN_C HRESULT WINAPI MileHeapAlloc(
    _In_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ SIZE_T dwBytes,
    _Out_ LPVOID* lpNewMem);

/**
 * Reallocates a block of memory from a heap. This function enables you to
 * resize a memory block and change other memory block properties. The
 * allocated memory is not movable.
 *
 * @param hHeap A handle to the heap from which the memory is to be
 *              reallocated.
 * @param dwFlags The heap reallocation options.
 * @param lpMem A pointer to the block of memory that the function reallocates.
 *              This pointer is returned by an earlier call to the
 *              MileHeapAlloc or MileHeapReAlloc function.
 * @param dwBytes The new size of the memory block, in bytes. A memory block's
 *                size can be increased or decreased by using this function.
 * @param lpNewMem A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 * @remark For more information, see HeapReAlloc.
 */
EXTERN_C HRESULT WINAPI MileHeapReAlloc(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem,
    _In_ SIZE_T dwBytes,
    _Out_ LPVOID* lpNewMem);

/**
 * Frees a memory block allocated from a heap by the MileHeapAlloc or
 * MileHeapReAlloc function.
 *
 * @param hHeap A handle to the heap whose memory block is to be freed.
 * @param dwFlags The heap free options.
 * @param lpMem A pointer to the memory block to be freed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapFree.
 */
EXTERN_C HRESULT WINAPI MileHeapFree(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem);

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
    _Out_ LPSC_HANDLE phSCManager);

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
    _Out_ LPSC_HANDLE phService);

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
    _Out_ PHANDLE ProcessHandle);

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
    _Out_ PHANDLE ThreadHandle);

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

#endif // !MILE_WINDOWS
