/*
 * PROJECT:   NSudo Software Development Kit
 * FILE:      NSudoContextPluginHost.h
 * PURPOSE:   Definition for NSudo context plugin host
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef NSUDO_CONTEXT_PLUGIN_HOST
#define NSUDO_CONTEXT_PLUGIN_HOST

#include "NSudoContextPlugin.h"

#include <map>
#include <string>

/**
 * @brief Definition for NSudo private context.
*/
typedef struct _NSUDO_CONTEXT_PRIVATE
{
    NSUDO_CONTEXT PublicContext;

    SIZE_T Size;

    HWND PiConsoleWindowHandle;
    HANDLE ConsoleInputHandle;
    HANDLE ConsoleOutputHandle;
    bool ConsoleMode;

    HMODULE ModuleHandle;
    LPCWSTR CommandArguments;

    std::map<std::string, std::wstring> Translations;

} NSUDO_CONTEXT_PRIVATE, *PNSUDO_CONTEXT_PRIVATE;


/**
 * @brief Fills the function table of the NSudo context.
 * @param Context The NSudo context.
*/
EXTERN_C VOID WINAPI NSudoContextFillFunctionTable(
    _In_ PNSUDO_CONTEXT Context);

/**
 * @brief Executes the context plugin.
 * @param Context The NSudo context.
 * @param PluginModuleName The module name of the context plugin.
 * @param PluginEntryPointName The entry point name of the context plugin.
 * @param CommandArguments The command line arguments of the context plugin.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
*/
EXTERN_C HRESULT WINAPI NSudoContextExecutePlugin(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCWSTR PluginModuleName,
    _In_ LPCSTR PluginEntryPointName,
    _In_ LPCWSTR CommandArguments);

#endif // !NSUDO_CONTEXT_PLUGIN_HOST
