/*
 * PROJECT:   NShadow
 * FILE:      NShadow.cpp
 * PURPOSE:   Implementation for NShadow
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "stdafx.h"

#include "NShadow.h"

typedef struct _NSHADOW_ENVIRONMENT_CONFIGURATION
{
    std::wstring CurrentDirectory;
    std::vector<std::wstring> EnvironmentVariables;

    std::wstring TokenIntegrityLevel;
    std::vector<std::wstring> TokenPrivileges;

} NSHADOW_ENVIRONMENT_CONFIGURATION, *PNSHADOW_ENVIRONMENT_CONFIGURATION;
