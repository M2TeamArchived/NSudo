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

#include <string>

// If the type T is a reference type, provides the member typedef type which is
// the type referred to by T. Otherwise type is T.
template<class T> struct M2RemoveReference { typedef T Type; };
template<class T> struct M2RemoveReference<T&> { typedef T Type; };
template<class T> struct M2RemoveReference<T&&> { typedef T Type; };

namespace M2
{
	// Disable C++ Object Copying
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

	// The implementation of smart object.
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

		// Check the object is vaild or not.
		bool IsInvalid()
		{
			return (this->m_Object == TObjectDefiner::GetInvalidValue());
		}

		// Detach the object.
		TObject Detach()
		{
			TObject Object = this->m_Object;
			this->m_Object = TObjectDefiner::GetInvalidValue();
			return Object;
		}

		// Close the object.
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

	// The handle definer for HANDLE object.
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

	// The handle definer for COM object.
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

	// The handle definer for memory block.
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

	// The implementation of thread.
	class CThread
	{
	private:
		// Internal implemention for creating the thread.
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

		// The thread object.
		CHandle m_Thread;

	public:
		CThread()
		{

		}

		// Create the thread.
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

		// Detach the thread object.
		HANDLE Detach()
		{
			return this->m_Thread.Detach();
		}

		// Resume the thread.
		DWORD Resume()
		{
			return ResumeThread(this->m_Thread);
		}

		// Suspend the thread.
		DWORD Suspend()
		{
			return SuspendThread(this->m_Thread);
		}

		// Wait the thread.
		DWORD Wait(
			_In_ DWORD dwMilliseconds = INFINITE,
			_In_ BOOL bAlertable = FALSE)
		{
			return WaitForSingleObjectEx(
				this->m_Thread, dwMilliseconds, bAlertable);
		}

	};

	// Wraps a critical section
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

	// Provides automatic locking and unlocking of a critical section.
	// Note: The AutoLock object must go out of scope before the CritSec.
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

}

// Retrieves the number of logical processors in the current group. 
// Parameters:
//   The function does not have parameters.
// Return value:
//   Return the number of logical processors in the current group.
inline DWORD M2GetNumberOfHardwareThreads()
{
	SYSTEM_INFO SystemInfo = { 0 };
	GetNativeSystemInfo(&SystemInfo);
	return SystemInfo.dwNumberOfProcessors;
}

// Write formatted data to a string. 
// Parameters:
//   Format: Format-control string.
//   ...: Optional arguments to be formatted.
// Return value:
//   Returns a formatted string if successful, or "N/A" otherwise.
std::wstring M2FormatString(
	_In_z_ _Printf_format_string_ wchar_t const* const Format,
	...);

// Retrieves the number of milliseconds that have elapsed since the system was
// started.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The number of milliseconds.
ULONGLONG M2GetTickCount();

// Searches a path for a file name.
// Parameters:
//   Path: A pointer to a null-terminated string of maximum length MAX_PATH 
//   that contains the path to search.
// Return value:
//   Returns a pointer to the address of the string if successful, or a pointer
//   to the beginning of the path otherwise.
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

// Converts from the UTF-8 string to the UTF-16 string.
// Parameters:
//   UTF8String: The UTF-8 string you want to convert.
// Return value:
//   The return value is the UTF-16 string.
std::wstring M2MakeUTF16String(const std::string& UTF8String);

// Converts from the UTF-16 string to the UTF-8 string.
// Parameters:
//   UTF16String: The UTF-16 string you want to convert.
// Return value:
//   The return value is the UTF-8 string.
std::string M2MakeUTF8String(const std::wstring& UTF16String);

// Retrieves the calling thread's last-error code value. The last-error code is
// maintained on a per-thread basis. Multiple threads do not overwrite each 
// other's last-error code.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The return value is the calling thread's last-error code which is 
//   converted to an HRESULT value.
HRESULT M2GetLastError();

// Retrieves the address of an exported function or variable from the specified
// dynamic-link library (DLL).
// Parameters:
//   lpProcAddress: The address of the exported function or variable
//   hModule: A handle to the DLL module that contains the function or 
//   variable. The LoadLibrary, LoadLibraryEx, LoadPackagedLibrary, or 
//   GetModuleHandle function returns this handle. This function does not 
//   retrieve addresses from modules that were loaded using the 
//   LOAD_LIBRARY_AS_DATAFILE flag.For more information, see LoadLibraryEx.
//   lpProcName: The function or variable name, or the function's ordinal 
//   value. If this parameter is an ordinal value, it must be in the low-order
//   word; the high-order word must be zero.
// Return value:
//   The function will return HRESULT. If the function succeeds, the return 
//   value is S_OK.
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

#endif // _M2_BASE_HELPERS_
