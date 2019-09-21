/*
 * PROJECT:   NSudo
 * FILE:      NSudo.cpp
 * PURPOSE:   Implementation for NSudo
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#define NOMINMAX

#pragma region targetver

#include <SDKDDKVer.h>

#define _WIN32_WINNT_WIN10_TH2 _WIN32_WINNT_WIN10
#define _WIN32_WINNT_WIN10_RS1 _WIN32_WINNT_WIN10

#pragma endregion

#include "M2.NSudo.h"

#include "M2WindowsHelpers.h"
#include "M2Win32GUIHelpers.h"

#include <commctrl.h>
#include <Userenv.h>
#include <WtsApi32.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Userenv.lib")
#pragma comment(lib,"WtsApi32.lib")

#include <cstdio>
#include <cwchar>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "json.hpp"

#if defined(NSUDO_GUI_WINDOWS)
#include <atlbase.h>
#include <atlwin.h>
#endif

#include "NSudoVersion.h"
#include "Resources/resource.h"


 // 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4505) // 未引用的本地函数已移除(等级 4)
#endif

std::wstring GetMessageByID(DWORD MessageID)
{
    std::wstring MessageString;
    LPWSTR pBuffer = nullptr;

    if (FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr,
        MessageID,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>(&pBuffer),
        0,
        nullptr))
    {
        MessageString = std::wstring(pBuffer, wcslen(pBuffer));

        LocalFree(pBuffer);
    }

    return MessageString;
}

HRESULT CreateCommandStoreItem(
    _In_ HKEY CommandStoreRoot,
    _In_ LPCWSTR ItemName,
    _In_ LPCWSTR ItemDescription,
    _In_ LPCWSTR ItemCommand,
    _In_ bool HasLUAShield)
{
    HRESULT hr = S_OK;
    M2::CHKey hCommandStoreItem;
    M2::CHKey hCommandStoreItemCommand;

    hr = M2RegCreateKey(
        CommandStoreRoot,
        ItemName,
        0,
        nullptr,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS | KEY_WOW64_64KEY,
        nullptr,
        &hCommandStoreItem,
        nullptr);
    if (FAILED(hr))
        return hr;

    hr = M2RegSetValue(
        hCommandStoreItem,
        L"",
        0,
        REG_SZ,
        reinterpret_cast<CONST BYTE*>(ItemDescription),
        static_cast<DWORD>(wcslen(ItemDescription) + 1) * sizeof(wchar_t));
    if (FAILED(hr))
        return hr;

    if (HasLUAShield)
    {
        hr = M2RegSetValue(
            hCommandStoreItem,
            L"HasLUAShield",
            0,
            REG_SZ,
            reinterpret_cast<CONST BYTE*>(L""),
            static_cast<DWORD>(wcslen(L"") + 1) * sizeof(wchar_t));
        if (FAILED(hr))
            return hr;
    }

    hr = M2RegCreateKey(
        hCommandStoreItem,
        L"command",
        0,
        nullptr,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS | KEY_WOW64_64KEY,
        nullptr,
        &hCommandStoreItemCommand,
        nullptr);
    if (FAILED(hr))
        return hr;

    hr = M2RegSetValue(
        hCommandStoreItemCommand,
        L"",
        0,
        REG_SZ,
        reinterpret_cast<CONST BYTE*>(ItemCommand),
        static_cast<DWORD>(wcslen(ItemCommand) + 1) * sizeof(wchar_t));
    if (FAILED(hr))
        return hr;

    return hr;
}

/*
   访问令牌特权定义
   The definitions of the Token Privileges
   */
typedef enum _TOKEN_PRIVILEGES_LIST
{
    SeMinWellKnownPrivilege = 2,
    SeCreateTokenPrivilege = 2,
    SeAssignPrimaryTokenPrivilege,
    SeLockMemoryPrivilege,
    SeIncreaseQuotaPrivilege,
    SeMachineAccountPrivilege,
    SeTcbPrivilege,
    SeSecurityPrivilege,
    SeTakeOwnershipPrivilege,
    SeLoadDriverPrivilege,
    SeSystemProfilePrivilege,
    SeSystemtimePrivilege,
    SeProfileSingleProcessPrivilege,
    SeIncreaseBasePriorityPrivilege,
    SeCreatePagefilePrivilege,
    SeCreatePermanentPrivilege,
    SeBackupPrivilege,
    SeRestorePrivilege,
    SeShutdownPrivilege,
    SeDebugPrivilege,
    SeAuditPrivilege,
    SeSystemEnvironmentPrivilege,
    SeChangeNotifyPrivilege,
    SeRemoteShutdownPrivilege,
    SeUndockPrivilege,
    SeSyncAgentPrivilege,
    SeEnableDelegationPrivilege,
    SeManageVolumePrivilege,
    SeImpersonatePrivilege,
    SeCreateGlobalPrivilege,
    SeTrustedCredManAccessPrivilege,
    SeRelabelPrivilege,
    SeIncreaseWorkingSetPrivilege,
    SeTimeZonePrivilege,
    SeCreateSymbolicLinkPrivilege,
    SeMaxWellKnownPrivilege = SeCreateSymbolicLinkPrivilege
} TOKEN_PRIVILEGES_LIST, *PTOKEN_PRIVILEGES_LIST;

/*
NSudoGetCurrentProcessSessionID获取当前进程的会话ID。
The NSudoGetCurrentProcessSessionID function obtains the Session ID of the
current process.

如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
If the function fails, the return value is NULL. To get extended error
information, call GetLastError.
*/
BOOL WINAPI NSudoGetCurrentProcessSessionID(
    _Out_ PDWORD SessionID)
{
    *SessionID = static_cast<DWORD>(-1);

    BOOL result = FALSE;
    M2::CHandle hToken;
    DWORD ReturnLength = 0;

    M2_PROCESS_ACCESS_TOKEN_SOURCE TokenSource;
    TokenSource.Type = M2_PROCESS_TOKEN_SOURCE_TYPE::Current;
    result = SUCCEEDED(M2OpenProcessToken(
        &hToken, &TokenSource, MAXIMUM_ALLOWED));
    if (result)
    {
        result = SUCCEEDED(M2GetTokenInformation(
            hToken,
            TokenSessionId,
            SessionID,
            sizeof(DWORD),
            &ReturnLength));
    }

    return result;
}

/*
NSudoSetTokenPrivilege函数启用或禁用指定的访问令牌的指定特权。启用或禁用一
个访问令牌的特权需要TOKEN_ADJUST_PRIVILEGES访问权限。
The NSudoSetTokenPrivilege function enables or disables the specified
privilege in the specified access token. Enabling or disabling privileges
in an access token requires TOKEN_ADJUST_PRIVILEGES access.

如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
If the function fails, the return value is NULL. To get extended error
information, call GetLastError.
*/
BOOL WINAPI NSudoSetTokenPrivilege(
    _In_ HANDLE hExistingToken,
    _In_ TOKEN_PRIVILEGES_LIST Privilege,
    _In_ bool bEnable)
{
    LUID_AND_ATTRIBUTES RawPrivilege;

    RawPrivilege.Luid.HighPart = 0;
    RawPrivilege.Luid.LowPart = Privilege;
    RawPrivilege.Attributes = (DWORD)(bEnable ? SE_PRIVILEGE_ENABLED : 0);

    DWORD ErrorCode = M2::NSudo::NSudoAdjustTokenPrivileges(
        hExistingToken, &RawPrivilege, 1);
    ::SetLastError(ErrorCode);
    return (ErrorCode == ERROR_SUCCESS);
}

