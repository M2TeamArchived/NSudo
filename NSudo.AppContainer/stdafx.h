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
#ifdef _DLL
#define _CRT_SECURE_NO_WARNINGS
#include <_msvcrt.h>
#endif 
#endif 

#pragma region TargetVersion

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// 将 _WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。

#include <SDKDDKVer.h>

#define _WIN32_WINNT_WIN10_TH2 _WIN32_WINNT_WIN10
#define _WIN32_WINNT_WIN10_RS1 _WIN32_WINNT_WIN10

#pragma endregion

#include <stdio.h>
#include <tchar.h>

#define M2_Base_Not_Overload_New

// NSudoSDK
#include "M2.NSudo.hpp"

// 字符串安全操作函数
#include <strsafe.h>
