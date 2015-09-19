#pragma once

struct LanguageResource
{
	wchar_t* NSudo_Text_Default;

	wchar_t* NSudo_Text_TI;
	wchar_t* NSudo_Text_Sys;
	wchar_t* NSudo_Text_CU;
	wchar_t* NSudo_Text_CP;
	wchar_t* NSudo_Text_CPD;

	wchar_t* NSudo_Text_EnableAll;
	wchar_t* NSudo_Text_DisableAll;

	wchar_t* NSudo_Text_Low;
	wchar_t* NSudo_Text_Medium;
	wchar_t* NSudo_Text_High;
	wchar_t* NSudo_Text_System;

	wchar_t* NSudo_AboutText;

	wchar_t* NSudo_Error_Text1;
	wchar_t* NSudo_Error_Text2;
	wchar_t* NSudo_Error_Text3;
	wchar_t* NSudo_Error_Text4;

	wchar_t* NSudoC_HelpText;
};

/*
LanguageResource TextRes = {
	L"默认",

	L"TrustedInstaller",
	L"System",
	L"当前用户",
	L"当前进程",
	L"当前进程(降权)",

	L"启用全部特权",
	L"禁用所有特权",

	L"低",
	L"中",
	L"高",
	L"系统",

	L"NSudo 3.2(Build 1000)\n"
	L"\xA9 2015 NSudo Team. All rights reserved.\n\n"
	L"捐赠支付宝账号: wxh32lkk@live.cn\n"
	L"感谢boyangpangzi,cjy__05,mhxkx,NotePad,tangmigoId,wondersnefu,xy137425740,月光光的大力支持（按照字母排序）",

	L"获取SE_DEBUG_NAME特权失败(请以管理员权限运行)",
	L"请在下拉框中输入命令行或选择快捷命令",
	L"进程创建失败",
	L"命令行参数有误，请修改(使用 - ? 参数查看帮助)",

	L"格式: NSudoC [ -U ] [ -P ] [ -M ] 命令行或常用任务名\n"
	L"  -U:[ T | S | C | P | D ] 用户\n"
	L"  	T TrustedInstaller\n"
	L"  	S System\n"
	L"  	C 当前用户\n"
	L"  	P 当前进程\n"
	L"  	D 当前进程(降权)\n\n"
	L"  -P:[ E | D ] 特权\n"
	L"  	E 启用全部特权\n"
	L"  	D 禁用所有特权\n"
	L"  	PS: 如果想以默认特权方式的话，请不要包含-P参数\n\n"
	L"  -M:[ S | H | M | L ] 完整性\n"
	L"  	S 系统\n"
	L"  	H 高\n"
	L"  	M 中\n"
	L"  	L 低\n"
	L"  	PS: 如果想以默认完整性方式的话，请不要包含-M参数\n\n"
	L"  -? 显示该内容\n\n"
	L"  例子：以TrustedInstaller权限，启用所有特权，完整性默认运行命令提示符\n"
	L"		NSudoC -U:T -P:E cmd\n"
};
*/