/*
NSudoSetTokenAllPrivileges函数启用或禁用指定的访问令牌的所有特权。启用或禁
用一个访问令牌的特权需要TOKEN_ADJUST_PRIVILEGES访问权限。
The NSudoSetTokenAllPrivileges function enables or disables all privileges
in the specified access token. Enabling or disabling privileges in an
access token requires TOKEN_ADJUST_PRIVILEGES access.

如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
If the function fails, the return value is NULL. To get extended error
information, call GetLastError.
*/
BOOL WINAPI NSudoSetTokenAllPrivileges(
    _In_ HANDLE hExistingToken,
    _In_ bool bEnable)
{
    BOOL result = FALSE;
    M2::CM2Memory<PTOKEN_PRIVILEGES> pTPs;

    result = SUCCEEDED(M2GetTokenInformation(
        pTPs,
        hExistingToken,
        TokenPrivileges));
    if (result)
    {
        // 设置特权信息
        for (DWORD i = 0; i < pTPs->PrivilegeCount; ++i)
            pTPs->Privileges[i].Attributes =
            (DWORD)(bEnable ? SE_PRIVILEGE_ENABLED : 0);

        // 设置进程特权
        DWORD ErrorCode = M2::NSudo::NSudoAdjustTokenPrivileges(
            hExistingToken, pTPs->Privileges, pTPs->PrivilegeCount);
        ::SetLastError(ErrorCode);
        result = (ErrorCode == ERROR_SUCCESS);
    }

    return result;
}

/*
NSudoSetTokenIntegrityLevel函数为指定的访问令牌设置完整性标签。
The NSudoSetTokenIntegrityLevel function sets the integrity level for the
specified access token.

如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
If the function fails, the return value is NULL. To get extended error
information, call GetLastError.
*/
BOOL WINAPI NSudoSetTokenIntegrityLevel(
    _In_ HANDLE TokenHandle,
    _In_ M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE IL)
{
    BOOL result = FALSE;
    TOKEN_MANDATORY_LABEL TML;

    // 初始化SID
    DWORD ErrorCode = M2::NSudo::NSudoCreateMandatoryLabelSid(
        &TML.Label.Sid, IL);
    ::SetLastError(ErrorCode);
    result = (ErrorCode == ERROR_SUCCESS);
    if (result)
    {
        // 初始化TOKEN_MANDATORY_LABEL
        TML.Label.Attributes = SE_GROUP_INTEGRITY;

        // 设置令牌对象
        result = SUCCEEDED(M2SetTokenInformation(
            TokenHandle, TokenIntegrityLevel, &TML, sizeof(TML)));

        ::FreeSid(TML.Label.Sid);
    }

    return result;
}

/*
NSudoCreateLUAToken函数从一个现有的访问令牌创建一个新的LUA访问令牌。
The NSudoCreateLUAToken function creates a new LUA access token from an
existing access token.

如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
If the function fails, the return value is NULL. To get extended error
information, call GetLastError.
*/
BOOL WINAPI NSudoCreateLUAToken(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ExistingTokenHandle)
{
    *TokenHandle = INVALID_HANDLE_VALUE;

    BOOL result = FALSE;
    DWORD Length = 0;
    BOOL EnableTokenVirtualization = TRUE;
    TOKEN_OWNER Owner = { 0 };
    TOKEN_DEFAULT_DACL NewTokenDacl = { 0 };
    M2::CHandle hToken;
    M2::CM2Memory<PTOKEN_USER> pTokenUser;
    M2::CM2Memory<PTOKEN_DEFAULT_DACL> pTokenDacl;
    M2::CMemory<PACL> NewDefaultDacl;
    PACCESS_ALLOWED_ACE pTempAce = nullptr;

    //创建受限令牌
    result = CreateRestrictedToken(
        ExistingTokenHandle,
        LUA_TOKEN,
        0, nullptr,
        0, nullptr,
        0, nullptr,
        &hToken);
    if (!result) goto FuncEnd;

    // 设置令牌完整性
    result = NSudoSetTokenIntegrityLevel(
        hToken, M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE::MEDIUM);
    if (!result) goto FuncEnd;

    // 获取令牌对应的用户账户SID信息
    result = SUCCEEDED(M2GetTokenInformation(
        pTokenUser,
        hToken,
        TokenUser));
    if (!result) goto FuncEnd;

    // 设置令牌Owner为当前用户
    Owner.Owner = pTokenUser->User.Sid;
    result = SUCCEEDED(M2SetTokenInformation(
        hToken, TokenOwner, &Owner, sizeof(TOKEN_OWNER)));
    if (!result) goto FuncEnd;

    // 获取令牌的DACL信息
    result = SUCCEEDED(M2GetTokenInformation(
        pTokenDacl,
        hToken,
        TokenDefaultDacl));
    if (!result) goto FuncEnd;

    // 计算新ACL大小
    Length = pTokenDacl->DefaultDacl->AclSize;
    Length += GetLengthSid(pTokenUser->User.Sid);
    Length += sizeof(ACCESS_ALLOWED_ACE);

    // 分配ACL结构内存
    if (!NewDefaultDacl.Alloc(Length))
    {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        goto FuncEnd;
    }
    NewTokenDacl.DefaultDacl = NewDefaultDacl;

    // 创建ACL
    result = InitializeAcl(
        NewTokenDacl.DefaultDacl,
        Length,
        pTokenDacl->DefaultDacl->AclRevision);
    if (!result) goto FuncEnd;

    // 添加ACE
    result = AddAccessAllowedAce(
        NewTokenDacl.DefaultDacl,
        pTokenDacl->DefaultDacl->AclRevision,
        GENERIC_ALL,
        pTokenUser->User.Sid);
    if (!result) goto FuncEnd;

    // 复制ACE
    for (ULONG i = 0;
        GetAce(pTokenDacl->DefaultDacl, i, (PVOID*)&pTempAce);
        ++i)
    {
        if (IsWellKnownSid(
            &pTempAce->SidStart,
            WELL_KNOWN_SID_TYPE::WinBuiltinAdministratorsSid))
            continue;

        AddAce(
            NewTokenDacl.DefaultDacl,
            pTokenDacl->DefaultDacl->AclRevision,
            0,
            pTempAce,
            pTempAce->Header.AceSize);
    }

    // 设置令牌DACL
    Length += sizeof(TOKEN_DEFAULT_DACL);
    result = SUCCEEDED(M2SetTokenInformation(
        hToken, TokenDefaultDacl, &NewTokenDacl, Length));
    if (!result) goto FuncEnd;

    // 开启LUA虚拟化
    result = SUCCEEDED(M2SetTokenInformation(
        hToken,
        TokenVirtualizationEnabled,
        &EnableTokenVirtualization,
        sizeof(BOOL)));
    if (!result) goto FuncEnd;

FuncEnd: // 扫尾

    if (result)
    {
        *TokenHandle = hToken.Detach();
    }

    return result;
}

