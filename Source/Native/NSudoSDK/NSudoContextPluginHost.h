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

/**
 * @brief Definition for NSudo private context.
*/
typedef struct _NSUDO_CONTEXT_PRIVATE
{
    NSUDO_CONTEXT PublicContext;

    SIZE_T Size;

    HWND PiConsoleWindowHandle;

    HMODULE ModuleHandle;
    LPCWSTR CommandArguments;

} NSUDO_CONTEXT_PRIVATE, * PNSUDO_CONTEXT_PRIVATE;


/**
 * @brief Fills the function table of the NSudo context.
 * @param Context The NSudo context.
*/
EXTERN_C VOID WINAPI NSudoContextFillFunctionTable(
    _In_ PNSUDO_CONTEXT Context);

#endif // !NSUDO_CONTEXT_PLUGIN_HOST
