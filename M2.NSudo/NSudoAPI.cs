using System;
using System.Runtime.InteropServices;

namespace M2.NSudo
{
    public enum TOKEN_INFORMATION_CLASS
    {
        TokenUser = 1,
        TokenGroups,
        TokenPrivileges,
        TokenOwner,
        TokenPrimaryGroup,
        TokenDefaultDacl,
        TokenSource,
        TokenType,
        TokenImpersonationLevel,
        TokenStatistics,
        TokenRestrictedSids,
        TokenSessionId,
        TokenGroupsAndPrivileges,
        TokenSessionReference,
        TokenSandBoxInert,
        TokenAuditPolicy,
        TokenOrigin,
        TokenElevationType,
        TokenLinkedToken,
        TokenElevation,
        TokenHasRestrictions,
        TokenAccessInformation,
        TokenVirtualizationAllowed,
        TokenVirtualizationEnabled,
        TokenIntegrityLevel,
        TokenUIAccess,
        TokenMandatoryPolicy,
        TokenLogonSid,
        TokenIsAppContainer,
        TokenCapabilities,
        TokenAppContainerSid,
        TokenAppContainerNumber,
        TokenUserClaimAttributes,
        TokenDeviceClaimAttributes,
        TokenRestrictedUserClaimAttributes,
        TokenRestrictedDeviceClaimAttributes,
        TokenDeviceGroups,
        TokenRestrictedDeviceGroups,
        TokenSecurityAttributes,
        TokenIsRestricted,
        TokenProcessTrustLevel,
        TokenPrivateNameSpace,
        TokenSingletonAttributes,
        TokenBnoIsolation,
        TokenChildProcessFlags,
        TokenIsLessPrivilegedAppContainer,
        TokenIsSandboxed,
        TokenOriginatingProcessTrustLevel,
        MaxTokenInfoClass
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct LUID
    {
        public UInt32 LowPart;
        public Int32 HighPart;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 4)]
    public struct LUID_AND_ATTRIBUTES
    {
        public LUID Luid;
        public UInt32 Attributes;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct SERVICE_STATUS_PROCESS
    {
        public int serviceType;
        public int currentState;
        public int controlsAccepted;
        public int win32ExitCode;
        public int serviceSpecificExitCode;
        public int checkPoint;
        public int waitHint;
        public int processID;
        public int serviceFlags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SID_AND_ATTRIBUTES
    {
        public IntPtr Sid;
        public uint Attributes;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SECURITY_ATTRIBUTES
    {
        public int nLength;
        public IntPtr lpSecurityDescriptor;
        public int bInheritHandle;
    }

    public enum SECURITY_IMPERSONATION_LEVEL
    {
        SecurityAnonymous,
        SecurityIdentification,
        SecurityImpersonation,
        SecurityDelegation
    }

    public enum TOKEN_TYPE
    {
        TokenPrimary = 1,
        TokenImpersonation
    }

    /// <summary>
    /// Contains values that specify the type of mandatory label.
    /// </summary>
    public enum NSUDO_MANDATORY_LABEL_TYPE
    {
        UNTRUSTED,
        LOW,
        MEDIUM,
        MEDIUM_PLUS,
        HIGH,
        SYSTEM,
        PROTECTED_PROCESS,
    }

    /// <summary>
    /// NSudo Shared Library Client Interface V1
    /// </summary>
    [Guid("8BD99D5D-2811-4036-A21E-63328115B364")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface INSudoClient
    {
        /// <summary>
        /// Allocates a block of memory from the default heap of the calling 
        /// process. The allocated memory will be initialized to zero. The 
        /// allocated memory is not movable.
        /// </summary>
        /// <param name="Size">
        /// The number of bytes to be allocated.
        /// </param>
        /// <returns>
        /// A pointer to the allocated memory block.
        /// </returns>
        public IntPtr AllocMemory(
            int Size);

        /// <summary>
        /// Reallocates a block of memory from the default heap of the calling 
        /// process. If the reallocation request is for a larger size, the 
        /// additional region of memory beyond the original size be initialized
        /// to zero. This function enables you to resize a memory block and 
        /// change other memory block properties.The allocated memory is not 
        /// movable.
        /// </summary>
        /// <param name="OldBlock">
        /// A pointer to the block of memory that the function reallocates. 
        /// This pointer is returned by an earlier call to the AllocMemory or 
        /// ReAllocMemory method.
        /// </param>
        /// <param name="NewSize">
        /// The new size of the memory block, in bytes. A memory block's size 
        /// can be increased or decreased by using this function.
        /// </param>
        /// <returns>
        /// A pointer to the allocated memory block. If the function fails, the
        /// original memory is not freed, and the original handle and pointer 
        /// are still valid.
        /// </returns>
        public IntPtr ReAllocMemory(
            IntPtr OldBlock,
            int NewSize);

        /// <summary>
        /// Frees a memory block allocated from a heap by the AllocMemory or 
        /// ReAllocMemory method.
        /// </summary>
        /// <param name="Block">
        /// A pointer to the memory block to be freed. This pointer is returned
        /// by the AllocMemory or ReAllocMemory method. If this pointer is 
        /// nullptr, the behavior is undefined.
        /// </param>
        public void FreeMemory(
            IntPtr Block);

        /// <summary>
        /// Retrieves a specified type of information about an access token. 
        /// The calling process must have appropriate access rights to obtain
        /// the information.
        /// </summary>
        /// <param name="TokenHandle">
        /// A handle to an access token from which information is retrieved.
        /// </param>
        /// <param name="TokenInformationClass">
        /// Specifies a value from the TOKEN_INFORMATION_CLASS enumerated type 
        /// to identify the type of information the function retrieves.
        /// </param>
        /// <param name="TokenInformation">
        /// A pointer to a buffer the function fills with the requested 
        /// information.
        /// </param>
        /// <param name="TokenInformationLength">
        /// Specifies the size, in bytes, of the buffer pointed to by the 
        /// TokenInformation parameter.
        /// </param>
        /// <returns>
        /// A variable that receives the number of bytes needed for the buffer 
        /// pointed to by the TokenInformation parameter.
        /// </returns>
        /// <remarks>
        /// For more information, see GetTokenInformation.
        /// </remarks>
        public UInt32 GetTokenInformation(
            IntPtr TokenHandle,
            TOKEN_INFORMATION_CLASS TokenInformationClass,
            out IntPtr TokenInformation,
            UInt32 TokenInformationLength);

        /// <summary>
        /// Retrieves a specified type of information about an access token. 
        /// The calling process must have appropriate access rights to obtain
        /// the information.
        /// </summary>
        /// <param name="TokenHandle">
        /// A handle to an access token from which information is retrieved.
        /// </param>
        /// <param name="TokenInformationClass">
        /// Specifies a value from the TOKEN_INFORMATION_CLASS enumerated type 
        /// to identify the type of information the function retrieves.
        /// </param>
        /// <returns>
        /// A pointer to a buffer the function fills with the requested 
        /// information. When you have finished using the information, free it
        /// by calling the FreeMemory method. You should also set the pointer 
        /// to NULL.
        /// </returns>
        /// <remarks>
        /// For more information, see GetTokenInformation.
        /// </remarks>
        public IntPtr GetTokenInformationWithMemory(
            IntPtr TokenHandle,
            TOKEN_INFORMATION_CLASS TokenInformationClass);

        /// <summary>
        /// Sets various types of information for a specified access token. The
        /// information that this function sets replaces existing information. 
        /// The calling process must have appropriate access rights to set the
        /// information.
        /// </summary>
        /// <param name="TokenHandle">
        /// A handle to the access token for which information is to be set.
        /// </param>
        /// <param name="TokenInformationClass">
        /// A value from the TOKEN_INFORMATION_CLASS enumerated type that 
        /// identifies the type of information the function sets. The valid 
        /// values from TOKEN_INFORMATION_CLASS are described in the 
        /// TokenInformation parameter.
        /// </param>
        /// <param name="TokenInformation">
        /// A pointer to a buffer that contains the information set in the 
        /// access token.
        /// </param>
        /// <param name="TokenInformationLength">
        /// Specifies the length, in bytes, of the buffer pointed to by 
        /// TokenInformation.
        /// </param>
        /// <remarks>
        /// For more information, see SetTokenInformation.
        /// </remarks>
        public void SetTokenInformation(
            IntPtr TokenHandle,
            TOKEN_INFORMATION_CLASS TokenInformationClass,
            IntPtr TokenInformation,
            UInt32 TokenInformationLength);

        /// <summary>
        /// Enables or disables privileges in the specified access token.
        /// </summary>
        /// <param name="TokenHandle">
        /// A handle to the access token that contains the privileges to be 
        /// modified. The handle must have TOKEN_ADJUST_PRIVILEGES access to 
        /// the token.
        /// </param>
        /// <param name="Privileges">
        /// A pointer to an array of LUID_AND_ATTRIBUTES structures that 
        /// specifies an array of privileges and their attributes. Each 
        /// structure contains the LUID and attributes of a privilege. To get
        /// the name of the privilege associated with a LUID, call the 
        /// GetPrivilegeValue method, passing the address of the LUID as the 
        /// value of the lpLuid parameter. The attributes of a privilege can be
        /// a combination of the following values.
        /// SE_PRIVILEGE_ENABLED
        ///     The function enables the privilege.
        /// SE_PRIVILEGE_REMOVED
        ///     The privilege is removed from the list of privileges in the token.
        /// None
        ///     The function disables the privilege.
        /// </param>
        /// <param name="PrivilegeCount">
        /// The number of entries in the Privileges array.
        /// </param>
        /// <remarks>
        /// For more information, see AdjustTokenPrivileges.
        /// </remarks>
        public void AdjustTokenPrivileges(
            IntPtr TokenHandle,
            ref LUID_AND_ATTRIBUTES Privileges,
            UInt32 PrivilegeCount);

        /// <summary>
        /// Enables or disables all privileges in the specified access token.
        /// </summary>
        /// <param name="TokenHandle">
        /// A handle to the access token that contains the privileges to be 
        /// modified. The handle must have TOKEN_ADJUST_PRIVILEGES access to 
        /// the token.
        /// </param>
        /// <param name="Attributes">
        /// The attributes of all privileges can be a combination of the 
        /// following values.
        /// SE_PRIVILEGE_ENABLED
        ///     The function enables the privilege.
        /// SE_PRIVILEGE_REMOVED
        ///     The privilege is removed from the list of privileges in the token.
        /// None
        ///     The function disables the privilege.
        /// </param>
        /// <remarks>
        /// For more information, see AdjustTokenPrivileges.
        /// </remarks>
        public void AdjustTokenAllPrivileges(
            IntPtr TokenHandle,
            UInt32 Attributes);

        /// <summary>
        /// Allocates and initializes a mandatory label security identifier 
        /// (SID).
        /// </summary>
        /// <param name="MandatoryLabelType">
        /// A value from the NSUDO_MANDATORY_LABEL_TYPE enumerated type that
        /// identifies the mandatory label.
        /// </param>
        /// <returns>
        /// A pointer to the allocated and initialized mandatory label SID 
        /// structure.
        /// </returns>
        /// <remarks>
        /// A SID allocated with the CreateMandatoryLabelSid method must be 
        /// freed by using the FreeSid function.
        /// </remarks>
        public IntPtr CreateMandatoryLabelSid(
            NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType);

        /// <summary>
        /// Sets mandatory label for a specified access token. The information 
        /// that this function sets replaces existing information. The calling 
        /// process must have appropriate access rights to set the information.
        /// </summary>
        /// <param name="TokenHandle">
        /// A handle to the access token for which information is to be set.
        /// </param>
        /// <param name="MandatoryLabelType">
        /// A value from the NSUDO_MANDATORY_LABEL_TYPE enumerated type that 
        /// identifies the mandatory label.
        /// </param>
        public void SetTokenMandatoryLabel(
            IntPtr TokenHandle,
            NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType);

        /// <summary>
        /// Starts a service if not started and retrieves the current status of
        /// the specified service.
        /// </summary>
        /// <param name="ServiceName">
        /// The name of the service to be started. This is the name specified 
        /// by the ServiceName parameter of the CreateService function when the
        /// service object was created, not the service display name that is 
        /// shown by user interface applications to identify the service. The 
        /// maximum string length is 256 characters. The service control 
        /// manager database preserves the case of the characters, but service 
        /// name comparisons are always case insensitive. Forward-slash (/) 
        /// and backslash (\) are invalid service name characters.
        /// </param>
        /// <returns>
        /// The process status information for a service.
        /// </returns>
        public SERVICE_STATUS_PROCESS StartWindowsService(
            [MarshalAs(UnmanagedType.LPWStr)] string ServiceName);

        /// <summary>
        /// A Remote Desktop Services session identifier.
        /// </summary>
        /// <param name="SessionId">
        /// Obtains the primary access token of the logged-on user specified by
        /// the session ID. To call this function successfully, the calling 
        /// application must be running within the context of the LocalSystem 
        /// account and have the SE_TCB_NAME privilege.
        /// </param>
        /// <returns>
        /// If the function succeeds, receives the token handle for the 
        /// logged-on user. Note that you must call the CloseHandle function to
        /// close this handle.
        /// </returns>
        /// <remarks>
        /// For more information, see WTSQueryUserToken.
        /// </remarks>
        public IntPtr CreateSessionToken(
            UInt32 SessionId);

        /// <summary>
        /// Creates a new access token that is a restricted version of an 
        /// existing access token. The restricted token can have disabled 
        /// security identifiers (SIDs), deleted privileges, and a list of 
        /// restricting SIDs. For more information, see Restricted Tokens.
        /// </summary>
        /// <param name="ExistingTokenHandle">
        /// A handle to a primary or impersonation token. The token can also be
        /// a restricted token. The handle must have TOKEN_DUPLICATE access to 
        /// the token.
        /// </param>
        /// <param name="Flags">
        /// Specifies additional privilege options. This parameter can be zero 
        /// or a combination of the following values.
        /// DISABLE_MAX_PRIVILEGE
        ///     Disables all privileges in the new token except the 
        ///     SeChangeNotifyPrivilege privilege. If this value is specified, 
        ///     the DeletePrivilegeCount and PrivilegesToDelete parameters are
        ///     ignored.
        /// SANDBOX_INERT
        ///     If this value is used, the system does not check AppLocker 
        ///     rules or apply Software Restriction Policies. For AppLocker, 
        ///     this flag disables checks for all four rule collections: 
        ///     Executable, Windows Installer, Script, and DLL.
        /// LUA_TOKEN
        ///     The new token is a LUA token.
        /// WRITE_RESTRICTED
        ///     The new token contains restricting SIDs that are considered 
        ///     only when evaluating write access.
        /// </param>
        /// <param name="DisableSidCount">
        /// Specifies the number of entries in the SidsToDisable array.
        /// </param>
        /// <param name="SidsToDisable">
        /// A pointer to an array of SID_AND_ATTRIBUTES structures that specify
        /// the deny-only SIDs in the restricted token.
        /// </param>
        /// <param name="DeletePrivilegeCount">
        /// Specifies the number of entries in the PrivilegesToDelete array.
        /// </param>
        /// <param name="PrivilegesToDelete">
        /// A pointer to an array of LUID_AND_ATTRIBUTES structures that 
        /// specify the privileges to delete in the restricted token.
        /// </param>
        /// <param name="RestrictedSidCount">
        /// Specifies the number of entries in the SidsToRestrict array.
        /// </param>
        /// <param name="SidsToRestrict">
        /// A pointer to an array of SID_AND_ATTRIBUTES structures that specify
        /// a list of restricting SIDs for the new token.
        /// </param>
        /// <returns>
        /// A variable that receives a handle to the new restricted token.
        /// </returns>
        /// <remarks>
        /// For more information, see CreateRestrictedToken.
        /// </remarks>
        public IntPtr CreateRestrictedToken(
            IntPtr ExistingTokenHandle,
            UInt32 Flags,
            UInt32 DisableSidCount,
            ref SID_AND_ATTRIBUTES SidsToDisable,
            UInt32 DeletePrivilegeCount,
            ref LUID_AND_ATTRIBUTES PrivilegesToDelete,
            UInt32 RestrictedSidCount,
            ref SID_AND_ATTRIBUTES SidsToRestrict);

        /// <summary>
        /// Creates a new access token that is a LUA version of an existing 
        /// access token.
        /// </summary>
        /// <param name="ExistingTokenHandle">
        /// ExistingTokenHandle A handle to a primary or impersonation token. 
        /// The token can also be a restricted token. The handle must have 
        /// TOKEN_DUPLICATE access to the token.
        /// </param>
        /// <returns>
        /// A variable that receives a handle to the new restricted token.
        /// </returns>
        public IntPtr CreateLUAToken(
            IntPtr ExistingTokenHandle);

        /// <summary>
        /// Assigns an impersonation token to a thread. The function can also
        /// cause a thread to stop using an impersonation token.
        /// </summary>
        /// <param name="TokenHandle">
        /// A handle to the impersonation token to assign to the thread. If 
        /// TokenHandle is NULL, the function causes the thread to stop using 
        /// an impersonation token.
        /// </param>
        /// <remarks>
        /// For more information, see SetThreadToken.
        /// </remarks>
        void SetCurrentThreadToken(
            IntPtr TokenHandle);

        /// <summary>
        /// Creates a new access token that duplicates an existing token. This 
        /// function can create either a primary token or an impersonation 
        /// token.
        /// </summary>
        /// <param name="ExistingTokenHandle">
        /// A handle to an access token opened with TOKEN_DUPLICATE access.
        /// </param>
        /// <param name="DesiredAccess">
        /// Specifies the requested access rights for the new token. To request
        /// all access rights that are valid for the caller, specify 
        /// MAXIMUM_ALLOWED.
        /// </param>
        /// <param name="TokenAttributes">
        /// A pointer to a SECURITY_ATTRIBUTES structure that specifies a 
        /// security descriptor for the new token and determines whether child
        /// processes can inherit the token.
        /// </param>
        /// <param name="ImpersonationLevel">
        /// Specifies a value from the SECURITY_IMPERSONATION_LEVEL enumeration
        /// that indicates the impersonation level of the new token.
        /// </param>
        /// <param name="TokenType">
        /// Specifies one of the following values from the TOKEN_TYPE 
        /// enumeration.
        /// TokenPrimary
        ///     The new token is a primary token that you can use in the 
        ///     CreateProcessAsUser function.
        /// TokenImpersonation
        ///     The new token is an impersonation token.
        /// </param>
        /// <returns>
        /// A handle variable that receives the new token.
        /// </returns>
        /// <remarks>
        /// For more information, see DuplicateTokenEx.
        /// </remarks>
        public IntPtr DuplicateToken(
            IntPtr ExistingTokenHandle,
            UInt32 DesiredAccess,
            ref SECURITY_ATTRIBUTES TokenAttributes,
            SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
            TOKEN_TYPE TokenType);

        /// <summary>
        /// Opens an existing local process object.
        /// </summary>
        /// <param name="DesiredAccess">
        /// The access to the process object. This access right is checked 
        /// against the security descriptor for the process. This parameter can
        /// be one or more of the process access rights.
        /// </param>
        /// <param name="InheritHandle">
        /// If this value is TRUE, processes created by this process will 
        /// inherit the handle. Otherwise, the processes do not inherit this 
        /// handle.
        /// </param>
        /// <param name="ProcessId">
        /// The identifier of the local process to be opened.
        /// </param>
        /// <returns>
        /// An open handle to the specified process.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenProcess.
        /// </remarks>
        public IntPtr OpenProcess(
            UInt32 DesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] bool InheritHandle,
            UInt32 ProcessId);

        /// <summary>
        /// Opens an existing local process object associated with a service 
        /// process, the calling application must be running within the context
        /// of the Administrator account and have the SE_DEBUG_NAME privilege 
        /// enabled.
        /// </summary>
        /// <param name="DesiredAccess">
        /// The access to the process object. This access right is checked 
        /// against the security descriptor for the process. This parameter can
        /// be one or more of the process access rights.
        /// </param>
        /// <param name="InheritHandle">
        /// If this value is TRUE, processes created by this process will 
        /// inherit the handle. Otherwise, the processes do not inherit this 
        /// handle.
        /// </param>
        /// <param name="ServiceName">
        /// The name of the service to be started. This is the name specified 
        /// by the ServiceName parameter of the CreateService function when the
        /// service object was created, not the service display name that is 
        /// shown by user interface applications to identify the service. The 
        /// maximum string length is 256 characters. The service control 
        /// manager database preserves the case of the characters, but service 
        /// name comparisons are always case insensitive. Forward-slash (/) 
        /// and backslash (\) are invalid service name characters.
        /// </param>
        /// <returns>
        /// An open handle to the specified process.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenProcess.
        /// </remarks>
        public IntPtr OpenServiceProcess(
            UInt32 DesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] bool InheritHandle,
            [MarshalAs(UnmanagedType.LPWStr)] string ServiceName);

        /// <summary>
        /// Opens an existing local process object associated with the Local 
        /// Security Authority process, the calling application must be running
        /// within the context of the Administrator account and have the 
        /// SE_DEBUG_NAME privilege enabled.
        /// </summary>
        /// <param name="DesiredAccess">
        /// The access to the process object. This access right is checked 
        /// against the security descriptor for the process. This parameter can
        /// be one or more of the process access rights.
        /// </param>
        /// <param name="InheritHandle">
        /// If this value is TRUE, processes created by this process will 
        /// inherit the handle. Otherwise, the processes do not inherit this 
        /// handle.
        /// </param>
        /// <returns>
        /// An open handle to the specified process.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenProcess.
        /// </remarks>
        public IntPtr OpenLsassProcess(
            UInt32 DesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] bool InheritHandle);

        /// <summary>
        /// Opens the access token associated with a process.
        /// </summary>
        /// <param name="ProcessHandle">
        /// A handle to the process whose access token is opened. The process 
        /// must have the PROCESS_QUERY_INFORMATION access permission.
        /// </param>
        /// <param name="DesiredAccess">
        /// The access to the process object. This access right is checked 
        /// against the security descriptor for the process. This parameter can
        /// be one or more of the process access rights.
        /// </param>
        /// <returns>
        /// A handle that identifies the newly opened access token when the 
        /// function returns.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenProcessToken.
        /// </remarks>
        public IntPtr OpenProcessTokenByProcessHandle(
            IntPtr ProcessHandle,
            UInt32 DesiredAccess);

        /// <summary>
        /// Opens the access token associated with the current process.
        /// </summary>
        /// <param name="DesiredAccess">
        /// The access to the process object. This access right is checked 
        /// against the security descriptor for the process. This parameter can
        /// be one or more of the process access rights.
        /// </param>
        /// <returns>
        /// A handle that identifies the newly opened access token when the 
        /// function returns.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenProcessToken.
        /// </remarks>
        public IntPtr OpenCurrentProcessToken(
            UInt32 DesiredAccess);

        /// <summary>
        /// Opens the access token associated with a process.
        /// </summary>
        /// <param name="ProcessId">
        /// The identifier of the local process to be opened.
        /// </param>
        /// <param name="DesiredAccess">
        /// The access to the process object. This access right is checked 
        /// against the security descriptor for the process. This parameter can
        /// be one or more of the process access rights.
        /// </param>
        /// <returns>
        /// A handle that identifies the newly opened access token when the 
        /// function returns.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenProcessToken.
        /// </remarks>
        public IntPtr OpenProcessTokenByProcessId(
            UInt32 ProcessId,
            UInt32 DesiredAccess);

        /// <summary>
        /// Opens the access token associated with a service process, the 
        /// calling application must be running within the context of the 
        /// Administrator account and have the SE_DEBUG_NAME privilege 
        /// enabled.
        /// </summary>
        /// <param name="ServiceName">
        /// The name of the service to be started. This is the name specified 
        /// by the ServiceName parameter of the CreateService function when the
        /// service object was created, not the service display name that is 
        /// shown by user interface applications to identify the service. The 
        /// maximum string length is 256 characters. The service control 
        /// manager database preserves the case of the characters, but service 
        /// name comparisons are always case insensitive. Forward-slash (/) 
        /// and backslash (\) are invalid service name characters.
        /// </param>
        /// <param name="DesiredAccess">
        /// The access to the process object. This access right is checked 
        /// against the security descriptor for the process. This parameter can
        /// be one or more of the process access rights.
        /// </param>
        /// <returns>
        /// A handle that identifies the newly opened access token when the 
        /// function returns.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenProcessToken.
        /// </remarks>
        public IntPtr OpenServiceProcessToken(
            [MarshalAs(UnmanagedType.LPWStr)] string ServiceName,
            UInt32 DesiredAccess);

        /// <summary>
        /// Opens the access token associated with the Local Security Authority
        /// process, the calling application must be running within the context
        /// of the Administrator account and have the SE_DEBUG_NAME privilege
        /// enabled.
        /// </summary>
        /// <param name="DesiredAccess">
        /// The access to the process object. This access right is checked 
        /// against the security descriptor for the process. This parameter can
        /// be one or more of the process access rights.
        /// </param>
        /// <returns>
        /// A handle that identifies the newly opened access token when the 
        /// function returns.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenProcessToken.
        /// </remarks>
        public IntPtr OpenLsassProcessToken(
            UInt32 DesiredAccess);

        /// <summary>
        /// Opens an existing thread object.
        /// </summary>
        /// <param name="DesiredAccess">
        /// The access to the thread object. This access right is checked 
        /// against the security descriptor for the thread. This parameter can
        /// be one or more of the thread access rights.
        /// </param>
        /// <param name="InheritHandle">
        /// If this value is TRUE, processes created by this process will 
        /// inherit the handle. Otherwise, the processes do not inherit this
        /// handle.
        /// </param>
        /// <param name="ThreadId">
        /// The identifier of the thread to be opened.
        /// </param>
        /// <returns>
        /// An open handle to the specified thread.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenThread.
        /// </remarks>
        public IntPtr OpenThread(
            UInt32 DesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] bool InheritHandle,
            UInt32 ThreadId);

