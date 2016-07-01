// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#ifndef _DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <_msvcrt.h>
#endif 

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

//#include<Userenv.h>
//#pragma comment(lib,"Userenv.lib")

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include "..\NSudoSDK\M2.BaseLib.hpp"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "resource.h"