HRESULT M2QueryWinLogonProcessId(
    _Out_ PDWORD ProcessId,
    _In_ DWORD SessionId)
{
    M2::CWTSMemory<PWTS_PROCESS_INFOW> pProcesses;
    DWORD dwProcessCount = 0;

    if (WTSEnumerateProcessesW(
        WTS_CURRENT_SERVER_HANDLE,
        0,
        1,
        &pProcesses,
        &dwProcessCount))
    {
        for (DWORD i = 0; i < dwProcessCount; ++i)
        {
            PWTS_PROCESS_INFOW pProcess = &pProcesses[i];

            if (pProcess->SessionId != SessionId)
                continue;

            if (!pProcess->pProcessName)
                continue;

            if (_wcsicmp(L"winlogon.exe", pProcess->pProcessName) != 0)
                continue;

            if (!pProcess->pUserSid)
                continue;

            if (!IsWellKnownSid(
                pProcess->pUserSid, WELL_KNOWN_SID_TYPE::WinLocalSystemSid))
                continue;

            *ProcessId = pProcess->ProcessId;
            return S_OK;
        }
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

/*
NSudoImpersonateAsSystem函数给当前线程分配一个SYSTEM用户模拟令牌。该函数还
可以使当前线程停止使用模拟令牌。
The NSudoImpersonateAsSystem function assigns an SYSTEM user impersonation
token to the current thread. The function can also cause the current thread
to stop using an impersonation token.

如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
If the function fails, the return value is NULL. To get extended error
information, call GetLastError.
*/
BOOL WINAPI NSudoImpersonateAsSystem()
{
    BOOL result = FALSE;

    DWORD dwSessionID = static_cast<DWORD>(-1);
    DWORD dwWinLogonPID = static_cast<DWORD>(-1);

    M2::CHandle OriginalToken;
    M2::CHandle Token;

    do
    {
        result = NSudoGetCurrentProcessSessionID(&dwSessionID);
        if (!result) break;

        if (FAILED(M2QueryWinLogonProcessId(&dwWinLogonPID, dwSessionID)))
            break;

        M2_PROCESS_ACCESS_TOKEN_SOURCE TokenSource;
        TokenSource.Type = M2_PROCESS_TOKEN_SOURCE_TYPE::ProcessId;
        TokenSource.ProcessId = dwWinLogonPID;
        if (FAILED(M2OpenProcessToken(
            &OriginalToken, &TokenSource, MAXIMUM_ALLOWED)))
            break;

        result = DuplicateTokenEx(
            OriginalToken,
            MAXIMUM_ALLOWED,
            nullptr,
            SecurityImpersonation,
            TokenImpersonation,
            &Token);
        if (!result) break;

        result = NSudoSetTokenAllPrivileges(Token, true);
        if (result)
        {
            result = SetThreadToken(nullptr, Token);
        }

    } while (false);

    return result;
}

/*
NSudoCreateProcess函数创建一个新进程和对应的主线程
The NSudoCreateProcess function creates a new process and its primary thread.

如果函数执行失败，返回值为NULL。调用GetLastError可获取详细错误码。
If the function fails, the return value is NULL. To get extended error
information, call GetLastError.
*/
bool NSudoCreateProcess(
    _In_opt_ HANDLE hToken,
    _Inout_ LPCWSTR lpCommandLine,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ DWORD WaitInterval,
    _In_ DWORD ProcessPriority = 0,
    _In_ DWORD ShowWindowMode = SW_SHOWDEFAULT,
    _In_ bool CreateNewConsole = true)
{
    DWORD dwCreationFlags = CREATE_SUSPENDED | CREATE_UNICODE_ENVIRONMENT;

    if (CreateNewConsole)
    {
        dwCreationFlags |= CREATE_NEW_CONSOLE;
    }

    STARTUPINFOW StartupInfo = { 0 };
    PROCESS_INFORMATION ProcessInfo = { 0 };

    StartupInfo.cb = sizeof(STARTUPINFOW);

    StartupInfo.lpDesktop = const_cast<LPWSTR>(L"WinSta0\\Default");

    StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = static_cast<WORD>(ShowWindowMode);

    LPVOID lpEnvironment = nullptr;

    BOOL result = FALSE;

    M2::CHandle hCurrentToken;
    M2_PROCESS_ACCESS_TOKEN_SOURCE TokenSource;
    TokenSource.Type = M2_PROCESS_TOKEN_SOURCE_TYPE::Current;
    if (SUCCEEDED(M2OpenProcessToken(
        &hCurrentToken, &TokenSource, MAXIMUM_ALLOWED)))
    {
        if (CreateEnvironmentBlock(&lpEnvironment, hCurrentToken, TRUE))
        {
            std::wstring ExpandedString;

            if (SUCCEEDED(M2ExpandEnvironmentStrings(
                ExpandedString,
                lpCommandLine)))
            {
                result = CreateProcessAsUserW(
                    hToken,
                    nullptr,
                    const_cast<LPWSTR>(ExpandedString.c_str()),
                    nullptr,
                    nullptr,
                    FALSE,
                    dwCreationFlags,
                    lpEnvironment,
                    lpCurrentDirectory,
                    &StartupInfo,
                    &ProcessInfo);

                if (result)
                {
                    SetPriorityClass(ProcessInfo.hProcess, ProcessPriority);

                    ResumeThread(ProcessInfo.hThread);

                    WaitForSingleObjectEx(
                        ProcessInfo.hProcess, WaitInterval, FALSE);

                    M2CloseHandle(ProcessInfo.hProcess);
                    M2CloseHandle(ProcessInfo.hThread);
                }
            }

            DestroyEnvironmentBlock(lpEnvironment);
        }
    }

    //返回结果
    return result;
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

// The NSudo message enum.
enum NSUDO_MESSAGE
{
    SUCCESS,
    PRIVILEGE_NOT_HELD,
    INVALID_COMMAND_PARAMETER,
    INVALID_TEXTBOX_PARAMETER,
    CREATE_PROCESS_FAILED,
    NEED_TO_SHOW_COMMAND_LINE_HELP,
    NEED_TO_SHOW_NSUDO_VERSION
};

const char* NSudoMessageTranslationID[] =
{
    "Message.Success",
    "Message.PrivilegeNotHeld",
    "Message.InvalidCommandParameter",
    "Message.InvalidTextBoxParameter",
    "Message.CreateProcessFailed",
    "",
    ""
};

class CNSudoTranslationAdapter
{
private:
    static std::wstring GetUTF8WithBOMStringResources(
        _In_ UINT uID)
    {
        M2_RESOURCE_INFO ResourceInfo = { 0 };
        if (SUCCEEDED(M2LoadResource(
            &ResourceInfo,
            GetModuleHandleW(nullptr),
            L"String",
            MAKEINTRESOURCEW(uID))))
        {
            // Raw string without the UTF-8 BOM. (0xEF,0xBB,0xBF)	
            return M2MakeUTF16String(std::string(
                reinterpret_cast<const char*>(ResourceInfo.Pointer) + 3,
                ResourceInfo.Size - 3));
        }

        return L"";
    }

public:
    static void Load(
        std::map<std::string, std::wstring>& StringTranslations)
    {
        StringTranslations.clear();

        StringTranslations.emplace(std::make_pair(
            "NSudo.VersionText",
            L"M2-Team NSudo " NSUDO_VERSION_STRING_FOR_SHOW));

        StringTranslations.emplace(std::make_pair(
            "NSudo.LogoText",
            L"M2-Team NSudo " NSUDO_VERSION_STRING_FOR_SHOW L"\r\n"
            L"© M2-Team. All rights reserved.\r\n"
            L"\r\n"));

        StringTranslations.emplace(std::make_pair(
            "NSudo.String.Links",
            CNSudoTranslationAdapter::GetUTF8WithBOMStringResources(
                IDR_String_Links)));

        StringTranslations.emplace(std::make_pair(
            "NSudo.String.CommandLineHelp",
            CNSudoTranslationAdapter::GetUTF8WithBOMStringResources(
                IDR_String_CommandLineHelp)));

        M2_RESOURCE_INFO ResourceInfo = { 0 };
        if (SUCCEEDED(M2LoadResource(
            &ResourceInfo,
            GetModuleHandleW(nullptr),
            L"String",
            MAKEINTRESOURCEW(IDR_String_Translations))))
        {
            nlohmann::json StringTranslationsJSON =
                nlohmann::json::parse(std::string(
                    reinterpret_cast<const char*>(ResourceInfo.Pointer),
                    ResourceInfo.Size));

            for (auto& Item : StringTranslationsJSON["Translations"].items())
            {
                StringTranslations.emplace(std::make_pair(
                    Item.key(),
                    M2MakeUTF16String(Item.value())));
            }
        }
    }
};

class CNSudoShortCutAdapter
{
public:
    static void Read(
        const std::wstring& ShortCutListPath,
        std::map<std::wstring, std::wstring>& ShortCutList)
    {
        ShortCutList.clear();

        FILE* FileStream = nullptr;

        if (_wfopen_s(&FileStream, ShortCutListPath.c_str(), L"r") == 0
            && FileStream)
        {
            nlohmann::json ConfigJSON = nlohmann::json::parse(FileStream);

            for (auto& Item : ConfigJSON["ShortCutList_V2"].items())
            {
                ShortCutList.emplace(std::make_pair(
                    M2MakeUTF16String(Item.key()),
                    M2MakeUTF16String(Item.value())));
            }

            fclose(FileStream);
        }
    }

    static void Write(
        const std::wstring& ShortCutListPath,
        const std::map<std::wstring, std::wstring>& ShortCutList)
    {
        ShortCutListPath;
        ShortCutList;
    }

    static std::wstring Translate(
        const std::map<std::wstring, std::wstring>& ShortCutList,
        const std::wstring& CommandLine)
    {
        auto iterator = ShortCutList.find(CommandLine);

        return iterator == ShortCutList.end() ? CommandLine : iterator->second;
    }
};

class CNSudoResourceManagement
{
private:
    bool m_IsInitialized = false;


    HINSTANCE m_Instance = nullptr;
    std::wstring m_ExePath;
    std::wstring m_AppPath;

    std::map<std::string, std::wstring> m_StringTranslations;
    std::map<std::wstring, std::wstring> m_ShortCutList;

    bool m_IsElevated = false;
    HANDLE m_OriginalCurrentProcessToken = INVALID_HANDLE_VALUE;

public:
    const HINSTANCE& Instance = this->m_Instance;
    const std::wstring& ExePath = this->m_ExePath;
    const std::wstring& AppPath = this->m_AppPath;

    const std::map<std::wstring, std::wstring>& ShortCutList =
        this->m_ShortCutList;

    const HANDLE& OriginalCurrentProcessToken =
        this->m_OriginalCurrentProcessToken;
    const bool& IsElevated = this->m_IsElevated;

public:
    CNSudoResourceManagement() = default;

    ~CNSudoResourceManagement()
    {
        if (this->m_IsInitialized)
        {
            UnInitialize();
        }
    }

    void Initialize()
    {
        if (!this->m_IsInitialized)
        {
            this->m_Instance = GetModuleHandleW(nullptr);

            this->m_ExePath = M2GetCurrentProcessModulePath();

            this->m_AppPath = this->m_ExePath;
            wcsrchr(&this->m_AppPath[0], L'\\')[0] = L'\0';
            this->m_AppPath.resize(wcslen(this->m_AppPath.c_str()));

            CNSudoTranslationAdapter::Load(this->m_StringTranslations);

            CNSudoShortCutAdapter::Read(
                this->AppPath + L"\\NSudo.json", this->m_ShortCutList);

            M2::CHandle CurrentProcessToken;

            M2_PROCESS_ACCESS_TOKEN_SOURCE TokenSource;
            TokenSource.Type = M2_PROCESS_TOKEN_SOURCE_TYPE::Current;
            if (SUCCEEDED(M2OpenProcessToken(
                &CurrentProcessToken, &TokenSource, MAXIMUM_ALLOWED)))
            {
                if (DuplicateTokenEx(
                    CurrentProcessToken,
                    MAXIMUM_ALLOWED,
                    nullptr,
                    SecurityIdentification,
                    TokenPrimary,
                    &this->m_OriginalCurrentProcessToken))
                {
                    this->m_IsElevated = NSudoSetTokenPrivilege(
                        CurrentProcessToken,
                        SeDebugPrivilege,
                        true);
                }
            }

            this->m_IsInitialized = true;
        }
    }

    void UnInitialize()
    {
        if (INVALID_HANDLE_VALUE != this->m_OriginalCurrentProcessToken)
        {
            M2CloseHandle(this->m_OriginalCurrentProcessToken);
        }
    }

    std::wstring GetTranslation(
        _In_ std::string Key)
    {
        return this->m_StringTranslations[Key];
    }

    std::wstring GetMessageString(
        _In_ NSUDO_MESSAGE MessageID)
    {
        return this->GetTranslation(NSudoMessageTranslationID[MessageID]);
    }
};

CNSudoResourceManagement g_ResourceManagement;

typedef struct _NSUDO_CONTEXT_MENU_ITEM
{
    std::wstring ItemName;
    std::wstring ItemDescription;
    std::wstring ItemCommandParameters;
    bool HasLUAShield = false;
} NSUDO_CONTEXT_MENU_ITEM, *PNSUDO_CONTEXT_MENU_ITEM;

class CNSudoContextMenuAdapter
{
public:
    static void Load(
        std::vector<NSUDO_CONTEXT_MENU_ITEM>& ContextMenuItems)
    {
        M2_RESOURCE_INFO ResourceInfo = { 0 };
        if (SUCCEEDED(M2LoadResource(
            &ResourceInfo,
            GetModuleHandleW(nullptr),
            L"Config",
            MAKEINTRESOURCEW(IDR_CONFIG_CONTEXT_MENU))))
        {
            nlohmann::json ContextMenuJSON =
                nlohmann::json::parse(std::string(
                    reinterpret_cast<const char*>(ResourceInfo.Pointer),
                    ResourceInfo.Size));

            for (auto& Item : ContextMenuJSON["ContextMenu"])
            {
                std::string RawItemName =
                    Item["ItemName"].get<std::string>();
                std::string RawItemDescriptionID =
                    Item["ItemDescriptionID"].get<std::string>();
                std::string RawItemCommandParameters =
                    Item["ItemCommandParameters"].get<std::string>();
                bool HasLUAShield =
                    Item["HasLUAShield"].get<bool>();

                NSUDO_CONTEXT_MENU_ITEM ContextMenuItem;

                ContextMenuItem.ItemName = M2MakeUTF16String(RawItemName);

                ContextMenuItem.ItemDescription =
                    g_ResourceManagement.GetTranslation(
                        RawItemDescriptionID);

                ContextMenuItem.ItemCommandParameters = M2MakeUTF16String(
                    RawItemCommandParameters);

                ContextMenuItem.HasLUAShield = HasLUAShield;

                ContextMenuItems.push_back(ContextMenuItem);
            }
        }
    }
};

class CNSudoContextMenuManagement
{
private:
    DWORD m_ConstructorError = ERROR_SUCCESS;

    std::wstring m_NSudoPath;
    M2::CHKey m_CommandStoreRoot;

    std::vector<NSUDO_CONTEXT_MENU_ITEM> m_ContextMenuItems;

public:
    CNSudoContextMenuManagement()
    {
        this->m_ConstructorError = M2GetWindowsDirectory(this->m_NSudoPath);
        if (FAILED(this->m_ConstructorError))
        {
            return;
        }
        this->m_NSudoPath.append(L"\\NSudo.exe");

        this->m_ConstructorError = RegOpenKeyExW(
            HKEY_LOCAL_MACHINE,
            L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell",
            0,
            KEY_ALL_ACCESS | KEY_WOW64_64KEY,
            &this->m_CommandStoreRoot);
        if (ERROR_SUCCESS != this->m_ConstructorError)
            return;

        CNSudoContextMenuAdapter::Load(this->m_ContextMenuItems);
    }

    HRESULT Install()
    {
        if (ERROR_SUCCESS != this->m_ConstructorError)
            return this->m_ConstructorError;

        CopyFileW(
            M2GetCurrentProcessModulePath().c_str(),
            this->m_NSudoPath.c_str(),
            FALSE);

        HRESULT hr = S_OK;

        std::wstring NSudoPathWithQuotation =
            std::wstring(L"\"") + this->m_NSudoPath + L"\"";

        M2::CHKey hNSudoItem;
        std::wstring SubCommands;

        for (NSUDO_CONTEXT_MENU_ITEM Item : this->m_ContextMenuItems)
        {
            std::wstring GeneratedItemCommand =
                NSudoPathWithQuotation + L" " +
                Item.ItemCommandParameters + L" " +
                L"-ShowWindowMode=Hide" + L" " +
                L"cmd /c start \"NSudo.ContextMenu.Launcher\" " + L"\"%1\"";

            hr = CreateCommandStoreItem(
                this->m_CommandStoreRoot,
                Item.ItemName.c_str(),
                Item.ItemDescription.c_str(),
                GeneratedItemCommand.c_str(),
                Item.HasLUAShield);
            if (FAILED(hr))
                return hr;

            SubCommands += Item.ItemName + L";";
        }

        hr = M2RegCreateKey(
            HKEY_CLASSES_ROOT,
            L"*\\shell\\NSudo",
            0,
            nullptr,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS | KEY_WOW64_64KEY,
            nullptr,
            &hNSudoItem,
            nullptr);
        if (FAILED(hr))
            return hr;

        struct
        {
            LPCWSTR lpValueName;
            LPCWSTR lpValueData;
        } ValueList[] =
        {
            {
                L"SubCommands",
                SubCommands.c_str()
            },{
                L"MUIVerb",
                L"NSudo"
            },{
                L"Icon",
                NSudoPathWithQuotation.c_str()
            },{
                L"Position",
                L"1"
            }
        };

        for (size_t i = 0; i < sizeof(ValueList) / sizeof(*ValueList); ++i)
        {
            hr = M2RegSetValue(
                hNSudoItem,
                ValueList[i].lpValueName,
                0,
                REG_SZ,
                reinterpret_cast<CONST BYTE*>(ValueList[i].lpValueData),
                sizeof(wchar_t) * static_cast<DWORD>(
                    wcslen(ValueList[i].lpValueData) + 1));
            if (FAILED(hr))
                return hr;

        }

        return hr;
    }

    DWORD Uninstall()
    {
        if (ERROR_SUCCESS != this->m_ConstructorError)
            return this->m_ConstructorError;

        // 首先尝试先去除只读，然后删除文件
        HANDLE hFile = INVALID_HANDLE_VALUE;
        HRESULT hr = M2CreateFile(
            &hFile,
            this->m_NSudoPath.c_str(),
            SYNCHRONIZE | DELETE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
            nullptr);
        if (SUCCEEDED(hr))
        {
            hr = M2DeleteFileIgnoreReadonlyAttribute(hFile);
            M2CloseHandle(hFile);
        }

        // 如果失败，则要求系统重启后删除
        if (FAILED(hr))
        {
            MoveFileExW(
                this->m_NSudoPath.c_str(),
                nullptr,
                MOVEFILE_DELAY_UNTIL_REBOOT);
        }

        DWORD dwError = ERROR_SUCCESS;

        for (NSUDO_CONTEXT_MENU_ITEM Item : this->m_ContextMenuItems)
        {
            dwError = RegDeleteTreeW(
                this->m_CommandStoreRoot,
                Item.ItemName.c_str());
            if (ERROR_SUCCESS != dwError)
                break;
        }

        dwError = RegDeleteTreeW(
            HKEY_CLASSES_ROOT,
            L"*\\shell\\NSudo");

        return dwError;
    }

};

// 解析命令行
NSUDO_MESSAGE NSudoCommandLineParser(
    _In_ bool bElevated,
    _In_ bool bEnableContextMenuManagement,
    _In_ std::wstring& ApplicationName,
    _In_ std::map<std::wstring, std::wstring>& OptionsAndParameters,
    _In_ std::wstring& UnresolvedCommandLine)
{
    UNREFERENCED_PARAMETER(ApplicationName);

    if (1 == OptionsAndParameters.size() && UnresolvedCommandLine.empty())
    {
        auto OptionAndParameter = *OptionsAndParameters.begin();


        if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"?") ||
            0 == _wcsicmp(OptionAndParameter.first.c_str(), L"H") ||
            0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Help"))
        {
            // 如果选项名是 "?", "H" 或 "Help"，则显示帮助。
            return NSUDO_MESSAGE::NEED_TO_SHOW_COMMAND_LINE_HELP;
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Version"))
        {
            // 如果选项名是 "?", "H" 或 "Help"，则显示 NSudo 版本号。
            return NSUDO_MESSAGE::NEED_TO_SHOW_NSUDO_VERSION;
        }
        else
        {
            if (bEnableContextMenuManagement)
            {
                CNSudoContextMenuManagement ContextMenuManagement;

                if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Install"))
                {
                    // 如果参数是 /Install 或 -Install，则安装NSudo到系统
                    if (FAILED(ContextMenuManagement.Install()))
                    {
                        ContextMenuManagement.Uninstall();
                    }

                    return NSUDO_MESSAGE::SUCCESS;
                }
                else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Uninstall"))
                {
                    // 如果参数是 /Uninstall 或 -Uninstall，则移除安装到系统的NSudo
                    ContextMenuManagement.Uninstall();

                    return NSUDO_MESSAGE::SUCCESS;
                }
            }

            return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
        }
    }

    DWORD dwSessionID = (DWORD)-1;

    // 获取当前进程会话ID
    if (!NSudoGetCurrentProcessSessionID(&dwSessionID))
    {
        return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
    }

    // 如果未提权或者模拟System权限失败
    if (!(bElevated && NSudoImpersonateAsSystem()))
    {
        return NSUDO_MESSAGE::PRIVILEGE_NOT_HELD;
    }

    bool bArgErr = false;

    M2::CHandle hToken;
    M2::CHandle hTempToken;

    // 解析参数列表

    enum class NSudoOptionUserValue
    {
        Default,
        TrustedInstaller,
        System,
        CurrentUser,
        CurrentProcess,
        CurrentProcessDropRight
    };

    enum class NSudoOptionPrivilegesValue
    {
        Default,
        EnableAllPrivileges,
        DisableAllPrivileges
    };

    enum class NSudoOptionProcessPriorityValue
    {
        Default,
        Idle,
        BelowNormal,
        Normal,
        AboveNormal,
        High,
        RealTime
    };

    enum class NSudoOptionWindowModeValue
    {
        Default,
        Show,
        Hide,
        Maximize,
        Minimize,
    };

    NSudoOptionUserValue UserMode =
        NSudoOptionUserValue::Default;
    NSudoOptionPrivilegesValue PrivilegesMode =
        NSudoOptionPrivilegesValue::Default;
    NSudoOptionProcessPriorityValue ProcessPriorityMode =
        NSudoOptionProcessPriorityValue::Default;
    NSudoOptionWindowModeValue WindowMode =
        NSudoOptionWindowModeValue::Default;

    DWORD WaitInterval = 0;
    std::wstring CurrentDirectory = g_ResourceManagement.AppPath;
    DWORD ShowWindowMode = SW_SHOWDEFAULT;
    bool CreateNewConsole = true;

    M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType =
        M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE::UNTRUSTED;

    for (auto& OptionAndParameter : OptionsAndParameters)
    {
        if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"U"))
        {
            if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"T"))
            {
                UserMode = NSudoOptionUserValue::TrustedInstaller;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"S"))
            {
                UserMode = NSudoOptionUserValue::System;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"C"))
            {
                UserMode = NSudoOptionUserValue::CurrentUser;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"P"))
            {
                UserMode = NSudoOptionUserValue::CurrentProcess;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"D"))
            {
                UserMode = NSudoOptionUserValue::CurrentProcessDropRight;
            }
            else
            {
                bArgErr = true;
                break;
            }
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"P"))
        {
            if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"E"))
            {
                PrivilegesMode = NSudoOptionPrivilegesValue::EnableAllPrivileges;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"D"))
            {
                PrivilegesMode = NSudoOptionPrivilegesValue::DisableAllPrivileges;
            }
            else
            {
                bArgErr = true;
                break;
            }
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"M"))
        {
            if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"S"))
            {
                MandatoryLabelType = M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE::SYSTEM;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"H"))
            {
                MandatoryLabelType = M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE::HIGH;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"M"))
            {
                MandatoryLabelType = M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE::MEDIUM;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"L"))
            {
                MandatoryLabelType = M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE::LOW;
            }
            else
            {
                bArgErr = true;
                break;
            }
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Wait"))
        {
            WaitInterval = INFINITE;
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"Priority"))
        {
            if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Idle"))
            {
                ProcessPriorityMode = NSudoOptionProcessPriorityValue::Idle;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"BelowNormal"))
            {
                ProcessPriorityMode = NSudoOptionProcessPriorityValue::BelowNormal;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Normal"))
            {
                ProcessPriorityMode = NSudoOptionProcessPriorityValue::Normal;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"AboveNormal"))
            {
                ProcessPriorityMode = NSudoOptionProcessPriorityValue::AboveNormal;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"High"))
            {
                ProcessPriorityMode = NSudoOptionProcessPriorityValue::High;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"RealTime"))
            {
                ProcessPriorityMode = NSudoOptionProcessPriorityValue::RealTime;
            }
            else
            {
                bArgErr = true;
                break;
            }
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"CurrentDirectory"))
        {
            CurrentDirectory = OptionAndParameter.second;
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"ShowWindowMode"))
        {
            if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Show"))
            {
                WindowMode = NSudoOptionWindowModeValue::Show;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Hide"))
            {
                WindowMode = NSudoOptionWindowModeValue::Hide;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Maximize"))
            {
                WindowMode = NSudoOptionWindowModeValue::Maximize;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Minimize"))
            {
                WindowMode = NSudoOptionWindowModeValue::Minimize;
            }
            else
            {
                bArgErr = true;
                break;
            }
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"UseCurrentConsole"))
        {
            CreateNewConsole = false;
        }
        else
        {
            bArgErr = true;
            break;
        }
    }

    if (bArgErr || NSudoOptionUserValue::Default == UserMode)
    {
        return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
    }

    M2::CHandle OriginalToken;

    if (NSudoOptionUserValue::TrustedInstaller == UserMode)
    {
        SERVICE_STATUS_PROCESS ssStatus;

        if (FAILED(M2StartService(L"TrustedInstaller", &ssStatus)))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }

        M2_PROCESS_ACCESS_TOKEN_SOURCE TokenSource;
        TokenSource.Type = M2_PROCESS_TOKEN_SOURCE_TYPE::ProcessId;
        TokenSource.ProcessId = ssStatus.dwProcessId;
        if (FAILED(M2OpenProcessToken(&OriginalToken, &TokenSource, MAXIMUM_ALLOWED)))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionUserValue::System == UserMode)
    {
        DWORD dwWinLogonPID = static_cast<DWORD>(-1);

        if (FAILED(M2QueryWinLogonProcessId(&dwWinLogonPID, dwSessionID)))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }

        M2_PROCESS_ACCESS_TOKEN_SOURCE TokenSource;
        TokenSource.Type = M2_PROCESS_TOKEN_SOURCE_TYPE::ProcessId;
        TokenSource.ProcessId = dwWinLogonPID;
        if (FAILED(M2OpenProcessToken(&OriginalToken, &TokenSource, MAXIMUM_ALLOWED)))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionUserValue::CurrentUser == UserMode)
    {
        if (!WTSQueryUserToken(dwSessionID, &OriginalToken))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionUserValue::CurrentProcess == UserMode)
    {
        if (!DuplicateTokenEx(
            g_ResourceManagement.OriginalCurrentProcessToken,
            MAXIMUM_ALLOWED,
            nullptr,
            SecurityIdentification,
            TokenPrimary,
            &OriginalToken))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionUserValue::CurrentProcessDropRight == UserMode)
    {
        if (!DuplicateTokenEx(
            g_ResourceManagement.OriginalCurrentProcessToken,
            MAXIMUM_ALLOWED,
            nullptr,
            SecurityIdentification,
            TokenPrimary,
            &hTempToken))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }

        if (!NSudoCreateLUAToken(&OriginalToken, hTempToken))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }

    if (!DuplicateTokenEx(
        OriginalToken,
        MAXIMUM_ALLOWED,
        nullptr,
        SecurityIdentification,
        TokenPrimary,
        &hToken))
    {
        return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
    }

    if (FAILED(M2SetTokenInformation(
        hToken,
        TokenSessionId,
        (PVOID)&dwSessionID,
        sizeof(DWORD))))
    {
        return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
    }

    if (NSudoOptionPrivilegesValue::EnableAllPrivileges == PrivilegesMode)
    {
        if (!NSudoSetTokenAllPrivileges(hToken, true))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionPrivilegesValue::DisableAllPrivileges == PrivilegesMode)
    {
        if (!NSudoSetTokenAllPrivileges(hToken, false))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }

    if (MandatoryLabelType != M2::NSudo::NSUDO_MANDATORY_LABEL_TYPE::UNTRUSTED)
    {
        if (!NSudoSetTokenIntegrityLevel(hToken, MandatoryLabelType))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }

    DWORD ProcessPriority = 0;

    if (NSudoOptionProcessPriorityValue::Idle == ProcessPriorityMode)
    {
        ProcessPriority = IDLE_PRIORITY_CLASS;
    }
    else if (NSudoOptionProcessPriorityValue::BelowNormal == ProcessPriorityMode)
    {
        ProcessPriority = BELOW_NORMAL_PRIORITY_CLASS;
    }
    else if (NSudoOptionProcessPriorityValue::Normal == ProcessPriorityMode)
    {
        ProcessPriority = NORMAL_PRIORITY_CLASS;
    }
    else if (NSudoOptionProcessPriorityValue::AboveNormal == ProcessPriorityMode)
    {
        ProcessPriority = ABOVE_NORMAL_PRIORITY_CLASS;
    }
    else if (NSudoOptionProcessPriorityValue::High == ProcessPriorityMode)
    {
        ProcessPriority = HIGH_PRIORITY_CLASS;
    }
    else if (NSudoOptionProcessPriorityValue::RealTime == ProcessPriorityMode)
    {
        ProcessPriority = REALTIME_PRIORITY_CLASS;
    }

    if (NSudoOptionWindowModeValue::Show == WindowMode)
    {
        ShowWindowMode = SW_SHOW;
    }
    else if (NSudoOptionWindowModeValue::Hide == WindowMode)
    {
        ShowWindowMode = SW_HIDE;
    }
    else if (NSudoOptionWindowModeValue::Maximize == WindowMode)
    {
        ShowWindowMode = SW_MAXIMIZE;
    }
    else if (NSudoOptionWindowModeValue::Minimize == WindowMode)
    {
        ShowWindowMode = SW_MINIMIZE;
    }

    if (UnresolvedCommandLine.empty())
    {
        return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
    }

    if (!NSudoCreateProcess(
        hToken,
        UnresolvedCommandLine.c_str(),
        CurrentDirectory.c_str(),
        WaitInterval,
        ProcessPriority,
        ShowWindowMode,
        CreateNewConsole))
    {
        return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
    }

    RevertToSelf();

    return NSUDO_MESSAGE::SUCCESS;
}

