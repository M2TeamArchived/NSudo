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

#include <Windows.h>

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
 * NSudo Shared Library Interface V1
 */
MIDL_INTERFACE("8BD99D5D-2811-4036-A21E-63328115B364")
INSudoClient : public IUnknown
{
public:

    /**
     * Allocates a block of memory from the default heap of the calling
     * process. The allocated memory will be initialized to zero. The
     * allocated memory is not movable.
     *
     * @param Size The number of bytes to be allocated.
     * @param Block A pointer to the allocated memory block.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     */
    virtual HRESULT STDMETHODCALLTYPE AllocMemory(
         _In_ SIZE_T Size,
         _Out_ LPVOID* Block) = 0;

    /**
     * Reallocates a block of memory from the default heap of the calling
     * process. If the reallocation request is for a larger size, the
     * additional region of memory beyond the original size be initialized
     * to zero. This function enables you to resize a memory block and change
     * other memory block properties. The allocated memory is not movable.
     *
     * @param OldBlock A pointer to the block of memory that the function
     *                 reallocates. This pointer is returned by an earlier
     *                 call to the AllocMemory or ReAllocMemory method.
     * @param NewSize The new size of the memory block, in bytes. A memory
     *                block's size can be increased or decreased by using
     *                this function.
     * @param NewBlock A pointer to the allocated memory block.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     *         If the function fails, the original memory is not freed, and
     *         the original handle and pointer are still valid.
     */
    virtual HRESULT STDMETHODCALLTYPE ReAllocMemory(
        _In_ PVOID OldBlock,
        _In_ SIZE_T NewSize,
        _Out_ PVOID* NewBlock) = 0;

    /**
     * Frees a memory block allocated from a heap by the AllocMemory or
     * ReAllocMemory method.
     *
     * @param Block A pointer to the memory block to be freed. This pointer is
     *              returned by the AllocMemory or ReAllocMemory method. If
     *              this pointer is nullptr, the behavior is undefined.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     */
    virtual HRESULT STDMETHODCALLTYPE FreeMemory(
        _In_ LPVOID Block) = 0;

    /**
     * Retrieves a specified type of information about an access token. The
     * calling process must have appropriate access rights to obtain the
     * information.
     *
     * @param TokenHandle A handle to an access token from which information is
     *                    retrieved.
     * @param TokenInformationClass Specifies a value from the
     *                              TOKEN_INFORMATION_CLASS enumerated type to
     *                              identify the type of information the
     *                              function retrieves.
     * @param TokenInformation A pointer to a buffer the function fills with
     *                         the requested information.
     * @param TokenInformationLength Specifies the size, in bytes, of the
     *                               buffer pointed to by the TokenInformation
     *                               parameter.
     * @param ReturnLength A pointer to a variable that receives the number of
     *                     bytes needed for the buffer pointed to by the
     *                     TokenInformation parameter.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see GetTokenInformation.
     */
    virtual HRESULT STDMETHODCALLTYPE GetTokenInformation(
        _In_ HANDLE TokenHandle,
        _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
        _Out_opt_ LPVOID TokenInformation,
        _In_ DWORD TokenInformationLength,
        _Out_ PDWORD ReturnLength) = 0;

    /**
     * Retrieves a specified type of information about an access token. The
     * calling process must have appropriate access rights to obtain the
     * information.
     *
     * @param TokenHandle A handle to an access token from which information is
     *                    retrieved.
     * @param TokenInformationClass Specifies a value from the
     *                              TOKEN_INFORMATION_CLASS enumerated type to
     *                              identify the type of information the
     *                              function retrieves.
     * @param OutputInformation A pointer to a buffer the function fills with
     *                          the requested information. When you have
     *                          finished using the information, free it by
     *                          calling the FreeMemory method. You should also
     *                          set the pointer to NULL.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see GetTokenInformation.
     */
    virtual HRESULT STDMETHODCALLTYPE GetTokenInformationWithMemory(
        _In_ HANDLE TokenHandle,
        _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
        _Out_ PVOID* OutputInformation) = 0;

    /**
     * Sets various types of information for a specified access token. The
     * information that this function sets replaces existing information. The
     * calling process must have appropriate access rights to set the
     * information.
     *
     * @param TokenHandle A handle to the access token for which information is
     *                    to be set.
     * @param TokenInformationClass A value from the TOKEN_INFORMATION_CLASS
     *                              enumerated type that identifies the type of
     *                              information the function sets. The valid
     *                              values from TOKEN_INFORMATION_CLASS are
     *                              described in the TokenInformation
     *                              parameter.
     * @param TokenInformation A pointer to a buffer that contains the
     *                         information set in the access token.
     * @param TokenInformationLength Specifies the length, in bytes, of the
     *                               buffer pointed to by TokenInformation.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see SetTokenInformation.
     */
    virtual HRESULT STDMETHODCALLTYPE SetTokenInformation(
        _In_ HANDLE TokenHandle,
        _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
        _In_ LPVOID TokenInformation,
        _In_ DWORD TokenInformationLength) = 0;

    /**
     * Enables or disables privileges in the specified access token.
     *
     * @param TokenHandle A handle to the access token that contains the
     *                    privileges to be modified. The handle must have
     *                    TOKEN_ADJUST_PRIVILEGES access to the token.
     * @param Privileges A pointer to an array of LUID_AND_ATTRIBUTES
     *                   structures that specifies an array of privileges
     *                   and their attributes. Each structure contains the
     *                   LUID and attributes of a privilege. To get the name
     *                   of the privilege associated with a LUID, call the
     *                   GetPrivilegeValue method, passing the address of the
     *                   LUID as the value of the lpLuid parameter. The
     *                   attributes of a privilege can be a combination of the
     *                   following values.
     *                   SE_PRIVILEGE_ENABLED
     *                       The function enables the privilege.
     *                   SE_PRIVILEGE_REMOVED
     *                       The privilege is removed from the list of
     *                       privileges in the token.
     *                   None
     *                       The function disables the privilege.
     * @param PrivilegeCount The number of entries in the Privileges array.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see AdjustTokenPrivileges.
     */
    virtual HRESULT STDMETHODCALLTYPE AdjustTokenPrivileges(
        _In_ HANDLE TokenHandle,
        _In_ PLUID_AND_ATTRIBUTES Privileges,
        _In_ DWORD PrivilegeCount) = 0;

    /**
     * Enables or disables all privileges in the specified access token.
     *
     * @param TokenHandle A handle to the access token that contains the
     *                    privileges to be modified. The handle must have
     *                    TOKEN_ADJUST_PRIVILEGES access to the token.
     * @param Attributes The attributes of all privileges can be a combination
     *                   of the following values.
     *                   SE_PRIVILEGE_ENABLED
     *                       The function enables the privilege.
     *                   SE_PRIVILEGE_REMOVED
     *                       The privilege is removed from the list of
     *                       privileges in the token.
     *                   None
     *                       The function disables the privilege.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     */
    virtual HRESULT STDMETHODCALLTYPE AdjustTokenAllPrivileges(
        _In_ HANDLE TokenHandle,
        _In_ DWORD Attributes) = 0;

    /**
     * Allocates and initializes a mandatory label security identifier (SID).
     *
     * @param MandatoryLabelType A value from the NSUDO_MANDATORY_LABEL_TYPE
     *                           enumerated type that identifies the
     *                           mandatory label.
     * @param MandatoryLabelSid A pointer to a variable that receives the
     *                          pointer to the allocated and initialized
     *                          mandatory label SID structure.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark A SID allocated with the CreateMandatoryLabelSid method must be
     *         freed by using the FreeSid function.
     */
    virtual HRESULT STDMETHODCALLTYPE CreateMandatoryLabelSid(
        _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType,
        _Out_ PSID* MandatoryLabelSid) = 0;

    /**
     * Sets mandatory label for a specified access token. The information that
     * this function sets replaces existing information. The calling process
     * must have appropriate access rights to set the information.
     *
     * @param TokenHandle A handle to the access token for which information is
     *                    to be set.
     * @param MandatoryLabelType A value from the NSUDO_MANDATORY_LABEL_TYPE
     *                           enumerated type that identifies the
     *                           mandatory label.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     */
    virtual HRESULT STDMETHODCALLTYPE SetTokenMandatoryLabel(
        _In_ HANDLE TokenHandle,
        _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType) = 0;

    /**
     * Starts a service if not started and retrieves the current status of the
     * specified service.
     *
     * @param ServiceName The name of the service to be started. This is the
     *                    name specified by the ServiceName parameter of the
     *                    CreateService function when the service object was
     *                    created, not the service display name that is shown by
     *                    user interface applications to identify the service.
     *                    The maximum string length is 256 characters. The
     *                    service control manager database preserves the case of
     *                    the characters, but service name comparisons are
     *                    always case insensitive. Forward-slash (/) and
     *                    backslash (\) are invalid service name characters.
     * @param ServiceStatus A pointer to the process status information for a
     *                      service.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     */
    virtual HRESULT STDMETHODCALLTYPE StartWindowsService(
        _In_ LPCWSTR ServiceName,
        _Out_ LPSERVICE_STATUS_PROCESS ServiceStatus) = 0;

    /**
     * Obtains the primary access token of the logged-on user specified by the
     * session ID. To call this function successfully, the calling application
     * must be running within the context of the LocalSystem account and have
     * the SE_TCB_NAME privilege.
     *
     * @param SessionId A Remote Desktop Services session identifier.
     * @param TokenHandle If the function succeeds, receives a pointer to the
     *                    token handle for the logged-on user. Note that you
     *                    must call the CloseHandle function to close this
     *                    handle.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see WTSQueryUserToken.
     */
    virtual HRESULT STDMETHODCALLTYPE CreateSessionToken(
        _In_ DWORD SessionId,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Creates a new access token that is a restricted version of an
     * existing access token. The restricted token can have disabled
     * security identifiers (SIDs), deleted privileges, and a list of
     * restricting SIDs. For more information, see Restricted Tokens.
     *
     * @param ExistingTokenHandle A handle to a primary or impersonation token.
     *                            The token can also be a restricted token. The
     *                            handle must have TOKEN_DUPLICATE access to
     *                            the token.
     * @param Flags Specifies additional privilege options. This parameter can
     *              be zero or a combination of the following values.
     *              DISABLE_MAX_PRIVILEGE
     *                  Disables all privileges in the new token except the
     *                  SeChangeNotifyPrivilege privilege. If this value is
     *                  specified, the DeletePrivilegeCount and
     *                  PrivilegesToDelete parameters are ignored.
     *              SANDBOX_INERT
     *                  If this value is used, the system does not check
     *                  AppLocker rules or apply Software Restriction
     *                  Policies. For AppLocker, this flag disables checks
     *                  for all four rule collections: Executable, Windows
     *                  Installer, Script, and DLL.
     *              LUA_TOKEN
     *                  The new token is a LUA token.
     *              WRITE_RESTRICTED
     *                  The new token contains restricting SIDs that are
     *                  considered only when evaluating write access.
     * @param DisableSidCount Specifies the number of entries in the
     *                        SidsToDisable array.
     * @param SidsToDisable A pointer to an array of SID_AND_ATTRIBUTES
     *                      structures that specify the deny-only SIDs
     *                      in the restricted token.
     * @param DeletePrivilegeCount Specifies the number of entries in the
     *                             PrivilegesToDelete array.
     * @param PrivilegesToDelete A pointer to an array of LUID_AND_ATTRIBUTES
     *                           structures that specify the privileges to
     *                           delete in the restricted token.
     * @param RestrictedSidCount Specifies the number of entries in the
     *                           SidsToRestrict array.
     * @param SidsToRestrict A pointer to an array of SID_AND_ATTRIBUTES
     *                       structures that specify a list of restricting
     *                       SIDs for the new token.
     * @param NewTokenHandle A pointer to a variable that receives a handle to
     *                       the new restricted token.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see CreateRestrictedToken.
     */
    virtual HRESULT STDMETHODCALLTYPE CreateRestrictedToken(
        _In_ HANDLE ExistingTokenHandle,
        _In_ DWORD Flags,
        _In_ DWORD DisableSidCount,
        _In_opt_ PSID_AND_ATTRIBUTES SidsToDisable,
        _In_ DWORD DeletePrivilegeCount,
        _In_opt_ PLUID_AND_ATTRIBUTES PrivilegesToDelete,
        _In_ DWORD RestrictedSidCount,
        _In_opt_ PSID_AND_ATTRIBUTES SidsToRestrict,
        _Out_ PHANDLE NewTokenHandle) = 0;

    /**
     * Creates a new access token that is a LUA version of an existing access
     * token.
     *
     * @param ExistingTokenHandle A handle to a primary or impersonation token.
     *                            The token can also be a restricted token. The
     *                            handle must have TOKEN_DUPLICATE access to
     *                            the token.
     * @param TokenHandle A pointer to a variable that receives a handle to the
     *                    new restricted token.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     */
    virtual HRESULT STDMETHODCALLTYPE CreateLUAToken(
        _In_ HANDLE ExistingTokenHandle,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Assigns an impersonation token to a thread. The function can also cause
     * a thread to stop using an impersonation token.
     *
     * @param TokenHandle A handle to the impersonation token to assign to the
     *                    thread. If TokenHandle is NULL, the function causes
     *                    the thread to stop using an impersonation token.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see SetThreadToken.
     */
    virtual HRESULT STDMETHODCALLTYPE SetCurrentThreadToken(
        _In_opt_ HANDLE TokenHandle) = 0;

    /**
     * Creates a new access token that duplicates an existing token. This
     * function can create either a primary token or an impersonation token.
     *
     * @param ExistingTokenHandle A handle to an access token opened with
     *                            TOKEN_DUPLICATE access.
     * @param DesiredAccess Specifies the requested access rights for the new
     *                      token. To request all access rights that are valid
     *                      for the caller, specify MAXIMUM_ALLOWED.
     * @param TokenAttributes A pointer to a SECURITY_ATTRIBUTES structure that
     *                        specifies a security descriptor for the new token
     *                        and determines whether child processes can
     *                        inherit the token.
     * @param ImpersonationLevel Specifies a value from the
     *                           SECURITY_IMPERSONATION_LEVEL enumeration that
     *                           indicates the impersonation level of the new
     *                           token.
     * @param TokenType Specifies one of the following values from the
     *                  TOKEN_TYPE enumeration.
     *                  TokenPrimary
     *                      The new token is a primary token that you can use
     *                      in the CreateProcessAsUser function.
     *                  TokenImpersonation
     *                      The new token is an impersonation token.
     * @param NewTokenHandle A pointer to a handle variable that receives the
     *                       new token.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see DuplicateTokenEx.
     */
    virtual HRESULT STDMETHODCALLTYPE DuplicateToken(
        _In_ HANDLE ExistingTokenHandle,
        _In_ DWORD DesiredAccess,
        _In_opt_ LPSECURITY_ATTRIBUTES TokenAttributes,
        _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
        _In_ TOKEN_TYPE TokenType,
        _Out_ PHANDLE NewTokenHandle) = 0;

    /**
     * Opens an existing local process object.
     *
     * @param DesiredAccess The access to the process object. This access right
     *                      is checked against the security descriptor for the
     *                      process. This parameter can be one or more of the
     *                      process access rights.
     * @param InheritHandle If this value is TRUE, processes created by this
     *                      process will inherit the handle. Otherwise, the
     *                      processes do not inherit this handle.
     * @param ProcessId The identifier of the local process to be opened.
     * @param ProcessHandle A pointer to an open handle to the specified
     *                      process.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenProcess.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenProcess(
        _In_ DWORD DesiredAccess,
        _In_ BOOL InheritHandle,
        _In_ DWORD ProcessId,
        _Out_ PHANDLE ProcessHandle) = 0;

    /**
     * Opens an existing local process object associated with a service
     * process, the calling application must be running within the context
     * of the Administrator account and have the SE_DEBUG_NAME privilege
     * enabled.
     *
     * @param DesiredAccess The access to the process object. This access right
     *                      is checked against the security descriptor for the
     *                      process. This parameter can be one or more of the
     *                      process access rights.
     * @param InheritHandle If this value is TRUE, processes created by this
     *                      process will inherit the handle. Otherwise, the
     *                      processes do not inherit this handle.
     * @param ServiceName The name of the service to be started. This is the
     *                    name specified by the ServiceName parameter of the
     *                    CreateService function when the service object was
     *                    created, not the service display name that is shown by
     *                    user interface applications to identify the service.
     *                    The maximum string length is 256 characters. The
     *                    service control manager database preserves the case of
     *                    the characters, but service name comparisons are
     *                    always case insensitive. Forward-slash (/) and
     *                    backslash (\) are invalid service name characters.
     * @param ProcessHandle A pointer to an open handle to the specified
     *                      process.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenProcess.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenServiceProcess(
        _In_ DWORD DesiredAccess,
        _In_ BOOL InheritHandle,
        _In_ LPCWSTR ServiceName,
        _Out_ PHANDLE ProcessHandle) = 0;

    /**
     * Opens an existing local process object associated with the Local
     * Security Authority process, the calling application must be running
     * within the context of the Administrator account and have the
     * SE_DEBUG_NAME privilege enabled.
     *
     * @param DesiredAccess The access to the process object. This access right
     *                      is checked against the security descriptor for the
     *                      process. This parameter can be one or more of the
     *                      process access rights.
     * @param InheritHandle If this value is TRUE, processes created by this
     *                      process will inherit the handle. Otherwise, the
     *                      processes do not inherit this handle.
     * @param ProcessHandle A pointer to an open handle to the specified
     *                      process.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenProcess.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenLsassProcess(
        _In_ DWORD DesiredAccess,
        _In_ BOOL InheritHandle,
        _Out_ PHANDLE ProcessHandle) = 0;

    /**
     * Opens the access token associated with a process.
     *
     * @param ProcessHandle A handle to the process whose access token is
     *                      opened. The process must have the
     *                      PROCESS_QUERY_INFORMATION access permission.
     * @param DesiredAccess The access to the process object. This access right
     *                      is checked against the security descriptor for the
     *                      process. This parameter can be one or more of the
     *                      process access rights.
     * @param TokenHandle A pointer to a handle that identifies the newly
     *                    opened access token when the function returns.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenProcessToken.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenProcessTokenByProcessHandle(
        _In_ HANDLE ProcessHandle,
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Opens the access token associated with the current process.
     *
     * @param DesiredAccess The access to the process object. This access right
     *                      is checked against the security descriptor for the
     *                      process. This parameter can be one or more of the
     *                      process access rights.
     * @param TokenHandle A pointer to a handle that identifies the newly
     *                    opened access token when the function returns.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenProcessToken.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenCurrentProcessToken(
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Opens the access token associated with a process.
     *
     * @param ProcessId The identifier of the local process to be opened.
     * @param DesiredAccess The access to the process object. This access right
     *                      is checked against the security descriptor for the
     *                      process. This parameter can be one or more of the
     *                      process access rights.
     * @param TokenHandle A pointer to a handle that identifies the newly
     *                    opened access token when the function returns.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenProcessToken.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenProcessTokenByProcessId(
        _In_ DWORD ProcessId,
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Opens the access token associated with a service process, the calling
     * application must be running within the context of the Administrator
     * account and have the SE_DEBUG_NAME privilege enabled.
     *
     * @param ServiceName The name of the service to be started. This is the
     *                    name specified by the ServiceName parameter of the
     *                    CreateService function when the service object was
     *                    created, not the service display name that is shown by
     *                    user interface applications to identify the service.
     *                    The maximum string length is 256 characters. The
     *                    service control manager database preserves the case of
     *                    the characters, but service name comparisons are
     *                    always case insensitive. Forward-slash (/) and
     *                    backslash (\) are invalid service name characters.
     * @param DesiredAccess The access to the process object. This access right
     *                      is checked against the security descriptor for the
     *                      process. This parameter can be one or more of the
     *                      process access rights.
     * @param TokenHandle A pointer to a handle that identifies the newly
     *                    opened access token when the function returns.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenProcessToken.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenServiceProcessToken(
        _In_ LPCWSTR ServiceName,
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Opens the access token associated with the Local Security Authority
     * process, the calling application must be running within the context
     * of the Administrator account and have the SE_DEBUG_NAME privilege
     * enabled.
     *
     * @param DesiredAccess The access to the process object. This access right
     *                      is checked against the security descriptor for the
     *                      process. This parameter can be one or more of the
     *                      process access rights.
     * @param TokenHandle A pointer to a handle that identifies the newly
     *                    opened access token when the function returns.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenProcessToken.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenLsassProcessToken(
        _In_ DWORD DesiredAccess,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Opens an existing thread object.
     *
     * @param DesiredAccess The access to the thread object. This access right
     *                      is checked against the security descriptor for the
     *                      thread. This parameter can be one or more of the
     *                      thread access rights.
     * @param InheritHandle If this value is TRUE, processes created by this
     *                      process will inherit the handle. Otherwise, the
     *                      processes do not inherit this handle.
     * @param ThreadId The identifier of the thread to be opened.
     * @param ThreadHandle A pointer to an open handle to the specified thread.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenThread.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenThread(
        _In_ DWORD DesiredAccess,
        _In_ BOOL InheritHandle,
        _In_ DWORD ThreadId,
        _Out_ PHANDLE ThreadHandle) = 0;

    /**
     * Opens the access token associated with a thread.
     *
     * @param ThreadHandle A handle to the thread whose access token is opened.
     * @param DesiredAccess Specifies an access mask that specifies the
     *                      requested types of access to the access token.
     *                      These requested access types are reconciled
     *                      against the token's discretionary access control
     *                      list (DACL) to determine which accesses are granted
     *                      or denied.
     * @param OpenAsSelf TRUE if the access check is to be made against the
     *                   process-level security context. FALSE if the access
     *                   check is to be made against the current security
     *                   context of the thread calling the OpenThreadToken
     *                   function.
     * @param TokenHandle A pointer to a variable that receives the handle to
     *                    the newly opened access token.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenThreadToken.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenThreadTokenByThreadHandle(
        _In_ HANDLE ThreadHandle,
        _In_ DWORD DesiredAccess,
        _In_ BOOL OpenAsSelf,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Opens the access token associated with the current thread.
     *
     * @param DesiredAccess Specifies an access mask that specifies the
     *                      requested types of access to the access token.
     *                      These requested access types are reconciled
     *                      against the token's discretionary access control
     *                      list (DACL) to determine which accesses are granted
     *                      or denied.
     * @param OpenAsSelf TRUE if the access check is to be made against the
     *                   process-level security context. FALSE if the access
     *                   check is to be made against the current security
     *                   context of the thread calling the OpenThreadToken
     *                   function.
     * @param TokenHandle A pointer to a variable that receives the handle to
     *                    the newly opened access token.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenThreadToken.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenCurrentThreadToken(
        _In_ DWORD DesiredAccess,
        _In_ BOOL OpenAsSelf,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Opens the access token associated with a thread.
     *
     * @param ThreadId The identifier of the thread to be opened.
     * @param DesiredAccess Specifies an access mask that specifies the
     *                      requested types of access to the access token.
     *                      These requested access types are reconciled
     *                      against the token's discretionary access control
     *                      list (DACL) to determine which accesses are granted
     *                      or denied.
     * @param OpenAsSelf TRUE if the access check is to be made against the
     *                   process-level security context. FALSE if the access
     *                   check is to be made against the current security
     *                   context of the thread calling the OpenThreadToken
     *                   function.
     * @param TokenHandle A pointer to a variable that receives the handle to
     *                    the newly opened access token.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see OpenThreadToken.
     */
    virtual HRESULT STDMETHODCALLTYPE OpenThreadTokenByThreadId(
        _In_ DWORD ThreadId,
        _In_ DWORD DesiredAccess,
        _In_ BOOL OpenAsSelf,
        _Out_ PHANDLE TokenHandle) = 0;

    /**
     * Retrieves the locally unique identifier (LUID) used on the local system
     * to locally represent the specified privilege name.
     *
     * @param Name A pointer to a null-terminated string that specifies the
     *             name of the privilege, as defined in the Winnt.h header
     *             file. For example, this parameter could specify the
     *             constant, SE_SECURITY_NAME, or its corresponding string,
     *             "SeSecurityPrivilege".
     * @param Value A pointer to a variable that receives the LUID by which the
     *              privilege is known on the local system.
     * @return HRESULT. If the method succeeds, the return value is S_OK.
     * @remark For more information, see LookupPrivilegeValue.
     */
    virtual HRESULT STDMETHODCALLTYPE GetPrivilegeValue(
        _In_ LPCWSTR Name,
        _Out_ PLUID Value) = 0;
};

/**
 * NSudo Shared Library Interface V1 Interface ID
 * {8BD99D5D-2811-4036-A21E-63328115B364}
 */
EXTERN_C const IID DECLSPEC_SELECTANY IID_INSudoClient =
{
    0x8BD99D5D,
    0x2811,
    0x4036,
    0xA2,
    0x1E,
    0x63,
    0x32,
    0x81,
    0x15,
    0xB3,
    0x64
};

/**
 * Creates an interface object and returns a pointer to it.
 *
 * @param InterfaceId The Interface ID being requested.
 * @param Instance A location to store the interface pointer to return.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI NSudoCreateInstance(
    _In_ REFIID InterfaceId,
    _Out_ PVOID* Instance);

#endif
