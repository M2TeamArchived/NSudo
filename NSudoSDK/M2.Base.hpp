/**************************************************************************
描述：基本库(有些是对M2.Native的封装)
维护者：Mouri_Naruto (M2-Team)
版本：1.5 (2016-11-27)
基于项目：无
协议：The MIT License
用法：直接Include此头文件即可(前提你要在这之前Include Windows.h)
建议的Windows SDK版本：10.0.10586及以后
***************************************************************************/

#pragma once

#ifndef M2_BASE
#define M2_BASE

// Windows 头文件
#include <windows.h>

// 用户模式本机API调用及其数据结构定义
#include "M2.Native.hpp"

// 窗口站管理调用及其数据结构定义
#include "M2.WinSta.hpp"

// COM类定义
#include "M2.ComHelper.hpp"

// 用宏实现内联GetLastError()
#define GetLastError() NtCurrentTeb()->LastErrorValue

// 用宏实现内联NativeAPI
#ifdef NATIVEAPI

#define HeapAlloc RtlAllocateHeap
#define HeapFree RtlFreeHeap

#define GetProcessHeap RtlProcessHeap

#endif


//GetProcessHeap()的速度比较慢，而且有大小上限限制。推荐新建一个堆或者直接使用C runtime
#ifndef M2_Base_Not_Overload_New

#define malloc(_Size) HeapAlloc(GetProcessHeap(), 0, _Size)
#define free(_Block) HeapFree(GetProcessHeap(), 0, _Block)

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable: 4595) // 为了重定向new和delete操作符
#endif

#include <new>

__forceinline void* __CRTDECL operator new(
	size_t _Size)
{
	return malloc(_Size);
}

__forceinline void* __CRTDECL operator new[](
	size_t _Size)
{
	return malloc(_Size);
}

__forceinline void __CRTDECL operator delete(
	void* _Block) throw()
{
	free(_Block);
}

__forceinline void __CRTDECL operator delete[](
	void* _Block) throw()
{
	free(_Block);
}

__forceinline void* __CRTDECL operator new(
	size_t                _Size,
	std::nothrow_t const&) throw()
{
	return malloc(_Size);
}

__forceinline void* __CRTDECL operator new[](
	size_t                _Size,
	std::nothrow_t const&) throw()
{
	return malloc(_Size);
}

__forceinline void __CRTDECL operator delete(
	void* _Block,
	std::nothrow_t const&) throw()
{
	free(_Block);
}

