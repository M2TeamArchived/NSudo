// MiniFM.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	wchar_t g_AppPath[260];
	GetModuleFileNameW(nullptr, g_AppPath, 260);
	wcsrchr(g_AppPath, L'\\')[0] = L'\0';

	OPENFILENAMEW ofn = { 0 };

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_HIDEREADONLY | OFN_FORCESHOWHIDDEN | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	ofn.lpstrInitialDir = g_AppPath;

	GetOpenFileNameW(&ofn);

	return 0;
}

