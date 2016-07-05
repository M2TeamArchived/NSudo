// MiniFM.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
// 微软SDK存在的警告
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#endif

// IFileDialog/IFileOpenDialog/IFileSaveDialog
#include <shobjidl.h>  

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#ifndef _DEBUG
#pragma comment(linker, "/ENTRY:EntryPoint") 
#endif 

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4191) // 从“type of expression”到“type required”的不安全转换(等级 3)
#endif

// 开启对话框Per-Monitor DPI Aware支持（Win10可用）
inline int EnablePerMonitorDialogScaling()
{
	typedef int(WINAPI *PFN_EnablePerMonitorDialogScaling)();

	PFN_EnablePerMonitorDialogScaling pEnablePerMonitorDialogScaling =
		(PFN_EnablePerMonitorDialogScaling)GetProcAddress(
			GetModuleHandleW(L"user32.dll"), (LPCSTR)2577);

	if (pEnablePerMonitorDialogScaling) return pEnablePerMonitorDialogScaling();
	return -1;
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

void EntryPoint()
{
	int uExitCode = wWinMain(
		GetModuleHandleW(nullptr),
		nullptr,
		nullptr,
		SW_SHOWNORMAL);
	
	ExitProcess((UINT)uExitCode);
}

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	IIntendToIgnoreThisVariable(hInstance);
	IIntendToIgnoreThisVariable(hPrevInstance);
	IIntendToIgnoreThisVariable(lpCmdLine);
	IIntendToIgnoreThisVariable(nShowCmd);

	EnablePerMonitorDialogScaling();
	
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
