/**************************************************************************
描述：基本库(有些是对M2.Native的封装)
维护者：Mouri_Naruto (M2-Team)
版本：1.0 (2016-06-25)
基于项目：无
协议：The MIT License
用法：直接Include此头文件即可(前提你要在这之前Include Windows.h)
建议的Windows SDK版本：10.0.10586及以后
***************************************************************************/

#pragma once

#ifndef M2_BASE
#define M2_BASE

namespace M2
{
	// 本机API内联调用(M2-Team编写的)
#ifdef NATIVELIB
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
		_In_ PUNICODE_STRING ObjectName,
		_In_ ULONG Attributes,
		_In_ HANDLE RootDirectory,
		_In_ PVOID SecurityDescriptor,
		_In_ PVOID SecurityQualityOfService)
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
#endif

	// 堆
#pragma region Heap

	// 在当前堆上分配内存
	inline void* M2AllocMemory(
		_In_ size_t Size)
	{
#ifdef NATIVELIB
		return RtlAllocateHeap(RtlProcessHeap(), 0, Size);
#else
		return malloc(Size);
#endif
	}

	// 在当前堆上释放内存
	inline void M2FreeMemory(
		_In_ void* BaseAddress)
	{
#ifdef NATIVELIB
		RtlFreeHeap(RtlProcessHeap(), 0, BaseAddress);
#else
		free(BaseAddress);
#endif
		BaseAddress = nullptr;
	}

	// 内存指针模板类
	template<typename PtrType> class CPtr
	{
	public:
		// 分配内存
		bool Alloc(_In_ size_t Size)
		{
			if (m_Ptr) this->Free();
			m_Ptr = M2AllocMemory(Size);
			return (m_Ptr != nullptr);
		}

		// 释放内存
		void Free()
		{
			M2FreeMemory(m_Ptr);
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
		DWORD dwPID = -1;
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
	
}

#endif