/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsHelpers.cpp
 * PURPOSE:   Implementation for the Windows helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "M2WindowsHelpers.h"

#include "Mile.Windows.h"

#ifdef _M2_WINDOWS_HELPERS_

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#include <VersionHelpers.h>
#endif

#include <strsafe.h>

#ifdef __cplusplus_winrt
#include <wrl\client.h>
#include <wrl\implements.h>
#include <robuffer.h>

#include <windows.foundation.h>
#include <windows.storage.streams.h>

#include <string>

using Microsoft::WRL::ComPtr;
using Microsoft::WRL::MakeAndInitialize;
using Microsoft::WRL::RuntimeClass;
using Microsoft::WRL::RuntimeClassFlags;
using Microsoft::WRL::RuntimeClassType;
#endif

#pragma region Error

#ifdef __cplusplus_winrt

/**
 * Throw the appropriate Platform::Exception for the given HRESULT.
 *
 * @param hr The error HRESULT that is represented by the exception.
 * @return This function does not return a value, but will throw
 *         Platform::Exception.
 */
__declspec(noreturn) void M2ThrowPlatformException(HRESULT hr)
{
    throw Platform::Exception::CreateException(hr);
}

/**
 * Throw the appropriate Platform::Exception for the given HRESULT.
 *
 * @param hr The error HRESULT that is represented by the exception.
 * @return This function does not return a value, but will throw
 *         Platform::Exception if it is a failed HRESULT value.
 */
void M2ThrowPlatformExceptionIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        M2ThrowPlatformException(hr);
    }
}

/**
 * Convert C++/CX exceptions in the callable code into HRESULTs.
 *
 * @return The function will return HRESULT.
 */
HRESULT M2ThrownPlatformExceptionToHResult()
{
    try
    {
        throw;
    }
    catch (Platform::Exception^ ex)
    {
        return ex->HResult;
    }
    catch (std::bad_alloc const&)
    {
        return E_OUTOFMEMORY;
    }
    catch (...)
    {
        return E_UNEXPECTED;
    }
}

#endif

#pragma endregion

#pragma region String

/**
 * Write formatted data to a string.
 *
 * @param Format Format-control string.
 * @param ... Optional arguments to be formatted.
 * @return A formatted string if successful, "N/A" otherwise.
 */
std::wstring M2FormatString(
    _In_z_ _Printf_format_string_ wchar_t const* const Format,
    ...)
{
    // Check the argument list.
    if (nullptr != Format)
    {
        va_list ArgList = nullptr;
        va_start(ArgList, Format);

        // Get the length of the format result.
        size_t nLength = static_cast<size_t>(_vscwprintf(Format, ArgList)) + 1;

        // Allocate for the format result.
        std::wstring Buffer(nLength + 1, L'\0');

        // Format the string.
        int nWritten = _vsnwprintf_s(
            &Buffer[0],
            Buffer.size(),
            nLength,
            Format,
            ArgList);

        va_end(ArgList);

        if (nWritten > 0)
        {
            // If succeed, resize to fit and return result.
            Buffer.resize(nWritten);
            return Buffer;
        }
    }

    // If failed, return "N/A".
    return L"N/A";
}

#ifdef CPPWINRT_VERSION

/**
 * Finds a sub string from a source string.
 *
 * @param SourceString The source string.
 * @param SubString The sub string.
 * @param IgnoreCase Determines whether to ignore case.
 * @return Returns true if successful, or false otherwise.
 */
bool M2FindSubString(
    winrt::hstring const& SourceString,
    winrt::hstring const& SubString,
    bool IgnoreCase)
{
    return (::FindNLSStringEx(
        nullptr,
        (IgnoreCase ? NORM_IGNORECASE : 0) | FIND_FROMSTART,
        SourceString.c_str(),
        SourceString.size(),
        SubString.c_str(),
        SubString.size(),
        nullptr,
        nullptr,
        nullptr,
        0) >= 0);
}

/**
 * Converts a numeric value into a string that represents the number expressed
 * as a size value in byte, bytes, kibibytes, mebibytes, gibibytes, tebibytes,
 * pebibytes or exbibytes, depending on the size.
 *
 * @param ByteSize The numeric byte size value to be converted.
 * @return Returns a winrt::hstring object which represents the converted
 *         string.
 */
winrt::hstring M2ConvertByteSizeToString(
    uint64_t ByteSize)
{
    const wchar_t* Systems[] =
    {
        L"Byte",
        L"Bytes",
        L"KiB",
        L"MiB",
        L"GiB",
        L"TiB",
        L"PiB",
        L"EiB"
    };

    size_t nSystem = 0;
    double result = static_cast<double>(ByteSize);

    if (ByteSize > 1)
    {
        for (
            nSystem = 1;
            nSystem < sizeof(Systems) / sizeof(*Systems);
            ++nSystem)
        {
            if (1024.0 > result)
                break;

            result /= 1024.0;
        }

        result = static_cast<uint64_t>(result * 100) / 100.0;
    }

    return winrt::to_hstring(result) + L" " + Systems[nSystem];
}

#endif

#ifdef __cplusplus_winrt

/**
 * Converts from the C++/CX string to the UTF-16 string.
 *
 * @param PlatformString The C++/CX string you want to convert.
 * @return The return value is the UTF-16 string.
 */
std::wstring M2MakeUTF16String(Platform::String^ PlatformString)
{
    return std::wstring(PlatformString->Data(), PlatformString->Length());
}

/**
 * Converts from the C++/CX string to the UTF-8 string.
 *
 * @param PlatformString The C++/CX string you want to convert.
 * @return The return value is the UTF-8 string.
 */
std::string M2MakeUTF8String(Platform::String^ PlatformString)
{
    std::string UTF8String;

    int UTF8StringLength = 0;
    HRESULT hr = ::MileWideCharToMultiByte(
        CP_UTF8,
        0,
        PlatformString->Data(),
        static_cast<int>(PlatformString->Length()),
        nullptr,
        0,
        nullptr,
        nullptr,
        &UTF8StringLength);
    if (SUCCEEDED(hr))
    {
        UTF8String.resize(UTF8StringLength);
        ::MileWideCharToMultiByte(
            CP_UTF8,
            0,
            PlatformString->Data(),
            static_cast<int>(PlatformString->Length()),
            &UTF8String[0],
            UTF8StringLength,
            nullptr,
            nullptr,
            nullptr);
    }

    return UTF8String;
}

/**
 * Converts from the UTF-8 string to the C++/CX string.
 *
 * @param UTF16String The UTF-16 string you want to convert.
 * @return The return value is the C++/CX string.
 */
Platform::String^ M2MakeCXString(const std::wstring& UTF16String)
{
    return ref new Platform::String(
        UTF16String.c_str(), static_cast<unsigned int>(UTF16String.size()));
}

/**
 * Finds a sub string from a source string.
 *
 * @param SourceString The source string.
 * @param SubString The sub string.
 * @param IgnoreCase Determines whether to ignore case.
 * @return Returns true if successful, or false otherwise.
 */
bool M2FindSubString(
    Platform::String^ SourceString,
    Platform::String^ SubString,
    bool IgnoreCase)
{
    return (::FindNLSStringEx(
        nullptr,
        (IgnoreCase ? NORM_IGNORECASE : 0) | FIND_FROMSTART,
        SourceString->Data(),
        SourceString->Length(),
        SubString->Data(),
        SubString->Length(),
        nullptr,
        nullptr,
        nullptr,
        0) >= 0);
}

/**
 * Converts a numeric value into a string that represents the number expressed
 * as a size value in byte, bytes, kibibytes, mebibytes, gibibytes, tebibytes,
 * pebibytes or exbibytes, depending on the size.
 *
 * @param ByteSize The numeric byte size value to be converted.
 * @return Returns a Platform::String object which represents the converted
 *         string.
 */
Platform::String^ M2ConvertByteSizeToString(uint64 ByteSize)
{
    double result = static_cast<double>(ByteSize);

    if (0.0 == result)
    {
        return L"0 Byte";
    }

    const wchar_t* Systems[] =
    {
        L"Bytes",
        L"KiB",
        L"MiB",
        L"GiB",
        L"TiB",
        L"PiB",
        L"EiB"
    };

    size_t nSystem = 0;
    for (; nSystem < sizeof(Systems) / sizeof(*Systems); ++nSystem)
    {
        if (1024.0 > result)
            break;

        result /= 1024.0;
    }

    Platform::String^ ByteSizeString =
        (static_cast<uint64>(result * 100) / 100.0).ToString();

    return ByteSizeString + Platform::StringReference(Systems[nSystem]);
}

#endif

#pragma endregion

#pragma region COM

#ifdef CPPWINRT_VERSION

/**
 * Creates a GUID, a unique 128-bit integer used for CLSIDs and interface
 * identifiers.
 *
 * @return The function will return GUID struct.
 */
