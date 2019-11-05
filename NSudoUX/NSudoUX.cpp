/*
 * PROJECT:   NSudo User Experience Library
 * FILE:      NSudoUX.cpp
 * PURPOSE:   Implementation for NSudo User Experience Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "NSudoUX.h"

#include "../NSudo/NSudoVersion.h"

#include "json.hpp"

EXTERN_C HMODULE g_NSudoUXModule;

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

/**
 * Converts from the UTF-8 string to the UTF-16 string.
 *
 * @param UTF8String The UTF-8 string you want to convert.
 * @return A converted UTF-16 string.
 */
std::wstring M2MakeUTF16String(const std::string& UTF8String)
{
    std::wstring UTF16String;

    int UTF16StringLength = MultiByteToWideChar(
        CP_UTF8,
        0,
        UTF8String.data(),
        (int)UTF8String.size(),
        nullptr,
        0);
    if (UTF16StringLength > 0)
    {
        UTF16String.resize(UTF16StringLength);
        MultiByteToWideChar(
            CP_UTF8,
            0,
            UTF8String.data(),
            (int)UTF8String.size(),
            &UTF16String[0],
            UTF16StringLength);
    }

    return UTF16String;
}

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

#include <vector>

class CNSudoUXResources
{
private:

    std::vector<BSTR> m_BStrPool;
    std::map<std::string, BSTR> m_StringTranslations;

public:

    BSTR MakeBStr(_In_ LPCWSTR String)
    {
        return this->m_BStrPool.emplace_back(::SysAllocString(String));
    }

    BSTR GetUTF8WithBOMStringResources(
        _In_ UINT uID)
    {
        M2_RESOURCE_INFO ResourceInfo = { 0 };
        if (SUCCEEDED(M2LoadResource(
            &ResourceInfo,
            g_NSudoUXModule,
            L"String",
            MAKEINTRESOURCEW(uID))))
        {
            // Raw string without the UTF-8 BOM. (0xEF,0xBB,0xBF)	
            return this->MakeBStr(M2MakeUTF16String(std::string(
                reinterpret_cast<const char*>(ResourceInfo.Pointer) + 3,
                ResourceInfo.Size - 3)).c_str());
        }

        return ::SysAllocString(L"");
    }

    void Initialize()
    {
        this->m_StringTranslations.clear();

        this->m_StringTranslations.emplace(std::make_pair(
            "NSudo.VersionText",
            this->MakeBStr(L"M2-Team NSudo " NSUDO_VERSION_STRING_FOR_SHOW)));

        this->m_StringTranslations.emplace(std::make_pair(
            "NSudo.LogoText",
            this->MakeBStr(L"M2-Team NSudo " NSUDO_VERSION_STRING_FOR_SHOW L"\r\n"
            L"© M2-Team. All rights reserved.\r\n"
            L"\r\n")));

        this->m_StringTranslations.emplace(std::make_pair(
            "NSudo.String.Links",
            GetUTF8WithBOMStringResources(
                IDR_String_Links)));

        this->m_StringTranslations.emplace(std::make_pair(
            "NSudo.String.CommandLineHelp",
            GetUTF8WithBOMStringResources(
                IDR_String_CommandLineHelp)));

        M2_RESOURCE_INFO ResourceInfo = { 0 };
        if (SUCCEEDED(M2LoadResource(
            &ResourceInfo,
            g_NSudoUXModule,
            L"String",
            MAKEINTRESOURCEW(IDR_String_Translations))))
        {
            nlohmann::json StringTranslationsJSON =
                nlohmann::json::parse(std::string(
                    reinterpret_cast<const char*>(ResourceInfo.Pointer),
                    ResourceInfo.Size));

            for (auto& Item : StringTranslationsJSON["Translations"].items())
            {
                this->m_StringTranslations.emplace(std::make_pair(
                    Item.key(),
                    this->MakeBStr(M2MakeUTF16String(Item.value()).c_str())));
            }
        }
    }

    BSTR GetTranslation(
        _In_ std::string Key)
    {
        return this->m_StringTranslations[Key];
    }
};

CNSudoUXResources g_UXResources;

void NSudoUXInitialize()
{
    return g_UXResources.Initialize();
}

EXTERN_C BSTR WINAPI NSudoUXGetTranslation(
    _In_ LPCSTR Key)
{
    return g_UXResources.GetTranslation(Key);
}

EXTERN_C BSTR WINAPI NSudoUXGetMessageString(
    _In_ NSUDO_MESSAGE MessageID)
{
    return NSudoUXGetTranslation(NSudoMessageTranslationID[MessageID]);
}

EXTERN_C void WINAPI NSudoUXLoadShortCut(
    _In_ LPCWSTR ShortCutListPath,
    std::map<std::wstring, BSTR>& ShortCutList)
{
    ShortCutList.clear();

    HANDLE FileHandle = ::CreateFileW(
        ShortCutListPath,
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
                nlohmann::json ConfigJSON = nlohmann::json::parse(MapAddress);

                for (auto& Item : ConfigJSON["ShortCutList_V2"].items())
                {
                    ShortCutList.emplace(std::make_pair(
                        M2MakeUTF16String(Item.key()),
                        g_UXResources.MakeBStr(M2MakeUTF16String(Item.value()).c_str())));
                }

                ::UnmapViewOfFile(MapAddress);
            }

            ::CloseHandle(FileMapping);
        }

        ::CloseHandle(FileHandle);
    }
}
