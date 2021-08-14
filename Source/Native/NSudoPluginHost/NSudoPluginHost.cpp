/*
 * PROJECT:   NSudo Plugin Host
 * FILE:      NSudoPluginHost.cpp
 * PURPOSE:   Implementation for NSudo Plugin Host
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Mile.Windows.h>

#include <string>
#include <vector>

#include <NSudoContextPluginHost.h>
#include <toml.hpp>

#include "Mile.Project.Properties.h"

int main()
{
    // Fall back to English in unsupported environment. (Temporary Hack)
    // Reference: https://github.com/M2Team/NSudo/issues/56
    switch (PRIMARYLANGID(::GetThreadUILanguage()))
    {
    case LANG_ENGLISH:
    case LANG_CHINESE:
        break;
    default:
        ::SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_NEUTRAL));
        break;
    }

    std::map<std::string, std::wstring> GlobalTranslations;

    Mile::RESOURCE_INFO ResourceInfo = { 0 };
    if (SUCCEEDED(Mile::LoadResource(
        &ResourceInfo,
        ::GetModuleHandleW(nullptr),
        L"Translations",
        MAKEINTRESOURCEW(1))))
    {
        try
        {
            toml::table Translations = toml::parse(std::string(
                reinterpret_cast<const char*>(ResourceInfo.Pointer),
                ResourceInfo.Size));
            for (auto const& Translation : Translations)
            {
                GlobalTranslations.emplace(std::make_pair(
                    Translation.first,
                    Mile::ToUtf16String(
                        Translation.second.value_or<std::string>(""))));
            }
        }
        catch (...)
        {

        }
    }

    NSUDO_CONTEXT_PRIVATE Context;

    ::NSudoContextFillFunctionTable(
        &Context.PublicContext);

    Context.Size = sizeof(NSUDO_CONTEXT_PRIVATE);

    Context.PiConsoleWindowHandle = nullptr;
    Context.ConsoleInputHandle = ::GetStdHandle(STD_INPUT_HANDLE);
    Context.ConsoleOutputHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
    Context.ConsoleMode = true;


    Context.PublicContext.Write(
        &Context.PublicContext,
        L"NSudo Plugin Host " MILE_PROJECT_VERSION_STRING L" (Build "
        MILE_PROJECT_MACRO_TO_STRING(MILE_PROJECT_VERSION_BUILD) L")" L"\r\n"
        L"(c) M2-Team. All rights reserved.\r\n"
        L"\r\n");

    Context.PublicContext.Write(
        &Context.PublicContext,
        GlobalTranslations["WarningText"].c_str());

    std::wstring CommandLine = std::wstring(::GetCommandLineW());

    std::vector<std::wstring> Arguments = Mile::SpiltCommandLine(CommandLine);
    if (Arguments.size() < 3)
    {
        Context.PublicContext.Write(
            &Context.PublicContext,
            GlobalTranslations["CommandLineHelpText"].c_str());
        return E_INVALIDARG;
    }

    std::wstring PluginModuleName = Arguments[1];
    std::wstring PluginEntryName = Arguments[2];
    std::wstring PluginArguments;

    if (Arguments.size() > 3)
    {
        std::size_t ArgumentSize = 0;

        ArgumentSize += Arguments[0].size() + 1;
        ArgumentSize += Arguments[1].size() + 1;
        ArgumentSize += Arguments[2].size() + 1;

        // Get the approximate location of the unresolved command line.
        // We use "(arg_size - 1)" to ensure that the program path
        // without quotes can also correctly parse.
        wchar_t* search_start =
            const_cast<wchar_t*>(CommandLine.c_str()) + (ArgumentSize - 1);

        // Get the unresolved command line. Search for the beginning of
        // the first parameter delimiter called space and exclude the
        // first space by adding 1 to the result.
        wchar_t* command = ::wcsstr(search_start, L" ") + 1;

        // Omit the space. (Thanks to wzzw.)
        while (command && *command == L' ')
        {
            ++command;
        }

        PluginArguments = std::wstring(command);
    }

    std::wstring RootPath = Mile::GetCurrentProcessModulePath();
    std::wcsrchr(&RootPath[0], '\\')[0] = L'\0';
    RootPath.resize(std::wcslen(RootPath.c_str()));

    HRESULT hr = ::NSudoContextExecutePlugin(
        &Context.PublicContext,
        (RootPath + L"\\" + PluginModuleName).c_str(),
        Mile::ToUtf8String(PluginEntryName).c_str(),
        PluginArguments.c_str());

    return hr;
}
