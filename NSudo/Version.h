#include "CIBuild.h"

#ifndef NSUDO_VERSION
#define NSUDO_VERSION 4, 4, 1705, 19
#endif

#ifndef _NSUDO_VERSION_STRING_
#define _NSUDO_VERSION_STRING_ L"4.4.1705.19"
#endif

#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4668) // 没有将“symbol'”定义为预处理器宏，用“0”替换“directives”(等级 4)
#endif

#ifndef NSUDO_VERSION_STRING
#if NSUDO_CI_BUILD
#define NSUDO_VERSION_STRING _NSUDO_VERSION_STRING_ NSUDO_CI_BUILD
#else
#define NSUDO_VERSION_STRING _NSUDO_VERSION_STRING_
#endif
#endif

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif



