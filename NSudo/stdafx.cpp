// stdafx.cpp : 只包括标准包含文件的源文件
// NSudo.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用

#ifndef  _DEBUG

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4100) // 未引用的形参
#endif

#include <_msvcrt.cpp>

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif 