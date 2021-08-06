/*
 * PROJECT:   NSudo Launcher
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

#include "Mile.Project.Properties.h"

int main()
{
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
        L"© M2-Team. All rights reserved.\r\n"
        L"\r\n"
        //L"DetailedVersionTag: 20210806_LegnaBrighost"
        //L"\r\n"
        //L"Under Construction. You should not use this version for production."
        //L"\r\n" 
        L"内部版本标签：20210806_LegnaBrighost\r\n"
        L"\r\n"
        L"本版属于内部开发版本。您不应将此用于生产。\r\n"
        L"\r\n");

    std::wstring CommandLine = std::wstring(::GetCommandLineW());

    std::vector<std::wstring> Arguments = Mile::SpiltCommandLine(CommandLine);
    if (Arguments.size() < 3)
    {
        Context.PublicContext.Write(
            &Context.PublicContext,
            L"命令行参数错误。\r\n"
            L"格式: NSudoPluginHost [ 插件模块名 ] [ 插件入口名 ] [插件参数]\r\n"
            L"注：插件模块必须与本二进制放在同一目录。\r\n"
            L"\r\n");
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
        wchar_t* command = wcsstr(search_start, L" ") + 1;

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
