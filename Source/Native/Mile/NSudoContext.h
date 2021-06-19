/*
 * PROJECT:   NSudo Software Development Kit
 * FILE:      NSudoContext.h
 * PURPOSE:   Definition for NSudo context plugin
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef _NSUDO_CONTEXT_H_
#define _NSUDO_CONTEXT_H_

#include <Windows.h>

/**
 * @brief Forward definition for NSudo context.
*/
typedef struct _NSUDO_CONTEXT NSUDO_CONTEXT, *PNSUDO_CONTEXT;

/**
 * @brief Definition for NSudo context.
*/
struct _NSUDO_CONTEXT
{
    /**
     * @brief Gets the module handle of the context plugin.
     * @param Context The NSudo context.
     * @return The module handle of the context plugin.
    */
    HMODULE(WINAPI* GetContextPluginModuleHandle)(
        _In_ PNSUDO_CONTEXT Context);

    /**
     * @brief Gets the command line arguments for the context plugin.
     * @param Context The NSudo context.
     * @return The command line arguments for the context plugin.
    */
    LPCWSTR(WINAPI* GetContextPluginCommandLine)(
        _In_ PNSUDO_CONTEXT Context);

    /**
     * @brief Writes the specified string value to the NSudo user interface.
     * @param Context The NSudo context.
     * @param Value The value to write.
    */
    VOID(WINAPI* Write)(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR Value);

    /**
     * @brief Writes the specified string value, followed by the current line
     *        terminator, to NSudo user interface.
     * @param Context The NSudo context.
     * @param Value The value to write.
    */
    VOID(WINAPI* WriteLine)(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR Value);
};

/**
 * @brief The entry point type of NSudo context plugin.
 * @param Context The NSudo context.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
*/
typedef HRESULT(WINAPI* NSudoContextPluginEntryPointType)(
    _In_ PNSUDO_CONTEXT Context);

#endif // !_NSUDO_CONTEXT_H_
