//NSudo 3.1
//NSudo Team. All rights reserved.

#include "stdafx.h"

//在指定的AppContainer运行一个程序(不能在模拟令牌模式调用，也不能在System和TrustedInstaller权限下调用)
bool NSudoCreateProcessInAppContainer(HANDLE hToken, PCWSTR pszAppContainerName, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,LPCWSTR lpCurrentDirectory)
{
	bool bRet = true;

	const WELL_KNOWN_SID_TYPE capabilitiyTypeList[] =
	{
		WinCapabilityInternetClientSid,
		WinCapabilityInternetClientServerSid,
		WinCapabilityPrivateNetworkClientServerSid,
		WinCapabilityPicturesLibrarySid,
		WinCapabilityVideosLibrarySid,
		WinCapabilityMusicLibrarySid,
		WinCapabilityDocumentsLibrarySid,
		WinCapabilitySharedUserCertificatesSid,
		WinCapabilityEnterpriseAuthenticationSid,
		WinCapabilityRemovableStorageSid,
	};

	SID_AND_ATTRIBUTES CapabilitiesList[10];
	for (int i = 0; i < 10; i++)
	{
		DWORD dwSIDSize = SECURITY_MAX_SID_SIZE;
		CapabilitiesList[i].Sid = new unsigned char[SECURITY_MAX_SID_SIZE];
		CapabilitiesList[i].Attributes = SE_GROUP_ENABLED;
		if (!CreateWellKnownSid(capabilitiyTypeList[i], NULL, CapabilitiesList[i].Sid, &dwSIDSize) ||
			!IsWellKnownSid(CapabilitiesList[i].Sid, capabilitiyTypeList[i]))
		{
			bRet = false;
			break;
		}
	}

	if (bRet)
	{
		bRet = false;

		PSID pAppContainerSID;
		if (S_OK == DeriveAppContainerSidFromAppContainerName(pszAppContainerName, &pAppContainerSID))
		{
			SECURITY_CAPABILITIES SecurityCapabilities = { pAppContainerSID, CapabilitiesList, 10, 0 };
			STARTUPINFOEX StartupInfoEx = { 0 };
			PROCESS_INFORMATION ProcessInfo = { 0 };
			StartupInfoEx.StartupInfo.cb = sizeof(STARTUPINFOEXW);

			SIZE_T cbAttributeListSize = 0;
			InitializeProcThreadAttributeList(NULL, 3, 0, &cbAttributeListSize);
			StartupInfoEx.lpAttributeList = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, cbAttributeListSize);
			if (InitializeProcThreadAttributeList(StartupInfoEx.lpAttributeList, 3, 0, &cbAttributeListSize))
			{
				if (UpdateProcThreadAttribute(
					StartupInfoEx.lpAttributeList,
					0,
					PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES,
					&SecurityCapabilities,
					sizeof(SecurityCapabilities),
					NULL,
					NULL))
				{
					if (CreateProcessAsUserW(
						hToken, lpApplicationName, lpCommandLine, nullptr, nullptr, FALSE,
						EXTENDED_STARTUPINFO_PRESENT | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
						NULL, lpCurrentDirectory, (LPSTARTUPINFOW)&StartupInfoEx, &ProcessInfo))
					{
						bRet = true;
					}
					DeleteProcThreadAttributeList(StartupInfoEx.lpAttributeList);
				}
			}
			FreeSid(pAppContainerSID);
		}
	}
	return bRet;
}

//创建一个AppContainer
bool NSudoCreateAppContainer(PCWSTR pszAppContainerName, PCWSTR pszDisplayName, PCWSTR pszDescription, bool bReCreate)
{
	bool bRet = false;

	PSID pSidAppContainerSid;

	if (bReCreate) DeleteAppContainerProfile(pszAppContainerName);

	if (S_OK == CreateAppContainerProfile(
		pszAppContainerName,
		pszDisplayName,
		pszDescription,
		NULL, NULL, &pSidAppContainerSid))
	{

		bRet = true;
	}

	if (pSidAppContainerSid) FreeSid(pSidAppContainerSid);

	return bRet;
}

//删除指定的AppContainer
bool NSudoDeleteAppContainer(PCWSTR pszAppContainerName)
{
	if (S_OK == DeleteAppContainerProfile(pszAppContainerName)) return true;
	return false;
}