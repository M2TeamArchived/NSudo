#pragma once

// Windows头文件
#include <Windows.h>

// 基本库

#include "NativeLib.hpp"
#include "WinStationLib.hpp"
#include "M2.Base.hpp"

#include "M2.NSudo.hpp"

#define MemAlloc M2::M2AllocMemory
#define MemFree M2::M2FreeMemory
#define InitObjAttr M2::M2InitObjectAttributes