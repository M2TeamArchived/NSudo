/******************************************************************************
项目:
	M2-Team\\NSudo\\NSudoSDK
描述：
	用户模式本机API调用及其数据结构定义
文件名:
	\\NSudoSDK\\M2.Native.hpp
基于项目：
	Process Hacker的PHNT库
许可协议：
	无（致敬ProcessHacker作者Wen Jia Liu）
用法：
	直接Include此头文件即可，如果要在内核模式使用则需要定义KERNELMODE宏
	如果出现C4668警告，则在预处理头文件定义加入以下内容
		#define _WIN32_WINNT_WIN10_TH2 _WIN32_WINNT_WIN10
		#define _WIN32_WINNT_WIN10_RS1 _WIN32_WINNT_WIN10
建议的Windows SDK版本：
	10.0.10586及以后
维护者列表：
	Mouri_Naruto (Mouri_Naruto@Outlook.com)
修订日志：
	2.2 (2017-01-06)
	移除关于C4668警告的解决方案（因为不起作用），改为在用法提示解决方法

	2.1 (2017-01-05)
	使用新的代码标头

	2.0 (2017-01-01)
	1.修复一些定义的错误
	2.增加对Zw开头系统调用的定义
	3.增加NTSTATUS的定义
	4.扩充基本的NT结构定义
	5.增添我和原作者的邮件内容（为什么不做任何的开源协议限制的原因）
	6.内置包含Windows IO操作定义

	1.0 (2016-06-26)
	初始版本，对基于Process Hacker的PHNT库进行了大幅度修改
	（去除了内核模式定义和整合了头文件，而且对里面的宏进行了标准化处理）  
******************************************************************************/

// 发送给Process Hacker作者的邮件（如果这信有语法错误，请包涵）
// PS：该邮件的中文只是我为了方便你们理解而加上去的
//
// Dear wj32
//
// I find the phnt lib when I was searching for information about Native API a 
// few days ago.
// 几天前我在查找Native API有关资料时发现了PHNT库
//
// I modify it and want to add it into my open source project which is 
// distributed under The MIT License.
// 我修改了它并想添加到使用了MIT协议的开源项目中
//
// But the Process Hacker is distributed under the GNU GPL version 3. So I want
//  to ask you for the permission.
// 但是Process Hacker使用GNU GPL version 3发行，所以我想请求你的许可
//
// I will add your permission text into the readme of my project
// 我将会在项目的Readme加入你的许可内容
//
// I am looking forward to hearing from you.
// 期待你的来信
//
// Yours, Mouri
//
// 作者回复 + 个人的理解（我也问了我的三个朋友，他们也觉得可以这样理解）
//
// I'm not clear on the copyright status of API headers, 
// but sorry I will not relicense such a big part of the project under MIT.
// 我不清楚API头文件的版权状态，但我不会以MIT协议重新发布PHNT项目
//
// Nevertheless some say that headers cannot be copyrighted and have copied
// phnt verbatim anyway without asking me.So do what you will...
// 不过一些人说头文件不能被版权保护且他们并未通知我就直接搬来使用；
// 所以，你做你想做的吧……
//
// 鉴于此（So do what you will...）
// 由于对作者的感激；也出于想方便众人的考量
// 该头文件不做任何的开源协议限制，随便你们用
// 
// 当然如果可以的话，希望你们可以安利（宣传）下Process Hacker项目
// http://processhacker.sourceforge.net/
// 这是一个非常不错的进程查看器
// 里面拥有除了微软外最齐全的ring3模式的Native API定义（即PHNT库）
//
// 如果你们只要纯粹的Native API定义的话，请参考这里
// https://github.com/Chuyu-Team/NativeLib
// 这个库我也会随时更新

// 翻译自Process Hacker对phnt库的注释（仅供参考）

// 该头文件提供本机API的定义

// 定义的注释会说明来源，以下是对该方面注释的说明
// * 没有注释 代表该定义从微软官方头文件中获取（NT和DDK头文件, winnt.h） 
// * "winbase" 代表该定义从Win32化的NT定义头文件(winbase.h)获取
// * "rev" 代表该定义是通过逆向工程获取
// * "dbg" 代表该定义通过Checked编译内核或者文件获取的调试信息和断点获取

// 可信度
// 1. 没有注释
// 2. dbg.
// 3. symbols, private. 类型也许有误
// 4. winbase. 名称和类型也许有误
// 5. rev.

#ifndef NATIVEAPI
#define NATIVEAPI

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

// 为编译通过而禁用的警告
//*****************************************************************************

#if _MSC_VER >= 1200
#pragma warning(push)
// 以下是ntdef.h定义的为编译通过而禁用的警告
#pragma warning(disable:4201) // 无名称的结构/联合(等级 4)
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
// 以下是ntisf.h定义的为编译通过而禁用的警告
#pragma warning(disable:4324) // 由于对齐说明符，结构被填充(等级 4)
// 为了定义未公开枚举的为编译通过而禁用的警告
#pragma warning(disable:4471) // 不带范围的枚举的前向声明(等级 4)
#endif

//*****************************************************************************

// 使用的Windows SDK头文件定义
//*****************************************************************************

#include <SDKDDKVer.h> // WindowsSDK平台定义

#include <windows.h> // Windows 头文件
#include <winioctl.h> // Windows IO操作定义

#pragma comment(lib,"ntdll.lib") // 指明编译时要链接ntdll.lib

//*****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// 定义winnt.h缺失但存在于ntdef.h的NT基本结构
//*****************************************************************************

#ifndef _NTDEF_
#define _NTDEF_

#ifndef DECLSPEC_GUARDIGNORE
#if (_MSC_FULL_VER >= 170065501) || defined(_D1VERSIONLKG171_)
#define DECLSPEC_GUARDIGNORE  __declspec(guard(ignore))
#else
#define DECLSPEC_GUARDIGNORE
#endif
#endif

#ifndef _MANAGED
#if defined(_M_IX86)
#define FASTCALL __fastcall
#else
#define FASTCALL
#endif
#else
#define FASTCALL NTAPI 
#endif

//
// The type QUAD and UQUAD are intended to use when a 8 byte aligned structure
// is required, but it is not a floating point number.
//

typedef struct _QUAD
{
	union
	{
		__int64 UseThisFieldToCopy;
		double  DoNotUseThisField;
	} DUMMYUNIONNAME;

} QUAD, UQUAD, *PQUAD, *PUQUAD;

//
// This isn't in NT, but it's useful.
//
typedef struct DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT) _QUAD_PTR
{
	ULONG_PTR DoNotUseThisField1;
	ULONG_PTR DoNotUseThisField2;
} QUAD_PTR, *PQUAD_PTR;

#if _WIN32_WINNT >= 0x0600 || (defined(__cplusplus) && defined(WINDOWS_ENABLE_CPLUSPLUS))

//
// Pointer to Const Unsigned Basics
//

typedef CONST UCHAR *PCUCHAR;
typedef CONST USHORT *PCUSHORT;
typedef CONST ULONG *PCULONG;
typedef CONST UQUAD *PCUQUAD;

#endif // _WIN32_WINNT >= 0x0600

//
// Signed characters
//

typedef signed char SCHAR, *PSCHAR;

#if _WIN32_WINNT >= 0x0600 || (defined(__cplusplus) && defined(WINDOWS_ENABLE_CPLUSPLUS))

typedef CONST SCHAR *PCSCHAR;

#endif // _WIN32_WINNT >= 0x0600

//
// Low order two bits of a handle are ignored by the system and available
// for use by application code as tag bits.  The remaining bits are opaque
// and used to store a serial number and table index.
//

#define OBJ_HANDLE_TAGBITS  0x00000003L

//
// Cardinal Data Types [0 - 2**N-2)
//

typedef CCHAR *PCCHAR;
typedef short CSHORT, *PCSHORT;
typedef ULONG CLONG, *PCLONG;

//
// Logical Data Type - These are 32-bit logical values.
//

typedef ULONG LOGICAL, *PLOGICAL;

//
// NTSTATUS //

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
/*lint -save -e624 */  // Don't complain about different typedefs.
typedef NTSTATUS *PNTSTATUS;
/*lint -restore */  // Resume checking for different typedefs.

#if _WIN32_WINNT >= 0x0600
typedef CONST NTSTATUS *PCNTSTATUS;
#endif // _WIN32_WINNT >= 0x0600

//
//  Status values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-------------------------+-------------------------------+
//  |Sev|C|       Facility          |               Code            |
//  +---+-+-------------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

//
// Generic test for information on any status value.
//

#ifdef _PREFAST_
#define NT_INFORMATION(Status) (((NTSTATUS)(Status)) >= (long)0x40000000)
#else
#define NT_INFORMATION(Status) ((((ULONG)(Status)) >> 30) == 1)
#endif

//
// Generic test for warning on any status value.
//

#ifdef _PREFAST_
#define NT_WARNING(Status) (((NTSTATUS)(Status) < (long)0xc0000000))
#else
#define NT_WARNING(Status) ((((ULONG)(Status)) >> 30) == 2)
#endif

//
// Generic test for error on any status value.
//

#ifdef _PREFAST_
#define NT_ERROR(Status) (((NTSTATUS)(Status)) >= (unsigned long)0xc0000000)
#else
#define NT_ERROR(Status) ((((ULONG)(Status)) >> 30) == 3)
#endif

//
// NT status macros
//
#define NT_FACILITY_MASK 0xfff
#define NT_FACILITY_SHIFT 16
#define NT_FACILITY(Status) ((((ULONG)(Status)) >> NT_FACILITY_SHIFT) & NT_FACILITY_MASK)

#define NT_NTWIN32(Status) (NT_FACILITY(Status) == FACILITY_NTWIN32)
#define WIN32_FROM_NTSTATUS(Status) (((ULONG)(Status)) & 0xffff)

//
// Large (64-bit) integer types and operations
//

#define TIME LARGE_INTEGER
#define _TIME _LARGE_INTEGER
#define PTIME PLARGE_INTEGER
#define LowTime LowPart
#define HighTime HighPart

//
// Physical address.
//

typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

//
// Event type
//

typedef enum _EVENT_TYPE
{
	NotificationEvent,
	SynchronizationEvent
} EVENT_TYPE;

//
// Timer type
//

typedef enum _TIMER_TYPE
{
	NotificationTimer,
	SynchronizationTimer
} TIMER_TYPE;

//
// Wait type
//

typedef enum _WAIT_TYPE
{
	WaitAll,
	WaitAny,
	WaitNotification,
	WaitDequeue
} WAIT_TYPE;

//
// Pointer to an Asciiz string
//

typedef _Null_terminated_ CHAR *PSZ;
typedef _Null_terminated_ CONST char *PCSZ;

//
// Counted String
//

typedef USHORT RTL_STRING_LENGTH_TYPE;

typedef struct _STRING
{
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength), length_is(Length)]
#endif // MIDL_PASS
	_Field_size_bytes_part_opt_(MaximumLength, Length) PCHAR Buffer;
} STRING, *PSTRING, ANSI_STRING, *PANSI_STRING, OEM_STRING, *POEM_STRING;

typedef CONST STRING* PCOEM_STRING;

//
// CONSTCounted String
//

typedef struct _CSTRING
{
	USHORT Length;
	USHORT MaximumLength;
	CONST char *Buffer;
} CSTRING, *PCSTRING, CANSI_STRING, *PCANSI_STRING;

//
// Unicode strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT * Buffer;
#else // MIDL_PASS
	_Field_size_bytes_part_opt_(MaximumLength, Length) PWCH   Buffer;
#endif // MIDL_PASS
} UNICODE_STRING, *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

#if _WIN32_WINNT >= 0x0500

#define DECLARE_CONST_UNICODE_STRING(_var, _string) \
	const WCHAR _var ## _buffer[] = _string; \
	__pragma(warning(push)) \
	__pragma(warning(disable:4221)) __pragma(warning(disable:4204)) \
	const UNICODE_STRING _var = { sizeof(_string) - sizeof(WCHAR), sizeof(_string), (PWCH) _var ## _buffer } \
	                            __pragma(warning(pop))

#define DECLARE_GLOBAL_CONST_UNICODE_STRING(_var, _str) \
	extern const __declspec(selectany) UNICODE_STRING _var = RTL_CONSTANT_STRING(_str)

#define DECLARE_UNICODE_STRING_SIZE(_var, _size) \
	WCHAR _var ## _buffer[_size]; \
	__pragma(warning(push)) \
	__pragma(warning(disable:4221)) __pragma(warning(disable:4204)) \
	UNICODE_STRING _var = { 0, (_size) * sizeof(WCHAR) , _var ## _buffer } \
	                      __pragma(warning(pop))

#endif // _WIN32_WINNT >= 0x0500

//
// Balanced tree node (AVL or RB) structure definitinon.
//

#pragma warning(push)
#pragma warning(disable:4214)

typedef struct _RTL_BALANCED_NODE
{
	union
	{
		struct _RTL_BALANCED_NODE *Children[2];
		struct
		{
			struct _RTL_BALANCED_NODE *Left;
			struct _RTL_BALANCED_NODE *Right;
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME;

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

	union
	{
		UCHAR Red : 1;
		UCHAR Balance : 2;
		ULONG_PTR ParentValue;
	} DUMMYUNIONNAME2;
} RTL_BALANCED_NODE, *PRTL_BALANCED_NODE;

#pragma warning(pop)

#define RTL_BALANCED_NODE_GET_PARENT_POINTER(Node) \
	((PRTL_BALANCED_NODE)((Node)->ParentValue & \
	                      ~RTL_BALANCED_NODE_RESERVED_PARENT_MASK))


typedef struct _SINGLE_LIST_ENTRY32
{
	ULONG Next;
} SINGLE_LIST_ENTRY32, *PSINGLE_LIST_ENTRY32;

#if !defined(MIDL_PASS)
__inline void ListEntry32To64(
	_In_ PLIST_ENTRY32 l32,
	_Out_ PLIST_ENTRY64 l64)
{
	l64->Flink = (ULONGLONG)(ULONG)l32->Flink;
	l64->Blink = (ULONGLONG)(ULONG)l32->Blink;
}

__inline void ListEntry64To32(
	_In_ PLIST_ENTRY64 l64,
	_Out_ PLIST_ENTRY32 l32)
{
	l32->Flink = (ULONG)l64->Flink;
	l32->Blink = (ULONG)l64->Blink;
}
#endif

typedef struct _STRING32
{
	USHORT   Length;
	USHORT   MaximumLength;
	ULONG  Buffer;
} STRING32;
typedef STRING32 *PSTRING32, ANSI_STRING32, *PANSI_STRING32;
typedef STRING32 UNICODE_STRING32, *PUNICODE_STRING32;

typedef struct _STRING64
{
	USHORT   Length;
	USHORT   MaximumLength;
	ULONGLONG  Buffer;
} STRING64;
typedef STRING64 *PSTRING64, ANSI_STRING64, *PANSI_STRING64;
typedef STRING64 UNICODE_STRING64, *PUNICODE_STRING64;

//
// Valid values for the Attributes field
//

#define OBJ_INHERIT                         0x00000002L
#define OBJ_PERMANENT                       0x00000010L
#define OBJ_EXCLUSIVE                       0x00000020L
#define OBJ_CASE_INSENSITIVE                0x00000040L
#define OBJ_OPENIF                          0x00000080L
#define OBJ_OPENLINK                        0x00000100L
#define OBJ_KERNEL_HANDLE                   0x00000200L
#define OBJ_FORCE_ACCESS_CHECK              0x00000400L
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP   0x00000800L
#define OBJ_DONT_REPARSE                    0x00001000L
#define OBJ_VALID_ATTRIBUTES                0x00001FF2L

//
// Object Attributes structure
//

typedef struct _OBJECT_ATTRIBUTES64
{
	ULONG Length;
	ULONG64 RootDirectory;
	ULONG64 ObjectName;
	ULONG Attributes;
	ULONG64 SecurityDescriptor;
	ULONG64 SecurityQualityOfService;
} OBJECT_ATTRIBUTES64, *POBJECT_ATTRIBUTES64;
typedef CONST OBJECT_ATTRIBUTES64 *PCOBJECT_ATTRIBUTES64;

typedef struct _OBJECT_ATTRIBUTES32
{
	ULONG Length;
	ULONG RootDirectory;
	ULONG ObjectName;
	ULONG Attributes;
	ULONG SecurityDescriptor;
	ULONG SecurityQualityOfService;
} OBJECT_ATTRIBUTES32, *POBJECT_ATTRIBUTES32;
typedef CONST OBJECT_ATTRIBUTES32 *PCOBJECT_ATTRIBUTES32;

typedef struct _OBJECT_ATTRIBUTES
{
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
	PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

//++
//
// VOID // InitializeObjectAttributes(
//     _Out_ POBJECT_ATTRIBUTES p,
//     _In_ PUNICODE_STRING n,
//     _In_ ULONG a,
//     _In_ HANDLE r,
//     _In_ PSECURITY_DESCRIPTOR s
//     )
//
//--
#define InitializeObjectAttributes( p, n, a, r, s ) { \
		(p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
		(p)->RootDirectory = r;                             \
		(p)->Attributes = a;                                \
		(p)->ObjectName = n;                                \
		(p)->SecurityDescriptor = s;                        \
		(p)->SecurityQualityOfService = NULL;               \
	}

// RTL_ to avoid collisions in the global namespace.
// I don't believe there are possible/likely constant RootDirectory
// or SecurityDescriptor values other than NULL, so they are hardcoded.
// As well, the string will generally be const, so we cast that away.
#define RTL_CONSTANT_OBJECT_ATTRIBUTES(n, a) \
	{ sizeof(OBJECT_ATTRIBUTES), NULL, RTL_CONST_CAST(PUNICODE_STRING)(n), a, NULL, NULL }

// This synonym is more appropriate for initializing what isn't actually const.
#define RTL_INIT_OBJECT_ATTRIBUTES(n, a) RTL_CONSTANT_OBJECT_ATTRIBUTES(n, a)


//
// Useful Helper Macros
//

//
// Determine if an argument is present by testing the value of the pointer
// to the argument value.
//

#define ARGUMENT_PRESENT(ArgumentPointer)    (\
        (CHAR *)((ULONG_PTR)(ArgumentPointer)) != (CHAR *)(NULL) )

//
// This works "generically" for Unicode and Ansi/Oem strings.
// Usage:
//   const static UNICODE_STRING FooU = RTL_CONSTANT_STRING(L"Foo");
//   const static         STRING Foo  = RTL_CONSTANT_STRING( "Foo");
// instead of the slower:
//   UNICODE_STRING FooU;
//           STRING Foo;
//   RtlInitUnicodeString(&FooU, L"Foo");
//          RtlInitString(&Foo ,  "Foo");
//
// Or:
//   const static char szFoo[] = "Foo";
//   const static STRING sFoo = RTL_CONSTANT_STRING(szFoo);
//
// This will compile without error or warning in C++. C will get a warning.
//
#ifdef __cplusplus
extern "C++"
{
	char _RTL_CONSTANT_STRING_type_check(const char *s);
	char _RTL_CONSTANT_STRING_type_check(const WCHAR *s);
	// __typeof would be desirable here instead of sizeof.
	template <size_t N> class _RTL_CONSTANT_STRING_remove_const_template_class;
	template <> class
		_RTL_CONSTANT_STRING_remove_const_template_class<sizeof(char)>
	{
	public:
		typedef  char T;
	};
	template <> class
		_RTL_CONSTANT_STRING_remove_const_template_class<sizeof(WCHAR)>
	{
	public:
		typedef WCHAR T;
	};
#define _RTL_CONSTANT_STRING_remove_const_macro(s) \
	(const_cast<_RTL_CONSTANT_STRING_remove_const_template_class<sizeof((s)[0])>::T*>(s))
}
#else
char _RTL_CONSTANT_STRING_type_check(const void *s);
#define _RTL_CONSTANT_STRING_remove_const_macro(s) (s)
#endif
#define RTL_CONSTANT_STRING(s) \
	{ \
	sizeof( s ) - sizeof( (s)[0] ), \
	sizeof( s ) / sizeof(_RTL_CONSTANT_STRING_type_check(s)), \
	_RTL_CONSTANT_STRING_remove_const_macro(s) \
	}

//
// Interrupt Request Level (IRQL)
//

typedef UCHAR KIRQL;
typedef KIRQL *PKIRQL;

//
// Product types
//

typedef enum _NT_PRODUCT_TYPE
{
	NtProductWinNt = 1,
	NtProductLanManNt,
	NtProductServer
} NT_PRODUCT_TYPE, *PNT_PRODUCT_TYPE;

//
// the bit mask, SharedUserData->SuiteMask, is a ULONG // so there can be a maximum of 32 entries
// in this enum.
//

typedef _Enum_is_bitflag_ enum _SUITE_TYPE
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

//
// Specific
//

typedef GUID *PGUID;
typedef LONG KPRIORITY;
typedef USHORT RTL_ATOM, *PRTL_ATOM;
typedef UCHAR KIRQL, *PKIRQL;
typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

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

#endif // _NTDEF_

//*****************************************************************************

// NTSTATUS值定义
//*****************************************************************************

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
#undef STATUS_SXS_EARLY_DEACTIVATION
#undef STATUS_SXS_INVALID_DEACTIVATION

#undef DBG_REPLY_LATER
#undef DBG_PRINTEXCEPTION_WIDE_C

#include <ntstatus.h> // NTSTATUS值定义

//*****************************************************************************

// 用户模式本机API调用及其数据结构定义
//*****************************************************************************

#ifndef KERNELMODE

#ifndef _NTNLS_H
#define _NTNLS_H

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

#endif

#ifndef _NTKEAPI_H
#define _NTKEAPI_H

#ifndef KERNELMODE
#define LOW_PRIORITY 0 // Lowest thread priority level
#define LOW_REALTIME_PRIORITY 16 // Lowest realtime priority level
#define HIGH_PRIORITY 31 // Highest thread priority level
#define MAXIMUM_PRIORITY 32 // Number of thread priority levels
#endif

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

#ifndef KERNELMODE

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

#endif

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtCallbackReturn(
	_In_reads_bytes_opt_(OutputLength) PVOID OutputBuffer,
	_In_ ULONG OutputLength,
	_In_ NTSTATUS Status
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCallbackReturn(
	_In_reads_bytes_opt_(OutputLength) PVOID OutputBuffer,
	_In_ ULONG OutputLength,
	_In_ NTSTATUS Status
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI VOID NTAPI NtFlushProcessWriteBuffers(
	VOID
);

NTSYSCALLAPI VOID NTAPI ZwFlushProcessWriteBuffers(
	VOID
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtQueryDebugFilterState(
	_In_ ULONG ComponentId,
	_In_ ULONG Level
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryDebugFilterState(
	_In_ ULONG ComponentId,
	_In_ ULONG Level
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetDebugFilterState(
	_In_ ULONG ComponentId,
	_In_ ULONG Level,
	_In_ BOOLEAN State
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetDebugFilterState(
	_In_ ULONG ComponentId,
	_In_ ULONG Level,
	_In_ BOOLEAN State
);

NTSYSCALLAPI NTSTATUS NTAPI NtYieldExecution(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwYieldExecution(
	VOID
);

#endif

#endif

#endif

#ifndef _NTLDR_H
#define _NTLDR_H

#ifndef KERNELMODE

// DLLs

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
	LoadReasonUnknown = -1
} LDR_DLL_LOAD_REASON, *PLDR_DLL_LOAD_REASON;

#define LDRP_PACKAGED_BINARY 0x00000001
#define LDRP_IMAGE_DLL 0x00000004
#define LDRP_LOAD_IN_PROGRESS 0x00001000
#define LDRP_ENTRY_PROCESSED 0x00004000
#define LDRP_DONT_CALL_FOR_THREADS 0x00040000
#define LDRP_PROCESS_ATTACH_CALLED 0x00080000
#define LDRP_PROCESS_ATTACH_FAILED 0x00100000
#define LDRP_IMAGE_NOT_AT_BASE 0x00200000 // Vista and below
#define LDRP_COR_IMAGE 0x00400000
#define LDRP_DONT_RELOCATE 0x00800000
#define LDRP_REDIRECTED 0x10000000
#define LDRP_COMPAT_DATABASE_PROCESSED 0x80000000

// Use the size of the structure as it was in Windows XP.
#define LDR_DATA_TABLE_ENTRY_SIZE_WINXP FIELD_OFFSET(LDR_DATA_TABLE_ENTRY, DdagNode)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN7 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY, BaseNameHashValue)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN8 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY, ImplicitPathOptions)

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
	PVOID EntryPoint;
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
			ULONG ReservedFlags5 : 3;
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
	PVOID Lock;
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
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef BOOLEAN(NTAPI *PDLL_INIT_ROUTINE)(
	_In_ PVOID DllHandle,
	_In_ ULONG Reason,
	_In_opt_ PCONTEXT Context
	);

NTSYSAPI NTSTATUS NTAPI LdrLoadDll(
	_In_opt_ PWSTR DllPath,
	_In_opt_ PULONG DllCharacteristics,
	_In_ PUNICODE_STRING DllName,
	_Out_ PVOID *DllHandle
);

NTSYSAPI NTSTATUS NTAPI LdrUnloadDll(
	_In_ PVOID DllHandle
);

NTSYSAPI NTSTATUS NTAPI LdrGetDllHandle(
	_In_opt_ PWSTR DllPath,
	_In_opt_ PULONG DllCharacteristics,
	_In_ PUNICODE_STRING DllName,
	_Out_ PVOID *DllHandle
);

#define LDR_GET_DLL_HANDLE_EX_UNCHANGED_REFCOUNT 0x00000001
#define LDR_GET_DLL_HANDLE_EX_PIN 0x00000002

NTSYSAPI NTSTATUS NTAPI LdrGetDllHandleEx(
	_In_ ULONG Flags,
	_In_opt_ PCWSTR DllPath,
	_In_opt_ PULONG DllCharacteristics,
	_In_ PUNICODE_STRING DllName,
	_Out_opt_ PVOID *DllHandle
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI LdrGetDllHandleByMapping(
	_In_ PVOID Base,
	_Out_ PVOID *DllHandle
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI LdrGetDllHandleByName(
	_In_opt_ PUNICODE_STRING BaseDllName,
	_In_opt_ PUNICODE_STRING FullDllName,
	_Out_ PVOID *DllHandle
);
#endif

#define LDR_ADDREF_DLL_PIN 0x00000001

NTSYSAPI NTSTATUS NTAPI LdrAddRefDll(
	_In_ ULONG Flags,
	_In_ PVOID DllHandle
);

NTSYSAPI NTSTATUS NTAPI LdrGetProcedureAddress(
	_In_ PVOID DllHandle,
	_In_opt_ PANSI_STRING ProcedureName,
	_In_opt_ ULONG ProcedureNumber,
	_Out_ PVOID *ProcedureAddress
);

// rev
#define LDR_GET_PROCEDURE_ADDRESS_DONT_RECORD_FORWARDER 0x00000001

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI LdrGetProcedureAddressEx(
	_In_ PVOID DllHandle,
	_In_opt_ PANSI_STRING ProcedureName,
	_In_opt_ ULONG ProcedureNumber,
	_Out_ PVOID *ProcedureAddress,
	_In_ ULONG Flags
);
#endif

#define LDR_LOCK_LOADER_LOCK_FLAG_RAISE_ON_ERRORS 0x00000001
#define LDR_LOCK_LOADER_LOCK_FLAG_TRY_ONLY 0x00000002

#define LDR_LOCK_LOADER_LOCK_DISPOSITION_INVALID 0
#define LDR_LOCK_LOADER_LOCK_DISPOSITION_LOCK_ACQUIRED 1
#define LDR_LOCK_LOADER_LOCK_DISPOSITION_LOCK_NOT_ACQUIRED 2

NTSYSAPI NTSTATUS NTAPI LdrLockLoaderLock(
	_In_ ULONG Flags,
	_Out_opt_ ULONG *Disposition,
	_Out_ PVOID *Cookie
);

#define LDR_UNLOCK_LOADER_LOCK_FLAG_RAISE_ON_ERRORS 0x00000001

NTSYSAPI NTSTATUS NTAPI LdrUnlockLoaderLock(
	_In_ ULONG Flags,
	_Inout_ PVOID Cookie
);

NTSYSAPI NTSTATUS NTAPI LdrRelocateImage(
	_In_ PVOID NewBase,
	_In_ PSTR LoaderName,
	_In_ NTSTATUS Success,
	_In_ NTSTATUS Conflict,
	_In_ NTSTATUS Invalid
);

NTSYSAPI NTSTATUS NTAPI LdrRelocateImageWithBias(
	_In_ PVOID NewBase,
	_In_ LONGLONG Bias,
	_In_ PSTR LoaderName,
	_In_ NTSTATUS Success,
	_In_ NTSTATUS Conflict,
	_In_ NTSTATUS Invalid
);

NTSYSAPI PIMAGE_BASE_RELOCATION NTAPI LdrProcessRelocationBlock(
	_In_ ULONG_PTR VA,
	_In_ ULONG SizeOfBlock,
	_In_ PUSHORT NextOffset,
	_In_ LONG_PTR Diff
);

NTSYSAPI BOOLEAN NTAPI LdrVerifyMappedImageMatchesChecksum(
	_In_ PVOID BaseAddress,
	_In_ SIZE_T NumberOfBytes,
	_In_ ULONG FileLength
);

typedef VOID(NTAPI *PLDR_IMPORT_MODULE_CALLBACK)(
	_In_ PVOID Parameter,
	_In_ PSTR ModuleName
	);

NTSYSAPI NTSTATUS NTAPI LdrVerifyImageMatchesChecksum(
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
NTSYSAPI NTSTATUS NTAPI LdrVerifyImageMatchesChecksumEx(
	_In_ HANDLE ImageFileHandle,
	_Inout_ PLDR_VERIFY_IMAGE_INFO VerifyInfo
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI LdrQueryModuleServiceTags(
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

typedef VOID(NTAPI *PLDR_DLL_NOTIFICATION_FUNCTION)(
	_In_ ULONG NotificationReason,
	_In_ PLDR_DLL_NOTIFICATION_DATA NotificationData,
	_In_opt_ PVOID Context
	);

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI NTSTATUS NTAPI LdrRegisterDllNotification(
	_In_ ULONG Flags,
	_In_ PLDR_DLL_NOTIFICATION_FUNCTION NotificationFunction,
	_In_ PVOID Context,
	_Out_ PVOID *Cookie
);

NTSYSAPI NTSTATUS NTAPI LdrUnregisterDllNotification(
	_In_ PVOID Cookie
);

#endif

// end_msdn

// Load as data table

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI NTSTATUS NTAPI LdrAddLoadAsDataTable(
	_In_ PVOID Module,
	_In_ PWSTR FilePath,
	_In_ SIZE_T Size,
	_In_ HANDLE Handle
);

// private
NTSYSAPI NTSTATUS NTAPI LdrRemoveLoadAsDataTable(
	_In_ PVOID InitModule,
	_Out_opt_ PVOID *BaseModule,
	_Out_opt_ PSIZE_T Size,
	_In_ ULONG Flags
);

// private
NTSYSAPI NTSTATUS NTAPI LdrGetFileNameFromLoadAsDataTable(
	_In_ PVOID Module,
	_Out_ PVOID *pFileNamePrt
);

#endif

#endif // (!KERNELMODE)

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

#endif

#ifndef _NTEXAPI_H
#define _NTEXAPI_H

#ifndef KERNELMODE

// Thread execution

NTSYSCALLAPI NTSTATUS NTAPI NtDelayExecution(
	_In_ BOOLEAN Alertable,
	_In_ PLARGE_INTEGER DelayInterval
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDelayExecution(
	_In_ BOOLEAN Alertable,
	_In_ PLARGE_INTEGER DelayInterval
);

// Environment values

NTSYSCALLAPI NTSTATUS NTAPI NtQuerySystemEnvironmentValue(
	_In_ PUNICODE_STRING VariableName,
	_Out_writes_bytes_(ValueLength) PWSTR VariableValue,
	_In_ USHORT ValueLength,
	_Out_opt_ PUSHORT ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySystemEnvironmentValue(
	_In_ PUNICODE_STRING VariableName,
	_Out_writes_bytes_(ValueLength) PWSTR VariableValue,
	_In_ USHORT ValueLength,
	_Out_opt_ PUSHORT ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetSystemEnvironmentValue(
	_In_ PUNICODE_STRING VariableName,
	_In_ PUNICODE_STRING VariableValue
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetSystemEnvironmentValue(
	_In_ PUNICODE_STRING VariableName,
	_In_ PUNICODE_STRING VariableValue
);

NTSYSCALLAPI NTSTATUS NTAPI NtQuerySystemEnvironmentValueEx(
	_In_ PUNICODE_STRING VariableName,
	_In_ LPGUID VendorGuid,
	_Out_writes_bytes_opt_(*ValueLength) PVOID Value,
	_Inout_ PULONG ValueLength,
	_Out_opt_ PULONG Attributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySystemEnvironmentValueEx(
	_In_ PUNICODE_STRING VariableName,
	_In_ LPGUID VendorGuid,
	_Out_writes_bytes_opt_(*ValueLength) PVOID Value,
	_Inout_ PULONG ValueLength,
	_Out_opt_ PULONG Attributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetSystemEnvironmentValueEx(
	_In_ PUNICODE_STRING VariableName,
	_In_ LPGUID VendorGuid,
	_In_reads_bytes_opt_(ValueLength) PVOID Value,
	_In_ ULONG ValueLength,
	_In_ ULONG Attributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetSystemEnvironmentValueEx(
	_In_ PUNICODE_STRING VariableName,
	_In_ LPGUID VendorGuid,
	_In_reads_bytes_opt_(ValueLength) PVOID Value,
	_In_ ULONG ValueLength,
	_In_ ULONG Attributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtEnumerateSystemEnvironmentValuesEx(
	_In_ ULONG InformationClass,
	_Out_ PVOID Buffer,
	_Inout_ PULONG BufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwEnumerateSystemEnvironmentValuesEx(
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

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSCALLAPI NTSTATUS NTAPI NtAddBootEntry(
	_In_ PBOOT_ENTRY BootEntry,
	_Out_opt_ PULONG Id
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAddBootEntry(
	_In_ PBOOT_ENTRY BootEntry,
	_Out_opt_ PULONG Id
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteBootEntry(
	_In_ ULONG Id
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteBootEntry(
	_In_ ULONG Id
);

NTSYSCALLAPI NTSTATUS NTAPI NtModifyBootEntry(
	_In_ PBOOT_ENTRY BootEntry
);

NTSYSCALLAPI NTSTATUS NTAPI ZwModifyBootEntry(
	_In_ PBOOT_ENTRY BootEntry
);

NTSYSCALLAPI NTSTATUS NTAPI NtEnumerateBootEntries(
	_Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
	_Inout_ PULONG BufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwEnumerateBootEntries(
	_Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
	_Inout_ PULONG BufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryBootEntryOrder(
	_Out_writes_opt_(*Count) PULONG Ids,
	_Inout_ PULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryBootEntryOrder(
	_Out_writes_opt_(*Count) PULONG Ids,
	_Inout_ PULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetBootEntryOrder(
	_In_reads_(Count) PULONG Ids,
	_In_ ULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetBootEntryOrder(
	_In_reads_(Count) PULONG Ids,
	_In_ ULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryBootOptions(
	_Out_writes_bytes_opt_(*BootOptionsLength) PBOOT_OPTIONS BootOptions,
	_Inout_ PULONG BootOptionsLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryBootOptions(
	_Out_writes_bytes_opt_(*BootOptionsLength) PBOOT_OPTIONS BootOptions,
	_Inout_ PULONG BootOptionsLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetBootOptions(
	_In_ PBOOT_OPTIONS BootOptions,
	_In_ ULONG FieldsToChange
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetBootOptions(
	_In_ PBOOT_OPTIONS BootOptions,
	_In_ ULONG FieldsToChange
);

NTSYSCALLAPI NTSTATUS NTAPI NtTranslateFilePath(
	_In_ PFILE_PATH InputFilePath,
	_In_ ULONG OutputType,
	_Out_writes_bytes_opt_(*OutputFilePathLength) PFILE_PATH OutputFilePath,
	_Inout_opt_ PULONG OutputFilePathLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwTranslateFilePath(
	_In_ PFILE_PATH InputFilePath,
	_In_ ULONG OutputType,
	_Out_writes_bytes_opt_(*OutputFilePathLength) PFILE_PATH OutputFilePath,
	_Inout_opt_ PULONG OutputFilePathLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtAddDriverEntry(
	_In_ PEFI_DRIVER_ENTRY DriverEntry,
	_Out_opt_ PULONG Id
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAddDriverEntry(
	_In_ PEFI_DRIVER_ENTRY DriverEntry,
	_Out_opt_ PULONG Id
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteDriverEntry(
	_In_ ULONG Id
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteDriverEntry(
	_In_ ULONG Id
);

NTSYSCALLAPI NTSTATUS NTAPI NtModifyDriverEntry(
	_In_ PEFI_DRIVER_ENTRY DriverEntry
);

NTSYSCALLAPI NTSTATUS NTAPI ZwModifyDriverEntry(
	_In_ PEFI_DRIVER_ENTRY DriverEntry
);

NTSYSCALLAPI NTSTATUS NTAPI NtEnumerateDriverEntries(
	_Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
	_Inout_ PULONG BufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwEnumerateDriverEntries(
	_Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
	_Inout_ PULONG BufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryDriverEntryOrder(
	_Out_writes_opt_(*Count) PULONG Ids,
	_Inout_ PULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryDriverEntryOrder(
	_Out_writes_opt_(*Count) PULONG Ids,
	_Inout_ PULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetDriverEntryOrder(
	_In_reads_(Count) PULONG Ids,
	_In_ ULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetDriverEntryOrder(
	_In_reads_(Count) PULONG Ids,
	_In_ ULONG Count
);

#endif

// Event

#ifndef EVENT_QUERY_STATE
#define EVENT_QUERY_STATE 0x0001
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateEvent(
	_Out_ PHANDLE EventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ EVENT_TYPE EventType,
	_In_ BOOLEAN InitialState
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateEvent(
	_Out_ PHANDLE EventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ EVENT_TYPE EventType,
	_In_ BOOLEAN InitialState
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenEvent(
	_Out_ PHANDLE EventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenEvent(
	_Out_ PHANDLE EventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetEvent(
	_In_ HANDLE EventHandle,
	_Out_opt_ PLONG PreviousState
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetEvent(
	_In_ HANDLE EventHandle,
	_Out_opt_ PLONG PreviousState
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetEventBoostPriority(
	_In_ HANDLE EventHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetEventBoostPriority(
	_In_ HANDLE EventHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtClearEvent(
	_In_ HANDLE EventHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwClearEvent(
	_In_ HANDLE EventHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtResetEvent(
	_In_ HANDLE EventHandle,
	_Out_opt_ PLONG PreviousState
);

NTSYSCALLAPI NTSTATUS NTAPI ZwResetEvent(
	_In_ HANDLE EventHandle,
	_Out_opt_ PLONG PreviousState
);

NTSYSCALLAPI NTSTATUS NTAPI NtPulseEvent(
	_In_ HANDLE EventHandle,
	_Out_opt_ PLONG PreviousState
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPulseEvent(
	_In_ HANDLE EventHandle,
	_Out_opt_ PLONG PreviousState
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryEvent(
	_In_ HANDLE EventHandle,
	_In_ EVENT_INFORMATION_CLASS EventInformationClass,
	_Out_writes_bytes_(EventInformationLength) PVOID EventInformation,
	_In_ ULONG EventInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryEvent(
	_In_ HANDLE EventHandle,
	_In_ EVENT_INFORMATION_CLASS EventInformationClass,
	_Out_writes_bytes_(EventInformationLength) PVOID EventInformation,
	_In_ ULONG EventInformationLength,
	_Out_opt_ PULONG ReturnLength
);

// Event Pair

#define EVENT_PAIR_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE)

NTSYSCALLAPI NTSTATUS NTAPI NtCreateEventPair(
	_Out_ PHANDLE EventPairHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateEventPair(
	_Out_ PHANDLE EventPairHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenEventPair(
	_Out_ PHANDLE EventPairHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenEventPair(
	_Out_ PHANDLE EventPairHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetLowEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetLowEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetHighEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetHighEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtWaitLowEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWaitLowEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtWaitHighEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWaitHighEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetLowWaitHighEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetLowWaitHighEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetHighWaitLowEventPair(
	_In_ HANDLE EventPairHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetHighWaitLowEventPair(
	_In_ HANDLE EventPairHandle
);

// Mutant

typedef enum _MUTANT_INFORMATION_CLASS
{
	MutantBasicInformation,
	MutantOwnerInformation
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateMutant(
	_Out_ PHANDLE MutantHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ BOOLEAN InitialOwner
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateMutant(
	_Out_ PHANDLE MutantHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ BOOLEAN InitialOwner
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenMutant(
	_Out_ PHANDLE MutantHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenMutant(
	_Out_ PHANDLE MutantHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtReleaseMutant(
	_In_ HANDLE MutantHandle,
	_Out_opt_ PLONG PreviousCount
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReleaseMutant(
	_In_ HANDLE MutantHandle,
	_Out_opt_ PLONG PreviousCount
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryMutant(
	_In_ HANDLE MutantHandle,
	_In_ MUTANT_INFORMATION_CLASS MutantInformationClass,
	_Out_writes_bytes_(MutantInformationLength) PVOID MutantInformation,
	_In_ ULONG MutantInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryMutant(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateSemaphore(
	_Out_ PHANDLE SemaphoreHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ LONG InitialCount,
	_In_ LONG MaximumCount
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateSemaphore(
	_Out_ PHANDLE SemaphoreHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ LONG InitialCount,
	_In_ LONG MaximumCount
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenSemaphore(
	_Out_ PHANDLE SemaphoreHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenSemaphore(
	_Out_ PHANDLE SemaphoreHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtReleaseSemaphore(
	_In_ HANDLE SemaphoreHandle,
	_In_ LONG ReleaseCount,
	_Out_opt_ PLONG PreviousCount
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReleaseSemaphore(
	_In_ HANDLE SemaphoreHandle,
	_In_ LONG ReleaseCount,
	_Out_opt_ PLONG PreviousCount
);

NTSYSCALLAPI NTSTATUS NTAPI NtQuerySemaphore(
	_In_ HANDLE SemaphoreHandle,
	_In_ SEMAPHORE_INFORMATION_CLASS SemaphoreInformationClass,
	_Out_writes_bytes_(SemaphoreInformationLength) PVOID SemaphoreInformation,
	_In_ ULONG SemaphoreInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySemaphore(
	_In_ HANDLE SemaphoreHandle,
	_In_ SEMAPHORE_INFORMATION_CLASS SemaphoreInformationClass,
	_Out_writes_bytes_(SemaphoreInformationLength) PVOID SemaphoreInformation,
	_In_ ULONG SemaphoreInformationLength,
	_Out_opt_ PULONG ReturnLength
);

// Timer

typedef enum _TIMER_INFORMATION_CLASS
{
	TimerBasicInformation
} TIMER_INFORMATION_CLASS;

typedef struct _TIMER_BASIC_INFORMATION
{
	LARGE_INTEGER RemainingTime;
	BOOLEAN TimerState;
} TIMER_BASIC_INFORMATION, *PTIMER_BASIC_INFORMATION;

typedef VOID(NTAPI *PTIMER_APC_ROUTINE)(
	_In_ PVOID TimerContext,
	_In_ ULONG TimerLowValue,
	_In_ LONG TimerHighValue
	);

typedef enum _TIMER_SET_INFORMATION_CLASS
{
	TimerSetCoalescableTimer,
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateTimer(
	_Out_ PHANDLE TimerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ TIMER_TYPE TimerType
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateTimer(
	_Out_ PHANDLE TimerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ TIMER_TYPE TimerType
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenTimer(
	_Out_ PHANDLE TimerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenTimer(
	_Out_ PHANDLE TimerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetTimer(
	_In_ HANDLE TimerHandle,
	_In_ PLARGE_INTEGER DueTime,
	_In_opt_ PTIMER_APC_ROUTINE TimerApcRoutine,
	_In_opt_ PVOID TimerContext,
	_In_ BOOLEAN ResumeTimer,
	_In_opt_ LONG Period,
	_Out_opt_ PBOOLEAN PreviousState
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetTimer(
	_In_ HANDLE TimerHandle,
	_In_ PLARGE_INTEGER DueTime,
	_In_opt_ PTIMER_APC_ROUTINE TimerApcRoutine,
	_In_opt_ PVOID TimerContext,
	_In_ BOOLEAN ResumeTimer,
	_In_opt_ LONG Period,
	_Out_opt_ PBOOLEAN PreviousState
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtSetTimerEx(
	_In_ HANDLE TimerHandle,
	_In_ TIMER_SET_INFORMATION_CLASS TimerSetInformationClass,
	_Inout_updates_bytes_opt_(TimerSetInformationLength) PVOID TimerSetInformation,
	_In_ ULONG TimerSetInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetTimerEx(
	_In_ HANDLE TimerHandle,
	_In_ TIMER_SET_INFORMATION_CLASS TimerSetInformationClass,
	_Inout_updates_bytes_opt_(TimerSetInformationLength) PVOID TimerSetInformation,
	_In_ ULONG TimerSetInformationLength
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtCancelTimer(
	_In_ HANDLE TimerHandle,
	_Out_opt_ PBOOLEAN CurrentState
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCancelTimer(
	_In_ HANDLE TimerHandle,
	_Out_opt_ PBOOLEAN CurrentState
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryTimer(
	_In_ HANDLE TimerHandle,
	_In_ TIMER_INFORMATION_CLASS TimerInformationClass,
	_Out_writes_bytes_(TimerInformationLength) PVOID TimerInformation,
	_In_ ULONG TimerInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryTimer(
	_In_ HANDLE TimerHandle,
	_In_ TIMER_INFORMATION_CLASS TimerInformationClass,
	_Out_writes_bytes_(TimerInformationLength) PVOID TimerInformation,
	_In_ ULONG TimerInformationLength,
	_Out_opt_ PULONG ReturnLength
);

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSCALLAPI NTSTATUS NTAPI NtCreateIRTimer(
	_Out_ PHANDLE TimerHandle,
	_In_ ACCESS_MASK DesiredAccess
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateIRTimer(
	_Out_ PHANDLE TimerHandle,
	_In_ ACCESS_MASK DesiredAccess
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetIRTimer(
	_In_ HANDLE TimerHandle,
	_In_opt_ PLARGE_INTEGER DueTime
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetIRTimer(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateTimer2(
	_Out_ PHANDLE TimerHandle,
	_In_opt_ PVOID Reserved1,
	_In_opt_ PVOID Reserved2,
	_In_ ULONG Attributes,
	_In_ ACCESS_MASK DesiredAccess
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateTimer2(
	_Out_ PHANDLE TimerHandle,
	_In_opt_ PVOID Reserved1,
	_In_opt_ PVOID Reserved2,
	_In_ ULONG Attributes,
	_In_ ACCESS_MASK DesiredAccess
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetTimer2(
	_In_ HANDLE TimerHandle,
	_In_ PLARGE_INTEGER DueTime,
	_In_opt_ PLARGE_INTEGER Period,
	_In_ PT2_SET_PARAMETERS Parameters
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetTimer2(
	_In_ HANDLE TimerHandle,
	_In_ PLARGE_INTEGER DueTime,
	_In_opt_ PLARGE_INTEGER Period,
	_In_ PT2_SET_PARAMETERS Parameters
);

NTSYSCALLAPI NTSTATUS NTAPI NtCancelTimer2(
	_In_ HANDLE TimerHandle,
	_In_ PT2_CANCEL_PARAMETERS Parameters
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCancelTimer2(
	_In_ HANDLE TimerHandle,
	_In_ PT2_CANCEL_PARAMETERS Parameters
);

#endif

// Profile

#define PROFILE_CONTROL 0x0001
#define PROFILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | PROFILE_CONTROL)

NTSYSCALLAPI NTSTATUS NTAPI NtCreateProfile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateProfile(
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
NTSYSCALLAPI NTSTATUS NTAPI NtCreateProfileEx(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateProfileEx(
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

NTSYSCALLAPI NTSTATUS NTAPI NtStartProfile(
	_In_ HANDLE ProfileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwStartProfile(
	_In_ HANDLE ProfileHandle
);


NTSYSCALLAPI NTSTATUS NTAPI NtStopProfile(
	_In_ HANDLE ProfileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwStopProfile(
	_In_ HANDLE ProfileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryIntervalProfile(
	_In_ KPROFILE_SOURCE ProfileSource,
	_Out_ PULONG Interval
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryIntervalProfile(
	_In_ KPROFILE_SOURCE ProfileSource,
	_Out_ PULONG Interval
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetIntervalProfile(
	_In_ ULONG Interval,
	_In_ KPROFILE_SOURCE Source
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetIntervalProfile(
	_In_ ULONG Interval,
	_In_ KPROFILE_SOURCE Source
);

// Keyed Event

#define KEYEDEVENT_WAIT 0x0001
#define KEYEDEVENT_WAKE 0x0002
#define KEYEDEVENT_ALL_ACCESS \
    (STANDARD_RIGHTS_REQUIRED | KEYEDEVENT_WAIT | KEYEDEVENT_WAKE)

NTSYSCALLAPI NTSTATUS NTAPI NtCreateKeyedEvent(
	_Out_ PHANDLE KeyedEventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateKeyedEvent(
	_Out_ PHANDLE KeyedEventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenKeyedEvent(
	_Out_ PHANDLE KeyedEventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenKeyedEvent(
	_Out_ PHANDLE KeyedEventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtReleaseKeyedEvent(
	_In_ HANDLE KeyedEventHandle,
	_In_ PVOID KeyValue,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReleaseKeyedEvent(
	_In_ HANDLE KeyedEventHandle,
	_In_ PVOID KeyValue,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI NtWaitForKeyedEvent(
	_In_ HANDLE KeyedEventHandle,
	_In_ PVOID KeyValue,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWaitForKeyedEvent(
	_In_ HANDLE KeyedEventHandle,
	_In_ PVOID KeyValue,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

// UMS

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtUmsThreadYield(
	_In_ PVOID SchedulerParam
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUmsThreadYield(
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
	WnfDataScopeProcess
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateWnfStateName(
	_Out_ PWNF_STATE_NAME StateName,
	_In_ WNF_STATE_NAME_LIFETIME NameLifetime,
	_In_ WNF_DATA_SCOPE DataScope,
	_In_ BOOLEAN PersistData,
	_In_opt_ PCWNF_TYPE_ID TypeId,
	_In_ ULONG MaximumStateSize,
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateWnfStateName(
	_Out_ PWNF_STATE_NAME StateName,
	_In_ WNF_STATE_NAME_LIFETIME NameLifetime,
	_In_ WNF_DATA_SCOPE DataScope,
	_In_ BOOLEAN PersistData,
	_In_opt_ PCWNF_TYPE_ID TypeId,
	_In_ ULONG MaximumStateSize,
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteWnfStateName(
	_In_ PCWNF_STATE_NAME StateName
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteWnfStateName(
	_In_ PCWNF_STATE_NAME StateName
);

NTSYSCALLAPI NTSTATUS NTAPI NtUpdateWnfStateData(
	_In_ PCWNF_STATE_NAME StateName,
	_In_reads_bytes_opt_(Length) const VOID *Buffer,
	_In_opt_ ULONG Length,
	_In_opt_ PCWNF_TYPE_ID TypeId,
	_In_opt_ const VOID *ExplicitScope,
	_In_ WNF_CHANGE_STAMP MatchingChangeStamp,
	_In_ LOGICAL CheckStamp
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUpdateWnfStateData(
	_In_ PCWNF_STATE_NAME StateName,
	_In_reads_bytes_opt_(Length) const VOID *Buffer,
	_In_opt_ ULONG Length,
	_In_opt_ PCWNF_TYPE_ID TypeId,
	_In_opt_ const VOID *ExplicitScope,
	_In_ WNF_CHANGE_STAMP MatchingChangeStamp,
	_In_ LOGICAL CheckStamp
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteWnfStateData(
	_In_ PCWNF_STATE_NAME StateName,
	_In_opt_ const VOID *ExplicitScope
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteWnfStateData(
	_In_ PCWNF_STATE_NAME StateName,
	_In_opt_ const VOID *ExplicitScope
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryWnfStateData(
	_In_ PCWNF_STATE_NAME StateName,
	_In_opt_ PCWNF_TYPE_ID TypeId,
	_In_opt_ const VOID *ExplicitScope,
	_Out_ PWNF_CHANGE_STAMP ChangeStamp,
	_Out_writes_bytes_to_opt_(*BufferSize, *BufferSize) PVOID Buffer,
	_Inout_ PULONG BufferSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryWnfStateData(
	_In_ PCWNF_STATE_NAME StateName,
	_In_opt_ PCWNF_TYPE_ID TypeId,
	_In_opt_ const VOID *ExplicitScope,
	_Out_ PWNF_CHANGE_STAMP ChangeStamp,
	_Out_writes_bytes_to_opt_(*BufferSize, *BufferSize) PVOID Buffer,
	_Inout_ PULONG BufferSize
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryWnfStateNameInformation(
	_In_ PCWNF_STATE_NAME StateName,
	_In_ WNF_STATE_NAME_INFORMATION NameInfoClass,
	_In_opt_ const VOID *ExplicitScope,
	_Out_writes_bytes_(InfoBufferSize) PVOID InfoBuffer,
	_In_ ULONG InfoBufferSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryWnfStateNameInformation(
	_In_ PCWNF_STATE_NAME StateName,
	_In_ WNF_STATE_NAME_INFORMATION NameInfoClass,
	_In_opt_ const VOID *ExplicitScope,
	_Out_writes_bytes_(InfoBufferSize) PVOID InfoBuffer,
	_In_ ULONG InfoBufferSize
);

NTSYSCALLAPI NTSTATUS NTAPI NtSubscribeWnfStateChange(
	_In_ PCWNF_STATE_NAME StateName,
	_In_opt_ WNF_CHANGE_STAMP ChangeStamp,
	_In_ ULONG EventMask,
	_Out_opt_ PULONG64 SubscriptionId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSubscribeWnfStateChange(
	_In_ PCWNF_STATE_NAME StateName,
	_In_opt_ WNF_CHANGE_STAMP ChangeStamp,
	_In_ ULONG EventMask,
	_Out_opt_ PULONG64 SubscriptionId
);

NTSYSCALLAPI NTSTATUS NTAPI NtUnsubscribeWnfStateChange(
	_In_ PCWNF_STATE_NAME StateName
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnsubscribeWnfStateChange(
	_In_ PCWNF_STATE_NAME StateName
);

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI NTSTATUS NTAPI NtGetCompleteWnfStateSubscription(
	_In_opt_ PWNF_STATE_NAME OldDescriptorStateName,
	_In_opt_ ULONG64 *OldSubscriptionId,
	_In_opt_ ULONG OldDescriptorEventMask,
	_In_opt_ ULONG OldDescriptorStatus,
	_Out_writes_bytes_(DescriptorSize) PWNF_DELIVERY_DESCRIPTOR NewDeliveryDescriptor,
	_In_ ULONG DescriptorSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetCompleteWnfStateSubscription(
	_In_opt_ PWNF_STATE_NAME OldDescriptorStateName,
	_In_opt_ ULONG64 *OldSubscriptionId,
	_In_opt_ ULONG OldDescriptorEventMask,
	_In_opt_ ULONG OldDescriptorStatus,
	_Out_writes_bytes_(DescriptorSize) PWNF_DELIVERY_DESCRIPTOR NewDeliveryDescriptor,
	_In_ ULONG DescriptorSize
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetWnfProcessNotificationEvent(
	_In_ HANDLE NotificationEvent
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetWnfProcessNotificationEvent(
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
	WorkerFactoryTimeout,
	WorkerFactoryRetryTimeout,
	WorkerFactoryIdleTimeout,
	WorkerFactoryBindingCount,
	WorkerFactoryThreadMinimum,
	WorkerFactoryThreadMaximum,
	WorkerFactoryPaused,
	WorkerFactoryBasicInformation,
	WorkerFactoryAdjustThreadGoal,
	WorkerFactoryCallbackType,
	WorkerFactoryStackInformation, // 10
	WorkerFactoryThreadBasePriority,
	WorkerFactoryTimeoutWaiters, // since THRESHOLD
	WorkerFactoryFlags,
	WorkerFactoryThreadSoftMaximum,
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateWorkerFactory(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateWorkerFactory(
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

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationWorkerFactory(
	_In_ HANDLE WorkerFactoryHandle,
	_In_ WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
	_Out_writes_bytes_(WorkerFactoryInformationLength) PVOID WorkerFactoryInformation,
	_In_ ULONG WorkerFactoryInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationWorkerFactory(
	_In_ HANDLE WorkerFactoryHandle,
	_In_ WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
	_Out_writes_bytes_(WorkerFactoryInformationLength) PVOID WorkerFactoryInformation,
	_In_ ULONG WorkerFactoryInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationWorkerFactory(
	_In_ HANDLE WorkerFactoryHandle,
	_In_ WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
	_In_reads_bytes_(WorkerFactoryInformationLength) PVOID WorkerFactoryInformation,
	_In_ ULONG WorkerFactoryInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationWorkerFactory(
	_In_ HANDLE WorkerFactoryHandle,
	_In_ WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
	_In_reads_bytes_(WorkerFactoryInformationLength) PVOID WorkerFactoryInformation,
	_In_ ULONG WorkerFactoryInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtShutdownWorkerFactory(
	_In_ HANDLE WorkerFactoryHandle,
	_Inout_ volatile LONG *PendingWorkerCount
);

NTSYSCALLAPI NTSTATUS NTAPI ZwShutdownWorkerFactory(
	_In_ HANDLE WorkerFactoryHandle,
	_Inout_ volatile LONG *PendingWorkerCount
);

NTSYSCALLAPI NTSTATUS NTAPI NtReleaseWorkerFactoryWorker(
	_In_ HANDLE WorkerFactoryHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReleaseWorkerFactoryWorker(
	_In_ HANDLE WorkerFactoryHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtWorkerFactoryWorkerReady(
	_In_ HANDLE WorkerFactoryHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWorkerFactoryWorkerReady(
	_In_ HANDLE WorkerFactoryHandle
);

struct _FILE_IO_COMPLETION_INFORMATION;

NTSYSCALLAPI NTSTATUS NTAPI NtWaitForWorkViaWorkerFactory(
	_In_ HANDLE WorkerFactoryHandle,
	_Out_ struct _FILE_IO_COMPLETION_INFORMATION *MiniPacket
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWaitForWorkViaWorkerFactory(
	_In_ HANDLE WorkerFactoryHandle,
	_Out_ struct _FILE_IO_COMPLETION_INFORMATION *MiniPacket
);

#endif

// Time

NTSYSCALLAPI NTSTATUS NTAPI NtQuerySystemTime(
	_Out_ PLARGE_INTEGER SystemTime
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySystemTime(
	_Out_ PLARGE_INTEGER SystemTime
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetSystemTime(
	_In_opt_ PLARGE_INTEGER SystemTime,
	_Out_opt_ PLARGE_INTEGER PreviousTime
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetSystemTime(
	_In_opt_ PLARGE_INTEGER SystemTime,
	_Out_opt_ PLARGE_INTEGER PreviousTime
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryTimerResolution(
	_Out_ PULONG MaximumTime,
	_Out_ PULONG MinimumTime,
	_Out_ PULONG CurrentTime
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryTimerResolution(
	_Out_ PULONG MaximumTime,
	_Out_ PULONG MinimumTime,
	_Out_ PULONG CurrentTime
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetTimerResolution(
	_In_ ULONG DesiredTime,
	_In_ BOOLEAN SetResolution,
	_Out_ PULONG ActualTime
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetTimerResolution(
	_In_ ULONG DesiredTime,
	_In_ BOOLEAN SetResolution,
	_Out_ PULONG ActualTime
);

// Performance Counter

NTSYSCALLAPI NTSTATUS NTAPI NtQueryPerformanceCounter(
	_Out_ PLARGE_INTEGER PerformanceCounter,
	_Out_opt_ PLARGE_INTEGER PerformanceFrequency
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryPerformanceCounter(
	_Out_ PLARGE_INTEGER PerformanceCounter,
	_Out_opt_ PLARGE_INTEGER PerformanceFrequency
);

// LUIDs

NTSYSCALLAPI NTSTATUS NTAPI NtAllocateLocallyUniqueId(
	_Out_ PLUID Luid
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAllocateLocallyUniqueId(
	_Out_ PLUID Luid
);

// UUIDs

NTSYSCALLAPI NTSTATUS NTAPI NtSetUuidSeed(
	_In_ PCHAR Seed
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetUuidSeed(
	_In_ PCHAR Seed
);

NTSYSCALLAPI NTSTATUS NTAPI NtAllocateUuids(
	_Out_ PULARGE_INTEGER Time,
	_Out_ PULONG Range,
	_Out_ PULONG Sequence,
	_Out_ PCHAR Seed
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAllocateUuids(
	_Out_ PULARGE_INTEGER Time,
	_Out_ PULONG Range,
	_Out_ PULONG Sequence,
	_Out_ PCHAR Seed
);

// System Information

#endif // (!KERNELMODE)

// rev
// private
// source:http://www.microsoft.com/whdc/system/Sysinternals/MoreThan64proc.mspx
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
	SystemLocksInformation, // q: SYSTEM_LOCK_INFORMATION
	SystemStackTraceInformation,
	SystemPagedPoolInformation, // not implemented
	SystemNonPagedPoolInformation, // not implemented
	SystemHandleInformation, // q: SYSTEM_HANDLE_INFORMATION
	SystemObjectInformation, // q: SYSTEM_OBJECTTYPE_INFORMATION mixed with SYSTEM_OBJECT_INFORMATION
	SystemPageFileInformation, // q: SYSTEM_PAGEFILE_INFORMATION
	SystemVdmInstemulInformation, // q
	SystemVdmBopInformation, // not implemented // 20
	SystemFileCacheInformation, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemCache)
	SystemPoolTagInformation, // q: SYSTEM_POOLTAG_INFORMATION
	SystemInterruptInformation, // q: SYSTEM_INTERRUPT_INFORMATION
	SystemDpcBehaviorInformation, // q: SYSTEM_DPC_BEHAVIOR_INFORMATION; s: SYSTEM_DPC_BEHAVIOR_INFORMATION (requires SeLoadDriverPrivilege)
	SystemFullMemoryInformation, // not implemented
	SystemLoadGdiDriverInformation, // s (kernel-mode only)
	SystemUnloadGdiDriverInformation, // s (kernel-mode only)
	SystemTimeAdjustmentInformation, // q: SYSTEM_QUERY_TIME_ADJUST_INFORMATION; s: SYSTEM_SET_TIME_ADJUST_INFORMATION (requires SeSystemtimePrivilege)
	SystemSummaryMemoryInformation, // not implemented
	SystemMirrorMemoryInformation, // s (requires license value "Kernel-MemoryMirroringSupported") (requires SeShutdownPrivilege) // 30
	SystemPerformanceTraceInformation, // s
	SystemObsolete0, // not implemented
	SystemExceptionInformation, // q: SYSTEM_EXCEPTION_INFORMATION
	SystemCrashDumpStateInformation, // s (requires SeDebugPrivilege)
	SystemKernelDebuggerInformation, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION
	SystemContextSwitchInformation, // q: SYSTEM_CONTEXT_SWITCH_INFORMATION
	SystemRegistryQuotaInformation, // q: SYSTEM_REGISTRY_QUOTA_INFORMATION; s (requires SeIncreaseQuotaPrivilege)
	SystemExtendServiceTableInformation, // s (requires SeLoadDriverPrivilege) // loads win32k only
	SystemPrioritySeperation, // s (requires SeTcbPrivilege)
	SystemVerifierAddDriverInformation, // s (requires SeDebugPrivilege) // 40
	SystemVerifierRemoveDriverInformation, // s (requires SeDebugPrivilege)
	SystemProcessorIdleInformation, // q: SYSTEM_PROCESSOR_IDLE_INFORMATION
	SystemLegacyDriverInformation, // q: SYSTEM_LEGACY_DRIVER_INFORMATION
	SystemCurrentTimeZoneInformation, // q
	SystemLookasideInformation, // q: SYSTEM_LOOKASIDE_INFORMATION
	SystemTimeSlipNotification, // s (requires SeSystemtimePrivilege)
	SystemSessionCreate, // not implemented
	SystemSessionDetach, // not implemented
	SystemSessionInformation, // not implemented
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
	SystemEmulationBasicInformation, // q
	SystemEmulationProcessorInformation,
	SystemExtendedHandleInformation, // q: SYSTEM_HANDLE_INFORMATION_EX
	SystemLostDelayedWriteInformation, // q: ULONG
	SystemBigPoolInformation, // q: SYSTEM_BIGPOOL_INFORMATION
	SystemSessionPoolTagInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION
	SystemSessionMappedViewInformation, // q: SYSTEM_SESSION_MAPPED_VIEW_INFORMATION
	SystemHotpatchInformation, // q; s
	SystemObjectSecurityMode, // q // 70
	SystemWatchdogTimerHandler, // s (kernel-mode only)
	SystemWatchdogTimerInformation, // q (kernel-mode only); s (kernel-mode only)
	SystemLogicalProcessorInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION
	SystemWow64SharedInformationObsolete, // not implemented
	SystemRegisterFirmwareTableInformationHandler, // s (kernel-mode only)
	SystemFirmwareTableInformation, // SYSTEM_FIRMWARE_TABLE_INFORMATION
	SystemModuleInformationEx, // q: RTL_PROCESS_MODULE_INFORMATION_EX
	SystemVerifierTriageInformation, // not implemented
	SystemSuperfetchInformation, // q; s: SUPERFETCH_INFORMATION // PfQuerySuperfetchInformation
	SystemMemoryListInformation, // q: SYSTEM_MEMORY_LIST_INFORMATION; s: SYSTEM_MEMORY_LIST_COMMAND (requires SeProfileSingleProcessPrivilege) // 80
	SystemFileCacheInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (same as SystemFileCacheInformation)
	SystemThreadPriorityClientIdInformation, // s: SYSTEM_THREAD_CID_PRIORITY_INFORMATION (requires SeIncreaseBasePriorityPrivilege)
	SystemProcessorIdleCycleTimeInformation, // q: SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION[]
	SystemVerifierCancellationInformation, // not implemented // name:wow64:whNT32QuerySystemVerifierCancellationInformation
	SystemProcessorPowerInformationEx, // not implemented
	SystemRefTraceInformation, // q; s: SYSTEM_REF_TRACE_INFORMATION // ObQueryRefTraceInformation
	SystemSpecialPoolInformation, // q; s (requires SeDebugPrivilege) // MmSpecialPoolTag, then MmSpecialPoolCatchOverruns != 0
	SystemProcessIdInformation, // q: SYSTEM_PROCESS_ID_INFORMATION
	SystemErrorPortInformation, // s (requires SeTcbPrivilege)
	SystemBootEnvironmentInformation, // q: SYSTEM_BOOT_ENVIRONMENT_INFORMATION // 90
	SystemHypervisorInformation, // q; s (kernel-mode only)
	SystemVerifierInformationEx, // q; s: SYSTEM_VERIFIER_INFORMATION_EX
	SystemTimeZoneInformation, // s (requires SeTimeZonePrivilege)
	SystemImageFileExecutionOptionsInformation, // s: SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION (requires SeTcbPrivilege)
	SystemCoverageInformation, // q; s // name:wow64:whNT32QuerySystemCoverageInformation; ExpCovQueryInformation
	SystemPrefetchPatchInformation, // not implemented
	SystemVerifierFaultsInformation, // s (requires SeDebugPrivilege)
	SystemSystemPartitionInformation, // q: SYSTEM_SYSTEM_PARTITION_INFORMATION
	SystemSystemDiskInformation, // q: SYSTEM_SYSTEM_DISK_INFORMATION
	SystemProcessorPerformanceDistribution, // q: SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION // 100
	SystemNumaProximityNodeInformation, // q
	SystemDynamicTimeZoneInformation, // q; s (requires SeTimeZonePrivilege)
	SystemCodeIntegrityInformation, // q: SYSTEM_CODEINTEGRITY_INFORMATION // SeCodeIntegrityQueryInformation
	SystemProcessorMicrocodeUpdateInformation, // s
	SystemProcessorBrandString, // q // HaliQuerySystemInformation -> HalpGetProcessorBrandString, info class 23
	SystemVirtualAddressInformation, // q: SYSTEM_VA_LIST_INFORMATION[]; s: SYSTEM_VA_LIST_INFORMATION[] (requires SeIncreaseQuotaPrivilege) // MmQuerySystemVaInformation
	SystemLogicalProcessorAndGroupInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX // since WIN7 // KeQueryLogicalProcessorRelationship
	SystemProcessorCycleTimeInformation, // q: SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION[]
	SystemStoreInformation, // q; s // SmQueryStoreInformation
	SystemRegistryAppendString, // s: SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS // 110
	SystemAitSamplingValue, // s: ULONG (requires SeProfileSingleProcessPrivilege)
	SystemVhdBootInformation, // q: SYSTEM_VHD_BOOT_INFORMATION
	SystemCpuQuotaInformation, // q; s // PsQueryCpuQuotaInformation
	SystemNativeBasicInformation, // not implemented
	SystemSpare1, // not implemented
	SystemLowPriorityIoInformation, // q: SYSTEM_LOW_PRIORITY_IO_INFORMATION
	SystemTpmBootEntropyInformation, // q: TPM_BOOT_ENTROPY_NT_RESULT // ExQueryTpmBootEntropyInformation
	SystemVerifierCountersInformation, // q: SYSTEM_VERIFIER_COUNTERS_INFORMATION
	SystemPagedPoolInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypePagedPool)
	SystemSystemPtesInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemPtes) // 120
	SystemNodeDistanceInformation, // q
	SystemAcpiAuditInformation, // q: SYSTEM_ACPI_AUDIT_INFORMATION // HaliQuerySystemInformation -> HalpAuditQueryResults, info class 26
	SystemBasicPerformanceInformation, // q: SYSTEM_BASIC_PERFORMANCE_INFORMATION // name:wow64:whNtQuerySystemInformation_SystemBasicPerformanceInformation
	SystemQueryPerformanceCounterInformation, // q: SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION // since WIN7 SP1
	SystemSessionBigPoolInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION // since WIN8
	SystemBootGraphicsInformation, // q; s: SYSTEM_BOOT_GRAPHICS_INFORMATION (kernel-mode only)
	SystemScrubPhysicalMemoryInformation,
	SystemBadPageInformation,
	SystemProcessorProfileControlArea,
	SystemCombinePhysicalMemoryInformation, // 130
	SystemEntropyInterruptTimingCallback,
	SystemConsoleInformation, // q: SYSTEM_CONSOLE_INFORMATION
	SystemPlatformBinaryInformation, // q: SYSTEM_PLATFORM_BINARY_INFORMATION
	SystemThrottleNotificationInformation,
	SystemHypervisorProcessorCountInformation, // q: SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION
	SystemDeviceDataInformation, // q: SYSTEM_DEVICE_DATA_INFORMATION
	SystemDeviceDataEnumerationInformation,
	SystemMemoryTopologyInformation, // q: SYSTEM_MEMORY_TOPOLOGY_INFORMATION
	SystemMemoryChannelInformation, // q: SYSTEM_MEMORY_CHANNEL_INFORMATION
	SystemBootLogoInformation, // q: SYSTEM_BOOT_LOGO_INFORMATION // 140
	SystemProcessorPerformanceInformationEx, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX // since WINBLUE
	SystemSpare0,
	SystemSecureBootPolicyInformation, // q: SYSTEM_SECUREBOOT_POLICY_INFORMATION
	SystemPageFileInformationEx, // q: SYSTEM_PAGEFILE_INFORMATION_EX
	SystemSecureBootInformation, // q: SYSTEM_SECUREBOOT_INFORMATION
	SystemEntropyInterruptTimingRawInformation,
	SystemPortableWorkspaceEfiLauncherInformation, // q: SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION
	SystemFullProcessInformation, // q: SYSTEM_PROCESS_INFORMATION with SYSTEM_PROCESS_INFORMATION_EXTENSION (requires admin)
	SystemKernelDebuggerInformationEx, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX
	SystemBootMetadataInformation, // 150
	SystemSoftRebootInformation,
	SystemElamCertificateInformation, // s: SYSTEM_ELAM_CERTIFICATE_INFORMATION
	SystemOfflineDumpConfigInformation,
	SystemProcessorFeaturesInformation, // q: SYSTEM_PROCESSOR_FEATURES_INFORMATION
	SystemRegistryReconciliationInformation,
	SystemEdidInformation,
	SystemManufacturingInformation, // q: SYSTEM_MANUFACTURING_INFORMATION // since THRESHOLD
	SystemEnergyEstimationConfigInformation, // q: SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION
	SystemHypervisorDetailInformation, // q: SYSTEM_HYPERVISOR_DETAIL_INFORMATION
	SystemProcessorCycleStatsInformation, // q: SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION // 160
	SystemVmGenerationCountInformation,
	SystemTrustedPlatformModuleInformation, // q: SYSTEM_TPM_INFORMATION
	SystemKernelDebuggerFlags,
	SystemCodeIntegrityPolicyInformation, // q: SYSTEM_CODEINTEGRITYPOLICY_INFORMATION
	SystemIsolatedUserModeInformation, // q: SYSTEM_ISOLATED_USER_MODE_INFORMATION
	SystemHardwareSecurityTestInterfaceResultsInformation,
	SystemSingleModuleInformation, // q: SYSTEM_SINGLE_MODULE_INFORMATION
	SystemAllowedCpuSetsInformation,
	SystemDmaProtectionInformation, // q: SYSTEM_DMA_PROTECTION_INFORMATION
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
	SystemInterruptSteeringInformation, // 180
	SystemSupportedProcessorArchitectures,
	SystemMemoryUsageInformation, // q: SYSTEM_MEMORY_USAGE_INFORMATION
	SystemCodeIntegrityCertificateInformation, // q: SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION
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
	USHORT ProcessorCount;
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
	ULONG ThreadState;
	KWAIT_REASON WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _TEB *PTEB;

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
	SYSTEM_THREAD_INFORMATION Threads[1];
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
typedef struct _SYSTEM_LOCK_TABLE_ENTRY_INFO
{
	PVOID Address;
	USHORT Type;
	USHORT Reserved1;
	ULONG ExclusiveOwnerThreadId;
	ULONG ActiveCount;
	ULONG ContentionCount;
	ULONG Reserved2[2];
	ULONG NumberOfSharedWaiters;
	ULONG NumberOfExclusiveWaiters;
} SYSTEM_LOCK_TABLE_ENTRY_INFO, *PSYSTEM_LOCK_TABLE_ENTRY_INFO;

// private
typedef struct _SYSTEM_LOCK_INFORMATION
{
	ULONG Count;
	SYSTEM_LOCK_TABLE_ENTRY_INFO Locks[1];
} SYSTEM_LOCK_INFORMATION, *PSYSTEM_LOCK_INFORMATION;

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

typedef struct _SYSTEM_SET_TIME_ADJUST_INFORMATION
{
	ULONG TimeAdjustment;
	BOOLEAN Enable;
} SYSTEM_SET_TIME_ADJUST_INFORMATION, *PSYSTEM_SET_TIME_ADJUST_INFORMATION;

typedef struct _SYSTEM_EXCEPTION_INFORMATION
{
	ULONG AlignmentFixupCount;
	ULONG ExceptionDispatchCount;
	ULONG FloatingEmulationCount;
	ULONG ByteWordEmulationCount;
} SYSTEM_EXCEPTION_INFORMATION, *PSYSTEM_EXCEPTION_INFORMATION;

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

typedef struct _SYSTEM_VERIFIER_INFORMATION
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
typedef struct _SYSTEM_REF_TRACE_INFORMATION
{
	BOOLEAN TraceEnable;
	BOOLEAN TracePermanent;
	UNICODE_STRING TraceProcessName;
	UNICODE_STRING TracePoolTags;
} SYSTEM_REF_TRACE_INFORMATION, *PSYSTEM_REF_TRACE_INFORMATION;

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
} SYSTEM_BOOT_ENVIRONMENT_INFORMATION, *PSYSTEM_BOOT_ENVIRONMENT_INFORMATION;

// private
typedef struct _SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION
{
	ULONG FlagsToEnable;
	ULONG FlagsToDisable;
} SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION, *PSYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION;

// private
typedef struct _SYSTEM_VERIFIER_INFORMATION_EX
{
	ULONG VerifyMode;
	ULONG OptionChanges;
	UNICODE_STRING PreviousBucketName;
	ULONG IrpCancelTimeoutMsec;
	ULONG VerifierExtensionEnabled;
	ULONG Reserved[1];
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

// private
typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT
{
	LARGE_INTEGER Hits; // ULONG in WIN8
	UCHAR PercentFrequency;
} SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT, *PSYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT;

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

// private
typedef struct _SYSTEM_CODEINTEGRITY_INFORMATION
{
	ULONG Length;
	ULONG CodeIntegrityOptions;
} SYSTEM_CODEINTEGRITY_INFORMATION, *PSYSTEM_CODEINTEGRITY_INFORMATION;

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
	SYSTEM_PAGEFILE_INFORMATION Info;
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
typedef struct _PROCESS_ENERGY_VALUES
{
	ULONGLONG Cycles[2][4];
	ULONGLONG DiskEnergy;
	ULONGLONG NetworkTailEnergy;
	ULONGLONG MBBTailEnergy;
	ULONGLONG NetworkTxRxBytes;
	ULONGLONG MBBTxRxBytes;
	union
	{
		struct
		{
			ULONG Foreground : 1;
		};
		ULONG WindowInformation;
	};
	ULONG PixelArea;
	LONGLONG PixelReportTimestamp;
	ULONGLONG PixelTime;
	LONGLONG ForegroundReportTimestamp;
	ULONGLONG ForegroundTime;
} PROCESS_ENERGY_VALUES, *PPROCESS_ENERGY_VALUES;

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
			ULONG Spare : 31;
		};
	};
	ULONG UserSidOffset;
	ULONG PackageFullNameOffset; // since THRESHOLD
	PROCESS_ENERGY_VALUES EnergyValues; // since THRESHOLD
	ULONG AppIdOffset; // since THRESHOLD
	SIZE_T SharedCommitCharge; // since THRESHOLD2
	ULONG JobObjectId; // since REDSTONE
	ULONG SpareUlong; // since REDSTONE
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
typedef struct _SYSTEM_DMA_PROTECTION_INFORMATION
{
	BOOLEAN DmaProtectionsAvailable;
	BOOLEAN DmaProtectionsInUse;
} SYSTEM_DMA_PROTECTION_INFORMATION, *PSYSTEM_DMA_PROTECTION_INFORMATION;

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
	BOOLEAN SpareFlags : 1;
	BOOLEAN TrustletRunning : 1;
	BOOLEAN SpareFlags2 : 1;
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
	HANDLE SiloIdList[1];
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
} SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION, *PSYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION;

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtQuerySystemInformation(
	_In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
	_In_ ULONG SystemInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySystemInformation(
	_In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
	_In_ ULONG SystemInformationLength,
	_Out_opt_ PULONG ReturnLength
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtQuerySystemInformationEx(
	_In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_In_reads_bytes_(InputBufferLength) PVOID InputBuffer,
	_In_ ULONG InputBufferLength,
	_Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
	_In_ ULONG SystemInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySystemInformationEx(
	_In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_In_reads_bytes_(InputBufferLength) PVOID InputBuffer,
	_In_ ULONG InputBufferLength,
	_Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
	_In_ ULONG SystemInformationLength,
	_Out_opt_ PULONG ReturnLength
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtSetSystemInformation(
	_In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_In_reads_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
	_In_ ULONG SystemInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetSystemInformation(
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

NTSYSCALLAPI NTSTATUS NTAPI NtSystemDebugControl(
	_In_ SYSDBG_COMMAND Command,
	_Inout_updates_bytes_opt_(InputBufferLength) PVOID InputBuffer,
	_In_ ULONG InputBufferLength,
	_Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
	_In_ ULONG OutputBufferLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSystemDebugControl(
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

// HARDERROR_MSG not included

NTSYSCALLAPI NTSTATUS NTAPI NtRaiseHardError(
	_In_ NTSTATUS ErrorStatus,
	_In_ ULONG NumberOfParameters,
	_In_ ULONG UnicodeStringParameterMask,
	_In_reads_(NumberOfParameters) PULONG_PTR Parameters,
	_In_ ULONG ValidResponseOptions,
	_Out_ PULONG Response
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRaiseHardError(
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

// 为使KUSER_SHARED_DATA编译通过而禁用的警告 
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4625) // 已将复制构造函数隐式定义为“已删除”(等级 4)
#pragma warning(disable:4626) // 已将对齐运算符隐式定义为“已删除”(等级 4)
#pragma warning(disable:5026) // 已将移动构造函数隐式定义为“已删除”(MSDN未定义)
#pragma warning(disable:5027) // 已将移动赋值运算符隐式定义为“已删除”(MSDN未定义)
#endif

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
	ULONG NtProductType;
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
	UCHAR Reserved6[2];

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
			ULONG SpareBits : 22;
		};
	};
	ULONG DataFlagsPad[1];

	ULONGLONG TestRetInstruction;
	LONGLONG QpcFrequency;
	ULONG SystemCall;
	ULONG SystemCallPad0;
	ULONGLONG SystemCallPad[2];

	union
	{
		volatile KSYSTEM_TIME TickCount;
		volatile ULONG64 TickCountQuad;
		ULONG ReservedTickCountOverlay[3];
	};
	ULONG TickCountPad[1];

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
	ULONG Reserved8;
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
			UCHAR QpcBypassEnabled : 1;
			UCHAR QpcShift : 1;
		};
	};

	LARGE_INTEGER TimeZoneBiasEffectiveStart;
	LARGE_INTEGER TimeZoneBiasEffectiveEnd;
	XSTATE_CONFIGURATION XState;
} KUSER_SHARED_DATA, *PKUSER_SHARED_DATA;
#include <poppack.h>

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TickCountMultiplier) == 0x4);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, InterruptTime) == 0x8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, SystemTime) == 0x14);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TimeZoneBias) == 0x20);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, ImageNumberLow) == 0x2c);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, ImageNumberHigh) == 0x2e);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NtSystemRoot) == 0x30);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, MaxStackTraceDepth) == 0x238);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, CryptoExponent) == 0x23c);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TimeZoneId) == 0x240);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, LargePageMinimum) == 0x244);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NtProductType) == 0x264);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, ProductTypeIsValid) == 0x268);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NtMajorVersion) == 0x26c);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NtMinorVersion) == 0x270);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, ProcessorFeatures) == 0x274);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, Reserved1) == 0x2b4);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, Reserved3) == 0x2b8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TimeSlip) == 0x2bc);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, AlternativeArchitecture) == 0x2c0);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, SystemExpirationDate) == 0x2c8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, SuiteMask) == 0x2d0);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, KdDebuggerEnabled) == 0x2d4);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, ActiveConsoleId) == 0x2d8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, DismountCount) == 0x2dc);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, ComPlusPackage) == 0x2e0);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, LastSystemRITEventTickCount) == 0x2e4);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, NumberOfPhysicalPages) == 0x2e8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, SafeBootMode) == 0x2ec);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TestRetInstruction) == 0x2f8);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, SystemCallPad) == 0x310);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TickCount) == 0x320);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, TickCountQuad) == 0x320);
C_ASSERT(FIELD_OFFSET(KUSER_SHARED_DATA, XState) == 0x3d8);
//C_ASSERT(sizeof(KUSER_SHARED_DATA) == 0x708); // Visual Studio has a problem with this

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

#endif

// Locale

NTSYSCALLAPI NTSTATUS NTAPI NtQueryDefaultLocale(
	_In_ BOOLEAN UserProfile,
	_Out_ PLCID DefaultLocaleId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryDefaultLocale(
	_In_ BOOLEAN UserProfile,
	_Out_ PLCID DefaultLocaleId
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetDefaultLocale(
	_In_ BOOLEAN UserProfile,
	_In_ LCID DefaultLocaleId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetDefaultLocale(
	_In_ BOOLEAN UserProfile,
	_In_ LCID DefaultLocaleId
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInstallUILanguage(
	_Out_ LANGID *InstallUILanguageId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInstallUILanguage(
	_Out_ LANGID *InstallUILanguageId
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI NTSTATUS NTAPI NtFlushInstallUILanguage(
	_In_ LANGID InstallUILanguage,
	_In_ ULONG SetComittedFlag
);

// private
NTSYSCALLAPI NTSTATUS NTAPI ZwFlushInstallUILanguage(
	_In_ LANGID InstallUILanguage,
	_In_ ULONG SetComittedFlag
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtQueryDefaultUILanguage(
	_Out_ LANGID *DefaultUILanguageId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryDefaultUILanguage(
	_Out_ LANGID *DefaultUILanguageId
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetDefaultUILanguage(
	_In_ LANGID DefaultUILanguageId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetDefaultUILanguage(
	_In_ LANGID DefaultUILanguageId
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI NTSTATUS NTAPI NtIsUILanguageComitted(
	VOID
);

// private
NTSYSCALLAPI NTSTATUS NTAPI ZwIsUILanguageComitted(
	VOID
);
#endif

// NLS

// begin_private

#if (NTDDI_VERSION >= NTDDI_VISTA)

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtInitializeNlsFiles(
	_Out_ PVOID *BaseAddress,
	_Out_ PLCID DefaultLocaleId,
	_Out_ PLARGE_INTEGER DefaultCasingTableSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwInitializeNlsFiles(
	_Out_ PVOID *BaseAddress,
	_Out_ PLCID DefaultLocaleId,
	_Out_ PLARGE_INTEGER DefaultCasingTableSize
);
#else
NTSYSCALLAPI NTSTATUS NTAPI NtInitializeNlsFiles(
	_Out_ PVOID *BaseAddress,
	_Out_ PLCID DefaultLocaleId,
	_Out_ PLARGE_INTEGER DefaultCasingTableSize,
	_Out_opt_ PULONG CurrentNLSVersion
);

NTSYSCALLAPI NTSTATUS NTAPI ZwInitializeNlsFiles(
	_Out_ PVOID *BaseAddress,
	_Out_ PLCID DefaultLocaleId,
	_Out_ PLARGE_INTEGER DefaultCasingTableSize,
	_Out_opt_ PULONG CurrentNLSVersion
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtGetNlsSectionPtr(
	_In_ ULONG SectionType,
	_In_ ULONG SectionData,
	_In_ PVOID ContextData,
	_Out_ PVOID *SectionPointer,
	_Out_ PULONG SectionSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetNlsSectionPtr(
	_In_ ULONG SectionType,
	_In_ ULONG SectionData,
	_In_ PVOID ContextData,
	_Out_ PVOID *SectionPointer,
	_Out_ PULONG SectionSize
);

#if (NTDDI_VERSION < NTDDI_WIN7)

NTSYSCALLAPI NTSTATUS NTAPI NtAcquireCMFViewOwnership(
	_Out_ PULONGLONG TimeStamp,
	_Out_ PBOOLEAN tokenTaken,
	_In_ BOOLEAN replaceExisting
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAcquireCMFViewOwnership(
	_Out_ PULONGLONG TimeStamp,
	_Out_ PBOOLEAN tokenTaken,
	_In_ BOOLEAN replaceExisting
);

NTSYSCALLAPI NTSTATUS NTAPI NtReleaseCMFViewOwnership(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReleaseCMFViewOwnership(
	VOID
);

#endif

NTSYSCALLAPI NTSTATUS NTAPI NtMapCMFModule(
	_In_ ULONG What,
	_In_ ULONG Index,
	_Out_opt_ PULONG CacheIndexOut,
	_Out_opt_ PULONG CacheFlagsOut,
	_Out_opt_ PULONG ViewSizeOut,
	_Out_opt_ PVOID *BaseAddress
);

NTSYSCALLAPI NTSTATUS NTAPI ZwMapCMFModule(
	_In_ ULONG What,
	_In_ ULONG Index,
	_Out_opt_ PULONG CacheIndexOut,
	_Out_opt_ PULONG CacheFlagsOut,
	_Out_opt_ PULONG ViewSizeOut,
	_Out_opt_ PVOID *BaseAddress
);

NTSYSCALLAPI NTSTATUS NTAPI NtGetMUIRegistryInfo(
	_In_ ULONG Flags,
	_Inout_ PULONG DataSize,
	_Out_ PVOID Data
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetMUIRegistryInfo(
	_In_ ULONG Flags,
	_Inout_ PULONG DataSize,
	_Out_ PVOID Data
);

#endif

// end_private

// Global atoms

NTSYSCALLAPI NTSTATUS NTAPI NtAddAtom(
	_In_reads_bytes_opt_(Length) PWSTR AtomName,
	_In_ ULONG Length,
	_Out_opt_ PRTL_ATOM Atom
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAddAtom(
	_In_reads_bytes_opt_(Length) PWSTR AtomName,
	_In_ ULONG Length,
	_Out_opt_ PRTL_ATOM Atom
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
NTSYSCALLAPI NTSTATUS NTAPI NtAddAtomEx(
	_In_reads_bytes_opt_(Length) PWSTR AtomName,
	_In_ ULONG Length,
	_Out_opt_ PRTL_ATOM Atom,
	_In_ ULONG Flags
);

// rev
NTSYSCALLAPI NTSTATUS NTAPI ZwAddAtomEx(
	_In_reads_bytes_opt_(Length) PWSTR AtomName,
	_In_ ULONG Length,
	_Out_opt_ PRTL_ATOM Atom,
	_In_ ULONG Flags
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtFindAtom(
	_In_reads_bytes_opt_(Length) PWSTR AtomName,
	_In_ ULONG Length,
	_Out_opt_ PRTL_ATOM Atom
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFindAtom(
	_In_reads_bytes_opt_(Length) PWSTR AtomName,
	_In_ ULONG Length,
	_Out_opt_ PRTL_ATOM Atom
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteAtom(
	_In_ RTL_ATOM Atom
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteAtom(
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

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationAtom(
	_In_ RTL_ATOM Atom,
	_In_ ATOM_INFORMATION_CLASS AtomInformationClass,
	_Out_writes_bytes_(AtomInformationLength) PVOID AtomInformation,
	_In_ ULONG AtomInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationAtom(
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

NTSYSCALLAPI NTSTATUS NTAPI NtQueryLicenseValue(
	_In_ PUNICODE_STRING ValueName,
	_Out_opt_ PULONG Type,
	_Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
	_In_ ULONG DataSize,
	_Out_ PULONG ResultDataSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryLicenseValue(
	_In_ PUNICODE_STRING ValueName,
	_Out_opt_ PULONG Type,
	_Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
	_In_ ULONG DataSize,
	_Out_ PULONG ResultDataSize
);

// Misc.

NTSYSCALLAPI NTSTATUS NTAPI NtSetDefaultHardErrorPort(
	_In_ HANDLE DefaultHardErrorPort
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetDefaultHardErrorPort(
	_In_ HANDLE DefaultHardErrorPort
);

typedef enum _SHUTDOWN_ACTION
{
	ShutdownNoReboot,
	ShutdownReboot,
	ShutdownPowerOff
} SHUTDOWN_ACTION;

NTSYSCALLAPI NTSTATUS NTAPI NtShutdownSystem(
	_In_ SHUTDOWN_ACTION Action
);

NTSYSCALLAPI NTSTATUS NTAPI ZwShutdownSystem(
	_In_ SHUTDOWN_ACTION Action
);

NTSYSCALLAPI NTSTATUS NTAPI NtDisplayString(
	_In_ PUNICODE_STRING String
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDisplayString(
	_In_ PUNICODE_STRING String
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtDrawText(
	_In_ PUNICODE_STRING String
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDrawText(
	_In_ PUNICODE_STRING String
);
#endif

#endif // (!KERNELMODE)

#endif

#ifndef _NTMMAPI_H
#define _NTMMAPI_H

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
	MemoryRegionInformationEx,
	MemoryPrivilegedBasicInformation
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
			ULONG Reserved : 26;
		};
	};
	SIZE_T RegionSize;
	SIZE_T CommitSize;
} MEMORY_REGION_INFORMATION, *PMEMORY_REGION_INFORMATION;

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
#ifdef _WIN64
			ULONG_PTR ReservedUlong : 32;
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
			ULONG Reserved : 30;
		};
	};
} MEMORY_IMAGE_INFORMATION, *PMEMORY_IMAGE_INFORMATION;

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
	ULONGLONG Reserved0 : 1; // reserved for future expansion
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
	ULONGLONG Reserved : 7; // reserved for future expansion
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
		PVOID FileObject; // mapped files
		PVOID UniqueFileObjectKey;
		PVOID ProtoPteAddress;
		PVOID VirtualAddress;  // everything else
	} u2;
} MMPFN_IDENTITY, *PMMPFN_IDENTITY;

typedef struct _MMPFN_MEMSNAP_INFORMATION
{
	ULONG_PTR InitialPageFrameIndex;
	ULONG_PTR Count;
} MMPFN_MEMSNAP_INFORMATION, *PMMPFN_MEMSNAP_INFORMATION;

typedef enum _SECTION_INFORMATION_CLASS
{
	SectionBasicInformation,
	SectionImageInformation,
	SectionRelocationInformation, // name:wow64:whNtQuerySection_SectionRelocationInformation
	SectionOriginalBaseInformation, // PVOID BaseAddress
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

#ifndef KERNELMODE
typedef enum _SECTION_INHERIT
{
	ViewShare = 1,
	ViewUnmap = 2
} SECTION_INHERIT;
#endif

#define SEC_BASED 0x200000
#define SEC_NO_CHANGE 0x400000
#define SEC_GLOBAL 0x20000000

#define MEM_EXECUTE_OPTION_DISABLE 0x1
#define MEM_EXECUTE_OPTION_ENABLE 0x2
#define MEM_EXECUTE_OPTION_DISABLE_THUNK_EMULATION 0x4
#define MEM_EXECUTE_OPTION_PERMANENT 0x8
#define MEM_EXECUTE_OPTION_EXECUTE_DISPATCH_ENABLE 0x10
#define MEM_EXECUTE_OPTION_IMAGE_DISPATCH_ENABLE 0x20
#define MEM_EXECUTE_OPTION_VALID_FLAGS 0x3f

// Virtual memory

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtAllocateVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
	_In_ ULONG_PTR ZeroBits,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG AllocationType,
	_In_ ULONG Protect
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAllocateVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
	_In_ ULONG_PTR ZeroBits,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG AllocationType,
	_In_ ULONG Protect
);

NTSYSCALLAPI NTSTATUS NTAPI NtFreeVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ PVOID *BaseAddress,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG FreeType
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFreeVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ PVOID *BaseAddress,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG FreeType
);

NTSYSCALLAPI NTSTATUS NTAPI NtReadVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_Out_writes_bytes_(BufferSize) PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesRead
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReadVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_Out_writes_bytes_(BufferSize) PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesRead
);

NTSYSCALLAPI NTSTATUS NTAPI NtWriteVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_In_reads_bytes_(BufferSize) PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesWritten
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWriteVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_In_reads_bytes_(BufferSize) PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesWritten
);

NTSYSCALLAPI NTSTATUS NTAPI NtProtectVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ PVOID *BaseAddress,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG NewProtect,
	_Out_ PULONG OldProtect
);

NTSYSCALLAPI NTSTATUS NTAPI ZwProtectVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ PVOID *BaseAddress,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG NewProtect,
	_Out_ PULONG OldProtect
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_ PVOID BaseAddress,
	_In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
	_Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
	_In_ SIZE_T MemoryInformationLength,
	_Out_opt_ PSIZE_T ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_ PVOID BaseAddress,
	_In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
	_Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
	_In_ SIZE_T MemoryInformationLength,
	_Out_opt_ PSIZE_T ReturnLength
);

#endif

// begin_private

typedef enum _VIRTUAL_MEMORY_INFORMATION_CLASS
{
	VmPrefetchInformation,
	VmPagePriorityInformation,
	VmCfgCallTargetInformation
} VIRTUAL_MEMORY_INFORMATION_CLASS;

typedef struct _MEMORY_RANGE_ENTRY
{
	PVOID VirtualAddress;
	SIZE_T NumberOfBytes;
} MEMORY_RANGE_ENTRY, *PMEMORY_RANGE_ENTRY;

// end_private

#ifndef KERNELMODE

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
	_In_ ULONG_PTR NumberOfEntries,
	_In_reads_(NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
	_In_reads_bytes_(VmInformationLength) PVOID VmInformation,
	_In_ ULONG VmInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
	_In_ ULONG_PTR NumberOfEntries,
	_In_reads_(NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
	_In_reads_bytes_(VmInformationLength) PVOID VmInformation,
	_In_ ULONG VmInformationLength
);

#endif

NTSYSCALLAPI NTSTATUS NTAPI NtLockVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ PVOID *BaseAddress,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG MapType
);

NTSYSCALLAPI NTSTATUS NTAPI ZwLockVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ PVOID *BaseAddress,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG MapType
);

NTSYSCALLAPI NTSTATUS NTAPI NtUnlockVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ PVOID *BaseAddress,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG MapType
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnlockVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_Inout_ PVOID *BaseAddress,
	_Inout_ PSIZE_T RegionSize,
	_In_ ULONG MapType
);

#endif

// Sections

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtCreateSection(
	_Out_ PHANDLE SectionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PLARGE_INTEGER MaximumSize,
	_In_ ULONG SectionPageProtection,
	_In_ ULONG AllocationAttributes,
	_In_opt_ HANDLE FileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateSection(
	_Out_ PHANDLE SectionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PLARGE_INTEGER MaximumSize,
	_In_ ULONG SectionPageProtection,
	_In_ ULONG AllocationAttributes,
	_In_opt_ HANDLE FileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenSection(
	_Out_ PHANDLE SectionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenSection(
	_Out_ PHANDLE SectionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtMapViewOfSection(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwMapViewOfSection(
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

NTSYSCALLAPI NTSTATUS NTAPI NtUnmapViewOfSection(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnmapViewOfSection(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI NTSTATUS NTAPI NtUnmapViewOfSectionEx(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnmapViewOfSectionEx(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_In_ ULONG Flags
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtExtendSection(
	_In_ HANDLE SectionHandle,
	_Inout_ PLARGE_INTEGER NewSectionSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwExtendSection(
	_In_ HANDLE SectionHandle,
	_Inout_ PLARGE_INTEGER NewSectionSize
);

NTSYSCALLAPI NTSTATUS NTAPI NtQuerySection(
	_In_ HANDLE SectionHandle,
	_In_ SECTION_INFORMATION_CLASS SectionInformationClass,
	_Out_writes_bytes_(SectionInformationLength) PVOID SectionInformation,
	_In_ SIZE_T SectionInformationLength,
	_Out_opt_ PSIZE_T ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySection(
	_In_ HANDLE SectionHandle,
	_In_ SECTION_INFORMATION_CLASS SectionInformationClass,
	_Out_writes_bytes_(SectionInformationLength) PVOID SectionInformation,
	_In_ SIZE_T SectionInformationLength,
	_Out_opt_ PSIZE_T ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtAreMappedFilesTheSame(
	_In_ PVOID File1MappedAsAnImage,
	_In_ PVOID File2MappedAsFile
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAreMappedFilesTheSame(
	_In_ PVOID File1MappedAsAnImage,
	_In_ PVOID File2MappedAsFile
);

#endif

// Partitions

// private
typedef enum _MEMORY_PARTITION_INFORMATION_CLASS
{
	SystemMemoryPartitionInformation, // q: MEMORY_PARTITION_CONFIGURATION_INFORMATION
	SystemMemoryPartitionMoveMemory, // s: MEMORY_PARTITION_TRANSFER_INFORMATION
	SystemMemoryPartitionAddPagefile, // s: MEMORY_PARTITION_PAGEFILE_INFORMATION
	SystemMemoryPartitionCombineMemory, // q; s: MEMORY_PARTITION_PAGE_COMBINE_INFORMATION
	SystemMemoryPartitionInitialAddMemory // q; s: MEMORY_PARTITION_INITIAL_ADD_INFORMATION
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

#ifndef KERNELMODE

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSCALLAPI NTSTATUS NTAPI NtCreatePartition(
	_Out_ PHANDLE PartitionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG PreferredNode
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreatePartition(
	_Out_ PHANDLE PartitionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG PreferredNode
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenPartition(
	_Out_ PHANDLE PartitionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenPartition(
	_Out_ PHANDLE PartitionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtManagePartition(
	_In_ MEMORY_PARTITION_INFORMATION_CLASS PartitionInformationClass,
	_In_ PVOID PartitionInformation,
	_In_ ULONG PartitionInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwManagePartition(
	_In_ MEMORY_PARTITION_INFORMATION_CLASS PartitionInformationClass,
	_In_ PVOID PartitionInformation,
	_In_ ULONG PartitionInformationLength
);

#endif

#endif

// User physical pages

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtMapUserPhysicalPages(
	_In_ PVOID VirtualAddress,
	_In_ ULONG_PTR NumberOfPages,
	_In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

NTSYSCALLAPI NTSTATUS NTAPI ZwMapUserPhysicalPages(
	_In_ PVOID VirtualAddress,
	_In_ ULONG_PTR NumberOfPages,
	_In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

NTSYSCALLAPI NTSTATUS NTAPI NtMapUserPhysicalPagesScatter(
	_In_reads_(NumberOfPages) PVOID *VirtualAddresses,
	_In_ ULONG_PTR NumberOfPages,
	_In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

NTSYSCALLAPI NTSTATUS NTAPI ZwMapUserPhysicalPagesScatter(
	_In_reads_(NumberOfPages) PVOID *VirtualAddresses,
	_In_ ULONG_PTR NumberOfPages,
	_In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

NTSYSCALLAPI NTSTATUS NTAPI NtAllocateUserPhysicalPages(
	_In_ HANDLE ProcessHandle,
	_Inout_ PULONG_PTR NumberOfPages,
	_Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAllocateUserPhysicalPages(
	_In_ HANDLE ProcessHandle,
	_Inout_ PULONG_PTR NumberOfPages,
	_Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray
);

NTSYSCALLAPI NTSTATUS NTAPI NtFreeUserPhysicalPages(
	_In_ HANDLE ProcessHandle,
	_Inout_ PULONG_PTR NumberOfPages,
	_In_reads_(*NumberOfPages) PULONG_PTR UserPfnArray
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFreeUserPhysicalPages(
	_In_ HANDLE ProcessHandle,
	_Inout_ PULONG_PTR NumberOfPages,
	_In_reads_(*NumberOfPages) PULONG_PTR UserPfnArray
);

#endif

// Sessions

#ifndef KERNELMODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtOpenSession(
	_Out_ PHANDLE SessionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenSession(
	_Out_ PHANDLE SessionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);
#endif

#endif

// Misc.

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtGetWriteWatch(
	_In_ HANDLE ProcessHandle,
	_In_ ULONG Flags,
	_In_ PVOID BaseAddress,
	_In_ SIZE_T RegionSize,
	_Out_writes_(*EntriesInUserAddressArray) PVOID *UserAddressArray,
	_Inout_ PULONG_PTR EntriesInUserAddressArray,
	_Out_ PULONG Granularity
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetWriteWatch(
	_In_ HANDLE ProcessHandle,
	_In_ ULONG Flags,
	_In_ PVOID BaseAddress,
	_In_ SIZE_T RegionSize,
	_Out_writes_(*EntriesInUserAddressArray) PVOID *UserAddressArray,
	_Inout_ PULONG_PTR EntriesInUserAddressArray,
	_Out_ PULONG Granularity
);

NTSYSCALLAPI NTSTATUS NTAPI NtResetWriteWatch(
	_In_ HANDLE ProcessHandle,
	_In_ PVOID BaseAddress,
	_In_ SIZE_T RegionSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwResetWriteWatch(
	_In_ HANDLE ProcessHandle,
	_In_ PVOID BaseAddress,
	_In_ SIZE_T RegionSize
);

NTSYSCALLAPI NTSTATUS NTAPI NtCreatePagingFile(
	_In_ PUNICODE_STRING PageFileName,
	_In_ PLARGE_INTEGER MinimumSize,
	_In_ PLARGE_INTEGER MaximumSize,
	_In_ ULONG Priority
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreatePagingFile(
	_In_ PUNICODE_STRING PageFileName,
	_In_ PLARGE_INTEGER MinimumSize,
	_In_ PLARGE_INTEGER MaximumSize,
	_In_ ULONG Priority
);

NTSYSCALLAPI NTSTATUS NTAPI NtFlushInstructionCache(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_In_ SIZE_T Length
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFlushInstructionCache(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_In_ SIZE_T Length
);

NTSYSCALLAPI NTSTATUS NTAPI NtFlushWriteBuffer(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFlushWriteBuffer(
	VOID
);

#endif

#endif

#ifndef _NTOBAPI_H
#define _NTOBAPI_H

#ifndef KERNELMODE
#define OBJECT_TYPE_CREATE 0x0001
#define OBJECT_TYPE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)
#endif

#ifndef KERNELMODE
#define DIRECTORY_QUERY 0x0001
#define DIRECTORY_TRAVERSE 0x0002
#define DIRECTORY_CREATE_OBJECT 0x0004
#define DIRECTORY_CREATE_SUBDIRECTORY 0x0008
#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xf)
#endif

#ifndef KERNELMODE
#define SYMBOLIC_LINK_QUERY 0x0001
#define SYMBOLIC_LINK_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)
#endif

#define OBJ_PROTECT_CLOSE 0x00000001
#ifndef OBJ_INHERIT
#define OBJ_INHERIT 0x00000002
#endif
#define OBJ_AUDIT_OBJECT_CLOSE 0x00000004

#ifndef KERNELMODE
typedef enum _OBJECT_INFORMATION_CLASS
{
	ObjectBasicInformation, // OBJECT_BASIC_INFORMATION
	ObjectNameInformation, // OBJECT_NAME_INFORMATION
	ObjectTypeInformation, // OBJECT_TYPE_INFORMATION
	ObjectTypesInformation, // OBJECT_TYPES_INFORMATION
	ObjectHandleFlagInformation, // OBJECT_HANDLE_FLAG_INFORMATION
	ObjectSessionInformation,
	ObjectSessionObjectInformation,
	MaxObjectInfoClass
} OBJECT_INFORMATION_CLASS;
#else
#define ObjectNameInformation 1
#define ObjectTypesInformation 3
#define ObjectHandleFlagInformation 4
#define ObjectSessionInformation 5
#endif

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

#ifndef KERNELMODE
typedef struct _OBJECT_NAME_INFORMATION
{
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;
#endif

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

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtQueryObject(
	_In_ HANDLE Handle,
	_In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
	_Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
	_In_ ULONG ObjectInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryObject(
	_In_ HANDLE Handle,
	_In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
	_Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
	_In_ ULONG ObjectInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationObject(
	_In_ HANDLE Handle,
	_In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
	_In_reads_bytes_(ObjectInformationLength) PVOID ObjectInformation,
	_In_ ULONG ObjectInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationObject(
	_In_ HANDLE Handle,
	_In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
	_In_reads_bytes_(ObjectInformationLength) PVOID ObjectInformation,
	_In_ ULONG ObjectInformationLength
);

#define DUPLICATE_CLOSE_SOURCE 0x00000001
#define DUPLICATE_SAME_ACCESS 0x00000002
#define DUPLICATE_SAME_ATTRIBUTES 0x00000004

NTSYSCALLAPI NTSTATUS NTAPI NtDuplicateObject(
	_In_ HANDLE SourceProcessHandle,
	_In_ HANDLE SourceHandle,
	_In_opt_ HANDLE TargetProcessHandle,
	_Out_opt_ PHANDLE TargetHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_In_ ULONG Options
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDuplicateObject(
	_In_ HANDLE SourceProcessHandle,
	_In_ HANDLE SourceHandle,
	_In_opt_ HANDLE TargetProcessHandle,
	_Out_opt_ PHANDLE TargetHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_In_ ULONG Options
);

NTSYSCALLAPI NTSTATUS NTAPI NtMakeTemporaryObject(
	_In_ HANDLE Handle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwMakeTemporaryObject(
	_In_ HANDLE Handle
);

NTSYSCALLAPI NTSTATUS NTAPI NtMakePermanentObject(
	_In_ HANDLE Handle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwMakePermanentObject(
	_In_ HANDLE Handle
);

NTSYSCALLAPI NTSTATUS NTAPI NtSignalAndWaitForSingleObject(
	_In_ HANDLE SignalHandle,
	_In_ HANDLE WaitHandle,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSignalAndWaitForSingleObject(
	_In_ HANDLE SignalHandle,
	_In_ HANDLE WaitHandle,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI NtWaitForSingleObject(
	_In_ HANDLE Handle,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWaitForSingleObject(
	_In_ HANDLE Handle,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI NtWaitForMultipleObjects(
	_In_ ULONG Count,
	_In_reads_(Count) HANDLE Handles[],
	_In_ WAIT_TYPE WaitType,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWaitForMultipleObjects(
	_In_ ULONG Count,
	_In_reads_(Count) HANDLE Handles[],
	_In_ WAIT_TYPE WaitType,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSCALLAPI NTSTATUS NTAPI NtWaitForMultipleObjects32(
	_In_ ULONG Count,
	_In_reads_(Count) LONG Handles[],
	_In_ WAIT_TYPE WaitType,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWaitForMultipleObjects32(
	_In_ ULONG Count,
	_In_reads_(Count) LONG Handles[],
	_In_ WAIT_TYPE WaitType,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtSetSecurityObject(
	_In_ HANDLE Handle,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetSecurityObject(
	_In_ HANDLE Handle,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

NTSYSCALLAPI NTSTATUS NTAPI NtQuerySecurityObject(
	_In_ HANDLE Handle,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_Out_writes_bytes_opt_(Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ ULONG Length,
	_Out_ PULONG LengthNeeded
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySecurityObject(
	_In_ HANDLE Handle,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_Out_writes_bytes_opt_(Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ ULONG Length,
	_Out_ PULONG LengthNeeded
);

NTSYSCALLAPI NTSTATUS NTAPI NtClose(
	_In_ HANDLE Handle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwClose(
	_In_ HANDLE Handle
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSCALLAPI NTSTATUS NTAPI NtCompareObjects(
	_In_ HANDLE FirstObjectHandle,
	_In_ HANDLE SecondObjectHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCompareObjects(
	_In_ HANDLE FirstObjectHandle,
	_In_ HANDLE SecondObjectHandle
);
#endif

#endif

// Directory objects

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtCreateDirectoryObject(
	_Out_ PHANDLE DirectoryHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateDirectoryObject(
	_Out_ PHANDLE DirectoryHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI NTSTATUS NTAPI NtCreateDirectoryObjectEx(
	_Out_ PHANDLE DirectoryHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ HANDLE ShadowDirectoryHandle,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateDirectoryObjectEx(
	_Out_ PHANDLE DirectoryHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ HANDLE ShadowDirectoryHandle,
	_In_ ULONG Flags
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtOpenDirectoryObject(
	_Out_ PHANDLE DirectoryHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenDirectoryObject(
	_Out_ PHANDLE DirectoryHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

typedef struct _OBJECT_DIRECTORY_INFORMATION
{
	UNICODE_STRING Name;
	UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

NTSYSCALLAPI NTSTATUS NTAPI NtQueryDirectoryObject(
	_In_ HANDLE DirectoryHandle,
	_Out_writes_bytes_opt_(Length) PVOID Buffer,
	_In_ ULONG Length,
	_In_ BOOLEAN ReturnSingleEntry,
	_In_ BOOLEAN RestartScan,
	_Inout_ PULONG Context,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryDirectoryObject(
	_In_ HANDLE DirectoryHandle,
	_Out_writes_bytes_opt_(Length) PVOID Buffer,
	_In_ ULONG Length,
	_In_ BOOLEAN ReturnSingleEntry,
	_In_ BOOLEAN RestartScan,
	_Inout_ PULONG Context,
	_Out_opt_ PULONG ReturnLength
);

#endif

// Private namespaces

#ifndef KERNELMODE

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSCALLAPI NTSTATUS NTAPI NtCreatePrivateNamespace(
	_Out_ PHANDLE NamespaceHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ PVOID BoundaryDescriptor
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreatePrivateNamespace(
	_Out_ PHANDLE NamespaceHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ PVOID BoundaryDescriptor
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenPrivateNamespace(
	_Out_ PHANDLE NamespaceHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ PVOID BoundaryDescriptor
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenPrivateNamespace(
	_Out_ PHANDLE NamespaceHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ PVOID BoundaryDescriptor
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeletePrivateNamespace(
	_In_ HANDLE NamespaceHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeletePrivateNamespace(
	_In_ HANDLE NamespaceHandle
);

#endif

#endif

// Symbolic links

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtCreateSymbolicLinkObject(
	_Out_ PHANDLE LinkHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ PUNICODE_STRING LinkTarget
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateSymbolicLinkObject(
	_Out_ PHANDLE LinkHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ PUNICODE_STRING LinkTarget
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenSymbolicLinkObject(
	_Out_ PHANDLE LinkHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenSymbolicLinkObject(
	_Out_ PHANDLE LinkHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtQuerySymbolicLinkObject(
	_In_ HANDLE LinkHandle,
	_Inout_ PUNICODE_STRING LinkTarget,
	_Out_opt_ PULONG ReturnedLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySymbolicLinkObject(
	_In_ HANDLE LinkHandle,
	_Inout_ PUNICODE_STRING LinkTarget,
	_Out_opt_ PULONG ReturnedLength
);

#endif

#endif

#ifndef _NTPSAPI_H
#define _NTPSAPI_H

#ifndef PROCESS_SET_PORT
#define PROCESS_SET_PORT 0x0800
#endif

#ifndef THREAD_ALERT
#define THREAD_ALERT 0x0004
#endif

#define GDI_HANDLE_BUFFER_SIZE32 34
#define GDI_HANDLE_BUFFER_SIZE64 60

#ifndef WIN64
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#endif

typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];

typedef ULONG GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef ULONG GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];

#define FLS_MAXIMUM_AVAILABLE 128
#define TLS_MINIMUM_AVAILABLE 64
#define TLS_EXPANSION_SLOTS 1024

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

#ifndef _NTPEBTEB_H
#define _NTPEBTEB_H

typedef struct _RTL_USER_PROCESS_PARAMETERS *PRTL_USER_PROCESS_PARAMETERS;
typedef struct _RTL_CRITICAL_SECTION *PRTL_CRITICAL_SECTION;

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
	PVOID AtlThunkSListPtr;
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
			ULONG ReservedBits0 : 27;
		};
	};
	union
	{
		PVOID KernelCallbackTable;
		PVOID UserSharedInfoPtr;
	};
	ULONG SystemReserved[1];
	ULONG AtlThunkSListPtr32;
	PVOID ApiSetMap;
	ULONG TlsExpansionCounter;
	PVOID TlsBitmap;
	ULONG TlsBitmapBits[2];
	PVOID ReadOnlySharedMemoryBase;
	PVOID HotpatchInformation;
	PVOID *ReadOnlyStaticServerData;
	PVOID AnsiCodePageData;
	PVOID OemCodePageData;
	PVOID UnicodeCaseTableData;

	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;

	LARGE_INTEGER CriticalSectionTimeout;
	SIZE_T HeapSegmentReserve;
	SIZE_T HeapSegmentCommit;
	SIZE_T HeapDeCommitTotalFreeThreshold;
	SIZE_T HeapDeCommitFreeBlockThreshold;

	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PVOID *ProcessHeaps;

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
	PVOID AppCompatInfo;

	UNICODE_STRING CSDVersion;

	PVOID ActivationContextData;
	PVOID ProcessAssemblyStorageMap;
	PVOID SystemDefaultActivationContextData;
	PVOID SystemAssemblyStorageMap;

	SIZE_T MinimumStackCommit;

	PVOID *FlsCallback;
	LIST_ENTRY FlsListHead;
	PVOID FlsBitmap;
	ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
	ULONG FlsHighIndex;

	PVOID WerRegistrationData;
	PVOID WerShipAssertPtr;
	PVOID pContextData;
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
	PVOID TppWorkerpListLock;
	LIST_ENTRY TppWorkerpList;
	PVOID WaitOnAddressHashTable[128];
} PEB, *PPEB;

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

typedef struct _TEB
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
	PVOID SystemReserved1[37];
	UCHAR WorkingOnBehalfTicket[8];
	NTSTATUS ExceptionCode;

	PVOID ActivationContextStackPointer;
	ULONG_PTR InstrumentationCallbackSp;
	ULONG_PTR InstrumentationCallbackPreviousPc;
	ULONG_PTR InstrumentationCallbackPreviousSp;
	ULONG TxFsContext;

	BOOLEAN InstrumentationCallbackDisabled;
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
	USHORT HeapVirtualAffinity;
	USHORT LowFragHeapDataSlot;
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
			USHORT SpareSameTebBits : 2;
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
} TEB, *PTEB;

#endif

#ifndef _NTGDI_H
#define _NTGDI_H

#define GDI_MAX_HANDLE_COUNT 0x4000

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

#endif


// source:http://www.microsoft.com/whdc/system/Sysinternals/MoreThan64proc.mspx

#ifndef KERNELMODE
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
	ProcessExceptionPort, // s: HANDLE
	ProcessAccessToken, // s: PROCESS_ACCESS_TOKEN
	ProcessLdtInformation, // qs: PROCESS_LDT_INFORMATION // 10
	ProcessLdtSize, // s: PROCESS_LDT_SIZE
	ProcessDefaultHardErrorMode, // qs: ULONG
	ProcessIoPortHandlers, // (kernel-mode only)
	ProcessPooledUsageAndLimits, // q: POOLED_USAGE_AND_LIMITS
	ProcessWorkingSetWatch, // q: PROCESS_WS_WATCH_INFORMATION[]; s: void
	ProcessUserModeIOPL,
	ProcessEnableAlignmentFaultFixup, // s: BOOLEAN
	ProcessPriorityClass, // qs: PROCESS_PRIORITY_CLASS
	ProcessWx86Information,
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
	ProcessResourceManagement,
	ProcessCookie, // q: ULONG
	ProcessImageInformation, // q: SECTION_IMAGE_INFORMATION
	ProcessCycleTime, // q: PROCESS_CYCLE_TIME_INFORMATION // since VISTA
	ProcessPagePriority, // q: ULONG
	ProcessInstrumentationCallback, // 40
	ProcessThreadStackAllocation, // s: PROCESS_STACK_ALLOCATION_INFORMATION, PROCESS_STACK_ALLOCATION_INFORMATION_EX
	ProcessWorkingSetWatchEx, // q: PROCESS_WS_WATCH_INFORMATION_EX[]
	ProcessImageFileNameWin32, // q: UNICODE_STRING
	ProcessImageFileMapping, // q: HANDLE (input)
	ProcessAffinityUpdateMode, // qs: PROCESS_AFFINITY_UPDATE_MODE
	ProcessMemoryAllocationMode, // qs: PROCESS_MEMORY_ALLOCATION_MODE
	ProcessGroupInformation, // q: USHORT[]
	ProcessTokenVirtualizationEnabled, // s: ULONG
	ProcessConsoleHostProcess, // q: ULONG_PTR
	ProcessWindowInformation, // q: PROCESS_WINDOW_INFORMATION // 50
	ProcessHandleInformation, // q: PROCESS_HANDLE_SNAPSHOT_INFORMATION // since WIN8
	ProcessMitigationPolicy, // s: PROCESS_MITIGATION_POLICY_INFORMATION
	ProcessDynamicFunctionTableInformation,
	ProcessHandleCheckingMode,
	ProcessKeepAliveCount, // q: PROCESS_KEEPALIVE_COUNT_INFORMATION
	ProcessRevokeFileHandles, // s: PROCESS_REVOKE_FILE_HANDLES_INFORMATION
	ProcessWorkingSetControl, // s: PROCESS_WORKING_SET_CONTROL
	ProcessHandleTable, // since WINBLUE
	ProcessCheckStackExtentsMode,
	ProcessCommandLineInformation, // q: UNICODE_STRING // 60
	ProcessProtectionInformation, // q: PS_PROTECTION
	ProcessMemoryExhaustion, // PROCESS_MEMORY_EXHAUSTION_INFO // since THRESHOLD
	ProcessFaultInformation, // PROCESS_FAULT_INFORMATION
	ProcessTelemetryIdInformation, // PROCESS_TELEMETRY_ID_INFORMATION
	ProcessCommitReleaseInformation, // PROCESS_COMMIT_RELEASE_INFORMATION
	ProcessDefaultCpuSetsInformation,
	ProcessAllowedCpuSetsInformation,
	ProcessSubsystemProcess,
	ProcessJobMemoryInformation, // PROCESS_JOB_MEMORY_INFO
	ProcessInPrivate, // since THRESHOLD2 // 70
	ProcessRaiseUMExceptionOnInvalidHandleClose,
	ProcessIumChallengeResponse,
	ProcessChildProcessInformation, // PROCESS_CHILD_PROCESS_INFORMATION
	ProcessHighGraphicsPriorityInformation,
	MaxProcessInfoClass
} PROCESSINFOCLASS;
#endif

#ifndef KERNELMODE
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
	ThreadWow64Context, // q: WOW64_CONTEXT
	ThreadGroupInformation, // q: GROUP_AFFINITY // 30
	ThreadUmsInformation, // q: THREAD_UMS_INFORMATION
	ThreadCounterProfiling,
	ThreadIdealProcessorEx, // q: PROCESSOR_NUMBER
	ThreadCpuAccountingInformation, // since WIN8
	ThreadSuspendCount, // since WINBLUE
	ThreadHeterogeneousCpuPolicy, // q: KHETERO_CPU_POLICY // since THRESHOLD
	ThreadContainerId, // q: GUID
	ThreadNameInformation, // qs: THREAD_NAME_INFORMATION
	ThreadSelectedCpuSets,
	ThreadSystemThreadInformation, // q: SYSTEM_THREAD_INFORMATION // 40
	ThreadActualGroupAffinity, // since THRESHOLD2
	ThreadDynamicCodePolicyInfo,
	ThreadExplicitCaseSensitivity,
	ThreadWorkOnBehalfTicket,
	MaxThreadInfoClass
} THREADINFOCLASS;
#endif

#ifndef KERNELMODE
// Use with both ProcessPagePriority and ThreadPagePriority
typedef struct _PAGE_PRIORITY_INFORMATION
{
	ULONG PagePriority;
} PAGE_PRIORITY_INFORMATION, *PPAGE_PRIORITY_INFORMATION;
#endif

// Process information structures

#ifndef KERNELMODE

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
			ULONG IsPicoProcess : 1;
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

#endif

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

#ifndef KERNELMODE

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

typedef struct _PROCESS_HANDLE_TRACING_ENABLE
{
	ULONG Flags; // 0 to disable, 1 to enable
} PROCESS_HANDLE_TRACING_ENABLE, *PPROCESS_HANDLE_TRACING_ENABLE;

typedef struct _PROCESS_HANDLE_TRACING_ENABLE_EX
{
	ULONG Flags; // 0 to disable, 1 to enable
	ULONG TotalSlots;
} PROCESS_HANDLE_TRACING_ENABLE_EX, *PPROCESS_HANDLE_TRACING_ENABLE_EX;

#define PROCESS_HANDLE_TRACING_MAX_STACKS 16
#define HANDLE_TRACE_DB_OPEN 1
#define HANDLE_TRACE_DB_CLOSE 2
#define HANDLE_TRACE_DB_BADREF 3

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

#endif

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

#ifndef KERNELMODE

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
	PsProtectedSignerMax
} PS_PROTECTED_SIGNER;

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
		ULONG Spare : 31;
	};
	SIZE_T CommitDebt;
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
	BOOLEAN EnableAutomaticOverride;
} PROCESS_CHILD_PROCESS_INFORMATION, *PPROCESS_CHILD_PROCESS_INFORMATION;

// end_private

#endif

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
	ULONG Flags;
	ULONG IsUmsSchedulerThread;
	ULONG IsUmsWorkerThread;
} THREAD_UMS_INFORMATION, *PTHREAD_UMS_INFORMATION;

// private
typedef struct _THREAD_NAME_INFORMATION
{
	UNICODE_STRING ThreadName;
} THREAD_NAME_INFORMATION, *PTHREAD_NAME_INFORMATION;

// Processes

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtCreateProcess(
	_Out_ PHANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ HANDLE ParentProcess,
	_In_ BOOLEAN InheritObjectTable,
	_In_opt_ HANDLE SectionHandle,
	_In_opt_ HANDLE DebugPort,
	_In_opt_ HANDLE ExceptionPort
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateProcess(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateProcessEx(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateProcessEx(
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

NTSYSCALLAPI NTSTATUS NTAPI NtOpenProcess(
	_Out_ PHANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PCLIENT_ID ClientId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenProcess(
	_Out_ PHANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PCLIENT_ID ClientId
);

NTSYSCALLAPI NTSTATUS NTAPI NtTerminateProcess(
	_In_opt_ HANDLE ProcessHandle,
	_In_ NTSTATUS ExitStatus
);

NTSYSCALLAPI NTSTATUS NTAPI ZwTerminateProcess(
	_In_opt_ HANDLE ProcessHandle,
	_In_ NTSTATUS ExitStatus
);

NTSYSCALLAPI NTSTATUS NTAPI NtSuspendProcess(
	_In_ HANDLE ProcessHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSuspendProcess(
	_In_ HANDLE ProcessHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtResumeProcess(
	_In_ HANDLE ProcessHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwResumeProcess(
	_In_ HANDLE ProcessHandle
);

FORCEINLINE HANDLE NtCurrentProcess()
{
	return (HANDLE)(LONG_PTR)-1;
}

FORCEINLINE HANDLE ZwCurrentProcess()
{
	return (HANDLE)(LONG_PTR)-1;
}

FORCEINLINE HANDLE NtCurrentThread()
{
	return (HANDLE)(LONG_PTR)-2;
}

FORCEINLINE HANDLE ZwCurrentThread()
{
	return (HANDLE)(LONG_PTR)-2;
}

FORCEINLINE HANDLE NtCurrentSession()
{
	return (HANDLE)(LONG_PTR)-3;
}

FORCEINLINE HANDLE ZwCurrentSession()
{
	return (HANDLE)(LONG_PTR)-3;
}

FORCEINLINE PPEB NtCurrentPeb()
{
	return NtCurrentTeb()->ProcessEnvironmentBlock;
}

FORCEINLINE PPEB ZwCurrentPeb()
{
	return NtCurrentTeb()->ProcessEnvironmentBlock;
}

// Not NT, but useful.
#pragma region NotNtButUseful

FORCEINLINE DWORD NtCurrentProcessId()
{
	return HandleToUlong(NtCurrentTeb()->ClientId.UniqueProcess);
}

FORCEINLINE DWORD ZwCurrentProcessId()
{
	return HandleToUlong(NtCurrentTeb()->ClientId.UniqueProcess);
}

FORCEINLINE DWORD NtCurrentThreadId()
{
	return HandleToUlong(NtCurrentTeb()->ClientId.UniqueThread);
}

FORCEINLINE DWORD ZwCurrentThreadId()
{
	return HandleToUlong(NtCurrentTeb()->ClientId.UniqueThread);
}

#pragma endregion

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationProcess(
	_In_ HANDLE ProcessHandle,
	_In_ PROCESSINFOCLASS ProcessInformationClass,
	_Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
	_In_ ULONG ProcessInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationProcess(
	_In_ HANDLE ProcessHandle,
	_In_ PROCESSINFOCLASS ProcessInformationClass,
	_Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
	_In_ ULONG ProcessInformationLength,
	_Out_opt_ PULONG ReturnLength
);

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSCALLAPI NTSTATUS NTAPI NtGetNextProcess(
	_In_ HANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_In_ ULONG Flags,
	_Out_ PHANDLE NewProcessHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetNextProcess(
	_In_ HANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_In_ ULONG Flags,
	_Out_ PHANDLE NewProcessHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtGetNextThread(
	_In_ HANDLE ProcessHandle,
	_In_ HANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_In_ ULONG Flags,
	_Out_ PHANDLE NewThreadHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetNextThread(
	_In_ HANDLE ProcessHandle,
	_In_ HANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_In_ ULONG Flags,
	_Out_ PHANDLE NewThreadHandle
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationProcess(
	_In_ HANDLE ProcessHandle,
	_In_ PROCESSINFOCLASS ProcessInformationClass,
	_In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
	_In_ ULONG ProcessInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationProcess(
	_In_ HANDLE ProcessHandle,
	_In_ PROCESSINFOCLASS ProcessInformationClass,
	_In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
	_In_ ULONG ProcessInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryPortInformationProcess(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryPortInformationProcess(
	VOID
);

#endif

// Threads

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtCreateThread(
	_Out_ PHANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ HANDLE ProcessHandle,
	_Out_ PCLIENT_ID ClientId,
	_In_ PCONTEXT ThreadContext,
	_In_ PINITIAL_TEB InitialTeb,
	_In_ BOOLEAN CreateSuspended
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateThread(
	_Out_ PHANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ HANDLE ProcessHandle,
	_Out_ PCLIENT_ID ClientId,
	_In_ PCONTEXT ThreadContext,
	_In_ PINITIAL_TEB InitialTeb,
	_In_ BOOLEAN CreateSuspended
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenThread(
	_Out_ PHANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PCLIENT_ID ClientId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenThread(
	_Out_ PHANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PCLIENT_ID ClientId
);

NTSYSCALLAPI NTSTATUS NTAPI NtTerminateThread(
	_In_opt_ HANDLE ThreadHandle,
	_In_ NTSTATUS ExitStatus
);

NTSYSCALLAPI NTSTATUS NTAPI ZwTerminateThread(
	_In_opt_ HANDLE ThreadHandle,
	_In_ NTSTATUS ExitStatus
);

NTSYSCALLAPI NTSTATUS NTAPI NtSuspendThread(
	_In_ HANDLE ThreadHandle,
	_Out_opt_ PULONG PreviousSuspendCount
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSuspendThread(
	_In_ HANDLE ThreadHandle,
	_Out_opt_ PULONG PreviousSuspendCount
);

NTSYSCALLAPI NTSTATUS NTAPI NtResumeThread(
	_In_ HANDLE ThreadHandle,
	_Out_opt_ PULONG PreviousSuspendCount
);

NTSYSCALLAPI NTSTATUS NTAPI ZwResumeThread(
	_In_ HANDLE ThreadHandle,
	_Out_opt_ PULONG PreviousSuspendCount
);

NTSYSCALLAPI ULONG NTAPI NtGetCurrentProcessorNumber(
	VOID
);

NTSYSCALLAPI ULONG NTAPI ZwGetCurrentProcessorNumber(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI NtGetContextThread(
	_In_ HANDLE ThreadHandle,
	_Inout_ PCONTEXT ThreadContext
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetContextThread(
	_In_ HANDLE ThreadHandle,
	_Inout_ PCONTEXT ThreadContext
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetContextThread(
	_In_ HANDLE ThreadHandle,
	_In_ PCONTEXT ThreadContext
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetContextThread(
	_In_ HANDLE ThreadHandle,
	_In_ PCONTEXT ThreadContext
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationThread(
	_In_ HANDLE ThreadHandle,
	_In_ THREADINFOCLASS ThreadInformationClass,
	_Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
	_In_ ULONG ThreadInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationThread(
	_In_ HANDLE ThreadHandle,
	_In_ THREADINFOCLASS ThreadInformationClass,
	_Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
	_In_ ULONG ThreadInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationThread(
	_In_ HANDLE ThreadHandle,
	_In_ THREADINFOCLASS ThreadInformationClass,
	_In_reads_bytes_(ThreadInformationLength) PVOID ThreadInformation,
	_In_ ULONG ThreadInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationThread(
	_In_ HANDLE ThreadHandle,
	_In_ THREADINFOCLASS ThreadInformationClass,
	_In_reads_bytes_(ThreadInformationLength) PVOID ThreadInformation,
	_In_ ULONG ThreadInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlertThread(
	_In_ HANDLE ThreadHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlertThread(
	_In_ HANDLE ThreadHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlertResumeThread(
	_In_ HANDLE ThreadHandle,
	_Out_opt_ PULONG PreviousSuspendCount
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlertResumeThread(
	_In_ HANDLE ThreadHandle,
	_Out_opt_ PULONG PreviousSuspendCount
);

NTSYSCALLAPI NTSTATUS NTAPI NtTestAlert(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwTestAlert(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI NtImpersonateThread(
	_In_ HANDLE ServerThreadHandle,
	_In_ HANDLE ClientThreadHandle,
	_In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos
);

NTSYSCALLAPI NTSTATUS NTAPI ZwImpersonateThread(
	_In_ HANDLE ServerThreadHandle,
	_In_ HANDLE ClientThreadHandle,
	_In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos
);

NTSYSCALLAPI NTSTATUS NTAPI NtRegisterThreadTerminatePort(
	_In_ HANDLE PortHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRegisterThreadTerminatePort(
	_In_ HANDLE PortHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetLdtEntries(
	_In_ ULONG Selector0,
	_In_ ULONG Entry0Low,
	_In_ ULONG Entry0Hi,
	_In_ ULONG Selector1,
	_In_ ULONG Entry1Low,
	_In_ ULONG Entry1Hi
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetLdtEntries(
	_In_ ULONG Selector0,
	_In_ ULONG Entry0Low,
	_In_ ULONG Entry0Hi,
	_In_ ULONG Selector1,
	_In_ ULONG Entry1Low,
	_In_ ULONG Entry1Hi
);

typedef VOID(*PPS_APC_ROUTINE)(
	_In_opt_ PVOID ApcArgument1,
	_In_opt_ PVOID ApcArgument2,
	_In_opt_ PVOID ApcArgument3
	);

NTSYSCALLAPI NTSTATUS NTAPI NtQueueApcThread(
	_In_ HANDLE ThreadHandle,
	_In_ PPS_APC_ROUTINE ApcRoutine,
	_In_opt_ PVOID ApcArgument1,
	_In_opt_ PVOID ApcArgument2,
	_In_opt_ PVOID ApcArgument3
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueueApcThread(
	_In_ HANDLE ThreadHandle,
	_In_ PPS_APC_ROUTINE ApcRoutine,
	_In_opt_ PVOID ApcArgument1,
	_In_opt_ PVOID ApcArgument2,
	_In_opt_ PVOID ApcArgument3
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtQueueApcThreadEx(
	_In_ HANDLE ThreadHandle,
	_In_opt_ HANDLE UserApcReserveHandle,
	_In_ PPS_APC_ROUTINE ApcRoutine,
	_In_opt_ PVOID ApcArgument1,
	_In_opt_ PVOID ApcArgument2,
	_In_opt_ PVOID ApcArgument3
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueueApcThreadEx(
	_In_ HANDLE ThreadHandle,
	_In_opt_ HANDLE UserApcReserveHandle,
	_In_ PPS_APC_ROUTINE ApcRoutine,
	_In_opt_ PVOID ApcArgument1,
	_In_opt_ PVOID ApcArgument2,
	_In_opt_ PVOID ApcArgument3
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)

// rev
NTSYSCALLAPI NTSTATUS NTAPI NtAlertThreadByThreadId(
	_In_ HANDLE ThreadId
);

// rev
NTSYSCALLAPI NTSTATUS NTAPI ZwAlertThreadByThreadId(
	_In_ HANDLE ThreadId
);

// rev
NTSYSCALLAPI NTSTATUS NTAPI NtWaitForAlertByThreadId(
	_In_ PVOID Address,
	_In_opt_ PLARGE_INTEGER Timeout
);

// rev
NTSYSCALLAPI NTSTATUS NTAPI ZwWaitForAlertByThreadId(
	_In_ PVOID Address,
	_In_opt_ PLARGE_INTEGER Timeout
);

#endif

#endif

// User processes and threads

#ifndef KERNELMODE

// Attributes

// begin_rev
#define PS_ATTRIBUTE_NUMBER_MASK 0x0000ffff
#define PS_ATTRIBUTE_THREAD 0x00010000 // can be used with threads
#define PS_ATTRIBUTE_INPUT 0x00020000 // input only
#define PS_ATTRIBUTE_UNKNOWN 0x00040000
// end_rev

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
	PsAttributeProtectionLevel,
	PsAttributeSecureProcess, // since THRESHOLD
	PsAttributeJobList,
	PsAttributeChildProcessPolicy, // since THRESHOLD2
	PsAttributeAllApplicationPackagesPolicy, // since REDSTONE
	PsAttributeWin32kFilter,
	PsAttributeSafeOpenPromptOriginClaim,
	PsAttributeBnoIsolation,
	PsAttributeDesktopAppPolicy,
	PsAttributeMax
} PS_ATTRIBUTE_NUM;

// begin_rev

#define PsAttributeValue(Number, Thread, Input, Unknown) \
    (((Number) & PS_ATTRIBUTE_NUMBER_MASK) | \
    ((Thread) ? PS_ATTRIBUTE_THREAD : 0) | \
    ((Input) ? PS_ATTRIBUTE_INPUT : 0) | \
    ((Unknown) ? PS_ATTRIBUTE_UNKNOWN : 0))

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
#define PS_ATTRIBUTE_MITIGATION_OPTIONS \
    PsAttributeValue(PsAttributeMitigationOptions, FALSE, TRUE, TRUE)

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

// Extended PROCESS_CREATE_FLAGS_*
// begin_rev
#define PROCESS_CREATE_FLAGS_LARGE_PAGE_SYSTEM_DLL 0x00000020
#define PROCESS_CREATE_FLAGS_PROTECTED_PROCESS 0x00000040
#define PROCESS_CREATE_FLAGS_CREATE_SESSION 0x00000080 // ?
#define PROCESS_CREATE_FLAGS_INHERIT_FROM_PARENT 0x00000100
// end_rev

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtCreateUserProcess(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateUserProcess(
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
#define THREAD_CREATE_FLAGS_INITIAL_THREAD 0x00000080
// end_rev

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtCreateThreadEx(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateThreadEx(
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

#endif

// Job objects

#ifndef KERNELMODE

NTSYSCALLAPI NTSTATUS NTAPI NtCreateJobObject(
	_Out_ PHANDLE JobHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateJobObject(
	_Out_ PHANDLE JobHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenJobObject(
	_Out_ PHANDLE JobHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenJobObject(
	_Out_ PHANDLE JobHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtAssignProcessToJobObject(
	_In_ HANDLE JobHandle,
	_In_ HANDLE ProcessHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAssignProcessToJobObject(
	_In_ HANDLE JobHandle,
	_In_ HANDLE ProcessHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtTerminateJobObject(
	_In_ HANDLE JobHandle,
	_In_ NTSTATUS ExitStatus
);

NTSYSCALLAPI NTSTATUS NTAPI ZwTerminateJobObject(
	_In_ HANDLE JobHandle,
	_In_ NTSTATUS ExitStatus
);

NTSYSCALLAPI NTSTATUS NTAPI NtIsProcessInJob(
	_In_ HANDLE ProcessHandle,
	_In_opt_ HANDLE JobHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwIsProcessInJob(
	_In_ HANDLE ProcessHandle,
	_In_opt_ HANDLE JobHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationJobObject(
	_In_opt_ HANDLE JobHandle,
	_In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
	_Out_writes_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
	_In_ ULONG JobObjectInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationJobObject(
	_In_opt_ HANDLE JobHandle,
	_In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
	_Out_writes_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
	_In_ ULONG JobObjectInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationJobObject(
	_In_ HANDLE JobHandle,
	_In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
	_In_reads_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
	_In_ ULONG JobObjectInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationJobObject(
	_In_ HANDLE JobHandle,
	_In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
	_In_reads_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
	_In_ ULONG JobObjectInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtCreateJobSet(
	_In_ ULONG NumJob,
	_In_reads_(NumJob) PJOB_SET_ARRAY UserJobSet,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateJobSet(
	_In_ ULONG NumJob,
	_In_reads_(NumJob) PJOB_SET_ARRAY UserJobSet,
	_In_ ULONG Flags
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSCALLAPI NTSTATUS NTAPI NtRevertContainerImpersonation(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRevertContainerImpersonation(
	VOID
);
#endif

#endif

// Reserve objects

#ifndef KERNELMODE

// private
typedef enum _MEMORY_RESERVE_TYPE
{
	MemoryReserveUserApc,
	MemoryReserveIoCompletion,
	MemoryReserveTypeMax
} MEMORY_RESERVE_TYPE;

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtAllocateReserveObject(
	_Out_ PHANDLE MemoryReserveHandle,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ MEMORY_RESERVE_TYPE Type
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAllocateReserveObject(
	_Out_ PHANDLE MemoryReserveHandle,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ MEMORY_RESERVE_TYPE Type
);
#endif

#endif

#endif

#ifndef KERNELMODE
#include "cfg.h"

#ifndef _NTDBG_H
#define _NTDBG_H

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

// System calls

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
	DebugObjectFlags = 1,
	MaxDebugObjectInfoClass
} DEBUGOBJECTINFOCLASS, *PDEBUGOBJECTINFOCLASS;

NTSYSCALLAPI NTSTATUS NTAPI NtCreateDebugObject(
	_Out_ PHANDLE DebugObjectHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateDebugObject(
	_Out_ PHANDLE DebugObjectHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI NtDebugActiveProcess(
	_In_ HANDLE ProcessHandle,
	_In_ HANDLE DebugObjectHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDebugActiveProcess(
	_In_ HANDLE ProcessHandle,
	_In_ HANDLE DebugObjectHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtDebugContinue(
	_In_ HANDLE DebugObjectHandle,
	_In_ PCLIENT_ID ClientId,
	_In_ NTSTATUS ContinueStatus
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDebugContinue(
	_In_ HANDLE DebugObjectHandle,
	_In_ PCLIENT_ID ClientId,
	_In_ NTSTATUS ContinueStatus
);

NTSYSCALLAPI NTSTATUS NTAPI NtRemoveProcessDebug(
	_In_ HANDLE ProcessHandle,
	_In_ HANDLE DebugObjectHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRemoveProcessDebug(
	_In_ HANDLE ProcessHandle,
	_In_ HANDLE DebugObjectHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationDebugObject(
	_In_ HANDLE DebugObjectHandle,
	_In_ DEBUGOBJECTINFOCLASS DebugObjectInformationClass,
	_In_ PVOID DebugInformation,
	_In_ ULONG DebugInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationDebugObject(
	_In_ HANDLE DebugObjectHandle,
	_In_ DEBUGOBJECTINFOCLASS DebugObjectInformationClass,
	_In_ PVOID DebugInformation,
	_In_ ULONG DebugInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtWaitForDebugEvent(
	_In_ HANDLE DebugObjectHandle,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout,
	_Out_ PVOID WaitStateChange
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWaitForDebugEvent(
	_In_ HANDLE DebugObjectHandle,
	_In_ BOOLEAN Alertable,
	_In_opt_ PLARGE_INTEGER Timeout,
	_Out_ PVOID WaitStateChange
);

// Debugging UI

NTSYSAPI NTSTATUS NTAPI DbgUiConnectToDbg(
	VOID
);

NTSYSAPI HANDLE NTAPI DbgUiGetThreadDebugObject(
	VOID
);

NTSYSAPI VOID NTAPI DbgUiSetThreadDebugObject(
	_In_ HANDLE DebugObject
);

NTSYSAPI NTSTATUS NTAPI DbgUiWaitStateChange(
	_Out_ PDBGUI_WAIT_STATE_CHANGE StateChange,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSAPI NTSTATUS NTAPI DbgUiContinue(
	_In_ PCLIENT_ID AppClientId,
	_In_ NTSTATUS ContinueStatus
);

NTSYSAPI NTSTATUS NTAPI DbgUiStopDebugging(
	_In_ HANDLE Process
);

NTSYSAPI NTSTATUS NTAPI DbgUiDebugActiveProcess(
	_In_ HANDLE Process
);

NTSYSAPI VOID NTAPI DbgUiRemoteBreakin(
	_In_ PVOID Context
);

NTSYSAPI NTSTATUS NTAPI DbgUiIssueRemoteBreakin(
	_In_ HANDLE Process
);

struct _DEBUG_EVENT;

NTSYSAPI NTSTATUS NTAPI DbgUiConvertStateChangeStructure(
	_In_ PDBGUI_WAIT_STATE_CHANGE StateChange,
	_Out_ struct _DEBUG_EVENT *DebugEvent
);

#endif

#ifndef _NTIOAPI_H
#define _NTIOAPI_H

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

typedef VOID(NTAPI *PIO_APC_ROUTINE)(
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
	FileIoPriorityHintInformation, // FILE_IO_PRIORITY_HINT_INFORMATION
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
	FileIdExtdDirectoryInformation, // FILE_ID_EXTD_DIR_INFORMATION
	FileReplaceCompletionInformation, // FILE_COMPLETION_INFORMATION // since WINBLUE
	FileHardLinkFullIdInformation, // FILE_LINK_ENTRY_FULL_ID_INFORMATION
	FileIdExtdBothDirectoryInformation, // FILE_ID_EXTD_BOTH_DIR_INFORMATION // since THRESHOLD
	FileDispositionInformationEx, // FILE_DISPOSITION_INFO_EX // since REDSTONE
	FileRenameInformationEx,
	FileRenameInformationExBypassAccessCheck,
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
	LONGLONG ParentFileId;
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

typedef struct _FILE_IO_PRIORITY_HINT_INFORMATION
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
	UCHAR ObjectId[16];
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
	FileFsVolumeFlagsInformation, // FILE_FS_VOLUME_FLAGS_INFORMATION
	FileFsSectorSizeInformation, // FILE_FS_SECTOR_SIZE_INFORMATION // since WIN8
	FileFsDataCopyInformation, // FILE_FS_DATA_COPY_INFORMATION
	FileFsMetadataSizeInformation, // FILE_FS_METADATA_SIZE_INFORMATION // since THRESHOLD
	FileFsMaximumInformation
} FSINFOCLASS, *PFSINFOCLASS;

// NtQueryVolumeInformation/NtSetVolumeInformation types

typedef struct _FILE_FS_LABEL_INFORMATION
{
	ULONG VolumeLabelLength;
	WCHAR VolumeLabel[1];
} FILE_FS_LABEL_INFORMATION, *PFILE_FS_LABEL_INFORMATION;

typedef struct _FILE_FS_VOLUME_INFORMATION
{
	LARGE_INTEGER VolumeCreationTime;
	ULONG VolumeSerialNumber;
	ULONG VolumeLabelLength;
	BOOLEAN SupportsObjects;
	WCHAR VolumeLabel[1];
} FILE_FS_VOLUME_INFORMATION, *PFILE_FS_VOLUME_INFORMATION;

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

typedef struct _FILE_FS_FULL_SIZE_INFORMATION
{
	LARGE_INTEGER TotalAllocationUnits;
	LARGE_INTEGER CallerAvailableAllocationUnits;
	LARGE_INTEGER ActualAvailableAllocationUnits;
	ULONG SectorsPerAllocationUnit;
	ULONG BytesPerSector;
} FILE_FS_FULL_SIZE_INFORMATION, *PFILE_FS_FULL_SIZE_INFORMATION;

typedef struct _FILE_FS_OBJECTID_INFORMATION
{
	UCHAR ObjectId[16];
	UCHAR ExtendedInfo[48];
} FILE_FS_OBJECTID_INFORMATION, *PFILE_FS_OBJECTID_INFORMATION;

typedef struct _FILE_FS_DEVICE_INFORMATION
{
	DEVICE_TYPE DeviceType;
	ULONG Characteristics;
} FILE_FS_DEVICE_INFORMATION, *PFILE_FS_DEVICE_INFORMATION;

typedef struct _FILE_FS_ATTRIBUTE_INFORMATION
{
	ULONG FileSystemAttributes;
	LONG MaximumComponentNameLength;
	ULONG FileSystemNameLength;
	WCHAR FileSystemName[1];
} FILE_FS_ATTRIBUTE_INFORMATION, *PFILE_FS_ATTRIBUTE_INFORMATION;

typedef struct _FILE_FS_DRIVER_PATH_INFORMATION
{
	BOOLEAN DriverInPath;
	ULONG DriverNameLength;
	WCHAR DriverName[1];
} FILE_FS_DRIVER_PATH_INFORMATION, *PFILE_FS_DRIVER_PATH_INFORMATION;

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

typedef struct _FILE_FS_METADATA_SIZE_INFORMATION
{
	LARGE_INTEGER TotalMetadataAllocationUnits;
	ULONG SectorsPerAllocationUnit;
	ULONG BytesPerSector;
} FILE_FS_METADATA_SIZE_INFORMATION, *PFILE_FS_METADATA_SIZE_INFORMATION;

// System calls

NTSYSCALLAPI NTSTATUS NTAPI NtCreateFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateNamedPipeFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateNamedPipeFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateMailslotFile(
	_Out_ PHANDLE FileHandle,
	_In_ ULONG DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ ULONG CreateOptions,
	_In_ ULONG MailslotQuota,
	_In_ ULONG MaximumMessageSize,
	_In_ PLARGE_INTEGER ReadTimeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateMailslotFile(
	_Out_ PHANDLE FileHandle,
	_In_ ULONG DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ ULONG CreateOptions,
	_In_ ULONG MailslotQuota,
	_In_ ULONG MaximumMessageSize,
	_In_ PLARGE_INTEGER ReadTimeout
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenFile(
	_Out_ PHANDLE FileHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ ULONG ShareAccess,
	_In_ ULONG OpenOptions
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenFile(
	_Out_ PHANDLE FileHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ ULONG ShareAccess,
	_In_ ULONG OpenOptions
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteFile(
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteFile(
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtFlushBuffersFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFlushBuffersFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);

#define FLUSH_FLAGS_FILE_DATA_ONLY 0x00000001
#define FLUSH_FLAGS_NO_SYNC 0x00000002

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI NTSTATUS NTAPI NtFlushBuffersFileEx(
	_In_ HANDLE FileHandle,
	_In_ ULONG Flags,
	_In_reads_bytes_(ParametersSize) PVOID Parameters,
	_In_ ULONG ParametersSize,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFlushBuffersFileEx(
	_In_ HANDLE FileHandle,
	_In_ ULONG Flags,
	_In_reads_bytes_(ParametersSize) PVOID Parameters,
	_In_ ULONG ParametersSize,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_Out_writes_bytes_(Length) PVOID FileInformation,
	_In_ ULONG Length,
	_In_ FILE_INFORMATION_CLASS FileInformationClass
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_Out_writes_bytes_(Length) PVOID FileInformation,
	_In_ ULONG Length,
	_In_ FILE_INFORMATION_CLASS FileInformationClass
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_reads_bytes_(Length) PVOID FileInformation,
	_In_ ULONG Length,
	_In_ FILE_INFORMATION_CLASS FileInformationClass
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_reads_bytes_(Length) PVOID FileInformation,
	_In_ ULONG Length,
	_In_ FILE_INFORMATION_CLASS FileInformationClass
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryDirectoryFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryDirectoryFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtQueryEaFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryEaFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtSetEaFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_reads_bytes_(Length) PVOID Buffer,
	_In_ ULONG Length
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetEaFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_reads_bytes_(Length) PVOID Buffer,
	_In_ ULONG Length
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryQuotaInformationFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryQuotaInformationFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtSetQuotaInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_reads_bytes_(Length) PVOID Buffer,
	_In_ ULONG Length
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetQuotaInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_reads_bytes_(Length) PVOID Buffer,
	_In_ ULONG Length
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryVolumeInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_Out_writes_bytes_(Length) PVOID FsInformation,
	_In_ ULONG Length,
	_In_ FSINFOCLASS FsInformationClass
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryVolumeInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_Out_writes_bytes_(Length) PVOID FsInformation,
	_In_ ULONG Length,
	_In_ FSINFOCLASS FsInformationClass
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetVolumeInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_reads_bytes_(Length) PVOID FsInformation,
	_In_ ULONG Length,
	_In_ FSINFOCLASS FsInformationClass
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetVolumeInformationFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_reads_bytes_(Length) PVOID FsInformation,
	_In_ ULONG Length,
	_In_ FSINFOCLASS FsInformationClass
);

NTSYSCALLAPI NTSTATUS NTAPI NtCancelIoFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCancelIoFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtCancelIoFileEx(
	_In_ HANDLE FileHandle,
	_In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCancelIoFileEx(
	_In_ HANDLE FileHandle,
	_In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSCALLAPI NTSTATUS NTAPI NtCancelSynchronousIoFile(
	_In_ HANDLE ThreadHandle,
	_In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCancelSynchronousIoFile(
	_In_ HANDLE ThreadHandle,
	_In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtDeviceIoControlFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwDeviceIoControlFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtFsControlFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwFsControlFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtReadFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwReadFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtWriteFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwWriteFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtReadFileScatter(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwReadFileScatter(
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

NTSYSCALLAPI NTSTATUS NTAPI NtWriteFileGather(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwWriteFileGather(
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

NTSYSCALLAPI NTSTATUS NTAPI NtLockFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwLockFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtUnlockFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ PLARGE_INTEGER ByteOffset,
	_In_ PLARGE_INTEGER Length,
	_In_ ULONG Key
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnlockFile(
	_In_ HANDLE FileHandle,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ PLARGE_INTEGER ByteOffset,
	_In_ PLARGE_INTEGER Length,
	_In_ ULONG Key
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryAttributesFile(
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PFILE_BASIC_INFORMATION FileInformation
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryAttributesFile(
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PFILE_BASIC_INFORMATION FileInformation
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryFullAttributesFile(
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PFILE_NETWORK_OPEN_INFORMATION FileInformation
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryFullAttributesFile(
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_ PFILE_NETWORK_OPEN_INFORMATION FileInformation
);

NTSYSCALLAPI NTSTATUS NTAPI NtNotifyChangeDirectoryFile(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwNotifyChangeDirectoryFile(
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

NTSYSCALLAPI NTSTATUS NTAPI NtLoadDriver(
	_In_ PUNICODE_STRING DriverServiceName
);

NTSYSCALLAPI NTSTATUS NTAPI ZwLoadDriver(
	_In_ PUNICODE_STRING DriverServiceName
);

NTSYSCALLAPI NTSTATUS NTAPI NtUnloadDriver(
	_In_ PUNICODE_STRING DriverServiceName
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnloadDriver(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateIoCompletion(
	_Out_ PHANDLE IoCompletionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ ULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateIoCompletion(
	_Out_ PHANDLE IoCompletionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ ULONG Count
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenIoCompletion(
	_Out_ PHANDLE IoCompletionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenIoCompletion(
	_Out_ PHANDLE IoCompletionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryIoCompletion(
	_In_ HANDLE IoCompletionHandle,
	_In_ IO_COMPLETION_INFORMATION_CLASS IoCompletionInformationClass,
	_Out_writes_bytes_(IoCompletionInformation) PVOID IoCompletionInformation,
	_In_ ULONG IoCompletionInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryIoCompletion(
	_In_ HANDLE IoCompletionHandle,
	_In_ IO_COMPLETION_INFORMATION_CLASS IoCompletionInformationClass,
	_Out_writes_bytes_(IoCompletionInformation) PVOID IoCompletionInformation,
	_In_ ULONG IoCompletionInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetIoCompletion(
	_In_ HANDLE IoCompletionHandle,
	_In_opt_ PVOID KeyContext,
	_In_opt_ PVOID ApcContext,
	_In_ NTSTATUS IoStatus,
	_In_ ULONG_PTR IoStatusInformation
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetIoCompletion(
	_In_ HANDLE IoCompletionHandle,
	_In_opt_ PVOID KeyContext,
	_In_opt_ PVOID ApcContext,
	_In_ NTSTATUS IoStatus,
	_In_ ULONG_PTR IoStatusInformation
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtSetIoCompletionEx(
	_In_ HANDLE IoCompletionHandle,
	_In_ HANDLE IoCompletionPacketHandle,
	_In_opt_ PVOID KeyContext,
	_In_opt_ PVOID ApcContext,
	_In_ NTSTATUS IoStatus,
	_In_ ULONG_PTR IoStatusInformation
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetIoCompletionEx(
	_In_ HANDLE IoCompletionHandle,
	_In_ HANDLE IoCompletionPacketHandle,
	_In_opt_ PVOID KeyContext,
	_In_opt_ PVOID ApcContext,
	_In_ NTSTATUS IoStatus,
	_In_ ULONG_PTR IoStatusInformation
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtRemoveIoCompletion(
	_In_ HANDLE IoCompletionHandle,
	_Out_ PVOID *KeyContext,
	_Out_ PVOID *ApcContext,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRemoveIoCompletion(
	_In_ HANDLE IoCompletionHandle,
	_Out_ PVOID *KeyContext,
	_Out_ PVOID *ApcContext,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_opt_ PLARGE_INTEGER Timeout
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtRemoveIoCompletionEx(
	_In_ HANDLE IoCompletionHandle,
	_Out_writes_to_(Count, *NumEntriesRemoved) PFILE_IO_COMPLETION_INFORMATION IoCompletionInformation,
	_In_ ULONG Count,
	_Out_ PULONG NumEntriesRemoved,
	_In_opt_ PLARGE_INTEGER Timeout,
	_In_ BOOLEAN Alertable
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRemoveIoCompletionEx(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateWaitCompletionPacket(
	_Out_ PHANDLE WaitCompletionPacketHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateWaitCompletionPacket(
	_Out_ PHANDLE WaitCompletionPacketHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtAssociateWaitCompletionPacket(
	_In_ HANDLE WaitCompletionPacketHandle,
	_In_ HANDLE IoCompletionHandle,
	_In_ HANDLE TargetObjectHandle,
	_In_opt_ PVOID KeyContext,
	_In_opt_ PVOID ApcContext,
	_In_ NTSTATUS IoStatus,
	_In_ ULONG_PTR IoStatusInformation,
	_Out_opt_ PBOOLEAN AlreadySignaled
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAssociateWaitCompletionPacket(
	_In_ HANDLE WaitCompletionPacketHandle,
	_In_ HANDLE IoCompletionHandle,
	_In_ HANDLE TargetObjectHandle,
	_In_opt_ PVOID KeyContext,
	_In_opt_ PVOID ApcContext,
	_In_ NTSTATUS IoStatus,
	_In_ ULONG_PTR IoStatusInformation,
	_Out_opt_ PBOOLEAN AlreadySignaled
);

NTSYSCALLAPI NTSTATUS NTAPI NtCancelWaitCompletionPacket(
	_In_ HANDLE WaitCompletionPacketHandle,
	_In_ BOOLEAN RemoveSignaledPacket
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCancelWaitCompletionPacket(
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

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtNotifyChangeSession(
	_In_ HANDLE SessionHandle,
	_In_ ULONG ChangeSequenceNumber,
	_In_ PLARGE_INTEGER ChangeTimeStamp,
	_In_ IO_SESSION_EVENT Event,
	_In_ IO_SESSION_STATE NewState,
	_In_ IO_SESSION_STATE PreviousState,
	_In_reads_bytes_opt_(PayloadSize) PVOID Payload,
	_In_ ULONG PayloadSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwNotifyChangeSession(
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

#endif

#ifndef _NTLPCAPI_H
#define _NTLPCAPI_H

// Local Inter-process Communication

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

NTSYSCALLAPI NTSTATUS NTAPI NtCreatePort(
	_Out_ PHANDLE PortHandle,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG MaxConnectionInfoLength,
	_In_ ULONG MaxMessageLength,
	_In_opt_ ULONG MaxPoolUsage
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreatePort(
	_Out_ PHANDLE PortHandle,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG MaxConnectionInfoLength,
	_In_ ULONG MaxMessageLength,
	_In_opt_ ULONG MaxPoolUsage
);

NTSYSCALLAPI NTSTATUS NTAPI NtCreateWaitablePort(
	_Out_ PHANDLE PortHandle,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG MaxConnectionInfoLength,
	_In_ ULONG MaxMessageLength,
	_In_opt_ ULONG MaxPoolUsage
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateWaitablePort(
	_Out_ PHANDLE PortHandle,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG MaxConnectionInfoLength,
	_In_ ULONG MaxMessageLength,
	_In_opt_ ULONG MaxPoolUsage
);

// Port connection (client)

NTSYSCALLAPI NTSTATUS NTAPI NtConnectPort(
	_Out_ PHANDLE PortHandle,
	_In_ PUNICODE_STRING PortName,
	_In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
	_Inout_opt_ PPORT_VIEW ClientView,
	_Inout_opt_ PREMOTE_PORT_VIEW ServerView,
	_Out_opt_ PULONG MaxMessageLength,
	_Inout_updates_bytes_to_opt_(*ConnectionInformationLength, *ConnectionInformationLength) PVOID ConnectionInformation,
	_Inout_opt_ PULONG ConnectionInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwConnectPort(
	_Out_ PHANDLE PortHandle,
	_In_ PUNICODE_STRING PortName,
	_In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
	_Inout_opt_ PPORT_VIEW ClientView,
	_Inout_opt_ PREMOTE_PORT_VIEW ServerView,
	_Out_opt_ PULONG MaxMessageLength,
	_Inout_updates_bytes_to_opt_(*ConnectionInformationLength, *ConnectionInformationLength) PVOID ConnectionInformation,
	_Inout_opt_ PULONG ConnectionInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSecureConnectPort(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwSecureConnectPort(
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

NTSYSCALLAPI NTSTATUS NTAPI NtListenPort(
	_In_ HANDLE PortHandle,
	_Out_ PPORT_MESSAGE ConnectionRequest
);

NTSYSCALLAPI NTSTATUS NTAPI ZwListenPort(
	_In_ HANDLE PortHandle,
	_Out_ PPORT_MESSAGE ConnectionRequest
);

NTSYSCALLAPI NTSTATUS NTAPI NtAcceptConnectPort(
	_Out_ PHANDLE PortHandle,
	_In_opt_ PVOID PortContext,
	_In_ PPORT_MESSAGE ConnectionRequest,
	_In_ BOOLEAN AcceptConnection,
	_Inout_opt_ PPORT_VIEW ServerView,
	_Out_opt_ PREMOTE_PORT_VIEW ClientView
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAcceptConnectPort(
	_Out_ PHANDLE PortHandle,
	_In_opt_ PVOID PortContext,
	_In_ PPORT_MESSAGE ConnectionRequest,
	_In_ BOOLEAN AcceptConnection,
	_Inout_opt_ PPORT_VIEW ServerView,
	_Out_opt_ PREMOTE_PORT_VIEW ClientView
);

NTSYSCALLAPI NTSTATUS NTAPI NtCompleteConnectPort(
	_In_ HANDLE PortHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCompleteConnectPort(
	_In_ HANDLE PortHandle
);

// General

NTSYSCALLAPI NTSTATUS NTAPI NtRequestPort(
	_In_ HANDLE PortHandle,
	_In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRequestPort(
	_In_ HANDLE PortHandle,
	_In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage
);

NTSYSCALLAPI NTSTATUS NTAPI NtRequestWaitReplyPort(
	_In_ HANDLE PortHandle,
	_In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage,
	_Out_ PPORT_MESSAGE ReplyMessage
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRequestWaitReplyPort(
	_In_ HANDLE PortHandle,
	_In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage,
	_Out_ PPORT_MESSAGE ReplyMessage
);

NTSYSCALLAPI NTSTATUS NTAPI NtReplyPort(
	_In_ HANDLE PortHandle,
	_In_reads_bytes_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReplyPort(
	_In_ HANDLE PortHandle,
	_In_reads_bytes_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage
);

NTSYSCALLAPI NTSTATUS NTAPI NtReplyWaitReplyPort(
	_In_ HANDLE PortHandle,
	_Inout_ PPORT_MESSAGE ReplyMessage
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReplyWaitReplyPort(
	_In_ HANDLE PortHandle,
	_Inout_ PPORT_MESSAGE ReplyMessage
);

NTSYSCALLAPI NTSTATUS NTAPI NtReplyWaitReceivePort(
	_In_ HANDLE PortHandle,
	_Out_opt_ PVOID *PortContext,
	_In_reads_bytes_opt_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage,
	_Out_ PPORT_MESSAGE ReceiveMessage
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReplyWaitReceivePort(
	_In_ HANDLE PortHandle,
	_Out_opt_ PVOID *PortContext,
	_In_reads_bytes_opt_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage,
	_Out_ PPORT_MESSAGE ReceiveMessage
);

NTSYSCALLAPI NTSTATUS NTAPI NtReplyWaitReceivePortEx(
	_In_ HANDLE PortHandle,
	_Out_opt_ PVOID *PortContext,
	_In_reads_bytes_opt_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage,
	_Out_ PPORT_MESSAGE ReceiveMessage,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReplyWaitReceivePortEx(
	_In_ HANDLE PortHandle,
	_Out_opt_ PVOID *PortContext,
	_In_reads_bytes_opt_(ReplyMessage->u1.s1.TotalLength) PPORT_MESSAGE ReplyMessage,
	_Out_ PPORT_MESSAGE ReceiveMessage,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI NtImpersonateClientOfPort(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message
);

NTSYSCALLAPI NTSTATUS NTAPI ZwImpersonateClientOfPort(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message
);

NTSYSCALLAPI NTSTATUS NTAPI NtReadRequestData(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message,
	_In_ ULONG DataEntryIndex,
	_Out_writes_bytes_to_(BufferSize, *NumberOfBytesRead) PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesRead
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReadRequestData(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message,
	_In_ ULONG DataEntryIndex,
	_Out_writes_bytes_to_(BufferSize, *NumberOfBytesRead) PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesRead
);

NTSYSCALLAPI NTSTATUS NTAPI NtWriteRequestData(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message,
	_In_ ULONG DataEntryIndex,
	_In_reads_bytes_(BufferSize) PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesWritten
);

NTSYSCALLAPI NTSTATUS NTAPI ZwWriteRequestData(
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

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationPort(
	_In_ HANDLE PortHandle,
	_In_ PORT_INFORMATION_CLASS PortInformationClass,
	_Out_writes_bytes_to_(Length, *ReturnLength) PVOID PortInformation,
	_In_ ULONG Length,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationPort(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcCreatePort(
	_Out_ PHANDLE PortHandle,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcCreatePort(
	_Out_ PHANDLE PortHandle,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcDisconnectPort(
	_In_ HANDLE PortHandle,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcDisconnectPort(
	_In_ HANDLE PortHandle,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcQueryInformation(
	_In_opt_ HANDLE PortHandle,
	_In_ ALPC_PORT_INFORMATION_CLASS PortInformationClass,
	_Inout_updates_bytes_to_(Length, *ReturnLength) PVOID PortInformation,
	_In_ ULONG Length,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcQueryInformation(
	_In_opt_ HANDLE PortHandle,
	_In_ ALPC_PORT_INFORMATION_CLASS PortInformationClass,
	_Inout_updates_bytes_to_(Length, *ReturnLength) PVOID PortInformation,
	_In_ ULONG Length,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcSetInformation(
	_In_ HANDLE PortHandle,
	_In_ ALPC_PORT_INFORMATION_CLASS PortInformationClass,
	_In_reads_bytes_opt_(Length) PVOID PortInformation,
	_In_ ULONG Length
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcSetInformation(
	_In_ HANDLE PortHandle,
	_In_ ALPC_PORT_INFORMATION_CLASS PortInformationClass,
	_In_reads_bytes_opt_(Length) PVOID PortInformation,
	_In_ ULONG Length
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcCreatePortSection(
	_In_ HANDLE PortHandle,
	_In_ ULONG Flags,
	_In_opt_ HANDLE SectionHandle,
	_In_ SIZE_T SectionSize,
	_Out_ PALPC_HANDLE AlpcSectionHandle,
	_Out_ PSIZE_T ActualSectionSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcCreatePortSection(
	_In_ HANDLE PortHandle,
	_In_ ULONG Flags,
	_In_opt_ HANDLE SectionHandle,
	_In_ SIZE_T SectionSize,
	_Out_ PALPC_HANDLE AlpcSectionHandle,
	_Out_ PSIZE_T ActualSectionSize
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcDeletePortSection(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ ALPC_HANDLE SectionHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcDeletePortSection(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ ALPC_HANDLE SectionHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcCreateResourceReserve(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ SIZE_T MessageSize,
	_Out_ PALPC_HANDLE ResourceId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcCreateResourceReserve(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ SIZE_T MessageSize,
	_Out_ PALPC_HANDLE ResourceId
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcDeleteResourceReserve(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ ALPC_HANDLE ResourceId
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcDeleteResourceReserve(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ ALPC_HANDLE ResourceId
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcCreateSectionView(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_Inout_ PALPC_DATA_VIEW_ATTR ViewAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcCreateSectionView(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_Inout_ PALPC_DATA_VIEW_ATTR ViewAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcDeleteSectionView(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ PVOID ViewBase
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcDeleteSectionView(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ PVOID ViewBase
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcCreateSecurityContext(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_Inout_ PALPC_SECURITY_ATTR SecurityAttribute
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcCreateSecurityContext(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_Inout_ PALPC_SECURITY_ATTR SecurityAttribute
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcDeleteSecurityContext(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ ALPC_HANDLE ContextHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcDeleteSecurityContext(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ ALPC_HANDLE ContextHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcRevokeSecurityContext(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ ALPC_HANDLE ContextHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcRevokeSecurityContext(
	_In_ HANDLE PortHandle,
	_Reserved_ ULONG Flags,
	_In_ ALPC_HANDLE ContextHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcQueryInformationMessage(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE PortMessage,
	_In_ ALPC_MESSAGE_INFORMATION_CLASS MessageInformationClass,
	_Out_writes_bytes_to_opt_(Length, *ReturnLength) PVOID MessageInformation,
	_In_ ULONG Length,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcQueryInformationMessage(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcConnectPort(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcConnectPort(
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
NTSYSCALLAPI NTSTATUS NTAPI NtAlpcConnectPortEx(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcConnectPortEx(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcAcceptConnectPort(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcAcceptConnectPort(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcSendWaitReceivePort(
	_In_ HANDLE PortHandle,
	_In_ ULONG Flags,
	_In_reads_bytes_opt_(SendMessage->u1.s1.TotalLength) PPORT_MESSAGE SendMessage,
	_Inout_opt_ PALPC_MESSAGE_ATTRIBUTES SendMessageAttributes,
	_Out_writes_bytes_to_opt_(*BufferLength, *BufferLength) PPORT_MESSAGE ReceiveMessage,
	_Inout_opt_ PSIZE_T BufferLength,
	_Inout_opt_ PALPC_MESSAGE_ATTRIBUTES ReceiveMessageAttributes,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcSendWaitReceivePort(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcCancelMessage(
	_In_ HANDLE PortHandle,
	_In_ ULONG Flags,
	_In_ PALPC_CONTEXT_ATTR MessageContext
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcCancelMessage(
	_In_ HANDLE PortHandle,
	_In_ ULONG Flags,
	_In_ PALPC_CONTEXT_ATTR MessageContext
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcImpersonateClientOfPort(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message,
	_In_ PVOID Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcImpersonateClientOfPort(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message,
	_In_ PVOID Flags
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSCALLAPI NTSTATUS NTAPI NtAlpcImpersonateClientContainerOfPort(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcImpersonateClientContainerOfPort(
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE Message,
	_In_ ULONG Flags
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcOpenSenderProcess(
	_Out_ PHANDLE ProcessHandle,
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE PortMessage,
	_In_ ULONG Flags,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcOpenSenderProcess(
	_Out_ PHANDLE ProcessHandle,
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE PortMessage,
	_In_ ULONG Flags,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtAlpcOpenSenderThread(
	_Out_ PHANDLE ThreadHandle,
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE PortMessage,
	_In_ ULONG Flags,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAlpcOpenSenderThread(
	_Out_ PHANDLE ThreadHandle,
	_In_ HANDLE PortHandle,
	_In_ PPORT_MESSAGE PortMessage,
	_In_ ULONG Flags,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

// Support functions

NTSYSAPI ULONG NTAPI AlpcMaxAllowedMessageLength(
	VOID
);

NTSYSAPI ULONG NTAPI AlpcGetHeaderSize(
	_In_ ULONG Flags
);

NTSYSAPI NTSTATUS NTAPI AlpcInitializeMessageAttribute(
	_In_ ULONG AttributeFlags,
	_Out_opt_ PALPC_MESSAGE_ATTRIBUTES Buffer,
	_In_ ULONG BufferSize,
	_Out_ PULONG RequiredBufferSize
);

NTSYSAPI PVOID NTAPI AlpcGetMessageAttribute(
	_In_ PALPC_MESSAGE_ATTRIBUTES Buffer,
	_In_ ULONG AttributeFlag
);

NTSYSAPI NTSTATUS NTAPI AlpcRegisterCompletionList(
	_In_ HANDLE PortHandle,
	_Out_ PALPC_COMPLETION_LIST_HEADER Buffer,
	_In_ ULONG Size,
	_In_ ULONG ConcurrencyCount,
	_In_ ULONG AttributeFlags
);

NTSYSAPI NTSTATUS NTAPI AlpcUnregisterCompletionList(
	_In_ HANDLE PortHandle
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI AlpcRundownCompletionList(
	_In_ HANDLE PortHandle
);
#endif

NTSYSAPI NTSTATUS NTAPI AlpcAdjustCompletionListConcurrencyCount(
	_In_ HANDLE PortHandle,
	_In_ ULONG ConcurrencyCount
);

NTSYSAPI BOOLEAN NTAPI AlpcRegisterCompletionListWorkerThread(
	_Inout_ PVOID CompletionList
);

NTSYSAPI BOOLEAN NTAPI AlpcUnregisterCompletionListWorkerThread(
	_Inout_ PVOID CompletionList
);

NTSYSAPI VOID NTAPI AlpcGetCompletionListLastMessageInformation(
	_In_ PVOID CompletionList,
	_Out_ PULONG LastMessageId,
	_Out_ PULONG LastCallbackId
);

NTSYSAPI ULONG NTAPI AlpcGetOutstandingCompletionListMessageCount(
	_In_ PVOID CompletionList
);

NTSYSAPI
PPORT_MESSAGE
NTAPI
AlpcGetMessageFromCompletionList(
	_In_ PVOID CompletionList,
	_Out_opt_ PALPC_MESSAGE_ATTRIBUTES *MessageAttributes
);

NTSYSAPI VOID NTAPI AlpcFreeCompletionListMessage(
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

#endif

#ifndef _NTPFAPI_H
#define _NTPFAPI_H

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
} PF_PRIVSOURCE_INFO, *PPF_PRIVSOURCE_INFO;

#define PF_PRIVSOURCE_QUERY_REQUEST_VERSION 3

typedef struct _PF_PRIVSOURCE_QUERY_REQUEST
{
	ULONG Version;
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

#define PF_PHYSICAL_MEMORY_RANGE_INFO_VERSION 1

typedef struct _PF_PHYSICAL_MEMORY_RANGE_INFO
{
	ULONG Version;
	ULONG RangeCount;
	PF_PHYSICAL_MEMORY_RANGE Ranges[1];
} PF_PHYSICAL_MEMORY_RANGE_INFO, *PPF_PHYSICAL_MEMORY_RANGE_INFO;

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

#endif

#ifndef _NTPNPAPI_H
#define _NTPNPAPI_H

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
	PlugPlayControlEnumerateDevice,
	PlugPlayControlRegisterNewDevice,
	PlugPlayControlDeregisterDevice,
	PlugPlayControlInitializeDevice,
	PlugPlayControlStartDevice,
	PlugPlayControlUnlockDevice,
	PlugPlayControlQueryAndRemoveDevice,
	PlugPlayControlUserResponse,
	PlugPlayControlGenerateLegacyDevice,
	PlugPlayControlGetInterfaceDeviceList,
	PlugPlayControlProperty,
	PlugPlayControlDeviceClassAssociation,
	PlugPlayControlGetRelatedDevice,
	PlugPlayControlGetInterfaceDeviceAlias,
	PlugPlayControlDeviceStatus,
	PlugPlayControlGetDeviceDepth,
	PlugPlayControlQueryDeviceRelations,
	PlugPlayControlTargetDeviceRelation,
	PlugPlayControlQueryConflictList,
	PlugPlayControlRetrieveDock,
	PlugPlayControlResetDevice,
	PlugPlayControlHaltDevice,
	PlugPlayControlGetBlockedDriverList,
	PlugPlayControlGetDeviceInterfaceEnabled,
	MaxPlugPlayControl
} PLUGPLAY_CONTROL_CLASS, *PPLUGPLAY_CONTROL_CLASS;

#if (NTDDI_VERSION < NTDDI_WIN8)
NTSYSCALLAPI NTSTATUS NTAPI NtGetPlugPlayEvent(
	_In_ HANDLE EventHandle,
	_In_opt_ PVOID Context,
	_Out_writes_bytes_(EventBufferSize) PPLUGPLAY_EVENT_BLOCK EventBlock,
	_In_ ULONG EventBufferSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetPlugPlayEvent(
	_In_ HANDLE EventHandle,
	_In_opt_ PVOID Context,
	_Out_writes_bytes_(EventBufferSize) PPLUGPLAY_EVENT_BLOCK EventBlock,
	_In_ ULONG EventBufferSize
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtPlugPlayControl(
	_In_ PLUGPLAY_CONTROL_CLASS PnPControlClass,
	_Inout_updates_bytes_(PnPControlDataLength) PVOID PnPControlData,
	_In_ ULONG PnPControlDataLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPlugPlayControl(
	_In_ PLUGPLAY_CONTROL_CLASS PnPControlClass,
	_Inout_updates_bytes_(PnPControlDataLength) PVOID PnPControlData,
	_In_ ULONG PnPControlDataLength
);

#if (NTDDI_VERSION >= NTDDI_WIN7)

NTSYSCALLAPI NTSTATUS NTAPI NtSerializeBoot(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSerializeBoot(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI NtEnableLastKnownGood(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwEnableLastKnownGood(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI NtDisableLastKnownGood(
	VOID
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDisableLastKnownGood(
	VOID
);

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtReplacePartitionUnit(
	_In_ PUNICODE_STRING TargetInstancePath,
	_In_ PUNICODE_STRING SpareInstancePath,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReplacePartitionUnit(
	_In_ PUNICODE_STRING TargetInstancePath,
	_In_ PUNICODE_STRING SpareInstancePath,
	_In_ ULONG Flags
);
#endif

#endif

#ifndef _NTPOAPI_H
#define _NTPOAPI_H

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

typedef enum
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

typedef NTSTATUS(NTAPI *PENTER_STATE_SYSTEM_HANDLER)(
	_In_ PVOID SystemContext
	);

typedef NTSTATUS(NTAPI *PENTER_STATE_HANDLER)(
	_In_ PVOID Context,
	_In_opt_ PENTER_STATE_SYSTEM_HANDLER SystemHandler,
	_In_ PVOID SystemContext,
	_In_ LONG NumberProcessors,
	_In_ volatile PLONG Number
	);

typedef struct _POWER_STATE_HANDLER
{
	POWER_STATE_HANDLER_TYPE Type;
	BOOLEAN RtcWake;
	UCHAR Spare[3];
	PENTER_STATE_HANDLER Handler;
	PVOID Context;
} POWER_STATE_HANDLER, *PPOWER_STATE_HANDLER;

typedef NTSTATUS(NTAPI *PENTER_STATE_NOTIFY_HANDLER)(
	_In_ POWER_STATE_HANDLER_TYPE State,
	_In_ PVOID Context,
	_In_ BOOLEAN Entering
	);

typedef struct _POWER_STATE_NOTIFY_HANDLER
{
	PENTER_STATE_NOTIFY_HANDLER Handler;
	PVOID Context;
} POWER_STATE_NOTIFY_HANDLER, *PPOWER_STATE_NOTIFY_HANDLER;

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

NTSYSCALLAPI NTSTATUS NTAPI NtPowerInformation(
	_In_ POWER_INFORMATION_LEVEL InformationLevel,
	_In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
	_In_ ULONG InputBufferLength,
	_Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
	_In_ ULONG OutputBufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPowerInformation(
	_In_ POWER_INFORMATION_LEVEL InformationLevel,
	_In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
	_In_ ULONG InputBufferLength,
	_Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
	_In_ ULONG OutputBufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetThreadExecutionState(
	_In_ EXECUTION_STATE NewFlags, // ES_* flags
	_Out_ EXECUTION_STATE *PreviousFlags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetThreadExecutionState(
	_In_ EXECUTION_STATE NewFlags, // ES_* flags
	_Out_ EXECUTION_STATE *PreviousFlags
);

NTSYSCALLAPI NTSTATUS NTAPI NtRequestWakeupLatency(
	_In_ LATENCY_TIME latency
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRequestWakeupLatency(
	_In_ LATENCY_TIME latency
);

NTSYSCALLAPI NTSTATUS NTAPI NtInitiatePowerAction(
	_In_ POWER_ACTION SystemAction,
	_In_ SYSTEM_POWER_STATE LightestSystemState,
	_In_ ULONG Flags, // POWER_ACTION_* flags
	_In_ BOOLEAN Asynchronous
);

NTSYSCALLAPI NTSTATUS NTAPI ZwInitiatePowerAction(
	_In_ POWER_ACTION SystemAction,
	_In_ SYSTEM_POWER_STATE LightestSystemState,
	_In_ ULONG Flags, // POWER_ACTION_* flags
	_In_ BOOLEAN Asynchronous
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetSystemPowerState(
	_In_ POWER_ACTION SystemAction,
	_In_ SYSTEM_POWER_STATE LightestSystemState,
	_In_ ULONG Flags // POWER_ACTION_* flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetSystemPowerState(
	_In_ POWER_ACTION SystemAction,
	_In_ SYSTEM_POWER_STATE LightestSystemState,
	_In_ ULONG Flags // POWER_ACTION_* flags
);

NTSYSCALLAPI NTSTATUS NTAPI NtGetDevicePowerState(
	_In_ HANDLE Device,
	_Out_ PDEVICE_POWER_STATE State
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetDevicePowerState(
	_In_ HANDLE Device,
	_Out_ PDEVICE_POWER_STATE State
);

NTSYSCALLAPI BOOLEAN NTAPI NtIsSystemResumeAutomatic(
	VOID
);

NTSYSCALLAPI BOOLEAN NTAPI ZwIsSystemResumeAutomatic(
	VOID
);

#endif

#ifndef _NTREGAPI_H
#define _NTREGAPI_H

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
	HANDLE PID;
	UNICODE_STRING KeyName;
} KEY_PID_ARRAY, *PKEY_PID_ARRAY;

typedef struct _KEY_OPEN_SUBKEYS_INFORMATION
{
	ULONG Count;
	KEY_PID_ARRAY KeyArray[1];
} KEY_OPEN_SUBKEYS_INFORMATION, *PKEY_OPEN_SUBKEYS_INFORMATION;

// System calls

NTSYSCALLAPI NTSTATUS NTAPI NtCreateKey(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Reserved_ ULONG TitleIndex,
	_In_opt_ PUNICODE_STRING Class,
	_In_ ULONG CreateOptions,
	_Out_opt_ PULONG Disposition
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateKey(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Reserved_ ULONG TitleIndex,
	_In_opt_ PUNICODE_STRING Class,
	_In_ ULONG CreateOptions,
	_Out_opt_ PULONG Disposition
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtCreateKeyTransacted(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_Reserved_ ULONG TitleIndex,
	_In_opt_ PUNICODE_STRING Class,
	_In_ ULONG CreateOptions,
	_In_ HANDLE TransactionHandle,
	_Out_opt_ PULONG Disposition
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateKeyTransacted(
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

NTSYSCALLAPI NTSTATUS NTAPI NtOpenKey(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenKey(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtOpenKeyTransacted(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ HANDLE TransactionHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenKeyTransacted(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ HANDLE TransactionHandle
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSCALLAPI NTSTATUS NTAPI NtOpenKeyEx(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG OpenOptions
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenKeyEx(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG OpenOptions
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenKeyTransactedEx(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG OpenOptions,
	_In_ HANDLE TransactionHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenKeyTransactedEx(
	_Out_ PHANDLE KeyHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG OpenOptions,
	_In_ HANDLE TransactionHandle
);
#endif

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteKey(
	_In_ HANDLE KeyHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteKey(
	_In_ HANDLE KeyHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtRenameKey(
	_In_ HANDLE KeyHandle,
	_In_ PUNICODE_STRING NewName
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRenameKey(
	_In_ HANDLE KeyHandle,
	_In_ PUNICODE_STRING NewName
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteValueKey(
	_In_ HANDLE KeyHandle,
	_In_ PUNICODE_STRING ValueName
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteValueKey(
	_In_ HANDLE KeyHandle,
	_In_ PUNICODE_STRING ValueName
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryKey(
	_In_ HANDLE KeyHandle,
	_In_ KEY_INFORMATION_CLASS KeyInformationClass,
	_Out_writes_bytes_opt_(Length) PVOID KeyInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryKey(
	_In_ HANDLE KeyHandle,
	_In_ KEY_INFORMATION_CLASS KeyInformationClass,
	_Out_writes_bytes_opt_(Length) PVOID KeyInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationKey(
	_In_ HANDLE KeyHandle,
	_In_ KEY_SET_INFORMATION_CLASS KeySetInformationClass,
	_In_reads_bytes_(KeySetInformationLength) PVOID KeySetInformation,
	_In_ ULONG KeySetInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationKey(
	_In_ HANDLE KeyHandle,
	_In_ KEY_SET_INFORMATION_CLASS KeySetInformationClass,
	_In_reads_bytes_(KeySetInformationLength) PVOID KeySetInformation,
	_In_ ULONG KeySetInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryValueKey(
	_In_ HANDLE KeyHandle,
	_In_ PUNICODE_STRING ValueName,
	_In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
	_Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryValueKey(
	_In_ HANDLE KeyHandle,
	_In_ PUNICODE_STRING ValueName,
	_In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
	_Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetValueKey(
	_In_ HANDLE KeyHandle,
	_In_ PUNICODE_STRING ValueName,
	_In_opt_ ULONG TitleIndex,
	_In_ ULONG Type,
	_In_reads_bytes_opt_(DataSize) PVOID Data,
	_In_ ULONG DataSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetValueKey(
	_In_ HANDLE KeyHandle,
	_In_ PUNICODE_STRING ValueName,
	_In_opt_ ULONG TitleIndex,
	_In_ ULONG Type,
	_In_reads_bytes_opt_(DataSize) PVOID Data,
	_In_ ULONG DataSize
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryMultipleValueKey(
	_In_ HANDLE KeyHandle,
	_Inout_updates_(EntryCount) PKEY_VALUE_ENTRY ValueEntries,
	_In_ ULONG EntryCount,
	_Out_writes_bytes_(*BufferLength) PVOID ValueBuffer,
	_Inout_ PULONG BufferLength,
	_Out_opt_ PULONG RequiredBufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryMultipleValueKey(
	_In_ HANDLE KeyHandle,
	_Inout_updates_(EntryCount) PKEY_VALUE_ENTRY ValueEntries,
	_In_ ULONG EntryCount,
	_Out_writes_bytes_(*BufferLength) PVOID ValueBuffer,
	_Inout_ PULONG BufferLength,
	_Out_opt_ PULONG RequiredBufferLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtEnumerateKey(
	_In_ HANDLE KeyHandle,
	_In_ ULONG Index,
	_In_ KEY_INFORMATION_CLASS KeyInformationClass,
	_Out_writes_bytes_opt_(Length) PVOID KeyInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwEnumerateKey(
	_In_ HANDLE KeyHandle,
	_In_ ULONG Index,
	_In_ KEY_INFORMATION_CLASS KeyInformationClass,
	_Out_writes_bytes_opt_(Length) PVOID KeyInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtEnumerateValueKey(
	_In_ HANDLE KeyHandle,
	_In_ ULONG Index,
	_In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
	_Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwEnumerateValueKey(
	_In_ HANDLE KeyHandle,
	_In_ ULONG Index,
	_In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
	_Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtFlushKey(
	_In_ HANDLE KeyHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFlushKey(
	_In_ HANDLE KeyHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtCompactKeys(
	_In_ ULONG Count,
	_In_reads_(Count) HANDLE KeyArray[]
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCompactKeys(
	_In_ ULONG Count,
	_In_reads_(Count) HANDLE KeyArray[]
);

NTSYSCALLAPI NTSTATUS NTAPI NtCompressKey(
	_In_ HANDLE Key
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCompressKey(
	_In_ HANDLE Key
);

NTSYSCALLAPI NTSTATUS NTAPI NtLoadKey(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ POBJECT_ATTRIBUTES SourceFile
);

NTSYSCALLAPI NTSTATUS NTAPI ZwLoadKey(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ POBJECT_ATTRIBUTES SourceFile
);

NTSYSCALLAPI NTSTATUS NTAPI NtLoadKey2(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ POBJECT_ATTRIBUTES SourceFile,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwLoadKey2(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ POBJECT_ATTRIBUTES SourceFile,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI NtLoadKeyEx(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ POBJECT_ATTRIBUTES SourceFile,
	_In_ ULONG Flags,
	_In_opt_ HANDLE TrustClassKey,
	_In_opt_ HANDLE Event,
	_In_opt_ ACCESS_MASK DesiredAccess,
	_Out_opt_ PHANDLE RootHandle,
	_Out_opt_ PIO_STATUS_BLOCK IoStatus
);

NTSYSCALLAPI NTSTATUS NTAPI ZwLoadKeyEx(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ POBJECT_ATTRIBUTES SourceFile,
	_In_ ULONG Flags,
	_In_opt_ HANDLE TrustClassKey,
	_In_opt_ HANDLE Event,
	_In_opt_ ACCESS_MASK DesiredAccess,
	_Out_opt_ PHANDLE RootHandle,
	_Out_opt_ PIO_STATUS_BLOCK IoStatus
);

NTSYSCALLAPI NTSTATUS NTAPI NtReplaceKey(
	_In_ POBJECT_ATTRIBUTES NewFile,
	_In_ HANDLE TargetHandle,
	_In_ POBJECT_ATTRIBUTES OldFile
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReplaceKey(
	_In_ POBJECT_ATTRIBUTES NewFile,
	_In_ HANDLE TargetHandle,
	_In_ POBJECT_ATTRIBUTES OldFile
);

NTSYSCALLAPI NTSTATUS NTAPI NtSaveKey(
	_In_ HANDLE KeyHandle,
	_In_ HANDLE FileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSaveKey(
	_In_ HANDLE KeyHandle,
	_In_ HANDLE FileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtSaveKeyEx(
	_In_ HANDLE KeyHandle,
	_In_ HANDLE FileHandle,
	_In_ ULONG Format
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSaveKeyEx(
	_In_ HANDLE KeyHandle,
	_In_ HANDLE FileHandle,
	_In_ ULONG Format
);

NTSYSCALLAPI NTSTATUS NTAPI NtSaveMergedKeys(
	_In_ HANDLE HighPrecedenceKeyHandle,
	_In_ HANDLE LowPrecedenceKeyHandle,
	_In_ HANDLE FileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSaveMergedKeys(
	_In_ HANDLE HighPrecedenceKeyHandle,
	_In_ HANDLE LowPrecedenceKeyHandle,
	_In_ HANDLE FileHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtRestoreKey(
	_In_ HANDLE KeyHandle,
	_In_ HANDLE FileHandle,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRestoreKey(
	_In_ HANDLE KeyHandle,
	_In_ HANDLE FileHandle,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI NtUnloadKey(
	_In_ POBJECT_ATTRIBUTES TargetKey
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnloadKey(
	_In_ POBJECT_ATTRIBUTES TargetKey
);

NTSYSCALLAPI NTSTATUS NTAPI NtUnloadKey2(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnloadKey2(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ ULONG Flags
);

NTSYSCALLAPI NTSTATUS NTAPI NtUnloadKeyEx(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_opt_ HANDLE Event
);

NTSYSCALLAPI NTSTATUS NTAPI ZwUnloadKeyEx(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_opt_ HANDLE Event
);

NTSYSCALLAPI NTSTATUS NTAPI NtNotifyChangeKey(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwNotifyChangeKey(
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

NTSYSCALLAPI NTSTATUS NTAPI NtNotifyChangeMultipleKeys(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwNotifyChangeMultipleKeys(
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

NTSYSCALLAPI NTSTATUS NTAPI NtQueryOpenSubKeys(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_Out_ PULONG HandleCount
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryOpenSubKeys(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_Out_ PULONG HandleCount
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryOpenSubKeysEx(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ ULONG BufferLength,
	_Out_writes_bytes_(BufferLength) PVOID Buffer,
	_Out_ PULONG RequiredSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryOpenSubKeysEx(
	_In_ POBJECT_ATTRIBUTES TargetKey,
	_In_ ULONG BufferLength,
	_Out_writes_bytes_(BufferLength) PVOID Buffer,
	_Out_ PULONG RequiredSize
);

NTSYSCALLAPI NTSTATUS NTAPI NtInitializeRegistry(
	_In_ USHORT BootCondition
);

NTSYSCALLAPI NTSTATUS NTAPI ZwInitializeRegistry(
	_In_ USHORT BootCondition
);

NTSYSCALLAPI NTSTATUS NTAPI NtLockRegistryKey(
	_In_ HANDLE KeyHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwLockRegistryKey(
	_In_ HANDLE KeyHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtLockProductActivationKeys(
	_Inout_opt_ ULONG *pPrivateVer,
	_Out_opt_ ULONG *pSafeMode
);

NTSYSCALLAPI NTSTATUS NTAPI ZwLockProductActivationKeys(
	_Inout_opt_ ULONG *pPrivateVer,
	_Out_opt_ ULONG *pSafeMode
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI NTSTATUS NTAPI NtFreezeRegistry(
	_In_ ULONG TimeOutInSeconds
);

// private
NTSYSCALLAPI NTSTATUS NTAPI ZwFreezeRegistry(
	_In_ ULONG TimeOutInSeconds
);

// private
NTSYSCALLAPI NTSTATUS NTAPI NtThawRegistry(
	VOID
);

// private
NTSYSCALLAPI NTSTATUS NTAPI ZwThawRegistry(
	VOID
);
#endif

#endif

#ifndef _NTRTL_H
#define _NTRTL_H

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
	return (BOOLEAN)(ListHead->Flink == ListHead);
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

	return (BOOLEAN)(Flink == Blink);
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

typedef RTL_GENERIC_COMPARE_RESULTS(NTAPI *PRTL_AVL_COMPARE_ROUTINE)(
	_In_ struct _RTL_AVL_TABLE *Table,
	_In_ PVOID FirstStruct,
	_In_ PVOID SecondStruct
	);

typedef PVOID(NTAPI *PRTL_AVL_ALLOCATE_ROUTINE)(
	_In_ struct _RTL_AVL_TABLE *Table,
	_In_ CLONG ByteSize
	);

typedef VOID(NTAPI *PRTL_AVL_FREE_ROUTINE)(
	_In_ struct _RTL_AVL_TABLE *Table,
	_In_ _Post_invalid_ PVOID Buffer
	);

typedef NTSTATUS(NTAPI *PRTL_AVL_MATCH_FUNCTION)(
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

NTSYSAPI VOID NTAPI RtlInitializeGenericTableAvl(
	_Out_ PRTL_AVL_TABLE Table,
	_In_ PRTL_AVL_COMPARE_ROUTINE CompareRoutine,
	_In_ PRTL_AVL_ALLOCATE_ROUTINE AllocateRoutine,
	_In_ PRTL_AVL_FREE_ROUTINE FreeRoutine,
	_In_opt_ PVOID TableContext
);

NTSYSAPI PVOID NTAPI RtlInsertElementGenericTableAvl(
	_In_ PRTL_AVL_TABLE Table,
	_In_reads_bytes_(BufferSize) PVOID Buffer,
	_In_ CLONG BufferSize,
	_Out_opt_ PBOOLEAN NewElement
);

NTSYSAPI PVOID NTAPI RtlInsertElementGenericTableFullAvl(
	_In_ PRTL_AVL_TABLE Table,
	_In_reads_bytes_(BufferSize) PVOID Buffer,
	_In_ CLONG BufferSize,
	_Out_opt_ PBOOLEAN NewElement,
	_In_ PVOID NodeOrParent,
	_In_ TABLE_SEARCH_RESULT SearchResult
);

NTSYSAPI BOOLEAN NTAPI RtlDeleteElementGenericTableAvl(
	_In_ PRTL_AVL_TABLE Table,
	_In_ PVOID Buffer
);

_Check_return_
NTSYSAPI PVOID NTAPI RtlLookupElementGenericTableAvl(
	_In_ PRTL_AVL_TABLE Table,
	_In_ PVOID Buffer
);

NTSYSAPI PVOID NTAPI RtlLookupElementGenericTableFullAvl(
	_In_ PRTL_AVL_TABLE Table,
	_In_ PVOID Buffer,
	_Out_ PVOID *NodeOrParent,
	_Out_ TABLE_SEARCH_RESULT *SearchResult
);

_Check_return_
NTSYSAPI PVOID NTAPI RtlEnumerateGenericTableAvl(
	_In_ PRTL_AVL_TABLE Table,
	_In_ BOOLEAN Restart
);

_Check_return_
NTSYSAPI PVOID NTAPI RtlEnumerateGenericTableWithoutSplayingAvl(
	_In_ PRTL_AVL_TABLE Table,
	_Inout_ PVOID *RestartKey
);

_Check_return_
NTSYSAPI PVOID NTAPI RtlLookupFirstMatchingElementGenericTableAvl(
	_In_ PRTL_AVL_TABLE Table,
	_In_ PVOID Buffer,
	_Out_ PVOID *RestartKey
);

_Check_return_
NTSYSAPI PVOID NTAPI RtlEnumerateGenericTableLikeADirectory(
	_In_ PRTL_AVL_TABLE Table,
	_In_opt_ PRTL_AVL_MATCH_FUNCTION MatchFunction,
	_In_opt_ PVOID MatchData,
	_In_ ULONG NextFlag,
	_Inout_ PVOID *RestartKey,
	_Inout_ PULONG DeleteCount,
	_In_ PVOID Buffer
);

_Check_return_
NTSYSAPI PVOID NTAPI RtlGetElementGenericTableAvl(
	_In_ PRTL_AVL_TABLE Table,
	_In_ ULONG I
);

NTSYSAPI ULONG NTAPI RtlNumberGenericTableElementsAvl(
	_In_ PRTL_AVL_TABLE Table
);

_Check_return_
NTSYSAPI BOOLEAN NTAPI RtlIsGenericTableEmptyAvl(
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

NTSYSAPI PRTL_SPLAY_LINKS NTAPI RtlSplay(
	_Inout_ PRTL_SPLAY_LINKS Links
);

NTSYSAPI PRTL_SPLAY_LINKS NTAPI RtlDelete(
	_In_ PRTL_SPLAY_LINKS Links
);

NTSYSAPI VOID NTAPI RtlDeleteNoSplay(
	_In_ PRTL_SPLAY_LINKS Links,
	_Inout_ PRTL_SPLAY_LINKS *Root
);

_Check_return_ 
NTSYSAPI PRTL_SPLAY_LINKS NTAPI RtlSubtreeSuccessor(
	_In_ PRTL_SPLAY_LINKS Links
);

_Check_return_ 
NTSYSAPI PRTL_SPLAY_LINKS NTAPI RtlSubtreePredecessor(
	_In_ PRTL_SPLAY_LINKS Links
);

_Check_return_ 
NTSYSAPI PRTL_SPLAY_LINKS NTAPI RtlRealSuccessor(
	_In_ PRTL_SPLAY_LINKS Links
);

_Check_return_ 
NTSYSAPI PRTL_SPLAY_LINKS NTAPI RtlRealPredecessor(
	_In_ PRTL_SPLAY_LINKS Links
);

struct _RTL_GENERIC_TABLE;

typedef RTL_GENERIC_COMPARE_RESULTS(NTAPI *PRTL_GENERIC_COMPARE_ROUTINE)(
	_In_ struct _RTL_GENERIC_TABLE *Table,
	_In_ PVOID FirstStruct,
	_In_ PVOID SecondStruct
	);

typedef PVOID(NTAPI *PRTL_GENERIC_ALLOCATE_ROUTINE)(
	_In_ struct _RTL_GENERIC_TABLE *Table,
	_In_ CLONG ByteSize
	);

typedef VOID(NTAPI *PRTL_GENERIC_FREE_ROUTINE)(
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

NTSYSAPI VOID NTAPI RtlInitializeGenericTable(
	_Out_ PRTL_GENERIC_TABLE Table,
	_In_ PRTL_GENERIC_COMPARE_ROUTINE CompareRoutine,
	_In_ PRTL_GENERIC_ALLOCATE_ROUTINE AllocateRoutine,
	_In_ PRTL_GENERIC_FREE_ROUTINE FreeRoutine,
	_In_opt_ PVOID TableContext
);

NTSYSAPI PVOID NTAPI RtlInsertElementGenericTable(
	_In_ PRTL_GENERIC_TABLE Table,
	_In_reads_bytes_(BufferSize) PVOID Buffer,
	_In_ CLONG BufferSize,
	_Out_opt_ PBOOLEAN NewElement
);

NTSYSAPI PVOID NTAPI RtlInsertElementGenericTableFull(
	_In_ PRTL_GENERIC_TABLE Table,
	_In_reads_bytes_(BufferSize) PVOID Buffer,
	_In_ CLONG BufferSize,
	_Out_opt_ PBOOLEAN NewElement,
	_In_ PVOID NodeOrParent,
	_In_ TABLE_SEARCH_RESULT SearchResult
);

NTSYSAPI BOOLEAN NTAPI RtlDeleteElementGenericTable(
	_In_ PRTL_GENERIC_TABLE Table,
	_In_ PVOID Buffer
);

_Check_return_ 
NTSYSAPI PVOID NTAPI RtlLookupElementGenericTable(
	_In_ PRTL_GENERIC_TABLE Table,
	_In_ PVOID Buffer
);

NTSYSAPI PVOID NTAPI RtlLookupElementGenericTableFull(
	_In_ PRTL_GENERIC_TABLE Table,
	_In_ PVOID Buffer,
	_Out_ PVOID *NodeOrParent,
	_Out_ TABLE_SEARCH_RESULT *SearchResult
);

_Check_return_ 
NTSYSAPI PVOID NTAPI RtlEnumerateGenericTable(
	_In_ PRTL_GENERIC_TABLE Table,
	_In_ BOOLEAN Restart
);

_Check_return_ 
NTSYSAPI PVOID NTAPI RtlEnumerateGenericTableWithoutSplaying(
	_In_ PRTL_GENERIC_TABLE Table,
	_Inout_ PVOID *RestartKey
);

_Check_return_ 
NTSYSAPI PVOID NTAPI RtlGetElementGenericTable(
	_In_ PRTL_GENERIC_TABLE Table,
	_In_ ULONG I
);

NTSYSAPI ULONG NTAPI RtlNumberGenericTableElements(
	_In_ PRTL_GENERIC_TABLE Table
);

_Check_return_ NTSYSAPI BOOLEAN NTAPI RtlIsGenericTableEmpty(
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
NTSYSAPI VOID NTAPI RtlRbInsertNodeEx(
	_In_ PRTL_RB_TREE Tree,
	_In_opt_ PRTL_BALANCED_NODE Parent,
	_In_ BOOLEAN Right,
	_Out_ PRTL_BALANCED_NODE Node
);

// rev
NTSYSAPI VOID NTAPI RtlRbRemoveNode(
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

FORCEINLINE VOID RtlInitHashTableContext(
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context)
{
	Context->ChainHead = NULL;
	Context->PrevLinkage = NULL;
}

FORCEINLINE VOID RtlInitHashTableContextFromEnumerator(
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context,
	_In_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator)
{
	Context->ChainHead = Enumerator->ChainHead;
	Context->PrevLinkage = Enumerator->HashEntry.Linkage.Blink;
}

FORCEINLINE VOID RtlReleaseHashTableContext(
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context)
{
	UNREFERENCED_PARAMETER(Context);
	return;
}

FORCEINLINE ULONG RtlTotalBucketsHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable)
{
	return HashTable->TableSize;
}

FORCEINLINE ULONG RtlNonEmptyBucketsHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable)
{
	return HashTable->NonEmptyBuckets;
}

FORCEINLINE ULONG RtlEmptyBucketsHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable)
{
	return HashTable->TableSize - HashTable->NonEmptyBuckets;
}

FORCEINLINE ULONG RtlTotalEntriesHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable)
{
	return HashTable->NumEntries;
}

FORCEINLINE ULONG RtlActiveEnumeratorsHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable)
{
	return HashTable->NumEnumerators;
}

_Must_inspect_result_ 
NTSYSAPI BOOLEAN NTAPI RtlCreateHashTable(
	_Inout_ _When_(*HashTable == NULL, __drv_allocatesMem(Mem)) PRTL_DYNAMIC_HASH_TABLE *HashTable,
	_In_ ULONG Shift,
	_In_ _Reserved_ ULONG Flags
);

NTSYSAPI VOID NTAPI RtlDeleteHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable
);

NTSYSAPI BOOLEAN NTAPI RtlInsertEntryHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_In_ PRTL_DYNAMIC_HASH_TABLE_ENTRY Entry,
	_In_ ULONG_PTR Signature,
	_Inout_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
);

NTSYSAPI BOOLEAN NTAPI RtlRemoveEntryHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_In_ PRTL_DYNAMIC_HASH_TABLE_ENTRY Entry,
	_Inout_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
);

_Must_inspect_result_
NTSYSAPI PRTL_DYNAMIC_HASH_TABLE_ENTRY NTAPI RtlLookupEntryHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_In_ ULONG_PTR Signature,
	_Out_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
);

_Must_inspect_result_
NTSYSAPI PRTL_DYNAMIC_HASH_TABLE_ENTRY NTAPI RtlGetNextEntryHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_In_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
);

NTSYSAPI BOOLEAN NTAPI RtlInitEnumerationHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

_Must_inspect_result_
NTSYSAPI PRTL_DYNAMIC_HASH_TABLE_ENTRY NTAPI RtlEnumerateEntryHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

NTSYSAPI VOID NTAPI RtlEndEnumerationHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

NTSYSAPI BOOLEAN NTAPI RtlInitWeakEnumerationHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

_Must_inspect_result_
NTSYSAPI PRTL_DYNAMIC_HASH_TABLE_ENTRY NTAPI RtlWeaklyEnumerateEntryHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

NTSYSAPI VOID NTAPI RtlEndWeakEnumerationHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

NTSYSAPI BOOLEAN NTAPI RtlExpandHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable
);

NTSYSAPI BOOLEAN NTAPI RtlContractHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable
);

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)

NTSYSAPI BOOLEAN NTAPI RtlInitStrongEnumerationHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

_Must_inspect_result_
NTSYSAPI PRTL_DYNAMIC_HASH_TABLE_ENTRY NTAPI RtlStronglyEnumerateEntryHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

NTSYSAPI VOID NTAPI RtlEndStrongEnumerationHashTable(
	_In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
	_Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);

#endif

// end_ntddk

// Critical sections

NTSYSAPI NTSTATUS NTAPI RtlInitializeCriticalSection(
	_Out_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI NTSTATUS NTAPI RtlInitializeCriticalSectionAndSpinCount(
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection,
	_In_ ULONG SpinCount
);

NTSYSAPI NTSTATUS NTAPI RtlDeleteCriticalSection(
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI NTSTATUS NTAPI RtlEnterCriticalSection(
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI NTSTATUS NTAPI RtlLeaveCriticalSection(
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI LOGICAL NTAPI RtlTryEnterCriticalSection(
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI LOGICAL NTAPI RtlIsCriticalSectionLocked(
	_In_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI LOGICAL NTAPI RtlIsCriticalSectionLockedByThread(
	_In_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI ULONG NTAPI RtlGetCriticalSectionRecursionCount(
	_In_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI ULONG NTAPI RtlSetCriticalSectionSpinCount(
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection,
	_In_ ULONG SpinCount
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI HANDLE NTAPI RtlQueryCriticalSectionOwner(
	_In_ HANDLE EventHandle
);
#endif

NTSYSAPI VOID NTAPI RtlCheckForOrphanedCriticalSections(
	_In_ HANDLE hThread
);

// Resources

typedef struct _RTL_RESOURCE
{
	RTL_CRITICAL_SECTION CriticalSection;

	HANDLE SharedSemaphore;
	ULONG NumberOfWaitingShared;
	HANDLE ExclusiveSemaphore;
	ULONG NumberOfWaitingExclusive;

	LONG NumberOfActive; // negative: exclusive acquire; zero: not acquired; positive: shared acquire(s)
	HANDLE ExclusiveOwnerThread;

	ULONG Flags; // RTL_RESOURCE_FLAG_*

	PRTL_RESOURCE_DEBUG DebugInfo;
} RTL_RESOURCE, *PRTL_RESOURCE;

#define RTL_RESOURCE_FLAG_LONG_TERM ((ULONG)0x00000001)

NTSYSAPI VOID NTAPI RtlInitializeResource(
	_Out_ PRTL_RESOURCE Resource
);

NTSYSAPI VOID NTAPI RtlDeleteResource(
	_Inout_ PRTL_RESOURCE Resource
);

NTSYSAPI BOOLEAN NTAPI RtlAcquireResourceShared(
	_Inout_ PRTL_RESOURCE Resource,
	_In_ BOOLEAN Wait
);

NTSYSAPI BOOLEAN NTAPI RtlAcquireResourceExclusive(
	_Inout_ PRTL_RESOURCE Resource,
	_In_ BOOLEAN Wait
);

NTSYSAPI VOID NTAPI RtlReleaseResource(
	_Inout_ PRTL_RESOURCE Resource
);

NTSYSAPI VOID NTAPI RtlConvertSharedToExclusive(
	_Inout_ PRTL_RESOURCE Resource
);

NTSYSAPI VOID NTAPI RtlConvertExclusiveToShared(
	_Inout_ PRTL_RESOURCE Resource
);

// Slim reader-writer locks, condition variables, and barriers

#if (NTDDI_VERSION >= NTDDI_VISTA)

// winbase:InitializeSRWLock
NTSYSAPI VOID NTAPI RtlInitializeSRWLock(
	_Out_ PRTL_SRWLOCK SRWLock
);

// winbase:AcquireSRWLockExclusive
NTSYSAPI VOID NTAPI RtlAcquireSRWLockExclusive(
	_Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:AcquireSRWLockShared
NTSYSAPI VOID NTAPI RtlAcquireSRWLockShared(
	_Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:ReleaseSRWLockExclusive
NTSYSAPI VOID NTAPI RtlReleaseSRWLockExclusive(
	_Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:ReleaseSRWLockShared
NTSYSAPI VOID NTAPI RtlReleaseSRWLockShared(
	_Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:TryAcquireSRWLockExclusive
NTSYSAPI BOOLEAN NTAPI RtlTryAcquireSRWLockExclusive(
	_Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:TryAcquireSRWLockShared
NTSYSAPI BOOLEAN NTAPI RtlTryAcquireSRWLockShared(
	_Inout_ PRTL_SRWLOCK SRWLock
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI VOID NTAPI RtlAcquireReleaseSRWLockExclusive(
	_Inout_ PRTL_SRWLOCK SRWLock
);
#endif

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// winbase:InitializeConditionVariable
NTSYSAPI VOID NTAPI RtlInitializeConditionVariable(
	_Out_ PRTL_CONDITION_VARIABLE ConditionVariable
);

// private
NTSYSAPI NTSTATUS NTAPI RtlSleepConditionVariableCS(
	_Inout_ PRTL_CONDITION_VARIABLE ConditionVariable,
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection,
	_In_opt_ PLARGE_INTEGER Timeout
);

// private
NTSYSAPI NTSTATUS NTAPI RtlSleepConditionVariableSRW(
	_Inout_ PRTL_CONDITION_VARIABLE ConditionVariable,
	_Inout_ PRTL_SRWLOCK SRWLock,
	_In_opt_ PLARGE_INTEGER Timeout,
	_In_ ULONG Flags
);

// winbase:WakeConditionVariable
NTSYSAPI VOID NTAPI RtlWakeConditionVariable(
	_Inout_ PRTL_CONDITION_VARIABLE ConditionVariable
);

// winbase:WakeAllConditionVariable
NTSYSAPI VOID NTAPI RtlWakeAllConditionVariable(
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

NTSYSAPI NTSTATUS NTAPI RtlInitBarrier(
	_Out_ PRTL_BARRIER Barrier,
	_In_ ULONG TotalThreads,
	_In_ ULONG SpinCount
);

NTSYSAPI NTSTATUS NTAPI RtlDeleteBarrier(
	_In_ PRTL_BARRIER Barrier
);

NTSYSAPI BOOLEAN NTAPI RtlBarrier(
	_Inout_ PRTL_BARRIER Barrier,
	_In_ ULONG Flags
);

NTSYSAPI BOOLEAN NTAPI RtlBarrierForDelete(
	_Inout_ PRTL_BARRIER Barrier,
	_In_ ULONG Flags
);

#endif

// end_private

// Wait on address

// begin_rev

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSAPI NTSTATUS NTAPI RtlWaitOnAddress(
	_In_ volatile VOID *Address,
	_In_ PVOID CompareAddress,
	_In_ SIZE_T AddressSize,
	_In_opt_ PLARGE_INTEGER Timeout
);

NTSYSAPI VOID NTAPI RtlWakeAddressAll(
	_In_ PVOID Address
);

NTSYSAPI VOID NTAPI RtlWakeAddressSingle(
	_In_ PVOID Address
);

#endif

// end_rev

// Strings

FORCEINLINE VOID RtlInitString(
	_Out_ PSTRING DestinationString,
	_In_opt_ PSTR SourceString)
{
	if (SourceString)
	{
		DestinationString->Length = (USHORT)strlen(SourceString);
		DestinationString->MaximumLength = (USHORT)(DestinationString->Length + 1);
	}
	else
	{
		DestinationString->Length = 0;
		DestinationString->MaximumLength = 0;
	}

	DestinationString->Buffer = SourceString;
}

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSAPI NTSTATUS NTAPI RtlInitStringEx(
	_Out_ PSTRING DestinationString,
	_In_opt_z_ PCSZ SourceString
);
#endif

FORCEINLINE VOID RtlInitAnsiString(
	_Out_ PANSI_STRING DestinationString,
	_In_opt_ PSTR SourceString)
{
	RtlInitString(DestinationString, SourceString);
}

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI NTSTATUS NTAPI RtlInitAnsiStringEx(
	_Out_ PANSI_STRING DestinationString,
	_In_opt_z_ PCSZ SourceString
);
#endif

NTSYSAPI VOID NTAPI RtlFreeAnsiString(
	_In_ PANSI_STRING AnsiString
);

NTSYSAPI VOID NTAPI RtlFreeOemString(
	_In_ POEM_STRING OemString
);

NTSYSAPI VOID NTAPI RtlCopyString(
	_In_ PSTRING DestinationString,
	_In_opt_ PSTRING SourceString
);

NTSYSAPI CHAR NTAPI RtlUpperChar(
	_In_ CHAR Character
);

_Must_inspect_result_
NTSYSAPI LONG NTAPI RtlCompareString(
	_In_ PSTRING String1,
	_In_ PSTRING String2,
	_In_ BOOLEAN CaseInSensitive
);

_Must_inspect_result_
NTSYSAPI BOOLEAN NTAPI RtlEqualString(
	_In_ PSTRING String1,
	_In_ PSTRING String2,
	_In_ BOOLEAN CaseInSensitive
);

_Must_inspect_result_
NTSYSAPI BOOLEAN NTAPI RtlPrefixString(
	_In_ PSTRING String1,
	_In_ PSTRING String2,
	_In_ BOOLEAN CaseInSensitive
);

NTSYSAPI NTSTATUS NTAPI RtlAppendStringToString(
	_In_ PSTRING Destination,
	_In_ PSTRING Source
);

NTSYSAPI NTSTATUS NTAPI RtlAppendAsciizToString(
	_In_ PSTRING Destination,
	_In_opt_ PSTR Source
);

NTSYSAPI VOID NTAPI RtlUpperString(
	_In_ PSTRING DestinationString,
	_In_ PSTRING SourceString
);

FORCEINLINE VOID RtlInitUnicodeString(
	_Out_ PUNICODE_STRING DestinationString,
	_In_opt_ PWSTR SourceString)
{
	if (SourceString)
	{
		DestinationString->Length = (USHORT)(wcslen(SourceString) * sizeof(WCHAR));
		DestinationString->MaximumLength = DestinationString->Length + sizeof(WCHAR);
	}
	else
	{
		DestinationString->Length = 0;
		DestinationString->MaximumLength = 0;
	}

	DestinationString->Buffer = SourceString;
}

NTSYSAPI NTSTATUS NTAPI RtlInitUnicodeStringEx(
	_Out_ PUNICODE_STRING DestinationString,
	_In_opt_ PWSTR SourceString
);

NTSYSAPI BOOLEAN NTAPI RtlCreateUnicodeString(
	_Out_ PUNICODE_STRING DestinationString,
	_In_ PWSTR SourceString
);

NTSYSAPI BOOLEAN NTAPI RtlCreateUnicodeStringFromAsciiz(
	_Out_ PUNICODE_STRING DestinationString,
	_In_ PSTR SourceString
);

NTSYSAPI VOID NTAPI RtlFreeUnicodeString(
	_In_ PUNICODE_STRING UnicodeString
);

#define RTL_DUPLICATE_UNICODE_STRING_NULL_TERMINATE (0x00000001)
#define RTL_DUPLICATE_UNICODE_STRING_ALLOCATE_NULL_STRING (0x00000002)

NTSYSAPI NTSTATUS NTAPI RtlDuplicateUnicodeString(
	_In_ ULONG Flags,
	_In_ PUNICODE_STRING StringIn,
	_Out_ PUNICODE_STRING StringOut
);

NTSYSAPI VOID NTAPI RtlCopyUnicodeString(
	_In_ PUNICODE_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString
);

NTSYSAPI WCHAR NTAPI RtlUpcaseUnicodeChar(
	_In_ WCHAR SourceCharacter
);

NTSYSAPI WCHAR NTAPI RtlDowncaseUnicodeChar(
	_In_ WCHAR SourceCharacter
);

_Must_inspect_result_
NTSYSAPI LONG NTAPI RtlCompareUnicodeString(
	_In_ PUNICODE_STRING String1,
	_In_ PUNICODE_STRING String2,
	_In_ BOOLEAN CaseInSensitive
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
_Must_inspect_result_
NTSYSAPI LONG NTAPI RtlCompareUnicodeStrings(
	_In_reads_(String1Length) PWCH String1,
	_In_ SIZE_T String1Length,
	_In_reads_(String2Length) PWCH String2,
	_In_ SIZE_T String2Length,
	_In_ BOOLEAN CaseInSensitive
);
#endif

_Must_inspect_result_
NTSYSAPI BOOLEAN NTAPI RtlEqualUnicodeString(
	_In_ PUNICODE_STRING String1,
	_In_ PUNICODE_STRING String2,
	_In_ BOOLEAN CaseInSensitive
);

#define HASH_STRING_ALGORITHM_DEFAULT 0
#define HASH_STRING_ALGORITHM_X65599 1
#define HASH_STRING_ALGORITHM_INVALID 0xffffffff

NTSYSAPI NTSTATUS NTAPI RtlHashUnicodeString(
	_In_ PUNICODE_STRING String,
	_In_ BOOLEAN CaseInSensitive,
	_In_ ULONG HashAlgorithm,
	_Out_ PULONG HashValue
);

NTSYSAPI NTSTATUS NTAPI RtlValidateUnicodeString(
	_In_ ULONG Flags,
	_In_ PUNICODE_STRING String
);

_Must_inspect_result_
NTSYSAPI BOOLEAN NTAPI RtlPrefixUnicodeString(
	_In_ PCUNICODE_STRING String1,
	_In_ PCUNICODE_STRING String2,
	_In_ BOOLEAN CaseInSensitive
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
_Must_inspect_result_
NTSYSAPI BOOLEAN NTAPI RtlSuffixUnicodeString(
	_In_ PCUNICODE_STRING String1,
	_In_ PCUNICODE_STRING String2,
	_In_ BOOLEAN CaseInSensitive
);
#endif

#define RTL_FIND_CHAR_IN_UNICODE_STRING_START_AT_END 0x00000001
#define RTL_FIND_CHAR_IN_UNICODE_STRING_COMPLEMENT_CHAR_SET 0x00000002
#define RTL_FIND_CHAR_IN_UNICODE_STRING_CASE_INSENSITIVE 0x00000004

NTSYSAPI NTSTATUS NTAPI RtlFindCharInUnicodeString(
	_In_ ULONG Flags,
	_In_ PUNICODE_STRING StringToSearch,
	_In_ PUNICODE_STRING CharSet,
	_Out_ PUSHORT NonInclusivePrefixLength
);

NTSYSAPI NTSTATUS NTAPI RtlAppendUnicodeStringToString(
	_In_ PUNICODE_STRING Destination,
	_In_ PUNICODE_STRING Source
);

NTSYSAPI NTSTATUS NTAPI RtlAppendUnicodeToString(
	_In_ PUNICODE_STRING Destination,
	_In_opt_ PWSTR Source
);

NTSYSAPI NTSTATUS NTAPI RtlUpcaseUnicodeString(
	_Inout_ PUNICODE_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI NTSTATUS NTAPI RtlDowncaseUnicodeString(
	_Inout_ PUNICODE_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI VOID NTAPI RtlEraseUnicodeString(
	_Inout_ PUNICODE_STRING String
);

NTSYSAPI NTSTATUS NTAPI RtlAnsiStringToUnicodeString(
	_Inout_ PUNICODE_STRING DestinationString,
	_In_ PANSI_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI NTSTATUS NTAPI RtlUnicodeStringToAnsiString(
	_Inout_ PANSI_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI WCHAR NTAPI RtlAnsiCharToUnicodeChar(
	_Inout_ PUCHAR *SourceCharacter
);

NTSYSAPI NTSTATUS NTAPI RtlUpcaseUnicodeStringToAnsiString(
	_Inout_ PANSI_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI NTSTATUS NTAPI RtlOemStringToUnicodeString(
	_Inout_ PUNICODE_STRING DestinationString,
	_In_ POEM_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI NTSTATUS NTAPI RtlUnicodeStringToOemString(
	_Inout_ POEM_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI NTSTATUS NTAPI RtlUpcaseUnicodeStringToOemString(
	_Inout_ POEM_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI NTSTATUS NTAPI RtlUnicodeStringToCountedOemString(
	_Inout_ POEM_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI NTSTATUS NTAPI RtlUpcaseUnicodeStringToCountedOemString(
	_Inout_ POEM_STRING DestinationString,
	_In_ PUNICODE_STRING SourceString,
	_In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI NTSTATUS NTAPI RtlMultiByteToUnicodeN(
	_Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG MaxBytesInUnicodeString,
	_Out_opt_ PULONG BytesInUnicodeString,
	_In_reads_bytes_(BytesInMultiByteString) PSTR MultiByteString,
	_In_ ULONG BytesInMultiByteString
);

NTSYSAPI NTSTATUS NTAPI RtlMultiByteToUnicodeSize(
	_Out_ PULONG BytesInUnicodeString,
	_In_reads_bytes_(BytesInMultiByteString) PSTR MultiByteString,
	_In_ ULONG BytesInMultiByteString
);

NTSYSAPI NTSTATUS NTAPI RtlUnicodeToMultiByteN(
	_Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
	_In_ ULONG MaxBytesInMultiByteString,
	_Out_opt_ PULONG BytesInMultiByteString,
	_In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG BytesInUnicodeString
);

NTSYSAPI NTSTATUS NTAPI RtlUnicodeToMultiByteSize(
	_Out_ PULONG BytesInMultiByteString,
	_In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG BytesInUnicodeString
);

NTSYSAPI NTSTATUS NTAPI RtlUpcaseUnicodeToMultiByteN(
	_Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
	_In_ ULONG MaxBytesInMultiByteString,
	_Out_opt_ PULONG BytesInMultiByteString,
	_In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG BytesInUnicodeString
);

NTSYSAPI NTSTATUS NTAPI RtlOemToUnicodeN(
	_Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWSTR UnicodeString,
	_In_ ULONG MaxBytesInUnicodeString,
	_Out_opt_ PULONG BytesInUnicodeString,
	_In_reads_bytes_(BytesInOemString) PCH OemString,
	_In_ ULONG BytesInOemString
);

NTSYSAPI NTSTATUS NTAPI RtlUnicodeToOemN(
	_Out_writes_bytes_to_(MaxBytesInOemString, *BytesInOemString) PCHAR OemString,
	_In_ ULONG MaxBytesInOemString,
	_Out_opt_ PULONG BytesInOemString,
	_In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG BytesInUnicodeString
);

NTSYSAPI NTSTATUS NTAPI RtlUpcaseUnicodeToOemN(
	_Out_writes_bytes_to_(MaxBytesInOemString, *BytesInOemString) PCHAR OemString,
	_In_ ULONG MaxBytesInOemString,
	_Out_opt_ PULONG BytesInOemString,
	_In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG BytesInUnicodeString
);

NTSYSAPI NTSTATUS NTAPI RtlConsoleMultiByteToUnicodeN(
	_Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG MaxBytesInUnicodeString,
	_Out_opt_ PULONG BytesInUnicodeString,
	_In_reads_bytes_(BytesInMultiByteString) PCH MultiByteString,
	_In_ ULONG BytesInMultiByteString,
	_Out_ PULONG pdwSpecialChar
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI NTSTATUS NTAPI RtlUTF8ToUnicodeN(
	_Out_writes_bytes_to_(UnicodeStringMaxByteCount, *UnicodeStringActualByteCount) PWSTR UnicodeStringDestination,
	_In_ ULONG UnicodeStringMaxByteCount,
	_Out_ PULONG UnicodeStringActualByteCount,
	_In_reads_bytes_(UTF8StringByteCount) PCH UTF8StringSource,
	_In_ ULONG UTF8StringByteCount
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI NTSTATUS NTAPI RtlUnicodeToUTF8N(
	_Out_writes_bytes_to_(UTF8StringMaxByteCount, *UTF8StringActualByteCount) PCHAR UTF8StringDestination,
	_In_ ULONG UTF8StringMaxByteCount,
	_Out_ PULONG UTF8StringActualByteCount,
	_In_reads_bytes_(UnicodeStringByteCount) PWCH UnicodeStringSource,
	_In_ ULONG UnicodeStringByteCount
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlCustomCPToUnicodeN(
	_In_ PCPTABLEINFO CustomCP,
	_Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG MaxBytesInUnicodeString,
	_Out_opt_ PULONG BytesInUnicodeString,
	_In_reads_bytes_(BytesInCustomCPString) PCH CustomCPString,
	_In_ ULONG BytesInCustomCPString
);

NTSYSAPI NTSTATUS NTAPI RtlUnicodeToCustomCPN(
	_In_ PCPTABLEINFO CustomCP,
	_Out_writes_bytes_to_(MaxBytesInCustomCPString, *BytesInCustomCPString) PCH CustomCPString,
	_In_ ULONG MaxBytesInCustomCPString,
	_Out_opt_ PULONG BytesInCustomCPString,
	_In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG BytesInUnicodeString
);

NTSYSAPI NTSTATUS NTAPI RtlUpcaseUnicodeToCustomCPN(
	_In_ PCPTABLEINFO CustomCP,
	_Out_writes_bytes_to_(MaxBytesInCustomCPString, *BytesInCustomCPString) PCH CustomCPString,
	_In_ ULONG MaxBytesInCustomCPString,
	_Out_opt_ PULONG BytesInCustomCPString,
	_In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
	_In_ ULONG BytesInUnicodeString
);

NTSYSAPI VOID NTAPI RtlInitCodePageTable(
	_In_ PUSHORT TableBase,
	_Out_ PCPTABLEINFO CodePageTable
);

NTSYSAPI VOID NTAPI RtlInitNlsTables(
	_In_ PUSHORT AnsiNlsBase,
	_In_ PUSHORT OemNlsBase,
	_In_ PUSHORT LanguageNlsBase,
	_Out_ PNLSTABLEINFO TableInfo
);

NTSYSAPI VOID NTAPI RtlResetRtlTranslations(
	_In_ PNLSTABLEINFO TableInfo
);

NTSYSAPI BOOLEAN NTAPI RtlIsTextUnicode(
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
NTSYSAPI NTSTATUS NTAPI RtlNormalizeString(
	_In_ ULONG NormForm, // RTL_NORM_FORM
	_In_ PCWSTR SourceString,
	_In_ LONG SourceStringLength,
	_Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
	_Inout_ PLONG DestinationStringLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI NTSTATUS NTAPI RtlIsNormalizedString(
	_In_ ULONG NormForm, // RTL_NORM_FORM
	_In_ PCWSTR SourceString,
	_In_ LONG SourceStringLength,
	_Out_ PBOOLEAN Normalized
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// ntifs:FsRtlIsNameInExpression
NTSYSAPI BOOLEAN NTAPI RtlIsNameInExpression(
	_In_ PUNICODE_STRING Expression,
	_In_ PUNICODE_STRING Name,
	_In_ BOOLEAN IgnoreCase,
	_In_opt_ PWCH UpcaseTable
);
#endif

NTSYSAPI BOOLEAN NTAPI RtlEqualDomainName(
	_In_ PUNICODE_STRING String1,
	_In_ PUNICODE_STRING String2
);

NTSYSAPI BOOLEAN NTAPI RtlEqualComputerName(
	_In_ PUNICODE_STRING String1,
	_In_ PUNICODE_STRING String2
);

NTSYSAPI NTSTATUS NTAPI RtlDnsHostNameToComputerName(
	_Out_ PUNICODE_STRING ComputerNameString,
	_In_ PCUNICODE_STRING DnsHostNameString,
	_In_ BOOLEAN AllocateComputerNameString
);

NTSYSAPI NTSTATUS NTAPI RtlStringFromGUID(
	_In_ PGUID Guid,
	_Out_ PUNICODE_STRING GuidString
);

NTSYSAPI NTSTATUS NTAPI RtlGUIDFromString(
	_In_ PUNICODE_STRING GuidString,
	_Out_ PGUID Guid
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI LONG NTAPI RtlCompareAltitudes(
	_In_ PUNICODE_STRING Altitude1,
	_In_ PUNICODE_STRING Altitude2
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

NTSYSAPI VOID NTAPI PfxInitialize(
	_Out_ PPREFIX_TABLE PrefixTable
);

NTSYSAPI BOOLEAN NTAPI PfxInsertPrefix(
	_In_ PPREFIX_TABLE PrefixTable,
	_In_ PSTRING Prefix,
	_Out_ PPREFIX_TABLE_ENTRY PrefixTableEntry
);

NTSYSAPI VOID NTAPI PfxRemovePrefix(
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

NTSYSAPI VOID NTAPI RtlInitializeUnicodePrefix(
	_Out_ PUNICODE_PREFIX_TABLE PrefixTable
);

NTSYSAPI BOOLEAN NTAPI RtlInsertUnicodePrefix(
	_In_ PUNICODE_PREFIX_TABLE PrefixTable,
	_In_ PUNICODE_STRING Prefix,
	_Out_ PUNICODE_PREFIX_TABLE_ENTRY PrefixTableEntry
);

NTSYSAPI VOID NTAPI RtlRemoveUnicodePrefix(
	_In_ PUNICODE_PREFIX_TABLE PrefixTable,
	_In_ PUNICODE_PREFIX_TABLE_ENTRY PrefixTableEntry
);

NTSYSAPI PUNICODE_PREFIX_TABLE_ENTRY NTAPI RtlFindUnicodePrefix(
	_In_ PUNICODE_PREFIX_TABLE PrefixTable,
	_In_ PUNICODE_STRING FullName,
	_In_ ULONG CaseInsensitiveIndex
);

NTSYSAPI PUNICODE_PREFIX_TABLE_ENTRY NTAPI RtlNextUnicodePrefix(
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

NTSYSAPI NTSTATUS NTAPI RtlGetCompressionWorkSpaceSize(
	_In_ USHORT CompressionFormatAndEngine,
	_Out_ PULONG CompressBufferWorkSpaceSize,
	_Out_ PULONG CompressFragmentWorkSpaceSize
);

NTSYSAPI NTSTATUS NTAPI RtlCompressBuffer(
	_In_ USHORT CompressionFormatAndEngine,
	_In_reads_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
	_In_ ULONG UncompressedBufferSize,
	_Out_writes_bytes_to_(CompressedBufferSize, *FinalCompressedSize) PUCHAR CompressedBuffer,
	_In_ ULONG CompressedBufferSize,
	_In_ ULONG UncompressedChunkSize,
	_Out_ PULONG FinalCompressedSize,
	_In_ PVOID WorkSpace
);

NTSYSAPI NTSTATUS NTAPI RtlDecompressBuffer(
	_In_ USHORT CompressionFormat,
	_Out_writes_bytes_to_(UncompressedBufferSize, *FinalUncompressedSize) PUCHAR UncompressedBuffer,
	_In_ ULONG UncompressedBufferSize,
	_In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
	_In_ ULONG CompressedBufferSize,
	_Out_ PULONG FinalUncompressedSize
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI NTSTATUS NTAPI RtlDecompressBufferEx(
	_In_ USHORT CompressionFormat,
	_Out_writes_bytes_to_(UncompressedBufferSize, *FinalUncompressedSize) PUCHAR UncompressedBuffer,
	_In_ ULONG UncompressedBufferSize,
	_In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
	_In_ ULONG CompressedBufferSize,
	_Out_ PULONG FinalUncompressedSize,
	_In_ PVOID WorkSpace
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlDecompressFragment(
	_In_ USHORT CompressionFormat,
	_Out_writes_bytes_to_(UncompressedFragmentSize, *FinalUncompressedSize) PUCHAR UncompressedFragment,
	_In_ ULONG UncompressedFragmentSize,
	_In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
	_In_ ULONG CompressedBufferSize,
	_In_range_(<, CompressedBufferSize) ULONG FragmentOffset,
	_Out_ PULONG FinalUncompressedSize,
	_In_ PVOID WorkSpace
);

NTSYSAPI NTSTATUS NTAPI RtlDescribeChunk(
	_In_ USHORT CompressionFormat,
	_Inout_ PUCHAR *CompressedBuffer,
	_In_ PUCHAR EndOfCompressedBufferPlus1,
	_Out_ PUCHAR *ChunkBuffer,
	_Out_ PULONG ChunkSize
);

NTSYSAPI NTSTATUS NTAPI RtlReserveChunk(
	_In_ USHORT CompressionFormat,
	_Inout_ PUCHAR *CompressedBuffer,
	_In_ PUCHAR EndOfCompressedBufferPlus1,
	_Out_ PUCHAR *ChunkBuffer,
	_In_ ULONG ChunkSize
);

NTSYSAPI NTSTATUS NTAPI RtlDecompressChunks(
	_Out_writes_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
	_In_ ULONG UncompressedBufferSize,
	_In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
	_In_ ULONG CompressedBufferSize,
	_In_reads_bytes_(CompressedTailSize) PUCHAR CompressedTail,
	_In_ ULONG CompressedTailSize,
	_In_ PCOMPRESSED_DATA_INFO CompressedDataInfo
);

NTSYSAPI NTSTATUS NTAPI RtlCompressChunks(
	_In_reads_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
	_In_ ULONG UncompressedBufferSize,
	_Out_writes_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
	_In_range_(>= , (UncompressedBufferSize - (UncompressedBufferSize / 16))) ULONG CompressedBufferSize,
	_Inout_updates_bytes_(CompressedDataInfoLength) PCOMPRESSED_DATA_INFO CompressedDataInfo,
	_In_range_(>, sizeof(COMPRESSED_DATA_INFO)) ULONG CompressedDataInfoLength,
	_In_ PVOID WorkSpace
);

// Locale

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI NTSTATUS NTAPI RtlConvertLCIDToString(
	_In_ LCID LcidValue,
	_In_ ULONG Base,
	_In_ ULONG Padding, // string is padded to this width
	_Out_writes_(Size) PWSTR pResultBuf,
	_In_ ULONG Size
);

// private
NTSYSAPI BOOLEAN NTAPI RtlIsValidLocaleName(
	_In_ PWSTR LocaleName,
	_In_ ULONG Flags
);

// private
NTSYSAPI NTSTATUS NTAPI RtlGetParentLocaleName(
	_In_ PWSTR LocaleName,
	_Inout_ PUNICODE_STRING ParentLocaleName,
	_In_ ULONG Flags,
	_In_ BOOLEAN AllocateDestinationString
);

// private
NTSYSAPI NTSTATUS NTAPI RtlLcidToLocaleName(
	_In_ LCID lcid, // sic
	_Inout_ PUNICODE_STRING LocaleName,
	_In_ ULONG Flags,
	_In_ BOOLEAN AllocateDestinationString
);

// private
NTSYSAPI NTSTATUS NTAPI RtlLocaleNameToLcid(
	_In_ PWSTR LocaleName,
	_Out_ PLCID lcid,
	_In_ ULONG Flags
);

// private
NTSYSAPI BOOLEAN NTAPI RtlLCIDToCultureName(
	_In_ LCID Lcid,
	_Inout_ PUNICODE_STRING String
);

// private
NTSYSAPI BOOLEAN NTAPI RtlCultureNameToLCID(
	_In_ PUNICODE_STRING String,
	_Out_ PLCID Lcid
);

// private
NTSYSAPI VOID NTAPI RtlCleanUpTEBLangLists(
	VOID
);

#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)

// rev
NTSYSAPI NTSTATUS NTAPI RtlGetLocaleFileMappingAddress(
	_Out_ PVOID *BaseAddress,
	_Out_ PLCID DefaultLocaleId,
	_Out_ PLARGE_INTEGER DefaultCasingTableSize
);

#endif

// PEB

NTSYSAPI VOID NTAPI RtlAcquirePebLock(
	VOID
);

NTSYSAPI VOID NTAPI RtlReleasePebLock(
	VOID
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI LOGICAL NTAPI RtlTryAcquirePebLock(
	VOID
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlAllocateFromPeb(
	_In_ ULONG Size,
	_Out_ PVOID *Block
);

NTSYSAPI NTSTATUS NTAPI RtlFreeToPeb(
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

	ULONG EnvironmentSize;
	ULONG EnvironmentVersion;
	PVOID PackageDependencyData;
	ULONG ProcessGroupId;
	ULONG LoaderThreads;
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

NTSYSAPI NTSTATUS NTAPI RtlCreateProcessParameters(
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
NTSYSAPI NTSTATUS NTAPI RtlCreateProcessParametersEx(
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

NTSYSAPI NTSTATUS NTAPI RtlDestroyProcessParameters(
	_In_ _Post_invalid_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
);

NTSYSAPI PRTL_USER_PROCESS_PARAMETERS NTAPI RtlNormalizeProcessParams(
	_Inout_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
);

NTSYSAPI PRTL_USER_PROCESS_PARAMETERS NTAPI RtlDeNormalizeProcessParams(
	_Inout_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
);

typedef struct _RTL_USER_PROCESS_INFORMATION
{
	ULONG Length;
	HANDLE Process;
	HANDLE Thread;
	CLIENT_ID ClientId;
	SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

// private
NTSYSAPI NTSTATUS NTAPI RtlCreateUserProcess(
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

#if (NTDDI_VERSION >= NTDDI_VISTA)
DECLSPEC_NORETURN
NTSYSAPI VOID NTAPI RtlExitUserProcess(
	_In_ NTSTATUS ExitStatus
);
#else

#define RtlExitUserProcess RtlExitUserProcess_R

DECLSPEC_NORETURN FORCEINLINE VOID RtlExitUserProcess_R(
	_In_ NTSTATUS ExitStatus)
{
	ExitProcess((NTSTATUS)ExitStatus);
}

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// begin_rev
#define RTL_CLONE_PROCESS_FLAGS_CREATE_SUSPENDED 0x00000001
#define RTL_CLONE_PROCESS_FLAGS_INHERIT_HANDLES 0x00000002
#define RTL_CLONE_PROCESS_FLAGS_NO_SYNCHRONIZE 0x00000004 // don't update synchronization objects
// end_rev

// private
NTSYSAPI NTSTATUS NTAPI RtlCloneUserProcess(
	_In_ ULONG ProcessFlags,
	_In_opt_ PSECURITY_DESCRIPTOR ProcessSecurityDescriptor,
	_In_opt_ PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
	_In_opt_ HANDLE DebugPort,
	_Out_ PRTL_USER_PROCESS_INFORMATION ProcessInformation
);

// private
NTSYSAPI VOID NTAPI RtlUpdateClonedCriticalSection(
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

// private
NTSYSAPI VOID NTAPI RtlUpdateClonedSRWLock(
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
NTSYSAPI NTSTATUS NTAPI RtlCreateProcessReflection(
	_In_ HANDLE ProcessHandle,
	_In_ ULONG Flags,
	_In_opt_ PVOID StartRoutine,
	_In_opt_ PVOID StartContext,
	_In_opt_ HANDLE EventHandle,
	_Out_opt_ PRTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION ReflectionInformation
);
#endif

#endif

NTSYSAPI NTSTATUS STDAPIVCALLTYPE RtlSetProcessIsCritical(
	_In_ BOOLEAN NewValue,
	_Out_opt_ PBOOLEAN OldValue,
	_In_ BOOLEAN CheckFlag
);

NTSYSAPI NTSTATUS STDAPIVCALLTYPE RtlSetThreadIsCritical(
	_In_ BOOLEAN NewValue,
	_Out_opt_ PBOOLEAN OldValue,
	_In_ BOOLEAN CheckFlag
);

// Threads

typedef NTSTATUS(NTAPI *PUSER_THREAD_START_ROUTINE)(
	_In_ PVOID ThreadParameter
	);

NTSYSAPI NTSTATUS NTAPI RtlCreateUserThread(
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
DECLSPEC_NORETURN NTSYSAPI VOID NTAPI RtlExitUserThread(
	_In_ NTSTATUS ExitStatus
);
#else

#define RtlExitUserThread RtlExitUserThread_R

DECLSPEC_NORETURN FORCEINLINE VOID RtlExitUserThread_R(
	_In_ NTSTATUS ExitStatus)
{
	ExitThread((DWORD)ExitStatus);
}

#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI NTSTATUS NTAPI RtlCreateUserStack(
	_In_opt_ SIZE_T CommittedStackSize,
	_In_opt_ SIZE_T MaximumStackSize,
	_In_opt_ ULONG_PTR ZeroBits,
	_In_ SIZE_T PageSize,
	_In_ ULONG_PTR ReserveAlignment,
	_Out_ PINITIAL_TEB InitialTeb
);

// private
NTSYSAPI NTSTATUS NTAPI RtlFreeUserStack(
	_In_ PVOID AllocationBase
);

#endif

NTSYSAPI VOID NTAPI RtlInitializeContext(
	_In_ HANDLE Process,
	_Out_ PCONTEXT Context,
	_In_opt_ PVOID Parameter,
	_In_opt_ PVOID InitialPc,
	_In_opt_ PVOID InitialSp
);

NTSYSAPI NTSTATUS NTAPI RtlRemoteCall(
	_In_ HANDLE Process,
	_In_ HANDLE Thread,
	_In_ PVOID CallSite,
	_In_ ULONG ArgumentCount,
	_In_opt_ PULONG_PTR Arguments,
	_In_ BOOLEAN PassContext,
	_In_ BOOLEAN AlreadySuspended
);

#ifdef _WIN64
// rev
NTSYSAPI NTSTATUS NTAPI RtlWow64GetThreadContext(
	_In_ HANDLE ThreadHandle,
	_Inout_ PWOW64_CONTEXT ThreadContext
);
#endif

#ifdef _WIN64
// rev
NTSYSAPI NTSTATUS NTAPI RtlWow64SetThreadContext(
	_In_ HANDLE ThreadHandle,
	_In_ PWOW64_CONTEXT ThreadContext
);
#endif

// Vectored exception handlers

NTSYSAPI PVOID NTAPI RtlAddVectoredExceptionHandler(
	_In_ ULONG First,
	_In_ PVECTORED_EXCEPTION_HANDLER Handler
);

NTSYSAPI ULONG NTAPI RtlRemoveVectoredExceptionHandler(
	_In_ PVOID Handle
);

NTSYSAPI PVOID NTAPI RtlAddVectoredContinueHandler(
	_In_ ULONG First,
	_In_ PVECTORED_EXCEPTION_HANDLER Handler
);

NTSYSAPI ULONG NTAPI RtlRemoveVectoredContinueHandler(
	_In_ PVOID Handle
);

// Runtime exception handling

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
NTSYSAPI PLIST_ENTRY NTAPI RtlGetFunctionTableListHead(
	VOID
);

#endif

// Images

NTSYSAPI PVOID NTAPI RtlPcToFileHeader(
	_In_ PVOID PcValue,
	_Out_ PVOID *BaseOfImage
);

NTSYSAPI PIMAGE_NT_HEADERS NTAPI RtlImageNtHeader(
	_In_ PVOID Base
);

#define RTL_IMAGE_NT_HEADER_EX_FLAG_NO_RANGE_CHECK 0x00000001

NTSYSAPI NTSTATUS NTAPI RtlImageNtHeaderEx(
	_In_ ULONG Flags,
	_In_ PVOID Base,
	_In_ ULONG64 Size,
	_Out_ PIMAGE_NT_HEADERS *OutHeaders
);

NTSYSAPI PVOID NTAPI RtlAddressInSectionTable(
	_In_ PIMAGE_NT_HEADERS NtHeaders,
	_In_ PVOID BaseOfImage,
	_In_ ULONG VirtualAddress
);

NTSYSAPI PIMAGE_SECTION_HEADER NTAPI RtlSectionTableFromVirtualAddress(
	_In_ PIMAGE_NT_HEADERS NtHeaders,
	_In_ PVOID BaseOfImage,
	_In_ ULONG VirtualAddress
);

NTSYSAPI PVOID NTAPI RtlImageDirectoryEntryToData(
	_In_ PVOID BaseOfImage,
	_In_ BOOLEAN MappedAsImage,
	_In_ USHORT DirectoryEntry,
	_Out_ PULONG Size
);

NTSYSAPI PIMAGE_SECTION_HEADER NTAPI RtlImageRvaToSection(
	_In_ PIMAGE_NT_HEADERS NtHeaders,
	_In_ PVOID Base,
	_In_ ULONG Rva
);

NTSYSAPI PVOID NTAPI RtlImageRvaToVa(
	_In_ PIMAGE_NT_HEADERS NtHeaders,
	_In_ PVOID Base,
	_In_ ULONG Rva,
	_Inout_opt_ PIMAGE_SECTION_HEADER *LastRvaSection
);

// Memory

NTSYSAPI SIZE_T NTAPI RtlCompareMemoryUlong(
	_In_ PVOID Source,
	_In_ SIZE_T Length,
	_In_ ULONG Pattern
);

NTSYSAPI VOID NTAPI RtlFillMemoryUlong(
	_Out_ PVOID Destination,
	_In_ SIZE_T Length,
	_In_ ULONG Pattern
);

NTSYSAPI VOID NTAPI RtlFillMemoryUlonglong(
	_Out_ PVOID Destination,
	_In_ SIZE_T Length,
	_In_ ULONGLONG Pattern
);

// Environment

NTSYSAPI NTSTATUS NTAPI RtlCreateEnvironment(
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
NTSYSAPI NTSTATUS NTAPI RtlCreateEnvironmentEx(
	_In_ PVOID SourceEnv,
	_Out_ PVOID *Environment,
	_In_ ULONG Flags
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlDestroyEnvironment(
	_In_ PVOID Environment
);

NTSYSAPI NTSTATUS NTAPI RtlSetCurrentEnvironment(
	_In_ PVOID Environment,
	_Out_opt_ PVOID *PreviousEnvironment
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlSetEnvironmentVar(
	_In_opt_ PWSTR *Environment,
	_In_reads_(NameLength) PWSTR Name,
	_In_ SIZE_T NameLength,
	_In_reads_(ValueLength) PWSTR Value,
	_In_ SIZE_T ValueLength
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlSetEnvironmentVariable(
	_In_opt_ PVOID *Environment,
	_In_ PUNICODE_STRING Name,
	_In_ PUNICODE_STRING Value
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlQueryEnvironmentVariable(
	_In_opt_ PVOID Environment,
	_In_reads_(NameLength) PWSTR Name,
	_In_ SIZE_T NameLength,
	_Out_writes_(ValueLength) PWSTR Value,
	_In_ SIZE_T ValueLength,
	_Out_ PSIZE_T ReturnLength
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlQueryEnvironmentVariable_U(
	_In_opt_ PVOID Environment,
	_In_ PUNICODE_STRING Name,
	_Out_ PUNICODE_STRING Value
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlExpandEnvironmentStrings(
	_In_opt_ PVOID Environment,
	_In_reads_(SrcLength) PWSTR Src,
	_In_ SIZE_T SrcLength,
	_Out_writes_(DstLength) PWSTR Dst,
	_In_ SIZE_T DstLength,
	_Out_opt_ PSIZE_T ReturnLength
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlExpandEnvironmentStrings_U(
	_In_opt_ PVOID Environment,
	_In_ PUNICODE_STRING Source,
	_Out_ PUNICODE_STRING Destination,
	_Out_opt_ PULONG ReturnedLength
);

NTSYSAPI NTSTATUS NTAPI RtlSetEnvironmentStrings(
	_In_ PWCHAR NewEnvironment,
	_In_ SIZE_T NewEnvironmentSize
);

// Current directory and paths

typedef struct _RTLP_CURDIR_REF *PRTLP_CURDIR_REF;

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

NTSYSAPI RTL_PATH_TYPE NTAPI RtlDetermineDosPathNameType_U(
	_In_ PWSTR DosFileName
);

NTSYSAPI ULONG NTAPI RtlIsDosDeviceName_U(
	_In_ PWSTR DosFileName
);

NTSYSAPI ULONG NTAPI RtlGetFullPathName_U(
	_In_ PWSTR FileName,
	_In_ ULONG BufferLength,
	_Out_writes_bytes_(BufferLength) PWSTR Buffer,
	_Out_opt_ PWSTR *FilePart
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI RtlGetFullPathName_UEx(
	_In_ PWSTR FileName,
	_In_ ULONG BufferLength,
	_Out_writes_bytes_(BufferLength) PWSTR Buffer,
	_Out_opt_ PWSTR *FilePart,
	_Out_opt_ RTL_PATH_TYPE *InputPathType
);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI NTSTATUS NTAPI RtlGetFullPathName_UstrEx(
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

NTSYSAPI ULONG NTAPI RtlGetCurrentDirectory_U(
	_In_ ULONG BufferLength,
	_Out_writes_bytes_(BufferLength) PWSTR Buffer
);

NTSYSAPI NTSTATUS NTAPI RtlSetCurrentDirectory_U(
	_In_ PUNICODE_STRING PathName
);

NTSYSAPI ULONG NTAPI RtlGetLongestNtPathLength(
	VOID
);

NTSYSAPI BOOLEAN NTAPI RtlDosPathNameToNtPathName_U(
	_In_ PWSTR DosFileName,
	_Out_ PUNICODE_STRING NtFileName,
	_Out_opt_ PWSTR *FilePart,
	_Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI NTSTATUS NTAPI RtlDosPathNameToNtPathName_U_WithStatus(
	_In_ PWSTR DosFileName,
	_Out_ PUNICODE_STRING NtFileName,
	_Out_opt_ PWSTR *FilePart,
	_Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI BOOLEAN NTAPI RtlDosPathNameToRelativeNtPathName_U(
	_In_ PWSTR DosFileName,
	_Out_ PUNICODE_STRING NtFileName,
	_Out_opt_ PWSTR *FilePart,
	_Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI NTSTATUS NTAPI RtlDosPathNameToRelativeNtPathName_U_WithStatus(
	_In_ PWSTR DosFileName,
	_Out_ PUNICODE_STRING NtFileName,
	_Out_opt_ PWSTR *FilePart,
	_Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI VOID NTAPI RtlReleaseRelativeName(
	_Inout_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

NTSYSAPI ULONG NTAPI RtlDosSearchPath_U(
	_In_ PWSTR Path,
	_In_ PWSTR FileName,
	_In_opt_ PWSTR Extension,
	_In_ ULONG BufferLength,
	_Out_writes_bytes_(BufferLength) PWSTR Buffer,
	_Out_opt_ PWSTR *FilePart
);

#define RTL_DOS_SEARCH_PATH_FLAG_APPLY_ISOLATION_REDIRECTION 0x00000001
#define RTL_DOS_SEARCH_PATH_FLAG_DISALLOW_DOT_RELATIVE_PATH_SEARCH 0x00000002
#define RTL_DOS_SEARCH_PATH_FLAG_APPLY_DEFAULT_EXTENSION_WHEN_NOT_RELATIVE_PATH_EVEN_IF_FILE_HAS_EXTENSION 0x00000004)

NTSYSAPI NTSTATUS NTAPI RtlDosSearchPath_Ustr(
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

NTSYSAPI BOOLEAN NTAPI RtlDoesFileExists_U(
	_In_ PWSTR FileName
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

typedef struct _RTL_PROCESS_HEAPS
{
	ULONG NumberOfHeaps;
	RTL_HEAP_INFORMATION Heaps[1];
} RTL_PROCESS_HEAPS, *PRTL_PROCESS_HEAPS;

typedef NTSTATUS(NTAPI *PRTL_HEAP_COMMIT_ROUTINE)(
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

NTSYSAPI PVOID NTAPI RtlCreateHeap(
	_In_ ULONG Flags,
	_In_opt_ PVOID HeapBase,
	_In_opt_ SIZE_T ReserveSize,
	_In_opt_ SIZE_T CommitSize,
	_In_opt_ PVOID Lock,
	_In_opt_ PRTL_HEAP_PARAMETERS Parameters
);

NTSYSAPI PVOID NTAPI RtlDestroyHeap(
	_Frees_ptr_ PVOID HeapHandle
);

NTSYSAPI PVOID NTAPI RtlAllocateHeap(
	_In_ PVOID HeapHandle,
	_In_opt_ ULONG Flags,
	_In_ SIZE_T Size
);

NTSYSAPI BOOLEAN NTAPI RtlFreeHeap(
	_In_ PVOID HeapHandle,
	_In_opt_ ULONG Flags,
	_Frees_ptr_opt_ PVOID BaseAddress
);

NTSYSAPI SIZE_T NTAPI RtlSizeHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags,
	_In_ PVOID BaseAddress
);

NTSYSAPI NTSTATUS NTAPI RtlZeroHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags
);

NTSYSAPI VOID NTAPI RtlProtectHeap(
	_In_ PVOID HeapHandle,
	_In_ BOOLEAN MakeReadOnly
);

FORCEINLINE HANDLE RtlProcessHeap()
{
	return NtCurrentPeb()->ProcessHeap;
}

NTSYSAPI BOOLEAN NTAPI RtlLockHeap(
	_In_ PVOID HeapHandle
);

NTSYSAPI BOOLEAN NTAPI RtlUnlockHeap(
	_In_ PVOID HeapHandle
);

NTSYSAPI PVOID NTAPI RtlReAllocateHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags,
	_Frees_ptr_opt_ PVOID BaseAddress,
	_In_ SIZE_T Size
);

NTSYSAPI BOOLEAN NTAPI RtlGetUserInfoHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags,
	_In_ PVOID BaseAddress,
	_Out_opt_ PVOID *UserValue,
	_Out_opt_ PULONG UserFlags
);

NTSYSAPI BOOLEAN NTAPI RtlSetUserValueHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags,
	_In_ PVOID BaseAddress,
	_In_ PVOID UserValue
);

NTSYSAPI BOOLEAN NTAPI RtlSetUserFlagsHeap(
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

NTSYSAPI ULONG NTAPI RtlCreateTagHeap(
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

NTSYSAPI NTSTATUS NTAPI RtlExtendHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags,
	_In_ PVOID Base,
	_In_ SIZE_T Size
);

NTSYSAPI SIZE_T NTAPI RtlCompactHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags
);

NTSYSAPI BOOLEAN NTAPI RtlValidateHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags,
	_In_ PVOID BaseAddress
);

NTSYSAPI BOOLEAN NTAPI RtlValidateProcessHeaps(
	VOID
);

NTSYSAPI ULONG NTAPI RtlGetProcessHeaps(
	_In_ ULONG NumberOfHeaps,
	_Out_ PVOID *ProcessHeaps
);

typedef NTSTATUS(NTAPI *PRTL_ENUM_HEAPS_ROUTINE)(
	_In_ PVOID HeapHandle,
	_In_ PVOID Parameter
	);

NTSYSAPI NTSTATUS NTAPI RtlEnumProcessHeaps(
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

NTSYSAPI NTSTATUS NTAPI RtlUsageHeap(
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

NTSYSAPI NTSTATUS NTAPI RtlWalkHeap(
	_In_ PVOID HeapHandle,
	_Inout_ PRTL_HEAP_WALK_ENTRY Entry
);

// rev
#define HeapDebuggingInformation 0x80000002

// rev
typedef NTSTATUS(NTAPI *PRTL_HEAP_LEAK_ENUMERATION_ROUTINE)(
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

NTSYSAPI NTSTATUS NTAPI RtlQueryHeapInformation(
	_In_ PVOID HeapHandle,
	_In_ HEAP_INFORMATION_CLASS HeapInformationClass,
	_Out_opt_ PVOID HeapInformation,
	_In_opt_ SIZE_T HeapInformationLength,
	_Out_opt_ PSIZE_T ReturnLength
);

NTSYSAPI NTSTATUS NTAPI RtlSetHeapInformation(
	_In_ PVOID HeapHandle,
	_In_ HEAP_INFORMATION_CLASS HeapInformationClass,
	_In_opt_ PVOID HeapInformation,
	_In_opt_ SIZE_T HeapInformationLength
);

NTSYSAPI ULONG NTAPI RtlMultipleAllocateHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags,
	_In_ SIZE_T Size,
	_In_ ULONG Count,
	_Out_ PVOID *Array
);

NTSYSAPI ULONG NTAPI RtlMultipleFreeHeap(
	_In_ PVOID HeapHandle,
	_In_ ULONG Flags,
	_In_ ULONG Count,
	_In_ PVOID *Array
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI VOID NTAPI RtlDetectHeapLeaks(
	VOID
);
#endif

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

NTSYSAPI NTSTATUS NTAPI RtlCreateMemoryZone(
	_Out_ PVOID *MemoryZone,
	_In_ SIZE_T InitialSize,
	_Reserved_ ULONG Flags
);

NTSYSAPI NTSTATUS NTAPI RtlDestroyMemoryZone(
	_In_ _Post_invalid_ PVOID MemoryZone
);

NTSYSAPI NTSTATUS NTAPI RtlAllocateMemoryZone(
	_In_ PVOID MemoryZone,
	_In_ SIZE_T BlockSize,
	_Out_ PVOID *Block
);

NTSYSAPI NTSTATUS NTAPI RtlResetMemoryZone(
	_In_ PVOID MemoryZone
);

NTSYSAPI NTSTATUS NTAPI RtlLockMemoryZone(
	_In_ PVOID MemoryZone
);

NTSYSAPI NTSTATUS NTAPI RtlUnlockMemoryZone(
	_In_ PVOID MemoryZone
);

#endif

// end_private

// Memory block lookaside lists

// begin_private

#if (NTDDI_VERSION >= NTDDI_VISTA)

NTSYSAPI NTSTATUS NTAPI RtlCreateMemoryBlockLookaside(
	_Out_ PVOID *MemoryBlockLookaside,
	_Reserved_ ULONG Flags,
	_In_ ULONG InitialSize,
	_In_ ULONG MinimumBlockSize,
	_In_ ULONG MaximumBlockSize
);

NTSYSAPI NTSTATUS NTAPI RtlDestroyMemoryBlockLookaside(
	_In_ PVOID MemoryBlockLookaside
);

NTSYSAPI NTSTATUS NTAPI RtlAllocateMemoryBlockLookaside(
	_In_ PVOID MemoryBlockLookaside,
	_In_ ULONG BlockSize,
	_Out_ PVOID *Block
);

NTSYSAPI NTSTATUS NTAPI RtlFreeMemoryBlockLookaside(
	_In_ PVOID MemoryBlockLookaside,
	_In_ PVOID Block
);

NTSYSAPI NTSTATUS NTAPI RtlExtendMemoryBlockLookaside(
	_In_ PVOID MemoryBlockLookaside,
	_In_ ULONG Increment
);

NTSYSAPI NTSTATUS NTAPI RtlResetMemoryBlockLookaside(
	_In_ PVOID MemoryBlockLookaside
);

NTSYSAPI NTSTATUS NTAPI RtlLockMemoryBlockLookaside(
	_In_ PVOID MemoryBlockLookaside
);

NTSYSAPI NTSTATUS NTAPI RtlUnlockMemoryBlockLookaside(
	_In_ PVOID MemoryBlockLookaside
);

#endif

// end_private

// Transactions

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI HANDLE NTAPI RtlGetCurrentTransaction(
	VOID
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI LOGICAL NTAPI RtlSetCurrentTransaction(
	_In_ HANDLE TransactionHandle
);
#endif

// LUIDs

FORCEINLINE BOOLEAN RtlIsEqualLuid(
	_In_ PLUID L1,
	_In_ PLUID L2
)
{
	return (BOOLEAN)(L1->LowPart == L2->LowPart &&
		L1->HighPart == L2->HighPart);
}

FORCEINLINE BOOLEAN RtlIsZeroLuid(
	_In_ PLUID L1
)
{
	return (BOOLEAN)((L1->LowPart | L1->HighPart) == 0);
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

NTSYSAPI VOID NTAPI RtlCopyLuid(
	_Out_ PLUID DestinationLuid,
	_In_ PLUID SourceLuid
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

NTSYSAPI NTSTATUS NTAPI RtlDestroyQueryDebugBuffer(
	_In_ PRTL_DEBUG_INFORMATION Buffer
);

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
NTSYSAPI PVOID NTAPI RtlCommitDebugInfo(
	_Inout_ PRTL_DEBUG_INFORMATION Buffer,
	_In_ SIZE_T Size
);

// private
NTSYSAPI VOID NTAPI RtlDeCommitDebugInfo(
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

NTSYSAPI NTSTATUS NTAPI RtlQueryProcessDebugInformation(
	_In_ HANDLE UniqueProcessId,
	_In_ ULONG Flags,
	_Inout_ PRTL_DEBUG_INFORMATION Buffer
);

// Messages

NTSYSAPI NTSTATUS NTAPI RtlFindMessage(
	_In_ PVOID DllHandle,
	_In_ ULONG MessageTableId,
	_In_ ULONG MessageLanguageId,
	_In_ ULONG MessageId,
	_Out_ PMESSAGE_RESOURCE_ENTRY *MessageEntry
);

NTSYSAPI NTSTATUS NTAPI RtlFormatMessage(
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

#define INIT_PARSE_MESSAGE_CONTEXT(ctx) \
    { \
        (ctx)->fFlags = 0; \
    }

#define TEST_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag) ((ctx)->fFlags & (flag))
#define SET_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag) ((ctx)->fFlags |= (flag))
#define CLEAR_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag) ((ctx)->fFlags &= ~(flag))

NTSYSAPI NTSTATUS NTAPI RtlFormatMessageEx(
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

// Errors

NTSYSAPI ULONG NTAPI RtlNtStatusToDosError(
	_In_ NTSTATUS Status
);

NTSYSAPI ULONG NTAPI RtlNtStatusToDosErrorNoTeb(
	_In_ NTSTATUS Status
);

NTSYSAPI NTSTATUS NTAPI RtlGetLastNtStatus(
	VOID
);

NTSYSAPI LONG NTAPI RtlGetLastWin32Error(
	VOID
);

NTSYSAPI VOID NTAPI RtlSetLastWin32ErrorAndNtStatusFromNtStatus(
	_In_ NTSTATUS Status
);

NTSYSAPI VOID NTAPI RtlSetLastWin32Error(
	_In_ LONG Win32Error
);

NTSYSAPI VOID NTAPI RtlRestoreLastWin32Error(
	_In_ LONG Win32Error
);

#define RTL_ERRORMODE_NOGPFAULTERRORBOX 0x0020
#define RTL_ERRORMODE_NOOPENFILEERRORBOX 0x0040

NTSYSAPI ULONG NTAPI RtlGetThreadErrorMode(
	VOID
);

NTSYSAPI NTSTATUS NTAPI RtlSetThreadErrorMode(
	_In_ ULONG NewMode,
	_Out_opt_ PULONG OldMode
);

// Windows Error Reporting

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlReportException(
	_In_ PEXCEPTION_RECORD ExceptionRecord,
	_In_ PCONTEXT ContextRecord,
	_In_ ULONG Flags
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlWerpReportException(
	_In_ ULONG ProcessId,
	_In_ HANDLE CrashReportSharedMem,
	_In_ ULONG Flags,
	_Out_ PHANDLE CrashVerticalProcessHandle
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI RtlReportSilentProcessExit(
	_In_ HANDLE ProcessHandle,
	_In_ NTSTATUS ExitStatus
);
#endif

// Vectored Exception Handlers

NTSYSAPI PVOID NTAPI RtlAddVectoredExceptionHandler(
	_In_ ULONG First,
	_In_ PVECTORED_EXCEPTION_HANDLER Handler
);

NTSYSAPI ULONG NTAPI RtlRemoveVectoredExceptionHandler(
	_In_ PVOID Handle
);

NTSYSAPI PVOID NTAPI RtlAddVectoredContinueHandler(
	_In_ ULONG First,
	_In_ PVECTORED_EXCEPTION_HANDLER Handler
);

NTSYSAPI ULONG NTAPI RtlRemoveVectoredContinueHandler(
	_In_ PVOID Handle
);

// Random

NTSYSAPI ULONG NTAPI RtlUniform(
	_Inout_ PULONG Seed
);

NTSYSAPI ULONG NTAPI RtlRandom(
	_Inout_ PULONG Seed
);

NTSYSAPI ULONG NTAPI RtlRandomEx(
	_Inout_ PULONG Seed
);

NTSYSAPI NTSTATUS NTAPI RtlComputeImportTableHash(
	_In_ HANDLE hFile,
	_Out_writes_bytes_(16) PCHAR Hash,
	_In_ ULONG ImportTableHashRevision // must be 1
);

// Integer conversion

NTSYSAPI NTSTATUS NTAPI RtlIntegerToChar(
	_In_ ULONG Value,
	_In_opt_ ULONG Base,
	_In_ LONG OutputLength, // negative to pad to width
	_Out_ PSTR String
);

NTSYSAPI NTSTATUS NTAPI RtlCharToInteger(
	_In_ PSTR String,
	_In_opt_ ULONG Base,
	_Out_ PULONG Value
);

NTSYSAPI NTSTATUS NTAPI RtlLargeIntegerToChar(
	_In_ PLARGE_INTEGER Value,
	_In_opt_ ULONG Base,
	_In_ LONG OutputLength,
	_Out_ PSTR String
);

NTSYSAPI NTSTATUS NTAPI RtlIntegerToUnicodeString(
	_In_ ULONG Value,
	_In_opt_ ULONG Base,
	_Inout_ PUNICODE_STRING String
);

NTSYSAPI NTSTATUS NTAPI RtlInt64ToUnicodeString(
	_In_ ULONGLONG Value,
	_In_opt_ ULONG Base,
	_Inout_ PUNICODE_STRING String
);

#ifdef _WIN64
#define RtlIntPtrToUnicodeString(Value, Base, String) RtlInt64ToUnicodeString(Value, Base, String)
#else
#define RtlIntPtrToUnicodeString(Value, Base, String) RtlIntegerToUnicodeString(Value, Base, String)
#endif

NTSYSAPI NTSTATUS NTAPI RtlUnicodeStringToInteger(
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
	_In_ struct in_addr *Addr,
	_Out_writes_(16) PWSTR S
);

NTSYSAPI NTSTATUS NTAPI RtlIpv4AddressToStringExW(
	_In_ struct in_addr *Address,
	_In_ USHORT Port,
	_Out_writes_to_(*AddressStringLength, *AddressStringLength) PWSTR AddressString,
	_Inout_ PULONG AddressStringLength
);

NTSYSAPI
PWSTR
NTAPI
RtlIpv6AddressToStringW(
	_In_ struct in6_addr *Addr,
	_Out_writes_(65) PWSTR S
);

NTSYSAPI NTSTATUS NTAPI RtlIpv6AddressToStringExW(
	_In_ struct in6_addr *Address,
	_In_ ULONG ScopeId,
	_In_ USHORT Port,
	_Out_writes_to_(*AddressStringLength, *AddressStringLength) PWSTR AddressString,
	_Inout_ PULONG AddressStringLength
);

NTSYSAPI NTSTATUS NTAPI RtlIpv4StringToAddressW(
	_In_ PWSTR S,
	_In_ BOOLEAN Strict,
	_Out_ PWSTR *Terminator,
	_Out_ struct in_addr *Addr
);

NTSYSAPI NTSTATUS NTAPI RtlIpv4StringToAddressExW(
	_In_ PWSTR AddressString,
	_In_ BOOLEAN Strict,
	_Out_ struct in_addr *Address,
	_Out_ PUSHORT Port
);

NTSYSAPI NTSTATUS NTAPI RtlIpv6StringToAddressW(
	_In_ PWSTR S,
	_Out_ PWSTR *Terminator,
	_Out_ struct in6_addr *Addr
);

NTSYSAPI NTSTATUS NTAPI RtlIpv6StringToAddressExW(
	_In_ PWSTR AddressString,
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

NTSYSAPI BOOLEAN NTAPI RtlCutoverTimeToSystemTime(
	_In_ PTIME_FIELDS CutoverTime,
	_Out_ PLARGE_INTEGER SystemTime,
	_In_ PLARGE_INTEGER CurrentSystemTime,
	_In_ BOOLEAN ThisYear
);

NTSYSAPI NTSTATUS NTAPI RtlSystemTimeToLocalTime(
	_In_ PLARGE_INTEGER SystemTime,
	_Out_ PLARGE_INTEGER LocalTime
);

NTSYSAPI NTSTATUS NTAPI RtlLocalTimeToSystemTime(
	_In_ PLARGE_INTEGER LocalTime,
	_Out_ PLARGE_INTEGER SystemTime
);

NTSYSAPI VOID NTAPI RtlTimeToElapsedTimeFields(
	_In_ PLARGE_INTEGER Time,
	_Out_ PTIME_FIELDS TimeFields
);

NTSYSAPI VOID NTAPI RtlTimeToTimeFields(
	_In_ PLARGE_INTEGER Time,
	_Out_ PTIME_FIELDS TimeFields
);

NTSYSAPI BOOLEAN NTAPI RtlTimeFieldsToTime(
	_In_ PTIME_FIELDS TimeFields, // Weekday is ignored
	_Out_ PLARGE_INTEGER Time
);

NTSYSAPI BOOLEAN NTAPI RtlTimeToSecondsSince1980(
	_In_ PLARGE_INTEGER Time,
	_Out_ PULONG ElapsedSeconds
);

NTSYSAPI VOID NTAPI RtlSecondsSince1980ToTime(
	_In_ ULONG ElapsedSeconds,
	_Out_ PLARGE_INTEGER Time
);

NTSYSAPI BOOLEAN NTAPI RtlTimeToSecondsSince1970(
	_In_ PLARGE_INTEGER Time,
	_Out_ PULONG ElapsedSeconds
);

NTSYSAPI VOID NTAPI RtlSecondsSince1970ToTime(
	_In_ ULONG ElapsedSeconds,
	_Out_ PLARGE_INTEGER Time
);

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

NTSYSAPI NTSTATUS NTAPI RtlQueryTimeZoneInformation(
	_Out_ PRTL_TIME_ZONE_INFORMATION TimeZoneInformation
);

NTSYSAPI NTSTATUS NTAPI RtlSetTimeZoneInformation(
	_In_ PRTL_TIME_ZONE_INFORMATION TimeZoneInformation
);

// Bitmaps

typedef struct _RTL_BITMAP
{
	ULONG SizeOfBitMap;
	PULONG Buffer;
} RTL_BITMAP, *PRTL_BITMAP;

NTSYSAPI VOID NTAPI RtlInitializeBitMap(
	_Out_ PRTL_BITMAP BitMapHeader,
	_In_ PULONG BitMapBuffer,
	_In_ ULONG SizeOfBitMap
);

_Check_return_
NTSYSAPI BOOLEAN NTAPI RtlTestBit(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitNumber
);

NTSYSAPI VOID NTAPI RtlClearAllBits(
	_In_ PRTL_BITMAP BitMapHeader
);

NTSYSAPI VOID NTAPI RtlSetAllBits(
	_In_ PRTL_BITMAP BitMapHeader
);

_Success_(return != -1)
_Check_return_
NTSYSAPI ULONG NTAPI RtlFindClearBits(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_ ULONG NumberToFind,
	_In_ ULONG HintIndex
);

_Success_(return != -1)
_Check_return_
NTSYSAPI ULONG NTAPI RtlFindSetBits(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_ ULONG NumberToFind,
	_In_ ULONG HintIndex
);

_Success_(return != -1)
NTSYSAPI ULONG NTAPI RtlFindClearBitsAndSet(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_ ULONG NumberToFind,
	_In_ ULONG HintIndex
);

_Success_(return != -1)
NTSYSAPI ULONG NTAPI RtlFindSetBitsAndClear(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_ ULONG NumberToFind,
	_In_ ULONG HintIndex
);

NTSYSAPI VOID NTAPI RtlClearBits(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
	_In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear
);

NTSYSAPI VOID NTAPI RtlSetBits(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
	_In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet
);

typedef struct _RTL_BITMAP_RUN
{
	ULONG StartingIndex;
	ULONG NumberOfBits;
} RTL_BITMAP_RUN, *PRTL_BITMAP_RUN;

NTSYSAPI ULONG NTAPI RtlFindClearRuns(
	_In_ PRTL_BITMAP BitMapHeader,
	_Out_writes_to_(SizeOfRunArray, return) PRTL_BITMAP_RUN RunArray,
	_In_range_(>, 0) ULONG SizeOfRunArray,
	_In_ BOOLEAN LocateLongestRuns
);

NTSYSAPI ULONG NTAPI RtlFindLongestRunClear(
	_In_ PRTL_BITMAP BitMapHeader,
	_Out_ PULONG StartingIndex
);

NTSYSAPI ULONG NTAPI RtlFindFirstRunClear(
	_In_ PRTL_BITMAP BitMapHeader,
	_Out_ PULONG StartingIndex
);

_Check_return_
FORCEINLINE BOOLEAN RtlCheckBit(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_range_(<, BitMapHeader->SizeOfBitMap) ULONG BitPosition)
{
#ifdef _WIN64
	return BitTest64((LONG64 const *)BitMapHeader->Buffer, (LONG64)BitPosition);
#else
	return (BOOLEAN)((((PLONG)BitMapHeader->Buffer)[BitPosition / 32] >> (BitPosition % 32)) & 0x1);
#endif
}

NTSYSAPI ULONG NTAPI RtlNumberOfClearBits(
	_In_ PRTL_BITMAP BitMapHeader
);

NTSYSAPI ULONG NTAPI RtlNumberOfSetBits(
	_In_ PRTL_BITMAP BitMapHeader
);

_Check_return_
NTSYSAPI BOOLEAN NTAPI RtlAreBitsClear(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_ ULONG StartingIndex,
	_In_ ULONG Length
);

_Check_return_
NTSYSAPI BOOLEAN NTAPI RtlAreBitsSet(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_ ULONG StartingIndex,
	_In_ ULONG Length
);

NTSYSAPI ULONG NTAPI RtlFindNextForwardRunClear(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_ ULONG FromIndex,
	_Out_ PULONG StartingRunIndex
);

NTSYSAPI ULONG NTAPI RtlFindLastBackwardRunClear(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_ ULONG FromIndex,
	_Out_ PULONG StartingRunIndex
);

#if (NTDDI_VERSION >= NTDDI_WIN7)

// rev
NTSYSAPI VOID NTAPI RtlInterlockedClearBitRun(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
	_In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear
);

// rev
NTSYSAPI VOID NTAPI RtlInterlockedSetBitRun(
	_In_ PRTL_BITMAP BitMapHeader,
	_In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
	_In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet
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

NTSYSAPI VOID NTAPI RtlInitializeHandleTable(
	_In_ ULONG MaximumNumberOfHandles,
	_In_ ULONG SizeOfHandleTableEntry,
	_Out_ PRTL_HANDLE_TABLE HandleTable
);

NTSYSAPI NTSTATUS NTAPI RtlDestroyHandleTable(
	_Inout_ PRTL_HANDLE_TABLE HandleTable
);

NTSYSAPI PRTL_HANDLE_TABLE_ENTRY NTAPI RtlAllocateHandle(
	_In_ PRTL_HANDLE_TABLE HandleTable,
	_Out_opt_ PULONG HandleIndex
);

NTSYSAPI BOOLEAN NTAPI RtlFreeHandle(
	_In_ PRTL_HANDLE_TABLE HandleTable,
	_In_ PRTL_HANDLE_TABLE_ENTRY Handle
);

NTSYSAPI BOOLEAN NTAPI RtlIsValidHandle(
	_In_ PRTL_HANDLE_TABLE HandleTable,
	_In_ PRTL_HANDLE_TABLE_ENTRY Handle
);

NTSYSAPI BOOLEAN NTAPI RtlIsValidIndexHandle(
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

NTSYSAPI NTSTATUS NTAPI RtlCreateAtomTable(
	_In_ ULONG NumberOfBuckets,
	_Out_ PVOID *AtomTableHandle
);

NTSYSAPI NTSTATUS NTAPI RtlDestroyAtomTable(
	_In_ _Post_invalid_ PVOID AtomTableHandle
);

NTSYSAPI NTSTATUS NTAPI RtlEmptyAtomTable(
	_In_ PVOID AtomTableHandle,
	_In_ BOOLEAN IncludePinnedAtoms
);

NTSYSAPI NTSTATUS NTAPI RtlAddAtomToAtomTable(
	_In_ PVOID AtomTableHandle,
	_In_ PWSTR AtomName,
	_Inout_opt_ PRTL_ATOM Atom
);

NTSYSAPI NTSTATUS NTAPI RtlLookupAtomInAtomTable(
	_In_ PVOID AtomTableHandle,
	_In_ PWSTR AtomName,
	_Out_opt_ PRTL_ATOM Atom
);

NTSYSAPI NTSTATUS NTAPI RtlDeleteAtomFromAtomTable(
	_In_ PVOID AtomTableHandle,
	_In_ RTL_ATOM Atom
);

NTSYSAPI NTSTATUS NTAPI RtlPinAtomInAtomTable(
	_In_ PVOID AtomTableHandle,
	_In_ RTL_ATOM Atom
);

NTSYSAPI NTSTATUS NTAPI RtlQueryAtomInAtomTable(
	_In_ PVOID AtomTableHandle,
	_In_ RTL_ATOM Atom,
	_Out_opt_ PULONG AtomUsage,
	_Out_opt_ PULONG AtomFlags,
	_Inout_updates_bytes_to_opt_(*AtomNameLength, *AtomNameLength) PWSTR AtomName,
	_Inout_opt_ PULONG AtomNameLength
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// rev
NTSYSAPI BOOLEAN NTAPI RtlGetIntegerAtom(
	_In_ PWSTR AtomName,
	_Out_opt_ PUSHORT IntegerAtom
);
#endif

// SIDs

_Check_return_
NTSYSAPI BOOLEAN NTAPI RtlValidSid(
	_In_ PSID Sid
);

_Check_return_
NTSYSAPI BOOLEAN NTAPI RtlEqualSid(
	_In_ PSID Sid1,
	_In_ PSID Sid2
);

NTSYSAPI ULONG NTAPI RtlLengthRequiredSid(
	_In_ ULONG SubAuthorityCount
);

NTSYSAPI PVOID NTAPI RtlFreeSid(
	_In_ _Post_invalid_ PSID Sid
);

_Check_return_
NTSYSAPI NTSTATUS NTAPI RtlAllocateAndInitializeSid(
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

NTSYSAPI NTSTATUS NTAPI RtlInitializeSid(
	_Out_ PSID Sid,
	_In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
	_In_ UCHAR SubAuthorityCount
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSAPI NTSTATUS NTAPI RtlInitializeSidEx(
	_Out_writes_bytes_(SECURITY_SID_SIZE(SubAuthorityCount)) PSID Sid,
	_In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
	_In_ UCHAR SubAuthorityCount,
	...
);
#endif

NTSYSAPI PSID_IDENTIFIER_AUTHORITY NTAPI RtlIdentifierAuthoritySid(
	_In_ PSID Sid
);

NTSYSAPI PULONG NTAPI RtlSubAuthoritySid(
	_In_ PSID Sid,
	_In_ ULONG SubAuthority
);

NTSYSAPI PUCHAR NTAPI RtlSubAuthorityCountSid(
	_In_ PSID Sid
);

NTSYSAPI ULONG NTAPI RtlLengthSid(
	_In_ PSID Sid
);

NTSYSAPI NTSTATUS NTAPI RtlCopySid(
	_In_ ULONG DestinationSidLength,
	_In_reads_bytes_(DestinationSidLength) PSID DestinationSid,
	_In_ PSID SourceSid
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI NTSTATUS NTAPI RtlCreateServiceSid(
	_In_ PUNICODE_STRING ServiceName,
	_Out_writes_bytes_opt_(*ServiceSidLength) PSID ServiceSid,
	_Inout_ PULONG ServiceSidLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlSidDominates(
	_In_ PSID Sid1,
	_In_ PSID Sid2,
	_Out_ PBOOLEAN pbDominate
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlSidEqualLevel(
	_In_ PSID Sid1,
	_In_ PSID Sid2,
	_Out_ PBOOLEAN pbEqual
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlSidIsHigherLevel(
	_In_ PSID Sid1,
	_In_ PSID Sid2,
	_Out_ PBOOLEAN pbHigher
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI NTSTATUS NTAPI RtlCreateVirtualAccountSid(
	_In_ PUNICODE_STRING Name,
	_In_ ULONG BaseSubAuthority,
	_Out_writes_bytes_(*SidLength) PSID Sid,
	_Inout_ PULONG SidLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI NTSTATUS NTAPI RtlReplaceSidInSd(
	_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ PSID OldSid,
	_In_ PSID NewSid,
	_Out_ ULONG *NumChanges
);
#endif

#define MAX_UNICODE_STACK_BUFFER_LENGTH 256

NTSYSAPI NTSTATUS NTAPI RtlConvertSidToUnicodeString(
	_Inout_ PUNICODE_STRING UnicodeString,
	_In_ PSID Sid,
	_In_ BOOLEAN AllocateDestinationString
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlSidHashInitialize(
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

// Security Descriptors

NTSYSAPI NTSTATUS NTAPI RtlCreateSecurityDescriptor(
	_Out_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ ULONG Revision
);

_Check_return_
NTSYSAPI BOOLEAN NTAPI RtlValidSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

NTSYSAPI ULONG NTAPI RtlLengthSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

_Check_return_
NTSYSAPI BOOLEAN NTAPI RtlValidRelativeSecurityDescriptor(
	_In_reads_bytes_(SecurityDescriptorLength) PSECURITY_DESCRIPTOR SecurityDescriptorInput,
	_In_ ULONG SecurityDescriptorLength,
	_In_ SECURITY_INFORMATION RequiredInformation
);

NTSYSAPI NTSTATUS NTAPI RtlGetControlSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PSECURITY_DESCRIPTOR_CONTROL Control,
	_Out_ PULONG Revision
);

NTSYSAPI NTSTATUS NTAPI RtlSetControlSecurityDescriptor(
	_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,
	_In_ SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet
);

NTSYSAPI NTSTATUS NTAPI RtlSetAttributesSecurityDescriptor(
	_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ SECURITY_DESCRIPTOR_CONTROL Control,
	_Out_ PULONG Revision
);

NTSYSAPI BOOLEAN NTAPI RtlGetSecurityDescriptorRMControl(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PUCHAR RMControl
);

NTSYSAPI VOID NTAPI RtlSetSecurityDescriptorRMControl(
	_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_opt_ PUCHAR RMControl
);

NTSYSAPI NTSTATUS NTAPI RtlSetDaclSecurityDescriptor(
	_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ BOOLEAN DaclPresent,
	_In_opt_ PACL Dacl,
	_In_opt_ BOOLEAN DaclDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlGetDaclSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PBOOLEAN DaclPresent,
	_Out_ PACL *Dacl,
	_Out_ PBOOLEAN DaclDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlSetSaclSecurityDescriptor(
	_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ BOOLEAN SaclPresent,
	_In_opt_ PACL Sacl,
	_In_opt_ BOOLEAN SaclDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlGetSaclSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PBOOLEAN SaclPresent,
	_Out_ PACL *Sacl,
	_Out_ PBOOLEAN SaclDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlGetSaclSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PBOOLEAN SaclPresent,
	_Out_ PACL *Sacl,
	_Out_ PBOOLEAN SaclDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlSetOwnerSecurityDescriptor(
	_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_opt_ PSID Owner,
	_In_opt_ BOOLEAN OwnerDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlGetOwnerSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PSID *Owner,
	_Out_ PBOOLEAN OwnerDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlSetGroupSecurityDescriptor(
	_Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_opt_ PSID Group,
	_In_opt_ BOOLEAN GroupDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlGetGroupSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PSID *Group,
	_Out_ PBOOLEAN GroupDefaulted
);

NTSYSAPI NTSTATUS NTAPI RtlMakeSelfRelativeSD(
	_In_ PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
	_Out_writes_bytes_(*BufferLength) PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
	_Inout_ PULONG BufferLength
);

NTSYSAPI NTSTATUS NTAPI RtlAbsoluteToSelfRelativeSD(
	_In_ PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
	_Out_writes_bytes_to_opt_(*BufferLength, *BufferLength) PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
	_Inout_ PULONG BufferLength
);

NTSYSAPI NTSTATUS NTAPI RtlSelfRelativeToAbsoluteSD(
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
NTSYSAPI NTSTATUS NTAPI RtlSelfRelativeToAbsoluteSD2(
	_Inout_ PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,
	_Inout_ PULONG pBufferSize
);

// Access masks

NTSYSAPI BOOLEAN NTAPI RtlAreAllAccessesGranted(
	_In_ ACCESS_MASK GrantedAccess,
	_In_ ACCESS_MASK DesiredAccess
);

NTSYSAPI BOOLEAN NTAPI RtlAreAnyAccessesGranted(
	_In_ ACCESS_MASK GrantedAccess,
	_In_ ACCESS_MASK DesiredAccess
);

NTSYSAPI VOID NTAPI RtlMapGenericMask(
	_Inout_ PACCESS_MASK AccessMask,
	_In_ PGENERIC_MAPPING GenericMapping
);

// ACLs

NTSYSAPI NTSTATUS NTAPI RtlCreateAcl(
	_Out_writes_bytes_(AclLength) PACL Acl,
	_In_ ULONG AclLength,
	_In_ ULONG AclRevision
);

NTSYSAPI BOOLEAN NTAPI RtlValidAcl(
	_In_ PACL Acl
);

NTSYSAPI NTSTATUS NTAPI RtlQueryInformationAcl(
	_In_ PACL Acl,
	_Out_writes_bytes_(AclInformationLength) PVOID AclInformation,
	_In_ ULONG AclInformationLength,
	_In_ ACL_INFORMATION_CLASS AclInformationClass
);

NTSYSAPI NTSTATUS NTAPI RtlSetInformationAcl(
	_Inout_ PACL Acl,
	_In_reads_bytes_(AclInformationLength) PVOID AclInformation,
	_In_ ULONG AclInformationLength,
	_In_ ACL_INFORMATION_CLASS AclInformationClass
);

NTSYSAPI NTSTATUS NTAPI RtlAddAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ULONG StartingAceIndex,
	_In_reads_bytes_(AceListLength) PVOID AceList,
	_In_ ULONG AceListLength
);

NTSYSAPI NTSTATUS NTAPI RtlDeleteAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceIndex
);

NTSYSAPI NTSTATUS NTAPI RtlGetAce(
	_In_ PACL Acl,
	_In_ ULONG AceIndex,
	_Outptr_ PVOID *Ace
);

NTSYSAPI BOOLEAN NTAPI RtlFirstFreeAce(
	_In_ PACL Acl,
	_Out_ PVOID *FirstFree
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI PVOID NTAPI RtlFindAceByType(
	_In_ PACL pAcl,
	_In_ UCHAR AceType,
	_Out_opt_ PULONG pIndex
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI BOOLEAN NTAPI RtlOwnerAcesPresent(
	_In_ PACL pAcl
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlAddAccessAllowedAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ACCESS_MASK AccessMask,
	_In_ PSID Sid
);

NTSYSAPI NTSTATUS NTAPI RtlAddAccessAllowedAceEx(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ULONG AceFlags,
	_In_ ACCESS_MASK AccessMask,
	_In_ PSID Sid
);

NTSYSAPI NTSTATUS NTAPI RtlAddAccessDeniedAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ACCESS_MASK AccessMask,
	_In_ PSID Sid
);

NTSYSAPI NTSTATUS NTAPI RtlAddAccessDeniedAceEx(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ULONG AceFlags,
	_In_ ACCESS_MASK AccessMask,
	_In_ PSID Sid
);

NTSYSAPI NTSTATUS NTAPI RtlAddAuditAccessAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ACCESS_MASK AccessMask,
	_In_ PSID Sid,
	_In_ BOOLEAN AuditSuccess,
	_In_ BOOLEAN AuditFailure
);

NTSYSAPI NTSTATUS NTAPI RtlAddAuditAccessAceEx(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ULONG AceFlags,
	_In_ ACCESS_MASK AccessMask,
	_In_ PSID Sid,
	_In_ BOOLEAN AuditSuccess,
	_In_ BOOLEAN AuditFailure
);

NTSYSAPI NTSTATUS NTAPI RtlAddAccessAllowedObjectAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ULONG AceFlags,
	_In_ ACCESS_MASK AccessMask,
	_In_opt_ PGUID ObjectTypeGuid,
	_In_opt_ PGUID InheritedObjectTypeGuid,
	_In_ PSID Sid
);

NTSYSAPI NTSTATUS NTAPI RtlAddAccessDeniedObjectAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ULONG AceFlags,
	_In_ ACCESS_MASK AccessMask,
	_In_opt_ PGUID ObjectTypeGuid,
	_In_opt_ PGUID InheritedObjectTypeGuid,
	_In_ PSID Sid
);

NTSYSAPI NTSTATUS NTAPI RtlAddAuditAccessObjectAce(
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

NTSYSAPI NTSTATUS NTAPI RtlAddCompoundAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ UCHAR AceType,
	_In_ ACCESS_MASK AccessMask,
	_In_ PSID ServerSid,
	_In_ PSID ClientSid
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlAddMandatoryAce(
	_Inout_ PACL Acl,
	_In_ ULONG AceRevision,
	_In_ ULONG AceFlags,
	_In_ PSID Sid,
	_In_ UCHAR AceType,
	_In_ ACCESS_MASK AccessMask
);
#endif

// Security objects

NTSYSAPI NTSTATUS NTAPI RtlNewSecurityObject(
	_In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
	_In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
	_Out_ PSECURITY_DESCRIPTOR *NewDescriptor,
	_In_ BOOLEAN IsDirectoryObject,
	_In_opt_ HANDLE Token,
	_In_ PGENERIC_MAPPING GenericMapping
);

NTSYSAPI NTSTATUS NTAPI RtlNewSecurityObjectEx(
	_In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
	_In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
	_Out_ PSECURITY_DESCRIPTOR *NewDescriptor,
	_In_opt_ GUID *ObjectType,
	_In_ BOOLEAN IsDirectoryObject,
	_In_ ULONG AutoInheritFlags, // SEF_*
	_In_opt_ HANDLE Token,
	_In_ PGENERIC_MAPPING GenericMapping
);

NTSYSAPI NTSTATUS NTAPI RtlNewSecurityObjectWithMultipleInheritance(
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

NTSYSAPI NTSTATUS NTAPI RtlDeleteSecurityObject(
	_Inout_ PSECURITY_DESCRIPTOR *ObjectDescriptor
);

NTSYSAPI NTSTATUS NTAPI RtlQuerySecurityObject(
	_In_ PSECURITY_DESCRIPTOR ObjectDescriptor,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_Out_opt_ PSECURITY_DESCRIPTOR ResultantDescriptor,
	_In_ ULONG DescriptorLength,
	_Out_ PULONG ReturnLength
);

NTSYSAPI NTSTATUS NTAPI RtlSetSecurityObject(
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR ModificationDescriptor,
	_Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
	_In_ PGENERIC_MAPPING GenericMapping,
	_In_opt_ HANDLE Token
);

NTSYSAPI NTSTATUS NTAPI RtlSetSecurityObjectEx(
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR ModificationDescriptor,
	_Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
	_In_ ULONG AutoInheritFlags, // SEF_*
	_In_ PGENERIC_MAPPING GenericMapping,
	_In_opt_ HANDLE Token
);

NTSYSAPI NTSTATUS NTAPI RtlConvertToAutoInheritSecurityObject(
	_In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
	_In_ PSECURITY_DESCRIPTOR CurrentSecurityDescriptor,
	_Out_ PSECURITY_DESCRIPTOR *NewSecurityDescriptor,
	_In_opt_ GUID *ObjectType,
	_In_ BOOLEAN IsDirectoryObject,
	_In_ PGENERIC_MAPPING GenericMapping
);

NTSYSAPI NTSTATUS NTAPI RtlNewInstanceSecurityObject(
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

NTSYSAPI NTSTATUS NTAPI RtlCopySecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR InputSecurityDescriptor,
	_Out_ PSECURITY_DESCRIPTOR *OutputSecurityDescriptor
);

// Misc. security

NTSYSAPI VOID NTAPI RtlRunEncodeUnicodeString(
	_Inout_ PUCHAR Seed,
	_In_ PUNICODE_STRING String
);

NTSYSAPI VOID NTAPI RtlRunDecodeUnicodeString(
	_In_ UCHAR Seed,
	_In_ PUNICODE_STRING String
);

NTSYSAPI NTSTATUS NTAPI RtlImpersonateSelf(
	_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlImpersonateSelfEx(
	_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
	_In_opt_ ACCESS_MASK AdditionalAccess,
	_Out_opt_ PHANDLE ThreadToken
);
#endif

NTSYSAPI NTSTATUS NTAPI RtlAdjustPrivilege(
	_In_ ULONG Privilege,
	_In_ BOOLEAN Enable,
	_In_ BOOLEAN Client,
	_Out_ PBOOLEAN WasEnabled
);

#define RTL_ACQUIRE_PRIVILEGE_REVERT 0x00000001
#define RTL_ACQUIRE_PRIVILEGE_PROCESS 0x00000002

NTSYSAPI NTSTATUS NTAPI RtlAcquirePrivilege(
	_In_ PULONG Privilege,
	_In_ ULONG NumPriv,
	_In_ ULONG Flags,
	_Out_ PVOID *ReturnedState
);

NTSYSAPI VOID NTAPI RtlReleasePrivilege(
	_In_ PVOID StatePointer
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlRemovePrivileges(
	_In_ HANDLE hToken,
	_In_ PULONG PrivilegesToKeep,
	_In_ ULONG PrivilegeCount
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSAPI NTSTATUS NTAPI RtlIsUntrustedObject(
	_In_opt_ HANDLE Handle,
	_In_opt_ PVOID Object,
	_Out_ PBOOLEAN UntrustedObject
);

NTSYSAPI ULONG NTAPI RtlQueryValidationRunlevel(
	_In_opt_ PCUNICODE_STRING ComponentName
);

#endif

// Private namespaces

#if (NTDDI_VERSION >= NTDDI_VISTA)

// begin_private

NTSYSAPI PVOID NTAPI RtlCreateBoundaryDescriptor(
	_In_ PUNICODE_STRING Name,
	_In_ ULONG Flags
);

NTSYSAPI VOID NTAPI RtlDeleteBoundaryDescriptor(
	_In_ PVOID BoundaryDescriptor
);

NTSYSAPI NTSTATUS NTAPI RtlAddSIDToBoundaryDescriptor(
	_Inout_ PVOID *BoundaryDescriptor,
	_In_ PSID RequiredSid
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI RtlAddIntegrityLabelToBoundaryDescriptor(
	_Inout_ PVOID *BoundaryDescriptor,
	_In_ PSID IntegrityLabel
);
#endif

// end_private

#endif

// Version

NTSYSAPI NTSTATUS NTAPI RtlGetVersion(
	_Out_ PRTL_OSVERSIONINFOW lpVersionInformation
);

NTSYSAPI NTSTATUS NTAPI RtlVerifyVersionInfo(
	_In_ PRTL_OSVERSIONINFOEXW VersionInfo,
	_In_ ULONG TypeMask,
	_In_ ULONGLONG ConditionMask
);

// System information

NTSYSAPI ULONG NTAPI RtlGetNtGlobalFlags(
	VOID
);

NTSYSAPI BOOLEAN NTAPI RtlGetNtProductType(
	_Out_ PNT_PRODUCT_TYPE NtProductType
);

// rev
NTSYSAPI VOID NTAPI RtlGetNtVersionNumbers(
	_Out_opt_ PULONG pNtMajorVersion,
	_Out_opt_ PULONG pNtMinorVersion,
	_Out_opt_ PULONG pNtBuildNumber
);

// Thread pool (old)

NTSYSAPI NTSTATUS NTAPI RtlRegisterWait(
	_Out_ PHANDLE WaitHandle,
	_In_ HANDLE Handle,
	_In_ WAITORTIMERCALLBACKFUNC Function,
	_In_ PVOID Context,
	_In_ ULONG Milliseconds,
	_In_ ULONG Flags
);

NTSYSAPI NTSTATUS NTAPI RtlDeregisterWait(
	_In_ HANDLE WaitHandle
);

NTSYSAPI NTSTATUS NTAPI RtlDeregisterWaitEx(
	_In_ HANDLE WaitHandle,
	_In_ HANDLE Event
);

NTSYSAPI NTSTATUS NTAPI RtlQueueWorkItem(
	_In_ WORKERCALLBACKFUNC Function,
	_In_ PVOID Context,
	_In_ ULONG Flags
);

NTSYSAPI NTSTATUS NTAPI RtlSetIoCompletionCallback(
	_In_ HANDLE FileHandle,
	_In_ APC_CALLBACK_FUNCTION CompletionProc,
	_In_ ULONG Flags
);

NTSYSAPI NTSTATUS NTAPI RtlCreateTimerQueue(
	_Out_ PHANDLE TimerQueueHandle
);

NTSYSAPI NTSTATUS NTAPI RtlCreateTimer(
	_In_ HANDLE TimerQueueHandle,
	_Out_ PHANDLE Handle,
	_In_ WAITORTIMERCALLBACKFUNC Function,
	_In_ PVOID Context,
	_In_ ULONG DueTime,
	_In_ ULONG Period,
	_In_ ULONG Flags
);

NTSYSAPI NTSTATUS NTAPI RtlUpdateTimer(
	_In_ HANDLE TimerQueueHandle,
	_In_ HANDLE TimerHandle,
	_In_ ULONG DueTime,
	_In_ ULONG Period
);

NTSYSAPI NTSTATUS NTAPI RtlDeleteTimer(
	_In_ HANDLE TimerQueueHandle,
	_In_ HANDLE TimerToCancel,
	_In_ HANDLE Event
);

NTSYSAPI NTSTATUS NTAPI RtlDeleteTimerQueue(
	_In_ HANDLE TimerQueueHandle
);

NTSYSAPI NTSTATUS NTAPI RtlDeleteTimerQueueEx(
	_In_ HANDLE TimerQueueHandle,
	_In_ HANDLE Event
);

// Registry access

NTSYSAPI NTSTATUS NTAPI RtlFormatCurrentUserKeyPath(
	_Out_ PUNICODE_STRING CurrentUserKeyPath
);

NTSYSAPI NTSTATUS NTAPI RtlOpenCurrentUser(
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

NTSYSAPI NTSTATUS NTAPI RtlCreateRegistryKey(
	_In_ ULONG RelativeTo,
	_In_ PWSTR Path
);

NTSYSAPI NTSTATUS NTAPI RtlCheckRegistryKey(
	_In_ ULONG RelativeTo,
	_In_ PWSTR Path
);

typedef NTSTATUS(NTAPI *PRTL_QUERY_REGISTRY_ROUTINE)(
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

NTSYSAPI NTSTATUS NTAPI RtlQueryRegistryValues(
	_In_ ULONG RelativeTo,
	_In_ PWSTR Path,
	_In_ PRTL_QUERY_REGISTRY_TABLE QueryTable,
	_In_ PVOID Context,
	_In_opt_ PVOID Environment
);

NTSYSAPI NTSTATUS NTAPI RtlWriteRegistryValue(
	_In_ ULONG RelativeTo,
	_In_ PWSTR Path,
	_In_ PWSTR ValueName,
	_In_ ULONG ValueType,
	_In_ PVOID ValueData,
	_In_ ULONG ValueLength
);

NTSYSAPI NTSTATUS NTAPI RtlDeleteRegistryValue(
	_In_ ULONG RelativeTo,
	_In_ PWSTR Path,
	_In_ PWSTR ValueName
);

// Debugging

NTSYSAPI VOID NTAPI DbgUserBreakPoint(
	VOID
);

NTSYSAPI VOID NTAPI DbgBreakPoint(
	VOID
);

NTSYSAPI VOID NTAPI DbgBreakPointWithStatus(
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
__cdecl
DbgPrint(
	_In_z_ _Printf_format_string_ PSTR Format,
	...
);

NTSYSAPI
ULONG
__cdecl
DbgPrintEx(
	_In_ ULONG ComponentId,
	_In_ ULONG Level,
	_In_z_ _Printf_format_string_ PSTR Format,
	...
);

NTSYSAPI ULONG NTAPI vDbgPrintEx(
	_In_ ULONG ComponentId,
	_In_ ULONG Level,
	_In_z_ PCH Format,
	_In_ va_list arglist
);

NTSYSAPI ULONG NTAPI vDbgPrintExWithPrefix(
	_In_z_ PCH Prefix,
	_In_ ULONG ComponentId,
	_In_ ULONG Level,
	_In_z_ PCH Format,
	_In_ va_list arglist
);

NTSYSAPI NTSTATUS NTAPI DbgQueryDebugFilterState(
	_In_ ULONG ComponentId,
	_In_ ULONG Level
);

NTSYSAPI NTSTATUS NTAPI DbgSetDebugFilterState(
	_In_ ULONG ComponentId,
	_In_ ULONG Level,
	_In_ BOOLEAN State
);

NTSYSAPI ULONG NTAPI DbgPrompt(
	_In_ PCH Prompt,
	_Out_writes_bytes_(Length) PCH Response,
	_In_ ULONG Length
);

// Thread profiling

#if (NTDDI_VERSION >= NTDDI_WIN7)

// begin_rev

NTSYSAPI NTSTATUS NTAPI RtlEnableThreadProfiling(
	_In_ HANDLE ThreadHandle,
	_In_ ULONG Flags,
	_In_ ULONG64 HardwareCounters,
	_Out_ PVOID *PerformanceDataHandle
);

NTSYSAPI NTSTATUS NTAPI RtlDisableThreadProfiling(
	_In_ PVOID PerformanceDataHandle
);

NTSYSAPI NTSTATUS NTAPI RtlQueryThreadProfiling(
	_In_ HANDLE ThreadHandle,
	_Out_ PBOOLEAN Enabled
);

NTSYSAPI NTSTATUS NTAPI RtlReadThreadProfilingData(
	_In_ HANDLE PerformanceDataHandle,
	_In_ ULONG Flags,
	_Out_ PPERFORMANCE_DATA PerformanceData
);

// end_rev

#endif

// WOW64

NTSYSAPI NTSTATUS NTAPI RtlGetNativeSystemInformation(
	_In_ ULONG SystemInformationClass,
	_In_ PVOID NativeSystemInformation,
	_In_ ULONG InformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSAPI NTSTATUS NTAPI RtlQueueApcWow64Thread(
	_In_ HANDLE ThreadHandle,
	_In_ PPS_APC_ROUTINE ApcRoutine,
	_In_ PVOID ApcArgument1,
	_In_ PVOID ApcArgument2,
	_In_ PVOID ApcArgument3
);

NTSYSAPI NTSTATUS NTAPI RtlWow64EnableFsRedirection(
	_In_ BOOLEAN Wow64FsEnableRedirection
);

NTSYSAPI NTSTATUS NTAPI RtlWow64EnableFsRedirectionEx(
	_In_ PVOID Wow64FsEnableRedirection,
	_Out_ PVOID *OldFsRedirectionLevel
);

// Misc.

NTSYSAPI ULONG NTAPI RtlGetCurrentProcessorNumber(
	VOID
);

NTSYSAPI ULONG32 NTAPI RtlComputeCrc32(
	_In_ ULONG32 PartialCrc,
	_In_ PVOID Buffer,
	_In_ ULONG Length
);

NTSYSAPI PVOID NTAPI RtlEncodePointer(
	_In_ PVOID Ptr
);

NTSYSAPI PVOID NTAPI RtlDecodePointer(
	_In_ PVOID Ptr
);

NTSYSAPI PVOID NTAPI RtlEncodeSystemPointer(
	_In_ PVOID Ptr
);

NTSYSAPI PVOID NTAPI RtlDecodeSystemPointer(
	_In_ PVOID Ptr
);

NTSYSAPI BOOLEAN NTAPI RtlIsThreadWithinLoaderCallout(
	VOID
);

NTSYSAPI VOID NTAPI RtlPushFrame(
	_In_ PTEB_ACTIVE_FRAME Frame
);

NTSYSAPI VOID NTAPI RtlPopFrame(
	_In_ PTEB_ACTIVE_FRAME Frame
);

NTSYSAPI
PTEB_ACTIVE_FRAME
NTAPI
RtlGetFrame(
	VOID
);

typedef ULONG(NTAPI *PRTLP_UNHANDLED_EXCEPTION_FILTER)(
	struct _EXCEPTION_POINTERS *ExceptionInfo
	);

NTSYSAPI VOID NTAPI RtlSetUnhandledExceptionFilter(
	_In_ PRTLP_UNHANDLED_EXCEPTION_FILTER UnhandledExceptionFilter
);

// begin_private

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
NTSYSAPI NTSTATUS NTAPI RtlQueryElevationFlags(
	_Out_ PRTL_ELEVATION_FLAGS Flags
);
#endif

// end_private

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlRegisterThreadWithCsrss(
	VOID
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlLockCurrentThread(
	VOID
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlUnlockCurrentThread(
	VOID
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlLockModuleSection(
	_In_ PVOID Address
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI NTSTATUS NTAPI RtlUnlockModuleSection(
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

NTSYSAPI
PRTL_UNLOAD_EVENT_TRACE
NTAPI
RtlGetUnloadEventTrace(
	VOID
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI VOID NTAPI RtlGetUnloadEventTraceEx(
	_Out_ PULONG *ElementSize,
	_Out_ PULONG *ElementCount,
	_Out_ PVOID *EventTrace // works across all processes
);
#endif

// end_msdn

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI LOGICAL NTAPI RtlQueryPerformanceCounter(
	_Out_ PLARGE_INTEGER PerformanceCounter
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI LOGICAL NTAPI RtlQueryPerformanceFrequency(
	_Out_ PLARGE_INTEGER PerformanceFrequency
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSAPI ULONG NTAPI RtlCrc32(
	_In_reads_bytes_(Size) const void *Buffer,
	_In_ size_t Size,
	_In_ ULONG InitialCrc
);

NTSYSAPI ULONGLONG NTAPI RtlCrc64(
	_In_reads_bytes_(Size) const void *Buffer,
	_In_ size_t Size,
	_In_ ULONGLONG InitialCrc
);

#endif

#endif

#ifndef _NTSEAPI_H
#define _NTSEAPI_H

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
#define SE_MAX_WELL_KNOWN_PRIVILEGE SE_CREATE_SYMBOLIC_LINK_PRIVILEGE


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

// Tokens

NTSYSCALLAPI NTSTATUS NTAPI NtCreateToken(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateToken(
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
NTSYSCALLAPI NTSTATUS NTAPI NtCreateLowBoxToken(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateLowBoxToken(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCreateTokenEx(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateTokenEx(
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

NTSYSCALLAPI NTSTATUS NTAPI NtOpenProcessToken(
	_In_ HANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_Out_ PHANDLE TokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenProcessToken(
	_In_ HANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_Out_ PHANDLE TokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenProcessTokenEx(
	_In_ HANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_Out_ PHANDLE TokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenProcessTokenEx(
	_In_ HANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_Out_ PHANDLE TokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenThreadToken(
	_In_ HANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ BOOLEAN OpenAsSelf,
	_Out_ PHANDLE TokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenThreadToken(
	_In_ HANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ BOOLEAN OpenAsSelf,
	_Out_ PHANDLE TokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenThreadTokenEx(
	_In_ HANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ BOOLEAN OpenAsSelf,
	_In_ ULONG HandleAttributes,
	_Out_ PHANDLE TokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenThreadTokenEx(
	_In_ HANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ BOOLEAN OpenAsSelf,
	_In_ ULONG HandleAttributes,
	_Out_ PHANDLE TokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtDuplicateToken(
	_In_ HANDLE ExistingTokenHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ BOOLEAN EffectiveOnly,
	_In_ TOKEN_TYPE TokenType,
	_Out_ PHANDLE NewTokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDuplicateToken(
	_In_ HANDLE ExistingTokenHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ BOOLEAN EffectiveOnly,
	_In_ TOKEN_TYPE TokenType,
	_Out_ PHANDLE NewTokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationToken(
	_In_ HANDLE TokenHandle,
	_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
	_Out_writes_bytes_(TokenInformationLength) PVOID TokenInformation,
	_In_ ULONG TokenInformationLength,
	_Out_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationToken(
	_In_ HANDLE TokenHandle,
	_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
	_Out_writes_bytes_(TokenInformationLength) PVOID TokenInformation,
	_In_ ULONG TokenInformationLength,
	_Out_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationToken(
	_In_ HANDLE TokenHandle,
	_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
	_In_reads_bytes_(TokenInformationLength) PVOID TokenInformation,
	_In_ ULONG TokenInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationToken(
	_In_ HANDLE TokenHandle,
	_In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
	_In_reads_bytes_(TokenInformationLength) PVOID TokenInformation,
	_In_ ULONG TokenInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtAdjustPrivilegesToken(
	_In_ HANDLE TokenHandle,
	_In_ BOOLEAN DisableAllPrivileges,
	_In_opt_ PTOKEN_PRIVILEGES NewState,
	_In_ ULONG BufferLength,
	_Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
	_Out_ _When_(PreviousState == NULL, _Out_opt_) PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAdjustPrivilegesToken(
	_In_ HANDLE TokenHandle,
	_In_ BOOLEAN DisableAllPrivileges,
	_In_opt_ PTOKEN_PRIVILEGES NewState,
	_In_ ULONG BufferLength,
	_Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
	_Out_ _When_(PreviousState == NULL, _Out_opt_) PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtAdjustGroupsToken(
	_In_ HANDLE TokenHandle,
	_In_ BOOLEAN ResetToDefault,
	_In_opt_ PTOKEN_GROUPS NewState,
	_In_opt_ ULONG BufferLength,
	_Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_GROUPS PreviousState,
	_Out_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAdjustGroupsToken(
	_In_ HANDLE TokenHandle,
	_In_ BOOLEAN ResetToDefault,
	_In_opt_ PTOKEN_GROUPS NewState,
	_In_opt_ ULONG BufferLength,
	_Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_GROUPS PreviousState,
	_Out_ PULONG ReturnLength
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI NTSTATUS NTAPI NtAdjustTokenClaimsAndDeviceGroups(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAdjustTokenClaimsAndDeviceGroups(
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

NTSYSCALLAPI NTSTATUS NTAPI NtFilterToken(
	_In_ HANDLE ExistingTokenHandle,
	_In_ ULONG Flags,
	_In_opt_ PTOKEN_GROUPS SidsToDisable,
	_In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
	_In_opt_ PTOKEN_GROUPS RestrictedSids,
	_Out_ PHANDLE NewTokenHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFilterToken(
	_In_ HANDLE ExistingTokenHandle,
	_In_ ULONG Flags,
	_In_opt_ PTOKEN_GROUPS SidsToDisable,
	_In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
	_In_opt_ PTOKEN_GROUPS RestrictedSids,
	_Out_ PHANDLE NewTokenHandle
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSCALLAPI NTSTATUS NTAPI NtFilterTokenEx(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwFilterTokenEx(
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

NTSYSCALLAPI NTSTATUS NTAPI NtCompareTokens(
	_In_ HANDLE FirstTokenHandle,
	_In_ HANDLE SecondTokenHandle,
	_Out_ PBOOLEAN Equal
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCompareTokens(
	_In_ HANDLE FirstTokenHandle,
	_In_ HANDLE SecondTokenHandle,
	_Out_ PBOOLEAN Equal
);

NTSYSCALLAPI NTSTATUS NTAPI NtPrivilegeCheck(
	_In_ HANDLE ClientToken,
	_Inout_ PPRIVILEGE_SET RequiredPrivileges,
	_Out_ PBOOLEAN Result
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPrivilegeCheck(
	_In_ HANDLE ClientToken,
	_Inout_ PPRIVILEGE_SET RequiredPrivileges,
	_Out_ PBOOLEAN Result
);

NTSYSCALLAPI NTSTATUS NTAPI NtImpersonateAnonymousToken(
	_In_ HANDLE ThreadHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwImpersonateAnonymousToken(
	_In_ HANDLE ThreadHandle
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSCALLAPI NTSTATUS NTAPI NtQuerySecurityAttributesToken(
	_In_ HANDLE TokenHandle,
	_In_reads_opt_(NumberOfAttributes) PUNICODE_STRING Attributes,
	_In_ ULONG NumberOfAttributes,
	_Out_writes_bytes_(Length) PVOID Buffer, // PTOKEN_SECURITY_ATTRIBUTES_INFORMATION
	_In_ ULONG Length,
	_Out_ PULONG ReturnLength
);

// rev
NTSYSCALLAPI NTSTATUS NTAPI ZwQuerySecurityAttributesToken(
	_In_ HANDLE TokenHandle,
	_In_reads_opt_(NumberOfAttributes) PUNICODE_STRING Attributes,
	_In_ ULONG NumberOfAttributes,
	_Out_writes_bytes_(Length) PVOID Buffer, // PTOKEN_SECURITY_ATTRIBUTES_INFORMATION
	_In_ ULONG Length,
	_Out_ PULONG ReturnLength
);
#endif

// Access checking

NTSYSCALLAPI NTSTATUS NTAPI NtAccessCheck(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ HANDLE ClientToken,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ PGENERIC_MAPPING GenericMapping,
	_Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
	_Inout_ PULONG PrivilegeSetLength,
	_Out_ PACCESS_MASK GrantedAccess,
	_Out_ PNTSTATUS AccessStatus
);

NTSYSCALLAPI NTSTATUS NTAPI ZwAccessCheck(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ HANDLE ClientToken,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ PGENERIC_MAPPING GenericMapping,
	_Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
	_Inout_ PULONG PrivilegeSetLength,
	_Out_ PACCESS_MASK GrantedAccess,
	_Out_ PNTSTATUS AccessStatus
);

NTSYSCALLAPI NTSTATUS NTAPI NtAccessCheckByType(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAccessCheckByType(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAccessCheckByTypeResultList(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAccessCheckByTypeResultList(
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

NTSYSCALLAPI NTSTATUS NTAPI NtSetCachedSigningLevel(
	_In_ ULONG Flags,
	_In_ SE_SIGNING_LEVEL InputSigningLevel,
	_In_reads_(SourceFileCount) PHANDLE SourceFiles,
	_In_ ULONG SourceFileCount,
	_In_opt_ HANDLE TargetFile
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetCachedSigningLevel(
	_In_ ULONG Flags,
	_In_ SE_SIGNING_LEVEL InputSigningLevel,
	_In_reads_(SourceFileCount) PHANDLE SourceFiles,
	_In_ ULONG SourceFileCount,
	_In_opt_ HANDLE TargetFile
);

NTSYSCALLAPI NTSTATUS NTAPI NtGetCachedSigningLevel(
	_In_ HANDLE File,
	_Out_ PULONG Flags,
	_Out_ PSE_SIGNING_LEVEL SigningLevel,
	_Out_writes_bytes_to_opt_(*ThumbprintSize, *ThumbprintSize) PUCHAR Thumbprint,
	_Inout_opt_ PULONG ThumbprintSize,
	_Out_opt_ PULONG ThumbprintAlgorithm
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetCachedSigningLevel(
	_In_ HANDLE File,
	_Out_ PULONG Flags,
	_Out_ PSE_SIGNING_LEVEL SigningLevel,
	_Out_writes_bytes_to_opt_(*ThumbprintSize, *ThumbprintSize) PUCHAR Thumbprint,
	_Inout_opt_ PULONG ThumbprintSize,
	_Out_opt_ PULONG ThumbprintAlgorithm
);

#endif

// Audit alarm

NTSYSCALLAPI NTSTATUS NTAPI NtAccessCheckAndAuditAlarm(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAccessCheckAndAuditAlarm(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAccessCheckByTypeAndAuditAlarm(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAccessCheckByTypeAndAuditAlarm(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAccessCheckByTypeResultListAndAuditAlarm(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAccessCheckByTypeResultListAndAuditAlarm(
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

NTSYSCALLAPI NTSTATUS NTAPI NtAccessCheckByTypeResultListAndAuditAlarmByHandle(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwAccessCheckByTypeResultListAndAuditAlarmByHandle(
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

NTSYSCALLAPI NTSTATUS NTAPI NtOpenObjectAuditAlarm(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenObjectAuditAlarm(
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

NTSYSCALLAPI NTSTATUS NTAPI NtPrivilegeObjectAuditAlarm(
	_In_ PUNICODE_STRING SubsystemName,
	_In_opt_ PVOID HandleId,
	_In_ HANDLE ClientToken,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ PPRIVILEGE_SET Privileges,
	_In_ BOOLEAN AccessGranted
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPrivilegeObjectAuditAlarm(
	_In_ PUNICODE_STRING SubsystemName,
	_In_opt_ PVOID HandleId,
	_In_ HANDLE ClientToken,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ PPRIVILEGE_SET Privileges,
	_In_ BOOLEAN AccessGranted
);

NTSYSCALLAPI NTSTATUS NTAPI NtCloseObjectAuditAlarm(
	_In_ PUNICODE_STRING SubsystemName,
	_In_opt_ PVOID HandleId,
	_In_ BOOLEAN GenerateOnClose
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCloseObjectAuditAlarm(
	_In_ PUNICODE_STRING SubsystemName,
	_In_opt_ PVOID HandleId,
	_In_ BOOLEAN GenerateOnClose
);

NTSYSCALLAPI NTSTATUS NTAPI NtDeleteObjectAuditAlarm(
	_In_ PUNICODE_STRING SubsystemName,
	_In_opt_ PVOID HandleId,
	_In_ BOOLEAN GenerateOnClose
);

NTSYSCALLAPI NTSTATUS NTAPI ZwDeleteObjectAuditAlarm(
	_In_ PUNICODE_STRING SubsystemName,
	_In_opt_ PVOID HandleId,
	_In_ BOOLEAN GenerateOnClose
);

NTSYSCALLAPI NTSTATUS NTAPI NtPrivilegedServiceAuditAlarm(
	_In_ PUNICODE_STRING SubsystemName,
	_In_ PUNICODE_STRING ServiceName,
	_In_ HANDLE ClientToken,
	_In_ PPRIVILEGE_SET Privileges,
	_In_ BOOLEAN AccessGranted
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPrivilegedServiceAuditAlarm(
	_In_ PUNICODE_STRING SubsystemName,
	_In_ PUNICODE_STRING ServiceName,
	_In_ HANDLE ClientToken,
	_In_ PPRIVILEGE_SET Privileges,
	_In_ BOOLEAN AccessGranted
);

// Misc.

typedef enum _FILTER_BOOT_OPTION_OPERATION
{
	FilterBootOptionOperationOpenSystemStore,
	FilterBootOptionOperationSetElement,
	FilterBootOptionOperationDeleteElement,
	FilterBootOptionOperationMax
} FILTER_BOOT_OPTION_OPERATION;

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSCALLAPI NTSTATUS NTAPI NtFilterBootOption(
	_In_ FILTER_BOOT_OPTION_OPERATION FilterOperation,
	_In_ ULONG ObjectType,
	_In_ ULONG ElementType,
	_In_reads_bytes_opt_(DataSize) PVOID Data,
	_In_ ULONG DataSize
);

NTSYSCALLAPI NTSTATUS NTAPI ZwFilterBootOption(
	_In_ FILTER_BOOT_OPTION_OPERATION FilterOperation,
	_In_ ULONG ObjectType,
	_In_ ULONG ElementType,
	_In_reads_bytes_opt_(DataSize) PVOID Data,
	_In_ ULONG DataSize
);
#endif

#endif

#ifndef _NTTMAPI_H
#define _NTTMAPI_H

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI NTSTATUS NTAPI NtCreateTransactionManager(
	_Out_ PHANDLE TmHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PUNICODE_STRING LogFileName,
	_In_opt_ ULONG CreateOptions,
	_In_opt_ ULONG CommitStrength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateTransactionManager(
	_Out_ PHANDLE TmHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PUNICODE_STRING LogFileName,
	_In_opt_ ULONG CreateOptions,
	_In_opt_ ULONG CommitStrength
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenTransactionManager(
	_Out_ PHANDLE TmHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PUNICODE_STRING LogFileName,
	_In_opt_ LPGUID TmIdentity,
	_In_opt_ ULONG OpenOptions
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenTransactionManager(
	_Out_ PHANDLE TmHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PUNICODE_STRING LogFileName,
	_In_opt_ LPGUID TmIdentity,
	_In_opt_ ULONG OpenOptions
);

NTSYSCALLAPI NTSTATUS NTAPI NtRenameTransactionManager(
	_In_ PUNICODE_STRING LogFileName,
	_In_ LPGUID ExistingTransactionManagerGuid
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRenameTransactionManager(
	_In_ PUNICODE_STRING LogFileName,
	_In_ LPGUID ExistingTransactionManagerGuid
);

NTSYSCALLAPI NTSTATUS NTAPI NtRollforwardTransactionManager(
	_In_ HANDLE TransactionManagerHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRollforwardTransactionManager(
	_In_ HANDLE TransactionManagerHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtRecoverTransactionManager(
	_In_ HANDLE TransactionManagerHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRecoverTransactionManager(
	_In_ HANDLE TransactionManagerHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationTransactionManager(
	_In_ HANDLE TransactionManagerHandle,
	_In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
	_Out_writes_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
	_In_ ULONG TransactionManagerInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationTransactionManager(
	_In_ HANDLE TransactionManagerHandle,
	_In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
	_Out_writes_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
	_In_ ULONG TransactionManagerInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationTransactionManager(
	_In_opt_ HANDLE TmHandle,
	_In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
	_In_reads_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
	_In_ ULONG TransactionManagerInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationTransactionManager(
	_In_opt_ HANDLE TmHandle,
	_In_ TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
	_In_reads_bytes_(TransactionManagerInformationLength) PVOID TransactionManagerInformation,
	_In_ ULONG TransactionManagerInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtEnumerateTransactionObject(
	_In_opt_ HANDLE RootObjectHandle,
	_In_ KTMOBJECT_TYPE QueryType,
	_Inout_updates_bytes_(ObjectCursorLength) PKTMOBJECT_CURSOR ObjectCursor,
	_In_ ULONG ObjectCursorLength,
	_Out_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwEnumerateTransactionObject(
	_In_opt_ HANDLE RootObjectHandle,
	_In_ KTMOBJECT_TYPE QueryType,
	_Inout_updates_bytes_(ObjectCursorLength) PKTMOBJECT_CURSOR ObjectCursor,
	_In_ ULONG ObjectCursorLength,
	_Out_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtCreateTransaction(
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

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateTransaction(
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

NTSYSCALLAPI NTSTATUS NTAPI NtOpenTransaction(
	_Out_ PHANDLE TransactionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ LPGUID Uow,
	_In_opt_ HANDLE TmHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenTransaction(
	_Out_ PHANDLE TransactionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ LPGUID Uow,
	_In_opt_ HANDLE TmHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
	_Out_writes_bytes_(TransactionInformationLength) PVOID TransactionInformation,
	_In_ ULONG TransactionInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
	_Out_writes_bytes_(TransactionInformationLength) PVOID TransactionInformation,
	_In_ ULONG TransactionInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
	_In_reads_bytes_(TransactionInformationLength) PVOID TransactionInformation,
	_In_ ULONG TransactionInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
	_In_reads_bytes_(TransactionInformationLength) PVOID TransactionInformation,
	_In_ ULONG TransactionInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
	_Out_writes_bytes_(TransactionInformationLength) PVOID TransactionInformation,
	_In_ ULONG TransactionInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtCommitTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ BOOLEAN Wait
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCommitTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ BOOLEAN Wait
);

NTSYSCALLAPI NTSTATUS NTAPI NtRollbackTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ BOOLEAN Wait
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRollbackTransaction(
	_In_ HANDLE TransactionHandle,
	_In_ BOOLEAN Wait
);

NTSYSCALLAPI NTSTATUS NTAPI NtCreateEnlistment(
	_Out_ PHANDLE EnlistmentHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ HANDLE ResourceManagerHandle,
	_In_ HANDLE TransactionHandle,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ ULONG CreateOptions,
	_In_ NOTIFICATION_MASK NotificationMask,
	_In_opt_ PVOID EnlistmentKey
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateEnlistment(
	_Out_ PHANDLE EnlistmentHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ HANDLE ResourceManagerHandle,
	_In_ HANDLE TransactionHandle,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ ULONG CreateOptions,
	_In_ NOTIFICATION_MASK NotificationMask,
	_In_opt_ PVOID EnlistmentKey
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenEnlistment(
	_Out_ PHANDLE EnlistmentHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ HANDLE ResourceManagerHandle,
	_In_ LPGUID EnlistmentGuid,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenEnlistment(
	_Out_ PHANDLE EnlistmentHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ HANDLE ResourceManagerHandle,
	_In_ LPGUID EnlistmentGuid,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
	_Out_writes_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
	_In_ ULONG EnlistmentInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
	_Out_writes_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
	_In_ ULONG EnlistmentInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationEnlistment(
	_In_opt_ HANDLE EnlistmentHandle,
	_In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
	_In_reads_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
	_In_ ULONG EnlistmentInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationEnlistment(
	_In_opt_ HANDLE EnlistmentHandle,
	_In_ ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
	_In_reads_bytes_(EnlistmentInformationLength) PVOID EnlistmentInformation,
	_In_ ULONG EnlistmentInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtRecoverEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PVOID EnlistmentKey
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRecoverEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PVOID EnlistmentKey
);

NTSYSCALLAPI NTSTATUS NTAPI NtPrePrepareEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPrePrepareEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtPrepareEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPrepareEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtCommitEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCommitEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtRollbackEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRollbackEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtPrePrepareComplete(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPrePrepareComplete(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtPrepareComplete(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPrepareComplete(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtCommitComplete(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCommitComplete(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtReadOnlyEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwReadOnlyEnlistment(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtRollbackComplete(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRollbackComplete(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtSinglePhaseReject(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSinglePhaseReject(
	_In_ HANDLE EnlistmentHandle,
	_In_opt_ PLARGE_INTEGER TmVirtualClock
);

NTSYSCALLAPI NTSTATUS NTAPI NtCreateResourceManager(
	_Out_ PHANDLE ResourceManagerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ HANDLE TmHandle,
	_In_ LPGUID RmGuid,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ ULONG CreateOptions,
	_In_opt_ PUNICODE_STRING Description
);

NTSYSCALLAPI NTSTATUS NTAPI ZwCreateResourceManager(
	_Out_ PHANDLE ResourceManagerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ HANDLE TmHandle,
	_In_ LPGUID RmGuid,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ ULONG CreateOptions,
	_In_opt_ PUNICODE_STRING Description
);

NTSYSCALLAPI NTSTATUS NTAPI NtOpenResourceManager(
	_Out_ PHANDLE ResourceManagerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ HANDLE TmHandle,
	_In_opt_ LPGUID ResourceManagerGuid,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI ZwOpenResourceManager(
	_Out_ PHANDLE ResourceManagerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ HANDLE TmHandle,
	_In_opt_ LPGUID ResourceManagerGuid,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSCALLAPI NTSTATUS NTAPI NtRecoverResourceManager(
	_In_ HANDLE ResourceManagerHandle
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRecoverResourceManager(
	_In_ HANDLE ResourceManagerHandle
);

NTSYSCALLAPI NTSTATUS NTAPI NtGetNotificationResourceManager(
	_In_ HANDLE ResourceManagerHandle,
	_Out_ PTRANSACTION_NOTIFICATION TransactionNotification,
	_In_ ULONG NotificationLength,
	_In_opt_ PLARGE_INTEGER Timeout,
	_Out_opt_ PULONG ReturnLength,
	_In_ ULONG Asynchronous,
	_In_opt_ ULONG_PTR AsynchronousContext
);

NTSYSCALLAPI NTSTATUS NTAPI ZwGetNotificationResourceManager(
	_In_ HANDLE ResourceManagerHandle,
	_Out_ PTRANSACTION_NOTIFICATION TransactionNotification,
	_In_ ULONG NotificationLength,
	_In_opt_ PLARGE_INTEGER Timeout,
	_Out_opt_ PULONG ReturnLength,
	_In_ ULONG Asynchronous,
	_In_opt_ ULONG_PTR AsynchronousContext
);

NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationResourceManager(
	_In_ HANDLE ResourceManagerHandle,
	_In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
	_Out_writes_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
	_In_ ULONG ResourceManagerInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwQueryInformationResourceManager(
	_In_ HANDLE ResourceManagerHandle,
	_In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
	_Out_writes_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
	_In_ ULONG ResourceManagerInformationLength,
	_Out_opt_ PULONG ReturnLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtSetInformationResourceManager(
	_In_ HANDLE ResourceManagerHandle,
	_In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
	_In_reads_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
	_In_ ULONG ResourceManagerInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI ZwSetInformationResourceManager(
	_In_ HANDLE ResourceManagerHandle,
	_In_ RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
	_In_reads_bytes_(ResourceManagerInformationLength) PVOID ResourceManagerInformation,
	_In_ ULONG ResourceManagerInformationLength
);

NTSYSCALLAPI NTSTATUS NTAPI NtRegisterProtocolAddressInformation(
	_In_ HANDLE ResourceManager,
	_In_ PCRM_PROTOCOL_ID ProtocolId,
	_In_ ULONG ProtocolInformationSize,
	_In_ PVOID ProtocolInformation,
	_In_opt_ ULONG CreateOptions
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRegisterProtocolAddressInformation(
	_In_ HANDLE ResourceManager,
	_In_ PCRM_PROTOCOL_ID ProtocolId,
	_In_ ULONG ProtocolInformationSize,
	_In_ PVOID ProtocolInformation,
	_In_opt_ ULONG CreateOptions
);

NTSYSCALLAPI NTSTATUS NTAPI NtPropagationComplete(
	_In_ HANDLE ResourceManagerHandle,
	_In_ ULONG RequestCookie,
	_In_ ULONG BufferLength,
	_In_ PVOID Buffer
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPropagationComplete(
	_In_ HANDLE ResourceManagerHandle,
	_In_ ULONG RequestCookie,
	_In_ ULONG BufferLength,
	_In_ PVOID Buffer
);

NTSYSCALLAPI NTSTATUS NTAPI NtPropagationFailed(
	_In_ HANDLE ResourceManagerHandle,
	_In_ ULONG RequestCookie,
	_In_ NTSTATUS PropStatus
);

NTSYSCALLAPI NTSTATUS NTAPI ZwPropagationFailed(
	_In_ HANDLE ResourceManagerHandle,
	_In_ ULONG RequestCookie,
	_In_ NTSTATUS PropStatus
);

// private
NTSYSCALLAPI NTSTATUS NTAPI NtFreezeTransactions(
	_In_ PLARGE_INTEGER FreezeTimeout,
	_In_ PLARGE_INTEGER ThawTimeout
);

// private
NTSYSCALLAPI NTSTATUS NTAPI ZwFreezeTransactions(
	_In_ PLARGE_INTEGER FreezeTimeout,
	_In_ PLARGE_INTEGER ThawTimeout
);

// private
NTSYSCALLAPI NTSTATUS NTAPI NtThawTransactions(
	VOID
);

// private
NTSYSCALLAPI NTSTATUS NTAPI ZwThawTransactions(
	VOID
);
#endif

#endif

#ifndef _NTTP_H
#define _NTTP_H

// Some types are already defined in winnt.h.

typedef struct _TP_ALPC TP_ALPC, *PTP_ALPC;

// private
typedef VOID(NTAPI *PTP_ALPC_CALLBACK)(
	_Inout_ PTP_CALLBACK_INSTANCE Instance,
	_Inout_opt_ PVOID Context,
	_In_ PTP_ALPC Alpc
	);

// rev
typedef VOID(NTAPI *PTP_ALPC_CALLBACK_EX)(
	_Inout_ PTP_CALLBACK_INSTANCE Instance,
	_Inout_opt_ PVOID Context,
	_In_ PTP_ALPC Alpc,
	_In_ PVOID ApcContext
	);

#if (NTDDI_VERSION >= NTDDI_VISTA)

// private
_Check_return_
NTSYSAPI NTSTATUS NTAPI TpAllocPool(
	_Out_ PTP_POOL *PoolReturn,
	_Reserved_ PVOID Reserved
);

// winbase:CloseThreadpool
NTSYSAPI VOID NTAPI TpReleasePool(
	_Inout_ PTP_POOL Pool
);

// winbase:SetThreadpoolThreadMaximum
NTSYSAPI VOID NTAPI TpSetPoolMaxThreads(
	_Inout_ PTP_POOL Pool,
	_In_ LONG MaxThreads
);

// private
NTSYSAPI NTSTATUS NTAPI TpSetPoolMinThreads(
	_Inout_ PTP_POOL Pool,
	_In_ LONG MinThreads
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI TpQueryPoolStackInformation(
	_In_ PTP_POOL Pool,
	_Out_ PTP_POOL_STACK_INFORMATION PoolStackInformation
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI TpSetPoolStackInformation(
	_Inout_ PTP_POOL Pool,
	_In_ PTP_POOL_STACK_INFORMATION PoolStackInformation
);
#endif

// private
_Check_return_
NTSYSAPI NTSTATUS NTAPI TpAllocCleanupGroup(
	_Out_ PTP_CLEANUP_GROUP *CleanupGroupReturn
);

// winbase:CloseThreadpoolCleanupGroup
NTSYSAPI VOID NTAPI TpReleaseCleanupGroup(
	_Inout_ PTP_CLEANUP_GROUP CleanupGroup
);

// winbase:CloseThreadpoolCleanupGroupMembers
NTSYSAPI VOID NTAPI TpReleaseCleanupGroupMembers(
	_Inout_ PTP_CLEANUP_GROUP CleanupGroup,
	_In_ LOGICAL CancelPendingCallbacks,
	_Inout_opt_ PVOID CleanupParameter
);

// winbase:SetEventWhenCallbackReturns
NTSYSAPI VOID NTAPI TpCallbackSetEventOnCompletion(
	_Inout_ PTP_CALLBACK_INSTANCE Instance,
	_In_ HANDLE Event
);

// winbase:ReleaseSemaphoreWhenCallbackReturns
NTSYSAPI VOID NTAPI TpCallbackReleaseSemaphoreOnCompletion(
	_Inout_ PTP_CALLBACK_INSTANCE Instance,
	_In_ HANDLE Semaphore,
	_In_ LONG ReleaseCount
);

// winbase:ReleaseMutexWhenCallbackReturns
NTSYSAPI VOID NTAPI TpCallbackReleaseMutexOnCompletion(
	_Inout_ PTP_CALLBACK_INSTANCE Instance,
	_In_ HANDLE Mutex
);

// winbase:LeaveCriticalSectionWhenCallbackReturns
NTSYSAPI VOID NTAPI TpCallbackLeaveCriticalSectionOnCompletion(
	_Inout_ PTP_CALLBACK_INSTANCE Instance,
	_Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

// winbase:FreeLibraryWhenCallbackReturns
NTSYSAPI VOID NTAPI TpCallbackUnloadDllOnCompletion(
	_Inout_ PTP_CALLBACK_INSTANCE Instance,
	_In_ PVOID DllHandle
);

// winbase:CallbackMayRunLong
NTSYSAPI NTSTATUS NTAPI TpCallbackMayRunLong(
	_Inout_ PTP_CALLBACK_INSTANCE Instance
);

// winbase:DisassociateCurrentThreadFromCallback
NTSYSAPI VOID NTAPI TpDisassociateCallback(
	_Inout_ PTP_CALLBACK_INSTANCE Instance
);

// winbase:TrySubmitThreadpoolCallback
_Check_return_
NTSYSAPI NTSTATUS NTAPI TpSimpleTryPost(
	_In_ PTP_SIMPLE_CALLBACK Callback,
	_Inout_opt_ PVOID Context,
	_In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
);

// private
_Check_return_
NTSYSAPI NTSTATUS NTAPI TpAllocWork(
	_Out_ PTP_WORK *WorkReturn,
	_In_ PTP_WORK_CALLBACK Callback,
	_Inout_opt_ PVOID Context,
	_In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
);

// winbase:CloseThreadpoolWork
NTSYSAPI VOID NTAPI TpReleaseWork(
	_Inout_ PTP_WORK Work
);

// winbase:SubmitThreadpoolWork
NTSYSAPI VOID NTAPI TpPostWork(
	_Inout_ PTP_WORK Work
);

// winbase:WaitForThreadpoolWorkCallbacks
NTSYSAPI VOID NTAPI TpWaitForWork(
	_Inout_ PTP_WORK Work,
	_In_ LOGICAL CancelPendingCallbacks
);

// private
_Check_return_
NTSYSAPI NTSTATUS NTAPI TpAllocTimer(
	_Out_ PTP_TIMER *Timer,
	_In_ PTP_TIMER_CALLBACK Callback,
	_Inout_opt_ PVOID Context,
	_In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
);

// winbase:CloseThreadpoolTimer
NTSYSAPI VOID NTAPI TpReleaseTimer(
	_Inout_ PTP_TIMER Timer
);

// winbase:SetThreadpoolTimer
NTSYSAPI VOID NTAPI TpSetTimer(
	_Inout_ PTP_TIMER Timer,
	_In_opt_ PLARGE_INTEGER DueTime,
	_In_ LONG Period,
	_In_opt_ LONG WindowLength
);

// winbase:IsThreadpoolTimerSet
NTSYSAPI LOGICAL NTAPI TpIsTimerSet(
	_In_ PTP_TIMER Timer
);

// winbase:WaitForThreadpoolTimerCallbacks
NTSYSAPI VOID NTAPI TpWaitForTimer(
	_Inout_ PTP_TIMER Timer,
	_In_ LOGICAL CancelPendingCallbacks
);

// private
_Check_return_
NTSYSAPI NTSTATUS NTAPI TpAllocWait(
	_Out_ PTP_WAIT *WaitReturn,
	_In_ PTP_WAIT_CALLBACK Callback,
	_Inout_opt_ PVOID Context,
	_In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
);

// winbase:CloseThreadpoolWait
NTSYSAPI VOID NTAPI TpReleaseWait(
	_Inout_ PTP_WAIT Wait
);

// winbase:SetThreadpoolWait
NTSYSAPI VOID NTAPI TpSetWait(
	_Inout_ PTP_WAIT Wait,
	_In_opt_ HANDLE Handle,
	_In_opt_ PLARGE_INTEGER Timeout
);

// winbase:WaitForThreadpoolWaitCallbacks
NTSYSAPI VOID NTAPI TpWaitForWait(
	_Inout_ PTP_WAIT Wait,
	_In_ LOGICAL CancelPendingCallbacks
);

// private
typedef VOID(NTAPI *PTP_IO_CALLBACK)(
	_Inout_ PTP_CALLBACK_INSTANCE Instance,
	_Inout_opt_ PVOID Context,
	_In_ PVOID ApcContext,
	_In_ PIO_STATUS_BLOCK IoSB,
	_In_ PTP_IO Io
	);

// private
_Check_return_
NTSYSAPI NTSTATUS NTAPI TpAllocIoCompletion(
	_Out_ PTP_IO *IoReturn,
	_In_ HANDLE File,
	_In_ PTP_IO_CALLBACK Callback,
	_Inout_opt_ PVOID Context,
	_In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
);

// winbase:CloseThreadpoolIo
NTSYSAPI VOID NTAPI TpReleaseIoCompletion(
	_Inout_ PTP_IO Io
);

// winbase:StartThreadpoolIo
NTSYSAPI VOID NTAPI TpStartAsyncIoOperation(
	_Inout_ PTP_IO Io
);

// winbase:CancelThreadpoolIo
NTSYSAPI VOID NTAPI TpCancelAsyncIoOperation(
	_Inout_ PTP_IO Io
);

// winbase:WaitForThreadpoolIoCallbacks
NTSYSAPI VOID NTAPI TpWaitForIoCompletion(
	_Inout_ PTP_IO Io,
	_In_ LOGICAL CancelPendingCallbacks
);

// private
NTSYSAPI NTSTATUS NTAPI TpAllocAlpcCompletion(
	_Out_ PTP_ALPC *AlpcReturn,
	_In_ HANDLE AlpcPort,
	_In_ PTP_ALPC_CALLBACK Callback,
	_Inout_opt_ PVOID Context,
	_In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI NTSTATUS NTAPI TpAllocAlpcCompletionEx(
	_Out_ PTP_ALPC *AlpcReturn,
	_In_ HANDLE AlpcPort,
	_In_ PTP_ALPC_CALLBACK_EX Callback,
	_Inout_opt_ PVOID Context,
	_In_opt_ PTP_CALLBACK_ENVIRON CallbackEnviron
);
#endif

// private
NTSYSAPI VOID NTAPI TpReleaseAlpcCompletion(
	_Inout_ PTP_ALPC Alpc
);

// private
NTSYSAPI VOID NTAPI TpWaitForAlpcCompletion(
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
NTSYSAPI VOID NTAPI TpCaptureCaller(
	_In_ TP_TRACE_TYPE Type
);

// private
NTSYSAPI VOID NTAPI TpCheckTerminateWorker(
	_In_ HANDLE Thread
);

#endif

#endif

#ifndef _NTXCAPI_H
#define _NTXCAPI_H

NTSYSAPI BOOLEAN NTAPI RtlDispatchException(
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

NTSYSAPI VOID NTAPI RtlRaiseException(
	_In_ PEXCEPTION_RECORD ExceptionRecord
);

NTSYSCALLAPI NTSTATUS NTAPI NtContinue(
	_In_ PCONTEXT ContextRecord,
	_In_ BOOLEAN TestAlert
);

NTSYSCALLAPI NTSTATUS NTAPI ZwContinue(
	_In_ PCONTEXT ContextRecord,
	_In_ BOOLEAN TestAlert
);

NTSYSCALLAPI NTSTATUS NTAPI NtRaiseException(
	_In_ PEXCEPTION_RECORD ExceptionRecord,
	_In_ PCONTEXT ContextRecord,
	_In_ BOOLEAN FirstChance
);

NTSYSCALLAPI NTSTATUS NTAPI ZwRaiseException(
	_In_ PEXCEPTION_RECORD ExceptionRecord,
	_In_ PCONTEXT ContextRecord,
	_In_ BOOLEAN FirstChance
);

#endif

#ifndef _NTWOW64_H
#define _NTWOW64_H

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
			ULONG ReservedFlags5 : 3;
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

	ULONG EnvironmentSize;
	ULONG EnvironmentVersion;
	WOW64_POINTER(PVOID) PackageDependencyData;
	ULONG ProcessGroupId;
	ULONG LoaderThreads;
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
	ULONG SystemReserved[1];
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

	WOW64_POINTER(PVOID *) FlsCallback;
	LIST_ENTRY32 FlsListHead;
	WOW64_POINTER(PVOID) FlsBitmap;
	ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
	ULONG FlsHighIndex;

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
} PEB32, *PPEB32;

C_ASSERT(FIELD_OFFSET(PEB32, IFEOKey) == 0x024);
C_ASSERT(FIELD_OFFSET(PEB32, UnicodeCaseTableData) == 0x060);
C_ASSERT(FIELD_OFFSET(PEB32, SystemAssemblyStorageMap) == 0x204);
C_ASSERT(FIELD_OFFSET(PEB32, pImageHeaderHash) == 0x23c);
C_ASSERT(FIELD_OFFSET(PEB32, WaitOnAddressHashTable) == 0x25c);
C_ASSERT(sizeof(PEB32) == 0x460);

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

#endif

#include "ntlsa.h"

#ifndef _NTSAM_H
#define _NTSAM_H

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

NTSTATUS NTAPI SamFreeMemory(
	_In_ PVOID Buffer
);

NTSTATUS NTAPI SamCloseHandle(
	_In_ SAM_HANDLE SamHandle
);

_Check_return_
NTSTATUS NTAPI SamSetSecurityObject(
	_In_ SAM_HANDLE ObjectHandle,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

_Check_return_
NTSTATUS NTAPI SamQuerySecurityObject(
	_In_ SAM_HANDLE ObjectHandle,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_Outptr_ PSECURITY_DESCRIPTOR *SecurityDescriptor
);

_Check_return_
NTSTATUS NTAPI SamRidToSid(
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
NTSTATUS NTAPI SamConnect(
	_In_opt_ PUNICODE_STRING ServerName,
	_Out_ PSAM_HANDLE ServerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_Check_return_
NTSTATUS NTAPI SamShutdownSamServer(
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
NTSTATUS NTAPI SamLookupDomainInSamServer(
	_In_ SAM_HANDLE ServerHandle,
	_In_ PUNICODE_STRING Name,
	_Outptr_ PSID *DomainId
);

_Check_return_
NTSTATUS NTAPI SamEnumerateDomainsInSamServer(
	_In_ SAM_HANDLE ServerHandle,
	_Inout_ PSAM_ENUMERATE_HANDLE EnumerationContext,
	_Outptr_ PVOID *Buffer, // PSAM_SID_ENUMERATION *Buffer
	_In_ ULONG PreferedMaximumLength,
	_Out_ PULONG CountReturned
);

_Check_return_
NTSTATUS NTAPI SamOpenDomain(
	_In_ SAM_HANDLE ServerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ PSID DomainId,
	_Out_ PSAM_HANDLE DomainHandle
);

_Check_return_
NTSTATUS NTAPI SamQueryInformationDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ DOMAIN_INFORMATION_CLASS DomainInformationClass,
	_Outptr_ PVOID *Buffer
);

_Check_return_
NTSTATUS NTAPI SamSetInformationDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ DOMAIN_INFORMATION_CLASS DomainInformationClass,
	_In_ PVOID DomainInformation
);

_Check_return_
NTSTATUS NTAPI SamLookupNamesInDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ ULONG Count,
	_In_reads_(Count) PUNICODE_STRING Names,
	_Out_ _Deref_post_count_(Count) PULONG *RelativeIds,
	_Out_ _Deref_post_count_(Count) PSID_NAME_USE *Use
);

_Check_return_
NTSTATUS NTAPI SamLookupIdsInDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ ULONG Count,
	_In_reads_(Count) PULONG RelativeIds,
	_Out_ _Deref_post_count_(Count) PUNICODE_STRING *Names,
	_Out_ _Deref_post_opt_count_(Count) PSID_NAME_USE *Use
);

_Check_return_
NTSTATUS NTAPI SamRemoveMemberFromForeignDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ PSID MemberId
);

_Check_return_
NTSTATUS NTAPI SamQueryLocalizableAccountsInDomain(
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
NTSTATUS NTAPI SamEnumerateGroupsInDomain(
	_In_ SAM_HANDLE DomainHandle,
	_Inout_ PSAM_ENUMERATE_HANDLE EnumerationContext,
	_Outptr_ PVOID *Buffer, // PSAM_RID_ENUMERATION *
	_In_ ULONG PreferedMaximumLength,
	_Out_ PULONG CountReturned
);

_Check_return_
NTSTATUS NTAPI SamCreateGroupInDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ PUNICODE_STRING AccountName,
	_In_ ACCESS_MASK DesiredAccess,
	_Out_ PSAM_HANDLE GroupHandle,
	_Out_ PULONG RelativeId
);

_Check_return_
NTSTATUS NTAPI SamOpenGroup(
	_In_ SAM_HANDLE DomainHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG GroupId,
	_Out_ PSAM_HANDLE GroupHandle
);

_Check_return_
NTSTATUS NTAPI SamDeleteGroup(
	_In_ SAM_HANDLE GroupHandle
);

_Check_return_
NTSTATUS NTAPI SamQueryInformationGroup(
	_In_ SAM_HANDLE GroupHandle,
	_In_ GROUP_INFORMATION_CLASS GroupInformationClass,
	_Outptr_ PVOID *Buffer
);

_Check_return_
NTSTATUS NTAPI SamSetInformationGroup(
	_In_ SAM_HANDLE GroupHandle,
	_In_ GROUP_INFORMATION_CLASS GroupInformationClass,
	_In_ PVOID Buffer
);

_Check_return_
NTSTATUS NTAPI SamAddMemberToGroup(
	_In_ SAM_HANDLE GroupHandle,
	_In_ ULONG MemberId,
	_In_ ULONG Attributes
);

_Check_return_
NTSTATUS NTAPI SamRemoveMemberFromGroup(
	_In_ SAM_HANDLE GroupHandle,
	_In_ ULONG MemberId
);

_Check_return_
NTSTATUS NTAPI SamGetMembersInGroup(
	_In_ SAM_HANDLE GroupHandle,
	_Out_ _Deref_post_count_(*MemberCount) PULONG *MemberIds,
	_Out_ _Deref_post_count_(*MemberCount) PULONG *Attributes,
	_Out_ PULONG MemberCount
);

_Check_return_
NTSTATUS NTAPI SamSetMemberAttributesOfGroup(
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
} ALIAS_GENERAL_INFORMATION, *PALIAS_GENERAL_INFORMATION;

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
NTSTATUS NTAPI SamEnumerateAliasesInDomain(
	_In_ SAM_HANDLE DomainHandle,
	_Inout_ PSAM_ENUMERATE_HANDLE EnumerationContext,
	_Outptr_ PVOID *Buffer, // PSAM_RID_ENUMERATION *Buffer
	_In_ ULONG PreferedMaximumLength,
	_Out_ PULONG CountReturned
);

_Check_return_
NTSTATUS NTAPI SamCreateAliasInDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ PUNICODE_STRING AccountName,
	_In_ ACCESS_MASK DesiredAccess,
	_Out_ PSAM_HANDLE AliasHandle,
	_Out_ PULONG RelativeId
);

_Check_return_
NTSTATUS NTAPI SamOpenAlias(
	_In_ SAM_HANDLE DomainHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG AliasId,
	_Out_ PSAM_HANDLE AliasHandle
);

_Check_return_
NTSTATUS NTAPI SamDeleteAlias(
	_In_ SAM_HANDLE AliasHandle
);

_Check_return_
NTSTATUS NTAPI SamQueryInformationAlias(
	_In_ SAM_HANDLE AliasHandle,
	_In_ ALIAS_INFORMATION_CLASS AliasInformationClass,
	_Outptr_ PVOID *Buffer
);

_Check_return_
NTSTATUS NTAPI SamSetInformationAlias(
	_In_ SAM_HANDLE AliasHandle,
	_In_ ALIAS_INFORMATION_CLASS AliasInformationClass,
	_In_ PVOID Buffer
);

_Check_return_
NTSTATUS NTAPI SamAddMemberToAlias(
	_In_ SAM_HANDLE AliasHandle,
	_In_ PSID MemberId
);

_Check_return_
NTSTATUS NTAPI SamAddMultipleMembersToAlias(
	_In_ SAM_HANDLE AliasHandle,
	_In_reads_(MemberCount) PSID *MemberIds,
	_In_ ULONG MemberCount
);

_Check_return_
NTSTATUS NTAPI SamRemoveMemberFromAlias(
	_In_ SAM_HANDLE AliasHandle,
	_In_ PSID MemberId
);

_Check_return_
NTSTATUS NTAPI SamRemoveMultipleMembersFromAlias(
	_In_ SAM_HANDLE AliasHandle,
	_In_reads_(MemberCount) PSID *MemberIds,
	_In_ ULONG MemberCount
);

_Check_return_
NTSTATUS NTAPI SamGetMembersInAlias(
	_In_ SAM_HANDLE AliasHandle,
	_Out_ _Deref_post_count_(*MemberCount) PSID **MemberIds,
	_Out_ PULONG MemberCount
);

_Check_return_
NTSTATUS NTAPI SamGetAliasMembership(
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
	UserGeneralInformation = 1,
	UserPreferencesInformation,
	UserLogonInformation,
	UserLogonHoursInformation,
	UserAccountInformation,
	UserNameInformation,
	UserAccountNameInformation,
	UserFullNameInformation,
	UserPrimaryGroupInformation,
	UserHomeInformation,
	UserScriptInformation,
	UserProfileInformation,
	UserAdminCommentInformation,
	UserWorkStationsInformation,
	UserSetPasswordInformation,
	UserControlInformation,
	UserExpiresInformation,
	UserInternal1Information,
	UserInternal2Information,
	UserParametersInformation,
	UserAllInformation,
	UserInternal3Information,
	UserInternal4Information,
	UserInternal5Information,
	UserInternal4InformationNew,
	UserInternal5InformationNew,
	UserInternal6Information,
	UserExtendedInformation,
	UserLogonUIInformation
} USER_INFORMATION_CLASS, *PUSER_INFORMATION_CLASS;

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

#define USER_ALL_READ_GENERAL_MASK (USER_ALL_USERNAME | \
    USER_ALL_FULLNAME | \
    USER_ALL_USERID | \
    USER_ALL_PRIMARYGROUPID | \
    USER_ALL_ADMINCOMMENT | \
    USER_ALL_USERCOMMENT)

// Fields that require USER_READ_LOGON access to read.

#define USER_ALL_READ_LOGON_MASK (USER_ALL_HOMEDIRECTORY | \
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

#define USER_ALL_READ_ACCOUNT_MASK (USER_ALL_PASSWORDLASTSET | \
    USER_ALL_ACCOUNTEXPIRES | \
    USER_ALL_USERACCOUNTCONTROL | \
    USER_ALL_PARAMETERS)

// Fields that require USER_READ_PREFERENCES access to read.

#define USER_ALL_READ_PREFERENCES_MASK (USER_ALL_COUNTRYCODE | \
    USER_ALL_CODEPAGE)

// Fields that can only be read by trusted clients.

#define USER_ALL_READ_TRUSTED_MASK (USER_ALL_NTPASSWORDPRESENT | \
    USER_ALL_LMPASSWORDPRESENT | \
    USER_ALL_PASSWORDEXPIRED | \
    USER_ALL_SECURITYDESCRIPTOR | \
    USER_ALL_PRIVATEDATA)

// Fields that can't be read.

#define USER_ALL_READ_CANT_MASK USER_ALL_UNDEFINED_MASK

// Fields that require USER_WRITE_ACCOUNT access to write.

#define USER_ALL_WRITE_ACCOUNT_MASK (USER_ALL_USERNAME | \
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

#define USER_ALL_WRITE_PREFERENCES_MASK (USER_ALL_USERCOMMENT | \
    USER_ALL_COUNTRYCODE | \
    USER_ALL_CODEPAGE)

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

#define USER_ALL_WRITE_TRUSTED_MASK (USER_ALL_LASTLOGON | \
    USER_ALL_LASTLOGOFF | \
    USER_ALL_BADPASSWORDCOUNT | \
    USER_ALL_LOGONCOUNT | \
    USER_ALL_PASSWORDLASTSET | \
    USER_ALL_SECURITYDESCRIPTOR | \
    USER_ALL_PRIVATEDATA)

// Fields that can't be written.

#define USER_ALL_WRITE_CANT_MASK (USER_ALL_USERID | \
    USER_ALL_PASSWORDCANCHANGE | \
    USER_ALL_PASSWORDMUSTCHANGE | \
    USER_ALL_UNDEFINED_MASK)

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

typedef struct _USER_PARAMETERS_INFORMATION
{
	UNICODE_STRING Parameters;
} USER_PARAMETERS_INFORMATION, *PUSER_PARAMETERS_INFORMATION;

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
} USER_LOGON_INFORMATION, *PUSER_LOGON_INFORMATION;
#include <poppack.h>

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
} USER_ACCOUNT_INFORMATION, *PUSER_ACCOUNT_INFORMATION;
#include <poppack.h>

typedef struct _USER_ACCOUNT_NAME_INFORMATION
{
	UNICODE_STRING UserName;
} USER_ACCOUNT_NAME_INFORMATION, *PUSER_ACCOUNT_NAME_INFORMATION;

typedef struct _USER_FULL_NAME_INFORMATION
{
	UNICODE_STRING FullName;
} USER_FULL_NAME_INFORMATION, *PUSER_FULL_NAME_INFORMATION;

typedef struct _USER_NAME_INFORMATION
{
	UNICODE_STRING UserName;
	UNICODE_STRING FullName;
} USER_NAME_INFORMATION, *PUSER_NAME_INFORMATION;

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

typedef struct _USER_LOGON_HOURS_INFORMATION
{
	LOGON_HOURS LogonHours;
} USER_LOGON_HOURS_INFORMATION, *PUSER_LOGON_HOURS_INFORMATION;

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
} USER_PWD_CHANGE_FAILURE_INFORMATION, *PUSER_PWD_CHANGE_FAILURE_INFORMATION;

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
NTSTATUS NTAPI SamEnumerateUsersInDomain(
	_In_ SAM_HANDLE DomainHandle,
	_Inout_ PSAM_ENUMERATE_HANDLE EnumerationContext,
	_In_ ULONG UserAccountControl,
	_Outptr_ PVOID *Buffer, // PSAM_RID_ENUMERATION *
	_In_ ULONG PreferedMaximumLength,
	_Out_ PULONG CountReturned
);

_Check_return_
NTSTATUS NTAPI SamCreateUserInDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ PUNICODE_STRING AccountName,
	_In_ ACCESS_MASK DesiredAccess,
	_Out_ PSAM_HANDLE UserHandle,
	_Out_ PULONG RelativeId
);

_Check_return_
NTSTATUS NTAPI SamCreateUser2InDomain(
	_In_ SAM_HANDLE DomainHandle,
	_In_ PUNICODE_STRING AccountName,
	_In_ ULONG AccountType,
	_In_ ACCESS_MASK DesiredAccess,
	_Out_ PSAM_HANDLE UserHandle,
	_Out_ PULONG GrantedAccess,
	_Out_ PULONG RelativeId
);

_Check_return_
NTSTATUS NTAPI SamOpenUser(
	_In_ SAM_HANDLE DomainHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG UserId,
	_Out_ PSAM_HANDLE UserHandle
);

_Check_return_
NTSTATUS NTAPI SamDeleteUser(
	_In_ SAM_HANDLE UserHandle
);

_Check_return_
NTSTATUS NTAPI SamQueryInformationUser(
	_In_ SAM_HANDLE UserHandle,
	_In_ USER_INFORMATION_CLASS UserInformationClass,
	_Outptr_ PVOID *Buffer
);

_Check_return_
NTSTATUS NTAPI SamSetInformationUser(
	_In_ SAM_HANDLE UserHandle,
	_In_ USER_INFORMATION_CLASS UserInformationClass,
	_In_ PVOID Buffer
);

_Check_return_
NTSTATUS NTAPI SamGetGroupsForUser(
	_In_ SAM_HANDLE UserHandle,
	_Out_ _Deref_post_count_(*MembershipCount) PGROUP_MEMBERSHIP *Groups,
	_Out_ PULONG MembershipCount
);

_Check_return_
NTSTATUS NTAPI SamChangePasswordUser(
	_In_ SAM_HANDLE UserHandle,
	_In_ PUNICODE_STRING OldPassword,
	_In_ PUNICODE_STRING NewPassword
);

_Check_return_
NTSTATUS NTAPI SamChangePasswordUser2(
	_In_ PUNICODE_STRING ServerName,
	_In_ PUNICODE_STRING UserName,
	_In_ PUNICODE_STRING OldPassword,
	_In_ PUNICODE_STRING NewPassword
);

_Check_return_
NTSTATUS NTAPI SamChangePasswordUser3(
	_In_ PUNICODE_STRING ServerName,
	_In_ PUNICODE_STRING UserName,
	_In_ PUNICODE_STRING OldPassword,
	_In_ PUNICODE_STRING NewPassword,
	_Outptr_ PDOMAIN_PASSWORD_INFORMATION *EffectivePasswordPolicy,
	_Outptr_ PUSER_PWD_CHANGE_FAILURE_INFORMATION *PasswordChangeFailureInfo
);

_Check_return_
NTSTATUS NTAPI SamQueryDisplayInformation(
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
NTSTATUS NTAPI SamGetDisplayEnumerationIndex(
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

typedef NTSTATUS(NTAPI *PSAM_DELTA_NOTIFICATION_ROUTINE)(
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
NTSTATUS NTAPI SamRegisterObjectChangeNotification(
	_In_ SECURITY_DB_OBJECT_TYPE ObjectType,
	_In_ HANDLE NotificationEventHandle
);

NTSTATUS NTAPI SamUnregisterObjectChangeNotification(
	_In_ SECURITY_DB_OBJECT_TYPE ObjectType,
	_In_ HANDLE NotificationEventHandle
);

// Compatibility mode

#define SAM_SID_COMPATIBILITY_ALL 0
#define SAM_SID_COMPATIBILITY_LAX 1
#define SAM_SID_COMPATIBILITY_STRICT 2

_Check_return_
NTSTATUS NTAPI SamGetCompatibilityMode(
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
NTSTATUS NTAPI SamValidatePassword(
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
NTSTATUS NTAPI SamPerformGenericOperation(
	_In_opt_ PWSTR ServerName,
	_In_ SAM_GENERIC_OPERATION_TYPE OperationType,
	_In_ PSAM_GENERIC_OPERATION_INPUT OperationIn,
	_Out_ PSAM_GENERIC_OPERATION_OUTPUT *OperationOut
);

#endif

#ifndef _NTMISC_H
#define _NTMISC_H

// Boot graphics

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSCALLAPI NTSTATUS NTAPI NtDrawText(
	_In_ PUNICODE_STRING Text
);

// rev
NTSYSCALLAPI NTSTATUS NTAPI ZwDrawText(
	_In_ PUNICODE_STRING Text
);
#endif

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

NTSYSCALLAPI NTSTATUS NTAPI NtVdmControl(
	_In_ VDMSERVICECLASS Service,
	_Inout_ PVOID ServiceData
);

NTSYSCALLAPI NTSTATUS NTAPI ZwVdmControl(
	_In_ VDMSERVICECLASS Service,
	_Inout_ PVOID ServiceData
);

// WMI/ETW

NTSYSCALLAPI NTSTATUS NTAPI NtTraceEvent(
	_In_ HANDLE TraceHandle,
	_In_ ULONG Flags,
	_In_ ULONG FieldSize,
	_In_ PVOID Fields
);

NTSYSCALLAPI NTSTATUS NTAPI ZwTraceEvent(
	_In_ HANDLE TraceHandle,
	_In_ ULONG Flags,
	_In_ ULONG FieldSize,
	_In_ PVOID Fields
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSCALLAPI NTSTATUS NTAPI NtTraceControl(
	_In_ ULONG FunctionCode,
	_In_reads_bytes_opt_(InBufferLen) PVOID InBuffer,
	_In_ ULONG InBufferLen,
	_Out_writes_bytes_opt_(OutBufferLen) PVOID OutBuffer,
	_In_ ULONG OutBufferLen,
	_Out_ PULONG ReturnLength
);

// private
NTSYSCALLAPI NTSTATUS NTAPI ZwTraceControl(
	_In_ ULONG FunctionCode,
	_In_reads_bytes_opt_(InBufferLen) PVOID InBuffer,
	_In_ ULONG InBufferLen,
	_Out_writes_bytes_opt_(OutBufferLen) PVOID OutBuffer,
	_In_ ULONG OutBufferLen,
	_Out_ PULONG ReturnLength
);
#endif

#endif

#endif

//*****************************************************************************

#ifdef __cplusplus
}
#endif

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif
