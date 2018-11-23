/******************************************************************************
Project: M2-Team Common Library
Description: Definition for the basic helper functions.
File Name: M2BaseHelpers.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_BASE_HELPERS_
#define _M2_BASE_HELPERS_

#include <Windows.h>

#include <assert.h>
#include <process.h>

#include <map>
#include <string>
#include <vector>

/// <summary>
/// If the type T is a reference type, provides the member typedef type which is
/// the type referred to by T. Otherwise type is T.
/// </summary>
template<class T> struct M2RemoveReference { typedef T Type; };

/// <summary>
/// If the type T is a reference type, provides the member typedef type which is
/// the type referred to by T. Otherwise type is T.
/// </summary>
template<class T> struct M2RemoveReference<T&> { typedef T Type; };

/// <summary>
/// If the type T is a reference type, provides the member typedef type which is
/// the type referred to by T. Otherwise type is T.
/// </summary>
template<class T> struct M2RemoveReference<T&&> { typedef T Type; };

namespace M2
{
	/// <summary>
	/// Disable C++ Object Copying
	/// </summary>
	class CDisableObjectCopying
	{
	protected:
		CDisableObjectCopying() = default;
		~CDisableObjectCopying() = default;

	private:
		CDisableObjectCopying(
			const CDisableObjectCopying&) = delete;
		CDisableObjectCopying& operator=(
			const CDisableObjectCopying&) = delete;
	};

	/// <summary>
	/// The implementation of smart object.
	/// </summary>
	template<typename TObject, typename TObjectDefiner>
	class CObject : CDisableObjectCopying
	{
	protected:
		TObject m_Object;
	public:
		CObject(TObject Object = TObjectDefiner::GetInvalidValue()) :
			m_Object(Object)
		{

		}

		~CObject()
		{
			this->Close();
		}

		TObject* operator&()
		{
			return &this->m_Object;
		}

		TObject operator=(TObject Object)
		{
			if (Object != this->m_Object)
			{
				this->Close();
				this->m_Object = Object;
			}
			return (this->m_Object);
		}

		operator TObject()
		{
			return this->m_Object;
		}

		bool IsInvalid()
		{
			return (this->m_Object == TObjectDefiner::GetInvalidValue());
		}

		TObject Detach()
		{
			TObject Object = this->m_Object;
			this->m_Object = TObjectDefiner::GetInvalidValue();
			return Object;
		}

		void Close()
		{
			if (!this->IsInvalid())
			{
				TObjectDefiner::Close(this->m_Object);
				this->m_Object = TObjectDefiner::GetInvalidValue();
			}
		}

		TObject operator->() const
		{
			return this->m_Object;
		}
	};

	/// <summary>
	/// The handle definer for HANDLE object.
	/// </summary>
#pragma region CHandle

	struct CHandleDefiner
	{
		static inline HANDLE GetInvalidValue()
		{
			return INVALID_HANDLE_VALUE;
		}

		static inline void Close(HANDLE Object)
		{
			CloseHandle(Object);
		}
	};

	typedef CObject<HANDLE, CHandleDefiner> CHandle;

#pragma endregion

	/// <summary>
	/// The handle definer for COM object.
	/// </summary>
#pragma region CComObject

	template<typename TComObject>
	struct CComObjectDefiner
	{
		static inline TComObject GetInvalidValue()
		{
			return nullptr;
		}

		static inline void Close(TComObject Object)
		{
			Object->Release();
		}
	};

	template<typename TComObject>
	class CComObject : public CObject<TComObject, CComObjectDefiner<TComObject>>
	{

	};

#pragma endregion

	/// <summary>
	/// The handle definer for memory block.
	/// </summary>
#pragma region CMemory

	template<typename TMemory>
	struct CMemoryDefiner
	{
		static inline TMemory GetInvalidValue()
		{
			return nullptr;
		}

		static inline void Close(TMemory Object)
		{
			free(Object);
		}
	};

	template<typename TMemory>
	class CMemory : public CObject<TMemory, CMemoryDefiner<TMemory>>
	{
	public:
		CMemory(TMemory Object = CMemoryDefiner<TMemory>::GetInvalidValue()) :
			CObject<TMemory, CMemoryDefiner<TMemory>>(Object)
		{

		}

		bool Alloc(size_t Size)
		{
			this->Free();
			return (this->m_Object = reinterpret_cast<TMemory>(malloc(Size)));
		}

		void Free()
		{
			this->Close();
		}
	};

#pragma endregion

	/// <summary>
	/// The implementation of thread.
	/// </summary>
	class CThread
	{
	private:
		HANDLE CreateThreadInternal(
			_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
			_In_ SIZE_T dwStackSize,
			_In_ LPTHREAD_START_ROUTINE lpStartAddress,
			_In_opt_ __drv_aliasesMem LPVOID lpParameter,
			_In_ DWORD dwCreationFlags,
			_Out_opt_ LPDWORD lpThreadId)
		{
			// sanity check for lpThreadId
			assert(sizeof(DWORD) == sizeof(unsigned));

			typedef unsigned(__stdcall* routine_type)(void*);

			// _beginthreadex calls CreateThread which will set the last error
			// value before it returns.
			return reinterpret_cast<HANDLE>(_beginthreadex(
				lpThreadAttributes,
				static_cast<unsigned>(dwStackSize),
				reinterpret_cast<routine_type>(lpStartAddress),
				lpParameter,
				dwCreationFlags,
				reinterpret_cast<unsigned*>(lpThreadId)));
		}

		CHandle m_Thread;

	public:
		CThread() = default;

		template<class TFunction>
		CThread(
			_In_ TFunction&& workerFunction,
			_In_ DWORD dwCreationFlags = 0)
		{
			auto ThreadFunctionInternal = [](LPVOID lpThreadParameter) -> DWORD
			{
				auto function = reinterpret_cast<TFunction*>(
					lpThreadParameter);
				(*function)();
				delete function;
				return 0;
			};

			this->m_Thread = CreateThreadInternal(
				nullptr,
				0,
				ThreadFunctionInternal,
				reinterpret_cast<void*>(
					new TFunction(std::move(workerFunction))),
				dwCreationFlags,
				nullptr);
		}

		HANDLE Detach()
		{
			return this->m_Thread.Detach();
		}

		DWORD Resume()
		{
			return ResumeThread(this->m_Thread);
		}

		DWORD Suspend()
		{
			return SuspendThread(this->m_Thread);
		}

		DWORD Wait(
			_In_ DWORD dwMilliseconds = INFINITE,
			_In_ BOOL bAlertable = FALSE)
		{
			return WaitForSingleObjectEx(
				this->m_Thread, dwMilliseconds, bAlertable);
		}

	};

	/// <summary>
	/// Wraps a critical section.
	/// </summary>
	class CCriticalSection
	{
	private:
		CRITICAL_SECTION m_CriticalSection;

	public:
		CCriticalSection()
		{
			InitializeCriticalSection(&this->m_CriticalSection);
		}

		~CCriticalSection()
		{
			DeleteCriticalSection(&this->m_CriticalSection);
		}

		_Acquires_lock_(m_CriticalSection) void Lock()
		{
			EnterCriticalSection(&this->m_CriticalSection);
		}
	
		_Releases_lock_(m_CriticalSection) void Unlock()
		{
			LeaveCriticalSection(&this->m_CriticalSection);
		}
	};

	/// <summary>
	/// Provides automatic locking and unlocking of a critical section.
	/// </summary>
	/// <remarks>
	/// The AutoLock object must go out of scope before the CritSec.
	/// </remarks>
	class AutoCriticalSectionLock
	{
	private:
		CCriticalSection* m_pCriticalSection;

	public:
		_Acquires_lock_(m_pCriticalSection) AutoCriticalSectionLock(
			CCriticalSection& CriticalSection)
		{
			m_pCriticalSection = &CriticalSection;
			m_pCriticalSection->Lock();
		}

		_Releases_lock_(m_pCriticalSection) ~AutoCriticalSectionLock()
		{
			m_pCriticalSection->Unlock();
		}
	};

	/// <summary>
	/// A template for implementing an object which the type is a singleton. I
	/// do not need to free the memory of the object because the OS releases all
	/// the unshared memory associated with the process after the process is
	/// terminated.
	/// </summary>
	template<class ClassType>
	class CSingleton : CDisableObjectCopying
	{
	private:
		static CCriticalSection m_SingletonCS;
		static ClassType* volatile m_Instance = nullptr;

	protected:
		CSingleton() = default;
		~CSingleton() = default;

	public:	
		static ClassType& Get()
		{
			M2::AutoCriticalSectionLock Lock(this->m_SingletonCS);

			if (nullptr == this->m_Instance)
			{
				this->m_Instance = new ClassType();
			}

			return *this->m_Instance;
		}
	};

}
 
/// <summary>
/// Retrieves the number of logical processors in the current group.
/// </summary>
/// <returns>
/// Return the number of logical processors in the current group.
/// </returns>
inline DWORD M2GetNumberOfHardwareThreads()
{
	SYSTEM_INFO SystemInfo = { 0 };
	GetNativeSystemInfo(&SystemInfo);
	return SystemInfo.dwNumberOfProcessors;
}

/// <summary>
/// Write formatted data to a string.
/// </summary>
/// <param name="Format">
/// Format-control string.
/// </param>
/// <param name="...">
/// Optional arguments to be formatted.
/// </param>
/// <returns>
/// Returns a formatted string if successful, or "N/A" otherwise.
/// </returns>
std::wstring M2FormatString(
	_In_z_ _Printf_format_string_ wchar_t const* const Format,
	...);

/// <summary>
/// Retrieves the number of milliseconds that have elapsed since the system was
/// started.
/// </summary>
/// <returns>
/// The number of milliseconds.
/// </returns>
ULONGLONG M2GetTickCount();

/// <summary>
/// Searches a path for a file name.
/// </summary>
/// <param name="Path">
/// A pointer to a null-terminated string of maximum length MAX_PATH that
/// contains the path to search.
/// </param>
/// <returns>
/// Returns a pointer to the address of the string if successful, or a pointer
/// to the beginning of the path otherwise.
/// </returns>
template<typename CharType>
CharType M2PathFindFileName(CharType Path)
{
	CharType FileName = Path;

	for (size_t i = 0; i < MAX_PATH; ++i)
	{
		if (!(Path && *Path))
			break;

		if (L'\\' == *Path || L'/' == *Path)
			FileName = Path + 1;

		++Path;
	}

	return FileName;
}
 
/// <summary>
/// Converts from the UTF-8 string to the UTF-16 string.
/// </summary>
/// <param name="UTF8String">
/// The UTF-8 string you want to convert.
/// </param>
/// <returns>
/// The return value is the UTF-16 string.
/// </returns>
std::wstring M2MakeUTF16String(const std::string& UTF8String);
 
/// <summary>
/// Converts from the UTF-16 string to the UTF-8 string.
/// </summary>
/// <param name="UTF16String">
/// The UTF-16 string you want to convert.
/// </param>
/// <returns>
/// The return value is the UTF-8 string.
/// </returns>
std::string M2MakeUTF8String(const std::wstring& UTF16String);
  
/// <summary>
/// Retrieves the calling thread's last-error code value. The last-error code is
/// maintained on a per-thread basis. Multiple threads do not overwrite each
/// other's last-error code.
/// </summary>
/// <returns>
/// The return value is the calling thread's last-error code which is converted
/// to an HRESULT value.
/// </returns>
HRESULT M2GetLastError();
 
/// <summary>
/// Retrieves the address of an exported function or variable from the specified
/// dynamic-link library (DLL).
/// </summary>
/// <param name="lpProcAddress">
/// The address of the exported function or variable.
/// </param>
/// <param name="hModule">
/// A handle to the DLL module that contains the function or variable. The
/// LoadLibrary, LoadLibraryEx, LoadPackagedLibrary, or GetModuleHandle function
/// returns this handle. This function does not retrieve addresses from modules
/// that were loaded using the LOAD_LIBRARY_AS_DATAFILE flag. For more
/// information, see LoadLibraryEx.
/// </param>
/// <param name="lpProcName">
/// The function or variable name, or the function's ordinal value. If this
/// parameter is an ordinal value, it must be in the low-order word; the
/// high-order word must be zero.
/// </param>
/// <returns>
/// The function will return HRESULT. If the function succeeds, the return value
/// is S_OK.
/// </returns>
template<typename ProcedureType>
inline HRESULT M2GetProcAddress(
	_Out_ ProcedureType& lpProcAddress,
	_In_ HMODULE hModule,
	_In_ LPCSTR lpProcName)
{
	HRESULT M2GetProcAddress(
		_Out_ FARPROC& lpProcAddress,
		_In_ HMODULE hModule,
		_In_ LPCSTR lpProcName);

	return M2GetProcAddress(
		reinterpret_cast<FARPROC&>(lpProcAddress), hModule, lpProcName);
}
 
/// <summary>
/// Retrieves the path of the executable file of the current process.
/// </summary>
/// <returns>
/// If the function succeeds, the return value is the path of the executable
/// file of the current process. If the function fails, the return value is an
/// empty string.
/// </returns>
std::wstring M2GetCurrentProcessModulePath();

/// <summary>
/// Parses a command line string and returns an array of the command line
/// arguments, along with a count of such arguments, in a way that is similar to
/// the standard C run-time.
/// </summary>
/// <param name="CommandLine">
/// A string that contains the full command line. If this parameter is an empty
/// string the function returns an array with only one empty string.
/// </param>
/// <returns>
/// The return value is an array of the command line arguments, along with a
/// count of such arguments.
/// </returns>
std::vector<std::wstring> M2SpiltCommandLine(
	const std::wstring& CommandLine);

/// <summary>
/// Parses a command line string and get more friendly result.
/// </summary>
/// <param name="CommandLine">
/// A string that contains the full command line. If this parameter is an empty
/// string the function returns an array with only one empty string.
/// </param>
/// <param name="OptionPrefixes">
/// One or more of the prefixes of option we want to use.
/// </param>
/// <param name="OptionParameterSeparators">
/// One or more of the separators of option we want to use.
/// </param>
/// <param name="ApplicationName">
/// The application name.
/// </param>
/// <param name="OptionsAndParameters">
/// The options and parameters.
/// </param>
/// <param name="UnresolvedCommandLine">
/// The unresolved command line.
/// </param>
void M2SpiltCommandLineEx(
	const std::wstring& CommandLine,
	const std::vector<std::wstring>& OptionPrefixes,
	const std::vector<std::wstring>& OptionParameterSeparators,
	std::wstring& ApplicationName,
	std::map<std::wstring, std::wstring>& OptionsAndParameters,
	std::wstring& UnresolvedCommandLine);

#endif // _M2_BASE_HELPERS_
