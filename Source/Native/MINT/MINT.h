/*
 * PROJECT:   Mouri's Internal NT API Collections (MINT)
 * FILE:      MINT.h
 * PURPOSE:   Definition for the Windows Internal API from ntdll.dll, 
 *            samlib.dll and winsta.dll
 *
 * LICENSE:   Relicensed under The MIT License from The CC BY 4.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

/*
 * This file is part of the Process Hacker project - https://processhacker.sf.io/ 
 *
 * You can redistribute this file and/or modify it under the terms of the 
 * Attribution 4.0 International (CC BY 4.0) license. 
 * 
 * You must give appropriate credit, provide a link to the license, and 
 * indicate if changes were made. You may do so in any reasonable manner, but 
 * not in any way that suggests the licensor endorses you or your use.
 */

#ifndef _MINT_
#define _MINT_

#ifdef __cplusplus
#ifdef MINT_USE_SEPARATE_NAMESPACE
namespace MINT {
#endif
#endif

// This header file provides access to Win32, plus NTSTATUS values and some access mask values.

#ifndef __cplusplus
#ifndef CINTERFACE
#define CINTERFACE
#endif

#ifndef COBJMACROS
#define COBJMACROS
#endif
#endif

#ifndef __cplusplus
// This is needed to workaround C17 preprocessor errors when using legacy versions of the Windows SDK. (dmex)
#ifndef MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS
#define MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS 0
#endif
#endif

#include <windows.h>
#include <windowsx.h>
#include <winioctl.h>

#undef STATUS_WAIT_0
#undef STATUS_ABANDONED_WAIT_0
#undef STATUS_USER_APC
#undef STATUS_TIMEOUT
#undef STATUS_PENDING
#undef DBG_EXCEPTION_HANDLED
#undef DBG_CONTINUE
#undef STATUS_SEGMENT_NOTIFICATION
#undef STATUS_FATAL_APP_EXIT
#undef DBG_TERMINATE_THREAD
#undef DBG_TERMINATE_PROCESS
#undef DBG_CONTROL_C
#undef DBG_PRINTEXCEPTION_C
#undef DBG_RIPEXCEPTION
#undef DBG_CONTROL_BREAK
#undef DBG_COMMAND_EXCEPTION
#undef STATUS_GUARD_PAGE_VIOLATION
#undef STATUS_DATATYPE_MISALIGNMENT
#undef STATUS_BREAKPOINT
#undef STATUS_SINGLE_STEP
#undef STATUS_LONGJUMP
#undef STATUS_UNWIND_CONSOLIDATE
#undef DBG_EXCEPTION_NOT_HANDLED
#undef STATUS_ACCESS_VIOLATION
#undef STATUS_IN_PAGE_ERROR
#undef STATUS_INVALID_HANDLE
#undef STATUS_INVALID_PARAMETER
#undef STATUS_NO_MEMORY
#undef STATUS_ILLEGAL_INSTRUCTION
#undef STATUS_NONCONTINUABLE_EXCEPTION
#undef STATUS_INVALID_DISPOSITION
#undef STATUS_ARRAY_BOUNDS_EXCEEDED
#undef STATUS_FLOAT_DENORMAL_OPERAND
#undef STATUS_FLOAT_DIVIDE_BY_ZERO
#undef STATUS_FLOAT_INEXACT_RESULT
#undef STATUS_FLOAT_INVALID_OPERATION
#undef STATUS_FLOAT_OVERFLOW
#undef STATUS_FLOAT_STACK_CHECK
#undef STATUS_FLOAT_UNDERFLOW
#undef STATUS_INTEGER_DIVIDE_BY_ZERO
#undef STATUS_INTEGER_OVERFLOW
#undef STATUS_PRIVILEGED_INSTRUCTION
#undef STATUS_STACK_OVERFLOW
#undef STATUS_DLL_NOT_FOUND
#undef STATUS_ORDINAL_NOT_FOUND
#undef STATUS_ENTRYPOINT_NOT_FOUND
#undef STATUS_CONTROL_C_EXIT
#undef STATUS_DLL_INIT_FAILED
#undef STATUS_FLOAT_MULTIPLE_FAULTS
#undef STATUS_FLOAT_MULTIPLE_TRAPS
#undef STATUS_REG_NAT_CONSUMPTION
#undef STATUS_HEAP_CORRUPTION
#undef STATUS_STACK_BUFFER_OVERRUN
#undef STATUS_INVALID_CRUNTIME_PARAMETER
#undef STATUS_ASSERTION_FAILURE
#undef STATUS_ENCLAVE_VIOLATION 

#undef STATUS_SXS_EARLY_DEACTIVATION
#undef STATUS_SXS_INVALID_DEACTIVATION

#undef DBG_REPLY_LATER
#undef DBG_PRINTEXCEPTION_WIDE_C

#undef STATUS_ALREADY_REGISTERED
#undef STATUS_INTERRUPTED
#undef STATUS_THREAD_NOT_RUNNING

#undef STATUS_CONTROL_STACK_VIOLATION

#undef WIN32_NO_STATUS
#include <ntstatus.h>

typedef double DOUBLE;
typedef GUID *PGUID;

// Desktop access rights
#define DESKTOP_ALL_ACCESS \
    (DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW | DESKTOP_ENUMERATE | \
    DESKTOP_HOOKCONTROL | DESKTOP_JOURNALPLAYBACK | DESKTOP_JOURNALRECORD | \
    DESKTOP_READOBJECTS | DESKTOP_SWITCHDESKTOP | DESKTOP_WRITEOBJECTS | \
    STANDARD_RIGHTS_REQUIRED)
#define DESKTOP_GENERIC_READ \
    (DESKTOP_ENUMERATE | DESKTOP_READOBJECTS | STANDARD_RIGHTS_READ)
#define DESKTOP_GENERIC_WRITE \
    (DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW | DESKTOP_HOOKCONTROL | \
    DESKTOP_JOURNALPLAYBACK | DESKTOP_JOURNALRECORD | DESKTOP_WRITEOBJECTS | \
    STANDARD_RIGHTS_WRITE)
#define DESKTOP_GENERIC_EXECUTE \
    (DESKTOP_SWITCHDESKTOP | STANDARD_RIGHTS_EXECUTE)

// Window station access rights
#define WINSTA_GENERIC_READ \
    (WINSTA_ENUMDESKTOPS | WINSTA_ENUMERATE | WINSTA_READATTRIBUTES | \
    WINSTA_READSCREEN | STANDARD_RIGHTS_READ)
#define WINSTA_GENERIC_WRITE \
    (WINSTA_ACCESSCLIPBOARD | WINSTA_CREATEDESKTOP | WINSTA_WRITEATTRIBUTES | \
    STANDARD_RIGHTS_WRITE)
#define WINSTA_GENERIC_EXECUTE \
    (WINSTA_ACCESSGLOBALATOMS | WINSTA_EXITWINDOWS | STANDARD_RIGHTS_EXECUTE)

// WMI access rights
#define WMIGUID_GENERIC_READ \
    (WMIGUID_QUERY | WMIGUID_NOTIFICATION | WMIGUID_READ_DESCRIPTION | \
    STANDARD_RIGHTS_READ)
#define WMIGUID_GENERIC_WRITE \
    (WMIGUID_SET | TRACELOG_CREATE_REALTIME | TRACELOG_CREATE_ONDISK | \
    STANDARD_RIGHTS_WRITE)
#define WMIGUID_GENERIC_EXECUTE \
    (WMIGUID_EXECUTE | TRACELOG_GUID_ENABLE | TRACELOG_LOG_EVENT | \
    TRACELOG_ACCESS_REALTIME | TRACELOG_REGISTER_GUIDS | \
    STANDARD_RIGHTS_EXECUTE)
 
// This header file provides access to NT APIs.

// Definitions are annotated to indicate their source. If a definition is not annotated, it has been
// retrieved from an official Microsoft source (NT headers, DDK headers, winnt.h).

// * "winbase" indicates that a definition has been reconstructed from a Win32-ized NT definition in
//   winbase.h.
// * "rev" indicates that a definition has been reverse-engineered.
// * "dbg" indicates that a definition has been obtained from a debug message or assertion in a
//   checked build of the kernel or file.

// Reliability:
// 1. No annotation.
// 2. dbg.
// 3. symbols, private. Types may be incorrect.
// 4. winbase. Names and types may be incorrect.
// 5. rev.

// Version
#include <SDKDDKVer.h>

#pragma comment(lib,"ntdll.lib")
#pragma comment(lib,"samlib.lib")
#pragma comment(lib,"winsta.lib")

// Warnings which disabled for compiling
#if _MSC_VER >= 1200
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable:4201)
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// #include <phnt_ntdef.h>
#ifndef _NTDEF_
#define _NTDEF_

// This header file provides basic NT types not included in Win32. If you have included winnt.h
// (perhaps indirectly), you must use this file instead of ntdef.h.

#ifndef NOTHING
#define NOTHING
#endif

// Basic types

typedef struct _QUAD
{
    union
    {
        __int64 UseThisFieldToCopy;
        double DoNotUseThisField;
    };
} QUAD, *PQUAD;

// This isn't in NT, but it's useful.
typedef struct DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT) _QUAD_PTR
{
    ULONG_PTR DoNotUseThisField1;
    ULONG_PTR DoNotUseThisField2;
} QUAD_PTR, *PQUAD_PTR;

typedef ULONG LOGICAL;
typedef ULONG *PLOGICAL;

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
typedef NTSTATUS *PNTSTATUS;

// Cardinal types

typedef char CCHAR;
typedef short CSHORT;
typedef ULONG CLONG;

typedef CCHAR *PCCHAR;
typedef CSHORT *PCSHORT;
typedef CLONG *PCLONG;

typedef PCSTR PCSZ;

// Specific

typedef UCHAR KIRQL, *PKIRQL;
typedef LONG KPRIORITY;
typedef USHORT RTL_ATOM, *PRTL_ATOM;

typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

typedef struct _LARGE_INTEGER_128
{
    LONGLONG QuadPart[2];
} LARGE_INTEGER_128, *PLARGE_INTEGER_128;

// NT status macros

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define NT_INFORMATION(Status) ((((ULONG)(Status)) >> 30) == 1)
#define NT_WARNING(Status) ((((ULONG)(Status)) >> 30) == 2)
#define NT_ERROR(Status) ((((ULONG)(Status)) >> 30) == 3)

#define NT_FACILITY_MASK 0xfff
#define NT_FACILITY_SHIFT 16
#define NT_FACILITY(Status) ((((ULONG)(Status)) >> NT_FACILITY_SHIFT) & NT_FACILITY_MASK)

#define NT_NTWIN32(Status) (NT_FACILITY(Status) == FACILITY_NTWIN32)
#define WIN32_FROM_NTSTATUS(Status) (((ULONG)(Status)) & 0xffff)

// Functions

#ifndef _WIN64
#define FASTCALL __fastcall
#else
#define FASTCALL
#endif

// Synchronization enumerations

typedef enum _EVENT_TYPE
{
    NotificationEvent,
    SynchronizationEvent
} EVENT_TYPE;

typedef enum _TIMER_TYPE
{
    NotificationTimer,
    SynchronizationTimer
} TIMER_TYPE;

typedef enum _WAIT_TYPE
{
    WaitAll,
    WaitAny,
    WaitNotification
} WAIT_TYPE;

// Strings

typedef struct _STRING
{
    USHORT Length;
    USHORT MaximumLength;
    _Field_size_bytes_part_opt_(MaximumLength, Length) PCHAR Buffer;
} STRING, *PSTRING, ANSI_STRING, *PANSI_STRING, OEM_STRING, *POEM_STRING;

typedef const STRING *PCSTRING;
typedef const ANSI_STRING *PCANSI_STRING;
typedef const OEM_STRING *PCOEM_STRING;

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    _Field_size_bytes_part_(MaximumLength, Length) PWCH Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef const UNICODE_STRING *PCUNICODE_STRING;

#define RTL_CONSTANT_STRING(s) { sizeof(s) - sizeof((s)[0]), sizeof(s), s }

// Balanced tree node

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

typedef struct _RTL_BALANCED_NODE
{
    union
    {
        struct _RTL_BALANCED_NODE *Children[2];
        struct
        {
            struct _RTL_BALANCED_NODE *Left;
            struct _RTL_BALANCED_NODE *Right;
        };
    };
    union
    {
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONG_PTR ParentValue;
    };
} RTL_BALANCED_NODE, *PRTL_BALANCED_NODE;

#define RTL_BALANCED_NODE_GET_PARENT_POINTER(Node) \
    ((PRTL_BALANCED_NODE)((Node)->ParentValue & ~RTL_BALANCED_NODE_RESERVED_PARENT_MASK))

// Portability

typedef struct _SINGLE_LIST_ENTRY32
{
    ULONG Next;
} SINGLE_LIST_ENTRY32, *PSINGLE_LIST_ENTRY32;

typedef struct _STRING32
{
    USHORT Length;
    USHORT MaximumLength;
    ULONG Buffer;
} STRING32, *PSTRING32;

typedef STRING32 UNICODE_STRING32, *PUNICODE_STRING32;
typedef STRING32 ANSI_STRING32, *PANSI_STRING32;

typedef struct _STRING64
{
    USHORT Length;
    USHORT MaximumLength;
    ULONGLONG Buffer;
} STRING64, *PSTRING64;

typedef STRING64 UNICODE_STRING64, *PUNICODE_STRING64;
typedef STRING64 ANSI_STRING64, *PANSI_STRING64;

// Object attributes

#define OBJ_PROTECT_CLOSE 0x00000001
#define OBJ_INHERIT 0x00000002
#define OBJ_AUDIT_OBJECT_CLOSE 0x00000004
#define OBJ_PERMANENT 0x00000010
#define OBJ_EXCLUSIVE 0x00000020
#define OBJ_CASE_INSENSITIVE 0x00000040
#define OBJ_OPENIF 0x00000080
#define OBJ_OPENLINK 0x00000100
#define OBJ_KERNEL_HANDLE 0x00000200
#define OBJ_FORCE_ACCESS_CHECK 0x00000400
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP 0x00000800
#define OBJ_DONT_REPARSE 0x00001000
#define OBJ_VALID_ATTRIBUTES 0x00001ff2

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor; // PSECURITY_DESCRIPTOR;
    PVOID SecurityQualityOfService; // PSECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef const OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

#define InitializeObjectAttributes(p, n, a, r, s) { \
    (p)->Length = sizeof(OBJECT_ATTRIBUTES); \
    (p)->RootDirectory = r; \
    (p)->Attributes = a; \
    (p)->ObjectName = n; \
    (p)->SecurityDescriptor = s; \
    (p)->SecurityQualityOfService = NULL; \
    }

#define RTL_CONSTANT_OBJECT_ATTRIBUTES(n, a) { sizeof(OBJECT_ATTRIBUTES), NULL, n, a, NULL, NULL }
#define RTL_INIT_OBJECT_ATTRIBUTES(n, a) RTL_CONSTANT_OBJECT_ATTRIBUTES(n, a)

#define OBJ_NAME_PATH_SEPARATOR ((WCHAR)L'\\')

// Portability

typedef struct _OBJECT_ATTRIBUTES64
{
    ULONG Length;
    ULONG64 RootDirectory;
    ULONG64 ObjectName;
    ULONG Attributes;
    ULONG64 SecurityDescriptor;
    ULONG64 SecurityQualityOfService;
} OBJECT_ATTRIBUTES64, *POBJECT_ATTRIBUTES64;

typedef const OBJECT_ATTRIBUTES64 *PCOBJECT_ATTRIBUTES64;

typedef struct _OBJECT_ATTRIBUTES32
{
    ULONG Length;
    ULONG RootDirectory;
    ULONG ObjectName;
    ULONG Attributes;
    ULONG SecurityDescriptor;
    ULONG SecurityQualityOfService;
} OBJECT_ATTRIBUTES32, *POBJECT_ATTRIBUTES32;

typedef const OBJECT_ATTRIBUTES32 *PCOBJECT_ATTRIBUTES32;

// Product types

typedef enum _NT_PRODUCT_TYPE
{
    NtProductWinNt = 1,
    NtProductLanManNt,
    NtProductServer
} NT_PRODUCT_TYPE, *PNT_PRODUCT_TYPE;

typedef enum _SUITE_TYPE
{
    SmallBusiness,
    Enterprise,
    BackOffice,
    CommunicationServer,
    TerminalServer,
    SmallBusinessRestricted,
    EmbeddedNT,
    DataCenter,
    SingleUserTS,
    Personal,
    Blade,
    EmbeddedRestricted,
    SecurityAppliance,
    StorageServer,
    ComputeServer,
    WHServer,
    PhoneNT,
    MaxSuiteType
} SUITE_TYPE;

// Specific

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _CLIENT_ID32
{
    ULONG UniqueProcess;
    ULONG UniqueThread;
} CLIENT_ID32, *PCLIENT_ID32;

typedef struct _CLIENT_ID64
{
    ULONGLONG UniqueProcess;
    ULONGLONG UniqueThread;
} CLIENT_ID64, *PCLIENT_ID64;

#include <pshpack4.h>

typedef struct _KSYSTEM_TIME
{
    ULONG LowPart;
    LONG High1Time;
    LONG High2Time;
} KSYSTEM_TIME, *PKSYSTEM_TIME;

#include <poppack.h>

#endif
 

// #include <ntnls.h>
#define MAXIMUM_LEADBYTES 12

typedef struct _CPTABLEINFO
{
    USHORT CodePage;
    USHORT MaximumCharacterSize;
    USHORT DefaultChar;
    USHORT UniDefaultChar;
    USHORT TransDefaultChar;
    USHORT TransUniDefaultChar;
    USHORT DBCSCodePage;
    UCHAR LeadByte[MAXIMUM_LEADBYTES];
    PUSHORT MultiByteTable;
    PVOID WideCharTable;
    PUSHORT DBCSRanges;
    PUSHORT DBCSOffsets;
} CPTABLEINFO, *PCPTABLEINFO;

typedef struct _NLSTABLEINFO
{
    CPTABLEINFO OemTableInfo;
    CPTABLEINFO AnsiTableInfo;
    PUSHORT UpperCaseTable;
    PUSHORT LowerCaseTable;
} NLSTABLEINFO, *PNLSTABLEINFO;

NTSYSAPI USHORT NlsAnsiCodePage;
NTSYSAPI BOOLEAN NlsMbCodePageTag;
NTSYSAPI BOOLEAN NlsMbOemCodePageTag;
 

// #include <ntkeapi.h>
#define LOW_PRIORITY 0 // Lowest thread priority level
#define LOW_REALTIME_PRIORITY 16 // Lowest realtime priority level
#define HIGH_PRIORITY 31 // Highest thread priority level
#define MAXIMUM_PRIORITY 32 // Number of thread priority levels

typedef enum _KTHREAD_STATE
{
    Initialized,
    Ready,
    Running,
    Standby,
    Terminated,
    Waiting,
    Transition,
    DeferredReady,
    GateWaitObsolete,
    WaitingForProcessInSwap,
    MaximumThreadState
} KTHREAD_STATE, *PKTHREAD_STATE;

// private
typedef enum _KHETERO_CPU_POLICY
{
    KHeteroCpuPolicyAll,
    KHeteroCpuPolicyLarge,
    KHeteroCpuPolicyLargeOrIdle,
    KHeteroCpuPolicySmall,
    KHeteroCpuPolicySmallOrIdle,
    KHeteroCpuPolicyDynamic,
    KHeteroCpuPolicyStaticMax,
    KHeteroCpuPolicyBiasedSmall,
    KHeteroCpuPolicyBiasedLarge,
    KHeteroCpuPolicyDefault,
    KHeteroCpuPolicyMax
} KHETERO_CPU_POLICY, *PKHETERO_CPU_POLICY;

typedef enum _KWAIT_REASON
{
    Executive,
    FreePage,
    PageIn,
    PoolAllocation,
    DelayExecution,
    Suspended,
    UserRequest,
    WrExecutive,
    WrFreePage,
    WrPageIn,
    WrPoolAllocation,
    WrDelayExecution,
    WrSuspended,
    WrUserRequest,
    WrEventPair,
    WrQueue,
    WrLpcReceive,
    WrLpcReply,
    WrVirtualMemory,
    WrPageOut,
    WrRendezvous,
    WrKeyedEvent,
    WrTerminated,
    WrProcessInSwap,
    WrCpuRateControl,
    WrCalloutStack,
    WrKernel,
    WrResource,
    WrPushLock,
    WrMutex,
    WrQuantumEnd,
    WrDispatchInt,
    WrPreempted,
    WrYieldExecution,
    WrFastMutex,
    WrGuardedMutex,
    WrRundown,
    WrAlertByThreadId,
    WrDeferredPreempt,
    WrPhysicalFault,
    MaximumWaitReason
} KWAIT_REASON, *PKWAIT_REASON;

typedef enum _KPROFILE_SOURCE
{
    ProfileTime,
    ProfileAlignmentFixup,
    ProfileTotalIssues,
    ProfilePipelineDry,
    ProfileLoadInstructions,
    ProfilePipelineFrozen,
    ProfileBranchInstructions,
    ProfileTotalNonissues,
    ProfileDcacheMisses,
    ProfileIcacheMisses,
    ProfileCacheMisses,
    ProfileBranchMispredictions,
    ProfileStoreInstructions,
    ProfileFpInstructions,
    ProfileIntegerInstructions,
    Profile2Issue,
    Profile3Issue,
    Profile4Issue,
    ProfileSpecialInstructions,
    ProfileTotalCycles,
    ProfileIcacheIssues,
    ProfileDcacheAccesses,
    ProfileMemoryBarrierCycles,
    ProfileLoadLinkedIssues,
    ProfileMaximum
} KPROFILE_SOURCE;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCallbackReturn(
    _In_reads_bytes_opt_(OutputLength) PVOID OutputBuffer,
    _In_ ULONG OutputLength,
    _In_ NTSTATUS Status
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCallbackReturn(
    _In_reads_bytes_opt_(OutputLength) PVOID OutputBuffer,
    _In_ ULONG OutputLength,
    _In_ NTSTATUS Status
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
VOID
NTAPI
NtFlushProcessWriteBuffers(
    VOID
    );

NTSYSCALLAPI
VOID
NTAPI
ZwFlushProcessWriteBuffers(
    VOID
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtYieldExecution(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwYieldExecution(
    VOID
    );
 


// #include <ntldr.h>
// DLLs

typedef BOOLEAN (NTAPI *PLDR_INIT_ROUTINE)(
    _In_ PVOID DllHandle,
    _In_ ULONG Reason,
    _In_opt_ PVOID Context
    );

// symbols
typedef struct _LDR_SERVICE_TAG_RECORD
{
    struct _LDR_SERVICE_TAG_RECORD *Next;
    ULONG ServiceTag;
} LDR_SERVICE_TAG_RECORD, *PLDR_SERVICE_TAG_RECORD;

// symbols
typedef struct _LDRP_CSLIST
{
    PSINGLE_LIST_ENTRY Tail;
} LDRP_CSLIST, *PLDRP_CSLIST;

// symbols
typedef enum _LDR_DDAG_STATE
{
    LdrModulesMerged = -5,
    LdrModulesInitError = -4,
    LdrModulesSnapError = -3,
    LdrModulesUnloaded = -2,
    LdrModulesUnloading = -1,
    LdrModulesPlaceHolder = 0,
    LdrModulesMapping = 1,
    LdrModulesMapped = 2,
    LdrModulesWaitingForDependencies = 3,
    LdrModulesSnapping = 4,
    LdrModulesSnapped = 5,
    LdrModulesCondensed = 6,
    LdrModulesReadyToInit = 7,
    LdrModulesInitializing = 8,
    LdrModulesReadyToRun = 9
} LDR_DDAG_STATE;

// symbols
typedef struct _LDR_DDAG_NODE
{
    LIST_ENTRY Modules;
    PLDR_SERVICE_TAG_RECORD ServiceTagList;
    ULONG LoadCount;
    ULONG LoadWhileUnloadingCount;
    ULONG LowestLink;
    union
    {
        LDRP_CSLIST Dependencies;
        SINGLE_LIST_ENTRY RemovalLink;
    };
    LDRP_CSLIST IncomingDependencies;
    LDR_DDAG_STATE State;
    SINGLE_LIST_ENTRY CondenseLink;
    ULONG PreorderNumber;
} LDR_DDAG_NODE, *PLDR_DDAG_NODE;

// rev
typedef struct _LDR_DEPENDENCY_RECORD
{
    SINGLE_LIST_ENTRY DependencyLink;
    PLDR_DDAG_NODE DependencyNode;
    SINGLE_LIST_ENTRY IncomingDependencyLink;
    PLDR_DDAG_NODE IncomingDependencyNode;
} LDR_DEPENDENCY_RECORD, *PLDR_DEPENDENCY_RECORD;

// symbols
typedef enum _LDR_DLL_LOAD_REASON
{
    LoadReasonStaticDependency,
    LoadReasonStaticForwarderDependency,
    LoadReasonDynamicForwarderDependency,
    LoadReasonDelayloadDependency,
    LoadReasonDynamicLoad,
    LoadReasonAsImageLoad,
    LoadReasonAsDataLoad,
    LoadReasonEnclavePrimary, // REDSTONE3
    LoadReasonEnclaveDependency,
    LoadReasonUnknown = -1
} LDR_DLL_LOAD_REASON, *PLDR_DLL_LOAD_REASON;

#define LDRP_PACKAGED_BINARY 0x00000001
#define LDRP_STATIC_LINK 0x00000002
#define LDRP_IMAGE_DLL 0x00000004
#define LDRP_LOAD_IN_PROGRESS 0x00001000
#define LDRP_UNLOAD_IN_PROGRESS 0x00002000
#define LDRP_ENTRY_PROCESSED 0x00004000
#define LDRP_ENTRY_INSERTED 0x00008000
#define LDRP_CURRENT_LOAD 0x00010000
#define LDRP_FAILED_BUILTIN_LOAD 0x00020000
#define LDRP_DONT_CALL_FOR_THREADS 0x00040000
#define LDRP_PROCESS_ATTACH_CALLED 0x00080000
#define LDRP_DEBUG_SYMBOLS_LOADED 0x00100000
#define LDRP_IMAGE_NOT_AT_BASE 0x00200000 // Vista and below
#define LDRP_COR_IMAGE 0x00400000
#define LDRP_DONT_RELOCATE 0x00800000 // LDR_COR_OWNS_UNMAP
#define LDRP_SYSTEM_MAPPED 0x01000000
#define LDRP_IMAGE_VERIFYING 0x02000000
#define LDRP_DRIVER_DEPENDENT_DLL 0x04000000
#define LDRP_ENTRY_NATIVE 0x08000000
#define LDRP_REDIRECTED 0x10000000
#define LDRP_NON_PAGED_DEBUG_INFO 0x20000000
#define LDRP_MM_LOADED 0x40000000
#define LDRP_COMPAT_DATABASE_PROCESSED 0x80000000

#define LDR_DATA_TABLE_ENTRY_SIZE_WINXP FIELD_OFFSET(LDR_DATA_TABLE_ENTRY, DdagNode)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN7 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY, BaseNameHashValue)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN8 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY, ImplicitPathOptions)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN10 sizeof(LDR_DATA_TABLE_ENTRY)

// symbols
typedef struct _LDR_DATA_TABLE_ENTRY
{
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    union
    {
        LIST_ENTRY InInitializationOrderLinks;
        LIST_ENTRY InProgressLinks;
    };
    PVOID DllBase;
    PLDR_INIT_ROUTINE EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    union
    {
        UCHAR FlagGroup[4];
        ULONG Flags;
        struct
        {
            ULONG PackagedBinary : 1;
            ULONG MarkedForRemoval : 1;
            ULONG ImageDll : 1;
            ULONG LoadNotificationsSent : 1;
            ULONG TelemetryEntryProcessed : 1;
            ULONG ProcessStaticImport : 1;
            ULONG InLegacyLists : 1;
            ULONG InIndexes : 1;
            ULONG ShimDll : 1;
            ULONG InExceptionTable : 1;
            ULONG ReservedFlags1 : 2;
            ULONG LoadInProgress : 1;
            ULONG LoadConfigProcessed : 1;
            ULONG EntryProcessed : 1;
            ULONG ProtectDelayLoad : 1;
            ULONG ReservedFlags3 : 2;
            ULONG DontCallForThreads : 1;
            ULONG ProcessAttachCalled : 1;
            ULONG ProcessAttachFailed : 1;
            ULONG CorDeferredValidate : 1;
            ULONG CorImage : 1;
            ULONG DontRelocate : 1;
            ULONG CorILOnly : 1;
            ULONG ChpeImage : 1;
            ULONG ReservedFlags5 : 2;
            ULONG Redirected : 1;
            ULONG ReservedFlags6 : 2;
            ULONG CompatDatabaseProcessed : 1;
        };
    };
    USHORT ObsoleteLoadCount;
    USHORT TlsIndex;
    LIST_ENTRY HashLinks;
    ULONG TimeDateStamp;
    struct _ACTIVATION_CONTEXT *EntryPointActivationContext;
    PVOID Lock; // RtlAcquireSRWLockExclusive
    PLDR_DDAG_NODE DdagNode;
    LIST_ENTRY NodeModuleLink;
    struct _LDRP_LOAD_CONTEXT *LoadContext;
    PVOID ParentDllBase;
    PVOID SwitchBackContext;
    RTL_BALANCED_NODE BaseAddressIndexNode;
    RTL_BALANCED_NODE MappingInfoIndexNode;
    ULONG_PTR OriginalBase;
    LARGE_INTEGER LoadTime;
    ULONG BaseNameHashValue;
    LDR_DLL_LOAD_REASON LoadReason;
    ULONG ImplicitPathOptions;
    ULONG ReferenceCount;
    ULONG DependentLoadFlags;
    UCHAR SigningLevel; // since REDSTONE2
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

#define LDR_IS_DATAFILE(DllHandle) (((ULONG_PTR)(DllHandle)) & (ULONG_PTR)1)
#define LDR_IS_IMAGEMAPPING(DllHandle) (((ULONG_PTR)(DllHandle)) & (ULONG_PTR)2)
#define LDR_IS_RESOURCE(DllHandle) (LDR_IS_IMAGEMAPPING(DllHandle) || LDR_IS_DATAFILE(DllHandle))

NTSYSAPI
NTSTATUS
NTAPI
LdrLoadDll(
    _In_opt_ PWSTR DllPath,
    _In_opt_ PULONG DllCharacteristics,
    _In_ PUNICODE_STRING DllName,
    _Out_ PVOID *DllHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrUnloadDll(
    _In_ PVOID DllHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrGetDllHandle(
    _In_opt_ PWSTR DllPath,
    _In_opt_ PULONG DllCharacteristics,
    _In_ PUNICODE_STRING DllName,
    _Out_ PVOID *DllHandle
    );

#define LDR_GET_DLL_HANDLE_EX_UNCHANGED_REFCOUNT 0x00000001
#define LDR_GET_DLL_HANDLE_EX_PIN 0x00000002

NTSYSAPI
NTSTATUS
NTAPI
LdrGetDllHandleEx(
    _In_ ULONG Flags,
    _In_opt_ PWSTR DllPath,
    _In_opt_ PULONG DllCharacteristics,
    _In_ PUNICODE_STRING DllName,
    _Out_opt_ PVOID *DllHandle
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrGetDllHandleByMapping(
    _In_ PVOID BaseAddress,
    _Out_ PVOID *DllHandle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrGetDllHandleByName(
    _In_opt_ PUNICODE_STRING BaseDllName,
    _In_opt_ PUNICODE_STRING FullDllName,
    _Out_ PVOID *DllHandle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrGetDllFullName(
    _In_ PVOID DllHandle,
    _Out_ PUNICODE_STRING FullDllName
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrGetDllDirectory(
    _Out_ PUNICODE_STRING DllDirectory
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrSetDllDirectory(
    _In_ PUNICODE_STRING DllDirectory
    );
#endif

#define LDR_ADDREF_DLL_PIN 0x00000001

NTSYSAPI
NTSTATUS
NTAPI
LdrAddRefDll(
    _In_ ULONG Flags,
    _In_ PVOID DllHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrGetProcedureAddress(
    _In_ PVOID DllHandle,
    _In_opt_ PANSI_STRING ProcedureName,
    _In_opt_ ULONG ProcedureNumber,
    _Out_ PVOID *ProcedureAddress
    );

// rev
#define LDR_GET_PROCEDURE_ADDRESS_DONT_RECORD_FORWARDER 0x00000001

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
LdrGetProcedureAddressEx(
    _In_ PVOID DllHandle,
    _In_opt_ PANSI_STRING ProcedureName,
    _In_opt_ ULONG ProcedureNumber,
    _Out_ PVOID *ProcedureAddress,
    _In_ ULONG Flags
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
LdrGetKnownDllSectionHandle(
    _In_ PCWSTR DllName,
    _In_ BOOLEAN KnownDlls32,
    _Out_ PHANDLE Section
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrGetProcedureAddressForCaller(
    _In_ PVOID DllHandle,
    _In_opt_ PANSI_STRING ProcedureName,
    _In_opt_ ULONG ProcedureNumber,
    _Out_ PVOID *ProcedureAddress,
    _In_ ULONG Flags,
    _In_ PVOID *Callback
    );
#endif

#define LDR_LOCK_LOADER_LOCK_FLAG_RAISE_ON_ERRORS 0x00000001
#define LDR_LOCK_LOADER_LOCK_FLAG_TRY_ONLY 0x00000002

#define LDR_LOCK_LOADER_LOCK_DISPOSITION_INVALID 0
#define LDR_LOCK_LOADER_LOCK_DISPOSITION_LOCK_ACQUIRED 1
#define LDR_LOCK_LOADER_LOCK_DISPOSITION_LOCK_NOT_ACQUIRED 2

NTSYSAPI
NTSTATUS
NTAPI
LdrLockLoaderLock(
    _In_ ULONG Flags,
    _Out_opt_ ULONG *Disposition,
    _Out_ PVOID *Cookie
    );

#define LDR_UNLOCK_LOADER_LOCK_FLAG_RAISE_ON_ERRORS 0x00000001

NTSYSAPI
NTSTATUS
NTAPI
LdrUnlockLoaderLock(
    _In_ ULONG Flags,
    _Inout_ PVOID Cookie
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrRelocateImage(
    _In_ PVOID NewBase,
    _In_opt_ PSTR LoaderName,
    _In_ NTSTATUS Success,
    _In_ NTSTATUS Conflict,
    _In_ NTSTATUS Invalid
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrRelocateImageWithBias(
    _In_ PVOID NewBase,
    _In_opt_ LONGLONG Bias,
    _In_opt_ PSTR LoaderName,
    _In_ NTSTATUS Success,
    _In_ NTSTATUS Conflict,
    _In_ NTSTATUS Invalid
    );

NTSYSAPI
PIMAGE_BASE_RELOCATION
NTAPI
LdrProcessRelocationBlock(
    _In_ ULONG_PTR VA,
    _In_ ULONG SizeOfBlock,
    _In_ PUSHORT NextOffset,
    _In_ LONG_PTR Diff
    );

NTSYSAPI
BOOLEAN
NTAPI
LdrVerifyMappedImageMatchesChecksum(
    _In_ PVOID BaseAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG FileLength
    );

typedef VOID (NTAPI *PLDR_IMPORT_MODULE_CALLBACK)(
    _In_ PVOID Parameter,
    _In_ PSTR ModuleName
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrVerifyImageMatchesChecksum(
    _In_ HANDLE ImageFileHandle,
    _In_opt_ PLDR_IMPORT_MODULE_CALLBACK ImportCallbackRoutine,
    _In_ PVOID ImportCallbackParameter,
    _Out_opt_ PUSHORT ImageCharacteristics
    );

// private
typedef struct _LDR_IMPORT_CALLBACK_INFO
{
    PLDR_IMPORT_MODULE_CALLBACK ImportCallbackRoutine;
    PVOID ImportCallbackParameter;
} LDR_IMPORT_CALLBACK_INFO, *PLDR_IMPORT_CALLBACK_INFO;

// private
typedef struct _LDR_SECTION_INFO
{
    HANDLE SectionHandle;
    ACCESS_MASK DesiredAccess;
    POBJECT_ATTRIBUTES ObjA;
    ULONG SectionPageProtection;
    ULONG AllocationAttributes;
} LDR_SECTION_INFO, *PLDR_SECTION_INFO;

// private
typedef struct _LDR_VERIFY_IMAGE_INFO
{
    ULONG Size;
    ULONG Flags;
    LDR_IMPORT_CALLBACK_INFO CallbackInfo;
    LDR_SECTION_INFO SectionInfo;
    USHORT ImageCharacteristics;
} LDR_VERIFY_IMAGE_INFO, *PLDR_VERIFY_IMAGE_INFO;

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
LdrVerifyImageMatchesChecksumEx(
    _In_ HANDLE ImageFileHandle,
    _Inout_ PLDR_VERIFY_IMAGE_INFO VerifyInfo
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
LdrQueryModuleServiceTags(
    _In_ PVOID DllHandle,
    _Out_writes_(*BufferSize) PULONG ServiceTagBuffer,
    _Inout_ PULONG BufferSize
    );
#endif

// begin_msdn:"DLL Load Notification"

#define LDR_DLL_NOTIFICATION_REASON_LOADED 1
#define LDR_DLL_NOTIFICATION_REASON_UNLOADED 2

typedef struct _LDR_DLL_LOADED_NOTIFICATION_DATA
{
    ULONG Flags;
    PUNICODE_STRING FullDllName;
    PUNICODE_STRING BaseDllName;
    PVOID DllBase;
    ULONG SizeOfImage;
} LDR_DLL_LOADED_NOTIFICATION_DATA, *PLDR_DLL_LOADED_NOTIFICATION_DATA;

typedef struct _LDR_DLL_UNLOADED_NOTIFICATION_DATA
{
    ULONG Flags;
    PCUNICODE_STRING FullDllName;
    PCUNICODE_STRING BaseDllName;
    PVOID DllBase;
    ULONG SizeOfImage;
} LDR_DLL_UNLOADED_NOTIFICATION_DATA, *PLDR_DLL_UNLOADED_NOTIFICATION_DATA;

typedef union _LDR_DLL_NOTIFICATION_DATA
{
    LDR_DLL_LOADED_NOTIFICATION_DATA Loaded;
    LDR_DLL_UNLOADED_NOTIFICATION_DATA Unloaded;
} LDR_DLL_NOTIFICATION_DATA, *PLDR_DLL_NOTIFICATION_DATA;

typedef VOID (NTAPI *PLDR_DLL_NOTIFICATION_FUNCTION)(
    _In_ ULONG NotificationReason,
    _In_ PLDR_DLL_NOTIFICATION_DATA NotificationData,
    _In_opt_ PVOID Context
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
LdrRegisterDllNotification(
    _In_ ULONG Flags,
    _In_ PLDR_DLL_NOTIFICATION_FUNCTION NotificationFunction,
    _In_ PVOID Context,
    _Out_ PVOID *Cookie
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrUnregisterDllNotification(
    _In_ PVOID Cookie
    );

#endif

// end_msdn

// rev
NTSYSAPI
PUNICODE_STRING
NTAPI
LdrStandardizeSystemPath(
    _In_ PUNICODE_STRING SystemPath
    );

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
typedef struct _LDR_FAILURE_DATA
{
    NTSTATUS Status;
    WCHAR DllName[0x20];
    WCHAR AdditionalInfo[0x20];
} LDR_FAILURE_DATA, *PLDR_FAILURE_DATA;

NTSYSAPI
PLDR_FAILURE_DATA
NTAPI
LdrGetFailureData(
    VOID
    );
#endif

// private
typedef struct _PS_MITIGATION_OPTIONS_MAP
{
    ULONG_PTR Map[3]; // 2 < 20H1
} PS_MITIGATION_OPTIONS_MAP, *PPS_MITIGATION_OPTIONS_MAP;

// private
typedef struct _PS_MITIGATION_AUDIT_OPTIONS_MAP
{
    ULONG_PTR Map[3]; // 2 < 20H1
} PS_MITIGATION_AUDIT_OPTIONS_MAP, *PPS_MITIGATION_AUDIT_OPTIONS_MAP;

// private
typedef struct _PS_SYSTEM_DLL_INIT_BLOCK
{
    ULONG Size;
    ULONG_PTR SystemDllWowRelocation;
    ULONG_PTR SystemDllNativeRelocation;
    ULONG_PTR Wow64SharedInformation[16];
    ULONG RngData;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG CfgOverride : 1;
            ULONG Reserved : 31;
        };
    };
    PS_MITIGATION_OPTIONS_MAP MitigationOptionsMap;
    ULONG_PTR CfgBitMap;
    ULONG_PTR CfgBitMapSize;
    ULONG_PTR Wow64CfgBitMap;
    ULONG_PTR Wow64CfgBitMapSize;
    PS_MITIGATION_AUDIT_OPTIONS_MAP MitigationAuditOptionsMap; // REDSTONE3
} PS_SYSTEM_DLL_INIT_BLOCK, *PPS_SYSTEM_DLL_INIT_BLOCK;

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
PPS_SYSTEM_DLL_INIT_BLOCK
NTAPI
LdrSystemDllInitBlock(
    VOID
    );
#endif

// Load as data table

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
LdrAddLoadAsDataTable(
    _In_ PVOID Module,
    _In_ PWSTR FilePath,
    _In_ SIZE_T Size,
    _In_ HANDLE Handle
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
LdrRemoveLoadAsDataTable(
    _In_ PVOID InitModule,
    _Out_opt_ PVOID *BaseModule,
    _Out_opt_ PSIZE_T Size,
    _In_ ULONG Flags
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
LdrGetFileNameFromLoadAsDataTable(
    _In_ PVOID Module,
    _Out_ PVOID *pFileNamePrt
    );

#endif

NTSYSAPI
NTSTATUS 
NTAPI 
LdrDisableThreadCalloutsForDll(
    _In_ PVOID DllImageBase
    );
    
// Resources

NTSYSAPI
NTSTATUS
NTAPI
LdrAccessResource(
    _In_ PVOID DllHandle,
    _In_ PIMAGE_RESOURCE_DATA_ENTRY ResourceDataEntry,
    _Out_opt_ PVOID *ResourceBuffer,
    _Out_opt_ ULONG *ResourceLength
    );

typedef struct _LDR_RESOURCE_INFO
{
    ULONG_PTR Type;
    ULONG_PTR Name;
    ULONG_PTR Language;
} LDR_RESOURCE_INFO, *PLDR_RESOURCE_INFO;

#define RESOURCE_TYPE_LEVEL 0
#define RESOURCE_NAME_LEVEL 1
#define RESOURCE_LANGUAGE_LEVEL 2
#define RESOURCE_DATA_LEVEL 3

NTSYSAPI
NTSTATUS
NTAPI
LdrFindResource_U(
    _In_ PVOID DllHandle,
    _In_ PLDR_RESOURCE_INFO ResourceInfo,
    _In_ ULONG Level,
    _Out_ PIMAGE_RESOURCE_DATA_ENTRY *ResourceDataEntry
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrFindResourceEx_U(
    _In_ ULONG Flags,
    _In_ PVOID DllHandle,
    _In_ PLDR_RESOURCE_INFO ResourceInfo,
    _In_ ULONG Level,
    _Out_ PIMAGE_RESOURCE_DATA_ENTRY *ResourceDataEntry
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrFindResourceDirectory_U(
    _In_ PVOID DllHandle,
    _In_ PLDR_RESOURCE_INFO ResourceInfo,
    _In_ ULONG Level,
    _Out_ PIMAGE_RESOURCE_DIRECTORY *ResourceDirectory
    );

// private 
typedef struct _LDR_ENUM_RESOURCE_ENTRY
{
    union
    {
        ULONG_PTR NameOrId;
        PIMAGE_RESOURCE_DIRECTORY_STRING Name;
        struct
        {
            USHORT Id;
            USHORT NameIsPresent;
        };
    } Path[3];
    PVOID Data;
    ULONG Size;
    ULONG Reserved;
} LDR_ENUM_RESOURCE_ENTRY, *PLDR_ENUM_RESOURCE_ENTRY;

#define NAME_FROM_RESOURCE_ENTRY(RootDirectory, Entry) \
    ((Entry)->NameIsString ? (ULONG_PTR)PTR_ADD_OFFSET((RootDirectory), (Entry)->NameOffset) : (Entry)->Id)

NTSYSAPI
NTSTATUS
NTAPI
LdrEnumResources(
    _In_ PVOID DllHandle,
    _In_ PLDR_RESOURCE_INFO ResourceInfo,
    _In_ ULONG Level,
    _Inout_ ULONG *ResourceCount,
    _Out_writes_to_opt_(*ResourceCount, *ResourceCount) PLDR_ENUM_RESOURCE_ENTRY Resources
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrFindEntryForAddress(
    _In_ PVOID DllHandle,
    _Out_ PLDR_DATA_TABLE_ENTRY *Entry
    );

// Module information

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
    HANDLE Section;
    PVOID MappedBase;
    PVOID ImageBase;
    ULONG ImageSize;
    ULONG Flags;
    USHORT LoadOrderIndex;
    USHORT InitOrderIndex;
    USHORT LoadCount;
    USHORT OffsetToFileName;
    UCHAR FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
    ULONG NumberOfModules;
    RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

// private
typedef struct _RTL_PROCESS_MODULE_INFORMATION_EX
{
    USHORT NextOffset;
    RTL_PROCESS_MODULE_INFORMATION BaseInfo;
    ULONG ImageChecksum;
    ULONG TimeDateStamp;
    PVOID DefaultBase;
} RTL_PROCESS_MODULE_INFORMATION_EX, *PRTL_PROCESS_MODULE_INFORMATION_EX;

NTSYSAPI
NTSTATUS
NTAPI
LdrQueryProcessModuleInformation(
    _In_opt_ PRTL_PROCESS_MODULES ModuleInformation,
    _In_opt_ ULONG Size,
    _Out_ PULONG ReturnedSize
    );

typedef VOID (NTAPI *PLDR_ENUM_CALLBACK)(
    _In_ PLDR_DATA_TABLE_ENTRY ModuleInformation, 
    _In_ PVOID Parameter, 
    _Out_ BOOLEAN *Stop
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrEnumerateLoadedModules(
    _In_ BOOLEAN ReservedFlag,
    _In_ PLDR_ENUM_CALLBACK EnumProc,
    _In_ PVOID Context
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrOpenImageFileOptionsKey(
    _In_ PUNICODE_STRING SubKey,
    _In_ BOOLEAN Wow64,
    _Out_ PHANDLE NewKeyHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrQueryImageFileKeyOption(
    _In_ HANDLE KeyHandle,
    _In_ PCWSTR ValueName,
    _In_ ULONG Type,
    _Out_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG ReturnedLength
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrQueryImageFileExecutionOptions(
    _In_ PUNICODE_STRING SubKey,
    _In_ PCWSTR ValueName,
    _In_ ULONG ValueSize,
    _Out_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG ReturnedLength
    );

NTSYSAPI
NTSTATUS
NTAPI
LdrQueryImageFileExecutionOptionsEx(
    _In_ PUNICODE_STRING SubKey,
    _In_ PCWSTR ValueName,
    _In_ ULONG Type,
    _Out_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG ReturnedLength,
    _In_ BOOLEAN Wow64
    );

// private
typedef struct _DELAYLOAD_PROC_DESCRIPTOR
{
    ULONG ImportDescribedByName;
    union
    {
        PCSTR Name;
        ULONG Ordinal;
    } Description;
} DELAYLOAD_PROC_DESCRIPTOR, *PDELAYLOAD_PROC_DESCRIPTOR;

// private
typedef struct _DELAYLOAD_INFO
{
    ULONG Size;
    PCIMAGE_DELAYLOAD_DESCRIPTOR DelayloadDescriptor;
    PIMAGE_THUNK_DATA ThunkAddress;
    PCSTR TargetDllName;
    DELAYLOAD_PROC_DESCRIPTOR TargetApiDescriptor;
    PVOID TargetModuleBase;
    PVOID Unused;
    ULONG LastError;
} DELAYLOAD_INFO, *PDELAYLOAD_INFO;

// private
typedef PVOID (NTAPI *PDELAYLOAD_FAILURE_DLL_CALLBACK)(
    _In_ ULONG NotificationReason,
    _In_ PDELAYLOAD_INFO DelayloadInfo
    );

// rev
typedef PVOID (NTAPI *PDELAYLOAD_FAILURE_SYSTEM_ROUTINE)(
    _In_ PCSTR DllName,
    _In_ PCSTR ProcName
    );

// rev
NTSYSAPI
PVOID
NTAPI
LdrResolveDelayLoadedAPI(
    _In_ PVOID ParentModuleBase,
    _In_ PCIMAGE_DELAYLOAD_DESCRIPTOR DelayloadDescriptor,
    _In_opt_ PDELAYLOAD_FAILURE_DLL_CALLBACK FailureDllHook,
    _In_opt_ PDELAYLOAD_FAILURE_SYSTEM_ROUTINE FailureSystemHook, // kernel32.DelayLoadFailureHook
    _Out_ PIMAGE_THUNK_DATA ThunkAddress,
    _Reserved_ ULONG Flags
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrResolveDelayLoadsFromDll(
    _In_ PVOID ParentBase,
    _In_ PCSTR TargetDllName,
    _Reserved_ ULONG Flags
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrSetDefaultDllDirectories(
    _In_ ULONG DirectoryFlags
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrShutdownProcess(
    VOID
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrShutdownThread(
    VOID
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
LdrSetImplicitPathOptions(
    _In_ ULONG ImplicitPathOptions
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
LdrControlFlowGuardEnforced(
    VOID
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_19H1)
// rev
NTSYSAPI
BOOLEAN
NTAPI
LdrIsModuleSxsRedirected(
    _In_ PVOID DllHandle
    );
#endif

// #include <ntexapi.h>
// #include <ntkeapi.h>


// Thread execution

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDelayExecution(
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER DelayInterval
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDelayExecution(
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER DelayInterval
    );

// Environment values

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySystemEnvironmentValue(
    _In_ PUNICODE_STRING VariableName,
    _Out_writes_bytes_(ValueLength) PWSTR VariableValue,
    _In_ USHORT ValueLength,
    _Out_opt_ PUSHORT ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySystemEnvironmentValue(
    _In_ PUNICODE_STRING VariableName,
    _Out_writes_bytes_(ValueLength) PWSTR VariableValue,
    _In_ USHORT ValueLength,
    _Out_opt_ PUSHORT ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetSystemEnvironmentValue(
    _In_ PUNICODE_STRING VariableName,
    _In_ PUNICODE_STRING VariableValue
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetSystemEnvironmentValue(
    _In_ PUNICODE_STRING VariableName,
    _In_ PUNICODE_STRING VariableValue
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySystemEnvironmentValueEx(
    _In_ PUNICODE_STRING VariableName,
    _In_ LPGUID VendorGuid,
    _Out_writes_bytes_opt_(*ValueLength) PVOID Value,
    _Inout_ PULONG ValueLength,
    _Out_opt_ PULONG Attributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySystemEnvironmentValueEx(
    _In_ PUNICODE_STRING VariableName,
    _In_ LPGUID VendorGuid,
    _Out_writes_bytes_opt_(*ValueLength) PVOID Value,
    _Inout_ PULONG ValueLength,
    _Out_opt_ PULONG Attributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetSystemEnvironmentValueEx(
    _In_ PUNICODE_STRING VariableName,
    _In_ LPGUID VendorGuid,
    _In_reads_bytes_opt_(ValueLength) PVOID Value,
    _In_ ULONG ValueLength,
    _In_ ULONG Attributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetSystemEnvironmentValueEx(
    _In_ PUNICODE_STRING VariableName,
    _In_ LPGUID VendorGuid,
    _In_reads_bytes_opt_(ValueLength) PVOID Value,
    _In_ ULONG ValueLength,
    _In_ ULONG Attributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnumerateSystemEnvironmentValuesEx(
    _In_ ULONG InformationClass,
    _Out_ PVOID Buffer,
    _Inout_ PULONG BufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwEnumerateSystemEnvironmentValuesEx(
    _In_ ULONG InformationClass,
    _Out_ PVOID Buffer,
    _Inout_ PULONG BufferLength
    );

// EFI

// private
typedef struct _BOOT_ENTRY
{
    ULONG Version;
    ULONG Length;
    ULONG Id;
    ULONG Attributes;
    ULONG FriendlyNameOffset;
    ULONG BootFilePathOffset;
    ULONG OsOptionsLength;
    UCHAR OsOptions[1];
} BOOT_ENTRY, *PBOOT_ENTRY;

// private
typedef struct _BOOT_ENTRY_LIST
{
    ULONG NextEntryOffset;
    BOOT_ENTRY BootEntry;
} BOOT_ENTRY_LIST, *PBOOT_ENTRY_LIST;

// private
typedef struct _BOOT_OPTIONS
{
    ULONG Version;
    ULONG Length;
    ULONG Timeout;
    ULONG CurrentBootEntryId;
    ULONG NextBootEntryId;
    WCHAR HeadlessRedirection[1];
} BOOT_OPTIONS, *PBOOT_OPTIONS;

// private
typedef struct _FILE_PATH
{
    ULONG Version;
    ULONG Length;
    ULONG Type;
    UCHAR FilePath[1];
} FILE_PATH, *PFILE_PATH;

// private
typedef struct _EFI_DRIVER_ENTRY
{
    ULONG Version;
    ULONG Length;
    ULONG Id;
    ULONG FriendlyNameOffset;
    ULONG DriverFilePathOffset;
} EFI_DRIVER_ENTRY, *PEFI_DRIVER_ENTRY;

// private
typedef struct _EFI_DRIVER_ENTRY_LIST
{
    ULONG NextEntryOffset;
    EFI_DRIVER_ENTRY DriverEntry;
} EFI_DRIVER_ENTRY_LIST, *PEFI_DRIVER_ENTRY_LIST;

#if (NTDDI_VERSION >= NTDDI_WINXP)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAddBootEntry(
    _In_ PBOOT_ENTRY BootEntry,
    _Out_opt_ PULONG Id
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAddBootEntry(
    _In_ PBOOT_ENTRY BootEntry,
    _Out_opt_ PULONG Id
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteBootEntry(
    _In_ ULONG Id
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteBootEntry(
    _In_ ULONG Id
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtModifyBootEntry(
    _In_ PBOOT_ENTRY BootEntry
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwModifyBootEntry(
    _In_ PBOOT_ENTRY BootEntry
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnumerateBootEntries(
    _Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
    _Inout_ PULONG BufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwEnumerateBootEntries(
    _Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
    _Inout_ PULONG BufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryBootEntryOrder(
    _Out_writes_opt_(*Count) PULONG Ids,
    _Inout_ PULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryBootEntryOrder(
    _Out_writes_opt_(*Count) PULONG Ids,
    _Inout_ PULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetBootEntryOrder(
    _In_reads_(Count) PULONG Ids,
    _In_ ULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetBootEntryOrder(
    _In_reads_(Count) PULONG Ids,
    _In_ ULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryBootOptions(
    _Out_writes_bytes_opt_(*BootOptionsLength) PBOOT_OPTIONS BootOptions,
    _Inout_ PULONG BootOptionsLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryBootOptions(
    _Out_writes_bytes_opt_(*BootOptionsLength) PBOOT_OPTIONS BootOptions,
    _Inout_ PULONG BootOptionsLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetBootOptions(
    _In_ PBOOT_OPTIONS BootOptions,
    _In_ ULONG FieldsToChange
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetBootOptions(
    _In_ PBOOT_OPTIONS BootOptions,
    _In_ ULONG FieldsToChange
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtTranslateFilePath(
    _In_ PFILE_PATH InputFilePath,
    _In_ ULONG OutputType,
    _Out_writes_bytes_opt_(*OutputFilePathLength) PFILE_PATH OutputFilePath,
    _Inout_opt_ PULONG OutputFilePathLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTranslateFilePath(
    _In_ PFILE_PATH InputFilePath,
    _In_ ULONG OutputType,
    _Out_writes_bytes_opt_(*OutputFilePathLength) PFILE_PATH OutputFilePath,
    _Inout_opt_ PULONG OutputFilePathLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAddDriverEntry(
    _In_ PEFI_DRIVER_ENTRY DriverEntry,
    _Out_opt_ PULONG Id
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAddDriverEntry(
    _In_ PEFI_DRIVER_ENTRY DriverEntry,
    _Out_opt_ PULONG Id
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteDriverEntry(
    _In_ ULONG Id
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteDriverEntry(
    _In_ ULONG Id
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtModifyDriverEntry(
    _In_ PEFI_DRIVER_ENTRY DriverEntry
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwModifyDriverEntry(
    _In_ PEFI_DRIVER_ENTRY DriverEntry
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnumerateDriverEntries(
    _Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
    _Inout_ PULONG BufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwEnumerateDriverEntries(
    _Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
    _Inout_ PULONG BufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDriverEntryOrder(
    _Out_writes_opt_(*Count) PULONG Ids,
    _Inout_ PULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryDriverEntryOrder(
    _Out_writes_opt_(*Count) PULONG Ids,
    _Inout_ PULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetDriverEntryOrder(
    _In_reads_(Count) PULONG Ids,
    _In_ ULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetDriverEntryOrder(
    _In_reads_(Count) PULONG Ids,
    _In_ ULONG Count
    );

#endif

typedef enum _FILTER_BOOT_OPTION_OPERATION
{
    FilterBootOptionOperationOpenSystemStore,
    FilterBootOptionOperationSetElement,
    FilterBootOptionOperationDeleteElement,
    FilterBootOptionOperationMax
} FILTER_BOOT_OPTION_OPERATION;

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFilterBootOption(
    _In_ FILTER_BOOT_OPTION_OPERATION FilterOperation,
    _In_ ULONG ObjectType,
    _In_ ULONG ElementType,
    _In_reads_bytes_opt_(DataSize) PVOID Data,
    _In_ ULONG DataSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFilterBootOption(
    _In_ FILTER_BOOT_OPTION_OPERATION FilterOperation,
    _In_ ULONG ObjectType,
    _In_ ULONG ElementType,
    _In_reads_bytes_opt_(DataSize) PVOID Data,
    _In_ ULONG DataSize
    );

#endif

// Event

#ifndef EVENT_QUERY_STATE
#define EVENT_QUERY_STATE 0x0001
#endif

#ifndef EVENT_MODIFY_STATE
#define EVENT_MODIFY_STATE 0x0002
#endif

#ifndef EVENT_ALL_ACCESS
#define EVENT_ALL_ACCESS (EVENT_QUERY_STATE|EVENT_MODIFY_STATE|STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE)
#endif

typedef enum _EVENT_INFORMATION_CLASS
{
    EventBasicInformation
} EVENT_INFORMATION_CLASS;

typedef struct _EVENT_BASIC_INFORMATION
{
    EVENT_TYPE EventType;
    LONG EventState;
} EVENT_BASIC_INFORMATION, *PEVENT_BASIC_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateEvent(
    _Out_ PHANDLE EventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ EVENT_TYPE EventType,
    _In_ BOOLEAN InitialState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateEvent(
    _Out_ PHANDLE EventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ EVENT_TYPE EventType,
    _In_ BOOLEAN InitialState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenEvent(
    _Out_ PHANDLE EventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenEvent(
    _Out_ PHANDLE EventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetEvent(
    _In_ HANDLE EventHandle,
    _Out_opt_ PLONG PreviousState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetEvent(
    _In_ HANDLE EventHandle,
    _Out_opt_ PLONG PreviousState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetEventBoostPriority(
    _In_ HANDLE EventHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetEventBoostPriority(
    _In_ HANDLE EventHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtClearEvent(
    _In_ HANDLE EventHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwClearEvent(
    _In_ HANDLE EventHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtResetEvent(
    _In_ HANDLE EventHandle,
    _Out_opt_ PLONG PreviousState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwResetEvent(
    _In_ HANDLE EventHandle,
    _Out_opt_ PLONG PreviousState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtPulseEvent(
    _In_ HANDLE EventHandle,
    _Out_opt_ PLONG PreviousState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPulseEvent(
    _In_ HANDLE EventHandle,
    _Out_opt_ PLONG PreviousState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryEvent(
    _In_ HANDLE EventHandle,
    _In_ EVENT_INFORMATION_CLASS EventInformationClass,
    _Out_writes_bytes_(EventInformationLength) PVOID EventInformation,
    _In_ ULONG EventInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryEvent(
    _In_ HANDLE EventHandle,
    _In_ EVENT_INFORMATION_CLASS EventInformationClass,
    _Out_writes_bytes_(EventInformationLength) PVOID EventInformation,
    _In_ ULONG EventInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

// Event Pair

#define EVENT_PAIR_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateEventPair(
    _Out_ PHANDLE EventPairHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateEventPair(
    _Out_ PHANDLE EventPairHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenEventPair(
    _Out_ PHANDLE EventPairHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenEventPair(
    _Out_ PHANDLE EventPairHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetLowEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetLowEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetHighEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetHighEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitLowEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitLowEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitHighEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitHighEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetLowWaitHighEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetLowWaitHighEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetHighWaitLowEventPair(
    _In_ HANDLE EventPairHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetHighWaitLowEventPair(
    _In_ HANDLE EventPairHandle
    );

// Mutant

typedef enum _MUTANT_INFORMATION_CLASS
{
    MutantBasicInformation, // MUTANT_BASIC_INFORMATION
    MutantOwnerInformation // MUTANT_OWNER_INFORMATION
} MUTANT_INFORMATION_CLASS;

typedef struct _MUTANT_BASIC_INFORMATION
{
    LONG CurrentCount;
    BOOLEAN OwnedByCaller;
    BOOLEAN AbandonedState;
} MUTANT_BASIC_INFORMATION, *PMUTANT_BASIC_INFORMATION;

typedef struct _MUTANT_OWNER_INFORMATION
{
    CLIENT_ID ClientId;
} MUTANT_OWNER_INFORMATION, *PMUTANT_OWNER_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateMutant(
    _Out_ PHANDLE MutantHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN InitialOwner
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateMutant(
    _Out_ PHANDLE MutantHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN InitialOwner
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenMutant(
    _Out_ PHANDLE MutantHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenMutant(
    _Out_ PHANDLE MutantHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReleaseMutant(
    _In_ HANDLE MutantHandle,
    _Out_opt_ PLONG PreviousCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReleaseMutant(
    _In_ HANDLE MutantHandle,
    _Out_opt_ PLONG PreviousCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryMutant(
    _In_ HANDLE MutantHandle,
    _In_ MUTANT_INFORMATION_CLASS MutantInformationClass,
    _Out_writes_bytes_(MutantInformationLength) PVOID MutantInformation,
    _In_ ULONG MutantInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryMutant(
    _In_ HANDLE MutantHandle,
    _In_ MUTANT_INFORMATION_CLASS MutantInformationClass,
    _Out_writes_bytes_(MutantInformationLength) PVOID MutantInformation,
    _In_ ULONG MutantInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

// Semaphore

#ifndef SEMAPHORE_QUERY_STATE
#define SEMAPHORE_QUERY_STATE 0x0001
#endif

typedef enum _SEMAPHORE_INFORMATION_CLASS
{
    SemaphoreBasicInformation
} SEMAPHORE_INFORMATION_CLASS;

typedef struct _SEMAPHORE_BASIC_INFORMATION
{
    LONG CurrentCount;
    LONG MaximumCount;
} SEMAPHORE_BASIC_INFORMATION, *PSEMAPHORE_BASIC_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSemaphore(
    _Out_ PHANDLE SemaphoreHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ LONG InitialCount,
    _In_ LONG MaximumCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateSemaphore(
    _Out_ PHANDLE SemaphoreHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ LONG InitialCount,
    _In_ LONG MaximumCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenSemaphore(
    _Out_ PHANDLE SemaphoreHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenSemaphore(
    _Out_ PHANDLE SemaphoreHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReleaseSemaphore(
    _In_ HANDLE SemaphoreHandle,
    _In_ LONG ReleaseCount,
    _Out_opt_ PLONG PreviousCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReleaseSemaphore(
    _In_ HANDLE SemaphoreHandle,
    _In_ LONG ReleaseCount,
    _Out_opt_ PLONG PreviousCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySemaphore(
    _In_ HANDLE SemaphoreHandle,
    _In_ SEMAPHORE_INFORMATION_CLASS SemaphoreInformationClass,
    _Out_writes_bytes_(SemaphoreInformationLength) PVOID SemaphoreInformation,
    _In_ ULONG SemaphoreInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySemaphore(
    _In_ HANDLE SemaphoreHandle,
    _In_ SEMAPHORE_INFORMATION_CLASS SemaphoreInformationClass,
    _Out_writes_bytes_(SemaphoreInformationLength) PVOID SemaphoreInformation,
    _In_ ULONG SemaphoreInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

// Timer

typedef enum _TIMER_INFORMATION_CLASS
{
    TimerBasicInformation // TIMER_BASIC_INFORMATION
} TIMER_INFORMATION_CLASS;

typedef struct _TIMER_BASIC_INFORMATION
{
    LARGE_INTEGER RemainingTime;
    BOOLEAN TimerState;
} TIMER_BASIC_INFORMATION, *PTIMER_BASIC_INFORMATION;

typedef VOID (NTAPI *PTIMER_APC_ROUTINE)(
    _In_ PVOID TimerContext,
    _In_ ULONG TimerLowValue,
    _In_ LONG TimerHighValue
    );

typedef enum _TIMER_SET_INFORMATION_CLASS
{
    TimerSetCoalescableTimer, // TIMER_SET_COALESCABLE_TIMER_INFO
    MaxTimerInfoClass
} TIMER_SET_INFORMATION_CLASS;

#if (NTDDI_VERSION >= NTDDI_WIN7)
struct _COUNTED_REASON_CONTEXT;

typedef struct _TIMER_SET_COALESCABLE_TIMER_INFO
{
    _In_ LARGE_INTEGER DueTime;
    _In_opt_ PTIMER_APC_ROUTINE TimerApcRoutine;
    _In_opt_ PVOID TimerContext;
    _In_opt_ struct _COUNTED_REASON_CONTEXT *WakeContext;
    _In_opt_ ULONG Period;
    _In_ ULONG TolerableDelay;
    _Out_opt_ PBOOLEAN PreviousState;
} TIMER_SET_COALESCABLE_TIMER_INFO, *PTIMER_SET_COALESCABLE_TIMER_INFO;
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateTimer(
    _Out_ PHANDLE TimerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TIMER_TYPE TimerType
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateTimer(
    _Out_ PHANDLE TimerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TIMER_TYPE TimerType
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenTimer(
    _Out_ PHANDLE TimerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenTimer(
    _Out_ PHANDLE TimerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetTimer(
    _In_ HANDLE TimerHandle,
    _In_ PLARGE_INTEGER DueTime,
    _In_opt_ PTIMER_APC_ROUTINE TimerApcRoutine,
    _In_opt_ PVOID TimerContext,
    _In_ BOOLEAN ResumeTimer,
    _In_opt_ LONG Period,
    _Out_opt_ PBOOLEAN PreviousState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetTimer(
    _In_ HANDLE TimerHandle,
    _In_ PLARGE_INTEGER DueTime,
    _In_opt_ PTIMER_APC_ROUTINE TimerApcRoutine,
    _In_opt_ PVOID TimerContext,
    _In_ BOOLEAN ResumeTimer,
    _In_opt_ LONG Period,
    _Out_opt_ PBOOLEAN PreviousState
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetTimerEx(
    _In_ HANDLE TimerHandle,
    _In_ TIMER_SET_INFORMATION_CLASS TimerSetInformationClass,
    _Inout_updates_bytes_opt_(TimerSetInformationLength) PVOID TimerSetInformation,
    _In_ ULONG TimerSetInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetTimerEx(
    _In_ HANDLE TimerHandle,
    _In_ TIMER_SET_INFORMATION_CLASS TimerSetInformationClass,
    _Inout_updates_bytes_opt_(TimerSetInformationLength) PVOID TimerSetInformation,
    _In_ ULONG TimerSetInformationLength
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCancelTimer(
    _In_ HANDLE TimerHandle,
    _Out_opt_ PBOOLEAN CurrentState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCancelTimer(
    _In_ HANDLE TimerHandle,
    _Out_opt_ PBOOLEAN CurrentState
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryTimer(
    _In_ HANDLE TimerHandle,
    _In_ TIMER_INFORMATION_CLASS TimerInformationClass,
    _Out_writes_bytes_(TimerInformationLength) PVOID TimerInformation,
    _In_ ULONG TimerInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryTimer(
    _In_ HANDLE TimerHandle,
    _In_ TIMER_INFORMATION_CLASS TimerInformationClass,
    _Out_writes_bytes_(TimerInformationLength) PVOID TimerInformation,
    _In_ ULONG TimerInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateIRTimer(
    _Out_ PHANDLE TimerHandle,
    _In_ ACCESS_MASK DesiredAccess
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateIRTimer(
    _Out_ PHANDLE TimerHandle,
    _In_ ACCESS_MASK DesiredAccess
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetIRTimer(
    _In_ HANDLE TimerHandle,
    _In_opt_ PLARGE_INTEGER DueTime
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetIRTimer(
    _In_ HANDLE TimerHandle,
    _In_opt_ PLARGE_INTEGER DueTime
    );

#endif

typedef struct _T2_SET_PARAMETERS_V0
{
    ULONG Version;
    ULONG Reserved;
    LONGLONG NoWakeTolerance;
} T2_SET_PARAMETERS, *PT2_SET_PARAMETERS;

typedef PVOID PT2_CANCEL_PARAMETERS;

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateTimer2(
    _Out_ PHANDLE TimerHandle,
    _In_opt_ PVOID Reserved1,
    _In_opt_ PVOID Reserved2,
    _In_ ULONG Attributes,
    _In_ ACCESS_MASK DesiredAccess
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateTimer2(
    _Out_ PHANDLE TimerHandle,
    _In_opt_ PVOID Reserved1,
    _In_opt_ PVOID Reserved2,
    _In_ ULONG Attributes,
    _In_ ACCESS_MASK DesiredAccess
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetTimer2(
    _In_ HANDLE TimerHandle,
    _In_ PLARGE_INTEGER DueTime,
    _In_opt_ PLARGE_INTEGER Period,
    _In_ PT2_SET_PARAMETERS Parameters
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetTimer2(
    _In_ HANDLE TimerHandle,
    _In_ PLARGE_INTEGER DueTime,
    _In_opt_ PLARGE_INTEGER Period,
    _In_ PT2_SET_PARAMETERS Parameters
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCancelTimer2(
    _In_ HANDLE TimerHandle,
    _In_ PT2_CANCEL_PARAMETERS Parameters
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCancelTimer2(
    _In_ HANDLE TimerHandle,
    _In_ PT2_CANCEL_PARAMETERS Parameters
    );

#endif

// Profile

#define PROFILE_CONTROL 0x0001
#define PROFILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | PROFILE_CONTROL)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProfile(
    _Out_ PHANDLE ProfileHandle,
    _In_opt_ HANDLE Process,
    _In_ PVOID ProfileBase,
    _In_ SIZE_T ProfileSize,
    _In_ ULONG BucketSize,
    _In_reads_bytes_(BufferSize) PULONG Buffer,
    _In_ ULONG BufferSize,
    _In_ KPROFILE_SOURCE ProfileSource,
    _In_ KAFFINITY Affinity
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateProfile(
    _Out_ PHANDLE ProfileHandle,
    _In_opt_ HANDLE Process,
    _In_ PVOID ProfileBase,
    _In_ SIZE_T ProfileSize,
    _In_ ULONG BucketSize,
    _In_reads_bytes_(BufferSize) PULONG Buffer,
    _In_ ULONG BufferSize,
    _In_ KPROFILE_SOURCE ProfileSource,
    _In_ KAFFINITY Affinity
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProfileEx(
    _Out_ PHANDLE ProfileHandle,
    _In_opt_ HANDLE Process,
    _In_ PVOID ProfileBase,
    _In_ SIZE_T ProfileSize,
    _In_ ULONG BucketSize,
    _In_reads_bytes_(BufferSize) PULONG Buffer,
    _In_ ULONG BufferSize,
    _In_ KPROFILE_SOURCE ProfileSource,
    _In_ USHORT GroupCount,
    _In_reads_(GroupCount) PGROUP_AFFINITY GroupAffinity
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateProfileEx(
    _Out_ PHANDLE ProfileHandle,
    _In_opt_ HANDLE Process,
    _In_ PVOID ProfileBase,
    _In_ SIZE_T ProfileSize,
    _In_ ULONG BucketSize,
    _In_reads_bytes_(BufferSize) PULONG Buffer,
    _In_ ULONG BufferSize,
    _In_ KPROFILE_SOURCE ProfileSource,
    _In_ USHORT GroupCount,
    _In_reads_(GroupCount) PGROUP_AFFINITY GroupAffinity
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtStartProfile(
    _In_ HANDLE ProfileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwStartProfile(
    _In_ HANDLE ProfileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtStopProfile(
    _In_ HANDLE ProfileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwStopProfile(
    _In_ HANDLE ProfileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryIntervalProfile(
    _In_ KPROFILE_SOURCE ProfileSource,
    _Out_ PULONG Interval
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryIntervalProfile(
    _In_ KPROFILE_SOURCE ProfileSource,
    _Out_ PULONG Interval
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetIntervalProfile(
    _In_ ULONG Interval,
    _In_ KPROFILE_SOURCE Source
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetIntervalProfile(
    _In_ ULONG Interval,
    _In_ KPROFILE_SOURCE Source
    );

// Keyed Event

#define KEYEDEVENT_WAIT 0x0001
#define KEYEDEVENT_WAKE 0x0002
#define KEYEDEVENT_ALL_ACCESS \
    (STANDARD_RIGHTS_REQUIRED | KEYEDEVENT_WAIT | KEYEDEVENT_WAKE)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateKeyedEvent(
    _Out_ PHANDLE KeyedEventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateKeyedEvent(
    _Out_ PHANDLE KeyedEventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKeyedEvent(
    _Out_ PHANDLE KeyedEventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenKeyedEvent(
    _Out_ PHANDLE KeyedEventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReleaseKeyedEvent(
    _In_ HANDLE KeyedEventHandle,
    _In_ PVOID KeyValue,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReleaseKeyedEvent(
    _In_ HANDLE KeyedEventHandle,
    _In_ PVOID KeyValue,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForKeyedEvent(
    _In_ HANDLE KeyedEventHandle,
    _In_ PVOID KeyValue,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitForKeyedEvent(
    _In_ HANDLE KeyedEventHandle,
    _In_ PVOID KeyValue,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

// UMS

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtUmsThreadYield(
    _In_ PVOID SchedulerParam
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUmsThreadYield(
    _In_ PVOID SchedulerParam
    );
#endif

// WNF

// begin_private

typedef struct _WNF_STATE_NAME
{
    ULONG Data[2];
} WNF_STATE_NAME, *PWNF_STATE_NAME;

typedef const WNF_STATE_NAME *PCWNF_STATE_NAME;

typedef enum _WNF_STATE_NAME_LIFETIME
{
    WnfWellKnownStateName,
    WnfPermanentStateName,
    WnfPersistentStateName,
    WnfTemporaryStateName
} WNF_STATE_NAME_LIFETIME;

typedef enum _WNF_STATE_NAME_INFORMATION
{
    WnfInfoStateNameExist,
    WnfInfoSubscribersPresent,
    WnfInfoIsQuiescent
} WNF_STATE_NAME_INFORMATION;

typedef enum _WNF_DATA_SCOPE
{
    WnfDataScopeSystem,
    WnfDataScopeSession,
    WnfDataScopeUser,
    WnfDataScopeProcess,
    WnfDataScopeMachine // REDSTONE3
} WNF_DATA_SCOPE;

typedef struct _WNF_TYPE_ID
{
    GUID TypeId;
} WNF_TYPE_ID, *PWNF_TYPE_ID;

typedef const WNF_TYPE_ID *PCWNF_TYPE_ID;

// rev
typedef ULONG WNF_CHANGE_STAMP, *PWNF_CHANGE_STAMP;

typedef struct _WNF_DELIVERY_DESCRIPTOR
{
    ULONGLONG SubscriptionId;
    WNF_STATE_NAME StateName;
    WNF_CHANGE_STAMP ChangeStamp;
    ULONG StateDataSize;
    ULONG EventMask;
    WNF_TYPE_ID TypeId;
    ULONG StateDataOffset;
} WNF_DELIVERY_DESCRIPTOR, *PWNF_DELIVERY_DESCRIPTOR;

// end_private

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateWnfStateName(
    _Out_ PWNF_STATE_NAME StateName,
    _In_ WNF_STATE_NAME_LIFETIME NameLifetime,
    _In_ WNF_DATA_SCOPE DataScope,
    _In_ BOOLEAN PersistData,
    _In_opt_ PCWNF_TYPE_ID TypeId,
    _In_ ULONG MaximumStateSize,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateWnfStateName(
    _Out_ PWNF_STATE_NAME StateName,
    _In_ WNF_STATE_NAME_LIFETIME NameLifetime,
    _In_ WNF_DATA_SCOPE DataScope,
    _In_ BOOLEAN PersistData,
    _In_opt_ PCWNF_TYPE_ID TypeId,
    _In_ ULONG MaximumStateSize,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteWnfStateName(
    _In_ PCWNF_STATE_NAME StateName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteWnfStateName(
    _In_ PCWNF_STATE_NAME StateName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUpdateWnfStateData(
    _In_ PCWNF_STATE_NAME StateName,
    _In_reads_bytes_opt_(Length) const VOID *Buffer,
    _In_opt_ ULONG Length,
    _In_opt_ PCWNF_TYPE_ID TypeId,
    _In_opt_ const VOID *ExplicitScope,
    _In_ WNF_CHANGE_STAMP MatchingChangeStamp,
    _In_ LOGICAL CheckStamp
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUpdateWnfStateData(
    _In_ PCWNF_STATE_NAME StateName,
    _In_reads_bytes_opt_(Length) const VOID *Buffer,
    _In_opt_ ULONG Length,
    _In_opt_ PCWNF_TYPE_ID TypeId,
    _In_opt_ const VOID *ExplicitScope,
    _In_ WNF_CHANGE_STAMP MatchingChangeStamp,
    _In_ LOGICAL CheckStamp
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteWnfStateData(
    _In_ PCWNF_STATE_NAME StateName,
    _In_opt_ const VOID *ExplicitScope
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteWnfStateData(
    _In_ PCWNF_STATE_NAME StateName,
    _In_opt_ const VOID *ExplicitScope
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryWnfStateData(
    _In_ PCWNF_STATE_NAME StateName,
    _In_opt_ PCWNF_TYPE_ID TypeId,
    _In_opt_ const VOID *ExplicitScope,
    _Out_ PWNF_CHANGE_STAMP ChangeStamp,
    _Out_writes_bytes_to_opt_(*BufferSize, *BufferSize) PVOID Buffer,
    _Inout_ PULONG BufferSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryWnfStateData(
    _In_ PCWNF_STATE_NAME StateName,
    _In_opt_ PCWNF_TYPE_ID TypeId,
    _In_opt_ const VOID *ExplicitScope,
    _Out_ PWNF_CHANGE_STAMP ChangeStamp,
    _Out_writes_bytes_to_opt_(*BufferSize, *BufferSize) PVOID Buffer,
    _Inout_ PULONG BufferSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryWnfStateNameInformation(
    _In_ PCWNF_STATE_NAME StateName,
    _In_ WNF_STATE_NAME_INFORMATION NameInfoClass,
    _In_opt_ const VOID *ExplicitScope,
    _Out_writes_bytes_(InfoBufferSize) PVOID InfoBuffer,
    _In_ ULONG InfoBufferSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryWnfStateNameInformation(
    _In_ PCWNF_STATE_NAME StateName,
    _In_ WNF_STATE_NAME_INFORMATION NameInfoClass,
    _In_opt_ const VOID *ExplicitScope,
    _Out_writes_bytes_(InfoBufferSize) PVOID InfoBuffer,
    _In_ ULONG InfoBufferSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSubscribeWnfStateChange(
    _In_ PCWNF_STATE_NAME StateName,
    _In_opt_ WNF_CHANGE_STAMP ChangeStamp,
    _In_ ULONG EventMask,
    _Out_opt_ PULONG64 SubscriptionId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSubscribeWnfStateChange(
    _In_ PCWNF_STATE_NAME StateName,
    _In_opt_ WNF_CHANGE_STAMP ChangeStamp,
    _In_ ULONG EventMask,
    _Out_opt_ PULONG64 SubscriptionId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnsubscribeWnfStateChange(
    _In_ PCWNF_STATE_NAME StateName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnsubscribeWnfStateChange(
    _In_ PCWNF_STATE_NAME StateName
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetCompleteWnfStateSubscription(
    _In_opt_ PWNF_STATE_NAME OldDescriptorStateName,
    _In_opt_ ULONG64 *OldSubscriptionId,
    _In_opt_ ULONG OldDescriptorEventMask,
    _In_opt_ ULONG OldDescriptorStatus,
    _Out_writes_bytes_(DescriptorSize) PWNF_DELIVERY_DESCRIPTOR NewDeliveryDescriptor,
    _In_ ULONG DescriptorSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetCompleteWnfStateSubscription(
    _In_opt_ PWNF_STATE_NAME OldDescriptorStateName,
    _In_opt_ ULONG64 *OldSubscriptionId,
    _In_opt_ ULONG OldDescriptorEventMask,
    _In_opt_ ULONG OldDescriptorStatus,
    _Out_writes_bytes_(DescriptorSize) PWNF_DELIVERY_DESCRIPTOR NewDeliveryDescriptor,
    _In_ ULONG DescriptorSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetWnfProcessNotificationEvent(
    _In_ HANDLE NotificationEvent
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetWnfProcessNotificationEvent(
    _In_ HANDLE NotificationEvent
    );

#endif

// Worker factory

// begin_rev

#define WORKER_FACTORY_RELEASE_WORKER 0x0001
#define WORKER_FACTORY_WAIT 0x0002
#define WORKER_FACTORY_SET_INFORMATION 0x0004
#define WORKER_FACTORY_QUERY_INFORMATION 0x0008
#define WORKER_FACTORY_READY_WORKER 0x0010
#define WORKER_FACTORY_SHUTDOWN 0x0020

#define WORKER_FACTORY_ALL_ACCESS ( \
    STANDARD_RIGHTS_REQUIRED | \
    WORKER_FACTORY_RELEASE_WORKER | \
    WORKER_FACTORY_WAIT | \
    WORKER_FACTORY_SET_INFORMATION | \
    WORKER_FACTORY_QUERY_INFORMATION | \
    WORKER_FACTORY_READY_WORKER | \
    WORKER_FACTORY_SHUTDOWN \
    )

// end_rev

// begin_private

typedef enum _WORKERFACTORYINFOCLASS
{
    WorkerFactoryTimeout, // q; s: LARGE_INTEGER
    WorkerFactoryRetryTimeout, // q; s: LARGE_INTEGER
    WorkerFactoryIdleTimeout, // q; s: LARGE_INTEGER
    WorkerFactoryBindingCount,
    WorkerFactoryThreadMinimum, // q; s: ULONG
    WorkerFactoryThreadMaximum, // q; s: ULONG
    WorkerFactoryPaused, // ULONG or BOOLEAN
    WorkerFactoryBasicInformation, // WORKER_FACTORY_BASIC_INFORMATION
    WorkerFactoryAdjustThreadGoal,
    WorkerFactoryCallbackType,
    WorkerFactoryStackInformation, // 10
    WorkerFactoryThreadBasePriority,
    WorkerFactoryTimeoutWaiters, // since THRESHOLD
    WorkerFactoryFlags,
    WorkerFactoryThreadSoftMaximum,
    WorkerFactoryThreadCpuSets, // since REDSTONE5
    MaxWorkerFactoryInfoClass
} WORKERFACTORYINFOCLASS, *PWORKERFACTORYINFOCLASS;

typedef struct _WORKER_FACTORY_BASIC_INFORMATION
{
    LARGE_INTEGER Timeout;
    LARGE_INTEGER RetryTimeout;
    LARGE_INTEGER IdleTimeout;
    BOOLEAN Paused;
    BOOLEAN TimerSet;
    BOOLEAN QueuedToExWorker;
    BOOLEAN MayCreate;
    BOOLEAN CreateInProgress;
    BOOLEAN InsertedIntoQueue;
    BOOLEAN Shutdown;
    ULONG BindingCount;
    ULONG ThreadMinimum;
    ULONG ThreadMaximum;
    ULONG PendingWorkerCount;
    ULONG WaitingWorkerCount;
    ULONG TotalWorkerCount;
    ULONG ReleaseCount;
    LONGLONG InfiniteWaitGoal;
    PVOID StartRoutine;
    PVOID StartParameter;
    HANDLE ProcessId;
    SIZE_T StackReserve;
    SIZE_T StackCommit;
    NTSTATUS LastThreadCreationStatus;
} WORKER_FACTORY_BASIC_INFORMATION, *PWORKER_FACTORY_BASIC_INFORMATION;

// end_private

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateWorkerFactory(
    _Out_ PHANDLE WorkerFactoryHandleReturn,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE CompletionPortHandle,
    _In_ HANDLE WorkerProcessHandle,
    _In_ PVOID StartRoutine,
    _In_opt_ PVOID StartParameter,
    _In_opt_ ULONG MaxThreadCount,
    _In_opt_ SIZE_T StackReserve,
    _In_opt_ SIZE_T StackCommit
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateWorkerFactory(
    _Out_ PHANDLE WorkerFactoryHandleReturn,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE CompletionPortHandle,
    _In_ HANDLE WorkerProcessHandle,
    _In_ PVOID StartRoutine,
    _In_opt_ PVOID StartParameter,
    _In_opt_ ULONG MaxThreadCount,
    _In_opt_ SIZE_T StackReserve,
    _In_opt_ SIZE_T StackCommit
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationWorkerFactory(
    _In_ HANDLE WorkerFactoryHandle,
    _In_ WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
    _Out_writes_bytes_(WorkerFactoryInformationLength) PVOID WorkerFactoryInformation,
    _In_ ULONG WorkerFactoryInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationWorkerFactory(
    _In_ HANDLE WorkerFactoryHandle,
    _In_ WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
    _Out_writes_bytes_(WorkerFactoryInformationLength) PVOID WorkerFactoryInformation,
    _In_ ULONG WorkerFactoryInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationWorkerFactory(
    _In_ HANDLE WorkerFactoryHandle,
    _In_ WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
    _In_reads_bytes_(WorkerFactoryInformationLength) PVOID WorkerFactoryInformation,
    _In_ ULONG WorkerFactoryInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationWorkerFactory(
    _In_ HANDLE WorkerFactoryHandle,
    _In_ WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
    _In_reads_bytes_(WorkerFactoryInformationLength) PVOID WorkerFactoryInformation,
    _In_ ULONG WorkerFactoryInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtShutdownWorkerFactory(
    _In_ HANDLE WorkerFactoryHandle,
    _Inout_ volatile LONG *PendingWorkerCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwShutdownWorkerFactory(
    _In_ HANDLE WorkerFactoryHandle,
    _Inout_ volatile LONG *PendingWorkerCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReleaseWorkerFactoryWorker(
    _In_ HANDLE WorkerFactoryHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReleaseWorkerFactoryWorker(
    _In_ HANDLE WorkerFactoryHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWorkerFactoryWorkerReady(
    _In_ HANDLE WorkerFactoryHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWorkerFactoryWorkerReady(
    _In_ HANDLE WorkerFactoryHandle
    );

struct _FILE_IO_COMPLETION_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForWorkViaWorkerFactory(
    _In_ HANDLE WorkerFactoryHandle,
    _Out_ struct _FILE_IO_COMPLETION_INFORMATION *MiniPacket
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitForWorkViaWorkerFactory(
    _In_ HANDLE WorkerFactoryHandle,
    _Out_ struct _FILE_IO_COMPLETION_INFORMATION *MiniPacket
    );

#endif

// Time

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySystemTime(
    _Out_ PLARGE_INTEGER SystemTime
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySystemTime(
    _Out_ PLARGE_INTEGER SystemTime
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetSystemTime(
    _In_opt_ PLARGE_INTEGER SystemTime,
    _Out_opt_ PLARGE_INTEGER PreviousTime
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetSystemTime(
    _In_opt_ PLARGE_INTEGER SystemTime,
    _Out_opt_ PLARGE_INTEGER PreviousTime
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryTimerResolution(
    _Out_ PULONG MaximumTime,
    _Out_ PULONG MinimumTime,
    _Out_ PULONG CurrentTime
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryTimerResolution(
    _Out_ PULONG MaximumTime,
    _Out_ PULONG MinimumTime,
    _Out_ PULONG CurrentTime
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetTimerResolution(
    _In_ ULONG DesiredTime,
    _In_ BOOLEAN SetResolution,
    _Out_ PULONG ActualTime
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetTimerResolution(
    _In_ ULONG DesiredTime,
    _In_ BOOLEAN SetResolution,
    _Out_ PULONG ActualTime
    );

// Performance Counter

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryPerformanceCounter(
    _Out_ PLARGE_INTEGER PerformanceCounter,
    _Out_opt_ PLARGE_INTEGER PerformanceFrequency
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryPerformanceCounter(
    _Out_ PLARGE_INTEGER PerformanceCounter,
    _Out_opt_ PLARGE_INTEGER PerformanceFrequency
    );

// LUIDs

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateLocallyUniqueId(
    _Out_ PLUID Luid
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAllocateLocallyUniqueId(
    _Out_ PLUID Luid
    );

// UUIDs

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetUuidSeed(
    _In_ PCHAR Seed
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetUuidSeed(
    _In_ PCHAR Seed
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateUuids(
    _Out_ PULARGE_INTEGER Time,
    _Out_ PULONG Range,
    _Out_ PULONG Sequence,
    _Out_ PCHAR Seed
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAllocateUuids(
    _Out_ PULARGE_INTEGER Time,
    _Out_ PULONG Range,
    _Out_ PULONG Sequence,
    _Out_ PCHAR Seed
    );

// System Information

// rev
// private
typedef enum _SYSTEM_INFORMATION_CLASS
{
    SystemBasicInformation, // q: SYSTEM_BASIC_INFORMATION
    SystemProcessorInformation, // q: SYSTEM_PROCESSOR_INFORMATION
    SystemPerformanceInformation, // q: SYSTEM_PERFORMANCE_INFORMATION
    SystemTimeOfDayInformation, // q: SYSTEM_TIMEOFDAY_INFORMATION
    SystemPathInformation, // not implemented
    SystemProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
    SystemCallCountInformation, // q: SYSTEM_CALL_COUNT_INFORMATION
    SystemDeviceInformation, // q: SYSTEM_DEVICE_INFORMATION
    SystemProcessorPerformanceInformation, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
    SystemFlagsInformation, // q: SYSTEM_FLAGS_INFORMATION
    SystemCallTimeInformation, // not implemented // SYSTEM_CALL_TIME_INFORMATION // 10
    SystemModuleInformation, // q: RTL_PROCESS_MODULES
    SystemLocksInformation, // q: RTL_PROCESS_LOCKS
    SystemStackTraceInformation, // q: RTL_PROCESS_BACKTRACES
    SystemPagedPoolInformation, // not implemented
    SystemNonPagedPoolInformation, // not implemented
    SystemHandleInformation, // q: SYSTEM_HANDLE_INFORMATION
    SystemObjectInformation, // q: SYSTEM_OBJECTTYPE_INFORMATION mixed with SYSTEM_OBJECT_INFORMATION
    SystemPageFileInformation, // q: SYSTEM_PAGEFILE_INFORMATION
    SystemVdmInstemulInformation, // q: SYSTEM_VDM_INSTEMUL_INFO
    SystemVdmBopInformation, // not implemented // 20
    SystemFileCacheInformation, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemCache)
    SystemPoolTagInformation, // q: SYSTEM_POOLTAG_INFORMATION
    SystemInterruptInformation, // q: SYSTEM_INTERRUPT_INFORMATION
    SystemDpcBehaviorInformation, // q: SYSTEM_DPC_BEHAVIOR_INFORMATION; s: SYSTEM_DPC_BEHAVIOR_INFORMATION (requires SeLoadDriverPrivilege)
    SystemFullMemoryInformation, // not implemented // SYSTEM_MEMORY_USAGE_INFORMATION
    SystemLoadGdiDriverInformation, // s (kernel-mode only)
    SystemUnloadGdiDriverInformation, // s (kernel-mode only)
    SystemTimeAdjustmentInformation, // q: SYSTEM_QUERY_TIME_ADJUST_INFORMATION; s: SYSTEM_SET_TIME_ADJUST_INFORMATION (requires SeSystemtimePrivilege)
    SystemSummaryMemoryInformation, // not implemented // SYSTEM_MEMORY_USAGE_INFORMATION
    SystemMirrorMemoryInformation, // s (requires license value "Kernel-MemoryMirroringSupported") (requires SeShutdownPrivilege) // 30
    SystemPerformanceTraceInformation, // q; s: (type depends on EVENT_TRACE_INFORMATION_CLASS)
    SystemObsolete0, // not implemented
    SystemExceptionInformation, // q: SYSTEM_EXCEPTION_INFORMATION
    SystemCrashDumpStateInformation, // s: SYSTEM_CRASH_DUMP_STATE_INFORMATION (requires SeDebugPrivilege)
    SystemKernelDebuggerInformation, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION
    SystemContextSwitchInformation, // q: SYSTEM_CONTEXT_SWITCH_INFORMATION
    SystemRegistryQuotaInformation, // q: SYSTEM_REGISTRY_QUOTA_INFORMATION; s (requires SeIncreaseQuotaPrivilege)
    SystemExtendServiceTableInformation, // s (requires SeLoadDriverPrivilege) // loads win32k only
    SystemPrioritySeperation, // s (requires SeTcbPrivilege)
    SystemVerifierAddDriverInformation, // s (requires SeDebugPrivilege) // 40
    SystemVerifierRemoveDriverInformation, // s (requires SeDebugPrivilege)
    SystemProcessorIdleInformation, // q: SYSTEM_PROCESSOR_IDLE_INFORMATION
    SystemLegacyDriverInformation, // q: SYSTEM_LEGACY_DRIVER_INFORMATION
    SystemCurrentTimeZoneInformation, // q; s: RTL_TIME_ZONE_INFORMATION
    SystemLookasideInformation, // q: SYSTEM_LOOKASIDE_INFORMATION
    SystemTimeSlipNotification, // s: HANDLE (NtCreateEvent) (requires SeSystemtimePrivilege)
    SystemSessionCreate, // not implemented
    SystemSessionDetach, // not implemented
    SystemSessionInformation, // not implemented (SYSTEM_SESSION_INFORMATION)
    SystemRangeStartInformation, // q: SYSTEM_RANGE_START_INFORMATION // 50
    SystemVerifierInformation, // q: SYSTEM_VERIFIER_INFORMATION; s (requires SeDebugPrivilege)
    SystemVerifierThunkExtend, // s (kernel-mode only)
    SystemSessionProcessInformation, // q: SYSTEM_SESSION_PROCESS_INFORMATION
    SystemLoadGdiDriverInSystemSpace, // s (kernel-mode only) (same as SystemLoadGdiDriverInformation)
    SystemNumaProcessorMap, // q
    SystemPrefetcherInformation, // q: PREFETCHER_INFORMATION; s: PREFETCHER_INFORMATION // PfSnQueryPrefetcherInformation
    SystemExtendedProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
    SystemRecommendedSharedDataAlignment, // q
    SystemComPlusPackage, // q; s
    SystemNumaAvailableMemory, // 60
    SystemProcessorPowerInformation, // q: SYSTEM_PROCESSOR_POWER_INFORMATION
    SystemEmulationBasicInformation,
    SystemEmulationProcessorInformation,
    SystemExtendedHandleInformation, // q: SYSTEM_HANDLE_INFORMATION_EX
    SystemLostDelayedWriteInformation, // q: ULONG
    SystemBigPoolInformation, // q: SYSTEM_BIGPOOL_INFORMATION
    SystemSessionPoolTagInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION
    SystemSessionMappedViewInformation, // q: SYSTEM_SESSION_MAPPED_VIEW_INFORMATION
    SystemHotpatchInformation, // q; s: SYSTEM_HOTPATCH_CODE_INFORMATION
    SystemObjectSecurityMode, // q: ULONG // 70
    SystemWatchdogTimerHandler, // s (kernel-mode only)
    SystemWatchdogTimerInformation, // q (kernel-mode only); s (kernel-mode only)
    SystemLogicalProcessorInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION
    SystemWow64SharedInformationObsolete, // not implemented
    SystemRegisterFirmwareTableInformationHandler, // s: SYSTEM_FIRMWARE_TABLE_HANDLER // (kernel-mode only)
    SystemFirmwareTableInformation, // SYSTEM_FIRMWARE_TABLE_INFORMATION
    SystemModuleInformationEx, // q: RTL_PROCESS_MODULE_INFORMATION_EX
    SystemVerifierTriageInformation, // not implemented
    SystemSuperfetchInformation, // q; s: SUPERFETCH_INFORMATION // PfQuerySuperfetchInformation
    SystemMemoryListInformation, // q: SYSTEM_MEMORY_LIST_INFORMATION; s: SYSTEM_MEMORY_LIST_COMMAND (requires SeProfileSingleProcessPrivilege) // 80
    SystemFileCacheInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (same as SystemFileCacheInformation)
    SystemThreadPriorityClientIdInformation, // s: SYSTEM_THREAD_CID_PRIORITY_INFORMATION (requires SeIncreaseBasePriorityPrivilege)
    SystemProcessorIdleCycleTimeInformation, // q: SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION[]
    SystemVerifierCancellationInformation, // SYSTEM_VERIFIER_CANCELLATION_INFORMATION // name:wow64:whNT32QuerySystemVerifierCancellationInformation
    SystemProcessorPowerInformationEx, // not implemented
    SystemRefTraceInformation, // q; s: SYSTEM_REF_TRACE_INFORMATION // ObQueryRefTraceInformation
    SystemSpecialPoolInformation, // q; s: SYSTEM_SPECIAL_POOL_INFORMATION (requires SeDebugPrivilege) // MmSpecialPoolTag, then MmSpecialPoolCatchOverruns != 0
    SystemProcessIdInformation, // q: SYSTEM_PROCESS_ID_INFORMATION
    SystemErrorPortInformation, // s (requires SeTcbPrivilege)
    SystemBootEnvironmentInformation, // q: SYSTEM_BOOT_ENVIRONMENT_INFORMATION // 90
    SystemHypervisorInformation, // q; s (kernel-mode only)
    SystemVerifierInformationEx, // q; s: SYSTEM_VERIFIER_INFORMATION_EX
    SystemTimeZoneInformation, // s (requires SeTimeZonePrivilege)
    SystemImageFileExecutionOptionsInformation, // s: SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION (requires SeTcbPrivilege)
    SystemCoverageInformation, // q; s // name:wow64:whNT32QuerySystemCoverageInformation; ExpCovQueryInformation
    SystemPrefetchPatchInformation, // SYSTEM_PREFETCH_PATCH_INFORMATION
    SystemVerifierFaultsInformation, // s: SYSTEM_VERIFIER_FAULTS_INFORMATION (requires SeDebugPrivilege)
    SystemSystemPartitionInformation, // q: SYSTEM_SYSTEM_PARTITION_INFORMATION
    SystemSystemDiskInformation, // q: SYSTEM_SYSTEM_DISK_INFORMATION
    SystemProcessorPerformanceDistribution, // q: SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION // 100
    SystemNumaProximityNodeInformation,
    SystemDynamicTimeZoneInformation, // q; s (requires SeTimeZonePrivilege)
    SystemCodeIntegrityInformation, // q: SYSTEM_CODEINTEGRITY_INFORMATION // SeCodeIntegrityQueryInformation
    SystemProcessorMicrocodeUpdateInformation, // s: SYSTEM_PROCESSOR_MICROCODE_UPDATE_INFORMATION
    SystemProcessorBrandString, // q // HaliQuerySystemInformation -> HalpGetProcessorBrandString, info class 23
    SystemVirtualAddressInformation, // q: SYSTEM_VA_LIST_INFORMATION[]; s: SYSTEM_VA_LIST_INFORMATION[] (requires SeIncreaseQuotaPrivilege) // MmQuerySystemVaInformation
    SystemLogicalProcessorAndGroupInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX // since WIN7 // KeQueryLogicalProcessorRelationship
    SystemProcessorCycleTimeInformation, // q: SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION[]
    SystemStoreInformation, // q; s: SYSTEM_STORE_INFORMATION // SmQueryStoreInformation
    SystemRegistryAppendString, // s: SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS // 110
    SystemAitSamplingValue, // s: ULONG (requires SeProfileSingleProcessPrivilege)
    SystemVhdBootInformation, // q: SYSTEM_VHD_BOOT_INFORMATION
    SystemCpuQuotaInformation, // q; s: PS_CPU_QUOTA_QUERY_INFORMATION
    SystemNativeBasicInformation, // q: SYSTEM_BASIC_INFORMATION
    SystemErrorPortTimeouts, // SYSTEM_ERROR_PORT_TIMEOUTS
    SystemLowPriorityIoInformation, // q: SYSTEM_LOW_PRIORITY_IO_INFORMATION
    SystemTpmBootEntropyInformation, // q: TPM_BOOT_ENTROPY_NT_RESULT // ExQueryTpmBootEntropyInformation
    SystemVerifierCountersInformation, // q: SYSTEM_VERIFIER_COUNTERS_INFORMATION
    SystemPagedPoolInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypePagedPool)
    SystemSystemPtesInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemPtes) // 120
    SystemNodeDistanceInformation,
    SystemAcpiAuditInformation, // q: SYSTEM_ACPI_AUDIT_INFORMATION // HaliQuerySystemInformation -> HalpAuditQueryResults, info class 26
    SystemBasicPerformanceInformation, // q: SYSTEM_BASIC_PERFORMANCE_INFORMATION // name:wow64:whNtQuerySystemInformation_SystemBasicPerformanceInformation
    SystemQueryPerformanceCounterInformation, // q: SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION // since WIN7 SP1
    SystemSessionBigPoolInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION // since WIN8
    SystemBootGraphicsInformation, // q; s: SYSTEM_BOOT_GRAPHICS_INFORMATION (kernel-mode only)
    SystemScrubPhysicalMemoryInformation, // q; s: MEMORY_SCRUB_INFORMATION
    SystemBadPageInformation,
    SystemProcessorProfileControlArea, // q; s: SYSTEM_PROCESSOR_PROFILE_CONTROL_AREA
    SystemCombinePhysicalMemoryInformation, // s: MEMORY_COMBINE_INFORMATION, MEMORY_COMBINE_INFORMATION_EX, MEMORY_COMBINE_INFORMATION_EX2 // 130
    SystemEntropyInterruptTimingInformation,
    SystemConsoleInformation, // q: SYSTEM_CONSOLE_INFORMATION
    SystemPlatformBinaryInformation, // q: SYSTEM_PLATFORM_BINARY_INFORMATION
    SystemPolicyInformation, // q: SYSTEM_POLICY_INFORMATION
    SystemHypervisorProcessorCountInformation, // q: SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION
    SystemDeviceDataInformation, // q: SYSTEM_DEVICE_DATA_INFORMATION
    SystemDeviceDataEnumerationInformation, // q: SYSTEM_DEVICE_DATA_INFORMATION
    SystemMemoryTopologyInformation, // q: SYSTEM_MEMORY_TOPOLOGY_INFORMATION
    SystemMemoryChannelInformation, // q: SYSTEM_MEMORY_CHANNEL_INFORMATION
    SystemBootLogoInformation, // q: SYSTEM_BOOT_LOGO_INFORMATION // 140
    SystemProcessorPerformanceInformationEx, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX // since WINBLUE
    SystemCriticalProcessErrorLogInformation,
    SystemSecureBootPolicyInformation, // q: SYSTEM_SECUREBOOT_POLICY_INFORMATION
    SystemPageFileInformationEx, // q: SYSTEM_PAGEFILE_INFORMATION_EX
    SystemSecureBootInformation, // q: SYSTEM_SECUREBOOT_INFORMATION
    SystemEntropyInterruptTimingRawInformation,
    SystemPortableWorkspaceEfiLauncherInformation, // q: SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION
    SystemFullProcessInformation, // q: SYSTEM_PROCESS_INFORMATION with SYSTEM_PROCESS_INFORMATION_EXTENSION (requires admin)
    SystemKernelDebuggerInformationEx, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX
    SystemBootMetadataInformation, // 150
    SystemSoftRebootInformation, // q: ULONG
    SystemElamCertificateInformation, // s: SYSTEM_ELAM_CERTIFICATE_INFORMATION
    SystemOfflineDumpConfigInformation,
    SystemProcessorFeaturesInformation, // q: SYSTEM_PROCESSOR_FEATURES_INFORMATION
    SystemRegistryReconciliationInformation, // s: NULL (requires admin) (flushes registry hives)
    SystemEdidInformation,
    SystemManufacturingInformation, // q: SYSTEM_MANUFACTURING_INFORMATION // since THRESHOLD
    SystemEnergyEstimationConfigInformation, // q: SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION
    SystemHypervisorDetailInformation, // q: SYSTEM_HYPERVISOR_DETAIL_INFORMATION
    SystemProcessorCycleStatsInformation, // q: SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION // 160
    SystemVmGenerationCountInformation,
    SystemTrustedPlatformModuleInformation, // q: SYSTEM_TPM_INFORMATION
    SystemKernelDebuggerFlags, // SYSTEM_KERNEL_DEBUGGER_FLAGS
    SystemCodeIntegrityPolicyInformation, // q: SYSTEM_CODEINTEGRITYPOLICY_INFORMATION
    SystemIsolatedUserModeInformation, // q: SYSTEM_ISOLATED_USER_MODE_INFORMATION
    SystemHardwareSecurityTestInterfaceResultsInformation,
    SystemSingleModuleInformation, // q: SYSTEM_SINGLE_MODULE_INFORMATION
    SystemAllowedCpuSetsInformation,
    SystemVsmProtectionInformation, // q: SYSTEM_VSM_PROTECTION_INFORMATION (previously SystemDmaProtectionInformation)
    SystemInterruptCpuSetsInformation, // q: SYSTEM_INTERRUPT_CPU_SET_INFORMATION // 170
    SystemSecureBootPolicyFullInformation, // q: SYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION
    SystemCodeIntegrityPolicyFullInformation,
    SystemAffinitizedInterruptProcessorInformation,
    SystemRootSiloInformation, // q: SYSTEM_ROOT_SILO_INFORMATION
    SystemCpuSetInformation, // q: SYSTEM_CPU_SET_INFORMATION // since THRESHOLD2
    SystemCpuSetTagInformation, // q: SYSTEM_CPU_SET_TAG_INFORMATION
    SystemWin32WerStartCallout,
    SystemSecureKernelProfileInformation, // q: SYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION
    SystemCodeIntegrityPlatformManifestInformation, // q: SYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION // since REDSTONE
    SystemInterruptSteeringInformation, // SYSTEM_INTERRUPT_STEERING_INFORMATION_INPUT // 180
    SystemSupportedProcessorArchitectures, // in: HANDLE, out: ULONG[3] // NtQuerySystemInformationEx
    SystemMemoryUsageInformation, // q: SYSTEM_MEMORY_USAGE_INFORMATION
    SystemCodeIntegrityCertificateInformation, // q: SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION
    SystemPhysicalMemoryInformation, // q: SYSTEM_PHYSICAL_MEMORY_INFORMATION // since REDSTONE2
    SystemControlFlowTransition,
    SystemKernelDebuggingAllowed, // s: ULONG
    SystemActivityModerationExeState, // SYSTEM_ACTIVITY_MODERATION_EXE_STATE
    SystemActivityModerationUserSettings, // SYSTEM_ACTIVITY_MODERATION_USER_SETTINGS
    SystemCodeIntegrityPoliciesFullInformation,
    SystemCodeIntegrityUnlockInformation, // SYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION // 190
    SystemIntegrityQuotaInformation,
    SystemFlushInformation, // q: SYSTEM_FLUSH_INFORMATION
    SystemProcessorIdleMaskInformation, // q: ULONG_PTR // since REDSTONE3
    SystemSecureDumpEncryptionInformation,
    SystemWriteConstraintInformation, // SYSTEM_WRITE_CONSTRAINT_INFORMATION
    SystemKernelVaShadowInformation, // SYSTEM_KERNEL_VA_SHADOW_INFORMATION
    SystemHypervisorSharedPageInformation, // SYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION // since REDSTONE4
    SystemFirmwareBootPerformanceInformation,
    SystemCodeIntegrityVerificationInformation, // SYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION
    SystemFirmwarePartitionInformation, // SYSTEM_FIRMWARE_PARTITION_INFORMATION // 200
    SystemSpeculationControlInformation, // SYSTEM_SPECULATION_CONTROL_INFORMATION // (CVE-2017-5715) REDSTONE3 and above.
    SystemDmaGuardPolicyInformation, // SYSTEM_DMA_GUARD_POLICY_INFORMATION
    SystemEnclaveLaunchControlInformation, // SYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION
    SystemWorkloadAllowedCpuSetsInformation, // SYSTEM_WORKLOAD_ALLOWED_CPU_SET_INFORMATION // since REDSTONE5
    SystemCodeIntegrityUnlockModeInformation,
    SystemLeapSecondInformation, // SYSTEM_LEAP_SECOND_INFORMATION
    SystemFlags2Information, // q: SYSTEM_FLAGS_INFORMATION
    SystemSecurityModelInformation, // SYSTEM_SECURITY_MODEL_INFORMATION // since 19H1
    SystemCodeIntegritySyntheticCacheInformation,
    SystemFeatureConfigurationInformation, // SYSTEM_FEATURE_CONFIGURATION_INFORMATION // since 20H1 // 210
    SystemFeatureConfigurationSectionInformation, // SYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION
    SystemFeatureUsageSubscriptionInformation,
    SystemSecureSpeculationControlInformation, // SECURE_SPECULATION_CONTROL_INFORMATION
    SystemSpacesBootInformation, // since 20H2
    SystemFwRamdiskInformation, // SYSTEM_FIRMWARE_RAMDISK_INFORMATION
    SystemWheaIpmiHardwareInformation,
    SystemDifSetRuleClassInformation,
    SystemDifClearRuleClassInformation,
    SystemDifApplyPluginVerificationOnDriver,
    SystemDifRemovePluginVerificationOnDriver, // 220
    SystemShadowStackInformation, // SYSTEM_SHADOW_STACK_INFORMATION
    SystemBuildVersionInformation, // SYSTEM_BUILD_VERSION_INFORMATION
    SystemPoolLimitInformation, // SYSTEM_POOL_LIMIT_INFORMATION
    SystemCodeIntegrityAddDynamicStore,
    SystemCodeIntegrityClearDynamicStores,
    SystemDifPoolTrackingInformation,
    SystemPoolZeroingInformation, // SYSTEM_POOL_ZEROING_INFORMATION
    MaxSystemInfoClass
} SYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_BASIC_INFORMATION
{
    ULONG Reserved;
    ULONG TimerResolution;
    ULONG PageSize;
    ULONG NumberOfPhysicalPages;
    ULONG LowestPhysicalPageNumber;
    ULONG HighestPhysicalPageNumber;
    ULONG AllocationGranularity;
    ULONG_PTR MinimumUserModeAddress;
    ULONG_PTR MaximumUserModeAddress;
    ULONG_PTR ActiveProcessorsAffinityMask;
    CCHAR NumberOfProcessors;
} SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

typedef struct _SYSTEM_PROCESSOR_INFORMATION
{
    USHORT ProcessorArchitecture;
    USHORT ProcessorLevel;
    USHORT ProcessorRevision;
    USHORT MaximumProcessors;
    ULONG ProcessorFeatureBits;
} SYSTEM_PROCESSOR_INFORMATION, *PSYSTEM_PROCESSOR_INFORMATION;

typedef struct _SYSTEM_PERFORMANCE_INFORMATION
{
    LARGE_INTEGER IdleProcessTime;
    LARGE_INTEGER IoReadTransferCount;
    LARGE_INTEGER IoWriteTransferCount;
    LARGE_INTEGER IoOtherTransferCount;
    ULONG IoReadOperationCount;
    ULONG IoWriteOperationCount;
    ULONG IoOtherOperationCount;
    ULONG AvailablePages;
    ULONG CommittedPages;
    ULONG CommitLimit;
    ULONG PeakCommitment;
    ULONG PageFaultCount;
    ULONG CopyOnWriteCount;
    ULONG TransitionCount;
    ULONG CacheTransitionCount;
    ULONG DemandZeroCount;
    ULONG PageReadCount;
    ULONG PageReadIoCount;
    ULONG CacheReadCount;
    ULONG CacheIoCount;
    ULONG DirtyPagesWriteCount;
    ULONG DirtyWriteIoCount;
    ULONG MappedPagesWriteCount;
    ULONG MappedWriteIoCount;
    ULONG PagedPoolPages;
    ULONG NonPagedPoolPages;
    ULONG PagedPoolAllocs;
    ULONG PagedPoolFrees;
    ULONG NonPagedPoolAllocs;
    ULONG NonPagedPoolFrees;
    ULONG FreeSystemPtes;
    ULONG ResidentSystemCodePage;
    ULONG TotalSystemDriverPages;
    ULONG TotalSystemCodePages;
    ULONG NonPagedPoolLookasideHits;
    ULONG PagedPoolLookasideHits;
    ULONG AvailablePagedPoolPages;
    ULONG ResidentSystemCachePage;
    ULONG ResidentPagedPoolPage;
    ULONG ResidentSystemDriverPage;
    ULONG CcFastReadNoWait;
    ULONG CcFastReadWait;
    ULONG CcFastReadResourceMiss;
    ULONG CcFastReadNotPossible;
    ULONG CcFastMdlReadNoWait;
    ULONG CcFastMdlReadWait;
    ULONG CcFastMdlReadResourceMiss;
    ULONG CcFastMdlReadNotPossible;
    ULONG CcMapDataNoWait;
    ULONG CcMapDataWait;
    ULONG CcMapDataNoWaitMiss;
    ULONG CcMapDataWaitMiss;
    ULONG CcPinMappedDataCount;
    ULONG CcPinReadNoWait;
    ULONG CcPinReadWait;
    ULONG CcPinReadNoWaitMiss;
    ULONG CcPinReadWaitMiss;
    ULONG CcCopyReadNoWait;
    ULONG CcCopyReadWait;
    ULONG CcCopyReadNoWaitMiss;
    ULONG CcCopyReadWaitMiss;
    ULONG CcMdlReadNoWait;
    ULONG CcMdlReadWait;
    ULONG CcMdlReadNoWaitMiss;
    ULONG CcMdlReadWaitMiss;
    ULONG CcReadAheadIos;
    ULONG CcLazyWriteIos;
    ULONG CcLazyWritePages;
    ULONG CcDataFlushes;
    ULONG CcDataPages;
    ULONG ContextSwitches;
    ULONG FirstLevelTbFills;
    ULONG SecondLevelTbFills;
    ULONG SystemCalls;
    ULONGLONG CcTotalDirtyPages; // since THRESHOLD
    ULONGLONG CcDirtyPageThreshold; // since THRESHOLD
    LONGLONG ResidentAvailablePages; // since THRESHOLD
    ULONGLONG SharedCommittedPages; // since THRESHOLD
} SYSTEM_PERFORMANCE_INFORMATION, *PSYSTEM_PERFORMANCE_INFORMATION;

typedef struct _SYSTEM_TIMEOFDAY_INFORMATION
{
    LARGE_INTEGER BootTime;
    LARGE_INTEGER CurrentTime;
    LARGE_INTEGER TimeZoneBias;
    ULONG TimeZoneId;
    ULONG Reserved;
    ULONGLONG BootTimeBias;
    ULONGLONG SleepTimeBias;
} SYSTEM_TIMEOFDAY_INFORMATION, *PSYSTEM_TIMEOFDAY_INFORMATION;

typedef struct _SYSTEM_THREAD_INFORMATION
{
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER CreateTime;
    ULONG WaitTime;
    PVOID StartAddress;
    CLIENT_ID ClientId;
    KPRIORITY Priority;
    LONG BasePriority;
    ULONG ContextSwitches;
    KTHREAD_STATE ThreadState;
    KWAIT_REASON WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _TEB TEB, *PTEB;

// private
typedef struct _SYSTEM_EXTENDED_THREAD_INFORMATION
{
    SYSTEM_THREAD_INFORMATION ThreadInfo;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID Win32StartAddress;
    PTEB TebBase; // since VISTA
    ULONG_PTR Reserved2;
    ULONG_PTR Reserved3;
    ULONG_PTR Reserved4;
} SYSTEM_EXTENDED_THREAD_INFORMATION, *PSYSTEM_EXTENDED_THREAD_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
    ULONG HardFaultCount; // since WIN7
    ULONG NumberOfThreadsHighWatermark; // since WIN7
    ULONGLONG CycleTime; // since WIN7
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
    ULONG HandleCount;
    ULONG SessionId;
    ULONG_PTR UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER ReadOperationCount;
    LARGE_INTEGER WriteOperationCount;
    LARGE_INTEGER OtherOperationCount;
    LARGE_INTEGER ReadTransferCount;
    LARGE_INTEGER WriteTransferCount;
    LARGE_INTEGER OtherTransferCount;
    SYSTEM_THREAD_INFORMATION Threads[1]; // SystemProcessInformation
    // SYSTEM_EXTENDED_THREAD_INFORMATION Threads[1]; // SystemExtendedProcessinformation
    // SYSTEM_EXTENDED_THREAD_INFORMATION + SYSTEM_PROCESS_INFORMATION_EXTENSION // SystemFullProcessInformation
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

typedef struct _SYSTEM_CALL_COUNT_INFORMATION
{
    ULONG Length;
    ULONG NumberOfTables;
} SYSTEM_CALL_COUNT_INFORMATION, *PSYSTEM_CALL_COUNT_INFORMATION;

typedef struct _SYSTEM_DEVICE_INFORMATION
{
    ULONG NumberOfDisks;
    ULONG NumberOfFloppies;
    ULONG NumberOfCdRoms;
    ULONG NumberOfTapes;
    ULONG NumberOfSerialPorts;
    ULONG NumberOfParallelPorts;
} SYSTEM_DEVICE_INFORMATION, *PSYSTEM_DEVICE_INFORMATION;

typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
{
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER DpcTime;
    LARGE_INTEGER InterruptTime;
    ULONG InterruptCount;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

typedef struct _SYSTEM_FLAGS_INFORMATION
{
    ULONG Flags; // NtGlobalFlag
} SYSTEM_FLAGS_INFORMATION, *PSYSTEM_FLAGS_INFORMATION;

// private
typedef struct _SYSTEM_CALL_TIME_INFORMATION
{
    ULONG Length;
    ULONG TotalCalls;
    LARGE_INTEGER TimeOfCalls[1];
} SYSTEM_CALL_TIME_INFORMATION, *PSYSTEM_CALL_TIME_INFORMATION;

// private
typedef struct _RTL_PROCESS_LOCK_INFORMATION
{
    PVOID Address;
    USHORT Type;
    USHORT CreatorBackTraceIndex;
    HANDLE OwningThread;
    LONG LockCount;
    ULONG ContentionCount;
    ULONG EntryCount;
    LONG RecursionCount;
    ULONG NumberOfWaitingShared;
    ULONG NumberOfWaitingExclusive;
} RTL_PROCESS_LOCK_INFORMATION, *PRTL_PROCESS_LOCK_INFORMATION;

// private
typedef struct _RTL_PROCESS_LOCKS
{
    ULONG NumberOfLocks;
    RTL_PROCESS_LOCK_INFORMATION Locks[1];
} RTL_PROCESS_LOCKS, *PRTL_PROCESS_LOCKS;

// private
typedef struct _RTL_PROCESS_BACKTRACE_INFORMATION
{
    PCHAR SymbolicBackTrace;
    ULONG TraceCount;
    USHORT Index;
    USHORT Depth;
    PVOID BackTrace[32];
} RTL_PROCESS_BACKTRACE_INFORMATION, *PRTL_PROCESS_BACKTRACE_INFORMATION;

// private
typedef struct _RTL_PROCESS_BACKTRACES
{
    ULONG CommittedMemory;
    ULONG ReservedMemory;
    ULONG NumberOfBackTraceLookups;
    ULONG NumberOfBackTraces;
    RTL_PROCESS_BACKTRACE_INFORMATION BackTraces[1];
} RTL_PROCESS_BACKTRACES, *PRTL_PROCESS_BACKTRACES;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
    USHORT UniqueProcessId;
    USHORT CreatorBackTraceIndex;
    UCHAR ObjectTypeIndex;
    UCHAR HandleAttributes;
    USHORT HandleValue;
    PVOID Object;
    ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
    ULONG NumberOfHandles;
    SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef struct _SYSTEM_OBJECTTYPE_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG NumberOfObjects;
    ULONG NumberOfHandles;
    ULONG TypeIndex;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
    ULONG PoolType;
    BOOLEAN SecurityRequired;
    BOOLEAN WaitableObject;
    UNICODE_STRING TypeName;
} SYSTEM_OBJECTTYPE_INFORMATION, *PSYSTEM_OBJECTTYPE_INFORMATION;

typedef struct _SYSTEM_OBJECT_INFORMATION
{
    ULONG NextEntryOffset;
    PVOID Object;
    HANDLE CreatorUniqueProcess;
    USHORT CreatorBackTraceIndex;
    USHORT Flags;
    LONG PointerCount;
    LONG HandleCount;
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    HANDLE ExclusiveProcessId;
    PVOID SecurityDescriptor;
    UNICODE_STRING NameInfo;
} SYSTEM_OBJECT_INFORMATION, *PSYSTEM_OBJECT_INFORMATION;

typedef struct _SYSTEM_PAGEFILE_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG TotalSize;
    ULONG TotalInUse;
    ULONG PeakUsage;
    UNICODE_STRING PageFileName;
} SYSTEM_PAGEFILE_INFORMATION, *PSYSTEM_PAGEFILE_INFORMATION;

typedef struct _SYSTEM_VDM_INSTEMUL_INFO
{
    ULONG SegmentNotPresent;
    ULONG VdmOpcode0F;
    ULONG OpcodeESPrefix;
    ULONG OpcodeCSPrefix;
    ULONG OpcodeSSPrefix;
    ULONG OpcodeDSPrefix;
    ULONG OpcodeFSPrefix;
    ULONG OpcodeGSPrefix;
    ULONG OpcodeOPER32Prefix;
    ULONG OpcodeADDR32Prefix;
    ULONG OpcodeINSB;
    ULONG OpcodeINSW;
    ULONG OpcodeOUTSB;
    ULONG OpcodeOUTSW;
    ULONG OpcodePUSHF;
    ULONG OpcodePOPF;
    ULONG OpcodeINTnn;
    ULONG OpcodeINTO;
    ULONG OpcodeIRET;
    ULONG OpcodeINBimm;
    ULONG OpcodeINWimm;
    ULONG OpcodeOUTBimm;
    ULONG OpcodeOUTWimm;
    ULONG OpcodeINB;
    ULONG OpcodeINW;
    ULONG OpcodeOUTB;
    ULONG OpcodeOUTW;
    ULONG OpcodeLOCKPrefix;
    ULONG OpcodeREPNEPrefix;
    ULONG OpcodeREPPrefix;
    ULONG OpcodeHLT;
    ULONG OpcodeCLI;
    ULONG OpcodeSTI;
    ULONG BopCount;
} SYSTEM_VDM_INSTEMUL_INFO, *PSYSTEM_VDM_INSTEMUL_INFO;

#define MM_WORKING_SET_MAX_HARD_ENABLE 0x1
#define MM_WORKING_SET_MAX_HARD_DISABLE 0x2
#define MM_WORKING_SET_MIN_HARD_ENABLE 0x4
#define MM_WORKING_SET_MIN_HARD_DISABLE 0x8

typedef struct _SYSTEM_FILECACHE_INFORMATION
{
    SIZE_T CurrentSize;
    SIZE_T PeakSize;
    ULONG PageFaultCount;
    SIZE_T MinimumWorkingSet;
    SIZE_T MaximumWorkingSet;
    SIZE_T CurrentSizeIncludingTransitionInPages;
    SIZE_T PeakSizeIncludingTransitionInPages;
    ULONG TransitionRePurposeCount;
    ULONG Flags;
} SYSTEM_FILECACHE_INFORMATION, *PSYSTEM_FILECACHE_INFORMATION;

// Can be used instead of SYSTEM_FILECACHE_INFORMATION
typedef struct _SYSTEM_BASIC_WORKING_SET_INFORMATION
{
    SIZE_T CurrentSize;
    SIZE_T PeakSize;
    ULONG PageFaultCount;
} SYSTEM_BASIC_WORKING_SET_INFORMATION, *PSYSTEM_BASIC_WORKING_SET_INFORMATION;

typedef struct _SYSTEM_POOLTAG
{
    union
    {
        UCHAR Tag[4];
        ULONG TagUlong;
    };
    ULONG PagedAllocs;
    ULONG PagedFrees;
    SIZE_T PagedUsed;
    ULONG NonPagedAllocs;
    ULONG NonPagedFrees;
    SIZE_T NonPagedUsed;
} SYSTEM_POOLTAG, *PSYSTEM_POOLTAG;

typedef struct _SYSTEM_POOLTAG_INFORMATION
{
    ULONG Count;
    SYSTEM_POOLTAG TagInfo[1];
} SYSTEM_POOLTAG_INFORMATION, *PSYSTEM_POOLTAG_INFORMATION;

typedef struct _SYSTEM_INTERRUPT_INFORMATION
{
    ULONG ContextSwitches;
    ULONG DpcCount;
    ULONG DpcRate;
    ULONG TimeIncrement;
    ULONG DpcBypassCount;
    ULONG ApcBypassCount;
} SYSTEM_INTERRUPT_INFORMATION, *PSYSTEM_INTERRUPT_INFORMATION;

typedef struct _SYSTEM_DPC_BEHAVIOR_INFORMATION
{
    ULONG Spare;
    ULONG DpcQueueDepth;
    ULONG MinimumDpcRate;
    ULONG AdjustDpcThreshold;
    ULONG IdealDpcRate;
} SYSTEM_DPC_BEHAVIOR_INFORMATION, *PSYSTEM_DPC_BEHAVIOR_INFORMATION;

typedef struct _SYSTEM_QUERY_TIME_ADJUST_INFORMATION
{
    ULONG TimeAdjustment;
    ULONG TimeIncrement;
    BOOLEAN Enable;
} SYSTEM_QUERY_TIME_ADJUST_INFORMATION, *PSYSTEM_QUERY_TIME_ADJUST_INFORMATION;

typedef struct _SYSTEM_QUERY_TIME_ADJUST_INFORMATION_PRECISE
{
    ULONGLONG TimeAdjustment;
    ULONGLONG TimeIncrement;
    BOOLEAN Enable;
} SYSTEM_QUERY_TIME_ADJUST_INFORMATION_PRECISE, *PSYSTEM_QUERY_TIME_ADJUST_INFORMATION_PRECISE;

typedef struct _SYSTEM_SET_TIME_ADJUST_INFORMATION
{
    ULONG TimeAdjustment;
    BOOLEAN Enable;
} SYSTEM_SET_TIME_ADJUST_INFORMATION, *PSYSTEM_SET_TIME_ADJUST_INFORMATION;

typedef struct _SYSTEM_SET_TIME_ADJUST_INFORMATION_PRECISE
{
    ULONGLONG TimeAdjustment;
    BOOLEAN Enable;
} SYSTEM_SET_TIME_ADJUST_INFORMATION_PRECISE, *PSYSTEM_SET_TIME_ADJUST_INFORMATION_PRECISE;

#ifndef _TRACEHANDLE_DEFINED
#define _TRACEHANDLE_DEFINED
typedef ULONG64 TRACEHANDLE, *PTRACEHANDLE;
#endif

typedef enum _EVENT_TRACE_INFORMATION_CLASS
{
    EventTraceKernelVersionInformation, // EVENT_TRACE_VERSION_INFORMATION
    EventTraceGroupMaskInformation, // EVENT_TRACE_GROUPMASK_INFORMATION
    EventTracePerformanceInformation, // EVENT_TRACE_PERFORMANCE_INFORMATION
    EventTraceTimeProfileInformation, // EVENT_TRACE_TIME_PROFILE_INFORMATION
    EventTraceSessionSecurityInformation, // EVENT_TRACE_SESSION_SECURITY_INFORMATION
    EventTraceSpinlockInformation, // EVENT_TRACE_SPINLOCK_INFORMATION
    EventTraceStackTracingInformation, // EVENT_TRACE_SYSTEM_EVENT_INFORMATION
    EventTraceExecutiveResourceInformation, // EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION
    EventTraceHeapTracingInformation, // EVENT_TRACE_HEAP_TRACING_INFORMATION
    EventTraceHeapSummaryTracingInformation, // EVENT_TRACE_HEAP_TRACING_INFORMATION
    EventTracePoolTagFilterInformation, // EVENT_TRACE_TAG_FILTER_INFORMATION
    EventTracePebsTracingInformation, // EVENT_TRACE_SYSTEM_EVENT_INFORMATION
    EventTraceProfileConfigInformation, // EVENT_TRACE_PROFILE_COUNTER_INFORMATION
    EventTraceProfileSourceListInformation, // EVENT_TRACE_PROFILE_LIST_INFORMATION
    EventTraceProfileEventListInformation, // EVENT_TRACE_SYSTEM_EVENT_INFORMATION
    EventTraceProfileCounterListInformation, // EVENT_TRACE_PROFILE_COUNTER_INFORMATION
    EventTraceStackCachingInformation, // EVENT_TRACE_STACK_CACHING_INFORMATION
    EventTraceObjectTypeFilterInformation, // EVENT_TRACE_TAG_FILTER_INFORMATION
    EventTraceSoftRestartInformation, // EVENT_TRACE_SOFT_RESTART_INFORMATION
    EventTraceLastBranchConfigurationInformation, // REDSTONE3
    EventTraceLastBranchEventListInformation,
    EventTraceProfileSourceAddInformation, // EVENT_TRACE_PROFILE_ADD_INFORMATION // REDSTONE4
    EventTraceProfileSourceRemoveInformation, // EVENT_TRACE_PROFILE_REMOVE_INFORMATION
    EventTraceProcessorTraceConfigurationInformation,
    EventTraceProcessorTraceEventListInformation,
    EventTraceCoverageSamplerInformation, // EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION
    EventTraceUnifiedStackCachingInformation, // sicne 21H1
    MaxEventTraceInfoClass
} EVENT_TRACE_INFORMATION_CLASS;

typedef struct _EVENT_TRACE_VERSION_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG EventTraceKernelVersion;
} EVENT_TRACE_VERSION_INFORMATION, *PEVENT_TRACE_VERSION_INFORMATION;

#define PERF_MASK_INDEX         (0xe0000000)
#define PERF_MASK_GROUP         (~PERF_MASK_INDEX)
#define PERF_NUM_MASKS          8

#define PERF_GET_MASK_INDEX(GM) (((GM) & PERF_MASK_INDEX) >> 29)
#define PERF_GET_MASK_GROUP(GM) ((GM) & PERF_MASK_GROUP)
#define PERFINFO_OR_GROUP_WITH_GROUPMASK(Group, pGroupMask) \
    (pGroupMask)->Masks[PERF_GET_MASK_INDEX(Group)] |= PERF_GET_MASK_GROUP(Group);

// Masks[0]
#define PERF_PROCESS            EVENT_TRACE_FLAG_PROCESS
#define PERF_THREAD             EVENT_TRACE_FLAG_THREAD
#define PERF_PROC_THREAD        EVENT_TRACE_FLAG_PROCESS | EVENT_TRACE_FLAG_THREAD
#define PERF_LOADER             EVENT_TRACE_FLAG_IMAGE_LOAD
#define PERF_PERF_COUNTER       EVENT_TRACE_FLAG_PROCESS_COUNTERS
#define PERF_FILENAME           EVENT_TRACE_FLAG_DISK_FILE_IO
#define PERF_DISK_IO            EVENT_TRACE_FLAG_DISK_FILE_IO | EVENT_TRACE_FLAG_DISK_IO
#define PERF_DISK_IO_INIT       EVENT_TRACE_FLAG_DISK_IO_INIT
#define PERF_ALL_FAULTS         EVENT_TRACE_FLAG_MEMORY_PAGE_FAULTS
#define PERF_HARD_FAULTS        EVENT_TRACE_FLAG_MEMORY_HARD_FAULTS
#define PERF_VAMAP              EVENT_TRACE_FLAG_VAMAP
#define PERF_NETWORK            EVENT_TRACE_FLAG_NETWORK_TCPIP
#define PERF_REGISTRY           EVENT_TRACE_FLAG_REGISTRY
#define PERF_DBGPRINT           EVENT_TRACE_FLAG_DBGPRINT
#define PERF_JOB                EVENT_TRACE_FLAG_JOB
#define PERF_ALPC               EVENT_TRACE_FLAG_ALPC
#define PERF_SPLIT_IO           EVENT_TRACE_FLAG_SPLIT_IO
#define PERF_DEBUG_EVENTS       EVENT_TRACE_FLAG_DEBUG_EVENTS
#define PERF_FILE_IO            EVENT_TRACE_FLAG_FILE_IO
#define PERF_FILE_IO_INIT       EVENT_TRACE_FLAG_FILE_IO_INIT
#define PERF_NO_SYSCONFIG       EVENT_TRACE_FLAG_NO_SYSCONFIG

// Masks[1]
#define PERF_MEMORY             0x20000001
#define PERF_PROFILE            0x20000002  // equivalent to EVENT_TRACE_FLAG_PROFILE
#define PERF_CONTEXT_SWITCH     0x20000004  // equivalent to EVENT_TRACE_FLAG_CSWITCH
#define PERF_FOOTPRINT          0x20000008
#define PERF_DRIVERS            0x20000010  // equivalent to EVENT_TRACE_FLAG_DRIVER
#define PERF_REFSET             0x20000020
#define PERF_POOL               0x20000040
#define PERF_POOLTRACE          0x20000041
#define PERF_DPC                0x20000080  // equivalent to EVENT_TRACE_FLAG_DPC
#define PERF_COMPACT_CSWITCH    0x20000100
#define PERF_DISPATCHER         0x20000200  // equivalent to EVENT_TRACE_FLAG_DISPATCHER
#define PERF_PMC_PROFILE        0x20000400
#define PERF_PROFILING          0x20000402
#define PERF_PROCESS_INSWAP     0x20000800
#define PERF_AFFINITY           0x20001000
#define PERF_PRIORITY           0x20002000
#define PERF_INTERRUPT          0x20004000  // equivalent to EVENT_TRACE_FLAG_INTERRUPT
#define PERF_VIRTUAL_ALLOC      0x20008000  // equivalent to EVENT_TRACE_FLAG_VIRTUAL_ALLOC
#define PERF_SPINLOCK           0x20010000
#define PERF_SYNC_OBJECTS       0x20020000
#define PERF_DPC_QUEUE          0x20040000
#define PERF_MEMINFO            0x20080000
#define PERF_CONTMEM_GEN        0x20100000
#define PERF_SPINLOCK_CNTRS     0x20200000
#define PERF_SPININSTR          0x20210000
#define PERF_SESSION            0x20400000
#define PERF_PFSECTION          0x20400000
#define PERF_MEMINFO_WS         0x20800000
#define PERF_KERNEL_QUEUE       0x21000000
#define PERF_INTERRUPT_STEER    0x22000000
#define PERF_SHOULD_YIELD       0x24000000
#define PERF_WS                 0x28000000

// Masks[2]
#define PERF_ANTI_STARVATION    0x40000001
#define PERF_PROCESS_FREEZE     0x40000002
#define PERF_PFN_LIST           0x40000004
#define PERF_WS_DETAIL          0x40000008
#define PERF_WS_ENTRY           0x40000010
#define PERF_HEAP               0x40000020
#define PERF_SYSCALL            0x40000040  // equivalent to EVENT_TRACE_FLAG_SYSTEMCALL
#define PERF_UMS                0x40000080
#define PERF_BACKTRACE          0x40000100
#define PERF_VULCAN             0x40000200
#define PERF_OBJECTS            0x40000400
#define PERF_EVENTS             0x40000800
#define PERF_FULLTRACE          0x40001000
#define PERF_DFSS               0x40002000
#define PERF_PREFETCH           0x40004000
#define PERF_PROCESSOR_IDLE     0x40008000
#define PERF_CPU_CONFIG         0x40010000
#define PERF_TIMER              0x40020000
#define PERF_CLOCK_INTERRUPT    0x40040000
#define PERF_LOAD_BALANCER      0x40080000
#define PERF_CLOCK_TIMER        0x40100000
#define PERF_IDLE_SELECTION     0x40200000
#define PERF_IPI                0x40400000
#define PERF_IO_TIMER           0x40800000
#define PERF_REG_HIVE           0x41000000
#define PERF_REG_NOTIF          0x42000000
#define PERF_PPM_EXIT_LATENCY   0x44000000
#define PERF_WORKER_THREAD      0x48000000

// Masks[4]
#define PERF_OPTICAL_IO         0x80000001
#define PERF_OPTICAL_IO_INIT    0x80000002
#define PERF_DLL_INFO           0x80000008
#define PERF_DLL_FLUSH_WS       0x80000010
#define PERF_OB_HANDLE          0x80000040
#define PERF_OB_OBJECT          0x80000080
#define PERF_WAKE_DROP          0x80000200
#define PERF_WAKE_EVENT         0x80000400
#define PERF_DEBUGGER           0x80000800
#define PERF_PROC_ATTACH        0x80001000
#define PERF_WAKE_COUNTER       0x80002000
#define PERF_POWER              0x80008000
#define PERF_SOFT_TRIM          0x80010000
#define PERF_CC                 0x80020000
#define PERF_FLT_IO_INIT        0x80080000
#define PERF_FLT_IO             0x80100000
#define PERF_FLT_FASTIO         0x80200000
#define PERF_FLT_IO_FAILURE     0x80400000
#define PERF_HV_PROFILE         0x80800000
#define PERF_WDF_DPC            0x81000000
#define PERF_WDF_INTERRUPT      0x82000000
#define PERF_CACHE_FLUSH        0x84000000

// Masks[5]
#define PERF_HIBER_RUNDOWN      0xA0000001

// Masks[6]
#define PERF_SYSCFG_SYSTEM      0xC0000001
#define PERF_SYSCFG_GRAPHICS    0xC0000002
#define PERF_SYSCFG_STORAGE     0xC0000004
#define PERF_SYSCFG_NETWORK     0xC0000008
#define PERF_SYSCFG_SERVICES    0xC0000010
#define PERF_SYSCFG_PNP         0xC0000020
#define PERF_SYSCFG_OPTICAL     0xC0000040
#define PERF_SYSCFG_ALL         0xDFFFFFFF

// Masks[7] - Control Mask. All flags that change system behavior go here.
#define PERF_CLUSTER_OFF        0xE0000001
#define PERF_MEMORY_CONTROL     0xE0000002

typedef ULONG PERFINFO_MASK;

typedef struct _PERFINFO_GROUPMASK
{
    ULONG Masks[PERF_NUM_MASKS];
} PERFINFO_GROUPMASK, *PPERFINFO_GROUPMASK;

typedef struct _EVENT_TRACE_GROUPMASK_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    PERFINFO_GROUPMASK EventTraceGroupMasks;
} EVENT_TRACE_GROUPMASK_INFORMATION, *PEVENT_TRACE_GROUPMASK_INFORMATION;

typedef struct _EVENT_TRACE_PERFORMANCE_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    LARGE_INTEGER LogfileBytesWritten;
} EVENT_TRACE_PERFORMANCE_INFORMATION, *PEVENT_TRACE_PERFORMANCE_INFORMATION;

typedef struct _EVENT_TRACE_TIME_PROFILE_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG ProfileInterval;
} EVENT_TRACE_TIME_PROFILE_INFORMATION, *PEVENT_TRACE_TIME_PROFILE_INFORMATION;

typedef struct _EVENT_TRACE_SESSION_SECURITY_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG SecurityInformation;
    TRACEHANDLE TraceHandle;
    UCHAR SecurityDescriptor[1];
} EVENT_TRACE_SESSION_SECURITY_INFORMATION, *PEVENT_TRACE_SESSION_SECURITY_INFORMATION;

typedef struct _EVENT_TRACE_SPINLOCK_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG SpinLockSpinThreshold;
    ULONG SpinLockAcquireSampleRate;
    ULONG SpinLockContentionSampleRate;
    ULONG SpinLockHoldThreshold;
} EVENT_TRACE_SPINLOCK_INFORMATION, *PEVENT_TRACE_SPINLOCK_INFORMATION;

typedef struct _EVENT_TRACE_SYSTEM_EVENT_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    ULONG HookId[1];
} EVENT_TRACE_SYSTEM_EVENT_INFORMATION, *PEVENT_TRACE_SYSTEM_EVENT_INFORMATION;

typedef struct _EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG ReleaseSamplingRate;
    ULONG ContentionSamplingRate;
    ULONG NumberOfExcessiveTimeouts;
} EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION, *PEVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION;

typedef struct _EVENT_TRACE_HEAP_TRACING_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG ProcessId;
} EVENT_TRACE_HEAP_TRACING_INFORMATION, *PEVENT_TRACE_HEAP_TRACING_INFORMATION;

typedef struct _EVENT_TRACE_TAG_FILTER_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    ULONG Filter[1];
} EVENT_TRACE_TAG_FILTER_INFORMATION, *PEVENT_TRACE_TAG_FILTER_INFORMATION;

typedef struct _EVENT_TRACE_PROFILE_COUNTER_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    ULONG ProfileSource[1];
} EVENT_TRACE_PROFILE_COUNTER_INFORMATION, *PEVENT_TRACE_PROFILE_COUNTER_INFORMATION;

//typedef struct _PROFILE_SOURCE_INFO
//{
//    ULONG NextEntryOffset;
//    ULONG Source;
//    ULONG MinInterval;
//    ULONG MaxInterval;
//    PVOID Reserved;
//    WCHAR Description[1];
//} PROFILE_SOURCE_INFO, *PPROFILE_SOURCE_INFO;

typedef struct _EVENT_TRACE_PROFILE_LIST_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG Spare;
    struct _PROFILE_SOURCE_INFO* Profile[1];
} EVENT_TRACE_PROFILE_LIST_INFORMATION, *PEVENT_TRACE_PROFILE_LIST_INFORMATION;

typedef struct _EVENT_TRACE_STACK_CACHING_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    BOOLEAN Enabled;
    UCHAR Reserved[3];
    ULONG CacheSize;
    ULONG BucketCount;
} EVENT_TRACE_STACK_CACHING_INFORMATION, *PEVENT_TRACE_STACK_CACHING_INFORMATION;

typedef struct _EVENT_TRACE_SOFT_RESTART_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    BOOLEAN PersistTraceBuffers;
    WCHAR FileName[1];
} EVENT_TRACE_SOFT_RESTART_INFORMATION, *PEVENT_TRACE_SOFT_RESTART_INFORMATION;

typedef struct _EVENT_TRACE_PROFILE_ADD_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    BOOLEAN PerfEvtEventSelect;
    BOOLEAN PerfEvtUnitSelect;
    ULONG PerfEvtType;
    ULONG CpuInfoHierarchy[0x3];
    ULONG InitialInterval;
    BOOLEAN AllowsHalt;
    BOOLEAN Persist;
    WCHAR ProfileSourceDescription[0x1];
} EVENT_TRACE_PROFILE_ADD_INFORMATION, *PEVENT_TRACE_PROFILE_ADD_INFORMATION;

typedef struct _EVENT_TRACE_PROFILE_REMOVE_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    KPROFILE_SOURCE ProfileSource;
    ULONG CpuInfoHierarchy[0x3];
} EVENT_TRACE_PROFILE_REMOVE_INFORMATION, *PEVENT_TRACE_PROFILE_REMOVE_INFORMATION;

typedef struct _EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    BOOLEAN CoverageSamplerInformationClass;
    UCHAR MajorVersion;
    UCHAR MinorVersion;
    UCHAR Reserved;
    HANDLE SamplerHandle;
} EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION, *PEVENT_TRACE_COVERAGE_SAMPLER_INFORMATION;

typedef struct _SYSTEM_EXCEPTION_INFORMATION
{
    ULONG AlignmentFixupCount;
    ULONG ExceptionDispatchCount;
    ULONG FloatingEmulationCount;
    ULONG ByteWordEmulationCount;
} SYSTEM_EXCEPTION_INFORMATION, *PSYSTEM_EXCEPTION_INFORMATION;

typedef enum _SYSTEM_CRASH_DUMP_CONFIGURATION_CLASS
{
    SystemCrashDumpDisable,
    SystemCrashDumpReconfigure,
    SystemCrashDumpInitializationComplete
} SYSTEM_CRASH_DUMP_CONFIGURATION_CLASS, *PSYSTEM_CRASH_DUMP_CONFIGURATION_CLASS;

typedef struct _SYSTEM_CRASH_DUMP_STATE_INFORMATION
{
    SYSTEM_CRASH_DUMP_CONFIGURATION_CLASS CrashDumpConfigurationClass;
} SYSTEM_CRASH_DUMP_STATE_INFORMATION, *PSYSTEM_CRASH_DUMP_STATE_INFORMATION;

typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
{
    BOOLEAN KernelDebuggerEnabled;
    BOOLEAN KernelDebuggerNotPresent;
} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

typedef struct _SYSTEM_CONTEXT_SWITCH_INFORMATION
{
    ULONG ContextSwitches;
    ULONG FindAny;
    ULONG FindLast;
    ULONG FindIdeal;
    ULONG IdleAny;
    ULONG IdleCurrent;
    ULONG IdleLast;
    ULONG IdleIdeal;
    ULONG PreemptAny;
    ULONG PreemptCurrent;
    ULONG PreemptLast;
    ULONG SwitchToIdle;
} SYSTEM_CONTEXT_SWITCH_INFORMATION, *PSYSTEM_CONTEXT_SWITCH_INFORMATION;

typedef struct _SYSTEM_REGISTRY_QUOTA_INFORMATION
{
    ULONG RegistryQuotaAllowed;
    ULONG RegistryQuotaUsed;
    SIZE_T PagedPoolSize;
} SYSTEM_REGISTRY_QUOTA_INFORMATION, *PSYSTEM_REGISTRY_QUOTA_INFORMATION;

typedef struct _SYSTEM_PROCESSOR_IDLE_INFORMATION
{
    ULONGLONG IdleTime;
    ULONGLONG C1Time;
    ULONGLONG C2Time;
    ULONGLONG C3Time;
    ULONG C1Transitions;
    ULONG C2Transitions;
    ULONG C3Transitions;
    ULONG Padding;
} SYSTEM_PROCESSOR_IDLE_INFORMATION, *PSYSTEM_PROCESSOR_IDLE_INFORMATION;

typedef struct _SYSTEM_LEGACY_DRIVER_INFORMATION
{
    ULONG VetoType;
    UNICODE_STRING VetoList;
} SYSTEM_LEGACY_DRIVER_INFORMATION, *PSYSTEM_LEGACY_DRIVER_INFORMATION;

typedef struct _SYSTEM_LOOKASIDE_INFORMATION
{
    USHORT CurrentDepth;
    USHORT MaximumDepth;
    ULONG TotalAllocates;
    ULONG AllocateMisses;
    ULONG TotalFrees;
    ULONG FreeMisses;
    ULONG Type;
    ULONG Tag;
    ULONG Size;
} SYSTEM_LOOKASIDE_INFORMATION, *PSYSTEM_LOOKASIDE_INFORMATION;

// private
typedef struct _SYSTEM_RANGE_START_INFORMATION
{
    PVOID SystemRangeStart;
} SYSTEM_RANGE_START_INFORMATION, *PSYSTEM_RANGE_START_INFORMATION;

typedef struct _SYSTEM_VERIFIER_INFORMATION_LEGACY // pre-19H1
{
    ULONG NextEntryOffset;
    ULONG Level;
    UNICODE_STRING DriverName;

    ULONG RaiseIrqls;
    ULONG AcquireSpinLocks;
    ULONG SynchronizeExecutions;
    ULONG AllocationsAttempted;

    ULONG AllocationsSucceeded;
    ULONG AllocationsSucceededSpecialPool;
    ULONG AllocationsWithNoTag;
    ULONG TrimRequests;

    ULONG Trims;
    ULONG AllocationsFailed;
    ULONG AllocationsFailedDeliberately;
    ULONG Loads;

    ULONG Unloads;
    ULONG UnTrackedPool;
    ULONG CurrentPagedPoolAllocations;
    ULONG CurrentNonPagedPoolAllocations;

    ULONG PeakPagedPoolAllocations;
    ULONG PeakNonPagedPoolAllocations;

    SIZE_T PagedPoolUsageInBytes;
    SIZE_T NonPagedPoolUsageInBytes;
    SIZE_T PeakPagedPoolUsageInBytes;
    SIZE_T PeakNonPagedPoolUsageInBytes;
} SYSTEM_VERIFIER_INFORMATION_LEGACY, *PSYSTEM_VERIFIER_INFORMATION_LEGACY;

typedef struct _SYSTEM_VERIFIER_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG Level;
    ULONG RuleClasses[2];
    ULONG TriageContext;
    ULONG AreAllDriversBeingVerified;

    UNICODE_STRING DriverName;

    ULONG RaiseIrqls;
    ULONG AcquireSpinLocks;
    ULONG SynchronizeExecutions;
    ULONG AllocationsAttempted;

    ULONG AllocationsSucceeded;
    ULONG AllocationsSucceededSpecialPool;
    ULONG AllocationsWithNoTag;
    ULONG TrimRequests;

    ULONG Trims;
    ULONG AllocationsFailed;
    ULONG AllocationsFailedDeliberately;
    ULONG Loads;

    ULONG Unloads;
    ULONG UnTrackedPool;
    ULONG CurrentPagedPoolAllocations;
    ULONG CurrentNonPagedPoolAllocations;

    ULONG PeakPagedPoolAllocations;
    ULONG PeakNonPagedPoolAllocations;

    SIZE_T PagedPoolUsageInBytes;
    SIZE_T NonPagedPoolUsageInBytes;
    SIZE_T PeakPagedPoolUsageInBytes;
    SIZE_T PeakNonPagedPoolUsageInBytes;
} SYSTEM_VERIFIER_INFORMATION, *PSYSTEM_VERIFIER_INFORMATION;

typedef struct _SYSTEM_SESSION_PROCESS_INFORMATION
{
    ULONG SessionId;
    ULONG SizeOfBuf;
    PVOID Buffer;
} SYSTEM_SESSION_PROCESS_INFORMATION, *PSYSTEM_SESSION_PROCESS_INFORMATION;

typedef struct _SYSTEM_PROCESSOR_POWER_INFORMATION
{
    UCHAR CurrentFrequency;
    UCHAR ThermalLimitFrequency;
    UCHAR ConstantThrottleFrequency;
    UCHAR DegradedThrottleFrequency;
    UCHAR LastBusyFrequency;
    UCHAR LastC3Frequency;
    UCHAR LastAdjustedBusyFrequency;
    UCHAR ProcessorMinThrottle;
    UCHAR ProcessorMaxThrottle;
    ULONG NumberOfFrequencies;
    ULONG PromotionCount;
    ULONG DemotionCount;
    ULONG ErrorCount;
    ULONG RetryCount;
    ULONGLONG CurrentFrequencyTime;
    ULONGLONG CurrentProcessorTime;
    ULONGLONG CurrentProcessorIdleTime;
    ULONGLONG LastProcessorTime;
    ULONGLONG LastProcessorIdleTime;
    ULONGLONG Energy;
} SYSTEM_PROCESSOR_POWER_INFORMATION, *PSYSTEM_PROCESSOR_POWER_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX
{
    PVOID Object;
    ULONG_PTR UniqueProcessId;
    ULONG_PTR HandleValue;
    ULONG GrantedAccess;
    USHORT CreatorBackTraceIndex;
    USHORT ObjectTypeIndex;
    ULONG HandleAttributes;
    ULONG Reserved;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;

typedef struct _SYSTEM_HANDLE_INFORMATION_EX
{
    ULONG_PTR NumberOfHandles;
    ULONG_PTR Reserved;
    SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX Handles[1];
} SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;

typedef struct _SYSTEM_BIGPOOL_ENTRY
{
    union
    {
        PVOID VirtualAddress;
        ULONG_PTR NonPaged : 1;
    };
    SIZE_T SizeInBytes;
    union
    {
        UCHAR Tag[4];
        ULONG TagUlong;
    };
} SYSTEM_BIGPOOL_ENTRY, *PSYSTEM_BIGPOOL_ENTRY;

typedef struct _SYSTEM_BIGPOOL_INFORMATION
{
    ULONG Count;
    SYSTEM_BIGPOOL_ENTRY AllocatedInfo[1];
} SYSTEM_BIGPOOL_INFORMATION, *PSYSTEM_BIGPOOL_INFORMATION;

typedef struct _SYSTEM_POOL_ENTRY
{
    BOOLEAN Allocated;
    BOOLEAN Spare0;
    USHORT AllocatorBackTraceIndex;
    ULONG Size;
    union
    {
        UCHAR Tag[4];
        ULONG TagUlong;
        PVOID ProcessChargedQuota;
    };
} SYSTEM_POOL_ENTRY, *PSYSTEM_POOL_ENTRY;

typedef struct _SYSTEM_POOL_INFORMATION
{
    SIZE_T TotalSize;
    PVOID FirstEntry;
    USHORT EntryOverhead;
    BOOLEAN PoolTagPresent;
    BOOLEAN Spare0;
    ULONG NumberOfEntries;
    SYSTEM_POOL_ENTRY Entries[1];
} SYSTEM_POOL_INFORMATION, *PSYSTEM_POOL_INFORMATION;

typedef struct _SYSTEM_SESSION_POOLTAG_INFORMATION
{
    SIZE_T NextEntryOffset;
    ULONG SessionId;
    ULONG Count;
    SYSTEM_POOLTAG TagInfo[1];
} SYSTEM_SESSION_POOLTAG_INFORMATION, *PSYSTEM_SESSION_POOLTAG_INFORMATION;

typedef struct _SYSTEM_SESSION_MAPPED_VIEW_INFORMATION
{
    SIZE_T NextEntryOffset;
    ULONG SessionId;
    ULONG ViewFailures;
    SIZE_T NumberOfBytesAvailable;
    SIZE_T NumberOfBytesAvailableContiguous;
} SYSTEM_SESSION_MAPPED_VIEW_INFORMATION, *PSYSTEM_SESSION_MAPPED_VIEW_INFORMATION;

// private
typedef enum _SYSTEM_FIRMWARE_TABLE_ACTION
{
    SystemFirmwareTableEnumerate,
    SystemFirmwareTableGet,
    SystemFirmwareTableMax
} SYSTEM_FIRMWARE_TABLE_ACTION;

// private
typedef struct _SYSTEM_FIRMWARE_TABLE_INFORMATION
{
    ULONG ProviderSignature; // (same as the GetSystemFirmwareTable function)
    SYSTEM_FIRMWARE_TABLE_ACTION Action;
    ULONG TableID;
    ULONG TableBufferLength;
    UCHAR TableBuffer[1];
} SYSTEM_FIRMWARE_TABLE_INFORMATION, *PSYSTEM_FIRMWARE_TABLE_INFORMATION;

// private
typedef NTSTATUS (__cdecl* PFNFTH)(
    _Inout_ PSYSTEM_FIRMWARE_TABLE_INFORMATION SystemFirmwareTableInfo
    );

// private
typedef struct _SYSTEM_FIRMWARE_TABLE_HANDLER
{
    ULONG ProviderSignature;
    BOOLEAN Register;
    PFNFTH FirmwareTableHandler;
    PVOID DriverObject;
} SYSTEM_FIRMWARE_TABLE_HANDLER, *PSYSTEM_FIRMWARE_TABLE_HANDLER;

// private
typedef struct _SYSTEM_MEMORY_LIST_INFORMATION
{
    ULONG_PTR ZeroPageCount;
    ULONG_PTR FreePageCount;
    ULONG_PTR ModifiedPageCount;
    ULONG_PTR ModifiedNoWritePageCount;
    ULONG_PTR BadPageCount;
    ULONG_PTR PageCountByPriority[8];
    ULONG_PTR RepurposedPagesByPriority[8];
    ULONG_PTR ModifiedPageCountPageFile;
} SYSTEM_MEMORY_LIST_INFORMATION, *PSYSTEM_MEMORY_LIST_INFORMATION;

// private
typedef enum _SYSTEM_MEMORY_LIST_COMMAND
{
    MemoryCaptureAccessedBits,
    MemoryCaptureAndResetAccessedBits,
    MemoryEmptyWorkingSets,
    MemoryFlushModifiedList,
    MemoryPurgeStandbyList,
    MemoryPurgeLowPriorityStandbyList,
    MemoryCommandMax
} SYSTEM_MEMORY_LIST_COMMAND;

// private
typedef struct _SYSTEM_THREAD_CID_PRIORITY_INFORMATION
{
    CLIENT_ID ClientId;
    KPRIORITY Priority;
} SYSTEM_THREAD_CID_PRIORITY_INFORMATION, *PSYSTEM_THREAD_CID_PRIORITY_INFORMATION;

// private
typedef struct _SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION
{
    ULONGLONG CycleTime;
} SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION, *PSYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION;

// private
typedef struct _SYSTEM_VERIFIER_ISSUE
{
    ULONGLONG IssueType;
    PVOID Address;
    ULONGLONG Parameters[2];
} SYSTEM_VERIFIER_ISSUE, *PSYSTEM_VERIFIER_ISSUE;

// private
typedef struct _SYSTEM_VERIFIER_CANCELLATION_INFORMATION
{
    ULONG CancelProbability;
    ULONG CancelThreshold;
    ULONG CompletionThreshold;
    ULONG CancellationVerifierDisabled;
    ULONG AvailableIssues;
    SYSTEM_VERIFIER_ISSUE Issues[128];
} SYSTEM_VERIFIER_CANCELLATION_INFORMATION, *PSYSTEM_VERIFIER_CANCELLATION_INFORMATION;

// private
typedef struct _SYSTEM_REF_TRACE_INFORMATION
{
    BOOLEAN TraceEnable;
    BOOLEAN TracePermanent;
    UNICODE_STRING TraceProcessName;
    UNICODE_STRING TracePoolTags;
} SYSTEM_REF_TRACE_INFORMATION, *PSYSTEM_REF_TRACE_INFORMATION;

// private
typedef struct _SYSTEM_SPECIAL_POOL_INFORMATION
{
    ULONG PoolTag;
    ULONG Flags;
} SYSTEM_SPECIAL_POOL_INFORMATION, *PSYSTEM_SPECIAL_POOL_INFORMATION;

// private
typedef struct _SYSTEM_PROCESS_ID_INFORMATION
{
    HANDLE ProcessId;
    UNICODE_STRING ImageName;
} SYSTEM_PROCESS_ID_INFORMATION, *PSYSTEM_PROCESS_ID_INFORMATION;

// private
typedef struct _SYSTEM_BOOT_ENVIRONMENT_INFORMATION
{
    GUID BootIdentifier;
    FIRMWARE_TYPE FirmwareType;
    union
    {
        ULONGLONG BootFlags;
        struct
        {
            ULONGLONG DbgMenuOsSelection : 1; // REDSTONE4
            ULONGLONG DbgHiberBoot : 1;
            ULONGLONG DbgSoftBoot : 1;
            ULONGLONG DbgMeasuredLaunch : 1;
            ULONGLONG DbgMeasuredLaunchCapable : 1; // 19H1
            ULONGLONG DbgSystemHiveReplace : 1;
            ULONGLONG DbgMeasuredLaunchSmmProtections : 1;
            ULONGLONG DbgMeasuredLaunchSmmLevel : 7; // 20H1
        };
    };
} SYSTEM_BOOT_ENVIRONMENT_INFORMATION, *PSYSTEM_BOOT_ENVIRONMENT_INFORMATION;

// private
typedef struct _SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION
{
    ULONG FlagsToEnable;
    ULONG FlagsToDisable;
} SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION, *PSYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION;

// private
typedef struct _SYSTEM_PREFETCH_PATCH_INFORMATION
{
    ULONG PrefetchPatchCount;
} SYSTEM_PREFETCH_PATCH_INFORMATION, *PSYSTEM_PREFETCH_PATCH_INFORMATION;

// private
typedef struct _SYSTEM_VERIFIER_FAULTS_INFORMATION
{
    ULONG Probability;
    ULONG MaxProbability;
    UNICODE_STRING PoolTags;
    UNICODE_STRING Applications;
} SYSTEM_VERIFIER_FAULTS_INFORMATION, *PSYSTEM_VERIFIER_FAULTS_INFORMATION;

// private
typedef struct _SYSTEM_VERIFIER_INFORMATION_EX
{
    ULONG VerifyMode;
    ULONG OptionChanges;
    UNICODE_STRING PreviousBucketName;
    ULONG IrpCancelTimeoutMsec;
    ULONG VerifierExtensionEnabled;
#ifdef _WIN64
    ULONG Reserved[1];
#else
    ULONG Reserved[3];
#endif
} SYSTEM_VERIFIER_INFORMATION_EX, *PSYSTEM_VERIFIER_INFORMATION_EX;

// private
typedef struct _SYSTEM_SYSTEM_PARTITION_INFORMATION
{
    UNICODE_STRING SystemPartition;
} SYSTEM_SYSTEM_PARTITION_INFORMATION, *PSYSTEM_SYSTEM_PARTITION_INFORMATION;

// private
typedef struct _SYSTEM_SYSTEM_DISK_INFORMATION
{
    UNICODE_STRING SystemDisk;
} SYSTEM_SYSTEM_DISK_INFORMATION, *PSYSTEM_SYSTEM_DISK_INFORMATION;

// private (Windows 8.1 and above)
typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT
{
    ULONGLONG Hits;
    UCHAR PercentFrequency;
} SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT, *PSYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT;

// private (Windows 7 and Windows 8)
typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT_WIN8
{
    ULONG Hits;
    UCHAR PercentFrequency;
} SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT_WIN8, *PSYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT_WIN8;

// private
typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_STATE_DISTRIBUTION
{
    ULONG ProcessorNumber;
    ULONG StateCount;
    SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT States[1];
} SYSTEM_PROCESSOR_PERFORMANCE_STATE_DISTRIBUTION, *PSYSTEM_PROCESSOR_PERFORMANCE_STATE_DISTRIBUTION;

// private
typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION
{
    ULONG ProcessorCount;
    ULONG Offsets[1];
} SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION, *PSYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION;

#define CODEINTEGRITY_OPTION_ENABLED 0x01
#define CODEINTEGRITY_OPTION_TESTSIGN 0x02
#define CODEINTEGRITY_OPTION_UMCI_ENABLED 0x04
#define CODEINTEGRITY_OPTION_UMCI_AUDITMODE_ENABLED 0x08
#define CODEINTEGRITY_OPTION_UMCI_EXCLUSIONPATHS_ENABLED 0x10
#define CODEINTEGRITY_OPTION_TEST_BUILD 0x20
#define CODEINTEGRITY_OPTION_PREPRODUCTION_BUILD 0x40
#define CODEINTEGRITY_OPTION_DEBUGMODE_ENABLED 0x80
#define CODEINTEGRITY_OPTION_FLIGHT_BUILD 0x100
#define CODEINTEGRITY_OPTION_FLIGHTING_ENABLED 0x200
#define CODEINTEGRITY_OPTION_HVCI_KMCI_ENABLED 0x400
#define CODEINTEGRITY_OPTION_HVCI_KMCI_AUDITMODE_ENABLED 0x800
#define CODEINTEGRITY_OPTION_HVCI_KMCI_STRICTMODE_ENABLED 0x1000
#define CODEINTEGRITY_OPTION_HVCI_IUM_ENABLED 0x2000

// private
typedef struct _SYSTEM_CODEINTEGRITY_INFORMATION
{
    ULONG Length;
    ULONG CodeIntegrityOptions;
} SYSTEM_CODEINTEGRITY_INFORMATION, *PSYSTEM_CODEINTEGRITY_INFORMATION;

// private
typedef struct _SYSTEM_PROCESSOR_MICROCODE_UPDATE_INFORMATION
{
    ULONG Operation;
} SYSTEM_PROCESSOR_MICROCODE_UPDATE_INFORMATION, *PSYSTEM_PROCESSOR_MICROCODE_UPDATE_INFORMATION;

// private
typedef enum _SYSTEM_VA_TYPE
{
    SystemVaTypeAll,
    SystemVaTypeNonPagedPool,
    SystemVaTypePagedPool,
    SystemVaTypeSystemCache,
    SystemVaTypeSystemPtes,
    SystemVaTypeSessionSpace,
    SystemVaTypeMax
} SYSTEM_VA_TYPE, *PSYSTEM_VA_TYPE;

// private
typedef struct _SYSTEM_VA_LIST_INFORMATION
{
    SIZE_T VirtualSize;
    SIZE_T VirtualPeak;
    SIZE_T VirtualLimit;
    SIZE_T AllocationFailures;
} SYSTEM_VA_LIST_INFORMATION, *PSYSTEM_VA_LIST_INFORMATION;

// rev
typedef enum _SYSTEM_STORE_INFORMATION_CLASS
{
    SystemStoreCompressionInformation = 22 // q: SYSTEM_STORE_COMPRESSION_INFORMATION
} SYSTEM_STORE_INFORMATION_CLASS;

// rev
#define SYSTEM_STORE_INFORMATION_VERSION 1

// rev
typedef struct _SYSTEM_STORE_INFORMATION
{
    _In_ ULONG Version;
    _In_ SYSTEM_STORE_INFORMATION_CLASS StoreInformationClass;
    _Inout_ PVOID Data;
    _Inout_ ULONG Length;
} SYSTEM_STORE_INFORMATION, *PSYSTEM_STORE_INFORMATION;

// rev
#define SYSTEM_STORE_COMPRESSION_INFORMATION_VERSION 3

// rev
typedef struct _SYSTEM_STORE_COMPRESSION_INFORMATION
{
    ULONG Version;
    ULONG CompressionPid;
    ULONGLONG CompressionWorkingSetSize;
    ULONGLONG CompressSize;
    ULONGLONG CompressedSize;
    ULONGLONG NonCompressedSize;
} SYSTEM_STORE_COMPRESSION_INFORMATION, *PSYSTEM_STORE_COMPRESSION_INFORMATION;

// private
typedef struct _SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS
{
    HANDLE KeyHandle;
    PUNICODE_STRING ValueNamePointer;
    PULONG RequiredLengthPointer;
    PUCHAR Buffer;
    ULONG BufferLength;
    ULONG Type;
    PUCHAR AppendBuffer;
    ULONG AppendBufferLength;
    BOOLEAN CreateIfDoesntExist;
    BOOLEAN TruncateExistingValue;
} SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS, *PSYSTEM_REGISTRY_APPEND_STRING_PARAMETERS;

// msdn
typedef struct _SYSTEM_VHD_BOOT_INFORMATION
{
    BOOLEAN OsDiskIsVhd;
    ULONG OsVhdFilePathOffset;
    WCHAR OsVhdParentVolume[ANYSIZE_ARRAY];
} SYSTEM_VHD_BOOT_INFORMATION, *PSYSTEM_VHD_BOOT_INFORMATION;

// private
typedef struct _PS_CPU_QUOTA_QUERY_ENTRY
{
    ULONG SessionId;
    ULONG Weight;
} PS_CPU_QUOTA_QUERY_ENTRY, *PPS_CPU_QUOTA_QUERY_ENTRY;

// private
typedef struct _PS_CPU_QUOTA_QUERY_INFORMATION
{
    ULONG SessionCount;
    PS_CPU_QUOTA_QUERY_ENTRY SessionInformation[1];
} PS_CPU_QUOTA_QUERY_INFORMATION, *PPS_CPU_QUOTA_QUERY_INFORMATION;

// private
typedef struct _SYSTEM_ERROR_PORT_TIMEOUTS
{
    ULONG StartTimeout;
    ULONG CommTimeout;
} SYSTEM_ERROR_PORT_TIMEOUTS, *PSYSTEM_ERROR_PORT_TIMEOUTS;

// private
typedef struct _SYSTEM_LOW_PRIORITY_IO_INFORMATION
{
    ULONG LowPriReadOperations;
    ULONG LowPriWriteOperations;
    ULONG KernelBumpedToNormalOperations;
    ULONG LowPriPagingReadOperations;
    ULONG KernelPagingReadsBumpedToNormal;
    ULONG LowPriPagingWriteOperations;
    ULONG KernelPagingWritesBumpedToNormal;
    ULONG BoostedIrpCount;
    ULONG BoostedPagingIrpCount;
    ULONG BlanketBoostCount;
} SYSTEM_LOW_PRIORITY_IO_INFORMATION, *PSYSTEM_LOW_PRIORITY_IO_INFORMATION;

// symbols
typedef enum _TPM_BOOT_ENTROPY_RESULT_CODE
{
    TpmBootEntropyStructureUninitialized,
    TpmBootEntropyDisabledByPolicy,
    TpmBootEntropyNoTpmFound,
    TpmBootEntropyTpmError,
    TpmBootEntropySuccess
} TPM_BOOT_ENTROPY_RESULT_CODE;

// Contents of KeLoaderBlock->Extension->TpmBootEntropyResult (TPM_BOOT_ENTROPY_LDR_RESULT).
// EntropyData is truncated to 40 bytes.

// private
typedef struct _TPM_BOOT_ENTROPY_NT_RESULT
{
    ULONGLONG Policy;
    TPM_BOOT_ENTROPY_RESULT_CODE ResultCode;
    NTSTATUS ResultStatus;
    ULONGLONG Time;
    ULONG EntropyLength;
    UCHAR EntropyData[40];
} TPM_BOOT_ENTROPY_NT_RESULT, *PTPM_BOOT_ENTROPY_NT_RESULT;

// private
typedef struct _SYSTEM_VERIFIER_COUNTERS_INFORMATION
{
    SYSTEM_VERIFIER_INFORMATION Legacy;
    ULONG RaiseIrqls;
    ULONG AcquireSpinLocks;
    ULONG SynchronizeExecutions;
    ULONG AllocationsWithNoTag;
    ULONG AllocationsFailed;
    ULONG AllocationsFailedDeliberately;
    SIZE_T LockedBytes;
    SIZE_T PeakLockedBytes;
    SIZE_T MappedLockedBytes;
    SIZE_T PeakMappedLockedBytes;
    SIZE_T MappedIoSpaceBytes;
    SIZE_T PeakMappedIoSpaceBytes;
    SIZE_T PagesForMdlBytes;
    SIZE_T PeakPagesForMdlBytes;
    SIZE_T ContiguousMemoryBytes;
    SIZE_T PeakContiguousMemoryBytes;
    ULONG ExecutePoolTypes; // REDSTONE2
    ULONG ExecutePageProtections;
    ULONG ExecutePageMappings;
    ULONG ExecuteWriteSections;
    ULONG SectionAlignmentFailures;
    ULONG UnsupportedRelocs;
    ULONG IATInExecutableSection;
} SYSTEM_VERIFIER_COUNTERS_INFORMATION, *PSYSTEM_VERIFIER_COUNTERS_INFORMATION;

// private
typedef struct _SYSTEM_ACPI_AUDIT_INFORMATION
{
    ULONG RsdpCount;
    ULONG SameRsdt : 1;
    ULONG SlicPresent : 1;
    ULONG SlicDifferent : 1;
} SYSTEM_ACPI_AUDIT_INFORMATION, *PSYSTEM_ACPI_AUDIT_INFORMATION;

// private
typedef struct _SYSTEM_BASIC_PERFORMANCE_INFORMATION
{
    SIZE_T AvailablePages;
    SIZE_T CommittedPages;
    SIZE_T CommitLimit;
    SIZE_T PeakCommitment;
} SYSTEM_BASIC_PERFORMANCE_INFORMATION, *PSYSTEM_BASIC_PERFORMANCE_INFORMATION;

// begin_msdn

typedef struct _QUERY_PERFORMANCE_COUNTER_FLAGS
{
    union
    {
        struct
        {
            ULONG KernelTransition : 1;
            ULONG Reserved : 31;
        };
        ULONG ul;
    };
} QUERY_PERFORMANCE_COUNTER_FLAGS;

typedef struct _SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION
{
    ULONG Version;
    QUERY_PERFORMANCE_COUNTER_FLAGS Flags;
    QUERY_PERFORMANCE_COUNTER_FLAGS ValidFlags;
} SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION, *PSYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION;

// end_msdn

// private
typedef enum _SYSTEM_PIXEL_FORMAT
{
    SystemPixelFormatUnknown,
    SystemPixelFormatR8G8B8,
    SystemPixelFormatR8G8B8X8,
    SystemPixelFormatB8G8R8,
    SystemPixelFormatB8G8R8X8
} SYSTEM_PIXEL_FORMAT;

// private
typedef struct _SYSTEM_BOOT_GRAPHICS_INFORMATION
{
    LARGE_INTEGER FrameBuffer;
    ULONG Width;
    ULONG Height;
    ULONG PixelStride;
    ULONG Flags;
    SYSTEM_PIXEL_FORMAT Format;
    ULONG DisplayRotation;
} SYSTEM_BOOT_GRAPHICS_INFORMATION, *PSYSTEM_BOOT_GRAPHICS_INFORMATION;

// private
typedef struct _MEMORY_SCRUB_INFORMATION
{
    HANDLE Handle;
    ULONG PagesScrubbed;
} MEMORY_SCRUB_INFORMATION, *PMEMORY_SCRUB_INFORMATION;

// private
typedef struct _PEBS_DS_SAVE_AREA32
{
    ULONG BtsBufferBase;
    ULONG BtsIndex;
    ULONG BtsAbsoluteMaximum;
    ULONG BtsInterruptThreshold;
    ULONG PebsBufferBase;
    ULONG PebsIndex;
    ULONG PebsAbsoluteMaximum;
    ULONG PebsInterruptThreshold;
    ULONG PebsGpCounterReset[8];
    ULONG PebsFixedCounterReset[4];
} PEBS_DS_SAVE_AREA32, *PPEBS_DS_SAVE_AREA32;

// private
typedef struct _PEBS_DS_SAVE_AREA64
{
    ULONGLONG BtsBufferBase;
    ULONGLONG BtsIndex;
    ULONGLONG BtsAbsoluteMaximum;
    ULONGLONG BtsInterruptThreshold;
    ULONGLONG PebsBufferBase;
    ULONGLONG PebsIndex;
    ULONGLONG PebsAbsoluteMaximum;
    ULONGLONG PebsInterruptThreshold;
    ULONGLONG PebsGpCounterReset[8];
    ULONGLONG PebsFixedCounterReset[4];
} PEBS_DS_SAVE_AREA64, *PPEBS_DS_SAVE_AREA64;

// private
typedef union _PEBS_DS_SAVE_AREA
{
    PEBS_DS_SAVE_AREA32 As32Bit;
    PEBS_DS_SAVE_AREA64 As64Bit;
} PEBS_DS_SAVE_AREA, *PPEBS_DS_SAVE_AREA;

// private
typedef struct _PROCESSOR_PROFILE_CONTROL_AREA
{
    PEBS_DS_SAVE_AREA PebsDsSaveArea;
} PROCESSOR_PROFILE_CONTROL_AREA, *PPROCESSOR_PROFILE_CONTROL_AREA;

// private
typedef struct _SYSTEM_PROCESSOR_PROFILE_CONTROL_AREA
{
    PROCESSOR_PROFILE_CONTROL_AREA ProcessorProfileControlArea;
    BOOLEAN Allocate;
} SYSTEM_PROCESSOR_PROFILE_CONTROL_AREA, *PSYSTEM_PROCESSOR_PROFILE_CONTROL_AREA;

// private
typedef struct _MEMORY_COMBINE_INFORMATION
{
    HANDLE Handle;
    ULONG_PTR PagesCombined;
} MEMORY_COMBINE_INFORMATION, *PMEMORY_COMBINE_INFORMATION;

// rev
#define MEMORY_COMBINE_FLAGS_COMMON_PAGES_ONLY 0x4

// private
typedef struct _MEMORY_COMBINE_INFORMATION_EX
{
    HANDLE Handle;
    ULONG_PTR PagesCombined;
    ULONG Flags;
} MEMORY_COMBINE_INFORMATION_EX, *PMEMORY_COMBINE_INFORMATION_EX;

// private
typedef struct _MEMORY_COMBINE_INFORMATION_EX2
{
    HANDLE Handle;
    ULONG_PTR PagesCombined;
    ULONG Flags;
    HANDLE ProcessHandle;
} MEMORY_COMBINE_INFORMATION_EX2, *PMEMORY_COMBINE_INFORMATION_EX2;

// private
typedef struct _SYSTEM_CONSOLE_INFORMATION
{
    ULONG DriverLoaded : 1;
    ULONG Spare : 31;
} SYSTEM_CONSOLE_INFORMATION, *PSYSTEM_CONSOLE_INFORMATION;

// private
typedef struct _SYSTEM_PLATFORM_BINARY_INFORMATION
{
    ULONG64 PhysicalAddress;
    PVOID HandoffBuffer;
    PVOID CommandLineBuffer;
    ULONG HandoffBufferSize;
    ULONG CommandLineBufferSize;
} SYSTEM_PLATFORM_BINARY_INFORMATION, *PSYSTEM_PLATFORM_BINARY_INFORMATION;

// private
typedef struct _SYSTEM_POLICY_INFORMATION
{
    PVOID InputData;
    PVOID OutputData;
    ULONG InputDataSize;
    ULONG OutputDataSize;
    ULONG Version;
} SYSTEM_POLICY_INFORMATION, *PSYSTEM_POLICY_INFORMATION;

// private
typedef struct _SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION
{
    ULONG NumberOfLogicalProcessors;
    ULONG NumberOfCores;
} SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION, *PSYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION;

// private
typedef struct _SYSTEM_DEVICE_DATA_INFORMATION
{
    UNICODE_STRING DeviceId;
    UNICODE_STRING DataName;
    ULONG DataType;
    ULONG DataBufferLength;
    PVOID DataBuffer;
} SYSTEM_DEVICE_DATA_INFORMATION, *PSYSTEM_DEVICE_DATA_INFORMATION;

// private
typedef struct _PHYSICAL_CHANNEL_RUN
{
    ULONG NodeNumber;
    ULONG ChannelNumber;
    ULONGLONG BasePage;
    ULONGLONG PageCount;
    ULONG Flags;
} PHYSICAL_CHANNEL_RUN, *PPHYSICAL_CHANNEL_RUN;

// private
typedef struct _SYSTEM_MEMORY_TOPOLOGY_INFORMATION
{
    ULONGLONG NumberOfRuns;
    ULONG NumberOfNodes;
    ULONG NumberOfChannels;
    PHYSICAL_CHANNEL_RUN Run[1];
} SYSTEM_MEMORY_TOPOLOGY_INFORMATION, *PSYSTEM_MEMORY_TOPOLOGY_INFORMATION;

// private
typedef struct _SYSTEM_MEMORY_CHANNEL_INFORMATION
{
    ULONG ChannelNumber;
    ULONG ChannelHeatIndex;
    ULONGLONG TotalPageCount;
    ULONGLONG ZeroPageCount;
    ULONGLONG FreePageCount;
    ULONGLONG StandbyPageCount;
} SYSTEM_MEMORY_CHANNEL_INFORMATION, *PSYSTEM_MEMORY_CHANNEL_INFORMATION;

// private
typedef struct _SYSTEM_BOOT_LOGO_INFORMATION
{
    ULONG Flags;
    ULONG BitmapOffset;
} SYSTEM_BOOT_LOGO_INFORMATION, *PSYSTEM_BOOT_LOGO_INFORMATION;

// private
typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX
{
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER DpcTime;
    LARGE_INTEGER InterruptTime;
    ULONG InterruptCount;
    ULONG Spare0;
    LARGE_INTEGER AvailableTime;
    LARGE_INTEGER Spare1;
    LARGE_INTEGER Spare2;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX;

// private
typedef struct _SYSTEM_SECUREBOOT_POLICY_INFORMATION
{
    GUID PolicyPublisher;
    ULONG PolicyVersion;
    ULONG PolicyOptions;
} SYSTEM_SECUREBOOT_POLICY_INFORMATION, *PSYSTEM_SECUREBOOT_POLICY_INFORMATION;

// private
typedef struct _SYSTEM_PAGEFILE_INFORMATION_EX
{
    union // HACK union declaration for convenience (dmex)
    {
        SYSTEM_PAGEFILE_INFORMATION Info;
        struct
        {
            ULONG NextEntryOffset;
            ULONG TotalSize;
            ULONG TotalInUse;
            ULONG PeakUsage;
            UNICODE_STRING PageFileName;
        };
    };

    ULONG MinimumSize;
    ULONG MaximumSize;
} SYSTEM_PAGEFILE_INFORMATION_EX, *PSYSTEM_PAGEFILE_INFORMATION_EX;

// private
typedef struct _SYSTEM_SECUREBOOT_INFORMATION
{
    BOOLEAN SecureBootEnabled;
    BOOLEAN SecureBootCapable;
} SYSTEM_SECUREBOOT_INFORMATION, *PSYSTEM_SECUREBOOT_INFORMATION;

// private
typedef struct _PROCESS_DISK_COUNTERS
{
    ULONGLONG BytesRead;
    ULONGLONG BytesWritten;
    ULONGLONG ReadOperationCount;
    ULONGLONG WriteOperationCount;
    ULONGLONG FlushOperationCount;
} PROCESS_DISK_COUNTERS, *PPROCESS_DISK_COUNTERS;

// private
typedef union _ENERGY_STATE_DURATION
{
    union
    {
        ULONGLONG Value;
        ULONG LastChangeTime;
    };

    ULONG Duration : 31;
    ULONG IsInState : 1;
} ENERGY_STATE_DURATION, *PENERGY_STATE_DURATION;

typedef struct _PROCESS_ENERGY_VALUES
{
    ULONGLONG Cycles[4][2];
    ULONGLONG DiskEnergy;
    ULONGLONG NetworkTailEnergy;
    ULONGLONG MBBTailEnergy;
    ULONGLONG NetworkTxRxBytes;
    ULONGLONG MBBTxRxBytes;
    union
    {
        ENERGY_STATE_DURATION Durations[3];
        struct
        {
            ENERGY_STATE_DURATION ForegroundDuration;
            ENERGY_STATE_DURATION DesktopVisibleDuration;
            ENERGY_STATE_DURATION PSMForegroundDuration;
        };
    };
    ULONG CompositionRendered;
    ULONG CompositionDirtyGenerated;
    ULONG CompositionDirtyPropagated;
    ULONG Reserved1;
    ULONGLONG AttributedCycles[4][2];
    ULONGLONG WorkOnBehalfCycles[4][2];
} PROCESS_ENERGY_VALUES, *PPROCESS_ENERGY_VALUES;

typedef struct _TIMELINE_BITMAP
{
    ULONGLONG Value;
    ULONG EndTime;
    ULONG Bitmap;
} TIMELINE_BITMAP, *PTIMELINE_BITMAP;

typedef struct _PROCESS_ENERGY_VALUES_EXTENSION
{
    union
    {
        TIMELINE_BITMAP Timelines[14]; // 9 for REDSTONE2, 14 for REDSTONE3/4/5
        struct
        {
            TIMELINE_BITMAP CpuTimeline;
            TIMELINE_BITMAP DiskTimeline;
            TIMELINE_BITMAP NetworkTimeline;
            TIMELINE_BITMAP MBBTimeline;
            TIMELINE_BITMAP ForegroundTimeline;
            TIMELINE_BITMAP DesktopVisibleTimeline;
            TIMELINE_BITMAP CompositionRenderedTimeline;
            TIMELINE_BITMAP CompositionDirtyGeneratedTimeline;
            TIMELINE_BITMAP CompositionDirtyPropagatedTimeline;
            TIMELINE_BITMAP InputTimeline; // REDSTONE3
            TIMELINE_BITMAP AudioInTimeline;
            TIMELINE_BITMAP AudioOutTimeline;
            TIMELINE_BITMAP DisplayRequiredTimeline;
            TIMELINE_BITMAP KeyboardInputTimeline;
        };
    };

    union // REDSTONE3
    {
        ENERGY_STATE_DURATION Durations[5];
        struct
        {
            ENERGY_STATE_DURATION InputDuration;
            ENERGY_STATE_DURATION AudioInDuration;
            ENERGY_STATE_DURATION AudioOutDuration;
            ENERGY_STATE_DURATION DisplayRequiredDuration;
            ENERGY_STATE_DURATION PSMBackgroundDuration;
        };
    };

    ULONG KeyboardInput;
    ULONG MouseInput;
} PROCESS_ENERGY_VALUES_EXTENSION, *PPROCESS_ENERGY_VALUES_EXTENSION;

typedef struct _PROCESS_EXTENDED_ENERGY_VALUES
{
    PROCESS_ENERGY_VALUES Base;
    PROCESS_ENERGY_VALUES_EXTENSION Extension;
} PROCESS_EXTENDED_ENERGY_VALUES, *PPROCESS_EXTENDED_ENERGY_VALUES;

// private
typedef enum _SYSTEM_PROCESS_CLASSIFICATION
{
    SystemProcessClassificationNormal,
    SystemProcessClassificationSystem,
    SystemProcessClassificationSecureSystem,
    SystemProcessClassificationMemCompression,
    SystemProcessClassificationRegistry, // REDSTONE4
    SystemProcessClassificationMaximum
} SYSTEM_PROCESS_CLASSIFICATION;

// private
typedef struct _SYSTEM_PROCESS_INFORMATION_EXTENSION
{
    PROCESS_DISK_COUNTERS DiskCounters;
    ULONGLONG ContextSwitches;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG HasStrongId : 1;
            ULONG Classification : 4; // SYSTEM_PROCESS_CLASSIFICATION
            ULONG BackgroundActivityModerated : 1;
            ULONG Spare : 26;
        };
    };
    ULONG UserSidOffset;
    ULONG PackageFullNameOffset; // since THRESHOLD
    PROCESS_ENERGY_VALUES EnergyValues; // since THRESHOLD
    ULONG AppIdOffset; // since THRESHOLD
    SIZE_T SharedCommitCharge; // since THRESHOLD2
    ULONG JobObjectId; // since REDSTONE
    ULONG SpareUlong; // since REDSTONE
    ULONGLONG ProcessSequenceNumber;
} SYSTEM_PROCESS_INFORMATION_EXTENSION, *PSYSTEM_PROCESS_INFORMATION_EXTENSION;

// private
typedef struct _SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION
{
    BOOLEAN EfiLauncherEnabled;
} SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION, *PSYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION;

// private
typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX
{
    BOOLEAN DebuggerAllowed;
    BOOLEAN DebuggerEnabled;
    BOOLEAN DebuggerPresent;
} SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION_EX;

// private
typedef struct _SYSTEM_ELAM_CERTIFICATE_INFORMATION
{
    HANDLE ElamDriverFile;
} SYSTEM_ELAM_CERTIFICATE_INFORMATION, *PSYSTEM_ELAM_CERTIFICATE_INFORMATION;

// private
typedef struct _SYSTEM_PROCESSOR_FEATURES_INFORMATION
{
    ULONGLONG ProcessorFeatureBits;
    ULONGLONG Reserved[3];
} SYSTEM_PROCESSOR_FEATURES_INFORMATION, *PSYSTEM_PROCESSOR_FEATURES_INFORMATION;

// private
typedef struct _SYSTEM_MANUFACTURING_INFORMATION
{
    ULONG Options;
    UNICODE_STRING ProfileName;
} SYSTEM_MANUFACTURING_INFORMATION, *PSYSTEM_MANUFACTURING_INFORMATION;

// private
typedef struct _SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION
{
    BOOLEAN Enabled;
} SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION, *PSYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION;

// private
typedef struct _HV_DETAILS
{
    ULONG Data[4];
} HV_DETAILS, *PHV_DETAILS;

// private
typedef struct _SYSTEM_HYPERVISOR_DETAIL_INFORMATION
{
    HV_DETAILS HvVendorAndMaxFunction;
    HV_DETAILS HypervisorInterface;
    HV_DETAILS HypervisorVersion;
    HV_DETAILS HvFeatures;
    HV_DETAILS HwFeatures;
    HV_DETAILS EnlightenmentInfo;
    HV_DETAILS ImplementationLimits;
} SYSTEM_HYPERVISOR_DETAIL_INFORMATION, *PSYSTEM_HYPERVISOR_DETAIL_INFORMATION;

// private
typedef struct _SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION
{
    ULONGLONG Cycles[2][4];
} SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION, *PSYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION;

// private
typedef struct _SYSTEM_TPM_INFORMATION
{
    ULONG Flags;
} SYSTEM_TPM_INFORMATION, *PSYSTEM_TPM_INFORMATION;

// private
typedef struct _SYSTEM_VSM_PROTECTION_INFORMATION
{
    BOOLEAN DmaProtectionsAvailable;
    BOOLEAN DmaProtectionsInUse;
    BOOLEAN HardwareMbecAvailable; // REDSTONE4 (CVE-2018-3639)
    BOOLEAN ApicVirtualizationAvailable; // 20H1
} SYSTEM_VSM_PROTECTION_INFORMATION, *PSYSTEM_VSM_PROTECTION_INFORMATION;

// private
typedef struct _SYSTEM_KERNEL_DEBUGGER_FLAGS
{
    BOOLEAN KernelDebuggerIgnoreUmExceptions;
} SYSTEM_KERNEL_DEBUGGER_FLAGS, *PSYSTEM_KERNEL_DEBUGGER_FLAGS;

// private
typedef struct _SYSTEM_CODEINTEGRITYPOLICY_INFORMATION
{
    ULONG Options;
    ULONG HVCIOptions;
    ULONGLONG Version;
    GUID PolicyGuid;
} SYSTEM_CODEINTEGRITYPOLICY_INFORMATION, *PSYSTEM_CODEINTEGRITYPOLICY_INFORMATION;

// private
typedef struct _SYSTEM_ISOLATED_USER_MODE_INFORMATION
{
    BOOLEAN SecureKernelRunning : 1;
    BOOLEAN HvciEnabled : 1;
    BOOLEAN HvciStrictMode : 1;
    BOOLEAN DebugEnabled : 1;
    BOOLEAN FirmwarePageProtection : 1;
    BOOLEAN EncryptionKeyAvailable : 1;
    BOOLEAN SpareFlags : 2;
    BOOLEAN TrustletRunning : 1;
    BOOLEAN HvciDisableAllowed : 1;
    BOOLEAN SpareFlags2 : 6;
    BOOLEAN Spare0[6];
    ULONGLONG Spare1;
} SYSTEM_ISOLATED_USER_MODE_INFORMATION, *PSYSTEM_ISOLATED_USER_MODE_INFORMATION;

// private
typedef struct _SYSTEM_SINGLE_MODULE_INFORMATION
{
    PVOID TargetModuleAddress;
    RTL_PROCESS_MODULE_INFORMATION_EX ExInfo;
} SYSTEM_SINGLE_MODULE_INFORMATION, *PSYSTEM_SINGLE_MODULE_INFORMATION;

// private
typedef struct _SYSTEM_INTERRUPT_CPU_SET_INFORMATION
{
    ULONG Gsiv;
    USHORT Group;
    ULONGLONG CpuSets;
} SYSTEM_INTERRUPT_CPU_SET_INFORMATION, *PSYSTEM_INTERRUPT_CPU_SET_INFORMATION;

// private
typedef struct _SYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION
{
    SYSTEM_SECUREBOOT_POLICY_INFORMATION PolicyInformation;
    ULONG PolicySize;
    UCHAR Policy[1];
} SYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION, *PSYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION;

// private
typedef struct _SYSTEM_ROOT_SILO_INFORMATION
{
    ULONG NumberOfSilos;
    ULONG SiloIdList[1];
} SYSTEM_ROOT_SILO_INFORMATION, *PSYSTEM_ROOT_SILO_INFORMATION;

// private
typedef struct _SYSTEM_CPU_SET_TAG_INFORMATION
{
    ULONGLONG Tag;
    ULONGLONG CpuSets[1];
} SYSTEM_CPU_SET_TAG_INFORMATION, *PSYSTEM_CPU_SET_TAG_INFORMATION;

// private
typedef struct _SYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION
{
    ULONG ExtentCount;
    ULONG ValidStructureSize;
    ULONG NextExtentIndex;
    ULONG ExtentRestart;
    ULONG CycleCount;
    ULONG TimeoutCount;
    ULONGLONG CycleTime;
    ULONGLONG CycleTimeMax;
    ULONGLONG ExtentTime;
    ULONG ExtentTimeIndex;
    ULONG ExtentTimeMaxIndex;
    ULONGLONG ExtentTimeMax;
    ULONGLONG HyperFlushTimeMax;
    ULONGLONG TranslateVaTimeMax;
    ULONGLONG DebugExemptionCount;
    ULONGLONG TbHitCount;
    ULONGLONG TbMissCount;
    ULONGLONG VinaPendingYield;
    ULONGLONG HashCycles;
    ULONG HistogramOffset;
    ULONG HistogramBuckets;
    ULONG HistogramShift;
    ULONG Reserved1;
    ULONGLONG PageNotPresentCount;
} SYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION, *PSYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION;

// private
typedef struct _SYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION
{
    ULONG PlatformManifestSize;
    UCHAR PlatformManifest[1];
} SYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION, *PSYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION;

// private
typedef struct _SYSTEM_INTERRUPT_STEERING_INFORMATION_INPUT
{
    ULONG Gsiv;
    UCHAR ControllerInterrupt;
    UCHAR EdgeInterrupt;
    UCHAR IsPrimaryInterrupt;
    GROUP_AFFINITY TargetAffinity;
} SYSTEM_INTERRUPT_STEERING_INFORMATION_INPUT, *PSYSTEM_INTERRUPT_STEERING_INFORMATION_INPUT;

// private
typedef struct _SYSTEM_MEMORY_USAGE_INFORMATION
{
    ULONGLONG TotalPhysicalBytes;
    ULONGLONG AvailableBytes;
    LONGLONG ResidentAvailableBytes;
    ULONGLONG CommittedBytes;
    ULONGLONG SharedCommittedBytes;
    ULONGLONG CommitLimitBytes;
    ULONGLONG PeakCommitmentBytes;
} SYSTEM_MEMORY_USAGE_INFORMATION, *PSYSTEM_MEMORY_USAGE_INFORMATION;

// private
typedef struct _SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION
{
    HANDLE ImageFile;
    ULONG Type; // REDSTONE4
} SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION, *PSYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION;

// private
typedef struct _SYSTEM_PHYSICAL_MEMORY_INFORMATION
{
    ULONGLONG TotalPhysicalBytes;
    ULONGLONG LowestPhysicalAddress;
    ULONGLONG HighestPhysicalAddress;
} SYSTEM_PHYSICAL_MEMORY_INFORMATION, *PSYSTEM_PHYSICAL_MEMORY_INFORMATION;

// private
typedef enum _SYSTEM_ACTIVITY_MODERATION_STATE
{
    SystemActivityModerationStateSystemManaged,
    SystemActivityModerationStateUserManagedAllowThrottling,
    SystemActivityModerationStateUserManagedDisableThrottling,
    MaxSystemActivityModerationState
} SYSTEM_ACTIVITY_MODERATION_STATE;

// private - REDSTONE2
typedef struct _SYSTEM_ACTIVITY_MODERATION_EXE_STATE // REDSTONE3: Renamed SYSTEM_ACTIVITY_MODERATION_INFO
{
    UNICODE_STRING ExePathNt;
    SYSTEM_ACTIVITY_MODERATION_STATE ModerationState;
} SYSTEM_ACTIVITY_MODERATION_EXE_STATE, *PSYSTEM_ACTIVITY_MODERATION_EXE_STATE;

typedef enum _SYSTEM_ACTIVITY_MODERATION_APP_TYPE
{
    SystemActivityModerationAppTypeClassic,
    SystemActivityModerationAppTypePackaged,
    MaxSystemActivityModerationAppType
} SYSTEM_ACTIVITY_MODERATION_APP_TYPE;

// private - REDSTONE3
typedef struct _SYSTEM_ACTIVITY_MODERATION_INFO
{
    UNICODE_STRING Identifier;
    SYSTEM_ACTIVITY_MODERATION_STATE ModerationState;
    SYSTEM_ACTIVITY_MODERATION_APP_TYPE AppType;
} SYSTEM_ACTIVITY_MODERATION_INFO, *PSYSTEM_ACTIVITY_MODERATION_INFO;

// private
typedef struct _SYSTEM_ACTIVITY_MODERATION_USER_SETTINGS
{
    HANDLE UserKeyHandle;
} SYSTEM_ACTIVITY_MODERATION_USER_SETTINGS, *PSYSTEM_ACTIVITY_MODERATION_USER_SETTINGS;

// private
typedef struct _SYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG Locked : 1;
            ULONG UnlockApplied : 1; // Unlockable field removed 19H1
            ULONG UnlockIdValid : 1;
            ULONG Reserved : 29;
        };
    };
    UCHAR UnlockId[32]; // REDSTONE4
} SYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION, *PSYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION;

// private
typedef struct _SYSTEM_FLUSH_INFORMATION
{
    ULONG SupportedFlushMethods;
    ULONG ProcessorCacheFlushSize;
    ULONGLONG SystemFlushCapabilities;
    ULONGLONG Reserved[2];
} SYSTEM_FLUSH_INFORMATION, *PSYSTEM_FLUSH_INFORMATION;

// private
typedef struct _SYSTEM_WRITE_CONSTRAINT_INFORMATION
{
    ULONG WriteConstraintPolicy;
    ULONG Reserved;
} SYSTEM_WRITE_CONSTRAINT_INFORMATION, *PSYSTEM_WRITE_CONSTRAINT_INFORMATION;

// private
typedef struct _SYSTEM_KERNEL_VA_SHADOW_INFORMATION
{
    union
    {
        ULONG KvaShadowFlags;
        struct
        {
            ULONG KvaShadowEnabled : 1;
            ULONG KvaShadowUserGlobal : 1;
            ULONG KvaShadowPcid : 1;
            ULONG KvaShadowInvpcid : 1;
            ULONG KvaShadowRequired : 1; // REDSTONE4
            ULONG KvaShadowRequiredAvailable : 1;
            ULONG InvalidPteBit : 6;
            ULONG L1DataCacheFlushSupported : 1;
            ULONG L1TerminalFaultMitigationPresent : 1;
            ULONG Reserved : 18;
        };
    };
} SYSTEM_KERNEL_VA_SHADOW_INFORMATION, *PSYSTEM_KERNEL_VA_SHADOW_INFORMATION;

// private
typedef struct _SYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION
{
    HANDLE FileHandle;
    ULONG ImageSize;
    PVOID Image;
} SYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION, *PSYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION;

// private
typedef struct _SYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION
{
    PVOID HypervisorSharedUserVa;
} SYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION, *PSYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION;

// private
typedef struct _SYSTEM_FIRMWARE_PARTITION_INFORMATION
{
    UNICODE_STRING FirmwarePartition;
} SYSTEM_FIRMWARE_PARTITION_INFORMATION, *PSYSTEM_FIRMWARE_PARTITION_INFORMATION;

// private
typedef struct _SYSTEM_SPECULATION_CONTROL_INFORMATION
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG BpbEnabled : 1;
            ULONG BpbDisabledSystemPolicy : 1;
            ULONG BpbDisabledNoHardwareSupport : 1;
            ULONG SpecCtrlEnumerated : 1;
            ULONG SpecCmdEnumerated : 1;
            ULONG IbrsPresent : 1;
            ULONG StibpPresent : 1;
            ULONG SmepPresent : 1;
            ULONG SpeculativeStoreBypassDisableAvailable : 1; // REDSTONE4 (CVE-2018-3639)
            ULONG SpeculativeStoreBypassDisableSupported : 1;
            ULONG SpeculativeStoreBypassDisabledSystemWide : 1;
            ULONG SpeculativeStoreBypassDisabledKernel : 1;
            ULONG SpeculativeStoreBypassDisableRequired : 1;
            ULONG BpbDisabledKernelToUser : 1;
            ULONG SpecCtrlRetpolineEnabled : 1;
            ULONG SpecCtrlImportOptimizationEnabled : 1;
            ULONG EnhancedIbrs : 1; // since 19H1
            ULONG HvL1tfStatusAvailable : 1;
            ULONG HvL1tfProcessorNotAffected : 1;
            ULONG HvL1tfMigitationEnabled : 1;
            ULONG HvL1tfMigitationNotEnabled_Hardware : 1;
            ULONG HvL1tfMigitationNotEnabled_LoadOption : 1;
            ULONG HvL1tfMigitationNotEnabled_CoreScheduler : 1;
            ULONG EnhancedIbrsReported : 1;
            ULONG MdsHardwareProtected : 1; // since 19H2
            ULONG MbClearEnabled : 1;
            ULONG MbClearReported : 1;
            ULONG Reserved : 5;
        };
    };
} SYSTEM_SPECULATION_CONTROL_INFORMATION, *PSYSTEM_SPECULATION_CONTROL_INFORMATION;

// private
typedef struct _SYSTEM_DMA_GUARD_POLICY_INFORMATION
{
    BOOLEAN DmaGuardPolicyEnabled;
} SYSTEM_DMA_GUARD_POLICY_INFORMATION, *PSYSTEM_DMA_GUARD_POLICY_INFORMATION;

// private
typedef struct _SYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION
{
    UCHAR EnclaveLaunchSigner[32];
} SYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION, *PSYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION;

// private
typedef struct _SYSTEM_WORKLOAD_ALLOWED_CPU_SET_INFORMATION
{
    ULONGLONG WorkloadClass;
    ULONGLONG CpuSets[1];
} SYSTEM_WORKLOAD_ALLOWED_CPU_SET_INFORMATION, *PSYSTEM_WORKLOAD_ALLOWED_CPU_SET_INFORMATION;

// private
typedef struct _SYSTEM_SECURITY_MODEL_INFORMATION
{
    union
    {
        ULONG SecurityModelFlags;
        struct
        {
            ULONG SModeAdminlessEnabled : 1;
            ULONG AllowDeviceOwnerProtectionDowngrade : 1;
            ULONG Reserved : 30;
        };
    };
} SYSTEM_SECURITY_MODEL_INFORMATION, *PSYSTEM_SECURITY_MODEL_INFORMATION;

// private
typedef struct _SYSTEM_FEATURE_CONFIGURATION_INFORMATION
{
    ULONGLONG ChangeStamp;
    struct _RTL_FEATURE_CONFIGURATION* Configuration; // see ntrtl.h for types
} SYSTEM_FEATURE_CONFIGURATION_INFORMATION, *PSYSTEM_FEATURE_CONFIGURATION_INFORMATION;

// private
typedef struct _SYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION_ENTRY
{
    ULONGLONG ChangeStamp;
    PVOID Section;
    ULONGLONG Size;
} SYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION_ENTRY, *PSYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION_ENTRY;

// private
typedef struct _SYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION
{
    ULONGLONG OverallChangeStamp;
    SYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION_ENTRY Descriptors[3];
} SYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION, *PSYSTEM_FEATURE_CONFIGURATION_SECTIONS_INFORMATION;

// private
typedef union _SECURE_SPECULATION_CONTROL_INFORMATION
{
    ULONG KvaShadowSupported : 1;
    ULONG KvaShadowEnabled : 1;
    ULONG KvaShadowUserGlobal : 1;
    ULONG KvaShadowPcid : 1;
    ULONG MbClearEnabled : 1;
    ULONG L1TFMitigated : 1; // since 20H2
    ULONG BpbEnabled : 1;
    ULONG IbrsPresent : 1;
    ULONG EnhancedIbrs : 1;
    ULONG StibpPresent : 1;
    ULONG SsbdSupported : 1;
    ULONG SsbdRequired : 1;
    ULONG BpbKernelToUser : 1;
    ULONG BpbUserToKernel : 1;
    ULONG Reserved : 18;
} SECURE_SPECULATION_CONTROL_INFORMATION, *PSECURE_SPECULATION_CONTROL_INFORMATION;

// private
typedef struct _SYSTEM_FIRMWARE_RAMDISK_INFORMATION
{
    ULONG Version;
    ULONG BlockSize;
    ULONG_PTR BaseAddress;
    SIZE_T Size;
} SYSTEM_FIRMWARE_RAMDISK_INFORMATION, *PSYSTEM_FIRMWARE_RAMDISK_INFORMATION;

// private
typedef struct _SYSTEM_SHADOW_STACK_INFORMATION
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG CetCapable : 1;
            ULONG UserCetAllowed : 1;
            ULONG ReservedForUserCet : 6;
            ULONG KernelCetEnabled : 1;
            ULONG ReservedForKernelCet : 7;
            ULONG Reserved : 16;
        };
    };
} SYSTEM_SHADOW_STACK_INFORMATION, *PSYSTEM_SHADOW_STACK_INFORMATION;

// private
typedef union _SYSTEM_BUILD_VERSION_INFORMATION_FLAGS
{
    ULONG Value32;
    struct
    {
        ULONG IsTopLevel : 1;
        ULONG IsChecked : 1;
    };
} SYSTEM_BUILD_VERSION_INFORMATION_FLAGS, *PSYSTEM_BUILD_VERSION_INFORMATION_FLAGS;

// private
typedef struct _SYSTEM_BUILD_VERSION_INFORMATION
{
    USHORT LayerNumber;
    USHORT LayerCount;
    ULONG OsMajorVersion;
    ULONG OsMinorVersion;
    ULONG NtBuildNumber;
    ULONG NtBuildQfe;
    UCHAR LayerName[128];
    UCHAR NtBuildBranch[128];
    UCHAR NtBuildLab[128];
    UCHAR NtBuildLabEx[128];
    UCHAR NtBuildStamp[26];
    UCHAR NtBuildArch[16];
    SYSTEM_BUILD_VERSION_INFORMATION_FLAGS Flags;
} SYSTEM_BUILD_VERSION_INFORMATION, *PSYSTEM_BUILD_VERSION_INFORMATION;

// private
typedef struct _SYSTEM_POOL_LIMIT_MEM_INFO
{
    ULONGLONG MemoryLimit;
    ULONGLONG NotificationLimit;
} SYSTEM_POOL_LIMIT_MEM_INFO, *PSYSTEM_POOL_LIMIT_MEM_INFO;

// private
typedef struct _SYSTEM_POOL_LIMIT_INFO
{
    ULONG PoolTag;
    SYSTEM_POOL_LIMIT_MEM_INFO MemLimits[2];
    WNF_STATE_NAME NotificationHandle;
} SYSTEM_POOL_LIMIT_INFO, *PSYSTEM_POOL_LIMIT_INFO;

// private
typedef struct _SYSTEM_POOL_LIMIT_INFORMATION
{
    ULONG Version;
    ULONG EntryCount;
    SYSTEM_POOL_LIMIT_INFO LimitEntries[1];
} SYSTEM_POOL_LIMIT_INFORMATION, *PSYSTEM_POOL_LIMIT_INFORMATION;

// private
//typedef struct _SYSTEM_POOL_ZEROING_INFORMATION
//{
//    BOOLEAN PoolZeroingSupportPresent;
//} SYSTEM_POOL_ZEROING_INFORMATION, *PSYSTEM_POOL_ZEROING_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySystemInformation(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySystemInformation(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySystemInformationEx(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _In_reads_bytes_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySystemInformationEx(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _In_reads_bytes_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetSystemInformation(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _In_reads_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetSystemInformation(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _In_reads_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength
    );

// SysDbg APIs

// private
typedef enum _SYSDBG_COMMAND
{
    SysDbgQueryModuleInformation,
    SysDbgQueryTraceInformation,
    SysDbgSetTracepoint,
    SysDbgSetSpecialCall,
    SysDbgClearSpecialCalls,
    SysDbgQuerySpecialCalls,
    SysDbgBreakPoint,
    SysDbgQueryVersion,
    SysDbgReadVirtual,
    SysDbgWriteVirtual,
    SysDbgReadPhysical,
    SysDbgWritePhysical,
    SysDbgReadControlSpace,
    SysDbgWriteControlSpace,
    SysDbgReadIoSpace,
    SysDbgWriteIoSpace,
    SysDbgReadMsr,
    SysDbgWriteMsr,
    SysDbgReadBusData,
    SysDbgWriteBusData,
    SysDbgCheckLowMemory,
    SysDbgEnableKernelDebugger,
    SysDbgDisableKernelDebugger,
    SysDbgGetAutoKdEnable,
    SysDbgSetAutoKdEnable,
    SysDbgGetPrintBufferSize,
    SysDbgSetPrintBufferSize,
    SysDbgGetKdUmExceptionEnable,
    SysDbgSetKdUmExceptionEnable,
    SysDbgGetTriageDump,
    SysDbgGetKdBlockEnable,
    SysDbgSetKdBlockEnable,
    SysDbgRegisterForUmBreakInfo,
    SysDbgGetUmBreakPid,
    SysDbgClearUmBreakPid,
    SysDbgGetUmAttachPid,
    SysDbgClearUmAttachPid,
    SysDbgGetLiveKernelDump
} SYSDBG_COMMAND, *PSYSDBG_COMMAND;

typedef struct _SYSDBG_VIRTUAL
{
    PVOID Address;
    PVOID Buffer;
    ULONG Request;
} SYSDBG_VIRTUAL, *PSYSDBG_VIRTUAL;

typedef struct _SYSDBG_PHYSICAL
{
    PHYSICAL_ADDRESS Address;
    PVOID Buffer;
    ULONG Request;
} SYSDBG_PHYSICAL, *PSYSDBG_PHYSICAL;

typedef struct _SYSDBG_CONTROL_SPACE
{
    ULONG64 Address;
    PVOID Buffer;
    ULONG Request;
    ULONG Processor;
} SYSDBG_CONTROL_SPACE, *PSYSDBG_CONTROL_SPACE;

enum _INTERFACE_TYPE;

typedef struct _SYSDBG_IO_SPACE
{
    ULONG64 Address;
    PVOID Buffer;
    ULONG Request;
    enum _INTERFACE_TYPE InterfaceType;
    ULONG BusNumber;
    ULONG AddressSpace;
} SYSDBG_IO_SPACE, *PSYSDBG_IO_SPACE;

typedef struct _SYSDBG_MSR
{
    ULONG Msr;
    ULONG64 Data;
} SYSDBG_MSR, *PSYSDBG_MSR;

enum _BUS_DATA_TYPE;

typedef struct _SYSDBG_BUS_DATA
{
    ULONG Address;
    PVOID Buffer;
    ULONG Request;
    enum _BUS_DATA_TYPE BusDataType;
    ULONG BusNumber;
    ULONG SlotNumber;
} SYSDBG_BUS_DATA, *PSYSDBG_BUS_DATA;

// private
typedef struct _SYSDBG_TRIAGE_DUMP
{
    ULONG Flags;
    ULONG BugCheckCode;
    ULONG_PTR BugCheckParam1;
    ULONG_PTR BugCheckParam2;
    ULONG_PTR BugCheckParam3;
    ULONG_PTR BugCheckParam4;
    ULONG ProcessHandles;
    ULONG ThreadHandles;
    PHANDLE Handles;
} SYSDBG_TRIAGE_DUMP, *PSYSDBG_TRIAGE_DUMP;

// private
typedef union _SYSDBG_LIVEDUMP_CONTROL_FLAGS
{
    struct
    {
        ULONG UseDumpStorageStack : 1;
        ULONG CompressMemoryPagesData : 1;
        ULONG IncludeUserSpaceMemoryPages : 1;
        ULONG AbortIfMemoryPressure : 1; // REDSTONE4
        ULONG Reserved : 28;
    };
    ULONG AsUlong;
} SYSDBG_LIVEDUMP_CONTROL_FLAGS, *PSYSDBG_LIVEDUMP_CONTROL_FLAGS;

// private
typedef union _SYSDBG_LIVEDUMP_CONTROL_ADDPAGES
{
    struct
    {
        ULONG HypervisorPages : 1;
        ULONG Reserved : 31;
    };
    ULONG AsUlong;
} SYSDBG_LIVEDUMP_CONTROL_ADDPAGES, *PSYSDBG_LIVEDUMP_CONTROL_ADDPAGES;

#define SYSDBG_LIVEDUMP_CONTROL_VERSION 1

// private
typedef struct _SYSDBG_LIVEDUMP_CONTROL
{
    ULONG Version;
    ULONG BugCheckCode;
    ULONG_PTR BugCheckParam1;
    ULONG_PTR BugCheckParam2;
    ULONG_PTR BugCheckParam3;
    ULONG_PTR BugCheckParam4;
    HANDLE DumpFileHandle;
    HANDLE CancelEventHandle;
    SYSDBG_LIVEDUMP_CONTROL_FLAGS Flags;
    SYSDBG_LIVEDUMP_CONTROL_ADDPAGES AddPagesControl;
} SYSDBG_LIVEDUMP_CONTROL, *PSYSDBG_LIVEDUMP_CONTROL;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSystemDebugControl(
    _In_ SYSDBG_COMMAND Command,
    _Inout_updates_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSystemDebugControl(
    _In_ SYSDBG_COMMAND Command,
    _Inout_updates_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_opt_ PULONG ReturnLength
    );

// Hard errors

typedef enum _HARDERROR_RESPONSE_OPTION
{
    OptionAbortRetryIgnore,
    OptionOk,
    OptionOkCancel,
    OptionRetryCancel,
    OptionYesNo,
    OptionYesNoCancel,
    OptionShutdownSystem,
    OptionOkNoWait,
    OptionCancelTryContinue
} HARDERROR_RESPONSE_OPTION;

typedef enum _HARDERROR_RESPONSE
{
    ResponseReturnToCaller,
    ResponseNotHandled,
    ResponseAbort,
    ResponseCancel,
    ResponseIgnore,
    ResponseNo,
    ResponseOk,
    ResponseRetry,
    ResponseYes,
    ResponseTryAgain,
    ResponseContinue
} HARDERROR_RESPONSE;

#define HARDERROR_OVERRIDE_ERRORMODE 0x10000000

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRaiseHardError(
    _In_ NTSTATUS ErrorStatus,
    _In_ ULONG NumberOfParameters,
    _In_ ULONG UnicodeStringParameterMask,
    _In_reads_(NumberOfParameters) PULONG_PTR Parameters,
    _In_ ULONG ValidResponseOptions,
    _Out_ PULONG Response
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRaiseHardError(
    _In_ NTSTATUS ErrorStatus,
    _In_ ULONG NumberOfParameters,
    _In_ ULONG UnicodeStringParameterMask,
    _In_reads_(NumberOfParameters) PULONG_PTR Parameters,
    _In_ ULONG ValidResponseOptions,
    _Out_ PULONG Response
    );

// Kernel-user shared data

typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE
{
    StandardDesign,
    NEC98x86,
    EndAlternatives
} ALTERNATIVE_ARCHITECTURE_TYPE;

#define PROCESSOR_FEATURE_MAX 64

#define MAX_WOW64_SHARED_ENTRIES 16

#define NX_SUPPORT_POLICY_ALWAYSOFF 0
#define NX_SUPPORT_POLICY_ALWAYSON 1
#define NX_SUPPORT_POLICY_OPTIN 2
#define NX_SUPPORT_POLICY_OPTOUT 3

#include <pshpack4.h>
typedef struct _KUSER_SHARED_DATA
{
    ULONG TickCountLowDeprecated;
    ULONG TickCountMultiplier;

    volatile KSYSTEM_TIME InterruptTime;
    volatile KSYSTEM_TIME SystemTime;
    volatile KSYSTEM_TIME TimeZoneBias;

    USHORT ImageNumberLow;
    USHORT ImageNumberHigh;

    WCHAR NtSystemRoot[260];

    ULONG MaxStackTraceDepth;

    ULONG CryptoExponent;

    ULONG TimeZoneId;
    ULONG LargePageMinimum;
    ULONG AitSamplingValue;
    ULONG AppCompatFlag;
    ULONGLONG RNGSeedVersion;
    ULONG GlobalValidationRunlevel;
    LONG TimeZoneBiasStamp;

    ULONG NtBuildNumber;
    NT_PRODUCT_TYPE NtProductType;
    BOOLEAN ProductTypeIsValid;
    UCHAR Reserved0[1];
    USHORT NativeProcessorArchitecture;

    ULONG NtMajorVersion;
    ULONG NtMinorVersion;

    BOOLEAN ProcessorFeatures[PROCESSOR_FEATURE_MAX];

    ULONG Reserved1;
    ULONG Reserved3;

    volatile ULONG TimeSlip;

    ALTERNATIVE_ARCHITECTURE_TYPE AlternativeArchitecture;
    ULONG BootId;

    LARGE_INTEGER SystemExpirationDate;

    ULONG SuiteMask;

    BOOLEAN KdDebuggerEnabled;
    union
    {
        UCHAR MitigationPolicies;
        struct
        {
            UCHAR NXSupportPolicy : 2;
            UCHAR SEHValidationPolicy : 2;
            UCHAR CurDirDevicesSkippedForDlls : 2;
            UCHAR Reserved : 2;
        };
    };

    USHORT CyclesPerYield;

    volatile ULONG ActiveConsoleId;

    volatile ULONG DismountCount;

    ULONG ComPlusPackage;

    ULONG LastSystemRITEventTickCount;

    ULONG NumberOfPhysicalPages;

    BOOLEAN SafeBootMode;
    UCHAR VirtualizationFlags;
    UCHAR Reserved12[2];

    union
    {
        ULONG SharedDataFlags;
        struct
        {
            ULONG DbgErrorPortPresent : 1;
            ULONG DbgElevationEnabled : 1;
            ULONG DbgVirtEnabled : 1;
            ULONG DbgInstallerDetectEnabled : 1;
            ULONG DbgLkgEnabled : 1;
            ULONG DbgDynProcessorEnabled : 1;
            ULONG DbgConsoleBrokerEnabled : 1;
            ULONG DbgSecureBootEnabled : 1;
            ULONG DbgMultiSessionSku : 1;
            ULONG DbgMultiUsersInSessionSku : 1;
            ULONG DbgStateSeparationEnabled : 1;
            ULONG SpareBits : 21;
        };
    };
    ULONG DataFlagsPad[1];

    ULONGLONG TestRetInstruction;
    LONGLONG QpcFrequency;

    ULONG SystemCall;

    union
    {
        ULONG AllFlags;
        struct
        {
            ULONG Win32Process : 1;
            ULONG Sgx2Enclave : 1;
            ULONG VbsBasicEnclave : 1;
            ULONG SpareBits : 29;
        };
    } UserCetAvailableEnvironments;

    ULONGLONG SystemCallPad[2];

    union
    {
        volatile KSYSTEM_TIME TickCount;
        volatile ULONG64 TickCountQuad;
        struct
        {
            ULONG ReservedTickCountOverlay[3];
            ULONG TickCountPad[1];
        };
    };

    ULONG Cookie;
    ULONG CookiePad[1];

    LONGLONG ConsoleSessionForegroundProcessId;
    ULONGLONG TimeUpdateLock;
    ULONGLONG BaselineSystemTimeQpc;
    ULONGLONG BaselineInterruptTimeQpc;
    ULONGLONG QpcSystemTimeIncrement;
    ULONGLONG QpcInterruptTimeIncrement;
    UCHAR QpcSystemTimeIncrementShift;
    UCHAR QpcInterruptTimeIncrementShift;

    USHORT UnparkedProcessorCount;
    ULONG EnclaveFeatureMask[4];

    ULONG TelemetryCoverageRound;

    USHORT UserModeGlobalLogger[16];
    ULONG ImageFileExecutionOptions;

    ULONG LangGenerationCount;
    ULONGLONG Reserved4;
    volatile ULONG64 InterruptTimeBias;
    volatile ULONG64 QpcBias;

    ULONG ActiveProcessorCount;
    volatile UCHAR ActiveGroupCount;
    UCHAR Reserved9;
    union
    {
        USHORT QpcData;
        struct
        {
            volatile UCHAR QpcBypassEnabled : 1;
            UCHAR QpcShift : 1;
        };
    };

    LARGE_INTEGER TimeZoneBiasEffectiveStart;
    LARGE_INTEGER TimeZoneBiasEffectiveEnd;
    XSTATE_CONFIGURATION XState;
    KSYSTEM_TIME FeatureConfigurationChangeStamp;
    ULONG Spare;
} KUSER_SHARED_DATA, *PKUSER_SHARED_DATA;
#include <poppack.h>

C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TickCountMultiplier) == 0x4);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, InterruptTime) == 0x8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, SystemTime) == 0x14);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NtSystemRoot) == 0x30);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, LargePageMinimum) == 0x244);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NtProductType) == 0x264);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NtMajorVersion) == 0x26c);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NtMinorVersion) == 0x270);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, ProcessorFeatures) == 0x274);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, KdDebuggerEnabled) == 0x2d4);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, ActiveConsoleId) == 0x2d8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NumberOfPhysicalPages) == 0x2e8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, SafeBootMode) == 0x2ec);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TickCount) == 0x320);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TickCountQuad) == 0x320);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, XState) == 0x3d8);
//C_ASSERT(sizeof(KUSER_SHARED_DATA) == 0x70C); // VS2019 has some weird issue with this.

#define USER_SHARED_DATA ((KUSER_SHARED_DATA * const)0x7ffe0000)

#if (NTDDI_VERSION >= NTDDI_WS03)

FORCEINLINE ULONGLONG NtGetTickCount64()
{
    ULARGE_INTEGER tickCount;

#ifdef _WIN64

    tickCount.QuadPart = USER_SHARED_DATA->TickCountQuad;

#else

    while (TRUE)
    {
        tickCount.HighPart = (ULONG)USER_SHARED_DATA->TickCount.High1Time;
        tickCount.LowPart = USER_SHARED_DATA->TickCount.LowPart;

        if (tickCount.HighPart == (ULONG)USER_SHARED_DATA->TickCount.High2Time)
            break;

        YieldProcessor();
    }

#endif

    return (UInt32x32To64(tickCount.LowPart, USER_SHARED_DATA->TickCountMultiplier) >> 24) +
        (UInt32x32To64(tickCount.HighPart, USER_SHARED_DATA->TickCountMultiplier) << 8);
}

FORCEINLINE ULONG NtGetTickCount()
{
#ifdef _WIN64

    return (ULONG)((USER_SHARED_DATA->TickCountQuad * USER_SHARED_DATA->TickCountMultiplier) >> 24);

#else

    ULARGE_INTEGER tickCount;

    while (TRUE)
    {
        tickCount.HighPart = (ULONG)USER_SHARED_DATA->TickCount.High1Time;
        tickCount.LowPart = USER_SHARED_DATA->TickCount.LowPart;

        if (tickCount.HighPart == (ULONG)USER_SHARED_DATA->TickCount.High2Time)
            break;

        YieldProcessor();
    }

    return (ULONG)((UInt32x32To64(tickCount.LowPart, USER_SHARED_DATA->TickCountMultiplier) >> 24) +
        UInt32x32To64((tickCount.HighPart << 8) & 0xffffffff, USER_SHARED_DATA->TickCountMultiplier));

#endif
}

#else

FORCEINLINE ULONGLONG NtGetTickCount64()
{
    return GetTickCount(); // pre PHNT_WS03 (dmex)
}

FORCEINLINE ULONG NtGetTickCount()
{
    return GetTickCount();
}

#endif

// Locale

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDefaultLocale(
    _In_ BOOLEAN UserProfile,
    _Out_ PLCID DefaultLocaleId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryDefaultLocale(
    _In_ BOOLEAN UserProfile,
    _Out_ PLCID DefaultLocaleId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetDefaultLocale(
    _In_ BOOLEAN UserProfile,
    _In_ LCID DefaultLocaleId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetDefaultLocale(
    _In_ BOOLEAN UserProfile,
    _In_ LCID DefaultLocaleId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInstallUILanguage(
    _Out_ LANGID *InstallUILanguageId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInstallUILanguage(
    _Out_ LANGID *InstallUILanguageId
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushInstallUILanguage(
    _In_ LANGID InstallUILanguage,
    _In_ ULONG SetComittedFlag
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFlushInstallUILanguage(
    _In_ LANGID InstallUILanguage,
    _In_ ULONG SetComittedFlag
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDefaultUILanguage(
    _Out_ LANGID *DefaultUILanguageId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryDefaultUILanguage(
    _Out_ LANGID *DefaultUILanguageId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetDefaultUILanguage(
    _In_ LANGID DefaultUILanguageId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetDefaultUILanguage(
    _In_ LANGID DefaultUILanguageId
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI
NTSTATUS
NTAPI
NtIsUILanguageComitted(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwIsUILanguageComitted(
    VOID
    );
#endif

// NLS

// begin_private

#if (NTDDI_VERSION >= NTDDI_VISTA)

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtInitializeNlsFiles(
    _Out_ PVOID *BaseAddress,
    _Out_ PLCID DefaultLocaleId,
    _Out_ PLARGE_INTEGER DefaultCasingTableSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwInitializeNlsFiles(
    _Out_ PVOID *BaseAddress,
    _Out_ PLCID DefaultLocaleId,
    _Out_ PLARGE_INTEGER DefaultCasingTableSize
    );
#else
NTSYSCALLAPI
NTSTATUS
NTAPI
NtInitializeNlsFiles(
    _Out_ PVOID *BaseAddress,
    _Out_ PLCID DefaultLocaleId,
    _Out_ PLARGE_INTEGER DefaultCasingTableSize,
    _Out_opt_ PULONG CurrentNLSVersion
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwInitializeNlsFiles(
    _Out_ PVOID *BaseAddress,
    _Out_ PLCID DefaultLocaleId,
    _Out_ PLARGE_INTEGER DefaultCasingTableSize,
    _Out_opt_ PULONG CurrentNLSVersion
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetNlsSectionPtr(
    _In_ ULONG SectionType,
    _In_ ULONG SectionData,
    _In_ PVOID ContextData,
    _Out_ PVOID *SectionPointer,
    _Out_ PULONG SectionSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetNlsSectionPtr(
    _In_ ULONG SectionType,
    _In_ ULONG SectionData,
    _In_ PVOID ContextData,
    _Out_ PVOID *SectionPointer,
    _Out_ PULONG SectionSize
    );

#if (NTDDI_VERSION < NTDDI_WIN7)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAcquireCMFViewOwnership(
    _Out_ PULONGLONG TimeStamp,
    _Out_ PBOOLEAN tokenTaken,
    _In_ BOOLEAN replaceExisting
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAcquireCMFViewOwnership(
    _Out_ PULONGLONG TimeStamp,
    _Out_ PBOOLEAN tokenTaken,
    _In_ BOOLEAN replaceExisting
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReleaseCMFViewOwnership(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReleaseCMFViewOwnership(
    VOID
    );

#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapCMFModule(
    _In_ ULONG What,
    _In_ ULONG Index,
    _Out_opt_ PULONG CacheIndexOut,
    _Out_opt_ PULONG CacheFlagsOut,
    _Out_opt_ PULONG ViewSizeOut,
    _Out_opt_ PVOID *BaseAddress
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwMapCMFModule(
    _In_ ULONG What,
    _In_ ULONG Index,
    _Out_opt_ PULONG CacheIndexOut,
    _Out_opt_ PULONG CacheFlagsOut,
    _Out_opt_ PULONG ViewSizeOut,
    _Out_opt_ PVOID *BaseAddress
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetMUIRegistryInfo(
    _In_ ULONG Flags,
    _Inout_ PULONG DataSize,
    _Out_ PVOID Data
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetMUIRegistryInfo(
    _In_ ULONG Flags,
    _Inout_ PULONG DataSize,
    _Out_ PVOID Data
    );

#endif

// end_private

// Global atoms

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAddAtom(
    _In_reads_bytes_opt_(Length) PWSTR AtomName,
    _In_ ULONG Length,
    _Out_opt_ PRTL_ATOM Atom
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAddAtom(
    _In_reads_bytes_opt_(Length) PWSTR AtomName,
    _In_ ULONG Length,
    _Out_opt_ PRTL_ATOM Atom
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)

#define ATOM_FLAG_GLOBAL 0x2

// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
NtAddAtomEx(
    _In_reads_bytes_opt_(Length) PWSTR AtomName,
    _In_ ULONG Length,
    _Out_opt_ PRTL_ATOM Atom,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAddAtomEx(
    _In_reads_bytes_opt_(Length) PWSTR AtomName,
    _In_ ULONG Length,
    _Out_opt_ PRTL_ATOM Atom,
    _In_ ULONG Flags
    );

#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFindAtom(
    _In_reads_bytes_opt_(Length) PWSTR AtomName,
    _In_ ULONG Length,
    _Out_opt_ PRTL_ATOM Atom
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFindAtom(
    _In_reads_bytes_opt_(Length) PWSTR AtomName,
    _In_ ULONG Length,
    _Out_opt_ PRTL_ATOM Atom
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteAtom(
    _In_ RTL_ATOM Atom
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteAtom(
    _In_ RTL_ATOM Atom
    );

typedef enum _ATOM_INFORMATION_CLASS
{
    AtomBasicInformation,
    AtomTableInformation
} ATOM_INFORMATION_CLASS;

typedef struct _ATOM_BASIC_INFORMATION
{
    USHORT UsageCount;
    USHORT Flags;
    USHORT NameLength;
    WCHAR Name[1];
} ATOM_BASIC_INFORMATION, *PATOM_BASIC_INFORMATION;

typedef struct _ATOM_TABLE_INFORMATION
{
    ULONG NumberOfAtoms;
    RTL_ATOM Atoms[1];
} ATOM_TABLE_INFORMATION, *PATOM_TABLE_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationAtom(
    _In_ RTL_ATOM Atom,
    _In_ ATOM_INFORMATION_CLASS AtomInformationClass,
    _Out_writes_bytes_(AtomInformationLength) PVOID AtomInformation,
    _In_ ULONG AtomInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationAtom(
    _In_ RTL_ATOM Atom,
    _In_ ATOM_INFORMATION_CLASS AtomInformationClass,
    _Out_writes_bytes_(AtomInformationLength) PVOID AtomInformation,
    _In_ ULONG AtomInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

// Global flags

#define FLG_STOP_ON_EXCEPTION 0x00000001 // uk
#define FLG_SHOW_LDR_SNAPS 0x00000002 // uk
#define FLG_DEBUG_INITIAL_COMMAND 0x00000004 // k
#define FLG_STOP_ON_HUNG_GUI 0x00000008 // k

#define FLG_HEAP_ENABLE_TAIL_CHECK 0x00000010 // u
#define FLG_HEAP_ENABLE_FREE_CHECK 0x00000020 // u
#define FLG_HEAP_VALIDATE_PARAMETERS 0x00000040 // u
#define FLG_HEAP_VALIDATE_ALL 0x00000080 // u

#define FLG_APPLICATION_VERIFIER 0x00000100 // u
#define FLG_POOL_ENABLE_TAGGING 0x00000400 // k
#define FLG_HEAP_ENABLE_TAGGING 0x00000800 // u

#define FLG_USER_STACK_TRACE_DB 0x00001000 // u,32
#define FLG_KERNEL_STACK_TRACE_DB 0x00002000 // k,32
#define FLG_MAINTAIN_OBJECT_TYPELIST 0x00004000 // k
#define FLG_HEAP_ENABLE_TAG_BY_DLL 0x00008000 // u

#define FLG_DISABLE_STACK_EXTENSION 0x00010000 // u
#define FLG_ENABLE_CSRDEBUG 0x00020000 // k
#define FLG_ENABLE_KDEBUG_SYMBOL_LOAD 0x00040000 // k
#define FLG_DISABLE_PAGE_KERNEL_STACKS 0x00080000 // k

#define FLG_ENABLE_SYSTEM_CRIT_BREAKS 0x00100000 // u
#define FLG_HEAP_DISABLE_COALESCING 0x00200000 // u
#define FLG_ENABLE_CLOSE_EXCEPTIONS 0x00400000 // k
#define FLG_ENABLE_EXCEPTION_LOGGING 0x00800000 // k

#define FLG_ENABLE_HANDLE_TYPE_TAGGING 0x01000000 // k
#define FLG_HEAP_PAGE_ALLOCS 0x02000000 // u
#define FLG_DEBUG_INITIAL_COMMAND_EX 0x04000000 // k
#define FLG_DISABLE_DBGPRINT 0x08000000 // k

#define FLG_CRITSEC_EVENT_CREATION 0x10000000 // u
#define FLG_LDR_TOP_DOWN 0x20000000 // u,64
#define FLG_ENABLE_HANDLE_EXCEPTIONS 0x40000000 // k
#define FLG_DISABLE_PROTDLLS 0x80000000 // u

#define FLG_VALID_BITS 0xfffffdff

#define FLG_USERMODE_VALID_BITS (FLG_STOP_ON_EXCEPTION | \
    FLG_SHOW_LDR_SNAPS | \
    FLG_HEAP_ENABLE_TAIL_CHECK | \
    FLG_HEAP_ENABLE_FREE_CHECK | \
    FLG_HEAP_VALIDATE_PARAMETERS | \
    FLG_HEAP_VALIDATE_ALL | \
    FLG_APPLICATION_VERIFIER | \
    FLG_HEAP_ENABLE_TAGGING | \
    FLG_USER_STACK_TRACE_DB | \
    FLG_HEAP_ENABLE_TAG_BY_DLL | \
    FLG_DISABLE_STACK_EXTENSION | \
    FLG_ENABLE_SYSTEM_CRIT_BREAKS | \
    FLG_HEAP_DISABLE_COALESCING | \
    FLG_DISABLE_PROTDLLS | \
    FLG_HEAP_PAGE_ALLOCS | \
    FLG_CRITSEC_EVENT_CREATION | \
    FLG_LDR_TOP_DOWN)

#define FLG_BOOTONLY_VALID_BITS (FLG_KERNEL_STACK_TRACE_DB | \
    FLG_MAINTAIN_OBJECT_TYPELIST | \
    FLG_ENABLE_CSRDEBUG | \
    FLG_DEBUG_INITIAL_COMMAND | \
    FLG_DEBUG_INITIAL_COMMAND_EX | \
    FLG_DISABLE_PAGE_KERNEL_STACKS)

#define FLG_KERNELMODE_VALID_BITS (FLG_STOP_ON_EXCEPTION | \
    FLG_SHOW_LDR_SNAPS | \
    FLG_STOP_ON_HUNG_GUI | \
    FLG_POOL_ENABLE_TAGGING | \
    FLG_ENABLE_KDEBUG_SYMBOL_LOAD | \
    FLG_ENABLE_CLOSE_EXCEPTIONS | \
    FLG_ENABLE_EXCEPTION_LOGGING | \
    FLG_ENABLE_HANDLE_TYPE_TAGGING | \
    FLG_DISABLE_DBGPRINT | \
    FLG_ENABLE_HANDLE_EXCEPTIONS)

// Licensing

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryLicenseValue(
    _In_ PUNICODE_STRING ValueName,
    _Out_opt_ PULONG Type,
    _Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
    _In_ ULONG DataSize,
    _Out_ PULONG ResultDataSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryLicenseValue(
    _In_ PUNICODE_STRING ValueName,
    _Out_opt_ PULONG Type,
    _Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
    _In_ ULONG DataSize,
    _Out_ PULONG ResultDataSize
    );

// Misc.

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetDefaultHardErrorPort(
    _In_ HANDLE DefaultHardErrorPort
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetDefaultHardErrorPort(
    _In_ HANDLE DefaultHardErrorPort
    );

typedef enum _SHUTDOWN_ACTION
{
    ShutdownNoReboot,
    ShutdownReboot,
    ShutdownPowerOff
} SHUTDOWN_ACTION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtShutdownSystem(
    _In_ SHUTDOWN_ACTION Action
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwShutdownSystem(
    _In_ SHUTDOWN_ACTION Action
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDisplayString(
    _In_ PUNICODE_STRING String
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDisplayString(
    _In_ PUNICODE_STRING String
    );

// Boot graphics

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
NtDrawText(
    _In_ PUNICODE_STRING Text
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDrawText(
    _In_ PUNICODE_STRING Text
    );
#endif
 


// #include <ntgdi.h>
#define GDI_MAX_HANDLE_COUNT 0xFFFF // 0x4000

#define GDI_HANDLE_INDEX_SHIFT 0
#define GDI_HANDLE_INDEX_BITS 16
#define GDI_HANDLE_INDEX_MASK 0xffff

#define GDI_HANDLE_TYPE_SHIFT 16
#define GDI_HANDLE_TYPE_BITS 5
#define GDI_HANDLE_TYPE_MASK 0x1f

#define GDI_HANDLE_ALTTYPE_SHIFT 21
#define GDI_HANDLE_ALTTYPE_BITS 2
#define GDI_HANDLE_ALTTYPE_MASK 0x3

#define GDI_HANDLE_STOCK_SHIFT 23
#define GDI_HANDLE_STOCK_BITS 1
#define GDI_HANDLE_STOCK_MASK 0x1

#define GDI_HANDLE_UNIQUE_SHIFT 24
#define GDI_HANDLE_UNIQUE_BITS 8
#define GDI_HANDLE_UNIQUE_MASK 0xff

#define GDI_HANDLE_INDEX(Handle) ((ULONG)(Handle) & GDI_HANDLE_INDEX_MASK)
#define GDI_HANDLE_TYPE(Handle) (((ULONG)(Handle) >> GDI_HANDLE_TYPE_SHIFT) & GDI_HANDLE_TYPE_MASK)
#define GDI_HANDLE_ALTTYPE(Handle) (((ULONG)(Handle) >> GDI_HANDLE_ALTTYPE_SHIFT) & GDI_HANDLE_ALTTYPE_MASK)
#define GDI_HANDLE_STOCK(Handle) (((ULONG)(Handle) >> GDI_HANDLE_STOCK_SHIFT)) & GDI_HANDLE_STOCK_MASK)

#define GDI_MAKE_HANDLE(Index, Unique) ((ULONG)(((ULONG)(Unique) << GDI_HANDLE_INDEX_BITS) | (ULONG)(Index)))

// GDI server-side types

#define GDI_DEF_TYPE 0 // invalid handle
#define GDI_DC_TYPE 1
#define GDI_DD_DIRECTDRAW_TYPE 2
#define GDI_DD_SURFACE_TYPE 3
#define GDI_RGN_TYPE 4
#define GDI_SURF_TYPE 5
#define GDI_CLIENTOBJ_TYPE 6
#define GDI_PATH_TYPE 7
#define GDI_PAL_TYPE 8
#define GDI_ICMLCS_TYPE 9
#define GDI_LFONT_TYPE 10
#define GDI_RFONT_TYPE 11
#define GDI_PFE_TYPE 12
#define GDI_PFT_TYPE 13
#define GDI_ICMCXF_TYPE 14
#define GDI_ICMDLL_TYPE 15
#define GDI_BRUSH_TYPE 16
#define GDI_PFF_TYPE 17 // unused
#define GDI_CACHE_TYPE 18 // unused
#define GDI_SPACE_TYPE 19
#define GDI_DBRUSH_TYPE 20 // unused
#define GDI_META_TYPE 21
#define GDI_EFSTATE_TYPE 22
#define GDI_BMFD_TYPE 23 // unused
#define GDI_VTFD_TYPE 24 // unused
#define GDI_TTFD_TYPE 25 // unused
#define GDI_RC_TYPE 26 // unused
#define GDI_TEMP_TYPE 27 // unused
#define GDI_DRVOBJ_TYPE 28
#define GDI_DCIOBJ_TYPE 29 // unused
#define GDI_SPOOL_TYPE 30

// GDI client-side types

#define GDI_CLIENT_TYPE_FROM_HANDLE(Handle) ((ULONG)(Handle) & ((GDI_HANDLE_ALTTYPE_MASK << GDI_HANDLE_ALTTYPE_SHIFT) | \
    (GDI_HANDLE_TYPE_MASK << GDI_HANDLE_TYPE_SHIFT)))
#define GDI_CLIENT_TYPE_FROM_UNIQUE(Unique) GDI_CLIENT_TYPE_FROM_HANDLE((ULONG)(Unique) << 16)

#define GDI_ALTTYPE_1 (1 << GDI_HANDLE_ALTTYPE_SHIFT)
#define GDI_ALTTYPE_2 (2 << GDI_HANDLE_ALTTYPE_SHIFT)
#define GDI_ALTTYPE_3 (3 << GDI_HANDLE_ALTTYPE_SHIFT)

#define GDI_CLIENT_BITMAP_TYPE (GDI_SURF_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_BRUSH_TYPE (GDI_BRUSH_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_CLIENTOBJ_TYPE (GDI_CLIENTOBJ_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_DC_TYPE (GDI_DC_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_FONT_TYPE (GDI_LFONT_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_PALETTE_TYPE (GDI_PAL_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_REGION_TYPE (GDI_RGN_TYPE << GDI_HANDLE_TYPE_SHIFT)

#define GDI_CLIENT_ALTDC_TYPE (GDI_CLIENT_DC_TYPE | GDI_ALTTYPE_1)
#define GDI_CLIENT_DIBSECTION_TYPE (GDI_CLIENT_BITMAP_TYPE | GDI_ALTTYPE_1)
#define GDI_CLIENT_EXTPEN_TYPE (GDI_CLIENT_BRUSH_TYPE | GDI_ALTTYPE_2)
#define GDI_CLIENT_METADC16_TYPE (GDI_CLIENT_CLIENTOBJ_TYPE | GDI_ALTTYPE_3)
#define GDI_CLIENT_METAFILE_TYPE (GDI_CLIENT_CLIENTOBJ_TYPE | GDI_ALTTYPE_2)
#define GDI_CLIENT_METAFILE16_TYPE (GDI_CLIENT_CLIENTOBJ_TYPE | GDI_ALTTYPE_1)
#define GDI_CLIENT_PEN_TYPE (GDI_CLIENT_BRUSH_TYPE | GDI_ALTTYPE_1)

typedef struct _GDI_HANDLE_ENTRY
{
    union
    {
        PVOID Object;
        PVOID NextFree;
    };
    union
    {
        struct
        {
            USHORT ProcessId;
            USHORT Lock : 1;
            USHORT Count : 15;
        };
        ULONG Value;
    } Owner;
    USHORT Unique;
    UCHAR Type;
    UCHAR Flags;
    PVOID UserPointer;
} GDI_HANDLE_ENTRY, *PGDI_HANDLE_ENTRY;

typedef struct _GDI_SHARED_MEMORY
{
    GDI_HANDLE_ENTRY Handles[GDI_MAX_HANDLE_COUNT];
} GDI_SHARED_MEMORY, *PGDI_SHARED_MEMORY;



// #include <ntmmapi.h>
// Protection constants

#define PAGE_NOACCESS 0x01
#define PAGE_READONLY 0x02
#define PAGE_READWRITE 0x04
#define PAGE_WRITECOPY 0x08
#define PAGE_EXECUTE 0x10
#define PAGE_EXECUTE_READ 0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD 0x100
#define PAGE_NOCACHE 0x200
#define PAGE_WRITECOMBINE 0x400

#define PAGE_REVERT_TO_FILE_MAP     0x80000000
#define PAGE_ENCLAVE_THREAD_CONTROL 0x80000000
#define PAGE_TARGETS_NO_UPDATE      0x40000000
#define PAGE_TARGETS_INVALID        0x40000000
#define PAGE_ENCLAVE_UNVALIDATED    0x20000000

// Region and section constants

#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000
#define MEM_DECOMMIT 0x00004000
#define MEM_RELEASE 0x00008000
#define MEM_FREE 0x00010000
#define MEM_PRIVATE 0x00020000
#define MEM_MAPPED 0x00040000
#define MEM_RESET 0x00080000
#define MEM_TOP_DOWN 0x00100000
#define MEM_WRITE_WATCH 0x00200000
#define MEM_PHYSICAL 0x00400000
#define MEM_ROTATE 0x00800000
#define MEM_DIFFERENT_IMAGE_BASE_OK 0x00800000
#define MEM_RESET_UNDO 0x01000000
#define MEM_LARGE_PAGES 0x20000000
#define MEM_DOS_LIM 0x40000000
#define MEM_4MB_PAGES 0x80000000

#define SEC_BASED 0x00200000
#define SEC_NO_CHANGE 0x00400000
#define SEC_FILE 0x00800000
#define SEC_IMAGE 0x01000000
#define SEC_PROTECTED_IMAGE 0x02000000
#define SEC_RESERVE 0x04000000
#define SEC_COMMIT 0x08000000
#define SEC_NOCACHE 0x10000000
#define SEC_GLOBAL 0x20000000
#define SEC_WRITECOMBINE 0x40000000
#define SEC_LARGE_PAGES 0x80000000
#define SEC_IMAGE_NO_EXECUTE (SEC_IMAGE | SEC_NOCACHE)

// private
typedef enum _MEMORY_INFORMATION_CLASS
{
    MemoryBasicInformation, // MEMORY_BASIC_INFORMATION
    MemoryWorkingSetInformation, // MEMORY_WORKING_SET_INFORMATION
    MemoryMappedFilenameInformation, // UNICODE_STRING
    MemoryRegionInformation, // MEMORY_REGION_INFORMATION
    MemoryWorkingSetExInformation, // MEMORY_WORKING_SET_EX_INFORMATION
    MemorySharedCommitInformation, // MEMORY_SHARED_COMMIT_INFORMATION
    MemoryImageInformation, // MEMORY_IMAGE_INFORMATION
    MemoryRegionInformationEx, // MEMORY_REGION_INFORMATION
    MemoryPrivilegedBasicInformation,
    MemoryEnclaveImageInformation, // MEMORY_ENCLAVE_IMAGE_INFORMATION // since REDSTONE3
    MemoryBasicInformationCapped, // 10
    MemoryPhysicalContiguityInformation, // MEMORY_PHYSICAL_CONTIGUITY_INFORMATION // since 20H1
    MaxMemoryInfoClass
} MEMORY_INFORMATION_CLASS;

typedef struct _MEMORY_WORKING_SET_BLOCK
{
    ULONG_PTR Protection : 5;
    ULONG_PTR ShareCount : 3;
    ULONG_PTR Shared : 1;
    ULONG_PTR Node : 3;
#ifdef _WIN64
    ULONG_PTR VirtualPage : 52;
#else
    ULONG VirtualPage : 20;
#endif
} MEMORY_WORKING_SET_BLOCK, *PMEMORY_WORKING_SET_BLOCK;

typedef struct _MEMORY_WORKING_SET_INFORMATION
{
    ULONG_PTR NumberOfEntries;
    MEMORY_WORKING_SET_BLOCK WorkingSetInfo[1];
} MEMORY_WORKING_SET_INFORMATION, *PMEMORY_WORKING_SET_INFORMATION;

// private
typedef struct _MEMORY_REGION_INFORMATION
{
    PVOID AllocationBase;
    ULONG AllocationProtect;
    union
    {
        ULONG RegionType;
        struct
        {
            ULONG Private : 1;
            ULONG MappedDataFile : 1;
            ULONG MappedImage : 1;
            ULONG MappedPageFile : 1;
            ULONG MappedPhysical : 1;
            ULONG DirectMapped : 1;
            ULONG SoftwareEnclave : 1; // REDSTONE3
            ULONG PageSize64K : 1;
            ULONG PlaceholderReservation : 1; // REDSTONE4
            ULONG Reserved : 23;
        };
    };
    SIZE_T RegionSize;
    SIZE_T CommitSize;
    ULONG_PTR PartitionId; // 19H1
    ULONG_PTR NodePreference; // 20H1
} MEMORY_REGION_INFORMATION, *PMEMORY_REGION_INFORMATION;

// private 
typedef enum _MEMORY_WORKING_SET_EX_LOCATION
{
    MemoryLocationInvalid,
    MemoryLocationResident,
    MemoryLocationPagefile,
    MemoryLocationReserved
} MEMORY_WORKING_SET_EX_LOCATION;

// private
typedef struct _MEMORY_WORKING_SET_EX_BLOCK
{
    union
    {
        struct
        {
            ULONG_PTR Valid : 1;
            ULONG_PTR ShareCount : 3;
            ULONG_PTR Win32Protection : 11;
            ULONG_PTR Shared : 1;
            ULONG_PTR Node : 6;
            ULONG_PTR Locked : 1;
            ULONG_PTR LargePage : 1;
            ULONG_PTR Priority : 3;
            ULONG_PTR Reserved : 3;
            ULONG_PTR SharedOriginal : 1;
            ULONG_PTR Bad : 1;
            ULONG_PTR Win32GraphicsProtection : 4; // 19H1
#ifdef _WIN64
            ULONG_PTR ReservedUlong : 28;
#endif
        };
        struct
        {
            ULONG_PTR Valid : 1;
            ULONG_PTR Reserved0 : 14;
            ULONG_PTR Shared : 1;
            ULONG_PTR Reserved1 : 5;
            ULONG_PTR PageTable : 1;
            ULONG_PTR Location : 2;
            ULONG_PTR Priority : 3;
            ULONG_PTR ModifiedList : 1;
            ULONG_PTR Reserved2 : 2;
            ULONG_PTR SharedOriginal : 1;
            ULONG_PTR Bad : 1;
#ifdef _WIN64
            ULONG_PTR ReservedUlong : 32;
#endif
        } Invalid;
    };
} MEMORY_WORKING_SET_EX_BLOCK, *PMEMORY_WORKING_SET_EX_BLOCK;

// private
typedef struct _MEMORY_WORKING_SET_EX_INFORMATION
{
    PVOID VirtualAddress;
    union
    {
        MEMORY_WORKING_SET_EX_BLOCK VirtualAttributes;
        ULONG_PTR Long;
    } u1;
} MEMORY_WORKING_SET_EX_INFORMATION, *PMEMORY_WORKING_SET_EX_INFORMATION;

// private
typedef struct _MEMORY_SHARED_COMMIT_INFORMATION
{
    SIZE_T CommitSize;
} MEMORY_SHARED_COMMIT_INFORMATION, *PMEMORY_SHARED_COMMIT_INFORMATION;

// private
typedef struct _MEMORY_IMAGE_INFORMATION
{
    PVOID ImageBase;
    SIZE_T SizeOfImage;
    union
    {
        ULONG ImageFlags;
        struct
        {
            ULONG ImagePartialMap : 1;
            ULONG ImageNotExecutable : 1;
            ULONG ImageSigningLevel : 4; // REDSTONE3
            ULONG Reserved : 26;
        };
    };
} MEMORY_IMAGE_INFORMATION, *PMEMORY_IMAGE_INFORMATION;

// private
typedef struct _MEMORY_ENCLAVE_IMAGE_INFORMATION
{
    MEMORY_IMAGE_INFORMATION ImageInfo;
    UCHAR UniqueID[32];
    UCHAR AuthorID[32];
} MEMORY_ENCLAVE_IMAGE_INFORMATION, *PMEMORY_ENCLAVE_IMAGE_INFORMATION;

// private
typedef enum _MEMORY_PHYSICAL_CONTIGUITY_UNIT_STATE
{
    MemoryNotContiguous,
    MemoryAlignedAndContiguous,
    MemoryNotResident,
    MemoryNotEligibleToMakeContiguous,
    MemoryContiguityStateMax,
} MEMORY_PHYSICAL_CONTIGUITY_UNIT_STATE;

// private
typedef struct _MEMORY_PHYSICAL_CONTIGUITY_UNIT_INFORMATION
{
    union
    {
        ULONG AllInformation;
        struct
        {
            ULONG State : 2;
            ULONG Reserved : 30;
        };
    };
} MEMORY_PHYSICAL_CONTIGUITY_UNIT_INFORMATION, *PMEMORY_PHYSICAL_CONTIGUITY_UNIT_INFORMATION;

// private
typedef struct _MEMORY_PHYSICAL_CONTIGUITY_INFORMATION
{
    PVOID VirtualAddress;
    ULONG_PTR Size;
    ULONG_PTR ContiguityUnitSize;
    ULONG Flags;
    PMEMORY_PHYSICAL_CONTIGUITY_UNIT_INFORMATION ContiguityUnitInformation;
} MEMORY_PHYSICAL_CONTIGUITY_INFORMATION, *PMEMORY_PHYSICAL_CONTIGUITY_INFORMATION;

#define MMPFNLIST_ZERO 0
#define MMPFNLIST_FREE 1
#define MMPFNLIST_STANDBY 2
#define MMPFNLIST_MODIFIED 3
#define MMPFNLIST_MODIFIEDNOWRITE 4
#define MMPFNLIST_BAD 5
#define MMPFNLIST_ACTIVE 6
#define MMPFNLIST_TRANSITION 7

#define MMPFNUSE_PROCESSPRIVATE 0
#define MMPFNUSE_FILE 1
#define MMPFNUSE_PAGEFILEMAPPED 2
#define MMPFNUSE_PAGETABLE 3
#define MMPFNUSE_PAGEDPOOL 4
#define MMPFNUSE_NONPAGEDPOOL 5
#define MMPFNUSE_SYSTEMPTE 6
#define MMPFNUSE_SESSIONPRIVATE 7
#define MMPFNUSE_METAFILE 8
#define MMPFNUSE_AWEPAGE 9
#define MMPFNUSE_DRIVERLOCKPAGE 10
#define MMPFNUSE_KERNELSTACK 11

// private
typedef struct _MEMORY_FRAME_INFORMATION
{
    ULONGLONG UseDescription : 4; // MMPFNUSE_*
    ULONGLONG ListDescription : 3; // MMPFNLIST_*
    ULONGLONG Cold : 1; // 19H1
    ULONGLONG Pinned : 1; // 1 - pinned, 0 - not pinned
    ULONGLONG DontUse : 48; // *_INFORMATION overlay
    ULONGLONG Priority : 3; // rev
    ULONGLONG Reserved : 4; // reserved for future expansion
} MEMORY_FRAME_INFORMATION;

// private
typedef struct _FILEOFFSET_INFORMATION
{
    ULONGLONG DontUse : 9; // MEMORY_FRAME_INFORMATION overlay
    ULONGLONG Offset : 48; // mapped files
    ULONGLONG Reserved : 7; // reserved for future expansion
} FILEOFFSET_INFORMATION;

// private
typedef struct _PAGEDIR_INFORMATION
{
    ULONGLONG DontUse : 9; // MEMORY_FRAME_INFORMATION overlay
    ULONGLONG PageDirectoryBase : 48; // private pages
    ULONGLONG Reserved : 7; // reserved for future expansion
} PAGEDIR_INFORMATION;

// private
typedef struct _UNIQUE_PROCESS_INFORMATION
{
    ULONGLONG DontUse : 9; // MEMORY_FRAME_INFORMATION overlay
    ULONGLONG UniqueProcessKey : 48; // ProcessId
    ULONGLONG Reserved  : 7; // reserved for future expansion
} UNIQUE_PROCESS_INFORMATION, *PUNIQUE_PROCESS_INFORMATION;

// private
typedef struct _MMPFN_IDENTITY
{
    union
    {
        MEMORY_FRAME_INFORMATION e1; // all
        FILEOFFSET_INFORMATION e2; // mapped files
        PAGEDIR_INFORMATION e3; // private pages
        UNIQUE_PROCESS_INFORMATION e4; // owning process
    } u1;
    ULONG_PTR PageFrameIndex; // all
    union
    {
        struct
        {
            ULONG_PTR Image : 1;
            ULONG_PTR Mismatch : 1;
        } e1;
        struct
        {
            ULONG_PTR CombinedPage;
        } e2;
        ULONG_PTR FileObject; // mapped files
        ULONG_PTR UniqueFileObjectKey;
        ULONG_PTR ProtoPteAddress;
        ULONG_PTR VirtualAddress;  // everything else
    } u2;
} MMPFN_IDENTITY, *PMMPFN_IDENTITY;

typedef struct _MMPFN_MEMSNAP_INFORMATION
{
    ULONG_PTR InitialPageFrameIndex;
    ULONG_PTR Count;
} MMPFN_MEMSNAP_INFORMATION, *PMMPFN_MEMSNAP_INFORMATION;

typedef enum _SECTION_INFORMATION_CLASS
{
    SectionBasicInformation, // q; SECTION_BASIC_INFORMATION
    SectionImageInformation, // q; SECTION_IMAGE_INFORMATION
    SectionRelocationInformation, // name:wow64:whNtQuerySection_SectionRelocationInformation
    SectionOriginalBaseInformation, // PVOID BaseAddress
    SectionInternalImageInformation, // SECTION_INTERNAL_IMAGE_INFORMATION // since REDSTONE2
    MaxSectionInfoClass
} SECTION_INFORMATION_CLASS;

typedef struct _SECTION_BASIC_INFORMATION
{
    PVOID BaseAddress;
    ULONG AllocationAttributes;
    LARGE_INTEGER MaximumSize;
} SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

// symbols
typedef struct _SECTION_IMAGE_INFORMATION
{
    PVOID TransferAddress;
    ULONG ZeroBits;
    SIZE_T MaximumStackSize;
    SIZE_T CommittedStackSize;
    ULONG SubSystemType;
    union
    {
        struct
        {
            USHORT SubSystemMinorVersion;
            USHORT SubSystemMajorVersion;
        };
        ULONG SubSystemVersion;
    };
    union
    {
        struct
        {
            USHORT MajorOperatingSystemVersion;
            USHORT MinorOperatingSystemVersion;
        };
        ULONG OperatingSystemVersion;
    };
    USHORT ImageCharacteristics;
    USHORT DllCharacteristics;
    USHORT Machine;
    BOOLEAN ImageContainsCode;
    union
    {
        UCHAR ImageFlags;
        struct
        {
            UCHAR ComPlusNativeReady : 1;
            UCHAR ComPlusILOnly : 1;
            UCHAR ImageDynamicallyRelocated : 1;
            UCHAR ImageMappedFlat : 1;
            UCHAR BaseBelow4gb : 1;
            UCHAR ComPlusPrefer32bit : 1;
            UCHAR Reserved : 2;
        };
    };
    ULONG LoaderFlags;
    ULONG ImageFileSize;
    ULONG CheckSum;
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

// symbols
typedef struct _SECTION_INTERNAL_IMAGE_INFORMATION
{
    SECTION_IMAGE_INFORMATION SectionInformation;
    union
    {
        ULONG ExtendedFlags;
        struct
        {
            ULONG ImageExportSuppressionEnabled : 1;
            ULONG ImageCetShadowStacksReady : 1; // 20H1
            ULONG ImageXfgEnabled : 1; // 20H2
            ULONG ImageCetShadowStacksStrictMode : 1;
            ULONG ImageCetSetContextIpValidationRelaxedMode : 1;
            ULONG ImageCetDynamicApisAllowInProc : 1;
            ULONG ImageCetDowngradeReserved1 : 1;
            ULONG ImageCetDowngradeReserved2 : 1;
            ULONG Reserved : 24;
        };
    };
} SECTION_INTERNAL_IMAGE_INFORMATION, *PSECTION_INTERNAL_IMAGE_INFORMATION;

typedef enum _SECTION_INHERIT
{
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

#define MEM_EXECUTE_OPTION_DISABLE 0x1
#define MEM_EXECUTE_OPTION_ENABLE 0x2
#define MEM_EXECUTE_OPTION_DISABLE_THUNK_EMULATION 0x4
#define MEM_EXECUTE_OPTION_PERMANENT 0x8
#define MEM_EXECUTE_OPTION_EXECUTE_DISPATCH_ENABLE 0x10
#define MEM_EXECUTE_OPTION_IMAGE_DISPATCH_ENABLE 0x20
#define MEM_EXECUTE_OPTION_VALID_FLAGS 0x3f

// Virtual memory

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAllocateVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
NTSYSAPI
NTSTATUS
NTAPI
NtAllocateVirtualMemoryEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG PageProtection,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreeVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFreeVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReadVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWriteVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesWritten
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWriteVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesWritten
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtProtectVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG NewProtect,
    _Out_ PULONG OldProtect
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwProtectVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG NewProtect,
    _Out_ PULONG OldProtect
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
    _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
    _In_ SIZE_T MemoryInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
    _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
    _In_ SIZE_T MemoryInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _Out_ struct _IO_STATUS_BLOCK* IoStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFlushVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _Out_ struct _IO_STATUS_BLOCK* IoStatus
    );

// begin_private
typedef enum _VIRTUAL_MEMORY_INFORMATION_CLASS
{
    VmPrefetchInformation, // ULONG
    VmPagePriorityInformation,
    VmCfgCallTargetInformation, // CFG_CALL_TARGET_LIST_INFORMATION // REDSTONE2
    VmPageDirtyStateInformation, // REDSTONE3
    VmImageHotPatchInformation, // 19H1
    VmPhysicalContiguityInformation, // 20H1
    VmVirtualMachinePrepopulateInformation,
    MaxVmInfoClass
} VIRTUAL_MEMORY_INFORMATION_CLASS;

typedef struct _MEMORY_RANGE_ENTRY
{
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} MEMORY_RANGE_ENTRY, *PMEMORY_RANGE_ENTRY;

typedef struct _CFG_CALL_TARGET_LIST_INFORMATION
{
    ULONG NumberOfEntries;
    ULONG Reserved;
    PULONG NumberOfEntriesProcessed;
    PCFG_CALL_TARGET_INFO CallTargetInfo;
    PVOID Section; // since REDSTONE5
    ULONGLONG FileOffset;
} CFG_CALL_TARGET_LIST_INFORMATION, *PCFG_CALL_TARGET_LIST_INFORMATION;
// end_private

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
    _In_ ULONG_PTR NumberOfEntries,
    _In_reads_ (NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
    _In_reads_bytes_ (VmInformationLength) PVOID VmInformation,
    _In_ ULONG VmInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
    _In_ ULONG_PTR NumberOfEntries,
    _In_reads_ (NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
    _In_reads_bytes_ (VmInformationLength) PVOID VmInformation,
    _In_ ULONG VmInformationLength
    );

#endif

#define MAP_PROCESS 1
#define MAP_SYSTEM 2

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLockVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLockVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnlockVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnlockVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType
    );

// Sections

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSectionEx(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateSectionEx(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapViewOfSection(
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*ViewSize) _Writable_bytes_(*ViewSize) _Post_readable_byte_size_(*ViewSize)) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwMapViewOfSection(
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*ViewSize) _Writable_bytes_(*ViewSize) _Post_readable_byte_size_(*ViewSize)) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
NTSYSAPI
NTSTATUS
NTAPI
NtMapViewOfSectionEx(
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*ViewSize) _Writable_bytes_(*ViewSize) _Post_readable_byte_size_(*ViewSize)) PVOID *BaseAddress,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect,
    _Inout_updates_opt_(ParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnmapViewOfSection(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnmapViewOfSection(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnmapViewOfSectionEx(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnmapViewOfSectionEx(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ ULONG Flags
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtExtendSection(
    _In_ HANDLE SectionHandle,
    _Inout_ PLARGE_INTEGER NewSectionSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwExtendSection(
    _In_ HANDLE SectionHandle,
    _Inout_ PLARGE_INTEGER NewSectionSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySection(
    _In_ HANDLE SectionHandle,
    _In_ SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_writes_bytes_(SectionInformationLength) PVOID SectionInformation,
    _In_ SIZE_T SectionInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySection(
    _In_ HANDLE SectionHandle,
    _In_ SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_writes_bytes_(SectionInformationLength) PVOID SectionInformation,
    _In_ SIZE_T SectionInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAreMappedFilesTheSame(
    _In_ PVOID File1MappedAsAnImage,
    _In_ PVOID File2MappedAsFile
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAreMappedFilesTheSame(
    _In_ PVOID File1MappedAsAnImage,
    _In_ PVOID File2MappedAsFile
    );

// Partitions

#ifndef MEMORY_PARTITION_QUERY_ACCESS
#define MEMORY_PARTITION_QUERY_ACCESS 0x0001
#define MEMORY_PARTITION_MODIFY_ACCESS 0x0002
#define MEMORY_PARTITION_ALL_ACCESS \
    (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | \
     MEMORY_PARTITION_QUERY_ACCESS | MEMORY_PARTITION_MODIFY_ACCESS)
#endif

// private
typedef enum _MEMORY_PARTITION_INFORMATION_CLASS
{
    SystemMemoryPartitionInformation, // q: MEMORY_PARTITION_CONFIGURATION_INFORMATION
    SystemMemoryPartitionMoveMemory, // s: MEMORY_PARTITION_TRANSFER_INFORMATION
    SystemMemoryPartitionAddPagefile, // s: MEMORY_PARTITION_PAGEFILE_INFORMATION
    SystemMemoryPartitionCombineMemory, // q; s: MEMORY_PARTITION_PAGE_COMBINE_INFORMATION
    SystemMemoryPartitionInitialAddMemory, // q; s: MEMORY_PARTITION_INITIAL_ADD_INFORMATION
    SystemMemoryPartitionGetMemoryEvents, // MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION // since REDSTONE2
    SystemMemoryPartitionMax
} MEMORY_PARTITION_INFORMATION_CLASS;

// private
typedef struct _MEMORY_PARTITION_CONFIGURATION_INFORMATION
{
    ULONG Flags;
    ULONG NumaNode;
    ULONG Channel;
    ULONG NumberOfNumaNodes;
    ULONG_PTR ResidentAvailablePages;
    ULONG_PTR CommittedPages;
    ULONG_PTR CommitLimit;
    ULONG_PTR PeakCommitment;
    ULONG_PTR TotalNumberOfPages;
    ULONG_PTR AvailablePages;
    ULONG_PTR ZeroPages;
    ULONG_PTR FreePages;
    ULONG_PTR StandbyPages;
    ULONG_PTR StandbyPageCountByPriority[8]; // since REDSTONE2
    ULONG_PTR RepurposedPagesByPriority[8];
    ULONG_PTR MaximumCommitLimit;
    ULONG_PTR DonatedPagesToPartitions;
    ULONG PartitionId; // since REDSTONE3
} MEMORY_PARTITION_CONFIGURATION_INFORMATION, *PMEMORY_PARTITION_CONFIGURATION_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_TRANSFER_INFORMATION
{
    ULONG_PTR NumberOfPages;
    ULONG NumaNode;
    ULONG Flags;
} MEMORY_PARTITION_TRANSFER_INFORMATION, *PMEMORY_PARTITION_TRANSFER_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_PAGEFILE_INFORMATION
{
    UNICODE_STRING PageFileName;
    LARGE_INTEGER MinimumSize;
    LARGE_INTEGER MaximumSize;
    ULONG Flags;
} MEMORY_PARTITION_PAGEFILE_INFORMATION, *PMEMORY_PARTITION_PAGEFILE_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_PAGE_COMBINE_INFORMATION
{
    HANDLE StopHandle;
    ULONG Flags;
    ULONG_PTR TotalNumberOfPages;
} MEMORY_PARTITION_PAGE_COMBINE_INFORMATION, *PMEMORY_PARTITION_PAGE_COMBINE_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_PAGE_RANGE
{
    ULONG_PTR StartPage;
    ULONG_PTR NumberOfPages;
} MEMORY_PARTITION_PAGE_RANGE, *PMEMORY_PARTITION_PAGE_RANGE;

// private
typedef struct _MEMORY_PARTITION_INITIAL_ADD_INFORMATION
{
    ULONG Flags;
    ULONG NumberOfRanges;
    ULONG_PTR NumberOfPagesAdded;
    MEMORY_PARTITION_PAGE_RANGE PartitionRanges[1];
} MEMORY_PARTITION_INITIAL_ADD_INFORMATION, *PMEMORY_PARTITION_INITIAL_ADD_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION
{
    union
    {    
        struct
        {
            ULONG CommitEvents : 1;
            ULONG Spare : 31;
        };
        ULONG AllFlags;
    } Flags;
    
    ULONG HandleAttributes;
    ULONG DesiredAccess;
    HANDLE LowCommitCondition; // \KernelObjects\LowCommitCondition
    HANDLE HighCommitCondition; // \KernelObjects\HighCommitCondition
    HANDLE MaximumCommitCondition; // \KernelObjects\MaximumCommitCondition
} MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION, *PMEMORY_PARTITION_MEMORY_EVENTS_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreatePartition(
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG PreferredNode
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreatePartition(
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG PreferredNode
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenPartition(
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenPartition(
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtManagePartition(
    _In_ MEMORY_PARTITION_INFORMATION_CLASS PartitionInformationClass,
    _In_ PVOID PartitionInformation,
    _In_ ULONG PartitionInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwManagePartition(
    _In_ MEMORY_PARTITION_INFORMATION_CLASS PartitionInformationClass,
    _In_ PVOID PartitionInformation,
    _In_ ULONG PartitionInformationLength
    );

#endif

// User physical pages

NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapUserPhysicalPages(
    _In_ PVOID VirtualAddress,
    _In_ ULONG_PTR NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwMapUserPhysicalPages(
    _In_ PVOID VirtualAddress,
    _In_ ULONG_PTR NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapUserPhysicalPagesScatter(
    _In_reads_(NumberOfPages) PVOID *VirtualAddresses,
    _In_ ULONG_PTR NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwMapUserPhysicalPagesScatter(
    _In_reads_(NumberOfPages) PVOID *VirtualAddresses,
    _In_ ULONG_PTR NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAllocateUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateUserPhysicalPagesEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray,
    _Inout_updates_opt_(ParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAllocateUserPhysicalPagesEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray,
    _Inout_updates_opt_(ParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreeUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _In_reads_(*NumberOfPages) PULONG_PTR UserPfnArray
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFreeUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _In_reads_(*NumberOfPages) PULONG_PTR UserPfnArray
    );

// Misc.

NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize,
    _Out_writes_(*EntriesInUserAddressArray) PVOID *UserAddressArray,
    _Inout_ PULONG_PTR EntriesInUserAddressArray,
    _Out_ PULONG Granularity
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize,
    _Out_writes_(*EntriesInUserAddressArray) PVOID *UserAddressArray,
    _Inout_ PULONG_PTR EntriesInUserAddressArray,
    _Out_ PULONG Granularity
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtResetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwResetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreatePagingFile(
    _In_ PUNICODE_STRING PageFileName,
    _In_ PLARGE_INTEGER MinimumSize,
    _In_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG Priority
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreatePagingFile(
    _In_ PUNICODE_STRING PageFileName,
    _In_ PLARGE_INTEGER MinimumSize,
    _In_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG Priority
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushInstructionCache(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ SIZE_T Length
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFlushInstructionCache(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ SIZE_T Length
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushWriteBuffer(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFlushWriteBuffer(
    VOID
    );

// Enclave support

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateEnclave(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T Size,
    _In_ SIZE_T InitialCommitment,
    _In_ ULONG EnclaveType,
    _In_reads_bytes_(EnclaveInformationLength) PVOID EnclaveInformation,
    _In_ ULONG EnclaveInformationLength,
    _Out_opt_ PULONG EnclaveError
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateEnclave(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T Size,
    _In_ SIZE_T InitialCommitment,
    _In_ ULONG EnclaveType,
    _In_reads_bytes_(EnclaveInformationLength) PVOID EnclaveInformation,
    _In_ ULONG EnclaveInformationLength,
    _Out_opt_ PULONG EnclaveError
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadEnclaveData(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _In_ ULONG Protect,
    _In_reads_bytes_(PageInformationLength) PVOID PageInformation,
    _In_ ULONG PageInformationLength,
    _Out_opt_ PSIZE_T NumberOfBytesWritten,
    _Out_opt_ PULONG EnclaveError
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLoadEnclaveData(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _In_ ULONG Protect,
    _In_reads_bytes_(PageInformationLength) PVOID PageInformation,
    _In_ ULONG PageInformationLength,
    _Out_opt_ PSIZE_T NumberOfBytesWritten,
    _Out_opt_ PULONG EnclaveError
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtInitializeEnclave(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_reads_bytes_(EnclaveInformationLength) PVOID EnclaveInformation,
    _In_ ULONG EnclaveInformationLength,
    _Out_opt_ PULONG EnclaveError
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwInitializeEnclave(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_reads_bytes_(EnclaveInformationLength) PVOID EnclaveInformation,
    _In_ ULONG EnclaveInformationLength,
    _Out_opt_ PULONG EnclaveError
    );

// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
NtTerminateEnclave(
    _In_ PVOID BaseAddress,
    _In_ BOOLEAN WaitForThread
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTerminateEnclave(
    _In_ PVOID BaseAddress,
    _In_ BOOLEAN WaitForThread
    );

// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCallEnclave(
    _In_ PENCLAVE_ROUTINE Routine,
    _In_ PVOID Parameter,
    _In_ BOOLEAN WaitForThread,
    _Out_opt_ PVOID *ReturnValue
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCallEnclave(
    _In_ PENCLAVE_ROUTINE Routine,
    _In_ PVOID Parameter,
    _In_ BOOLEAN WaitForThread,
    _Out_opt_ PVOID *ReturnValue
    );

// #include <ntobapi.h>
#define OBJECT_TYPE_CREATE 0x0001
#define OBJECT_TYPE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)

#define DIRECTORY_QUERY 0x0001
#define DIRECTORY_TRAVERSE 0x0002
#define DIRECTORY_CREATE_OBJECT 0x0004
#define DIRECTORY_CREATE_SUBDIRECTORY 0x0008
#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xf)

#define SYMBOLIC_LINK_QUERY 0x0001
#define SYMBOLIC_LINK_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)

#ifndef OBJ_PROTECT_CLOSE
#define OBJ_PROTECT_CLOSE 0x00000001
#endif
#ifndef OBJ_INHERIT
#define OBJ_INHERIT 0x00000002
#endif
#ifndef OBJ_AUDIT_OBJECT_CLOSE
#define OBJ_AUDIT_OBJECT_CLOSE 0x00000004
#endif

typedef enum _OBJECT_INFORMATION_CLASS
{
    ObjectBasicInformation, // q: OBJECT_BASIC_INFORMATION
    ObjectNameInformation, // q: OBJECT_NAME_INFORMATION
    ObjectTypeInformation, // q: OBJECT_TYPE_INFORMATION
    ObjectTypesInformation, // q: OBJECT_TYPES_INFORMATION
    ObjectHandleFlagInformation, // qs: OBJECT_HANDLE_FLAG_INFORMATION
    ObjectSessionInformation,
    ObjectSessionObjectInformation,
    MaxObjectInfoClass
} OBJECT_INFORMATION_CLASS;

typedef struct _OBJECT_BASIC_INFORMATION
{
    ULONG Attributes;
    ACCESS_MASK GrantedAccess;
    ULONG HandleCount;
    ULONG PointerCount;
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    ULONG Reserved[3];
    ULONG NameInfoSize;
    ULONG TypeInfoSize;
    ULONG SecurityDescriptorSize;
    LARGE_INTEGER CreationTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;

typedef struct _OBJECT_NAME_INFORMATION
{
    UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef struct _OBJECT_TYPE_INFORMATION
{
    UNICODE_STRING TypeName;
    ULONG TotalNumberOfObjects;
    ULONG TotalNumberOfHandles;
    ULONG TotalPagedPoolUsage;
    ULONG TotalNonPagedPoolUsage;
    ULONG TotalNamePoolUsage;
    ULONG TotalHandleTableUsage;
    ULONG HighWaterNumberOfObjects;
    ULONG HighWaterNumberOfHandles;
    ULONG HighWaterPagedPoolUsage;
    ULONG HighWaterNonPagedPoolUsage;
    ULONG HighWaterNamePoolUsage;
    ULONG HighWaterHandleTableUsage;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
    BOOLEAN SecurityRequired;
    BOOLEAN MaintainHandleCount;
    UCHAR TypeIndex; // since WINBLUE
    CHAR ReservedByte;
    ULONG PoolType;
    ULONG DefaultPagedPoolCharge;
    ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

typedef struct _OBJECT_TYPES_INFORMATION
{
    ULONG NumberOfTypes;
} OBJECT_TYPES_INFORMATION, *POBJECT_TYPES_INFORMATION;

typedef struct _OBJECT_HANDLE_FLAG_INFORMATION
{
    BOOLEAN Inherit;
    BOOLEAN ProtectFromClose;
} OBJECT_HANDLE_FLAG_INFORMATION, *POBJECT_HANDLE_FLAG_INFORMATION;

// Objects, handles

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryObject(
    _In_opt_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryObject(
    _In_opt_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationObject(
    _In_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _In_reads_bytes_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationObject(
    _In_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _In_reads_bytes_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength
    );

#define DUPLICATE_CLOSE_SOURCE 0x00000001
#define DUPLICATE_SAME_ACCESS 0x00000002
#define DUPLICATE_SAME_ATTRIBUTES 0x00000004

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDuplicateObject(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_opt_ HANDLE TargetProcessHandle,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDuplicateObject(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_opt_ HANDLE TargetProcessHandle,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtMakeTemporaryObject(
    _In_ HANDLE Handle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwMakeTemporaryObject(
    _In_ HANDLE Handle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtMakePermanentObject(
    _In_ HANDLE Handle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwMakePermanentObject(
    _In_ HANDLE Handle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSignalAndWaitForSingleObject(
    _In_ HANDLE SignalHandle,
    _In_ HANDLE WaitHandle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSignalAndWaitForSingleObject(
    _In_ HANDLE SignalHandle,
    _In_ HANDLE WaitHandle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForSingleObject(
    _In_ HANDLE Handle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitForSingleObject(
    _In_ HANDLE Handle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForMultipleObjects(
    _In_ ULONG Count,
    _In_reads_(Count) HANDLE Handles[],
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitForMultipleObjects(
    _In_ ULONG Count,
    _In_reads_(Count) HANDLE Handles[],
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForMultipleObjects32(
    _In_ ULONG Count,
    _In_reads_(Count) LONG Handles[],
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitForMultipleObjects32(
    _In_ ULONG Count,
    _In_reads_(Count) LONG Handles[],
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetSecurityObject(
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetSecurityObject(
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySecurityObject(
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _Out_writes_bytes_opt_(Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Length,
    _Out_ PULONG LengthNeeded
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySecurityObject(
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _Out_writes_bytes_opt_(Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Length,
    _Out_ PULONG LengthNeeded
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtClose(
    _In_ _Post_ptr_invalid_ HANDLE Handle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwClose(
    _In_ _Post_ptr_invalid_ HANDLE Handle
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompareObjects(
    _In_ HANDLE FirstObjectHandle,
    _In_ HANDLE SecondObjectHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCompareObjects(
    _In_ HANDLE FirstObjectHandle,
    _In_ HANDLE SecondObjectHandle
    );
#endif

// Directory objects

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateDirectoryObject(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateDirectoryObject(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateDirectoryObjectEx(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ShadowDirectoryHandle,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateDirectoryObjectEx(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ShadowDirectoryHandle,
    _In_ ULONG Flags
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenDirectoryObject(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenDirectoryObject(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

typedef struct _OBJECT_DIRECTORY_INFORMATION
{
    UNICODE_STRING Name;
    UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDirectoryObject(
    _In_ HANDLE DirectoryHandle,
    _Out_writes_bytes_opt_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_ BOOLEAN RestartScan,
    _Inout_ PULONG Context,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryDirectoryObject(
    _In_ HANDLE DirectoryHandle,
    _Out_writes_bytes_opt_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_ BOOLEAN RestartScan,
    _Inout_ PULONG Context,
    _Out_opt_ PULONG ReturnLength
    );

// Private namespaces

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreatePrivateNamespace(
    _Out_ PHANDLE NamespaceHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PVOID BoundaryDescriptor
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreatePrivateNamespace(
    _Out_ PHANDLE NamespaceHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PVOID BoundaryDescriptor
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenPrivateNamespace(
    _Out_ PHANDLE NamespaceHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PVOID BoundaryDescriptor
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenPrivateNamespace(
    _Out_ PHANDLE NamespaceHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PVOID BoundaryDescriptor
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeletePrivateNamespace(
    _In_ HANDLE NamespaceHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeletePrivateNamespace(
    _In_ HANDLE NamespaceHandle
    );

#endif

// Symbolic links

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSymbolicLinkObject(
    _Out_ PHANDLE LinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PUNICODE_STRING LinkTarget
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateSymbolicLinkObject(
    _Out_ PHANDLE LinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PUNICODE_STRING LinkTarget
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenSymbolicLinkObject(
    _Out_ PHANDLE LinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenSymbolicLinkObject(
    _Out_ PHANDLE LinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySymbolicLinkObject(
    _In_ HANDLE LinkHandle,
    _Inout_ PUNICODE_STRING LinkTarget,
    _Out_opt_ PULONG ReturnedLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySymbolicLinkObject(
    _In_ HANDLE LinkHandle,
    _Inout_ PUNICODE_STRING LinkTarget,
    _Out_opt_ PULONG ReturnedLength
    );

typedef enum _SYMBOLIC_LINK_INFO_CLASS
{
    SymbolicLinkGlobalInformation = 1, // s: ULONG
    SymbolicLinkAccessMask, // s: ACCESS_MASK
    MaxnSymbolicLinkInfoClass
} SYMBOLIC_LINK_INFO_CLASS;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationSymbolicLink(
    _In_ HANDLE LinkHandle,
    _In_ SYMBOLIC_LINK_INFO_CLASS SymbolicLinkInformationClass,
    _In_reads_bytes_(SymbolicLinkInformationLength) PVOID SymbolicLinkInformation,
    _In_ ULONG SymbolicLinkInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationSymbolicLink(
    _In_ HANDLE LinkHandle,
    _In_ SYMBOLIC_LINK_INFO_CLASS SymbolicLinkInformationClass,
    _In_reads_bytes_(SymbolicLinkInformationLength) PVOID SymbolicLinkInformation,
    _In_ ULONG SymbolicLinkInformationLength
    );

// #include <ntpsapi.h>
#ifndef PROCESS_SET_PORT
#define PROCESS_SET_PORT 0x0800
#endif

#ifndef THREAD_ALERT
#define THREAD_ALERT 0x0004
#endif

#define GDI_HANDLE_BUFFER_SIZE32 34
#define GDI_HANDLE_BUFFER_SIZE64 60

#ifndef _WIN64
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#endif

typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];

typedef ULONG GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef ULONG GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];

#ifndef FLS_MAXIMUM_AVAILABLE
#define FLS_MAXIMUM_AVAILABLE 128
#endif
#ifndef TLS_MINIMUM_AVAILABLE
#define TLS_MINIMUM_AVAILABLE 64
#endif
#ifndef TLS_EXPANSION_SLOTS
#define TLS_EXPANSION_SLOTS 1024
#endif

// symbols
typedef struct _PEB_LDR_DATA
{
    ULONG Length;
    BOOLEAN Initialized;
    HANDLE SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID EntryInProgress;
    BOOLEAN ShutdownInProgress;
    HANDLE ShutdownThreadId;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _INITIAL_TEB
{
    struct
    {
        PVOID OldStackBase;
        PVOID OldStackLimit;
    } OldInitialTeb;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID StackAllocationBase;
} INITIAL_TEB, *PINITIAL_TEB;

typedef struct _WOW64_PROCESS
{
    PVOID Wow64;
} WOW64_PROCESS, *PWOW64_PROCESS;

// #include <ntpebteb.h>
typedef struct _RTL_USER_PROCESS_PARAMETERS *PRTL_USER_PROCESS_PARAMETERS;
typedef struct _RTL_CRITICAL_SECTION *PRTL_CRITICAL_SECTION;

// private
typedef struct _ACTIVATION_CONTEXT_STACK
{
    struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME* ActiveFrame;
    LIST_ENTRY FrameListCache;
    ULONG Flags;
    ULONG NextCookieSequenceNumber;
    ULONG StackId;
} ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;

// private
typedef struct _API_SET_NAMESPACE
{
    ULONG Version;
    ULONG Size;
    ULONG Flags;
    ULONG Count;
    ULONG EntryOffset;
    ULONG HashOffset;
    ULONG HashFactor;
} API_SET_NAMESPACE, *PAPI_SET_NAMESPACE;

// private
typedef struct _API_SET_HASH_ENTRY
{
    ULONG Hash;
    ULONG Index;
} API_SET_HASH_ENTRY, *PAPI_SET_HASH_ENTRY;

// private
typedef struct _API_SET_NAMESPACE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG HashedLength;
    ULONG ValueOffset;
    ULONG ValueCount;
} API_SET_NAMESPACE_ENTRY, *PAPI_SET_NAMESPACE_ENTRY;

// private
typedef struct _API_SET_VALUE_ENTRY 
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG ValueOffset;
    ULONG ValueLength;
} API_SET_VALUE_ENTRY, *PAPI_SET_VALUE_ENTRY;

// symbols
typedef struct _PEB
{
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    union
    {
        BOOLEAN BitField;
        struct
        {
            BOOLEAN ImageUsesLargePages : 1;
            BOOLEAN IsProtectedProcess : 1;
            BOOLEAN IsImageDynamicallyRelocated : 1;
            BOOLEAN SkipPatchingUser32Forwarders : 1;
            BOOLEAN IsPackagedProcess : 1;
            BOOLEAN IsAppContainer : 1;
            BOOLEAN IsProtectedProcessLight : 1;
            BOOLEAN IsLongPathAwareProcess : 1;
        };
    };

    HANDLE Mutant;

    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID SubSystemData;
    PVOID ProcessHeap;
    PRTL_CRITICAL_SECTION FastPebLock;
    PSLIST_HEADER AtlThunkSListPtr;
    PVOID IFEOKey;

    union
    {
        ULONG CrossProcessFlags;
        struct
        {
            ULONG ProcessInJob : 1;
            ULONG ProcessInitializing : 1;
            ULONG ProcessUsingVEH : 1;
            ULONG ProcessUsingVCH : 1;
            ULONG ProcessUsingFTH : 1;
            ULONG ProcessPreviouslyThrottled : 1;
            ULONG ProcessCurrentlyThrottled : 1;
            ULONG ProcessImagesHotPatched : 1; // REDSTONE5
            ULONG ReservedBits0 : 24;
        };
    };
    union
    {
        PVOID KernelCallbackTable;
        PVOID UserSharedInfoPtr;
    };
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    PAPI_SET_NAMESPACE ApiSetMap;
    ULONG TlsExpansionCounter;
    PVOID TlsBitmap;
    ULONG TlsBitmapBits[2];
    
    PVOID ReadOnlySharedMemoryBase; 
    PVOID SharedData; // HotpatchInformation
    PVOID *ReadOnlyStaticServerData;
    
    PVOID AnsiCodePageData; // PCPTABLEINFO
    PVOID OemCodePageData; // PCPTABLEINFO
    PVOID UnicodeCaseTableData; // PNLSTABLEINFO

    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;

    ULARGE_INTEGER CriticalSectionTimeout;
    SIZE_T HeapSegmentReserve;
    SIZE_T HeapSegmentCommit;
    SIZE_T HeapDeCommitTotalFreeThreshold;
    SIZE_T HeapDeCommitFreeBlockThreshold;

    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    PVOID *ProcessHeaps; // PHEAP

    PVOID GdiSharedHandleTable;
    PVOID ProcessStarterHelper;
    ULONG GdiDCAttributeList;

    PRTL_CRITICAL_SECTION LoaderLock;

    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    ULONG_PTR ActiveProcessAffinityMask;
    GDI_HANDLE_BUFFER GdiHandleBuffer;
    PVOID PostProcessInitRoutine;

    PVOID TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32];

    ULONG SessionId;

    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    PVOID pShimData;
    PVOID AppCompatInfo; // APPCOMPAT_EXE_DATA

    UNICODE_STRING CSDVersion;

    PVOID ActivationContextData; // ACTIVATION_CONTEXT_DATA
    PVOID ProcessAssemblyStorageMap; // ASSEMBLY_STORAGE_MAP
    PVOID SystemDefaultActivationContextData; // ACTIVATION_CONTEXT_DATA
    PVOID SystemAssemblyStorageMap; // ASSEMBLY_STORAGE_MAP

    SIZE_T MinimumStackCommit;

    PVOID SparePointers[4]; // 19H1 (previously FlsCallback to FlsHighIndex)
    ULONG SpareUlongs[5]; // 19H1
    //PVOID* FlsCallback;
    //LIST_ENTRY FlsListHead;
    //PVOID FlsBitmap;
    //ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
    //ULONG FlsHighIndex;

    PVOID WerRegistrationData;
    PVOID WerShipAssertPtr;
    PVOID pUnused; // pContextData
    PVOID pImageHeaderHash;
    union
    {
        ULONG TracingFlags;
        struct
        {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG LibLoaderTracingEnabled : 1;
            ULONG SpareTracingBits : 29;
        };
    };
    ULONGLONG CsrServerReadOnlySharedMemoryBase;
    PRTL_CRITICAL_SECTION TppWorkerpListLock;
    LIST_ENTRY TppWorkerpList;
    PVOID WaitOnAddressHashTable[128];
    PVOID TelemetryCoverageHeader; // REDSTONE3
    ULONG CloudFileFlags;
    ULONG CloudFileDiagFlags; // REDSTONE4
    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderCompatibilityModeReserved[7];
    struct _LEAP_SECOND_DATA *LeapSecondData; // REDSTONE5
    union
    {
        ULONG LeapSecondFlags;
        struct
        {
            ULONG SixtySecondEnabled : 1;
            ULONG Reserved : 31;
        };
    };
    ULONG NtGlobalFlag2;
} PEB, *PPEB;

#ifdef _WIN64
C_ASSERT(FIELD_OFFSET(PEB, SessionId) == 0x2C0);
//C_ASSERT(sizeof(PEB) == 0x7B0); // REDSTONE3
//C_ASSERT(sizeof(PEB) == 0x7B8); // REDSTONE4
C_ASSERT(sizeof(PEB) == 0x7C8); // REDSTONE5 // 19H1
#else
C_ASSERT(FIELD_OFFSET(PEB, SessionId) == 0x1D4);
//C_ASSERT(sizeof(PEB) == 0x468); // REDSTONE3
//C_ASSERT(sizeof(PEB) == 0x470); // REDSTONE4
C_ASSERT(sizeof(PEB) == 0x480); // REDSTONE5 // 19H1
#endif

#define GDI_BATCH_BUFFER_SIZE 310

typedef struct _GDI_TEB_BATCH
{
    ULONG Offset;
    ULONG_PTR HDC;
    ULONG Buffer[GDI_BATCH_BUFFER_SIZE];
} GDI_TEB_BATCH, *PGDI_TEB_BATCH;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT
{
    ULONG Flags;
    PSTR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, *PTEB_ACTIVE_FRAME_CONTEXT;

typedef struct _TEB_ACTIVE_FRAME
{
    ULONG Flags;
    struct _TEB_ACTIVE_FRAME *Previous;
    PTEB_ACTIVE_FRAME_CONTEXT Context;
} TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;

struct _TEB
{
    NT_TIB NtTib;

    PVOID EnvironmentPointer;
    CLIENT_ID ClientId;
    PVOID ActiveRpcHandle;
    PVOID ThreadLocalStoragePointer;
    PPEB ProcessEnvironmentBlock;

    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    PVOID CsrClientThread;
    PVOID Win32ThreadInfo;
    ULONG User32Reserved[26];
    ULONG UserReserved[5];
    PVOID WOW32Reserved;
    LCID CurrentLocale;
    ULONG FpSoftwareStatusRegister;
    PVOID ReservedForDebuggerInstrumentation[16];
#ifdef _WIN64
    PVOID SystemReserved1[30];
#else
    PVOID SystemReserved1[26];
#endif
    
    CHAR PlaceholderCompatibilityMode;
    BOOLEAN PlaceholderHydrationAlwaysExplicit;
    CHAR PlaceholderReserved[10];

    ULONG ProxiedProcessId;
    ACTIVATION_CONTEXT_STACK ActivationStack;
    
    UCHAR WorkingOnBehalfTicket[8];
    NTSTATUS ExceptionCode;

    PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;
    ULONG_PTR InstrumentationCallbackSp;
    ULONG_PTR InstrumentationCallbackPreviousPc;
    ULONG_PTR InstrumentationCallbackPreviousSp;
#ifdef _WIN64
    ULONG TxFsContext;
#endif

    BOOLEAN InstrumentationCallbackDisabled;
#ifdef _WIN64
    BOOLEAN UnalignedLoadStoreExceptions;
#endif
#ifndef _WIN64
    UCHAR SpareBytes[23];
    ULONG TxFsContext;
#endif
    GDI_TEB_BATCH GdiTebBatch;
    CLIENT_ID RealClientId;
    HANDLE GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    PVOID GdiThreadLocalInfo;
    ULONG_PTR Win32ClientInfo[62];
    PVOID glDispatchTable[233];
    ULONG_PTR glReserved1[29];
    PVOID glReserved2;
    PVOID glSectionInfo;
    PVOID glSection;
    PVOID glTable;
    PVOID glCurrentRC;
    PVOID glContext;

    NTSTATUS LastStatusValue;
    UNICODE_STRING StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[261];

    PVOID DeallocationStack;
    PVOID TlsSlots[64];
    LIST_ENTRY TlsLinks;

    PVOID Vdm;
    PVOID ReservedForNtRpc;
    PVOID DbgSsReserved[2];

    ULONG HardErrorMode;
#ifdef _WIN64
    PVOID Instrumentation[11];
#else
    PVOID Instrumentation[9];
#endif
    GUID ActivityId;

    PVOID SubProcessTag;
    PVOID PerflibData;
    PVOID EtwTraceData;
    PVOID WinSockData;
    ULONG GdiBatchCount;

    union
    {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        ULONG IdealProcessorValue;
        struct
        {
            UCHAR ReservedPad0;
            UCHAR ReservedPad1;
            UCHAR ReservedPad2;
            UCHAR IdealProcessor;
        };
    };

    ULONG GuaranteedStackBytes;
    PVOID ReservedForPerf;
    PVOID ReservedForOle;
    ULONG WaitingOnLoaderLock;
    PVOID SavedPriorityState;
    ULONG_PTR ReservedForCodeCoverage;
    PVOID ThreadPoolData;
    PVOID *TlsExpansionSlots;
#ifdef _WIN64
    PVOID DeallocationBStore;
    PVOID BStoreLimit;
#endif
    ULONG MuiGeneration;
    ULONG IsImpersonating;
    PVOID NlsCache;
    PVOID pShimData;
    ULONG HeapData;
    HANDLE CurrentTransactionHandle;
    PTEB_ACTIVE_FRAME ActiveFrame;
    PVOID FlsData;

    PVOID PreferredLanguages;
    PVOID UserPrefLanguages;
    PVOID MergedPrefLanguages;
    ULONG MuiImpersonation;

    union
    {
        USHORT CrossTebFlags;
        USHORT SpareCrossTebBits : 16;
    };
    union
    {
        USHORT SameTebFlags;
        struct
        {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SkipLoaderInit : 1;
            USHORT SpareSameTebBits : 1;
        };
    };

    PVOID TxnScopeEnterCallback;
    PVOID TxnScopeExitCallback;
    PVOID TxnScopeContext;
    ULONG LockCount;
    LONG WowTebOffset;
    PVOID ResourceRetValue;
    PVOID ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;
};
 


// source:http://www.microsoft.com/whdc/system/Sysinternals/MoreThan64proc.mspx
typedef enum _PROCESSINFOCLASS
{
    ProcessBasicInformation, // q: PROCESS_BASIC_INFORMATION, PROCESS_EXTENDED_BASIC_INFORMATION
    ProcessQuotaLimits, // qs: QUOTA_LIMITS, QUOTA_LIMITS_EX
    ProcessIoCounters, // q: IO_COUNTERS
    ProcessVmCounters, // q: VM_COUNTERS, VM_COUNTERS_EX, VM_COUNTERS_EX2
    ProcessTimes, // q: KERNEL_USER_TIMES
    ProcessBasePriority, // s: KPRIORITY
    ProcessRaisePriority, // s: ULONG
    ProcessDebugPort, // q: HANDLE
    ProcessExceptionPort, // s: PROCESS_EXCEPTION_PORT
    ProcessAccessToken, // s: PROCESS_ACCESS_TOKEN
    ProcessLdtInformation, // qs: PROCESS_LDT_INFORMATION // 10
    ProcessLdtSize, // s: PROCESS_LDT_SIZE
    ProcessDefaultHardErrorMode, // qs: ULONG
    ProcessIoPortHandlers, // (kernel-mode only) // PROCESS_IO_PORT_HANDLER_INFORMATION
    ProcessPooledUsageAndLimits, // q: POOLED_USAGE_AND_LIMITS
    ProcessWorkingSetWatch, // q: PROCESS_WS_WATCH_INFORMATION[]; s: void
    ProcessUserModeIOPL, // qs: ULONG (requires SeTcbPrivilege)
    ProcessEnableAlignmentFaultFixup, // s: BOOLEAN
    ProcessPriorityClass, // qs: PROCESS_PRIORITY_CLASS
    ProcessWx86Information, // qs: ULONG (requires SeTcbPrivilege) (VdmAllowed)
    ProcessHandleCount, // q: ULONG, PROCESS_HANDLE_INFORMATION // 20
    ProcessAffinityMask, // s: KAFFINITY
    ProcessPriorityBoost, // qs: ULONG
    ProcessDeviceMap, // qs: PROCESS_DEVICEMAP_INFORMATION, PROCESS_DEVICEMAP_INFORMATION_EX
    ProcessSessionInformation, // q: PROCESS_SESSION_INFORMATION
    ProcessForegroundInformation, // s: PROCESS_FOREGROUND_BACKGROUND
    ProcessWow64Information, // q: ULONG_PTR
    ProcessImageFileName, // q: UNICODE_STRING
    ProcessLUIDDeviceMapsEnabled, // q: ULONG
    ProcessBreakOnTermination, // qs: ULONG
    ProcessDebugObjectHandle, // q: HANDLE // 30
    ProcessDebugFlags, // qs: ULONG
    ProcessHandleTracing, // q: PROCESS_HANDLE_TRACING_QUERY; s: size 0 disables, otherwise enables
    ProcessIoPriority, // qs: IO_PRIORITY_HINT
    ProcessExecuteFlags, // qs: ULONG
    ProcessTlsInformation, // PROCESS_TLS_INFORMATION // ProcessResourceManagement 
    ProcessCookie, // q: ULONG
    ProcessImageInformation, // q: SECTION_IMAGE_INFORMATION
    ProcessCycleTime, // q: PROCESS_CYCLE_TIME_INFORMATION // since VISTA
    ProcessPagePriority, // q: PAGE_PRIORITY_INFORMATION
    ProcessInstrumentationCallback, // qs: PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION // 40
    ProcessThreadStackAllocation, // s: PROCESS_STACK_ALLOCATION_INFORMATION, PROCESS_STACK_ALLOCATION_INFORMATION_EX
    ProcessWorkingSetWatchEx, // q: PROCESS_WS_WATCH_INFORMATION_EX[]
    ProcessImageFileNameWin32, // q: UNICODE_STRING
    ProcessImageFileMapping, // q: HANDLE (input)
    ProcessAffinityUpdateMode, // qs: PROCESS_AFFINITY_UPDATE_MODE
    ProcessMemoryAllocationMode, // qs: PROCESS_MEMORY_ALLOCATION_MODE
    ProcessGroupInformation, // q: USHORT[]
    ProcessTokenVirtualizationEnabled, // s: ULONG
    ProcessConsoleHostProcess, // q: ULONG_PTR // ProcessOwnerInformation
    ProcessWindowInformation, // q: PROCESS_WINDOW_INFORMATION // 50
    ProcessHandleInformation, // q: PROCESS_HANDLE_SNAPSHOT_INFORMATION // since WIN8
    ProcessMitigationPolicy, // s: PROCESS_MITIGATION_POLICY_INFORMATION
    ProcessDynamicFunctionTableInformation,
    ProcessHandleCheckingMode, // qs: ULONG; s: 0 disables, otherwise enables
    ProcessKeepAliveCount, // q: PROCESS_KEEPALIVE_COUNT_INFORMATION
    ProcessRevokeFileHandles, // s: PROCESS_REVOKE_FILE_HANDLES_INFORMATION
    ProcessWorkingSetControl, // s: PROCESS_WORKING_SET_CONTROL
    ProcessHandleTable, // q: ULONG[] // since WINBLUE
    ProcessCheckStackExtentsMode, // qs: ULONG // KPROCESS->CheckStackExtents (CFG)
    ProcessCommandLineInformation, // q: UNICODE_STRING // 60
    ProcessProtectionInformation, // q: PS_PROTECTION
    ProcessMemoryExhaustion, // PROCESS_MEMORY_EXHAUSTION_INFO // since THRESHOLD
    ProcessFaultInformation, // PROCESS_FAULT_INFORMATION
    ProcessTelemetryIdInformation, // q: PROCESS_TELEMETRY_ID_INFORMATION
    ProcessCommitReleaseInformation, // PROCESS_COMMIT_RELEASE_INFORMATION
    ProcessDefaultCpuSetsInformation,
    ProcessAllowedCpuSetsInformation,
    ProcessSubsystemProcess,
    ProcessJobMemoryInformation, // q: PROCESS_JOB_MEMORY_INFO
    ProcessInPrivate, // since THRESHOLD2 // 70
    ProcessRaiseUMExceptionOnInvalidHandleClose, // qs: ULONG; s: 0 disables, otherwise enables
    ProcessIumChallengeResponse,
    ProcessChildProcessInformation, // q: PROCESS_CHILD_PROCESS_INFORMATION
    ProcessHighGraphicsPriorityInformation, // qs: BOOLEAN (requires SeTcbPrivilege)
    ProcessSubsystemInformation, // q: SUBSYSTEM_INFORMATION_TYPE // since REDSTONE2
    ProcessEnergyValues, // q: PROCESS_ENERGY_VALUES, PROCESS_EXTENDED_ENERGY_VALUES
    ProcessPowerThrottlingState, // qs: POWER_THROTTLING_PROCESS_STATE
    ProcessReserved3Information, // ProcessActivityThrottlePolicy // PROCESS_ACTIVITY_THROTTLE_POLICY
    ProcessWin32kSyscallFilterInformation, // q: WIN32K_SYSCALL_FILTER
    ProcessDisableSystemAllowedCpuSets, // 80
    ProcessWakeInformation, // PROCESS_WAKE_INFORMATION
    ProcessEnergyTrackingState, // PROCESS_ENERGY_TRACKING_STATE
    ProcessManageWritesToExecutableMemory, // MANAGE_WRITES_TO_EXECUTABLE_MEMORY // since REDSTONE3
    ProcessCaptureTrustletLiveDump,
    ProcessTelemetryCoverage,
    ProcessEnclaveInformation,
    ProcessEnableReadWriteVmLogging, // PROCESS_READWRITEVM_LOGGING_INFORMATION
    ProcessUptimeInformation, // q: PROCESS_UPTIME_INFORMATION
    ProcessImageSection, // q: HANDLE
    ProcessDebugAuthInformation, // since REDSTONE4 // 90
    ProcessSystemResourceManagement, // PROCESS_SYSTEM_RESOURCE_MANAGEMENT
    ProcessSequenceNumber, // q: ULONGLONG
    ProcessLoaderDetour, // since REDSTONE5
    ProcessSecurityDomainInformation, // PROCESS_SECURITY_DOMAIN_INFORMATION
    ProcessCombineSecurityDomainsInformation, // PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION
    ProcessEnableLogging, // PROCESS_LOGGING_INFORMATION
    ProcessLeapSecondInformation, // PROCESS_LEAP_SECOND_INFORMATION
    ProcessFiberShadowStackAllocation, // PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION // since 19H1
    ProcessFreeFiberShadowStackAllocation, // PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
    ProcessAltSystemCallInformation, // qs: BOOLEAN (kernel-mode only) // INT2E // since 20H1 // 100
    ProcessDynamicEHContinuationTargets, // PROCESS_DYNAMIC_EH_CONTINUATION_TARGETS_INFORMATION
    ProcessDynamicEnforcedCetCompatibleRanges, // PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE_INFORMATION // since 20H2
    MaxProcessInfoClass
} PROCESSINFOCLASS;

typedef enum _THREADINFOCLASS
{
    ThreadBasicInformation, // q: THREAD_BASIC_INFORMATION
    ThreadTimes, // q: KERNEL_USER_TIMES
    ThreadPriority, // s: KPRIORITY
    ThreadBasePriority, // s: LONG
    ThreadAffinityMask, // s: KAFFINITY
    ThreadImpersonationToken, // s: HANDLE
    ThreadDescriptorTableEntry, // q: DESCRIPTOR_TABLE_ENTRY (or WOW64_DESCRIPTOR_TABLE_ENTRY)
    ThreadEnableAlignmentFaultFixup, // s: BOOLEAN
    ThreadEventPair,
    ThreadQuerySetWin32StartAddress, // q: PVOID
    ThreadZeroTlsCell, // 10
    ThreadPerformanceCount, // q: LARGE_INTEGER
    ThreadAmILastThread, // q: ULONG
    ThreadIdealProcessor, // s: ULONG
    ThreadPriorityBoost, // qs: ULONG
    ThreadSetTlsArrayAddress,
    ThreadIsIoPending, // q: ULONG
    ThreadHideFromDebugger, // s: void
    ThreadBreakOnTermination, // qs: ULONG
    ThreadSwitchLegacyState,
    ThreadIsTerminated, // q: ULONG // 20
    ThreadLastSystemCall, // q: THREAD_LAST_SYSCALL_INFORMATION
    ThreadIoPriority, // qs: IO_PRIORITY_HINT
    ThreadCycleTime, // q: THREAD_CYCLE_TIME_INFORMATION
    ThreadPagePriority, // q: ULONG
    ThreadActualBasePriority,
    ThreadTebInformation, // q: THREAD_TEB_INFORMATION (requires THREAD_GET_CONTEXT + THREAD_SET_CONTEXT)
    ThreadCSwitchMon,
    ThreadCSwitchPmu,
    ThreadWow64Context, // qs: WOW64_CONTEXT
    ThreadGroupInformation, // q: GROUP_AFFINITY // 30
    ThreadUmsInformation, // q: THREAD_UMS_INFORMATION
    ThreadCounterProfiling, // sizeof(1) 
    ThreadIdealProcessorEx, // q: PROCESSOR_NUMBER
    ThreadCpuAccountingInformation, // sizeof(1) // since WIN8
    ThreadSuspendCount, // q: ULONG // since WINBLUE
    ThreadHeterogeneousCpuPolicy, // q: KHETERO_CPU_POLICY // since THRESHOLD
    ThreadContainerId, // q: GUID
    ThreadNameInformation, // qs: THREAD_NAME_INFORMATION
    ThreadSelectedCpuSets,
    ThreadSystemThreadInformation, // q: SYSTEM_THREAD_INFORMATION // 40
    ThreadActualGroupAffinity, // sizeof(16) // since THRESHOLD2
    ThreadDynamicCodePolicyInfo, // sizeof(4)
    ThreadExplicitCaseSensitivity, // qs: ULONG; s: 0 disables, otherwise enables
    ThreadWorkOnBehalfTicket, // RTL_WORK_ON_BEHALF_TICKET_EX
    ThreadSubsystemInformation, // q: SUBSYSTEM_INFORMATION_TYPE // since REDSTONE2
    ThreadDbgkWerReportActive,
    ThreadAttachContainer,
    ThreadManageWritesToExecutableMemory, // MANAGE_WRITES_TO_EXECUTABLE_MEMORY // since REDSTONE3
    ThreadPowerThrottlingState, // POWER_THROTTLING_THREAD_STATE
    ThreadWorkloadClass, // THREAD_WORKLOAD_CLASS // since REDSTONE5 // 50
    MaxThreadInfoClass
} THREADINFOCLASS;

// Use with both ProcessPagePriority and ThreadPagePriority
typedef struct _PAGE_PRIORITY_INFORMATION
{
    ULONG PagePriority;
} PAGE_PRIORITY_INFORMATION, *PPAGE_PRIORITY_INFORMATION;

// Process information structures

typedef struct _PROCESS_BASIC_INFORMATION
{
    NTSTATUS ExitStatus;
    PPEB PebBaseAddress;
    ULONG_PTR AffinityMask;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION, *PPROCESS_BASIC_INFORMATION;

typedef struct _PROCESS_EXTENDED_BASIC_INFORMATION
{
    SIZE_T Size; // set to sizeof structure on input
    PROCESS_BASIC_INFORMATION BasicInfo;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG IsProtectedProcess : 1;
            ULONG IsWow64Process : 1;
            ULONG IsProcessDeleting : 1;
            ULONG IsCrossSessionCreate : 1;
            ULONG IsFrozen : 1;
            ULONG IsBackground : 1;
            ULONG IsStronglyNamed : 1;
            ULONG IsSecureProcess : 1;
            ULONG IsSubsystemProcess : 1;
            ULONG SpareBits : 23;
        };
    };
} PROCESS_EXTENDED_BASIC_INFORMATION, *PPROCESS_EXTENDED_BASIC_INFORMATION;

typedef struct _VM_COUNTERS
{
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
} VM_COUNTERS, *PVM_COUNTERS;

typedef struct _VM_COUNTERS_EX
{
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivateUsage;
} VM_COUNTERS_EX, *PVM_COUNTERS_EX;

// private
typedef struct _VM_COUNTERS_EX2
{
    VM_COUNTERS_EX CountersEx;
    SIZE_T PrivateWorkingSetSize;
    SIZE_T SharedCommitUsage;
} VM_COUNTERS_EX2, *PVM_COUNTERS_EX2;

typedef struct _KERNEL_USER_TIMES
{
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER ExitTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
} KERNEL_USER_TIMES, *PKERNEL_USER_TIMES;

typedef struct _POOLED_USAGE_AND_LIMITS
{
    SIZE_T PeakPagedPoolUsage;
    SIZE_T PagedPoolUsage;
    SIZE_T PagedPoolLimit;
    SIZE_T PeakNonPagedPoolUsage;
    SIZE_T NonPagedPoolUsage;
    SIZE_T NonPagedPoolLimit;
    SIZE_T PeakPagefileUsage;
    SIZE_T PagefileUsage;
    SIZE_T PagefileLimit;
} POOLED_USAGE_AND_LIMITS, *PPOOLED_USAGE_AND_LIMITS;

#define PROCESS_EXCEPTION_PORT_ALL_STATE_BITS 0x00000003
#define PROCESS_EXCEPTION_PORT_ALL_STATE_FLAGS ((ULONG_PTR)((1UL << PROCESS_EXCEPTION_PORT_ALL_STATE_BITS) - 1))

typedef struct _PROCESS_EXCEPTION_PORT 
{
    _In_ HANDLE ExceptionPortHandle; // Handle to the exception port. No particular access required.
    _Inout_ ULONG StateFlags; // Miscellaneous state flags to be cached along with the exception port in the kernel.
} PROCESS_EXCEPTION_PORT, *PPROCESS_EXCEPTION_PORT;

typedef struct _PROCESS_ACCESS_TOKEN
{
    HANDLE Token; // needs TOKEN_ASSIGN_PRIMARY access
    HANDLE Thread; // handle to initial/only thread; needs THREAD_QUERY_INFORMATION access
} PROCESS_ACCESS_TOKEN, *PPROCESS_ACCESS_TOKEN;

typedef struct _PROCESS_LDT_INFORMATION
{
    ULONG Start;
    ULONG Length;
    LDT_ENTRY LdtEntries[1];
} PROCESS_LDT_INFORMATION, *PPROCESS_LDT_INFORMATION;

typedef struct _PROCESS_LDT_SIZE
{
    ULONG Length;
} PROCESS_LDT_SIZE, *PPROCESS_LDT_SIZE;

typedef struct _PROCESS_WS_WATCH_INFORMATION
{
    PVOID FaultingPc;
    PVOID FaultingVa;
} PROCESS_WS_WATCH_INFORMATION, *PPROCESS_WS_WATCH_INFORMATION;

// psapi:PSAPI_WS_WATCH_INFORMATION_EX
typedef struct _PROCESS_WS_WATCH_INFORMATION_EX
{
    PROCESS_WS_WATCH_INFORMATION BasicInfo;
    ULONG_PTR FaultingThreadId;
    ULONG_PTR Flags;
} PROCESS_WS_WATCH_INFORMATION_EX, *PPROCESS_WS_WATCH_INFORMATION_EX;

#define PROCESS_PRIORITY_CLASS_UNKNOWN 0
#define PROCESS_PRIORITY_CLASS_IDLE 1
#define PROCESS_PRIORITY_CLASS_NORMAL 2
#define PROCESS_PRIORITY_CLASS_HIGH 3
#define PROCESS_PRIORITY_CLASS_REALTIME 4
#define PROCESS_PRIORITY_CLASS_BELOW_NORMAL 5
#define PROCESS_PRIORITY_CLASS_ABOVE_NORMAL 6

typedef struct _PROCESS_PRIORITY_CLASS
{
    BOOLEAN Foreground;
    UCHAR PriorityClass;
} PROCESS_PRIORITY_CLASS, *PPROCESS_PRIORITY_CLASS;

typedef struct _PROCESS_FOREGROUND_BACKGROUND
{
    BOOLEAN Foreground;
} PROCESS_FOREGROUND_BACKGROUND, *PPROCESS_FOREGROUND_BACKGROUND;

typedef struct _PROCESS_DEVICEMAP_INFORMATION
{
    union
    {
        struct
        {
            HANDLE DirectoryHandle;
        } Set;
        struct
        {
            ULONG DriveMap;
            UCHAR DriveType[32];
        } Query;
    };
} PROCESS_DEVICEMAP_INFORMATION, *PPROCESS_DEVICEMAP_INFORMATION;

#define PROCESS_LUID_DOSDEVICES_ONLY 0x00000001

typedef struct _PROCESS_DEVICEMAP_INFORMATION_EX
{
    union
    {
        struct
        {
            HANDLE DirectoryHandle;
        } Set;
        struct
        {
            ULONG DriveMap;
            UCHAR DriveType[32];
        } Query;
    };
    ULONG Flags; // PROCESS_LUID_DOSDEVICES_ONLY
} PROCESS_DEVICEMAP_INFORMATION_EX, *PPROCESS_DEVICEMAP_INFORMATION_EX;

typedef struct _PROCESS_SESSION_INFORMATION
{
    ULONG SessionId;
} PROCESS_SESSION_INFORMATION, *PPROCESS_SESSION_INFORMATION;

#define PROCESS_HANDLE_EXCEPTIONS_ENABLED 0x00000001

#define PROCESS_HANDLE_RAISE_EXCEPTION_ON_INVALID_HANDLE_CLOSE_DISABLED 0x00000000
#define PROCESS_HANDLE_RAISE_EXCEPTION_ON_INVALID_HANDLE_CLOSE_ENABLED 0x00000001

typedef struct _PROCESS_HANDLE_TRACING_ENABLE
{
    ULONG Flags;
} PROCESS_HANDLE_TRACING_ENABLE, *PPROCESS_HANDLE_TRACING_ENABLE;

#define PROCESS_HANDLE_TRACING_MAX_SLOTS 0x20000

typedef struct _PROCESS_HANDLE_TRACING_ENABLE_EX
{
    ULONG Flags;
    ULONG TotalSlots;
} PROCESS_HANDLE_TRACING_ENABLE_EX, *PPROCESS_HANDLE_TRACING_ENABLE_EX;

#define PROCESS_HANDLE_TRACING_MAX_STACKS 16

#define PROCESS_HANDLE_TRACE_TYPE_OPEN 1
#define PROCESS_HANDLE_TRACE_TYPE_CLOSE 2
#define PROCESS_HANDLE_TRACE_TYPE_BADREF 3

typedef struct _PROCESS_HANDLE_TRACING_ENTRY
{
    HANDLE Handle;
    CLIENT_ID ClientId;
    ULONG Type;
    PVOID Stacks[PROCESS_HANDLE_TRACING_MAX_STACKS];
} PROCESS_HANDLE_TRACING_ENTRY, *PPROCESS_HANDLE_TRACING_ENTRY;

typedef struct _PROCESS_HANDLE_TRACING_QUERY
{
    HANDLE Handle;
    ULONG TotalTraces;
    PROCESS_HANDLE_TRACING_ENTRY HandleTrace[1];
} PROCESS_HANDLE_TRACING_QUERY, *PPROCESS_HANDLE_TRACING_QUERY;

// private
typedef struct _THREAD_TLS_INFORMATION
{
    ULONG Flags;
    PVOID NewTlsData;
    PVOID OldTlsData;
    HANDLE ThreadId;
} THREAD_TLS_INFORMATION, *PTHREAD_TLS_INFORMATION;

// private
typedef enum _PROCESS_TLS_INFORMATION_TYPE
{
    ProcessTlsReplaceIndex,
    ProcessTlsReplaceVector,
    MaxProcessTlsOperation
} PROCESS_TLS_INFORMATION_TYPE, *PPROCESS_TLS_INFORMATION_TYPE;

// private
typedef struct _PROCESS_TLS_INFORMATION
{
    ULONG Flags;
    ULONG OperationType;
    ULONG ThreadDataCount;
    ULONG TlsIndex;
    ULONG PreviousCount;
    THREAD_TLS_INFORMATION ThreadData[1];
} PROCESS_TLS_INFORMATION, *PPROCESS_TLS_INFORMATION;

// private
typedef struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
    ULONG Version;
    ULONG Reserved;
    PVOID Callback;
} PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION, *PPROCESS_INSTRUMENTATION_CALLBACK_INFORMATION;

// private
typedef struct _PROCESS_STACK_ALLOCATION_INFORMATION
{
    SIZE_T ReserveSize;
    SIZE_T ZeroBits;
    PVOID StackBase;
} PROCESS_STACK_ALLOCATION_INFORMATION, *PPROCESS_STACK_ALLOCATION_INFORMATION;

// private
typedef struct _PROCESS_STACK_ALLOCATION_INFORMATION_EX
{
    ULONG PreferredNode;
    ULONG Reserved0;
    ULONG Reserved1;
    ULONG Reserved2;
    PROCESS_STACK_ALLOCATION_INFORMATION AllocInfo;
} PROCESS_STACK_ALLOCATION_INFORMATION_EX, *PPROCESS_STACK_ALLOCATION_INFORMATION_EX;

// private
typedef union _PROCESS_AFFINITY_UPDATE_MODE
{
    ULONG Flags;
    struct
    {
        ULONG EnableAutoUpdate : 1;
        ULONG Permanent : 1;
        ULONG Reserved : 30;
    };
} PROCESS_AFFINITY_UPDATE_MODE, *PPROCESS_AFFINITY_UPDATE_MODE;

// private
typedef union _PROCESS_MEMORY_ALLOCATION_MODE
{
    ULONG Flags;
    struct
    {
        ULONG TopDown : 1;
        ULONG Reserved : 31;
    };
} PROCESS_MEMORY_ALLOCATION_MODE, *PPROCESS_MEMORY_ALLOCATION_MODE;

// private
typedef struct _PROCESS_HANDLE_INFORMATION
{
    ULONG HandleCount;
    ULONG HandleCountHighWatermark;
} PROCESS_HANDLE_INFORMATION, *PPROCESS_HANDLE_INFORMATION;

// private
typedef struct _PROCESS_CYCLE_TIME_INFORMATION
{
    ULONGLONG AccumulatedCycles;
    ULONGLONG CurrentCycleCount;
} PROCESS_CYCLE_TIME_INFORMATION, *PPROCESS_CYCLE_TIME_INFORMATION;

// private
typedef struct _PROCESS_WINDOW_INFORMATION
{
    ULONG WindowFlags;
    USHORT WindowTitleLength;
    WCHAR WindowTitle[1];
} PROCESS_WINDOW_INFORMATION, *PPROCESS_WINDOW_INFORMATION;

// private
typedef struct _PROCESS_HANDLE_TABLE_ENTRY_INFO
{
    HANDLE HandleValue;
    ULONG_PTR HandleCount;
    ULONG_PTR PointerCount;
    ULONG GrantedAccess;
    ULONG ObjectTypeIndex;
    ULONG HandleAttributes;
    ULONG Reserved;
} PROCESS_HANDLE_TABLE_ENTRY_INFO, *PPROCESS_HANDLE_TABLE_ENTRY_INFO;

// private
typedef struct _PROCESS_HANDLE_SNAPSHOT_INFORMATION
{
    ULONG_PTR NumberOfHandles;
    ULONG_PTR Reserved;
    PROCESS_HANDLE_TABLE_ENTRY_INFO Handles[1];
} PROCESS_HANDLE_SNAPSHOT_INFORMATION, *PPROCESS_HANDLE_SNAPSHOT_INFORMATION;

// TODO: remove after switch to 21H1 SDK
typedef struct _PROCESS_MITIGATION_USER_SHADOW_STACK_POLICY_INT {
    union {
        DWORD Flags;
        struct {
            DWORD EnableUserShadowStack : 1;
            DWORD AuditUserShadowStack : 1;
            DWORD SetContextIpValidation : 1;
            DWORD AuditSetContextIpValidation : 1;
            DWORD EnableUserShadowStackStrictMode : 1;
            DWORD BlockNonCetBinaries : 1;
            DWORD BlockNonCetBinariesNonEhcont : 1;
            DWORD AuditBlockNonCetBinaries : 1;
            DWORD CetDynamicApisOutOfProcOnly : 1;
            DWORD ReservedFlags : 23;

        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
} PROCESS_MITIGATION_USER_SHADOW_STACK_POLICY_INT, * PPROCESS_MITIGATION_USER_SHADOW_STACK_POLICY_INT;

// private
typedef struct _PROCESS_MITIGATION_POLICY_INFORMATION
{
    PROCESS_MITIGATION_POLICY Policy;
    union
    {
        PROCESS_MITIGATION_ASLR_POLICY ASLRPolicy;
        PROCESS_MITIGATION_STRICT_HANDLE_CHECK_POLICY StrictHandleCheckPolicy;
        PROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY SystemCallDisablePolicy;
        PROCESS_MITIGATION_EXTENSION_POINT_DISABLE_POLICY ExtensionPointDisablePolicy;
        PROCESS_MITIGATION_DYNAMIC_CODE_POLICY DynamicCodePolicy;
        PROCESS_MITIGATION_CONTROL_FLOW_GUARD_POLICY ControlFlowGuardPolicy;
        PROCESS_MITIGATION_BINARY_SIGNATURE_POLICY SignaturePolicy;
        PROCESS_MITIGATION_FONT_DISABLE_POLICY FontDisablePolicy;
        PROCESS_MITIGATION_IMAGE_LOAD_POLICY ImageLoadPolicy;
        PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY SystemCallFilterPolicy;
        PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY PayloadRestrictionPolicy;
        PROCESS_MITIGATION_CHILD_PROCESS_POLICY ChildProcessPolicy;
        PROCESS_MITIGATION_SIDE_CHANNEL_ISOLATION_POLICY SideChannelIsolationPolicy;
        PROCESS_MITIGATION_USER_SHADOW_STACK_POLICY_INT UserShadowStackPolicy;
    };
} PROCESS_MITIGATION_POLICY_INFORMATION, *PPROCESS_MITIGATION_POLICY_INFORMATION;

typedef struct _PROCESS_KEEPALIVE_COUNT_INFORMATION
{
    ULONG WakeCount;
    ULONG NoWakeCount;
} PROCESS_KEEPALIVE_COUNT_INFORMATION, *PPROCESS_KEEPALIVE_COUNT_INFORMATION;

typedef struct _PROCESS_REVOKE_FILE_HANDLES_INFORMATION
{
    UNICODE_STRING TargetDevicePath;
} PROCESS_REVOKE_FILE_HANDLES_INFORMATION, *PPROCESS_REVOKE_FILE_HANDLES_INFORMATION;

// begin_private

typedef enum _PROCESS_WORKING_SET_OPERATION
{
    ProcessWorkingSetSwap,
    ProcessWorkingSetEmpty,
    ProcessWorkingSetOperationMax
} PROCESS_WORKING_SET_OPERATION;

typedef struct _PROCESS_WORKING_SET_CONTROL
{
    ULONG Version;
    PROCESS_WORKING_SET_OPERATION Operation;
    ULONG Flags;
} PROCESS_WORKING_SET_CONTROL, *PPROCESS_WORKING_SET_CONTROL;

typedef enum _PS_PROTECTED_TYPE
{
    PsProtectedTypeNone,
    PsProtectedTypeProtectedLight,
    PsProtectedTypeProtected,
    PsProtectedTypeMax
} PS_PROTECTED_TYPE;

typedef enum _PS_PROTECTED_SIGNER
{
    PsProtectedSignerNone,
    PsProtectedSignerAuthenticode,
    PsProtectedSignerCodeGen,
    PsProtectedSignerAntimalware,
    PsProtectedSignerLsa,
    PsProtectedSignerWindows,
    PsProtectedSignerWinTcb,
    PsProtectedSignerWinSystem,
    PsProtectedSignerApp,
    PsProtectedSignerMax
} PS_PROTECTED_SIGNER;

#define PS_PROTECTED_SIGNER_MASK 0xFF
#define PS_PROTECTED_AUDIT_MASK 0x08
#define PS_PROTECTED_TYPE_MASK 0x07

// vProtectionLevel.Level = PsProtectedValue(PsProtectedSignerCodeGen, FALSE, PsProtectedTypeProtectedLight)
#define PsProtectedValue(aSigner, aAudit, aType) ( \
    ((aSigner & PS_PROTECTED_SIGNER_MASK) << 4) | \
    ((aAudit & PS_PROTECTED_AUDIT_MASK) << 3) | \
    (aType & PS_PROTECTED_TYPE_MASK)\
    )

// InitializePsProtection(&vProtectionLevel, PsProtectedSignerCodeGen, FALSE, PsProtectedTypeProtectedLight)
#define InitializePsProtection(aProtectionLevelPtr, aSigner, aAudit, aType) { \
    (aProtectionLevelPtr)->Signer = aSigner; \
    (aProtectionLevelPtr)->Audit = aAudit; \
    (aProtectionLevelPtr)->Type = aType; \
    }

typedef struct _PS_PROTECTION
{
    union
    {
        UCHAR Level;
        struct
        {
            UCHAR Type : 3;
            UCHAR Audit : 1;
            UCHAR Signer : 4;
        };
    };
} PS_PROTECTION, *PPS_PROTECTION;

typedef struct _PROCESS_FAULT_INFORMATION
{
    ULONG FaultFlags;
    ULONG AdditionalInfo;
} PROCESS_FAULT_INFORMATION, *PPROCESS_FAULT_INFORMATION;

typedef struct _PROCESS_TELEMETRY_ID_INFORMATION
{
    ULONG HeaderSize;
    ULONG ProcessId;
    ULONGLONG ProcessStartKey;
    ULONGLONG CreateTime;
    ULONGLONG CreateInterruptTime;
    ULONGLONG CreateUnbiasedInterruptTime;
    ULONGLONG ProcessSequenceNumber;
    ULONGLONG SessionCreateTime;
    ULONG SessionId;
    ULONG BootId;
    ULONG ImageChecksum;
    ULONG ImageTimeDateStamp;
    ULONG UserSidOffset;
    ULONG ImagePathOffset;
    ULONG PackageNameOffset;
    ULONG RelativeAppNameOffset;
    ULONG CommandLineOffset;
} PROCESS_TELEMETRY_ID_INFORMATION, *PPROCESS_TELEMETRY_ID_INFORMATION;

typedef struct _PROCESS_COMMIT_RELEASE_INFORMATION
{
    ULONG Version;
    struct
    {
        ULONG Eligible : 1;
        ULONG ReleaseRepurposedMemResetCommit : 1;
        ULONG ForceReleaseMemResetCommit : 1;
        ULONG Spare : 29;
    };
    SIZE_T CommitDebt;
    SIZE_T CommittedMemResetSize;
    SIZE_T RepurposedMemResetSize;
} PROCESS_COMMIT_RELEASE_INFORMATION, *PPROCESS_COMMIT_RELEASE_INFORMATION;

typedef struct _PROCESS_JOB_MEMORY_INFO
{
    ULONGLONG SharedCommitUsage;
    ULONGLONG PrivateCommitUsage;
    ULONGLONG PeakPrivateCommitUsage;
    ULONGLONG PrivateCommitLimit;
    ULONGLONG TotalCommitLimit;
} PROCESS_JOB_MEMORY_INFO, *PPROCESS_JOB_MEMORY_INFO;

typedef struct _PROCESS_CHILD_PROCESS_INFORMATION
{
    BOOLEAN ProhibitChildProcesses;
    BOOLEAN AlwaysAllowSecureChildProcess; // REDSTONE3
    BOOLEAN AuditProhibitChildProcesses;
} PROCESS_CHILD_PROCESS_INFORMATION, *PPROCESS_CHILD_PROCESS_INFORMATION;

#define POWER_THROTTLING_PROCESS_CURRENT_VERSION 1
#define POWER_THROTTLING_PROCESS_EXECUTION_SPEED 0x1
#define POWER_THROTTLING_PROCESS_DELAYTIMERS 0x2
#define POWER_THROTTLING_PROCESS_VALID_FLAGS ((POWER_THROTTLING_PROCESS_EXECUTION_SPEED | POWER_THROTTLING_PROCESS_DELAYTIMERS))

typedef struct _POWER_THROTTLING_PROCESS_STATE
{
    ULONG Version;
    ULONG ControlMask;
    ULONG StateMask;
} POWER_THROTTLING_PROCESS_STATE, *PPOWER_THROTTLING_PROCESS_STATE;

typedef struct _WIN32K_SYSCALL_FILTER
{
    ULONG FilterState;
    ULONG FilterSet;
} WIN32K_SYSCALL_FILTER, *PWIN32K_SYSCALL_FILTER;

typedef struct _PROCESS_WAKE_INFORMATION
{
    ULONGLONG NotificationChannel;
    ULONG WakeCounters[7];
    struct _JOBOBJECT_WAKE_FILTER* WakeFilter;
} PROCESS_WAKE_INFORMATION, *PPROCESS_WAKE_INFORMATION;

typedef struct _PROCESS_ENERGY_TRACKING_STATE
{
    ULONG StateUpdateMask;
    ULONG StateDesiredValue;
    ULONG StateSequence;
    ULONG UpdateTag : 1;
    WCHAR Tag[64];
} PROCESS_ENERGY_TRACKING_STATE, *PPROCESS_ENERGY_TRACKING_STATE;

typedef struct _MANAGE_WRITES_TO_EXECUTABLE_MEMORY
{
    ULONG Version : 8;
    ULONG ProcessEnableWriteExceptions : 1;
    ULONG ThreadAllowWrites : 1;
    ULONG Spare : 22;
    PVOID KernelWriteToExecutableSignal; // 19H1
} MANAGE_WRITES_TO_EXECUTABLE_MEMORY, *PMANAGE_WRITES_TO_EXECUTABLE_MEMORY;

#define POWER_THROTTLING_THREAD_CURRENT_VERSION 1
#define POWER_THROTTLING_THREAD_EXECUTION_SPEED 0x1
#define POWER_THROTTLING_THREAD_VALID_FLAGS (POWER_THROTTLING_THREAD_EXECUTION_SPEED)

typedef struct _POWER_THROTTLING_THREAD_STATE
{
    ULONG Version;
    ULONG ControlMask;
    ULONG StateMask;
} POWER_THROTTLING_THREAD_STATE, *PPOWER_THROTTLING_THREAD_STATE;

#define PROCESS_READWRITEVM_LOGGING_ENABLE_READVM 1
#define PROCESS_READWRITEVM_LOGGING_ENABLE_WRITEVM 2
#define PROCESS_READWRITEVM_LOGGING_ENABLE_READVM_V 1UL
#define PROCESS_READWRITEVM_LOGGING_ENABLE_WRITEVM_V 2UL

typedef union _PROCESS_READWRITEVM_LOGGING_INFORMATION
{
    UCHAR Flags;
    struct
    {
        UCHAR EnableReadVmLogging : 1;
        UCHAR EnableWriteVmLogging : 1;
        UCHAR Unused : 6;
    };
} PROCESS_READWRITEVM_LOGGING_INFORMATION, *PPROCESS_READWRITEVM_LOGGING_INFORMATION;

typedef struct _PROCESS_UPTIME_INFORMATION
{
    ULONGLONG QueryInterruptTime;
    ULONGLONG QueryUnbiasedTime;
    ULONGLONG EndInterruptTime;
    ULONGLONG TimeSinceCreation;
    ULONGLONG Uptime;
    ULONGLONG SuspendedTime;
    union
    {
        ULONG HangCount : 4;
        ULONG GhostCount : 4;
        ULONG Crashed : 1;
        ULONG Terminated : 1;       
    };
} PROCESS_UPTIME_INFORMATION, *PPROCESS_UPTIME_INFORMATION;

typedef union _PROCESS_SYSTEM_RESOURCE_MANAGEMENT
{
    ULONG Flags;
    struct
    {
        ULONG Foreground : 1;
        ULONG Reserved : 31;
    };
} PROCESS_SYSTEM_RESOURCE_MANAGEMENT, *PPROCESS_SYSTEM_RESOURCE_MANAGEMENT;

// private
typedef struct _PROCESS_SECURITY_DOMAIN_INFORMATION
{
    ULONGLONG SecurityDomain;
} PROCESS_SECURITY_DOMAIN_INFORMATION, *PPROCESS_SECURITY_DOMAIN_INFORMATION;

// private
typedef struct _PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION
{
    HANDLE ProcessHandle;
} PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION, *PPROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION;

// private
typedef struct _PROCESS_LOGGING_INFORMATION
{
    ULONG Flags;
    struct
    {
        ULONG EnableReadVmLogging : 1;
        ULONG EnableWriteVmLogging : 1;
        ULONG EnableProcessSuspendResumeLogging : 1;
        ULONG EnableThreadSuspendResumeLogging : 1;
        ULONG Reserved : 28;
    };
} PROCESS_LOGGING_INFORMATION, *PPROCESS_LOGGING_INFORMATION;

// private
typedef struct _PROCESS_LEAP_SECOND_INFORMATION
{
    ULONG Flags;
    ULONG Reserved;
} PROCESS_LEAP_SECOND_INFORMATION, *PPROCESS_LEAP_SECOND_INFORMATION;

// private
typedef struct _PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
{
    ULONGLONG ReserveSize;
    ULONGLONG CommitSize;
    ULONG PreferredNode;
    ULONG Reserved;
    PVOID Ssp;
} PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION, *PPROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION;

// private
typedef struct _PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
{
    PVOID Ssp;
} PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION, *PPROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION;

//// private
//typedef struct _PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE
//{
//    ULONG_PTR BaseAddress;
//    SIZE_T Size;
//    ULONG Flags;
//} PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE, *PPROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE;
//
//// private
//typedef struct _PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGES_INFORMATION
//{
//    USHORT NumberOfRanges;
//    USHORT Reserved;
//    ULONG Reserved2;
//    PPROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE Ranges;
//} PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGES_INFORMATION, *PPROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGES_INFORMATION;

// end_private

// Thread information structures

typedef struct _THREAD_BASIC_INFORMATION
{
    NTSTATUS ExitStatus;
    PTEB TebBaseAddress;
    CLIENT_ID ClientId;
    ULONG_PTR AffinityMask;
    KPRIORITY Priority;
    LONG BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

// private
typedef struct _THREAD_LAST_SYSCALL_INFORMATION
{
    PVOID FirstArgument;
    USHORT SystemCallNumber;
#ifdef WIN64
    USHORT Pad[0x3]; // since REDSTONE2
#else
    USHORT Pad[0x1]; // since REDSTONE2
#endif
    ULONG64 WaitTime;
} THREAD_LAST_SYSCALL_INFORMATION, *PTHREAD_LAST_SYSCALL_INFORMATION;

// private
typedef struct _THREAD_CYCLE_TIME_INFORMATION
{
    ULONGLONG AccumulatedCycles;
    ULONGLONG CurrentCycleCount;
} THREAD_CYCLE_TIME_INFORMATION, *PTHREAD_CYCLE_TIME_INFORMATION;

// private
typedef struct _THREAD_TEB_INFORMATION
{
    PVOID TebInformation; // buffer to place data in
    ULONG TebOffset; // offset in TEB to begin reading from
    ULONG BytesToRead; // number of bytes to read
} THREAD_TEB_INFORMATION, *PTHREAD_TEB_INFORMATION;

// symbols
typedef struct _COUNTER_READING
{
    HARDWARE_COUNTER_TYPE Type;
    ULONG Index;
    ULONG64 Start;
    ULONG64 Total;
} COUNTER_READING, *PCOUNTER_READING;

// symbols
typedef struct _THREAD_PERFORMANCE_DATA
{
    USHORT Size;
    USHORT Version;
    PROCESSOR_NUMBER ProcessorNumber;
    ULONG ContextSwitches;
    ULONG HwCountersCount;
    ULONG64 UpdateCount;
    ULONG64 WaitReasonBitMap;
    ULONG64 HardwareCounters;
    COUNTER_READING CycleTime;
    COUNTER_READING HwCounters[MAX_HW_COUNTERS];
} THREAD_PERFORMANCE_DATA, *PTHREAD_PERFORMANCE_DATA;

// private
typedef struct _THREAD_PROFILING_INFORMATION
{
    ULONG64 HardwareCounters;
    ULONG Flags;
    ULONG Enable;
    PTHREAD_PERFORMANCE_DATA PerformanceData;
} THREAD_PROFILING_INFORMATION, *PTHREAD_PROFILING_INFORMATION;

// private
typedef struct _RTL_UMS_CONTEXT
{
    SINGLE_LIST_ENTRY Link;
    CONTEXT Context;
    PVOID Teb;
    PVOID UserContext;
    volatile ULONG ScheduledThread;
    volatile ULONG Suspended;
    volatile ULONG VolatileContext;
    volatile ULONG Terminated;
    volatile ULONG DebugActive;
    volatile ULONG RunningOnSelfThread;
    volatile ULONG DenyRunningOnSelfThread;
    volatile LONG Flags;
    volatile ULONG64 KernelUpdateLock;
    volatile ULONG64 PrimaryClientID;
    volatile ULONG64 ContextLock;
    struct _RTL_UMS_CONTEXT* PrimaryUmsContext;
    ULONG SwitchCount;
    ULONG KernelYieldCount;
    ULONG MixedYieldCount;
    ULONG YieldCount;
} RTL_UMS_CONTEXT, *PRTL_UMS_CONTEXT;

// private
typedef enum _THREAD_UMS_INFORMATION_COMMAND
{
    UmsInformationCommandInvalid,
    UmsInformationCommandAttach,
    UmsInformationCommandDetach,
    UmsInformationCommandQuery
} THREAD_UMS_INFORMATION_COMMAND;

// private
typedef struct _RTL_UMS_COMPLETION_LIST
{
    PSINGLE_LIST_ENTRY ThreadListHead;
    PVOID CompletionEvent;
    ULONG CompletionFlags;
    SINGLE_LIST_ENTRY InternalListHead;
} RTL_UMS_COMPLETION_LIST, *PRTL_UMS_COMPLETION_LIST;

// private
typedef struct _THREAD_UMS_INFORMATION
{
    THREAD_UMS_INFORMATION_COMMAND Command;
    PRTL_UMS_COMPLETION_LIST CompletionList;
    PRTL_UMS_CONTEXT UmsContext;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG IsUmsSchedulerThread : 1;
            ULONG IsUmsWorkerThread : 1;
            ULONG SpareBits : 30;
        };
    };
} THREAD_UMS_INFORMATION, *PTHREAD_UMS_INFORMATION;

// private
typedef struct _THREAD_NAME_INFORMATION
{
    UNICODE_STRING ThreadName;
} THREAD_NAME_INFORMATION, *PTHREAD_NAME_INFORMATION;

// private
typedef struct _ALPC_WORK_ON_BEHALF_TICKET
{
    ULONG ThreadId;
    ULONG ThreadCreationTimeLow;
} ALPC_WORK_ON_BEHALF_TICKET, *PALPC_WORK_ON_BEHALF_TICKET;

// private
typedef struct _RTL_WORK_ON_BEHALF_TICKET_EX
{
    ALPC_WORK_ON_BEHALF_TICKET Ticket;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG CurrentThread : 1;
            ULONG Reserved1 : 31;
        };
    };
    ULONG Reserved2;
} RTL_WORK_ON_BEHALF_TICKET_EX, *PRTL_WORK_ON_BEHALF_TICKET_EX;

// private
typedef enum _SUBSYSTEM_INFORMATION_TYPE 
{
    SubsystemInformationTypeWin32,
    SubsystemInformationTypeWSL,
    MaxSubsystemInformationType
} SUBSYSTEM_INFORMATION_TYPE;

// private
typedef enum _THREAD_WORKLOAD_CLASS
{
    ThreadWorkloadClassDefault,
    ThreadWorkloadClassGraphics,
    MaxThreadWorkloadClass
} THREAD_WORKLOAD_CLASS;

// Processes

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritObjectTable,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE ExceptionPort
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritObjectTable,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE ExceptionPort
    );

#define PROCESS_CREATE_FLAGS_BREAKAWAY 0x00000001
#define PROCESS_CREATE_FLAGS_NO_DEBUG_INHERIT 0x00000002
#define PROCESS_CREATE_FLAGS_INHERIT_HANDLES 0x00000004
#define PROCESS_CREATE_FLAGS_OVERRIDE_ADDRESS_SPACE 0x00000008
#define PROCESS_CREATE_FLAGS_LARGE_PAGES 0x00000010

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProcessEx(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ ULONG Flags,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE ExceptionPort,
    _In_ ULONG JobMemberLevel
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateProcessEx(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ ULONG Flags,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE ExceptionPort,
    _In_ ULONG JobMemberLevel
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtTerminateProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ NTSTATUS ExitStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTerminateProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ NTSTATUS ExitStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSuspendProcess(
    _In_ HANDLE ProcessHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSuspendProcess(
    _In_ HANDLE ProcessHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtResumeProcess(
    _In_ HANDLE ProcessHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwResumeProcess(
    _In_ HANDLE ProcessHandle
    );

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)
#define ZwCurrentProcess() NtCurrentProcess()
#define NtCurrentThread() ((HANDLE)(LONG_PTR)-2)
#define ZwCurrentThread() NtCurrentThread()
#define NtCurrentSession() ((HANDLE)(LONG_PTR)-3)
#define ZwCurrentSession() NtCurrentSession()
#define NtCurrentPeb() (NtCurrentTeb()->ProcessEnvironmentBlock)

// Windows 8 and above
#define NtCurrentProcessToken() ((HANDLE)(LONG_PTR)-4) // NtOpenProcessToken(NtCurrentProcess())
#define NtCurrentThreadToken() ((HANDLE)(LONG_PTR)-5) // NtOpenThreadToken(NtCurrentThread())
#define NtCurrentThreadEffectiveToken() ((HANDLE)(LONG_PTR)-6) // NtOpenThreadToken(NtCurrentThread()) + NtOpenProcessToken(NtCurrentProcess())

#define NtCurrentSilo() ((HANDLE)(LONG_PTR)-1)

// Not NT, but useful.
#define NtCurrentProcessId() (NtCurrentTeb()->ClientId.UniqueProcess)
#define NtCurrentThreadId() (NtCurrentTeb()->ClientId.UniqueThread)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

#if (NTDDI_VERSION >= NTDDI_WS03)

#define PROCESS_GET_NEXT_FLAGS_PREVIOUS_PROCESS 0x00000001

NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetNextProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewProcessHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetNextProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewProcessHandle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetNextThread(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewThreadHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetNextThread(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewThreadHandle
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryPortInformationProcess(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryPortInformationProcess(
    VOID
    );

// Threads

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _Out_ PCLIENT_ID ClientId,
    _In_ PCONTEXT ThreadContext,
    _In_ PINITIAL_TEB InitialTeb,
    _In_ BOOLEAN CreateSuspended
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _Out_ PCLIENT_ID ClientId,
    _In_ PCONTEXT ThreadContext,
    _In_ PINITIAL_TEB InitialTeb,
    _In_ BOOLEAN CreateSuspended
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtTerminateThread(
    _In_opt_ HANDLE ThreadHandle,
    _In_ NTSTATUS ExitStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTerminateThread(
    _In_opt_ HANDLE ThreadHandle,
    _In_ NTSTATUS ExitStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSuspendThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSuspendThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
    );

NTSYSCALLAPI
ULONG
NTAPI
NtGetCurrentProcessorNumber(
    VOID
    );

NTSYSCALLAPI
ULONG
NTAPI
ZwGetCurrentProcessorNumber(
    VOID
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
ULONG
NTAPI
NtGetCurrentProcessorNumberEx(
    _Out_opt_ PPROCESSOR_NUMBER ProcNumber
    );

NTSYSCALLAPI
ULONG
NTAPI
ZwGetCurrentProcessorNumberEx(
    _Out_opt_ PPROCESSOR_NUMBER ProcNumber
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetContextThread(
    _In_ HANDLE ThreadHandle,
    _Inout_ PCONTEXT ThreadContext
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetContextThread(
    _In_ HANDLE ThreadHandle,
    _Inout_ PCONTEXT ThreadContext
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetContextThread(
    _In_ HANDLE ThreadHandle,
    _In_ PCONTEXT ThreadContext
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetContextThread(
    _In_ HANDLE ThreadHandle,
    _In_ PCONTEXT ThreadContext
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _In_reads_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _In_reads_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlertThread(
    _In_ HANDLE ThreadHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlertThread(
    _In_ HANDLE ThreadHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlertResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlertResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtTestAlert(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTestAlert(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtImpersonateThread(
    _In_ HANDLE ServerThreadHandle,
    _In_ HANDLE ClientThreadHandle,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwImpersonateThread(
    _In_ HANDLE ServerThreadHandle,
    _In_ HANDLE ClientThreadHandle,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRegisterThreadTerminatePort(
    _In_ HANDLE PortHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRegisterThreadTerminatePort(
    _In_ HANDLE PortHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetLdtEntries(
    _In_ ULONG Selector0,
    _In_ ULONG Entry0Low,
    _In_ ULONG Entry0Hi,
    _In_ ULONG Selector1,
    _In_ ULONG Entry1Low,
    _In_ ULONG Entry1Hi
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetLdtEntries(
    _In_ ULONG Selector0,
    _In_ ULONG Entry0Low,
    _In_ ULONG Entry0Hi,
    _In_ ULONG Selector1,
    _In_ ULONG Entry1Low,
    _In_ ULONG Entry1Hi
    );

typedef VOID (*PPS_APC_ROUTINE)(
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueueApcThread(
    _In_ HANDLE ThreadHandle,
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueueApcThread(
    _In_ HANDLE ThreadHandle,
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)

#define APC_FORCE_THREAD_SIGNAL ((HANDLE)1) // ReserveHandle

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueueApcThreadEx(
    _In_ HANDLE ThreadHandle,
    _In_opt_ HANDLE ReserveHandle, // NtAllocateReserveObject
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueueApcThreadEx(
    _In_ HANDLE ThreadHandle,
    _In_opt_ HANDLE ReserveHandle, // NtAllocateReserveObject
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)

// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlertThreadByThreadId(
    _In_ HANDLE ThreadId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlertThreadByThreadId(
    _In_ HANDLE ThreadId
    );

// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForAlertByThreadId(
    _In_ PVOID Address,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitForAlertByThreadId(
    _In_ PVOID Address,
    _In_opt_ PLARGE_INTEGER Timeout
    );

#endif

// User processes and threads

// Attributes

// private
#define PS_ATTRIBUTE_NUMBER_MASK 0x0000ffff
#define PS_ATTRIBUTE_THREAD 0x00010000 // may be used with thread creation
#define PS_ATTRIBUTE_INPUT 0x00020000 // input only
#define PS_ATTRIBUTE_ADDITIVE 0x00040000 // "accumulated" e.g. bitmasks, counters, etc.

// private
typedef enum _PS_ATTRIBUTE_NUM
{
    PsAttributeParentProcess, // in HANDLE
    PsAttributeDebugPort, // in HANDLE
    PsAttributeToken, // in HANDLE
    PsAttributeClientId, // out PCLIENT_ID
    PsAttributeTebAddress, // out PTEB *
    PsAttributeImageName, // in PWSTR
    PsAttributeImageInfo, // out PSECTION_IMAGE_INFORMATION
    PsAttributeMemoryReserve, // in PPS_MEMORY_RESERVE
    PsAttributePriorityClass, // in UCHAR
    PsAttributeErrorMode, // in ULONG
    PsAttributeStdHandleInfo, // 10, in PPS_STD_HANDLE_INFO
    PsAttributeHandleList, // in PHANDLE
    PsAttributeGroupAffinity, // in PGROUP_AFFINITY
    PsAttributePreferredNode, // in PUSHORT
    PsAttributeIdealProcessor, // in PPROCESSOR_NUMBER
    PsAttributeUmsThread, // ? in PUMS_CREATE_THREAD_ATTRIBUTES
    PsAttributeMitigationOptions, // in UCHAR
    PsAttributeProtectionLevel, // in ULONG
    PsAttributeSecureProcess, // since THRESHOLD
    PsAttributeJobList,
    PsAttributeChildProcessPolicy, // since THRESHOLD2
    PsAttributeAllApplicationPackagesPolicy, // since REDSTONE
    PsAttributeWin32kFilter,
    PsAttributeSafeOpenPromptOriginClaim,
    PsAttributeBnoIsolation, // PS_BNO_ISOLATION_PARAMETERS
    PsAttributeDesktopAppPolicy, // in ULONG
    PsAttributeChpe, // since REDSTONE3
    PsAttributeMax
} PS_ATTRIBUTE_NUM;

// begin_rev

#define PsAttributeValue(Number, Thread, Input, Additive) \
    (((Number) & PS_ATTRIBUTE_NUMBER_MASK) | \
    ((Thread) ? PS_ATTRIBUTE_THREAD : 0) | \
    ((Input) ? PS_ATTRIBUTE_INPUT : 0) | \
    ((Additive) ? PS_ATTRIBUTE_ADDITIVE : 0))

#define PS_ATTRIBUTE_PARENT_PROCESS \
    PsAttributeValue(PsAttributeParentProcess, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_DEBUG_PORT \
    PsAttributeValue(PsAttributeDebugPort, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_TOKEN \
    PsAttributeValue(PsAttributeToken, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_CLIENT_ID \
    PsAttributeValue(PsAttributeClientId, TRUE, FALSE, FALSE)
#define PS_ATTRIBUTE_TEB_ADDRESS \
    PsAttributeValue(PsAttributeTebAddress, TRUE, FALSE, FALSE)
#define PS_ATTRIBUTE_IMAGE_NAME \
    PsAttributeValue(PsAttributeImageName, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_IMAGE_INFO \
    PsAttributeValue(PsAttributeImageInfo, FALSE, FALSE, FALSE)
#define PS_ATTRIBUTE_MEMORY_RESERVE \
    PsAttributeValue(PsAttributeMemoryReserve, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_PRIORITY_CLASS \
    PsAttributeValue(PsAttributePriorityClass, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_ERROR_MODE \
    PsAttributeValue(PsAttributeErrorMode, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_STD_HANDLE_INFO \
    PsAttributeValue(PsAttributeStdHandleInfo, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_HANDLE_LIST \
    PsAttributeValue(PsAttributeHandleList, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_GROUP_AFFINITY \
    PsAttributeValue(PsAttributeGroupAffinity, TRUE, TRUE, FALSE)
#define PS_ATTRIBUTE_PREFERRED_NODE \
    PsAttributeValue(PsAttributePreferredNode, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_IDEAL_PROCESSOR \
    PsAttributeValue(PsAttributeIdealProcessor, TRUE, TRUE, FALSE)
#define PS_ATTRIBUTE_UMS_THREAD \
    PsAttributeValue(PsAttributeUmsThread, TRUE, TRUE, FALSE)
#define PS_ATTRIBUTE_MITIGATION_OPTIONS \
    PsAttributeValue(PsAttributeMitigationOptions, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_PROTECTION_LEVEL \
    PsAttributeValue(PsAttributeProtectionLevel, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_SECURE_PROCESS \
    PsAttributeValue(PsAttributeSecureProcess, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_JOB_LIST \
    PsAttributeValue(PsAttributeJobList, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_CHILD_PROCESS_POLICY \
    PsAttributeValue(PsAttributeChildProcessPolicy, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_ALL_APPLICATION_PACKAGES_POLICY \
    PsAttributeValue(PsAttributeAllApplicationPackagesPolicy, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_WIN32K_FILTER \
    PsAttributeValue(PsAttributeWin32kFilter, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_SAFE_OPEN_PROMPT_ORIGIN_CLAIM \
    PsAttributeValue(PsAttributeSafeOpenPromptOriginClaim, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_BNO_ISOLATION \
    PsAttributeValue(PsAttributeBnoIsolation, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_DESKTOP_APP_POLICY \
    PsAttributeValue(PsAttributeDesktopAppPolicy, FALSE, TRUE, FALSE)

// end_rev

// begin_private

typedef struct _PS_ATTRIBUTE
{
    ULONG_PTR Attribute;
    SIZE_T Size;
    union
    {
        ULONG_PTR Value;
        PVOID ValuePtr;
    };
    PSIZE_T ReturnLength;
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST
{
    SIZE_T TotalLength;
    PS_ATTRIBUTE Attributes[1];
} PS_ATTRIBUTE_LIST, *PPS_ATTRIBUTE_LIST;

typedef struct _PS_MEMORY_RESERVE
{
    PVOID ReserveAddress;
    SIZE_T ReserveSize;
} PS_MEMORY_RESERVE, *PPS_MEMORY_RESERVE;

typedef enum _PS_STD_HANDLE_STATE
{
    PsNeverDuplicate,
    PsRequestDuplicate, // duplicate standard handles specified by PseudoHandleMask, and only if StdHandleSubsystemType matches the image subsystem
    PsAlwaysDuplicate, // always duplicate standard handles
    PsMaxStdHandleStates
} PS_STD_HANDLE_STATE;

// begin_rev
#define PS_STD_INPUT_HANDLE 0x1
#define PS_STD_OUTPUT_HANDLE 0x2
#define PS_STD_ERROR_HANDLE 0x4
// end_rev

typedef struct _PS_STD_HANDLE_INFO
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG StdHandleState : 2; // PS_STD_HANDLE_STATE
            ULONG PseudoHandleMask : 3; // PS_STD_*
        };
    };
    ULONG StdHandleSubsystemType;
} PS_STD_HANDLE_INFO, *PPS_STD_HANDLE_INFO;

// private
typedef struct _PS_BNO_ISOLATION_PARAMETERS
{
    UNICODE_STRING IsolationPrefix;
    ULONG HandleCount;
    PVOID *Handles;
    BOOLEAN IsolationEnabled;
} PS_BNO_ISOLATION_PARAMETERS, *PPS_BNO_ISOLATION_PARAMETERS;

// private
typedef enum _PS_MITIGATION_OPTION
{
    PS_MITIGATION_OPTION_NX,
    PS_MITIGATION_OPTION_SEHOP,
    PS_MITIGATION_OPTION_FORCE_RELOCATE_IMAGES,
    PS_MITIGATION_OPTION_HEAP_TERMINATE,
    PS_MITIGATION_OPTION_BOTTOM_UP_ASLR,
    PS_MITIGATION_OPTION_HIGH_ENTROPY_ASLR,
    PS_MITIGATION_OPTION_STRICT_HANDLE_CHECKS,
    PS_MITIGATION_OPTION_WIN32K_SYSTEM_CALL_DISABLE,
    PS_MITIGATION_OPTION_EXTENSION_POINT_DISABLE,
    PS_MITIGATION_OPTION_PROHIBIT_DYNAMIC_CODE,
    PS_MITIGATION_OPTION_CONTROL_FLOW_GUARD,
    PS_MITIGATION_OPTION_BLOCK_NON_MICROSOFT_BINARIES,
    PS_MITIGATION_OPTION_FONT_DISABLE,
    PS_MITIGATION_OPTION_IMAGE_LOAD_NO_REMOTE,
    PS_MITIGATION_OPTION_IMAGE_LOAD_NO_LOW_LABEL,
    PS_MITIGATION_OPTION_IMAGE_LOAD_PREFER_SYSTEM32,
    PS_MITIGATION_OPTION_RETURN_FLOW_GUARD,
    PS_MITIGATION_OPTION_LOADER_INTEGRITY_CONTINUITY,
    PS_MITIGATION_OPTION_STRICT_CONTROL_FLOW_GUARD,
    PS_MITIGATION_OPTION_RESTRICT_SET_THREAD_CONTEXT,
    PS_MITIGATION_OPTION_ROP_STACKPIVOT, // since REDSTONE3
    PS_MITIGATION_OPTION_ROP_CALLER_CHECK,
    PS_MITIGATION_OPTION_ROP_SIMEXEC,
    PS_MITIGATION_OPTION_EXPORT_ADDRESS_FILTER,
    PS_MITIGATION_OPTION_EXPORT_ADDRESS_FILTER_PLUS,
    PS_MITIGATION_OPTION_RESTRICT_CHILD_PROCESS_CREATION,
    PS_MITIGATION_OPTION_IMPORT_ADDRESS_FILTER,
    PS_MITIGATION_OPTION_MODULE_TAMPERING_PROTECTION,
    PS_MITIGATION_OPTION_RESTRICT_INDIRECT_BRANCH_PREDICTION,
    PS_MITIGATION_OPTION_SPECULATIVE_STORE_BYPASS_DISABLE, // since REDSTONE5
    PS_MITIGATION_OPTION_ALLOW_DOWNGRADE_DYNAMIC_CODE_POLICY,
    PS_MITIGATION_OPTION_CET_SHADOW_STACKS
} PS_MITIGATION_OPTION;

// windows-internals-book:"Chapter 5"
typedef enum _PS_CREATE_STATE
{
    PsCreateInitialState,
    PsCreateFailOnFileOpen,
    PsCreateFailOnSectionCreate,
    PsCreateFailExeFormat,
    PsCreateFailMachineMismatch,
    PsCreateFailExeName, // Debugger specified
    PsCreateSuccess,
    PsCreateMaximumStates
} PS_CREATE_STATE;

typedef struct _PS_CREATE_INFO
{
    SIZE_T Size;
    PS_CREATE_STATE State;
    union
    {
        // PsCreateInitialState
        struct
        {
            union
            {
                ULONG InitFlags;
                struct
                {
                    UCHAR WriteOutputOnExit : 1;
                    UCHAR DetectManifest : 1;
                    UCHAR IFEOSkipDebugger : 1;
                    UCHAR IFEODoNotPropagateKeyState : 1;
                    UCHAR SpareBits1 : 4;
                    UCHAR SpareBits2 : 8;
                    USHORT ProhibitedImageCharacteristics : 16;
                };
            };
            ACCESS_MASK AdditionalFileAccess;
        } InitState;

        // PsCreateFailOnSectionCreate
        struct
        {
            HANDLE FileHandle;
        } FailSection;

        // PsCreateFailExeFormat
        struct
        {
            USHORT DllCharacteristics;
        } ExeFormat;

        // PsCreateFailExeName
        struct
        {
            HANDLE IFEOKey;
        } ExeName;

        // PsCreateSuccess
        struct
        {
            union
            {
                ULONG OutputFlags;
                struct
                {
                    UCHAR ProtectedProcess : 1;
                    UCHAR AddressSpaceOverride : 1;
                    UCHAR DevOverrideEnabled : 1; // from Image File Execution Options
                    UCHAR ManifestDetected : 1;
                    UCHAR ProtectedProcessLight : 1;
                    UCHAR SpareBits1 : 3;
                    UCHAR SpareBits2 : 8;
                    USHORT SpareBits3 : 16;
                };
            };
            HANDLE FileHandle;
            HANDLE SectionHandle;
            ULONGLONG UserProcessParametersNative;
            ULONG UserProcessParametersWow64;
            ULONG CurrentParameterFlags;
            ULONGLONG PebAddressNative;
            ULONG PebAddressWow64;
            ULONGLONG ManifestAddress;
            ULONG ManifestSize;
        } SuccessState;
    };
} PS_CREATE_INFO, *PPS_CREATE_INFO;

// end_private

// begin_rev
#define PROCESS_CREATE_FLAGS_BREAKAWAY 0x00000001
#define PROCESS_CREATE_FLAGS_NO_DEBUG_INHERIT 0x00000002
#define PROCESS_CREATE_FLAGS_INHERIT_HANDLES 0x00000004
#define PROCESS_CREATE_FLAGS_OVERRIDE_ADDRESS_SPACE 0x00000008
#define PROCESS_CREATE_FLAGS_LARGE_PAGES 0x00000010
#define PROCESS_CREATE_FLAGS_LARGE_PAGE_SYSTEM_DLL 0x00000020
// Extended PROCESS_CREATE_FLAGS_*
#define PROCESS_CREATE_FLAGS_PROTECTED_PROCESS 0x00000040
#define PROCESS_CREATE_FLAGS_CREATE_SESSION 0x00000080 // ?
#define PROCESS_CREATE_FLAGS_INHERIT_FROM_PARENT 0x00000100
#define PROCESS_CREATE_FLAGS_SUSPENDED 0x00000200
#define PROCESS_CREATE_FLAGS_EXTENDED_UNKNOWN 0x00000400
// end_rev

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateUserProcess(
    _Out_ PHANDLE ProcessHandle,
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK ProcessDesiredAccess,
    _In_ ACCESS_MASK ThreadDesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ProcessObjectAttributes,
    _In_opt_ POBJECT_ATTRIBUTES ThreadObjectAttributes,
    _In_ ULONG ProcessFlags, // PROCESS_CREATE_FLAGS_*
    _In_ ULONG ThreadFlags, // THREAD_CREATE_FLAGS_*
    _In_opt_ PVOID ProcessParameters, // PRTL_USER_PROCESS_PARAMETERS
    _Inout_ PPS_CREATE_INFO CreateInfo,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateUserProcess(
    _Out_ PHANDLE ProcessHandle,
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK ProcessDesiredAccess,
    _In_ ACCESS_MASK ThreadDesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ProcessObjectAttributes,
    _In_opt_ POBJECT_ATTRIBUTES ThreadObjectAttributes,
    _In_ ULONG ProcessFlags, // PROCESS_CREATE_FLAGS_*
    _In_ ULONG ThreadFlags, // THREAD_CREATE_FLAGS_*
    _In_opt_ PVOID ProcessParameters, // PRTL_USER_PROCESS_PARAMETERS
    _Inout_ PPS_CREATE_INFO CreateInfo,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
    );
#endif

// begin_rev
#define THREAD_CREATE_FLAGS_CREATE_SUSPENDED 0x00000001
#define THREAD_CREATE_FLAGS_SKIP_THREAD_ATTACH 0x00000002 // ?
#define THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER 0x00000004
#define THREAD_CREATE_FLAGS_HAS_SECURITY_DESCRIPTOR 0x00000010 // ?
#define THREAD_CREATE_FLAGS_ACCESS_CHECK_IN_TARGET 0x00000020 // ?
#define THREAD_CREATE_FLAGS_SKIP_THREAD_SUSPEND 0x00000040 // ?
#define THREAD_CREATE_FLAGS_INITIAL_THREAD 0x00000080
// end_rev

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThreadEx(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_ PVOID StartRoutine, // PUSER_THREAD_START_ROUTINE
    _In_opt_ PVOID Argument,
    _In_ ULONG CreateFlags, // THREAD_CREATE_FLAGS_*
    _In_ SIZE_T ZeroBits,
    _In_ SIZE_T StackSize,
    _In_ SIZE_T MaximumStackSize,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateThreadEx(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_ PVOID StartRoutine, // PUSER_THREAD_START_ROUTINE
    _In_opt_ PVOID Argument,
    _In_ ULONG CreateFlags, // THREAD_CREATE_FLAGS_*
    _In_ SIZE_T ZeroBits,
    _In_ SIZE_T StackSize,
    _In_ SIZE_T MaximumStackSize,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
    );
#endif

// Job objects

// JOBOBJECTINFOCLASS
// Note: We don't use an enum since it conflicts with the Windows SDK.
#define JobObjectBasicAccountingInformation 1 // JOBOBJECT_BASIC_ACCOUNTING_INFORMATION
#define JobObjectBasicLimitInformation 2 // JOBOBJECT_BASIC_LIMIT_INFORMATION
#define JobObjectBasicProcessIdList 3 // JOBOBJECT_BASIC_PROCESS_ID_LIST
#define JobObjectBasicUIRestrictions 4 // JOBOBJECT_BASIC_UI_RESTRICTIONS
#define JobObjectSecurityLimitInformation 5 // JOBOBJECT_SECURITY_LIMIT_INFORMATION
#define JobObjectEndOfJobTimeInformation 6 // JOBOBJECT_END_OF_JOB_TIME_INFORMATION
#define JobObjectAssociateCompletionPortInformation 7 // JOBOBJECT_ASSOCIATE_COMPLETION_PORT
#define JobObjectBasicAndIoAccountingInformation 8 // JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION
#define JobObjectExtendedLimitInformation 9 // JOBOBJECT_EXTENDED_LIMIT_INFORMATION
#define JobObjectJobSetInformation 10 // JOBOBJECT_JOBSET_INFORMATION
#define JobObjectGroupInformation 11 // USHORT
#define JobObjectNotificationLimitInformation 12 // JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION
#define JobObjectLimitViolationInformation 13 // JOBOBJECT_LIMIT_VIOLATION_INFORMATION
#define JobObjectGroupInformationEx 14 // GROUP_AFFINITY (ARRAY)
#define JobObjectCpuRateControlInformation 15 // JOBOBJECT_CPU_RATE_CONTROL_INFORMATION
#define JobObjectCompletionFilter 16
#define JobObjectCompletionCounter 17
#define JobObjectFreezeInformation 18 // JOBOBJECT_FREEZE_INFORMATION
#define JobObjectExtendedAccountingInformation 19 // JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION
#define JobObjectWakeInformation 20 // JOBOBJECT_WAKE_INFORMATION
#define JobObjectBackgroundInformation 21
#define JobObjectSchedulingRankBiasInformation 22
#define JobObjectTimerVirtualizationInformation 23
#define JobObjectCycleTimeNotification 24
#define JobObjectClearEvent 25
#define JobObjectInterferenceInformation 26 // JOBOBJECT_INTERFERENCE_INFORMATION
#define JobObjectClearPeakJobMemoryUsed 27
#define JobObjectMemoryUsageInformation 28 // JOBOBJECT_MEMORY_USAGE_INFORMATION // JOBOBJECT_MEMORY_USAGE_INFORMATION_V2
#define JobObjectSharedCommit 29
#define JobObjectContainerId 30
#define JobObjectIoRateControlInformation 31
#define JobObjectNetRateControlInformation 32 // JOBOBJECT_NET_RATE_CONTROL_INFORMATION
#define JobObjectNotificationLimitInformation2 33 // JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION_2
#define JobObjectLimitViolationInformation2 34 // JOBOBJECT_LIMIT_VIOLATION_INFORMATION_2
#define JobObjectCreateSilo 35
#define JobObjectSiloBasicInformation 36 // SILOOBJECT_BASIC_INFORMATION
#define JobObjectSiloRootDirectory 37 // SILOOBJECT_ROOT_DIRECTORY
#define JobObjectServerSiloBasicInformation 38 // SERVERSILO_BASIC_INFORMATION
#define JobObjectServerSiloUserSharedData 39 // SILO_USER_SHARED_DATA
#define JobObjectServerSiloInitialize 40
#define JobObjectServerSiloRunningState 41
#define JobObjectIoAttribution 42
#define JobObjectMemoryPartitionInformation 43
#define JobObjectContainerTelemetryId 44
#define JobObjectSiloSystemRoot 45
#define JobObjectEnergyTrackingState 46 // JOBOBJECT_ENERGY_TRACKING_STATE
#define JobObjectThreadImpersonationInformation 47
#define MaxJobObjectInfoClass 48

// private
typedef struct _JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION
{
    JOBOBJECT_BASIC_ACCOUNTING_INFORMATION BasicInfo;
    IO_COUNTERS IoInfo;
    PROCESS_DISK_COUNTERS DiskIoInfo;
    ULONG64 ContextSwitches;
    LARGE_INTEGER TotalCycleTime;
    ULONG64 ReadyTime;
    PROCESS_ENERGY_VALUES EnergyValues;
} JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION, *PJOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION;

// private
typedef struct _JOBOBJECT_WAKE_INFORMATION
{
    HANDLE NotificationChannel;
    ULONG64 WakeCounters[7];
} JOBOBJECT_WAKE_INFORMATION, *PJOBOBJECT_WAKE_INFORMATION;

// private
typedef struct _JOBOBJECT_WAKE_INFORMATION_V1
{
    HANDLE NotificationChannel;
    ULONG64 WakeCounters[4];
} JOBOBJECT_WAKE_INFORMATION_V1, *PJOBOBJECT_WAKE_INFORMATION_V1;

// private
typedef struct _JOBOBJECT_INTERFERENCE_INFORMATION
{
    ULONG64 Count;
} JOBOBJECT_INTERFERENCE_INFORMATION, *PJOBOBJECT_INTERFERENCE_INFORMATION;

// private
typedef struct _JOBOBJECT_WAKE_FILTER
{
    ULONG HighEdgeFilter;
    ULONG LowEdgeFilter;
} JOBOBJECT_WAKE_FILTER, *PJOBOBJECT_WAKE_FILTER;

// private
typedef struct _JOBOBJECT_FREEZE_INFORMATION
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG FreezeOperation : 1;
            ULONG FilterOperation : 1;
            ULONG SwapOperation : 1;
            ULONG Reserved : 29;
        };
    };
    BOOLEAN Freeze;
    BOOLEAN Swap;
    UCHAR Reserved0[2];
    JOBOBJECT_WAKE_FILTER WakeFilter;
} JOBOBJECT_FREEZE_INFORMATION, *PJOBOBJECT_FREEZE_INFORMATION;

// private
typedef struct _JOBOBJECT_MEMORY_USAGE_INFORMATION
{
    ULONG64 JobMemory;
    ULONG64 PeakJobMemoryUsed;
} JOBOBJECT_MEMORY_USAGE_INFORMATION, *PJOBOBJECT_MEMORY_USAGE_INFORMATION;

// private
typedef struct _JOBOBJECT_MEMORY_USAGE_INFORMATION_V2
{
    JOBOBJECT_MEMORY_USAGE_INFORMATION BasicInfo;
    ULONG64 JobSharedMemory;
    ULONG64 Reserved[2];
} JOBOBJECT_MEMORY_USAGE_INFORMATION_V2, *PJOBOBJECT_MEMORY_USAGE_INFORMATION_V2;

// private
typedef struct _SILO_USER_SHARED_DATA
{
    ULONG64 ServiceSessionId;
    ULONG ActiveConsoleId;
    LONGLONG ConsoleSessionForegroundProcessId;
    NT_PRODUCT_TYPE NtProductType;
    ULONG SuiteMask;
    ULONG SharedUserSessionId;
    BOOLEAN IsMultiSessionSku;
    WCHAR NtSystemRoot[260];
    USHORT UserModeGlobalLogger[16];
} SILO_USER_SHARED_DATA, *PSILO_USER_SHARED_DATA;

// private
typedef struct _SILOOBJECT_ROOT_DIRECTORY
{
    ULONG ControlFlags;
    UNICODE_STRING Path;
} SILOOBJECT_ROOT_DIRECTORY, *PSILOOBJECT_ROOT_DIRECTORY;

// private
typedef struct _JOBOBJECT_ENERGY_TRACKING_STATE
{
    ULONG64 Value;
    ULONG UpdateMask;
    ULONG DesiredState;
} JOBOBJECT_ENERGY_TRACKING_STATE, *PJOBOBJECT_ENERGY_TRACKING_STATE;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAssignProcessToJobObject(
    _In_ HANDLE JobHandle,
    _In_ HANDLE ProcessHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAssignProcessToJobObject(
    _In_ HANDLE JobHandle,
    _In_ HANDLE ProcessHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtTerminateJobObject(
    _In_ HANDLE JobHandle,
    _In_ NTSTATUS ExitStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTerminateJobObject(
    _In_ HANDLE JobHandle,
    _In_ NTSTATUS ExitStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtIsProcessInJob(
    _In_ HANDLE ProcessHandle,
    _In_opt_ HANDLE JobHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwIsProcessInJob(
    _In_ HANDLE ProcessHandle,
    _In_opt_ HANDLE JobHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationJobObject(
    _In_opt_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _Out_writes_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationJobObject(
    _In_opt_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _Out_writes_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationJobObject(
    _In_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _In_reads_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationJobObject(
    _In_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _In_reads_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateJobSet(
    _In_ ULONG NumJob,
    _In_reads_(NumJob) PJOB_SET_ARRAY UserJobSet,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateJobSet(
    _In_ ULONG NumJob,
    _In_reads_(NumJob) PJOB_SET_ARRAY UserJobSet,
    _In_ ULONG Flags
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRevertContainerImpersonation(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRevertContainerImpersonation(
    VOID
    );
#endif

// Reserve objects

// private
typedef enum _MEMORY_RESERVE_TYPE
{
    MemoryReserveUserApc,
    MemoryReserveIoCompletion,
    MemoryReserveTypeMax
} MEMORY_RESERVE_TYPE;

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateReserveObject(
    _Out_ PHANDLE MemoryReserveHandle,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ MEMORY_RESERVE_TYPE Type
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAllocateReserveObject(
    _Out_ PHANDLE MemoryReserveHandle,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ MEMORY_RESERVE_TYPE Type
    );
#endif
 


#include <cfg.h>
// #include <ntdbg.h>
// Debugging

NTSYSAPI
VOID
NTAPI
DbgUserBreakPoint(
    VOID
    );

NTSYSAPI
VOID
NTAPI
DbgBreakPoint(
    VOID
    );

NTSYSAPI
VOID
NTAPI
DbgBreakPointWithStatus(
    _In_ ULONG Status
    );

#define DBG_STATUS_CONTROL_C 1
#define DBG_STATUS_SYSRQ 2
#define DBG_STATUS_BUGCHECK_FIRST 3
#define DBG_STATUS_BUGCHECK_SECOND 4
#define DBG_STATUS_FATAL 5
#define DBG_STATUS_DEBUG_CONTROL 6
#define DBG_STATUS_WORKER 7

NTSYSAPI
ULONG
STDAPIVCALLTYPE
DbgPrint(
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...
    );

NTSYSAPI
ULONG
STDAPIVCALLTYPE
DbgPrintEx(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...
    );

NTSYSAPI
ULONG
NTAPI
vDbgPrintEx(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCCH Format,
    _In_ va_list arglist
    );

NTSYSAPI
ULONG
NTAPI
vDbgPrintExWithPrefix(
    _In_z_ PCCH Prefix,
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCCH Format,
    _In_ va_list arglist
    );

NTSYSAPI
NTSTATUS
NTAPI
DbgQueryDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level
    );

NTSYSAPI
NTSTATUS
NTAPI
DbgSetDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State
    );

NTSYSAPI
ULONG
NTAPI
DbgPrompt(
    _In_ PCCH Prompt,
    _Out_writes_bytes_(Length) PCH Response,
    _In_ ULONG Length
    );

// Definitions

typedef struct _DBGKM_EXCEPTION
{
    EXCEPTION_RECORD ExceptionRecord;
    ULONG FirstChance;
} DBGKM_EXCEPTION, *PDBGKM_EXCEPTION;

typedef struct _DBGKM_CREATE_THREAD
{
    ULONG SubSystemKey;
    PVOID StartAddress;
} DBGKM_CREATE_THREAD, *PDBGKM_CREATE_THREAD;

typedef struct _DBGKM_CREATE_PROCESS
{
    ULONG SubSystemKey;
    HANDLE FileHandle;
    PVOID BaseOfImage;
    ULONG DebugInfoFileOffset;
    ULONG DebugInfoSize;
    DBGKM_CREATE_THREAD InitialThread;
} DBGKM_CREATE_PROCESS, *PDBGKM_CREATE_PROCESS;

typedef struct _DBGKM_EXIT_THREAD
{
    NTSTATUS ExitStatus;
} DBGKM_EXIT_THREAD, *PDBGKM_EXIT_THREAD;

typedef struct _DBGKM_EXIT_PROCESS
{
    NTSTATUS ExitStatus;
} DBGKM_EXIT_PROCESS, *PDBGKM_EXIT_PROCESS;

typedef struct _DBGKM_LOAD_DLL
{
    HANDLE FileHandle;
    PVOID BaseOfDll;
    ULONG DebugInfoFileOffset;
    ULONG DebugInfoSize;
    PVOID NamePointer;
} DBGKM_LOAD_DLL, *PDBGKM_LOAD_DLL;

typedef struct _DBGKM_UNLOAD_DLL
{
    PVOID BaseAddress;
} DBGKM_UNLOAD_DLL, *PDBGKM_UNLOAD_DLL;

typedef enum _DBG_STATE
{
    DbgIdle,
    DbgReplyPending,
    DbgCreateThreadStateChange,
    DbgCreateProcessStateChange,
    DbgExitThreadStateChange,
    DbgExitProcessStateChange,
    DbgExceptionStateChange,
    DbgBreakpointStateChange,
    DbgSingleStepStateChange,
    DbgLoadDllStateChange,
    DbgUnloadDllStateChange
} DBG_STATE, *PDBG_STATE;

typedef struct _DBGUI_CREATE_THREAD
{
    HANDLE HandleToThread;
    DBGKM_CREATE_THREAD NewThread;
} DBGUI_CREATE_THREAD, *PDBGUI_CREATE_THREAD;

typedef struct _DBGUI_CREATE_PROCESS
{
    HANDLE HandleToProcess;
    HANDLE HandleToThread;
    DBGKM_CREATE_PROCESS NewProcess;
} DBGUI_CREATE_PROCESS, *PDBGUI_CREATE_PROCESS;

typedef struct _DBGUI_WAIT_STATE_CHANGE
{
    DBG_STATE NewState;
    CLIENT_ID AppClientId;
    union
    {
        DBGKM_EXCEPTION Exception;
        DBGUI_CREATE_THREAD CreateThread;
        DBGUI_CREATE_PROCESS CreateProcessInfo;
        DBGKM_EXIT_THREAD ExitThread;
        DBGKM_EXIT_PROCESS ExitProcess;
        DBGKM_LOAD_DLL LoadDll;
        DBGKM_UNLOAD_DLL UnloadDll;
    } StateInfo;
} DBGUI_WAIT_STATE_CHANGE, *PDBGUI_WAIT_STATE_CHANGE;

#define DEBUG_READ_EVENT 0x0001
#define DEBUG_PROCESS_ASSIGN 0x0002
#define DEBUG_SET_INFORMATION 0x0004
#define DEBUG_QUERY_INFORMATION 0x0008
#define DEBUG_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | \
    DEBUG_READ_EVENT | DEBUG_PROCESS_ASSIGN | DEBUG_SET_INFORMATION | \
    DEBUG_QUERY_INFORMATION)

#define DEBUG_KILL_ON_CLOSE 0x1

typedef enum _DEBUGOBJECTINFOCLASS
{
    DebugObjectUnusedInformation,
    DebugObjectKillProcessOnExitInformation,
    MaxDebugObjectInfoClass
} DEBUGOBJECTINFOCLASS, *PDEBUGOBJECTINFOCLASS;

// System calls

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateDebugObject(
    _Out_ PHANDLE DebugObjectHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateDebugObject(
    _Out_ PHANDLE DebugObjectHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDebugActiveProcess(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE DebugObjectHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDebugActiveProcess(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE DebugObjectHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDebugContinue(
    _In_ HANDLE DebugObjectHandle,
    _In_ PCLIENT_ID ClientId,
    _In_ NTSTATUS ContinueStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDebugContinue(
    _In_ HANDLE DebugObjectHandle,
    _In_ PCLIENT_ID ClientId,
    _In_ NTSTATUS ContinueStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRemoveProcessDebug(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE DebugObjectHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRemoveProcessDebug(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE DebugObjectHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationDebugObject(
    _In_ HANDLE DebugObjectHandle,
    _In_ DEBUGOBJECTINFOCLASS DebugObjectInformationClass,
    _In_ PVOID DebugInformation,
    _In_ ULONG DebugInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationDebugObject(
    _In_ HANDLE DebugObjectHandle,
    _In_ DEBUGOBJECTINFOCLASS DebugObjectInformationClass,
    _In_ PVOID DebugInformation,
    _In_ ULONG DebugInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForDebugEvent(
    _In_ HANDLE DebugObjectHandle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_ PDBGUI_WAIT_STATE_CHANGE WaitStateChange
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWaitForDebugEvent(
    _In_ HANDLE DebugObjectHandle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_ PDBGUI_WAIT_STATE_CHANGE WaitStateChange
    );

// Debugging UI

NTSYSAPI
NTSTATUS
NTAPI
DbgUiConnectToDbg(
    VOID
    );

NTSYSAPI
HANDLE
NTAPI
DbgUiGetThreadDebugObject(
    VOID
    );

NTSYSAPI
VOID
NTAPI
DbgUiSetThreadDebugObject(
    _In_ HANDLE DebugObject
    );

NTSYSAPI
NTSTATUS
NTAPI
DbgUiWaitStateChange(
    _Out_ PDBGUI_WAIT_STATE_CHANGE StateChange,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSAPI
NTSTATUS
NTAPI
DbgUiContinue(
    _In_ PCLIENT_ID AppClientId,
    _In_ NTSTATUS ContinueStatus
    );

NTSYSAPI
NTSTATUS
NTAPI
DbgUiStopDebugging(
    _In_ HANDLE Process
    );

NTSYSAPI
NTSTATUS
NTAPI
DbgUiDebugActiveProcess(
    _In_ HANDLE Process
    );

NTSYSAPI
VOID
NTAPI
DbgUiRemoteBreakin(
    _In_ PVOID Context
    );

NTSYSAPI
NTSTATUS
NTAPI
DbgUiIssueRemoteBreakin(
    _In_ HANDLE Process
    );

NTSYSAPI
NTSTATUS
NTAPI
DbgUiConvertStateChangeStructure(
    _In_ PDBGUI_WAIT_STATE_CHANGE StateChange,
    _Out_ LPDEBUG_EVENT DebugEvent
    );

struct _EVENT_FILTER_DESCRIPTOR;

typedef VOID (NTAPI *PENABLECALLBACK)(
    _In_ LPCGUID SourceId,
    _In_ ULONG IsEnabled,
    _In_ UCHAR Level,
    _In_ ULONGLONG MatchAnyKeyword,
    _In_ ULONGLONG MatchAllKeyword,
    _In_opt_ struct _EVENT_FILTER_DESCRIPTOR *FilterData,
    _Inout_opt_ PVOID CallbackContext
    );

typedef ULONGLONG REGHANDLE, *PREGHANDLE;

NTSYSAPI
NTSTATUS
NTAPI
EtwEventRegister(
    _In_ LPCGUID ProviderId,
    _In_opt_ PENABLECALLBACK EnableCallback,
    _In_opt_ PVOID CallbackContext,
    _Out_ PREGHANDLE RegHandle
    );
 

// #include <ntioapi.h>
// Create disposition

#define FILE_SUPERSEDE 0x00000000
#define FILE_OPEN 0x00000001
#define FILE_CREATE 0x00000002
#define FILE_OPEN_IF 0x00000003
#define FILE_OVERWRITE 0x00000004
#define FILE_OVERWRITE_IF 0x00000005
#define FILE_MAXIMUM_DISPOSITION 0x00000005

// Create/open flags

#define FILE_DIRECTORY_FILE 0x00000001
#define FILE_WRITE_THROUGH 0x00000002
#define FILE_SEQUENTIAL_ONLY 0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING 0x00000008

#define FILE_SYNCHRONOUS_IO_ALERT 0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT 0x00000020
#define FILE_NON_DIRECTORY_FILE 0x00000040
#define FILE_CREATE_TREE_CONNECTION 0x00000080

#define FILE_COMPLETE_IF_OPLOCKED 0x00000100
#define FILE_NO_EA_KNOWLEDGE 0x00000200
#define FILE_OPEN_FOR_RECOVERY 0x00000400
#define FILE_RANDOM_ACCESS 0x00000800

#define FILE_DELETE_ON_CLOSE 0x00001000
#define FILE_OPEN_BY_FILE_ID 0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT 0x00004000
#define FILE_NO_COMPRESSION 0x00008000
#if (NTDDI_VERSION >= NTDDI_WIN7)
#define FILE_OPEN_REQUIRING_OPLOCK 0x00010000
#define FILE_DISALLOW_EXCLUSIVE 0x00020000
#endif
#if (NTDDI_VERSION >= NTDDI_WIN8)
#define FILE_SESSION_AWARE 0x00040000
#endif

#define FILE_RESERVE_OPFILTER 0x00100000
#define FILE_OPEN_REPARSE_POINT 0x00200000
#define FILE_OPEN_NO_RECALL 0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY 0x00800000

#define FILE_COPY_STRUCTURED_STORAGE 0x00000041
#define FILE_STRUCTURED_STORAGE 0x00000441

// I/O status information values for NtCreateFile/NtOpenFile

#define FILE_SUPERSEDED 0x00000000
#define FILE_OPENED 0x00000001
#define FILE_CREATED 0x00000002
#define FILE_OVERWRITTEN 0x00000003
#define FILE_EXISTS 0x00000004
#define FILE_DOES_NOT_EXIST 0x00000005

// Special ByteOffset parameters

#define FILE_WRITE_TO_END_OF_FILE 0xffffffff
#define FILE_USE_FILE_POINTER_POSITION 0xfffffffe

// Alignment requirement values

#define FILE_BYTE_ALIGNMENT 0x00000000
#define FILE_WORD_ALIGNMENT 0x00000001
#define FILE_LONG_ALIGNMENT 0x00000003
#define FILE_QUAD_ALIGNMENT 0x00000007
#define FILE_OCTA_ALIGNMENT 0x0000000f
#define FILE_32_BYTE_ALIGNMENT 0x0000001f
#define FILE_64_BYTE_ALIGNMENT 0x0000003f
#define FILE_128_BYTE_ALIGNMENT 0x0000007f
#define FILE_256_BYTE_ALIGNMENT 0x000000ff
#define FILE_512_BYTE_ALIGNMENT 0x000001ff

// Maximum length of a filename string

#define MAXIMUM_FILENAME_LENGTH 256

// Extended attributes

#define FILE_NEED_EA 0x00000080

#define FILE_EA_TYPE_BINARY 0xfffe
#define FILE_EA_TYPE_ASCII 0xfffd
#define FILE_EA_TYPE_BITMAP 0xfffb
#define FILE_EA_TYPE_METAFILE 0xfffa
#define FILE_EA_TYPE_ICON 0xfff9
#define FILE_EA_TYPE_EA 0xffee
#define FILE_EA_TYPE_MVMT 0xffdf
#define FILE_EA_TYPE_MVST 0xffde
#define FILE_EA_TYPE_ASN1 0xffdd
#define FILE_EA_TYPE_FAMILY_IDS 0xff01

// Device characteristics

#define FILE_REMOVABLE_MEDIA 0x00000001
#define FILE_READ_ONLY_DEVICE 0x00000002
#define FILE_FLOPPY_DISKETTE 0x00000004
#define FILE_WRITE_ONCE_MEDIA 0x00000008
#define FILE_REMOTE_DEVICE 0x00000010
#define FILE_DEVICE_IS_MOUNTED 0x00000020
#define FILE_VIRTUAL_VOLUME 0x00000040
#define FILE_AUTOGENERATED_DEVICE_NAME 0x00000080
#define FILE_DEVICE_SECURE_OPEN 0x00000100
#define FILE_CHARACTERISTIC_PNP_DEVICE 0x00000800
#define FILE_CHARACTERISTIC_TS_DEVICE 0x00001000
#define FILE_CHARACTERISTIC_WEBDAV_DEVICE 0x00002000
#define FILE_CHARACTERISTIC_CSV 0x00010000
#define FILE_DEVICE_ALLOW_APPCONTAINER_TRAVERSAL 0x00020000
#define FILE_PORTABLE_DEVICE 0x00040000

// Named pipe values

// NamedPipeType for NtCreateNamedPipeFile
#define FILE_PIPE_BYTE_STREAM_TYPE 0x00000000
#define FILE_PIPE_MESSAGE_TYPE 0x00000001
#define FILE_PIPE_ACCEPT_REMOTE_CLIENTS 0x00000000
#define FILE_PIPE_REJECT_REMOTE_CLIENTS 0x00000002
#define FILE_PIPE_TYPE_VALID_MASK 0x00000003

// CompletionMode for NtCreateNamedPipeFile
#define FILE_PIPE_QUEUE_OPERATION 0x00000000
#define FILE_PIPE_COMPLETE_OPERATION 0x00000001

// ReadMode for NtCreateNamedPipeFile
#define FILE_PIPE_BYTE_STREAM_MODE 0x00000000
#define FILE_PIPE_MESSAGE_MODE 0x00000001

// NamedPipeConfiguration for NtQueryInformationFile
#define FILE_PIPE_INBOUND 0x00000000
#define FILE_PIPE_OUTBOUND 0x00000001
#define FILE_PIPE_FULL_DUPLEX 0x00000002

// NamedPipeState for NtQueryInformationFile
#define FILE_PIPE_DISCONNECTED_STATE 0x00000001
#define FILE_PIPE_LISTENING_STATE 0x00000002
#define FILE_PIPE_CONNECTED_STATE 0x00000003
#define FILE_PIPE_CLOSING_STATE 0x00000004

// NamedPipeEnd for NtQueryInformationFile
#define FILE_PIPE_CLIENT_END 0x00000000
#define FILE_PIPE_SERVER_END 0x00000001

// Win32 pipe instance limit (0xff)
#define FILE_PIPE_UNLIMITED_INSTANCES 0xffffffff 

// Mailslot values

#define MAILSLOT_SIZE_AUTO 0

typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID Pointer;
    };
    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef VOID (NTAPI *PIO_APC_ROUTINE)(
    _In_ PVOID ApcContext,
    _In_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG Reserved
    );

// private
typedef struct _FILE_IO_COMPLETION_INFORMATION
{
    PVOID KeyContext;
    PVOID ApcContext;
    IO_STATUS_BLOCK IoStatusBlock;
} FILE_IO_COMPLETION_INFORMATION, *PFILE_IO_COMPLETION_INFORMATION;

typedef enum _FILE_INFORMATION_CLASS
{
    FileDirectoryInformation = 1, // FILE_DIRECTORY_INFORMATION
    FileFullDirectoryInformation, // FILE_FULL_DIR_INFORMATION
    FileBothDirectoryInformation, // FILE_BOTH_DIR_INFORMATION
    FileBasicInformation, // FILE_BASIC_INFORMATION
    FileStandardInformation, // FILE_STANDARD_INFORMATION
    FileInternalInformation, // FILE_INTERNAL_INFORMATION
    FileEaInformation, // FILE_EA_INFORMATION
    FileAccessInformation, // FILE_ACCESS_INFORMATION
    FileNameInformation, // FILE_NAME_INFORMATION
    FileRenameInformation, // FILE_RENAME_INFORMATION // 10
    FileLinkInformation, // FILE_LINK_INFORMATION
    FileNamesInformation, // FILE_NAMES_INFORMATION
    FileDispositionInformation, // FILE_DISPOSITION_INFORMATION
    FilePositionInformation, // FILE_POSITION_INFORMATION
    FileFullEaInformation, // FILE_FULL_EA_INFORMATION
    FileModeInformation, // FILE_MODE_INFORMATION
    FileAlignmentInformation, // FILE_ALIGNMENT_INFORMATION
    FileAllInformation, // FILE_ALL_INFORMATION
    FileAllocationInformation, // FILE_ALLOCATION_INFORMATION
    FileEndOfFileInformation, // FILE_END_OF_FILE_INFORMATION // 20
    FileAlternateNameInformation, // FILE_NAME_INFORMATION
    FileStreamInformation, // FILE_STREAM_INFORMATION
    FilePipeInformation, // FILE_PIPE_INFORMATION
    FilePipeLocalInformation, // FILE_PIPE_LOCAL_INFORMATION
    FilePipeRemoteInformation, // FILE_PIPE_REMOTE_INFORMATION
    FileMailslotQueryInformation, // FILE_MAILSLOT_QUERY_INFORMATION
    FileMailslotSetInformation, // FILE_MAILSLOT_SET_INFORMATION
    FileCompressionInformation, // FILE_COMPRESSION_INFORMATION
    FileObjectIdInformation, // FILE_OBJECTID_INFORMATION
    FileCompletionInformation, // FILE_COMPLETION_INFORMATION // 30
    FileMoveClusterInformation, // FILE_MOVE_CLUSTER_INFORMATION
    FileQuotaInformation, // FILE_QUOTA_INFORMATION
    FileReparsePointInformation, // FILE_REPARSE_POINT_INFORMATION
    FileNetworkOpenInformation, // FILE_NETWORK_OPEN_INFORMATION
    FileAttributeTagInformation, // FILE_ATTRIBUTE_TAG_INFORMATION
    FileTrackingInformation, // FILE_TRACKING_INFORMATION
    FileIdBothDirectoryInformation, // FILE_ID_BOTH_DIR_INFORMATION
    FileIdFullDirectoryInformation, // FILE_ID_FULL_DIR_INFORMATION
    FileValidDataLengthInformation, // FILE_VALID_DATA_LENGTH_INFORMATION
    FileShortNameInformation, // FILE_NAME_INFORMATION // 40
    FileIoCompletionNotificationInformation, // FILE_IO_COMPLETION_NOTIFICATION_INFORMATION // since VISTA
    FileIoStatusBlockRangeInformation, // FILE_IOSTATUSBLOCK_RANGE_INFORMATION
    FileIoPriorityHintInformation, // FILE_IO_PRIORITY_HINT_INFORMATION, FILE_IO_PRIORITY_HINT_INFORMATION_EX
    FileSfioReserveInformation, // FILE_SFIO_RESERVE_INFORMATION
    FileSfioVolumeInformation, // FILE_SFIO_VOLUME_INFORMATION
    FileHardLinkInformation, // FILE_LINKS_INFORMATION
    FileProcessIdsUsingFileInformation, // FILE_PROCESS_IDS_USING_FILE_INFORMATION
    FileNormalizedNameInformation, // FILE_NAME_INFORMATION
    FileNetworkPhysicalNameInformation, // FILE_NETWORK_PHYSICAL_NAME_INFORMATION
    FileIdGlobalTxDirectoryInformation, // FILE_ID_GLOBAL_TX_DIR_INFORMATION // since WIN7 // 50
    FileIsRemoteDeviceInformation, // FILE_IS_REMOTE_DEVICE_INFORMATION
    FileUnusedInformation,
    FileNumaNodeInformation, // FILE_NUMA_NODE_INFORMATION
    FileStandardLinkInformation, // FILE_STANDARD_LINK_INFORMATION
    FileRemoteProtocolInformation, // FILE_REMOTE_PROTOCOL_INFORMATION
    FileRenameInformationBypassAccessCheck, // (kernel-mode only); FILE_RENAME_INFORMATION // since WIN8
    FileLinkInformationBypassAccessCheck, // (kernel-mode only); FILE_LINK_INFORMATION
    FileVolumeNameInformation, // FILE_VOLUME_NAME_INFORMATION
    FileIdInformation, // FILE_ID_INFORMATION
    FileIdExtdDirectoryInformation, // FILE_ID_EXTD_DIR_INFORMATION // 60
    FileReplaceCompletionInformation, // FILE_COMPLETION_INFORMATION // since WINBLUE
    FileHardLinkFullIdInformation, // FILE_LINK_ENTRY_FULL_ID_INFORMATION
    FileIdExtdBothDirectoryInformation, // FILE_ID_EXTD_BOTH_DIR_INFORMATION // since THRESHOLD
    FileDispositionInformationEx, // FILE_DISPOSITION_INFO_EX // since REDSTONE
    FileRenameInformationEx, // FILE_RENAME_INFORMATION_EX
    FileRenameInformationExBypassAccessCheck, // (kernel-mode only); FILE_RENAME_INFORMATION_EX
    FileDesiredStorageClassInformation, // FILE_DESIRED_STORAGE_CLASS_INFORMATION // since REDSTONE2
    FileStatInformation, // FILE_STAT_INFORMATION
    FileMemoryPartitionInformation, // FILE_MEMORY_PARTITION_INFORMATION // since REDSTONE3
    FileStatLxInformation, // FILE_STAT_LX_INFORMATION // since REDSTONE4 // 70
    FileCaseSensitiveInformation, // FILE_CASE_SENSITIVE_INFORMATION
    FileLinkInformationEx, // FILE_LINK_INFORMATION_EX // since REDSTONE5
    FileLinkInformationExBypassAccessCheck, // (kernel-mode only); FILE_LINK_INFORMATION_EX
    FileStorageReserveIdInformation, // FILE_SET_STORAGE_RESERVE_ID_INFORMATION
    FileCaseSensitiveInformationForceAccessCheck, // FILE_CASE_SENSITIVE_INFORMATION
    FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

// NtQueryInformationFile/NtSetInformationFile types

typedef struct _FILE_BASIC_INFORMATION
{
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    ULONG FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef struct _FILE_STANDARD_INFORMATION
{
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG NumberOfLinks;
    BOOLEAN DeletePending;
    BOOLEAN Directory;
} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

typedef struct _FILE_STANDARD_INFORMATION_EX
{
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG NumberOfLinks;
    BOOLEAN DeletePending;
    BOOLEAN Directory;
    BOOLEAN AlternateStream;
    BOOLEAN MetadataAttribute;
} FILE_STANDARD_INFORMATION_EX, *PFILE_STANDARD_INFORMATION_EX;

typedef struct _FILE_INTERNAL_INFORMATION
{
    LARGE_INTEGER IndexNumber;
} FILE_INTERNAL_INFORMATION, *PFILE_INTERNAL_INFORMATION;

typedef struct _FILE_EA_INFORMATION
{
    ULONG EaSize;
} FILE_EA_INFORMATION, *PFILE_EA_INFORMATION;

typedef struct _FILE_ACCESS_INFORMATION
{
    ACCESS_MASK AccessFlags;
} FILE_ACCESS_INFORMATION, *PFILE_ACCESS_INFORMATION;

typedef struct _FILE_POSITION_INFORMATION
{
    LARGE_INTEGER CurrentByteOffset;
} FILE_POSITION_INFORMATION, *PFILE_POSITION_INFORMATION;

typedef struct _FILE_MODE_INFORMATION
{
    ULONG Mode;
} FILE_MODE_INFORMATION, *PFILE_MODE_INFORMATION;

typedef struct _FILE_ALIGNMENT_INFORMATION
{
    ULONG AlignmentRequirement;
} FILE_ALIGNMENT_INFORMATION, *PFILE_ALIGNMENT_INFORMATION;

typedef struct _FILE_NAME_INFORMATION
{
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;

typedef struct _FILE_ALL_INFORMATION
{
    FILE_BASIC_INFORMATION BasicInformation;
    FILE_STANDARD_INFORMATION StandardInformation;
    FILE_INTERNAL_INFORMATION InternalInformation;
    FILE_EA_INFORMATION EaInformation;
    FILE_ACCESS_INFORMATION AccessInformation;
    FILE_POSITION_INFORMATION PositionInformation;
    FILE_MODE_INFORMATION ModeInformation;
    FILE_ALIGNMENT_INFORMATION AlignmentInformation;
    FILE_NAME_INFORMATION NameInformation;
} FILE_ALL_INFORMATION, *PFILE_ALL_INFORMATION;

typedef struct _FILE_NETWORK_OPEN_INFORMATION
{
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG FileAttributes;
} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;

typedef struct _FILE_ATTRIBUTE_TAG_INFORMATION
{
    ULONG FileAttributes;
    ULONG ReparseTag;
} FILE_ATTRIBUTE_TAG_INFORMATION, *PFILE_ATTRIBUTE_TAG_INFORMATION;

typedef struct _FILE_ALLOCATION_INFORMATION
{
    LARGE_INTEGER AllocationSize;
} FILE_ALLOCATION_INFORMATION, *PFILE_ALLOCATION_INFORMATION;

typedef struct _FILE_COMPRESSION_INFORMATION
{
    LARGE_INTEGER CompressedFileSize;
    USHORT CompressionFormat;
    UCHAR CompressionUnitShift;
    UCHAR ChunkShift;
    UCHAR ClusterShift;
    UCHAR Reserved[3];
} FILE_COMPRESSION_INFORMATION, *PFILE_COMPRESSION_INFORMATION;

typedef struct _FILE_DISPOSITION_INFORMATION
{
    BOOLEAN DeleteFile;
} FILE_DISPOSITION_INFORMATION, *PFILE_DISPOSITION_INFORMATION;

typedef struct _FILE_END_OF_FILE_INFORMATION
{
    LARGE_INTEGER EndOfFile;
} FILE_END_OF_FILE_INFORMATION, *PFILE_END_OF_FILE_INFORMATION;

typedef struct _FILE_VALID_DATA_LENGTH_INFORMATION
{
    LARGE_INTEGER ValidDataLength;
} FILE_VALID_DATA_LENGTH_INFORMATION, *PFILE_VALID_DATA_LENGTH_INFORMATION;

typedef struct _FILE_LINK_INFORMATION
{
    BOOLEAN ReplaceIfExists;
    HANDLE RootDirectory;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_LINK_INFORMATION, *PFILE_LINK_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
#define FILE_LINK_REPLACE_IF_EXISTS 0x00000001
#define FILE_LINK_POSIX_SEMANTICS 0x00000002
#define FILE_LINK_SUPPRESS_STORAGE_RESERVE_INHERITANCE 0x00000008
#define FILE_LINK_NO_INCREASE_AVAILABLE_SPACE 0x00000010
#define FILE_LINK_NO_DECREASE_AVAILABLE_SPACE 0x00000020
#define FILE_LINK_PRESERVE_AVAILABLE_SPACE 0x00000030
#define FILE_LINK_IGNORE_READONLY_ATTRIBUTE 0x00000040
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_19H1)
#define FILE_LINK_FORCE_RESIZE_TARGET_SR 0x00000080
#define FILE_LINK_FORCE_RESIZE_SOURCE_SR 0x00000100
#define FILE_LINK_FORCE_RESIZE_SR 0x00000180
#endif

typedef struct _FILE_LINK_INFORMATION_EX
{
    ULONG Flags;
    HANDLE RootDirectory;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_LINK_INFORMATION_EX, *PFILE_LINK_INFORMATION_EX;

typedef struct _FILE_MOVE_CLUSTER_INFORMATION
{
    ULONG ClusterCount;
    HANDLE RootDirectory;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_MOVE_CLUSTER_INFORMATION, *PFILE_MOVE_CLUSTER_INFORMATION;

typedef struct _FILE_RENAME_INFORMATION
{
    BOOLEAN ReplaceIfExists;
    HANDLE RootDirectory;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
#define FILE_RENAME_REPLACE_IF_EXISTS 0x00000001
#define FILE_RENAME_POSIX_SEMANTICS 0x00000002
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
#define FILE_RENAME_SUPPRESS_PIN_STATE_INHERITANCE 0x00000004
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
#define FILE_RENAME_SUPPRESS_STORAGE_RESERVE_INHERITANCE 0x00000008
#define FILE_RENAME_NO_INCREASE_AVAILABLE_SPACE 0x00000010
#define FILE_RENAME_NO_DECREASE_AVAILABLE_SPACE 0x00000020
#define FILE_RENAME_PRESERVE_AVAILABLE_SPACE 0x00000030
#define FILE_RENAME_IGNORE_READONLY_ATTRIBUTE 0x00000040
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_19H1)
#define FILE_RENAME_FORCE_RESIZE_TARGET_SR 0x00000080
#define FILE_RENAME_FORCE_RESIZE_SOURCE_SR 0x00000100
#define FILE_RENAME_FORCE_RESIZE_SR 0x00000180
#endif

typedef struct _FILE_RENAME_INFORMATION_EX
{
    ULONG Flags;
    HANDLE RootDirectory;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_RENAME_INFORMATION_EX, *PFILE_RENAME_INFORMATION_EX;

typedef struct _FILE_STREAM_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG StreamNameLength;
    LARGE_INTEGER StreamSize;
    LARGE_INTEGER StreamAllocationSize;
    WCHAR StreamName[1];
} FILE_STREAM_INFORMATION, *PFILE_STREAM_INFORMATION;

typedef struct _FILE_TRACKING_INFORMATION
{
    HANDLE DestinationFile;
    ULONG ObjectInformationLength;
    CHAR ObjectInformation[1];
} FILE_TRACKING_INFORMATION, *PFILE_TRACKING_INFORMATION;

typedef struct _FILE_COMPLETION_INFORMATION
{
    HANDLE Port;
    PVOID Key;
} FILE_COMPLETION_INFORMATION, *PFILE_COMPLETION_INFORMATION;

typedef struct _FILE_PIPE_INFORMATION
{
     ULONG ReadMode;
     ULONG CompletionMode;
} FILE_PIPE_INFORMATION, *PFILE_PIPE_INFORMATION;

typedef struct _FILE_PIPE_LOCAL_INFORMATION
{
     ULONG NamedPipeType;
     ULONG NamedPipeConfiguration;
     ULONG MaximumInstances;
     ULONG CurrentInstances;
     ULONG InboundQuota;
     ULONG ReadDataAvailable;
     ULONG OutboundQuota;
     ULONG WriteQuotaAvailable;
     ULONG NamedPipeState;
     ULONG NamedPipeEnd;
} FILE_PIPE_LOCAL_INFORMATION, *PFILE_PIPE_LOCAL_INFORMATION;

typedef struct _FILE_PIPE_REMOTE_INFORMATION
{
     LARGE_INTEGER CollectDataTime;
     ULONG MaximumCollectionCount;
} FILE_PIPE_REMOTE_INFORMATION, *PFILE_PIPE_REMOTE_INFORMATION;

typedef struct _FILE_MAILSLOT_QUERY_INFORMATION
{
    ULONG MaximumMessageSize;
    ULONG MailslotQuota;
    ULONG NextMessageSize;
    ULONG MessagesAvailable;
    LARGE_INTEGER ReadTimeout;
} FILE_MAILSLOT_QUERY_INFORMATION, *PFILE_MAILSLOT_QUERY_INFORMATION;

typedef struct _FILE_MAILSLOT_SET_INFORMATION
{
    PLARGE_INTEGER ReadTimeout;
} FILE_MAILSLOT_SET_INFORMATION, *PFILE_MAILSLOT_SET_INFORMATION;

typedef struct _FILE_REPARSE_POINT_INFORMATION
{
    LONGLONG FileReference;
    ULONG Tag;
} FILE_REPARSE_POINT_INFORMATION, *PFILE_REPARSE_POINT_INFORMATION;

typedef struct _FILE_LINK_ENTRY_INFORMATION
{
    ULONG NextEntryOffset;
    LONGLONG ParentFileId; // LARGE_INTEGER
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_LINK_ENTRY_INFORMATION, *PFILE_LINK_ENTRY_INFORMATION;

typedef struct _FILE_LINKS_INFORMATION
{
    ULONG BytesNeeded;
    ULONG EntriesReturned;
    FILE_LINK_ENTRY_INFORMATION Entry;
} FILE_LINKS_INFORMATION, *PFILE_LINKS_INFORMATION;

typedef struct _FILE_NETWORK_PHYSICAL_NAME_INFORMATION
{
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_NETWORK_PHYSICAL_NAME_INFORMATION, *PFILE_NETWORK_PHYSICAL_NAME_INFORMATION;

typedef struct _FILE_STANDARD_LINK_INFORMATION
{
    ULONG NumberOfAccessibleLinks;
    ULONG TotalNumberOfLinks;
    BOOLEAN DeletePending;
    BOOLEAN Directory;
} FILE_STANDARD_LINK_INFORMATION, *PFILE_STANDARD_LINK_INFORMATION;

typedef struct _FILE_SFIO_RESERVE_INFORMATION
{
    ULONG RequestsPerPeriod;
    ULONG Period;
    BOOLEAN RetryFailures;
    BOOLEAN Discardable;
    ULONG RequestSize;
    ULONG NumOutstandingRequests;
} FILE_SFIO_RESERVE_INFORMATION, *PFILE_SFIO_RESERVE_INFORMATION;

typedef struct _FILE_SFIO_VOLUME_INFORMATION
{
    ULONG MaximumRequestsPerPeriod;
    ULONG MinimumPeriod;
    ULONG MinimumTransferSize;
} FILE_SFIO_VOLUME_INFORMATION, *PFILE_SFIO_VOLUME_INFORMATION;

typedef enum _IO_PRIORITY_HINT
{
    IoPriorityVeryLow = 0, // Defragging, content indexing and other background I/Os.
    IoPriorityLow, // Prefetching for applications.
    IoPriorityNormal, // Normal I/Os.
    IoPriorityHigh, // Used by filesystems for checkpoint I/O.
    IoPriorityCritical, // Used by memory manager. Not available for applications.
    MaxIoPriorityTypes
} IO_PRIORITY_HINT;

typedef DECLSPEC_ALIGN(8) struct _FILE_IO_PRIORITY_HINT_INFORMATION
{
    IO_PRIORITY_HINT PriorityHint;
} FILE_IO_PRIORITY_HINT_INFORMATION, *PFILE_IO_PRIORITY_HINT_INFORMATION;

typedef struct _FILE_IO_PRIORITY_HINT_INFORMATION_EX
{
    IO_PRIORITY_HINT PriorityHint;
    BOOLEAN BoostOutstanding;
} FILE_IO_PRIORITY_HINT_INFORMATION_EX, *PFILE_IO_PRIORITY_HINT_INFORMATION_EX;

#define FILE_SKIP_COMPLETION_PORT_ON_SUCCESS 0x1
#define FILE_SKIP_SET_EVENT_ON_HANDLE 0x2
#define FILE_SKIP_SET_USER_EVENT_ON_FAST_IO 0x4

typedef struct _FILE_IO_COMPLETION_NOTIFICATION_INFORMATION
{
    ULONG Flags;
} FILE_IO_COMPLETION_NOTIFICATION_INFORMATION, *PFILE_IO_COMPLETION_NOTIFICATION_INFORMATION;

typedef struct _FILE_PROCESS_IDS_USING_FILE_INFORMATION
{
    ULONG NumberOfProcessIdsInList;
    ULONG_PTR ProcessIdList[1];
} FILE_PROCESS_IDS_USING_FILE_INFORMATION, *PFILE_PROCESS_IDS_USING_FILE_INFORMATION;

typedef struct _FILE_IS_REMOTE_DEVICE_INFORMATION
{
    BOOLEAN IsRemote;
} FILE_IS_REMOTE_DEVICE_INFORMATION, *PFILE_IS_REMOTE_DEVICE_INFORMATION;

typedef struct _FILE_NUMA_NODE_INFORMATION
{
    USHORT NodeNumber;
} FILE_NUMA_NODE_INFORMATION, *PFILE_NUMA_NODE_INFORMATION;

typedef struct _FILE_IOSTATUSBLOCK_RANGE_INFORMATION
{
    PUCHAR IoStatusBlockRange;
    ULONG Length;
} FILE_IOSTATUSBLOCK_RANGE_INFORMATION, *PFILE_IOSTATUSBLOCK_RANGE_INFORMATION;

typedef struct _FILE_REMOTE_PROTOCOL_INFORMATION
{
    USHORT StructureVersion; // 1
    USHORT StructureSize;

    ULONG Protocol; // WNNC_NET_*

    USHORT ProtocolMajorVersion;
    USHORT ProtocolMinorVersion;
    USHORT ProtocolRevision;

    USHORT Reserved;

    // Generic information

    ULONG Flags;

    struct
    {
        ULONG Reserved[8];
    } GenericReserved;

    // Specific information

#if (NTDDI_VERSION < NTDDI_WIN8)
    struct
    {
        ULONG Reserved[16];
    } ProtocolSpecificReserved;
#else
    union
    {
        struct
        {
            struct
            {
                ULONG Capabilities;
            } Server;
            struct
            {
                ULONG Capabilities;
                ULONG CachingFlags;
            } Share;
        } Smb2;
        ULONG Reserved[16];
    } ProtocolSpecific;
#endif
} FILE_REMOTE_PROTOCOL_INFORMATION, *PFILE_REMOTE_PROTOCOL_INFORMATION;

#define CHECKSUM_ENFORCEMENT_OFF 0x00000001

typedef struct _FILE_INTEGRITY_STREAM_INFORMATION
{
    USHORT ChecksumAlgorithm;
    UCHAR ChecksumChunkShift;
    UCHAR ClusterShift;
    ULONG Flags;
} FILE_INTEGRITY_STREAM_INFORMATION, *PFILE_INTEGRITY_STREAM_INFORMATION;

typedef struct _FILE_VOLUME_NAME_INFORMATION
{
    ULONG DeviceNameLength;
    WCHAR DeviceName[1];
} FILE_VOLUME_NAME_INFORMATION, *PFILE_VOLUME_NAME_INFORMATION;

typedef struct _FILE_ID_INFORMATION
{
    ULONGLONG VolumeSerialNumber;
    FILE_ID_128 FileId;
} FILE_ID_INFORMATION, *PFILE_ID_INFORMATION;

typedef struct _FILE_ID_EXTD_DIR_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    ULONG ReparsePointTag;
    FILE_ID_128 FileId;
    WCHAR FileName[1];
} FILE_ID_EXTD_DIR_INFORMATION, *PFILE_ID_EXTD_DIR_INFORMATION;

typedef struct _FILE_LINK_ENTRY_FULL_ID_INFORMATION
{
    ULONG NextEntryOffset;
    FILE_ID_128 ParentFileId;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_LINK_ENTRY_FULL_ID_INFORMATION, *PFILE_LINK_ENTRY_FULL_ID_INFORMATION;

typedef struct _FILE_ID_EXTD_BOTH_DIR_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    ULONG ReparsePointTag;
    FILE_ID_128 FileId;
    CCHAR ShortNameLength;
    WCHAR ShortName[12];
    WCHAR FileName[1];
} FILE_ID_EXTD_BOTH_DIR_INFORMATION, *PFILE_ID_EXTD_BOTH_DIR_INFORMATION;

// private
typedef struct _FILE_STAT_INFORMATION
{
    LARGE_INTEGER FileId;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG FileAttributes;
    ULONG ReparseTag;
    ULONG NumberOfLinks;
    ULONG EffectiveAccess;
} FILE_STAT_INFORMATION, *PFILE_STAT_INFORMATION;

// private
typedef struct _FILE_MEMORY_PARTITION_INFORMATION
{
    HANDLE OwnerPartitionHandle;
    union
    {
        struct
        {
            UCHAR NoCrossPartitionAccess;
            UCHAR Spare[3];
        };
        ULONG AllFlags;
    } Flags;
} FILE_MEMORY_PARTITION_INFORMATION, *PFILE_MEMORY_PARTITION_INFORMATION;

// private
typedef struct _FILE_STAT_LX_INFORMATION
{
    LARGE_INTEGER FileId;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG FileAttributes;
    ULONG ReparseTag;
    ULONG NumberOfLinks;
    ULONG EffectiveAccess;
    ULONG LxFlags;
    ULONG LxUid;
    ULONG LxGid;
    ULONG LxMode;
    ULONG LxDeviceIdMajor;
    ULONG LxDeviceIdMinor;
} FILE_STAT_LX_INFORMATION, *PFILE_STAT_LX_INFORMATION;

// private
typedef struct _FILE_CASE_SENSITIVE_INFORMATION
{
    ULONG Flags;
} FILE_CASE_SENSITIVE_INFORMATION, *PFILE_CASE_SENSITIVE_INFORMATION;

// NtQueryDirectoryFile types

typedef struct _FILE_DIRECTORY_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;

typedef struct _FILE_FULL_DIR_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    WCHAR FileName[1];
} FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

typedef struct _FILE_ID_FULL_DIR_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    LARGE_INTEGER FileId;
    WCHAR FileName[1];
} FILE_ID_FULL_DIR_INFORMATION, *PFILE_ID_FULL_DIR_INFORMATION;

typedef struct _FILE_BOTH_DIR_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    CCHAR ShortNameLength;
    WCHAR ShortName[12];
    WCHAR FileName[1];
} FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;

typedef struct _FILE_ID_BOTH_DIR_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    CCHAR ShortNameLength;
    WCHAR ShortName[12];
    LARGE_INTEGER FileId;
    WCHAR FileName[1];
} FILE_ID_BOTH_DIR_INFORMATION, *PFILE_ID_BOTH_DIR_INFORMATION;

typedef struct _FILE_NAMES_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_NAMES_INFORMATION, *PFILE_NAMES_INFORMATION;

typedef struct _FILE_ID_GLOBAL_TX_DIR_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    LARGE_INTEGER FileId;
    GUID LockingTransactionId;
    ULONG TxInfoFlags;
    WCHAR FileName[1];
} FILE_ID_GLOBAL_TX_DIR_INFORMATION, *PFILE_ID_GLOBAL_TX_DIR_INFORMATION;

#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_WRITELOCKED 0x00000001
#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_VISIBLE_TO_TX 0x00000002
#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_VISIBLE_OUTSIDE_TX 0x00000004

typedef struct _FILE_OBJECTID_INFORMATION
{
    LONGLONG FileReference;
    UCHAR ObjectId[16]; // GUID
    union
    {
        struct
        {
            UCHAR BirthVolumeId[16];
            UCHAR BirthObjectId[16];
            UCHAR DomainId[16];
        };
        UCHAR ExtendedInfo[48];
    };
} FILE_OBJECTID_INFORMATION, *PFILE_OBJECTID_INFORMATION;

// NtQueryEaFile/NtSetEaFile types

typedef struct _FILE_FULL_EA_INFORMATION
{
    ULONG NextEntryOffset;
    UCHAR Flags;
    UCHAR EaNameLength;
    USHORT EaValueLength;
    CHAR EaName[1];
} FILE_FULL_EA_INFORMATION, *PFILE_FULL_EA_INFORMATION;

typedef struct _FILE_GET_EA_INFORMATION
{
    ULONG NextEntryOffset;
    UCHAR EaNameLength;
    CHAR EaName[1];
} FILE_GET_EA_INFORMATION, *PFILE_GET_EA_INFORMATION;

// NtQueryQuotaInformationFile/NtSetQuotaInformationFile types

typedef struct _FILE_GET_QUOTA_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG SidLength;
    SID Sid;
} FILE_GET_QUOTA_INFORMATION, *PFILE_GET_QUOTA_INFORMATION;

typedef struct _FILE_QUOTA_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG SidLength;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER QuotaUsed;
    LARGE_INTEGER QuotaThreshold;
    LARGE_INTEGER QuotaLimit;
    SID Sid;
} FILE_QUOTA_INFORMATION, *PFILE_QUOTA_INFORMATION;

typedef enum _FSINFOCLASS
{
    FileFsVolumeInformation = 1, // FILE_FS_VOLUME_INFORMATION
    FileFsLabelInformation, // FILE_FS_LABEL_INFORMATION
    FileFsSizeInformation, // FILE_FS_SIZE_INFORMATION
    FileFsDeviceInformation, // FILE_FS_DEVICE_INFORMATION
    FileFsAttributeInformation, // FILE_FS_ATTRIBUTE_INFORMATION
    FileFsControlInformation, // FILE_FS_CONTROL_INFORMATION
    FileFsFullSizeInformation, // FILE_FS_FULL_SIZE_INFORMATION
    FileFsObjectIdInformation, // FILE_FS_OBJECTID_INFORMATION
    FileFsDriverPathInformation, // FILE_FS_DRIVER_PATH_INFORMATION
    FileFsVolumeFlagsInformation, // FILE_FS_VOLUME_FLAGS_INFORMATION // 10
    FileFsSectorSizeInformation, // FILE_FS_SECTOR_SIZE_INFORMATION // since WIN8
    FileFsDataCopyInformation, // FILE_FS_DATA_COPY_INFORMATION
    FileFsMetadataSizeInformation, // FILE_FS_METADATA_SIZE_INFORMATION // since THRESHOLD
    FileFsFullSizeInformationEx, // FILE_FS_FULL_SIZE_INFORMATION_EX // since REDSTONE5
    FileFsMaximumInformation
} FSINFOCLASS, *PFSINFOCLASS;

// NtQueryVolumeInformation/NtSetVolumeInformation types

// private
typedef struct _FILE_FS_VOLUME_INFORMATION
{
    LARGE_INTEGER VolumeCreationTime;
    ULONG VolumeSerialNumber;
    ULONG VolumeLabelLength;
    BOOLEAN SupportsObjects;
    WCHAR VolumeLabel[1];
} FILE_FS_VOLUME_INFORMATION, *PFILE_FS_VOLUME_INFORMATION;

// private
typedef struct _FILE_FS_LABEL_INFORMATION
{
    ULONG VolumeLabelLength;
    WCHAR VolumeLabel[1];
} FILE_FS_LABEL_INFORMATION, * PFILE_FS_LABEL_INFORMATION;

// private
typedef struct _FILE_FS_SIZE_INFORMATION
{
    LARGE_INTEGER TotalAllocationUnits;
    LARGE_INTEGER AvailableAllocationUnits;
    ULONG SectorsPerAllocationUnit;
    ULONG BytesPerSector;
} FILE_FS_SIZE_INFORMATION, *PFILE_FS_SIZE_INFORMATION;

// private
typedef struct _FILE_FS_CONTROL_INFORMATION
{
    LARGE_INTEGER FreeSpaceStartFiltering;
    LARGE_INTEGER FreeSpaceThreshold;
    LARGE_INTEGER FreeSpaceStopFiltering;
    LARGE_INTEGER DefaultQuotaThreshold;
    LARGE_INTEGER DefaultQuotaLimit;
    ULONG FileSystemControlFlags;
} FILE_FS_CONTROL_INFORMATION, *PFILE_FS_CONTROL_INFORMATION;

// private
typedef struct _FILE_FS_FULL_SIZE_INFORMATION
{
    LARGE_INTEGER TotalAllocationUnits;
    LARGE_INTEGER CallerAvailableAllocationUnits;
    LARGE_INTEGER ActualAvailableAllocationUnits;
    ULONG SectorsPerAllocationUnit;
    ULONG BytesPerSector;
} FILE_FS_FULL_SIZE_INFORMATION, *PFILE_FS_FULL_SIZE_INFORMATION;

// private
typedef struct _FILE_FS_OBJECTID_INFORMATION
{
    UCHAR ObjectId[16];
    UCHAR ExtendedInfo[48];
} FILE_FS_OBJECTID_INFORMATION, *PFILE_FS_OBJECTID_INFORMATION;

// private
typedef struct _FILE_FS_DEVICE_INFORMATION
{
    DEVICE_TYPE DeviceType;
    ULONG Characteristics;
} FILE_FS_DEVICE_INFORMATION, *PFILE_FS_DEVICE_INFORMATION;

// private
typedef struct _FILE_FS_ATTRIBUTE_INFORMATION
{
    ULONG FileSystemAttributes;
    LONG MaximumComponentNameLength;
    ULONG FileSystemNameLength;
    WCHAR FileSystemName[1];
} FILE_FS_ATTRIBUTE_INFORMATION, *PFILE_FS_ATTRIBUTE_INFORMATION;

// private
typedef struct _FILE_FS_DRIVER_PATH_INFORMATION
{
    BOOLEAN DriverInPath;
    ULONG DriverNameLength;
    WCHAR DriverName[1];
} FILE_FS_DRIVER_PATH_INFORMATION, *PFILE_FS_DRIVER_PATH_INFORMATION;

// private
typedef struct _FILE_FS_VOLUME_FLAGS_INFORMATION
{
    ULONG Flags;
} FILE_FS_VOLUME_FLAGS_INFORMATION, *PFILE_FS_VOLUME_FLAGS_INFORMATION;

#define SSINFO_FLAGS_ALIGNED_DEVICE 0x00000001
#define SSINFO_FLAGS_PARTITION_ALIGNED_ON_DEVICE 0x00000002

// If set for Sector and Partition fields, alignment is not known.
#define SSINFO_OFFSET_UNKNOWN 0xffffffff

typedef struct _FILE_FS_SECTOR_SIZE_INFORMATION
{
    ULONG LogicalBytesPerSector;
    ULONG PhysicalBytesPerSectorForAtomicity;
    ULONG PhysicalBytesPerSectorForPerformance;
    ULONG FileSystemEffectivePhysicalBytesPerSectorForAtomicity;
    ULONG Flags;
    ULONG ByteOffsetForSectorAlignment;
    ULONG ByteOffsetForPartitionAlignment;
} FILE_FS_SECTOR_SIZE_INFORMATION, *PFILE_FS_SECTOR_SIZE_INFORMATION;

// private
typedef struct _FILE_FS_DATA_COPY_INFORMATION
{
    ULONG NumberOfCopies;
} FILE_FS_DATA_COPY_INFORMATION, *PFILE_FS_DATA_COPY_INFORMATION;

// private
typedef struct _FILE_FS_METADATA_SIZE_INFORMATION
{
    LARGE_INTEGER TotalMetadataAllocationUnits;
    ULONG SectorsPerAllocationUnit;
    ULONG BytesPerSector;
} FILE_FS_METADATA_SIZE_INFORMATION, *PFILE_FS_METADATA_SIZE_INFORMATION;

// private
typedef struct _FILE_FS_FULL_SIZE_INFORMATION_EX
{
    ULONGLONG ActualTotalAllocationUnits;
    ULONGLONG ActualAvailableAllocationUnits;
    ULONGLONG ActualPoolUnavailableAllocationUnits;
    ULONGLONG CallerTotalAllocationUnits;
    ULONGLONG CallerAvailableAllocationUnits;
    ULONGLONG CallerPoolUnavailableAllocationUnits;
    ULONGLONG UsedAllocationUnits;
    ULONGLONG TotalReservedAllocationUnits;
    ULONGLONG VolumeStorageReserveAllocationUnits;
    ULONGLONG AvailableCommittedAllocationUnits;
    ULONGLONG PoolAvailableAllocationUnits;
    ULONG SectorsPerAllocationUnit;
    ULONG BytesPerSector;
} FILE_FS_FULL_SIZE_INFORMATION_EX, *PFILE_FS_FULL_SIZE_INFORMATION_EX;

// System calls

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_reads_bytes_opt_(EaLength) PVOID EaBuffer,
    _In_ ULONG EaLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_reads_bytes_opt_(EaLength) PVOID EaBuffer,
    _In_ ULONG EaLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateNamedPipeFile(
    _Out_ PHANDLE FileHandle,
    _In_ ULONG DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_ ULONG NamedPipeType,
    _In_ ULONG ReadMode,
    _In_ ULONG CompletionMode,
    _In_ ULONG MaximumInstances,
    _In_ ULONG InboundQuota,
    _In_ ULONG OutboundQuota,
    _In_opt_ PLARGE_INTEGER DefaultTimeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateNamedPipeFile(
    _Out_ PHANDLE FileHandle,
    _In_ ULONG DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_ ULONG NamedPipeType,
    _In_ ULONG ReadMode,
    _In_ ULONG CompletionMode,
    _In_ ULONG MaximumInstances,
    _In_ ULONG InboundQuota,
    _In_ ULONG OutboundQuota,
    _In_opt_ PLARGE_INTEGER DefaultTimeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateMailslotFile(
    _Out_ PHANDLE FileHandle,
    _In_ ULONG DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CreateOptions,
    _In_ ULONG MailslotQuota,
    _In_ ULONG MaximumMessageSize,
    _In_ PLARGE_INTEGER ReadTimeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateMailslotFile(
    _Out_ PHANDLE FileHandle,
    _In_ ULONG DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CreateOptions,
    _In_ ULONG MailslotQuota,
    _In_ ULONG MaximumMessageSize,
    _In_ PLARGE_INTEGER ReadTimeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG OpenOptions
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG OpenOptions
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushBuffersFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFlushBuffersFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );

#define FLUSH_FLAGS_FILE_DATA_ONLY 0x00000001
#define FLUSH_FLAGS_NO_SYNC 0x00000002
#define FLUSH_FLAGS_FILE_DATA_SYNC_ONLY 0x00000004 // REDSTONE1

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushBuffersFileEx(
    _In_ HANDLE FileHandle,
    _In_ ULONG Flags,
    _In_reads_bytes_(ParametersSize) PVOID Parameters,
    _In_ ULONG ParametersSize,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFlushBuffersFileEx(
    _In_ HANDLE FileHandle,
    _In_ ULONG Flags,
    _In_reads_bytes_(ParametersSize) PVOID Parameters,
    _In_ ULONG ParametersSize,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationByName(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationByName(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDirectoryFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_opt_ PUNICODE_STRING FileName,
    _In_ BOOLEAN RestartScan
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryDirectoryFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_opt_ PUNICODE_STRING FileName,
    _In_ BOOLEAN RestartScan
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDirectoryFileEx(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ ULONG QueryFlags,
    _In_opt_ PUNICODE_STRING FileName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryDirectoryFileEx(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ ULONG QueryFlags,
    _In_opt_ PUNICODE_STRING FileName
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryEaFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_reads_bytes_opt_(EaListLength) PVOID EaList,
    _In_ ULONG EaListLength,
    _In_opt_ PULONG EaIndex,
    _In_ BOOLEAN RestartScan
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryEaFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_reads_bytes_opt_(EaListLength) PVOID EaList,
    _In_ ULONG EaListLength,
    _In_opt_ PULONG EaIndex,
    _In_ BOOLEAN RestartScan
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetEaFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetEaFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryQuotaInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_reads_bytes_opt_(SidListLength) PVOID SidList,
    _In_ ULONG SidListLength,
    _In_opt_ PSID StartSid,
    _In_ BOOLEAN RestartScan
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryQuotaInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_reads_bytes_opt_(SidListLength) PVOID SidList,
    _In_ ULONG SidListLength,
    _In_opt_ PSID StartSid,
    _In_ BOOLEAN RestartScan
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetQuotaInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetQuotaInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryVolumeInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FsInformation,
    _In_ ULONG Length,
    _In_ FSINFOCLASS FsInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryVolumeInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FsInformation,
    _In_ ULONG Length,
    _In_ FSINFOCLASS FsInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetVolumeInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID FsInformation,
    _In_ ULONG Length,
    _In_ FSINFOCLASS FsInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetVolumeInformationFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID FsInformation,
    _In_ ULONG Length,
    _In_ FSINFOCLASS FsInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCancelIoFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCancelIoFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCancelIoFileEx(
    _In_ HANDLE FileHandle,
    _In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCancelIoFileEx(
    _In_ HANDLE FileHandle,
    _In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCancelSynchronousIoFile(
    _In_ HANDLE ThreadHandle,
    _In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCancelSynchronousIoFile(
    _In_ HANDLE ThreadHandle,
    _In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeviceIoControlFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG IoControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeviceIoControlFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG IoControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFsControlFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG FsControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFsControlFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG FsControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReadFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWriteFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWriteFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadFileScatter(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReadFileScatter(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWriteFileGather(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWriteFileGather(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PFILE_SEGMENT_ELEMENT SegmentArray,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLockFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PLARGE_INTEGER ByteOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ ULONG Key,
    _In_ BOOLEAN FailImmediately,
    _In_ BOOLEAN ExclusiveLock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLockFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PLARGE_INTEGER ByteOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ ULONG Key,
    _In_ BOOLEAN FailImmediately,
    _In_ BOOLEAN ExclusiveLock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnlockFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PLARGE_INTEGER ByteOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ ULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnlockFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PLARGE_INTEGER ByteOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ ULONG Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryAttributesFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PFILE_BASIC_INFORMATION FileInformation
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryAttributesFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PFILE_BASIC_INFORMATION FileInformation
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryFullAttributesFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PFILE_NETWORK_OPEN_INFORMATION FileInformation
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryFullAttributesFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PFILE_NETWORK_OPEN_INFORMATION FileInformation
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtNotifyChangeDirectoryFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer, // FILE_NOTIFY_INFORMATION
    _In_ ULONG Length,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwNotifyChangeDirectoryFile(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer, // FILE_NOTIFY_INFORMATION
    _In_ ULONG Length,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree
    );

// private
typedef enum _DIRECTORY_NOTIFY_INFORMATION_CLASS
{
    DirectoryNotifyInformation, // FILE_NOTIFY_INFORMATION
    DirectoryNotifyExtendedInformation // FILE_NOTIFY_EXTENDED_INFORMATION
} DIRECTORY_NOTIFY_INFORMATION_CLASS, *PDIRECTORY_NOTIFY_INFORMATION_CLASS;

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtNotifyChangeDirectoryFileEx(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _In_opt_ DIRECTORY_NOTIFY_INFORMATION_CLASS DirectoryNotifyInformationClass
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwNotifyChangeDirectoryFileEx(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _In_opt_ DIRECTORY_NOTIFY_INFORMATION_CLASS DirectoryNotifyInformationClass
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadDriver(
    _In_ PUNICODE_STRING DriverServiceName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLoadDriver(
    _In_ PUNICODE_STRING DriverServiceName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnloadDriver(
    _In_ PUNICODE_STRING DriverServiceName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnloadDriver(
    _In_ PUNICODE_STRING DriverServiceName
    );

// I/O completion port

#ifndef IO_COMPLETION_QUERY_STATE
#define IO_COMPLETION_QUERY_STATE 0x0001
#endif

typedef enum _IO_COMPLETION_INFORMATION_CLASS
{
    IoCompletionBasicInformation
} IO_COMPLETION_INFORMATION_CLASS;

typedef struct _IO_COMPLETION_BASIC_INFORMATION
{
    LONG Depth;
} IO_COMPLETION_BASIC_INFORMATION, *PIO_COMPLETION_BASIC_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateIoCompletion(
    _Out_ PHANDLE IoCompletionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateIoCompletion(
    _Out_ PHANDLE IoCompletionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG Count
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenIoCompletion(
    _Out_ PHANDLE IoCompletionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenIoCompletion(
    _Out_ PHANDLE IoCompletionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryIoCompletion(
    _In_ HANDLE IoCompletionHandle,
    _In_ IO_COMPLETION_INFORMATION_CLASS IoCompletionInformationClass,
    _Out_writes_bytes_(IoCompletionInformationLength) PVOID IoCompletionInformation,
    _In_ ULONG IoCompletionInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryIoCompletion(
    _In_ HANDLE IoCompletionHandle,
    _In_ IO_COMPLETION_INFORMATION_CLASS IoCompletionInformationClass,
    _Out_writes_bytes_(IoCompletionInformationLength) PVOID IoCompletionInformation,
    _In_ ULONG IoCompletionInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetIoCompletion(
    _In_ HANDLE IoCompletionHandle,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetIoCompletion(
    _In_ HANDLE IoCompletionHandle,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetIoCompletionEx(
    _In_ HANDLE IoCompletionHandle,
    _In_ HANDLE IoCompletionPacketHandle,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetIoCompletionEx(
    _In_ HANDLE IoCompletionHandle,
    _In_ HANDLE IoCompletionPacketHandle,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRemoveIoCompletion(
    _In_ HANDLE IoCompletionHandle,
    _Out_ PVOID *KeyContext,
    _Out_ PVOID *ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRemoveIoCompletion(
    _In_ HANDLE IoCompletionHandle,
    _Out_ PVOID *KeyContext,
    _Out_ PVOID *ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER Timeout
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRemoveIoCompletionEx(
    _In_ HANDLE IoCompletionHandle,
    _Out_writes_to_(Count, *NumEntriesRemoved) PFILE_IO_COMPLETION_INFORMATION IoCompletionInformation,
    _In_ ULONG Count,
    _Out_ PULONG NumEntriesRemoved,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_ BOOLEAN Alertable
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRemoveIoCompletionEx(
    _In_ HANDLE IoCompletionHandle,
    _Out_writes_to_(Count, *NumEntriesRemoved) PFILE_IO_COMPLETION_INFORMATION IoCompletionInformation,
    _In_ ULONG Count,
    _Out_ PULONG NumEntriesRemoved,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_ BOOLEAN Alertable
    );
#endif

// Wait completion packet

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateWaitCompletionPacket(
    _Out_ PHANDLE WaitCompletionPacketHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateWaitCompletionPacket(
    _Out_ PHANDLE WaitCompletionPacketHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAssociateWaitCompletionPacket(
    _In_ HANDLE WaitCompletionPacketHandle,
    _In_ HANDLE IoCompletionHandle,
    _In_ HANDLE TargetObjectHandle,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation,
    _Out_opt_ PBOOLEAN AlreadySignaled
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAssociateWaitCompletionPacket(
    _In_ HANDLE WaitCompletionPacketHandle,
    _In_ HANDLE IoCompletionHandle,
    _In_ HANDLE TargetObjectHandle,
    _In_opt_ PVOID KeyContext,
    _In_opt_ PVOID ApcContext,
    _In_ NTSTATUS IoStatus,
    _In_ ULONG_PTR IoStatusInformation,
    _Out_opt_ PBOOLEAN AlreadySignaled
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCancelWaitCompletionPacket(
    _In_ HANDLE WaitCompletionPacketHandle,
    _In_ BOOLEAN RemoveSignaledPacket
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCancelWaitCompletionPacket(
    _In_ HANDLE WaitCompletionPacketHandle,
    _In_ BOOLEAN RemoveSignaledPacket
    );

#endif

// Sessions

typedef enum _IO_SESSION_EVENT
{
    IoSessionEventIgnore,
    IoSessionEventCreated,
    IoSessionEventTerminated,
    IoSessionEventConnected,
    IoSessionEventDisconnected,
    IoSessionEventLogon,
    IoSessionEventLogoff,
    IoSessionEventMax
} IO_SESSION_EVENT;

typedef enum _IO_SESSION_STATE
{
    IoSessionStateCreated,
    IoSessionStateInitialized,
    IoSessionStateConnected,
    IoSessionStateDisconnected,
    IoSessionStateDisconnectedLoggedOn,
    IoSessionStateLoggedOn,
    IoSessionStateLoggedOff,
    IoSessionStateTerminated,
    IoSessionStateMax
} IO_SESSION_STATE;

// Sessions

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenSession(
    _Out_ PHANDLE SessionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenSession(
    _Out_ PHANDLE SessionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtNotifyChangeSession(
    _In_ HANDLE SessionHandle,
    _In_ ULONG ChangeSequenceNumber,
    _In_ PLARGE_INTEGER ChangeTimeStamp,
    _In_ IO_SESSION_EVENT Event,
    _In_ IO_SESSION_STATE NewState,
    _In_ IO_SESSION_STATE PreviousState,
    _In_reads_bytes_opt_(PayloadSize) PVOID Payload,
    _In_ ULONG PayloadSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwNotifyChangeSession(
    _In_ HANDLE SessionHandle,
    _In_ ULONG ChangeSequenceNumber,
    _In_ PLARGE_INTEGER ChangeTimeStamp,
    _In_ IO_SESSION_EVENT Event,
    _In_ IO_SESSION_STATE NewState,
    _In_ IO_SESSION_STATE PreviousState,
    _In_reads_bytes_opt_(PayloadSize) PVOID Payload,
    _In_ ULONG PayloadSize
    );
#endif

// Other types

typedef enum _INTERFACE_TYPE
{
    InterfaceTypeUndefined = -1,
    Internal,
    Isa,
    Eisa,
    MicroChannel,
    TurboChannel,
    PCIBus,
    VMEBus,
    NuBus,
    PCMCIABus,
    CBus,
    MPIBus,
    MPSABus,
    ProcessorInternal,
    InternalPowerBus,
    PNPISABus,
    PNPBus,
    Vmcs,
    MaximumInterfaceType
} INTERFACE_TYPE, *PINTERFACE_TYPE;

typedef enum _DMA_WIDTH
{
    Width8Bits,
    Width16Bits,
    Width32Bits,
    MaximumDmaWidth
} DMA_WIDTH, *PDMA_WIDTH;

typedef enum _DMA_SPEED
{
    Compatible,
    TypeA,
    TypeB,
    TypeC,
    TypeF,
    MaximumDmaSpeed
} DMA_SPEED, *PDMA_SPEED;

typedef enum _BUS_DATA_TYPE
{
    ConfigurationSpaceUndefined = -1,
    Cmos,
    EisaConfiguration,
    Pos,
    CbusConfiguration,
    PCIConfiguration,
    VMEConfiguration,
    NuBusConfiguration,
    PCMCIAConfiguration,
    MPIConfiguration,
    MPSAConfiguration,
    PNPISAConfiguration,
    SgiInternalConfiguration,
    MaximumBusDataType
} BUS_DATA_TYPE, *PBUS_DATA_TYPE;

// Control structures

// Reparse structure for FSCTL_SET_REPARSE_POINT, FSCTL_GET_REPARSE_POINT, FSCTL_DELETE_REPARSE_POINT

#define SYMLINK_FLAG_RELATIVE 1

typedef struct _REPARSE_DATA_BUFFER
{
    ULONG ReparseTag;
    USHORT ReparseDataLength;
    USHORT Reserved;
    union
    {
        struct
        {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            ULONG Flags;
            WCHAR PathBuffer[1];
        } SymbolicLinkReparseBuffer;
        struct
        {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            WCHAR PathBuffer[1];
        } MountPointReparseBuffer;
        struct
        {
            UCHAR DataBuffer[1];
        } GenericReparseBuffer;
    };
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;

// Named pipe FS control definitions

#define DEVICE_NAMED_PIPE L"\\Device\\NamedPipe\\"

#define FSCTL_PIPE_ASSIGN_EVENT             CTL_CODE(FILE_DEVICE_NAMED_PIPE, 0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_DISCONNECT               CTL_CODE(FILE_DEVICE_NAMED_PIPE, 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_LISTEN                   CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_PEEK                     CTL_CODE(FILE_DEVICE_NAMED_PIPE, 3, METHOD_BUFFERED, FILE_READ_DATA)
#define FSCTL_PIPE_QUERY_EVENT              CTL_CODE(FILE_DEVICE_NAMED_PIPE, 4, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_TRANSCEIVE               CTL_CODE(FILE_DEVICE_NAMED_PIPE, 5, METHOD_NEITHER,  FILE_READ_DATA | FILE_WRITE_DATA)
#define FSCTL_PIPE_WAIT                     CTL_CODE(FILE_DEVICE_NAMED_PIPE, 6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_IMPERSONATE              CTL_CODE(FILE_DEVICE_NAMED_PIPE, 7, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_SET_CLIENT_PROCESS       CTL_CODE(FILE_DEVICE_NAMED_PIPE, 8, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_QUERY_CLIENT_PROCESS     CTL_CODE(FILE_DEVICE_NAMED_PIPE, 9, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_GET_PIPE_ATTRIBUTE       CTL_CODE(FILE_DEVICE_NAMED_PIPE, 10, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_SET_PIPE_ATTRIBUTE       CTL_CODE(FILE_DEVICE_NAMED_PIPE, 11, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_GET_CONNECTION_ATTRIBUTE CTL_CODE(FILE_DEVICE_NAMED_PIPE, 12, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_SET_CONNECTION_ATTRIBUTE CTL_CODE(FILE_DEVICE_NAMED_PIPE, 13, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_GET_HANDLE_ATTRIBUTE     CTL_CODE(FILE_DEVICE_NAMED_PIPE, 14, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_SET_HANDLE_ATTRIBUTE     CTL_CODE(FILE_DEVICE_NAMED_PIPE, 15, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_FLUSH                    CTL_CODE(FILE_DEVICE_NAMED_PIPE, 16, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_PIPE_DISABLE_IMPERSONATE      CTL_CODE(FILE_DEVICE_NAMED_PIPE, 17, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_SILO_ARRIVAL             CTL_CODE(FILE_DEVICE_NAMED_PIPE, 18, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_PIPE_CREATE_SYMLINK           CTL_CODE(FILE_DEVICE_NAMED_PIPE, 19, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define FSCTL_PIPE_DELETE_SYMLINK           CTL_CODE(FILE_DEVICE_NAMED_PIPE, 20, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

#define FSCTL_PIPE_INTERNAL_READ            CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2045, METHOD_BUFFERED, FILE_READ_DATA)
#define FSCTL_PIPE_INTERNAL_WRITE           CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2046, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_PIPE_INTERNAL_TRANSCEIVE      CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2047, METHOD_NEITHER, FILE_READ_DATA | FILE_WRITE_DATA)
#define FSCTL_PIPE_INTERNAL_READ_OVFLOW     CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2048, METHOD_BUFFERED, FILE_READ_DATA)

// Flags for query event

#define FILE_PIPE_READ_DATA 0x00000000
#define FILE_PIPE_WRITE_SPACE 0x00000001

// Input for FSCTL_PIPE_ASSIGN_EVENT
typedef struct _FILE_PIPE_ASSIGN_EVENT_BUFFER
{
    HANDLE EventHandle;
    ULONG KeyValue;
} FILE_PIPE_ASSIGN_EVENT_BUFFER, *PFILE_PIPE_ASSIGN_EVENT_BUFFER;

// Output for FILE_PIPE_PEEK_BUFFER
typedef struct _FILE_PIPE_PEEK_BUFFER
{
    ULONG NamedPipeState;
    ULONG ReadDataAvailable;
    ULONG NumberOfMessages;
    ULONG MessageLength;
    CHAR Data[1];
} FILE_PIPE_PEEK_BUFFER, *PFILE_PIPE_PEEK_BUFFER;

// Output for FSCTL_PIPE_QUERY_EVENT
typedef struct _FILE_PIPE_EVENT_BUFFER
{
    ULONG NamedPipeState;
    ULONG EntryType;
    ULONG ByteCount;
    ULONG KeyValue;
    ULONG NumberRequests;
} FILE_PIPE_EVENT_BUFFER, *PFILE_PIPE_EVENT_BUFFER;

// Input for FSCTL_PIPE_WAIT
typedef struct _FILE_PIPE_WAIT_FOR_BUFFER
{
    LARGE_INTEGER Timeout;
    ULONG NameLength;
    BOOLEAN TimeoutSpecified;
    WCHAR Name[1];
} FILE_PIPE_WAIT_FOR_BUFFER, *PFILE_PIPE_WAIT_FOR_BUFFER;

// Input for FSCTL_PIPE_SET_CLIENT_PROCESS, Output for FSCTL_PIPE_QUERY_CLIENT_PROCESS
typedef struct _FILE_PIPE_CLIENT_PROCESS_BUFFER
{
#if !defined(BUILD_WOW6432)
    PVOID ClientSession;
    PVOID ClientProcess;
#else
    ULONGLONG ClientSession;
    ULONGLONG ClientProcess;
#endif
} FILE_PIPE_CLIENT_PROCESS_BUFFER, *PFILE_PIPE_CLIENT_PROCESS_BUFFER;

#define FILE_PIPE_COMPUTER_NAME_LENGTH 15

// Input for FSCTL_PIPE_SET_CLIENT_PROCESS, Output for FSCTL_PIPE_QUERY_CLIENT_PROCESS
typedef struct _FILE_PIPE_CLIENT_PROCESS_BUFFER_EX
{
#if !defined(BUILD_WOW6432)
    PVOID ClientSession;
    PVOID ClientProcess;
#else
    ULONGLONG ClientSession;
    ULONGLONG ClientProcess;
#endif
    USHORT ClientComputerNameLength; // in bytes
    WCHAR ClientComputerBuffer[FILE_PIPE_COMPUTER_NAME_LENGTH + 1]; // null-terminated
} FILE_PIPE_CLIENT_PROCESS_BUFFER_EX, *PFILE_PIPE_CLIENT_PROCESS_BUFFER_EX;

// Control structure for FSCTL_PIPE_SILO_ARRIVAL

typedef struct _FILE_PIPE_SILO_ARRIVAL_INPUT
{
    HANDLE JobHandle;
} FILE_PIPE_SILO_ARRIVAL_INPUT, *PFILE_PIPE_SILO_ARRIVAL_INPUT;

//
// Flags for create symlink
//

//
// A global symlink will cause resolution of the symlink's target to occur in
// the host silo (i.e. not in any current silo).  For example, if there is a
// symlink at \Device\Silos\37\Device\NamedPipe\symlink then the target will be
// resolved as \Device\NamedPipe\target instead of \Device\Silos\37\Device\NamedPipe\target
//
#define FILE_PIPE_SYMLINK_FLAG_GLOBAL   0x1

//
// A relative symlink will cause resolution of the symlink's target to occur relative
// to the root of the named pipe file system.  For example, if there is a symlink at
// \Device\NamedPipe\symlink that has a target called "target", then the target will
// be resolved as \Device\NamedPipe\target
//
#define FILE_PIPE_SYMLINK_FLAG_RELATIVE 0x2

#define FILE_PIPE_SYMLINK_VALID_FLAGS \
    (FILE_PIPE_SYMLINK_FLAG_GLOBAL | FILE_PIPE_SYMLINK_FLAG_RELATIVE)

// Control structure for FSCTL_PIPE_CREATE_SYMLINK

typedef struct _FILE_PIPE_CREATE_SYMLINK_INPUT
{
    USHORT NameOffset;
    USHORT NameLength;
    USHORT SubstituteNameOffset;
    USHORT SubstituteNameLength;
    ULONG Flags;
} FILE_PIPE_CREATE_SYMLINK_INPUT, *PFILE_PIPE_CREATE_SYMLINK_INPUT;

// Control structure for FSCTL_PIPE_DELETE_SYMLINK

typedef struct _FILE_PIPE_DELETE_SYMLINK_INPUT
{
    USHORT NameOffset;
    USHORT NameLength;
} FILE_PIPE_DELETE_SYMLINK_INPUT, *PFILE_PIPE_DELETE_SYMLINK_INPUT;

// Mailslot FS control definitions

#define MAILSLOT_CLASS_FIRSTCLASS 1
#define MAILSLOT_CLASS_SECONDCLASS 2

#define FSCTL_MAILSLOT_PEEK             CTL_CODE(FILE_DEVICE_MAILSLOT, 0, METHOD_NEITHER, FILE_READ_DATA)

// Output for FSCTL_MAILSLOT_PEEK
typedef struct _FILE_MAILSLOT_PEEK_BUFFER
{
    ULONG ReadDataAvailable;
    ULONG NumberOfMessages;
    ULONG MessageLength;
} FILE_MAILSLOT_PEEK_BUFFER, *PFILE_MAILSLOT_PEEK_BUFFER;

// Mount manager FS control definitions

#define MOUNTMGR_DEVICE_NAME L"\\Device\\MountPointManager"
#define MOUNTMGRCONTROLTYPE 0x0000006D // 'm'
#define MOUNTDEVCONTROLTYPE 0x0000004D // 'M'

#define IOCTL_MOUNTMGR_CREATE_POINT                 CTL_CODE(MOUNTMGRCONTROLTYPE, 0, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_MOUNTMGR_DELETE_POINTS                CTL_CODE(MOUNTMGRCONTROLTYPE, 1, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_MOUNTMGR_QUERY_POINTS                 CTL_CODE(MOUNTMGRCONTROLTYPE, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MOUNTMGR_DELETE_POINTS_DBONLY         CTL_CODE(MOUNTMGRCONTROLTYPE, 3, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_MOUNTMGR_NEXT_DRIVE_LETTER            CTL_CODE(MOUNTMGRCONTROLTYPE, 4, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_MOUNTMGR_AUTO_DL_ASSIGNMENTS          CTL_CODE(MOUNTMGRCONTROLTYPE, 5, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_MOUNTMGR_VOLUME_MOUNT_POINT_CREATED   CTL_CODE(MOUNTMGRCONTROLTYPE, 6, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_MOUNTMGR_VOLUME_MOUNT_POINT_DELETED   CTL_CODE(MOUNTMGRCONTROLTYPE, 7, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_MOUNTMGR_CHANGE_NOTIFY                CTL_CODE(MOUNTMGRCONTROLTYPE, 8, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_MOUNTMGR_KEEP_LINKS_WHEN_OFFLINE      CTL_CODE(MOUNTMGRCONTROLTYPE, 9, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_MOUNTMGR_CHECK_UNPROCESSED_VOLUMES    CTL_CODE(MOUNTMGRCONTROLTYPE, 10, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_MOUNTMGR_VOLUME_ARRIVAL_NOTIFICATION  CTL_CODE(MOUNTMGRCONTROLTYPE, 11, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATH        CTL_CODE(MOUNTMGRCONTROLTYPE, 12, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATHS       CTL_CODE(MOUNTMGRCONTROLTYPE, 13, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_MOUNTDEV_QUERY_DEVICE_NAME            CTL_CODE(MOUNTDEVCONTROLTYPE, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)

// Input structure for IOCTL_MOUNTMGR_CREATE_POINT.
typedef struct _MOUNTMGR_CREATE_POINT_INPUT
{
    USHORT SymbolicLinkNameOffset;
    USHORT SymbolicLinkNameLength;
    USHORT DeviceNameOffset;
    USHORT DeviceNameLength;
} MOUNTMGR_CREATE_POINT_INPUT, *PMOUNTMGR_CREATE_POINT_INPUT;

// Input structure for IOCTL_MOUNTMGR_DELETE_POINTS, IOCTL_MOUNTMGR_QUERY_POINTS, and IOCTL_MOUNTMGR_DELETE_POINTS_DBONLY.
typedef struct _MOUNTMGR_MOUNT_POINT
{
    ULONG SymbolicLinkNameOffset;
    USHORT SymbolicLinkNameLength;
    USHORT Reserved1;
    ULONG UniqueIdOffset;
    USHORT UniqueIdLength;
    USHORT Reserved2;
    ULONG DeviceNameOffset;
    USHORT DeviceNameLength;
    USHORT Reserved3;
} MOUNTMGR_MOUNT_POINT, * PMOUNTMGR_MOUNT_POINT;

// Output structure for IOCTL_MOUNTMGR_DELETE_POINTS, IOCTL_MOUNTMGR_QUERY_POINTS, and IOCTL_MOUNTMGR_DELETE_POINTS_DBONLY.
typedef struct _MOUNTMGR_MOUNT_POINTS
{
    ULONG Size;
    ULONG NumberOfMountPoints;
    MOUNTMGR_MOUNT_POINT MountPoints[1];
} MOUNTMGR_MOUNT_POINTS, *PMOUNTMGR_MOUNT_POINTS;

// Input structure for IOCTL_MOUNTMGR_NEXT_DRIVE_LETTER.
typedef struct _MOUNTMGR_DRIVE_LETTER_TARGET
{
    USHORT DeviceNameLength;
    WCHAR DeviceName[1];
} MOUNTMGR_DRIVE_LETTER_TARGET, *PMOUNTMGR_DRIVE_LETTER_TARGET;

// Output structure for IOCTL_MOUNTMGR_NEXT_DRIVE_LETTER.
typedef struct _MOUNTMGR_DRIVE_LETTER_INFORMATION
{
    BOOLEAN DriveLetterWasAssigned;
    UCHAR CurrentDriveLetter;
} MOUNTMGR_DRIVE_LETTER_INFORMATION, *PMOUNTMGR_DRIVE_LETTER_INFORMATION;

// Input structure for IOCTL_MOUNTMGR_VOLUME_MOUNT_POINT_CREATED and
// IOCTL_MOUNTMGR_VOLUME_MOUNT_POINT_DELETED.
typedef struct _MOUNTMGR_VOLUME_MOUNT_POINT
{
    USHORT SourceVolumeNameOffset;
    USHORT SourceVolumeNameLength;
    USHORT TargetVolumeNameOffset;
    USHORT TargetVolumeNameLength;
} MOUNTMGR_VOLUME_MOUNT_POINT, *PMOUNTMGR_VOLUME_MOUNT_POINT;

// Input structure for IOCTL_MOUNTMGR_CHANGE_NOTIFY.
// Output structure for IOCTL_MOUNTMGR_CHANGE_NOTIFY.
typedef struct _MOUNTMGR_CHANGE_NOTIFY_INFO
{
    ULONG EpicNumber;
} MOUNTMGR_CHANGE_NOTIFY_INFO, *PMOUNTMGR_CHANGE_NOTIFY_INFO;

// Input structure for IOCTL_MOUNTMGR_KEEP_LINKS_WHEN_OFFLINE,
// IOCTL_MOUNTMGR_VOLUME_ARRIVAL_NOTIFICATION,
// IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATH, and
// IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATHS.
// IOCTL_MOUNTMGR_PREPARE_VOLUME_DELETE
// IOCTL_MOUNTMGR_CANCEL_VOLUME_DELETE
typedef struct _MOUNTMGR_TARGET_NAME
{
    USHORT DeviceNameLength;
    WCHAR DeviceName[1];
} MOUNTMGR_TARGET_NAME, * PMOUNTMGR_TARGET_NAME;

// Macro that defines what a "drive letter" mount point is.  This macro can
// be used to scan the result from QUERY_POINTS to discover which mount points
// are find "drive letter" mount points.
#define MOUNTMGR_IS_DRIVE_LETTER(s) ( \
    (s)->Length == 28 && \
    (s)->Buffer[0] == '\\' && \
    (s)->Buffer[1] == 'D' && \
    (s)->Buffer[2] == 'o' && \
    (s)->Buffer[3] == 's' && \
    (s)->Buffer[4] == 'D' && \
    (s)->Buffer[5] == 'e' && \
    (s)->Buffer[6] == 'v' && \
    (s)->Buffer[7] == 'i' && \
    (s)->Buffer[8] == 'c' && \
    (s)->Buffer[9] == 'e' && \
    (s)->Buffer[10] == 's' && \
    (s)->Buffer[11] == '\\' && \
    (s)->Buffer[12] >= 'A' && \
    (s)->Buffer[12] <= 'Z' && \
    (s)->Buffer[13] == ':')

// Macro that defines what a "volume name" mount point is.  This macro can
// be used to scan the result from QUERY_POINTS to discover which mount points
// are "volume name" mount points.
#define MOUNTMGR_IS_VOLUME_NAME(s) ( \
     ((s)->Length == 96 || ((s)->Length == 98 && (s)->Buffer[48] == '\\')) && \
     (s)->Buffer[0] == '\\' && \
     ((s)->Buffer[1] == '?' || (s)->Buffer[1] == '\\') && \
     (s)->Buffer[2] == '?' && \
     (s)->Buffer[3] == '\\' && \
     (s)->Buffer[4] == 'V' && \
     (s)->Buffer[5] == 'o' && \
     (s)->Buffer[6] == 'l' && \
     (s)->Buffer[7] == 'u' && \
     (s)->Buffer[8] == 'm' && \
     (s)->Buffer[9] == 'e' && \
     (s)->Buffer[10] == '{' && \
     (s)->Buffer[19] == '-' && \
     (s)->Buffer[24] == '-' && \
     (s)->Buffer[29] == '-' && \
     (s)->Buffer[34] == '-' && \
     (s)->Buffer[47] == '}')

// Output structure for IOCTL_MOUNTDEV_QUERY_DEVICE_NAME.
typedef struct _MOUNTDEV_NAME
{
    USHORT NameLength;
    WCHAR Name[1];
} MOUNTDEV_NAME, * PMOUNTDEV_NAME;

// Output structure for IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATH and IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATHS.
typedef struct _MOUNTMGR_VOLUME_PATHS
{
    ULONG MultiSzLength;
    WCHAR MultiSz[1];
} MOUNTMGR_VOLUME_PATHS, *PMOUNTMGR_VOLUME_PATHS;

#define MOUNTMGR_IS_DOS_VOLUME_NAME(s) ( \
     MOUNTMGR_IS_VOLUME_NAME(s) && \
     (s)->Length == 96 && \
     (s)->Buffer[1] == '\\')

#define MOUNTMGR_IS_DOS_VOLUME_NAME_WB(s) ( \
     MOUNTMGR_IS_VOLUME_NAME(s) && \
     (s)->Length == 98 && \
     (s)->Buffer[1] == '\\')

#define MOUNTMGR_IS_NT_VOLUME_NAME(s) ( \
     MOUNTMGR_IS_VOLUME_NAME(s) && \
     (s)->Length == 96 && \
     (s)->Buffer[1] == '?')

#define MOUNTMGR_IS_NT_VOLUME_NAME_WB(s) ( \
     MOUNTMGR_IS_VOLUME_NAME(s) && \
     (s)->Length == 98 && \
     (s)->Buffer[1] == '?')

// #include <ntlpcapi.h>
#define PORT_CONNECT 0x0001
#define PORT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1)

typedef struct _PORT_MESSAGE
{
    union
    {
        struct
        {
            CSHORT DataLength;
            CSHORT TotalLength;
        } s1;
        ULONG Length;
    } u1;
    union
    {
        struct
        {
            CSHORT Type;
            CSHORT DataInfoOffset;
        } s2;
        ULONG ZeroInit;
    } u2;
    union
    {
        CLIENT_ID ClientId;
        double DoNotUseThisField;
    };
    ULONG MessageId;
    union
    {
        SIZE_T ClientViewSize; // only valid for LPC_CONNECTION_REQUEST messages
        ULONG CallbackId; // only valid for LPC_REQUEST messages
    };
} PORT_MESSAGE, *PPORT_MESSAGE;

typedef struct _PORT_DATA_ENTRY
{
    PVOID Base;
    ULONG Size;
} PORT_DATA_ENTRY, *PPORT_DATA_ENTRY;

typedef struct _PORT_DATA_INFORMATION
{
    ULONG CountDataEntries;
    PORT_DATA_ENTRY DataEntries[1];
} PORT_DATA_INFORMATION, *PPORT_DATA_INFORMATION;

#define LPC_REQUEST 1
#define LPC_REPLY 2
#define LPC_DATAGRAM 3
#define LPC_LOST_REPLY 4
#define LPC_PORT_CLOSED 5
#define LPC_CLIENT_DIED 6
#define LPC_EXCEPTION 7
#define LPC_DEBUG_EVENT 8
#define LPC_ERROR_EVENT 9
#define LPC_CONNECTION_REQUEST 10

#define LPC_KERNELMODE_MESSAGE (CSHORT)0x8000
#define LPC_NO_IMPERSONATE (CSHORT)0x4000

#define PORT_VALID_OBJECT_ATTRIBUTES OBJ_CASE_INSENSITIVE

#ifdef _WIN64
#define PORT_MAXIMUM_MESSAGE_LENGTH 512
#else
#define PORT_MAXIMUM_MESSAGE_LENGTH 256
#endif

#define LPC_MAX_CONNECTION_INFO_SIZE (16 * sizeof(ULONG_PTR))

#define PORT_TOTAL_MAXIMUM_MESSAGE_LENGTH \
    ((PORT_MAXIMUM_MESSAGE_LENGTH + sizeof(PORT_MESSAGE) + LPC_MAX_CONNECTION_INFO_SIZE + 0xf) & ~0xf)

typedef struct _LPC_CLIENT_DIED_MSG
{
    PORT_MESSAGE PortMsg;
    LARGE_INTEGER CreateTime;
} LPC_CLIENT_DIED_MSG, *PLPC_CLIENT_DIED_MSG;

typedef struct _PORT_VIEW
{
    ULONG Length;
    HANDLE SectionHandle;
    ULONG SectionOffset;
    SIZE_T ViewSize;
    PVOID ViewBase;
    PVOID ViewRemoteBase;
} PORT_VIEW, *PPORT_VIEW;

typedef struct _REMOTE_PORT_VIEW
{
    ULONG Length;
    SIZE_T ViewSize;
    PVOID ViewBase;
} REMOTE_PORT_VIEW, *PREMOTE_PORT_VIEW;

// WOW64 definitions

// Except in a small number of special cases, WOW64 programs using the LPC APIs must use the 64-bit versions of the
// PORT_MESSAGE, PORT_VIEW and REMOTE_PORT_VIEW data structures. Note that we take a different approach than the
// official NT headers, which produce 64-bit versions in a 32-bit environment when USE_LPC6432 is defined.

typedef struct _PORT_MESSAGE64
{
    union
    {
        struct
        {
            CSHORT DataLength;
            CSHORT TotalLength;
        } s1;
        ULONG Length;
    } u1;
    union
    {
        struct
        {
            CSHORT Type;
            CSHORT DataInfoOffset;
        } s2;
        ULONG ZeroInit;
    } u2;
    union
    {
        CLIENT_ID64 ClientId;
        double DoNotUseThisField;
    };
    ULONG MessageId;
    union
    {
        ULONGLONG ClientViewSize; // only valid for LPC_CONNECTION_REQUEST messages
        ULONG CallbackId; // only valid for LPC_REQUEST messages
    };
} PORT_MESSAGE64, *PPORT_MESSAGE64;

typedef struct _LPC_CLIENT_DIED_MSG64
{
    PORT_MESSAGE64 PortMsg;
    LARGE_INTEGER CreateTime;
} LPC_CLIENT_DIED_MSG64, *PLPC_CLIENT_DIED_MSG64;

typedef struct _PORT_VIEW64
{
    ULONG Length;
    ULONGLONG SectionHandle;
    ULONG SectionOffset;
    ULONGLONG ViewSize;
    ULONGLONG ViewBase;
    ULONGLONG ViewRemoteBase;
} PORT_VIEW64, *PPORT_VIEW64;

typedef struct _REMOTE_PORT_VIEW64
{
    ULONG Length;
    ULONGLONG ViewSize;
    ULONGLONG ViewBase;
} REMOTE_PORT_VIEW64, *PREMOTE_PORT_VIEW64;

// Port creation

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreatePort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG MaxConnectionInfoLength,
    _In_ ULONG MaxMessageLength,
    _In_opt_ ULONG MaxPoolUsage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreatePort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG MaxConnectionInfoLength,
    _In_ ULONG MaxMessageLength,
    _In_opt_ ULONG MaxPoolUsage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateWaitablePort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG MaxConnectionInfoLength,
    _In_ ULONG MaxMessageLength,
    _In_opt_ ULONG MaxPoolUsage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateWaitablePort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG MaxConnectionInfoLength,
    _In_ ULONG MaxMessageLength,
    _In_opt_ ULONG MaxPoolUsage
    );

// Port connection (client)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ PUNICODE_STRING PortName,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    _Inout_opt_ PPORT_VIEW ClientView,
    _Inout_opt_ PREMOTE_PORT_VIEW ServerView,
    _Out_opt_ PULONG MaxMessageLength,
    _Inout_updates_bytes_to_opt_(*ConnectionInformationLength, *ConnectionInformationLength) PVOID ConnectionInformation,
    _Inout_opt_ PULONG ConnectionInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ PUNICODE_STRING PortName,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    _Inout_opt_ PPORT_VIEW ClientView,
    _Inout_opt_ PREMOTE_PORT_VIEW ServerView,
    _Out_opt_ PULONG MaxMessageLength,
    _Inout_updates_bytes_to_opt_(*ConnectionInformationLength, *ConnectionInformationLength) PVOID ConnectionInformation,
    _Inout_opt_ PULONG ConnectionInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSecureConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ PUNICODE_STRING PortName,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    _Inout_opt_ PPORT_VIEW ClientView,
    _In_opt_ PSID RequiredServerSid,
    _Inout_opt_ PREMOTE_PORT_VIEW ServerView,
    _Out_opt_ PULONG MaxMessageLength,
    _Inout_updates_bytes_to_opt_(*ConnectionInformationLength, *ConnectionInformationLength) PVOID ConnectionInformation,
    _Inout_opt_ PULONG ConnectionInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSecureConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ PUNICODE_STRING PortName,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    _Inout_opt_ PPORT_VIEW ClientView,
    _In_opt_ PSID RequiredServerSid,
    _Inout_opt_ PREMOTE_PORT_VIEW ServerView,
    _Out_opt_ PULONG MaxMessageLength,
    _Inout_updates_bytes_to_opt_(*ConnectionInformationLength, *ConnectionInformationLength) PVOID ConnectionInformation,
    _Inout_opt_ PULONG ConnectionInformationLength
    );

// Port connection (server)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtListenPort(
    _In_ HANDLE PortHandle,
    _Out_ PPORT_MESSAGE ConnectionRequest
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwListenPort(
    _In_ HANDLE PortHandle,
    _Out_ PPORT_MESSAGE ConnectionRequest
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAcceptConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ PVOID PortContext,
    _In_ PPORT_MESSAGE ConnectionRequest,
    _In_ BOOLEAN AcceptConnection,
    _Inout_opt_ PPORT_VIEW ServerView,
    _Out_opt_ PREMOTE_PORT_VIEW ClientView
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAcceptConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ PVOID PortContext,
    _In_ PPORT_MESSAGE ConnectionRequest,
    _In_ BOOLEAN AcceptConnection,
    _Inout_opt_ PPORT_VIEW ServerView,
    _Out_opt_ PREMOTE_PORT_VIEW ClientView
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompleteConnectPort(
    _In_ HANDLE PortHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCompleteConnectPort(
    _In_ HANDLE PortHandle
    );

// General

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRequestPort(
    _In_ HANDLE PortHandle,
    _In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRequestPort(
    _In_ HANDLE PortHandle,
    _In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRequestWaitReplyPort(
    _In_ HANDLE PortHandle,
    _In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage,
    _Out_ PPORT_MESSAGE ReplyMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRequestWaitReplyPort(
    _In_ HANDLE PortHandle,
    _In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage,
    _Out_ PPORT_MESSAGE ReplyMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReplyPort(
    _In_ HANDLE PortHandle,
    _In_reads_bytes_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReplyPort(
    _In_ HANDLE PortHandle,
    _In_reads_bytes_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReplyWaitReplyPort(
    _In_ HANDLE PortHandle,
    _Inout_ PPORT_MESSAGE ReplyMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReplyWaitReplyPort(
    _In_ HANDLE PortHandle,
    _Inout_ PPORT_MESSAGE ReplyMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReplyWaitReceivePort(
    _In_ HANDLE PortHandle,
    _Out_opt_ PVOID *PortContext,
    _In_reads_bytes_opt_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage,
    _Out_ PPORT_MESSAGE ReceiveMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReplyWaitReceivePort(
    _In_ HANDLE PortHandle,
    _Out_opt_ PVOID *PortContext,
    _In_reads_bytes_opt_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage,
    _Out_ PPORT_MESSAGE ReceiveMessage
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReplyWaitReceivePortEx(
    _In_ HANDLE PortHandle,
    _Out_opt_ PVOID *PortContext,
    _In_reads_bytes_opt_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage,
    _Out_ PPORT_MESSAGE ReceiveMessage,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReplyWaitReceivePortEx(
    _In_ HANDLE PortHandle,
    _Out_opt_ PVOID *PortContext,
    _In_reads_bytes_opt_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage,
    _Out_ PPORT_MESSAGE ReceiveMessage,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtImpersonateClientOfPort(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwImpersonateClientOfPort(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadRequestData(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message,
    _In_ ULONG DataEntryIndex,
    _Out_writes_bytes_to_(BufferSize, *NumberOfBytesRead) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReadRequestData(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message,
    _In_ ULONG DataEntryIndex,
    _Out_writes_bytes_to_(BufferSize, *NumberOfBytesRead) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWriteRequestData(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message,
    _In_ ULONG DataEntryIndex,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesWritten
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwWriteRequestData(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message,
    _In_ ULONG DataEntryIndex,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesWritten
    );

typedef enum _PORT_INFORMATION_CLASS
{
    PortBasicInformation,
    PortDumpInformation
} PORT_INFORMATION_CLASS;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationPort(
    _In_ HANDLE PortHandle,
    _In_ PORT_INFORMATION_CLASS PortInformationClass,
    _Out_writes_bytes_to_(Length, *ReturnLength) PVOID PortInformation,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationPort(
    _In_ HANDLE PortHandle,
    _In_ PORT_INFORMATION_CLASS PortInformationClass,
    _Out_writes_bytes_to_(Length, *ReturnLength) PVOID PortInformation,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength
    );

// Asynchronous Local Inter-process Communication

// rev
typedef HANDLE ALPC_HANDLE, *PALPC_HANDLE;

#define ALPC_PORFLG_ALLOW_LPC_REQUESTS 0x20000 // rev
#define ALPC_PORFLG_WAITABLE_PORT 0x40000 // dbg
#define ALPC_PORFLG_SYSTEM_PROCESS 0x100000 // dbg

// symbols
typedef struct _ALPC_PORT_ATTRIBUTES
{
    ULONG Flags;
    SECURITY_QUALITY_OF_SERVICE SecurityQos;
    SIZE_T MaxMessageLength;
    SIZE_T MemoryBandwidth;
    SIZE_T MaxPoolUsage;
    SIZE_T MaxSectionSize;
    SIZE_T MaxViewSize;
    SIZE_T MaxTotalSectionSize;
    ULONG DupObjectTypes;
#ifdef _WIN64
    ULONG Reserved;
#endif
} ALPC_PORT_ATTRIBUTES, *PALPC_PORT_ATTRIBUTES;

// begin_rev
#define ALPC_MESSAGE_SECURITY_ATTRIBUTE 0x80000000
#define ALPC_MESSAGE_VIEW_ATTRIBUTE 0x40000000
#define ALPC_MESSAGE_CONTEXT_ATTRIBUTE 0x20000000
#define ALPC_MESSAGE_HANDLE_ATTRIBUTE 0x10000000
// end_rev

// symbols
typedef struct _ALPC_MESSAGE_ATTRIBUTES
{
    ULONG AllocatedAttributes;
    ULONG ValidAttributes;
} ALPC_MESSAGE_ATTRIBUTES, *PALPC_MESSAGE_ATTRIBUTES;

// symbols
typedef struct _ALPC_COMPLETION_LIST_STATE
{
    union
    {
        struct
        {
            ULONG64 Head : 24;
            ULONG64 Tail : 24;
            ULONG64 ActiveThreadCount : 16;
        } s1;
        ULONG64 Value;
    } u1;
} ALPC_COMPLETION_LIST_STATE, *PALPC_COMPLETION_LIST_STATE;

#define ALPC_COMPLETION_LIST_BUFFER_GRANULARITY_MASK 0x3f // dbg

// symbols
typedef struct DECLSPEC_ALIGN(128) _ALPC_COMPLETION_LIST_HEADER
{
    ULONG64 StartMagic;

    ULONG TotalSize;
    ULONG ListOffset;
    ULONG ListSize;
    ULONG BitmapOffset;
    ULONG BitmapSize;
    ULONG DataOffset;
    ULONG DataSize;
    ULONG AttributeFlags;
    ULONG AttributeSize;

    DECLSPEC_ALIGN(128) ALPC_COMPLETION_LIST_STATE State;
    ULONG LastMessageId;
    ULONG LastCallbackId;
    DECLSPEC_ALIGN(128) ULONG PostCount;
    DECLSPEC_ALIGN(128) ULONG ReturnCount;
    DECLSPEC_ALIGN(128) ULONG LogSequenceNumber;
    DECLSPEC_ALIGN(128) RTL_SRWLOCK UserLock;

    ULONG64 EndMagic;
} ALPC_COMPLETION_LIST_HEADER, *PALPC_COMPLETION_LIST_HEADER;

// private
typedef struct _ALPC_CONTEXT_ATTR
{
    PVOID PortContext;
    PVOID MessageContext;
    ULONG Sequence;
    ULONG MessageId;
    ULONG CallbackId;
} ALPC_CONTEXT_ATTR, *PALPC_CONTEXT_ATTR;

// begin_rev
#define ALPC_HANDLEFLG_DUPLICATE_SAME_ACCESS 0x10000
#define ALPC_HANDLEFLG_DUPLICATE_SAME_ATTRIBUTES 0x20000
#define ALPC_HANDLEFLG_DUPLICATE_INHERIT 0x80000
// end_rev

// private
typedef struct _ALPC_HANDLE_ATTR32
{
    ULONG Flags;
    ULONG Reserved0;
    ULONG SameAccess;
    ULONG SameAttributes;
    ULONG Indirect;
    ULONG Inherit;
    ULONG Reserved1;
    ULONG Handle;
    ULONG ObjectType; // ObjectTypeCode, not ObjectTypeIndex
    ULONG DesiredAccess;
    ULONG GrantedAccess;
} ALPC_HANDLE_ATTR32, *PALPC_HANDLE_ATTR32;

// private
typedef struct _ALPC_HANDLE_ATTR
{
    ULONG Flags;
    ULONG Reserved0;
    ULONG SameAccess;
    ULONG SameAttributes;
    ULONG Indirect;
    ULONG Inherit;
    ULONG Reserved1;
    HANDLE Handle;
    PALPC_HANDLE_ATTR32 HandleAttrArray;
    ULONG ObjectType; // ObjectTypeCode, not ObjectTypeIndex
    ULONG HandleCount;
    ACCESS_MASK DesiredAccess;
    ACCESS_MASK GrantedAccess;
} ALPC_HANDLE_ATTR, *PALPC_HANDLE_ATTR;

#define ALPC_SECFLG_CREATE_HANDLE 0x20000 // dbg
#define ALPC_SECFLG_NOSECTIONHANDLE 0x40000
// private
typedef struct _ALPC_SECURITY_ATTR
{
    ULONG Flags;
    PSECURITY_QUALITY_OF_SERVICE QoS;
    ALPC_HANDLE ContextHandle; // dbg
} ALPC_SECURITY_ATTR, *PALPC_SECURITY_ATTR;

// begin_rev
#define ALPC_VIEWFLG_NOT_SECURE 0x40000
// end_rev

// private
typedef struct _ALPC_DATA_VIEW_ATTR
{
    ULONG Flags;
    ALPC_HANDLE SectionHandle;
    PVOID ViewBase; // must be zero on input
    SIZE_T ViewSize;
} ALPC_DATA_VIEW_ATTR, *PALPC_DATA_VIEW_ATTR;

// private
typedef enum _ALPC_PORT_INFORMATION_CLASS
{
    AlpcBasicInformation, // q: out ALPC_BASIC_INFORMATION
    AlpcPortInformation, // s: in ALPC_PORT_ATTRIBUTES
    AlpcAssociateCompletionPortInformation, // s: in ALPC_PORT_ASSOCIATE_COMPLETION_PORT
    AlpcConnectedSIDInformation, // q: in SID
    AlpcServerInformation, // q: inout ALPC_SERVER_INFORMATION
    AlpcMessageZoneInformation, // s: in ALPC_PORT_MESSAGE_ZONE_INFORMATION
    AlpcRegisterCompletionListInformation, // s: in ALPC_PORT_COMPLETION_LIST_INFORMATION
    AlpcUnregisterCompletionListInformation, // s: VOID
    AlpcAdjustCompletionListConcurrencyCountInformation, // s: in ULONG
    AlpcRegisterCallbackInformation, // kernel-mode only
    AlpcCompletionListRundownInformation, // s: VOID
    AlpcWaitForPortReferences
} ALPC_PORT_INFORMATION_CLASS;

// private
typedef struct _ALPC_BASIC_INFORMATION
{
    ULONG Flags;
    ULONG SequenceNo;
    PVOID PortContext;
} ALPC_BASIC_INFORMATION, *PALPC_BASIC_INFORMATION;

// private
typedef struct _ALPC_PORT_ASSOCIATE_COMPLETION_PORT
{
    PVOID CompletionKey;
    HANDLE CompletionPort;
} ALPC_PORT_ASSOCIATE_COMPLETION_PORT, *PALPC_PORT_ASSOCIATE_COMPLETION_PORT;

// private
typedef struct _ALPC_SERVER_INFORMATION
{
    union
    {
        struct
        {
            HANDLE ThreadHandle;
        } In;
        struct
        {
            BOOLEAN ThreadBlocked;
            HANDLE ConnectedProcessId;
            UNICODE_STRING ConnectionPortName;
        } Out;
    };
} ALPC_SERVER_INFORMATION, *PALPC_SERVER_INFORMATION;

// private
typedef struct _ALPC_PORT_MESSAGE_ZONE_INFORMATION
{
    PVOID Buffer;
    ULONG Size;
} ALPC_PORT_MESSAGE_ZONE_INFORMATION, *PALPC_PORT_MESSAGE_ZONE_INFORMATION;

// private
typedef struct _ALPC_PORT_COMPLETION_LIST_INFORMATION
{
    PVOID Buffer; // PALPC_COMPLETION_LIST_HEADER
    ULONG Size;
    ULONG ConcurrencyCount;
    ULONG AttributeFlags;
} ALPC_PORT_COMPLETION_LIST_INFORMATION, *PALPC_PORT_COMPLETION_LIST_INFORMATION;

// private
typedef enum _ALPC_MESSAGE_INFORMATION_CLASS
{
    AlpcMessageSidInformation, // q: out SID
    AlpcMessageTokenModifiedIdInformation,  // q: out LUID
    AlpcMessageDirectStatusInformation,
    AlpcMessageHandleInformation, // ALPC_MESSAGE_HANDLE_INFORMATION
    MaxAlpcMessageInfoClass
} ALPC_MESSAGE_INFORMATION_CLASS, *PALPC_MESSAGE_INFORMATION_CLASS;

typedef struct _ALPC_MESSAGE_HANDLE_INFORMATION
{
    ULONG Index;
    ULONG Flags;
    ULONG Handle;
    ULONG ObjectType;
    ACCESS_MASK GrantedAccess;
} ALPC_MESSAGE_HANDLE_INFORMATION, *PALPC_MESSAGE_HANDLE_INFORMATION;

// begin_private

#if (NTDDI_VERSION >= NTDDI_VISTA)

// System calls

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcCreatePort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcCreatePort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcDisconnectPort(
    _In_ HANDLE PortHandle,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcDisconnectPort(
    _In_ HANDLE PortHandle,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcQueryInformation(
    _In_opt_ HANDLE PortHandle,
    _In_ ALPC_PORT_INFORMATION_CLASS PortInformationClass,
    _Inout_updates_bytes_to_(Length, *ReturnLength) PVOID PortInformation,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcQueryInformation(
    _In_opt_ HANDLE PortHandle,
    _In_ ALPC_PORT_INFORMATION_CLASS PortInformationClass,
    _Inout_updates_bytes_to_(Length, *ReturnLength) PVOID PortInformation,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcSetInformation(
    _In_ HANDLE PortHandle,
    _In_ ALPC_PORT_INFORMATION_CLASS PortInformationClass,
    _In_reads_bytes_opt_(Length) PVOID PortInformation,
    _In_ ULONG Length
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcSetInformation(
    _In_ HANDLE PortHandle,
    _In_ ALPC_PORT_INFORMATION_CLASS PortInformationClass,
    _In_reads_bytes_opt_(Length) PVOID PortInformation,
    _In_ ULONG Length
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcCreatePortSection(
    _In_ HANDLE PortHandle,
    _In_ ULONG Flags,
    _In_opt_ HANDLE SectionHandle,
    _In_ SIZE_T SectionSize,
    _Out_ PALPC_HANDLE AlpcSectionHandle,
    _Out_ PSIZE_T ActualSectionSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcCreatePortSection(
    _In_ HANDLE PortHandle,
    _In_ ULONG Flags,
    _In_opt_ HANDLE SectionHandle,
    _In_ SIZE_T SectionSize,
    _Out_ PALPC_HANDLE AlpcSectionHandle,
    _Out_ PSIZE_T ActualSectionSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcDeletePortSection(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ ALPC_HANDLE SectionHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcDeletePortSection(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ ALPC_HANDLE SectionHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcCreateResourceReserve(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ SIZE_T MessageSize,
    _Out_ PALPC_HANDLE ResourceId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcCreateResourceReserve(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ SIZE_T MessageSize,
    _Out_ PALPC_HANDLE ResourceId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcDeleteResourceReserve(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ ALPC_HANDLE ResourceId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcDeleteResourceReserve(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ ALPC_HANDLE ResourceId
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcCreateSectionView(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _Inout_ PALPC_DATA_VIEW_ATTR ViewAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcCreateSectionView(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _Inout_ PALPC_DATA_VIEW_ATTR ViewAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcDeleteSectionView(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ PVOID ViewBase
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcDeleteSectionView(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ PVOID ViewBase
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcCreateSecurityContext(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _Inout_ PALPC_SECURITY_ATTR SecurityAttribute
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcCreateSecurityContext(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _Inout_ PALPC_SECURITY_ATTR SecurityAttribute
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcDeleteSecurityContext(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ ALPC_HANDLE ContextHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcDeleteSecurityContext(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ ALPC_HANDLE ContextHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcRevokeSecurityContext(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ ALPC_HANDLE ContextHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcRevokeSecurityContext(
    _In_ HANDLE PortHandle,
    _Reserved_ ULONG Flags,
    _In_ ALPC_HANDLE ContextHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcQueryInformationMessage(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE PortMessage,
    _In_ ALPC_MESSAGE_INFORMATION_CLASS MessageInformationClass,
    _Out_writes_bytes_to_opt_(Length, *ReturnLength) PVOID MessageInformation,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcQueryInformationMessage(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE PortMessage,
    _In_ ALPC_MESSAGE_INFORMATION_CLASS MessageInformationClass,
    _Out_writes_bytes_to_opt_(Length, *ReturnLength) PVOID MessageInformation,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength
    );

#define ALPC_MSGFLG_REPLY_MESSAGE 0x1
#define ALPC_MSGFLG_LPC_MODE 0x2 // ?
#define ALPC_MSGFLG_RELEASE_MESSAGE 0x10000 // dbg
#define ALPC_MSGFLG_SYNC_REQUEST 0x20000 // dbg
#define ALPC_MSGFLG_WAIT_USER_MODE 0x100000
#define ALPC_MSGFLG_WAIT_ALERTABLE 0x200000
#define ALPC_MSGFLG_WOW64_CALL 0x80000000 // dbg

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ PUNICODE_STRING PortName,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes,
    _In_ ULONG Flags,
    _In_opt_ PSID RequiredServerSid,
    _Inout_updates_bytes_to_opt_(*BufferLength, *BufferLength) PPORT_MESSAGE ConnectionMessage,
    _Inout_opt_ PULONG BufferLength,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES OutMessageAttributes,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES InMessageAttributes,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ PUNICODE_STRING PortName,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes,
    _In_ ULONG Flags,
    _In_opt_ PSID RequiredServerSid,
    _Inout_updates_bytes_to_opt_(*BufferLength, *BufferLength) PPORT_MESSAGE ConnectionMessage,
    _Inout_opt_ PULONG BufferLength,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES OutMessageAttributes,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES InMessageAttributes,
    _In_opt_ PLARGE_INTEGER Timeout
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcConnectPortEx(
    _Out_ PHANDLE PortHandle,
    _In_ POBJECT_ATTRIBUTES ConnectionPortObjectAttributes,
    _In_opt_ POBJECT_ATTRIBUTES ClientPortObjectAttributes,
    _In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes,
    _In_ ULONG Flags,
    _In_opt_ PSECURITY_DESCRIPTOR ServerSecurityRequirements,
    _Inout_updates_bytes_to_opt_(*BufferLength, *BufferLength) PPORT_MESSAGE ConnectionMessage,
    _Inout_opt_ PSIZE_T BufferLength,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES OutMessageAttributes,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES InMessageAttributes,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcConnectPortEx(
    _Out_ PHANDLE PortHandle,
    _In_ POBJECT_ATTRIBUTES ConnectionPortObjectAttributes,
    _In_opt_ POBJECT_ATTRIBUTES ClientPortObjectAttributes,
    _In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes,
    _In_ ULONG Flags,
    _In_opt_ PSECURITY_DESCRIPTOR ServerSecurityRequirements,
    _Inout_updates_bytes_to_opt_(*BufferLength, *BufferLength) PPORT_MESSAGE ConnectionMessage,
    _Inout_opt_ PSIZE_T BufferLength,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES OutMessageAttributes,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES InMessageAttributes,
    _In_opt_ PLARGE_INTEGER Timeout
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcAcceptConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ HANDLE ConnectionPortHandle,
    _In_ ULONG Flags,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes,
    _In_opt_ PVOID PortContext,
    _In_reads_bytes_(ConnectionRequest->u1.s1.TotalLength) PPORT_MESSAGE ConnectionRequest,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES ConnectionMessageAttributes,
    _In_ BOOLEAN AcceptConnection
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcAcceptConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ HANDLE ConnectionPortHandle,
    _In_ ULONG Flags,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes,
    _In_opt_ PVOID PortContext,
    _In_reads_bytes_(ConnectionRequest->u1.s1.TotalLength) PPORT_MESSAGE ConnectionRequest,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES ConnectionMessageAttributes,
    _In_ BOOLEAN AcceptConnection
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcSendWaitReceivePort(
    _In_ HANDLE PortHandle,
    _In_ ULONG Flags,
    _In_reads_bytes_opt_(SendMessage->u1.s1.TotalLength) PPORT_MESSAGE SendMessage,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES SendMessageAttributes,
    _Out_writes_bytes_to_opt_(*BufferLength, *BufferLength) PPORT_MESSAGE ReceiveMessage,
    _Inout_opt_ PSIZE_T BufferLength,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES ReceiveMessageAttributes,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcSendWaitReceivePort(
    _In_ HANDLE PortHandle,
    _In_ ULONG Flags,
    _In_reads_bytes_opt_(SendMessage->u1.s1.TotalLength) PPORT_MESSAGE SendMessage,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES SendMessageAttributes,
    _Out_writes_bytes_to_opt_(*BufferLength, *BufferLength) PPORT_MESSAGE ReceiveMessage,
    _Inout_opt_ PSIZE_T BufferLength,
    _Inout_opt_ PALPC_MESSAGE_ATTRIBUTES ReceiveMessageAttributes,
    _In_opt_ PLARGE_INTEGER Timeout
    );

#define ALPC_CANCELFLG_TRY_CANCEL 0x1 // dbg
#define ALPC_CANCELFLG_NO_CONTEXT_CHECK 0x8
#define ALPC_CANCELFLGP_FLUSH 0x10000 // dbg

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcCancelMessage(
    _In_ HANDLE PortHandle,
    _In_ ULONG Flags,
    _In_ PALPC_CONTEXT_ATTR MessageContext
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcCancelMessage(
    _In_ HANDLE PortHandle,
    _In_ ULONG Flags,
    _In_ PALPC_CONTEXT_ATTR MessageContext
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcImpersonateClientOfPort(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message,
    _In_ PVOID Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcImpersonateClientOfPort(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message,
    _In_ PVOID Flags
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcImpersonateClientContainerOfPort(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcImpersonateClientContainerOfPort(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE Message,
    _In_ ULONG Flags
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcOpenSenderProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE PortMessage,
    _In_ ULONG Flags,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcOpenSenderProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE PortMessage,
    _In_ ULONG Flags,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlpcOpenSenderThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE PortMessage,
    _In_ ULONG Flags,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAlpcOpenSenderThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE PortMessage,
    _In_ ULONG Flags,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

// Support functions

NTSYSAPI
ULONG
NTAPI
AlpcMaxAllowedMessageLength(
    VOID
    );

NTSYSAPI
ULONG
NTAPI
AlpcGetHeaderSize(
    _In_ ULONG Flags
    );

#define ALPC_ATTRFLG_ALLOCATEDATTR 0x20000000
#define ALPC_ATTRFLG_VALIDATTR 0x40000000
#define ALPC_ATTRFLG_KEEPRUNNINGATTR 0x60000000

NTSYSAPI
NTSTATUS
NTAPI
AlpcInitializeMessageAttribute(
    _In_ ULONG AttributeFlags,
    _Out_opt_ PALPC_MESSAGE_ATTRIBUTES Buffer,
    _In_ ULONG BufferSize,
    _Out_ PULONG RequiredBufferSize
    );

NTSYSAPI
PVOID
NTAPI
AlpcGetMessageAttribute(
    _In_ PALPC_MESSAGE_ATTRIBUTES Buffer,
    _In_ ULONG AttributeFlag
    );

NTSYSAPI
NTSTATUS
NTAPI
AlpcRegisterCompletionList(
    _In_ HANDLE PortHandle,
    _Out_ PALPC_COMPLETION_LIST_HEADER Buffer,
    _In_ ULONG Size,
    _In_ ULONG ConcurrencyCount,
    _In_ ULONG AttributeFlags
    );

NTSYSAPI
NTSTATUS
NTAPI
AlpcUnregisterCompletionList(
    _In_ HANDLE PortHandle
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
AlpcRundownCompletionList(
    _In_ HANDLE PortHandle
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
AlpcAdjustCompletionListConcurrencyCount(
    _In_ HANDLE PortHandle,
    _In_ ULONG ConcurrencyCount
    );

NTSYSAPI
BOOLEAN
NTAPI
AlpcRegisterCompletionListWorkerThread(
    _Inout_ PVOID CompletionList
    );

NTSYSAPI
BOOLEAN
NTAPI
AlpcUnregisterCompletionListWorkerThread(
    _Inout_ PVOID CompletionList
    );

NTSYSAPI
VOID
NTAPI
AlpcGetCompletionListLastMessageInformation(
    _In_ PVOID CompletionList,
    _Out_ PULONG LastMessageId,
    _Out_ PULONG LastCallbackId
    );

NTSYSAPI
ULONG
NTAPI
AlpcGetOutstandingCompletionListMessageCount(
    _In_ PVOID CompletionList
    );

NTSYSAPI
PPORT_MESSAGE
NTAPI
AlpcGetMessageFromCompletionList(
    _In_ PVOID CompletionList,
    _Out_opt_ PALPC_MESSAGE_ATTRIBUTES *MessageAttributes
    );

NTSYSAPI
VOID
NTAPI
AlpcFreeCompletionListMessage(
    _Inout_ PVOID CompletionList,
    _In_ PPORT_MESSAGE Message
    );

NTSYSAPI
PALPC_MESSAGE_ATTRIBUTES
NTAPI
AlpcGetCompletionListMessageAttributes(
    _In_ PVOID CompletionList,
    _In_ PPORT_MESSAGE Message
    );

#endif

// end_private
 

// #include <ntpfapi.h>
// begin_private

// Prefetch

typedef enum _PF_BOOT_PHASE_ID
{
    PfKernelInitPhase = 0,
    PfBootDriverInitPhase = 90,
    PfSystemDriverInitPhase = 120,
    PfSessionManagerInitPhase = 150,
    PfSMRegistryInitPhase = 180,
    PfVideoInitPhase = 210,
    PfPostVideoInitPhase = 240,
    PfBootAcceptedRegistryInitPhase = 270,
    PfUserShellReadyPhase = 300,
    PfMaxBootPhaseId = 900
} PF_BOOT_PHASE_ID;

typedef enum _PF_ENABLE_STATUS
{
    PfSvNotSpecified,
    PfSvEnabled,
    PfSvDisabled,
    PfSvMaxEnableStatus
} PF_ENABLE_STATUS;

typedef struct _PF_TRACE_LIMITS
{
    ULONG MaxNumPages;
    ULONG MaxNumSections;
    LONGLONG TimerPeriod;
} PF_TRACE_LIMITS, *PPF_TRACE_LIMITS;

typedef struct _PF_SYSTEM_PREFETCH_PARAMETERS
{
    PF_ENABLE_STATUS EnableStatus[2];
    PF_TRACE_LIMITS TraceLimits[2];
    ULONG MaxNumActiveTraces;
    ULONG MaxNumSavedTraces;
    WCHAR RootDirPath[32];
    WCHAR HostingApplicationList[128];
} PF_SYSTEM_PREFETCH_PARAMETERS, *PPF_SYSTEM_PREFETCH_PARAMETERS;

#define PF_BOOT_CONTROL_VERSION 1

typedef struct _PF_BOOT_CONTROL
{
    ULONG Version;
    ULONG DisableBootPrefetching;
} PF_BOOT_CONTROL, *PPF_BOOT_CONTROL;

typedef enum _PREFETCHER_INFORMATION_CLASS
{
    PrefetcherRetrieveTrace = 1, // q: CHAR[]
    PrefetcherSystemParameters, // q: PF_SYSTEM_PREFETCH_PARAMETERS
    PrefetcherBootPhase, // s: PF_BOOT_PHASE_ID
    PrefetcherRetrieveBootLoaderTrace, // q: CHAR[]
    PrefetcherBootControl // s: PF_BOOT_CONTROL
} PREFETCHER_INFORMATION_CLASS;

#define PREFETCHER_INFORMATION_VERSION 23 // rev
#define PREFETCHER_INFORMATION_MAGIC ('kuhC') // rev

typedef struct _PREFETCHER_INFORMATION
{
    ULONG Version;
    ULONG Magic;
    PREFETCHER_INFORMATION_CLASS PrefetcherInformationClass;
    PVOID PrefetcherInformation;
    ULONG PrefetcherInformationLength;
} PREFETCHER_INFORMATION, *PPREFETCHER_INFORMATION;

// Superfetch

typedef struct _PF_SYSTEM_SUPERFETCH_PARAMETERS
{
    ULONG EnabledComponents;
    ULONG BootID;
    ULONG SavedSectInfoTracesMax;
    ULONG SavedPageAccessTracesMax;
    ULONG ScenarioPrefetchTimeoutStandby;
    ULONG ScenarioPrefetchTimeoutHibernate;
} PF_SYSTEM_SUPERFETCH_PARAMETERS, *PPF_SYSTEM_SUPERFETCH_PARAMETERS;

#define PF_PFN_PRIO_REQUEST_VERSION 1
#define PF_PFN_PRIO_REQUEST_QUERY_MEMORY_LIST 0x1
#define PF_PFN_PRIO_REQUEST_VALID_FLAGS 0x1

typedef struct _PF_PFN_PRIO_REQUEST
{
    ULONG Version;
    ULONG RequestFlags;
    ULONG_PTR PfnCount;
    SYSTEM_MEMORY_LIST_INFORMATION MemInfo;
    MMPFN_IDENTITY PageData[256];
} PF_PFN_PRIO_REQUEST, *PPF_PFN_PRIO_REQUEST;

typedef enum _PFS_PRIVATE_PAGE_SOURCE_TYPE
{
    PfsPrivateSourceKernel,
    PfsPrivateSourceSession,
    PfsPrivateSourceProcess,
    PfsPrivateSourceMax
} PFS_PRIVATE_PAGE_SOURCE_TYPE;

typedef struct _PFS_PRIVATE_PAGE_SOURCE
{
    PFS_PRIVATE_PAGE_SOURCE_TYPE Type;
    union
    {
        ULONG SessionId;
        ULONG ProcessId;
    };
    ULONG ImagePathHash;
    ULONG_PTR UniqueProcessHash;
} PFS_PRIVATE_PAGE_SOURCE, *PPFS_PRIVATE_PAGE_SOURCE;

typedef struct _PF_PRIVSOURCE_INFO
{
    PFS_PRIVATE_PAGE_SOURCE DbInfo;
    PVOID EProcess;
    SIZE_T WsPrivatePages;
    SIZE_T TotalPrivatePages;
    ULONG SessionID;
    CHAR ImageName[16];
    union {
        ULONG_PTR WsSwapPages;                 // process only PF_PRIVSOURCE_QUERY_WS_SWAP_PAGES.
        ULONG_PTR SessionPagedPoolPages;       // session only.
        ULONG_PTR StoreSizePages;              // process only PF_PRIVSOURCE_QUERY_STORE_INFO.
    };
    ULONG_PTR WsTotalPages;         // process/session only.
    ULONG DeepFreezeTimeMs;         // process only.
    ULONG ModernApp : 1;            // process only.
    ULONG DeepFrozen : 1;           // process only. If set, DeepFreezeTimeMs contains the time at which the freeze occurred
    ULONG Foreground : 1;           // process only.
    ULONG PerProcessStore : 1;      // process only.
    ULONG Spare : 28;
} PF_PRIVSOURCE_INFO, *PPF_PRIVSOURCE_INFO;

#define PF_PRIVSOURCE_QUERY_REQUEST_VERSION 8

typedef struct _PF_PRIVSOURCE_QUERY_REQUEST
{
    ULONG Version;
    ULONG Flags;
    ULONG InfoCount;
    PF_PRIVSOURCE_INFO InfoArray[1];
} PF_PRIVSOURCE_QUERY_REQUEST, *PPF_PRIVSOURCE_QUERY_REQUEST;

typedef enum _PF_PHASED_SCENARIO_TYPE
{
    PfScenarioTypeNone,
    PfScenarioTypeStandby,
    PfScenarioTypeHibernate,
    PfScenarioTypeFUS,
    PfScenarioTypeMax
} PF_PHASED_SCENARIO_TYPE;

#define PF_SCENARIO_PHASE_INFO_VERSION 4

typedef struct _PF_SCENARIO_PHASE_INFO
{
    ULONG Version;
    PF_PHASED_SCENARIO_TYPE ScenType;
    ULONG PhaseId;
    ULONG SequenceNumber;
    ULONG Flags;
    ULONG FUSUserId;
} PF_SCENARIO_PHASE_INFO, *PPF_SCENARIO_PHASE_INFO;

typedef struct _PF_MEMORY_LIST_NODE
{
    ULONGLONG Node : 8;
    ULONGLONG Spare : 56;
    ULONGLONG StandbyLowPageCount;
    ULONGLONG StandbyMediumPageCount;
    ULONGLONG StandbyHighPageCount;
    ULONGLONG FreePageCount;
    ULONGLONG ModifiedPageCount;
} PF_MEMORY_LIST_NODE, *PPF_MEMORY_LIST_NODE;

#define PF_MEMORY_LIST_INFO_VERSION 1

typedef struct _PF_MEMORY_LIST_INFO
{
    ULONG Version;
    ULONG Size;
    ULONG NodeCount;
    PF_MEMORY_LIST_NODE Nodes[1];
} PF_MEMORY_LIST_INFO, *PPF_MEMORY_LIST_INFO;

typedef struct _PF_PHYSICAL_MEMORY_RANGE
{
    ULONG_PTR BasePfn;
    ULONG_PTR PageCount;
} PF_PHYSICAL_MEMORY_RANGE, *PPF_PHYSICAL_MEMORY_RANGE;

#define PF_PHYSICAL_MEMORY_RANGE_INFO_V1_VERSION 1

typedef struct _PF_PHYSICAL_MEMORY_RANGE_INFO_V1
{
    ULONG Version;
    ULONG RangeCount;
    PF_PHYSICAL_MEMORY_RANGE Ranges[1];
} PF_PHYSICAL_MEMORY_RANGE_INFO_V1, *PPF_PHYSICAL_MEMORY_RANGE_INFO_V1;

#define PF_PHYSICAL_MEMORY_RANGE_INFO_V2_VERSION 2

typedef struct _PF_PHYSICAL_MEMORY_RANGE_INFO_V2
{
    ULONG Version;
    ULONG Flags;
    ULONG RangeCount;
    PF_PHYSICAL_MEMORY_RANGE Ranges[ANYSIZE_ARRAY];
} PF_PHYSICAL_MEMORY_RANGE_INFO_V2, *PPF_PHYSICAL_MEMORY_RANGE_INFO_V2;

// begin_rev

#define PF_REPURPOSED_BY_PREFETCH_INFO_VERSION 1

typedef struct _PF_REPURPOSED_BY_PREFETCH_INFO
{
    ULONG Version;
    ULONG RepurposedByPrefetch;
} PF_REPURPOSED_BY_PREFETCH_INFO, *PPF_REPURPOSED_BY_PREFETCH_INFO;

// end_rev

typedef enum _SUPERFETCH_INFORMATION_CLASS
{
    SuperfetchRetrieveTrace = 1, // q: CHAR[]
    SuperfetchSystemParameters, // q: PF_SYSTEM_SUPERFETCH_PARAMETERS
    SuperfetchLogEvent,
    SuperfetchGenerateTrace,
    SuperfetchPrefetch,
    SuperfetchPfnQuery, // q: PF_PFN_PRIO_REQUEST
    SuperfetchPfnSetPriority,
    SuperfetchPrivSourceQuery, // q: PF_PRIVSOURCE_QUERY_REQUEST
    SuperfetchSequenceNumberQuery, // q: ULONG
    SuperfetchScenarioPhase, // 10
    SuperfetchWorkerPriority,
    SuperfetchScenarioQuery, // q: PF_SCENARIO_PHASE_INFO
    SuperfetchScenarioPrefetch,
    SuperfetchRobustnessControl,
    SuperfetchTimeControl,
    SuperfetchMemoryListQuery, // q: PF_MEMORY_LIST_INFO
    SuperfetchMemoryRangesQuery, // q: PF_PHYSICAL_MEMORY_RANGE_INFO
    SuperfetchTracingControl,
    SuperfetchTrimWhileAgingControl,
    SuperfetchRepurposedByPrefetch, // q: PF_REPURPOSED_BY_PREFETCH_INFO // rev
    SuperfetchInformationMax
} SUPERFETCH_INFORMATION_CLASS;

#define SUPERFETCH_INFORMATION_VERSION 45 // rev
#define SUPERFETCH_INFORMATION_MAGIC ('kuhC') // rev

typedef struct _SUPERFETCH_INFORMATION
{
    _In_ ULONG Version;
    _In_ ULONG Magic;
    _In_ SUPERFETCH_INFORMATION_CLASS InfoClass;
    _Inout_ PVOID Data;
    _Inout_ ULONG Length;
} SUPERFETCH_INFORMATION, *PSUPERFETCH_INFORMATION;

// end_private
 

// #include <ntpnpapi.h>
typedef enum _PLUGPLAY_EVENT_CATEGORY
{
    HardwareProfileChangeEvent,
    TargetDeviceChangeEvent,
    DeviceClassChangeEvent,
    CustomDeviceEvent,
    DeviceInstallEvent,
    DeviceArrivalEvent,
    PowerEvent,
    VetoEvent,
    BlockedDriverEvent,
    InvalidIDEvent,
    MaxPlugEventCategory
} PLUGPLAY_EVENT_CATEGORY, *PPLUGPLAY_EVENT_CATEGORY;

typedef struct _PLUGPLAY_EVENT_BLOCK
{
    GUID EventGuid;
    PLUGPLAY_EVENT_CATEGORY EventCategory;
    PULONG Result;
    ULONG Flags;
    ULONG TotalSize;
    PVOID DeviceObject;

    union
    {
        struct
        {
            GUID ClassGuid;
            WCHAR SymbolicLinkName[1];
        } DeviceClass;
        struct
        {
            WCHAR DeviceIds[1];
        } TargetDevice;
        struct
        {
            WCHAR DeviceId[1];
        } InstallDevice;
        struct
        {
            PVOID NotificationStructure;
            WCHAR DeviceIds[1];
        } CustomNotification;
        struct
        {
            PVOID Notification;
        } ProfileNotification;
        struct
        {
            ULONG NotificationCode;
            ULONG NotificationData;
        } PowerNotification;
        struct
        {
            PNP_VETO_TYPE VetoType;
            WCHAR DeviceIdVetoNameBuffer[1]; // DeviceId<null>VetoName<null><null>
        } VetoNotification;
        struct
        {
            GUID BlockedDriverGuid;
        } BlockedDriverNotification;
        struct
        {
            WCHAR ParentId[1];
        } InvalidIDNotification;
    } u;
} PLUGPLAY_EVENT_BLOCK, *PPLUGPLAY_EVENT_BLOCK;

typedef enum _PLUGPLAY_CONTROL_CLASS
{
    PlugPlayControlEnumerateDevice, // PLUGPLAY_CONTROL_ENUMERATE_DEVICE_DATA
    PlugPlayControlRegisterNewDevice, // PLUGPLAY_CONTROL_DEVICE_CONTROL_DATA
    PlugPlayControlDeregisterDevice, // PLUGPLAY_CONTROL_DEVICE_CONTROL_DATA
    PlugPlayControlInitializeDevice, // PLUGPLAY_CONTROL_DEVICE_CONTROL_DATA
    PlugPlayControlStartDevice, // PLUGPLAY_CONTROL_DEVICE_CONTROL_DATA
    PlugPlayControlUnlockDevice, // PLUGPLAY_CONTROL_DEVICE_CONTROL_DATA
    PlugPlayControlQueryAndRemoveDevice, // PLUGPLAY_CONTROL_QUERY_AND_REMOVE_DATA
    PlugPlayControlUserResponse, // PLUGPLAY_CONTROL_USER_RESPONSE_DATA
    PlugPlayControlGenerateLegacyDevice, // PLUGPLAY_CONTROL_LEGACY_DEVGEN_DATA
    PlugPlayControlGetInterfaceDeviceList, // PLUGPLAY_CONTROL_INTERFACE_LIST_DATA
    PlugPlayControlProperty, // PLUGPLAY_CONTROL_PROPERTY_DATA
    PlugPlayControlDeviceClassAssociation, // PLUGPLAY_CONTROL_CLASS_ASSOCIATION_DATA
    PlugPlayControlGetRelatedDevice, // PLUGPLAY_CONTROL_RELATED_DEVICE_DATA
    PlugPlayControlGetInterfaceDeviceAlias, // PLUGPLAY_CONTROL_INTERFACE_ALIAS_DATA
    PlugPlayControlDeviceStatus, // PLUGPLAY_CONTROL_STATUS_DATA
    PlugPlayControlGetDeviceDepth, // PLUGPLAY_CONTROL_DEPTH_DATA
    PlugPlayControlQueryDeviceRelations, // PLUGPLAY_CONTROL_DEVICE_RELATIONS_DATA
    PlugPlayControlTargetDeviceRelation, // PLUGPLAY_CONTROL_TARGET_RELATION_DATA
    PlugPlayControlQueryConflictList, // PLUGPLAY_CONTROL_CONFLICT_LIST
    PlugPlayControlRetrieveDock, // PLUGPLAY_CONTROL_RETRIEVE_DOCK_DATA
    PlugPlayControlResetDevice, // PLUGPLAY_CONTROL_DEVICE_CONTROL_DATA
    PlugPlayControlHaltDevice, // PLUGPLAY_CONTROL_DEVICE_CONTROL_DATA
    PlugPlayControlGetBlockedDriverList, // PLUGPLAY_CONTROL_BLOCKED_DRIVER_DATA
    PlugPlayControlGetDeviceInterfaceEnabled, // PLUGPLAY_CONTROL_DEVICE_INTERFACE_ENABLED
    MaxPlugPlayControl
} PLUGPLAY_CONTROL_CLASS, *PPLUGPLAY_CONTROL_CLASS;

#if (NTDDI_VERSION < NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetPlugPlayEvent(
    _In_ HANDLE EventHandle,
    _In_opt_ PVOID Context,
    _Out_writes_bytes_(EventBufferSize) PPLUGPLAY_EVENT_BLOCK EventBlock,
    _In_ ULONG EventBufferSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetPlugPlayEvent(
    _In_ HANDLE EventHandle,
    _In_opt_ PVOID Context,
    _Out_writes_bytes_(EventBufferSize) PPLUGPLAY_EVENT_BLOCK EventBlock,
    _In_ ULONG EventBufferSize
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtPlugPlayControl(
    _In_ PLUGPLAY_CONTROL_CLASS PnPControlClass,
    _Inout_updates_bytes_(PnPControlDataLength) PVOID PnPControlData,
    _In_ ULONG PnPControlDataLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPlugPlayControl(
    _In_ PLUGPLAY_CONTROL_CLASS PnPControlClass,
    _Inout_updates_bytes_(PnPControlDataLength) PVOID PnPControlData,
    _In_ ULONG PnPControlDataLength
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSerializeBoot(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSerializeBoot(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnableLastKnownGood(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwEnableLastKnownGood(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDisableLastKnownGood(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDisableLastKnownGood(
    VOID
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtReplacePartitionUnit(
    _In_ PUNICODE_STRING TargetInstancePath,
    _In_ PUNICODE_STRING SpareInstancePath,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReplacePartitionUnit(
    _In_ PUNICODE_STRING TargetInstancePath,
    _In_ PUNICODE_STRING SpareInstancePath,
    _In_ ULONG Flags
    );
#endif
 

// #include <ntpoapi.h>
typedef union _POWER_STATE
{
    SYSTEM_POWER_STATE SystemState;
    DEVICE_POWER_STATE DeviceState;
} POWER_STATE, *PPOWER_STATE;

typedef enum _POWER_STATE_TYPE
{
    SystemPowerState = 0,
    DevicePowerState
} POWER_STATE_TYPE, *PPOWER_STATE_TYPE;

#if (NTDDI_VERSION >= NTDDI_VISTA)
// wdm
typedef struct _SYSTEM_POWER_STATE_CONTEXT
{
    union
    {
        struct
        {
            ULONG Reserved1 : 8;
            ULONG TargetSystemState : 4;
            ULONG EffectiveSystemState : 4;
            ULONG CurrentSystemState : 4;
            ULONG IgnoreHibernationPath : 1;
            ULONG PseudoTransition : 1;
            ULONG Reserved2 : 10;
        };
        ULONG ContextAsUlong;
    };
} SYSTEM_POWER_STATE_CONTEXT, *PSYSTEM_POWER_STATE_CONTEXT;
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
#define  POWER_REQUEST_CONTEXT_NOT_SPECIFIED DIAGNOSTIC_REASON_NOT_SPECIFIED

/** \cond NEVER */ // disable doxygen warning
// wdm
typedef struct _COUNTED_REASON_CONTEXT
{
    ULONG Version;
    ULONG Flags;
    union
    {
        struct
        {
            UNICODE_STRING ResourceFileName;
            USHORT ResourceReasonId;
            ULONG StringCount;
            PUNICODE_STRING _Field_size_(StringCount) ReasonStrings;
        };
        UNICODE_STRING SimpleString;
    };
} COUNTED_REASON_CONTEXT, *PCOUNTED_REASON_CONTEXT;
/** \endcond */
#endif

typedef enum _POWER_STATE_HANDLER_TYPE
{
    PowerStateSleeping1 = 0,
    PowerStateSleeping2 = 1,
    PowerStateSleeping3 = 2,
    PowerStateSleeping4 = 3,
    PowerStateShutdownOff = 4,
    PowerStateShutdownReset = 5,
    PowerStateSleeping4Firmware = 6,
    PowerStateMaximum = 7
} POWER_STATE_HANDLER_TYPE, *PPOWER_STATE_HANDLER_TYPE;

typedef NTSTATUS (NTAPI *PENTER_STATE_SYSTEM_HANDLER)(
    _In_ PVOID SystemContext
    );

typedef NTSTATUS (NTAPI *PENTER_STATE_HANDLER)(
    _In_ PVOID Context,
    _In_opt_ PENTER_STATE_SYSTEM_HANDLER SystemHandler,
    _In_ PVOID SystemContext,
    _In_ LONG NumberProcessors,
    _In_ LONG volatile *Number
    );

typedef struct _POWER_STATE_HANDLER
{
    POWER_STATE_HANDLER_TYPE Type;
    BOOLEAN RtcWake;
    UCHAR Spare[3];
    PENTER_STATE_HANDLER Handler;
    PVOID Context;
} POWER_STATE_HANDLER, *PPOWER_STATE_HANDLER;

typedef NTSTATUS (NTAPI *PENTER_STATE_NOTIFY_HANDLER)(
    _In_ POWER_STATE_HANDLER_TYPE State,
    _In_ PVOID Context,
    _In_ BOOLEAN Entering
    );

typedef struct _POWER_STATE_NOTIFY_HANDLER
{
    PENTER_STATE_NOTIFY_HANDLER Handler;
    PVOID Context;
} POWER_STATE_NOTIFY_HANDLER, *PPOWER_STATE_NOTIFY_HANDLER;

// POWER_INFORMATION_LEVEL
// Note: We don't use an enum for these values to minimize conflicts with the Windows SDK. (dmex)
#define SystemPowerPolicyAc 0 // SYSTEM_POWER_POLICY // GET: InputBuffer NULL. SET: InputBuffer not NULL.
#define SystemPowerPolicyDc 1 // SYSTEM_POWER_POLICY
#define VerifySystemPolicyAc 2 // SYSTEM_POWER_POLICY
#define VerifySystemPolicyDc 3 // SYSTEM_POWER_POLICY
#define SystemPowerCapabilities 4 // SYSTEM_POWER_CAPABILITIES
#define SystemBatteryState 5 // SYSTEM_BATTERY_STATE
#define SystemPowerStateHandler 6 // (kernel-mode only)
#define ProcessorStateHandler 7 // (kernel-mode only)
#define SystemPowerPolicyCurrent 8 // SYSTEM_POWER_POLICY
#define AdministratorPowerPolicy 9 // ADMINISTRATOR_POWER_POLICY
#define SystemReserveHiberFile 10 // BOOLEAN // (requires SeCreatePagefilePrivilege) // TRUE: hibernation file created. FALSE: hibernation file deleted.
#define ProcessorInformation 11 // PROCESSOR_POWER_INFORMATION
#define SystemPowerInformation 12 // SYSTEM_POWER_INFORMATION
#define ProcessorStateHandler2 13 // not implemented
#define LastWakeTime 14 // ULONGLONG
#define LastSleepTime 15 // ULONGLONG
#define SystemExecutionState 16 // EXECUTION_STATE // NtSetThreadExecutionState
#define SystemPowerStateNotifyHandler 17 // (kernel-mode only)
#define ProcessorPowerPolicyAc 18 // not implemented
#define ProcessorPowerPolicyDc 19 // not implemented
#define VerifyProcessorPowerPolicyAc 20 // not implemented
#define VerifyProcessorPowerPolicyDc 21 // not implemented
#define ProcessorPowerPolicyCurrent 22 // not implemented
#define SystemPowerStateLogging 23
#define SystemPowerLoggingEntry 24 // (kernel-mode only)
#define SetPowerSettingValue 25 // (kernel-mode only)
#define NotifyUserPowerSetting 26 // not implemented
#define PowerInformationLevelUnused0 27 // not implemented
#define SystemMonitorHiberBootPowerOff 28 // NULL (PowerMonitorOff)
#define SystemVideoState 29 // MONITOR_DISPLAY_STATE
#define TraceApplicationPowerMessage 30 // (kernel-mode only)
#define TraceApplicationPowerMessageEnd 31 // (kernel-mode only)
#define ProcessorPerfStates 32 // (kernel-mode only)
#define ProcessorIdleStates 33 // (kernel-mode only)
#define ProcessorCap 34 // (kernel-mode only)
#define SystemWakeSource 35
#define SystemHiberFileInformation 36
#define TraceServicePowerMessage 37
#define ProcessorLoad 38
#define PowerShutdownNotification 39 // (kernel-mode only)
#define MonitorCapabilities 40 // (kernel-mode only)
#define SessionPowerInit 41 // (kernel-mode only)
#define SessionDisplayState 42 // (kernel-mode only)
#define PowerRequestCreate 43 // in: COUNTED_REASON_CONTEXT, out: HANDLE
#define PowerRequestAction 44 // in: POWER_REQUEST_ACTION
#define GetPowerRequestList 45 // out: POWER_REQUEST_LIST
#define ProcessorInformationEx 46 // in: USHORT, out: PROCESSOR_POWER_INFORMATION
#define NotifyUserModeLegacyPowerEvent 47 // (kernel-mode only)
#define GroupPark 48 // (debug-mode boot only) 
#define ProcessorIdleDomains 49 // (kernel-mode only)
#define WakeTimerList 50 // powercfg.exe /waketimers
#define SystemHiberFileSize 51 // ULONG
#define ProcessorIdleStatesHv 52 // (kernel-mode only)
#define ProcessorPerfStatesHv 53 // (kernel-mode only)
#define ProcessorPerfCapHv 54 // (kernel-mode only)
#define ProcessorSetIdle 55 // (debug-mode boot only) 
#define LogicalProcessorIdling 56 // (kernel-mode only)
#define UserPresence 57 // not implemented
#define PowerSettingNotificationName 58
#define GetPowerSettingValue 59 // GUID
#define IdleResiliency 60 // POWER_IDLE_RESILIENCY
#define SessionRITState 61 // (kernel-mode only)
#define SessionConnectNotification 62 // (kernel-mode only)
#define SessionPowerCleanup 63 // (kernel-mode only)
#define SessionLockState 64
#define SystemHiberbootState 65 // BOOLEAN // fast startup supported
#define PlatformInformation 66 // BOOLEAN // connected standby supported
#define PdcInvocation 67 // (kernel-mode only)
#define MonitorInvocation 68 // (kernel-mode only)
#define FirmwareTableInformationRegistered 69 // (kernel-mode only)
#define SetShutdownSelectedTime 70 // NULL
#define SuspendResumeInvocation 71 // (kernel-mode only)
#define PlmPowerRequestCreate 72 // in: COUNTED_REASON_CONTEXT, out: HANDLE
#define ScreenOff 73 // NULL (PowerMonitorOff)
#define CsDeviceNotification 74 // (kernel-mode only)
#define PlatformRole 75 // POWER_PLATFORM_ROLE
#define LastResumePerformance 76 // RESUME_PERFORMANCE
#define DisplayBurst 77 // NULL (PowerMonitorOn)
#define ExitLatencySamplingPercentage 78
#define RegisterSpmPowerSettings 79 // (kernel-mode only)
#define PlatformIdleStates 80 // (kernel-mode only)
#define ProcessorIdleVeto 81 // (kernel-mode only) // deprecated
#define PlatformIdleVeto 82 // (kernel-mode only) // deprecated
#define SystemBatteryStatePrecise 83 // SYSTEM_BATTERY_STATE
#define ThermalEvent 84  // THERMAL_EVENT // PowerReportThermalEvent
#define PowerRequestActionInternal 85 // (kernel-mode only)
#define BatteryDeviceState 86
#define PowerInformationInternal 87
#define ThermalStandby 88 // NULL // shutdown with thermal standby as reason.
#define SystemHiberFileType 89 // ULONG // zero ? reduced : full // powercfg.exe /h /type 
#define PhysicalPowerButtonPress 90 // BOOLEAN
#define QueryPotentialDripsConstraint 91 // (kernel-mode only)
#define EnergyTrackerCreate 92
#define EnergyTrackerQuery 93
#define UpdateBlackBoxRecorder 94
#define SessionAllowExternalDmaDevices 95
#define PowerInformationLevelMaximum 96

#if (NTDDI_VERSION >= NTDDI_WIN7)
// POWER_REQUEST_TYPE
// Note: We don't use an enum since it conflicts with the Windows SDK.
#define PowerRequestDisplayRequired 0
#define PowerRequestSystemRequired 1
#define PowerRequestAwayModeRequired 2
#define PowerRequestExecutionRequired 3        // Windows 8+
#define PowerRequestPerfBoostRequired 4        // Windows 8+
#define PowerRequestActiveLockScreenRequired 5 // Windows 10 RS1+ (reserved on Windows 8)
// Values 6 and 7 are reserved for Windows 8 only
#define PowerRequestFullScreenVideoRequired 8  // Windows 8 only

typedef struct _POWER_REQUEST_ACTION
{
    HANDLE PowerRequest;
    POWER_REQUEST_TYPE RequestType;
    BOOLEAN Enable;
    HANDLE TargetProcess; // Windows 8+ and only for requests created via PlmPowerRequestCreate
} POWER_REQUEST_ACTION, * PPOWER_REQUEST_ACTION;

typedef struct _POWER_REQUEST_LIST
{
    ULONG_PTR cElements;
    ULONG_PTR OffsetsToRequests[ANYSIZE_ARRAY]; // PPOWER_REQUEST
} POWER_REQUEST_LIST, *PPOWER_REQUEST_LIST;

typedef enum _POWER_REQUEST_ORIGIN
{
    POWER_REQUEST_ORIGIN_DRIVER = 0,
    POWER_REQUEST_ORIGIN_PROCESS = 1,
    POWER_REQUEST_ORIGIN_SERVICE = 2
} POWER_REQUEST_ORIGIN;

typedef struct _POWER_REQUEST_BODY
{
    ULONG_PTR cbSize;
    POWER_REQUEST_ORIGIN Origin;
    ULONG_PTR OffsetToRequester; // PWSTR
    union
    {
        struct
        {
            ULONG ProcessId;
            ULONG ServiceTag;
        };
        ULONG_PTR OffsetToDriverName; // PWSTR
    };    
    ULONG_PTR OffsetToContext; // PCOUNTED_REASON_CONTEXT_RELATIVE
} POWER_REQUEST_BODY, *PPOWER_REQUEST_BODY;

// The number of supported request types per version
#define POWER_REQUEST_SUPPORTED_TYPES_V1 3 // Windows 7
#define POWER_REQUEST_SUPPORTED_TYPES_V2 9 // Windows 8
#define POWER_REQUEST_SUPPORTED_TYPES_V3 5 // Windows 8.1 and Windows 10 TH1-TH2
#define POWER_REQUEST_SUPPORTED_TYPES_V4 6 // Windows 10 RS1+

typedef struct _POWER_REQUEST
{
    union
    {
        struct
        {
            ULONG Reserved;
            ULONG ActiveCount[POWER_REQUEST_SUPPORTED_TYPES_V1];
            POWER_REQUEST_BODY Body;
        } V1;
#if (NTDDI_VERSION >= NTDDI_WIN8)
        struct
        {
            ULONG Reserved;
            ULONG ActiveCount[POWER_REQUEST_SUPPORTED_TYPES_V2];
            POWER_REQUEST_BODY Body;
        } V2;
#endif
#if (NTDDI_VERSION >= NTDDI_WINBLUE)
        struct
        {
            ULONG Reserved;
            ULONG ActiveCount[POWER_REQUEST_SUPPORTED_TYPES_V3];
            POWER_REQUEST_BODY Body;
        } V3;
#endif
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
        struct
        {
            ULONG Reserved;
            ULONG ActiveCount[POWER_REQUEST_SUPPORTED_TYPES_V4];
            POWER_REQUEST_BODY Body;
        } V4;
#endif
    };
} POWER_REQUEST, *PPOWER_REQUEST;

typedef struct _COUNTED_REASON_CONTEXT_RELATIVE
{
    ULONG Flags;
    union
    {
        struct
        {
            ULONG_PTR OffsetToResourceFileName;
            USHORT ResourceReasonId;
            ULONG StringCount;
            ULONG_PTR OffsetToReasonStrings;
        };
        ULONG_PTR OffsetToSimpleString;
    };
} COUNTED_REASON_CONTEXT_RELATIVE, *PCOUNTED_REASON_CONTEXT_RELATIVE;
#endif

typedef struct _PROCESSOR_POWER_INFORMATION
{
    ULONG Number;
    ULONG MaxMhz;
    ULONG CurrentMhz;
    ULONG MhzLimit;
    ULONG MaxIdleState;
    ULONG CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;

typedef struct _SYSTEM_POWER_INFORMATION
{
    ULONG MaxIdlenessAllowed;
    ULONG Idleness;
    ULONG TimeRemaining;
    UCHAR CoolingMode;
} SYSTEM_POWER_INFORMATION, *PSYSTEM_POWER_INFORMATION;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtPowerInformation(
    _In_ POWER_INFORMATION_LEVEL InformationLevel,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPowerInformation(
    _In_ POWER_INFORMATION_LEVEL InformationLevel,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetThreadExecutionState(
    _In_ EXECUTION_STATE NewFlags, // ES_* flags
    _Out_ EXECUTION_STATE *PreviousFlags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetThreadExecutionState(
    _In_ EXECUTION_STATE NewFlags, // ES_* flags
    _Out_ EXECUTION_STATE *PreviousFlags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRequestWakeupLatency(
    _In_ LATENCY_TIME latency
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRequestWakeupLatency(
    _In_ LATENCY_TIME latency
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtInitiatePowerAction(
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags, // POWER_ACTION_* flags
    _In_ BOOLEAN Asynchronous
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwInitiatePowerAction(
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags, // POWER_ACTION_* flags
    _In_ BOOLEAN Asynchronous
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetSystemPowerState(
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags // POWER_ACTION_* flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetSystemPowerState(
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags // POWER_ACTION_* flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetDevicePowerState(
    _In_ HANDLE Device,
    _Out_ PDEVICE_POWER_STATE State
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetDevicePowerState(
    _In_ HANDLE Device,
    _Out_ PDEVICE_POWER_STATE State
    );

NTSYSCALLAPI
BOOLEAN
NTAPI
NtIsSystemResumeAutomatic(
    VOID
    );

NTSYSCALLAPI
BOOLEAN
NTAPI
ZwIsSystemResumeAutomatic(
    VOID
    );
 

// #include <ntregapi.h>
// Boot condition flags (NtInitializeRegistry)

#define REG_INIT_BOOT_SM 0x0000
#define REG_INIT_BOOT_SETUP 0x0001
#define REG_INIT_BOOT_ACCEPTED_BASE 0x0002
#define REG_INIT_BOOT_ACCEPTED_MAX REG_INIT_BOOT_ACCEPTED_BASE + 999

#define REG_MAX_KEY_VALUE_NAME_LENGTH 32767
#define REG_MAX_KEY_NAME_LENGTH 512

typedef enum _KEY_INFORMATION_CLASS
{
    KeyBasicInformation, // KEY_BASIC_INFORMATION
    KeyNodeInformation, // KEY_NODE_INFORMATION
    KeyFullInformation, // KEY_FULL_INFORMATION
    KeyNameInformation, // KEY_NAME_INFORMATION
    KeyCachedInformation, // KEY_CACHED_INFORMATION
    KeyFlagsInformation, // KEY_FLAGS_INFORMATION
    KeyVirtualizationInformation, // KEY_VIRTUALIZATION_INFORMATION
    KeyHandleTagsInformation, // KEY_HANDLE_TAGS_INFORMATION
    KeyTrustInformation, // KEY_TRUST_INFORMATION
    KeyLayerInformation, // KEY_LAYER_INFORMATION
    MaxKeyInfoClass
} KEY_INFORMATION_CLASS;

typedef struct _KEY_BASIC_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
    ULONG TitleIndex;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_BASIC_INFORMATION, *PKEY_BASIC_INFORMATION;

typedef struct _KEY_NODE_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
    ULONG TitleIndex;
    ULONG ClassOffset;
    ULONG ClassLength;
    ULONG NameLength;
    WCHAR Name[1];
    // ...
    // WCHAR Class[1];
} KEY_NODE_INFORMATION, *PKEY_NODE_INFORMATION;

typedef struct _KEY_FULL_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
    ULONG TitleIndex;
    ULONG ClassOffset;
    ULONG ClassLength;
    ULONG SubKeys;
    ULONG MaxNameLen;
    ULONG MaxClassLen;
    ULONG Values;
    ULONG MaxValueNameLen;
    ULONG MaxValueDataLen;
    WCHAR Class[1];
} KEY_FULL_INFORMATION, *PKEY_FULL_INFORMATION;

typedef struct _KEY_NAME_INFORMATION
{
    ULONG NameLength;
    WCHAR Name[1];
} KEY_NAME_INFORMATION, *PKEY_NAME_INFORMATION;

typedef struct _KEY_CACHED_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
    ULONG TitleIndex;
    ULONG SubKeys;
    ULONG MaxNameLen;
    ULONG Values;
    ULONG MaxValueNameLen;
    ULONG MaxValueDataLen;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_CACHED_INFORMATION, *PKEY_CACHED_INFORMATION;

typedef struct _KEY_FLAGS_INFORMATION
{
    ULONG UserFlags;
} KEY_FLAGS_INFORMATION, *PKEY_FLAGS_INFORMATION;

typedef struct _KEY_VIRTUALIZATION_INFORMATION
{
    ULONG VirtualizationCandidate : 1; // Tells whether the key is part of the virtualization namespace scope (only HKLM\Software for now).
    ULONG VirtualizationEnabled : 1; // Tells whether virtualization is enabled on this key. Can be 1 only if above flag is 1.
    ULONG VirtualTarget : 1; // Tells if the key is a virtual key. Can be 1 only if above 2 are 0. Valid only on the virtual store key handles.
    ULONG VirtualStore : 1; // Tells if the key is a part of the virtual store path. Valid only on the virtual store key handles.
    ULONG VirtualSource : 1; // Tells if the key has ever been virtualized, can be 1 only if VirtualizationCandidate is 1.
    ULONG Reserved : 27;
} KEY_VIRTUALIZATION_INFORMATION, *PKEY_VIRTUALIZATION_INFORMATION;

// private
typedef struct _KEY_TRUST_INFORMATION
{
    ULONG TrustedKey : 1;
    ULONG Reserved : 31;
} KEY_TRUST_INFORMATION, *PKEY_TRUST_INFORMATION;

// private
typedef struct _KEY_LAYER_INFORMATION
{
    ULONG IsTombstone;
    ULONG IsSupersedeLocal;
    ULONG IsSupersedeTree;
    ULONG ClassIsInherited;
    ULONG Reserved;
} KEY_LAYER_INFORMATION, *PKEY_LAYER_INFORMATION;

typedef enum _KEY_SET_INFORMATION_CLASS
{
    KeyWriteTimeInformation, // KEY_WRITE_TIME_INFORMATION
    KeyWow64FlagsInformation, // KEY_WOW64_FLAGS_INFORMATION
    KeyControlFlagsInformation, // KEY_CONTROL_FLAGS_INFORMATION
    KeySetVirtualizationInformation, // KEY_SET_VIRTUALIZATION_INFORMATION
    KeySetDebugInformation,
    KeySetHandleTagsInformation, // KEY_HANDLE_TAGS_INFORMATION
    KeySetLayerInformation, // KEY_SET_LAYER_INFORMATION
    MaxKeySetInfoClass
} KEY_SET_INFORMATION_CLASS;

typedef struct _KEY_WRITE_TIME_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
} KEY_WRITE_TIME_INFORMATION, *PKEY_WRITE_TIME_INFORMATION;

typedef struct _KEY_WOW64_FLAGS_INFORMATION
{
    ULONG UserFlags;
} KEY_WOW64_FLAGS_INFORMATION, *PKEY_WOW64_FLAGS_INFORMATION;

typedef struct _KEY_HANDLE_TAGS_INFORMATION
{
    ULONG HandleTags;
} KEY_HANDLE_TAGS_INFORMATION, *PKEY_HANDLE_TAGS_INFORMATION;

typedef struct _KEY_SET_LAYER_INFORMATION
{
    ULONG IsTombstone : 1;
    ULONG IsSupersedeLocal : 1;
    ULONG IsSupersedeTree : 1;
    ULONG ClassIsInherited : 1;
    ULONG Reserved : 28;
} KEY_SET_LAYER_INFORMATION, *PKEY_SET_LAYER_INFORMATION;

typedef struct _KEY_CONTROL_FLAGS_INFORMATION
{
    ULONG ControlFlags;
} KEY_CONTROL_FLAGS_INFORMATION, *PKEY_CONTROL_FLAGS_INFORMATION;

typedef struct _KEY_SET_VIRTUALIZATION_INFORMATION
{
    ULONG VirtualTarget : 1;
    ULONG VirtualStore : 1;
    ULONG VirtualSource : 1; // true if key has been virtualized at least once
    ULONG Reserved : 29;
} KEY_SET_VIRTUALIZATION_INFORMATION, *PKEY_SET_VIRTUALIZATION_INFORMATION;

typedef enum _KEY_VALUE_INFORMATION_CLASS
{
    KeyValueBasicInformation, // KEY_VALUE_BASIC_INFORMATION
    KeyValueFullInformation, // KEY_VALUE_FULL_INFORMATION
    KeyValuePartialInformation, // KEY_VALUE_PARTIAL_INFORMATION
    KeyValueFullInformationAlign64,
    KeyValuePartialInformationAlign64,  // KEY_VALUE_PARTIAL_INFORMATION_ALIGN64
    KeyValueLayerInformation, // KEY_VALUE_LAYER_INFORMATION
    MaxKeyValueInfoClass
} KEY_VALUE_INFORMATION_CLASS;

typedef struct _KEY_VALUE_BASIC_INFORMATION
{
    ULONG TitleIndex;
    ULONG Type;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_VALUE_BASIC_INFORMATION, *PKEY_VALUE_BASIC_INFORMATION;

typedef struct _KEY_VALUE_FULL_INFORMATION
{
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataOffset;
    ULONG DataLength;
    ULONG NameLength;
    WCHAR Name[1];
    // ...
    // UCHAR Data[1];
} KEY_VALUE_FULL_INFORMATION, *PKEY_VALUE_FULL_INFORMATION;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION
{
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataLength;
    UCHAR Data[1];
} KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION_ALIGN64
{
    ULONG Type;
    ULONG DataLength;
    UCHAR Data[1];
} KEY_VALUE_PARTIAL_INFORMATION_ALIGN64, *PKEY_VALUE_PARTIAL_INFORMATION_ALIGN64;

// private
typedef struct _KEY_VALUE_LAYER_INFORMATION
{
    ULONG IsTombstone;
    ULONG Reserved;
} KEY_VALUE_LAYER_INFORMATION, *PKEY_VALUE_LAYER_INFORMATION;

typedef struct _KEY_VALUE_ENTRY
{
    PUNICODE_STRING ValueName;
    ULONG DataLength;
    ULONG DataOffset;
    ULONG Type;
} KEY_VALUE_ENTRY, *PKEY_VALUE_ENTRY;

typedef enum _REG_ACTION
{
    KeyAdded,
    KeyRemoved,
    KeyModified
} REG_ACTION;

typedef struct _REG_NOTIFY_INFORMATION
{
    ULONG NextEntryOffset;
    REG_ACTION Action;
    ULONG KeyLength;
    WCHAR Key[1];
} REG_NOTIFY_INFORMATION, *PREG_NOTIFY_INFORMATION;

typedef struct _KEY_PID_ARRAY
{
    HANDLE ProcessId;
    UNICODE_STRING KeyName;
} KEY_PID_ARRAY, *PKEY_PID_ARRAY;

typedef struct _KEY_OPEN_SUBKEYS_INFORMATION
{
    ULONG Count;
    KEY_PID_ARRAY KeyArray[1];
} KEY_OPEN_SUBKEYS_INFORMATION, *PKEY_OPEN_SUBKEYS_INFORMATION;

// System calls

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _In_ HANDLE TransactionHandle,
    _Out_opt_ PULONG Disposition
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _In_ HANDLE TransactionHandle,
    _Out_opt_ PULONG Disposition
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE TransactionHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE TransactionHandle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKeyEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenKeyEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKeyTransactedEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions,
    _In_ HANDLE TransactionHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenKeyTransactedEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions,
    _In_ HANDLE TransactionHandle
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteKey(
    _In_ HANDLE KeyHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteKey(
    _In_ HANDLE KeyHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRenameKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING NewName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRenameKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING NewName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryKey(
    _In_ HANDLE KeyHandle,
    _In_ KEY_INFORMATION_CLASS KeyInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryKey(
    _In_ HANDLE KeyHandle,
    _In_ KEY_INFORMATION_CLASS KeyInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationKey(
    _In_ HANDLE KeyHandle,
    _In_ KEY_SET_INFORMATION_CLASS KeySetInformationClass,
    _In_reads_bytes_(KeySetInformationLength) PVOID KeySetInformation,
    _In_ ULONG KeySetInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationKey(
    _In_ HANDLE KeyHandle,
    _In_ KEY_SET_INFORMATION_CLASS KeySetInformationClass,
    _In_reads_bytes_(KeySetInformationLength) PVOID KeySetInformation,
    _In_ ULONG KeySetInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_opt_ ULONG TitleIndex,
    _In_ ULONG Type,
    _In_reads_bytes_opt_(DataSize) PVOID Data,
    _In_ ULONG DataSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_opt_ ULONG TitleIndex,
    _In_ ULONG Type,
    _In_reads_bytes_opt_(DataSize) PVOID Data,
    _In_ ULONG DataSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryMultipleValueKey(
    _In_ HANDLE KeyHandle,
    _Inout_updates_(EntryCount) PKEY_VALUE_ENTRY ValueEntries,
    _In_ ULONG EntryCount,
    _Out_writes_bytes_(*BufferLength) PVOID ValueBuffer,
    _Inout_ PULONG BufferLength,
    _Out_opt_ PULONG RequiredBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryMultipleValueKey(
    _In_ HANDLE KeyHandle,
    _Inout_updates_(EntryCount) PKEY_VALUE_ENTRY ValueEntries,
    _In_ ULONG EntryCount,
    _Out_writes_bytes_(*BufferLength) PVOID ValueBuffer,
    _Inout_ PULONG BufferLength,
    _Out_opt_ PULONG RequiredBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnumerateKey(
    _In_ HANDLE KeyHandle,
    _In_ ULONG Index,
    _In_ KEY_INFORMATION_CLASS KeyInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwEnumerateKey(
    _In_ HANDLE KeyHandle,
    _In_ ULONG Index,
    _In_ KEY_INFORMATION_CLASS KeyInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnumerateValueKey(
    _In_ HANDLE KeyHandle,
    _In_ ULONG Index,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwEnumerateValueKey(
    _In_ HANDLE KeyHandle,
    _In_ ULONG Index,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushKey(
    _In_ HANDLE KeyHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFlushKey(
    _In_ HANDLE KeyHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompactKeys(
    _In_ ULONG Count,
    _In_reads_(Count) HANDLE KeyArray[]
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCompactKeys(
    _In_ ULONG Count,
    _In_reads_(Count) HANDLE KeyArray[]
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompressKey(
    _In_ HANDLE Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCompressKey(
    _In_ HANDLE Key
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadKey(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLoadKey(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadKey2(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLoadKey2(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadKeyEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags,
    _In_opt_ HANDLE TrustClassKey, // this and below were added on Win10
    _In_opt_ HANDLE Event,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _Out_opt_ PHANDLE RootHandle,
    _Reserved_ PVOID Reserved // previously PIO_STATUS_BLOCK
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLoadKeyEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags,
    _In_opt_ HANDLE TrustClassKey, // this and below were added on Win10
    _In_opt_ HANDLE Event,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _Out_opt_ PHANDLE RootHandle,
    _Reserved_ PVOID Reserved // previously PIO_STATUS_BLOCK
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtReplaceKey(
    _In_ POBJECT_ATTRIBUTES NewFile,
    _In_ HANDLE TargetHandle,
    _In_ POBJECT_ATTRIBUTES OldFile
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReplaceKey(
    _In_ POBJECT_ATTRIBUTES NewFile,
    _In_ HANDLE TargetHandle,
    _In_ POBJECT_ATTRIBUTES OldFile
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSaveKey(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSaveKey(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSaveKeyEx(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle,
    _In_ ULONG Format
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSaveKeyEx(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle,
    _In_ ULONG Format
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSaveMergedKeys(
    _In_ HANDLE HighPrecedenceKeyHandle,
    _In_ HANDLE LowPrecedenceKeyHandle,
    _In_ HANDLE FileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSaveMergedKeys(
    _In_ HANDLE HighPrecedenceKeyHandle,
    _In_ HANDLE LowPrecedenceKeyHandle,
    _In_ HANDLE FileHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRestoreKey(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRestoreKey(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnloadKey(
    _In_ POBJECT_ATTRIBUTES TargetKey
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnloadKey(
    _In_ POBJECT_ATTRIBUTES TargetKey
    );

//
// NtUnloadKey2 Flags (from winnt.h)
//
//#define REG_FORCE_UNLOAD            1
//#define REG_UNLOAD_LEGAL_FLAGS      (REG_FORCE_UNLOAD)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnloadKey2(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnloadKey2(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ ULONG Flags
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnloadKeyEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_opt_ HANDLE Event
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwUnloadKeyEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_opt_ HANDLE Event
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtNotifyChangeKey(
    _In_ HANDLE KeyHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ BOOLEAN Asynchronous
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwNotifyChangeKey(
    _In_ HANDLE KeyHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ BOOLEAN Asynchronous
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtNotifyChangeMultipleKeys(
    _In_ HANDLE MasterKeyHandle,
    _In_opt_ ULONG Count,
    _In_reads_opt_(Count) OBJECT_ATTRIBUTES SubordinateObjects[],
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ BOOLEAN Asynchronous
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwNotifyChangeMultipleKeys(
    _In_ HANDLE MasterKeyHandle,
    _In_opt_ ULONG Count,
    _In_reads_opt_(Count) OBJECT_ATTRIBUTES SubordinateObjects[],
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ BOOLEAN Asynchronous
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryOpenSubKeys(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _Out_ PULONG HandleCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryOpenSubKeys(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _Out_ PULONG HandleCount
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryOpenSubKeysEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_opt_(BufferLength) PVOID Buffer,
    _Out_ PULONG RequiredSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryOpenSubKeysEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_opt_(BufferLength) PVOID Buffer,
    _Out_ PULONG RequiredSize
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtInitializeRegistry(
    _In_ USHORT BootCondition
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwInitializeRegistry(
    _In_ USHORT BootCondition
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLockRegistryKey(
    _In_ HANDLE KeyHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLockRegistryKey(
    _In_ HANDLE KeyHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtLockProductActivationKeys(
    _Inout_opt_ ULONG *pPrivateVer,
    _Out_opt_ ULONG *pSafeMode
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwLockProductActivationKeys(
    _Inout_opt_ ULONG *pPrivateVer,
    _Out_opt_ ULONG *pSafeMode
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreezeRegistry(
    _In_ ULONG TimeOutInSeconds
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFreezeRegistry(
    _In_ ULONG TimeOutInSeconds
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI
NTSTATUS
NTAPI
NtThawRegistry(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwThawRegistry(
    VOID
    );
#endif
 

// #include <ntrtl.h>
#define RtlOffsetToPointer(Base, Offset) ((PCHAR)(((PCHAR)(Base)) + ((ULONG_PTR)(Offset))))
#define RtlPointerToOffset(Base, Pointer) ((ULONG)(((PCHAR)(Pointer)) - ((PCHAR)(Base))))

// Linked lists

FORCEINLINE VOID InitializeListHead(
    _Out_ PLIST_ENTRY ListHead
    )
{
    ListHead->Flink = ListHead->Blink = ListHead;
}

_Check_return_ FORCEINLINE BOOLEAN IsListEmpty(
    _In_ PLIST_ENTRY ListHead
    )
{
    return ListHead->Flink == ListHead;
}

FORCEINLINE BOOLEAN RemoveEntryList(
    _In_ PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Flink;

    Flink = Entry->Flink;
    Blink = Entry->Blink;
    Blink->Flink = Flink;
    Flink->Blink = Blink;

    return Flink == Blink;
}

FORCEINLINE PLIST_ENTRY RemoveHeadList(
    _Inout_ PLIST_ENTRY ListHead
    )
{
    PLIST_ENTRY Flink;
    PLIST_ENTRY Entry;

    Entry = ListHead->Flink;
    Flink = Entry->Flink;
    ListHead->Flink = Flink;
    Flink->Blink = ListHead;

    return Entry;
}

FORCEINLINE PLIST_ENTRY RemoveTailList(
    _Inout_ PLIST_ENTRY ListHead
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Entry;

    Entry = ListHead->Blink;
    Blink = Entry->Blink;
    ListHead->Blink = Blink;
    Blink->Flink = ListHead;

    return Entry;
}

FORCEINLINE VOID InsertTailList(
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;

    Blink = ListHead->Blink;
    Entry->Flink = ListHead;
    Entry->Blink = Blink;
    Blink->Flink = Entry;
    ListHead->Blink = Entry;
}

FORCEINLINE VOID InsertHeadList(
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Flink;

    Flink = ListHead->Flink;
    Entry->Flink = Flink;
    Entry->Blink = ListHead;
    Flink->Blink = Entry;
    ListHead->Flink = Entry;
}

FORCEINLINE VOID AppendTailList(
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ PLIST_ENTRY ListToAppend
    )
{
    PLIST_ENTRY ListEnd = ListHead->Blink;

    ListHead->Blink->Flink = ListToAppend;
    ListHead->Blink = ListToAppend->Blink;
    ListToAppend->Blink->Flink = ListHead;
    ListToAppend->Blink = ListEnd;
}

FORCEINLINE PSINGLE_LIST_ENTRY PopEntryList(
    _Inout_ PSINGLE_LIST_ENTRY ListHead
    )
{
    PSINGLE_LIST_ENTRY FirstEntry;

    FirstEntry = ListHead->Next;

    if (FirstEntry)
        ListHead->Next = FirstEntry->Next;

    return FirstEntry;
}

FORCEINLINE VOID PushEntryList(
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ PSINGLE_LIST_ENTRY Entry
    )
{
    Entry->Next = ListHead->Next;
    ListHead->Next = Entry;
}

// AVL and splay trees

typedef enum _TABLE_SEARCH_RESULT
{
    TableEmptyTree,
    TableFoundNode,
    TableInsertAsLeft,
    TableInsertAsRight
} TABLE_SEARCH_RESULT;

typedef enum _RTL_GENERIC_COMPARE_RESULTS
{
    GenericLessThan,
    GenericGreaterThan,
    GenericEqual
} RTL_GENERIC_COMPARE_RESULTS;

typedef RTL_GENERIC_COMPARE_RESULTS (NTAPI *PRTL_AVL_COMPARE_ROUTINE)(
    _In_ struct _RTL_AVL_TABLE *Table,
    _In_ PVOID FirstStruct,
    _In_ PVOID SecondStruct
    );

typedef PVOID (NTAPI *PRTL_AVL_ALLOCATE_ROUTINE)(
    _In_ struct _RTL_AVL_TABLE *Table,
    _In_ CLONG ByteSize
    );

typedef VOID (NTAPI *PRTL_AVL_FREE_ROUTINE)(
    _In_ struct _RTL_AVL_TABLE *Table,
    _In_ _Post_invalid_ PVOID Buffer
    );

typedef NTSTATUS (NTAPI *PRTL_AVL_MATCH_FUNCTION)(
    _In_ struct _RTL_AVL_TABLE *Table,
    _In_ PVOID UserData,
    _In_ PVOID MatchData
    );

typedef struct _RTL_BALANCED_LINKS
{
    struct _RTL_BALANCED_LINKS *Parent;
    struct _RTL_BALANCED_LINKS *LeftChild;
    struct _RTL_BALANCED_LINKS *RightChild;
    CHAR Balance;
    UCHAR Reserved[3];
} RTL_BALANCED_LINKS, *PRTL_BALANCED_LINKS;

typedef struct _RTL_AVL_TABLE
{
    RTL_BALANCED_LINKS BalancedRoot;
    PVOID OrderedPointer;
    ULONG WhichOrderedElement;
    ULONG NumberGenericTableElements;
    ULONG DepthOfTree;
    PRTL_BALANCED_LINKS RestartKey;
    ULONG DeleteCount;
    PRTL_AVL_COMPARE_ROUTINE CompareRoutine;
    PRTL_AVL_ALLOCATE_ROUTINE AllocateRoutine;
    PRTL_AVL_FREE_ROUTINE FreeRoutine;
    PVOID TableContext;
} RTL_AVL_TABLE, *PRTL_AVL_TABLE;

NTSYSAPI
VOID
NTAPI
RtlInitializeGenericTableAvl(
    _Out_ PRTL_AVL_TABLE Table,
    _In_ PRTL_AVL_COMPARE_ROUTINE CompareRoutine,
    _In_ PRTL_AVL_ALLOCATE_ROUTINE AllocateRoutine,
    _In_ PRTL_AVL_FREE_ROUTINE FreeRoutine,
    _In_opt_ PVOID TableContext
    );

NTSYSAPI
PVOID
NTAPI
RtlInsertElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ CLONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement
    );

NTSYSAPI
PVOID
NTAPI
RtlInsertElementGenericTableFullAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ CLONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement,
    _In_ PVOID NodeOrParent,
    _In_ TABLE_SEARCH_RESULT SearchResult
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlDeleteElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlLookupElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer
    );

NTSYSAPI
PVOID
NTAPI
RtlLookupElementGenericTableFullAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer,
    _Out_ PVOID *NodeOrParent,
    _Out_ TABLE_SEARCH_RESULT *SearchResult
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ BOOLEAN Restart
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTableWithoutSplayingAvl(
    _In_ PRTL_AVL_TABLE Table,
    _Inout_ PVOID *RestartKey
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlLookupFirstMatchingElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer,
    _Out_ PVOID *RestartKey
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTableLikeADirectory(
    _In_ PRTL_AVL_TABLE Table,
    _In_opt_ PRTL_AVL_MATCH_FUNCTION MatchFunction,
    _In_opt_ PVOID MatchData,
    _In_ ULONG NextFlag,
    _Inout_ PVOID *RestartKey,
    _Inout_ PULONG DeleteCount,
    _In_ PVOID Buffer
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlGetElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ ULONG I
    );

NTSYSAPI
ULONG
NTAPI
RtlNumberGenericTableElementsAvl(
    _In_ PRTL_AVL_TABLE Table
    );

_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlIsGenericTableEmptyAvl(
    _In_ PRTL_AVL_TABLE Table
    );

typedef struct _RTL_SPLAY_LINKS
{
    struct _RTL_SPLAY_LINKS *Parent;
    struct _RTL_SPLAY_LINKS *LeftChild;
    struct _RTL_SPLAY_LINKS *RightChild;
} RTL_SPLAY_LINKS, *PRTL_SPLAY_LINKS;

#define RtlInitializeSplayLinks(Links) \
{ \
    PRTL_SPLAY_LINKS _SplayLinks; \
    _SplayLinks = (PRTL_SPLAY_LINKS)(Links); \
    _SplayLinks->Parent = _SplayLinks; \
    _SplayLinks->LeftChild = NULL; \
    _SplayLinks->RightChild = NULL; \
}

#define RtlParent(Links) ((PRTL_SPLAY_LINKS)(Links)->Parent)
#define RtlLeftChild(Links) ((PRTL_SPLAY_LINKS)(Links)->LeftChild)
#define RtlRightChild(Links) ((PRTL_SPLAY_LINKS)(Links)->RightChild)
#define RtlIsRoot(Links) ((RtlParent(Links) == (PRTL_SPLAY_LINKS)(Links)))
#define RtlIsLeftChild(Links) ((RtlLeftChild(RtlParent(Links)) == (PRTL_SPLAY_LINKS)(Links)))
#define RtlIsRightChild(Links) ((RtlRightChild(RtlParent(Links)) == (PRTL_SPLAY_LINKS)(Links)))

#define RtlInsertAsLeftChild(ParentLinks, ChildLinks) \
{ \
    PRTL_SPLAY_LINKS _SplayParent; \
    PRTL_SPLAY_LINKS _SplayChild; \
    _SplayParent = (PRTL_SPLAY_LINKS)(ParentLinks); \
    _SplayChild = (PRTL_SPLAY_LINKS)(ChildLinks); \
    _SplayParent->LeftChild = _SplayChild; \
    _SplayChild->Parent = _SplayParent; \
}

#define RtlInsertAsRightChild(ParentLinks, ChildLinks) \
{ \
    PRTL_SPLAY_LINKS _SplayParent; \
    PRTL_SPLAY_LINKS _SplayChild; \
    _SplayParent = (PRTL_SPLAY_LINKS)(ParentLinks); \
    _SplayChild = (PRTL_SPLAY_LINKS)(ChildLinks); \
    _SplayParent->RightChild = _SplayChild; \
    _SplayChild->Parent = _SplayParent; \
}

NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlSplay(
    _Inout_ PRTL_SPLAY_LINKS Links
    );

NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlDelete(
    _In_ PRTL_SPLAY_LINKS Links
    );

NTSYSAPI
VOID
NTAPI
RtlDeleteNoSplay(
    _In_ PRTL_SPLAY_LINKS Links,
    _Inout_ PRTL_SPLAY_LINKS *Root
    );

_Check_return_
NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlSubtreeSuccessor(
    _In_ PRTL_SPLAY_LINKS Links
    );

_Check_return_
NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlSubtreePredecessor(
    _In_ PRTL_SPLAY_LINKS Links
    );

_Check_return_
NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlRealSuccessor(
    _In_ PRTL_SPLAY_LINKS Links
    );

_Check_return_
NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlRealPredecessor(
    _In_ PRTL_SPLAY_LINKS Links
    );

struct _RTL_GENERIC_TABLE;

typedef RTL_GENERIC_COMPARE_RESULTS (NTAPI *PRTL_GENERIC_COMPARE_ROUTINE)(
    _In_ struct _RTL_GENERIC_TABLE *Table,
    _In_ PVOID FirstStruct,
    _In_ PVOID SecondStruct
    );

typedef PVOID (NTAPI *PRTL_GENERIC_ALLOCATE_ROUTINE)(
    _In_ struct _RTL_GENERIC_TABLE *Table,
    _In_ CLONG ByteSize
    );

typedef VOID (NTAPI *PRTL_GENERIC_FREE_ROUTINE)(
    _In_ struct _RTL_GENERIC_TABLE *Table,
    _In_ _Post_invalid_ PVOID Buffer
    );

typedef struct _RTL_GENERIC_TABLE
{
    PRTL_SPLAY_LINKS TableRoot;
    LIST_ENTRY InsertOrderList;
    PLIST_ENTRY OrderedPointer;
    ULONG WhichOrderedElement;
    ULONG NumberGenericTableElements;
    PRTL_GENERIC_COMPARE_ROUTINE CompareRoutine;
    PRTL_GENERIC_ALLOCATE_ROUTINE AllocateRoutine;
    PRTL_GENERIC_FREE_ROUTINE FreeRoutine;
    PVOID TableContext;
} RTL_GENERIC_TABLE, *PRTL_GENERIC_TABLE;

NTSYSAPI
VOID
NTAPI
RtlInitializeGenericTable(
    _Out_ PRTL_GENERIC_TABLE Table,
    _In_ PRTL_GENERIC_COMPARE_ROUTINE CompareRoutine,
    _In_ PRTL_GENERIC_ALLOCATE_ROUTINE AllocateRoutine,
    _In_ PRTL_GENERIC_FREE_ROUTINE FreeRoutine,
    _In_opt_ PVOID TableContext
    );

NTSYSAPI
PVOID
NTAPI
RtlInsertElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ CLONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement
    );

NTSYSAPI
PVOID
NTAPI
RtlInsertElementGenericTableFull(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ CLONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement,
    _In_ PVOID NodeOrParent,
    _In_ TABLE_SEARCH_RESULT SearchResult
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlDeleteElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ PVOID Buffer
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlLookupElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ PVOID Buffer
    );

NTSYSAPI
PVOID
NTAPI
RtlLookupElementGenericTableFull(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ PVOID Buffer,
    _Out_ PVOID *NodeOrParent,
    _Out_ TABLE_SEARCH_RESULT *SearchResult
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ BOOLEAN Restart
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTableWithoutSplaying(
    _In_ PRTL_GENERIC_TABLE Table,
    _Inout_ PVOID *RestartKey
    );

_Check_return_
NTSYSAPI
PVOID
NTAPI
RtlGetElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ ULONG I
    );

NTSYSAPI
ULONG
NTAPI
RtlNumberGenericTableElements(
    _In_ PRTL_GENERIC_TABLE Table
    );

_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlIsGenericTableEmpty(
    _In_ PRTL_GENERIC_TABLE Table
    );

// RB trees

typedef struct _RTL_RB_TREE
{
    PRTL_BALANCED_NODE Root;
    PRTL_BALANCED_NODE Min;
} RTL_RB_TREE, *PRTL_RB_TREE;

#if (NTDDI_VERSION >= NTDDI_WIN8)

// rev
NTSYSAPI
VOID
NTAPI
RtlRbInsertNodeEx(
    _In_ PRTL_RB_TREE Tree,
    _In_opt_ PRTL_BALANCED_NODE Parent,
    _In_ BOOLEAN Right,
    _Out_ PRTL_BALANCED_NODE Node
    );

// rev
NTSYSAPI
VOID
NTAPI
RtlRbRemoveNode(
    _In_ PRTL_RB_TREE Tree,
    _In_ PRTL_BALANCED_NODE Node
    );

#endif

// Hash tables

// begin_ntddk

#define RTL_HASH_ALLOCATED_HEADER 0x00000001
#define RTL_HASH_RESERVED_SIGNATURE 0

typedef struct _RTL_DYNAMIC_HASH_TABLE_ENTRY
{
    LIST_ENTRY Linkage;
    ULONG_PTR Signature;
} RTL_DYNAMIC_HASH_TABLE_ENTRY, *PRTL_DYNAMIC_HASH_TABLE_ENTRY;

#define HASH_ENTRY_KEY(x) ((x)->Signature)

typedef struct _RTL_DYNAMIC_HASH_TABLE_CONTEXT
{
    PLIST_ENTRY ChainHead;
    PLIST_ENTRY PrevLinkage;
    ULONG_PTR Signature;
} RTL_DYNAMIC_HASH_TABLE_CONTEXT, *PRTL_DYNAMIC_HASH_TABLE_CONTEXT;

typedef struct _RTL_DYNAMIC_HASH_TABLE_ENUMERATOR
{
    RTL_DYNAMIC_HASH_TABLE_ENTRY HashEntry;
    PLIST_ENTRY ChainHead;
    ULONG BucketIndex;
} RTL_DYNAMIC_HASH_TABLE_ENUMERATOR, *PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR;

typedef struct _RTL_DYNAMIC_HASH_TABLE
{
    // Entries initialized at creation.
    ULONG Flags;
    ULONG Shift;

    // Entries used in bucket computation.
    ULONG TableSize;
    ULONG Pivot;
    ULONG DivisorMask;

    // Counters.
    ULONG NumEntries;
    ULONG NonEmptyBuckets;
    ULONG NumEnumerators;

    // The directory. This field is for internal use only.
    PVOID Directory;
} RTL_DYNAMIC_HASH_TABLE, *PRTL_DYNAMIC_HASH_TABLE;

#if (NTDDI_VERSION >= NTDDI_WIN7)

FORCEINLINE
VOID
RtlInitHashTableContext(
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
    )
{
    Context->ChainHead = NULL;
    Context->PrevLinkage = NULL;
}

FORCEINLINE
VOID
RtlInitHashTableContextFromEnumerator(
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context,
    _In_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    )
{
    Context->ChainHead = Enumerator->ChainHead;
    Context->PrevLinkage = Enumerator->HashEntry.Linkage.Blink;
}

FORCEINLINE
VOID
RtlReleaseHashTableContext(
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
    )
{
    UNREFERENCED_PARAMETER(Context);
    return;
}

FORCEINLINE
ULONG
RtlTotalBucketsHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
    )
{
    return HashTable->TableSize;
}

FORCEINLINE
ULONG
RtlNonEmptyBucketsHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
    )
{
    return HashTable->NonEmptyBuckets;
}

FORCEINLINE
ULONG
RtlEmptyBucketsHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
    )
{
    return HashTable->TableSize - HashTable->NonEmptyBuckets;
}

FORCEINLINE
ULONG
RtlTotalEntriesHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
    )
{
    return HashTable->NumEntries;
}

FORCEINLINE
ULONG
RtlActiveEnumeratorsHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
    )
{
    return HashTable->NumEnumerators;
}

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlCreateHashTable(
    _Inout_ _When_(*HashTable == NULL, __drv_allocatesMem(Mem)) PRTL_DYNAMIC_HASH_TABLE *HashTable,
    _In_ ULONG Shift,
    _In_ _Reserved_ ULONG Flags
    );

NTSYSAPI
VOID
NTAPI
RtlDeleteHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlInsertEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ PRTL_DYNAMIC_HASH_TABLE_ENTRY Entry,
    _In_ ULONG_PTR Signature,
    _Inout_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlRemoveEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ PRTL_DYNAMIC_HASH_TABLE_ENTRY Entry,
    _Inout_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
    );

_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlLookupEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ ULONG_PTR Signature,
    _Out_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
    );

_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlGetNextEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlInitEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlEnumerateEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

NTSYSAPI
VOID
NTAPI
RtlEndEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlInitWeakEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlWeaklyEnumerateEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

NTSYSAPI
VOID
NTAPI
RtlEndWeakEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlExpandHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlContractHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSAPI
BOOLEAN
NTAPI
RtlInitStrongEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlStronglyEnumerateEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

NTSYSAPI
VOID
NTAPI
RtlEndStrongEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
    );

#endif

// end_ntddk

// Critical sections

NTSYSAPI
NTSTATUS
NTAPI
RtlInitializeCriticalSection(
    _Out_ PRTL_CRITICAL_SECTION CriticalSection
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlInitializeCriticalSectionAndSpinCount(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection,
    _In_ ULONG SpinCount
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlEnterCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlLeaveCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
    );

NTSYSAPI
LOGICAL
NTAPI
RtlTryEnterCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
    );

NTSYSAPI
LOGICAL
NTAPI
RtlIsCriticalSectionLocked(
    _In_ PRTL_CRITICAL_SECTION CriticalSection
    );

NTSYSAPI
LOGICAL
NTAPI
RtlIsCriticalSectionLockedByThread(
    _In_ PRTL_CRITICAL_SECTION CriticalSection
    );

NTSYSAPI
ULONG
NTAPI
RtlGetCriticalSectionRecursionCount(
    _In_ PRTL_CRITICAL_SECTION CriticalSection
    );

NTSYSAPI
ULONG
NTAPI
RtlSetCriticalSectionSpinCount(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection,
    _In_ ULONG SpinCount
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
HANDLE
NTAPI
RtlQueryCriticalSectionOwner(
    _In_ HANDLE EventHandle
    );
#endif

NTSYSAPI
VOID
NTAPI
RtlCheckForOrphanedCriticalSections(
    _In_ HANDLE ThreadHandle
    );

// Resources

typedef struct _RTL_RESOURCE
{
    RTL_CRITICAL_SECTION CriticalSection;

    HANDLE SharedSemaphore;
    volatile ULONG NumberOfWaitingShared;
    HANDLE ExclusiveSemaphore;
    volatile ULONG NumberOfWaitingExclusive;

    volatile LONG NumberOfActive; // negative: exclusive acquire; zero: not acquired; positive: shared acquire(s)
    HANDLE ExclusiveOwnerThread;

    ULONG Flags; // RTL_RESOURCE_FLAG_*

    PRTL_RESOURCE_DEBUG DebugInfo;
} RTL_RESOURCE, *PRTL_RESOURCE;

#define RTL_RESOURCE_FLAG_LONG_TERM ((ULONG)0x00000001)

NTSYSAPI
VOID
NTAPI
RtlInitializeResource(
    _Out_ PRTL_RESOURCE Resource
    );

NTSYSAPI
VOID
NTAPI
RtlDeleteResource(
    _Inout_ PRTL_RESOURCE Resource
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlAcquireResourceShared(
    _Inout_ PRTL_RESOURCE Resource,
    _In_ BOOLEAN Wait
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlAcquireResourceExclusive(
    _Inout_ PRTL_RESOURCE Resource,
    _In_ BOOLEAN Wait
    );

NTSYSAPI
VOID
NTAPI
RtlReleaseResource(
    _Inout_ PRTL_RESOURCE Resource
    );

NTSYSAPI
VOID
NTAPI
RtlConvertSharedToExclusive(
    _Inout_ PRTL_RESOURCE Resource
    );

NTSYSAPI
VOID
NTAPI
RtlConvertExclusiveToShared(
    _Inout_ PRTL_RESOURCE Resource
    );

// Slim reader-writer locks, condition variables, and barriers

#if (NTDDI_VERSION >= NTDDI_VISTA)

// winbase:InitializeSRWLock
NTSYSAPI
VOID
NTAPI
RtlInitializeSRWLock(
    _Out_ PRTL_SRWLOCK SRWLock
    );

// winbase:AcquireSRWLockExclusive
NTSYSAPI
VOID
NTAPI
RtlAcquireSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock
    );

// winbase:AcquireSRWLockShared
NTSYSAPI
VOID
NTAPI
RtlAcquireSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock
    );

// winbase:ReleaseSRWLockExclusive
NTSYSAPI
VOID
NTAPI
RtlReleaseSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock
    );

// winbase:ReleaseSRWLockShared
NTSYSAPI
VOID
NTAPI
RtlReleaseSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock
    );

// winbase:TryAcquireSRWLockExclusive
NTSYSAPI
BOOLEAN
NTAPI
RtlTryAcquireSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock
    );

// winbase:TryAcquireSRWLockShared
NTSYSAPI
BOOLEAN
NTAPI
RtlTryAcquireSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
VOID
NTAPI
RtlAcquireReleaseSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock
    );
#endif

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// winbase:InitializeConditionVariable
NTSYSAPI
VOID
NTAPI
RtlInitializeConditionVariable(
    _Out_ PRTL_CONDITION_VARIABLE ConditionVariable
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSleepConditionVariableCS(
    _Inout_ PRTL_CONDITION_VARIABLE ConditionVariable,
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection,
    _In_opt_ PLARGE_INTEGER Timeout
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSleepConditionVariableSRW(
    _Inout_ PRTL_CONDITION_VARIABLE ConditionVariable,
    _Inout_ PRTL_SRWLOCK SRWLock,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_ ULONG Flags
    );

// winbase:WakeConditionVariable
NTSYSAPI
VOID
NTAPI
RtlWakeConditionVariable(
    _Inout_ PRTL_CONDITION_VARIABLE ConditionVariable
    );

// winbase:WakeAllConditionVariable
NTSYSAPI
VOID
NTAPI
RtlWakeAllConditionVariable(
    _Inout_ PRTL_CONDITION_VARIABLE ConditionVariable
    );

#endif

// begin_rev
#define RTL_BARRIER_FLAGS_SPIN_ONLY 0x00000001 // never block on event - always spin
#define RTL_BARRIER_FLAGS_BLOCK_ONLY 0x00000002 // always block on event - never spin
#define RTL_BARRIER_FLAGS_NO_DELETE 0x00000004 // use if barrier will never be deleted
// end_rev

// begin_private

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
RtlInitBarrier(
    _Out_ PRTL_BARRIER Barrier,
    _In_ ULONG TotalThreads,
    _In_ ULONG SpinCount
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteBarrier(
    _In_ PRTL_BARRIER Barrier
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlBarrier(
    _Inout_ PRTL_BARRIER Barrier,
    _In_ ULONG Flags
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlBarrierForDelete(
    _Inout_ PRTL_BARRIER Barrier,
    _In_ ULONG Flags
    );

#endif

// end_private

// Wait on address

// begin_rev

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSAPI
NTSTATUS
NTAPI
RtlWaitOnAddress(
    _In_ volatile VOID *Address,
    _In_ PVOID CompareAddress,
    _In_ SIZE_T AddressSize,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTSYSAPI
VOID
NTAPI
RtlWakeAddressAll(
    _In_ PVOID Address
    );

NTSYSAPI
VOID
NTAPI
RtlWakeAddressSingle(
    _In_ PVOID Address
    );

#endif

// end_rev

// Strings

NTSYSAPI
VOID
NTAPI
RtlInitString(
    _Out_ PSTRING DestinationString,
    _In_opt_ PCSTR SourceString
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitStringEx(
    _Out_ PSTRING DestinationString,
    _In_opt_z_ PCSZ SourceString
    );
#endif

NTSYSAPI
VOID
NTAPI
RtlInitAnsiString(
    _Out_ PANSI_STRING DestinationString,
    _In_opt_ PCSTR SourceString
    );

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitAnsiStringEx(
    _Out_ PANSI_STRING DestinationString,
    _In_opt_z_ PCSZ SourceString
    );
#endif

NTSYSAPI
VOID
NTAPI
RtlFreeAnsiString(
    _In_ PANSI_STRING AnsiString
    );

NTSYSAPI
VOID
NTAPI
RtlFreeOemString(
    _Inout_ POEM_STRING OemString
    );

NTSYSAPI
VOID
NTAPI
RtlCopyString(
    _In_ PSTRING DestinationString,
    _In_opt_ PSTRING SourceString
    );

NTSYSAPI
CHAR
NTAPI
RtlUpperChar(
    _In_ CHAR Character
    );

_Must_inspect_result_
NTSYSAPI
LONG
NTAPI
RtlCompareString(
    _In_ PSTRING String1,
    _In_ PSTRING String2,
    _In_ BOOLEAN CaseInSensitive
    );

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualString(
    _In_ PSTRING String1,
    _In_ PSTRING String2,
    _In_ BOOLEAN CaseInSensitive
    );

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlPrefixString(
    _In_ PSTRING String1,
    _In_ PSTRING String2,
    _In_ BOOLEAN CaseInSensitive
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAppendStringToString(
    _Inout_ PSTRING Destination,
    _In_ PSTRING Source
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAppendAsciizToString(
    _In_ PSTRING Destination,
    _In_opt_ PCSTR Source
    );

NTSYSAPI
VOID
NTAPI
RtlUpperString(
    _In_ PSTRING DestinationString,
    _In_ PSTRING SourceString
    );

FORCEINLINE
BOOLEAN
RtlIsNullOrEmptyUnicodeString(
    _In_opt_ PUNICODE_STRING String
    )
{
    return !String || String->Length == 0;
}

FORCEINLINE
VOID
NTAPI
RtlInitEmptyUnicodeString(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_ PWCHAR Buffer,
    _In_ USHORT MaximumLength
    )
{
    DestinationString->Buffer = Buffer;
    DestinationString->MaximumLength = MaximumLength;
    DestinationString->Length = 0;
}

NTSYSAPI
VOID
NTAPI
RtlInitUnicodeString(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ PCWSTR SourceString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlInitUnicodeStringEx(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ PCWSTR SourceString
    );

_Success_(return != 0)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlCreateUnicodeString(
    _Out_ PUNICODE_STRING DestinationString,
    _In_z_ PCWSTR SourceString
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlCreateUnicodeStringFromAsciiz(
    _Out_ PUNICODE_STRING DestinationString,
    _In_ PCSTR SourceString
    );

NTSYSAPI
VOID
NTAPI
RtlFreeUnicodeString(
    _In_ PUNICODE_STRING UnicodeString
    );

#define RTL_DUPLICATE_UNICODE_STRING_NULL_TERMINATE (0x00000001)
#define RTL_DUPLICATE_UNICODE_STRING_ALLOCATE_NULL_STRING (0x00000002)

NTSYSAPI
NTSTATUS
NTAPI
RtlDuplicateUnicodeString(
    _In_ ULONG Flags,
    _In_ PUNICODE_STRING StringIn,
    _Out_ PUNICODE_STRING StringOut
    );

NTSYSAPI
VOID
NTAPI
RtlCopyUnicodeString(
    _In_ PUNICODE_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString
    );

NTSYSAPI
WCHAR
NTAPI
RtlUpcaseUnicodeChar(
    _In_ WCHAR SourceCharacter
    );

NTSYSAPI
WCHAR
NTAPI
RtlDowncaseUnicodeChar(
    _In_ WCHAR SourceCharacter
    );

_Must_inspect_result_
NTSYSAPI
LONG
NTAPI
RtlCompareUnicodeString(
    _In_ PUNICODE_STRING String1,
    _In_ PUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
_Must_inspect_result_
NTSYSAPI
LONG
NTAPI
RtlCompareUnicodeStrings(
    _In_reads_(String1Length) PCWCH String1,
    _In_ SIZE_T String1Length,
    _In_reads_(String2Length) PCWCH String2,
    _In_ SIZE_T String2Length,
    _In_ BOOLEAN CaseInSensitive
    );
#endif

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualUnicodeString(
    _In_ PUNICODE_STRING String1,
    _In_ PUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
    );

#define HASH_STRING_ALGORITHM_DEFAULT 0
#define HASH_STRING_ALGORITHM_X65599 1
#define HASH_STRING_ALGORITHM_INVALID 0xffffffff

NTSYSAPI
NTSTATUS
NTAPI
RtlHashUnicodeString(
    _In_ PUNICODE_STRING String,
    _In_ BOOLEAN CaseInSensitive,
    _In_ ULONG HashAlgorithm,
    _Out_ PULONG HashValue
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlValidateUnicodeString(
    _In_ ULONG Flags,
    _In_ PUNICODE_STRING String
    );

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlPrefixUnicodeString(
    _In_ PUNICODE_STRING String1,
    _In_ PUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlSuffixUnicodeString(
    _In_ PUNICODE_STRING String1,
    _In_ PUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)
_Must_inspect_result_
NTSYSAPI
PWCHAR
NTAPI
RtlFindUnicodeSubstring(
    _In_ PUNICODE_STRING FullString,
    _In_ PUNICODE_STRING SearchString,
    _In_ BOOLEAN CaseInSensitive
    );
#endif

#define RTL_FIND_CHAR_IN_UNICODE_STRING_START_AT_END 0x00000001
#define RTL_FIND_CHAR_IN_UNICODE_STRING_COMPLEMENT_CHAR_SET 0x00000002
#define RTL_FIND_CHAR_IN_UNICODE_STRING_CASE_INSENSITIVE 0x00000004

NTSYSAPI
NTSTATUS
NTAPI
RtlFindCharInUnicodeString(
    _In_ ULONG Flags,
    _In_ PUNICODE_STRING StringToSearch,
    _In_ PUNICODE_STRING CharSet,
    _Out_ PUSHORT NonInclusivePrefixLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAppendUnicodeStringToString(
    _In_ PUNICODE_STRING Destination,
    _In_ PUNICODE_STRING Source
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAppendUnicodeToString(
    _In_ PUNICODE_STRING Destination,
    _In_opt_ PCWSTR Source
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeString(
    _Inout_ PUNICODE_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDowncaseUnicodeString(
    _Inout_ PUNICODE_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
VOID
NTAPI
RtlEraseUnicodeString(
    _Inout_ PUNICODE_STRING String
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAnsiStringToUnicodeString(
    _Inout_ PUNICODE_STRING DestinationString,
    _In_ PANSI_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToAnsiString(
    _Inout_ PANSI_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
WCHAR
NTAPI
RtlAnsiCharToUnicodeChar(
    _Inout_ PUCHAR *SourceCharacter
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToAnsiString(
    _Inout_ PANSI_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlOemStringToUnicodeString(
    _Inout_ PUNICODE_STRING DestinationString,
    _In_ POEM_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToOemString(
    _Inout_ POEM_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToOemString(
    _Inout_ POEM_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlOemStringToCountedUnicodeString(
    _Inout_ PUNICODE_STRING DestinationString,
    _In_ PCOEM_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToCountedOemString(
    _Inout_ POEM_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToCountedOemString(
    _Inout_ POEM_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlMultiByteToUnicodeN(
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) PCSTR MultiByteString,
    _In_ ULONG BytesInMultiByteString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlMultiByteToUnicodeSize(
    _Out_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) PCSTR MultiByteString,
    _In_ ULONG BytesInMultiByteString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToMultiByteN(
    _Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
    _In_ ULONG MaxBytesInMultiByteString,
    _Out_opt_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToMultiByteSize(
    _Out_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeToMultiByteN(
    _Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
    _In_ ULONG MaxBytesInMultiByteString,
    _Out_opt_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlOemToUnicodeN(
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWSTR UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInOemString) PCCH OemString,
    _In_ ULONG BytesInOemString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToOemN(
    _Out_writes_bytes_to_(MaxBytesInOemString, *BytesInOemString) PCHAR OemString,
    _In_ ULONG MaxBytesInOemString,
    _Out_opt_ PULONG BytesInOemString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeToOemN(
    _Out_writes_bytes_to_(MaxBytesInOemString, *BytesInOemString) PCHAR OemString,
    _In_ ULONG MaxBytesInOemString,
    _Out_opt_ PULONG BytesInOemString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlConsoleMultiByteToUnicodeN(
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) PCCH MultiByteString,
    _In_ ULONG BytesInMultiByteString,
    _Out_ PULONG pdwSpecialChar
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
NTSTATUS
NTAPI
RtlUTF8ToUnicodeN(
    _Out_writes_bytes_to_(UnicodeStringMaxByteCount, *UnicodeStringActualByteCount) PWSTR UnicodeStringDestination,
    _In_ ULONG UnicodeStringMaxByteCount,
    _Out_ PULONG UnicodeStringActualByteCount,
    _In_reads_bytes_(UTF8StringByteCount) PCCH UTF8StringSource,
    _In_ ULONG UTF8StringByteCount
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToUTF8N(
    _Out_writes_bytes_to_(UTF8StringMaxByteCount, *UTF8StringActualByteCount) PCHAR UTF8StringDestination,
    _In_ ULONG UTF8StringMaxByteCount,
    _Out_ PULONG UTF8StringActualByteCount,
    _In_reads_bytes_(UnicodeStringByteCount) PCWCH UnicodeStringSource,
    _In_ ULONG UnicodeStringByteCount
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlCustomCPToUnicodeN(
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG BytesInCustomCPString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToCustomCPN(
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInCustomCPString, *BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG MaxBytesInCustomCPString,
    _Out_opt_ PULONG BytesInCustomCPString,
    _In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeToCustomCPN(
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInCustomCPString, *BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG MaxBytesInCustomCPString,
    _Out_opt_ PULONG BytesInCustomCPString,
    _In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
    );

NTSYSAPI
VOID
NTAPI
RtlInitCodePageTable(
    _In_reads_z_(2) PUSHORT TableBase,
    _Inout_ PCPTABLEINFO CodePageTable
    );

NTSYSAPI
VOID
NTAPI
RtlInitNlsTables(
    _In_ PUSHORT AnsiNlsBase,
    _In_ PUSHORT OemNlsBase,
    _In_ PUSHORT LanguageNlsBase,
    _Out_ PNLSTABLEINFO TableInfo // PCPTABLEINFO?
    );

NTSYSAPI
VOID
NTAPI
RtlResetRtlTranslations(
    _In_ PNLSTABLEINFO TableInfo
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlIsTextUnicode(
    _In_ PVOID Buffer,
    _In_ ULONG Size,
    _Inout_opt_ PULONG Result
    );

typedef enum _RTL_NORM_FORM
{
    NormOther = 0x0,
    NormC = 0x1,
    NormD = 0x2,
    NormKC = 0x5,
    NormKD = 0x6,
    NormIdna = 0xd,
    DisallowUnassigned = 0x100,
    NormCDisallowUnassigned = 0x101,
    NormDDisallowUnassigned = 0x102,
    NormKCDisallowUnassigned = 0x105,
    NormKDDisallowUnassigned = 0x106,
    NormIdnaDisallowUnassigned = 0x10d
} RTL_NORM_FORM;

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
NTSTATUS
NTAPI
RtlNormalizeString(
    _In_ ULONG NormForm, // RTL_NORM_FORM
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
NTSTATUS
NTAPI
RtlIsNormalizedString(
    _In_ ULONG NormForm, // RTL_NORM_FORM
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_ PBOOLEAN Normalized
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// ntifs:FsRtlIsNameInExpression
NTSYSAPI
BOOLEAN
NTAPI
RtlIsNameInExpression(
    _In_ PUNICODE_STRING Expression,
    _In_ PUNICODE_STRING Name,
    _In_ BOOLEAN IgnoreCase,
    _In_opt_ PWCH UpcaseTable
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsNameInUnUpcasedExpression(
    _In_ PUNICODE_STRING Expression,
    _In_ PUNICODE_STRING Name,
    _In_ BOOLEAN IgnoreCase,
    _In_opt_ PWCH UpcaseTable
    );
#endif

NTSYSAPI
BOOLEAN
NTAPI
RtlEqualDomainName(
    _In_ PUNICODE_STRING String1,
    _In_ PUNICODE_STRING String2
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlEqualComputerName(
    _In_ PUNICODE_STRING String1,
    _In_ PUNICODE_STRING String2
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDnsHostNameToComputerName(
    _Out_ PUNICODE_STRING ComputerNameString,
    _In_ PUNICODE_STRING DnsHostNameString,
    _In_ BOOLEAN AllocateComputerNameString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlStringFromGUID(
    _In_ PGUID Guid,
    _Out_ PUNICODE_STRING GuidString
    );

#if (NTDDI_VERSION >= NTDDI_WINBLUE)

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlStringFromGUIDEx(
    _In_ PGUID Guid,
    _Inout_ PUNICODE_STRING GuidString,
    _In_ BOOLEAN AllocateGuidString
    );

#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlGUIDFromString(
    _In_ PUNICODE_STRING GuidString,
    _Out_ PGUID Guid
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
LONG
NTAPI
RtlCompareAltitudes(
    _In_ PUNICODE_STRING Altitude1,
    _In_ PUNICODE_STRING Altitude2
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIdnToAscii(
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIdnToUnicode(
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIdnToNameprepUnicode(
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength
    );

#endif

// Prefix

typedef struct _PREFIX_TABLE_ENTRY
{
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    struct _PREFIX_TABLE_ENTRY *NextPrefixTree;
    RTL_SPLAY_LINKS Links;
    PSTRING Prefix;
} PREFIX_TABLE_ENTRY, *PPREFIX_TABLE_ENTRY;

typedef struct _PREFIX_TABLE
{
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    PPREFIX_TABLE_ENTRY NextPrefixTree;
} PREFIX_TABLE, *PPREFIX_TABLE;

NTSYSAPI
VOID
NTAPI
PfxInitialize(
    _Out_ PPREFIX_TABLE PrefixTable
    );

NTSYSAPI
BOOLEAN
NTAPI
PfxInsertPrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PSTRING Prefix,
    _Out_ PPREFIX_TABLE_ENTRY PrefixTableEntry
    );

NTSYSAPI
VOID
NTAPI
PfxRemovePrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PPREFIX_TABLE_ENTRY PrefixTableEntry
    );

NTSYSAPI
PPREFIX_TABLE_ENTRY
NTAPI
PfxFindPrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PSTRING FullName
    );

typedef struct _UNICODE_PREFIX_TABLE_ENTRY
{
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    struct _UNICODE_PREFIX_TABLE_ENTRY *NextPrefixTree;
    struct _UNICODE_PREFIX_TABLE_ENTRY *CaseMatch;
    RTL_SPLAY_LINKS Links;
    PUNICODE_STRING Prefix;
} UNICODE_PREFIX_TABLE_ENTRY, *PUNICODE_PREFIX_TABLE_ENTRY;

typedef struct _UNICODE_PREFIX_TABLE
{
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    PUNICODE_PREFIX_TABLE_ENTRY NextPrefixTree;
    PUNICODE_PREFIX_TABLE_ENTRY LastNextEntry;
} UNICODE_PREFIX_TABLE, *PUNICODE_PREFIX_TABLE;

NTSYSAPI
VOID
NTAPI
RtlInitializeUnicodePrefix(
    _Out_ PUNICODE_PREFIX_TABLE PrefixTable
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlInsertUnicodePrefix(
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ PUNICODE_STRING Prefix,
    _Out_ PUNICODE_PREFIX_TABLE_ENTRY PrefixTableEntry
    );

NTSYSAPI
VOID
NTAPI
RtlRemoveUnicodePrefix(
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ PUNICODE_PREFIX_TABLE_ENTRY PrefixTableEntry
    );

NTSYSAPI
PUNICODE_PREFIX_TABLE_ENTRY
NTAPI
RtlFindUnicodePrefix(
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ PUNICODE_STRING FullName,
    _In_ ULONG CaseInsensitiveIndex
    );

NTSYSAPI
PUNICODE_PREFIX_TABLE_ENTRY
NTAPI
RtlNextUnicodePrefix(
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ BOOLEAN Restart
    );

// Compression

typedef struct _COMPRESSED_DATA_INFO
{
    USHORT CompressionFormatAndEngine; // COMPRESSION_FORMAT_* and COMPRESSION_ENGINE_*

    UCHAR CompressionUnitShift;
    UCHAR ChunkShift;
    UCHAR ClusterShift;
    UCHAR Reserved;

    USHORT NumberOfChunks;

    ULONG CompressedChunkSizes[1];
} COMPRESSED_DATA_INFO, *PCOMPRESSED_DATA_INFO;

NTSYSAPI
NTSTATUS
NTAPI
RtlGetCompressionWorkSpaceSize(
    _In_ USHORT CompressionFormatAndEngine,
    _Out_ PULONG CompressBufferWorkSpaceSize,
    _Out_ PULONG CompressFragmentWorkSpaceSize
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCompressBuffer(
    _In_ USHORT CompressionFormatAndEngine,
    _In_reads_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _Out_writes_bytes_to_(CompressedBufferSize, *FinalCompressedSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_ ULONG UncompressedChunkSize,
    _Out_ PULONG FinalCompressedSize,
    _In_ PVOID WorkSpace
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressBuffer(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedBufferSize, *FinalUncompressedSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _Out_ PULONG FinalUncompressedSize
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressBufferEx(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedBufferSize, *FinalUncompressedSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _Out_ PULONG FinalUncompressedSize,
    _In_opt_ PVOID WorkSpace
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressBufferEx2(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedBufferSize, *FinalUncompressedSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_ ULONG UncompressedChunkSize,
    _Out_ PULONG FinalUncompressedSize,
    _In_opt_ PVOID WorkSpace
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressFragment(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedFragmentSize, *FinalUncompressedSize) PUCHAR UncompressedFragment,
    _In_ ULONG UncompressedFragmentSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_range_(<, CompressedBufferSize) ULONG FragmentOffset,
    _Out_ PULONG FinalUncompressedSize,
    _In_ PVOID WorkSpace
    );

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressFragmentEx(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedFragmentSize, *FinalUncompressedSize) PUCHAR UncompressedFragment,
    _In_ ULONG UncompressedFragmentSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_range_(<, CompressedBufferSize) ULONG FragmentOffset,
    _In_ ULONG UncompressedChunkSize,
    _Out_ PULONG FinalUncompressedSize,
    _In_ PVOID WorkSpace
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlDescribeChunk(
    _In_ USHORT CompressionFormat,
    _Inout_ PUCHAR *CompressedBuffer,
    _In_ PUCHAR EndOfCompressedBufferPlus1,
    _Out_ PUCHAR *ChunkBuffer,
    _Out_ PULONG ChunkSize
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlReserveChunk(
    _In_ USHORT CompressionFormat,
    _Inout_ PUCHAR *CompressedBuffer,
    _In_ PUCHAR EndOfCompressedBufferPlus1,
    _Out_ PUCHAR *ChunkBuffer,
    _In_ ULONG ChunkSize
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressChunks(
    _Out_writes_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_reads_bytes_(CompressedTailSize) PUCHAR CompressedTail,
    _In_ ULONG CompressedTailSize,
    _In_ PCOMPRESSED_DATA_INFO CompressedDataInfo
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCompressChunks(
    _In_reads_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _Out_writes_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_range_(>=, (UncompressedBufferSize - (UncompressedBufferSize / 16))) ULONG CompressedBufferSize,
    _Inout_updates_bytes_(CompressedDataInfoLength) PCOMPRESSED_DATA_INFO CompressedDataInfo,
    _In_range_(>, sizeof(COMPRESSED_DATA_INFO)) ULONG CompressedDataInfoLength,
    _In_ PVOID WorkSpace
    );

// Locale

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlConvertLCIDToString(
    _In_ LCID LcidValue,
    _In_ ULONG Base,
    _In_ ULONG Padding, // string is padded to this width
    _Out_writes_(Size) PWSTR pResultBuf,
    _In_ ULONG Size
    );

// private
NTSYSAPI
BOOLEAN
NTAPI
RtlIsValidLocaleName(
    _In_ PCWSTR LocaleName,
    _In_ ULONG Flags
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlGetParentLocaleName(
    _In_ PCWSTR LocaleName,
    _Inout_ PUNICODE_STRING ParentLocaleName,
    _In_ ULONG Flags,
    _In_ BOOLEAN AllocateDestinationString
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLcidToLocaleName(
    _In_ LCID lcid, // sic
    _Inout_ PUNICODE_STRING LocaleName,
    _In_ ULONG Flags,
    _In_ BOOLEAN AllocateDestinationString
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLocaleNameToLcid(
    _In_ PCWSTR LocaleName,
    _Out_ PLCID lcid,
    _In_ ULONG Flags
    );

// private
NTSYSAPI
BOOLEAN
NTAPI
RtlLCIDToCultureName(
    _In_ LCID Lcid,
    _Inout_ PUNICODE_STRING String
    );

// private
NTSYSAPI
BOOLEAN
NTAPI
RtlCultureNameToLCID(
    _In_ PUNICODE_STRING String,
    _Out_ PLCID Lcid
    );

// private
NTSYSAPI
VOID
NTAPI
RtlCleanUpTEBLangLists(
    VOID
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetLocaleFileMappingAddress(
    _Out_ PVOID *BaseAddress,
    _Out_ PLCID DefaultLocaleId,
    _Out_ PLARGE_INTEGER DefaultCasingTableSize
    );

#endif

// PEB

NTSYSAPI
PPEB
NTAPI
RtlGetCurrentPeb(
    VOID
    );

NTSYSAPI
VOID
NTAPI
RtlAcquirePebLock(
    VOID
    );

NTSYSAPI
VOID
NTAPI
RtlReleasePebLock(
    VOID
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
LOGICAL
NTAPI
RtlTryAcquirePebLock(
    VOID
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateFromPeb(
    _In_ ULONG Size,
    _Out_ PVOID *Block
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlFreeToPeb(
    _In_ PVOID Block,
    _In_ ULONG Size
    );

// Processes

#define DOS_MAX_COMPONENT_LENGTH 255
#define DOS_MAX_PATH_LENGTH (DOS_MAX_COMPONENT_LENGTH + 5)

typedef struct _CURDIR
{
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, *PCURDIR;

#define RTL_USER_PROC_CURDIR_CLOSE 0x00000002
#define RTL_USER_PROC_CURDIR_INHERIT 0x00000003

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

#define RTL_MAX_DRIVE_LETTERS 32
#define RTL_DRIVE_LETTER_VALID (USHORT)0x0001

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
    ULONG MaximumLength;
    ULONG Length;

    ULONG Flags;
    ULONG DebugFlags;

    HANDLE ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;

    CURDIR CurrentDirectory;
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    PVOID Environment;

    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;

    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];

    ULONG_PTR EnvironmentSize;
    ULONG_PTR EnvironmentVersion;

    PVOID PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;

    UNICODE_STRING RedirectionDllName; // REDSTONE4
    UNICODE_STRING HeapPartitionName; // 19H1
    ULONG_PTR DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

#define RTL_USER_PROC_PARAMS_NORMALIZED 0x00000001
#define RTL_USER_PROC_PROFILE_USER 0x00000002
#define RTL_USER_PROC_PROFILE_KERNEL 0x00000004
#define RTL_USER_PROC_PROFILE_SERVER 0x00000008
#define RTL_USER_PROC_RESERVE_1MB 0x00000020
#define RTL_USER_PROC_RESERVE_16MB 0x00000040
#define RTL_USER_PROC_CASE_SENSITIVE 0x00000080
#define RTL_USER_PROC_DISABLE_HEAP_DECOMMIT 0x00000100
#define RTL_USER_PROC_DLL_REDIRECTION_LOCAL 0x00001000
#define RTL_USER_PROC_APP_MANIFEST_PRESENT 0x00002000
#define RTL_USER_PROC_IMAGE_KEY_MISSING 0x00004000
#define RTL_USER_PROC_OPTIN_PROCESS 0x00020000

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateProcessParameters(
    _Out_ PRTL_USER_PROCESS_PARAMETERS *pProcessParameters,
    _In_ PUNICODE_STRING ImagePathName,
    _In_opt_ PUNICODE_STRING DllPath,
    _In_opt_ PUNICODE_STRING CurrentDirectory,
    _In_opt_ PUNICODE_STRING CommandLine,
    _In_opt_ PVOID Environment,
    _In_opt_ PUNICODE_STRING WindowTitle,
    _In_opt_ PUNICODE_STRING DesktopInfo,
    _In_opt_ PUNICODE_STRING ShellInfo,
    _In_opt_ PUNICODE_STRING RuntimeData
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateProcessParametersEx(
    _Out_ PRTL_USER_PROCESS_PARAMETERS *pProcessParameters,
    _In_ PUNICODE_STRING ImagePathName,
    _In_opt_ PUNICODE_STRING DllPath,
    _In_opt_ PUNICODE_STRING CurrentDirectory,
    _In_opt_ PUNICODE_STRING CommandLine,
    _In_opt_ PVOID Environment,
    _In_opt_ PUNICODE_STRING WindowTitle,
    _In_opt_ PUNICODE_STRING DesktopInfo,
    _In_opt_ PUNICODE_STRING ShellInfo,
    _In_opt_ PUNICODE_STRING RuntimeData,
    _In_ ULONG Flags // pass RTL_USER_PROC_PARAMS_NORMALIZED to keep parameters normalized
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyProcessParameters(
    _In_ _Post_invalid_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
    );

NTSYSAPI
PRTL_USER_PROCESS_PARAMETERS
NTAPI
RtlNormalizeProcessParams(
    _Inout_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
    );

NTSYSAPI
PRTL_USER_PROCESS_PARAMETERS
NTAPI
RtlDeNormalizeProcessParams(
    _Inout_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
    );

typedef struct _RTL_USER_PROCESS_INFORMATION
{
    ULONG Length;
    HANDLE ProcessHandle;
    HANDLE ThreadHandle;
    CLIENT_ID ClientId;
    SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserProcess(
    _In_ PUNICODE_STRING NtImagePathName,
    _In_ ULONG AttributesDeprecated,
    _In_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
    _In_opt_ PSECURITY_DESCRIPTOR ProcessSecurityDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
    _In_opt_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritHandles,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE TokenHandle, // used to be ExceptionPort
    _Out_ PRTL_USER_PROCESS_INFORMATION ProcessInformation
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserProcessEx(
    _In_ PUNICODE_STRING NtImagePathName,
    _In_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
    _In_ BOOLEAN InheritHandles,
    _Reserved_ ULONG Flags,
    _Out_ PRTL_USER_PROCESS_INFORMATION ProcessInformation
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
DECLSPEC_NORETURN
NTSYSAPI
VOID
NTAPI
RtlExitUserProcess(
    _In_ NTSTATUS ExitStatus
    );
#else

#define RtlExitUserProcess RtlExitUserProcess_R

DECLSPEC_NORETURN
FORCEINLINE VOID RtlExitUserProcess_R(
    _In_ NTSTATUS ExitStatus
    )
{
    ExitProcess(ExitStatus);
}

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// begin_rev
#define RTL_CLONE_PROCESS_FLAGS_CREATE_SUSPENDED 0x00000001
#define RTL_CLONE_PROCESS_FLAGS_INHERIT_HANDLES 0x00000002
#define RTL_CLONE_PROCESS_FLAGS_NO_SYNCHRONIZE 0x00000004 // don't update synchronization objects
// end_rev

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCloneUserProcess(
    _In_ ULONG ProcessFlags,
    _In_opt_ PSECURITY_DESCRIPTOR ProcessSecurityDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
    _In_opt_ HANDLE DebugPort,
    _Out_ PRTL_USER_PROCESS_INFORMATION ProcessInformation
    );

// private
NTSYSAPI
VOID
NTAPI
RtlUpdateClonedCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
    );

// private
NTSYSAPI
VOID
NTAPI
RtlUpdateClonedSRWLock(
    _Inout_ PRTL_SRWLOCK SRWLock,
    _In_ LOGICAL Shared // TRUE to set to shared acquire
    );

// private
typedef struct _RTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION
{
    HANDLE ReflectionProcessHandle;
    HANDLE ReflectionThreadHandle;
    CLIENT_ID ReflectionClientId;
} RTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION, *PRTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateProcessReflection(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_opt_ PVOID StartRoutine,
    _In_opt_ PVOID StartContext,
    _In_opt_ HANDLE EventHandle,
    _Out_opt_ PRTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION ReflectionInformation
    );
#endif

#endif

NTSYSAPI
NTSTATUS
STDAPIVCALLTYPE
RtlSetProcessIsCritical(
    _In_ BOOLEAN NewValue,
    _Out_opt_ PBOOLEAN OldValue,
    _In_ BOOLEAN CheckFlag
    );

NTSYSAPI
NTSTATUS
STDAPIVCALLTYPE
RtlSetThreadIsCritical(
    _In_ BOOLEAN NewValue,
    _Out_opt_ PBOOLEAN OldValue,
    _In_ BOOLEAN CheckFlag
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlValidProcessProtection(
    _In_ PS_PROTECTION ProcessProtection
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlTestProtectedAccess(
    _In_ PS_PROTECTION Source,
    _In_ PS_PROTECTION Target
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCurrentProcess( // NtCompareObjects(NtCurrentProcess(), ProcessHandle)
    _In_ HANDLE ProcessHandle
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCurrentThread( // NtCompareObjects(NtCurrentThread(), ThreadHandle)
    _In_ HANDLE ThreadHandle
    );
#endif

// Threads

typedef NTSTATUS (NTAPI *PUSER_THREAD_START_ROUTINE)(
    _In_ PVOID ThreadParameter
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserThread(
    _In_ HANDLE Process,
    _In_opt_ PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
    _In_ BOOLEAN CreateSuspended,
    _In_opt_ ULONG ZeroBits,
    _In_opt_ SIZE_T MaximumStackSize,
    _In_opt_ SIZE_T CommittedStackSize,
    _In_ PUSER_THREAD_START_ROUTINE StartAddress,
    _In_opt_ PVOID Parameter,
    _Out_opt_ PHANDLE Thread,
    _Out_opt_ PCLIENT_ID ClientId
    );

#if (NTDDI_VERSION >= NTDDI_VISTA) // should be NTDDI_WINXP, but is NTDDI_VISTA for consistency with RtlExitUserProcess
DECLSPEC_NORETURN
NTSYSAPI
VOID
NTAPI
RtlExitUserThread(
    _In_ NTSTATUS ExitStatus
    );
#else

#define RtlExitUserThread RtlExitUserThread_R

DECLSPEC_NORETURN
FORCEINLINE VOID RtlExitUserThread_R(
    _In_ NTSTATUS ExitStatus
    )
{
    ExitThread(ExitStatus);
}

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCurrentThreadAttachExempt(
    VOID
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserStack(
    _In_opt_ SIZE_T CommittedStackSize,
    _In_opt_ SIZE_T MaximumStackSize,
    _In_opt_ ULONG_PTR ZeroBits,
    _In_ SIZE_T PageSize,
    _In_ ULONG_PTR ReserveAlignment,
    _Out_ PINITIAL_TEB InitialTeb
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlFreeUserStack(
    _In_ PVOID AllocationBase
    );

#endif

// Extended thread context

typedef struct _CONTEXT_CHUNK 
{
    LONG Offset; // Offset may be negative.
    ULONG Length;
} CONTEXT_CHUNK, *PCONTEXT_CHUNK;

typedef struct _CONTEXT_EX 
{
    CONTEXT_CHUNK All;
    CONTEXT_CHUNK Legacy;
    CONTEXT_CHUNK XState;
} CONTEXT_EX, *PCONTEXT_EX;

#define CONTEXT_EX_LENGTH ALIGN_UP_BY(sizeof(CONTEXT_EX), PAGE_SIZE)
#define RTL_CONTEXT_EX_OFFSET(ContextEx, Chunk) ((ContextEx)->Chunk.Offset)
#define RTL_CONTEXT_EX_LENGTH(ContextEx, Chunk) ((ContextEx)->Chunk.Length)
#define RTL_CONTEXT_EX_CHUNK(Base, Layout, Chunk) ((PVOID)((PCHAR)(Base) + RTL_CONTEXT_EX_OFFSET(Layout, Chunk)))
#define RTL_CONTEXT_OFFSET(Context, Chunk) RTL_CONTEXT_EX_OFFSET((PCONTEXT_EX)(Context + 1), Chunk)
#define RTL_CONTEXT_LENGTH(Context, Chunk) RTL_CONTEXT_EX_LENGTH((PCONTEXT_EX)(Context + 1), Chunk)
#define RTL_CONTEXT_CHUNK(Context, Chunk) RTL_CONTEXT_EX_CHUNK((PCONTEXT_EX)(Context + 1), (PCONTEXT_EX)(Context + 1), Chunk)

NTSYSAPI
VOID
NTAPI
RtlInitializeContext(
    _In_ HANDLE Process,
    _Out_ PCONTEXT Context,
    _In_opt_ PVOID Parameter,
    _In_opt_ PVOID InitialPc,
    _In_opt_ PVOID InitialSp
    );

NTSYSAPI
ULONG
NTAPI
RtlInitializeExtendedContext(
    _Out_ PCONTEXT Context,
    _In_ ULONG ContextFlags,
    _Out_ PCONTEXT_EX* ContextEx
    );

NTSYSAPI
ULONG
NTAPI
RtlCopyExtendedContext(
    _Out_ PCONTEXT_EX Destination,
    _In_ ULONG ContextFlags,
    _In_ PCONTEXT_EX Source
    );

NTSYSAPI
ULONG
NTAPI
RtlGetExtendedContextLength(
    _In_ ULONG ContextFlags,
    _Out_ PULONG ContextLength
    );

NTSYSAPI
ULONG64
NTAPI
RtlGetExtendedFeaturesMask(
    _In_ PCONTEXT_EX ContextEx
    );

NTSYSAPI
PVOID
NTAPI
RtlLocateExtendedFeature(
    _In_ PCONTEXT_EX ContextEx,
    _In_ ULONG FeatureId,
    _Out_opt_ PULONG Length
    );

NTSYSAPI
PCONTEXT
NTAPI
RtlLocateLegacyContext(
    _In_ PCONTEXT_EX ContextEx,
    _Out_opt_ PULONG Length
    );

NTSYSAPI
VOID
NTAPI
RtlSetExtendedFeaturesMask(
    _In_ PCONTEXT_EX ContextEx,
    _In_ ULONG64 FeatureMask
    );

#ifdef _WIN64
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlWow64GetThreadContext(
    _In_ HANDLE ThreadHandle,
    _Inout_ PWOW64_CONTEXT ThreadContext
    );
#endif

#ifdef _WIN64
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlWow64SetThreadContext(
    _In_ HANDLE ThreadHandle,
    _In_ PWOW64_CONTEXT ThreadContext
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlRemoteCall(
    _In_ HANDLE Process,
    _In_ HANDLE Thread,
    _In_ PVOID CallSite,
    _In_ ULONG ArgumentCount,
    _In_opt_ PULONG_PTR Arguments,
    _In_ BOOLEAN PassContext,
    _In_ BOOLEAN AlreadySuspended
    );

// Vectored exception handlers

NTSYSAPI
PVOID
NTAPI
RtlAddVectoredExceptionHandler(
    _In_ ULONG First,
    _In_ PVECTORED_EXCEPTION_HANDLER Handler
    );

NTSYSAPI
ULONG
NTAPI
RtlRemoveVectoredExceptionHandler(
    _In_ PVOID Handle
    );

NTSYSAPI
PVOID
NTAPI
RtlAddVectoredContinueHandler(
    _In_ ULONG First,
    _In_ PVECTORED_EXCEPTION_HANDLER Handler
    );

NTSYSAPI
ULONG
NTAPI
RtlRemoveVectoredContinueHandler(
    _In_ PVOID Handle
    );

// Runtime exception handling

typedef ULONG (NTAPI *PRTLP_UNHANDLED_EXCEPTION_FILTER)(
    _In_ PEXCEPTION_POINTERS ExceptionInfo
    );

NTSYSAPI
VOID
NTAPI
RtlSetUnhandledExceptionFilter(
    _In_ PRTLP_UNHANDLED_EXCEPTION_FILTER UnhandledExceptionFilter
    );

// rev
NTSYSAPI
LONG
NTAPI
RtlUnhandledExceptionFilter(
    _In_ PEXCEPTION_POINTERS ExceptionPointers
    );

// rev
NTSYSAPI
LONG
NTAPI
RtlUnhandledExceptionFilter2(
    _In_ PEXCEPTION_POINTERS ExceptionPointers,
    _In_ ULONG Flags
    );

// rev
NTSYSAPI
LONG
NTAPI
RtlKnownExceptionFilter(
    _In_ PEXCEPTION_POINTERS ExceptionPointers
    );

#ifdef _WIN64

// private
typedef enum _FUNCTION_TABLE_TYPE
{
    RF_SORTED,
    RF_UNSORTED,
    RF_CALLBACK,
    RF_KERNEL_DYNAMIC
} FUNCTION_TABLE_TYPE;

// private
typedef struct _DYNAMIC_FUNCTION_TABLE
{
    LIST_ENTRY ListEntry;
    PRUNTIME_FUNCTION FunctionTable;
    LARGE_INTEGER TimeStamp;
    ULONG64 MinimumAddress;
    ULONG64 MaximumAddress;
    ULONG64 BaseAddress;
    PGET_RUNTIME_FUNCTION_CALLBACK Callback;
    PVOID Context;
    PWSTR OutOfProcessCallbackDll;
    FUNCTION_TABLE_TYPE Type;
    ULONG EntryCount;
    RTL_BALANCED_NODE TreeNode;
} DYNAMIC_FUNCTION_TABLE, *PDYNAMIC_FUNCTION_TABLE;

// rev
NTSYSAPI
PLIST_ENTRY
NTAPI
RtlGetFunctionTableListHead(
    VOID
    );

#endif

// Images

NTSYSAPI
PIMAGE_NT_HEADERS
NTAPI
RtlImageNtHeader(
    _In_ PVOID BaseOfImage
    );

#define RTL_IMAGE_NT_HEADER_EX_FLAG_NO_RANGE_CHECK 0x00000001

NTSYSAPI
NTSTATUS
NTAPI
RtlImageNtHeaderEx(
    _In_ ULONG Flags,
    _In_ PVOID BaseOfImage,
    _In_ ULONG64 Size,
    _Out_ PIMAGE_NT_HEADERS *OutHeaders
    );

NTSYSAPI
PVOID
NTAPI
RtlAddressInSectionTable(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG VirtualAddress
    );

NTSYSAPI
PIMAGE_SECTION_HEADER
NTAPI
RtlSectionTableFromVirtualAddress(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG VirtualAddress
    );

NTSYSAPI
PVOID
NTAPI
RtlImageDirectoryEntryToData(
    _In_ PVOID BaseOfImage,
    _In_ BOOLEAN MappedAsImage,
    _In_ USHORT DirectoryEntry,
    _Out_ PULONG Size
    );

NTSYSAPI
PIMAGE_SECTION_HEADER
NTAPI
RtlImageRvaToSection(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG Rva
    );

NTSYSAPI
PVOID
NTAPI
RtlImageRvaToVa(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG Rva,
    _Out_opt_ PIMAGE_SECTION_HEADER *LastRvaSection
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)

// rev
NTSYSAPI
PVOID
NTAPI
RtlFindExportedRoutineByName(
    _In_ PVOID BaseOfImage,
    _In_ PCSTR RoutineName
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGuardCheckLongJumpTarget(
    _In_ PVOID PcValue, 
    _In_ BOOL IsFastFail, 
    _Out_ PBOOL IsLongJumpTarget
    );

#endif

// Memory

_Must_inspect_result_
NTSYSAPI
SIZE_T
NTAPI
RtlCompareMemoryUlong(
    _In_reads_bytes_(Length) PVOID Source,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern
    );

#if defined(_M_AMD64)
FORCEINLINE
VOID
RtlFillMemoryUlong(
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern
    )
{
    PULONG Address = (PULONG)Destination;

    //
    // If the number of DWORDs is not zero, then fill the specified buffer
    // with the specified pattern.
    //

    if ((Length /= 4) != 0) {

        //
        // If the destination is not quadword aligned (ignoring low bits),
        // then align the destination by storing one DWORD.
        //

        if (((ULONG64)Address & 4) != 0) {
            *Address = Pattern;
            if ((Length -= 1) == 0) {
                return;
            }

            Address += 1;
        }

        //
        // If the number of QWORDs is not zero, then fill the destination
        // buffer a QWORD at a time.
        //

         __stosq((PULONG64)(Address),
                 Pattern | ((ULONG64)Pattern << 32),
                 Length / 2);

        if ((Length & 1) != 0) {
            Address[Length - 1] = Pattern;
        }
    }

    return;
}
#else
NTSYSAPI
VOID
NTAPI
RtlFillMemoryUlong(
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern
    );
#endif

#if defined(_M_AMD64)

#define RtlFillMemoryUlonglong(Destination, Length, Pattern) \
    __stosq((PULONG64)(Destination), Pattern, (Length) / 8)

#else
NTSYSAPI
VOID
NTAPI
RtlFillMemoryUlonglong(
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONGLONG Pattern
    );
#endif
// Environment

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateEnvironment(
    _In_ BOOLEAN CloneCurrentEnvironment,
    _Out_ PVOID *Environment
    );

// begin_rev
#define RTL_CREATE_ENVIRONMENT_TRANSLATE 0x1 // translate from multi-byte to Unicode
#define RTL_CREATE_ENVIRONMENT_TRANSLATE_FROM_OEM 0x2 // translate from OEM to Unicode (Translate flag must also be set)
#define RTL_CREATE_ENVIRONMENT_EMPTY 0x4 // create empty environment block
// end_rev

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateEnvironmentEx(
    _In_ PVOID SourceEnv,
    _Out_ PVOID *Environment,
    _In_ ULONG Flags
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyEnvironment(
    _In_ PVOID Environment
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetCurrentEnvironment(
    _In_ PVOID Environment,
    _Out_opt_ PVOID *PreviousEnvironment
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSetEnvironmentVar(
    _Inout_opt_ PVOID *Environment,
    _In_reads_(NameLength) PCWSTR Name,
    _In_ SIZE_T NameLength,
    _In_reads_(ValueLength) PCWSTR Value,
    _In_ SIZE_T ValueLength
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlSetEnvironmentVariable(
    _Inout_opt_ PVOID *Environment,
    _In_ PUNICODE_STRING Name,
    _In_opt_ PUNICODE_STRING Value
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryEnvironmentVariable(
    _In_opt_ PVOID Environment,
    _In_reads_(NameLength) PCWSTR Name,
    _In_ SIZE_T NameLength,
    _Out_writes_(ValueLength) PWSTR Value,
    _In_ SIZE_T ValueLength,
    _Out_ PSIZE_T ReturnLength
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryEnvironmentVariable_U(
    _In_opt_ PVOID Environment,
    _In_ PUNICODE_STRING Name,
    _Inout_ PUNICODE_STRING Value
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlExpandEnvironmentStrings(
    _In_opt_ PVOID Environment,
    _In_reads_(SrcLength) PCWSTR Src,
    _In_ SIZE_T SrcLength,
    _Out_writes_(DstLength) PWSTR Dst,
    _In_ SIZE_T DstLength,
    _Out_opt_ PSIZE_T ReturnLength
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlExpandEnvironmentStrings_U(
    _In_opt_ PVOID Environment,
    _In_ PUNICODE_STRING Source,
    _Inout_ PUNICODE_STRING Destination,
    _Out_opt_ PULONG ReturnedLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetEnvironmentStrings(
    _In_ PCWCHAR NewEnvironment,
    _In_ SIZE_T NewEnvironmentSize
    );

// Directory and path support

typedef struct _RTLP_CURDIR_REF
{
    LONG ReferenceCount;
    HANDLE DirectoryHandle;
} RTLP_CURDIR_REF, *PRTLP_CURDIR_REF;

typedef struct _RTL_RELATIVE_NAME_U
{
    UNICODE_STRING RelativeName;
    HANDLE ContainingDirectory;
    PRTLP_CURDIR_REF CurDirRef;
} RTL_RELATIVE_NAME_U, *PRTL_RELATIVE_NAME_U;

typedef enum _RTL_PATH_TYPE
{
    RtlPathTypeUnknown,
    RtlPathTypeUncAbsolute,
    RtlPathTypeDriveAbsolute,
    RtlPathTypeDriveRelative,
    RtlPathTypeRooted,
    RtlPathTypeRelative,
    RtlPathTypeLocalDevice,
    RtlPathTypeRootLocalDevice
} RTL_PATH_TYPE;

// Data exports (ntdll.lib/ntdllp.lib)

NTSYSAPI PWSTR RtlNtdllName;
NTSYSAPI UNICODE_STRING RtlDosPathSeperatorsString;
NTSYSAPI UNICODE_STRING RtlAlternateDosPathSeperatorString;
NTSYSAPI UNICODE_STRING RtlNtPathSeperatorString;

// Path functions

NTSYSAPI
RTL_PATH_TYPE
NTAPI
RtlDetermineDosPathNameType_U(
    _In_ PCWSTR DosFileName
    );

NTSYSAPI
RTL_PATH_TYPE
NTAPI
RtlDetermineDosPathNameType_Ustr(
    _In_ PCUNICODE_STRING DosFileName
    );

NTSYSAPI
ULONG
NTAPI
RtlIsDosDeviceName_U(
    _In_ PCWSTR DosFileName
    );

NTSYSAPI
ULONG
NTAPI
RtlIsDosDeviceName_Ustr(
    _In_ PUNICODE_STRING DosFileName
    );

NTSYSAPI
ULONG
NTAPI
RtlGetFullPathName_U(
    _In_ PCWSTR FileName,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer,
    _Out_opt_ PWSTR *FilePart
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetFullPathName_UEx(
    _In_ PCWSTR FileName,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer,
    _Out_opt_ PWSTR *FilePart,
    _Out_opt_ ULONG *BytesRequired
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
NTSTATUS
NTAPI
RtlGetFullPathName_UstrEx(
    _In_ PUNICODE_STRING FileName,
    _Inout_ PUNICODE_STRING StaticString,
    _Out_opt_ PUNICODE_STRING DynamicString,
    _Out_opt_ PUNICODE_STRING *StringUsed,
    _Out_opt_ SIZE_T *FilePartPrefixCch,
    _Out_opt_ PBOOLEAN NameInvalid,
    _Out_ RTL_PATH_TYPE *InputPathType,
    _Out_opt_ SIZE_T *BytesRequired
    );
#endif

NTSYSAPI
ULONG
NTAPI
RtlGetCurrentDirectory_U(
    _In_ ULONG BufferLength,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetCurrentDirectory_U(
    _In_ PUNICODE_STRING PathName
    );

NTSYSAPI
ULONG
NTAPI
RtlGetLongestNtPathLength(
    VOID
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlDosPathNameToNtPathName_U(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR *FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
    );

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
NTSTATUS
NTAPI
RtlDosPathNameToNtPathName_U_WithStatus(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR *FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDosLongPathNameToNtPathName_U_WithStatus(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR *FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
BOOLEAN
NTAPI
RtlDosPathNameToRelativeNtPathName_U(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR *FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
NTSTATUS
NTAPI
RtlDosPathNameToRelativeNtPathName_U_WithStatus(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR *FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDosLongPathNameToRelativeNtPathName_U_WithStatus(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR *FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
VOID
NTAPI
RtlReleaseRelativeName(
    _Inout_ PRTL_RELATIVE_NAME_U RelativeName
    );
#endif

NTSYSAPI
ULONG
NTAPI
RtlDosSearchPath_U(
    _In_ PCWSTR Path,
    _In_ PCWSTR FileName,
    _In_opt_ PCWSTR Extension,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer,
    _Out_opt_ PWSTR *FilePart
    );

#define RTL_DOS_SEARCH_PATH_FLAG_APPLY_ISOLATION_REDIRECTION 0x00000001
#define RTL_DOS_SEARCH_PATH_FLAG_DISALLOW_DOT_RELATIVE_PATH_SEARCH 0x00000002
#define RTL_DOS_SEARCH_PATH_FLAG_APPLY_DEFAULT_EXTENSION_WHEN_NOT_RELATIVE_PATH_EVEN_IF_FILE_HAS_EXTENSION 0x00000004

NTSYSAPI
NTSTATUS
NTAPI
RtlDosSearchPath_Ustr(
    _In_ ULONG Flags,
    _In_ PUNICODE_STRING Path,
    _In_ PUNICODE_STRING FileName,
    _In_opt_ PUNICODE_STRING DefaultExtension,
    _Out_opt_ PUNICODE_STRING StaticString,
    _Out_opt_ PUNICODE_STRING DynamicString,
    _Out_opt_ PCUNICODE_STRING *FullFileNameOut,
    _Out_opt_ SIZE_T *FilePartPrefixCch,
    _Out_opt_ SIZE_T *BytesRequired
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlDoesFileExists_U(
    _In_ PCWSTR FileName
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetLengthWithoutLastFullDosOrNtPathElement(
    _Reserved_ ULONG Flags,
    _In_ PUNICODE_STRING PathString,
    _Out_ PULONG Length
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetLengthWithoutTrailingPathSeperators(
    _Reserved_ ULONG Flags,
    _In_ PUNICODE_STRING PathString,
    _Out_ PULONG Length
    );

typedef struct _GENERATE_NAME_CONTEXT
{
    USHORT Checksum;
    BOOLEAN CheckSumInserted;
    UCHAR NameLength;
    WCHAR NameBuffer[8];
    ULONG ExtensionLength;
    WCHAR ExtensionBuffer[4];
    ULONG LastIndexValue;
} GENERATE_NAME_CONTEXT, *PGENERATE_NAME_CONTEXT;

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlGenerate8dot3Name(
    _In_ PUNICODE_STRING Name,
    _In_ BOOLEAN AllowExtendedCharacters,
    _Inout_ PGENERATE_NAME_CONTEXT Context,
    _Inout_ PUNICODE_STRING Name8dot3
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlComputePrivatizedDllName_U(
    _In_ PUNICODE_STRING DllName,
    _Out_ PUNICODE_STRING RealName,
    _Out_ PUNICODE_STRING LocalName
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlGetSearchPath(
    _Out_ PWSTR *SearchPath
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetSearchPathMode(
    _In_ ULONG Flags
    );

// rev
NTSYSAPI
PWSTR
NTAPI
RtlGetExePath(
    VOID
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)

// private
NTSYSAPI
PWSTR
NTAPI
RtlGetNtSystemRoot(
    VOID
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlAreLongPathsEnabled(
    VOID
    );

#endif

NTSYSAPI
BOOLEAN
NTAPI
RtlIsThreadWithinLoaderCallout(
    VOID
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlDllShutdownInProgress(
    VOID
    );

// Heaps

typedef struct _RTL_HEAP_ENTRY
{
    SIZE_T Size;
    USHORT Flags;
    USHORT AllocatorBackTraceIndex;
    union
    {
        struct
        {
            SIZE_T Settable;
            ULONG Tag;
        } s1;
        struct
        {
            SIZE_T CommittedSize;
            PVOID FirstBlock;
        } s2;
    } u;
} RTL_HEAP_ENTRY, *PRTL_HEAP_ENTRY;

#define RTL_HEAP_BUSY (USHORT)0x0001
#define RTL_HEAP_SEGMENT (USHORT)0x0002
#define RTL_HEAP_SETTABLE_VALUE (USHORT)0x0010
#define RTL_HEAP_SETTABLE_FLAG1 (USHORT)0x0020
#define RTL_HEAP_SETTABLE_FLAG2 (USHORT)0x0040
#define RTL_HEAP_SETTABLE_FLAG3 (USHORT)0x0080
#define RTL_HEAP_SETTABLE_FLAGS (USHORT)0x00e0
#define RTL_HEAP_UNCOMMITTED_RANGE (USHORT)0x0100
#define RTL_HEAP_PROTECTED_ENTRY (USHORT)0x0200

typedef struct _RTL_HEAP_TAG
{
    ULONG NumberOfAllocations;
    ULONG NumberOfFrees;
    SIZE_T BytesAllocated;
    USHORT TagIndex;
    USHORT CreatorBackTraceIndex;
    WCHAR TagName[24];
} RTL_HEAP_TAG, *PRTL_HEAP_TAG;

typedef struct _RTL_HEAP_INFORMATION
{
    PVOID BaseAddress;
    ULONG Flags;
    USHORT EntryOverhead;
    USHORT CreatorBackTraceIndex;
    SIZE_T BytesAllocated;
    SIZE_T BytesCommitted;
    ULONG NumberOfTags;
    ULONG NumberOfEntries;
    ULONG NumberOfPseudoTags;
    ULONG PseudoTagGranularity;
    ULONG Reserved[5];
    PRTL_HEAP_TAG Tags;
    PRTL_HEAP_ENTRY Entries;
} RTL_HEAP_INFORMATION, *PRTL_HEAP_INFORMATION;

#define RTL_HEAP_SIGNATURE 0xFFEEFFEEUL
#define RTL_HEAP_SEGMENT_SIGNATURE 0xDDEEDDEEUL

typedef struct _RTL_PROCESS_HEAPS
{
    ULONG NumberOfHeaps;
    RTL_HEAP_INFORMATION Heaps[1];
} RTL_PROCESS_HEAPS, *PRTL_PROCESS_HEAPS;

typedef NTSTATUS (NTAPI *PRTL_HEAP_COMMIT_ROUTINE)(
    _In_ PVOID Base,
    _Inout_ PVOID *CommitAddress,
    _Inout_ PSIZE_T CommitSize
    );

typedef struct _RTL_HEAP_PARAMETERS
{
    ULONG Length;
    SIZE_T SegmentReserve;
    SIZE_T SegmentCommit;
    SIZE_T DeCommitFreeBlockThreshold;
    SIZE_T DeCommitTotalFreeThreshold;
    SIZE_T MaximumAllocationSize;
    SIZE_T VirtualMemoryThreshold;
    SIZE_T InitialCommit;
    SIZE_T InitialReserve;
    PRTL_HEAP_COMMIT_ROUTINE CommitRoutine;
    SIZE_T Reserved[2];
} RTL_HEAP_PARAMETERS, *PRTL_HEAP_PARAMETERS;

#define HEAP_SETTABLE_USER_VALUE 0x00000100
#define HEAP_SETTABLE_USER_FLAG1 0x00000200
#define HEAP_SETTABLE_USER_FLAG2 0x00000400
#define HEAP_SETTABLE_USER_FLAG3 0x00000800
#define HEAP_SETTABLE_USER_FLAGS 0x00000e00

#define HEAP_CLASS_0 0x00000000 // Process heap
#define HEAP_CLASS_1 0x00001000 // Private heap
#define HEAP_CLASS_2 0x00002000 // Kernel heap
#define HEAP_CLASS_3 0x00003000 // GDI heap
#define HEAP_CLASS_4 0x00004000 // User heap
#define HEAP_CLASS_5 0x00005000 // Console heap
#define HEAP_CLASS_6 0x00006000 // User desktop heap
#define HEAP_CLASS_7 0x00007000 // CSR shared heap
#define HEAP_CLASS_8 0x00008000 // CSR port heap
#define HEAP_CLASS_MASK 0x0000f000

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlCreateHeap(
    _In_ ULONG Flags,
    _In_opt_ PVOID HeapBase,
    _In_opt_ SIZE_T ReserveSize,
    _In_opt_ SIZE_T CommitSize,
    _In_opt_ PVOID Lock,
    _In_opt_ PRTL_HEAP_PARAMETERS Parameters
    );

NTSYSAPI
PVOID
NTAPI
RtlDestroyHeap(
    _In_ _Post_invalid_ PVOID HeapHandle
    );

_Must_inspect_result_
_Ret_maybenull_
_Post_writable_byte_size_(Size)
NTSYSAPI
PVOID
NTAPI
RtlAllocateHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _In_ SIZE_T Size
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
_Success_(return != 0)
NTSYSAPI
LOGICAL
NTAPI
RtlFreeHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress
    );
#else
_Success_(return)
NTSYSAPI
BOOLEAN
NTAPI
RtlFreeHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress
    );
#endif

NTSYSAPI
SIZE_T
NTAPI
RtlSizeHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlZeroHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags
    );

NTSYSAPI
VOID
NTAPI
RtlProtectHeap(
    _In_ PVOID HeapHandle,
    _In_ BOOLEAN MakeReadOnly
    );

#define RtlProcessHeap() (NtCurrentPeb()->ProcessHeap)

NTSYSAPI
BOOLEAN
NTAPI
RtlLockHeap(
    _In_ PVOID HeapHandle
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlUnlockHeap(
    _In_ PVOID HeapHandle
    );

NTSYSAPI
PVOID
NTAPI
RtlReAllocateHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress,
    _In_ SIZE_T Size
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlGetUserInfoHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _Out_opt_ PVOID *UserValue,
    _Out_opt_ PULONG UserFlags
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlSetUserValueHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ PVOID UserValue
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlSetUserFlagsHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ ULONG UserFlagsReset,
    _In_ ULONG UserFlagsSet
    );

typedef struct _RTL_HEAP_TAG_INFO
{
    ULONG NumberOfAllocations;
    ULONG NumberOfFrees;
    SIZE_T BytesAllocated;
} RTL_HEAP_TAG_INFO, *PRTL_HEAP_TAG_INFO;

#define RTL_HEAP_MAKE_TAG HEAP_MAKE_TAG_FLAGS

NTSYSAPI
ULONG
NTAPI
RtlCreateTagHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_opt_ PWSTR TagPrefix,
    _In_ PWSTR TagNames
    );

NTSYSAPI
PWSTR
NTAPI
RtlQueryTagHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ USHORT TagIndex,
    _In_ BOOLEAN ResetCounters,
    _Out_opt_ PRTL_HEAP_TAG_INFO TagInfo
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlExtendHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID Base,
    _In_ SIZE_T Size
    );

NTSYSAPI
SIZE_T
NTAPI
RtlCompactHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlValidateHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlValidateProcessHeaps(
    VOID
    );

NTSYSAPI
ULONG
NTAPI
RtlGetProcessHeaps(
    _In_ ULONG NumberOfHeaps,
    _Out_ PVOID *ProcessHeaps
    );

typedef NTSTATUS (NTAPI *PRTL_ENUM_HEAPS_ROUTINE)(
    _In_ PVOID HeapHandle,
    _In_ PVOID Parameter
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlEnumProcessHeaps(
    _In_ PRTL_ENUM_HEAPS_ROUTINE EnumRoutine,
    _In_ PVOID Parameter
    );

typedef struct _RTL_HEAP_USAGE_ENTRY
{
    struct _RTL_HEAP_USAGE_ENTRY *Next;
    PVOID Address;
    SIZE_T Size;
    USHORT AllocatorBackTraceIndex;
    USHORT TagIndex;
} RTL_HEAP_USAGE_ENTRY, *PRTL_HEAP_USAGE_ENTRY;

typedef struct _RTL_HEAP_USAGE
{
    ULONG Length;
    SIZE_T BytesAllocated;
    SIZE_T BytesCommitted;
    SIZE_T BytesReserved;
    SIZE_T BytesReservedMaximum;
    PRTL_HEAP_USAGE_ENTRY Entries;
    PRTL_HEAP_USAGE_ENTRY AddedEntries;
    PRTL_HEAP_USAGE_ENTRY RemovedEntries;
    ULONG_PTR Reserved[8];
} RTL_HEAP_USAGE, *PRTL_HEAP_USAGE;

#define HEAP_USAGE_ALLOCATED_BLOCKS HEAP_REALLOC_IN_PLACE_ONLY
#define HEAP_USAGE_FREE_BUFFER HEAP_ZERO_MEMORY

NTSYSAPI
NTSTATUS
NTAPI
RtlUsageHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _Inout_ PRTL_HEAP_USAGE Usage
    );

typedef struct _RTL_HEAP_WALK_ENTRY
{
    PVOID DataAddress;
    SIZE_T DataSize;
    UCHAR OverheadBytes;
    UCHAR SegmentIndex;
    USHORT Flags;
    union
    {
        struct
        {
            SIZE_T Settable;
            USHORT TagIndex;
            USHORT AllocatorBackTraceIndex;
            ULONG Reserved[2];
        } Block;
        struct
        {
            ULONG CommittedSize;
            ULONG UnCommittedSize;
            PVOID FirstEntry;
            PVOID LastEntry;
        } Segment;
    };
} RTL_HEAP_WALK_ENTRY, *PRTL_HEAP_WALK_ENTRY;

NTSYSAPI
NTSTATUS
NTAPI
RtlWalkHeap(
    _In_ PVOID HeapHandle,
    _Inout_ PRTL_HEAP_WALK_ENTRY Entry
    );

// HEAP_INFORMATION_CLASS
#define HeapCompatibilityInformation 0x0 // q; s: ULONG
#define HeapEnableTerminationOnCorruption 0x1 // q; s: NULL
#define HeapExtendedInformation 0x2 // q; s: HEAP_EXTENDED_INFORMATION
#define HeapOptimizeResources 0x3 // q; s: HEAP_OPTIMIZE_RESOURCES_INFORMATION 
#define HeapTaggingInformation 0x4
#define HeapStackDatabase 0x5
#define HeapMemoryLimit 0x6 // 19H2
#define HeapDetailedFailureInformation 0x80000001
#define HeapSetDebuggingInformation 0x80000002 // q; s: HEAP_DEBUGGING_INFORMATION

typedef enum _HEAP_COMPATIBILITY_MODE
{
    HEAP_COMPATIBILITY_STANDARD = 0UL,
    HEAP_COMPATIBILITY_LAL = 1UL,
    HEAP_COMPATIBILITY_LFH = 2UL,
} HEAP_COMPATIBILITY_MODE;

typedef struct _PROCESS_HEAP_INFORMATION
{
    ULONG_PTR ReserveSize;
    ULONG_PTR CommitSize;
    ULONG NumberOfHeaps;
    ULONG_PTR FirstHeapInformationOffset;
} PROCESS_HEAP_INFORMATION, *PPROCESS_HEAP_INFORMATION;

typedef struct _HEAP_INFORMATION
{
    ULONG_PTR Address;
    ULONG Mode;
    ULONG_PTR ReserveSize;
    ULONG_PTR CommitSize;
    ULONG_PTR FirstRegionInformationOffset;
    ULONG_PTR NextHeapInformationOffset;
} HEAP_INFORMATION, *PHEAP_INFORMATION;

typedef struct _HEAP_EXTENDED_INFORMATION
{
    HANDLE Process;
    ULONG_PTR Heap;
    ULONG Level;
    PVOID CallbackRoutine;
    PVOID CallbackContext;
    union
    {
        PROCESS_HEAP_INFORMATION ProcessHeapInformation;
        HEAP_INFORMATION HeapInformation;
    };
} HEAP_EXTENDED_INFORMATION, *PHEAP_EXTENDED_INFORMATION;

// rev
typedef NTSTATUS (NTAPI *PRTL_HEAP_LEAK_ENUMERATION_ROUTINE)(
    _In_ LONG Reserved,
    _In_ PVOID HeapHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T BlockSize,
    _In_ ULONG StackTraceDepth,
    _In_ PVOID *StackTrace
    );

// symbols
typedef struct _HEAP_DEBUGGING_INFORMATION
{
    PVOID InterceptorFunction;
    USHORT InterceptorValue;
    ULONG ExtendedOptions;
    ULONG StackTraceDepth;
    SIZE_T MinTotalBlockSize;
    SIZE_T MaxTotalBlockSize;
    PRTL_HEAP_LEAK_ENUMERATION_ROUTINE HeapLeakEnumerationRoutine;
} HEAP_DEBUGGING_INFORMATION, *PHEAP_DEBUGGING_INFORMATION;

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryHeapInformation(
    _In_ PVOID HeapHandle,
    _In_ HEAP_INFORMATION_CLASS HeapInformationClass,
    _Out_opt_ PVOID HeapInformation,
    _In_opt_ SIZE_T HeapInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetHeapInformation(
    _In_ PVOID HeapHandle,
    _In_ HEAP_INFORMATION_CLASS HeapInformationClass,
    _In_opt_ PVOID HeapInformation,
    _In_opt_ SIZE_T HeapInformationLength
    );

NTSYSAPI
ULONG
NTAPI
RtlMultipleAllocateHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Count,
    _Out_ PVOID *Array
    );

NTSYSAPI
ULONG
NTAPI
RtlMultipleFreeHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ ULONG Count,
    _In_ PVOID *Array
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
VOID
NTAPI
RtlDetectHeapLeaks(
    VOID
    );
#endif

NTSYSAPI
VOID
NTAPI
RtlFlushHeaps(
    VOID
    );

// Memory zones

// begin_private

typedef struct _RTL_MEMORY_ZONE_SEGMENT
{
    struct _RTL_MEMORY_ZONE_SEGMENT *NextSegment;
    SIZE_T Size;
    PVOID Next;
    PVOID Limit;
} RTL_MEMORY_ZONE_SEGMENT, *PRTL_MEMORY_ZONE_SEGMENT;

typedef struct _RTL_MEMORY_ZONE
{
    RTL_MEMORY_ZONE_SEGMENT Segment;
    RTL_SRWLOCK Lock;
    ULONG LockCount;
    PRTL_MEMORY_ZONE_SEGMENT FirstSegment;
} RTL_MEMORY_ZONE, *PRTL_MEMORY_ZONE;

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateMemoryZone(
    _Out_ PVOID *MemoryZone,
    _In_ SIZE_T InitialSize,
    _Reserved_ ULONG Flags
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyMemoryZone(
    _In_ _Post_invalid_ PVOID MemoryZone
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateMemoryZone(
    _In_ PVOID MemoryZone,
    _In_ SIZE_T BlockSize,
    _Out_ PVOID *Block
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlResetMemoryZone(
    _In_ PVOID MemoryZone
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlLockMemoryZone(
    _In_ PVOID MemoryZone
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockMemoryZone(
    _In_ PVOID MemoryZone
    );

#endif

// end_private

// Memory block lookaside lists

// begin_private

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateMemoryBlockLookaside(
    _Out_ PVOID *MemoryBlockLookaside,
    _Reserved_ ULONG Flags,
    _In_ ULONG InitialSize,
    _In_ ULONG MinimumBlockSize,
    _In_ ULONG MaximumBlockSize
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside,
    _In_ ULONG BlockSize,
    _Out_ PVOID *Block
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlFreeMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside,
    _In_ PVOID Block
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlExtendMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside,
    _In_ ULONG Increment
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlResetMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlLockMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside
    );

#endif

// end_private

// Transactions

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
HANDLE
NTAPI
RtlGetCurrentTransaction(
    VOID
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
LOGICAL
NTAPI
RtlSetCurrentTransaction(
    _In_ HANDLE TransactionHandle
    );
#endif

// LUIDs

FORCEINLINE BOOLEAN RtlIsEqualLuid( // RtlEqualLuid
    _In_ PLUID L1,
    _In_ PLUID L2
    )
{
    return L1->LowPart == L2->LowPart &&
        L1->HighPart == L2->HighPart;
}

FORCEINLINE BOOLEAN RtlIsZeroLuid(
    _In_ PLUID L1
    )
{
    return (L1->LowPart | L1->HighPart) == 0;
}

FORCEINLINE LUID RtlConvertLongToLuid(
    _In_ LONG Long
    )
{
    LUID tempLuid;
    LARGE_INTEGER tempLi;

    tempLi.QuadPart = Long;
    tempLuid.LowPart = tempLi.LowPart;
    tempLuid.HighPart = tempLi.HighPart;

    return tempLuid;
}

FORCEINLINE LUID RtlConvertUlongToLuid(
    _In_ ULONG Ulong
    )
{
    LUID tempLuid;

    tempLuid.LowPart = Ulong;
    tempLuid.HighPart = 0;

    return tempLuid;
}

NTSYSAPI
VOID
NTAPI
RtlCopyLuid(
    _Out_ PLUID DestinationLuid,
    _In_ PLUID SourceLuid
    );

// ros
NTSYSAPI
VOID
NTAPI
RtlCopyLuidAndAttributesArray(
    _In_ ULONG Count,
    _In_ PLUID_AND_ATTRIBUTES Src,
    _In_ PLUID_AND_ATTRIBUTES Dest
    );

// Byte swap routines.

NTSYSAPI
USHORT
FASTCALL
RtlUshortByteSwap(
    _In_ USHORT Source
    );

NTSYSAPI
ULONG
FASTCALL
RtlUlongByteSwap(
    _In_ ULONG Source
    );

NTSYSAPI
ULONGLONG
FASTCALL
RtlUlonglongByteSwap(
    _In_ ULONGLONG Source
    );

// Debugging

// private
typedef struct _RTL_PROCESS_VERIFIER_OPTIONS
{
    ULONG SizeStruct;
    ULONG Option;
    UCHAR OptionData[1];
} RTL_PROCESS_VERIFIER_OPTIONS, *PRTL_PROCESS_VERIFIER_OPTIONS;

// private
typedef struct _RTL_DEBUG_INFORMATION
{
    HANDLE SectionHandleClient;
    PVOID ViewBaseClient;
    PVOID ViewBaseTarget;
    ULONG_PTR ViewBaseDelta;
    HANDLE EventPairClient;
    HANDLE EventPairTarget;
    HANDLE TargetProcessId;
    HANDLE TargetThreadHandle;
    ULONG Flags;
    SIZE_T OffsetFree;
    SIZE_T CommitSize;
    SIZE_T ViewSize;
    union
    {
        struct _RTL_PROCESS_MODULES *Modules;
        struct _RTL_PROCESS_MODULE_INFORMATION_EX *ModulesEx;
    };
    struct _RTL_PROCESS_BACKTRACES *BackTraces;
    struct _RTL_PROCESS_HEAPS *Heaps;
    struct _RTL_PROCESS_LOCKS *Locks;
    PVOID SpecificHeap;
    HANDLE TargetProcessHandle;
    PRTL_PROCESS_VERIFIER_OPTIONS VerifierOptions;
    PVOID ProcessHeap;
    HANDLE CriticalSectionHandle;
    HANDLE CriticalSectionOwnerThread;
    PVOID Reserved[4];
} RTL_DEBUG_INFORMATION, *PRTL_DEBUG_INFORMATION;

NTSYSAPI
PRTL_DEBUG_INFORMATION
NTAPI
RtlCreateQueryDebugBuffer(
    _In_opt_ ULONG MaximumCommit,
    _In_ BOOLEAN UseEventPair
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyQueryDebugBuffer(
    _In_ PRTL_DEBUG_INFORMATION Buffer
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
PVOID
NTAPI
RtlCommitDebugInfo(
    _Inout_ PRTL_DEBUG_INFORMATION Buffer,
    _In_ SIZE_T Size
    );

// private
NTSYSAPI
VOID
NTAPI
RtlDeCommitDebugInfo(
    _Inout_ PRTL_DEBUG_INFORMATION Buffer,
    _In_ PVOID p,
    _In_ SIZE_T Size
    );

#endif

#define RTL_QUERY_PROCESS_MODULES 0x00000001
#define RTL_QUERY_PROCESS_BACKTRACES 0x00000002
#define RTL_QUERY_PROCESS_HEAP_SUMMARY 0x00000004
#define RTL_QUERY_PROCESS_HEAP_TAGS 0x00000008
#define RTL_QUERY_PROCESS_HEAP_ENTRIES 0x00000010
#define RTL_QUERY_PROCESS_LOCKS 0x00000020
#define RTL_QUERY_PROCESS_MODULES32 0x00000040
#define RTL_QUERY_PROCESS_VERIFIER_OPTIONS 0x00000080 // rev
#define RTL_QUERY_PROCESS_MODULESEX 0x00000100 // rev
#define RTL_QUERY_PROCESS_HEAP_ENTRIES_EX 0x00000200 // ?
#define RTL_QUERY_PROCESS_CS_OWNER 0x00000400 // rev
#define RTL_QUERY_PROCESS_NONINVASIVE 0x80000000

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryProcessDebugInformation(
    _In_ HANDLE UniqueProcessId,
    _In_ ULONG Flags,
    _Inout_ PRTL_DEBUG_INFORMATION Buffer
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetProcessDebugInformation(
    _In_ HANDLE UniqueProcessId,
    _In_ ULONG Flags,
    _Inout_ PRTL_DEBUG_INFORMATION Buffer
    );

// Messages

NTSYSAPI
NTSTATUS
NTAPI
RtlFindMessage(
    _In_ PVOID DllHandle,
    _In_ ULONG MessageTableId,
    _In_ ULONG MessageLanguageId,
    _In_ ULONG MessageId,
    _Out_ PMESSAGE_RESOURCE_ENTRY *MessageEntry
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlFormatMessage(
    _In_ PWSTR MessageFormat,
    _In_ ULONG MaximumWidth,
    _In_ BOOLEAN IgnoreInserts,
    _In_ BOOLEAN ArgumentsAreAnsi,
    _In_ BOOLEAN ArgumentsAreAnArray,
    _In_ va_list *Arguments,
    _Out_writes_bytes_to_(Length, *ReturnLength) PWSTR Buffer,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength
    );

typedef struct _PARSE_MESSAGE_CONTEXT
{
    ULONG fFlags;
    ULONG cwSavColumn;
    SIZE_T iwSrc;
    SIZE_T iwDst;
    SIZE_T iwDstSpace;
    va_list lpvArgStart;
} PARSE_MESSAGE_CONTEXT, *PPARSE_MESSAGE_CONTEXT;

#define INIT_PARSE_MESSAGE_CONTEXT(ctx) { (ctx)->fFlags = 0; }
#define TEST_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag) ((ctx)->fFlags & (flag))
#define SET_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag) ((ctx)->fFlags |= (flag))
#define CLEAR_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag) ((ctx)->fFlags &= ~(flag))

NTSYSAPI
NTSTATUS
NTAPI
RtlFormatMessageEx(
    _In_ PWSTR MessageFormat,
    _In_ ULONG MaximumWidth,
    _In_ BOOLEAN IgnoreInserts,
    _In_ BOOLEAN ArgumentsAreAnsi,
    _In_ BOOLEAN ArgumentsAreAnArray,
    _In_ va_list *Arguments,
    _Out_writes_bytes_to_(Length, *ReturnLength) PWSTR Buffer,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength,
    _Out_opt_ PPARSE_MESSAGE_CONTEXT ParseContext
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetFileMUIPath(
    _In_ ULONG Flags,
    _In_ PCWSTR FilePath,
    _Inout_opt_ PWSTR Language,
    _Inout_ PULONG LanguageLength,
    _Out_opt_ PWSTR FileMUIPath,
    _Inout_ PULONG FileMUIPathLength,
    _Inout_ PULONGLONG Enumerator
    );

// Errors

NTSYSAPI
ULONG
NTAPI
RtlNtStatusToDosError(
    _In_ NTSTATUS Status
    );

NTSYSAPI
ULONG
NTAPI
RtlNtStatusToDosErrorNoTeb(
    _In_ NTSTATUS Status
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetLastNtStatus(
    VOID
    );

NTSYSAPI
LONG
NTAPI
RtlGetLastWin32Error(
    VOID
    );

NTSYSAPI
VOID
NTAPI
RtlSetLastWin32ErrorAndNtStatusFromNtStatus(
    _In_ NTSTATUS Status
    );

NTSYSAPI
VOID
NTAPI
RtlSetLastWin32Error(
    _In_ LONG Win32Error
    );

NTSYSAPI
VOID
NTAPI
RtlRestoreLastWin32Error(
    _In_ LONG Win32Error
    );

#define RTL_ERRORMODE_FAILCRITICALERRORS 0x0010
#define RTL_ERRORMODE_NOGPFAULTERRORBOX 0x0020
#define RTL_ERRORMODE_NOOPENFILEERRORBOX 0x0040

NTSYSAPI
ULONG
NTAPI
RtlGetThreadErrorMode(
    VOID
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetThreadErrorMode(
    _In_ ULONG NewMode,
    _Out_opt_ PULONG OldMode
    );

// Windows Error Reporting

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlReportException(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ ULONG Flags
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlReportExceptionEx(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ ULONG Flags,
    _In_ PLARGE_INTEGER Timeout
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlWerpReportException(
    _In_ ULONG ProcessId,
    _In_ HANDLE CrashReportSharedMem,
    _In_ ULONG Flags,
    _Out_ PHANDLE CrashVerticalProcessHandle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlReportSilentProcessExit(
    _In_ HANDLE ProcessHandle,
    _In_ NTSTATUS ExitStatus
    );
#endif

// Vectored Exception Handlers

NTSYSAPI
PVOID
NTAPI
RtlAddVectoredExceptionHandler(
    _In_ ULONG First,
    _In_ PVECTORED_EXCEPTION_HANDLER Handler
    );

NTSYSAPI
ULONG
NTAPI
RtlRemoveVectoredExceptionHandler(
    _In_ PVOID Handle
    );

NTSYSAPI
PVOID
NTAPI
RtlAddVectoredContinueHandler(
    _In_ ULONG First,
    _In_ PVECTORED_EXCEPTION_HANDLER Handler
    );

NTSYSAPI
ULONG
NTAPI
RtlRemoveVectoredContinueHandler(
    _In_ PVOID Handle
    );

// Random

NTSYSAPI
ULONG
NTAPI
RtlUniform(
    _Inout_ PULONG Seed
    );

_Ret_range_(<=, MAXLONG)
NTSYSAPI
ULONG
NTAPI
RtlRandom(
    _Inout_ PULONG Seed
    );

_Ret_range_(<=, MAXLONG)
NTSYSAPI
ULONG
NTAPI
RtlRandomEx(
    _Inout_ PULONG Seed
    );

#define RTL_IMPORT_TABLE_HASH_REVISION 1

NTSYSAPI
NTSTATUS
NTAPI
RtlComputeImportTableHash(
    _In_ HANDLE FileHandle,
    _Out_writes_bytes_(16) PCHAR Hash,
    _In_ ULONG ImportTableHashRevision // must be 1
    );

// Integer conversion

NTSYSAPI
NTSTATUS
NTAPI
RtlIntegerToChar(
    _In_ ULONG Value,
    _In_opt_ ULONG Base,
    _In_ LONG OutputLength, // negative to pad to width
    _Out_ PSTR String
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCharToInteger(
    _In_ PCSTR String,
    _In_opt_ ULONG Base,
    _Out_ PULONG Value
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlLargeIntegerToChar(
    _In_ PLARGE_INTEGER Value,
    _In_opt_ ULONG Base,
    _In_ LONG OutputLength,
    _Out_ PSTR String
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIntegerToUnicodeString(
    _In_ ULONG Value,
    _In_opt_ ULONG Base,
    _Inout_ PUNICODE_STRING String
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlInt64ToUnicodeString(
    _In_ ULONGLONG Value,
    _In_opt_ ULONG Base,
    _Inout_ PUNICODE_STRING String
    );

#ifdef _WIN64
#define RtlIntPtrToUnicodeString(Value, Base, String) RtlInt64ToUnicodeString(Value, Base, String)
#else
#define RtlIntPtrToUnicodeString(Value, Base, String) RtlIntegerToUnicodeString(Value, Base, String)
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToInteger(
    _In_ PUNICODE_STRING String,
    _In_opt_ ULONG Base,
    _Out_ PULONG Value
    );

// IPv4/6 conversion

struct in_addr;
struct in6_addr;

NTSYSAPI
PWSTR
NTAPI
RtlIpv4AddressToStringW(
    _In_ const struct in_addr *Address,
    _Out_writes_(16) PWSTR AddressString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIpv4AddressToStringExW(
    _In_ const struct in_addr *Address,
    _In_ USHORT Port,
    _Out_writes_to_(*AddressStringLength, *AddressStringLength) PWSTR AddressString,
    _Inout_ PULONG AddressStringLength
    );

NTSYSAPI
PWSTR
NTAPI
RtlIpv6AddressToStringW(
    _In_ const struct in6_addr *Address,
    _Out_writes_(46) PWSTR AddressString
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIpv6AddressToStringExW(
    _In_ const struct in6_addr *Address,
    _In_ ULONG ScopeId,
    _In_ USHORT Port,
    _Out_writes_to_(*AddressStringLength, *AddressStringLength) PWSTR AddressString,
    _Inout_ PULONG AddressStringLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIpv4StringToAddressW(
    _In_ PCWSTR AddressString,
    _In_ BOOLEAN Strict,
    _Out_ LPCWSTR *Terminator,
    _Out_ struct in_addr *Address
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIpv4StringToAddressExW(
    _In_ PCWSTR AddressString,
    _In_ BOOLEAN Strict,
    _Out_ struct in_addr *Address,
    _Out_ PUSHORT Port
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIpv6StringToAddressW(
    _In_ PCWSTR AddressString,
    _Out_ PCWSTR *Terminator,
    _Out_ struct in6_addr *Address
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIpv6StringToAddressExW(
    _In_ PCWSTR AddressString,
    _Out_ struct in6_addr *Address,
    _Out_ PULONG ScopeId,
    _Out_ PUSHORT Port
    );

#define RtlIpv4AddressToString RtlIpv4AddressToStringW
#define RtlIpv4AddressToStringEx RtlIpv4AddressToStringExW
#define RtlIpv6AddressToString RtlIpv6AddressToStringW
#define RtlIpv6AddressToStringEx RtlIpv6AddressToStringExW
#define RtlIpv4StringToAddress RtlIpv4StringToAddressW
#define RtlIpv4StringToAddressEx RtlIpv4StringToAddressExW
#define RtlIpv6StringToAddress RtlIpv6StringToAddressW
#define RtlIpv6StringToAddressEx RtlIpv6StringToAddressExW

// Time

typedef struct _TIME_FIELDS
{
    CSHORT Year; // 1601...
    CSHORT Month; // 1..12
    CSHORT Day; // 1..31
    CSHORT Hour; // 0..23
    CSHORT Minute; // 0..59
    CSHORT Second; // 0..59
    CSHORT Milliseconds; // 0..999
    CSHORT Weekday; // 0..6 = Sunday..Saturday
} TIME_FIELDS, *PTIME_FIELDS;

NTSYSAPI
BOOLEAN
NTAPI
RtlCutoverTimeToSystemTime(
    _In_ PTIME_FIELDS CutoverTime,
    _Out_ PLARGE_INTEGER SystemTime,
    _In_ PLARGE_INTEGER CurrentSystemTime,
    _In_ BOOLEAN ThisYear
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSystemTimeToLocalTime(
    _In_ PLARGE_INTEGER SystemTime,
    _Out_ PLARGE_INTEGER LocalTime
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlLocalTimeToSystemTime(
    _In_ PLARGE_INTEGER LocalTime,
    _Out_ PLARGE_INTEGER SystemTime
    );

NTSYSAPI
VOID
NTAPI
RtlTimeToElapsedTimeFields(
    _In_ PLARGE_INTEGER Time,
    _Out_ PTIME_FIELDS TimeFields
    );

NTSYSAPI
VOID
NTAPI
RtlTimeToTimeFields(
    _In_ PLARGE_INTEGER Time,
    _Out_ PTIME_FIELDS TimeFields
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlTimeFieldsToTime(
    _In_ PTIME_FIELDS TimeFields, // Weekday is ignored
    _Out_ PLARGE_INTEGER Time
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlTimeToSecondsSince1980(
    _In_ PLARGE_INTEGER Time,
    _Out_ PULONG ElapsedSeconds
    );

NTSYSAPI
VOID
NTAPI
RtlSecondsSince1980ToTime(
    _In_ ULONG ElapsedSeconds,
    _Out_ PLARGE_INTEGER Time
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlTimeToSecondsSince1970(
    _In_ PLARGE_INTEGER Time,
    _Out_ PULONG ElapsedSeconds
    );

NTSYSAPI
VOID
NTAPI
RtlSecondsSince1970ToTime(
    _In_ ULONG ElapsedSeconds,
    _Out_ PLARGE_INTEGER Time
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
ULONGLONG
NTAPI
RtlGetSystemTimePrecise(
    VOID
    );
#endif

// Time zones

typedef struct _RTL_TIME_ZONE_INFORMATION
{
    LONG Bias;
    WCHAR StandardName[32];
    TIME_FIELDS StandardStart;
    LONG StandardBias;
    WCHAR DaylightName[32];
    TIME_FIELDS DaylightStart;
    LONG DaylightBias;
} RTL_TIME_ZONE_INFORMATION, *PRTL_TIME_ZONE_INFORMATION;

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryTimeZoneInformation(
    _Out_ PRTL_TIME_ZONE_INFORMATION TimeZoneInformation
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetTimeZoneInformation(
    _In_ PRTL_TIME_ZONE_INFORMATION TimeZoneInformation
    );

// Bitmaps

typedef struct _RTL_BITMAP
{
    ULONG SizeOfBitMap;
    PULONG Buffer;
} RTL_BITMAP, *PRTL_BITMAP;

NTSYSAPI
VOID
NTAPI
RtlInitializeBitMap(
    _Out_ PRTL_BITMAP BitMapHeader,
    _In_ PULONG BitMapBuffer,
    _In_ ULONG SizeOfBitMap
    );

_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlTestBit(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber
    );

NTSYSAPI
VOID
NTAPI
RtlClearAllBits(
    _In_ PRTL_BITMAP BitMapHeader
    );

NTSYSAPI
VOID
NTAPI
RtlSetAllBits(
    _In_ PRTL_BITMAP BitMapHeader
    );

_Success_(return != -1)
_Check_return_
NTSYSAPI
ULONG
NTAPI
RtlFindClearBits(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex
    );

_Success_(return != -1)
_Check_return_
NTSYSAPI
ULONG
NTAPI
RtlFindSetBits(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex
    );

_Success_(return != -1)
NTSYSAPI
ULONG
NTAPI
RtlFindClearBitsAndSet(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex
    );

_Success_(return != -1)
NTSYSAPI
ULONG
NTAPI
RtlFindSetBitsAndClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex
    );

NTSYSAPI
VOID
NTAPI
RtlClearBits(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear
    );

NTSYSAPI
VOID
NTAPI
RtlSetBits(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet
    );

NTSYSAPI
CCHAR
NTAPI
RtlFindMostSignificantBit(
    _In_ ULONGLONG Set
    );

NTSYSAPI
CCHAR
NTAPI
RtlFindLeastSignificantBit(
    _In_ ULONGLONG Set
    );

typedef struct _RTL_BITMAP_RUN
{
    ULONG StartingIndex;
    ULONG NumberOfBits;
} RTL_BITMAP_RUN, *PRTL_BITMAP_RUN;

NTSYSAPI
ULONG
NTAPI
RtlFindClearRuns(
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_writes_to_(SizeOfRunArray, return) PRTL_BITMAP_RUN RunArray,
    _In_range_(>, 0) ULONG SizeOfRunArray,
    _In_ BOOLEAN LocateLongestRuns
    );

NTSYSAPI
ULONG
NTAPI
RtlFindLongestRunClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_ PULONG StartingIndex
    );

NTSYSAPI
ULONG
NTAPI
RtlFindFirstRunClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_ PULONG StartingIndex
    );

_Check_return_
FORCEINLINE
BOOLEAN
RtlCheckBit(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitPosition
    )
{
#ifdef _WIN64
    return BitTest64((LONG64 const *)BitMapHeader->Buffer, (LONG64)BitPosition);
#else
    return (((PLONG)BitMapHeader->Buffer)[BitPosition / 32] >> (BitPosition % 32)) & 0x1;
#endif
}

NTSYSAPI
ULONG
NTAPI
RtlNumberOfClearBits(
    _In_ PRTL_BITMAP BitMapHeader
    );

NTSYSAPI
ULONG
NTAPI
RtlNumberOfSetBits(
    _In_ PRTL_BITMAP BitMapHeader
    );

_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlAreBitsClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length
    );

_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlAreBitsSet(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length
    );

NTSYSAPI
ULONG
NTAPI
RtlFindNextForwardRunClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex
    );

NTSYSAPI
ULONG
NTAPI
RtlFindLastBackwardRunClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
ULONG
NTAPI
RtlNumberOfSetBitsUlongPtr(
    _In_ ULONG_PTR Target
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)

// rev
NTSYSAPI
VOID
NTAPI
RtlInterlockedClearBitRun(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear
    );

// rev
NTSYSAPI
VOID
NTAPI
RtlInterlockedSetBitRun(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSAPI
VOID
NTAPI
RtlCopyBitMap(
    _In_ PRTL_BITMAP Source,
    _In_ PRTL_BITMAP Destination,
    _In_range_(0, Destination->SizeOfBitMap - 1) ULONG TargetBit
    );

NTSYSAPI
VOID
NTAPI
RtlExtractBitMap(
    _In_ PRTL_BITMAP Source,
    _In_ PRTL_BITMAP Destination,
    _In_range_(0, Source->SizeOfBitMap - 1) ULONG TargetBit,
    _In_range_(0, Source->SizeOfBitMap) ULONG NumberOfBits
    );

NTSYSAPI
ULONG
NTAPI
RtlNumberOfClearBitsInRange(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length
    );

NTSYSAPI
ULONG
NTAPI
RtlNumberOfSetBitsInRange(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length
    );

#endif


#if (NTDDI_VERSION >= NTDDI_WIN10)

// private
typedef struct _RTL_BITMAP_EX
{
    ULONG64 SizeOfBitMap;
    PULONG64 Buffer;
} RTL_BITMAP_EX, *PRTL_BITMAP_EX;

// rev
NTSYSAPI
VOID
NTAPI
RtlInitializeBitMapEx(
    _Out_ PRTL_BITMAP_EX BitMapHeader,
    _In_ PULONG64 BitMapBuffer,
    _In_ ULONG64 SizeOfBitMap
    );

// rev
_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlTestBitEx(
    _In_ PRTL_BITMAP_EX BitMapHeader,
    _In_range_(<, BitMapHeader->SizeOfBitMap) ULONG64 BitNumber
    );

#endif

// Handle tables

typedef struct _RTL_HANDLE_TABLE_ENTRY
{
    union
    {
        ULONG Flags; // allocated entries have the low bit set
        struct _RTL_HANDLE_TABLE_ENTRY *NextFree;
    };
} RTL_HANDLE_TABLE_ENTRY, *PRTL_HANDLE_TABLE_ENTRY;

#define RTL_HANDLE_ALLOCATED (USHORT)0x0001

typedef struct _RTL_HANDLE_TABLE
{
    ULONG MaximumNumberOfHandles;
    ULONG SizeOfHandleTableEntry;
    ULONG Reserved[2];
    PRTL_HANDLE_TABLE_ENTRY FreeHandles;
    PRTL_HANDLE_TABLE_ENTRY CommittedHandles;
    PRTL_HANDLE_TABLE_ENTRY UnCommittedHandles;
    PRTL_HANDLE_TABLE_ENTRY MaxReservedHandles;
} RTL_HANDLE_TABLE, *PRTL_HANDLE_TABLE;

NTSYSAPI
VOID
NTAPI
RtlInitializeHandleTable(
    _In_ ULONG MaximumNumberOfHandles,
    _In_ ULONG SizeOfHandleTableEntry,
    _Out_ PRTL_HANDLE_TABLE HandleTable
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyHandleTable(
    _Inout_ PRTL_HANDLE_TABLE HandleTable
    );

NTSYSAPI
PRTL_HANDLE_TABLE_ENTRY
NTAPI
RtlAllocateHandle(
    _In_ PRTL_HANDLE_TABLE HandleTable,
    _Out_opt_ PULONG HandleIndex
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlFreeHandle(
    _In_ PRTL_HANDLE_TABLE HandleTable,
    _In_ PRTL_HANDLE_TABLE_ENTRY Handle
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlIsValidHandle(
    _In_ PRTL_HANDLE_TABLE HandleTable,
    _In_ PRTL_HANDLE_TABLE_ENTRY Handle
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlIsValidIndexHandle(
    _In_ PRTL_HANDLE_TABLE HandleTable,
    _In_ ULONG HandleIndex,
    _Out_ PRTL_HANDLE_TABLE_ENTRY *Handle
    );

// Atom tables

#define RTL_ATOM_MAXIMUM_INTEGER_ATOM (RTL_ATOM)0xc000
#define RTL_ATOM_INVALID_ATOM (RTL_ATOM)0x0000
#define RTL_ATOM_TABLE_DEFAULT_NUMBER_OF_BUCKETS 37
#define RTL_ATOM_MAXIMUM_NAME_LENGTH 255
#define RTL_ATOM_PINNED 0x01

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateAtomTable(
    _In_ ULONG NumberOfBuckets,
    _Out_ PVOID *AtomTableHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyAtomTable(
    _In_ _Post_invalid_ PVOID AtomTableHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlEmptyAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ BOOLEAN IncludePinnedAtoms
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAtomToAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ PWSTR AtomName,
    _Inout_opt_ PRTL_ATOM Atom
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlLookupAtomInAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ PWSTR AtomName,
    _Out_opt_ PRTL_ATOM Atom
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteAtomFromAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ RTL_ATOM Atom
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlPinAtomInAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ RTL_ATOM Atom
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryAtomInAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ RTL_ATOM Atom,
    _Out_opt_ PULONG AtomUsage,
    _Out_opt_ PULONG AtomFlags,
    _Inout_updates_bytes_to_opt_(*AtomNameLength, *AtomNameLength) PWSTR AtomName,
    _Inout_opt_ PULONG AtomNameLength
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlGetIntegerAtom(
    _In_ PWSTR AtomName,
    _Out_opt_ PUSHORT IntegerAtom
    );
#endif

// SIDs

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlValidSid(
    _In_ PSID Sid
    );

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualSid(
    _In_ PSID Sid1,
    _In_ PSID Sid2
    );

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualPrefixSid(
    _In_ PSID Sid1,
    _In_ PSID Sid2
    );

NTSYSAPI
ULONG
NTAPI
RtlLengthRequiredSid(
    _In_ ULONG SubAuthorityCount
    );

NTSYSAPI
PVOID
NTAPI
RtlFreeSid(
    _In_ _Post_invalid_ PSID Sid
    );

_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateAndInitializeSid(
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    _In_ ULONG SubAuthority0,
    _In_ ULONG SubAuthority1,
    _In_ ULONG SubAuthority2,
    _In_ ULONG SubAuthority3,
    _In_ ULONG SubAuthority4,
    _In_ ULONG SubAuthority5,
    _In_ ULONG SubAuthority6,
    _In_ ULONG SubAuthority7,
    _Outptr_ PSID *Sid
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateAndInitializeSidEx(
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    _In_reads_(SubAuthorityCount) PULONG SubAuthorities,
    _Outptr_ PSID *Sid
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlInitializeSid(
    _Out_ PSID Sid,
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitializeSidEx(
    _Out_writes_bytes_(SECURITY_SID_SIZE(SubAuthorityCount)) PSID Sid,
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    ...
    );
#endif

NTSYSAPI
PSID_IDENTIFIER_AUTHORITY
NTAPI
RtlIdentifierAuthoritySid(
    _In_ PSID Sid
    );

NTSYSAPI
PULONG
NTAPI
RtlSubAuthoritySid(
    _In_ PSID Sid,
    _In_ ULONG SubAuthority
    );

NTSYSAPI
PUCHAR
NTAPI
RtlSubAuthorityCountSid(
    _In_ PSID Sid
    );

NTSYSAPI
ULONG
NTAPI
RtlLengthSid(
    _In_ PSID Sid
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCopySid(
    _In_ ULONG DestinationSidLength,
    _Out_writes_bytes_(DestinationSidLength) PSID DestinationSid,
    _In_ PSID SourceSid
    );

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlCopySidAndAttributesArray(
    _In_ ULONG Count,
    _In_ PSID_AND_ATTRIBUTES Src,
    _In_ ULONG SidAreaSize,
    _In_ PSID_AND_ATTRIBUTES Dest,
    _In_ PSID SidArea,
    _Out_ PSID *RemainingSidArea,
    _Out_ PULONG RemainingSidAreaSize
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateServiceSid(
    _In_ PUNICODE_STRING ServiceName,
    _Out_writes_bytes_opt_(*ServiceSidLength) PSID ServiceSid,
    _Inout_ PULONG ServiceSidLength
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSidDominates(
    _In_ PSID Sid1,
    _In_ PSID Sid2,
    _Out_ PBOOLEAN Dominates
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WINBLUE)

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSidDominatesForTrust(
    _In_ PSID Sid1,
    _In_ PSID Sid2,
    _Out_ PBOOLEAN DominatesTrust // TokenProcessTrustLevel
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSidEqualLevel(
    _In_ PSID Sid1,
    _In_ PSID Sid2,
    _Out_ PBOOLEAN EqualLevel
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSidIsHigherLevel(
    _In_ PSID Sid1,
    _In_ PSID Sid2,
    _Out_ PBOOLEAN HigherLevel
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateVirtualAccountSid(
    _In_ PUNICODE_STRING Name,
    _In_ ULONG BaseSubAuthority,
    _Out_writes_bytes_(*SidLength) PSID Sid,
    _Inout_ PULONG SidLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
NTSTATUS
NTAPI
RtlReplaceSidInSd(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PSID OldSid,
    _In_ PSID NewSid,
    _Out_ ULONG *NumChanges
    );
#endif

#define MAX_UNICODE_STACK_BUFFER_LENGTH 256

NTSYSAPI
NTSTATUS
NTAPI
RtlLengthSidAsUnicodeString(
    _In_ PSID Sid,
    _Out_ PULONG StringLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlConvertSidToUnicodeString(
    _Inout_ PUNICODE_STRING UnicodeString,
    _In_ PSID Sid,
    _In_ BOOLEAN AllocateDestinationString
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSidHashInitialize(
    _In_reads_(SidCount) PSID_AND_ATTRIBUTES SidAttr,
    _In_ ULONG SidCount,
    _Out_ PSID_AND_ATTRIBUTES_HASH SidAttrHash
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
PSID_AND_ATTRIBUTES
NTAPI
RtlSidHashLookup(
    _In_ PSID_AND_ATTRIBUTES_HASH SidAttrHash,
    _In_ PSID Sid
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsElevatedRid(
    _In_ PSID_AND_ATTRIBUTES SidAttr
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDeriveCapabilitySidsFromName(
    _Inout_ PUNICODE_STRING UnicodeString,
    _Out_ PSID CapabilityGroupSid,
    _Out_ PSID CapabilitySid
    );
#endif

// Security Descriptors

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateSecurityDescriptor(
    _Out_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Revision
    );

_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlValidSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

NTSYSAPI
ULONG
NTAPI
RtlLengthSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlValidRelativeSecurityDescriptor(
    _In_reads_bytes_(SecurityDescriptorLength) PSECURITY_DESCRIPTOR SecurityDescriptorInput,
    _In_ ULONG SecurityDescriptorLength,
    _In_ SECURITY_INFORMATION RequiredInformation
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetControlSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PSECURITY_DESCRIPTOR_CONTROL Control,
    _Out_ PULONG Revision
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetControlSecurityDescriptor(
     _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
     _In_ SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,
     _In_ SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet
     );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetAttributesSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ SECURITY_DESCRIPTOR_CONTROL Control,
    _Out_ PULONG Revision
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlGetSecurityDescriptorRMControl(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PUCHAR RMControl
    );

NTSYSAPI
VOID
NTAPI
RtlSetSecurityDescriptorRMControl(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PUCHAR RMControl
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetDaclSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ BOOLEAN DaclPresent,
    _In_opt_ PACL Dacl,
    _In_opt_ BOOLEAN DaclDefaulted
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetDaclSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PBOOLEAN DaclPresent,
    _Outptr_result_maybenull_ PACL *Dacl,
    _Out_ PBOOLEAN DaclDefaulted
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetSaclSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ BOOLEAN SaclPresent,
    _In_opt_ PACL Sacl,
    _In_opt_ BOOLEAN SaclDefaulted
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetSaclSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PBOOLEAN SaclPresent,
    _Out_ PACL *Sacl,
    _Out_ PBOOLEAN SaclDefaulted
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetOwnerSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID Owner,
    _In_ BOOLEAN OwnerDefaulted
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetOwnerSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_result_maybenull_ PSID *Owner,
    _Out_ PBOOLEAN OwnerDefaulted
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetGroupSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID Group,
    _In_ BOOLEAN GroupDefaulted
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetGroupSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_result_maybenull_ PSID *Group,
    _Out_ PBOOLEAN GroupDefaulted
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlMakeSelfRelativeSD(
    _In_ PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
    _Out_writes_bytes_(*BufferLength) PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Inout_ PULONG BufferLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAbsoluteToSelfRelativeSD(
    _In_ PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
    _Out_writes_bytes_to_opt_(*BufferLength, *BufferLength) PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Inout_ PULONG BufferLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSelfRelativeToAbsoluteSD(
    _In_ PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Out_writes_bytes_to_opt_(*AbsoluteSecurityDescriptorSize, *AbsoluteSecurityDescriptorSize) PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
    _Inout_ PULONG AbsoluteSecurityDescriptorSize,
    _Out_writes_bytes_to_opt_(*DaclSize, *DaclSize) PACL Dacl,
    _Inout_ PULONG DaclSize,
    _Out_writes_bytes_to_opt_(*SaclSize, *SaclSize) PACL Sacl,
    _Inout_ PULONG SaclSize,
    _Out_writes_bytes_to_opt_(*OwnerSize, *OwnerSize) PSID Owner,
    _Inout_ PULONG OwnerSize,
    _Out_writes_bytes_to_opt_(*PrimaryGroupSize, *PrimaryGroupSize) PSID PrimaryGroup,
    _Inout_ PULONG PrimaryGroupSize
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSelfRelativeToAbsoluteSD2(
    _Inout_ PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,
    _Inout_ PULONG pBufferSize
    );

// Access masks

NTSYSAPI
BOOLEAN
NTAPI
RtlAreAllAccessesGranted(
    _In_ ACCESS_MASK GrantedAccess,
    _In_ ACCESS_MASK DesiredAccess
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlAreAnyAccessesGranted(
    _In_ ACCESS_MASK GrantedAccess,
    _In_ ACCESS_MASK DesiredAccess
    );

NTSYSAPI
VOID
NTAPI
RtlMapGenericMask(
    _Inout_ PACCESS_MASK AccessMask,
    _In_ PGENERIC_MAPPING GenericMapping
    );

// ACLs

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateAcl(
    _Out_writes_bytes_(AclLength) PACL Acl,
    _In_ ULONG AclLength,
    _In_ ULONG AclRevision
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlValidAcl(
    _In_ PACL Acl
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryInformationAcl(
    _In_ PACL Acl,
    _Out_writes_bytes_(AclInformationLength) PVOID AclInformation,
    _In_ ULONG AclInformationLength,
    _In_ ACL_INFORMATION_CLASS AclInformationClass
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetInformationAcl(
    _Inout_ PACL Acl,
    _In_reads_bytes_(AclInformationLength) PVOID AclInformation,
    _In_ ULONG AclInformationLength,
    _In_ ACL_INFORMATION_CLASS AclInformationClass
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG StartingAceIndex,
    _In_reads_bytes_(AceListLength) PVOID AceList,
    _In_ ULONG AceListLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceIndex
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlGetAce(
    _In_ PACL Acl,
    _In_ ULONG AceIndex,
    _Outptr_ PVOID *Ace
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlFirstFreeAce(
    _In_ PACL Acl,
    _Out_ PVOID *FirstFree
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
PVOID
NTAPI
RtlFindAceByType(
    _In_ PACL pAcl,
    _In_ UCHAR AceType,
    _Out_opt_ PULONG pIndex
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
BOOLEAN
NTAPI
RtlOwnerAcesPresent(
    _In_ PACL pAcl
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessAllowedAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessAllowedAceEx(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessDeniedAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessDeniedAceEx(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAuditAccessAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid,
    _In_ BOOLEAN AuditSuccess,
    _In_ BOOLEAN AuditFailure
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAuditAccessAceEx(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid,
    _In_ BOOLEAN AuditSuccess,
    _In_ BOOLEAN AuditFailure
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessAllowedObjectAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_opt_ PGUID ObjectTypeGuid,
    _In_opt_ PGUID InheritedObjectTypeGuid,
    _In_ PSID Sid
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessDeniedObjectAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_opt_ PGUID ObjectTypeGuid,
    _In_opt_ PGUID InheritedObjectTypeGuid,
    _In_ PSID Sid
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAuditAccessObjectAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_opt_ PGUID ObjectTypeGuid,
    _In_opt_ PGUID InheritedObjectTypeGuid,
    _In_ PSID Sid,
    _In_ BOOLEAN AuditSuccess,
    _In_ BOOLEAN AuditFailure
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddCompoundAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ UCHAR AceType,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID ServerSid,
    _In_ PSID ClientSid
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlAddMandatoryAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ PSID Sid,
    _In_ UCHAR AceType,
    _In_ ACCESS_MASK AccessMask
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddResourceAttributeAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ULONG AccessMask,
    _In_ PSID Sid,
    _In_ PCLAIM_SECURITY_ATTRIBUTES_INFORMATION AttributeInfo,
    _Out_ PULONG ReturnLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddScopedPolicyIDAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ULONG AccessMask,
    _In_ PSID Sid
    );
#endif

// Named pipes

NTSYSAPI
NTSTATUS
NTAPI
RtlDefaultNpAcl(
    _Out_ PACL *Acl
    );

// Security objects

NTSYSAPI
NTSTATUS
NTAPI
RtlNewSecurityObject(
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *NewDescriptor,
    _In_ BOOLEAN IsDirectoryObject,
    _In_opt_ HANDLE Token,
    _In_ PGENERIC_MAPPING GenericMapping
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlNewSecurityObjectEx(
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *NewDescriptor,
    _In_opt_ GUID *ObjectType,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ ULONG AutoInheritFlags, // SEF_*
    _In_opt_ HANDLE Token,
    _In_ PGENERIC_MAPPING GenericMapping
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlNewSecurityObjectWithMultipleInheritance(
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *NewDescriptor,
    _In_opt_ GUID **ObjectType,
    _In_ ULONG GuidCount,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ ULONG AutoInheritFlags, // SEF_*
    _In_opt_ HANDLE Token,
    _In_ PGENERIC_MAPPING GenericMapping
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteSecurityObject(
    _Inout_ PSECURITY_DESCRIPTOR *ObjectDescriptor
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlQuerySecurityObject(
     _In_ PSECURITY_DESCRIPTOR ObjectDescriptor,
     _In_ SECURITY_INFORMATION SecurityInformation,
     _Out_opt_ PSECURITY_DESCRIPTOR ResultantDescriptor,
     _In_ ULONG DescriptorLength,
     _Out_ PULONG ReturnLength
     );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetSecurityObject(
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR ModificationDescriptor,
    _Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_opt_ HANDLE Token
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetSecurityObjectEx(
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR ModificationDescriptor,
    _Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
    _In_ ULONG AutoInheritFlags, // SEF_*
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_opt_ HANDLE Token
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlConvertToAutoInheritSecurityObject(
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_ PSECURITY_DESCRIPTOR CurrentSecurityDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *NewSecurityDescriptor,
    _In_opt_ GUID *ObjectType,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ PGENERIC_MAPPING GenericMapping
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlNewInstanceSecurityObject(
    _In_ BOOLEAN ParentDescriptorChanged,
    _In_ BOOLEAN CreatorDescriptorChanged,
    _In_ PLUID OldClientTokenModifiedId,
    _Out_ PLUID NewClientTokenModifiedId,
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *NewDescriptor,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ HANDLE Token,
    _In_ PGENERIC_MAPPING GenericMapping
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCopySecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR InputSecurityDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *OutputSecurityDescriptor
    );

// Misc. security

NTSYSAPI
VOID
NTAPI
RtlRunEncodeUnicodeString(
    _Inout_ PUCHAR Seed,
    _In_ PUNICODE_STRING String
    );

NTSYSAPI
VOID
NTAPI
RtlRunDecodeUnicodeString(
    _In_ UCHAR Seed,
    _In_ PUNICODE_STRING String
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlImpersonateSelf(
    _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlImpersonateSelfEx(
    _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
    _In_opt_ ACCESS_MASK AdditionalAccess,
    _Out_opt_ PHANDLE ThreadToken
    );
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlAdjustPrivilege(
    _In_ ULONG Privilege,
    _In_ BOOLEAN Enable,
    _In_ BOOLEAN Client,
    _Out_ PBOOLEAN WasEnabled
    );

#define RTL_ACQUIRE_PRIVILEGE_REVERT 0x00000001
#define RTL_ACQUIRE_PRIVILEGE_PROCESS 0x00000002

NTSYSAPI
NTSTATUS
NTAPI
RtlAcquirePrivilege(
    _In_ PULONG Privilege,
    _In_ ULONG NumPriv,
    _In_ ULONG Flags,
    _Out_ PVOID *ReturnedState
    );

NTSYSAPI
VOID
NTAPI
RtlReleasePrivilege(
    _In_ PVOID StatePointer
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlRemovePrivileges(
    _In_ HANDLE TokenHandle,
    _In_ PULONG PrivilegesToKeep,
    _In_ ULONG PrivilegeCount
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlIsUntrustedObject(
    _In_opt_ HANDLE Handle,
    _In_opt_ PVOID Object,
    _Out_ PBOOLEAN IsUntrustedObject
    );

NTSYSAPI
ULONG
NTAPI
RtlQueryValidationRunlevel(
    _In_opt_ PUNICODE_STRING ComponentName
    );

#endif

// Private namespaces

#if (NTDDI_VERSION >= NTDDI_VISTA)

// begin_private

NTSYSAPI
HANDLE
NTAPI
RtlCreateBoundaryDescriptor(
    _In_ PUNICODE_STRING Name,
    _In_ ULONG Flags
    );

NTSYSAPI
VOID
NTAPI
RtlDeleteBoundaryDescriptor(
    _In_ HANDLE BoundaryDescriptor
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlAddSIDToBoundaryDescriptor(
    _Inout_ PHANDLE BoundaryDescriptor,
    _In_ PSID RequiredSid
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlAddIntegrityLabelToBoundaryDescriptor(
    _Inout_ PHANDLE BoundaryDescriptor,
    _In_ PSID IntegrityLabel
    );
#endif

// end_private

#endif

// Version

NTSYSAPI
NTSTATUS
NTAPI
RtlGetVersion(
    _Out_ PRTL_OSVERSIONINFOEXW VersionInformation // PRTL_OSVERSIONINFOW
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlVerifyVersionInfo(
    _In_ PRTL_OSVERSIONINFOEXW VersionInformation, // PRTL_OSVERSIONINFOW
    _In_ ULONG TypeMask,
    _In_ ULONGLONG ConditionMask
    );

// rev
NTSYSAPI
VOID
NTAPI
RtlGetNtVersionNumbers(
    _Out_opt_ PULONG NtMajorVersion,
    _Out_opt_ PULONG NtMinorVersion,
    _Out_opt_ PULONG NtBuildNumber
    );

// System information

// rev
NTSYSAPI
ULONG
NTAPI
RtlGetNtGlobalFlags(
    VOID
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlGetNtProductType(
    _Out_ PNT_PRODUCT_TYPE NtProductType
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)
// private
NTSYSAPI
ULONG
NTAPI
RtlGetSuiteMask(
    VOID
    );
#endif

// Thread pool (old)

NTSYSAPI
NTSTATUS
NTAPI
RtlRegisterWait(
    _Out_ PHANDLE WaitHandle,
    _In_ HANDLE Handle,
    _In_ WAITORTIMERCALLBACKFUNC Function,
    _In_ PVOID Context,
    _In_ ULONG Milliseconds,
    _In_ ULONG Flags
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeregisterWait(
    _In_ HANDLE WaitHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeregisterWaitEx(
    _In_ HANDLE WaitHandle,
    _In_ HANDLE Event
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlQueueWorkItem(
    _In_ WORKERCALLBACKFUNC Function,
    _In_ PVOID Context,
    _In_ ULONG Flags
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetIoCompletionCallback(
    _In_ HANDLE FileHandle,
    _In_ APC_CALLBACK_FUNCTION CompletionProc,
    _In_ ULONG Flags
    );

typedef NTSTATUS (NTAPI *PRTL_START_POOL_THREAD)(
    _In_ PTHREAD_START_ROUTINE Function,
    _In_ PVOID Parameter,
    _Out_ PHANDLE ThreadHandle
    );

typedef NTSTATUS (NTAPI *PRTL_EXIT_POOL_THREAD)(
    _In_ NTSTATUS ExitStatus
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetThreadPoolStartFunc(
    _In_ PRTL_START_POOL_THREAD StartPoolThread,
    _In_ PRTL_EXIT_POOL_THREAD ExitPoolThread
    );

NTSYSAPI
VOID
NTAPI
RtlUserThreadStart(
    _In_ PTHREAD_START_ROUTINE Function,
    _In_ PVOID Parameter
    );

NTSYSAPI
VOID
NTAPI
LdrInitializeThunk(
    _In_ PCONTEXT ContextRecord,
    _In_ PVOID Parameter
    );

// Timer support

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateTimerQueue(
    _Out_ PHANDLE TimerQueueHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateTimer(
    _In_ HANDLE TimerQueueHandle,
    _Out_ PHANDLE Handle,
    _In_ WAITORTIMERCALLBACKFUNC Function,
    _In_opt_ PVOID Context,
    _In_ ULONG DueTime,
    _In_ ULONG Period,
    _In_ ULONG Flags
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlUpdateTimer(
    _In_ HANDLE TimerQueueHandle,
    _In_ HANDLE TimerHandle,
    _In_ ULONG DueTime,
    _In_ ULONG Period
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteTimer(
    _In_ HANDLE TimerQueueHandle,
    _In_ HANDLE TimerToCancel,
    _In_opt_ HANDLE Event
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteTimerQueue(
    _In_ HANDLE TimerQueueHandle
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteTimerQueueEx(
    _In_ HANDLE TimerQueueHandle,
    _In_ HANDLE Event
    );

// Registry access

NTSYSAPI
NTSTATUS
NTAPI
RtlFormatCurrentUserKeyPath(
    _Out_ PUNICODE_STRING CurrentUserKeyPath
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlOpenCurrentUser(
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE CurrentUserKey
    );

#define RTL_REGISTRY_ABSOLUTE 0
#define RTL_REGISTRY_SERVICES 1 // \Registry\Machine\System\CurrentControlSet\Services
#define RTL_REGISTRY_CONTROL 2 // \Registry\Machine\System\CurrentControlSet\Control
#define RTL_REGISTRY_WINDOWS_NT 3 // \Registry\Machine\Software\Microsoft\Windows NT\CurrentVersion
#define RTL_REGISTRY_DEVICEMAP 4 // \Registry\Machine\Hardware\DeviceMap
#define RTL_REGISTRY_USER 5 // \Registry\User\CurrentUser
#define RTL_REGISTRY_MAXIMUM 6
#define RTL_REGISTRY_HANDLE 0x40000000
#define RTL_REGISTRY_OPTIONAL 0x80000000

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateRegistryKey(
    _In_ ULONG RelativeTo,
    _In_ PWSTR Path
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCheckRegistryKey(
    _In_ ULONG RelativeTo,
    _In_ PWSTR Path
    );

typedef NTSTATUS (NTAPI *PRTL_QUERY_REGISTRY_ROUTINE)(
    _In_ PWSTR ValueName,
    _In_ ULONG ValueType,
    _In_ PVOID ValueData,
    _In_ ULONG ValueLength,
    _In_ PVOID Context,
    _In_ PVOID EntryContext
    );

typedef struct _RTL_QUERY_REGISTRY_TABLE
{
    PRTL_QUERY_REGISTRY_ROUTINE QueryRoutine;
    ULONG Flags;
    PWSTR Name;
    PVOID EntryContext;
    ULONG DefaultType;
    PVOID DefaultData;
    ULONG DefaultLength;
} RTL_QUERY_REGISTRY_TABLE, *PRTL_QUERY_REGISTRY_TABLE;

#define RTL_QUERY_REGISTRY_SUBKEY 0x00000001
#define RTL_QUERY_REGISTRY_TOPKEY 0x00000002
#define RTL_QUERY_REGISTRY_REQUIRED 0x00000004
#define RTL_QUERY_REGISTRY_NOVALUE 0x00000008
#define RTL_QUERY_REGISTRY_NOEXPAND 0x00000010
#define RTL_QUERY_REGISTRY_DIRECT 0x00000020
#define RTL_QUERY_REGISTRY_DELETE 0x00000040

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryRegistryValues(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_ PRTL_QUERY_REGISTRY_TABLE QueryTable,
    _In_ PVOID Context,
    _In_opt_ PVOID Environment
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryRegistryValuesEx(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_ PRTL_QUERY_REGISTRY_TABLE QueryTable,
    _In_ PVOID Context,
    _In_opt_ PVOID Environment
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlWriteRegistryValue(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_ PCWSTR ValueName,
    _In_ ULONG ValueType,
    _In_ PVOID ValueData,
    _In_ ULONG ValueLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteRegistryValue(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_ PCWSTR ValueName
    );

// Thread profiling

#if (NTDDI_VERSION >= NTDDI_WIN7)

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlEnableThreadProfiling(
    _In_ HANDLE ThreadHandle,
    _In_ ULONG Flags,
    _In_ ULONG64 HardwareCounters,
    _Out_ PVOID *PerformanceDataHandle
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDisableThreadProfiling(
    _In_ PVOID PerformanceDataHandle
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryThreadProfiling(
    _In_ HANDLE ThreadHandle,
    _Out_ PBOOLEAN Enabled
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlReadThreadProfilingData(
    _In_ HANDLE PerformanceDataHandle,
    _In_ ULONG Flags,
    _Out_ PPERFORMANCE_DATA PerformanceData
    );

#endif

// WOW64

NTSYSAPI
NTSTATUS
NTAPI
RtlGetNativeSystemInformation(
    _In_ ULONG SystemInformationClass,
    _In_ PVOID NativeSystemInformation,
    _In_ ULONG InformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlQueueApcWow64Thread(
    _In_ HANDLE ThreadHandle,
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlWow64EnableFsRedirection(
    _In_ BOOLEAN Wow64FsEnableRedirection
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlWow64EnableFsRedirectionEx(
    _In_ PVOID Wow64FsEnableRedirection,
    _Out_ PVOID *OldFsRedirectionLevel
    );

// Misc.

NTSYSAPI
ULONG32
NTAPI
RtlComputeCrc32(
    _In_ ULONG32 PartialCrc,
    _In_ PVOID Buffer,
    _In_ ULONG Length
    );

NTSYSAPI
PVOID
NTAPI
RtlEncodePointer(
    _In_ PVOID Ptr
    );

NTSYSAPI
PVOID
NTAPI
RtlDecodePointer(
    _In_ PVOID Ptr
    );

NTSYSAPI
PVOID
NTAPI
RtlEncodeSystemPointer(
    _In_ PVOID Ptr
    );

NTSYSAPI
PVOID
NTAPI
RtlDecodeSystemPointer(
    _In_ PVOID Ptr
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlEncodeRemotePointer(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID Pointer,
    _Out_ PVOID *EncodedPointer
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDecodeRemotePointer(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID Pointer,
    _Out_ PVOID *DecodedPointer
    );
#endif

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsProcessorFeaturePresent(
    _In_ ULONG ProcessorFeature
    );

// rev
NTSYSAPI
ULONG
NTAPI
RtlGetCurrentProcessorNumber(
    VOID
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)

// rev
NTSYSAPI
VOID
NTAPI
RtlGetCurrentProcessorNumberEx(
    _Out_ PPROCESSOR_NUMBER ProcessorNumber
    );

#endif

// Stack support

NTSYSAPI
VOID
NTAPI
RtlPushFrame(
    _In_ PTEB_ACTIVE_FRAME Frame
    );

NTSYSAPI
VOID
NTAPI
RtlPopFrame(
    _In_ PTEB_ACTIVE_FRAME Frame
    );

NTSYSAPI
PTEB_ACTIVE_FRAME
NTAPI
RtlGetFrame(
    VOID
    );

#define RTL_WALK_USER_MODE_STACK 0x00000001
#define RTL_WALK_VALID_FLAGS 0x00000001
#define RTL_STACK_WALKING_MODE_FRAMES_TO_SKIP_SHIFT 0x00000008

// private
NTSYSAPI
ULONG
NTAPI
RtlWalkFrameChain(
    _Out_writes_(Count - (Flags >> RTL_STACK_WALKING_MODE_FRAMES_TO_SKIP_SHIFT)) PVOID *Callers,
    _In_ ULONG Count,
    _In_ ULONG Flags
    );

// rev
NTSYSAPI
VOID
NTAPI
RtlGetCallersAddress( // Use the intrinsic _ReturnAddress instead.
    _Out_ PVOID *CallersAddress,
    _Out_ PVOID *CallersCaller
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)

NTSYSAPI
ULONG64
NTAPI
RtlGetEnabledExtendedFeatures(
    _In_ ULONG64 FeatureMask
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)

// msdn
NTSYSAPI
ULONG64
NTAPI
RtlGetEnabledExtendedAndSupervisorFeatures(
    _In_ ULONG64 FeatureMask
    );

// msdn
_Ret_maybenull_
_Success_(return != NULL)
NTSYSAPI
PVOID
NTAPI
RtlLocateSupervisorFeature(
    _In_ PXSAVE_AREA_HEADER XStateHeader,
    _In_range_(XSTATE_AVX, MAXIMUM_XSTATE_FEATURES - 1) ULONG FeatureId,
    _Out_opt_ PULONG Length
    );

#endif

// private
typedef union _RTL_ELEVATION_FLAGS
{
    ULONG Flags;
    struct
    {
        ULONG ElevationEnabled : 1;
        ULONG VirtualizationEnabled : 1;
        ULONG InstallerDetectEnabled : 1;
        ULONG ReservedBits : 29;
    };
} RTL_ELEVATION_FLAGS, *PRTL_ELEVATION_FLAGS;

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryElevationFlags(
    _Out_ PRTL_ELEVATION_FLAGS Flags
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlRegisterThreadWithCsrss(
    VOID
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLockCurrentThread(
    VOID
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockCurrentThread(
    VOID
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLockModuleSection(
    _In_ PVOID Address
    );

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockModuleSection(
    _In_ PVOID Address
    );

#endif

// begin_msdn:"Winternl"

#define RTL_UNLOAD_EVENT_TRACE_NUMBER 64

// private
typedef struct _RTL_UNLOAD_EVENT_TRACE
{
    PVOID BaseAddress;
    SIZE_T SizeOfImage;
    ULONG Sequence;
    ULONG TimeDateStamp;
    ULONG CheckSum;
    WCHAR ImageName[32];
    ULONG Version[2];
} RTL_UNLOAD_EVENT_TRACE, *PRTL_UNLOAD_EVENT_TRACE;

typedef struct _RTL_UNLOAD_EVENT_TRACE32 
{
    ULONG BaseAddress;
    ULONG SizeOfImage;
    ULONG Sequence;
    ULONG TimeDateStamp;
    ULONG CheckSum;
    WCHAR ImageName[32];
    ULONG Version[2];
} RTL_UNLOAD_EVENT_TRACE32, *PRTL_UNLOAD_EVENT_TRACE32;

NTSYSAPI
PRTL_UNLOAD_EVENT_TRACE
NTAPI
RtlGetUnloadEventTrace(
    VOID
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
VOID
NTAPI
RtlGetUnloadEventTraceEx(
    _Out_ PULONG *ElementSize,
    _Out_ PULONG *ElementCount,
    _Out_ PVOID *EventTrace // works across all processes
    );
#endif

// end_msdn

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
LOGICAL
NTAPI
RtlQueryPerformanceCounter(
    _Out_ PLARGE_INTEGER PerformanceCounter
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
LOGICAL
NTAPI
RtlQueryPerformanceFrequency(
    _Out_ PLARGE_INTEGER PerformanceFrequency
    );
#endif

// Image Mitigation

// rev
typedef enum _IMAGE_MITIGATION_POLICY
{
    ImageDepPolicy, // RTL_IMAGE_MITIGATION_DEP_POLICY
    ImageAslrPolicy, // RTL_IMAGE_MITIGATION_ASLR_POLICY
    ImageDynamicCodePolicy, // RTL_IMAGE_MITIGATION_DYNAMIC_CODE_POLICY
    ImageStrictHandleCheckPolicy, // RTL_IMAGE_MITIGATION_STRICT_HANDLE_CHECK_POLICY
    ImageSystemCallDisablePolicy, // RTL_IMAGE_MITIGATION_SYSTEM_CALL_DISABLE_POLICY
    ImageMitigationOptionsMask,
    ImageExtensionPointDisablePolicy, // RTL_IMAGE_MITIGATION_EXTENSION_POINT_DISABLE_POLICY
    ImageControlFlowGuardPolicy, // RTL_IMAGE_MITIGATION_CONTROL_FLOW_GUARD_POLICY
    ImageSignaturePolicy, // RTL_IMAGE_MITIGATION_BINARY_SIGNATURE_POLICY
    ImageFontDisablePolicy, // RTL_IMAGE_MITIGATION_FONT_DISABLE_POLICY
    ImageImageLoadPolicy, // RTL_IMAGE_MITIGATION_IMAGE_LOAD_POLICY
    ImagePayloadRestrictionPolicy, // RTL_IMAGE_MITIGATION_PAYLOAD_RESTRICTION_POLICY
    ImageChildProcessPolicy, // RTL_IMAGE_MITIGATION_CHILD_PROCESS_POLICY
    ImageSehopPolicy, // RTL_IMAGE_MITIGATION_SEHOP_POLICY
    ImageHeapPolicy, // RTL_IMAGE_MITIGATION_HEAP_POLICY
    MaxImageMitigationPolicy
} IMAGE_MITIGATION_POLICY;

// rev
typedef union _RTL_IMAGE_MITIGATION_POLICY
{
    struct
    {
        ULONG64 AuditState : 2;
        ULONG64 AuditFlag : 1;
        ULONG64 EnableAdditionalAuditingOption : 1;
        ULONG64 Reserved : 60;
    };
    struct
    {
        ULONG64 PolicyState : 2;
        ULONG64 AlwaysInherit : 1;
        ULONG64 EnableAdditionalPolicyOption : 1;
        ULONG64 AuditReserved : 60;
    };
} RTL_IMAGE_MITIGATION_POLICY, *PRTL_IMAGE_MITIGATION_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_DEP_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY Dep;
} RTL_IMAGE_MITIGATION_DEP_POLICY, *PRTL_IMAGE_MITIGATION_DEP_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_ASLR_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY ForceRelocateImages;
    RTL_IMAGE_MITIGATION_POLICY BottomUpRandomization;
    RTL_IMAGE_MITIGATION_POLICY HighEntropyRandomization;
} RTL_IMAGE_MITIGATION_ASLR_POLICY, *PRTL_IMAGE_MITIGATION_ASLR_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_DYNAMIC_CODE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY BlockDynamicCode;
} RTL_IMAGE_MITIGATION_DYNAMIC_CODE_POLICY, *PRTL_IMAGE_MITIGATION_DYNAMIC_CODE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_STRICT_HANDLE_CHECK_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY StrictHandleChecks;
} RTL_IMAGE_MITIGATION_STRICT_HANDLE_CHECK_POLICY, *PRTL_IMAGE_MITIGATION_STRICT_HANDLE_CHECK_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_SYSTEM_CALL_DISABLE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY BlockWin32kSystemCalls;
} RTL_IMAGE_MITIGATION_SYSTEM_CALL_DISABLE_POLICY, *PRTL_IMAGE_MITIGATION_SYSTEM_CALL_DISABLE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_EXTENSION_POINT_DISABLE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY DisableExtensionPoints;
} RTL_IMAGE_MITIGATION_EXTENSION_POINT_DISABLE_POLICY, *PRTL_IMAGE_MITIGATION_EXTENSION_POINT_DISABLE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_CONTROL_FLOW_GUARD_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY ControlFlowGuard;
    RTL_IMAGE_MITIGATION_POLICY StrictControlFlowGuard;
} RTL_IMAGE_MITIGATION_CONTROL_FLOW_GUARD_POLICY, *PRTL_IMAGE_MITIGATION_CONTROL_FLOW_GUARD_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_BINARY_SIGNATURE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY BlockNonMicrosoftSignedBinaries;
    RTL_IMAGE_MITIGATION_POLICY EnforceSigningOnModuleDependencies;
} RTL_IMAGE_MITIGATION_BINARY_SIGNATURE_POLICY, *PRTL_IMAGE_MITIGATION_BINARY_SIGNATURE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_FONT_DISABLE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY DisableNonSystemFonts;
} RTL_IMAGE_MITIGATION_FONT_DISABLE_POLICY, *PRTL_IMAGE_MITIGATION_FONT_DISABLE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_IMAGE_LOAD_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY BlockRemoteImageLoads;
    RTL_IMAGE_MITIGATION_POLICY BlockLowLabelImageLoads;
    RTL_IMAGE_MITIGATION_POLICY PreferSystem32;
} RTL_IMAGE_MITIGATION_IMAGE_LOAD_POLICY, *PRTL_IMAGE_MITIGATION_IMAGE_LOAD_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_PAYLOAD_RESTRICTION_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY EnableExportAddressFilter;
    RTL_IMAGE_MITIGATION_POLICY EnableExportAddressFilterPlus;
    RTL_IMAGE_MITIGATION_POLICY EnableImportAddressFilter;
    RTL_IMAGE_MITIGATION_POLICY EnableRopStackPivot;
    RTL_IMAGE_MITIGATION_POLICY EnableRopCallerCheck;
    RTL_IMAGE_MITIGATION_POLICY EnableRopSimExec;
    WCHAR EafPlusModuleList[512]; // 19H1
} RTL_IMAGE_MITIGATION_PAYLOAD_RESTRICTION_POLICY, *PRTL_IMAGE_MITIGATION_PAYLOAD_RESTRICTION_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_CHILD_PROCESS_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY DisallowChildProcessCreation;
} RTL_IMAGE_MITIGATION_CHILD_PROCESS_POLICY, *PRTL_IMAGE_MITIGATION_CHILD_PROCESS_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_SEHOP_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY Sehop;
} RTL_IMAGE_MITIGATION_SEHOP_POLICY, *PRTL_IMAGE_MITIGATION_SEHOP_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_HEAP_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY TerminateOnHeapErrors;
} RTL_IMAGE_MITIGATION_HEAP_POLICY, *PRTL_IMAGE_MITIGATION_HEAP_POLICY;

typedef enum _RTL_IMAGE_MITIGATION_OPTION_STATE
{
    RtlMitigationOptionStateNotConfigured,
    RtlMitigationOptionStateOn,
    RtlMitigationOptionStateOff
} RTL_IMAGE_MITIGATION_OPTION_STATE;

// rev from PROCESS_MITIGATION_FLAGS
#define RTL_IMAGE_MITIGATION_FLAG_RESET 0x1
#define RTL_IMAGE_MITIGATION_FLAG_REMOVE 0x2
#define RTL_IMAGE_MITIGATION_FLAG_OSDEFAULT 0x4
#define RTL_IMAGE_MITIGATION_FLAG_AUDIT 0x8

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryImageMitigationPolicy(
    _In_opt_ PWSTR ImagePath, // NULL for system-wide defaults
    _In_ IMAGE_MITIGATION_POLICY Policy,
    _In_ ULONG Flags,
    _Inout_ PVOID Buffer,
    _In_ ULONG BufferSize
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetImageMitigationPolicy(
    _In_opt_ PWSTR ImagePath, // NULL for system-wide defaults
    _In_ IMAGE_MITIGATION_POLICY Policy,
    _In_ ULONG Flags,
    _Inout_ PVOID Buffer,
    _In_ ULONG BufferSize
    );

#endif

// session 

// rev
NTSYSAPI
ULONG
NTAPI
RtlGetCurrentServiceSessionId(
    VOID
    );

// private
NTSYSAPI
ULONG
NTAPI
RtlGetActiveConsoleId(
    VOID
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// private
NTSYSAPI
ULONGLONG
NTAPI
RtlGetConsoleSessionForegroundProcessId(
    VOID
    );
#endif

// Appcontainer

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetTokenNamedObjectPath(
    _In_ HANDLE Token, 
    _In_opt_ PSID Sid, 
    _Out_ PUNICODE_STRING ObjectPath // RtlFreeUnicodeString
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetAppContainerNamedObjectPath(
    _In_opt_ HANDLE Token,
    _In_opt_ PSID AppContainerSid,
    _In_ BOOLEAN RelativePath,
    _Out_ PUNICODE_STRING ObjectPath // RtlFreeUnicodeString
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetAppContainerParent(
    _In_ PSID AppContainerSid, 
    _Out_ PSID* AppContainerSidParent // RtlFreeSid
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckSandboxedToken(
    _In_opt_ HANDLE TokenHandle,
    _Out_ PBOOLEAN IsSandboxed
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckTokenCapability(
    _In_opt_ HANDLE TokenHandle,
    _In_ PSID CapabilitySidToCheck,
    _Out_ PBOOLEAN HasCapability
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCapabilityCheck(
    _In_opt_ HANDLE TokenHandle,
    _In_ PUNICODE_STRING CapabilityName,
    _Out_ PBOOLEAN HasCapability
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckTokenMembership(
    _In_opt_ HANDLE TokenHandle,
    _In_ PSID SidToCheck,
    _Out_ PBOOLEAN IsMember
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckTokenMembershipEx(
    _In_opt_ HANDLE TokenHandle,
    _In_ PSID SidToCheck,
    _In_ ULONG Flags, // CTMF_VALID_FLAGS
    _Out_ PBOOLEAN IsMember
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryTokenHostIdAsUlong64(
    _In_ HANDLE TokenHandle,
    _Out_ PULONG64 HostId // (WIN://PKGHOSTID)
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsParentOfChildAppContainer(
    _In_ PSID ParentAppContainerSid,
    _In_ PSID ChildAppContainerSid
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCapabilitySid(
    _In_ PSID Sid
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsPackageSid(
    _In_ PSID Sid
    );

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsValidProcessTrustLabelSid(
    _In_ PSID Sid
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlIsStateSeparationEnabled(
    VOID
    );

typedef enum _APPCONTAINER_SID_TYPE
{
    NotAppContainerSidType,
    ChildAppContainerSidType,
    ParentAppContainerSidType,
    InvalidAppContainerSidType,
    MaxAppContainerSidType
} APPCONTAINER_SID_TYPE, *PAPPCONTAINER_SID_TYPE;

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetAppContainerSidType(
    _In_ PSID AppContainerSid,
    _Out_ PAPPCONTAINER_SID_TYPE AppContainerSidType
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlFlsAlloc(
    _In_ PFLS_CALLBACK_FUNCTION Callback,
    _Out_ PULONG FlsIndex
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlFlsFree(
    _In_ ULONG FlsIndex
    );

typedef enum _STATE_LOCATION_TYPE 
{
    LocationTypeRegistry,
    LocationTypeFileSystem,
    LocationTypeMaximum
} STATE_LOCATION_TYPE;

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlGetPersistedStateLocation(
    _In_ PCWSTR SourceID,
    _In_opt_ PCWSTR CustomValue,
    _In_opt_ PCWSTR DefaultPath,
    _In_ STATE_LOCATION_TYPE StateLocationType,
    _Out_writes_bytes_to_opt_(BufferLengthIn, *BufferLengthOut) PWCHAR TargetPath,
    _In_ ULONG BufferLengthIn,
    _Out_opt_ PULONG BufferLengthOut
    );

// msdn
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCloudFilesPlaceholder(
    _In_ ULONG FileAttributes,
    _In_ ULONG ReparseTag
    );

// msdn
NTSYSAPI
BOOLEAN
NTAPI
RtlIsPartialPlaceholder(
    _In_ ULONG FileAttributes,
    _In_ ULONG ReparseTag
    );

// msdn
NTSYSAPI
NTSTATUS
NTAPI
RtlIsPartialPlaceholderFileHandle(
    _In_ HANDLE FileHandle,
    _Out_ PBOOLEAN IsPartialPlaceholder
    );

// msdn
NTSYSAPI
NTSTATUS
NTAPI
RtlIsPartialPlaceholderFileInfo(
    _In_ PVOID InfoBuffer,
    _In_ FILE_INFORMATION_CLASS InfoClass,
    _Out_ PBOOLEAN IsPartialPlaceholder
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)

#undef PHCM_MAX
#define PHCM_APPLICATION_DEFAULT ((CHAR)0)
#define PHCM_DISGUISE_PLACEHOLDERS ((CHAR)1)
#define PHCM_EXPOSE_PLACEHOLDERS ((CHAR)2)
#define PHCM_MAX ((CHAR)2)

#define PHCM_ERROR_INVALID_PARAMETER ((CHAR)-1)
#define PHCM_ERROR_NO_TEB ((CHAR)-2)

NTSYSAPI
CHAR
NTAPI
RtlQueryThreadPlaceholderCompatibilityMode(
    VOID
    );

NTSYSAPI
CHAR
NTAPI
RtlSetThreadPlaceholderCompatibilityMode(
    _In_ CHAR Mode
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)

#undef PHCM_MAX
#define PHCM_DISGUISE_FULL_PLACEHOLDERS ((CHAR)3)
#define PHCM_MAX ((CHAR)3)
#define PHCM_ERROR_NO_PEB ((CHAR)-3)

NTSYSAPI
CHAR
NTAPI
RtlQueryProcessPlaceholderCompatibilityMode(
    VOID
    );

NTSYSAPI
CHAR
NTAPI
RtlSetProcessPlaceholderCompatibilityMode(
    _In_ CHAR Mode
    );

#endif

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsNonEmptyDirectoryReparsePointAllowed(
    _In_ ULONG ReparseTag
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlAppxIsFileOwnedByTrustedInstaller(
    _In_ HANDLE FileHandle, 
    _Out_ PBOOLEAN IsFileOwnedByTrustedInstaller
    );

// rev
typedef struct _PS_PKG_CLAIM
{
    ULONGLONG Flags;
    ULONGLONG Origin;
} PS_PKG_CLAIM, *PPS_PKG_CLAIM;

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryPackageClaims(
    _In_ HANDLE TokenHandle,
    _Out_writes_bytes_to_opt_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_opt_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ PGUID DynamicId,
    _Out_opt_ PPS_PKG_CLAIM PkgClaim,
    _Out_opt_ PULONG64 AttributesPresent
    );

// Protected policies

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryProtectedPolicy(
    _In_ PGUID PolicyGuid,
    _Out_ PULONG_PTR PolicyValue
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetProtectedPolicy(
    _In_ PGUID PolicyGuid,
    _In_ ULONG_PTR PolicyValue,
    _Out_ PULONG_PTR OldPolicyValue
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// private
NTSYSAPI
BOOLEAN
NTAPI
RtlIsMultiSessionSku(
    VOID
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// private
NTSYSAPI
BOOLEAN
NTAPI
RtlIsMultiUsersInSessionSku(
    VOID
    );
#endif

// private
typedef enum _RTL_BSD_ITEM_TYPE
{
    RtlBsdItemVersionNumber, // q; s: ULONG
    RtlBsdItemProductType, // q; s: NT_PRODUCT_TYPE (ULONG)
    RtlBsdItemAabEnabled, // q: s: BOOLEAN
    RtlBsdItemAabTimeout, // q: s: UCHAR
    RtlBsdItemBootGood, // q: s: BOOLEAN
    RtlBsdItemBootShutdown, // q: s: BOOLEAN
    RtlBsdSleepInProgress, // q: s: BOOLEAN
    RtlBsdPowerTransition,
    RtlBsdItemBootAttemptCount, // q: s: UCHAR
    RtlBsdItemBootCheckpoint, // q: s: UCHAR
    RtlBsdItemBootId, // q; s: ULONG (USER_SHARED_DATA->BootId)
    RtlBsdItemShutdownBootId, // q; s: ULONG
    RtlBsdItemReportedAbnormalShutdownBootId, // q; s: ULONG
    RtlBsdItemErrorInfo,
    RtlBsdItemPowerButtonPressInfo,
    RtlBsdItemChecksum, // q: s: UCHAR
    RtlBsdPowerTransitionExtension,
    RtlBsdItemFeatureConfigurationState, // q; s: ULONG
    RtlBsdItemMax
} RTL_BSD_ITEM_TYPE;

// private
typedef struct _RTL_BSD_ITEM
{
    RTL_BSD_ITEM_TYPE Type;
    PVOID DataBuffer;
    ULONG DataLength;
} RTL_BSD_ITEM, *PRTL_BSD_ITEM;

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateBootStatusDataFile(
    VOID
    );

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlLockBootStatusData(
    _Out_ PHANDLE FileHandle
    );

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockBootStatusData(
    _In_ HANDLE FileHandle
    );

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlGetSetBootStatusData(
    _In_ HANDLE FileHandle,
    _In_ BOOLEAN Read,
    _In_ RTL_BSD_ITEM_TYPE DataClass,
    _In_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG ReturnLength
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckBootStatusIntegrity(
    _In_ HANDLE FileHandle, 
    _Out_ PBOOLEAN Verified
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetSystemBootStatus(
    _In_ RTL_BSD_ITEM_TYPE BootStatusInformationClass,
    _Out_ PVOID DataBuffer,
    _In_ ULONG DataLength,
    _Out_opt_ PULONG ReturnLength
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetSystemBootStatus(
    _In_ RTL_BSD_ITEM_TYPE BootStatusInformationClass,
    _In_ PVOID DataBuffer,
    _In_ ULONG DataLength,
    _Out_opt_ PULONG ReturnLength
    );
#endif

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckPortableOperatingSystem(
    _Out_ PBOOLEAN IsPortable // VOID
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetPortableOperatingSystem(
    _In_ BOOLEAN IsPortable
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI
NTSTATUS
NTAPI
RtlFindClosestEncodableLength(
    _In_ ULONGLONG SourceLength,
    _Out_ PULONGLONG TargetLength
    );

#endif

// Memory cache

typedef NTSTATUS (NTAPI *PRTL_SECURE_MEMORY_CACHE_CALLBACK)(
    _In_ PVOID Address,
    _In_ SIZE_T Length
    );

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlRegisterSecureMemoryCacheCallback(
    _In_ PRTL_SECURE_MEMORY_CACHE_CALLBACK Callback
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlDeregisterSecureMemoryCacheCallback(
    _In_ PRTL_SECURE_MEMORY_CACHE_CALLBACK Callback
    );

// ros
NTSYSAPI
BOOLEAN
NTAPI
RtlFlushSecureMemoryCache(
    _In_ PVOID MemoryCache,
    _In_opt_ SIZE_T MemoryLength
    );

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)

// Feature configuration

typedef struct __RTL_FEATURE_USAGE_REPORT
{
    ULONG FeatureId;
    USHORT ReportingKind;
    USHORT ReportingOptions;
} RTL_FEATURE_USAGE_REPORT, *PRTL_FEATURE_USAGE_REPORT;

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlNotifyFeatureUsage(
    _In_ PRTL_FEATURE_USAGE_REPORT FeatureUsageReport
    );

typedef enum _RTL_FEATURE_CONFIGURATION_TYPE
{
    RtlFeatureConfigurationBoot,
    RtlFeatureConfigurationRuntime,
    RtlFeatureConfigurationCount
} RTL_FEATURE_CONFIGURATION_TYPE;

// rev
typedef struct _RTL_FEATURE_CONFIGURATION
{
    ULONG FeatureId;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG Priority : 4;
            ULONG EnabledState : 2;
            ULONG IsWexpConfiguration : 1;
            ULONG HasSubscriptions : 1;
            ULONG Variant : 6;
            ULONG VariantPayloadKind : 2;
            ULONG Reserved : 16;
        };
    };
    ULONG VariantPayload;
} RTL_FEATURE_CONFIGURATION, *PRTL_FEATURE_CONFIGURATION;

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryFeatureConfiguration(
    _In_ ULONG FeatureId,
    _In_ RTL_FEATURE_CONFIGURATION_TYPE FeatureType,
    _Inout_ PULONGLONG ChangeStamp,
    _In_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetFeatureConfigurations(
    _Inout_ PULONGLONG ChangeStamp,
    _In_ RTL_FEATURE_CONFIGURATION_TYPE FeatureType,
    _In_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration,
    _In_ ULONG FeatureConfigurationCount
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryAllFeatureConfigurations(
    _In_ RTL_FEATURE_CONFIGURATION_TYPE FeatureType,
    _Inout_ PULONGLONG ChangeStamp,
    _Out_ PRTL_FEATURE_CONFIGURATION FeatureConfigurations,
    _Inout_ PULONG FeatureConfigurationCount
    );

// rev
NTSYSAPI
ULONGLONG
NTAPI
RtlQueryFeatureConfigurationChangeStamp(
    VOID
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryFeatureUsageNotificationSubscriptions(
    _Out_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration,
    _Inout_ PULONG FeatureConfigurationCount
    );

typedef VOID (NTAPI *PRTL_FEATURE_CONFIGURATION_CHANGE_NOTIFICAION)(
    _In_opt_ PVOID Context
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlRegisterFeatureConfigurationChangeNotification(
    _In_ PRTL_FEATURE_CONFIGURATION_CHANGE_NOTIFICAION Callback,
    _In_opt_ PVOID Context,
    _Inout_opt_ PULONGLONG ChangeStamp,
    _Out_ PHANDLE NotificationHandle
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlUnregisterFeatureConfigurationChangeNotification(
    _In_ HANDLE NotificationHandle
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSubscribeForFeatureUsageNotification(
    _In_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration,
    _In_ ULONG FeatureConfigurationCount
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlUnsubscribeFromFeatureUsageNotifications(
    _In_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration,
    _In_ ULONG FeatureConfigurationCount
    );
#endif


// #include <ntseapi.h>
// Privileges

#define SE_MIN_WELL_KNOWN_PRIVILEGE (2L)
#define SE_CREATE_TOKEN_PRIVILEGE (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE (3L)
#define SE_LOCK_MEMORY_PRIVILEGE (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE (5L)

#define SE_MACHINE_ACCOUNT_PRIVILEGE (6L)
#define SE_TCB_PRIVILEGE (7L)
#define SE_SECURITY_PRIVILEGE (8L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE (9L)
#define SE_LOAD_DRIVER_PRIVILEGE (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE (11L)
#define SE_SYSTEMTIME_PRIVILEGE (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE (16L)
#define SE_BACKUP_PRIVILEGE (17L)
#define SE_RESTORE_PRIVILEGE (18L)
#define SE_SHUTDOWN_PRIVILEGE (19L)
#define SE_DEBUG_PRIVILEGE (20L)
#define SE_AUDIT_PRIVILEGE (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE (24L)
#define SE_UNDOCK_PRIVILEGE (25L)
#define SE_SYNC_AGENT_PRIVILEGE (26L)
#define SE_ENABLE_DELEGATION_PRIVILEGE (27L)
#define SE_MANAGE_VOLUME_PRIVILEGE (28L)
#define SE_IMPERSONATE_PRIVILEGE (29L)
#define SE_CREATE_GLOBAL_PRIVILEGE (30L)
#define SE_TRUSTED_CREDMAN_ACCESS_PRIVILEGE (31L)
#define SE_RELABEL_PRIVILEGE (32L)
#define SE_INC_WORKING_SET_PRIVILEGE (33L)
#define SE_TIME_ZONE_PRIVILEGE (34L)
#define SE_CREATE_SYMBOLIC_LINK_PRIVILEGE (35L)
#define SE_DELEGATE_SESSION_USER_IMPERSONATE_PRIVILEGE (36L)
#define SE_MAX_WELL_KNOWN_PRIVILEGE SE_DELEGATE_SESSION_USER_IMPERSONATE_PRIVILEGE

// Authz

// begin_rev

// Types

#define TOKEN_SECURITY_ATTRIBUTE_TYPE_INVALID 0x00
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_INT64 0x01
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_UINT64 0x02
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_STRING 0x03
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_FQBN 0x04
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_SID 0x05
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_BOOLEAN 0x06
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_OCTET_STRING 0x10

// Flags

#define TOKEN_SECURITY_ATTRIBUTE_NON_INHERITABLE 0x0001
#define TOKEN_SECURITY_ATTRIBUTE_VALUE_CASE_SENSITIVE 0x0002
#define TOKEN_SECURITY_ATTRIBUTE_USE_FOR_DENY_ONLY 0x0004
#define TOKEN_SECURITY_ATTRIBUTE_DISABLED_BY_DEFAULT 0x0008
#define TOKEN_SECURITY_ATTRIBUTE_DISABLED 0x0010
#define TOKEN_SECURITY_ATTRIBUTE_MANDATORY 0x0020
#define TOKEN_SECURITY_ATTRIBUTE_COMPARE_IGNORE 0x0040

#define TOKEN_SECURITY_ATTRIBUTE_VALID_FLAGS ( \
    TOKEN_SECURITY_ATTRIBUTE_NON_INHERITABLE | \
    TOKEN_SECURITY_ATTRIBUTE_VALUE_CASE_SENSITIVE | \
    TOKEN_SECURITY_ATTRIBUTE_USE_FOR_DENY_ONLY | \
    TOKEN_SECURITY_ATTRIBUTE_DISABLED_BY_DEFAULT | \
    TOKEN_SECURITY_ATTRIBUTE_DISABLED | \
    TOKEN_SECURITY_ATTRIBUTE_MANDATORY)

#define TOKEN_SECURITY_ATTRIBUTE_CUSTOM_FLAGS 0xffff0000

// end_rev

// private
typedef struct _TOKEN_SECURITY_ATTRIBUTE_FQBN_VALUE
{
    ULONG64 Version;
    UNICODE_STRING Name;
} TOKEN_SECURITY_ATTRIBUTE_FQBN_VALUE, *PTOKEN_SECURITY_ATTRIBUTE_FQBN_VALUE;

// private
typedef struct _TOKEN_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE
{
    PVOID pValue;
    ULONG ValueLength;
} TOKEN_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE, *PTOKEN_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE;

// private
typedef struct _TOKEN_SECURITY_ATTRIBUTE_V1
{
    UNICODE_STRING Name;
    USHORT ValueType;
    USHORT Reserved;
    ULONG Flags;
    ULONG ValueCount;
    union
    {
        PLONG64 pInt64;
        PULONG64 pUint64;
        PUNICODE_STRING pString;
        PTOKEN_SECURITY_ATTRIBUTE_FQBN_VALUE pFqbn;
        PTOKEN_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE pOctetString;
    } Values;
} TOKEN_SECURITY_ATTRIBUTE_V1, *PTOKEN_SECURITY_ATTRIBUTE_V1;

// rev
#define TOKEN_SECURITY_ATTRIBUTES_INFORMATION_VERSION_V1 1
// rev
#define TOKEN_SECURITY_ATTRIBUTES_INFORMATION_VERSION TOKEN_SECURITY_ATTRIBUTES_INFORMATION_VERSION_V1

// private
typedef struct _TOKEN_SECURITY_ATTRIBUTES_INFORMATION
{
    USHORT Version;
    USHORT Reserved;
    ULONG AttributeCount;
    union
    {
        PTOKEN_SECURITY_ATTRIBUTE_V1 pAttributeV1;
    } Attribute;
} TOKEN_SECURITY_ATTRIBUTES_INFORMATION, *PTOKEN_SECURITY_ATTRIBUTES_INFORMATION;

// rev
typedef struct _TOKEN_PROCESS_TRUST_LEVEL
{
    PSID TrustLevelSid;
} TOKEN_PROCESS_TRUST_LEVEL, *PTOKEN_PROCESS_TRUST_LEVEL;

// Tokens

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateToken(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE TokenType,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER User,
    _In_ PTOKEN_GROUPS Groups,
    _In_ PTOKEN_PRIVILEGES Privileges,
    _In_opt_ PTOKEN_OWNER Owner,
    _In_ PTOKEN_PRIMARY_GROUP PrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL DefaultDacl,
    _In_ PTOKEN_SOURCE TokenSource
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateToken(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE TokenType,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER User,
    _In_ PTOKEN_GROUPS Groups,
    _In_ PTOKEN_PRIVILEGES Privileges,
    _In_opt_ PTOKEN_OWNER Owner,
    _In_ PTOKEN_PRIMARY_GROUP PrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL DefaultDacl,
    _In_ PTOKEN_SOURCE TokenSource
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateLowBoxToken(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PSID PackageSid,
    _In_ ULONG CapabilityCount,
    _In_reads_opt_(CapabilityCount) PSID_AND_ATTRIBUTES Capabilities,
    _In_ ULONG HandleCount,
    _In_reads_opt_(HandleCount) HANDLE *Handles
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateLowBoxToken(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PSID PackageSid,
    _In_ ULONG CapabilityCount,
    _In_reads_opt_(CapabilityCount) PSID_AND_ATTRIBUTES Capabilities,
    _In_ ULONG HandleCount,
    _In_reads_opt_(HandleCount) HANDLE *Handles
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateTokenEx(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE TokenType,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER User,
    _In_ PTOKEN_GROUPS Groups,
    _In_ PTOKEN_PRIVILEGES Privileges,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION UserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION DeviceAttributes,
    _In_opt_ PTOKEN_GROUPS DeviceGroups,
    _In_opt_ PTOKEN_MANDATORY_POLICY TokenMandatoryPolicy,
    _In_opt_ PTOKEN_OWNER Owner,
    _In_ PTOKEN_PRIMARY_GROUP PrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL DefaultDacl,
    _In_ PTOKEN_SOURCE TokenSource
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateTokenEx(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE TokenType,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER User,
    _In_ PTOKEN_GROUPS Groups,
    _In_ PTOKEN_PRIVILEGES Privileges,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION UserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION DeviceAttributes,
    _In_opt_ PTOKEN_GROUPS DeviceGroups,
    _In_opt_ PTOKEN_MANDATORY_POLICY TokenMandatoryPolicy,
    _In_opt_ PTOKEN_OWNER Owner,
    _In_ PTOKEN_PRIMARY_GROUP PrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL DefaultDacl,
    _In_ PTOKEN_SOURCE TokenSource
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcessToken(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE TokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenProcessToken(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE TokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcessTokenEx(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _Out_ PHANDLE TokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenProcessTokenEx(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _Out_ PHANDLE TokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenThreadToken(
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OpenAsSelf,
    _Out_ PHANDLE TokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenThreadToken(
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OpenAsSelf,
    _Out_ PHANDLE TokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenThreadTokenEx(
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OpenAsSelf,
    _In_ ULONG HandleAttributes,
    _Out_ PHANDLE TokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenThreadTokenEx(
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OpenAsSelf,
    _In_ ULONG HandleAttributes,
    _Out_ PHANDLE TokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDuplicateToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN EffectiveOnly,
    _In_ TOKEN_TYPE TokenType,
    _Out_ PHANDLE NewTokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDuplicateToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN EffectiveOnly,
    _In_ TOKEN_TYPE TokenType,
    _Out_ PHANDLE NewTokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_writes_bytes_to_opt_(TokenInformationLength, *ReturnLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength,
    _Out_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_writes_bytes_to_opt_(TokenInformationLength, *ReturnLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength,
    _Out_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _In_reads_bytes_(TokenInformationLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _In_reads_bytes_(TokenInformationLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAdjustPrivilegesToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAdjustPrivilegesToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAdjustGroupsToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN ResetToDefault,
    _In_opt_ PTOKEN_GROUPS NewState,
    _In_opt_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_GROUPS PreviousState,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAdjustGroupsToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN ResetToDefault,
    _In_opt_ PTOKEN_GROUPS NewState,
    _In_opt_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_GROUPS PreviousState,
    _Out_opt_ PULONG ReturnLength
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtAdjustTokenClaimsAndDeviceGroups(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN UserResetToDefault,
    _In_ BOOLEAN DeviceResetToDefault,
    _In_ BOOLEAN DeviceGroupsResetToDefault,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewUserState,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewDeviceState,
    _In_opt_ PTOKEN_GROUPS NewDeviceGroupsState,
    _In_ ULONG UserBufferLength,
    _Out_writes_bytes_to_opt_(UserBufferLength, *UserReturnLength) PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousUserState,
    _In_ ULONG DeviceBufferLength,
    _Out_writes_bytes_to_opt_(DeviceBufferLength, *DeviceReturnLength) PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousDeviceState,
    _In_ ULONG DeviceGroupsBufferLength,
    _Out_writes_bytes_to_opt_(DeviceGroupsBufferLength, *DeviceGroupsReturnBufferLength) PTOKEN_GROUPS PreviousDeviceGroups,
    _Out_opt_ PULONG UserReturnLength,
    _Out_opt_ PULONG DeviceReturnLength,
    _Out_opt_ PULONG DeviceGroupsReturnBufferLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAdjustTokenClaimsAndDeviceGroups(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN UserResetToDefault,
    _In_ BOOLEAN DeviceResetToDefault,
    _In_ BOOLEAN DeviceGroupsResetToDefault,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewUserState,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewDeviceState,
    _In_opt_ PTOKEN_GROUPS NewDeviceGroupsState,
    _In_ ULONG UserBufferLength,
    _Out_writes_bytes_to_opt_(UserBufferLength, *UserReturnLength) PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousUserState,
    _In_ ULONG DeviceBufferLength,
    _Out_writes_bytes_to_opt_(DeviceBufferLength, *DeviceReturnLength) PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousDeviceState,
    _In_ ULONG DeviceGroupsBufferLength,
    _Out_writes_bytes_to_opt_(DeviceGroupsBufferLength, *DeviceGroupsReturnBufferLength) PTOKEN_GROUPS PreviousDeviceGroups,
    _Out_opt_ PULONG UserReturnLength,
    _Out_opt_ PULONG DeviceReturnLength,
    _Out_opt_ PULONG DeviceGroupsReturnBufferLength
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtFilterToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _Out_ PHANDLE NewTokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFilterToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _Out_ PHANDLE NewTokenHandle
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtFilterTokenEx(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _In_ ULONG DisableUserClaimsCount,
    _In_opt_ PUNICODE_STRING UserClaimsToDisable,
    _In_ ULONG DisableDeviceClaimsCount,
    _In_opt_ PUNICODE_STRING DeviceClaimsToDisable,
    _In_opt_ PTOKEN_GROUPS DeviceGroupsToDisable,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedUserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedDeviceAttributes,
    _In_opt_ PTOKEN_GROUPS RestrictedDeviceGroups,
    _Out_ PHANDLE NewTokenHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFilterTokenEx(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _In_ ULONG DisableUserClaimsCount,
    _In_opt_ PUNICODE_STRING UserClaimsToDisable,
    _In_ ULONG DisableDeviceClaimsCount,
    _In_opt_ PUNICODE_STRING DeviceClaimsToDisable,
    _In_opt_ PTOKEN_GROUPS DeviceGroupsToDisable,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedUserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedDeviceAttributes,
    _In_opt_ PTOKEN_GROUPS RestrictedDeviceGroups,
    _Out_ PHANDLE NewTokenHandle
    );
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompareTokens(
    _In_ HANDLE FirstTokenHandle,
    _In_ HANDLE SecondTokenHandle,
    _Out_ PBOOLEAN Equal
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCompareTokens(
    _In_ HANDLE FirstTokenHandle,
    _In_ HANDLE SecondTokenHandle,
    _Out_ PBOOLEAN Equal
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrivilegeCheck(
    _In_ HANDLE ClientToken,
    _Inout_ PPRIVILEGE_SET RequiredPrivileges,
    _Out_ PBOOLEAN Result
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPrivilegeCheck(
    _In_ HANDLE ClientToken,
    _Inout_ PPRIVILEGE_SET RequiredPrivileges,
    _Out_ PBOOLEAN Result
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtImpersonateAnonymousToken(
    _In_ HANDLE ThreadHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwImpersonateAnonymousToken(
    _In_ HANDLE ThreadHandle
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySecurityAttributesToken(
    _In_ HANDLE TokenHandle,
    _In_reads_opt_(NumberOfAttributes) PUNICODE_STRING Attributes,
    _In_ ULONG NumberOfAttributes,
    _Out_writes_bytes_(Length) PVOID Buffer, // PTOKEN_SECURITY_ATTRIBUTES_INFORMATION
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQuerySecurityAttributesToken(
    _In_ HANDLE TokenHandle,
    _In_reads_opt_(NumberOfAttributes) PUNICODE_STRING Attributes,
    _In_ ULONG NumberOfAttributes,
    _Out_writes_bytes_(Length) PVOID Buffer, // PTOKEN_SECURITY_ATTRIBUTES_INFORMATION
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength
    );
#endif

// Access checking

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheck(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAccessCheck(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByType(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_reads_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAccessCheckByType(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_reads_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByTypeResultList(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_reads_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAccessCheckByTypeResultList(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_reads_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus
    );

// Signing

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetCachedSigningLevel(
    _In_ ULONG Flags,
    _In_ SE_SIGNING_LEVEL InputSigningLevel,
    _In_reads_(SourceFileCount) PHANDLE SourceFiles,
    _In_ ULONG SourceFileCount,
    _In_opt_ HANDLE TargetFile
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetCachedSigningLevel(
    _In_ ULONG Flags,
    _In_ SE_SIGNING_LEVEL InputSigningLevel,
    _In_reads_(SourceFileCount) PHANDLE SourceFiles,
    _In_ ULONG SourceFileCount,
    _In_opt_ HANDLE TargetFile
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetCachedSigningLevel(
    _In_ HANDLE File,
    _Out_ PULONG Flags,
    _Out_ PSE_SIGNING_LEVEL SigningLevel,
    _Out_writes_bytes_to_opt_(*ThumbprintSize, *ThumbprintSize) PUCHAR Thumbprint,
    _Inout_opt_ PULONG ThumbprintSize,
    _Out_opt_ PULONG ThumbprintAlgorithm
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetCachedSigningLevel(
    _In_ HANDLE File,
    _Out_ PULONG Flags,
    _Out_ PSE_SIGNING_LEVEL SigningLevel,
    _Out_writes_bytes_to_opt_(*ThumbprintSize, *ThumbprintSize) PUCHAR Thumbprint,
    _Inout_opt_ PULONG ThumbprintSize,
    _Out_opt_ PULONG ThumbprintAlgorithm
    );

// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompareSigningLevels(
    _In_ SE_SIGNING_LEVEL FirstSigningLevel,
    _In_ SE_SIGNING_LEVEL SecondSigningLevel
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCompareSigningLevels(
    _In_ SE_SIGNING_LEVEL FirstSigningLevel,
    _In_ SE_SIGNING_LEVEL SecondSigningLevel
    );

#endif

// Audit alarm

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAccessCheckAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByTypeAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAccessCheckByTypeAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByTypeResultListAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAccessCheckByTypeResultListAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByTypeResultListAndAuditAlarmByHandle(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ HANDLE ClientToken,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwAccessCheckByTypeResultListAndAuditAlarmByHandle(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ HANDLE ClientToken,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK GrantedAccess,
    _In_opt_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN ObjectCreation,
    _In_ BOOLEAN AccessGranted,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK GrantedAccess,
    _In_opt_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN ObjectCreation,
    _In_ BOOLEAN AccessGranted,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrivilegeObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPrivilegeObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCloseObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ BOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCloseObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ BOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ BOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwDeleteObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ BOOLEAN GenerateOnClose
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrivilegedServiceAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_ PUNICODE_STRING ServiceName,
    _In_ HANDLE ClientToken,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPrivilegedServiceAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_ PUNICODE_STRING ServiceName,
    _In_ HANDLE ClientToken,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted
    );
 

// #include <nttmapi.h>
#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateTransactionManager(
    _Out_ PHANDLE TmHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PUNICODE_STRING LogFileName,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ ULONG CommitStrength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateTransactionManager(
    _Out_ PHANDLE TmHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PUNICODE_STRING LogFileName,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ ULONG CommitStrength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenTransactionManager(
    _Out_ PHANDLE TmHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PUNICODE_STRING LogFileName,
    _In_opt_ LPGUID TmIdentity,
    _In_opt_ ULONG OpenOptions
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenTransactionManager(
    _Out_ PHANDLE TmHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PUNICODE_STRING LogFileName,
    _In_opt_ LPGUID TmIdentity,
    _In_opt_ ULONG OpenOptions
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRenameTransactionManager(
    _In_ PUNICODE_STRING LogFileName,
    _In_ LPGUID ExistingTransactionManagerGuid
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRenameTransactionManager(
    _In_ PUNICODE_STRING LogFileName,
    _In_ LPGUID ExistingTransactionManagerGuid
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRollforwardTransactionManager(
    _In_ HANDLE TransactionManagerHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRollforwardTransactionManager(
    _In_ HANDLE TransactionManagerHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRecoverTransactionManager(
    _In_ HANDLE TransactionManagerHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRecoverTransactionManager(
    _In_ HANDLE TransactionManagerHandle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationTransactionManager(
    _In_ HANDLE TransactionManagerHandle,
    _In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
    _Out_writes_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
    _In_ ULONG TransactionManagerInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationTransactionManager(
    _In_ HANDLE TransactionManagerHandle,
    _In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
    _Out_writes_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
    _In_ ULONG TransactionManagerInformationLength,
    _Out_opt_ PULONG ReturnLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationTransactionManager(
    _In_opt_ HANDLE TmHandle,
    _In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
    _In_reads_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
    _In_ ULONG TransactionManagerInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationTransactionManager(
    _In_opt_ HANDLE TmHandle,
    _In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
    _In_reads_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
    _In_ ULONG TransactionManagerInformationLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnumerateTransactionObject(
    _In_opt_ HANDLE RootObjectHandle,
    _In_ KTMOBJECT_TYPE QueryType,
    _Inout_updates_bytes_(ObjectCursorLength) PKTMOBJECT_CURSOR ObjectCursor,
    _In_ ULONG ObjectCursorLength,
    _Out_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwEnumerateTransactionObject(
    _In_opt_ HANDLE RootObjectHandle,
    _In_ KTMOBJECT_TYPE QueryType,
    _Inout_updates_bytes_(ObjectCursorLength) PKTMOBJECT_CURSOR ObjectCursor,
    _In_ ULONG ObjectCursorLength,
    _Out_ PULONG ReturnLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateTransaction(
    _Out_ PHANDLE TransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ LPGUID Uow,
    _In_opt_ HANDLE TmHandle,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ ULONG IsolationLevel,
    _In_opt_ ULONG IsolationFlags,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_opt_ PUNICODE_STRING Description
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateTransaction(
    _Out_ PHANDLE TransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ LPGUID Uow,
    _In_opt_ HANDLE TmHandle,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ ULONG IsolationLevel,
    _In_opt_ ULONG IsolationFlags,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_opt_ PUNICODE_STRING Description
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenTransaction(
    _Out_ PHANDLE TransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ LPGUID Uow,
    _In_opt_ HANDLE TmHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenTransaction(
    _Out_ PHANDLE TransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ LPGUID Uow,
    _In_opt_ HANDLE TmHandle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
    _Out_writes_bytes_(TransactionInformationLength) PVOID TransactionInformation,
    _In_ ULONG TransactionInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
    _Out_writes_bytes_(TransactionInformationLength) PVOID TransactionInformation,
    _In_ ULONG TransactionInformationLength,
    _Out_opt_ PULONG ReturnLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
    _In_reads_bytes_(TransactionInformationLength) PVOID TransactionInformation,
    _In_ ULONG TransactionInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
    _In_reads_bytes_(TransactionInformationLength) PVOID TransactionInformation,
    _In_ ULONG TransactionInformationLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCommitTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ BOOLEAN Wait
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCommitTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ BOOLEAN Wait
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRollbackTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ BOOLEAN Wait
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRollbackTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ BOOLEAN Wait
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateEnlistment(
    _Out_ PHANDLE EnlistmentHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE ResourceManagerHandle,
    _In_ HANDLE TransactionHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG CreateOptions,
    _In_ NOTIFICATION_MASK NotificationMask,
    _In_opt_ PVOID EnlistmentKey
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateEnlistment(
    _Out_ PHANDLE EnlistmentHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE ResourceManagerHandle,
    _In_ HANDLE TransactionHandle,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG CreateOptions,
    _In_ NOTIFICATION_MASK NotificationMask,
    _In_opt_ PVOID EnlistmentKey
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenEnlistment(
    _Out_ PHANDLE EnlistmentHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE ResourceManagerHandle,
    _In_ LPGUID EnlistmentGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenEnlistment(
    _Out_ PHANDLE EnlistmentHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE ResourceManagerHandle,
    _In_ LPGUID EnlistmentGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
    _Out_writes_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
    _In_ ULONG EnlistmentInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
    _Out_writes_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
    _In_ ULONG EnlistmentInformationLength,
    _Out_opt_ PULONG ReturnLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationEnlistment(
    _In_opt_ HANDLE EnlistmentHandle,
    _In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
    _In_reads_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
    _In_ ULONG EnlistmentInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationEnlistment(
    _In_opt_ HANDLE EnlistmentHandle,
    _In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
    _In_reads_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
    _In_ ULONG EnlistmentInformationLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRecoverEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PVOID EnlistmentKey
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRecoverEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PVOID EnlistmentKey
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrePrepareEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPrePrepareEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrepareEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPrepareEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCommitEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCommitEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRollbackEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRollbackEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrePrepareComplete(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPrePrepareComplete(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrepareComplete(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPrepareComplete(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCommitComplete(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCommitComplete(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadOnlyEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwReadOnlyEnlistment(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRollbackComplete(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRollbackComplete(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtSinglePhaseReject(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSinglePhaseReject(
    _In_ HANDLE EnlistmentHandle,
    _In_opt_ PLARGE_INTEGER TmVirtualClock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateResourceManager(
    _Out_ PHANDLE ResourceManagerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE TmHandle,
    _In_ LPGUID RmGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ PUNICODE_STRING Description
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateResourceManager(
    _Out_ PHANDLE ResourceManagerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE TmHandle,
    _In_ LPGUID RmGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG CreateOptions,
    _In_opt_ PUNICODE_STRING Description
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenResourceManager(
    _Out_ PHANDLE ResourceManagerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE TmHandle,
    _In_opt_ LPGUID ResourceManagerGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwOpenResourceManager(
    _Out_ PHANDLE ResourceManagerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ HANDLE TmHandle,
    _In_opt_ LPGUID ResourceManagerGuid,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRecoverResourceManager(
    _In_ HANDLE ResourceManagerHandle
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRecoverResourceManager(
    _In_ HANDLE ResourceManagerHandle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetNotificationResourceManager(
    _In_ HANDLE ResourceManagerHandle,
    _Out_ PTRANSACTION_NOTIFICATION TransactionNotification,
    _In_ ULONG NotificationLength,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_opt_ PULONG ReturnLength,
    _In_ ULONG Asynchronous,
    _In_opt_ ULONG_PTR AsynchronousContext
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwGetNotificationResourceManager(
    _In_ HANDLE ResourceManagerHandle,
    _Out_ PTRANSACTION_NOTIFICATION TransactionNotification,
    _In_ ULONG NotificationLength,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_opt_ PULONG ReturnLength,
    _In_ ULONG Asynchronous,
    _In_opt_ ULONG_PTR AsynchronousContext
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationResourceManager(
    _In_ HANDLE ResourceManagerHandle,
    _In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
    _Out_writes_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
    _In_ ULONG ResourceManagerInformationLength,
    _Out_opt_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwQueryInformationResourceManager(
    _In_ HANDLE ResourceManagerHandle,
    _In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
    _Out_writes_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
    _In_ ULONG ResourceManagerInformationLength,
    _Out_opt_ PULONG ReturnLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationResourceManager(
    _In_ HANDLE ResourceManagerHandle,
    _In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
    _In_reads_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
    _In_ ULONG ResourceManagerInformationLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwSetInformationResourceManager(
    _In_ HANDLE ResourceManagerHandle,
    _In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
    _In_reads_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
    _In_ ULONG ResourceManagerInformationLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtRegisterProtocolAddressInformation(
    _In_ HANDLE ResourceManager,
    _In_ PCRM_PROTOCOL_ID ProtocolId,
    _In_ ULONG ProtocolInformationSize,
    _In_ PVOID ProtocolInformation,
    _In_opt_ ULONG CreateOptions
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRegisterProtocolAddressInformation(
    _In_ HANDLE ResourceManager,
    _In_ PCRM_PROTOCOL_ID ProtocolId,
    _In_ ULONG ProtocolInformationSize,
    _In_ PVOID ProtocolInformation,
    _In_opt_ ULONG CreateOptions
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtPropagationComplete(
    _In_ HANDLE ResourceManagerHandle,
    _In_ ULONG RequestCookie,
    _In_ ULONG BufferLength,
    _In_ PVOID Buffer
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPropagationComplete(
    _In_ HANDLE ResourceManagerHandle,
    _In_ ULONG RequestCookie,
    _In_ ULONG BufferLength,
    _In_ PVOID Buffer
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtPropagationFailed(
    _In_ HANDLE ResourceManagerHandle,
    _In_ ULONG RequestCookie,
    _In_ NTSTATUS PropStatus
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwPropagationFailed(
    _In_ HANDLE ResourceManagerHandle,
    _In_ ULONG RequestCookie,
    _In_ NTSTATUS PropStatus
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreezeTransactions(
    _In_ PLARGE_INTEGER FreezeTimeout,
    _In_ PLARGE_INTEGER ThawTimeout
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwFreezeTransactions(
    _In_ PLARGE_INTEGER FreezeTimeout,
    _In_ PLARGE_INTEGER ThawTimeout
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI
NTSTATUS
NTAPI
NtThawTransactions(
    VOID
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwThawTransactions(
    VOID
    );
#endif
 

// #include <nttp.h>
// Some types are already defined in winnt.h.

typedef struct _TP_ALPC TP_ALPC, *PTP_ALPC;

// private
typedef VOID (NTAPI *PTP_ALPC_CALLBACK)(
    _Inout_ PTP_CALLBACK_INSTANCE Instance,
    _Inout_opt_ PVOID Context,
    _In_ PTP_ALPC Alpc
    );

// rev
typedef VOID (NTAPI *PTP_ALPC_CALLBACK_EX)(
    _Inout_ PTP_CALLBACK_INSTANCE Instance,
    _Inout_opt_ PVOID Context,
    _In_ PTP_ALPC Alpc,
    _In_ PVOID ApcContext
    );

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
_Check_return_
NTSYSAPI
NTSTATUS
NTAPI
TpAllocPool(
    _Out_ PTP_POOL *PoolReturn,
    _Reserved_ PVOID Reserved
    );

// winbase:CloseThreadpool
NTSYSAPI
VOID
NTAPI
TpReleasePool(
    _Inout_ PTP_POOL Pool
    );

// winbase:SetThreadpoolThreadMaximum
NTSYSAPI
VOID
NTAPI
TpSetPoolMaxThreads(
    _Inout_ PTP_POOL Pool,
    _In_ ULONG MaxThreads
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
TpSetPoolMinThreads(
    _Inout_ PTP_POOL Pool,
    _In_ ULONG MinThreads
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
TpQueryPoolStackInformation(
    _In_ PTP_POOL Pool,
    _Out_ PTP_POOL_STACK_INFORMATION PoolStackInformation
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
TpSetPoolStackInformation(
    _Inout_ PTP_POOL Pool,
    _In_ PTP_POOL_STACK_INFORMATION PoolStackInformation
    );
#endif

// private
_Check_return_
NTSYSAPI
NTSTATUS
NTAPI
TpAllocCleanupGroup(
    _Out_ PTP_CLEANUP_GROUP *CleanupGroupReturn
    );

// winbase:CloseThreadpoolCleanupGroup
NTSYSAPI
VOID
NTAPI
TpReleaseCleanupGroup(
    _Inout_ PTP_CLEANUP_GROUP CleanupGroup
    );

// winbase:CloseThreadpoolCleanupGroupMembers
NTSYSAPI
VOID
NTAPI
TpReleaseCleanupGroupMembers(
    _Inout_ PTP_CLEANUP_GROUP CleanupGroup,
    _In_ LOGICAL CancelPendingCallbacks,
    _Inout_opt_ PVOID CleanupParameter
    );

// winbase:SetEventWhenCallbackReturns
NTSYSAPI
VOID
NTAPI
TpCallbackSetEventOnCompletion(
    _Inout_ PTP_CALLBACK_INSTANCE Instance,
    _In_ HANDLE Event
    );

// winbase:ReleaseSemaphoreWhenCallbackReturns
NTSYSAPI
VOID
NTAPI
TpCallbackReleaseSemaphoreOnCompletion(
    _Inout_ PTP_CALLBACK_INSTANCE Instance,
    _In_ HANDLE Semaphore,
    _In_ ULONG ReleaseCount
    );

// winbase:ReleaseMutexWhenCallbackReturns
NTSYSAPI
VOID
NTAPI
TpCallbackReleaseMutexOnCompletion(
    _Inout_ PTP_CALLBACK_INSTANCE Instance,
    _In_ HANDLE Mutex
    );

// winbase:LeaveCriticalSectionWhenCallbackReturns
NTSYSAPI
VOID
NTAPI
TpCallbackLeaveCriticalSectionOnCompletion(
    _Inout_ PTP_CALLBACK_INSTANCE Instance,
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
    );

// winbase:FreeLibraryWhenCallbackReturns
NTSYSAPI
VOID
NTAPI
TpCallbackUnloadDllOnCompletion(
    _Inout_ PTP_CALLBACK_INSTANCE Instance,
    _In_ PVOID DllHandle
    );

// winbase:CallbackMayRunLong
NTSYSAPI
NTSTATUS
NTAPI
TpCallbackMayRunLong(
    _Inout_ PTP_CALLBACK_INSTANCE Instance
    );

// winbase:DisassociateCurrentThreadFromCallback
NTSYSAPI
VOID
NTAPI
TpDisassociateCallback(
    _Inout_ PTP_CALLBACK_INSTANCE Instance
    );

// winbase:TrySubmitThreadpoolCallback
_Check_return_
NTSYSAPI
NTSTATUS
NTAPI
TpSimpleTryPost(
    _In_ PTP_SIMPLE_CALLBACK Callback,
    _Inout_opt_ PVOID Context,
    _In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
    );

// private
_Check_return_
NTSYSAPI
NTSTATUS
NTAPI
TpAllocWork(
    _Out_ PTP_WORK *WorkReturn,
    _In_ PTP_WORK_CALLBACK Callback,
    _Inout_opt_ PVOID Context,
    _In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
    );

// winbase:CloseThreadpoolWork
NTSYSAPI
VOID
NTAPI
TpReleaseWork(
    _Inout_ PTP_WORK Work
    );

// winbase:SubmitThreadpoolWork
NTSYSAPI
VOID
NTAPI
TpPostWork(
    _Inout_ PTP_WORK Work
    );

// winbase:WaitForThreadpoolWorkCallbacks
NTSYSAPI
VOID
NTAPI
TpWaitForWork(
    _Inout_ PTP_WORK Work,
    _In_ LOGICAL CancelPendingCallbacks
    );

// private
_Check_return_
NTSYSAPI
NTSTATUS
NTAPI
TpAllocTimer(
    _Out_ PTP_TIMER *Timer,
    _In_ PTP_TIMER_CALLBACK Callback,
    _Inout_opt_ PVOID Context,
    _In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
    );

// winbase:CloseThreadpoolTimer
NTSYSAPI
VOID
NTAPI
TpReleaseTimer(
    _Inout_ PTP_TIMER Timer
    );

// winbase:SetThreadpoolTimer
NTSYSAPI
VOID
NTAPI
TpSetTimer(
    _Inout_ PTP_TIMER Timer,
    _In_opt_ PLARGE_INTEGER DueTime,
    _In_ ULONG Period,
    _In_opt_ ULONG WindowLength
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// winbase:SetThreadpoolTimerEx
NTSYSAPI
NTSTATUS
NTAPI
TpSetTimerEx(
    _Inout_ PTP_TIMER Timer,
    _In_opt_ PLARGE_INTEGER DueTime,
    _In_ ULONG Period,
    _In_opt_ ULONG WindowLength
    );
#endif

// winbase:IsThreadpoolTimerSet
NTSYSAPI
LOGICAL
NTAPI
TpIsTimerSet(
    _In_ PTP_TIMER Timer
    );

// winbase:WaitForThreadpoolTimerCallbacks
NTSYSAPI
VOID
NTAPI
TpWaitForTimer(
    _Inout_ PTP_TIMER Timer,
    _In_ LOGICAL CancelPendingCallbacks
    );

// private
_Check_return_
NTSYSAPI
NTSTATUS
NTAPI
TpAllocWait(
    _Out_ PTP_WAIT *WaitReturn,
    _In_ PTP_WAIT_CALLBACK Callback,
    _Inout_opt_ PVOID Context,
    _In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
    );

// winbase:CloseThreadpoolWait
NTSYSAPI
VOID
NTAPI
TpReleaseWait(
    _Inout_ PTP_WAIT Wait
    );

// winbase:SetThreadpoolWait
NTSYSAPI
VOID
NTAPI
TpSetWait(
    _Inout_ PTP_WAIT Wait,
    _In_opt_ HANDLE Handle,
    _In_opt_ PLARGE_INTEGER Timeout
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// winbase:SetThreadpoolWaitEx
NTSYSAPI
NTSTATUS
NTAPI
TpSetWaitEx(
    _Inout_ PTP_WAIT Wait,
    _In_opt_ HANDLE Handle,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_opt_ PVOID Reserved
    );
#endif

// winbase:WaitForThreadpoolWaitCallbacks
NTSYSAPI
VOID
NTAPI
TpWaitForWait(
    _Inout_ PTP_WAIT Wait,
    _In_ LOGICAL CancelPendingCallbacks
    );

// private
typedef VOID (NTAPI *PTP_IO_CALLBACK)(
    _Inout_ PTP_CALLBACK_INSTANCE Instance,
    _Inout_opt_ PVOID Context,
    _In_ PVOID ApcContext,
    _In_ PIO_STATUS_BLOCK IoSB,
    _In_ PTP_IO Io
    );

// private
_Check_return_
NTSYSAPI
NTSTATUS
NTAPI
TpAllocIoCompletion(
    _Out_ PTP_IO *IoReturn,
    _In_ HANDLE File,
    _In_ PTP_IO_CALLBACK Callback,
    _Inout_opt_ PVOID Context,
    _In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
    );

// winbase:CloseThreadpoolIo
NTSYSAPI
VOID
NTAPI
TpReleaseIoCompletion(
    _Inout_ PTP_IO Io
    );

// winbase:StartThreadpoolIo
NTSYSAPI
VOID
NTAPI
TpStartAsyncIoOperation(
    _Inout_ PTP_IO Io
    );

// winbase:CancelThreadpoolIo
NTSYSAPI
VOID
NTAPI
TpCancelAsyncIoOperation(
    _Inout_ PTP_IO Io
    );

// winbase:WaitForThreadpoolIoCallbacks
NTSYSAPI
VOID
NTAPI
TpWaitForIoCompletion(
    _Inout_ PTP_IO Io,
    _In_ LOGICAL CancelPendingCallbacks
    );

// private
NTSYSAPI
NTSTATUS
NTAPI
TpAllocAlpcCompletion(
    _Out_ PTP_ALPC *AlpcReturn,
    _In_ HANDLE AlpcPort,
    _In_ PTP_ALPC_CALLBACK Callback,
    _Inout_opt_ PVOID Context,
    _In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
TpAllocAlpcCompletionEx(
    _Out_ PTP_ALPC *AlpcReturn,
    _In_ HANDLE AlpcPort,
    _In_ PTP_ALPC_CALLBACK_EX Callback,
    _Inout_opt_ PVOID Context,
    _In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
    );
#endif

// private
NTSYSAPI
VOID
NTAPI
TpReleaseAlpcCompletion(
    _Inout_ PTP_ALPC Alpc
    );

// private
NTSYSAPI
VOID
NTAPI
TpWaitForAlpcCompletion(
    _Inout_ PTP_ALPC Alpc
    );

// private
typedef enum _TP_TRACE_TYPE
{
    TpTraceThreadPriority = 1,
    TpTraceThreadAffinity,
    MaxTpTraceType
} TP_TRACE_TYPE;

// private
NTSYSAPI
VOID
NTAPI
TpCaptureCaller(
    _In_ TP_TRACE_TYPE Type
    );

// private
NTSYSAPI
VOID
NTAPI
TpCheckTerminateWorker(
    _In_ HANDLE Thread
    );

#endif
 

// #include <ntxcapi.h>
NTSYSAPI
BOOLEAN
NTAPI
RtlDispatchException(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord
    );

NTSYSAPI
DECLSPEC_NORETURN
VOID
NTAPI
RtlRaiseStatus(
    _In_ NTSTATUS Status
    );

NTSYSAPI
VOID
NTAPI
RtlRaiseException(
    _In_ PEXCEPTION_RECORD ExceptionRecord
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
NtContinue(
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN TestAlert
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwContinue(
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN TestAlert
    );

#if (NTDDI_VERSION >= NTDDI_WIN10)
typedef enum _KCONTINUE_TYPE
{
    KCONTINUE_UNWIND,
    KCONTINUE_RESUME,
    KCONTINUE_LONGJUMP,
    KCONTINUE_SET,
    KCONTINUE_LAST,
} KCONTINUE_TYPE;

typedef struct _KCONTINUE_ARGUMENT
{
    KCONTINUE_TYPE ContinueType;
    ULONG ContinueFlags;
    ULONGLONG Reserved[2];
} KCONTINUE_ARGUMENT, *PKCONTINUE_ARGUMENT;

#define KCONTINUE_FLAG_TEST_ALERT 0x00000001 // wbenny
#define KCONTINUE_FLAG_DELIVER_APC 0x00000002 // wbenny

NTSYSCALLAPI
NTSTATUS
NTAPI
NtContinueEx(
    _In_ PCONTEXT ContextRecord,
    _In_ PKCONTINUE_ARGUMENT ContinueArgument // BOOLEAN is also valid
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwContinueEx(
    _In_ PCONTEXT ContextRecord,
    _In_ PKCONTINUE_ARGUMENT ContinueArgument // BOOLEAN is also valid
    );

//FORCEINLINE
//NTSTATUS
//NtContinue(
//    _In_ PCONTEXT ContextRecord,
//    _In_ BOOLEAN TestAlert
//    )
//{
//    return NtContinueEx(ContextRecord, (PCONTINUE_ARGUMENT)TestAlert);
//}
#endif

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRaiseException(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN FirstChance
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwRaiseException(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN FirstChance
    );

__analysis_noreturn
NTSYSCALLAPI
VOID
NTAPI
RtlAssert(
    _In_ PVOID VoidFailedAssertion,
    _In_ PVOID VoidFileName,
    _In_ ULONG LineNumber,
    _In_opt_ PSTR MutableMessage
    );

#define RTL_ASSERT(exp) \
    ((!(exp)) ? (RtlAssert((PVOID)#exp, (PVOID)__FILE__, __LINE__, NULL), FALSE) : TRUE)
#define RTL_ASSERTMSG(msg, exp) \
    ((!(exp)) ? (RtlAssert((PVOID)#exp, (PVOID)__FILE__, __LINE__, msg), FALSE) : TRUE)
#define RTL_SOFT_ASSERT(_exp) \
    ((!(_exp)) ? (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n", __FILE__, __LINE__, #_exp), FALSE) : TRUE)
#define RTL_SOFT_ASSERTMSG(_msg, _exp) \
    ((!(_exp)) ? (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n   Message: %s\n", __FILE__, __LINE__, #_exp, (_msg)), FALSE) : TRUE)
 


// #include <ntd3dkmt.h>
#if __has_include(<d3dkmthk.h>)
#include <d3dkmthk.h>
#else

typedef UINT32 D3DKMT_HANDLE;
typedef D3DKMT_HANDLE *PD3DKMT_HANDLE;

typedef enum _KMTQUERYADAPTERINFOTYPE
{
    KMTQAITYPE_UMDRIVERPRIVATE,
    KMTQAITYPE_UMDRIVERNAME, // D3DKMT_UMDFILENAMEINFO
    KMTQAITYPE_UMOPENGLINFO, // D3DKMT_OPENGLINFO
    KMTQAITYPE_GETSEGMENTSIZE, // D3DKMT_SEGMENTSIZEINFO
    KMTQAITYPE_ADAPTERGUID, // GUID
    KMTQAITYPE_FLIPQUEUEINFO, // D3DKMT_FLIPQUEUEINFO
    KMTQAITYPE_ADAPTERADDRESS, // D3DKMT_ADAPTERADDRESS
    KMTQAITYPE_SETWORKINGSETINFO, // D3DKMT_WORKINGSETINFO
    KMTQAITYPE_ADAPTERREGISTRYINFO, // D3DKMT_ADAPTERREGISTRYINFO
    KMTQAITYPE_CURRENTDISPLAYMODE, // D3DKMT_CURRENTDISPLAYMODE
    KMTQAITYPE_MODELIST, // D3DKMT_DISPLAYMODE[] // 10
    KMTQAITYPE_CHECKDRIVERUPDATESTATUS,
    KMTQAITYPE_VIRTUALADDRESSINFO, // D3DKMT_VIRTUALADDRESSINFO
    KMTQAITYPE_DRIVERVERSION, // D3DKMT_DRIVERVERSION
    KMTQAITYPE_UNKNOWN,
    KMTQAITYPE_ADAPTERTYPE, // D3DKMT_ADAPTERTYPE // since WIN8
    KMTQAITYPE_OUTPUTDUPLCONTEXTSCOUNT, // D3DKMT_OUTPUTDUPLCONTEXTSCOUNT
    KMTQAITYPE_WDDM_1_2_CAPS, // D3DKMT_WDDM_1_2_CAPS
    KMTQAITYPE_UMD_DRIVER_VERSION, // D3DKMT_UMD_DRIVER_VERSION
    KMTQAITYPE_DIRECTFLIP_SUPPORT, // D3DKMT_DIRECTFLIP_SUPPORT
    KMTQAITYPE_MULTIPLANEOVERLAY_SUPPORT, // D3DKMT_MULTIPLANEOVERLAY_SUPPORT // since WDDM1_3 // 20
    KMTQAITYPE_DLIST_DRIVER_NAME, // D3DKMT_DLIST_DRIVER_NAME
    KMTQAITYPE_WDDM_1_3_CAPS, // D3DKMT_WDDM_1_3_CAPS
    KMTQAITYPE_MULTIPLANEOVERLAY_HUD_SUPPORT, // D3DKMT_MULTIPLANEOVERLAY_HUD_SUPPORT
    KMTQAITYPE_WDDM_2_0_CAPS, // D3DKMT_WDDM_2_0_CAPS // since WDDM2_0
    KMTQAITYPE_NODEMETADATA, // D3DKMT_NODEMETADATA
    KMTQAITYPE_CPDRIVERNAME, // D3DKMT_CPDRIVERNAME
    KMTQAITYPE_XBOX, // D3DKMT_XBOX
    KMTQAITYPE_INDEPENDENTFLIP_SUPPORT, // D3DKMT_INDEPENDENTFLIP_SUPPORT
    KMTQAITYPE_MIRACASTCOMPANIONDRIVERNAME, // D3DKMT_MIRACASTCOMPANIONDRIVERNAME
    KMTQAITYPE_PHYSICALADAPTERCOUNT, // D3DKMT_PHYSICAL_ADAPTER_COUNT // 30
    KMTQAITYPE_PHYSICALADAPTERDEVICEIDS, // D3DKMT_QUERY_DEVICE_IDS
    KMTQAITYPE_DRIVERCAPS_EXT, // D3DKMT_DRIVERCAPS_EXT
    KMTQAITYPE_QUERY_MIRACAST_DRIVER_TYPE, // D3DKMT_QUERY_MIRACAST_DRIVER_TYPE
    KMTQAITYPE_QUERY_GPUMMU_CAPS, // D3DKMT_QUERY_GPUMMU_CAPS
    KMTQAITYPE_QUERY_MULTIPLANEOVERLAY_DECODE_SUPPORT, // D3DKMT_MULTIPLANEOVERLAY_DECODE_SUPPORT
    KMTQAITYPE_QUERY_HW_PROTECTION_TEARDOWN_COUNT, // UINT32
    KMTQAITYPE_QUERY_ISBADDRIVERFORHWPROTECTIONDISABLED, // D3DKMT_ISBADDRIVERFORHWPROTECTIONDISABLED
    KMTQAITYPE_MULTIPLANEOVERLAY_SECONDARY_SUPPORT, // D3DKMT_MULTIPLANEOVERLAY_SECONDARY_SUPPORT
    KMTQAITYPE_INDEPENDENTFLIP_SECONDARY_SUPPORT, // D3DKMT_INDEPENDENTFLIP_SECONDARY_SUPPORT
    KMTQAITYPE_PANELFITTER_SUPPORT, // D3DKMT_PANELFITTER_SUPPORT // since WDDM2_1 // 40
    KMTQAITYPE_PHYSICALADAPTERPNPKEY, // D3DKMT_QUERY_PHYSICAL_ADAPTER_PNP_KEY // since WDDM2_2
    KMTQAITYPE_GETSEGMENTGROUPSIZE, // D3DKMT_SEGMENTGROUPSIZEINFO
    KMTQAITYPE_MPO3DDI_SUPPORT, // D3DKMT_MPO3DDI_SUPPORT
    KMTQAITYPE_HWDRM_SUPPORT, // D3DKMT_HWDRM_SUPPORT
    KMTQAITYPE_MPOKERNELCAPS_SUPPORT, // D3DKMT_MPOKERNELCAPS_SUPPORT
    KMTQAITYPE_MULTIPLANEOVERLAY_STRETCH_SUPPORT, // D3DKMT_MULTIPLANEOVERLAY_STRETCH_SUPPORT
    KMTQAITYPE_GET_DEVICE_VIDPN_OWNERSHIP_INFO, // D3DKMT_GET_DEVICE_VIDPN_OWNERSHIP_INFO
    KMTQAITYPE_QUERYREGISTRY, // D3DDDI_QUERYREGISTRY_INFO // since WDDM2_4
    KMTQAITYPE_KMD_DRIVER_VERSION, // D3DKMT_KMD_DRIVER_VERSION
    KMTQAITYPE_BLOCKLIST_KERNEL, // D3DKMT_BLOCKLIST_INFO // 50
    KMTQAITYPE_BLOCKLIST_RUNTIME, // D3DKMT_BLOCKLIST_INFO
    KMTQAITYPE_ADAPTERGUID_RENDER, // GUID
    KMTQAITYPE_ADAPTERADDRESS_RENDER, // D3DKMT_ADAPTERADDRESS
    KMTQAITYPE_ADAPTERREGISTRYINFO_RENDER, // D3DKMT_ADAPTERREGISTRYINFO
    KMTQAITYPE_CHECKDRIVERUPDATESTATUS_RENDER,
    KMTQAITYPE_DRIVERVERSION_RENDER, // D3DKMT_DRIVERVERSION
    KMTQAITYPE_ADAPTERTYPE_RENDER, // D3DKMT_ADAPTERTYPE
    KMTQAITYPE_WDDM_1_2_CAPS_RENDER, // D3DKMT_WDDM_1_2_CAPS
    KMTQAITYPE_WDDM_1_3_CAPS_RENDER, // D3DKMT_WDDM_1_3_CAPS
    KMTQAITYPE_QUERY_ADAPTER_UNIQUE_GUID, // D3DKMT_QUERY_ADAPTER_UNIQUE_GUID // 60
    KMTQAITYPE_NODEPERFDATA, // D3DKMT_NODE_PERFDATA
    KMTQAITYPE_ADAPTERPERFDATA, // D3DKMT_ADAPTER_PERFDATA
    KMTQAITYPE_ADAPTERPERFDATA_CAPS, // D3DKMT_ADAPTER_PERFDATACAPS
    KMTQUITYPE_GPUVERSION, // D3DKMT_GPUVERSION
    KMTQAITYPE_DRIVER_DESCRIPTION, // D3DKMT_DRIVER_DESCRIPTION // since WDDM2_6
    KMTQAITYPE_DRIVER_DESCRIPTION_RENDER, // D3DKMT_DRIVER_DESCRIPTION
    KMTQAITYPE_SCANOUT_CAPS, // D3DKMT_QUERY_SCANOUT_CAPS
    KMTQAITYPE_DISPLAY_UMDRIVERNAME,
    KMTQAITYPE_PARAVIRTUALIZATION_RENDER,
    KMTQAITYPE_SERVICENAME, // 70
    KMTQAITYPE_WDDM_2_7_CAPS, // D3DKMT_WDDM_2_7_CAPS
    KMTQAITYPE_TRACKEDWORKLOAD_SUPPORT
} KMTQUERYADAPTERINFOTYPE;

typedef enum _KMTUMDVERSION
{
    KMTUMDVERSION_DX9,
    KMTUMDVERSION_DX10,
    KMTUMDVERSION_DX11,
    KMTUMDVERSION_DX12,
    NUM_KMTUMDVERSIONS
} KMTUMDVERSION;

// The D3DKMT_UMDFILENAMEINFO structure contains the name of an OpenGL ICD that is based on the specified version of the DirectX runtime.
typedef struct _D3DKMT_UMDFILENAMEINFO
{
    _In_ KMTUMDVERSION Version; // A KMTUMDVERSION-typed value that indicates the version of the DirectX runtime to retrieve the name of an OpenGL ICD for.
    _Out_ WCHAR UmdFileName[MAX_PATH]; // A string that contains the name of the OpenGL ICD.
} D3DKMT_UMDFILENAMEINFO;

// The D3DKMT_OPENGLINFO structure describes OpenGL installable client driver (ICD) information.
typedef struct _D3DKMT_OPENGLINFO
{
    _Out_ WCHAR UmdOpenGlIcdFileName[MAX_PATH]; // An array of wide characters that contains the file name of the OpenGL ICD.
    _Out_ ULONG Version; // The version of the OpenGL ICD.
    _In_ ULONG Flags; // This member is currently unused.
} D3DKMT_OPENGLINFO;

// The D3DKMT_SEGMENTSIZEINFO structure describes the size, in bytes, of memory and aperture segments.
typedef struct _D3DKMT_SEGMENTSIZEINFO
{
    _Out_ ULONGLONG DedicatedVideoMemorySize; // The size, in bytes, of memory that is dedicated from video memory.
    _Out_ ULONGLONG DedicatedSystemMemorySize; // The size, in bytes, of memory that is dedicated from system memory.
    _Out_ ULONGLONG SharedSystemMemorySize; // The size, in bytes, of memory from system memory that can be shared by many users.
} D3DKMT_SEGMENTSIZEINFO;

// The D3DKMT_FLIPINFOFLAGS structure identifies flipping capabilities of the display miniport driver.
typedef struct _D3DKMT_FLIPINFOFLAGS 
{
    UINT32 FlipInterval : 1; // A UINT value that specifies whether the display miniport driver natively supports the scheduling of a flip command to take effect after two, three or four vertical syncs occur. 
    UINT32 Reserved : 31;
} D3DKMT_FLIPINFOFLAGS;

// The D3DKMT_FLIPQUEUEINFO structure describes information about the graphics adapter's queue of flip operations.
typedef struct _D3DKMT_FLIPQUEUEINFO 
{
    _Out_ UINT32 MaxHardwareFlipQueueLength; // The maximum number of flip operations that can be queued for hardware-flip queuing.
    _Out_ UINT32 MaxSoftwareFlipQueueLength; // The maximum number of flip operations that can be queued for software-flip queuing on hardware that supports memory mapped I/O (MMIO)-based flips.
    _Out_ D3DKMT_FLIPINFOFLAGS FlipFlags; // indicates, in bit-field flags, flipping capabilities.
} D3DKMT_FLIPQUEUEINFO;

// The D3DKMT_ADAPTERADDRESS structure describes the physical location of the graphics adapter.
typedef struct _D3DKMT_ADAPTERADDRESS 
{
    _Out_ UINT32 BusNumber; // The number of the bus that the graphics adapter's physical device is located on.
    _Out_ UINT32 DeviceNumber; // The index of the graphics adapter's physical device on the bus.
    _Out_ UINT32 FunctionNumber; // The function number of the graphics adapter on the physical device.
} D3DKMT_ADAPTERADDRESS;

typedef struct _D3DKMT_WORKINGSETFLAGS
{
    UINT32 UseDefault : 1; // A UINT value that specifies whether the display miniport driver uses the default working set.
    UINT32 Reserved : 31; // This member is reserved and should be set to zero.
} D3DKMT_WORKINGSETFLAGS;

// The D3DKMT_WORKINGSETINFO structure describes information about the graphics adapter's working set.
typedef struct _D3DKMT_WORKINGSETINFO
{
    _Out_ D3DKMT_WORKINGSETFLAGS Flags; // A D3DKMT_WORKINGSETFLAGS structure that indicates, in bit-field flags, working-set properties.
    _Out_ ULONG MinimumWorkingSetPercentile; // The minimum working-set percentile.
    _Out_ ULONG MaximumWorkingSetPercentile; // The maximum working-set percentile.
} D3DKMT_WORKINGSETINFO;

// The D3DKMT_ADAPTERREGISTRYINFO structure contains registry information about the graphics adapter.
typedef struct _D3DKMT_ADAPTERREGISTRYINFO 
{
    _Out_ WCHAR AdapterString[MAX_PATH]; // A string that contains the name of the graphics adapter.
    _Out_ WCHAR BiosString[MAX_PATH]; // A string that contains the name of the BIOS for the graphics adapter.
    _Out_ WCHAR DacType[MAX_PATH]; // A string that contains the DAC type for the graphics adapter.
    _Out_ WCHAR ChipType[MAX_PATH]; // A string that contains the chip type for the graphics adapter.
} D3DKMT_ADAPTERREGISTRYINFO;

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |       \
                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))

typedef enum _D3DDDIFORMAT
{
    D3DDDIFMT_UNKNOWN = 0,
    D3DDDIFMT_R8G8B8 = 20,
    D3DDDIFMT_A8R8G8B8 = 21,
    D3DDDIFMT_X8R8G8B8 = 22,
    D3DDDIFMT_R5G6B5 = 23,
    D3DDDIFMT_X1R5G5B5 = 24,
    D3DDDIFMT_A1R5G5B5 = 25,
    D3DDDIFMT_A4R4G4B4 = 26,
    D3DDDIFMT_R3G3B2 = 27,
    D3DDDIFMT_A8 = 28,
    D3DDDIFMT_A8R3G3B2 = 29,
    D3DDDIFMT_X4R4G4B4 = 30,
    D3DDDIFMT_A2B10G10R10 = 31,
    D3DDDIFMT_A8B8G8R8 = 32,
    D3DDDIFMT_X8B8G8R8 = 33,
    D3DDDIFMT_G16R16 = 34,
    D3DDDIFMT_A2R10G10B10 = 35,
    D3DDDIFMT_A16B16G16R16 = 36,
    D3DDDIFMT_A8P8 = 40,
    D3DDDIFMT_P8 = 41,
    D3DDDIFMT_L8 = 50,
    D3DDDIFMT_A8L8 = 51,
    D3DDDIFMT_A4L4 = 52,
    D3DDDIFMT_V8U8 = 60,
    D3DDDIFMT_L6V5U5 = 61,
    D3DDDIFMT_X8L8V8U8 = 62,
    D3DDDIFMT_Q8W8V8U8 = 63,
    D3DDDIFMT_V16U16 = 64,
    D3DDDIFMT_W11V11U10 = 65,
    D3DDDIFMT_A2W10V10U10 = 67,

    D3DDDIFMT_UYVY = MAKEFOURCC('U', 'Y', 'V', 'Y'),
    D3DDDIFMT_R8G8_B8G8 = MAKEFOURCC('R', 'G', 'B', 'G'),
    D3DDDIFMT_YUY2 = MAKEFOURCC('Y', 'U', 'Y', '2'),
    D3DDDIFMT_G8R8_G8B8 = MAKEFOURCC('G', 'R', 'G', 'B'),
    D3DDDIFMT_DXT1 = MAKEFOURCC('D', 'X', 'T', '1'),
    D3DDDIFMT_DXT2 = MAKEFOURCC('D', 'X', 'T', '2'),
    D3DDDIFMT_DXT3 = MAKEFOURCC('D', 'X', 'T', '3'),
    D3DDDIFMT_DXT4 = MAKEFOURCC('D', 'X', 'T', '4'),
    D3DDDIFMT_DXT5 = MAKEFOURCC('D', 'X', 'T', '5'),

    D3DDDIFMT_D16_LOCKABLE = 70,
    D3DDDIFMT_D32 = 71,
    D3DDDIFMT_D15S1 = 73,
    D3DDDIFMT_D24S8 = 75,
    D3DDDIFMT_D24X8 = 77,
    D3DDDIFMT_D24X4S4 = 79,
    D3DDDIFMT_D16 = 80,
    D3DDDIFMT_D32F_LOCKABLE = 82,
    D3DDDIFMT_D24FS8 = 83,
    D3DDDIFMT_D32_LOCKABLE = 84,
    D3DDDIFMT_S8_LOCKABLE = 85,
    D3DDDIFMT_S1D15 = 72,
    D3DDDIFMT_S8D24 = 74,
    D3DDDIFMT_X8D24 = 76,
    D3DDDIFMT_X4S4D24 = 78,
    D3DDDIFMT_L16 = 81,
    D3DDDIFMT_G8R8 = 91, // WDDM1_3
    D3DDDIFMT_R8 = 92, // WDDM1_3
    D3DDDIFMT_VERTEXDATA = 100,
    D3DDDIFMT_INDEX16 = 101,
    D3DDDIFMT_INDEX32 = 102,
    D3DDDIFMT_Q16W16V16U16 = 110,

    D3DDDIFMT_MULTI2_ARGB8 = MAKEFOURCC('M', 'E', 'T', '1'),

    // Floating point surface formats

    // s10e5 formats (16-bits per channel)
    D3DDDIFMT_R16F = 111,
    D3DDDIFMT_G16R16F = 112,
    D3DDDIFMT_A16B16G16R16F = 113,

    // IEEE s23e8 formats (32-bits per channel)
    D3DDDIFMT_R32F = 114,
    D3DDDIFMT_G32R32F = 115,
    D3DDDIFMT_A32B32G32R32F = 116,

    D3DDDIFMT_CxV8U8 = 117,

    // Monochrome 1 bit per pixel format
    D3DDDIFMT_A1 = 118,

    // 2.8 biased fixed point
    D3DDDIFMT_A2B10G10R10_XR_BIAS = 119,

    // Decode compressed buffer formats
    D3DDDIFMT_DXVACOMPBUFFER_BASE = 150,
    D3DDDIFMT_PICTUREPARAMSDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0,    // 150
    D3DDDIFMT_MACROBLOCKDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE + 1,    // 151
    D3DDDIFMT_RESIDUALDIFFERENCEDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE + 2,    // 152
    D3DDDIFMT_DEBLOCKINGDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE + 3,    // 153
    D3DDDIFMT_INVERSEQUANTIZATIONDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE + 4,    // 154
    D3DDDIFMT_SLICECONTROLDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE + 5,    // 155
    D3DDDIFMT_BITSTREAMDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE + 6,    // 156
    D3DDDIFMT_MOTIONVECTORBUFFER = D3DDDIFMT_DXVACOMPBUFFER_BASE + 7,    // 157
    D3DDDIFMT_FILMGRAINBUFFER = D3DDDIFMT_DXVACOMPBUFFER_BASE + 8,    // 158
    D3DDDIFMT_DXVA_RESERVED9 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 9,    // 159
    D3DDDIFMT_DXVA_RESERVED10 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 10,   // 160
    D3DDDIFMT_DXVA_RESERVED11 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 11,   // 161
    D3DDDIFMT_DXVA_RESERVED12 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 12,   // 162
    D3DDDIFMT_DXVA_RESERVED13 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 13,   // 163
    D3DDDIFMT_DXVA_RESERVED14 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 14,   // 164
    D3DDDIFMT_DXVA_RESERVED15 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 15,   // 165
    D3DDDIFMT_DXVA_RESERVED16 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 16,   // 166
    D3DDDIFMT_DXVA_RESERVED17 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 17,   // 167
    D3DDDIFMT_DXVA_RESERVED18 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 18,   // 168
    D3DDDIFMT_DXVA_RESERVED19 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 19,   // 169
    D3DDDIFMT_DXVA_RESERVED20 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 20,   // 170
    D3DDDIFMT_DXVA_RESERVED21 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 21,   // 171
    D3DDDIFMT_DXVA_RESERVED22 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 22,   // 172
    D3DDDIFMT_DXVA_RESERVED23 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 23,   // 173
    D3DDDIFMT_DXVA_RESERVED24 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 24,   // 174
    D3DDDIFMT_DXVA_RESERVED25 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 25,   // 175
    D3DDDIFMT_DXVA_RESERVED26 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 26,   // 176
    D3DDDIFMT_DXVA_RESERVED27 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 27,   // 177
    D3DDDIFMT_DXVA_RESERVED28 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 28,   // 178
    D3DDDIFMT_DXVA_RESERVED29 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 29,   // 179
    D3DDDIFMT_DXVA_RESERVED30 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 30,   // 180
    D3DDDIFMT_DXVA_RESERVED31 = D3DDDIFMT_DXVACOMPBUFFER_BASE + 31,   // 181
    D3DDDIFMT_DXVACOMPBUFFER_MAX = D3DDDIFMT_DXVA_RESERVED31,

    D3DDDIFMT_BINARYBUFFER = 199,

    D3DDDIFMT_FORCE_UINT = 0x7fffffff
} D3DDDIFORMAT;

typedef struct _D3DDDI_RATIONAL
{
    UINT32 Numerator;
    UINT32 Denominator;
} D3DDDI_RATIONAL;

typedef enum _D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING
{
    D3DDDI_VSSLO_UNINITIALIZED = 0,
    D3DDDI_VSSLO_PROGRESSIVE = 1,
    D3DDDI_VSSLO_INTERLACED_UPPERFIELDFIRST = 2,
    D3DDDI_VSSLO_INTERLACED_LOWERFIELDFIRST = 3,
    D3DDDI_VSSLO_OTHER = 255
} D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING;

typedef enum _D3DDDI_ROTATION
{
    D3DDDI_ROTATION_IDENTITY = 1, // No rotation.
    D3DDDI_ROTATION_90 = 2, // Rotated 90 degrees.
    D3DDDI_ROTATION_180 = 3, // Rotated 180 degrees.
    D3DDDI_ROTATION_270 = 4 // Rotated 270 degrees.
} D3DDDI_ROTATION;
#endif

typedef enum _D3DKMDT_MODE_PRUNING_REASON
{
    D3DKMDT_MPR_UNINITIALIZED = 0, // mode was pruned or is supported because of:
    D3DKMDT_MPR_ALLCAPS = 1, //   all of the monitor caps (only used to imply lack of support - for support, specific reason is always indicated)
    D3DKMDT_MPR_DESCRIPTOR_MONITOR_SOURCE_MODE = 2, //   monitor source mode in the monitor descriptor
    D3DKMDT_MPR_DESCRIPTOR_MONITOR_FREQUENCY_RANGE = 3, //   monitor frequency range in the monitor descriptor
    D3DKMDT_MPR_DESCRIPTOR_OVERRIDE_MONITOR_SOURCE_MODE = 4, //   monitor source mode in the monitor descriptor override
    D3DKMDT_MPR_DESCRIPTOR_OVERRIDE_MONITOR_FREQUENCY_RANGE = 5, //   monitor frequency range in the monitor descriptor override
    D3DKMDT_MPR_DEFAULT_PROFILE_MONITOR_SOURCE_MODE = 6, //   monitor source mode in the default monitor profile
    D3DKMDT_MPR_DRIVER_RECOMMENDED_MONITOR_SOURCE_MODE = 7, //   monitor source mode recommended by the driver
    D3DKMDT_MPR_MONITOR_FREQUENCY_RANGE_OVERRIDE = 8, //   monitor frequency range override
    D3DKMDT_MPR_CLONE_PATH_PRUNED = 9, //   Mode is pruned because other path(s) in clone cluster has(have) no mode supported by monitor
    D3DKMDT_MPR_MAXVALID = 10
} D3DKMDT_MODE_PRUNING_REASON;

// This structure takes 8 bytes.
// The unnamed UINT of size 0 forces alignment of the structure to
// make it exactly occupy 8 bytes, see MSDN docs on C++ bitfields
// for more details
typedef struct _D3DKMDT_DISPLAYMODE_FLAGS
{
    UINT32 ValidatedAgainstMonitorCaps : 1;
    UINT32 RoundedFakeMode : 1;
    UINT32 : 0;
    D3DKMDT_MODE_PRUNING_REASON ModePruningReason : 4;
    UINT32 Stereo : 1; // since WIN8
    UINT32 AdvancedScanCapable : 1;
    UINT32 PreferredTiming : 1; // since WDDM2_0
    UINT32 PhysicalModeSupported : 1;
    UINT32 Reserved : 24;
} D3DKMDT_DISPLAYMODE_FLAGS;

// The D3DKMT_DISPLAYMODE structure describes a display mode.
typedef struct _D3DKMT_DISPLAYMODE 
{
    _Out_ UINT32 Width; // The screen width of the display mode, in pixels.
    _Out_ UINT32 Height; // The screen height of the display mode, in pixels.
    _Out_ D3DDDIFORMAT Format; // A D3DDDIFORMAT-typed value that indicates the pixel format of the display mode.
    _Out_ UINT32 IntegerRefreshRate; // A UINT value that indicates the refresh rate of the display mode.
    _Out_ D3DDDI_RATIONAL RefreshRate; // A D3DDDI_RATIONAL structure that indicates the refresh rate of the display mode.
    _Out_ D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING ScanLineOrdering; // A D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING-typed value that indicates how scan lines are ordered in the display mode.
    _Out_ D3DDDI_ROTATION DisplayOrientation; // A D3DDDI_ROTATION-typed value that identifies the orientation of the display mode.
    _Out_ UINT32 DisplayFixedOutput; // The fixed output of the display mode.
    _Out_ D3DKMDT_DISPLAYMODE_FLAGS Flags; // A D3DKMDT_DISPLAYMODE_FLAGS structure that indicates information about the display mode.
} D3DKMT_DISPLAYMODE;

// The D3DKMT_CURRENTDISPLAYMODE structure describes the current display mode of the specified video source.
typedef struct _D3DKMT_CURRENTDISPLAYMODE
{
    _In_ UINT32 VidPnSourceId; // The zero-based identification number of the video present source in a path of a video present network (VidPN) topology that the display mode applies to.
    _Out_ D3DKMT_DISPLAYMODE DisplayMode; // A D3DKMT_DISPLAYMODE structure that represents the current display mode.
} D3DKMT_CURRENTDISPLAYMODE;

// private
typedef struct _D3DKMT_VIRTUALADDRESSFLAGS
{
    UINT32 VirtualAddressSupported : 1;
    UINT32 Reserved : 31;
} D3DKMT_VIRTUALADDRESSFLAGS;

// private
typedef struct _D3DKMT_VIRTUALADDRESSINFO
{
    D3DKMT_VIRTUALADDRESSFLAGS VirtualAddressFlags;
} D3DKMT_VIRTUALADDRESSINFO;

// The D3DKMT_DRIVERVERSION enumeration type contains values that indicate the version of the display driver model that the display miniport driver supports.
typedef enum D3DKMT_DRIVERVERSION // QAI_DRIVERVERSION
{
    KMT_DRIVERVERSION_WDDM_1_0 = 1000, // The display miniport driver supports the Windows Vista display driver model (WDDM) without Windows 7 features.
    KMT_DRIVERVERSION_WDDM_1_1_PRERELEASE = 1102, // The display miniport driver supports the Windows Vista display driver model with prereleased Windows 7 features.
    KMT_DRIVERVERSION_WDDM_1_1 = 1105, // The display miniport driver supports the Windows Vista display driver model with released Windows 7 features.
    KMT_DRIVERVERSION_WDDM_1_2 = 1200, // The display miniport driver supports the Windows Vista display driver model with released Windows 8 features. Supported starting with Windows 8.
    KMT_DRIVERVERSION_WDDM_1_3 = 1300, // The display miniport driver supports the Windows display driver model with released Windows 8.1 features. Supported starting with Windows 8.1.
    KMT_DRIVERVERSION_WDDM_2_0 = 2000, // The display miniport driver supports the Windows display driver model with released Windows 10 features. Supported starting with Windows 10.
    KMT_DRIVERVERSION_WDDM_2_1 = 2100, // 1607
    KMT_DRIVERVERSION_WDDM_2_2 = 2200, // 1703
    KMT_DRIVERVERSION_WDDM_2_3 = 2300, // 1709
    KMT_DRIVERVERSION_WDDM_2_4 = 2400, // 1803
    KMT_DRIVERVERSION_WDDM_2_5 = 2500, // 1809
    KMT_DRIVERVERSION_WDDM_2_6 = 2600, // 19H1
    KMT_DRIVERVERSION_WDDM_2_7 = 2700 // 20H1
} D3DKMT_DRIVERVERSION;

// Specifies the type of display device that the graphics adapter supports.
typedef struct _D3DKMT_ADAPTERTYPE
{
    union
    {
        struct
        {
            UINT32 RenderSupported : 1;
            UINT32 DisplaySupported : 1;
            UINT32 SoftwareDevice : 1;
            UINT32 PostDevice : 1;
            UINT32 HybridDiscrete : 1; // since WDDM1_3
            UINT32 HybridIntegrated : 1;
            UINT32 IndirectDisplayDevice : 1;
            UINT32 Paravirtualized : 1; // since WDDM2_3
            UINT32 ACGSupported : 1;
            UINT32 SupportSetTimingsFromVidPn : 1;
            UINT32 Detachable : 1;
            UINT32 ComputeOnly : 1; // since WDDM2_7
            UINT32 Prototype : 1;
            UINT32 Reserved : 19;
        };
        UINT32 Value;
    };
} D3DKMT_ADAPTERTYPE;

// Specifies the number of current Desktop Duplication API (DDA) clients that are attached to a given video present network (VidPN).
typedef struct _D3DKMT_OUTPUTDUPLCONTEXTSCOUNT
{
    UINT32 VidPnSourceId; // The ID of the video present network (VidPN).
    UINT32 OutputDuplicationCount; // The number of current DDA clients that are attached to the VidPN specified by the VidPnSourceId member.
} D3DKMT_OUTPUTDUPLCONTEXTSCOUNT;

typedef enum _D3DKMDT_GRAPHICS_PREEMPTION_GRANULARITY
{
    D3DKMDT_GRAPHICS_PREEMPTION_NONE = 0,
    D3DKMDT_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY = 100,
    D3DKMDT_GRAPHICS_PREEMPTION_PRIMITIVE_BOUNDARY = 200,
    D3DKMDT_GRAPHICS_PREEMPTION_TRIANGLE_BOUNDARY = 300,
    D3DKMDT_GRAPHICS_PREEMPTION_PIXEL_BOUNDARY = 400,
    D3DKMDT_GRAPHICS_PREEMPTION_SHADER_BOUNDARY = 500,
} D3DKMDT_GRAPHICS_PREEMPTION_GRANULARITY;

typedef enum _D3DKMDT_COMPUTE_PREEMPTION_GRANULARITY
{
    D3DKMDT_COMPUTE_PREEMPTION_NONE = 0,
    D3DKMDT_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY = 100,
    D3DKMDT_COMPUTE_PREEMPTION_DISPATCH_BOUNDARY = 200,
    D3DKMDT_COMPUTE_PREEMPTION_THREAD_GROUP_BOUNDARY = 300,
    D3DKMDT_COMPUTE_PREEMPTION_THREAD_BOUNDARY = 400,
    D3DKMDT_COMPUTE_PREEMPTION_SHADER_BOUNDARY = 500,
} D3DKMDT_COMPUTE_PREEMPTION_GRANULARITY;

typedef struct _D3DKMDT_PREEMPTION_CAPS
{
    D3DKMDT_GRAPHICS_PREEMPTION_GRANULARITY GraphicsPreemptionGranularity;
    D3DKMDT_COMPUTE_PREEMPTION_GRANULARITY ComputePreemptionGranularity;
} D3DKMDT_PREEMPTION_CAPS;

typedef struct _D3DKMT_WDDM_1_2_CAPS
{
    D3DKMDT_PREEMPTION_CAPS PreemptionCaps;
    union
    {
        struct
        {
            UINT32 SupportNonVGA : 1;
            UINT32 SupportSmoothRotation : 1;
            UINT32 SupportPerEngineTDR : 1;
            UINT32 SupportKernelModeCommandBuffer : 1;
            UINT32 SupportCCD : 1;
            UINT32 SupportSoftwareDeviceBitmaps : 1;
            UINT32 SupportGammaRamp : 1;
            UINT32 SupportHWCursor : 1;
            UINT32 SupportHWVSync : 1;
            UINT32 SupportSurpriseRemovalInHibernation : 1;
            UINT32 Reserved : 22;
        };
        UINT32 Value;
    };
} D3DKMT_WDDM_1_2_CAPS;

// Indicates the version number of the user-mode driver.
typedef struct _D3DKMT_UMD_DRIVER_VERSION 
{
    LARGE_INTEGER DriverVersion; // The user-mode driver version.
} D3DKMT_UMD_DRIVER_VERSION;

// Indicates whether the user-mode driver supports Direct Flip operations, in which video memory is seamlessly flipped between an application's managed primary allocations and the Desktop Window Manager (DWM) managed primary allocations.
typedef struct _D3DKMT_DIRECTFLIP_SUPPORT
{
    BOOL Supported; // If TRUE, the driver supports Direct Flip operations. Otherwise, the driver does not support Direct Flip operations.
} D3DKMT_DIRECTFLIP_SUPPORT;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_SUPPORT
{
    BOOL Supported;
} D3DKMT_MULTIPLANEOVERLAY_SUPPORT;

typedef struct _D3DKMT_DLIST_DRIVER_NAME
{
    _Out_ WCHAR DListFileName[MAX_PATH]; // DList driver file name
} D3DKMT_DLIST_DRIVER_NAME;

typedef struct _D3DKMT_WDDM_1_3_CAPS
{
    union
    {
        struct
        {
            UINT32 SupportMiracast : 1;
            UINT32 IsHybridIntegratedGPU : 1;
            UINT32 IsHybridDiscreteGPU : 1;
            UINT32 SupportPowerManagementPStates : 1;
            UINT32 SupportVirtualModes : 1;
            UINT32 SupportCrossAdapterResource : 1;
            UINT32 Reserved : 26;
        };
        UINT32 Value;
    };
} D3DKMT_WDDM_1_3_CAPS;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_HUD_SUPPORT
{
    UINT32 VidPnSourceId; // Not yet used.
    BOOL Update;
    BOOL KernelSupported;
    BOOL HudSupported;
} D3DKMT_MULTIPLANEOVERLAY_HUD_SUPPORT;

typedef struct _D3DKMT_WDDM_2_0_CAPS
{
    union
    {
        struct
        {
            UINT32 Support64BitAtomics : 1;
            UINT32 GpuMmuSupported : 1;
            UINT32 IoMmuSupported : 1;
            UINT32 FlipOverwriteSupported : 1; // since WDDM2_4
            UINT32 SupportContextlessPresent : 1;
            UINT32 SupportSurpriseRemoval : 1; // since WDDM2_7
            UINT32 Reserved : 26;
        };
        UINT32 Value;
    };
} D3DKMT_WDDM_2_0_CAPS;

#include <pshpack1.h>

#define DXGK_MAX_METADATA_NAME_LENGTH 32

typedef enum _DXGK_ENGINE_TYPE
{
    DXGK_ENGINE_TYPE_OTHER = 0, // This value is used for proprietary or unique functionality that is not exposed by typical adapters, as well as for an engine that performs work that doesn't fall under another category.
    DXGK_ENGINE_TYPE_3D = 1, // The adapter's 3-D processing engine. All adapters that are not a display-only device have one 3-D engine.
    DXGK_ENGINE_TYPE_VIDEO_DECODE = 2, // The engine that handles video decoding, including decompression of video frames from an input stream into typical YUV surfaces. The workload packets for an H.264 video codec workload test must appear on either the decode engine or the 3-D engine.
    DXGK_ENGINE_TYPE_VIDEO_ENCODE = 3, // The engine that handles video encoding, including compression of typical video frames into an encoded video format.
    DXGK_ENGINE_TYPE_VIDEO_PROCESSING = 4, // The engine that is responsible for any video processing that is done after a video input stream is decoded. Such processing can include RGB surface conversion, filtering, stretching, color correction, deinterlacing, or other steps that are required before the final image is rendered to the display screen. The workload packets for workload tests must appear on either the video processing engine or the 3-D engine.
    DXGK_ENGINE_TYPE_SCENE_ASSEMBLY = 5, // The engine that performs vertex processing of 3-D workloads as a preliminary pass prior to the remainder of the 3-D rendering. This engine also stores vertices in bins that tile-based rendering engines use.
    DXGK_ENGINE_TYPE_COPY = 6, // The engine that is a copy engine used for moving data. This engine can perform subresource updates, blitting, paging, or other similar data handling. The workload packets for calls to CopySubresourceRegion or UpdateSubResource methods of Direct3D 10 and Direct3D 11 must appear on either the copy engine or the 3-D engine.
    DXGK_ENGINE_TYPE_OVERLAY = 7, // The virtual engine that is used for synchronized flipping of overlays in Direct3D 9.
    DXGK_ENGINE_TYPE_CRYPTO,
    DXGK_ENGINE_TYPE_MAX
} DXGK_ENGINE_TYPE;

typedef struct _DXGK_NODEMETADATA_FLAGS
{
    union
    {
        struct
        {
            UINT32 ContextSchedulingSupported : 1;
            UINT32 RingBufferFenceRelease : 1;
            UINT32 SupportTrackedWorkload : 1;
            UINT32 Reserved : 13;
            UINT32 MaxInFlightHwQueueBuffers : 16;
        };
        UINT32 Value;
    };
} DXGK_NODEMETADATA_FLAGS;

typedef struct _DXGK_NODEMETADATA
{
    DXGK_ENGINE_TYPE EngineType;
    WCHAR FriendlyName[DXGK_MAX_METADATA_NAME_LENGTH];
    DXGK_NODEMETADATA_FLAGS Flags;
    BOOLEAN GpuMmuSupported;
    BOOLEAN IoMmuSupported;
} DXGK_NODEMETADATA;

typedef DXGK_NODEMETADATA DXGKARG_GETNODEMETADATA;

typedef struct _D3DKMT_NODEMETADATA
{
    _In_ UINT32 NodeOrdinalAndAdapterIndex;
    _Out_ DXGK_NODEMETADATA NodeData;
} D3DKMT_NODEMETADATA;

#include <poppack.h>

typedef struct _D3DKMT_CPDRIVERNAME
{
    WCHAR ContentProtectionFileName[MAX_PATH];
} D3DKMT_CPDRIVERNAME;

typedef struct _D3DKMT_XBOX
{
    BOOL IsXBOX;
} D3DKMT_XBOX;

typedef struct _D3DKMT_INDEPENDENTFLIP_SUPPORT
{
    BOOL Supported;
} D3DKMT_INDEPENDENTFLIP_SUPPORT;

typedef struct _D3DKMT_MIRACASTCOMPANIONDRIVERNAME
{
    WCHAR MiracastCompanionDriverName[MAX_PATH];
} D3DKMT_MIRACASTCOMPANIONDRIVERNAME;

typedef struct _D3DKMT_PHYSICAL_ADAPTER_COUNT
{
    UINT32 Count;
} D3DKMT_PHYSICAL_ADAPTER_COUNT;

typedef struct _D3DKMT_DEVICE_IDS
{
    UINT32 VendorID;
    UINT32 DeviceID;
    UINT32 SubVendorID;
    UINT32 SubSystemID;
    UINT32 RevisionID;
    UINT32 BusType;
} D3DKMT_DEVICE_IDS;

typedef struct _D3DKMT_QUERY_DEVICE_IDS
{
    _In_ UINT32 PhysicalAdapterIndex;
    _Out_ D3DKMT_DEVICE_IDS DeviceIds;
} D3DKMT_QUERY_DEVICE_IDS;

typedef struct _D3DKMT_DRIVERCAPS_EXT
{
    union
    {
        struct
        {
            UINT32 VirtualModeSupport : 1;
            UINT32 Reserved : 31;
        };
        UINT32 Value;
    };
} D3DKMT_DRIVERCAPS_EXT;

typedef enum _D3DKMT_MIRACAST_DRIVER_TYPE
{
    D3DKMT_MIRACAST_DRIVER_NOT_SUPPORTED = 0,
    D3DKMT_MIRACAST_DRIVER_IHV = 1,
    D3DKMT_MIRACAST_DRIVER_MS = 2,
} D3DKMT_MIRACAST_DRIVER_TYPE;

typedef struct _D3DKMT_QUERY_MIRACAST_DRIVER_TYPE
{
    D3DKMT_MIRACAST_DRIVER_TYPE MiracastDriverType;
} D3DKMT_QUERY_MIRACAST_DRIVER_TYPE;

typedef struct _D3DKMT_GPUMMU_CAPS
{
    union
    {
        struct
        {
            UINT32 ReadOnlyMemorySupported : 1;
            UINT32 NoExecuteMemorySupported : 1;
            UINT32 CacheCoherentMemorySupported : 1;
            UINT32 Reserved : 29;
        };
        UINT32 Value;
    } Flags;
    UINT32 VirtualAddressBitCount;
} D3DKMT_GPUMMU_CAPS;

typedef struct _D3DKMT_QUERY_GPUMMU_CAPS
{
    _In_ UINT32 PhysicalAdapterIndex;
    _Out_ D3DKMT_GPUMMU_CAPS Caps;
} D3DKMT_QUERY_GPUMMU_CAPS;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_DECODE_SUPPORT
{
    BOOL Supported;
} D3DKMT_MULTIPLANEOVERLAY_DECODE_SUPPORT;

typedef struct _D3DKMT_ISBADDRIVERFORHWPROTECTIONDISABLED
{
    BOOL Disabled;
} D3DKMT_ISBADDRIVERFORHWPROTECTIONDISABLED;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_SECONDARY_SUPPORT
{
    BOOL Supported;
} D3DKMT_MULTIPLANEOVERLAY_SECONDARY_SUPPORT;

typedef struct _D3DKMT_INDEPENDENTFLIP_SECONDARY_SUPPORT
{
    BOOL Supported;
} D3DKMT_INDEPENDENTFLIP_SECONDARY_SUPPORT;

typedef struct _D3DKMT_PANELFITTER_SUPPORT
{
    BOOL Supported;
} D3DKMT_PANELFITTER_SUPPORT;

typedef enum _D3DKMT_PNP_KEY_TYPE
{
    D3DKMT_PNP_KEY_HARDWARE = 1,
    D3DKMT_PNP_KEY_SOFTWARE = 2
} D3DKMT_PNP_KEY_TYPE;

// A structure that holds information to query the physical adapter PNP key.
typedef struct _D3DKMT_QUERY_PHYSICAL_ADAPTER_PNP_KEY
{
    _In_ UINT32 PhysicalAdapterIndex; // The physical adapter index.
    _In_ D3DKMT_PNP_KEY_TYPE PnPKeyType; // The type of the PNP key being queried.
    _Field_size_opt_(*pCchDest) WCHAR *pDest; // A WCHAR value respresenting the pDest.
    _Inout_ UINT32 *pCchDest; // A UINT value representing the pCchDest.
} D3DKMT_QUERY_PHYSICAL_ADAPTER_PNP_KEY;

// A structure that holds information about the segment group size.
typedef struct _D3DKMT_SEGMENTGROUPSIZEINFO
{
    _In_ UINT32 PhysicalAdapterIndex; // An index to the physical adapter.
    _Out_ D3DKMT_SEGMENTSIZEINFO LegacyInfo; // Legacy segment size info.
    _Out_ ULONGLONG LocalMemory; // The size of local memory.
    _Out_ ULONGLONG NonLocalMemory; // The size of non-local memory.
    _Out_ ULONGLONG NonBudgetMemory; // The size of non-budget memory.
} D3DKMT_SEGMENTGROUPSIZEINFO;

// A structure that holds the support status.
typedef struct _D3DKMT_MPO3DDI_SUPPORT
{
    BOOL Supported; // Indicates whether support exists.
} D3DKMT_MPO3DDI_SUPPORT;

typedef struct _D3DKMT_HWDRM_SUPPORT
{
    BOOLEAN Supported;
} D3DKMT_HWDRM_SUPPORT;

typedef struct _D3DKMT_MPOKERNELCAPS_SUPPORT
{
    BOOL Supported;
} D3DKMT_MPOKERNELCAPS_SUPPORT;

typedef struct _D3DKMT_MULTIPLANEOVERLAY_STRETCH_SUPPORT
{
    UINT32 VidPnSourceId;
    BOOL Update;
    BOOL Supported;
} D3DKMT_MULTIPLANEOVERLAY_STRETCH_SUPPORT;

typedef struct _D3DKMT_GET_DEVICE_VIDPN_OWNERSHIP_INFO
{
    _In_ D3DKMT_HANDLE hDevice; // Indentifies the device
    _Out_ BOOLEAN bFailedDwmAcquireVidPn; // True if Dwm Acquire VidPn failed due to another Dwm device having ownership
} D3DKMT_GET_DEVICE_VIDPN_OWNERSHIP_INFO;

typedef struct _D3DDDI_QUERYREGISTRY_FLAGS
{
    union
    {
        struct
        {
            UINT32 TranslatePath : 1;
            UINT32 MutableValue : 1;
            UINT32 Reserved : 30;
        };
        UINT32 Value;
    };
} D3DDDI_QUERYREGISTRY_FLAGS;

typedef enum _D3DDDI_QUERYREGISTRY_TYPE
{
    D3DDDI_QUERYREGISTRY_SERVICEKEY = 0, // HKLM\System\CurrentControlSet\Services\nvlddmkm
    D3DDDI_QUERYREGISTRY_ADAPTERKEY = 1, // HKLM\System\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000
    D3DDDI_QUERYREGISTRY_DRIVERSTOREPATH = 2,
    D3DDDI_QUERYREGISTRY_DRIVERIMAGEPATH = 3, // REDSTONE5
    D3DDDI_QUERYREGISTRY_MAX,
} D3DDDI_QUERYREGISTRY_TYPE;

typedef enum _D3DDDI_QUERYREGISTRY_STATUS
{
    D3DDDI_QUERYREGISTRY_STATUS_SUCCESS = 0,
    D3DDDI_QUERYREGISTRY_STATUS_BUFFER_OVERFLOW = 1,
    D3DDDI_QUERYREGISTRY_STATUS_FAIL = 2,
    D3DDDI_QUERYREGISTRY_STATUS_MAX,
} D3DDDI_QUERYREGISTRY_STATUS;

// Contains information about the query registry.
// PrivateDriverSize must be sizeof(D3DDDI_QUERYREGISTRY_INFO) + (size of the the key value in bytes)
typedef struct _D3DDDI_QUERYREGISTRY_INFO
{
    _In_ D3DDDI_QUERYREGISTRY_TYPE QueryType;
    _In_ D3DDDI_QUERYREGISTRY_FLAGS QueryFlags;
    _In_ WCHAR ValueName[MAX_PATH]; // The name of the registry value.
    _In_ ULONG ValueType; // REG_XX types (https://msdn.microsoft.com/en-us/library/windows/desktop/ms724884.aspx)
    _In_ ULONG PhysicalAdapterIndex;   // The physical adapter index in a LDA chain.
    _Out_ ULONG OutputValueSize;// Number of bytes written to the output value or required in case of D3DDDI_QUERYREGISTRY_STATUS_BUFFER_OVERFLOW.
    _Out_ D3DDDI_QUERYREGISTRY_STATUS Status;
    union
    {
        _Out_ ULONG OutputDword;
        _Out_ UINT64 OutputQword;
        _Out_ WCHAR OutputString[1];
        _Out_ BYTE OutputBinary[1];
    };
} D3DDDI_QUERYREGISTRY_INFO;

// Contains the kernel mode driver version.
typedef struct _D3DKMT_KMD_DRIVER_VERSION
{
    LARGE_INTEGER DriverVersion; // The driver version.
} D3DKMT_KMD_DRIVER_VERSION;

typedef struct _D3DKMT_BLOCKLIST_INFO
{
    UINT32 Size; // The size of the block list.
    WCHAR BlockList[1]; // The block list.
} D3DKMT_BLOCKLIST_INFO;

// Used to query for a unique guid.
typedef struct _D3DKMT_QUERY_ADAPTER_UNIQUE_GUID
{
    WCHAR AdapterUniqueGUID[40];
} D3DKMT_QUERY_ADAPTER_UNIQUE_GUID;

// Represents performance data collected per engine from an adapter on an interval basis.
typedef struct _D3DKMT_NODE_PERFDATA
{
    _In_ UINT32 NodeOrdinal; // Node ordinal of the requested engine.
    _In_ UINT32 PhysicalAdapterIndex; // The physical adapter index in a LDA chain.
    _Out_ ULONGLONG Frequency; // Clock frequency of the requested engine, represented in hertz.
    _Out_ ULONGLONG MaxFrequency; // The max frequency the engine can normally reach in hertz while not overclocked.
    _Out_ ULONGLONG MaxFrequencyOC; // The max frequency the engine can reach with it�s current overclock in hertz.
    _Out_ ULONG Voltage; // Voltage of the engine in milli volts mV
    _Out_ ULONG VoltageMax; // The max voltage of the engine in milli volts while not overclocked.
    _Out_ ULONG VoltageMaxOC; // The max voltage of the engine while overclocked in milli volts.
    _Out_ ULONGLONG MaxTransitionLatency; // Max transition latency to change the frequency in 100 nanoseconds // REDSTONE5
} D3DKMT_NODE_PERFDATA;

// Represents performance data collected per adapter on an interval basis.
typedef struct _D3DKMT_ADAPTER_PERFDATA
{
    _In_ UINT32 PhysicalAdapterIndex; // The physical adapter index in a LDA chain.
    _Out_ ULONGLONG MemoryFrequency; // Clock frequency of the memory in hertz
    _Out_ ULONGLONG MaxMemoryFrequency; // Max clock frequency of the memory while not overclocked, represented in hertz.
    _Out_ ULONGLONG MaxMemoryFrequencyOC; // Clock frequency of the memory while overclocked in hertz.
    _Out_ ULONGLONG MemoryBandwidth; // Amount of memory transferred in bytes
    _Out_ ULONGLONG PCIEBandwidth; // Amount of memory transferred over PCI-E in bytes
    _Out_ ULONG FanRPM; // Fan rpm
    _Out_ ULONG Power; // Power draw of the adapter in tenths of a percentage
    _Out_ ULONG Temperature; // Temperature in deci-Celsius 1 = 0.1C
    _Out_ UCHAR PowerStateOverride; // Overrides dxgkrnls power view of linked adapters.
} D3DKMT_ADAPTER_PERFDATA;

// Represents data capabilities that are static and queried once per GPU during initialization.
typedef struct _D3DKMT_ADAPTER_PERFDATACAPS
{
    _In_ UINT32 PhysicalAdapterIndex; // The physical adapter index in a LDA chain.
    _Out_ ULONGLONG MaxMemoryBandwidth; // Max memory bandwidth in bytes for 1 second
    _Out_ ULONGLONG MaxPCIEBandwidth; // Max pcie bandwidth in bytes for 1 second
    _Out_ ULONG MaxFanRPM; // Max fan rpm
    _Out_ ULONG TemperatureMax; // Max temperature before damage levels
    _Out_ ULONG TemperatureWarning; // The temperature level where throttling begins.
} D3DKMT_ADAPTER_PERFDATACAPS;

#define DXGK_MAX_GPUVERSION_NAME_LENGTH 32

// Used to collect the bios version and gpu architecture name once during GPU initialization.
typedef struct _D3DKMT_GPUVERSION
{
    _In_ UINT32 PhysicalAdapterIndex; // The physical adapter index in a LDA chain.
    _Out_ WCHAR BiosVersion[DXGK_MAX_GPUVERSION_NAME_LENGTH]; // The current bios of the adapter.
    _Out_ WCHAR GpuArchitecture[DXGK_MAX_GPUVERSION_NAME_LENGTH]; // The gpu architecture of the adapter.
} D3DKMT_GPUVERSION;

// Describes the kernel mode display driver.
typedef struct _D3DKMT_DRIVER_DESCRIPTION
{
    WCHAR DriverDescription[4096]; // out: Pointer to a string of characters that represent the driver description.
} D3DKMT_DRIVER_DESCRIPTION;

typedef struct _D3DKMT_QUERY_SCANOUT_CAPS
{
    ULONG VidPnSourceId;
    UINT Caps;
} D3DKMT_QUERY_SCANOUT_CAPS;

typedef struct _D3DKMT_WDDM_2_7_CAPS
{
    union
    {
        struct
        {
            UINT32 HwSchSupported : 1;
            UINT32 HwSchEnabled : 1;
            UINT32 HwSchEnabledByDefault : 1;
            UINT32 ReseIndependentVidPnVSyncControlrved : 1;
            UINT32 Reserved : 28;
        };
        UINT32 Value;
    };
} D3DKMT_WDDM_2_7_CAPS;

// Describes the mapping of the given name of a device to a graphics adapter handle and monitor output.
typedef struct _D3DKMT_OPENADAPTERFROMDEVICENAME
{
    _In_ PWSTR DeviceName; // A Null-terminated string that contains the name of the device from which to open an adapter instance.
    _Out_ D3DKMT_HANDLE AdapterHandle; // A handle to the graphics adapter for the device that DeviceName specifies.
    _Out_ LUID AdapterLuid; // The locally unique identifier (LUID) of the graphics adapter for the device that DeviceName specifies.
} D3DKMT_OPENADAPTERFROMDEVICENAME;

// Describes the mapping of the given name of a GDI device to a graphics adapter handle and monitor output.
typedef struct _D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME
{
    _In_ WCHAR DeviceName[32]; // A Unicode string that contains the name of the GDI device from which to open an adapter instance.
    _Out_ D3DKMT_HANDLE AdapterHandle; // A handle to the graphics adapter for the GDI device that DeviceName specifies.
    _Out_ LUID AdapterLuid; // The locally unique identifier (LUID) of the graphics adapter for the GDI device that DeviceName specifies. 
    _Out_ ULONG VidPnSourceId; // D3DDDI_VIDEO_PRESENT_SOURCE_ID // The zero-based identification number of the video present source.
} D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME;

// Describes the mapping of a device context handle (HDC) to a graphics adapter handle and monitor output.
typedef struct _D3DKMT_OPENADAPTERFROMHDC
{
    _In_ HDC hDc; // The HDC for the graphics adapter and monitor output that are retrieved.
    _Out_ D3DKMT_HANDLE AdapterHandle; // A handle to the graphics adapter for the HDC that hDc specifies.
    _Out_ LUID AdapterLuid; // The locally unique identifier (LUID) of the graphics adapter for the HDC that hDc specifies.
    _Out_ ULONG VidPnSourceId; // D3DDDI_VIDEO_PRESENT_SOURCE_ID // The zero-based identification number of the video present source.
} D3DKMT_OPENADAPTERFROMHDC;

// Describes the mapping of the given locally unique identifier (LUID) of a device to a graphics adapter handle.
typedef struct _D3DKMT_OPENADAPTERFROMLUID
{
    _In_ LUID AdapterLuid;
    _Out_ D3DKMT_HANDLE AdapterHandle;
} D3DKMT_OPENADAPTERFROMLUID;

// Supplies configuration information about a graphics adapter.
typedef struct _D3DKMT_ADAPTERINFO
{
    D3DKMT_HANDLE AdapterHandle; // A handle to the adapter.
    LUID AdapterLuid; // A LUID that serves as an identifier for the adapter.
    ULONG NumOfSources; // The number of video present sources supported by the adapter.
    BOOL bPresentMoveRegionsPreferred; // If TRUE, the adapter prefers move regions.
} D3DKMT_ADAPTERINFO;

#define MAX_ENUM_ADAPTERS 16

// Supplies information for enumerating all graphics adapters on the system.
typedef struct _D3DKMT_ENUMADAPTERS
{
    _In_ ULONG NumAdapters; // The number of graphics adapters.
    _Out_ D3DKMT_ADAPTERINFO Adapters[MAX_ENUM_ADAPTERS]; // An array of D3DKMT_ADAPTERINFO structures that supply configuration information for each adapter.
} D3DKMT_ENUMADAPTERS;

// Supplies information for enumerating all graphics adapters on the system.
typedef struct _D3DKMT_ENUMADAPTERS2
{
    _Inout_ ULONG NumAdapters; // On input, the count of the pAdapters array buffer. On output, the number of adapters enumerated.
    _Out_ D3DKMT_ADAPTERINFO* Adapters; // Array of enumerated adapters containing NumAdapters elements.
} D3DKMT_ENUMADAPTERS2;

typedef union _D3DKMT_ENUMADAPTERS_FILTER
{
    ULONG64 IncludeComputeOnly : 1;
    ULONG64 IncludeDisplayOnly : 1;
    ULONG64 Reserved : 62;
} D3DKMT_ENUMADAPTERS_FILTER;

typedef struct _D3DKMT_ENUMADAPTERS3
{
    _In_ D3DKMT_ENUMADAPTERS_FILTER Filter;
    _Inout_ ULONG NumAdapters;
    _Out_ D3DKMT_ADAPTERINFO* Adapters;
} D3DKMT_ENUMADAPTERS3;

// The D3DKMT_CLOSEADAPTER structure specifies the graphics adapter to close.
typedef struct _D3DKMT_CLOSEADAPTER
{
    _In_ D3DKMT_HANDLE AdapterHandle; // A handle to the graphics adapter to close.
} D3DKMT_CLOSEADAPTER;

typedef struct _D3DKMT_QUERYADAPTERINFO
{
    _In_ D3DKMT_HANDLE AdapterHandle;
    _In_ KMTQUERYADAPTERINFOTYPE Type;
    _Inout_bytecount_(PrivateDriverDataSize) PVOID PrivateDriverData;
    _Out_ UINT32 PrivateDriverDataSize;
} D3DKMT_QUERYADAPTERINFO;

typedef enum _D3DKMT_QUERYRESULT_PREEMPTION_ATTEMPT_RESULT
{
    D3DKMT_PreemptionAttempt = 0,
    D3DKMT_PreemptionAttemptSuccess = 1,
    D3DKMT_PreemptionAttemptMissNoCommand = 2,
    D3DKMT_PreemptionAttemptMissNotEnabled = 3,
    D3DKMT_PreemptionAttemptMissNextFence = 4,
    D3DKMT_PreemptionAttemptMissPagingCommand = 5,
    D3DKMT_PreemptionAttemptMissSplittedCommand = 6,
    D3DKMT_PreemptionAttemptMissFenceCommand= 7,
    D3DKMT_PreemptionAttemptMissRenderPendingFlip = 8,
    D3DKMT_PreemptionAttemptMissNotMakingProgress = 9,
    D3DKMT_PreemptionAttemptMissLessPriority = 10,
    D3DKMT_PreemptionAttemptMissRemainingQuantum = 11,
    D3DKMT_PreemptionAttemptMissRemainingPreemptionQuantum = 12,
    D3DKMT_PreemptionAttemptMissAlreadyPreempting = 13,
    D3DKMT_PreemptionAttemptMissGlobalBlock = 14,
    D3DKMT_PreemptionAttemptMissAlreadyRunning = 15,
    D3DKMT_PreemptionAttemptStatisticsMax
} D3DKMT_QUERYRESULT_PREEMPTION_ATTEMPT_RESULT;

typedef enum _D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE
{
    D3DKMT_ClientRenderBuffer = 0,
    D3DKMT_ClientPagingBuffer = 1,
    D3DKMT_SystemPagingBuffer = 2,
    D3DKMT_SystemPreemptionBuffer = 3,
    D3DKMT_DmaPacketTypeMax
} D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE;

typedef enum _D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE
{
    D3DKMT_RenderCommandBuffer = 0,
    D3DKMT_DeferredCommandBuffer = 1,
    D3DKMT_SystemCommandBuffer = 2,
    D3DKMT_MmIoFlipCommandBuffer = 3,
    D3DKMT_WaitCommandBuffer = 4,
    D3DKMT_SignalCommandBuffer = 5,
    D3DKMT_DeviceCommandBuffer = 6,
    D3DKMT_SoftwareCommandBuffer = 7,
    D3DKMT_QueuePacketTypeMax
} D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE;

typedef enum _D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS
{
    D3DKMT_AllocationPriorityClassMinimum = 0,
    D3DKMT_AllocationPriorityClassLow = 1,
    D3DKMT_AllocationPriorityClassNormal = 2,
    D3DKMT_AllocationPriorityClassHigh = 3,
    D3DKMT_AllocationPriorityClassMaximum = 4,
    D3DKMT_MaxAllocationPriorityClass
} D3DKMT_QUERYSTATISTICS_ALLOCATION_PRIORITY_CLASS;

#define D3DKMT_QUERYSTATISTICS_SEGMENT_PREFERENCE_MAX 5

typedef struct _D3DKMT_QUERYSTATISTICS_COUNTER
{
    ULONG Count;
    ULONGLONG Bytes;
} D3DKMT_QUERYSTATISTICS_COUNTER;

typedef struct _D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_INFORMATION
{
    ULONG PacketSubmited;
    ULONG PacketCompleted;
    ULONG PacketPreempted;
    ULONG PacketFaulted;
} D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_INFORMATION
{
    ULONG PacketSubmited;
    ULONG PacketCompleted;
} D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_PACKET_INFORMATION
{
    D3DKMT_QUERYSTATISTICS_QUEUE_PACKET_TYPE_INFORMATION QueuePacket[D3DKMT_QueuePacketTypeMax];
    D3DKMT_QUERYSTATISTICS_DMA_PACKET_TYPE_INFORMATION DmaPacket[D3DKMT_DmaPacketTypeMax];
} D3DKMT_QUERYSTATISTICS_PACKET_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_PREEMPTION_INFORMATION
{
    ULONG PreemptionCounter[D3DKMT_PreemptionAttemptStatisticsMax];
} D3DKMT_QUERYSTATISTICS_PREEMPTION_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION
{
    LARGE_INTEGER RunningTime; // 100ns
    ULONG ContextSwitch;
    D3DKMT_QUERYSTATISTICS_PREEMPTION_INFORMATION PreemptionStatistics;
    D3DKMT_QUERYSTATISTICS_PACKET_INFORMATION PacketStatistics;
    ULONG64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_NODE_INFORMATION
{
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION GlobalInformation; // global
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION SystemInformation; // system thread
    //ULONG NodeId; // Win10
    ULONG64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_NODE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION
{
    ULONG Frame;
    ULONG CancelledFrame;
    ULONG QueuedPresent;
    ULONG64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_VIDPNSOURCE_INFORMATION
{
    D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION GlobalInformation; // global
    D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION SystemInformation; // system thread
    ULONG64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_VIDPNSOURCE_INFORMATION;

typedef struct _D3DKMT_QUERYSTATSTICS_REFERENCE_DMA_BUFFER
{
    ULONG NbCall;
    ULONG NbAllocationsReferenced;
    ULONG MaxNbAllocationsReferenced;
    ULONG NbNULLReference;
    ULONG NbWriteReference;
    ULONG NbRenamedAllocationsReferenced;
    ULONG NbIterationSearchingRenamedAllocation;
    ULONG NbLockedAllocationReferenced;
    ULONG NbAllocationWithValidPrepatchingInfoReferenced;
    ULONG NbAllocationWithInvalidPrepatchingInfoReferenced;
    ULONG NbDMABufferSuccessfullyPrePatched;
    ULONG NbPrimariesReferencesOverflow;
    ULONG NbAllocationWithNonPreferredResources;
    ULONG NbAllocationInsertedInMigrationTable;
} D3DKMT_QUERYSTATSTICS_REFERENCE_DMA_BUFFER;

typedef struct _D3DKMT_QUERYSTATSTICS_RENAMING
{
    ULONG NbAllocationsRenamed;
    ULONG NbAllocationsShrinked;
    ULONG NbRenamedBuffer;
    ULONG MaxRenamingListLength;
    ULONG NbFailuresDueToRenamingLimit;
    ULONG NbFailuresDueToCreateAllocation;
    ULONG NbFailuresDueToOpenAllocation;
    ULONG NbFailuresDueToLowResource;
    ULONG NbFailuresDueToNonRetiredLimit;
} D3DKMT_QUERYSTATSTICS_RENAMING;

typedef struct _D3DKMT_QUERYSTATSTICS_PREPRATION
{
    ULONG BroadcastStall;
    ULONG NbDMAPrepared;
    ULONG NbDMAPreparedLongPath;
    ULONG ImmediateHighestPreparationPass;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocationsTrimmed;
} D3DKMT_QUERYSTATSTICS_PREPRATION;

typedef struct _D3DKMT_QUERYSTATSTICS_PAGING_FAULT
{
    D3DKMT_QUERYSTATISTICS_COUNTER Faults;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsFirstTimeAccess;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsReclaimed;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsMigration;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsIncorrectResource;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsLostContent;
    D3DKMT_QUERYSTATISTICS_COUNTER FaultsEvicted;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocationsMEM_RESET;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocationsUnresetSuccess;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocationsUnresetFail;
    ULONG AllocationsUnresetSuccessRead;
    ULONG AllocationsUnresetFailRead;

    D3DKMT_QUERYSTATISTICS_COUNTER Evictions;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToPreparation;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToLock;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToClose;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToPurge;
    D3DKMT_QUERYSTATISTICS_COUNTER EvictionsDueToSuspendCPUAccess;
} D3DKMT_QUERYSTATSTICS_PAGING_FAULT;

typedef struct _D3DKMT_QUERYSTATSTICS_PAGING_TRANSFER
{
    ULONGLONG BytesFilled;
    ULONGLONG BytesDiscarded;
    ULONGLONG BytesMappedIntoAperture;
    ULONGLONG BytesUnmappedFromAperture;
    ULONGLONG BytesTransferredFromMdlToMemory;
    ULONGLONG BytesTransferredFromMemoryToMdl;
    ULONGLONG BytesTransferredFromApertureToMemory;
    ULONGLONG BytesTransferredFromMemoryToAperture;
} D3DKMT_QUERYSTATSTICS_PAGING_TRANSFER;

typedef struct _D3DKMT_QUERYSTATSTICS_SWIZZLING_RANGE
{
    ULONG NbRangesAcquired;
    ULONG NbRangesReleased;
} D3DKMT_QUERYSTATSTICS_SWIZZLING_RANGE;

typedef struct _D3DKMT_QUERYSTATSTICS_LOCKS
{
    ULONG NbLocks;
    ULONG NbLocksWaitFlag;
    ULONG NbLocksDiscardFlag;
    ULONG NbLocksNoOverwrite;
    ULONG NbLocksNoReadSync;
    ULONG NbLocksLinearization;
    ULONG NbComplexLocks;
} D3DKMT_QUERYSTATSTICS_LOCKS;

typedef struct _D3DKMT_QUERYSTATSTICS_ALLOCATIONS
{
    D3DKMT_QUERYSTATISTICS_COUNTER Created;
    D3DKMT_QUERYSTATISTICS_COUNTER Destroyed;
    D3DKMT_QUERYSTATISTICS_COUNTER Opened;
    D3DKMT_QUERYSTATISTICS_COUNTER Closed;
    D3DKMT_QUERYSTATISTICS_COUNTER MigratedSuccess;
    D3DKMT_QUERYSTATISTICS_COUNTER MigratedFail;
    D3DKMT_QUERYSTATISTICS_COUNTER MigratedAbandoned;
} D3DKMT_QUERYSTATSTICS_ALLOCATIONS;

typedef struct _D3DKMT_QUERYSTATSTICS_TERMINATIONS
{
    D3DKMT_QUERYSTATISTICS_COUNTER TerminatedShared;
    D3DKMT_QUERYSTATISTICS_COUNTER TerminatedNonShared;
    D3DKMT_QUERYSTATISTICS_COUNTER DestroyedShared;
    D3DKMT_QUERYSTATISTICS_COUNTER DestroyedNonShared;
} D3DKMT_QUERYSTATSTICS_TERMINATIONS;

typedef struct _D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION
{
    ULONG NbSegments;
    ULONG NodeCount;
    ULONG VidPnSourceCount;

    ULONG VSyncEnabled;
    ULONG TdrDetectedCount;

    LONGLONG ZeroLengthDmaBuffers;
    ULONGLONG RestartedPeriod;

    D3DKMT_QUERYSTATSTICS_REFERENCE_DMA_BUFFER ReferenceDmaBuffer;
    D3DKMT_QUERYSTATSTICS_RENAMING Renaming;
    D3DKMT_QUERYSTATSTICS_PREPRATION Preparation;
    D3DKMT_QUERYSTATSTICS_PAGING_FAULT PagingFault;
    D3DKMT_QUERYSTATSTICS_PAGING_TRANSFER PagingTransfer;
    D3DKMT_QUERYSTATSTICS_SWIZZLING_RANGE SwizzlingRange;
    D3DKMT_QUERYSTATSTICS_LOCKS Locks;
    D3DKMT_QUERYSTATSTICS_ALLOCATIONS Allocations;
    D3DKMT_QUERYSTATSTICS_TERMINATIONS Terminations;

    ULONG64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_SYSTEM_MEMORY
{
    ULONGLONG BytesAllocated;
    ULONGLONG BytesReserved;
    ULONG SmallAllocationBlocks;
    ULONG LargeAllocationBlocks;
    ULONGLONG WriteCombinedBytesAllocated;
    ULONGLONG WriteCombinedBytesReserved;
    ULONGLONG CachedBytesAllocated;
    ULONGLONG CachedBytesReserved;
    ULONGLONG SectionBytesAllocated;
    ULONGLONG SectionBytesReserved;
} D3DKMT_QUERYSTATISTICS_SYSTEM_MEMORY;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_INFORMATION
{
    ULONG NodeCount;
    ULONG VidPnSourceCount;

    D3DKMT_QUERYSTATISTICS_SYSTEM_MEMORY SystemMemory;

    ULONG64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_PROCESS_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_DMA_BUFFER
{
    D3DKMT_QUERYSTATISTICS_COUNTER Size;
    ULONG AllocationListBytes;
    ULONG PatchLocationListBytes;
} D3DKMT_QUERYSTATISTICS_DMA_BUFFER;

typedef struct _D3DKMT_QUERYSTATISTICS_COMMITMENT_DATA
{
    ULONG64 TotalBytesEvictedFromProcess;
    ULONG64 BytesBySegmentPreference[D3DKMT_QUERYSTATISTICS_SEGMENT_PREFERENCE_MAX];
} D3DKMT_QUERYSTATISTICS_COMMITMENT_DATA;

typedef struct _D3DKMT_QUERYSTATISTICS_POLICY
{
    ULONGLONG PreferApertureForRead[D3DKMT_MaxAllocationPriorityClass];
    ULONGLONG PreferAperture[D3DKMT_MaxAllocationPriorityClass];
    ULONGLONG MemResetOnPaging;
    ULONGLONG RemovePagesFromWorkingSetOnPaging;
    ULONGLONG MigrationEnabled;
} D3DKMT_QUERYSTATISTICS_POLICY;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER_INFORMATION
{
    ULONG NbSegments;
    ULONG NodeCount;
    ULONG VidPnSourceCount;

    ULONG VirtualMemoryUsage;

    D3DKMT_QUERYSTATISTICS_DMA_BUFFER DmaBuffer;
    D3DKMT_QUERYSTATISTICS_COMMITMENT_DATA CommitmentData;
    D3DKMT_QUERYSTATISTICS_POLICY _Policy;

    ULONG64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_MEMORY
{
    ULONGLONG TotalBytesEvicted;
    ULONG AllocsCommitted;
    ULONG AllocsResident;
} D3DKMT_QUERYSTATISTICS_MEMORY;

typedef struct _D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION_V1
{
    ULONG CommitLimit;
    ULONG BytesCommitted;
    ULONG BytesResident;

    D3DKMT_QUERYSTATISTICS_MEMORY Memory;

    ULONG Aperture; // boolean

    ULONGLONG TotalBytesEvictedByPriority[D3DKMT_MaxAllocationPriorityClass];

    ULONG64 SystemMemoryEndAddress;
    struct
    {
        ULONG64 PreservedDuringStandby : 1;
        ULONG64 PreservedDuringHibernate : 1;
        ULONG64 PartiallyPreservedDuringHibernate : 1;
        ULONG64 Reserved : 61;
    } PowerFlags;

    ULONG64 Reserved[7];
} D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION_V1;

typedef struct _D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION
{
    ULONGLONG CommitLimit;
    ULONGLONG BytesCommitted;
    ULONGLONG BytesResident;

    D3DKMT_QUERYSTATISTICS_MEMORY Memory;

    ULONG Aperture; // boolean

    ULONGLONG TotalBytesEvictedByPriority[D3DKMT_MaxAllocationPriorityClass];

    ULONG64 SystemMemoryEndAddress;
    struct
    {
        ULONG64 PreservedDuringStandby : 1;
        ULONG64 PreservedDuringHibernate : 1;
        ULONG64 PartiallyPreservedDuringHibernate : 1;
        ULONG64 Reserved : 61;
    } PowerFlags;

    ULONG64 Reserved[6];
} D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION;

typedef struct _D3DKMT_QUERYSTATISTICS_VIDEO_MEMORY
{
    ULONG AllocsCommitted;
    D3DKMT_QUERYSTATISTICS_COUNTER AllocsResidentInP[D3DKMT_QUERYSTATISTICS_SEGMENT_PREFERENCE_MAX];
    D3DKMT_QUERYSTATISTICS_COUNTER AllocsResidentInNonPreferred;
    ULONGLONG TotalBytesEvictedDueToPreparation;
} D3DKMT_QUERYSTATISTICS_VIDEO_MEMORY;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_POLICY
{
    ULONGLONG UseMRU;
} D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_POLICY;

typedef struct _D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_INFORMATION
{
    ULONGLONG BytesCommitted;
    ULONGLONG MaximumWorkingSet;
    ULONGLONG MinimumWorkingSet;

    ULONG NbReferencedAllocationEvictedInPeriod;

    D3DKMT_QUERYSTATISTICS_VIDEO_MEMORY VideoMemory;
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_POLICY _Policy;

    ULONG64 Reserved[8];
} D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_INFORMATION;

typedef enum _D3DKMT_QUERYSTATISTICS_TYPE
{
    D3DKMT_QUERYSTATISTICS_ADAPTER,
    D3DKMT_QUERYSTATISTICS_PROCESS,
    D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER,
    D3DKMT_QUERYSTATISTICS_SEGMENT,
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT,
    D3DKMT_QUERYSTATISTICS_NODE,
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE,
    D3DKMT_QUERYSTATISTICS_VIDPNSOURCE,
    D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE,
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_GROUP,
    D3DKMT_QUERYSTATISTICS_PHYSICAL_ADAPTER
} D3DKMT_QUERYSTATISTICS_TYPE;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT
{
    ULONG SegmentId;
} D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_NODE
{
    ULONG NodeId;
} D3DKMT_QUERYSTATISTICS_QUERY_NODE;

typedef struct _D3DKMT_QUERYSTATISTICS_QUERY_VIDPNSOURCE
{
    ULONG VidPnSourceId;
} D3DKMT_QUERYSTATISTICS_QUERY_VIDPNSOURCE;

typedef union _D3DKMT_QUERYSTATISTICS_RESULT
{
    D3DKMT_QUERYSTATISTICS_ADAPTER_INFORMATION AdapterInformation;
    // D3DKMT_QUERYSTATISTICS_PHYSICAL_ADAPTER_INFORMATION PhysAdapterInformation;
    D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION_V1 SegmentInformationV1; // WIN7
    D3DKMT_QUERYSTATISTICS_SEGMENT_INFORMATION SegmentInformation; // WIN8
    D3DKMT_QUERYSTATISTICS_NODE_INFORMATION NodeInformation;
    D3DKMT_QUERYSTATISTICS_VIDPNSOURCE_INFORMATION VidPnSourceInformation;
    D3DKMT_QUERYSTATISTICS_PROCESS_INFORMATION ProcessInformation;
    D3DKMT_QUERYSTATISTICS_PROCESS_ADAPTER_INFORMATION ProcessAdapterInformation;
    D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_INFORMATION ProcessSegmentInformation;
    D3DKMT_QUERYSTATISTICS_PROCESS_NODE_INFORMATION ProcessNodeInformation;
    D3DKMT_QUERYSTATISTICS_PROCESS_VIDPNSOURCE_INFORMATION ProcessVidPnSourceInformation;
    // D3DKMT_QUERYSTATISTICS_PROCESS_SEGMENT_GROUP_INFORMATION ProcessSegmentGroupInformation;
} D3DKMT_QUERYSTATISTICS_RESULT;

typedef struct _D3DKMT_QUERYSTATISTICS
{
    _In_ D3DKMT_QUERYSTATISTICS_TYPE Type;
    _In_ LUID AdapterLuid;
    _In_opt_ HANDLE ProcessHandle;
    _Out_ D3DKMT_QUERYSTATISTICS_RESULT QueryResult;

    union
    {
        _In_ D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT QuerySegment;
        _In_ D3DKMT_QUERYSTATISTICS_QUERY_SEGMENT QueryProcessSegment;
        _In_ D3DKMT_QUERYSTATISTICS_QUERY_NODE QueryNode;
        _In_ D3DKMT_QUERYSTATISTICS_QUERY_NODE QueryProcessNode;
        _In_ D3DKMT_QUERYSTATISTICS_QUERY_VIDPNSOURCE QueryVidPnSource;
        _In_ D3DKMT_QUERYSTATISTICS_QUERY_VIDPNSOURCE QueryProcessVidPnSource;
    };
} D3DKMT_QUERYSTATISTICS;

typedef enum _D3DKMT_MEMORY_SEGMENT_GROUP
{
    D3DKMT_MEMORY_SEGMENT_GROUP_LOCAL = 0,
    D3DKMT_MEMORY_SEGMENT_GROUP_NON_LOCAL = 1
} D3DKMT_MEMORY_SEGMENT_GROUP;

typedef struct _D3DKMT_QUERYVIDEOMEMORYINFO
{
    _In_opt_ HANDLE ProcessHandle; // A handle to a process. If NULL, the current process is used. The process handle must be opened with PROCESS_QUERY_INFORMATION privileges.
    _In_ D3DKMT_HANDLE AdapterHandle; // The adapter to query for this process
    _In_ D3DKMT_MEMORY_SEGMENT_GROUP MemorySegmentGroup; // The memory segment group to query.
    _Out_ UINT64 Budget; // Total memory the application may use
    _Out_ UINT64 CurrentUsage; // Current memory usage of the device
    _Out_ UINT64 CurrentReservation; // Current reservation of the device
    _Out_ UINT64 AvailableForReservation; // Total that the device may reserve
    _In_ UINT32 PhysicalAdapterIndex; // Zero based physical adapter index in the LDA configuration.
} D3DKMT_QUERYVIDEOMEMORYINFO;

typedef enum _D3DKMT_ESCAPETYPE
{
    D3DKMT_ESCAPE_DRIVERPRIVATE = 0,
    D3DKMT_ESCAPE_VIDMM = 1, // D3DKMT_VIDMM_ESCAPE
    D3DKMT_ESCAPE_TDRDBGCTRL = 2, // D3DKMT_TDRDBGCTRLTYPE
    D3DKMT_ESCAPE_VIDSCH = 3, // D3DKMT_VIDSCH_ESCAPE
    D3DKMT_ESCAPE_DEVICE = 4, // D3DKMT_DEVICE_ESCAPE
    D3DKMT_ESCAPE_DMM = 5, // D3DKMT_DMM_ESCAPE
    D3DKMT_ESCAPE_DEBUG_SNAPSHOT = 6, // D3DKMT_DEBUG_SNAPSHOT_ESCAPE
    // unused (7 was previously used to set driver update in-progress status, D3DKMT_ESCAPE_SETDRIVERUPDATESTATUS)
    D3DKMT_ESCAPE_DRT_TEST = 8,
    D3DKMT_ESCAPE_DIAGNOSTICS = 9, // since WIN8
    D3DKMT_ESCAPE_OUTPUTDUPL_SNAPSHOT = 10,
    D3DKMT_ESCAPE_OUTPUTDUPL_DIAGNOSTICS = 11,
    D3DKMT_ESCAPE_BDD_PNP = 12,
    D3DKMT_ESCAPE_BDD_FALLBACK = 13,
    D3DKMT_ESCAPE_ACTIVATE_SPECIFIC_DIAG = 14, // D3DKMT_ACTIVATE_SPECIFIC_DIAG_ESCAPE
    D3DKMT_ESCAPE_MODES_PRUNED_OUT = 15,
    D3DKMT_ESCAPE_WHQL_INFO = 16, // UINT32 ??
    D3DKMT_ESCAPE_BRIGHTNESS = 17,
    D3DKMT_ESCAPE_EDID_CACHE = 18,  // UINT32 ??
    D3DKMT_ESCAPE_GENERIC_ADAPTER_DIAG_INFO = 19,
    D3DKMT_ESCAPE_MIRACAST_DISPLAY_REQUEST = 20, // since WDDM1_3
    D3DKMT_ESCAPE_HISTORY_BUFFER_STATUS = 21,
    // 22 can be reused for future needs as it was never exposed for external purposes
    D3DKMT_ESCAPE_MIRACAST_ADAPTER_DIAG_INFO = 23,
    D3DKMT_ESCAPE_FORCE_BDDFALLBACK_HEADLESS = 24, // since WDDM2_0
    D3DKMT_ESCAPE_REQUEST_MACHINE_CRASH = 25, // D3DKMT_REQUEST_MACHINE_CRASH_ESCAPE
    D3DKMT_ESCAPE_HMD_GET_EDID_BASE_BLOCK = 26,
    D3DKMT_ESCAPE_SOFTGPU_ENABLE_DISABLE_HMD = 27,
    D3DKMT_ESCAPE_PROCESS_VERIFIER_OPTION = 28,
    D3DKMT_ESCAPE_ADAPTER_VERIFIER_OPTION = 29,
    D3DKMT_ESCAPE_IDD_REQUEST = 30, // since WDDM2_1
    D3DKMT_ESCAPE_DOD_SET_DIRTYRECT_MODE = 31,
    D3DKMT_ESCAPE_LOG_CODEPOINT_PACKET = 32,
    D3DKMT_ESCAPE_LOG_USERMODE_DAIG_PACKET = 33, // since WDDM2_2
    D3DKMT_ESCAPE_GET_EXTERNAL_DIAGNOSTICS = 34,
    // unused (35 previously was D3DKMT_ESCAPE_GET_PREFERRED_MODE)
    D3DKMT_ESCAPE_GET_DISPLAY_CONFIGURATIONS = 36, // since WDDM2_3
    D3DKMT_ESCAPE_QUERY_IOMMU_STATUS = 37, // since WDDM2_4
    D3DKMT_ESCAPE_CCD_DATABASE = 38, // since WDDM2_6

    D3DKMT_ESCAPE_WIN32K_START = 1024,
    D3DKMT_ESCAPE_WIN32K_HIP_DEVICE_INFO = 1024,
    D3DKMT_ESCAPE_WIN32K_QUERY_CD_ROTATION_BLOCK = 1025,
    D3DKMT_ESCAPE_WIN32K_DPI_INFO = 1026, // Use hContext for the desired hdev // since WDDM1_3
    D3DKMT_ESCAPE_WIN32K_PRESENTER_VIEW_INFO = 1027,
    D3DKMT_ESCAPE_WIN32K_SYSTEM_DPI = 1028,
    D3DKMT_ESCAPE_WIN32K_BDD_FALLBACK = 1029, // since WDDM2_0
    D3DKMT_ESCAPE_WIN32K_DDA_TEST_CTL = 1030,
    D3DKMT_ESCAPE_WIN32K_USER_DETECTED_BLACK_SCREEN = 1031,
    D3DKMT_ESCAPE_WIN32K_HMD_ENUM = 1032,
    D3DKMT_ESCAPE_WIN32K_HMD_CONTROL = 1033,
    D3DKMT_ESCAPE_WIN32K_LPMDISPLAY_CONTROL = 1034,
} D3DKMT_ESCAPETYPE;

typedef enum _D3DKMT_VIDMMESCAPETYPE
{
    D3DKMT_VIDMMESCAPETYPE_SETFAULT = 0,
    D3DKMT_VIDMMESCAPETYPE_RUN_COHERENCY_TEST = 1,
    D3DKMT_VIDMMESCAPETYPE_RUN_UNMAP_TO_DUMMY_PAGE_TEST = 2,
    D3DKMT_VIDMMESCAPETYPE_APERTURE_CORRUPTION_CHECK = 3,
    D3DKMT_VIDMMESCAPETYPE_SUSPEND_CPU_ACCESS_TEST = 4,
    D3DKMT_VIDMMESCAPETYPE_EVICT = 5,
    D3DKMT_VIDMMESCAPETYPE_EVICT_BY_NT_HANDLE = 6,
    D3DKMT_VIDMMESCAPETYPE_GET_VAD_INFO = 7,
    D3DKMT_VIDMMESCAPETYPE_SET_BUDGET = 8,
    D3DKMT_VIDMMESCAPETYPE_SUSPEND_PROCESS = 9,
    D3DKMT_VIDMMESCAPETYPE_RESUME_PROCESS = 10,
    D3DKMT_VIDMMESCAPETYPE_GET_BUDGET = 11,
    D3DKMT_VIDMMESCAPETYPE_SET_TRIM_INTERVALS = 12,
    D3DKMT_VIDMMESCAPETYPE_EVICT_BY_CRITERIA = 13,
    D3DKMT_VIDMMESCAPETYPE_WAKE = 14,
    D3DKMT_VIDMMESCAPETYPE_DEFRAG = 15,
} D3DKMT_VIDMMESCAPETYPE;

typedef struct _D3DKMT_VAD_DESC
{
    _In_ UINT32 VadIndex; // 0xFFFFFFFF to use the VAD address
    _In_ UINT64 VadAddress;
    _Out_ UINT32 NumMappedRanges;
    _Out_ UINT32 VadType; // 0 - reserved, 1 - Mapped
    _Out_ UINT64 StartAddress;
    _Out_ UINT64 EndAddress;
} D3DKMT_VAD_DESC;

typedef struct _D3DKMT_VA_RANGE_DESC
{
    _In_ UINT64 VadAddress;
    _In_ UINT32 VaRangeIndex;
    _In_ UINT32 PhysicalAdapterIndex;
    _Out_ UINT64 StartAddress;
    _Out_ UINT64 EndAddress;
    _Out_ UINT64 DriverProtection;
    _Out_ UINT32 OwnerType; // VIDMM_VAD_OWNER_TYPE
    _Out_ UINT64 pOwner;
    _Out_ UINT64 OwnerOffset;
    _Out_ UINT32 Protection; // D3DDDIGPUVIRTUALADDRESS_PROTECTION_TYPE
} D3DKMT_VA_RANGE_DESC;

typedef struct _D3DKMT_PAGE_TABLE_LEVEL_DESC
{
    UINT32 IndexBitCount;
    UINT64 IndexMask;
    UINT64 IndexShift;
    UINT64 LowerLevelsMask;
    UINT64 EntryCoverageInPages;
} D3DKMT_PAGE_TABLE_LEVEL_DESC;

#define DXGK_MAX_PAGE_TABLE_LEVEL_COUNT 6
#define DXGK_MIN_PAGE_TABLE_LEVEL_COUNT 2

typedef struct _DXGK_ESCAPE_GPUMMUCAPS
{
    BOOLEAN ReadOnlyMemorySupported;
    BOOLEAN NoExecuteMemorySupported;
    BOOLEAN ZeroInPteSupported;
    BOOLEAN CacheCoherentMemorySupported;
    BOOLEAN LargePageSupported;
    BOOLEAN DualPteSupported;
    BOOLEAN AllowNonAlignedLargePageAddress;
    UINT32 VirtualAddressBitCount;
    UINT32 PageTableLevelCount;
    D3DKMT_PAGE_TABLE_LEVEL_DESC PageTableLevelDesk[DXGK_MAX_PAGE_TABLE_LEVEL_COUNT];
} DXGK_ESCAPE_GPUMMUCAPS;

typedef struct _D3DKMT_GET_GPUMMU_CAPS
{
    UINT32 PhysicalAdapterIndex; // In
    DXGK_ESCAPE_GPUMMUCAPS GpuMmuCaps; // Out
} D3DKMT_GET_GPUMMU_CAPS;

typedef enum _DXGK_PTE_PAGE_SIZE
{
    DXGK_PTE_PAGE_TABLE_PAGE_4KB = 0,
    DXGK_PTE_PAGE_TABLE_PAGE_64KB = 1,
} DXGK_PTE_PAGE_SIZE;

typedef struct _DXGK_PTE
{
    union
    {
        struct
        {
            ULONGLONG Valid : 1;
            ULONGLONG Zero : 1;
            ULONGLONG CacheCoherent : 1;
            ULONGLONG ReadOnly : 1;
            ULONGLONG NoExecute : 1;
            ULONGLONG Segment : 5;
            ULONGLONG LargePage : 1;
            ULONGLONG PhysicalAdapterIndex : 6;
            ULONGLONG PageTablePageSize : 2; // DXGK_PTE_PAGE_SIZE
            ULONGLONG SystemReserved0 : 1;
            ULONGLONG Reserved : 44;
        };
        ULONGLONG Flags;
    };
    union
    {
        ULONGLONG PageAddress;      // High 52 bits of 64 bit physical address. Low 12 bits are zero.
        ULONGLONG PageTableAddress; // High 52 bits of 64 bit physical address. Low 12 bits are zero.
    };
} DXGK_PTE;

#define D3DKMT_GET_PTE_MAX 64

typedef struct _D3DKMT_GET_PTE
{
    _In_ UINT32 PhysicalAdapterIndex;
    _In_ UINT32 PageTableLevel;
    _In_ UINT32 PageTableIndex[DXGK_MAX_PAGE_TABLE_LEVEL_COUNT];
    _In_ BOOLEAN b64KBPte; // Valid only when dual PTEs are supported. Out - PT is 64KB.
    _In_ UINT32 NumPtes; // Number of PTEs to fill. Out - number of filled PTEs
    _Out_ DXGK_PTE Pte[D3DKMT_GET_PTE_MAX];
    _Out_ UINT32 NumValidEntries;
} D3DKMT_GET_PTE;

#define D3DKMT_MAX_SEGMENT_COUNT 32

typedef struct _D3DKMT_SEGMENT_CAPS
{
    UINT64 Size;
    UINT32 PageSize;
    ULONG SegmentId;
    BOOLEAN bAperture;
    BOOLEAN bReservedSysMem;
    D3DKMT_MEMORY_SEGMENT_GROUP BudgetGroup;
} D3DKMT_SEGMENT_CAPS;

typedef struct _D3DKMT_GET_SEGMENT_CAPS
{
    _In_ UINT32 PhysicalAdapterIndex;
    _Out_ UINT32 NumSegments;
    _Out_ D3DKMT_SEGMENT_CAPS SegmentCaps[D3DKMT_MAX_SEGMENT_COUNT];
} D3DKMT_GET_SEGMENT_CAPS;

typedef struct _D3DKMT_EVICTION_CRITERIA
{
    UINT64 MinimumSize;
    UINT64 MaximumSize;
    struct
    {
        union
        {
            struct
            {
                UINT32 Primary : 1;
                UINT32 Reserved : 31;
            } Flags;
            UINT32 Value;
        };
    };
} D3DKMT_EVICTION_CRITERIA;

typedef enum _D3DKMT_VAD_ESCAPE_COMMAND
{
    D3DKMT_VAD_ESCAPE_GETNUMVADS,
    D3DKMT_VAD_ESCAPE_GETVAD,
    D3DKMT_VAD_ESCAPE_GETVADRANGE,
    D3DKMT_VAD_ESCAPE_GET_PTE,
    D3DKMT_VAD_ESCAPE_GET_GPUMMU_CAPS,
    D3DKMT_VAD_ESCAPE_GET_SEGMENT_CAPS,
} D3DKMT_VAD_ESCAPE_COMMAND;

typedef enum _D3DKMT_DEFRAG_ESCAPE_OPERATION
{
    D3DKMT_DEFRAG_ESCAPE_GET_FRAGMENTATION_STATS = 0,
    D3DKMT_DEFRAG_ESCAPE_DEFRAG_UPWARD = 1,
    D3DKMT_DEFRAG_ESCAPE_DEFRAG_DOWNWARD = 2,
    D3DKMT_DEFRAG_ESCAPE_DEFRAG_PASS = 3,
    D3DKMT_DEFRAG_ESCAPE_VERIFY_TRANSFER = 4,
} D3DKMT_DEFRAG_ESCAPE_OPERATION;

typedef struct _D3DKMT_VIDMM_ESCAPE
{
    D3DKMT_VIDMMESCAPETYPE Type;
    union
    {
        struct
        {
            union
            {
                struct
                {
                    ULONG ProbeAndLock : 1;
                    ULONG SplitPoint : 1;
                    ULONG NoDemotion : 1;
                    ULONG SwizzlingAperture : 1;
                    ULONG PagingPathLockSubRange : 1;
                    ULONG PagingPathLockMinRange : 1;
                    ULONG ComplexLock : 1;
                    ULONG FailVARotation : 1;
                    ULONG NoWriteCombined : 1;
                    ULONG NoPrePatching : 1;
                    ULONG AlwaysRepatch : 1;
                    ULONG ExpectPreparationFailure : 1;
                    ULONG FailUserModeVAMapping : 1;
                    ULONG NeverDiscardOfferedAllocation : 1; // since WIN8
                    ULONG AlwaysDiscardOfferedAllocation : 1;
                    ULONG Reserved : 17;
                };
                ULONG Value;
            };
        } SetFault;
        struct
        {
            D3DKMT_HANDLE ResourceHandle;
            D3DKMT_HANDLE AllocationHandle;
            HANDLE hProcess; // 0 to evict memory for the current process, otherwise it is a process handle from OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId).
        } Evict;
        struct
        {
            UINT64 NtHandle; // Used by D3DKMT_VIDMMESCAPETYPE_EVICT_BY_NT_HANDLE
        } EvictByNtHandle;
        struct
        {
            union
            {
                struct 
                {
                    UINT32 NumVads;
                } GetNumVads;
                D3DKMT_VAD_DESC GetVad;
                D3DKMT_VA_RANGE_DESC GetVadRange;
                D3DKMT_GET_GPUMMU_CAPS GetGpuMmuCaps;
                D3DKMT_GET_PTE GetPte;
                D3DKMT_GET_SEGMENT_CAPS GetSegmentCaps;
            };
            _In_ D3DKMT_VAD_ESCAPE_COMMAND Command;
            _Out_ NTSTATUS Status;
        } GetVads;
        struct
        {
            ULONGLONG LocalMemoryBudget;
            ULONGLONG SystemMemoryBudget;
        } SetBudget;
        struct
        {
            HANDLE hProcess;
            BOOL bAllowWakeOnSubmission;
        } SuspendProcess;
        struct
        {
            HANDLE hProcess;
        } ResumeProcess;
        struct
        {
            UINT64 NumBytesToTrim;
        } GetBudget;
        struct
        {
            ULONG MinTrimInterval; // In 100ns units
            ULONG MaxTrimInterval; // In 100ns units
            ULONG IdleTrimInterval; // In 100ns units
        } SetTrimIntervals;
        D3DKMT_EVICTION_CRITERIA EvictByCriteria;
        struct
        {
            BOOL bFlush;
        } Wake;
        struct
        {
            D3DKMT_DEFRAG_ESCAPE_OPERATION Operation;          
            UINT32 SegmentId;
            ULONGLONG TotalCommitted;
            ULONGLONG TotalFree;
            ULONGLONG LargestGapBefore;
            ULONGLONG LargestGapAfter;
        } Defrag;
    };
} D3DKMT_VIDMM_ESCAPE;

typedef enum _D3DKMT_TDRDBGCTRLTYPE
{
    D3DKMT_TDRDBGCTRLTYPE_FORCETDR = 0, // Simulate a TDR
    D3DKMT_TDRDBGCTRLTYPE_DISABLEBREAK = 1, // Disable DebugBreak on timeout
    D3DKMT_TDRDBGCTRLTYPE_ENABLEBREAK = 2, // Enable DebugBreak on timeout
    D3DKMT_TDRDBGCTRLTYPE_UNCONDITIONAL = 3, // Disables all safety conditions (e.g. check for consecutive recoveries)
    D3DKMT_TDRDBGCTRLTYPE_VSYNCTDR = 4, // Simulate a Vsync TDR
    D3DKMT_TDRDBGCTRLTYPE_GPUTDR = 5, // Simulate a GPU TDR
    D3DKMT_TDRDBGCTRLTYPE_FORCEDODTDR = 6, // Simulate a Display Only Present TDR // since WIN8
    D3DKMT_TDRDBGCTRLTYPE_FORCEDODVSYNCTDR = 7, // Simulate a Display Only Vsync TDR
    D3DKMT_TDRDBGCTRLTYPE_ENGINETDR = 8, // Simulate an engine TDR
} D3DKMT_TDRDBGCTRLTYPE;

typedef enum _D3DKMT_VIDSCHESCAPETYPE
{
    D3DKMT_VIDSCHESCAPETYPE_PREEMPTIONCONTROL = 0, // Enable/Disable preemption
    D3DKMT_VIDSCHESCAPETYPE_SUSPENDSCHEDULER = 1, // Suspend/Resume scheduler (obsolate)
    D3DKMT_VIDSCHESCAPETYPE_TDRCONTROL = 2, // Tdr control
    D3DKMT_VIDSCHESCAPETYPE_SUSPENDRESUME = 3, // Suspend/Resume scheduler
    D3DKMT_VIDSCHESCAPETYPE_ENABLECONTEXTDELAY = 4, // Enable/Disable context delay // since WIN8
    D3DKMT_VIDSCHESCAPETYPE_CONFIGURE_TDR_LIMIT = 5, // Configure TdrLimitCount and TdrLimitTime
    D3DKMT_VIDSCHESCAPETYPE_VGPU_RESET = 6, // Trigger VGPU reset 
    D3DKMT_VIDSCHESCAPETYPE_PFN_CONTROL = 7, // Periodic frame notification control
} D3DKMT_VIDSCHESCAPETYPE;

typedef enum _D3DKMT_ESCAPE_PFN_CONTROL_COMMAND
{
    D3DKMT_ESCAPE_PFN_CONTROL_DEFAULT,
    D3DKMT_ESCAPE_PFN_CONTROL_FORCE_CPU,
    D3DKMT_ESCAPE_PFN_CONTROL_FORCE_GPU
} D3DKMT_ESCAPE_PFN_CONTROL_COMMAND;

typedef struct _D3DKMT_VIDSCH_ESCAPE
{
    D3DKMT_VIDSCHESCAPETYPE Type;
    union
    {
        BOOL PreemptionControl; // enable/disable preemption
        BOOL EnableContextDelay; // enable/disable context delay // since WIN8
        struct
        {
            ULONG TdrControl; // control tdr
            union
            {
                ULONG NodeOrdinal; // valid if TdrControl is set to D3DKMT_TDRDBGCTRLTYPE_ENGINETDR
            };
        } TdrControl2;
        BOOL SuspendScheduler; // suspend/resume scheduler (obsolate) // since Vista
        ULONG TdrControl; // control tdr
        ULONG SuspendTime; // time period to suspend.
        struct
        {
            UINT Count;
            UINT Time; // In seconds
        } TdrLimit;
        D3DKMT_ESCAPE_PFN_CONTROL_COMMAND PfnControl; // periodic frame notification control
    };
} D3DKMT_VIDSCH_ESCAPE;

typedef enum _D3DKMT_DEVICEESCAPE_TYPE
{
    D3DKMT_DEVICEESCAPE_VIDPNFROMALLOCATION = 0,
    D3DKMT_DEVICEESCAPE_RESTOREGAMMA = 1,
} D3DKMT_DEVICEESCAPE_TYPE;

typedef struct _D3DKMT_DEVICE_ESCAPE
{
    D3DKMT_DEVICEESCAPE_TYPE Type;
    union
    {
        struct
        {
            _In_ D3DKMT_HANDLE hPrimaryAllocation; // Primary allocation handle
            _Out_ UINT32 VidPnSourceId; // VidPnSoureId of primary allocation
        } VidPnFromAllocation;
    };
} D3DKMT_DEVICE_ESCAPE;

typedef enum _D3DKMT_DMMESCAPETYPE
{
    D3DKMT_DMMESCAPETYPE_UNINITIALIZED = 0,
    D3DKMT_DMMESCAPETYPE_GET_SUMMARY_INFO = 1,
    D3DKMT_DMMESCAPETYPE_GET_VIDEO_PRESENT_SOURCES_INFO = 2,
    D3DKMT_DMMESCAPETYPE_GET_VIDEO_PRESENT_TARGETS_INFO = 3,
    D3DKMT_DMMESCAPETYPE_GET_ACTIVEVIDPN_INFO = 4,
    D3DKMT_DMMESCAPETYPE_GET_MONITORS_INFO = 5,
    D3DKMT_DMMESCAPETYPE_RECENTLY_COMMITTED_VIDPNS_INFO = 6,
    D3DKMT_DMMESCAPETYPE_RECENT_MODECHANGE_REQUESTS_INFO = 7,
    D3DKMT_DMMESCAPETYPE_RECENTLY_RECOMMENDED_VIDPNS_INFO = 8,
    D3DKMT_DMMESCAPETYPE_RECENT_MONITOR_PRESENCE_EVENTS_INFO = 9,
    D3DKMT_DMMESCAPETYPE_ACTIVEVIDPN_SOURCEMODESET_INFO = 10,
    D3DKMT_DMMESCAPETYPE_ACTIVEVIDPN_COFUNCPATHMODALITY_INFO = 11,
    D3DKMT_DMMESCAPETYPE_GET_LASTCLIENTCOMMITTEDVIDPN_INFO = 12,
    D3DKMT_DMMESCAPETYPE_GET_VERSION_INFO = 13,
    D3DKMT_DMMESCAPETYPE_VIDPN_MGR_DIAGNOSTICS = 14
} D3DKMT_DMMESCAPETYPE;

typedef struct _D3DKMT_DMM_ESCAPE
{
    _In_ D3DKMT_DMMESCAPETYPE Type;
    _In_ SIZE_T ProvidedBufferSize; // actual size of Data[] array, in bytes.
    _Out_ SIZE_T MinRequiredBufferSize; // minimum required size of Data[] array to contain requested data.
    _Out_writes_bytes_(ProvidedBufferSize) UCHAR Data[1];
} D3DKMT_DMM_ESCAPE;

typedef struct _D3DKMT_DEBUG_SNAPSHOT_ESCAPE
{
    ULONG Length; // out: Actual length of the snapshot written in Buffer
    BYTE Buffer[1]; // out: Buffer to place snapshot
} D3DKMT_DEBUG_SNAPSHOT_ESCAPE;

typedef enum _D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE
{
    D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE_EXTRA_CCD_DATABASE_INFO = 0,
    D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE_MODES_PRUNED = 15,
}D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE;

typedef struct _D3DKMT_ACTIVATE_SPECIFIC_DIAG_ESCAPE
{
    D3DKMT_ACTIVATE_SPECIFIC_DIAG_TYPE Type; // The escape type that needs to be (de)activated
    BOOL Activate; // FALSE means deactivate
} D3DKMT_ACTIVATE_SPECIFIC_DIAG_ESCAPE;

typedef struct _D3DKMT_REQUEST_MACHINE_CRASH_ESCAPE
{
    ULONG_PTR Param1;
    ULONG_PTR Param2;
    ULONG_PTR Param3;
} D3DKMT_REQUEST_MACHINE_CRASH_ESCAPE;

typedef struct _D3DDDI_ESCAPEFLAGS
{
    union
    {
        struct
        {
            UINT32 HardwareAccess : 1;
            UINT32 DeviceStatusQuery : 1; // since WDDM1_3
            UINT32 ChangeFrameLatency : 1;
            UINT32 NoAdapterSynchronization : 1; // since WDDM2_0
            UINT32 Reserved : 1; // Used internally by DisplayOnly present // since WDDM2_2
            UINT32 VirtualMachineData : 1; // Cannot be set from user mode
            UINT32 DriverKnownEscape : 1; // Driver private data points to a well known structure
            UINT32 DriverCommonEscape : 1; // Private data points runtime defined structure
            UINT32 Reserved2 : 24;
        };
        UINT32 Value;
    };
} D3DDDI_ESCAPEFLAGS;

// The D3DKMT_ESCAPE structure describes information that is exchanged with the display miniport driver.
typedef struct _D3DKMT_ESCAPE 
{
    _In_ D3DKMT_HANDLE AdapterHandle;
    _In_opt_ D3DKMT_HANDLE DeviceHandle;
    _In_ D3DKMT_ESCAPETYPE Type;
    _In_ D3DDDI_ESCAPEFLAGS Flags;
    _Inout_ PVOID PrivateDriverData;
    _In_ UINT32 PrivateDriverDataSize;
    _In_opt_ D3DKMT_HANDLE ContextHandle;
} D3DKMT_ESCAPE;

// Function pointers

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTOpenAdapterFromDeviceName(
    _Inout_ CONST D3DKMT_OPENADAPTERFROMDEVICENAME *pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTOpenAdapterFromGdiDisplayName(
    _Inout_ CONST D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME *pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTOpenAdapterFromHdc(
    _Inout_ CONST D3DKMT_OPENADAPTERFROMHDC *pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTOpenAdapterFromLuid(
    _Inout_ CONST D3DKMT_OPENADAPTERFROMLUID *pAdapter
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTEnumAdapters(
    _Inout_ CONST D3DKMT_ENUMADAPTERS *pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTEnumAdapters2(
    _Inout_ CONST D3DKMT_ENUMADAPTERS2 *pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTEnumAdapters3(
    _Inout_ CONST D3DKMT_ENUMADAPTERS2* pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTCloseAdapter(
    _In_ CONST D3DKMT_CLOSEADAPTER *pData
    );

NTSYSAPI
NTSTATUS
NTAPI 
D3DKMTQueryAdapterInfo(
    _Inout_ CONST D3DKMT_QUERYADAPTERINFO *pData
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
D3DKMTQueryStatistics(
    _Inout_ CONST D3DKMT_QUERYSTATISTICS *pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTQueryVideoMemoryInfo(
    _Inout_ CONST D3DKMT_QUERYVIDEOMEMORYINFO *pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTEscape(
    _Inout_ CONST D3DKMT_ESCAPE *pData
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTSetProcessSchedulingPriorityClass(
    _In_ HANDLE, 
    _In_ enum D3DKMT_SCHEDULINGPRIORITYCLASS
    );

NTSYSAPI
NTSTATUS
NTAPI
D3DKMTGetProcessSchedulingPriorityClass(
    _In_ HANDLE, 
    _Out_ enum D3DKMT_SCHEDULINGPRIORITYCLASS*
    );

#endif
// #include <ntwow64.h>
#define WOW64_SYSTEM_DIRECTORY "SysWOW64"
#define WOW64_SYSTEM_DIRECTORY_U L"SysWOW64"
#define WOW64_X86_TAG " (x86)"
#define WOW64_X86_TAG_U L" (x86)"

// In USER_SHARED_DATA
typedef enum _WOW64_SHARED_INFORMATION
{
    SharedNtdll32LdrInitializeThunk,
    SharedNtdll32KiUserExceptionDispatcher,
    SharedNtdll32KiUserApcDispatcher,
    SharedNtdll32KiUserCallbackDispatcher,
    SharedNtdll32ExpInterlockedPopEntrySListFault,
    SharedNtdll32ExpInterlockedPopEntrySListResume,
    SharedNtdll32ExpInterlockedPopEntrySListEnd,
    SharedNtdll32RtlUserThreadStart,
    SharedNtdll32pQueryProcessDebugInformationRemote,
    SharedNtdll32BaseAddress,
    SharedNtdll32LdrSystemDllInitBlock,
    Wow64SharedPageEntriesCount
} WOW64_SHARED_INFORMATION;

// 32-bit definitions

#define WOW64_POINTER(Type) ULONG

typedef struct _RTL_BALANCED_NODE32
{
    union
    {
        WOW64_POINTER(struct _RTL_BALANCED_NODE *) Children[2];
        struct
        {
            WOW64_POINTER(struct _RTL_BALANCED_NODE *) Left;
            WOW64_POINTER(struct _RTL_BALANCED_NODE *) Right;
        };
    };
    union
    {
        WOW64_POINTER(UCHAR) Red : 1;
        WOW64_POINTER(UCHAR) Balance : 2;
        WOW64_POINTER(ULONG_PTR) ParentValue;
    };
} RTL_BALANCED_NODE32, *PRTL_BALANCED_NODE32;

typedef struct _RTL_RB_TREE32
{
    WOW64_POINTER(PRTL_BALANCED_NODE) Root;
    WOW64_POINTER(PRTL_BALANCED_NODE) Min;
} RTL_RB_TREE32, *PRTL_RB_TREE32;

typedef struct _PEB_LDR_DATA32
{
    ULONG Length;
    BOOLEAN Initialized;
    WOW64_POINTER(HANDLE) SsHandle;
    LIST_ENTRY32 InLoadOrderModuleList;
    LIST_ENTRY32 InMemoryOrderModuleList;
    LIST_ENTRY32 InInitializationOrderModuleList;
    WOW64_POINTER(PVOID) EntryInProgress;
    BOOLEAN ShutdownInProgress;
    WOW64_POINTER(HANDLE) ShutdownThreadId;
} PEB_LDR_DATA32, *PPEB_LDR_DATA32;

typedef struct _LDR_SERVICE_TAG_RECORD32
{
    WOW64_POINTER(struct _LDR_SERVICE_TAG_RECORD *) Next;
    ULONG ServiceTag;
} LDR_SERVICE_TAG_RECORD32, *PLDR_SERVICE_TAG_RECORD32;

typedef struct _LDRP_CSLIST32
{
    WOW64_POINTER(PSINGLE_LIST_ENTRY) Tail;
} LDRP_CSLIST32, *PLDRP_CSLIST32;

typedef struct _LDR_DDAG_NODE32
{
    LIST_ENTRY32 Modules;
    WOW64_POINTER(PLDR_SERVICE_TAG_RECORD) ServiceTagList;
    ULONG LoadCount;
    ULONG LoadWhileUnloadingCount;
    ULONG LowestLink;
    union
    {
        LDRP_CSLIST32 Dependencies;
        SINGLE_LIST_ENTRY32 RemovalLink;
    };
    LDRP_CSLIST32 IncomingDependencies;
    LDR_DDAG_STATE State;
    SINGLE_LIST_ENTRY32 CondenseLink;
    ULONG PreorderNumber;
} LDR_DDAG_NODE32, *PLDR_DDAG_NODE32;

#define LDR_DATA_TABLE_ENTRY_SIZE_WINXP_32 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY32, DdagNode)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN7_32 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY32, BaseNameHashValue)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN8_32 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY32, ImplicitPathOptions)

typedef struct _LDR_DATA_TABLE_ENTRY32
{
    LIST_ENTRY32 InLoadOrderLinks;
    LIST_ENTRY32 InMemoryOrderLinks;
    union
    {
        LIST_ENTRY32 InInitializationOrderLinks;
        LIST_ENTRY32 InProgressLinks;
    };
    WOW64_POINTER(PVOID) DllBase;
    WOW64_POINTER(PVOID) EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING32 FullDllName;
    UNICODE_STRING32 BaseDllName;
    union
    {
        UCHAR FlagGroup[4];
        ULONG Flags;
        struct
        {
            ULONG PackagedBinary : 1;
            ULONG MarkedForRemoval : 1;
            ULONG ImageDll : 1;
            ULONG LoadNotificationsSent : 1;
            ULONG TelemetryEntryProcessed : 1;
            ULONG ProcessStaticImport : 1;
            ULONG InLegacyLists : 1;
            ULONG InIndexes : 1;
            ULONG ShimDll : 1;
            ULONG InExceptionTable : 1;
            ULONG ReservedFlags1 : 2;
            ULONG LoadInProgress : 1;
            ULONG LoadConfigProcessed : 1;
            ULONG EntryProcessed : 1;
            ULONG ProtectDelayLoad : 1;
            ULONG ReservedFlags3 : 2;
            ULONG DontCallForThreads : 1;
            ULONG ProcessAttachCalled : 1;
            ULONG ProcessAttachFailed : 1;
            ULONG CorDeferredValidate : 1;
            ULONG CorImage : 1;
            ULONG DontRelocate : 1;
            ULONG CorILOnly : 1;
            ULONG ChpeImage : 1;
            ULONG ReservedFlags5 : 2;
            ULONG Redirected : 1;
            ULONG ReservedFlags6 : 2;
            ULONG CompatDatabaseProcessed : 1;
        };
    };
    USHORT ObsoleteLoadCount;
    USHORT TlsIndex;
    LIST_ENTRY32 HashLinks;
    ULONG TimeDateStamp;
    WOW64_POINTER(struct _ACTIVATION_CONTEXT *) EntryPointActivationContext;
    WOW64_POINTER(PVOID) Lock;
    WOW64_POINTER(PLDR_DDAG_NODE) DdagNode;
    LIST_ENTRY32 NodeModuleLink;
    WOW64_POINTER(struct _LDRP_LOAD_CONTEXT *) LoadContext;
    WOW64_POINTER(PVOID) ParentDllBase;
    WOW64_POINTER(PVOID) SwitchBackContext;
    RTL_BALANCED_NODE32 BaseAddressIndexNode;
    RTL_BALANCED_NODE32 MappingInfoIndexNode;
    WOW64_POINTER(ULONG_PTR) OriginalBase;
    LARGE_INTEGER LoadTime;
    ULONG BaseNameHashValue;
    LDR_DLL_LOAD_REASON LoadReason;
    ULONG ImplicitPathOptions;
    ULONG ReferenceCount;
    ULONG DependentLoadFlags;
    UCHAR SigningLevel; // since REDSTONE2
} LDR_DATA_TABLE_ENTRY32, *PLDR_DATA_TABLE_ENTRY32;

typedef struct _CURDIR32
{
    UNICODE_STRING32 DosPath;
    WOW64_POINTER(HANDLE) Handle;
} CURDIR32, *PCURDIR32;

typedef struct _RTL_DRIVE_LETTER_CURDIR32
{
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    STRING32 DosPath;
} RTL_DRIVE_LETTER_CURDIR32, *PRTL_DRIVE_LETTER_CURDIR32;

typedef struct _RTL_USER_PROCESS_PARAMETERS32
{
    ULONG MaximumLength;
    ULONG Length;

    ULONG Flags;
    ULONG DebugFlags;

    WOW64_POINTER(HANDLE) ConsoleHandle;
    ULONG ConsoleFlags;
    WOW64_POINTER(HANDLE) StandardInput;
    WOW64_POINTER(HANDLE) StandardOutput;
    WOW64_POINTER(HANDLE) StandardError;

    CURDIR32 CurrentDirectory;
    UNICODE_STRING32 DllPath;
    UNICODE_STRING32 ImagePathName;
    UNICODE_STRING32 CommandLine;
    WOW64_POINTER(PVOID) Environment;

    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;

    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING32 WindowTitle;
    UNICODE_STRING32 DesktopInfo;
    UNICODE_STRING32 ShellInfo;
    UNICODE_STRING32 RuntimeData;
    RTL_DRIVE_LETTER_CURDIR32 CurrentDirectories[RTL_MAX_DRIVE_LETTERS];

    WOW64_POINTER(ULONG_PTR) EnvironmentSize;
    WOW64_POINTER(ULONG_PTR) EnvironmentVersion;
    WOW64_POINTER(PVOID) PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;

    UNICODE_STRING32 RedirectionDllName; // REDSTONE4
    UNICODE_STRING32 HeapPartitionName; // 19H1
    WOW64_POINTER(ULONG_PTR) DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
} RTL_USER_PROCESS_PARAMETERS32, *PRTL_USER_PROCESS_PARAMETERS32;

typedef struct _PEB32
{
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    union
    {
        BOOLEAN BitField;
        struct
        {
            BOOLEAN ImageUsesLargePages : 1;
            BOOLEAN IsProtectedProcess : 1;
            BOOLEAN IsImageDynamicallyRelocated : 1;
            BOOLEAN SkipPatchingUser32Forwarders : 1;
            BOOLEAN IsPackagedProcess : 1;
            BOOLEAN IsAppContainer : 1;
            BOOLEAN IsProtectedProcessLight : 1;
            BOOLEAN IsLongPathAwareProcess : 1;
        };
    };
    WOW64_POINTER(HANDLE) Mutant;

    WOW64_POINTER(PVOID) ImageBaseAddress;
    WOW64_POINTER(PPEB_LDR_DATA) Ldr;
    WOW64_POINTER(PRTL_USER_PROCESS_PARAMETERS) ProcessParameters;
    WOW64_POINTER(PVOID) SubSystemData;
    WOW64_POINTER(PVOID) ProcessHeap;
    WOW64_POINTER(PRTL_CRITICAL_SECTION) FastPebLock;
    WOW64_POINTER(PVOID) AtlThunkSListPtr;
    WOW64_POINTER(PVOID) IFEOKey;
    union
    {
        ULONG CrossProcessFlags;
        struct
        {
            ULONG ProcessInJob : 1;
            ULONG ProcessInitializing : 1;
            ULONG ProcessUsingVEH : 1;
            ULONG ProcessUsingVCH : 1;
            ULONG ProcessUsingFTH : 1;
            ULONG ReservedBits0 : 27;
        };
    };
    union
    {
        WOW64_POINTER(PVOID) KernelCallbackTable;
        WOW64_POINTER(PVOID) UserSharedInfoPtr;
    };
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    WOW64_POINTER(PVOID) ApiSetMap;
    ULONG TlsExpansionCounter;
    WOW64_POINTER(PVOID) TlsBitmap;
    ULONG TlsBitmapBits[2];
    WOW64_POINTER(PVOID) ReadOnlySharedMemoryBase;
    WOW64_POINTER(PVOID) HotpatchInformation;
    WOW64_POINTER(PVOID *) ReadOnlyStaticServerData;
    WOW64_POINTER(PVOID) AnsiCodePageData;
    WOW64_POINTER(PVOID) OemCodePageData;
    WOW64_POINTER(PVOID) UnicodeCaseTableData;

    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;

    LARGE_INTEGER CriticalSectionTimeout;
    WOW64_POINTER(SIZE_T) HeapSegmentReserve;
    WOW64_POINTER(SIZE_T) HeapSegmentCommit;
    WOW64_POINTER(SIZE_T) HeapDeCommitTotalFreeThreshold;
    WOW64_POINTER(SIZE_T) HeapDeCommitFreeBlockThreshold;

    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    WOW64_POINTER(PVOID *) ProcessHeaps;

    WOW64_POINTER(PVOID) GdiSharedHandleTable;
    WOW64_POINTER(PVOID) ProcessStarterHelper;
    ULONG GdiDCAttributeList;

    WOW64_POINTER(PRTL_CRITICAL_SECTION) LoaderLock;

    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    WOW64_POINTER(ULONG_PTR) ActiveProcessAffinityMask;
    GDI_HANDLE_BUFFER32 GdiHandleBuffer;
    WOW64_POINTER(PVOID) PostProcessInitRoutine;

    WOW64_POINTER(PVOID) TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32];

    ULONG SessionId;

    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    WOW64_POINTER(PVOID) pShimData;
    WOW64_POINTER(PVOID) AppCompatInfo;

    UNICODE_STRING32 CSDVersion;

    WOW64_POINTER(PVOID) ActivationContextData;
    WOW64_POINTER(PVOID) ProcessAssemblyStorageMap;
    WOW64_POINTER(PVOID) SystemDefaultActivationContextData;
    WOW64_POINTER(PVOID) SystemAssemblyStorageMap;

    WOW64_POINTER(SIZE_T) MinimumStackCommit;

    WOW64_POINTER(PVOID) SparePointers[4];
    ULONG SpareUlongs[5];
    //WOW64_POINTER(PVOID *) FlsCallback;
    //LIST_ENTRY32 FlsListHead;
    //WOW64_POINTER(PVOID) FlsBitmap;
    //ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
    //ULONG FlsHighIndex;

    WOW64_POINTER(PVOID) WerRegistrationData;
    WOW64_POINTER(PVOID) WerShipAssertPtr;
    WOW64_POINTER(PVOID) pContextData;
    WOW64_POINTER(PVOID) pImageHeaderHash;
    union
    {
        ULONG TracingFlags;
        struct
        {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG LibLoaderTracingEnabled : 1;
            ULONG SpareTracingBits : 29;
        };
    };
    ULONGLONG CsrServerReadOnlySharedMemoryBase;
    WOW64_POINTER(PVOID) TppWorkerpListLock;
    LIST_ENTRY32 TppWorkerpList;
    WOW64_POINTER(PVOID) WaitOnAddressHashTable[128];
    WOW64_POINTER(PVOID) TelemetryCoverageHeader; // REDSTONE3
    ULONG CloudFileFlags;
    ULONG CloudFileDiagFlags; // REDSTONE4
    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderCompatibilityModeReserved[7];
} PEB32, *PPEB32;

C_ASSERT(FIELD_OFFSET(PEB32, IFEOKey) == 0x024);
C_ASSERT(FIELD_OFFSET(PEB32, UnicodeCaseTableData) == 0x060);
C_ASSERT(FIELD_OFFSET(PEB32, SystemAssemblyStorageMap) == 0x204);
C_ASSERT(FIELD_OFFSET(PEB32, pImageHeaderHash) == 0x23c);
C_ASSERT(FIELD_OFFSET(PEB32, WaitOnAddressHashTable) == 0x25c);
//C_ASSERT(sizeof(PEB32) == 0x460); // REDSTONE3
C_ASSERT(sizeof(PEB32) == 0x470);

#define GDI_BATCH_BUFFER_SIZE 310

typedef struct _GDI_TEB_BATCH32
{
    ULONG Offset;
    WOW64_POINTER(ULONG_PTR) HDC;
    ULONG Buffer[GDI_BATCH_BUFFER_SIZE];
} GDI_TEB_BATCH32, *PGDI_TEB_BATCH32;

typedef struct _TEB32
{
    NT_TIB32 NtTib;

    WOW64_POINTER(PVOID) EnvironmentPointer;
    CLIENT_ID32 ClientId;
    WOW64_POINTER(PVOID) ActiveRpcHandle;
    WOW64_POINTER(PVOID) ThreadLocalStoragePointer;
    WOW64_POINTER(PPEB) ProcessEnvironmentBlock;

    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    WOW64_POINTER(PVOID) CsrClientThread;
    WOW64_POINTER(PVOID) Win32ThreadInfo;
    ULONG User32Reserved[26];
    ULONG UserReserved[5];
    WOW64_POINTER(PVOID) WOW32Reserved;
    LCID CurrentLocale;
    ULONG FpSoftwareStatusRegister;
    WOW64_POINTER(PVOID) ReservedForDebuggerInstrumentation[16];
    WOW64_POINTER(PVOID) SystemReserved1[36];
    UCHAR WorkingOnBehalfTicket[8];
    NTSTATUS ExceptionCode;

    WOW64_POINTER(PVOID) ActivationContextStackPointer;
    WOW64_POINTER(ULONG_PTR) InstrumentationCallbackSp;
    WOW64_POINTER(ULONG_PTR) InstrumentationCallbackPreviousPc;
    WOW64_POINTER(ULONG_PTR) InstrumentationCallbackPreviousSp;
    BOOLEAN InstrumentationCallbackDisabled;
    UCHAR SpareBytes[23];
    ULONG TxFsContext;

    GDI_TEB_BATCH32 GdiTebBatch;
    CLIENT_ID32 RealClientId;
    WOW64_POINTER(HANDLE) GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    WOW64_POINTER(PVOID) GdiThreadLocalInfo;
    WOW64_POINTER(ULONG_PTR) Win32ClientInfo[62];
    WOW64_POINTER(PVOID) glDispatchTable[233];
    WOW64_POINTER(ULONG_PTR) glReserved1[29];
    WOW64_POINTER(PVOID) glReserved2;
    WOW64_POINTER(PVOID) glSectionInfo;
    WOW64_POINTER(PVOID) glSection;
    WOW64_POINTER(PVOID) glTable;
    WOW64_POINTER(PVOID) glCurrentRC;
    WOW64_POINTER(PVOID) glContext;

    NTSTATUS LastStatusValue;
    UNICODE_STRING32 StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[261];

    WOW64_POINTER(PVOID) DeallocationStack;
    WOW64_POINTER(PVOID) TlsSlots[64];
    LIST_ENTRY32 TlsLinks;

    WOW64_POINTER(PVOID) Vdm;
    WOW64_POINTER(PVOID) ReservedForNtRpc;
    WOW64_POINTER(PVOID) DbgSsReserved[2];

    ULONG HardErrorMode;
    WOW64_POINTER(PVOID) Instrumentation[9];
    GUID ActivityId;

    WOW64_POINTER(PVOID) SubProcessTag;
    WOW64_POINTER(PVOID) PerflibData;
    WOW64_POINTER(PVOID) EtwTraceData;
    WOW64_POINTER(PVOID) WinSockData;
    ULONG GdiBatchCount;

    union
    {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        ULONG IdealProcessorValue;
        struct
        {
            UCHAR ReservedPad0;
            UCHAR ReservedPad1;
            UCHAR ReservedPad2;
            UCHAR IdealProcessor;
        };
    };

    ULONG GuaranteedStackBytes;
    WOW64_POINTER(PVOID) ReservedForPerf;
    WOW64_POINTER(PVOID) ReservedForOle;
    ULONG WaitingOnLoaderLock;
    WOW64_POINTER(PVOID) SavedPriorityState;
    WOW64_POINTER(ULONG_PTR) ReservedForCodeCoverage;
    WOW64_POINTER(PVOID) ThreadPoolData;
    WOW64_POINTER(PVOID *) TlsExpansionSlots;

    ULONG MuiGeneration;
    ULONG IsImpersonating;
    WOW64_POINTER(PVOID) NlsCache;
    WOW64_POINTER(PVOID) pShimData;
    USHORT HeapVirtualAffinity;
    USHORT LowFragHeapDataSlot;
    WOW64_POINTER(HANDLE) CurrentTransactionHandle;
    WOW64_POINTER(PTEB_ACTIVE_FRAME) ActiveFrame;
    WOW64_POINTER(PVOID) FlsData;

    WOW64_POINTER(PVOID) PreferredLanguages;
    WOW64_POINTER(PVOID) UserPrefLanguages;
    WOW64_POINTER(PVOID) MergedPrefLanguages;
    ULONG MuiImpersonation;

    union
    {
        USHORT CrossTebFlags;
        USHORT SpareCrossTebBits : 16;
    };
    union
    {
        USHORT SameTebFlags;
        struct
        {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SpareSameTebBits : 2;
        };
    };

    WOW64_POINTER(PVOID) TxnScopeEnterCallback;
    WOW64_POINTER(PVOID) TxnScopeExitCallback;
    WOW64_POINTER(PVOID) TxnScopeContext;
    ULONG LockCount;
    LONG WowTebOffset;
    WOW64_POINTER(PVOID) ResourceRetValue;
    WOW64_POINTER(PVOID) ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;
} TEB32, *PTEB32;

C_ASSERT(FIELD_OFFSET(TEB32, ProcessEnvironmentBlock) == 0x030);
C_ASSERT(FIELD_OFFSET(TEB32, ExceptionCode) == 0x1a4);
C_ASSERT(FIELD_OFFSET(TEB32, TxFsContext) == 0x1d0);
C_ASSERT(FIELD_OFFSET(TEB32, glContext) == 0xbf0);
C_ASSERT(FIELD_OFFSET(TEB32, StaticUnicodeBuffer) == 0xc00);
C_ASSERT(FIELD_OFFSET(TEB32, TlsLinks) == 0xf10);
C_ASSERT(FIELD_OFFSET(TEB32, DbgSsReserved) == 0xf20);
C_ASSERT(FIELD_OFFSET(TEB32, ActivityId) == 0xf50);
C_ASSERT(FIELD_OFFSET(TEB32, GdiBatchCount) == 0xf70);
C_ASSERT(FIELD_OFFSET(TEB32, TlsExpansionSlots) == 0xf94);
C_ASSERT(FIELD_OFFSET(TEB32, FlsData) == 0xfb4);
C_ASSERT(FIELD_OFFSET(TEB32, MuiImpersonation) == 0xfc4);
C_ASSERT(FIELD_OFFSET(TEB32, ReservedForCrt) == 0xfe8);
C_ASSERT(FIELD_OFFSET(TEB32, EffectiveContainerId) == 0xff0);
C_ASSERT(sizeof(TEB32) == 0x1000);

// Conversion

FORCEINLINE VOID UStr32ToUStr(
    _Out_ PUNICODE_STRING Destination,
    _In_ PUNICODE_STRING32 Source
    )
{
    Destination->Length = Source->Length;
    Destination->MaximumLength = Source->MaximumLength;
    Destination->Buffer = (PWCH)UlongToPtr(Source->Buffer);
}

FORCEINLINE VOID UStrToUStr32(
    _Out_ PUNICODE_STRING32 Destination,
    _In_ PUNICODE_STRING Source
    )
{
    Destination->Length = Source->Length;
    Destination->MaximumLength = Source->MaximumLength;
    Destination->Buffer = PtrToUlong(Source->Buffer);
}
 


#include <ntlsa.h>
// #include <ntsam.h>
#define SAM_MAXIMUM_LOOKUP_COUNT (1000)
#define SAM_MAXIMUM_LOOKUP_LENGTH (32000)
#define SAM_MAX_PASSWORD_LENGTH (256)
#define SAM_PASSWORD_ENCRYPTION_SALT_LEN (16)

typedef PVOID SAM_HANDLE, *PSAM_HANDLE;
typedef ULONG SAM_ENUMERATE_HANDLE, *PSAM_ENUMERATE_HANDLE;

typedef struct _SAM_RID_ENUMERATION
{
    ULONG RelativeId;
    UNICODE_STRING Name;
} SAM_RID_ENUMERATION, *PSAM_RID_ENUMERATION;

typedef struct _SAM_SID_ENUMERATION
{
    PSID Sid;
    UNICODE_STRING Name;
} SAM_SID_ENUMERATION, *PSAM_SID_ENUMERATION;

typedef struct _SAM_BYTE_ARRAY
{
    ULONG Size;
    _Field_size_bytes_(Size) PUCHAR Data;
} SAM_BYTE_ARRAY, *PSAM_BYTE_ARRAY;

typedef struct _SAM_BYTE_ARRAY_32K
{
    ULONG Size;
    _Field_size_bytes_(Size) PUCHAR Data;
} SAM_BYTE_ARRAY_32K, *PSAM_BYTE_ARRAY_32K;

typedef SAM_BYTE_ARRAY_32K SAM_SHELL_OBJECT_PROPERTIES, *PSAM_SHELL_OBJECT_PROPERTIES;

// Basic

NTSTATUS
NTAPI
SamFreeMemory(
    _In_ PVOID Buffer
    );

NTSTATUS
NTAPI
SamCloseHandle(
    _In_ SAM_HANDLE SamHandle
    );

_Check_return_
NTSTATUS
NTAPI
SamSetSecurityObject(
    _In_ SAM_HANDLE ObjectHandle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

_Check_return_
NTSTATUS
NTAPI
SamQuerySecurityObject(
    _In_ SAM_HANDLE ObjectHandle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _Outptr_ PSECURITY_DESCRIPTOR *SecurityDescriptor
    );

_Check_return_
NTSTATUS
NTAPI
SamRidToSid(
    _In_ SAM_HANDLE ObjectHandle,
    _In_ ULONG Rid,
    _Outptr_ PSID *Sid
    );

// Server

#define SAM_SERVER_CONNECT 0x0001
#define SAM_SERVER_SHUTDOWN 0x0002
#define SAM_SERVER_INITIALIZE 0x0004
#define SAM_SERVER_CREATE_DOMAIN 0x0008
#define SAM_SERVER_ENUMERATE_DOMAINS 0x0010
#define SAM_SERVER_LOOKUP_DOMAIN 0x0020

#define SAM_SERVER_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED     | \
    SAM_SERVER_CONNECT | \
    SAM_SERVER_INITIALIZE | \
    SAM_SERVER_CREATE_DOMAIN | \
    SAM_SERVER_SHUTDOWN | \
    SAM_SERVER_ENUMERATE_DOMAINS | \
    SAM_SERVER_LOOKUP_DOMAIN)

#define SAM_SERVER_READ (STANDARD_RIGHTS_READ | \
    SAM_SERVER_ENUMERATE_DOMAINS)

#define SAM_SERVER_WRITE (STANDARD_RIGHTS_WRITE | \
    SAM_SERVER_INITIALIZE | \
    SAM_SERVER_CREATE_DOMAIN | \
    SAM_SERVER_SHUTDOWN)

#define SAM_SERVER_EXECUTE (STANDARD_RIGHTS_EXECUTE | \
    SAM_SERVER_CONNECT | \
    SAM_SERVER_LOOKUP_DOMAIN)

// Functions

_Check_return_
NTSTATUS
NTAPI
SamConnect(
    _In_opt_ PUNICODE_STRING ServerName,
    _Out_ PSAM_HANDLE ServerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
    );

_Check_return_
NTSTATUS
NTAPI
SamShutdownSamServer(
    _In_ SAM_HANDLE ServerHandle
    );

// Domain

#define DOMAIN_READ_PASSWORD_PARAMETERS 0x0001
#define DOMAIN_WRITE_PASSWORD_PARAMS 0x0002
#define DOMAIN_READ_OTHER_PARAMETERS 0x0004
#define DOMAIN_WRITE_OTHER_PARAMETERS 0x0008
#define DOMAIN_CREATE_USER 0x0010
#define DOMAIN_CREATE_GROUP 0x0020
#define DOMAIN_CREATE_ALIAS 0x0040
#define DOMAIN_GET_ALIAS_MEMBERSHIP 0x0080
#define DOMAIN_LIST_ACCOUNTS 0x0100
#define DOMAIN_LOOKUP 0x0200
#define DOMAIN_ADMINISTER_SERVER 0x0400

#define DOMAIN_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | \
    DOMAIN_READ_OTHER_PARAMETERS | \
    DOMAIN_WRITE_OTHER_PARAMETERS | \
    DOMAIN_WRITE_PASSWORD_PARAMS | \
    DOMAIN_CREATE_USER | \
    DOMAIN_CREATE_GROUP | \
    DOMAIN_CREATE_ALIAS | \
    DOMAIN_GET_ALIAS_MEMBERSHIP | \
    DOMAIN_LIST_ACCOUNTS | \
    DOMAIN_READ_PASSWORD_PARAMETERS | \
    DOMAIN_LOOKUP | \
    DOMAIN_ADMINISTER_SERVER)

#define DOMAIN_READ (STANDARD_RIGHTS_READ | \
    DOMAIN_GET_ALIAS_MEMBERSHIP | \
    DOMAIN_READ_OTHER_PARAMETERS)

#define DOMAIN_WRITE (STANDARD_RIGHTS_WRITE | \
    DOMAIN_WRITE_OTHER_PARAMETERS | \
    DOMAIN_WRITE_PASSWORD_PARAMS | \
    DOMAIN_CREATE_USER | \
    DOMAIN_CREATE_GROUP | \
    DOMAIN_CREATE_ALIAS | \
    DOMAIN_ADMINISTER_SERVER)

#define DOMAIN_EXECUTE (STANDARD_RIGHTS_EXECUTE | \
    DOMAIN_READ_PASSWORD_PARAMETERS | \
    DOMAIN_LIST_ACCOUNTS | \
    DOMAIN_LOOKUP)

#define DOMAIN_PROMOTION_INCREMENT { 0x0, 0x10 }
#define DOMAIN_PROMOTION_MASK { 0x0, 0xfffffff0 }

// SamQueryInformationDomain/SamSetInformationDomain types

typedef enum _DOMAIN_INFORMATION_CLASS
{
    DomainPasswordInformation = 1,
    DomainGeneralInformation,
    DomainLogoffInformation,
    DomainOemInformation,
    DomainNameInformation,
    DomainReplicationInformation,
    DomainServerRoleInformation,
    DomainModifiedInformation,
    DomainStateInformation,
    DomainUasInformation,
    DomainGeneralInformation2,
    DomainLockoutInformation,
    DomainModifiedInformation2
} DOMAIN_INFORMATION_CLASS;

typedef enum _DOMAIN_SERVER_ENABLE_STATE
{
    DomainServerEnabled = 1,
    DomainServerDisabled
} DOMAIN_SERVER_ENABLE_STATE, *PDOMAIN_SERVER_ENABLE_STATE;

typedef enum _DOMAIN_SERVER_ROLE
{
    DomainServerRoleBackup = 2,
    DomainServerRolePrimary
} DOMAIN_SERVER_ROLE, *PDOMAIN_SERVER_ROLE;

#include <pshpack4.h>
typedef struct _DOMAIN_GENERAL_INFORMATION
{
    LARGE_INTEGER ForceLogoff;
    UNICODE_STRING OemInformation;
    UNICODE_STRING DomainName;
    UNICODE_STRING ReplicaSourceNodeName;
    LARGE_INTEGER DomainModifiedCount;
    DOMAIN_SERVER_ENABLE_STATE DomainServerState;
    DOMAIN_SERVER_ROLE DomainServerRole;
    BOOLEAN UasCompatibilityRequired;
    ULONG UserCount;
    ULONG GroupCount;
    ULONG AliasCount;
} DOMAIN_GENERAL_INFORMATION, *PDOMAIN_GENERAL_INFORMATION;
#include <poppack.h>

#include <pshpack4.h>
typedef struct _DOMAIN_GENERAL_INFORMATION2
{
    DOMAIN_GENERAL_INFORMATION I1;
    LARGE_INTEGER LockoutDuration; // delta time
    LARGE_INTEGER LockoutObservationWindow; // delta time
    USHORT LockoutThreshold;
} DOMAIN_GENERAL_INFORMATION2, *PDOMAIN_GENERAL_INFORMATION2;
#include <poppack.h>

typedef struct _DOMAIN_UAS_INFORMATION
{
    BOOLEAN UasCompatibilityRequired;
} DOMAIN_UAS_INFORMATION;

#ifndef _DOMAIN_PASSWORD_INFORMATION_DEFINED // defined in ntsecapi.h
#define _DOMAIN_PASSWORD_INFORMATION_DEFINED

typedef struct _DOMAIN_PASSWORD_INFORMATION
{
    USHORT MinPasswordLength;
    USHORT PasswordHistoryLength;
    ULONG PasswordProperties;
    LARGE_INTEGER MaxPasswordAge;
    LARGE_INTEGER MinPasswordAge;
} DOMAIN_PASSWORD_INFORMATION, *PDOMAIN_PASSWORD_INFORMATION;

// PasswordProperties flags

#define DOMAIN_PASSWORD_COMPLEX 0x00000001L
#define DOMAIN_PASSWORD_NO_ANON_CHANGE 0x00000002L
#define DOMAIN_PASSWORD_NO_CLEAR_CHANGE 0x00000004L
#define DOMAIN_LOCKOUT_ADMINS 0x00000008L
#define DOMAIN_PASSWORD_STORE_CLEARTEXT 0x00000010L
#define DOMAIN_REFUSE_PASSWORD_CHANGE 0x00000020L
#define DOMAIN_NO_LM_OWF_CHANGE 0x00000040L

#endif

typedef enum _DOMAIN_PASSWORD_CONSTRUCTION
{
    DomainPasswordSimple = 1,
    DomainPasswordComplex
} DOMAIN_PASSWORD_CONSTRUCTION;

typedef struct _DOMAIN_LOGOFF_INFORMATION
{
    LARGE_INTEGER ForceLogoff;
} DOMAIN_LOGOFF_INFORMATION, *PDOMAIN_LOGOFF_INFORMATION;

typedef struct _DOMAIN_OEM_INFORMATION
{
    UNICODE_STRING OemInformation;
} DOMAIN_OEM_INFORMATION, *PDOMAIN_OEM_INFORMATION;

typedef struct _DOMAIN_NAME_INFORMATION
{
    UNICODE_STRING DomainName;
} DOMAIN_NAME_INFORMATION, *PDOMAIN_NAME_INFORMATION;

typedef struct _DOMAIN_SERVER_ROLE_INFORMATION
{
    DOMAIN_SERVER_ROLE DomainServerRole;
} DOMAIN_SERVER_ROLE_INFORMATION, *PDOMAIN_SERVER_ROLE_INFORMATION;

typedef struct _DOMAIN_REPLICATION_INFORMATION
{
    UNICODE_STRING ReplicaSourceNodeName;
} DOMAIN_REPLICATION_INFORMATION, *PDOMAIN_REPLICATION_INFORMATION;

typedef struct _DOMAIN_MODIFIED_INFORMATION
{
    LARGE_INTEGER DomainModifiedCount;
    LARGE_INTEGER CreationTime;
} DOMAIN_MODIFIED_INFORMATION, *PDOMAIN_MODIFIED_INFORMATION;

typedef struct _DOMAIN_MODIFIED_INFORMATION2
{
    LARGE_INTEGER DomainModifiedCount;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER ModifiedCountAtLastPromotion;
} DOMAIN_MODIFIED_INFORMATION2, *PDOMAIN_MODIFIED_INFORMATION2;

typedef struct _DOMAIN_STATE_INFORMATION
{
    DOMAIN_SERVER_ENABLE_STATE DomainServerState;
} DOMAIN_STATE_INFORMATION, *PDOMAIN_STATE_INFORMATION;

typedef struct _DOMAIN_LOCKOUT_INFORMATION
{
    LARGE_INTEGER LockoutDuration; // delta time
    LARGE_INTEGER LockoutObservationWindow; // delta time
    USHORT LockoutThreshold; // zero means no lockout
} DOMAIN_LOCKOUT_INFORMATION, *PDOMAIN_LOCKOUT_INFORMATION;

// SamQueryDisplayInformation types

typedef enum _DOMAIN_DISPLAY_INFORMATION
{
    DomainDisplayUser = 1,
    DomainDisplayMachine,
    DomainDisplayGroup,
    DomainDisplayOemUser,
    DomainDisplayOemGroup,
    DomainDisplayServer
} DOMAIN_DISPLAY_INFORMATION, *PDOMAIN_DISPLAY_INFORMATION;

typedef struct _DOMAIN_DISPLAY_USER
{
    ULONG Index;
    ULONG Rid;
    ULONG AccountControl;
    UNICODE_STRING LogonName;
    UNICODE_STRING AdminComment;
    UNICODE_STRING FullName;
} DOMAIN_DISPLAY_USER, *PDOMAIN_DISPLAY_USER;

typedef struct _DOMAIN_DISPLAY_MACHINE
{
    ULONG Index;
    ULONG Rid;
    ULONG AccountControl;
    UNICODE_STRING Machine;
    UNICODE_STRING Comment;
} DOMAIN_DISPLAY_MACHINE, *PDOMAIN_DISPLAY_MACHINE;

typedef struct _DOMAIN_DISPLAY_GROUP
{
    ULONG Index;
    ULONG Rid;
    ULONG Attributes;
    UNICODE_STRING Group;
    UNICODE_STRING Comment;
} DOMAIN_DISPLAY_GROUP, *PDOMAIN_DISPLAY_GROUP;

typedef struct _DOMAIN_DISPLAY_OEM_USER
{
    ULONG Index;
    OEM_STRING User;
} DOMAIN_DISPLAY_OEM_USER, *PDOMAIN_DISPLAY_OEM_USER;

typedef struct _DOMAIN_DISPLAY_OEM_GROUP
{
    ULONG Index;
    OEM_STRING Group;
} DOMAIN_DISPLAY_OEM_GROUP, *PDOMAIN_DISPLAY_OEM_GROUP;

// SamQueryLocalizableAccountsInDomain types

typedef enum _DOMAIN_LOCALIZABLE_ACCOUNTS_INFORMATION
{
    DomainLocalizableAccountsBasic = 1,
} DOMAIN_LOCALIZABLE_ACCOUNTS_INFORMATION, *PDOMAIN_LOCALIZABLE_ACCOUNTS_INFORMATION;

typedef struct _DOMAIN_LOCALIZABLE_ACCOUNTS_ENTRY
{
    ULONG Rid;
    SID_NAME_USE Use;
    UNICODE_STRING Name;
    UNICODE_STRING AdminComment;
} DOMAIN_LOCALIZABLE_ACCOUNT_ENTRY, *PDOMAIN_LOCALIZABLE_ACCOUNT_ENTRY;

typedef struct _DOMAIN_LOCALIZABLE_ACCOUNTS
{
    ULONG Count;
    _Field_size_(Count) DOMAIN_LOCALIZABLE_ACCOUNT_ENTRY *Entries;
} DOMAIN_LOCALIZABLE_ACCOUNTS_BASIC, *PDOMAIN_LOCALIZABLE_ACCOUNTS_BASIC;

typedef union _DOMAIN_LOCALIZABLE_INFO_BUFFER
{
    DOMAIN_LOCALIZABLE_ACCOUNTS_BASIC Basic;
} DOMAIN_LOCALIZABLE_ACCOUNTS_INFO_BUFFER, *PDOMAIN_LOCALIZABLE_ACCOUNTS_INFO_BUFFER;

// Functions

_Check_return_
NTSTATUS
NTAPI
SamLookupDomainInSamServer(
    _In_ SAM_HANDLE ServerHandle,
    _In_ PUNICODE_STRING Name,
    _Outptr_ PSID *DomainId
    );

_Check_return_
NTSTATUS
NTAPI
SamEnumerateDomainsInSamServer(
    _In_ SAM_HANDLE ServerHandle,
    _Inout_ PSAM_ENUMERATE_HANDLE EnumerationContext,
    _Outptr_ PVOID *Buffer, // PSAM_SID_ENUMERATION *Buffer
    _In_ ULONG PreferedMaximumLength,
    _Out_ PULONG CountReturned
    );

_Check_return_
NTSTATUS
NTAPI
SamOpenDomain(
    _In_ SAM_HANDLE ServerHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PSID DomainId,
    _Out_ PSAM_HANDLE DomainHandle
    );

_Check_return_
NTSTATUS
NTAPI
SamQueryInformationDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ DOMAIN_INFORMATION_CLASS DomainInformationClass,
    _Outptr_ PVOID *Buffer
    );

_Check_return_
NTSTATUS
NTAPI
SamSetInformationDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ DOMAIN_INFORMATION_CLASS DomainInformationClass,
    _In_ PVOID DomainInformation
    );

_Check_return_
NTSTATUS
NTAPI
SamLookupNamesInDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ ULONG Count,
    _In_reads_(Count) PUNICODE_STRING Names,
    _Out_ _Deref_post_count_(Count) PULONG *RelativeIds,
    _Out_ _Deref_post_count_(Count) PSID_NAME_USE *Use
    );

_Check_return_
NTSTATUS
NTAPI
SamLookupIdsInDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ ULONG Count,
    _In_reads_(Count) PULONG RelativeIds,
    _Out_ _Deref_post_count_(Count) PUNICODE_STRING *Names,
    _Out_ _Deref_post_opt_count_(Count) PSID_NAME_USE *Use
    );

_Check_return_
NTSTATUS
NTAPI
SamRemoveMemberFromForeignDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ PSID MemberId
    );

_Check_return_
NTSTATUS
NTAPI
SamQueryLocalizableAccountsInDomain(
    _In_ SAM_HANDLE Domain,
    _In_ ULONG Flags,
    _In_ ULONG LanguageId,
    _In_ DOMAIN_LOCALIZABLE_ACCOUNTS_INFORMATION Class,
    _Outptr_ PVOID *Buffer
    );

// Group

#define GROUP_READ_INFORMATION 0x0001
#define GROUP_WRITE_ACCOUNT 0x0002
#define GROUP_ADD_MEMBER 0x0004
#define GROUP_REMOVE_MEMBER 0x0008
#define GROUP_LIST_MEMBERS 0x0010

#define GROUP_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | \
    GROUP_LIST_MEMBERS | \
    GROUP_WRITE_ACCOUNT | \
    GROUP_ADD_MEMBER | \
    GROUP_REMOVE_MEMBER | \
    GROUP_READ_INFORMATION)

#define GROUP_READ (STANDARD_RIGHTS_READ | \
    GROUP_LIST_MEMBERS)

#define GROUP_WRITE (STANDARD_RIGHTS_WRITE | \
    GROUP_WRITE_ACCOUNT | \
    GROUP_ADD_MEMBER | \
    GROUP_REMOVE_MEMBER)

#define GROUP_EXECUTE (STANDARD_RIGHTS_EXECUTE | \
    GROUP_READ_INFORMATION)

typedef struct _GROUP_MEMBERSHIP
{
    ULONG RelativeId;
    ULONG Attributes;
} GROUP_MEMBERSHIP, *PGROUP_MEMBERSHIP;

// SamQueryInformationGroup/SamSetInformationGroup types

typedef enum _GROUP_INFORMATION_CLASS
{
    GroupGeneralInformation = 1,
    GroupNameInformation,
    GroupAttributeInformation,
    GroupAdminCommentInformation,
    GroupReplicationInformation
} GROUP_INFORMATION_CLASS;

typedef struct _GROUP_GENERAL_INFORMATION
{
    UNICODE_STRING Name;
    ULONG Attributes;
    ULONG MemberCount;
    UNICODE_STRING AdminComment;
} GROUP_GENERAL_INFORMATION, *PGROUP_GENERAL_INFORMATION;

typedef struct _GROUP_NAME_INFORMATION
{
    UNICODE_STRING Name;
} GROUP_NAME_INFORMATION, *PGROUP_NAME_INFORMATION;

typedef struct _GROUP_ATTRIBUTE_INFORMATION
{
    ULONG Attributes;
} GROUP_ATTRIBUTE_INFORMATION, *PGROUP_ATTRIBUTE_INFORMATION;

typedef struct _GROUP_ADM_COMMENT_INFORMATION
{
    UNICODE_STRING AdminComment;
} GROUP_ADM_COMMENT_INFORMATION, *PGROUP_ADM_COMMENT_INFORMATION;

// Functions

_Check_return_
NTSTATUS
NTAPI
SamEnumerateGroupsInDomain(
    _In_ SAM_HANDLE DomainHandle,
    _Inout_ PSAM_ENUMERATE_HANDLE EnumerationContext,
    _Outptr_ PVOID *Buffer, // PSAM_RID_ENUMERATION *
    _In_ ULONG PreferedMaximumLength,
    _Out_ PULONG CountReturned
    );

_Check_return_
NTSTATUS
NTAPI
SamCreateGroupInDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ PUNICODE_STRING AccountName,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PSAM_HANDLE GroupHandle,
    _Out_ PULONG RelativeId
    );

_Check_return_
NTSTATUS
NTAPI
SamOpenGroup(
    _In_ SAM_HANDLE DomainHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG GroupId,
    _Out_ PSAM_HANDLE GroupHandle
    );

_Check_return_
NTSTATUS
NTAPI
SamDeleteGroup(
    _In_ SAM_HANDLE GroupHandle
    );

_Check_return_
NTSTATUS
NTAPI
SamQueryInformationGroup(
    _In_ SAM_HANDLE GroupHandle,
    _In_ GROUP_INFORMATION_CLASS GroupInformationClass,
    _Outptr_ PVOID *Buffer
    );

_Check_return_
NTSTATUS
NTAPI
SamSetInformationGroup(
    _In_ SAM_HANDLE GroupHandle,
    _In_ GROUP_INFORMATION_CLASS GroupInformationClass,
    _In_ PVOID Buffer
    );

_Check_return_
NTSTATUS
NTAPI
SamAddMemberToGroup(
    _In_ SAM_HANDLE GroupHandle,
    _In_ ULONG MemberId,
    _In_ ULONG Attributes
    );

_Check_return_
NTSTATUS
NTAPI
SamRemoveMemberFromGroup(
    _In_ SAM_HANDLE GroupHandle,
    _In_ ULONG MemberId
    );

_Check_return_
NTSTATUS
NTAPI
SamGetMembersInGroup(
    _In_ SAM_HANDLE GroupHandle,
    _Out_ _Deref_post_count_(*MemberCount) PULONG *MemberIds,
    _Out_ _Deref_post_count_(*MemberCount) PULONG *Attributes,
    _Out_ PULONG MemberCount
    );

_Check_return_
NTSTATUS
NTAPI
SamSetMemberAttributesOfGroup(
    _In_ SAM_HANDLE GroupHandle,
    _In_ ULONG MemberId,
    _In_ ULONG Attributes
    );

// Alias

#define ALIAS_ADD_MEMBER 0x0001
#define ALIAS_REMOVE_MEMBER 0x0002
#define ALIAS_LIST_MEMBERS 0x0004
#define ALIAS_READ_INFORMATION 0x0008
#define ALIAS_WRITE_ACCOUNT 0x0010

#define ALIAS_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | \
    ALIAS_READ_INFORMATION | \
    ALIAS_WRITE_ACCOUNT | \
    ALIAS_LIST_MEMBERS | \
    ALIAS_ADD_MEMBER | \
    ALIAS_REMOVE_MEMBER)

#define ALIAS_READ (STANDARD_RIGHTS_READ | \
    ALIAS_LIST_MEMBERS)

#define ALIAS_WRITE (STANDARD_RIGHTS_WRITE | \
    ALIAS_WRITE_ACCOUNT | \
    ALIAS_ADD_MEMBER | \
    ALIAS_REMOVE_MEMBER)

#define ALIAS_EXECUTE (STANDARD_RIGHTS_EXECUTE | \
    ALIAS_READ_INFORMATION)

// SamQueryInformationAlias/SamSetInformationAlias types

typedef enum _ALIAS_INFORMATION_CLASS
{
    AliasGeneralInformation = 1,
    AliasNameInformation,
    AliasAdminCommentInformation,
    AliasReplicationInformation,
    AliasExtendedInformation,
} ALIAS_INFORMATION_CLASS;

typedef struct _ALIAS_GENERAL_INFORMATION
{
    UNICODE_STRING Name;
    ULONG MemberCount;
    UNICODE_STRING AdminComment;
} ALIAS_GENERAL_INFORMATION,  *PALIAS_GENERAL_INFORMATION;

typedef struct _ALIAS_NAME_INFORMATION
{
    UNICODE_STRING Name;
} ALIAS_NAME_INFORMATION, *PALIAS_NAME_INFORMATION;

typedef struct _ALIAS_ADM_COMMENT_INFORMATION
{
    UNICODE_STRING AdminComment;
} ALIAS_ADM_COMMENT_INFORMATION, *PALIAS_ADM_COMMENT_INFORMATION;

#define ALIAS_ALL_NAME (0x00000001L)
#define ALIAS_ALL_MEMBER_COUNT (0x00000002L)
#define ALIAS_ALL_ADMIN_COMMENT (0x00000004L)
#define ALIAS_ALL_SHELL_ADMIN_OBJECT_PROPERTIES (0x00000008L)

typedef struct _ALIAS_EXTENDED_INFORMATION
{
    ULONG WhichFields;
    SAM_SHELL_OBJECT_PROPERTIES ShellAdminObjectProperties;
} ALIAS_EXTENDED_INFORMATION, *PALIAS_EXTENDED_INFORMATION;

// Functions

_Check_return_
NTSTATUS
NTAPI
SamEnumerateAliasesInDomain(
    _In_ SAM_HANDLE DomainHandle,
    _Inout_ PSAM_ENUMERATE_HANDLE EnumerationContext,
    _Outptr_ PVOID *Buffer, // PSAM_RID_ENUMERATION *Buffer
    _In_ ULONG PreferedMaximumLength,
    _Out_ PULONG CountReturned
    );

_Check_return_
NTSTATUS
NTAPI
SamCreateAliasInDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ PUNICODE_STRING AccountName,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PSAM_HANDLE AliasHandle,
    _Out_ PULONG RelativeId
    );

_Check_return_
NTSTATUS
NTAPI
SamOpenAlias(
    _In_ SAM_HANDLE DomainHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG AliasId,
    _Out_ PSAM_HANDLE AliasHandle
    );

_Check_return_
NTSTATUS
NTAPI
SamDeleteAlias(
    _In_ SAM_HANDLE AliasHandle
    );

_Check_return_
NTSTATUS
NTAPI
SamQueryInformationAlias(
    _In_ SAM_HANDLE AliasHandle,
    _In_ ALIAS_INFORMATION_CLASS AliasInformationClass,
    _Outptr_ PVOID *Buffer
    );

_Check_return_
NTSTATUS
NTAPI
SamSetInformationAlias(
    _In_ SAM_HANDLE AliasHandle,
    _In_ ALIAS_INFORMATION_CLASS AliasInformationClass,
    _In_ PVOID Buffer
    );

_Check_return_
NTSTATUS
NTAPI
SamAddMemberToAlias(
    _In_ SAM_HANDLE AliasHandle,
    _In_ PSID MemberId
    );

_Check_return_
NTSTATUS
NTAPI
SamAddMultipleMembersToAlias(
    _In_ SAM_HANDLE AliasHandle,
    _In_reads_(MemberCount) PSID *MemberIds,
    _In_ ULONG MemberCount
    );

_Check_return_
NTSTATUS
NTAPI
SamRemoveMemberFromAlias(
    _In_ SAM_HANDLE AliasHandle,
    _In_ PSID MemberId
    );

_Check_return_
NTSTATUS
NTAPI
SamRemoveMultipleMembersFromAlias(
    _In_ SAM_HANDLE AliasHandle,
    _In_reads_(MemberCount) PSID *MemberIds,
    _In_ ULONG MemberCount
    );

_Check_return_
NTSTATUS
NTAPI
SamGetMembersInAlias(
    _In_ SAM_HANDLE AliasHandle,
    _Out_ _Deref_post_count_(*MemberCount) PSID **MemberIds,
    _Out_ PULONG MemberCount
    );

_Check_return_
NTSTATUS
NTAPI
SamGetAliasMembership(
    _In_ SAM_HANDLE DomainHandle,
    _In_ ULONG PassedCount,
    _In_reads_(PassedCount) PSID *Sids,
    _Out_ PULONG MembershipCount,
    _Out_ _Deref_post_count_(*MembershipCount) PULONG *Aliases
    );

// Group types

#define GROUP_TYPE_BUILTIN_LOCAL_GROUP 0x00000001
#define GROUP_TYPE_ACCOUNT_GROUP 0x00000002
#define GROUP_TYPE_RESOURCE_GROUP 0x00000004
#define GROUP_TYPE_UNIVERSAL_GROUP 0x00000008
#define GROUP_TYPE_APP_BASIC_GROUP 0x00000010
#define GROUP_TYPE_APP_QUERY_GROUP 0x00000020
#define GROUP_TYPE_SECURITY_ENABLED 0x80000000

#define GROUP_TYPE_RESOURCE_BEHAVOIR (GROUP_TYPE_RESOURCE_GROUP | \
    GROUP_TYPE_APP_BASIC_GROUP | \
    GROUP_TYPE_APP_QUERY_GROUP)

// User

#define USER_READ_GENERAL 0x0001
#define USER_READ_PREFERENCES 0x0002
#define USER_WRITE_PREFERENCES 0x0004
#define USER_READ_LOGON 0x0008
#define USER_READ_ACCOUNT 0x0010
#define USER_WRITE_ACCOUNT 0x0020
#define USER_CHANGE_PASSWORD 0x0040
#define USER_FORCE_PASSWORD_CHANGE 0x0080
#define USER_LIST_GROUPS 0x0100
#define USER_READ_GROUP_INFORMATION 0x0200
#define USER_WRITE_GROUP_INFORMATION 0x0400

#define USER_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | \
    USER_READ_PREFERENCES | \
    USER_READ_LOGON | \
    USER_LIST_GROUPS | \
    USER_READ_GROUP_INFORMATION | \
    USER_WRITE_PREFERENCES | \
    USER_CHANGE_PASSWORD | \
    USER_FORCE_PASSWORD_CHANGE | \
    USER_READ_GENERAL | \
    USER_READ_ACCOUNT | \
    USER_WRITE_ACCOUNT | \
    USER_WRITE_GROUP_INFORMATION)

#define USER_READ (STANDARD_RIGHTS_READ | \
    USER_READ_PREFERENCES | \
    USER_READ_LOGON | \
    USER_READ_ACCOUNT | \
    USER_LIST_GROUPS | \
    USER_READ_GROUP_INFORMATION)

#define USER_WRITE (STANDARD_RIGHTS_WRITE | \
    USER_WRITE_PREFERENCES | \
    USER_CHANGE_PASSWORD)

#define USER_EXECUTE (STANDARD_RIGHTS_EXECUTE | \
    USER_READ_GENERAL | \
    USER_CHANGE_PASSWORD)

// User account control flags

#define USER_ACCOUNT_DISABLED (0x00000001)
#define USER_HOME_DIRECTORY_REQUIRED (0x00000002)
#define USER_PASSWORD_NOT_REQUIRED (0x00000004)
#define USER_TEMP_DUPLICATE_ACCOUNT (0x00000008)
#define USER_NORMAL_ACCOUNT (0x00000010)
#define USER_MNS_LOGON_ACCOUNT (0x00000020)
#define USER_INTERDOMAIN_TRUST_ACCOUNT (0x00000040)
#define USER_WORKSTATION_TRUST_ACCOUNT (0x00000080)
#define USER_SERVER_TRUST_ACCOUNT (0x00000100)
#define USER_DONT_EXPIRE_PASSWORD (0x00000200)
#define USER_ACCOUNT_AUTO_LOCKED (0x00000400)
#define USER_ENCRYPTED_TEXT_PASSWORD_ALLOWED (0x00000800)
#define USER_SMARTCARD_REQUIRED (0x00001000)
#define USER_TRUSTED_FOR_DELEGATION (0x00002000)
#define USER_NOT_DELEGATED (0x00004000)
#define USER_USE_DES_KEY_ONLY (0x00008000)
#define USER_DONT_REQUIRE_PREAUTH (0x00010000)
#define USER_PASSWORD_EXPIRED (0x00020000)
#define USER_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION (0x00040000)
#define USER_NO_AUTH_DATA_REQUIRED (0x00080000)
#define USER_PARTIAL_SECRETS_ACCOUNT (0x00100000)
#define USER_USE_AES_KEYS (0x00200000) // not used

#define NEXT_FREE_ACCOUNT_CONTROL_BIT (USER_USE_AES_KEYS << 1)

#define USER_MACHINE_ACCOUNT_MASK ( \
    USER_INTERDOMAIN_TRUST_ACCOUNT | \
    USER_WORKSTATION_TRUST_ACCOUNT | \
    USER_SERVER_TRUST_ACCOUNT \
    )

#define USER_ACCOUNT_TYPE_MASK ( \
    USER_TEMP_DUPLICATE_ACCOUNT | \
    USER_NORMAL_ACCOUNT | \
    USER_MACHINE_ACCOUNT_MASK \
    )

#define USER_COMPUTED_ACCOUNT_CONTROL_BITS ( \
    USER_ACCOUNT_AUTO_LOCKED | \
    USER_PASSWORD_EXPIRED \
    )

// Logon times may be expressed in day, hour, or minute granularity.

#define SAM_DAYS_PER_WEEK (7)
#define SAM_HOURS_PER_WEEK (24 * SAM_DAYS_PER_WEEK)
#define SAM_MINUTES_PER_WEEK (60 * SAM_HOURS_PER_WEEK)

typedef struct _LOGON_HOURS
{
    USHORT UnitsPerWeek;

    // UnitsPerWeek is the number of equal length time units the week is
    // divided into. This value is used to compute the length of the bit
    // string in logon_hours. Must be less than or equal to
    // SAM_UNITS_PER_WEEK (10080) for this release.
    //
    // LogonHours is a bit map of valid logon times. Each bit represents
    // a unique division in a week. The largest bit map supported is 1260
    // bytes (10080 bits), which represents minutes per week. In this case
    // the first bit (bit 0, byte 0) is Sunday, 00:00:00 - 00-00:59; bit 1,
    // byte 0 is Sunday, 00:01:00 - 00:01:59, etc. A NULL pointer means
    // DONT_CHANGE for SamSetInformationUser() calls.

    PUCHAR LogonHours;
} LOGON_HOURS, *PLOGON_HOURS;

typedef struct _SR_SECURITY_DESCRIPTOR
{
    ULONG Length;
    PUCHAR SecurityDescriptor;
} SR_SECURITY_DESCRIPTOR, *PSR_SECURITY_DESCRIPTOR;

// SamQueryInformationUser/SamSetInformationUser types

typedef enum _USER_INFORMATION_CLASS
{
    UserGeneralInformation = 1, // USER_GENERAL_INFORMATION
    UserPreferencesInformation, // USER_PREFERENCES_INFORMATION
    UserLogonInformation, // USER_LOGON_INFORMATION
    UserLogonHoursInformation, // USER_LOGON_HOURS_INFORMATION
    UserAccountInformation, // USER_ACCOUNT_INFORMATION
    UserNameInformation, // USER_NAME_INFORMATION
    UserAccountNameInformation, // USER_ACCOUNT_NAME_INFORMATION
    UserFullNameInformation, // USER_FULL_NAME_INFORMATION
    UserPrimaryGroupInformation, // USER_PRIMARY_GROUP_INFORMATION
    UserHomeInformation, // USER_HOME_INFORMATION
    UserScriptInformation, // USER_SCRIPT_INFORMATION
    UserProfileInformation, // USER_PROFILE_INFORMATION
    UserAdminCommentInformation, // USER_ADMIN_COMMENT_INFORMATION
    UserWorkStationsInformation, // USER_WORKSTATIONS_INFORMATION
    UserSetPasswordInformation, // USER_SET_PASSWORD_INFORMATION
    UserControlInformation, // USER_CONTROL_INFORMATION
    UserExpiresInformation, // USER_EXPIRES_INFORMATION
    UserInternal1Information,
    UserInternal2Information,
    UserParametersInformation, // USER_PARAMETERS_INFORMATION
    UserAllInformation, // USER_ALL_INFORMATION
    UserInternal3Information,
    UserInternal4Information,
    UserInternal5Information,
    UserInternal4InformationNew,
    UserInternal5InformationNew,
    UserInternal6Information,
    UserExtendedInformation, // USER_EXTENDED_INFORMATION
    UserLogonUIInformation // USER_LOGON_UI_INFORMATION
} USER_INFORMATION_CLASS, *PUSER_INFORMATION_CLASS;

typedef struct _USER_GENERAL_INFORMATION
{
    UNICODE_STRING UserName;
    UNICODE_STRING FullName;
    ULONG PrimaryGroupId;
    UNICODE_STRING AdminComment;
    UNICODE_STRING UserComment;
} USER_GENERAL_INFORMATION, *PUSER_GENERAL_INFORMATION;

typedef struct _USER_PREFERENCES_INFORMATION
{
    UNICODE_STRING UserComment;
    UNICODE_STRING Reserved1;
    USHORT CountryCode;
    USHORT CodePage;
} USER_PREFERENCES_INFORMATION, *PUSER_PREFERENCES_INFORMATION;

#include <pshpack4.h>
typedef struct _USER_LOGON_INFORMATION
{
    UNICODE_STRING UserName;
    UNICODE_STRING FullName;
    ULONG UserId;
    ULONG PrimaryGroupId;
    UNICODE_STRING HomeDirectory;
    UNICODE_STRING HomeDirectoryDrive;
    UNICODE_STRING ScriptPath;
    UNICODE_STRING ProfilePath;
    UNICODE_STRING WorkStations;
    LARGE_INTEGER LastLogon;
    LARGE_INTEGER LastLogoff;
    LARGE_INTEGER PasswordLastSet;
    LARGE_INTEGER PasswordCanChange;
    LARGE_INTEGER PasswordMustChange;
    LOGON_HOURS LogonHours;
    USHORT BadPasswordCount;
    USHORT LogonCount;
    ULONG UserAccountControl;
} USER_LOGON_INFORMATION, * PUSER_LOGON_INFORMATION;
#include <poppack.h>

typedef struct _USER_LOGON_HOURS_INFORMATION
{
    LOGON_HOURS LogonHours;
} USER_LOGON_HOURS_INFORMATION, * PUSER_LOGON_HOURS_INFORMATION;

#include <pshpack4.h>
typedef struct _USER_ACCOUNT_INFORMATION
{
    UNICODE_STRING UserName;
    UNICODE_STRING FullName;
    ULONG UserId;
    ULONG PrimaryGroupId;
    UNICODE_STRING HomeDirectory;
    UNICODE_STRING HomeDirectoryDrive;
    UNICODE_STRING ScriptPath;
    UNICODE_STRING ProfilePath;
    UNICODE_STRING AdminComment;
    UNICODE_STRING WorkStations;
    LARGE_INTEGER LastLogon;
    LARGE_INTEGER LastLogoff;
    LOGON_HOURS LogonHours;
    USHORT BadPasswordCount;
    USHORT LogonCount;
    LARGE_INTEGER PasswordLastSet;
    LARGE_INTEGER AccountExpires;
    ULONG UserAccountControl;
} USER_ACCOUNT_INFORMATION, * PUSER_ACCOUNT_INFORMATION;
#include <poppack.h>

typedef struct _USER_NAME_INFORMATION
{
    UNICODE_STRING UserName;
    UNICODE_STRING FullName;
} USER_NAME_INFORMATION, *PUSER_NAME_INFORMATION;

typedef struct _USER_ACCOUNT_NAME_INFORMATION
{
    UNICODE_STRING UserName;
} USER_ACCOUNT_NAME_INFORMATION, *PUSER_ACCOUNT_NAME_INFORMATION;

typedef struct _USER_FULL_NAME_INFORMATION
{
    UNICODE_STRING FullName;
} USER_FULL_NAME_INFORMATION, *PUSER_FULL_NAME_INFORMATION;

typedef struct _USER_PRIMARY_GROUP_INFORMATION
{
    ULONG PrimaryGroupId;
} USER_PRIMARY_GROUP_INFORMATION, *PUSER_PRIMARY_GROUP_INFORMATION;

typedef struct _USER_HOME_INFORMATION
{
    UNICODE_STRING HomeDirectory;
    UNICODE_STRING HomeDirectoryDrive;
} USER_HOME_INFORMATION, *PUSER_HOME_INFORMATION;

typedef struct _USER_SCRIPT_INFORMATION
{
    UNICODE_STRING ScriptPath;
} USER_SCRIPT_INFORMATION, *PUSER_SCRIPT_INFORMATION;

typedef struct _USER_PROFILE_INFORMATION
{
    UNICODE_STRING ProfilePath;
} USER_PROFILE_INFORMATION, *PUSER_PROFILE_INFORMATION;

typedef struct _USER_ADMIN_COMMENT_INFORMATION
{
    UNICODE_STRING AdminComment;
} USER_ADMIN_COMMENT_INFORMATION, *PUSER_ADMIN_COMMENT_INFORMATION;

typedef struct _USER_WORKSTATIONS_INFORMATION
{
    UNICODE_STRING WorkStations;
} USER_WORKSTATIONS_INFORMATION, *PUSER_WORKSTATIONS_INFORMATION;

typedef struct _USER_SET_PASSWORD_INFORMATION
{
    UNICODE_STRING Password;
    BOOLEAN PasswordExpired;
} USER_SET_PASSWORD_INFORMATION, *PUSER_SET_PASSWORD_INFORMATION;

typedef struct _USER_CONTROL_INFORMATION
{
    ULONG UserAccountControl;
} USER_CONTROL_INFORMATION, *PUSER_CONTROL_INFORMATION;

typedef struct _USER_EXPIRES_INFORMATION
{
    LARGE_INTEGER AccountExpires;
} USER_EXPIRES_INFORMATION, *PUSER_EXPIRES_INFORMATION;

typedef struct _USER_PARAMETERS_INFORMATION
{
    UNICODE_STRING Parameters;
} USER_PARAMETERS_INFORMATION, *PUSER_PARAMETERS_INFORMATION;

// Flags for WhichFields in USER_ALL_INFORMATION

#define USER_ALL_USERNAME 0x00000001
#define USER_ALL_FULLNAME 0x00000002
#define USER_ALL_USERID 0x00000004
#define USER_ALL_PRIMARYGROUPID 0x00000008
#define USER_ALL_ADMINCOMMENT 0x00000010
#define USER_ALL_USERCOMMENT 0x00000020
#define USER_ALL_HOMEDIRECTORY 0x00000040
#define USER_ALL_HOMEDIRECTORYDRIVE 0x00000080
#define USER_ALL_SCRIPTPATH 0x00000100
#define USER_ALL_PROFILEPATH 0x00000200
#define USER_ALL_WORKSTATIONS 0x00000400
#define USER_ALL_LASTLOGON 0x00000800
#define USER_ALL_LASTLOGOFF 0x00001000
#define USER_ALL_LOGONHOURS 0x00002000
#define USER_ALL_BADPASSWORDCOUNT 0x00004000
#define USER_ALL_LOGONCOUNT 0x00008000
#define USER_ALL_PASSWORDCANCHANGE 0x00010000
#define USER_ALL_PASSWORDMUSTCHANGE 0x00020000
#define USER_ALL_PASSWORDLASTSET 0x00040000
#define USER_ALL_ACCOUNTEXPIRES 0x00080000
#define USER_ALL_USERACCOUNTCONTROL 0x00100000
#define USER_ALL_PARAMETERS 0x00200000
#define USER_ALL_COUNTRYCODE 0x00400000
#define USER_ALL_CODEPAGE 0x00800000
#define USER_ALL_NTPASSWORDPRESENT 0x01000000 // field AND boolean
#define USER_ALL_LMPASSWORDPRESENT 0x02000000 // field AND boolean
#define USER_ALL_PRIVATEDATA 0x04000000 // field AND boolean
#define USER_ALL_PASSWORDEXPIRED 0x08000000
#define USER_ALL_SECURITYDESCRIPTOR 0x10000000
#define USER_ALL_OWFPASSWORD 0x20000000 // boolean

#define USER_ALL_UNDEFINED_MASK 0xc0000000

// Fields that require USER_READ_GENERAL access to read.

#define USER_ALL_READ_GENERAL_MASK \
    (USER_ALL_USERNAME | \
    USER_ALL_FULLNAME | \
    USER_ALL_USERID | \
    USER_ALL_PRIMARYGROUPID | \
    USER_ALL_ADMINCOMMENT | \
    USER_ALL_USERCOMMENT)

// Fields that require USER_READ_LOGON access to read.

#define USER_ALL_READ_LOGON_MASK \
   (USER_ALL_HOMEDIRECTORY | \
    USER_ALL_HOMEDIRECTORYDRIVE | \
    USER_ALL_SCRIPTPATH | \
    USER_ALL_PROFILEPATH | \
    USER_ALL_WORKSTATIONS | \
    USER_ALL_LASTLOGON | \
    USER_ALL_LASTLOGOFF | \
    USER_ALL_LOGONHOURS | \
    USER_ALL_BADPASSWORDCOUNT | \
    USER_ALL_LOGONCOUNT | \
    USER_ALL_PASSWORDCANCHANGE | \
    USER_ALL_PASSWORDMUSTCHANGE)

// Fields that require USER_READ_ACCOUNT access to read.

#define USER_ALL_READ_ACCOUNT_MASK \
    (USER_ALL_PASSWORDLASTSET | \
    USER_ALL_ACCOUNTEXPIRES | \
    USER_ALL_USERACCOUNTCONTROL | \
    USER_ALL_PARAMETERS)

// Fields that require USER_READ_PREFERENCES access to read.

#define USER_ALL_READ_PREFERENCES_MASK \
    (USER_ALL_COUNTRYCODE | USER_ALL_CODEPAGE)

// Fields that can only be read by trusted clients.

#define USER_ALL_READ_TRUSTED_MASK \
    (USER_ALL_NTPASSWORDPRESENT | \
    USER_ALL_LMPASSWORDPRESENT | \
    USER_ALL_PASSWORDEXPIRED | \
    USER_ALL_SECURITYDESCRIPTOR | \
    USER_ALL_PRIVATEDATA)

// Fields that can't be read.

#define USER_ALL_READ_CANT_MASK USER_ALL_UNDEFINED_MASK

// Fields that require USER_WRITE_ACCOUNT access to write.

#define USER_ALL_WRITE_ACCOUNT_MASK \
    (USER_ALL_USERNAME | \
    USER_ALL_FULLNAME | \
    USER_ALL_PRIMARYGROUPID | \
    USER_ALL_HOMEDIRECTORY | \
    USER_ALL_HOMEDIRECTORYDRIVE | \
    USER_ALL_SCRIPTPATH | \
    USER_ALL_PROFILEPATH | \
    USER_ALL_ADMINCOMMENT | \
    USER_ALL_WORKSTATIONS | \
    USER_ALL_LOGONHOURS | \
    USER_ALL_ACCOUNTEXPIRES | \
    USER_ALL_USERACCOUNTCONTROL | \
    USER_ALL_PARAMETERS)

// Fields that require USER_WRITE_PREFERENCES access to write.

#define USER_ALL_WRITE_PREFERENCES_MASK \
    (USER_ALL_USERCOMMENT | USER_ALL_COUNTRYCODE | USER_ALL_CODEPAGE)

// Fields that require USER_FORCE_PASSWORD_CHANGE access to write.
//
// Note that non-trusted clients only set the NT password as a
// UNICODE string. The wrapper will convert it to an LM password,
// OWF and encrypt both versions. Trusted clients can pass in OWF
// versions of either or both.

#define USER_ALL_WRITE_FORCE_PASSWORD_CHANGE_MASK \
    (USER_ALL_NTPASSWORDPRESENT | \
    USER_ALL_LMPASSWORDPRESENT | \
    USER_ALL_PASSWORDEXPIRED)

// Fields that can only be written by trusted clients.

#define USER_ALL_WRITE_TRUSTED_MASK \
    (USER_ALL_LASTLOGON | \
    USER_ALL_LASTLOGOFF | \
    USER_ALL_BADPASSWORDCOUNT | \
    USER_ALL_LOGONCOUNT | \
    USER_ALL_PASSWORDLASTSET | \
    USER_ALL_SECURITYDESCRIPTOR | \
    USER_ALL_PRIVATEDATA)

// Fields that can't be written.

#define USER_ALL_WRITE_CANT_MASK \
    (USER_ALL_USERID | \
    USER_ALL_PASSWORDCANCHANGE | \
    USER_ALL_PASSWORDMUSTCHANGE | \
    USER_ALL_UNDEFINED_MASK)

#include <pshpack4.h>
typedef struct _USER_ALL_INFORMATION
{
    LARGE_INTEGER LastLogon;
    LARGE_INTEGER LastLogoff;
    LARGE_INTEGER PasswordLastSet;
    LARGE_INTEGER AccountExpires;
    LARGE_INTEGER PasswordCanChange;
    LARGE_INTEGER PasswordMustChange;
    UNICODE_STRING UserName;
    UNICODE_STRING FullName;
    UNICODE_STRING HomeDirectory;
    UNICODE_STRING HomeDirectoryDrive;
    UNICODE_STRING ScriptPath;
    UNICODE_STRING ProfilePath;
    UNICODE_STRING AdminComment;
    UNICODE_STRING WorkStations;
    UNICODE_STRING UserComment;
    UNICODE_STRING Parameters;
    UNICODE_STRING LmPassword;
    UNICODE_STRING NtPassword;
    UNICODE_STRING PrivateData;
    SR_SECURITY_DESCRIPTOR SecurityDescriptor;
    ULONG UserId;
    ULONG PrimaryGroupId;
    ULONG UserAccountControl;
    ULONG WhichFields;
    LOGON_HOURS LogonHours;
    USHORT BadPasswordCount;
    USHORT LogonCount;
    USHORT CountryCode;
    USHORT CodePage;
    BOOLEAN LmPasswordPresent;
    BOOLEAN NtPasswordPresent;
    BOOLEAN PasswordExpired;
    BOOLEAN PrivateDataSensitive;
} USER_ALL_INFORMATION, *PUSER_ALL_INFORMATION;
#include <poppack.h>

typedef SAM_BYTE_ARRAY_32K SAM_USER_TILE, *PSAM_USER_TILE;

// 0xff000fff is reserved for internal callers and implementation.

#define USER_EXTENDED_FIELD_USER_TILE (0x00001000L)
#define USER_EXTENDED_FIELD_PASSWORD_HINT (0x00002000L)
#define USER_EXTENDED_FIELD_DONT_SHOW_IN_LOGON_UI (0x00004000L)
#define USER_EXTENDED_FIELD_SHELL_ADMIN_OBJECT_PROPERTIES (0x00008000L)

typedef struct _USER_EXTENDED_INFORMATION
{
    ULONG ExtendedWhichFields;
    SAM_USER_TILE UserTile;
    UNICODE_STRING PasswordHint;
    BOOLEAN DontShowInLogonUI;
    SAM_SHELL_OBJECT_PROPERTIES ShellAdminObjectProperties;
} USER_EXTENDED_INFORMATION, *PUSER_EXTENDED_INFORMATION;

// For local callers only.
typedef struct _USER_LOGON_UI_INFORMATION
{
    BOOLEAN PasswordIsBlank;
    BOOLEAN AccountIsDisabled;
} USER_LOGON_UI_INFORMATION, *PUSER_LOGON_UI_INFORMATION;

// SamChangePasswordUser3 types

// Error values:
// * SAM_PWD_CHANGE_NO_ERROR
// * SAM_PWD_CHANGE_PASSWORD_TOO_SHORT
// * SAM_PWD_CHANGE_PWD_IN_HISTORY
// * SAM_PWD_CHANGE_USERNAME_IN_PASSWORD
// * SAM_PWD_CHANGE_FULLNAME_IN_PASSWORD
// * SAM_PWD_CHANGE_MACHINE_PASSWORD_NOT_DEFAULT
// * SAM_PWD_CHANGE_FAILED_BY_FILTER

typedef struct _USER_PWD_CHANGE_FAILURE_INFORMATION
{
    ULONG ExtendedFailureReason;
    UNICODE_STRING FilterModuleName;
} USER_PWD_CHANGE_FAILURE_INFORMATION,*PUSER_PWD_CHANGE_FAILURE_INFORMATION;

// ExtendedFailureReason values

#define SAM_PWD_CHANGE_NO_ERROR 0
#define SAM_PWD_CHANGE_PASSWORD_TOO_SHORT 1
#define SAM_PWD_CHANGE_PWD_IN_HISTORY 2
#define SAM_PWD_CHANGE_USERNAME_IN_PASSWORD 3
#define SAM_PWD_CHANGE_FULLNAME_IN_PASSWORD 4
#define SAM_PWD_CHANGE_NOT_COMPLEX 5
#define SAM_PWD_CHANGE_MACHINE_PASSWORD_NOT_DEFAULT 6
#define SAM_PWD_CHANGE_FAILED_BY_FILTER 7
#define SAM_PWD_CHANGE_PASSWORD_TOO_LONG 8
#define SAM_PWD_CHANGE_FAILURE_REASON_MAX 8

// Functions

_Check_return_
NTSTATUS
NTAPI
SamEnumerateUsersInDomain(
    _In_ SAM_HANDLE DomainHandle,
    _Inout_ PSAM_ENUMERATE_HANDLE EnumerationContext,
    _In_ ULONG UserAccountControl,
    _Outptr_ PVOID *Buffer, // PSAM_RID_ENUMERATION *
    _In_ ULONG PreferedMaximumLength,
    _Out_ PULONG CountReturned
    );

_Check_return_
NTSTATUS
NTAPI
SamCreateUserInDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ PUNICODE_STRING AccountName,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PSAM_HANDLE UserHandle,
    _Out_ PULONG RelativeId
    );

_Check_return_
NTSTATUS
NTAPI
SamCreateUser2InDomain(
    _In_ SAM_HANDLE DomainHandle,
    _In_ PUNICODE_STRING AccountName,
    _In_ ULONG AccountType,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PSAM_HANDLE UserHandle,
    _Out_ PULONG GrantedAccess,
    _Out_ PULONG RelativeId
    );

_Check_return_
NTSTATUS
NTAPI
SamOpenUser(
    _In_ SAM_HANDLE DomainHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG UserId,
    _Out_ PSAM_HANDLE UserHandle
    );

_Check_return_
NTSTATUS
NTAPI
SamDeleteUser(
    _In_ SAM_HANDLE UserHandle
    );

_Check_return_
NTSTATUS
NTAPI
SamQueryInformationUser(
    _In_ SAM_HANDLE UserHandle,
    _In_ USER_INFORMATION_CLASS UserInformationClass,
    _Outptr_ PVOID *Buffer
    );

_Check_return_
NTSTATUS
NTAPI
SamSetInformationUser(
    _In_ SAM_HANDLE UserHandle,
    _In_ USER_INFORMATION_CLASS UserInformationClass,
    _In_ PVOID Buffer
    );

_Check_return_
NTSTATUS
NTAPI
SamGetGroupsForUser(
    _In_ SAM_HANDLE UserHandle,
    _Out_ _Deref_post_count_(*MembershipCount) PGROUP_MEMBERSHIP *Groups,
    _Out_ PULONG MembershipCount
    );

_Check_return_
NTSTATUS
NTAPI
SamChangePasswordUser(
    _In_ SAM_HANDLE UserHandle,
    _In_ PUNICODE_STRING OldPassword,
    _In_ PUNICODE_STRING NewPassword
    );

_Check_return_
NTSTATUS
NTAPI
SamChangePasswordUser2(
    _In_ PUNICODE_STRING ServerName,
    _In_ PUNICODE_STRING UserName,
    _In_ PUNICODE_STRING OldPassword,
    _In_ PUNICODE_STRING NewPassword
    );

_Check_return_
NTSTATUS
NTAPI
SamChangePasswordUser3(
    _In_ PUNICODE_STRING ServerName,
    _In_ PUNICODE_STRING UserName,
    _In_ PUNICODE_STRING OldPassword,
    _In_ PUNICODE_STRING NewPassword,
    _Outptr_ PDOMAIN_PASSWORD_INFORMATION *EffectivePasswordPolicy,
    _Outptr_ PUSER_PWD_CHANGE_FAILURE_INFORMATION *PasswordChangeFailureInfo
    );

_Check_return_
NTSTATUS
NTAPI
SamQueryDisplayInformation(
    _In_ SAM_HANDLE DomainHandle,
    _In_ DOMAIN_DISPLAY_INFORMATION DisplayInformation,
    _In_ ULONG Index,
    _In_ ULONG EntryCount,
    _In_ ULONG PreferredMaximumLength,
    _In_ PULONG TotalAvailable,
    _Out_ PULONG TotalReturned,
    _Out_ PULONG ReturnedEntryCount,
    _Outptr_ PVOID *SortedBuffer
    );

_Check_return_
NTSTATUS
NTAPI
SamGetDisplayEnumerationIndex(
    _In_ SAM_HANDLE DomainHandle,
    _In_ DOMAIN_DISPLAY_INFORMATION DisplayInformation,
    _In_ PUNICODE_STRING Prefix,
    _Out_ PULONG Index
    );

// Database replication

typedef enum _SECURITY_DB_DELTA_TYPE
{
    SecurityDbNew = 1,
    SecurityDbRename,
    SecurityDbDelete,
    SecurityDbChangeMemberAdd,
    SecurityDbChangeMemberSet,
    SecurityDbChangeMemberDel,
    SecurityDbChange,
    SecurityDbChangePassword
} SECURITY_DB_DELTA_TYPE, *PSECURITY_DB_DELTA_TYPE;

typedef enum _SECURITY_DB_OBJECT_TYPE
{
    SecurityDbObjectSamDomain = 1,
    SecurityDbObjectSamUser,
    SecurityDbObjectSamGroup,
    SecurityDbObjectSamAlias,
    SecurityDbObjectLsaPolicy,
    SecurityDbObjectLsaTDomain,
    SecurityDbObjectLsaAccount,
    SecurityDbObjectLsaSecret
} SECURITY_DB_OBJECT_TYPE, *PSECURITY_DB_OBJECT_TYPE;

typedef enum _SAM_ACCOUNT_TYPE
{
    SamObjectUser = 1,
    SamObjectGroup,
    SamObjectAlias
} SAM_ACCOUNT_TYPE, *PSAM_ACCOUNT_TYPE;

#define SAM_USER_ACCOUNT (0x00000001)
#define SAM_GLOBAL_GROUP_ACCOUNT (0x00000002)
#define SAM_LOCAL_GROUP_ACCOUNT (0x00000004)

typedef struct _SAM_GROUP_MEMBER_ID
{
    ULONG MemberRid;
} SAM_GROUP_MEMBER_ID, *PSAM_GROUP_MEMBER_ID;

typedef struct _SAM_ALIAS_MEMBER_ID
{
    PSID MemberSid;
} SAM_ALIAS_MEMBER_ID, *PSAM_ALIAS_MEMBER_ID;

typedef union _SAM_DELTA_DATA
{
    SAM_GROUP_MEMBER_ID GroupMemberId;
    SAM_ALIAS_MEMBER_ID AliasMemberId;
    ULONG AccountControl;
} SAM_DELTA_DATA, *PSAM_DELTA_DATA;

typedef NTSTATUS (NTAPI *PSAM_DELTA_NOTIFICATION_ROUTINE)(
    _In_ PSID DomainSid,
    _In_ SECURITY_DB_DELTA_TYPE DeltaType,
    _In_ SECURITY_DB_OBJECT_TYPE ObjectType,
    _In_ ULONG ObjectRid,
    _In_opt_ PUNICODE_STRING ObjectName,
    _In_ PLARGE_INTEGER ModifiedCount,
    _In_opt_ PSAM_DELTA_DATA DeltaData
    );

#define SAM_DELTA_NOTIFY_ROUTINE "DeltaNotify"

_Check_return_
NTSTATUS
NTAPI
SamRegisterObjectChangeNotification(
    _In_ SECURITY_DB_OBJECT_TYPE ObjectType,
    _In_ HANDLE NotificationEventHandle
    );

NTSTATUS
NTAPI
SamUnregisterObjectChangeNotification(
    _In_ SECURITY_DB_OBJECT_TYPE ObjectType,
    _In_ HANDLE NotificationEventHandle
    );

// Compatibility mode

#define SAM_SID_COMPATIBILITY_ALL 0
#define SAM_SID_COMPATIBILITY_LAX 1
#define SAM_SID_COMPATIBILITY_STRICT 2

_Check_return_
NTSTATUS
NTAPI
SamGetCompatibilityMode(
    _In_ SAM_HANDLE ObjectHandle,
    _Out_ ULONG *Mode
    );

// Password validation

typedef enum _PASSWORD_POLICY_VALIDATION_TYPE
{
    SamValidateAuthentication = 1,
    SamValidatePasswordChange,
    SamValidatePasswordReset
} PASSWORD_POLICY_VALIDATION_TYPE;

typedef struct _SAM_VALIDATE_PASSWORD_HASH
{
    ULONG Length;
    _Field_size_bytes_(Length) PUCHAR Hash;
} SAM_VALIDATE_PASSWORD_HASH, *PSAM_VALIDATE_PASSWORD_HASH;

// Flags for PresentFields in SAM_VALIDATE_PERSISTED_FIELDS

#define SAM_VALIDATE_PASSWORD_LAST_SET 0x00000001
#define SAM_VALIDATE_BAD_PASSWORD_TIME 0x00000002
#define SAM_VALIDATE_LOCKOUT_TIME 0x00000004
#define SAM_VALIDATE_BAD_PASSWORD_COUNT 0x00000008
#define SAM_VALIDATE_PASSWORD_HISTORY_LENGTH 0x00000010
#define SAM_VALIDATE_PASSWORD_HISTORY 0x00000020

typedef struct _SAM_VALIDATE_PERSISTED_FIELDS
{
    ULONG PresentFields;
    LARGE_INTEGER PasswordLastSet;
    LARGE_INTEGER BadPasswordTime;
    LARGE_INTEGER LockoutTime;
    ULONG BadPasswordCount;
    ULONG PasswordHistoryLength;
    _Field_size_bytes_(PasswordHistoryLength) PSAM_VALIDATE_PASSWORD_HASH PasswordHistory;
} SAM_VALIDATE_PERSISTED_FIELDS, *PSAM_VALIDATE_PERSISTED_FIELDS;

typedef enum _SAM_VALIDATE_VALIDATION_STATUS
{
    SamValidateSuccess = 0,
    SamValidatePasswordMustChange,
    SamValidateAccountLockedOut,
    SamValidatePasswordExpired,
    SamValidatePasswordIncorrect,
    SamValidatePasswordIsInHistory,
    SamValidatePasswordTooShort,
    SamValidatePasswordTooLong,
    SamValidatePasswordNotComplexEnough,
    SamValidatePasswordTooRecent,
    SamValidatePasswordFilterError
} SAM_VALIDATE_VALIDATION_STATUS, *PSAM_VALIDATE_VALIDATION_STATUS;

typedef struct _SAM_VALIDATE_STANDARD_OUTPUT_ARG
{
    SAM_VALIDATE_PERSISTED_FIELDS ChangedPersistedFields;
    SAM_VALIDATE_VALIDATION_STATUS ValidationStatus;
} SAM_VALIDATE_STANDARD_OUTPUT_ARG, *PSAM_VALIDATE_STANDARD_OUTPUT_ARG;

typedef struct _SAM_VALIDATE_AUTHENTICATION_INPUT_ARG
{
    SAM_VALIDATE_PERSISTED_FIELDS InputPersistedFields;
    BOOLEAN PasswordMatched;
} SAM_VALIDATE_AUTHENTICATION_INPUT_ARG, *PSAM_VALIDATE_AUTHENTICATION_INPUT_ARG;

typedef struct _SAM_VALIDATE_PASSWORD_CHANGE_INPUT_ARG
{
    SAM_VALIDATE_PERSISTED_FIELDS InputPersistedFields;
    UNICODE_STRING ClearPassword;
    UNICODE_STRING UserAccountName;
    SAM_VALIDATE_PASSWORD_HASH HashedPassword;
    BOOLEAN PasswordMatch; // denotes if the old password supplied by user matched or not
} SAM_VALIDATE_PASSWORD_CHANGE_INPUT_ARG, *PSAM_VALIDATE_PASSWORD_CHANGE_INPUT_ARG;

typedef struct _SAM_VALIDATE_PASSWORD_RESET_INPUT_ARG
{
    SAM_VALIDATE_PERSISTED_FIELDS InputPersistedFields;
    UNICODE_STRING ClearPassword;
    UNICODE_STRING UserAccountName;
    SAM_VALIDATE_PASSWORD_HASH HashedPassword;
    BOOLEAN PasswordMustChangeAtNextLogon; // looked at only for password reset
    BOOLEAN ClearLockout; // can be used clear user account lockout
}SAM_VALIDATE_PASSWORD_RESET_INPUT_ARG, *PSAM_VALIDATE_PASSWORD_RESET_INPUT_ARG;

typedef union _SAM_VALIDATE_INPUT_ARG
{
    SAM_VALIDATE_AUTHENTICATION_INPUT_ARG ValidateAuthenticationInput;
    SAM_VALIDATE_PASSWORD_CHANGE_INPUT_ARG ValidatePasswordChangeInput;
    SAM_VALIDATE_PASSWORD_RESET_INPUT_ARG ValidatePasswordResetInput;
} SAM_VALIDATE_INPUT_ARG, *PSAM_VALIDATE_INPUT_ARG;

typedef union _SAM_VALIDATE_OUTPUT_ARG
{
    SAM_VALIDATE_STANDARD_OUTPUT_ARG ValidateAuthenticationOutput;
    SAM_VALIDATE_STANDARD_OUTPUT_ARG ValidatePasswordChangeOutput;
    SAM_VALIDATE_STANDARD_OUTPUT_ARG ValidatePasswordResetOutput;
} SAM_VALIDATE_OUTPUT_ARG, *PSAM_VALIDATE_OUTPUT_ARG;

_Check_return_
NTSTATUS
NTAPI
SamValidatePassword(
    _In_opt_ PUNICODE_STRING ServerName,
    _In_ PASSWORD_POLICY_VALIDATION_TYPE ValidationType,
    _In_ PSAM_VALIDATE_INPUT_ARG InputArg,
    _Out_ PSAM_VALIDATE_OUTPUT_ARG *OutputArg
    );

// Generic operation

typedef enum _SAM_GENERIC_OPERATION_TYPE
{
    SamObjectChangeNotificationOperation
} SAM_GENERIC_OPERATION_TYPE, *PSAM_GENERIC_OPERATION_TYPE;

typedef struct _SAM_OPERATION_OBJCHG_INPUT
{
    BOOLEAN Register;
    ULONG64 EventHandle;
    SECURITY_DB_OBJECT_TYPE ObjectType;
    ULONG ProcessID;
} SAM_OPERATION_OBJCHG_INPUT, *PSAM_OPERATION_OBJCHG_INPUT;

typedef struct _SAM_OPERATION_OBJCHG_OUTPUT
{
    ULONG Reserved;
} SAM_OPERATION_OBJCHG_OUTPUT, *PSAM_OPERATION_OBJCHG_OUTPUT;

typedef union _SAM_GENERIC_OPERATION_INPUT
{
    SAM_OPERATION_OBJCHG_INPUT ObjChangeIn;
} SAM_GENERIC_OPERATION_INPUT, *PSAM_GENERIC_OPERATION_INPUT;

typedef union _SAM_GENERIC_OPERATION_OUTPUT
{
    SAM_OPERATION_OBJCHG_OUTPUT ObjChangeOut;
} SAM_GENERIC_OPERATION_OUTPUT, *PSAM_GENERIC_OPERATION_OUTPUT;

_Check_return_
NTSTATUS
NTAPI
SamPerformGenericOperation(
    _In_opt_ PWSTR ServerName,
    _In_ SAM_GENERIC_OPERATION_TYPE OperationType,
    _In_ PSAM_GENERIC_OPERATION_INPUT OperationIn,
    _Out_ PSAM_GENERIC_OPERATION_OUTPUT *OperationOut
    );
 


// #include <ntmisc.h>
// Filter manager

#define FLT_PORT_CONNECT 0x0001
#define FLT_PORT_ALL_ACCESS (FLT_PORT_CONNECT | STANDARD_RIGHTS_ALL)

// VDM

typedef enum _VDMSERVICECLASS
{
    VdmStartExecution,
    VdmQueueInterrupt,
    VdmDelayInterrupt,
    VdmInitialize,
    VdmFeatures,
    VdmSetInt21Handler,
    VdmQueryDir,
    VdmPrinterDirectIoOpen,
    VdmPrinterDirectIoClose,
    VdmPrinterInitialize,
    VdmSetLdtEntries,
    VdmSetProcessLdtInfo,
    VdmAdlibEmulation,
    VdmPMCliControl,
    VdmQueryVdmProcess
} VDMSERVICECLASS, *PVDMSERVICECLASS;

NTSYSCALLAPI
NTSTATUS
NTAPI
NtVdmControl(
    _In_ VDMSERVICECLASS Service,
    _Inout_ PVOID ServiceData
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwVdmControl(
    _In_ VDMSERVICECLASS Service,
    _Inout_ PVOID ServiceData
    );

// WMI/ETW

NTSYSCALLAPI
NTSTATUS
NTAPI
NtTraceEvent(
    _In_ HANDLE TraceHandle,
    _In_ ULONG Flags,
    _In_ ULONG FieldSize,
    _In_ PVOID Fields
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTraceEvent(
    _In_ HANDLE TraceHandle,
    _In_ ULONG Flags,
    _In_ ULONG FieldSize,
    _In_ PVOID Fields
    );

typedef enum _TRACE_CONTROL_INFORMATION_CLASS
{
    TraceControlStartLogger = 1,
    TraceControlStopLogger = 2,
    TraceControlQueryLogger = 3,
    TraceControlUpdateLogger = 4,
    TraceControlFlushLogger = 5,
    TraceControlIncrementLoggerFile = 6,

    TraceControlRealtimeConnect = 11,
    TraceControlWdiDispatchControl = 13,
    TraceControlRealtimeDisconnectConsumerByHandle = 14,

    TraceControlReceiveNotification = 16,
    TraceControlEnableGuid = 17,
    TraceControlSendReplyDataBlock = 18,
    TraceControlReceiveReplyDataBlock = 19,
    TraceControlWdiUpdateSem = 20,
    TraceControlGetTraceGuidList = 21,
    TraceControlGetTraceGuidInfo = 22,
    TraceControlEnumerateTraceGuids = 23,

    TraceControlQueryReferenceTime = 25,
    TraceControlTrackProviderBinary = 26,
    TraceControlAddNotificationEvent = 27,
    TraceControlUpdateDisallowList = 28,

    TraceControlUseDescriptorTypeUm = 31,
    TraceControlGetTraceGroupList = 32,
    TraceControlGetTraceGroupInfo = 33,
    TraceControlTraceSetDisallowList= 34,
    TraceControlSetCompressionSettings = 35,
    TraceControlGetCompressionSettings= 36,
    TraceControlUpdatePeriodicCaptureState = 37,
    TraceControlGetPrivateSessionTraceHandle = 38,
    TraceControlRegisterPrivateSession = 39,
    TraceControlQuerySessionDemuxObject = 40,
    TraceControlSetProviderBinaryTracking = 41,
    TraceControlMaxLoggers = 42,
    TraceControlMaxPmcCounter = 43
} TRACE_CONTROL_INFORMATION_CLASS;

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI
NTSTATUS
NTAPI
NtTraceControl(
    _In_ TRACE_CONTROL_INFORMATION_CLASS TraceInformationClass,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(TraceInformationLength) PVOID TraceInformation,
    _In_ ULONG TraceInformationLength,
    _Out_ PULONG ReturnLength
    );

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTraceControl(
    _In_ TRACE_CONTROL_INFORMATION_CLASS TraceInformationClass,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(TraceInformationLength) PVOID TraceInformation,
    _In_ ULONG TraceInformationLength,
    _Out_ PULONG ReturnLength
    );
#endif
 


// #include <ntsmss.h>
NTSYSAPI
NTSTATUS
NTAPI
RtlConnectToSm(
    _In_ PUNICODE_STRING ApiPortName,
    _In_ HANDLE ApiPortHandle,
    _In_ DWORD ProcessImageType,
    _Out_ PHANDLE SmssConnection
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSendMsgToSm(
    _In_ HANDLE ApiPortHandle,
    _In_ PPORT_MESSAGE MessageData
    );
 


// #include <subprocesstag.h>
typedef enum _TAG_INFO_LEVEL
{
    eTagInfoLevelNameFromTag = 1, // TAG_INFO_NAME_FROM_TAG
    eTagInfoLevelNamesReferencingModule, // TAG_INFO_NAMES_REFERENCING_MODULE
    eTagInfoLevelNameTagMapping, // TAG_INFO_NAME_TAG_MAPPING
    eTagInfoLevelMax
} TAG_INFO_LEVEL;

typedef enum _TAG_TYPE
{
    eTagTypeService = 1,
    eTagTypeMax
} TAG_TYPE;

typedef struct _TAG_INFO_NAME_FROM_TAG_IN_PARAMS
{
    ULONG dwPid;
    ULONG dwTag;
} TAG_INFO_NAME_FROM_TAG_IN_PARAMS, *PTAG_INFO_NAME_FROM_TAG_IN_PARAMS;

typedef struct _TAG_INFO_NAME_FROM_TAG_OUT_PARAMS
{
    ULONG eTagType;
    PWSTR pszName;
} TAG_INFO_NAME_FROM_TAG_OUT_PARAMS, *PTAG_INFO_NAME_FROM_TAG_OUT_PARAMS;

typedef struct _TAG_INFO_NAME_FROM_TAG
{
    TAG_INFO_NAME_FROM_TAG_IN_PARAMS InParams;
    TAG_INFO_NAME_FROM_TAG_OUT_PARAMS OutParams;
} TAG_INFO_NAME_FROM_TAG, *PTAG_INFO_NAME_FROM_TAG;

typedef struct _TAG_INFO_NAMES_REFERENCING_MODULE_IN_PARAMS
{
    ULONG dwPid;
    PWSTR pszModule;
} TAG_INFO_NAMES_REFERENCING_MODULE_IN_PARAMS, *PTAG_INFO_NAMES_REFERENCING_MODULE_IN_PARAMS;

typedef struct _TAG_INFO_NAMES_REFERENCING_MODULE_OUT_PARAMS
{
    ULONG eTagType;
    PWSTR pmszNames;
} TAG_INFO_NAMES_REFERENCING_MODULE_OUT_PARAMS, *PTAG_INFO_NAMES_REFERENCING_MODULE_OUT_PARAMS;

typedef struct _TAG_INFO_NAMES_REFERENCING_MODULE
{
    TAG_INFO_NAMES_REFERENCING_MODULE_IN_PARAMS InParams;
    TAG_INFO_NAMES_REFERENCING_MODULE_OUT_PARAMS OutParams;
} TAG_INFO_NAMES_REFERENCING_MODULE, *PTAG_INFO_NAMES_REFERENCING_MODULE;

typedef struct _TAG_INFO_NAME_TAG_MAPPING_IN_PARAMS
{
    ULONG dwPid;
} TAG_INFO_NAME_TAG_MAPPING_IN_PARAMS, *PTAG_INFO_NAME_TAG_MAPPING_IN_PARAMS;

typedef struct _TAG_INFO_NAME_TAG_MAPPING_ELEMENT
{
    ULONG eTagType;
    ULONG dwTag;
    PWSTR pszName;
    PWSTR pszGroupName;
} TAG_INFO_NAME_TAG_MAPPING_ELEMENT, *PTAG_INFO_NAME_TAG_MAPPING_ELEMENT;

typedef struct _TAG_INFO_NAME_TAG_MAPPING_OUT_PARAMS
{
    ULONG cElements;
    PTAG_INFO_NAME_TAG_MAPPING_ELEMENT pNameTagMappingElements;
} TAG_INFO_NAME_TAG_MAPPING_OUT_PARAMS, *PTAG_INFO_NAME_TAG_MAPPING_OUT_PARAMS;

typedef struct _TAG_INFO_NAME_TAG_MAPPING
{
    TAG_INFO_NAME_TAG_MAPPING_IN_PARAMS InParams;
    PTAG_INFO_NAME_TAG_MAPPING_OUT_PARAMS pOutParams;
} TAG_INFO_NAME_TAG_MAPPING, *PTAG_INFO_NAME_TAG_MAPPING;

_Must_inspect_result_
ULONG
WINAPI
I_QueryTagInformation(
    _In_opt_ PCWSTR MachineName,
    _In_ TAG_INFO_LEVEL InfoLevel,
    _Inout_ PVOID TagInfo
    );

typedef ULONG (WINAPI *PQUERY_TAG_INFORMATION)(
    _In_opt_ PCWSTR MachineName,
    _In_ TAG_INFO_LEVEL InfoLevel,
    _Inout_ PVOID TagInfo
    );
 


// #include <winsta.h>
// Access rights

#define WINSTATION_QUERY 0x00000001 // WinStationQueryInformation
#define WINSTATION_SET 0x00000002 // WinStationSetInformation
#define WINSTATION_RESET 0x00000004 // WinStationReset
#define WINSTATION_VIRTUAL 0x00000008 //read/write direct data
#define WINSTATION_SHADOW 0x00000010 // WinStationShadow
#define WINSTATION_LOGON 0x00000020 // logon to WinStation
#define WINSTATION_LOGOFF 0x00000040 // WinStationLogoff
#define WINSTATION_MSG 0x00000080 // WinStationMsg
#define WINSTATION_CONNECT 0x00000100 // WinStationConnect
#define WINSTATION_DISCONNECT 0x00000200 // WinStationDisconnect
#define WINSTATION_GUEST_ACCESS WINSTATION_LOGON

#define WINSTATION_CURRENT_GUEST_ACCESS (WINSTATION_VIRTUAL | WINSTATION_LOGOFF)
#define WINSTATION_USER_ACCESS (WINSTATION_GUEST_ACCESS | WINSTATION_QUERY | WINSTATION_CONNECT)
#define WINSTATION_CURRENT_USER_ACCESS \
    (WINSTATION_SET | WINSTATION_RESET | WINSTATION_VIRTUAL | \
    WINSTATION_LOGOFF | WINSTATION_DISCONNECT)
#define WINSTATION_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | WINSTATION_QUERY | \
    WINSTATION_SET | WINSTATION_RESET | WINSTATION_VIRTUAL | \
    WINSTATION_SHADOW | WINSTATION_LOGON | WINSTATION_MSG | \
    WINSTATION_CONNECT | WINSTATION_DISCONNECT)

#define WDPREFIX_LENGTH 12
#define CALLBACK_LENGTH 50
#define DLLNAME_LENGTH 32
#define CDNAME_LENGTH 32
#define WDNAME_LENGTH 32
#define PDNAME_LENGTH 32
#define DEVICENAME_LENGTH 128
#define MODEMNAME_LENGTH DEVICENAME_LENGTH
#define STACK_ADDRESS_LENGTH 128
#define MAX_BR_NAME 65
#define DIRECTORY_LENGTH 256
#define INITIALPROGRAM_LENGTH 256
#define USERNAME_LENGTH 20
#define DOMAIN_LENGTH 17
#define PASSWORD_LENGTH 14
#define NASISPECIFICNAME_LENGTH 14
#define NASIUSERNAME_LENGTH 47
#define NASIPASSWORD_LENGTH 24
#define NASISESSIONNAME_LENGTH 16
#define NASIFILESERVER_LENGTH 47

#define CLIENTDATANAME_LENGTH 7
#define CLIENTNAME_LENGTH 20
#define CLIENTADDRESS_LENGTH 30
#define IMEFILENAME_LENGTH 32
#define DIRECTORY_LENGTH 256
#define CLIENTLICENSE_LENGTH 32
#define CLIENTMODEM_LENGTH 40
#define CLIENT_PRODUCT_ID_LENGTH 32
#define MAX_COUNTER_EXTENSIONS 2
#define WINSTATIONNAME_LENGTH 32

#define TERMSRV_TOTAL_SESSIONS 1
#define TERMSRV_DISC_SESSIONS 2
#define TERMSRV_RECON_SESSIONS 3
#define TERMSRV_CURRENT_ACTIVE_SESSIONS 4
#define TERMSRV_CURRENT_DISC_SESSIONS 5
#define TERMSRV_PENDING_SESSIONS 6
#define TERMSRV_SUCC_TOTAL_LOGONS 7
#define TERMSRV_SUCC_LOCAL_LOGONS 8
#define TERMSRV_SUCC_REMOTE_LOGONS 9
#define TERMSRV_SUCC_SESSION0_LOGONS 10
#define TERMSRV_CURRENT_TERMINATING_SESSIONS 11
#define TERMSRV_CURRENT_LOGGEDON_SESSIONS 12

typedef RTL_TIME_ZONE_INFORMATION TS_TIME_ZONE_INFORMATION, *PTS_TIME_ZONE_INFORMATION;

typedef WCHAR WINSTATIONNAME[WINSTATIONNAME_LENGTH + 1];

// Variable length data descriptor (not needed)
typedef struct _VARDATA_WIRE
{
    USHORT Size;
    USHORT Offset;
} VARDATA_WIRE, *PVARDATA_WIRE;

typedef enum _WINSTATIONSTATECLASS
{
    State_Active = 0,
    State_Connected = 1,
    State_ConnectQuery = 2,
    State_Shadow = 3,
    State_Disconnected = 4,
    State_Idle = 5,
    State_Listen = 6,
    State_Reset = 7,
    State_Down = 8,
    State_Init = 9
} WINSTATIONSTATECLASS;

typedef struct _SESSIONIDW
{
    union
    {
        ULONG SessionId;
        ULONG LogonId;
    };
    WINSTATIONNAME WinStationName;
    WINSTATIONSTATECLASS State;
} SESSIONIDW, *PSESSIONIDW;

// private
typedef enum _WINSTATIONINFOCLASS
{
    WinStationCreateData, // WINSTATIONCREATE
    WinStationConfiguration, // WINSTACONFIGWIRE + USERCONFIG
    WinStationPdParams, // PDPARAMS
    WinStationWd, // WDCONFIG
    WinStationPd, // PDCONFIG2 + PDPARAMS
    WinStationPrinter, // Not supported.
    WinStationClient, // WINSTATIONCLIENT
    WinStationModules,
    WinStationInformation, // WINSTATIONINFORMATION
    WinStationTrace,
    WinStationBeep,
    WinStationEncryptionOff,
    WinStationEncryptionPerm,
    WinStationNtSecurity,
    WinStationUserToken, // WINSTATIONUSERTOKEN
    WinStationUnused1,
    WinStationVideoData, // WINSTATIONVIDEODATA
    WinStationInitialProgram,
    WinStationCd, // CDCONFIG
    WinStationSystemTrace,
    WinStationVirtualData,
    WinStationClientData, // WINSTATIONCLIENTDATA
    WinStationSecureDesktopEnter,
    WinStationSecureDesktopExit,
    WinStationLoadBalanceSessionTarget, // ULONG
    WinStationLoadIndicator, // WINSTATIONLOADINDICATORDATA
    WinStationShadowInfo, // WINSTATIONSHADOW
    WinStationDigProductId, // WINSTATIONPRODID
    WinStationLockedState, // BOOL
    WinStationRemoteAddress, // WINSTATIONREMOTEADDRESS
    WinStationIdleTime, // ULONG
    WinStationLastReconnectType, // ULONG
    WinStationDisallowAutoReconnect, // BOOLEAN
    WinStationMprNotifyInfo,
    WinStationExecSrvSystemPipe,
    WinStationSmartCardAutoLogon,
    WinStationIsAdminLoggedOn,
    WinStationReconnectedFromId, // ULONG
    WinStationEffectsPolicy, // ULONG
    WinStationType, // ULONG
    WinStationInformationEx, // WINSTATIONINFORMATIONEX 
    WinStationValidationInfo
} WINSTATIONINFOCLASS;

// Retrieves general information on the type of terminal server session (protocol) to which the session belongs.
typedef struct _WINSTATIONCREATE
{
    ULONG fEnableWinStation : 1;
    ULONG MaxInstanceCount;
} WINSTATIONCREATE, *PWINSTATIONCREATE;

typedef struct _WINSTACONFIGWIRE
{
    WCHAR Comment[61]; // The WinStation descriptive comment.
    CHAR OEMId[4]; // Value identifying the OEM implementor of the TermService Listener to which this session (WinStation) belongs. This can be any value defined by the implementer (OEM) of the listener.
    VARDATA_WIRE UserConfig; // VARDATA_WIRE structure defining the size and offset of the variable-length user configuration data succeeding it.
    VARDATA_WIRE NewFields; // VARDATA_WIRE structure defining the size and offset of the variable-length new data succeeding it. This field is not used and is a placeholder for any new data, if and when added.
} WINSTACONFIGWIRE, *PWINSTACONFIGWIRE;

typedef enum _CALLBACKCLASS
{
    Callback_Disable,
    Callback_Roving,
    Callback_Fixed
} CALLBACKCLASS;

// The SHADOWCLASS enumeration is used to indicate the shadow-related settings for a session running on a terminal server.
typedef enum _SHADOWCLASS
{
    Shadow_Disable, // Shadowing is disabled.
    Shadow_EnableInputNotify, // Permission is asked first from the session being shadowed. The shadower is also permitted keyboard and mouse input.
    Shadow_EnableInputNoNotify, // Permission is not asked first from the session being shadowed. The shadower is also permitted keyboard and mouse input.
    Shadow_EnableNoInputNotify, // Permission is asked first from the session being shadowed. The shadower is not permitted keyboard and mouse input and MUST observe the shadowed session.
    Shadow_EnableNoInputNoNotify // Permission is not asked first from the session being shadowed. The shadower is not permitted keyboard and mouse input and MUST observe the shadowed session.
} SHADOWCLASS;

// For a specific terminal server session, the USERCONFIG structure indicates the user and session configuration.
// https://msdn.microsoft.com/en-us/library/cc248610.aspx
typedef struct _USERCONFIG
{
    ULONG fInheritAutoLogon : 1;
    ULONG fInheritResetBroken : 1;
    ULONG fInheritReconnectSame : 1;
    ULONG fInheritInitialProgram : 1;
    ULONG fInheritCallback : 1;
    ULONG fInheritCallbackNumber : 1;
    ULONG fInheritShadow : 1;
    ULONG fInheritMaxSessionTime : 1;
    ULONG fInheritMaxDisconnectionTime : 1;
    ULONG fInheritMaxIdleTime : 1;
    ULONG fInheritAutoClient : 1;
    ULONG fInheritSecurity : 1;
    ULONG fPromptForPassword : 1;
    ULONG fResetBroken : 1;
    ULONG fReconnectSame : 1;
    ULONG fLogonDisabled : 1;
    ULONG fWallPaperDisabled : 1;
    ULONG fAutoClientDrives : 1;
    ULONG fAutoClientLpts : 1;
    ULONG fForceClientLptDef : 1;
    ULONG fRequireEncryption : 1;
    ULONG fDisableEncryption : 1;
    ULONG fUnused1 : 1;
    ULONG fHomeDirectoryMapRoot : 1;
    ULONG fUseDefaultGina : 1;
    ULONG fCursorBlinkDisabled : 1;
    ULONG fPublishedApp : 1;
    ULONG fHideTitleBar : 1;
    ULONG fMaximize : 1;
    ULONG fDisableCpm : 1;
    ULONG fDisableCdm : 1;
    ULONG fDisableCcm : 1;
    ULONG fDisableLPT : 1;
    ULONG fDisableClip : 1;
    ULONG fDisableExe : 1;
    ULONG fDisableCam : 1;
    ULONG fDisableAutoReconnect : 1;
    ULONG ColorDepth : 3;
    ULONG fInheritColorDepth : 1;
    ULONG fErrorInvalidProfile : 1;
    ULONG fPasswordIsScPin : 1;
    ULONG fDisablePNPRedir : 1;
    WCHAR UserName[USERNAME_LENGTH + 1];
    WCHAR Domain[DOMAIN_LENGTH + 1];
    WCHAR Password[PASSWORD_LENGTH + 1];
    WCHAR WorkDirectory[DIRECTORY_LENGTH + 1];
    WCHAR InitialProgram[INITIALPROGRAM_LENGTH + 1];
    WCHAR CallbackNumber[CALLBACK_LENGTH + 1];
    CALLBACKCLASS Callback;
    SHADOWCLASS Shadow;
    ULONG MaxConnectionTime;
    ULONG MaxDisconnectionTime;
    ULONG MaxIdleTime;
    ULONG KeyboardLayout;
    BYTE MinEncryptionLevel;
    WCHAR NWLogonServer[NASIFILESERVER_LENGTH + 1];
    WCHAR PublishedName[MAX_BR_NAME];
    WCHAR WFProfilePath[DIRECTORY_LENGTH + 1];
    WCHAR WFHomeDir[DIRECTORY_LENGTH + 1];
    WCHAR WFHomeDirDrive[4];
} USERCONFIG, *PUSERCONFIG;

typedef enum _SDCLASS
{
    SdNone = 0,
    SdConsole,
    SdNetwork,
    SdAsync,
    SdOemTransport
} SDCLASS;

typedef WCHAR DEVICENAME[DEVICENAME_LENGTH + 1];
typedef WCHAR MODEMNAME[MODEMNAME_LENGTH + 1];
typedef WCHAR NASISPECIFICNAME[NASISPECIFICNAME_LENGTH + 1];
typedef WCHAR NASIUSERNAME[NASIUSERNAME_LENGTH + 1];
typedef WCHAR NASIPASSWORD[NASIPASSWORD_LENGTH + 1];
typedef WCHAR NASISESIONNAME[NASISESSIONNAME_LENGTH + 1];
typedef WCHAR NASIFILESERVER[NASIFILESERVER_LENGTH + 1];
typedef WCHAR WDNAME[WDNAME_LENGTH + 1];
typedef WCHAR WDPREFIX[WDPREFIX_LENGTH + 1];
typedef WCHAR CDNAME[CDNAME_LENGTH + 1];
typedef WCHAR DLLNAME[DLLNAME_LENGTH + 1];
typedef WCHAR PDNAME[PDNAME_LENGTH + 1];

typedef struct _NETWORKCONFIG
{
    LONG LanAdapter;
    DEVICENAME NetworkName;
    ULONG Flags;
} NETWORKCONFIG, *PNETWORKCONFIG;

typedef enum _FLOWCONTROLCLASS
{
    FlowControl_None,
    FlowControl_Hardware,
    FlowControl_Software
} FLOWCONTROLCLASS;

typedef enum _RECEIVEFLOWCONTROLCLASS
{
    ReceiveFlowControl_None,
    ReceiveFlowControl_RTS,
    ReceiveFlowControl_DTR,
} RECEIVEFLOWCONTROLCLASS;

typedef enum _TRANSMITFLOWCONTROLCLASS
{
    TransmitFlowControl_None,
    TransmitFlowControl_CTS,
    TransmitFlowControl_DSR,
} TRANSMITFLOWCONTROLCLASS;

typedef enum _ASYNCCONNECTCLASS
{
    Connect_CTS,
    Connect_DSR,
    Connect_RI,
    Connect_DCD,
    Connect_FirstChar,
    Connect_Perm,
} ASYNCCONNECTCLASS;

typedef struct _FLOWCONTROLCONFIG
{
    ULONG fEnableSoftwareTx : 1;
    ULONG fEnableSoftwareRx : 1;
    ULONG fEnableDTR : 1;
    ULONG fEnableRTS : 1;
    CHAR XonChar;
    CHAR XoffChar;
    FLOWCONTROLCLASS Type;
    RECEIVEFLOWCONTROLCLASS HardwareReceive;
    TRANSMITFLOWCONTROLCLASS HardwareTransmit;
} FLOWCONTROLCONFIG, *PFLOWCONTROLCONFIG;

typedef struct _CONNECTCONFIG
{
    ASYNCCONNECTCLASS Type;
    ULONG fEnableBreakDisconnect : 1;
} CONNECTCONFIG, *PCONNECTCONFIG;

typedef struct _ASYNCCONFIG
{
    DEVICENAME DeviceName;
    MODEMNAME ModemName;
    ULONG BaudRate;
    ULONG Parity;
    ULONG StopBits;
    ULONG ByteSize;
    ULONG fEnableDsrSensitivity : 1;
    ULONG fConnectionDriver : 1;
    FLOWCONTROLCONFIG FlowControl;
    CONNECTCONFIG Connect;
} ASYNCCONFIG, *PASYNCCONFIG;

typedef struct _NASICONFIG
{
    NASISPECIFICNAME SpecificName;
    NASIUSERNAME UserName;
    NASIPASSWORD PassWord;
    NASISESIONNAME SessionName;
    NASIFILESERVER FileServer;
    BOOLEAN GlobalSession;
} NASICONFIG, *PNASICONFIG;

typedef struct _OEMTDCONFIG
{
    LONG Adapter;
    DEVICENAME DeviceName;
    ULONG Flags;
} OEMTDCONFIG, *POEMTDCONFIG;

// Retrieves transport protocol driver parameters.
typedef struct _PDPARAMS
{
    SDCLASS SdClass; // Stack driver class. Indicates which one of the union's structures is valid.
    union
    {
        NETWORKCONFIG Network; // Configuration of network drivers. Used if SdClass is SdNetwork.
        ASYNCCONFIG Async; // Configuration of async (modem) driver. Used if SdClass is SdAsync.
        NASICONFIG Nasi; // Reserved.
        OEMTDCONFIG OemTd; // Configuration of OEM transport driver. Used if SdClass is SdOemTransport.
    };
} PDPARAMS, *PPDPARAMS;

// The WinStation (session) driver configuration.
typedef struct _WDCONFIG
{
    WDNAME WdName; // The descriptive name of the WinStation driver.
    DLLNAME WdDLL; // The driver's image name.
    DLLNAME WsxDLL; // Used by the Terminal Services service to communicate with the WinStation driver.
    ULONG WdFlag; // Driver flags.
    ULONG WdInputBufferLength; // Length, in bytes, of the input buffer used by the driver. Defaults to 2048.
    DLLNAME CfgDLL; // Configuration DLL used by Terminal Services administrative tools for configuring the driver.
    WDPREFIX WdPrefix; // Used as the prefix of the WinStation name generated for the connected sessions with this WinStation driver.
} WDCONFIG, *PWDCONFIG;

// The protocol driver's software configuration.
typedef struct _PDCONFIG2
{
    PDNAME PdName;
    SDCLASS SdClass;
    DLLNAME PdDLL;
    ULONG PdFlag;
    ULONG OutBufLength;
    ULONG OutBufCount;
    ULONG OutBufDelay;
    ULONG InteractiveDelay;
    ULONG PortNumber;
    ULONG KeepAliveTimeout;
} PDCONFIG2, *PPDCONFIG2;

// WinStationClient
typedef struct _WINSTATIONCLIENT
{
    ULONG fTextOnly : 1;
    ULONG fDisableCtrlAltDel : 1;
    ULONG fMouse : 1;
    ULONG fDoubleClickDetect : 1;
    ULONG fINetClient : 1;
    ULONG fPromptForPassword : 1;
    ULONG fMaximizeShell : 1;
    ULONG fEnableWindowsKey : 1;
    ULONG fRemoteConsoleAudio : 1;
    ULONG fPasswordIsScPin : 1;
    ULONG fNoAudioPlayback : 1;
    ULONG fUsingSavedCreds : 1;
    WCHAR ClientName[CLIENTNAME_LENGTH + 1];
    WCHAR Domain[DOMAIN_LENGTH + 1];
    WCHAR UserName[USERNAME_LENGTH + 1];
    WCHAR Password[PASSWORD_LENGTH + 1];
    WCHAR WorkDirectory[DIRECTORY_LENGTH + 1];
    WCHAR InitialProgram[INITIALPROGRAM_LENGTH + 1];
    ULONG SerialNumber;
    BYTE EncryptionLevel;
    ULONG ClientAddressFamily;
    WCHAR ClientAddress[CLIENTADDRESS_LENGTH + 1];
    USHORT HRes;
    USHORT VRes;
    USHORT ColorDepth;
    USHORT ProtocolType;
    ULONG KeyboardLayout;
    ULONG KeyboardType;
    ULONG KeyboardSubType;
    ULONG KeyboardFunctionKey;
    WCHAR ImeFileName[IMEFILENAME_LENGTH + 1];
    WCHAR ClientDirectory[DIRECTORY_LENGTH + 1];
    WCHAR ClientLicense[CLIENTLICENSE_LENGTH + 1];
    WCHAR ClientModem[CLIENTMODEM_LENGTH + 1];
    ULONG ClientBuildNumber;
    ULONG ClientHardwareId;
    USHORT ClientProductId;
    USHORT OutBufCountHost;
    USHORT OutBufCountClient;
    USHORT OutBufLength;
    WCHAR AudioDriverName[9];
    TS_TIME_ZONE_INFORMATION ClientTimeZone;
    ULONG ClientSessionId;
    WCHAR ClientDigProductId[CLIENT_PRODUCT_ID_LENGTH];
    ULONG PerformanceFlags;
    ULONG ActiveInputLocale;
} WINSTATIONCLIENT, *PWINSTATIONCLIENT;

typedef struct _TSHARE_COUNTERS
{
    ULONG Reserved;
} TSHARE_COUNTERS, *PTSHARE_COUNTERS;

typedef struct _PROTOCOLCOUNTERS
{
    ULONG WdBytes;
    ULONG WdFrames;
    ULONG WaitForOutBuf;
    ULONG Frames;
    ULONG Bytes;
    ULONG CompressedBytes;
    ULONG CompressFlushes;
    ULONG Errors;
    ULONG Timeouts;
    ULONG AsyncFramingError;
    ULONG AsyncOverrunError;
    ULONG AsyncOverflowError;
    ULONG AsyncParityError;
    ULONG TdErrors;
    USHORT ProtocolType;
    USHORT Length;
    union
    {
        TSHARE_COUNTERS TShareCounters;
        ULONG Reserved[100];
    } Specific;
} PROTOCOLCOUNTERS, *PPROTOCOLCOUNTERS;

typedef struct _THINWIRECACHE
{
    ULONG CacheReads;
    ULONG CacheHits;
} THINWIRECACHE, *PTHINWIRECACHE;

#define MAX_THINWIRECACHE 4

typedef struct _RESERVED_CACHE
{
    THINWIRECACHE ThinWireCache[MAX_THINWIRECACHE];
} RESERVED_CACHE, *PRESERVED_CACHE;

typedef struct _TSHARE_CACHE
{
    ULONG Reserved;
} TSHARE_CACHE, *PTSHARE_CACHE;

typedef struct CACHE_STATISTICS
{
    USHORT ProtocolType;
    USHORT Length;
    union
    {
        RESERVED_CACHE ReservedCacheStats;
        TSHARE_CACHE TShareCacheStats;
        ULONG Reserved[20];
    } Specific;
} CACHE_STATISTICS, *PCACHE_STATISTICS;

typedef struct _PROTOCOLSTATUS
{
    PROTOCOLCOUNTERS Output;
    PROTOCOLCOUNTERS Input;
    CACHE_STATISTICS Cache;
    ULONG AsyncSignal;
    ULONG AsyncSignalMask;
} PROTOCOLSTATUS, *PPROTOCOLSTATUS;

// Retrieves information on the session.
typedef struct _WINSTATIONINFORMATION
{
    WINSTATIONSTATECLASS ConnectState;
    WINSTATIONNAME WinStationName;
    ULONG LogonId;
    LARGE_INTEGER ConnectTime;
    LARGE_INTEGER DisconnectTime;
    LARGE_INTEGER LastInputTime;
    LARGE_INTEGER LogonTime;
    PROTOCOLSTATUS Status;
    WCHAR Domain[DOMAIN_LENGTH + 1];
    WCHAR UserName[USERNAME_LENGTH + 1];
    LARGE_INTEGER CurrentTime;
} WINSTATIONINFORMATION, *PWINSTATIONINFORMATION;

// Retrieves the user's token in the session. Caller requires WINSTATION_ALL_ACCESS permission.
typedef struct _WINSTATIONUSERTOKEN
{
    HANDLE ProcessId;
    HANDLE ThreadId;
    HANDLE UserToken;
} WINSTATIONUSERTOKEN, *PWINSTATIONUSERTOKEN;

// Retrieves resolution and color depth of the session.
typedef struct _WINSTATIONVIDEODATA
{
    USHORT HResolution;
    USHORT VResolution;
    USHORT fColorDepth;
} WINSTATIONVIDEODATA, *PWINSTATIONVIDEODATA;

typedef enum _CDCLASS
{
    CdNone, // No connection driver.   
    CdModem, // Connection driver is a modem.
    CdClass_Maximum,
} CDCLASS;

// Connection driver configuration. It is used for connecting via modem to a server.
typedef struct _CDCONFIG
{
    CDCLASS CdClass; // Connection driver type.
    CDNAME CdName; // Connection driver descriptive name.
    DLLNAME CdDLL; // Connection driver image name.
    ULONG CdFlag; // Connection driver flags. Connection driver specific.
} CDCONFIG, *PCDCONFIG;

// The name has the following form:
// name syntax : xxxyyyy<null>
typedef CHAR CLIENTDATANAME[CLIENTDATANAME_LENGTH + 1];
typedef CHAR* PCLIENTDATANAME;

typedef struct _WINSTATIONCLIENTDATA
{
    CLIENTDATANAME DataName; // Identifies the type of data sent in this WINSTATIONCLIENTDATA structure. The definition is dependent on the caller and on the client receiving it. This MUST be a data name following a format similar to that of the CLIENTDATANAME data type.
    BOOLEAN fUnicodeData; // TRUE indicates data is in Unicode format; FALSE otherwise.
} WINSTATIONCLIENTDATA, *PWINSTATIONCLIENTDATA;

typedef enum _LOADFACTORTYPE
{
    ErrorConstraint, // An error occurred while obtaining constraint data.
    PagedPoolConstraint, // The amount of paged pool is the constraint.
    NonPagedPoolConstraint, // The amount of non-paged pool is the constraint.
    AvailablePagesConstraint, // The amount of available pages is the constraint.
    SystemPtesConstraint, // The number of system page table entries (PTEs) is the constraint.
    CPUConstraint // CPU usage is the constraint.
} LOADFACTORTYPE;

// The WINSTATIONLOADINDICATORDATA structure defines data used for the load balancing of a server.
typedef struct _WINSTATIONLOADINDICATORDATA
{
    ULONG RemainingSessionCapacity; // The estimated number of additional sessions that can be supported given the CPU constraint.
    LOADFACTORTYPE LoadFactor; // Indicates the most constrained current resource.
    ULONG TotalSessions; // The total number of sessions.
    ULONG DisconnectedSessions; // The number of disconnected sessions.
    LARGE_INTEGER IdleCPU; // This is always set to 0.
    LARGE_INTEGER TotalCPU; // This is always set to 0.
    ULONG RawSessionCapacity; // The raw number of sessions capacity.
    ULONG reserved[9]; // Reserved.
} WINSTATIONLOADINDICATORDATA, *PWINSTATIONLOADINDICATORDATA;

typedef enum _SHADOWSTATECLASS
{
    State_NoShadow, // No shadow operations are currently being performed on this session.
    State_Shadowing, // The session is shadowing a different session. The current session is referred to as a shadow client.
    State_Shadowed // The session is being shadowed by a different session. The current session is referred to as a shadow target.
} SHADOWSTATECLASS;

// Retrieves the current shadow state of a session.
typedef struct _WINSTATIONSHADOW
{
    SHADOWSTATECLASS ShadowState; // Specifies the current state of shadowing.
    SHADOWCLASS ShadowClass; // Specifies the type of shadowing.
    ULONG SessionId; // Specifies the session ID of the session.
    ULONG ProtocolType; // Specifies the type of protocol on the session. Can be one of the following values.
} WINSTATIONSHADOW, *PWINSTATIONSHADOW;

// Retrieves the client product ID and current product ID of the session.
typedef struct _WINSTATIONPRODID
{
    WCHAR DigProductId[CLIENT_PRODUCT_ID_LENGTH];
    WCHAR ClientDigProductId[CLIENT_PRODUCT_ID_LENGTH];
    WCHAR OuterMostDigProductId[CLIENT_PRODUCT_ID_LENGTH];
    ULONG CurrentSessionId;
    ULONG ClientSessionId;
    ULONG OuterMostSessionId;
} WINSTATIONPRODID, *PWINSTATIONPRODID;

// Retrieves the remote IP address of the terminal server client in the session.
typedef struct _WINSTATIONREMOTEADDRESS
{
    USHORT sin_family;
    union
    {
        struct
        {
            USHORT sin_port;
            ULONG sin_addr;
            UCHAR sin_zero[8];
        } ipv4;
        struct
        {
            USHORT sin6_port;
            ULONG sin6_flowinfo;
            USHORT sin6_addr[8];
            ULONG sin6_scope_id;
        } ipv6;
    };
} WINSTATIONREMOTEADDRESS, *PWINSTATIONREMOTEADDRESS;

// WinStationInformationEx

// private
typedef struct _WINSTATIONINFORMATIONEX_LEVEL1
{
    ULONG SessionId;
    WINSTATIONSTATECLASS SessionState;
    LONG SessionFlags;
    WINSTATIONNAME WinStationName;
    WCHAR UserName[USERNAME_LENGTH + 1];
    WCHAR DomainName[DOMAIN_LENGTH + 1];
    LARGE_INTEGER LogonTime;
    LARGE_INTEGER ConnectTime;
    LARGE_INTEGER DisconnectTime;
    LARGE_INTEGER LastInputTime;
    LARGE_INTEGER CurrentTime;
    PROTOCOLSTATUS ProtocolStatus;
} WINSTATIONINFORMATIONEX_LEVEL1, *PWINSTATIONINFORMATIONEX_LEVEL1;

// private
typedef struct _WINSTATIONINFORMATIONEX_LEVEL2
{
    ULONG SessionId;
    WINSTATIONSTATECLASS SessionState;
    LONG SessionFlags;
    WINSTATIONNAME WinStationName;
    WCHAR SamCompatibleUserName[USERNAME_LENGTH + 1];
    WCHAR SamCompatibleDomainName[DOMAIN_LENGTH + 1];
    LARGE_INTEGER LogonTime;
    LARGE_INTEGER ConnectTime;
    LARGE_INTEGER DisconnectTime;
    LARGE_INTEGER LastInputTime;
    LARGE_INTEGER CurrentTime;
    PROTOCOLSTATUS ProtocolStatus;
    WCHAR UserName[257];
    WCHAR DomainName[256];
} WINSTATIONINFORMATIONEX_LEVEL2, *PWINSTATIONINFORMATIONEX_LEVEL2;

// private
typedef union _WINSTATIONINFORMATIONEX_LEVEL
{
    WINSTATIONINFORMATIONEX_LEVEL1 WinStationInfoExLevel1;
    WINSTATIONINFORMATIONEX_LEVEL2 WinStationInfoExLevel2;
} WINSTATIONINFORMATIONEX_LEVEL, *PWINSTATIONINFORMATIONEX_LEVEL;

// private
typedef struct _WINSTATIONINFORMATIONEX
{
    ULONG Level;
    WINSTATIONINFORMATIONEX_LEVEL Data;
} WINSTATIONINFORMATIONEX, *PWINSTATIONINFORMATIONEX;

#define TS_PROCESS_INFO_MAGIC_NT4 0x23495452

typedef struct _TS_PROCESS_INFORMATION_NT4
{
    ULONG MagicNumber;
    ULONG LogonId;
    PVOID ProcessSid;
    ULONG Pad;
} TS_PROCESS_INFORMATION_NT4, *PTS_PROCESS_INFORMATION_NT4;

#define SIZEOF_TS4_SYSTEM_THREAD_INFORMATION 64
#define SIZEOF_TS4_SYSTEM_PROCESS_INFORMATION 136

typedef struct _TS_SYS_PROCESS_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    LARGE_INTEGER SpareLi1;
    LARGE_INTEGER SpareLi2;
    LARGE_INTEGER SpareLi3;
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    LONG BasePriority;
    ULONG UniqueProcessId;
    ULONG InheritedFromUniqueProcessId;
    ULONG HandleCount;
    ULONG SessionId;
    ULONG SpareUl3;
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    ULONG PeakWorkingSetSize;
    ULONG WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
} TS_SYS_PROCESS_INFORMATION, *PTS_SYS_PROCESS_INFORMATION;

typedef struct _TS_ALL_PROCESSES_INFO
{
    PTS_SYS_PROCESS_INFORMATION pTsProcessInfo;
    ULONG SizeOfSid;
    PSID pSid;
} TS_ALL_PROCESSES_INFO, *PTS_ALL_PROCESSES_INFO;

typedef struct _TS_COUNTER_HEADER
{
    DWORD dwCounterID;
    BOOLEAN bResult;
} TS_COUNTER_HEADER, *PTS_COUNTER_HEADER;

typedef struct _TS_COUNTER
{
    TS_COUNTER_HEADER CounterHead;
    DWORD dwValue;
    LARGE_INTEGER StartTime;
} TS_COUNTER, *PTS_COUNTER;

// Flags for WinStationShutdownSystem
#define WSD_LOGOFF 0x1
#define WSD_SHUTDOWN 0x2
#define WSD_REBOOT 0x4
#define WSD_POWEROFF 0x8

// Flags for WinStationWaitSystemEvent
#define WEVENT_NONE 0x0
#define WEVENT_CREATE 0x1
#define WEVENT_DELETE 0x2
#define WEVENT_RENAME 0x4
#define WEVENT_CONNECT 0x8
#define WEVENT_DISCONNECT 0x10
#define WEVENT_LOGON 0x20
#define WEVENT_LOGOFF 0x40
#define WEVENT_STATECHANGE 0x80
#define WEVENT_LICENSE 0x100
#define WEVENT_ALL 0x7fffffff
#define WEVENT_FLUSH 0x80000000

// Hotkey modifiers for WinStationShadow
#define KBDSHIFT 0x1
#define KBDCTRL 0x2
#define KBDALT 0x4

// begin_rev
// Flags for WinStationRegisterConsoleNotification
#define WNOTIFY_ALL_SESSIONS 0x1
// end_rev

// In the functions below, memory returned can be freed using LocalFree. NULL can be specified for
// server handles to indicate the local server. -1 can be specified for session IDs to indicate the
// current session ID.

#define LOGONID_CURRENT (-1)
#define SERVERNAME_CURRENT ((PWSTR)NULL)

// rev
BOOLEAN
WINAPI
WinStationFreeMemory(
    _In_ PVOID Buffer
    );

// rev
HANDLE
WINAPI
WinStationOpenServerW(
    _In_ PWSTR ServerName
    );

// rev
BOOLEAN
WINAPI
WinStationCloseServer(
    _In_ HANDLE ServerHandle
    );

// rev
BOOLEAN
WINAPI
WinStationServerPing(
    _In_opt_ HANDLE ServerHandle
    );

// rev
BOOLEAN
WINAPI
WinStationGetTermSrvCountersValue(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG Count,
    _Inout_ PTS_COUNTER Counters // set counter IDs before calling
    );

BOOLEAN
WINAPI
WinStationShutdownSystem(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG ShutdownFlags // WSD_*
    );

// rev
BOOLEAN
WINAPI
WinStationWaitSystemEvent(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG EventMask, // WEVENT_*
    _Out_ PULONG EventFlags
    );

// rev
BOOLEAN
WINAPI
WinStationRegisterConsoleNotification(
    _In_opt_ HANDLE ServerHandle,
    _In_ HWND WindowHandle,
    _In_ ULONG Flags
    );

// rev
BOOLEAN
WINAPI
WinStationUnRegisterConsoleNotification(
    _In_opt_ HANDLE ServerHandle,
    _In_ HWND WindowHandle
    );

// Sessions

// rev
BOOLEAN
WINAPI
WinStationEnumerateW(
    _In_opt_ HANDLE ServerHandle,
    _Out_ PSESSIONIDW *SessionIds,
    _Out_ PULONG Count
    );

BOOLEAN
WINAPI
WinStationQueryInformationW(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG SessionId,
    _In_ WINSTATIONINFOCLASS WinStationInformationClass,
    _Out_writes_bytes_(WinStationInformationLength) PVOID pWinStationInformation,
    _In_ ULONG WinStationInformationLength,
    _Out_ PULONG pReturnLength
    );

// rev
BOOLEAN
WINAPI
WinStationSetInformationW(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG SessionId,
    _In_ WINSTATIONINFOCLASS WinStationInformationClass,
    _In_reads_bytes_(WinStationInformationLength) PVOID pWinStationInformation,
    _In_ ULONG WinStationInformationLength
    );

BOOLEAN
WINAPI
WinStationNameFromLogonIdW(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG SessionId,
    _Out_writes_(WINSTATIONNAME_LENGTH + 1) PWSTR pWinStationName
    );

// rev
BOOLEAN
WINAPI
WinStationSendMessageW(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG SessionId,
    _In_ PWSTR Title,
    _In_ ULONG TitleLength,
    _In_ PWSTR Message,
    _In_ ULONG MessageLength,
    _In_ ULONG Style,
    _In_ ULONG Timeout,
    _Out_ PULONG Response,
    _In_ BOOLEAN DoNotWait
    );

BOOLEAN
WINAPI
WinStationConnectW(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG SessionId,
    _In_ ULONG TargetSessionId,
    _In_opt_ PWSTR pPassword,
    _In_ BOOLEAN bWait
    );

BOOLEAN
WINAPI
WinStationDisconnect(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG SessionId,
    _In_ BOOLEAN bWait
    );

// rev
BOOLEAN
WINAPI
WinStationReset(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG SessionId,
    _In_ BOOLEAN bWait
    );

// rev
BOOLEAN
WINAPI
WinStationShadow(
    _In_opt_ HANDLE ServerHandle,
    _In_ PWSTR TargetServerName,
    _In_ ULONG TargetSessionId,
    _In_ UCHAR HotKeyVk,
    _In_ USHORT HotkeyModifiers // KBD*
    );

// rev
BOOLEAN
WINAPI
WinStationShadowStop(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG SessionId,
    _In_ BOOLEAN bWait // ignored
    );

// Processes

// rev
BOOLEAN
WINAPI
WinStationEnumerateProcesses(
    _In_opt_ HANDLE ServerHandle,
    _Out_ PVOID *Processes
    );

// rev
BOOLEAN
WINAPI
WinStationGetAllProcesses(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG Level,
    _Out_ PULONG NumberOfProcesses,
    _Out_ PTS_ALL_PROCESSES_INFO *Processes
    );

// rev
BOOLEAN
WINAPI
WinStationFreeGAPMemory(
    _In_ ULONG Level,
    _In_ PTS_ALL_PROCESSES_INFO Processes,
    _In_ ULONG NumberOfProcesses
    );

// rev
BOOLEAN
WINAPI
WinStationTerminateProcess(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG ProcessId,
    _In_ ULONG ExitCode
    );

BOOLEAN
WINAPI
WinStationGetProcessSid(
    _In_opt_ HANDLE ServerHandle,
    _In_ ULONG ProcessId,
    _In_ FILETIME ProcessStartTime,
    _Out_ PVOID pProcessUserSid,
    _Inout_ PULONG dwSidSize
    );

// Services isolation

#if (NTDDI_VERSION >= NTDDI_VISTA)

// rev
BOOLEAN
WINAPI
WinStationSwitchToServicesSession(
    VOID
    );

// rev
BOOLEAN
WINAPI
WinStationRevertFromServicesSession(
    VOID
    );

#endif

// Misc.

BOOLEAN
WINAPI
_WinStationWaitForConnect(
    VOID
    );
 


#ifdef __cplusplus
}
#endif

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif



#ifdef __cplusplus
#ifdef MINT_USE_SEPARATE_NAMESPACE
}
#endif
#endif

#endif // !_MINT_