__forceinline void __CRTDECL operator delete[](
	void* _Block,
	std::nothrow_t const&) throw()
{
	free(_Block);
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif //M2_Base_Not_Overload_New


namespace M2
{
	// 本机API内联调用(M2-Team编写的)
#ifdef NATIVEAPI
	// 获取KUSER_SHARED_DATA结构
	inline PKUSER_SHARED_DATA M2GetKUserSharedData()
	{
		return ((PKUSER_SHARED_DATA const)0x7ffe0000);
	}

	// 获取当前系统会话号
	inline DWORD M2GetCurrentSessionID()
	{
		return M2GetKUserSharedData()->ActiveConsoleId;
	}

	// 初始化OBJECT_ATTRIBUTES结构
	inline void M2InitObjectAttributes(
		_Out_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_ PUNICODE_STRING ObjectName = nullptr,
		_In_ ULONG Attributes = 0,
		_In_ HANDLE RootDirectory = nullptr,
		_In_ PVOID SecurityDescriptor = nullptr,
		_In_ PVOID SecurityQualityOfService = nullptr)
	{
		ObjectAttributes->Length = sizeof(OBJECT_ATTRIBUTES);
		ObjectAttributes->RootDirectory = RootDirectory;
		ObjectAttributes->Attributes = Attributes;
		ObjectAttributes->ObjectName = ObjectName;
		ObjectAttributes->SecurityDescriptor = SecurityDescriptor;
		ObjectAttributes->SecurityQualityOfService = SecurityQualityOfService;
	}

	// 初始化SECURITY_QUALITY_OF_SERVICE结构
	inline void M2InitSecurityQuailtyOfService(
		_Out_ PSECURITY_QUALITY_OF_SERVICE SecurityQuailtyOfService,
		_In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
		_In_ SECURITY_CONTEXT_TRACKING_MODE ContextTrackingMode,
		_In_ BOOLEAN EffectiveOnly)
	{
		SecurityQuailtyOfService->Length = sizeof(SECURITY_QUALITY_OF_SERVICE);
		SecurityQuailtyOfService->ImpersonationLevel = ImpersonationLevel;
		SecurityQuailtyOfService->ContextTrackingMode = ContextTrackingMode;
		SecurityQuailtyOfService->EffectiveOnly = EffectiveOnly;
	}

	// 初始化CLIENT_ID结构
	inline void M2InitClientID(
		_Out_ PCLIENT_ID ClientID,
		_In_opt_ DWORD ProcessID,
		_In_opt_ DWORD ThreadID)
	{
		ClientID->UniqueProcess = UlongToHandle(ProcessID);
		ClientID->UniqueThread = UlongToHandle(ThreadID);
	}
#endif

	// 堆
#pragma region Heap
	
	// 在默认堆上分配内存
	FORCEINLINE PVOID M2HeapAlloc(
		_In_ SIZE_T Size)
	{
		return HeapAlloc(GetProcessHeap(), 0, Size);
	}

	// 在默认堆上释放内存
	FORCEINLINE VOID M2HeapFree(
		_In_ PVOID BaseAddress)
	{
		HeapFree(GetProcessHeap(), 0, BaseAddress);
	}


#ifdef NATIVEAPI

	// 在默认堆上分配内存
	template<typename PtrType>
	FORCEINLINE NTSTATUS M2HeapAlloc(
		_In_ SIZE_T Size,
		_Out_ PtrType &BaseAddress)
	{
		BaseAddress = (PtrType)RtlAllocateHeap(RtlProcessHeap(), 0, Size);
		return (BaseAddress ? STATUS_SUCCESS : STATUS_NO_MEMORY);
	}

#endif


	// 分配初始化为零的内存
	__forceinline void* M2AllocZeroedMemory(
		_In_ size_t Size)
	{
		return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
	}	

	// 内存指针模板类
	template<typename PtrType> class CPtr
	{
	public:
		// 分配内存
		bool Alloc(_In_ size_t Size)
		{
			if (m_Ptr) this->Free();
			m_Ptr = malloc(Size);
			return (m_Ptr != nullptr);
		}

		// 释放内存
		void Free()
		{
			free(m_Ptr);
			m_Ptr = nullptr;
		}

		// 获取内存指针
		operator PtrType() const
		{
			return (PtrType)m_Ptr;
		}

		// 获取内存指针(->运算符)
		PtrType operator->() const
		{
			return (PtrType)m_Ptr;
		}

		// 设置内存指针
		CPtr& operator=(_In_ PtrType Ptr)
		{
			if (Ptr != m_Ptr) // 如果值相同返回自身,否则赋新值
			{
				if (m_Ptr) this->Free(); // 如果内存已分配则释放			
				m_Ptr = Ptr; // 设置内存指针
			}
			return *this; // 返回自身
		}

		// 退出时释放内存
		~CPtr()
		{
			if (m_Ptr) this->Free();
		}

	private:
		//指针内部变量
		void *m_Ptr = nullptr;
	};

#pragma endregion

	// 服务
#pragma region Services

	//启动一个服务并返回服务进程ID
	static DWORD WINAPI M2StartService(
		_In_ LPCWSTR lpServiceName)
	{
		DWORD dwPID = (DWORD)-1;
		SERVICE_STATUS_PROCESS ssStatus;
		SC_HANDLE schSCManager = nullptr;
		SC_HANDLE schService = nullptr;
		DWORD dwBytesNeeded;
		bool bStarted = false;

		// 打开SCM管理器句柄
		schSCManager = OpenSCManagerW(nullptr, nullptr, GENERIC_EXECUTE);
		if (!schSCManager) goto FuncEnd;

		// 打开服务句柄
		schService = OpenServiceW(
			schSCManager, lpServiceName,
			SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
		if (!schService) goto FuncEnd;

		// 查询状态
		while (QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssStatus,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded))
		{
			// 如果服务处于停止状态并且没有调用StartServiceW
			if (ssStatus.dwCurrentState == SERVICE_STOPPED && !bStarted)
			{
				bStarted = true;
				if (StartServiceW(schService, 0, nullptr)) continue;
			}
			// 如果服务在加载和卸载过程中，你需要等待
			else if (ssStatus.dwCurrentState == SERVICE_START_PENDING
				|| ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
			{
				Sleep(ssStatus.dwWaitHint);
				continue;
			}
			// 在其他情况下break
			break;
		}

		// 如果服务启用或正在运行，则返回服务对应进程PID
		if (ssStatus.dwCurrentState != SERVICE_STOPPED &&
			ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
			dwPID = ssStatus.dwProcessId;

	FuncEnd: //退出时关闭句柄并返回

		if (schService) CloseServiceHandle(schService);
		if (schSCManager) CloseServiceHandle(schSCManager);
		return dwPID;
	}

#pragma endregion

	// 忽略未调用变量警告
	template<typename T> void IIntendToIgnoreThisVariable(const T&) {}

	// 转换Win32错误码为HRESULT值
	inline HRESULT ConvertWin32ErrorToHResult(_In_ DWORD dwWin32Error)
	{
		// 如果错误代码为ERROR_SUCCESS, 则转换为非指定的错误
		if (dwWin32Error == ERROR_SUCCESS) return E_FAIL;

		// 如果错误代码已经是HRESULT值，则直接返回
		if (dwWin32Error & 0xFFFF0000) return static_cast<HRESULT>(dwWin32Error);

		// 否则把错误代码转换为HRESULT值
		return static_cast<HRESULT>(
			dwWin32Error | (FACILITY_WIN32 << 16) | 0x80000000);

	}

#ifdef NATIVEAPI

	// 通过直接访问PEB结构获取当前进程模块,以替代GetModuleHandleW(NULL)
	__forceinline HMODULE M2GetCurrentModuleHandle()
	{
		return reinterpret_cast<HMODULE>(NtCurrentPeb()->ImageBaseAddress);
	}

	// 加载dll
	inline NTSTATUS M2LoadDll(
		_In_ LPCWSTR lpDllName,
		_Out_ PVOID &lpDllModule)
	{
		UNICODE_STRING usDllName = { 0 };
		RtlInitUnicodeString(&usDllName, const_cast<PWSTR>(lpDllName));

		return LdrLoadDll(
			nullptr, nullptr, &usDllName, &lpDllModule);
	}

	// 卸载dll
	inline NTSTATUS M2UnloadDll(
		_In_ PVOID pDllModule)
	{
		return (pDllModule ? LdrUnloadDll(pDllModule) : 0);
	}

	// 获取dll函数入口
	template<typename FuncType> inline NTSTATUS M2GetFunc(
		_In_ PVOID lpDllModule,
		_In_ LPSTR lpFuncName,
		_Out_ FuncType &pFuncAddress)
	{
		ANSI_STRING asFuncName = { 0 };
		RtlInitAnsiString(&asFuncName, lpFuncName);

		return LdrGetProcedureAddress(
			lpDllModule, &asFuncName, 0,
			reinterpret_cast<PVOID*>(&pFuncAddress));
	}

#endif

}

#endif