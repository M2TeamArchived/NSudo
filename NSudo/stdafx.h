// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#define NOMINMAX

#include "targetver.h"

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

#include "ThirdParty\rapidjson\document.h"
#include "ThirdParty\rapidjson\istreamwrapper.h"
#include "ThirdParty\rapidjson\encodedstream.h"

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
