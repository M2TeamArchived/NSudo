// MiniFM.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <shobjidl.h>               // for IFileDialog/IFileOpenDialog/IFileSaveDialog

#pragma comment(lib,"shlwapi.lib")

#pragma comment(linker, "/ENTRY:EntryPoint") 

void EntryPoint()
{
	int uExitCode = wWinMain(
		GetModuleHandleW(nullptr),
		nullptr,
		nullptr,
		SW_SHOWNORMAL);
	
	ExitProcess(uExitCode);
}

int WINAPI wWinMain1(
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

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	HRESULT hr = S_OK;
	IFileDialog *pFileDialog = nullptr;
	IShellItem *pShellItemFolder = nullptr;
	wchar_t g_AppPath[260];

	// 初始化COM
	hr = CoInitializeEx(
		nullptr,
		COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr)) goto FuncEnd;

	// 创建IFileDialog接口对象
	hr = CoCreateInstance(
		CLSID_FileOpenDialog,
		nullptr,
		CLSCTX_INPROC_SERVER,
		__uuidof(IFileDialog),
		(void**)&pFileDialog);
	if (FAILED(hr)) goto FuncEnd;

	// 设置选项
	hr = pFileDialog->SetOptions(
		FOS_FORCEFILESYSTEM | FOS_ALLOWMULTISELECT | FOS_FORCESHOWHIDDEN);
	if (FAILED(hr)) goto FuncEnd;

	// 获取当前路径
	GetModuleFileNameW(nullptr, g_AppPath, 260);
	wcsrchr(g_AppPath, L'\\')[0] = L'\0';

	// 获取当前路径的IShellItem接口对象
	hr = SHCreateItemFromParsingName(
		g_AppPath,
		nullptr,
		__uuidof(IShellItem),
		(void**)&pShellItemFolder);
	if (FAILED(hr)) goto FuncEnd;

	// 设置路径
	pFileDialog->SetFolder(pShellItemFolder);
	if (FAILED(hr)) goto FuncEnd;

	// 显示窗口
	hr = pFileDialog->Show(nullptr);

FuncEnd:
	if (pShellItemFolder) pShellItemFolder->Release();
	if (pFileDialog) pFileDialog->Release();
	CoUninitialize();

	return 0;
}