void NSudoPrintMsg(
    _In_opt_ HINSTANCE hInstance,
    _In_opt_ HWND hWnd,
    _In_ LPCWSTR lpContent)
{
    std::wstring DialogContent =
        g_ResourceManagement.GetTranslation("NSudo.LogoText") +
        lpContent +
        g_ResourceManagement.GetTranslation("NSudo.String.Links");

#if defined(NSUDO_CUI_CONSOLE)
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hWnd);

    DWORD NumberOfCharsWritten = 0;
    WriteConsoleW(
        GetStdHandle(STD_OUTPUT_HANDLE),
        DialogContent.c_str(),
        (DWORD)DialogContent.size(),
        &NumberOfCharsWritten,
        nullptr);
#elif defined(NSUDO_GUI_WINDOWS)
    M2MessageDialog(
        hInstance,
        hWnd,
        MAKEINTRESOURCE(IDI_NSUDO),
        L"NSudo",
        DialogContent.c_str());
#endif
}

HRESULT NSudoShowAboutDialog(
    _In_ HWND hwndParent)
{
    std::wstring DialogContent =
        g_ResourceManagement.GetTranslation("NSudo.LogoText") +
        g_ResourceManagement.GetTranslation("NSudo.String.CommandLineHelp") +
        g_ResourceManagement.GetTranslation("NSudo.String.Links");

    SetLastError(ERROR_SUCCESS);

#if defined(NSUDO_CUI_CONSOLE)
    UNREFERENCED_PARAMETER(hwndParent);

    DWORD NumberOfCharsWritten = 0;
    WriteConsoleW(
        GetStdHandle(STD_OUTPUT_HANDLE),
        DialogContent.c_str(),
        (DWORD)DialogContent.size(),
        &NumberOfCharsWritten,
        nullptr);
#elif defined(NSUDO_GUI_WINDOWS)
    M2MessageDialog(
        g_ResourceManagement.Instance,
        hwndParent,
        MAKEINTRESOURCE(IDI_NSUDO),
        L"NSudo",
        DialogContent.c_str());
#endif

    return M2GetLastHResultError();
}

