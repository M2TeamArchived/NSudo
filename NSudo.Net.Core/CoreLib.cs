using System;
using System.Diagnostics;
using System.ServiceProcess;


/*These Code are unimplemented*/

namespace NSudo
{
    public class CoreLib
    {
        //获取一个进程的PID
        int NSudoGetProcessID(string szProcessName, bool bUnderCurrentSessionID)
        {
            int dwPID = -1 /*进程ID*/, dwUserSessionID = Process.GetCurrentProcess().SessionId /*会话ID*/;

            try
            {
                Process[] ps = Process.GetProcesses();
                foreach (Process p in ps)
                {
                    if (szProcessName == p.ProcessName) //寻找%szProcessName%进程
                    {
                        if (bUnderCurrentSessionID && p.SessionId != dwUserSessionID) continue; //判断是否是当前用户ID
                        dwPID = p.Id;
                        break;
                    }
                }
            }
            catch { }
      
            return dwPID;
        }

        //根据令牌创建进程（对CreateProcess和CreateEnvironmentBlock的封装，可能需要SE_ASSIGNPRIMARYTOKEN_NAME特权）
        bool NSudoCreateProcess(IntPtr hToken, string lpCommandLine)
        {
            Win32.STARTUPINFO StartupInfo = new Win32.STARTUPINFO();
            Win32.PROCESS_INFORMATION ProcessInfo = new Win32.PROCESS_INFORMATION();
            StartupInfo.lpDesktop = @"WinSta0\\Default";

            string szSystemDirectory = Environment.GetFolderPath(Environment.SpecialFolder.System);
            string szBuffer = @szSystemDirectory + "\\cmd.exe /c start \"" + szSystemDirectory + "\\cmd.exe\" " + lpCommandLine;

            return CreateProcessWithTokenW(
                hToken,
                LOGON_WITH_PROFILE,
                NULL,
                szBuffer,
                CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT,
                NULL,
                NULL,
                &StartupInfo,
                &ProcessInfo);
        }

        //设置令牌权限
        bool SetTokenPrivilege(IntPtr TokenHandle, string lpName, bool bEnable)
        {
            TOKEN_PRIVILEGES TP;

            TP.PrivilegeCount = 1;
            TP.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : NULL;

            if (LookupPrivilegeValueW(NULL, lpName, &TP.Privileges[0].Luid))
            {
                AdjustTokenPrivileges(TokenHandle, FALSE, &TP, sizeof(TP), NULL, NULL);
                if (GetLastError() == ERROR_SUCCESS) return true;
            }

            return false;
        }

        //设置当前进程令牌权限
        bool SetCurrentProcessPrivilege(string lpName, bool bEnable)
        {
            bool bRet = false;
            IntPtr hCurrentProcessToken = new IntPtr();
            if (Win32.OpenProcessToken(Process.GetCurrentProcess().Handle, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, ref hCurrentProcessToken))
            {
                bRet = SetTokenPrivilege(hCurrentProcessToken, lpName, bEnable);
                Win32.CloseHandle(hCurrentProcessToken);
            }
            return bRet;
        }

        //一键开启或关闭所有特权
        void NSudoAdjustAllTokenPrivileges(IntPtr TokenHandle, bool bEnable)
        {
            wchar_t* PrivilegeList[] =
            {
        SE_CREATE_TOKEN_NAME,
        SE_ASSIGNPRIMARYTOKEN_NAME,
        SE_LOCK_MEMORY_NAME,
        SE_INCREASE_QUOTA_NAME,
        SE_UNSOLICITED_INPUT_NAME,
        SE_MACHINE_ACCOUNT_NAME,
        SE_TCB_NAME,
        SE_SECURITY_NAME,
        SE_TAKE_OWNERSHIP_NAME,
        SE_LOAD_DRIVER_NAME,
        SE_SYSTEM_PROFILE_NAME,
        SE_SYSTEMTIME_NAME,
        SE_PROF_SINGLE_PROCESS_NAME,
        SE_INC_BASE_PRIORITY_NAME,
        SE_CREATE_PAGEFILE_NAME,
        SE_CREATE_PERMANENT_NAME,
        SE_BACKUP_NAME,
        SE_RESTORE_NAME,
        SE_SHUTDOWN_NAME,
        SE_DEBUG_NAME,
        SE_AUDIT_NAME,
        SE_SYSTEM_ENVIRONMENT_NAME,
        SE_CHANGE_NOTIFY_NAME,
        SE_REMOTE_SHUTDOWN_NAME,
        SE_UNDOCK_NAME,
        SE_SYNC_AGENT_NAME,
        SE_ENABLE_DELEGATION_NAME,
        SE_MANAGE_VOLUME_NAME,
        SE_IMPERSONATE_NAME,
        SE_CREATE_GLOBAL_NAME,
        SE_TRUSTED_CREDMAN_ACCESS_NAME,
        SE_RELABEL_NAME,
        SE_INC_WORKING_SET_NAME,
        SE_TIME_ZONE_NAME,
        SE_CREATE_SYMBOLIC_LINK_NAME
    };

            for (int i = 0; i < sizeof(PrivilegeList) / sizeof(wchar_t*); i++)
            {
                SetTokenPrivilege(TokenHandle, PrivilegeList[i], bEnable);
            }
        }

