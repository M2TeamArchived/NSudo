/*
 * PROJECT:   NSudo Software Development Kit
 * FILE:      NSudoContextPlugin.h
 * PURPOSE:   Definition for NSudo context plugin
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef NSUDO_CONTEXT_PLUGIN
#define NSUDO_CONTEXT_PLUGIN

#include <Windows.h>

/**
 * @brief Definition for NSudo context.
*/
typedef struct _NSUDO_CONTEXT
{
    /**
     * @brief Prints a message.
     * @param Message The content of the message.
    */
    VOID(WINAPI* PrintMessage)(
        _In_ LPCWSTR Message);

} NSUDO_CONTEXT, * PNSUDO_CONTEXT;

/**
 * @brief The entry point type of NSudo context plugin.
 * @param Context The NSudo context.
 * @param ModuleHandle The module handle of the context plugin.
 * @param CommandLine The command-line arguments for the context plugin.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
*/
typedef HRESULT(WINAPI* NSudoContextPluginEntryPointType)(
    _In_ PNSUDO_CONTEXT Context,
    _In_ HMODULE ModuleHandle,
    _In_ LPCWSTR CommandLine);

#endif // !NSUDO_CONTEXT_PLUGIN