#if defined(NSUDO_GUI_WINDOWS)

class CNSudoMainWindow : public ATL::CDialogImpl<CNSudoMainWindow>
{
public:
    enum { IDD = IDD_NSudoDlg };

public:
    BEGIN_MSG_MAP(CNSudoMainWindow)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_DPICHANGED, OnDPIChanged)

        COMMAND_ID_HANDLER(IDC_Run, OnRun)
        COMMAND_ID_HANDLER(IDC_About, OnAbout)
        COMMAND_ID_HANDLER(IDC_Browse, OnBrowse)

        MESSAGE_HANDLER(WM_DROPFILES, OnDropFiles)
    END_MSG_MAP()

public:
    CNSudoMainWindow()
    {
        M2EnablePerMonitorDialogScaling();

        ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
        ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); // WM_COPYGLOBALDATA
    }

    ~CNSudoMainWindow()
    {

    }

private:
    HICON m_hNSudoIcon = nullptr;
    HICON m_hWarningIcon = nullptr;

    int m_xDPI = USER_DEFAULT_SCREEN_DPI;
    int m_yDPI = USER_DEFAULT_SCREEN_DPI;

    ATL::CWindow m_hUserName;
    ATL::CWindow m_hCheckBox;
    ATL::CWindow m_hszPath;

    LRESULT OnClose(
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam,
        BOOL& bHandled)
    {
        UNREFERENCED_PARAMETER(uMsg);
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        UNREFERENCED_PARAMETER(bHandled);

        this->EndDialog(0);
        return 0;
    }

    LRESULT OnInitDialog(
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam,
        BOOL& bHandled)
    {
        UNREFERENCED_PARAMETER(uMsg);
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        UNREFERENCED_PARAMETER(bHandled);

        this->m_hUserName = this->GetDlgItem(IDC_UserName);
        this->m_hCheckBox = this->GetDlgItem(IDC_Check_EnableAllPrivileges);
        this->m_hszPath = this->GetDlgItem(IDC_szPath);

        this->SetWindowTextW(
            g_ResourceManagement.GetTranslation("NSudo.VersionText").c_str());

        struct { const char* ID; ATL::CWindow Control; } x[] =
        {
            { "EnableAllPrivileges" , this->m_hCheckBox },
            { "WarningText" , this->GetDlgItem(IDC_WARNINGTEXT) },
            { "SettingsGroupText" ,this->GetDlgItem(IDC_SETTINGSGROUPTEXT) },
            { "Static.User",this->GetDlgItem(IDC_STATIC_USER) },
            { "Static.Open", this->GetDlgItem(IDC_STATIC_OPEN) },
            { "Button.About", this->GetDlgItem(IDC_About) },
            { "Button.Browse", this->GetDlgItem(IDC_Browse) },
            { "Button.Run", this->GetDlgItem(IDC_Run) }
        };

        for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); ++i)
        {
            std::wstring Buffer = g_ResourceManagement.GetTranslation(x[i].ID);
            x[i].Control.SetWindowTextW(Buffer.c_str());
        }

        HRESULT hr = E_FAIL;

        hr = M2GetDpiForMonitor(
            MonitorFromWindow(this->m_hWnd, MONITOR_DEFAULTTONEAREST),
            MDT_EFFECTIVE_DPI, (UINT*)&this->m_xDPI, (UINT*)&this->m_yDPI);
        if (hr != S_OK)
        {
            this->m_xDPI = GetDeviceCaps(this->GetDC(), LOGPIXELSX);
            this->m_yDPI = GetDeviceCaps(this->GetDC(), LOGPIXELSY);
        }

        this->m_hNSudoIcon = (HICON)LoadImageW(
            g_ResourceManagement.Instance,
            MAKEINTRESOURCE(IDI_NSUDO),
            IMAGE_ICON,
            256,
            256,
            LR_SHARED);

        SendMessageW(this->m_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)this->m_hNSudoIcon);
        SendMessageW(this->m_hWnd, WM_SETICON, ICON_BIG, (LPARAM)this->m_hNSudoIcon);

        this->m_hWarningIcon = (HICON)LoadImageW(
            nullptr,
            IDI_WARNING,
            IMAGE_ICON,
            0,
            0,
            LR_SHARED);

        const char* UserNameID[] = { "TI" ,"System" ,"CurrentProcess" ,"CurrentUser" };
        for (size_t i = 0; i < sizeof(UserNameID) / sizeof(*UserNameID); ++i)
        {
            std::wstring Buffer = g_ResourceManagement.GetTranslation(UserNameID[i]);
            SendMessageW(this->m_hUserName, CB_INSERTSTRING, 0, (LPARAM)Buffer.c_str());
        }

        //设置默认项"TrustedInstaller"
        SendMessageW(this->m_hUserName, CB_SETCURSEL, 3, 0);

        for (std::pair<std::wstring, std::wstring> Item
            : g_ResourceManagement.ShortCutList)
        {
            SendMessageW(
                this->m_hszPath,
                CB_INSERTSTRING,
                0,
                (LPARAM)Item.first.c_str());
        }

        return TRUE;
    }

    POINT GetPhysicalPoint(const POINT& LogicalPoint)
    {
        POINT PhysicalPoint;

        PhysicalPoint.x = MulDiv(
            LogicalPoint.x, this->m_xDPI, USER_DEFAULT_SCREEN_DPI);
        PhysicalPoint.y = MulDiv(
            LogicalPoint.y, this->m_yDPI, USER_DEFAULT_SCREEN_DPI);

        return PhysicalPoint;
    }

    SIZE GetPhysicalSize(const SIZE& LogicalSize)
    {
        SIZE PhysicalSize;

        PhysicalSize.cx = MulDiv(
            LogicalSize.cx, this->m_xDPI, USER_DEFAULT_SCREEN_DPI);
        PhysicalSize.cy = MulDiv(
            LogicalSize.cy, this->m_yDPI, USER_DEFAULT_SCREEN_DPI);

        return PhysicalSize;
    }

    BOOL DrawIconWithHighDPISupport(
        _In_ HDC hdc,
        _In_ const POINT& LogicalPoint,
        _In_ HICON hIcon,
        const SIZE& LogicalSize,
        _In_ UINT istepIfAniCur,
        _In_opt_ HBRUSH hbrFlickerFreeDraw,
        _In_ UINT diFlags)
    {
        POINT PhysicalPoint = GetPhysicalPoint(LogicalPoint);
        SIZE PhysicalSize = GetPhysicalSize(LogicalSize);

        return DrawIconEx(
            hdc,
            PhysicalPoint.x,
            PhysicalPoint.y,
            hIcon,
            PhysicalSize.cx,
            PhysicalSize.cy,
            istepIfAniCur,
            hbrFlickerFreeDraw,
            diFlags);
    }

    BOOL GetLogicalClientRect(
        _Out_ RECT& LogicalRect)
    {
        BOOL result = GetClientRect(&LogicalRect);

        LogicalRect.left = MulDiv(
            LogicalRect.left, USER_DEFAULT_SCREEN_DPI, this->m_xDPI);
        LogicalRect.top = MulDiv(
            LogicalRect.top, USER_DEFAULT_SCREEN_DPI, this->m_yDPI);
        LogicalRect.right = MulDiv(
            LogicalRect.right, USER_DEFAULT_SCREEN_DPI, this->m_xDPI);
        LogicalRect.bottom = MulDiv(
            LogicalRect.bottom, USER_DEFAULT_SCREEN_DPI, this->m_yDPI);

        return result;
    }

    LRESULT OnPaint(
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam,
        BOOL& bHandled)
    {
        UNREFERENCED_PARAMETER(uMsg);
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        UNREFERENCED_PARAMETER(bHandled);

        PAINTSTRUCT ps;
        HDC hdc = this->BeginPaint(&ps);

        RECT rect = { 0 };
        this->GetLogicalClientRect(rect);

        DrawIconWithHighDPISupport(
            hdc,
            {16, 16},
            this->m_hNSudoIcon,
            {64, 64},
            0,
            nullptr,
            DI_NORMAL | DI_COMPAT);
        DrawIconWithHighDPISupport(
            hdc,
            {16, (rect.bottom - rect.top) - 40 },
            this->m_hWarningIcon,
            {24, 24},
            0,
            nullptr,
            DI_NORMAL | DI_COMPAT);

        this->EndPaint(&ps);

        return 0;
    }

    LRESULT OnDPIChanged(
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam,
        BOOL& bHandled)
    {
        UNREFERENCED_PARAMETER(uMsg);
        UNREFERENCED_PARAMETER(lParam);
        UNREFERENCED_PARAMETER(bHandled);

        this->m_xDPI = LOWORD(wParam);
        this->m_yDPI = HIWORD(wParam);

        return 0;
    }

    LRESULT OnRun(
        WORD wNotifyCode,
        WORD wID,
        HWND hWndCtl,
        BOOL& bHandled)
    {
        UNREFERENCED_PARAMETER(wNotifyCode);
        UNREFERENCED_PARAMETER(wID);
        UNREFERENCED_PARAMETER(hWndCtl);
        UNREFERENCED_PARAMETER(bHandled);

        std::wstring UserName(MAX_PATH, L'\0');
        auto UserNameLength = this->m_hUserName.GetWindowTextW(
            &UserName[0],
            static_cast<int>(UserName.size()));
        UserName.resize(UserNameLength);

        bool NeedToEnableAllPrivileges = false;
        if (BST_CHECKED == SendMessageW(this->m_hCheckBox, BM_GETCHECK, 0, 0))
        {
            NeedToEnableAllPrivileges = true;
        }

        std::wstring RawCommandLine(MAX_PATH, L'\0');
        auto RawCommandLineLength = this->m_hszPath.GetWindowTextW(
            &RawCommandLine[0],
            static_cast<int>(RawCommandLine.size()));
        RawCommandLine.resize(RawCommandLineLength);

        if (_wcsicmp(L"", RawCommandLine.c_str()) == 0)
        {
            std::wstring Buffer = g_ResourceManagement.GetMessageString(
                NSUDO_MESSAGE::INVALID_TEXTBOX_PARAMETER);
            NSudoPrintMsg(
                g_ResourceManagement.Instance,
                this->m_hWnd,
                Buffer.c_str());
        }
        else
        {
            std::wstring CommandLine = L"NSudo -ShowWindowMode=Hide";

            // 获取用户令牌
            if (0 == _wcsicmp(
                g_ResourceManagement.GetTranslation("TI").c_str(),
                UserName.c_str()))
            {
                CommandLine += L" -U:T";
            }
            else if (0 == _wcsicmp(
                g_ResourceManagement.GetTranslation("System").c_str(),
                UserName.c_str()))
            {
                CommandLine += L" -U:S";
            }
            else if (0 == _wcsicmp(
                g_ResourceManagement.GetTranslation("CurrentProcess").c_str(),
                UserName.c_str()))
            {
                CommandLine += L" -U:P";
            }
            else if (0 == _wcsicmp(
                g_ResourceManagement.GetTranslation("CurrentUser").c_str(),
                UserName.c_str()))
            {
                CommandLine += L" -U:C";
            }

            // 如果勾选启用全部特权，则尝试对令牌启用全部特权
            if (NeedToEnableAllPrivileges)
            {
                CommandLine += L" -P:E";
            }

            CommandLine += L" ";
            CommandLine += RawCommandLine;

            std::wstring ApplicationName;
            std::map<std::wstring, std::wstring> OptionsAndParameters;
            std::wstring UnresolvedCommandLine;

            M2SpiltCommandLineEx(
                CommandLine,
                std::vector<std::wstring>{ L"-", L"/", L"--" },
                std::vector<std::wstring>{ L"=", L":" },
                ApplicationName,
                OptionsAndParameters,
                UnresolvedCommandLine);

            UnresolvedCommandLine =
                L"cmd /c start \"NSudo.Launcher\" " +
                CNSudoShortCutAdapter::Translate(
                    g_ResourceManagement.ShortCutList,
                    UnresolvedCommandLine);

            NSUDO_MESSAGE message = NSudoCommandLineParser(
                true,
                true,
                ApplicationName,
                OptionsAndParameters,
                UnresolvedCommandLine);
            if (NSUDO_MESSAGE::SUCCESS != message)
            {
                std::wstring Buffer = g_ResourceManagement.GetMessageString(
                    message);
                NSudoPrintMsg(
                    g_ResourceManagement.Instance,
                    this->m_hWnd,
                    Buffer.c_str());
            }
        }

        return 0;
    }

    LRESULT OnAbout(
        WORD wNotifyCode,
        WORD wID,
        HWND hWndCtl,
        BOOL& bHandled)
    {
        UNREFERENCED_PARAMETER(wNotifyCode);
        UNREFERENCED_PARAMETER(wID);
        UNREFERENCED_PARAMETER(hWndCtl);
        UNREFERENCED_PARAMETER(bHandled);

        NSudoShowAboutDialog(this->m_hWnd);

        return 0;
    }

    LRESULT OnBrowse(
        WORD wNotifyCode,
        WORD wID,
        HWND hWndCtl,
        BOOL& bHandled)
    {
        UNREFERENCED_PARAMETER(wNotifyCode);
        UNREFERENCED_PARAMETER(wID);
        UNREFERENCED_PARAMETER(hWndCtl);
        UNREFERENCED_PARAMETER(bHandled);

        std::wstring buffer(MAX_PATH + 2, L'\0');

        buffer[0] = L'\"';

        OPENFILENAME ofn = { 0 };

        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = this->m_hWnd;
        ofn.nMaxFile = MAX_PATH;
        ofn.nMaxFileTitle = MAX_PATH;
        ofn.lpstrFile = &buffer[1];
        ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

        GetOpenFileNameW(&ofn);

        buffer.resize(wcslen(buffer.c_str()));

        buffer[buffer.size()] = L'\"';

        if (wcslen(buffer.c_str()) > 2)
            this->m_hszPath.SetWindowTextW(buffer.c_str());

        return 0;
    }

    LRESULT OnDropFiles(
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam,
        BOOL& bHandled)
    {
        UNREFERENCED_PARAMETER(uMsg);
        UNREFERENCED_PARAMETER(lParam);
        UNREFERENCED_PARAMETER(bHandled);

        std::wstring buffer(MAX_PATH + 2, L'\0');

        buffer[0] = L'\"';

        UINT length = DragQueryFileW(
            (HDROP)wParam, 0, &buffer[1], (int)(buffer.size() - 2));
        buffer.resize(static_cast<size_t>(length) + 1);

        if (!(GetFileAttributesW(&buffer[1]) & FILE_ATTRIBUTE_DIRECTORY))
        {
            buffer[buffer.size()] = L'\"';
            this->m_hszPath.SetWindowTextW(buffer.c_str());
        }

        DragFinish((HDROP)wParam);

        return 0;
    }
};