        //获取System权限令牌(需要SE_DEBUG_NAME特权)
        bool NSudoGetSystemToken(ref IntPtr hNewToken)
        {
            bool bRet = false;

            //获取当前会话ID下的winlogon的PID
            int dwWinLogonPID = NSudoGetProcessID("winlogon.exe", true);
            if (dwWinLogonPID != -1)
            {
                try
                {
                    IntPtr hToken = new IntPtr();
                    if (Win32.OpenProcessToken(Process.GetProcessById(dwWinLogonPID).Handle, Win32.TOKEN_DUPLICATE, ref hToken))
                    {
                        bRet = Win32.DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, null, Win32.SECURITY_IMPERSONATION_LEVEL.SecurityIdentification, Win32.TOKEN_TYPE.TokenPrimary, hNewToken);
                        Win32.CloseHandle(hToken);
                    }
                }
                catch { }          
            }
            return bRet;
        }

        //模拟当前进程的权限令牌为System权限(如果想取消模拟，可以调用RevertToSelf)
        bool NSudoImpersonateSystemToken()
        {
            bool bRet = false;

            HANDLE hSystemToken;
            if (NSudoGetSystemToken(&hSystemToken)) //获取System权限令牌
            {
                NSudoAdjustAllTokenPrivileges(hSystemToken, true); //在模拟令牌上开启所有特权
                bRet = ImpersonateLoggedOnUser(hSystemToken); //模拟令牌
                Win32.CloseHandle(hSystemToken);
            }
            return bRet;
        }

        //获取TrustedInstaller权限令牌(需要SE_DEBUG_NAME特权)
        bool NSudoGetTrustedInstallerToken(ref IntPtr hNewToken)
        {
            bool bRet = false;

            ServiceController sc = new ServiceController("TrustedInstaller");
            if (sc.Status == ServiceControllerStatus.Stopped) sc.Start();

            if (NSudoImpersonateSystemToken())
            {
                //获取当前会话ID下的TrustedInstaller的PID
                int dwTIPID = NSudoGetProcessID("TrustedInstaller.exe", false);

                if (dwTIPID != -1)
                {
                    IntPtr hToken = new IntPtr();
                    if (Win32.OpenProcessToken(Process.GetProcessById(dwTIPID).Handle, TOKEN_DUPLICATE | TOKEN_QUERY, ref hToken))
                    {
                        bRet = Win32.DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, null, Win32.SECURITY_IMPERSONATION_LEVEL.SecurityIdentification, Win32.TOKEN_TYPE.TokenPrimary, ref hNewToken);
                        Win32.CloseHandle(hToken);
                    }
                }

                RevertToSelf();
            }

