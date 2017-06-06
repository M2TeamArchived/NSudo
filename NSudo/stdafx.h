// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#define NOMINMAX

#include "targetver.h"

#include <NSudoAPI.h>

// C++ 运行时库
#include <stdio.h>
#include <tchar.h>

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include <strsafe.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "resource.h"

#include <vector>
#include <string>
#include <fstream>

#include "ThirdParty\json.hpp"

#include "m2base.h"
