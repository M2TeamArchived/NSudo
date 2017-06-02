/******************************************************************************
项目：NSudo
描述：NSudo 版本定义
文件名：Version.h
许可协议：The MIT License

Project: NSudo
Description: NSudo Version Definition
File Name: Version.h
License: The MIT License
******************************************************************************/

#include "CIBuild.h"

#ifndef NSUDO_VER
#define NSUDO_VER

#define NSUDO_VER_MAJOR 5
#define NSUDO_VER_MINOR 0
#define NSUDO_VER_BUILD 1706
#define NSUDO_VER_REV 2
#endif

#ifndef NSUDO_VER_FMT_COMMA
#define NSUDO_VER_FMT_COMMA NSUDO_VER_MAJOR,NSUDO_VER_MINOR,NSUDO_VER_BUILD,NSUDO_VER_REV
#endif

#ifndef NSUDO_VER_FMT_DOT
#define NSUDO_VER_FMT_DOT NSUDO_VER_MAJOR.NSUDO_VER_MINOR.NSUDO_VER_BUILD.NSUDO_VER_REV
#endif


#ifndef MACRO_TO_STRING
#define _MACRO_TO_STRING(arg) L#arg
#define MACRO_TO_STRING(arg) _MACRO_TO_STRING(arg)
#endif

#ifndef NSUDO_VERSION
#define NSUDO_VERSION NSUDO_VER_FMT_COMMA
#endif

#ifndef _NSUDO_VERSION_STRING_
#define _NSUDO_VERSION_STRING_ MACRO_TO_STRING(NSUDO_VER_FMT_DOT)
#endif

#ifndef NSUDO_VERSION_STRING
#ifdef NSUDO_CI_BUILD
#define NSUDO_VERSION_STRING _NSUDO_VERSION_STRING_ L" " NSUDO_CI_BUILD
#else
#define NSUDO_VERSION_STRING _NSUDO_VERSION_STRING_
#endif
#endif
