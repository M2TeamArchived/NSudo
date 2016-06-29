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

	// 文件操作
#pragma region FileOperation

	// 判断目录是否是"."或".."
	inline bool IsDots(_In_ LPCWSTR Name)
	{
		// 由于字符可以看作无符号整数,所以L'\0'即0可看作false
		return Name[0] == L'.' && (!Name[1] || (Name[1] == L'.' && !Name[2]));
	}

	// 设置NTFS压缩属性
	static HRESULT _SetNTFSCompaction(_In_ HANDLE FileHandle, _In_ USHORT CompressType)
	{
		DWORD dwError = ERROR_SUCCESS;

#ifdef NATIVELIB
		IO_STATUS_BLOCK IoStatus = { 0 };

		NTSTATUS status = NtFsControlFile(
			FileHandle, nullptr, nullptr, nullptr, &IoStatus,
			FSCTL_SET_COMPRESSION, 
			&CompressType, sizeof(CompressType), nullptr, 0);
		dwError = RtlNtStatusToDosError(status);
#else
		DeviceIoControl(
			FileHandle, 
			FSCTL_SET_COMPRESSION,
			&CompressType, sizeof(CompressType), nullptr, 0,
			nullptr, nullptr);
		dwError = GetLastError();
#endif	

		return HRESULT_FROM_WIN32(dwError);
	}

	// 对指定文件执行NTFS压缩
	inline HRESULT NTFSCompactFile(
		_In_ HANDLE FileHandle)
	{		
		return _SetNTFSCompaction(FileHandle, COMPRESSION_FORMAT_DEFAULT);
	}

	// 对指定文件执行NTFS解压缩
	inline HRESULT NTFSUnCompactFile(
		_In_ HANDLE FileHandle)
	{
		return _SetNTFSCompaction(FileHandle, COMPRESSION_FORMAT_NONE);
	}

#if(_WIN32_WINNT >= _WIN32_WINNT_WIN10)
	enum FileCompressionAlgorithm
	{
		XPRESS4K,
		LZX,
		XPRESS8K,
		XPRESS16K,
		MAXIMUM
	};

	typedef struct _WOF_FILE_EXTERNAL_BACKING_V1
	{
		WOF_EXTERNAL_INFO WofInfo;
		FILE_PROVIDER_EXTERNAL_INFO_V1 FileProviderInfo;
	} WOF_FILE_EXTERNAL_BACKING_V1, *PWOF_FILE_EXTERNAL_BACKING_V1;

	// 对指定文件执行Wof压缩
	static HRESULT WINAPI WofCompactFile(
		_In_ HANDLE FileHandle,
		_In_ DWORD CompactAlgorithm
	)
	{
		WOF_FILE_EXTERNAL_BACKING_V1 WofFileInfo = { 0 };

		WofFileInfo.WofInfo.Version = WOF_CURRENT_VERSION;
		WofFileInfo.WofInfo.Provider = WOF_PROVIDER_FILE;
		WofFileInfo.FileProviderInfo.Version = FILE_PROVIDER_CURRENT_VERSION;
		WofFileInfo.FileProviderInfo.Algorithm = CompactAlgorithm;
		WofFileInfo.FileProviderInfo.Flags = 0;

		DWORD dwError = ERROR_SUCCESS;

#ifdef NATIVELIB
		IO_STATUS_BLOCK IoStatus = { 0 };

		NTSTATUS status = NtFsControlFile(
			FileHandle, nullptr, nullptr, nullptr, &IoStatus,
			FSCTL_SET_EXTERNAL_BACKING, 
			&WofFileInfo, sizeof(WofFileInfo), nullptr, 0);
		dwError = RtlNtStatusToDosError(status);
#else
		DeviceIoControl(
			FileHandle,
			FSCTL_SET_EXTERNAL_BACKING, 
			&WofFileInfo, sizeof(WofFileInfo), nullptr, 0,
			nullptr, nullptr);
		dwError = GetLastError();
#endif	

		return HRESULT_FROM_WIN32(dwError);
	}

	// 对指定文件执行Wof解压缩
	static HRESULT WINAPI WofUnCompactFile(
		_In_ HANDLE FileHandle
	)
	{
		DWORD dwError = ERROR_SUCCESS;

#ifdef NATIVELIB
		IO_STATUS_BLOCK IoStatus = { 0 };

		NTSTATUS status = NtFsControlFile(
			FileHandle, nullptr, nullptr, nullptr, &IoStatus,
			FSCTL_DELETE_EXTERNAL_BACKING,
			nullptr, 0, nullptr, 0);
		dwError = RtlNtStatusToDosError(status);
#else
		DeviceIoControl(
			FileHandle,
			FSCTL_DELETE_EXTERNAL_BACKING,
			nullptr, 0, nullptr, 0,
			nullptr, nullptr);
		dwError = GetLastError();
#endif	

		return HRESULT_FROM_WIN32(dwError);
	}

	// 获取指定文件的Wof压缩算法 (如果文件未压缩或执行失败返回 -1)
	static DWORD WINAPI WofGetFileCompactAlgorithm(
		_In_ HANDLE FileHandle)
	{
		WOF_FILE_EXTERNAL_BACKING_V1 WofFileInfo = { 0 };

		bool bRet = false;

#ifdef NATIVELIB
		IO_STATUS_BLOCK IoStatus = { 0 };

		NTSTATUS status = NtFsControlFile(
			FileHandle, nullptr, nullptr, nullptr, &IoStatus,
			FSCTL_GET_EXTERNAL_BACKING,
			nullptr, 0, &WofFileInfo, sizeof(WofFileInfo));
		bRet = NT_SUCCESS(status);
#else
		bRet = (DeviceIoControl(
			FileHandle,
			FSCTL_GET_EXTERNAL_BACKING,
			nullptr, 0, &WofFileInfo, sizeof(WofFileInfo),
			nullptr, nullptr) != 0);
#endif	

		return !bRet ? -1 : WofFileInfo.FileProviderInfo.Algorithm;
	}

#endif

#ifdef NATIVELIB
	// 文件夹遍历回调函数
	typedef bool(WINAPI *LPCB_ENUM_DIRECTORY)(
		_In_ LPCWSTR lpRootDirectory,
		_In_ PFILE_ID_BOTH_DIR_INFORMATION lpFindData,
		_In_opt_ LPVOID lpParameter);

	// 遍历目录
	static NTSTATUS M2EnumDirectory(
		_In_ LPCWSTR lpFolderName,
		_In_ LPCB_ENUM_DIRECTORY lpCallBackRoutine,
		_In_opt_ LPVOID lpParameter,
		_In_ bool bEnumLower)
	{
		const int nSize = sizeof(FILE_ID_BOTH_DIR_INFORMATION) + MAX_PATH * 2;
		NTSTATUS status = 0;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		wchar_t *szBuffer = nullptr;
		UNICODE_STRING strUnicode = { 0 };
		OBJECT_ATTRIBUTES obAttr = { 0 };
		IO_STATUS_BLOCK objIoStatus = { 0 };
		PFILE_ID_BOTH_DIR_INFORMATION lpFindData = nullptr;

		szBuffer = (wchar_t *)M2AllocMemory((MAX_PATH + 5) * sizeof(wchar_t));
		if (!szBuffer)
		{
			status = STATUS_NO_MEMORY;
			goto FuncEnd;
		}

		_swprintf_c(szBuffer, MAX_PATH + 5, L"\\??\\%s\\", lpFolderName);

		RtlInitUnicodeString(&strUnicode, szBuffer);

		M2InitObjectAttributes(
			&obAttr, &strUnicode, OBJ_CASE_INSENSITIVE, nullptr, nullptr, nullptr);

		// 打开文件夹并获取句柄
		status = NtCreateFile(&hFind,
			FILE_LIST_DIRECTORY | SYNCHRONIZE,
			&obAttr,
			&objIoStatus,
			nullptr,
			0,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			FILE_OPEN,
			FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT | FILE_OPEN_FOR_BACKUP_INTENT,
			nullptr,
			0);
		if (!NT_SUCCESS(status)) goto FuncEnd;

		lpFindData = (PFILE_ID_BOTH_DIR_INFORMATION)M2AllocMemory(nSize);
		if (!lpFindData)
		{
			status = STATUS_NO_MEMORY;
			goto FuncEnd;
		}

		while (true)
		{
			// 遍历目录并获取内容
			status = NtQueryDirectoryFile(
				hFind,
				nullptr,
				nullptr,
				nullptr,
				&objIoStatus,
				lpFindData,
				nSize,
				FileIdBothDirectoryInformation,
				TRUE,
				nullptr,
				FALSE);
			if (!NT_SUCCESS(status)) break;

			// 给文件名添加字符串结束符
			lpFindData->FileName[lpFindData->FileNameLength / 2] = L'\0';

			// 略过"."和".."文件夹
			if (M2::IsDots(lpFindData->FileName)) continue;

			// 如果是目录且不为重解析点(符号链接,Junction)则递归遍历下级目录
			if (bEnumLower &&
				(lpFindData->FileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				!(lpFindData->FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
			{
				_swprintf_c(szBuffer, MAX_PATH + 5,
					L"%s\\%s", lpFolderName, lpFindData->FileName);
				status = M2EnumDirectory(
					szBuffer, lpCallBackRoutine, lpParameter, true);
			}

			// 回调
			if (!lpCallBackRoutine(lpFolderName, lpFindData, lpParameter))
				break;
		}

	FuncEnd:
		if (lpFindData) M2FreeMemory(lpFindData);
		if (szBuffer) M2FreeMemory(szBuffer);

		NtClose(hFind);

		return status;
	}
#endif	

	// 获取文件物理大小
	static UINT64 GetFileAllocationSize(LPCWSTR FilePath)
	{
		HANDLE hFile = CreateFileW(
			FilePath,
			0,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			nullptr,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			nullptr);

		FILE_STANDARD_INFO info = { 0 };

		if (hFile != INVALID_HANDLE_VALUE)
		{
			GetFileInformationByHandleEx(
				hFile, FileStandardInfo, &info, sizeof(info));

			CloseHandle(hFile);
		}

		return info.AllocationSize.QuadPart;
	}

#pragma endregion

	// GUID
#pragma region GUID

	// 粗略判断是否为GUID字符串
	inline bool IsGuidString(wchar_t *lpString)
	{
		return (
			wcslen(lpString) == 38 &&
			lpString[0] == L'{' &&
			lpString[37] == L'}' &&
			lpString[9] == L'-' &&
			lpString[14] == L'-' &&
			lpString[19] == L'-'&&
			lpString[24] == L'-' &&
			lpString[38] == L'\0'
			);
	}

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

	// 字符串
#pragma region String

	// 转换一个字符串为宽字符串（返回的字符串需要用free释放）
	static LPWSTR ToWideString(
		_In_ LPCSTR szString)
	{
		// 获取字符串长度
		int nSize = MultiByteToWideChar(CP_ACP, 0, szString, -1, nullptr, 0);

		// 分配内存块
		wchar_t *szWideString = (wchar_t*)malloc(nSize * sizeof(wchar_t));

		// 如果内存块可用则转换字符串
		if (szWideString)
			MultiByteToWideChar(CP_ACP, 0, szString, -1, szWideString, nSize);

		// 返回转换后的宽字符串
		return szWideString;
	}

	// 数字对应字符的常量定义
	static const wchar_t g_NumChars[] = L"0123456789ABCDEF";

	// 转换数字为字符串
	static void ConvertUInt32ToString(
		_In_ UINT32 value,
		_In_ int base,
		_Out_ LPWSTR string)
	{
		wchar_t temp[31];
		unsigned i = 0;
		while (value >= base)
		{
			temp[i++] = g_NumChars[unsigned(value % base)];
			value /= base;
		}
		*string++ = g_NumChars[value];

		while (i != 0)
		{
			i--;
			*string++ = temp[i];
		}
		*string = L'\0';
	}

#pragma endregion
	
}

#endif