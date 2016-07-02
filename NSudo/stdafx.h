// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

// Disable Warnings
#if _MSC_VER >= 1200
//#pragma warning(disable:4018) // signed/unsigned mismatch
#pragma warning(disable:4100) // unreferenced formal parameter
#pragma warning(disable:4505) // Unreferenced local function has been removed
#pragma warning(disable:4710) // function not inlined
#pragma warning(disable:4711) // function 'function' selected for inline expansion
#endif

#ifndef _DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <_msvcrt.h>
#endif 

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

// Disable Warnings
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4464) // relative include path contains '..'
#endif

// NSudoSDK
#include "..\NSudoSDK\M2.BaseLib.hpp"

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "resource.h"