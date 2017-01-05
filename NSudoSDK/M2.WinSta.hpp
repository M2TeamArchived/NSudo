/******************************************************************************
项目:
	M2-Team\\NSudo\\NSudoSDK
描述：
	窗口站管理调用及其数据结构定义
文件名:
	\\NSudoSDK\\M2.WinSta.hpp
基于项目：
	Process Hacker的PHNT库
许可协议：
	无（致敬ProcessHacker作者Wen Jia Liu）
用法：
	直接Include此头文件即可
建议的Windows SDK版本：
	10.0.10586及以后
维护者列表：
	Mouri_Naruto (Mouri_Naruto@Outlook.com)
修订日志：
	1.1(2017-01-05)
	1.使用新的代码标头
	2.整理定义

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

#ifndef WINSTAAPI
#define WINSTAAPI

#if _MSC_VER > 1000
#pragma once
#endif

// Windows 头文件
#include <windows.h>

// SDK 版本定义
#include <SDKDDKVer.h>

// winsta.lib
#pragma comment(lib,"winsta.lib")

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	// begin_msdn:http://msdn.microsoft.com/en-us/library/cc248779%28PROT.10%29.aspx

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

	typedef enum _WINSTATIONINFOCLASS
	{
		WinStationCreateData,
		WinStationConfiguration,
		WinStationPdParams,
		WinStationWd,
		WinStationPd,
		WinStationPrinter,
		WinStationClient,
		WinStationModules,
		WinStationInformation,
		WinStationTrace,
		WinStationBeep,
		WinStationEncryptionOff,
		WinStationEncryptionPerm,
		WinStationNtSecurity,
		WinStationUserToken,
		WinStationUnused1,
		WinStationVideoData,
		WinStationInitialProgram,
		WinStationCd,
		WinStationSystemTrace,
		WinStationVirtualData,
		WinStationClientData,
		WinStationSecureDesktopEnter,
		WinStationSecureDesktopExit,
		WinStationLoadBalanceSessionTarget,
		WinStationLoadIndicator,
		WinStationShadowInfo,
		WinStationDigProductId,
		WinStationLockedState,
		WinStationRemoteAddress,
		WinStationIdleTime,
		WinStationLastReconnectType,
		WinStationDisallowAutoReconnect,
		WinStationUnused2,
		WinStationUnused3,
		WinStationUnused4,
		WinStationUnused5,
		WinStationReconnectedFromId,
		WinStationEffectsPolicy,
		WinStationType,
		WinStationInformationEx,
		WinStationValidationInfo
	} WINSTATIONINFOCLASS;

	// WinStationCreateData
	typedef struct _WINSTATIONCREATE
	{
		ULONG fEnableWinStation : 1;
		ULONG MaxInstanceCount;
	} WINSTATIONCREATE, *PWINSTATIONCREATE;

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

	// WinStationInformation
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

	// WinStationUserToken
	typedef struct _WINSTATIONUSERTOKEN
	{
		HANDLE ProcessId;
		HANDLE ThreadId;
		HANDLE UserToken;
	} WINSTATIONUSERTOKEN, *PWINSTATIONUSERTOKEN;

	// WinStationVideoData
	typedef struct _WINSTATIONVIDEODATA
	{
		USHORT HResolution;
		USHORT VResolution;
		USHORT fColorDepth;
	} WINSTATIONVIDEODATA, *PWINSTATIONVIDEODATA;

	// WinStationDigProductId
	typedef struct _WINSTATIONPRODID
	{
		WCHAR DigProductId[CLIENT_PRODUCT_ID_LENGTH];
		WCHAR ClientDigProductId[CLIENT_PRODUCT_ID_LENGTH];
		WCHAR OuterMostDigProductId[CLIENT_PRODUCT_ID_LENGTH];
		ULONG CurrentSessionId;
		ULONG ClientSessionId;
		ULONG OuterMostSessionId;
	} WINSTATIONPRODID, *PWINSTATIONPRODID;

	// WinStationRemoteAddress
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

	// In the functions below, memory returned can be freed using LocalFree.
	// NULL can be specified for server handles to indicate the local server.
	// -1 can be specified for session IDs to indicate the current session ID.

#define LOGONID_CURRENT (-1)
#define SERVERNAME_CURRENT (NULL)

	// rev
	BOOLEAN WINAPI WinStationFreeMemory(
		_In_ PVOID Buffer
	);

	// rev
	HANDLE WINAPI WinStationOpenServerW(
		_In_ PWSTR ServerName
	);

	// rev
	BOOLEAN WINAPI WinStationCloseServer(
		_In_ HANDLE hServer
	);

	// rev
	BOOLEAN WINAPI WinStationServerPing(
		_In_opt_ HANDLE hServer
	);

	// rev
	BOOLEAN WINAPI WinStationGetTermSrvCountersValue(
		_In_opt_ HANDLE hServer,
		_In_ ULONG Count,
		_Inout_ PTS_COUNTER Counters // set counter IDs before calling
	);

	BOOLEAN WINAPI WinStationShutdownSystem(
		_In_opt_ HANDLE hServer,
		_In_ ULONG ShutdownFlags // WSD_*
	);

	// rev
	BOOLEAN WINAPI WinStationWaitSystemEvent(
		_In_opt_ HANDLE hServer,
		_In_ ULONG EventMask, // WEVENT_*
		_Out_ PULONG EventFlags
	);

	// rev
	BOOLEAN WINAPI WinStationRegisterConsoleNotification(
		_In_opt_ HANDLE hServer,
		_In_ HWND WindowHandle,
		_In_ ULONG Flags
	);

	// rev
	BOOLEAN WINAPI WinStationUnRegisterConsoleNotification(
		_In_opt_ HANDLE hServer,
		_In_ HWND WindowHandle
	);

	// Sessions

	// rev
	BOOLEAN WINAPI WinStationEnumerateW(
		_In_opt_ HANDLE hServer,
		_Out_ PSESSIONIDW *SessionIds,
		_Out_ PULONG Count
	);

	BOOLEAN WINAPI WinStationQueryInformationW(
		_In_opt_ HANDLE hServer,
		_In_ ULONG SessionId,
		_In_ WINSTATIONINFOCLASS WinStationInformationClass,
		_Out_writes_bytes_(WinStationInformationLength) PVOID pWinStationInformation,
		_In_ ULONG WinStationInformationLength,
		_Out_ PULONG pReturnLength
	);

	// rev
	BOOLEAN WINAPI WinStationSetInformationW(
		_In_opt_ HANDLE hServer,
		_In_ ULONG SessionId,
		_In_ WINSTATIONINFOCLASS WinStationInformationClass,
		_In_reads_bytes_(WinStationInformationLength) PVOID pWinStationInformation,
		_In_ ULONG WinStationInformationLength
	);

	BOOLEAN WINAPI WinStationNameFromLogonIdW(
		_In_opt_ HANDLE hServer,
		_In_ ULONG SessionId,
		_Out_writes_(WINSTATIONNAME_LENGTH + 1) PWSTR pWinStationName
	);

	// rev
	BOOLEAN WINAPI WinStationSendMessageW(
		_In_opt_ HANDLE hServer,
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

	BOOLEAN WINAPI WinStationConnectW(
		_In_opt_ HANDLE hServer,
		_In_ ULONG SessionId,
		_In_ ULONG TargetSessionId,
		_In_opt_ PWSTR pPassword,
		_In_ BOOLEAN bWait
	);

	BOOLEAN WINAPI WinStationDisconnect(
		_In_opt_ HANDLE hServer,
		_In_ ULONG SessionId,
		_In_ BOOLEAN bWait
	);

	// rev
	BOOLEAN WINAPI WinStationReset(
		_In_opt_ HANDLE hServer,
		_In_ ULONG SessionId,
		_In_ BOOLEAN bWait
	);

	// rev
	BOOLEAN WINAPI WinStationShadow(
		_In_opt_ HANDLE hServer,
		_In_ PWSTR TargetServerName,
		_In_ ULONG TargetSessionId,
		_In_ UCHAR HotKeyVk,
		_In_ USHORT HotkeyModifiers // KBD*
	);

	// rev
	BOOLEAN WINAPI WinStationShadowStop(
		_In_opt_ HANDLE hServer,
		_In_ ULONG SessionId,
		_In_ BOOLEAN bWait // ignored
	);

	// Processes

	// rev
	BOOLEAN WINAPI WinStationEnumerateProcesses(
		_In_opt_ HANDLE hServer,
		_Out_ PVOID *Processes
	);

	// rev
	BOOLEAN WINAPI WinStationGetAllProcesses(
		_In_opt_ HANDLE hServer,
		_In_ ULONG Level,
		_Out_ PULONG NumberOfProcesses,
		_Out_ PTS_ALL_PROCESSES_INFO *Processes
	);

	// rev
	BOOLEAN WINAPI WinStationFreeGAPMemory(
		_In_ ULONG Level,
		_In_ PTS_ALL_PROCESSES_INFO Processes,
		_In_ ULONG NumberOfProcesses
	);

	// rev
	BOOLEAN WINAPI WinStationTerminateProcess(
		_In_opt_ HANDLE hServer,
		_In_ ULONG ProcessId,
		_In_ ULONG ExitCode
	);

	BOOLEAN WINAPI WinStationGetProcessSid(
		_In_opt_ HANDLE hServer,
		_In_ ULONG ProcessId,
		_In_ FILETIME ProcessStartTime,
		_Out_ PVOID pProcessUserSid,
		_Inout_ PULONG dwSidSize
	);

	// Services isolation

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)

	// rev
	BOOLEAN WINAPI WinStationSwitchToServicesSession(
		VOID
	);

	// rev
	BOOLEAN WINAPI WinStationRevertFromServicesSession(
		VOID
	);

#endif

	// Misc.

	BOOLEAN WINAPI _WinStationWaitForConnect(
		VOID
	);

	// end_msdn
#ifdef __cplusplus
}
#endif

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif // !M2_WINSTATION