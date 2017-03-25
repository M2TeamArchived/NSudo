// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
// 编译器优化可能出现的警告（去除未引用函数并适当对一些函数使用内联）
#pragma warning(disable:4505) // 未引用的本地函数已移除(等级 4)
#pragma warning(disable:4710) // 函数未内联(等级 4)
#pragma warning(disable:4711) // 为自动内联扩展选定了函数(等级 1,只是提示信息)
#endif

#ifndef _DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <_msvcrt.h>
#endif 

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <M2.SDK.h>

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include <strsafe.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "resource.h"