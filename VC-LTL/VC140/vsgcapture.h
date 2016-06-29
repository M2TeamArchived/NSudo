#pragma once
#pragma comment(lib,"VsGraphicsHelper.lib")

#include <Windows.h>
#include <stdio.h>
#include <sal.h>
#include <functional>

#if defined(__ID3D11DeviceContext2_INTERFACE_DEFINED__)
#error Programmatic graphics capture does not support Direct3D 11.2 APIs.
#endif

#ifndef VSG_DEFAULT_RUN_FILENAME
#define VSG_DEFAULT_RUN_FILENAME L"default.vsglog"
#endif

extern "C" void __stdcall VsgDbgInit(_In_z_ wchar_t const * szVSGLog);
extern "C" void __stdcall VsgDbgInitDelayed(std::function<void (int len, wchar_t * pszBuffer)>);
extern "C" void __stdcall VsgDbgUnInit();
extern "C" void __stdcall VsgDbgToggleHUD();
extern "C" void __stdcall VsgDbgCaptureCurrentFrame();
extern "C" void __stdcall VsgDbgBeginCapture();
extern "C" void __stdcall VsgDbgEndCapture();
extern "C" void __stdcall VsgDbgCopy(_In_z_ wchar_t const * szNewVSGLog);
extern "C" void __stdcall VsgDbgAddHUDMessage(_In_z_ wchar_t const * szMessage);


class VsgDbg
{
public:
	VsgDbg(bool bDefaultInit)
	{
		if(bDefaultInit)
		{
#ifndef DONT_SAVE_VSGLOG_TO_TEMP	

#if WINAPI_FAMILY == 2
			Init([=] (int len, wchar_t * pszBuffer) {

				const wchar_t * tempPath = Platform::String::Concat(Platform::String::Concat(Windows::Storage::ApplicationData::Current->TemporaryFolder->Path, L"\\"), VSG_DEFAULT_RUN_FILENAME)->Data();
				wcscpy_s(pszBuffer, len, tempPath);
			});
#else
			Init([=] (int len, wchar_t * pszBuffer) {

				wchar_t tempDir[MAX_PATH];
				wchar_t filePath[MAX_PATH];

				if(GetTempPath(MAX_PATH, tempDir) == 0)
				{
					return;
				}

				swprintf_s(filePath, MAX_PATH, L"%s%s", tempDir, VSG_DEFAULT_RUN_FILENAME);

				wcscpy_s(pszBuffer, len, filePath);
			});
#endif

#else
			Init([=] (int len, wchar_t * pszBuffer) { 
				wcscpy_s(pszBuffer, len, VSG_DEFAULT_RUN_FILENAME);
			});
#endif
		}
	}

	~VsgDbg()
	{
		UnInit();
	}

	void Init(std::function<void (int len, wchar_t * pszBuffer)> vsgLogGetter)
	{
		VsgDbgInitDelayed(vsgLogGetter);
	}


	void UnInit()
	{
		VsgDbgUnInit();
	}

	void ToggleHUD()
	{
		VsgDbgToggleHUD();
	}

	void BeginCapture ()
	{
		VsgDbgBeginCapture ();
	}

	void EndCapture ()
	{
		VsgDbgEndCapture ();
	}

	void CaptureCurrentFrame ()
	{
		VsgDbgCaptureCurrentFrame ();
	}

	void Copy(_In_z_ wchar_t const * szNewVSGLog)
	{
		VsgDbgCopy(szNewVSGLog);
	}

	void AddMessage(_In_z_ wchar_t const * szMessage)
	{
		VsgDbgAddHUDMessage(szMessage);
	}
};

#ifndef VSG_NODEFAULT_INSTANCE
	_declspec(selectany) VsgDbg *g_pVsgDbg;
	
	inline void  UnInitVsPix()
	{
		if(g_pVsgDbg != NULL)
		{
			delete g_pVsgDbg;
		}
	}

	inline void  InitVsPix()
	{
		g_pVsgDbg = new VsgDbg(true); atexit(&UnInitVsPix); 
	}


	#pragma section(".CRT$XCT",long,read)
	__declspec(allocate(".CRT$XCT"))  _declspec(selectany) _declspec(dllexport) void (*pInitFunc)() = InitVsPix;
		
#endif