GUID M2CreateGuid()
{
    GUID guid = { 0 };
    winrt::check_hresult(CoCreateGuid(&guid));
    return guid;
}

#endif

#ifdef __cplusplus_winrt

/**
 * Retrieves the raw pointer from the provided IBuffer object.
 *
 * @param Buffer The IBuffer object you want to retrieve the raw pointer.
 * @return If the function succeeds, the return value is the raw pointer from
 *         the provided IBuffer object. If the function fails, the return value
 *         is nullptr.
 * @remark The lifetime of the returned buffer is controlled by the lifetime of
 *         the buffer object that's passed to this method. When the buffer has
 *         been released, the pointer becomes invalid and must not be used.
 */
byte* M2GetPointer(Windows::Storage::Streams::IBuffer^ Buffer)
{
    byte* pBuffer = nullptr;
    Windows::Storage::Streams::IBufferByteAccess* pBufferByteAccess = nullptr;
    IInspectable* pBufferABIObject = M2GetInspectable(Buffer);
    if (SUCCEEDED(pBufferABIObject->QueryInterface(&pBufferByteAccess)))
    {
        pBufferByteAccess->Buffer(&pBuffer);
        pBufferByteAccess->Release();
    }

    return pBuffer;
}

class BufferReference : public RuntimeClass<
    RuntimeClassFlags<RuntimeClassType::WinRtClassicComMix>,
    ABI::Windows::Storage::Streams::IBuffer,
    Windows::Storage::Streams::IBufferByteAccess>
{
private:
    UINT32 m_Capacity;
    UINT32 m_Length;
    byte* m_Pointer;

public:
    virtual ~BufferReference()
    {
    }

    STDMETHODIMP RuntimeClassInitialize(
        byte* Pointer, UINT32 Capacity)
    {
        m_Capacity = Capacity;
        m_Length = Capacity;
        m_Pointer = Pointer;
        return S_OK;
    }

    // IBufferByteAccess::Buffer
    STDMETHODIMP Buffer(byte** value)
    {
        *value = m_Pointer;
        return S_OK;
    }

    // IBuffer::get_Capacity
    STDMETHODIMP get_Capacity(UINT32* value)
    {
        *value = m_Capacity;
        return S_OK;
    }

    // IBuffer::get_Length
    STDMETHODIMP get_Length(UINT32* value)
    {
        *value = m_Length;
        return S_OK;
    }

    // IBuffer::put_Length
    STDMETHODIMP put_Length(UINT32 value)
    {
        if (value > m_Capacity)
            return E_INVALIDARG;
        m_Length = value;
        return S_OK;
    }
};

// Retrieves the IBuffer object from the provided raw pointer.
// Parameters:
//   Pointer: The raw pointer you want to retrieve the IBuffer object.
//   Capacity: The size of raw pointer you want to retrieve the IBuffer object.
// Return value:
//   If the function succeeds, the return value is the IBuffer object from the 
//   provided raw pointer. If the function fails, the return value is nullptr.
// Warning: 
//   The lifetime of the returned IBuffer object is controlled by the lifetime 
//   of the raw pointer that's passed to this method. When the raw pointer has 
//   been released, the IBuffer object becomes invalid and must not be used.
Windows::Storage::Streams::IBuffer^ M2MakeIBuffer(
    byte* Pointer,
    UINT32 Capacity)
{
    using Windows::Storage::Streams::IBuffer;

    IBuffer^ buffer = nullptr;

    ComPtr<BufferReference> bufferReference;
    if (SUCCEEDED(MakeAndInitialize<BufferReference>(
        &bufferReference, Pointer, Capacity)))
    {
        buffer = reinterpret_cast<IBuffer^>(bufferReference.Get());
    }

    return buffer;
}

/**
 * Creates a GUID, a unique 128-bit integer used for CLSIDs and interface
 * identifiers.
 *
 * @return The function will return Platform::Guid object.
 */
Platform::Guid M2CreateGuid()
{
    GUID guid = { 0 };
    M2ThrowPlatformExceptionIfFailed(CoCreateGuid(&guid));
    return Platform::Guid(guid);
}

#endif

#pragma endregion

#pragma region Environment

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Enables the Per-Monitor DPI Aware for the specified dialog using the
 * internal API from Windows.
 *
 * @return INT. If failed. returns -1.
 * @remarks You need to use this function in Windows 10 Threshold 1 or Windows
 *          10 Threshold 2.
 */
