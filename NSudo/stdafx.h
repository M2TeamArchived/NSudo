/*
 * PROJECT:   NSudo
 * FILE:      stdafx.h
 * PURPOSE:   Precompiled Header
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#define NOMINMAX

#pragma region targetver

#include <SDKDDKVer.h>

#define _WIN32_WINNT_WIN10_TH2 _WIN32_WINNT_WIN10
#define _WIN32_WINNT_WIN10_RS1 _WIN32_WINNT_WIN10

#pragma endregion


#include "M2BaseHelpers.h"
#include "M2Win32Helpers.h"
#include "M2Win32GUIHelpers.h"

#include "NSudoAPI.h"

#include <stdio.h>
#include <tchar.h>

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "NSudoVersion.h"
#include "resource.h"

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