#endif

int NSudoMain()
{
    //SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));

    //SetThreadUILanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL));

    //SetThreadUILanguage(1033);

    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    g_ResourceManagement.Initialize();

    std::wstring ApplicationName;
    std::map<std::wstring, std::wstring> OptionsAndParameters;
    std::wstring UnresolvedCommandLine;

    M2SpiltCommandLineEx(
        std::wstring(GetCommandLineW()),
        std::vector<std::wstring>{ L"-", L"/", L"--" },
        std::vector<std::wstring>{ L"=", L":" },
        ApplicationName,
        OptionsAndParameters,
        UnresolvedCommandLine);

    UnresolvedCommandLine = CNSudoShortCutAdapter::Translate(
        g_ResourceManagement.ShortCutList,
        UnresolvedCommandLine);

    if (OptionsAndParameters.empty() && UnresolvedCommandLine.empty())
    {
#if defined(NSUDO_CUI_CONSOLE)
        NSudoShowAboutDialog(nullptr);
#elif defined(NSUDO_GUI_WINDOWS)
        CNSudoMainWindow MainWindow;
        MainWindow.DoModal(nullptr);
#endif
        return 0;
    }

#if defined(NSUDO_CUI_CONSOLE)
    NSUDO_MESSAGE message = NSudoCommandLineParser(
        g_ResourceManagement.IsElevated,
        false,
        ApplicationName,
        OptionsAndParameters,
        UnresolvedCommandLine);
#elif defined(NSUDO_GUI_WINDOWS)
    NSUDO_MESSAGE message = NSudoCommandLineParser(
        g_ResourceManagement.IsElevated,
        true,
        ApplicationName,
        OptionsAndParameters,
        UnresolvedCommandLine);
#endif

    if (NSUDO_MESSAGE::NEED_TO_SHOW_COMMAND_LINE_HELP == message)
    {
        NSudoShowAboutDialog(nullptr);
    }
    else if (NSUDO_MESSAGE::NEED_TO_SHOW_NSUDO_VERSION == message)
    {
        NSudoPrintMsg(
            g_ResourceManagement.Instance,
            nullptr,
            g_ResourceManagement.GetTranslation("NSudo.VersionText").c_str());
    }
    else if (NSUDO_MESSAGE::SUCCESS != message)
    {
        std::wstring Buffer = g_ResourceManagement.GetMessageString(
            message);
        NSudoPrintMsg(
            g_ResourceManagement.Instance,
            nullptr,
            Buffer.c_str());
        return -1;
    }

    return 0;
}


#if defined(NSUDO_CUI_CONSOLE)
int main()
#elif defined(NSUDO_GUI_WINDOWS)
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
#endif
{
#if defined(NSUDO_GUI_WINDOWS)
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);
#endif

    return NSudoMain();
}