INT M2EnablePerMonitorDialogScaling()
{
    // This hack is only for Windows 10 only.
    if (!::IsWindowsVersionOrGreater(10, 0, 0))
    {
        return -1;
    }

    // We don't need this hack if the Per Monitor Aware V2 is existed.
    OSVERSIONINFOEXW OSVersionInfoEx = { 0 };
    OSVersionInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
    OSVersionInfoEx.dwBuildNumber = 14393;
    if (::VerifyVersionInfoW(
        &OSVersionInfoEx,
        VER_BUILDNUMBER,
        ::VerSetConditionMask(0, VER_BUILDNUMBER, VER_GREATER_EQUAL)))
    {
        return -1;
    }

    HMODULE ModuleHandle = ::GetModuleHandleW(L"user32.dll");
    if (!ModuleHandle)
    {
        return -1;
    }

    typedef INT(WINAPI* ProcType)();

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetProcAddress(ModuleHandle, reinterpret_cast<LPCSTR>(2577)));
    if (!ProcAddress)
    {
        return -1;
    }
    
    return ProcAddress();
}

#endif

#pragma endregion

#pragma region WinRT

#ifdef CPPWINRT_VERSION

/**
 * Execute function on the UI thread with normal priority.
 *
 * @param agileCallback The function you want to execute.
 * @return The return value is Windows::Foundation::IAsyncAction^.
 */
winrt::IAsyncAction M2ExecuteOnUIThread(
    winrt::DispatchedHandler const& agileCallback)
{
    using winrt::Windows::ApplicationModel::Core::CoreApplication;
    using winrt::Windows::UI::Core::CoreDispatcherPriority;

    return CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(
        CoreDispatcherPriority::Normal, agileCallback);
}

namespace M2
{
    void NotifyPropertyChangedBase::RaisePropertyChanged(
        std::wstring_view const& PropertyName)
    {
        this->m_PropertyChanged(
            *this, winrt::PropertyChangedEventArgs(PropertyName));
    }

    winrt::event_token NotifyPropertyChangedBase::PropertyChanged(
        winrt::PropertyChangedEventHandler const& value)
    {
        return this->m_PropertyChanged.add(value);
    }

    void NotifyPropertyChangedBase::PropertyChanged(
        winrt::event_token const& token)
    {
        this->m_PropertyChanged.remove(token);
    }
}

#endif

#ifdef __cplusplus_winrt

/**
 * Handle the completed asynchronous call.
 *
 * @param Async The completed asynchronous call you want to handle.
 * @return Return the HRESULT determined by the asynchronous call.
 */
HRESULT M2AsyncHandleCompleted(Platform::Object^ Async)
{
    HRESULT hr = S_OK;
    ABI::Windows::Foundation::IAsyncInfo* asyncInfo = nullptr;

    hr = M2GetInspectable(Async)->QueryInterface(&asyncInfo);
    if (SUCCEEDED(hr))
    {
        // Get the error code.
        AsyncStatus asyncStatus;
        hr = asyncInfo->get_Status(&asyncStatus);
        if (SUCCEEDED(hr))
        {
            if (AsyncStatus::Completed == asyncStatus)
            {
                // Just return S_OK if succeeded.
                hr = S_OK;
            }
            else if (AsyncStatus::Started == asyncStatus)
            {
                // Cancel the asynchronous call and return error code if 
                // the status is still Started, the timeout interval has
                // been elapsed.
                hr = asyncInfo->Cancel();
                if (SUCCEEDED(hr)) hr = __HRESULT_FROM_WIN32(ERROR_TIMEOUT);
            }
            else if (AsyncStatus::Canceled == asyncStatus)
            {
                // If the status is Cancelled, return the error code.
                hr = E_ABORT;
            }
            else
            {
                HRESULT hrTemp;

                // If the status is other value, return the error code.	
                hr = asyncInfo->get_ErrorCode(&hrTemp);
                if (SUCCEEDED(hr)) hr = hrTemp;
            }
        }

        asyncInfo->Release();
    }

    return hr;
}

/**
 * Execute function on the UI thread with normal priority.
 *
 * @param agileCallback The function you want to execute.
 * @return The return value is Windows::Foundation::IAsyncAction^.
 */
Windows::Foundation::IAsyncAction^ M2ExecuteOnUIThread(
    Windows::UI::Core::DispatchedHandler^ agileCallback)
{
    using Windows::ApplicationModel::Core::CoreApplication;
    using Windows::UI::Core::CoreDispatcherPriority;

    return CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
        CoreDispatcherPriority::Normal, agileCallback);
}

#endif

#pragma endregion

#endif // _M2_WINDOWS_HELPERS_
