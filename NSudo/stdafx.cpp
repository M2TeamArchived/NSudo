// stdafx.cpp : 只包括标准包含文件的源文件
// NSudo.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用

#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4061) // 枚举数没有被 case 标签显式处理(等级 4)
#pragma warning(disable:4100) // 未引用的形参(等级 4)
#pragma warning(disable:4273) // dll 链接不一致(等级 1)
#pragma warning(disable:4365) // 有符号/无符号不匹配(等级 4)
#pragma warning(disable:4571) // 不再捕获结构化的异常(SEH)(等级 4)
#pragma warning(disable:4625) // 已将复制构造函数隐式定义为“已删除”(等级 4)
#pragma warning(disable:4623) // 已将默认构造函数隐式定义为“已删除”(等级 4)
#pragma warning(disable:4626) // 已将对齐运算符隐式定义为“已删除”(等级 4)
#pragma warning(disable:4774) // 参数中应存在的格式字符串不为字符串字面量
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#pragma warning(disable:4987) // 使用了非标准扩展: “throw (...)”(等级 4)
#pragma warning(disable:5026) // 已将移动构造函数隐式定义为“已删除”
#pragma warning(disable:5027) // 已将移动赋值运算符隐式定义为“已删除”
#endif

#include <_msvcrt.cpp>

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#include <M2.Base.cpp>
