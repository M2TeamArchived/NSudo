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

#include "NSudoAPI.h"

#include "M2WindowsHelpers.h"
#include "M2Win32GUIHelpers.h"

#include <commctrl.h>
#include <Userenv.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Userenv.lib")

#include <cstdio>
#include <cwchar>
#include <fstream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

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

/**
 * The resource info struct.
 */
typedef struct _M2_RESOURCE_INFO
{
    DWORD Size;
    LPVOID Pointer;
} M2_RESOURCE_INFO, * PM2_RESOURCE_INFO;

/**
 * Obtain the best matching resource with the specified type and name in the
 * specified module.
 *
 * @param lpResourceInfo The resource info which contains the pointer and size.
 * @param hModule A handle to the module whose portable executable file or an
 *                accompanying MUI file contains the resource. If this
 *                parameter is NULL, the function searches the module used to
 *                create the current process.
 * @param lpType The resource type. Alternately, rather than a pointer, this
 *               parameter can be MAKEINTRESOURCE(ID), where ID is the integer
 *               identifier of the given resource type.
 * @param lpName The name of the resource. Alternately, rather than a pointer,
 *               this parameter can be MAKEINTRESOURCE(ID), where ID is the
 *               integer identifier of the resource.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2LoadResource(
    _Out_ PM2_RESOURCE_INFO lpResourceInfo,
    _In_opt_ HMODULE hModule,
    _In_ LPCWSTR lpType,
    _In_ LPCWSTR lpName)
{
    if (!lpResourceInfo)
        return E_INVALIDARG;

    lpResourceInfo->Size = 0;
    lpResourceInfo->Pointer = nullptr;

    HRSRC ResourceFind = FindResourceExW(
        hModule, lpType, lpName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    if (!ResourceFind)
        return ::HRESULT_FROM_WIN32(::GetLastError());

    lpResourceInfo->Size = SizeofResource(hModule, ResourceFind);

    HGLOBAL ResourceLoad = LoadResource(hModule, ResourceFind);
    if (!ResourceLoad)
        return ::HRESULT_FROM_WIN32(::GetLastError());

    lpResourceInfo->Pointer = LockResource(ResourceLoad);

    return S_OK;
}

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

#include "jsmn.h"

bool JsmnParseJson(
    _Out_ jsmntok_t** JsonTokens,
    _Out_ std::int32_t* JsonTokensCount,
    _In_ const char* JsonString,
    _In_ std::size_t JsonStringLength)
{
    if (!(JsonTokens && JsonTokensCount && JsonString && JsonStringLength))
    {
        return false;
    }

    *JsonTokens = nullptr;
    *JsonTokensCount = 0;

    jsmn_parser Parser;

    ::jsmn_init(&Parser);
    std::int32_t TokenCount = ::jsmn_parse(
        &Parser, JsonString, JsonStringLength, nullptr, 0);

    jsmntok_t* Tokens = reinterpret_cast<jsmntok_t*>(::malloc(
        TokenCount * sizeof(jsmntok_t)));
    if (Tokens)
    {
        ::jsmn_init(&Parser);
        std::int32_t TokensCount = ::jsmn_parse(
            &Parser, JsonString, JsonStringLength, Tokens, TokenCount);
        if (TokensCount > 0)
        {
            *JsonTokens = Tokens;
            *JsonTokensCount = TokensCount;
        }
        else
        {
            ::free(Tokens);
        }
    }

    return Tokens;
}

typedef struct _JSON_TOKEN_INFO
{
    jsmntype_t Type;
    const char* Name;
    std::size_t NameLength;
    int Size;
} JSON_TOKEN_INFO, *PJSON_TOKEN_INFO;

void JsmnGetTokenInfo(
    _Out_ PJSON_TOKEN_INFO JsonTokenInfo,
    _In_ const char* JsonString,
    _In_ jsmntok_t* JsonToken)
{
    JsonTokenInfo->Type = JsonToken->type;
    JsonTokenInfo->Name = JsonString + JsonToken->start;
    JsonTokenInfo->NameLength = JsonToken->end - JsonToken->start;
    JsonTokenInfo->Size = JsonToken->size;
}

bool JsmnJsonEqual(
    _In_ const char* JsonString,
    _In_ jsmntok_t* JsonToken,
    _In_ const char* String)
{
    if (JsonToken->type == JSMN_STRING)
    {
        const char* CurrentToken = JsonString + JsonToken->start;
        std::size_t CurrentTokenLength = JsonToken->end - JsonToken->start;
        if (::strlen(String) == CurrentTokenLength)
        {
            if (::strncmp(CurrentToken, String, CurrentTokenLength) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

/*void x()
{
    JobObjectCreateSilo;
    JobObjectExtendedLimitInformation;
    JobObjectCpuRateControlInformation;
    JobObjectReserved23Information; // JobObjectSiloSystemRoot
    JobObjectReserved25Information; // JobObjectThreadImpersonationInformation
    JobObjectReserved13Information; // JobObjectContainerId
    JobObjectReserved15Information; // JobObjectSiloRootDirectory
    JobObjectReserved16Information; // JobObjectServerSiloBasicInformation
    JobObjectReserved17Information; // JobObjectServerSiloUserSharedData
    JobObjectReserved18Information; // JobObjectServerSiloInitialize
}*/

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
            const char* JsonString =
                reinterpret_cast<const char*>(ResourceInfo.Pointer) + 3;
            std::size_t JsonStringLength =
                ResourceInfo.Size - 3;

            jsmntok_t* JsonTokens = nullptr;
            std::int32_t JsonTokensCount = 0;
            if (JsmnParseJson(
                &JsonTokens,
                &JsonTokensCount,
                JsonString,
                JsonStringLength))
            {
                for (size_t i = 0; i < static_cast<size_t>(JsonTokensCount); ++i)
                {
                    if (JsmnJsonEqual(
                        JsonString,
                        &JsonTokens[i],
                        "Translations"))
                    {
                        if (JsonTokens[i + 1].type != JSMN_OBJECT)
                        {
                            continue;
                        }

                        for (size_t j = 0; j < static_cast<size_t>(JsonTokens[i + 1].size); ++j)
                        {
                            jsmntok_t& Key = JsonTokens[i + (j * 2) + 2];
                            jsmntok_t& Value = JsonTokens[i + (j * 2) + 3];

                            if (Key.type != JSMN_STRING ||
                                Value.type != JSMN_STRING)
                            {
                                continue;
                            }

                            StringTranslations.emplace(std::make_pair(
                                std::string(
                                    JsonString + Key.start,
                                    Key.end - Key.start),
                                M2MakeUTF16String(std::string(
                                    JsonString + Value.start,
                                    Value.end - Value.start))));
                        }
                        i += JsonTokens[i + 1].size + 1;
                    }
                }

                ::free(JsonTokens);
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

        HANDLE FileHandle = ::CreateFileW(
            ShortCutListPath.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_SEQUENTIAL_SCAN,
            nullptr);
        if (FileHandle != INVALID_HANDLE_VALUE)
        {
            DWORD FileSize = ::GetFileSize(FileHandle, nullptr);

            HANDLE FileMapping = CreateFileMappingW(
                FileHandle, nullptr, PAGE_WRITECOPY, 0, 0, nullptr);
            if (FileMapping)
            {
                const char* MapAddress = reinterpret_cast<const char*>(
                    MapViewOfFile(FileMapping, FILE_MAP_COPY, 0, 0, FileSize));
                if (MapAddress)
                {
                    const char* JsonString = MapAddress + 3;
                    std::size_t JsonStringLength = FileSize - 3;

                    jsmntok_t* JsonTokens = nullptr;
                    std::int32_t JsonTokensCount = 0;
                    if (JsmnParseJson(
                        &JsonTokens,
                        &JsonTokensCount,
                        JsonString,
                        JsonStringLength))
                    {
                        for (size_t i = 0; i < static_cast<size_t>(JsonTokensCount); ++i)
                        {
                            if (JsmnJsonEqual(
                                JsonString,
                                &JsonTokens[i],
                                "ShortCutList_V2"))
                            {
                                if (JsonTokens[i + 1].type != JSMN_OBJECT)
                                {
                                    continue;
                                }

                                for (size_t j = 0; j < static_cast<size_t>(JsonTokens[i + 1].size); ++j)
                                {
                                    jsmntok_t& Key = JsonTokens[i + (j * 2) + 2];
                                    jsmntok_t& Value = JsonTokens[i + (j * 2) + 3];

                                    if (Key.type != JSMN_STRING ||
                                        Value.type != JSMN_STRING)
                                    {
                                        continue;
                                    }

                                    ShortCutList.emplace(std::make_pair(
                                        M2MakeUTF16String(std::string(
                                            JsonString + Key.start,
                                            Key.end - Key.start)),
                                        M2MakeUTF16String(std::string(
                                            JsonString + Value.start,
                                            Value.end - Value.start))));
                                }
                                i += JsonTokens[i + 1].size + 1;
                            }
                        }

                        ::free(JsonTokens);
                    }

                    ::UnmapViewOfFile(MapAddress);
                }

                ::CloseHandle(FileMapping);
            }

            ::CloseHandle(FileHandle);
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

public:
    const HINSTANCE& Instance = this->m_Instance;
    const std::wstring& ExePath = this->m_ExePath;
    const std::wstring& AppPath = this->m_AppPath;

    const std::map<std::wstring, std::wstring>& ShortCutList =
        this->m_ShortCutList;

    INSudoMemoryManager* pNSudoMemoryManager = nullptr;
    INSudoClient* pNSudoClient = nullptr;

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
            ::NSudoInitialize();

            this->m_Instance = GetModuleHandleW(nullptr);

            this->m_ExePath = M2GetCurrentProcessModulePath();

            this->m_AppPath = this->m_ExePath;
            wcsrchr(&this->m_AppPath[0], L'\\')[0] = L'\0';
            this->m_AppPath.resize(wcslen(this->m_AppPath.c_str()));

            CNSudoTranslationAdapter::Load(this->m_StringTranslations);

            CNSudoShortCutAdapter::Read(
                this->AppPath + L"\\NSudo.json", this->m_ShortCutList);

            HRESULT hr = S_OK;

            hr = ::NSudoCreateInstance(
                IID_INSudoMemoryManager,
                reinterpret_cast<PVOID*>(&this->pNSudoMemoryManager));
            if (S_OK != hr)
            {
                ::ExitProcess(hr);
            }

            hr = ::NSudoCreateInstance(
                IID_INSudoClient,
                reinterpret_cast<PVOID*>(&this->pNSudoClient));
            if (S_OK != hr)
            {
                ::ExitProcess(hr);
            }

            this->m_IsInitialized = true;
        }
    }

    void UnInitialize()
    {
        if (this->pNSudoClient)
        {
            this->pNSudoClient->Release();
        }

        ::NSudoUninitialize();
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

/**
 * Enables or disables privileges in the specified access token.
 *
 * @param TokenHandle A handle to the access token that contains the
 *                    privileges to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token.
 * @param Privileges A key value map of privilege name and attributes.
 *                   The attributes of a privilege can be a combination
 *                   of the following values.
 *                   SE_PRIVILEGE_ENABLED
 *                       The function enables the privilege.
 *                   SE_PRIVILEGE_REMOVED
 *                       The privilege is removed from the list of
 *                       privileges in the token.
 *                   None
 *                       The function disables the privilege.
 * @return Standard Win32 Error. If the function succeeds, the return
 *         value is ERROR_SUCCESS.
 * @remark For more information, see AdjustTokenPrivileges.
 */
HRESULT NSudoAdjustTokenPrivileges(
    HANDLE TokenHandle,
    std::map<std::wstring, DWORD> const& Privileges)
{
    std::vector<LUID_AND_ATTRIBUTES> RawPrivileges;

    for (auto const& Privilege : Privileges)
    {
        LUID_AND_ATTRIBUTES RawPrivilege;

        HRESULT hr = g_ResourceManagement.pNSudoClient->GetPrivilegeValue(
            Privilege.first.c_str(), &RawPrivilege.Luid);
        if (hr != S_OK)
        {
            return hr;
        }

        RawPrivilege.Attributes = Privilege.second;

        RawPrivileges.push_back(RawPrivilege);
    }

    return g_ResourceManagement.pNSudoClient->AdjustTokenPrivileges(
        TokenHandle,
        &RawPrivileges[0],
        static_cast<DWORD>(RawPrivileges.size()));
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
    if (g_ResourceManagement.pNSudoClient->OpenCurrentProcessToken(
        MAXIMUM_ALLOWED, &hCurrentToken) == S_OK)
    {
        if (CreateEnvironmentBlock(&lpEnvironment, hToken, TRUE))
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

class ThreadTokenContext
{
public:

    HRESULT hr;

    ThreadTokenContext(HANDLE TokenHandle) :
        hr(g_ResourceManagement.pNSudoClient->SetCurrentThreadToken(TokenHandle))
    {
    }

    ~ThreadTokenContext()
    {
        g_ResourceManagement.pNSudoClient->SetCurrentThreadToken(nullptr);
    }

};

// 解析命令行
NSUDO_MESSAGE NSudoCommandLineParser(
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
            return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
        }
    }

    HRESULT hr = S_OK;

    M2::CHandle DuplicatedToken;
    if (hr == S_OK)
    {
        M2::CHandle  CurrentProcessToken;
        hr = g_ResourceManagement.pNSudoClient->OpenCurrentProcessToken(
            MAXIMUM_ALLOWED, &CurrentProcessToken);
        if (hr == S_OK)
        {
            hr = g_ResourceManagement.pNSudoClient->DuplicateToken(
                CurrentProcessToken,
                MAXIMUM_ALLOWED,
                nullptr,
                SecurityImpersonation,
                TokenImpersonation,
                &DuplicatedToken);
            if (hr == S_OK)
            {
                std::map<std::wstring, DWORD> Privileges;

                Privileges.insert(std::pair(
                    SE_DEBUG_NAME, SE_PRIVILEGE_ENABLED));

                hr = NSudoAdjustTokenPrivileges(
                    DuplicatedToken, Privileges);
            }
        }
    }

    ThreadTokenContext CurrentThreadTokenContext(DuplicatedToken);

    // 如果未获取 SeDebugPrivilege 权限，大概率不是管理员权限
    if (!(hr == S_OK && CurrentThreadTokenContext.hr == S_OK))
    {
        return NSUDO_MESSAGE::PRIVILEGE_NOT_HELD;
    }

    DWORD dwSessionID = static_cast<DWORD>(-1);

    M2::CHandle CurrentThreadToken;
    hr = g_ResourceManagement.pNSudoClient->OpenCurrentThreadToken(
        MAXIMUM_ALLOWED, FALSE, &CurrentThreadToken);
    if (hr == S_OK)
    {
        DWORD ReturnLength = 0;
        hr = g_ResourceManagement.pNSudoClient->GetTokenInformation(
            CurrentThreadToken,
            TokenSessionId,
            &dwSessionID,
            sizeof(DWORD),
            &ReturnLength);
    }

    // 获取当前会话 ID 失败
    if (hr != S_OK)
    {
        return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
    }

    M2::CHandle SystemToken;

    {
        M2::CHandle OriginalToken;

        hr = g_ResourceManagement.pNSudoClient->OpenLsassProcessToken(
            MAXIMUM_ALLOWED, &OriginalToken);
        if (hr == S_OK)
        {
            hr = g_ResourceManagement.pNSudoClient->DuplicateToken(
                OriginalToken,
                MAXIMUM_ALLOWED,
                nullptr,
                SecurityImpersonation,
                TokenImpersonation,
                &SystemToken);
            if (hr == S_OK)
            {
                hr = g_ResourceManagement.pNSudoClient->AdjustTokenAllPrivileges(
                    SystemToken, SE_PRIVILEGE_ENABLED);
            }
        }
    }

    ThreadTokenContext SystemTokenContext(SystemToken);

    // 如果模拟System权限失败
    if (!(hr == S_OK && SystemTokenContext.hr == S_OK))
    {
        return NSUDO_MESSAGE::PRIVILEGE_NOT_HELD;
    }





    //HANDLE UserToken = INVALID_HANDLE_VALUE;
    //if (::LogonUserExW(
    //    L"YoloUser",
    //    L".",
    //    L"123456",
    //    LOGON32_LOGON_INTERACTIVE,
    //    LOGON32_PROVIDER_DEFAULT,
    //    &UserToken,
    //    nullptr,
    //    nullptr,
    //    nullptr,
    //    nullptr))
    //{
    //    //BOOL re = ImpersonateLoggedOnUser(UserToken);
    //    //re = re;

    //    DWORD ReturnLength = 0;
    //    TOKEN_LINKED_TOKEN LinkedToken = { 0 };
    //    hr = g_ResourceManagement.pNSudoClient->GetTokenInformation(UserToken, TokenLinkedToken, &LinkedToken, sizeof(LinkedToken), &ReturnLength);

    //    

    //    PROFILEINFOW ProfileInfo = { 0 };
    //    ProfileInfo.dwSize = sizeof(PROFILEINFOW);
    //    ProfileInfo.lpUserName = L"YoloUser";

    //    if (::LoadUserProfileW(LinkedToken.LinkedToken, &ProfileInfo))
    //    {

    //        //hr = g_ResourceManagement.pNSudoClient->GetTokenInformation(UserToken, TokenLogonSid);

    //        //wchar_t NameBuffer[260];
    //        //DWORD LengthNeeded = 0;
    //        //::GetUserObjectInformationW(
    //        //    //::GetProcessWindowStation(),
    //        //    ::GetThreadDesktop(::GetCurrentThreadId()),
    //        //    UOI_NAME,
    //        //    NameBuffer,
    //        //    sizeof(NameBuffer),
    //        //    &LengthNeeded);

    //        /*DWORD ReturnLength = 0;
    //        hr = g_ResourceManagement.pNSudoClient->GetTokenInformation(
    //            UserToken,
    //            TokenSessionId,
    //            &dwSessionID,
    //            sizeof(DWORD),
    //            &ReturnLength);*/

    //        //::ImpersonateLoggedOnUser(UserToken);
    //        NSudoCreateProcess(
    //            LinkedToken.LinkedToken,
    //            L"E:\\source\\repos\\GUIDemoForLegacyWindows\\Release\\GUIDemoForLegacyWindows.exe",
    //            nullptr,
    //            INFINITE);

    //        HRESULT hr2 = ::GetLastError();
    //        hr2 = hr2;

    //        ::UnloadUserProfile(LinkedToken.LinkedToken, ProfileInfo.hProfile);
    //    }

    //    ::CloseHandle(UserToken);
    //}


    // 0xc0000142

    
    




    bool bArgErr = false;

    M2::CHandle hToken;

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

    NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType =
        NSUDO_MANDATORY_LABEL_TYPE::UNTRUSTED;

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
                MandatoryLabelType = NSUDO_MANDATORY_LABEL_TYPE::SYSTEM;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"H"))
            {
                MandatoryLabelType = NSUDO_MANDATORY_LABEL_TYPE::HIGH;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"M"))
            {
                MandatoryLabelType = NSUDO_MANDATORY_LABEL_TYPE::MEDIUM;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"L"))
            {
                MandatoryLabelType = NSUDO_MANDATORY_LABEL_TYPE::LOW;
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
        if (S_OK != g_ResourceManagement.pNSudoClient->OpenServiceProcessToken(
            L"TrustedInstaller", MAXIMUM_ALLOWED, &OriginalToken))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionUserValue::System == UserMode)
    {
        if (S_OK != g_ResourceManagement.pNSudoClient->OpenLsassProcessToken(
            MAXIMUM_ALLOWED, &OriginalToken))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionUserValue::CurrentUser == UserMode)
    {
        if (S_OK != g_ResourceManagement.pNSudoClient->CreateSessionToken(
            dwSessionID, &OriginalToken))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionUserValue::CurrentProcess == UserMode)
    {
        if (S_OK != g_ResourceManagement.pNSudoClient->OpenCurrentProcessToken(
            MAXIMUM_ALLOWED, &OriginalToken))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionUserValue::CurrentProcessDropRight == UserMode)
    {
        HANDLE CurrentProcessToken = nullptr;
        hr = g_ResourceManagement.pNSudoClient->OpenCurrentProcessToken(
            MAXIMUM_ALLOWED, &CurrentProcessToken);
        if (hr == S_OK)
        {
            hr = g_ResourceManagement.pNSudoClient->CreateLUAToken(
                CurrentProcessToken, &OriginalToken);

            ::CloseHandle(CurrentProcessToken);
        }

        if (S_OK != hr)
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }

    if (S_OK != g_ResourceManagement.pNSudoClient->DuplicateToken(
        OriginalToken,
        MAXIMUM_ALLOWED,
        nullptr,
        SecurityIdentification,
        TokenPrimary,
        &hToken))
    {
        return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
    }

    if (S_OK != g_ResourceManagement.pNSudoClient->SetTokenInformation(
        hToken,
        TokenSessionId,
        (PVOID)&dwSessionID,
        sizeof(DWORD)))
    {
        return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
    }

    if (NSudoOptionPrivilegesValue::EnableAllPrivileges == PrivilegesMode)
    {
        if (S_OK != g_ResourceManagement.pNSudoClient->AdjustTokenAllPrivileges(
            hToken, SE_PRIVILEGE_ENABLED))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }
    else if (NSudoOptionPrivilegesValue::DisableAllPrivileges == PrivilegesMode)
    {
        if (S_OK != g_ResourceManagement.pNSudoClient->AdjustTokenAllPrivileges(
            hToken, 0))
        {
            return NSUDO_MESSAGE::CREATE_PROCESS_FAILED;
        }
    }

    if (MandatoryLabelType != NSUDO_MANDATORY_LABEL_TYPE::UNTRUSTED)
    {
        if (S_OK != g_ResourceManagement.pNSudoClient->SetTokenMandatoryLabel(
            hToken, MandatoryLabelType))
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
            { 16, 16 },
            this->m_hNSudoIcon,
            { 64, 64 },
            0,
            nullptr,
            DI_NORMAL | DI_COMPAT);
        DrawIconWithHighDPISupport(
            hdc,
            { 16, (rect.bottom - rect.top) - 40 },
            this->m_hWarningIcon,
            { 24, 24 },
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

    NSUDO_MESSAGE message = NSudoCommandLineParser(
        ApplicationName,
        OptionsAndParameters,
        UnresolvedCommandLine);

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
