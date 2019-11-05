/*
 * PROJECT:   NSudo User Experience Library
 * FILE:      NSudoUX.h
 * PURPOSE:   Definition for NSudo User Experience Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef NSUDO_UX
#define NSUDO_UX

#ifndef __cplusplus
#error "[NSudoUX] You should use a C++ compiler."
#endif

#include <Windows.h>

#include <map>
#include <string>

#include "Resources/resource.h"

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

EXTERN_C BSTR WINAPI NSudoUXGetTranslation(
    _In_ LPCSTR Key);

EXTERN_C BSTR WINAPI NSudoUXGetMessageString(
    _In_ NSUDO_MESSAGE MessageID);

EXTERN_C void WINAPI NSudoUXLoadShortCut(
    LPCWSTR ShortCutListPath,
    std::map<std::wstring, BSTR>& ShortCutList);

#endif
