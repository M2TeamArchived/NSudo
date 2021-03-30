/*
 * PROJECT:   NSudo Launcher
 * FILE:      NSudoLauncherGUI.cpp
 * PURPOSE:   Implementation for NSudo Launcher GUI
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
#include <Mile.Windows.h>

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

#define _ATL_NO_AUTOMATIC_NAMESPACE
#include <atlbase.h>
#include <atlwin.h>

#define _WTL_NO_AUTOMATIC_NAMESPACE
#define _ATL_NO_OPENGL
#include "WTL/atlapp.h"
#include "WTL/atlcrack.h"
#include "WTL/atlctrls.h"
#include "WTL/atlframe.h"
#include "WTL/atlmisc.h"

#include "Mile.Project.Properties.h"
#include "NSudoLauncherGUIResource.h"

#include <NSudoLauncherResources.h>

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
} JSON_TOKEN_INFO, * PJSON_TOKEN_INFO;

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
            return Mile::ToUtf16String(std::string(
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
            L"M2-Team NSudo Launcher " MILE_PROJECT_VERSION_STRING));

        StringTranslations.emplace(std::make_pair(
            "NSudo.LogoText",
            L"M2-Team NSudo Launcher " MILE_PROJECT_VERSION_STRING L"\r\n"
            L"© M2-Team. All rights reserved.\r\n"
            L"\r\n"));

        StringTranslations.emplace(std::make_pair(
            "NSudo.String.Links",
            CNSudoTranslationAdapter::GetUTF8WithBOMStringResources(
                IDR_STRING_LINKS)));

        StringTranslations.emplace(std::make_pair(
            "NSudo.String.CommandLineHelp",
            CNSudoTranslationAdapter::GetUTF8WithBOMStringResources(
                IDR_STRING_COMMAND_LINE_HELP)));

        M2_RESOURCE_INFO ResourceInfo = { 0 };
        if (SUCCEEDED(M2LoadResource(
            &ResourceInfo,
            GetModuleHandleW(nullptr),
            L"String",
            MAKEINTRESOURCEW(IDR_STRING_TRANSLATIONS))))
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
                                Mile::ToUtf16String(std::string(
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

        HRESULT hr = S_OK;
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
            UINT64 FileSize = 0;

            hr = Mile::GetFileSize(FileHandle, &FileSize);
            if (hr == S_OK)
            {
                char* FileContent = reinterpret_cast<char*>(
                    Mile::HeapMemory::Allocate(static_cast<SIZE_T>(FileSize)));
                if (FileContent)
                {
                    DWORD NumberOfBytesRead = 0;
                    hr = Mile::ReadFile(
                        FileHandle,
                        FileContent,
                        static_cast<DWORD>(FileSize),
                        &NumberOfBytesRead);
                    if (hr == S_OK)
                    {
                        const char* JsonString = FileContent + 3;
                        std::size_t JsonStringLength = NumberOfBytesRead - 3;

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
                                            Mile::ToUtf16String(std::string(
                                                JsonString + Key.start,
                                                Key.end - Key.start)),
                                            Mile::ToUtf16String(std::string(
                                                JsonString + Value.start,
                                                Value.end - Value.start))));
                                    }
                                    i += JsonTokens[i + 1].size + 1;
                                }
                            }

                            ::free(JsonTokens);
                        }
                    }

                    Mile::HeapMemory::Free(FileContent);
                }
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

            this->m_ExePath = Mile::GetCurrentProcessModulePath();

            this->m_AppPath = this->m_ExePath;
            wcsrchr(&this->m_AppPath[0], L'\\')[0] = L'\0';
            this->m_AppPath.resize(wcslen(this->m_AppPath.c_str()));

            CNSudoTranslationAdapter::Load(this->m_StringTranslations);

            CNSudoShortCutAdapter::Read(
                this->AppPath + L"\\NSudo.json", this->m_ShortCutList);

            this->m_IsInitialized = true;
        }
    }

    void UnInitialize()
    {
        // TODO: Empty
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
            // 如果选项名是 "Version"，则显示 NSudo 版本号。
            return NSUDO_MESSAGE::NEED_TO_SHOW_NSUDO_VERSION;
        }
        else
        {
            return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
        }
    }

    bool bArgErr = false;

    // 解析参数列表

    DWORD WaitInterval = 0;
    std::wstring CurrentDirectory = g_ResourceManagement.AppPath;
    BOOL CreateNewConsole = TRUE;

    NSUDO_USER_MODE_TYPE UserModeType =
        NSUDO_USER_MODE_TYPE::DEFAULT;

    NSUDO_PRIVILEGES_MODE_TYPE PrivilegesModeType =
        NSUDO_PRIVILEGES_MODE_TYPE::DEFAULT;

    NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType =
        NSUDO_MANDATORY_LABEL_TYPE::UNTRUSTED;

    NSUDO_PROCESS_PRIORITY_CLASS_TYPE ProcessPriorityClassType =
        NSUDO_PROCESS_PRIORITY_CLASS_TYPE::NORMAL;

    NSUDO_SHOW_WINDOW_MODE_TYPE ShowWindowModeType =
        NSUDO_SHOW_WINDOW_MODE_TYPE::DEFAULT;

    for (auto& OptionAndParameter : OptionsAndParameters)
    {
        if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"U"))
        {
            if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"T"))
            {
                UserModeType = NSUDO_USER_MODE_TYPE::TRUSTED_INSTALLER;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"S"))
            {
                UserModeType = NSUDO_USER_MODE_TYPE::SYSTEM;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"C"))
            {
                UserModeType = NSUDO_USER_MODE_TYPE::CURRENT_USER;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"P"))
            {
                UserModeType = NSUDO_USER_MODE_TYPE::CURRENT_PROCESS;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"D"))
            {
                UserModeType = NSUDO_USER_MODE_TYPE::CURRENT_PROCESS_DROP_RIGHT;
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
                PrivilegesModeType = NSUDO_PRIVILEGES_MODE_TYPE::ENABLE_ALL_PRIVILEGES;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"D"))
            {
                PrivilegesModeType = NSUDO_PRIVILEGES_MODE_TYPE::DISABLE_ALL_PRIVILEGES;
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
                ProcessPriorityClassType = NSUDO_PROCESS_PRIORITY_CLASS_TYPE::IDLE;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"BelowNormal"))
            {
                ProcessPriorityClassType = NSUDO_PROCESS_PRIORITY_CLASS_TYPE::BELOW_NORMAL;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Normal"))
            {
                ProcessPriorityClassType = NSUDO_PROCESS_PRIORITY_CLASS_TYPE::NORMAL;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"AboveNormal"))
            {
                ProcessPriorityClassType = NSUDO_PROCESS_PRIORITY_CLASS_TYPE::ABOVE_NORMAL;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"High"))
            {
                ProcessPriorityClassType = NSUDO_PROCESS_PRIORITY_CLASS_TYPE::HIGH;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"RealTime"))
            {
                ProcessPriorityClassType = NSUDO_PROCESS_PRIORITY_CLASS_TYPE::REALTIME;
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
                ShowWindowModeType = NSUDO_SHOW_WINDOW_MODE_TYPE::SHOW;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Hide"))
            {
                ShowWindowModeType = NSUDO_SHOW_WINDOW_MODE_TYPE::HIDE;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Maximize"))
            {
                ShowWindowModeType = NSUDO_SHOW_WINDOW_MODE_TYPE::MAXIMIZE;
            }
            else if (0 == _wcsicmp(OptionAndParameter.second.c_str(), L"Minimize"))
            {
                ShowWindowModeType = NSUDO_SHOW_WINDOW_MODE_TYPE::MINIMIZE;
            }
            else
            {
                bArgErr = true;
                break;
            }
        }
        else if (0 == _wcsicmp(OptionAndParameter.first.c_str(), L"UseCurrentConsole"))
        {
            CreateNewConsole = FALSE;
        }
        else
        {
            bArgErr = true;
            break;
        }
    }

    if (bArgErr || UnresolvedCommandLine.empty())
    {
        return NSUDO_MESSAGE::INVALID_COMMAND_PARAMETER;
    }

    if (NSudoCreateProcess(
        UserModeType,
        PrivilegesModeType,
        MandatoryLabelType,
        ProcessPriorityClassType,
        ShowWindowModeType,
        WaitInterval,
        CreateNewConsole,
        UnresolvedCommandLine.c_str(),
        CurrentDirectory.c_str()) != S_OK)
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

    M2MessageDialog(
        hInstance,
        hWnd,
        MAKEINTRESOURCE(IDI_NSUDO_LAUNCHER),
        g_ResourceManagement.GetTranslation("NSudo.VersionText").c_str(),
        DialogContent.c_str());
}

HRESULT NSudoShowAboutDialog(
    _In_ HWND hwndParent)
{
    std::wstring DialogContent =
        g_ResourceManagement.GetTranslation("NSudo.LogoText") +
        g_ResourceManagement.GetTranslation("NSudo.String.CommandLineHelp") +
        g_ResourceManagement.GetTranslation("NSudo.String.Links");

    SetLastError(ERROR_SUCCESS);

    M2MessageDialog(
        g_ResourceManagement.Instance,
        hwndParent,
        MAKEINTRESOURCE(IDI_NSUDO_LAUNCHER),
        g_ResourceManagement.GetTranslation("NSudo.VersionText").c_str(),
        DialogContent.c_str());

    return ::HRESULT_FROM_WIN32(::GetLastError());
}

class CNSudoMainWindow : public ATL::CDialogImpl<CNSudoMainWindow>
{
public:
    enum { IDD = IDD_NSudoDlg };

public:
    BEGIN_MSG_MAP(CNSudoMainWindow)
        MSG_WM_CLOSE(OnClose)
        MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_PAINT(OnPaint)
        MSG_WM_DPICHANGED(OnDpiChanged)
        MSG_WM_DROPFILES(OnDropFiles)

        COMMAND_ID_HANDLER_EX(IDC_Run, OnRun)
        COMMAND_ID_HANDLER_EX(IDC_About, OnAbout)
        COMMAND_ID_HANDLER_EX(IDC_Browse, OnBrowse)
    END_MSG_MAP()

public:
    CNSudoMainWindow()
    {
        Mile::EnablePerMonitorDialogScaling();

        ::ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
        ::ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); // WM_COPYGLOBALDATA
    }

    ~CNSudoMainWindow()
    {

    }

private:

    WTL::CIcon NSudoIcon;
    WTL::CIcon WarningIcon;

    int m_xDPI = USER_DEFAULT_SCREEN_DPI;
    int m_yDPI = USER_DEFAULT_SCREEN_DPI;

    WTL::CComboBox UserNameComboBox;
    WTL::CButton EnableAllPrivilegesCheckBox;
    WTL::CComboBox PathComboBox;

    void OnClose()
    {
        this->EndDialog(0);
    }

    BOOL OnInitDialog(ATL::CWindow wndFocus, LPARAM lInitParam)
    {
        UNREFERENCED_PARAMETER(wndFocus);
        UNREFERENCED_PARAMETER(lInitParam);

        this->UserNameComboBox = this->GetDlgItem(IDC_UserName);
        this->EnableAllPrivilegesCheckBox = this->GetDlgItem(
            IDC_Check_EnableAllPrivileges);
        this->PathComboBox = this->GetDlgItem(IDC_szPath);

        this->SetWindowTextW(
            g_ResourceManagement.GetTranslation("NSudo.VersionText").c_str());

        struct { const char* ID; ATL::CWindow Control; } x[] =
        {
            { "EnableAllPrivileges" , this->EnableAllPrivilegesCheckBox },
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

        hr = Mile::GetDpiForMonitor(
            MonitorFromWindow(this->m_hWnd, MONITOR_DEFAULTTONEAREST),
            MDT_EFFECTIVE_DPI, (UINT*)&this->m_xDPI, (UINT*)&this->m_yDPI);
        if (hr != S_OK)
        {
            this->m_xDPI = WTL::CDC(this->GetDC()).GetDeviceCaps(LOGPIXELSX);
            this->m_yDPI = WTL::CDC(this->GetDC()).GetDeviceCaps(LOGPIXELSY);
        }

        this->NSudoIcon.LoadIconW(
            MAKEINTRESOURCE(IDI_NSUDO_LAUNCHER),
            256,
            256,
            LR_SHARED);

        this->SetIcon(this->NSudoIcon, TRUE);
        this->SetIcon(this->NSudoIcon, FALSE);

        this->WarningIcon.LoadOEMIcon(IDI_WARNING);

        const char* UserNameID[] = { "TI" ,"System" ,"CurrentProcess" ,"CurrentUser" };
        for (size_t i = 0; i < sizeof(UserNameID) / sizeof(*UserNameID); ++i)
        {
            std::wstring Buffer = g_ResourceManagement.GetTranslation(UserNameID[i]);

            this->UserNameComboBox.InsertString(0, Buffer.c_str());
        }

        //设置默认项"TrustedInstaller"
        this->UserNameComboBox.SetCurSel(3);

        for (std::pair<std::wstring, std::wstring> Item
            : g_ResourceManagement.ShortCutList)
        {
            this->PathComboBox.InsertString(0, Item.first.c_str());
        }

        return TRUE;
    }

    POINT GetPhysicalPoint(const POINT& LogicalPoint)
    {
        POINT PhysicalPoint;

        PhysicalPoint.x = ::MulDiv(
            LogicalPoint.x, this->m_xDPI, USER_DEFAULT_SCREEN_DPI);
        PhysicalPoint.y = ::MulDiv(
            LogicalPoint.y, this->m_yDPI, USER_DEFAULT_SCREEN_DPI);

        return PhysicalPoint;
    }

    SIZE GetPhysicalSize(const SIZE& LogicalSize)
    {
        SIZE PhysicalSize;

        PhysicalSize.cx = ::MulDiv(
            LogicalSize.cx, this->m_xDPI, USER_DEFAULT_SCREEN_DPI);
        PhysicalSize.cy = ::MulDiv(
            LogicalSize.cy, this->m_yDPI, USER_DEFAULT_SCREEN_DPI);

        return PhysicalSize;
    }

    BOOL GetLogicalClientRect(
        _Out_ RECT& LogicalRect)
    {
        BOOL result = this->GetClientRect(&LogicalRect);

        LogicalRect.left = ::MulDiv(
            LogicalRect.left, USER_DEFAULT_SCREEN_DPI, this->m_xDPI);
        LogicalRect.top = ::MulDiv(
            LogicalRect.top, USER_DEFAULT_SCREEN_DPI, this->m_yDPI);
        LogicalRect.right = ::MulDiv(
            LogicalRect.right, USER_DEFAULT_SCREEN_DPI, this->m_xDPI);
        LogicalRect.bottom = ::MulDiv(
            LogicalRect.bottom, USER_DEFAULT_SCREEN_DPI, this->m_yDPI);

        return result;
    }

    void OnPaint(WTL::CDCHandle dc)
    {
        UNREFERENCED_PARAMETER(dc);

        WTL::CPaintDC DC(this->m_hWnd);

        RECT rect = { 0 };
        this->GetLogicalClientRect(rect);

        DC.DrawIconEx(
            this->GetPhysicalPoint({ 16, 16 }),
            this->NSudoIcon,
            this->GetPhysicalSize({ 64, 64 }),
            0,
            nullptr,
            DI_NORMAL | DI_COMPAT);

        DC.DrawIconEx(
            this->GetPhysicalPoint({ 16, (rect.bottom - rect.top) - 40 }),
            this->WarningIcon,
            this->GetPhysicalSize({ 24, 24 }),
            0,
            nullptr,
            DI_NORMAL | DI_COMPAT);
    }

    void OnDpiChanged(UINT nDpiX, UINT nDpiY, PRECT pRect)
    {
        UNREFERENCED_PARAMETER(pRect);

        this->m_xDPI = nDpiX;
        this->m_yDPI = nDpiY;
    }

    void OnDropFiles(HDROP hDropInfo)
    {
        std::wstring buffer(MAX_PATH + 2, L'\0');

        buffer[0] = L'\"';

        UINT length = ::DragQueryFileW(
            hDropInfo, 0, &buffer[1], (int)(buffer.size() - 2));
        buffer.resize(static_cast<size_t>(length) + 1);

        if (!(::GetFileAttributesW(&buffer[1]) & FILE_ATTRIBUTE_DIRECTORY))
        {
            buffer[buffer.size()] = L'\"';
            this->PathComboBox.SetWindowTextW(buffer.c_str());
        }

        ::DragFinish(hDropInfo);
    }

    LRESULT OnRun(UINT uNotifyCode, int nID, CWindow wndCtl)
    {
        UNREFERENCED_PARAMETER(uNotifyCode);
        UNREFERENCED_PARAMETER(nID);
        UNREFERENCED_PARAMETER(wndCtl);

        std::wstring UserName(MAX_PATH, L'\0');
        auto UserNameLength = this->UserNameComboBox.GetWindowTextW(
            &UserName[0],
            static_cast<int>(UserName.size()));
        UserName.resize(UserNameLength);

        bool NeedToEnableAllPrivileges = false;

        if (BST_CHECKED == this->EnableAllPrivilegesCheckBox.GetCheck())
        {
            NeedToEnableAllPrivileges = true;
        }

        std::wstring RawCommandLine(MAX_PATH, L'\0');
        auto RawCommandLineLength = this->PathComboBox.GetWindowTextW(
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

            Mile::SpiltCommandLineEx(
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

    LRESULT OnAbout(UINT uNotifyCode, int nID, CWindow wndCtl)
    {
        UNREFERENCED_PARAMETER(uNotifyCode);
        UNREFERENCED_PARAMETER(nID);
        UNREFERENCED_PARAMETER(wndCtl);

        NSudoShowAboutDialog(this->m_hWnd);

        return 0;
    }

    LRESULT OnBrowse(UINT uNotifyCode, int nID, CWindow wndCtl)
    {
        UNREFERENCED_PARAMETER(uNotifyCode);
        UNREFERENCED_PARAMETER(nID);
        UNREFERENCED_PARAMETER(wndCtl);

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
            this->PathComboBox.SetWindowTextW(buffer.c_str());

        return 0;
    }
};

//#include <Mile.Windows.TrustedLibraryLoader.h>
//
//void comment()
//{
//    HRESULT hr = NSudoCreateProcess(
//        NSUDO_USER_MODE_TYPE::CURRENT_USER_ELEVATED,
//        NSUDO_PRIVILEGES_MODE_TYPE::DEFAULT,
//        NSUDO_MANDATORY_LABEL_TYPE::MEDIUM,
//        NSUDO_PROCESS_PRIORITY_CLASS_TYPE::NORMAL,
//        NSUDO_SHOW_WINDOW_MODE_TYPE::SHOW,
//        INFINITE,
//        TRUE,
//        LR"(C:\Windows\System32\cmd.exe)", nullptr);
//
//    hr;
//
//
//    int x = GetSystemMetrics(SM_CXPADDEDBORDER);
//    int y = GetSystemMetricsForDpi(SM_CXPADDEDBORDER, 96);
//    x; y;
//
//    ::MileLoadLibraryFromSystem32(L"srclient.dll");
//
//    HANDLE CurrentProcessToken = INVALID_HANDLE_VALUE;
//    HRESULT hr = ::MileOpenCurrentProcessToken(
//        MAXIMUM_ALLOWED, &CurrentProcessToken);
//    if (hr != S_OK)
//    {
//        return hr;
//    }
//
//    TOKEN_LINKED_TOKEN LinkedToken = { 0 };
//    DWORD ReturnLength = 0;
//
//    hr = ::MileGetTokenInformation(
//        CurrentProcessToken,
//        TokenLinkedToken,
//        &LinkedToken,
//        sizeof(TOKEN_LINKED_TOKEN),
//        &ReturnLength);
//
//    HANDLE hToken = INVALID_HANDLE_VALUE;
//
//    hr = ::MileAdjustTokenAllPrivileges(
//        CurrentProcessToken,
//        SE_PRIVILEGE_ENABLED);
//
//    hr = ::MileSetCurrentThreadToken(LinkedToken.LinkedToken);
//
//    hr = ::MileDuplicateToken(
//        LinkedToken.LinkedToken,
//        MAXIMUM_ALLOWED,
//        nullptr,
//        SecurityIdentification,
//        TokenPrimary,
//        &hToken);
//
//
//
//    STARTUPINFOW StartupInfo = { 0 };
//    PROCESS_INFORMATION ProcessInfo = { 0 };
//
//    StartupInfo.cb = sizeof(STARTUPINFOW);
//
//    StartupInfo.lpDesktop = const_cast<LPWSTR>(L"WinSta0\\Default");
//
//
//    ::CreateProcessWithTokenW(
//        LinkedToken.LinkedToken,
//        0,
//        L"C:\\Windows\\System32\\notepad.exe",
//        nullptr,
//        CREATE_UNICODE_ENVIRONMENT | CREATE_NEW_CONSOLE,
//        nullptr,
//        nullptr,
//        &StartupInfo,
//        &ProcessInfo);
//
//    hr = GetLastError();
//
//    hr = ::MileCreateProcessAsUser(
//        nullptr,
//        L"C:\\Windows\\System32\\notepad.exe",
//        nullptr,
//        nullptr,
//        nullptr,
//        FALSE,
//        CREATE_UNICODE_ENVIRONMENT | CREATE_NEW_CONSOLE,
//        nullptr,
//        nullptr,
//        &StartupInfo,
//        &ProcessInfo);
//
//    ::SetDllDirectoryW(L"");
//    ::SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32);
//
//    SetThreadUILanguage(MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN));
//
//    SetThreadUILanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL));
//
//    SetThreadUILanguage(1033);
//
//    std::wstring fuck = Mile::GetHResultMessage(E_FAIL);
//    MessageBoxW(nullptr, fuck.c_str(), L"NSudo", 0);
//}

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    // Fall back to English in unsupported environment. (Temporary Hack)
    // Reference: https://github.com/M2Team/NSudo/issues/56
    switch (PRIMARYLANGID(::GetThreadUILanguage()))
    {
    case LANG_ENGLISH:
    case LANG_SPANISH:
    case LANG_FRENCH:
    case LANG_ITALIAN:
    case LANG_CHINESE:
        break;
    default:
        ::SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_NEUTRAL));
        break;
    }

    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    g_ResourceManagement.Initialize();

    std::wstring ApplicationName;
    std::map<std::wstring, std::wstring> OptionsAndParameters;
    std::wstring UnresolvedCommandLine;

    Mile::SpiltCommandLineEx(
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
        CNSudoMainWindow MainWindow;
        MainWindow.DoModal(nullptr);
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