        /// <summary>
        /// Opens the access token associated with a thread.
        /// </summary>
        /// <param name="ThreadHandle">
        /// A handle to the thread whose access token is opened.
        /// </param>
        /// <param name="DesiredAccess">
        /// Specifies an access mask that specifies the requested types of 
        /// access to the access token. These requested access types are 
        /// reconciled against the token's discretionary access control list 
        /// (DACL) to determine which accesses are granted or denied.
        /// </param>
        /// <param name="OpenAsSelf">
        /// TRUE if the access check is to be made against the process-level 
        /// security context. FALSE if the access check is to be made against 
        /// the current security context of the thread calling the 
        /// OpenThreadToken function.
        /// </param>
        /// <returns>
        /// A variable that receives the handle to the newly opened access 
        /// token.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenThreadToken.
        /// </remarks>
        public IntPtr OpenThreadTokenByThreadHandle(
            IntPtr ThreadHandle,
            UInt32 DesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] bool OpenAsSelf);

        /// <summary>
        /// Opens the access token associated with the current thread.
        /// </summary>
        /// <param name="DesiredAccess">
        /// Specifies an access mask that specifies the requested types of 
        /// access to the access token. These requested access types are 
        /// reconciled against the token's discretionary access control list 
        /// (DACL) to determine which accesses are granted or denied.
        /// </param>
        /// <param name="OpenAsSelf">
        /// TRUE if the access check is to be made against the process-level 
        /// security context. FALSE if the access check is to be made against 
        /// the current security context of the thread calling the 
        /// OpenThreadToken function.
        /// </param>
        /// <returns>
        /// A variable that receives the handle to the newly opened access 
        /// token.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenThreadToken.
        /// </remarks>
        public IntPtr OpenCurrentThreadToken(
            UInt32 DesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] bool OpenAsSelf);

        /// <summary>
        /// Opens the access token associated with a thread.
        /// </summary>
        /// <param name="ThreadId">
        /// The identifier of the thread to be opened.
        /// </param>
        /// <param name="DesiredAccess">
        /// Specifies an access mask that specifies the requested types of 
        /// access to the access token. These requested access types are 
        /// reconciled against the token's discretionary access control list 
        /// (DACL) to determine which accesses are granted or denied.
        /// </param>
        /// <param name="OpenAsSelf">
        /// TRUE if the access check is to be made against the process-level 
        /// security context. FALSE if the access check is to be made against 
        /// the current security context of the thread calling the 
        /// OpenThreadToken function.
        /// </param>
        /// <returns>
        /// A variable that receives the handle to the newly opened access 
        /// token.
        /// </returns>
        /// <remarks>
        /// For more information, see OpenThreadToken.
        /// </remarks>
        public IntPtr OpenThreadTokenByThreadId(
            UInt32 ThreadId,
            UInt32 DesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] bool OpenAsSelf);

        /// <summary>
        /// Retrieves the locally unique identifier (LUID) used on the local 
        /// system to locally represent the specified privilege name.
        /// </summary>
        /// <param name="Name">
        /// A pointer to a null-terminated string that specifies the name of 
        /// the privilege, as defined in the Winnt.h header file. For example,
        /// this parameter could specify the constant, SE_SECURITY_NAME, or its
        /// corresponding string, "SeSecurityPrivilege".
        /// </param>
        /// <returns>
        /// A variable that receives the LUID by which the privilege is known 
        /// on the local system.
        /// </returns>
        /// <remarks>
        /// For more information, see LookupPrivilegeValue.
        /// </remarks>
        public LUID GetPrivilegeValue(
            [MarshalAs(UnmanagedType.LPWStr)] string Name);
    }
}
