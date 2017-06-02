/******************************************************************************
项目：NSudoSDK
描述：NSudo库
文件名：NSudoAPI.h
许可协议：The MIT License

Project: NSudoSDK
Description: NSudo Library
File Name: NSudoAPI.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _NSUDOAPI_
#define _NSUDOAPI_

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#endif

#include <Windows.h>
#include <WtsApi32.h>

#pragma comment(lib,"WtsApi32.lib")

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	

#ifdef __cplusplus
}
#endif

#endif