            return bRet;
        }

        //获取当前用户的令牌(需要SE_DEBUG_NAME特权)
        bool NSudoGetCurrentUserToken(ref IntPtr phNewToken)
        {
            bool bRet = false;

            if (NSudoImpersonateSystemToken())
            {
                DWORD dwUserSessionId = WTSGetActiveConsoleSessionId();
                if (0xFFFFFFFF != dwUserSessionId)
                {
                    bRet = WTSQueryUserToken(dwUserSessionId, phNewToken);
                }

                RevertToSelf();
            }

            return bRet;
        }

        //设置令牌完整性
        bool SetTokenIntegrity(IntPtr hToken, string szIntegritySID)
        {
            bool bRet = false;

            TOKEN_MANDATORY_LABEL TokenMandatoryLabel = { 0 };  //令牌完整性结构
            if (ConvertStringSidToSidW(szIntegritySID, &TokenMandatoryLabel.Label.Sid)) //获取低完整性SID
            {
                TokenMandatoryLabel.Label.Attributes = SE_GROUP_INTEGRITY;

                //设置进程完整性级别
                bRet = SetTokenInformation(hToken, TokenIntegrityLevel, &TokenMandatoryLabel, sizeof(TokenMandatoryLabel));

                FreeSid(TokenMandatoryLabel.Label.Sid); //释放低完整性SID
            }

            return bRet;
        }

        //获取当前进程的令牌
        bool NSudoGetCurrentProcessToken(ref IntPtr hNewToken)
        {
            bool bRet = false;

            IntPtr hToken = new IntPtr();
            if (Win32.OpenProcessToken(Process.GetCurrentProcess().Handle, MAXIMUM_ALLOWED, ref hToken)) //打开当前进程令牌
            {
                bRet = Win32.DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, null, Win32.SECURITY_IMPERSONATION_LEVEL.SecurityIdentification, Win32.TOKEN_TYPE.TokenPrimary, hNewToken);
                Win32.CloseHandle(hToken); // 关闭 hToken 句柄
            }

            return bRet;
        }

        //对当前进程进行降权并获取令牌
        bool NSudoCreateLUAToken(ref IntPtr hNewToken)
        {
            bool bRet = false;

            IntPtr hToken = new IntPtr();


            HANDLE hHeap = GetProcessHeap();

            // 创建受限令牌
            if (Win32.NtFilterToken(Process.GetCurrentProcess().Handle, LUA_TOKEN, NULL, NULL, NULL, ref hToken) >= 0)
            {
                //完整性设置为中（管理员权限需要）
                SetTokenIntegrity(hToken, "S-1-16-8192");

                DWORD dwReturnLength;
                bRet = GetTokenInformation(hToken, TokenUser, 0, 0, &dwReturnLength);

                PTOKEN_USER pTokenUser = (PTOKEN_USER)HeapAlloc(hHeap, 0, dwReturnLength);
                if (pTokenUser)
                {
                    GetTokenInformation(hToken, TokenUser, pTokenUser, dwReturnLength, &dwReturnLength);

                    //设置令牌Owner为当前用户（管理员权限需要）
                    PTOKEN_OWNER pTokenOwner = (PTOKEN_OWNER)HeapAlloc(hHeap, 0, sizeof(TOKEN_OWNER));
                    if (pTokenOwner)
                    {
                        pTokenOwner->Owner = pTokenUser->User.Sid;
                        SetTokenInformation(hToken, TokenOwner, pTokenOwner, 4);
                        HeapFree(hHeap, 0, pTokenOwner);
                    }

                    //设置令牌的ACL（管理员权限需要）
                    GetTokenInformation(hToken, TokenDefaultDacl, 0, 0, &dwReturnLength);

                    PTOKEN_DEFAULT_DACL pTokenDefaultDacl = (PTOKEN_DEFAULT_DACL)HeapAlloc(hHeap, 0, dwReturnLength);
                    if (pTokenDefaultDacl)
                    {
                        GetTokenInformation(hToken, TokenDefaultDacl, pTokenDefaultDacl, dwReturnLength, &dwReturnLength);

                        //删除Administrator对于该令牌的权限
                        //DeleteAce(pTokenDefaultDacl->DefaultDacl, 0);

                        //初始化EXPLICIT_ACCESS结构
                        EXPLICIT_ACCESS_W ea;
                        ea.grfAccessMode = GRANT_ACCESS;
                        ea.grfAccessPermissions = GENERIC_ALL;
                        ea.grfInheritance = OBJECT_INHERIT_ACE | CONTAINER_INHERIT_ACE;
                        BuildTrusteeWithSidW(&ea.Trustee, pTokenUser->User.Sid);

                        PACL pNewACL = NULL;
                        if (ERROR_SUCCESS == SetEntriesInAclW(1, &ea, pTokenDefaultDacl->DefaultDacl, &pNewACL))
                        {
                            pTokenDefaultDacl->DefaultDacl = pNewACL;
                            SetTokenInformation(hToken, TokenDefaultDacl, pTokenDefaultDacl, sizeof(pTokenDefaultDacl));
                        }
                        HeapFree(hHeap, 0, pTokenDefaultDacl);
                    }
                    HeapFree(hHeap, 0, pTokenUser);
                }

                //复制令牌
                bRet = Win32.DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, null, Win32.SECURITY_IMPERSONATION_LEVEL.SecurityIdentification, Win32.TOKEN_TYPE.TokenPrimary, ref hNewToken);

                Win32.CloseHandle(hToken);
            }

            return bRet;
        }

    }
}
