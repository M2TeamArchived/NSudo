#pragma once

#pragma comment(lib,"winsta.lib")

#define LOGONID_CURRENT     ((ULONG)-1)
#define SERVERNAME_CURRENT  ((HANDLE)NULL)

typedef	enum _WINSTATIONINFOCLASS
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
	WinStationInformationEx
} WINSTATIONINFOCLASS;

typedef struct _WINSTATIONUSERTOKEN {
	HANDLE ProcessId;
	HANDLE ThreadId;
	HANDLE UserToken;
} WINSTATIONUSERTOKEN, *PWINSTATIONUSERTOKEN;

extern "C" BOOLEAN WINAPI WinStationQueryInformationW(
	_In_   HANDLE hServer,
	_In_   ULONG LogonId,
	_In_   WINSTATIONINFOCLASS WinStationInformationClass,
	_Out_  PVOID pWinStationInformation,
	_In_   ULONG WinStationInformationLength,
	_Out_  PULONG pReturnLength);


/*BOOLEAN WINAPI WinStationQueryInformationW(
	_In_   HANDLE hServer,
	_In_   ULONG LogonId,
	_In_   WINSTATIONINFOCLASS WinStationInformationClass,
	_Out_  PVOID pWinStationInformation,
	_In_   ULONG WinStationInformationLength,
	_Out_  PULONG pReturnLength
	)
{
	HINSTANCE hInstWinSta = LoadLibraryW(L"winsta.dll");
	if (hInstWinSta == NULL) return FALSE;

	typedef BOOLEAN(WINAPI * PWINSTATIONQUERYINFORMATIONW)(
		HANDLE, ULONG, WINSTATIONINFOCLASS, PVOID, ULONG, PULONG);

	PWINSTATIONQUERYINFORMATIONW WinStationQueryInformationW =
		(PWINSTATIONQUERYINFORMATIONW)GetProcAddress(hInstWinSta, "WinStationQueryInformationW");

	if (WinStationQueryInformationW == NULL) return FALSE;

	return WinStationQueryInformationW(
		hServer,
		LogonId,
		WinStationInformationClass,
		pWinStationInformation,
		WinStationInformationLength,
		pReturnLength);
}*/