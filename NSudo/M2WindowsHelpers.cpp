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

#include <Mile.Windows.h>

#ifdef _M2_WINDOWS_BASE_EXTENDED_HELPERS_

DWORD M2GetLastWin32Error(
    _In_ BOOL IsLastFunctionCallSucceeded,
    _In_ BOOL UseLastErrorWhenSucceeded)
{
    if (IsLastFunctionCallSucceeded && !UseLastErrorWhenSucceeded)
        return ERROR_SUCCESS;

    DWORD LastError = GetLastError();

    if (!IsLastFunctionCallSucceeded && ERROR_SUCCESS == LastError)
        return ERROR_FUNCTION_FAILED;

    return LastError;
}

HRESULT M2GetLastHResultError(
    _In_ BOOL IsLastFunctionCallSucceeded,
    _In_ BOOL UseLastErrorWhenSucceeded)
{
    return HRESULT_FROM_WIN32(M2GetLastWin32Error(
        IsLastFunctionCallSucceeded,
        UseLastErrorWhenSucceeded));
}

HRESULT M2CoCreateInstance(
    _In_ LPCWSTR lpszCLSID,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ LPCWSTR lpszIID,
    _Out_ LPVOID* ppv)
{
    CLSID clsid;
    IID iid;

    HRESULT hr = CLSIDFromString(lpszCLSID, &clsid);
    if (SUCCEEDED(hr))
    {
        hr = IIDFromString(lpszIID, &iid);
        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(clsid, pUnkOuter, dwClsContext, iid, ppv);
        }
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Retrieves the string type data for the specified value name associated with
 * an open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the registry value.
 * @param lpData A pointer to a buffer that receives the value's data. When you
 *               have finished using the information, free it by calling the
 *               M2FreeMemory function. You should also set the pointer to
 *               NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegQueryValueEx.
 */
HRESULT M2RegQueryStringValue(
    _Out_ LPWSTR* lpData,
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName)
{
    *lpData = nullptr;

    DWORD cbData = 0;
    HRESULT hr = ::MileRegQueryValue(
        hKey,
        lpValueName,
        nullptr,
        nullptr,
        nullptr,
        &cbData);
    if (SUCCEEDED(hr))
    {
        hr = ::MileAllocMemory(cbData, reinterpret_cast<PVOID*>(lpData));
        if (SUCCEEDED(hr))
        {
            DWORD Type = 0;
            hr = ::MileRegQueryValue(
                hKey,
                lpValueName,
                nullptr,
                &Type,
                reinterpret_cast<LPBYTE>(*lpData),
                &cbData);
            if (SUCCEEDED(hr) && REG_SZ != Type)
                hr = __HRESULT_FROM_WIN32(ERROR_ILLEGAL_ELEMENT_ADDRESS);

            if (FAILED(hr))
                hr = ::MileFreeMemory(*lpData);
        }
    }

    return hr;
}

#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Determines whether the interface id have the correct interface name.
 *
 * @param InterfaceID A pointer to the string representation of the IID.
 * @param InterfaceName A pointer to the interface name string.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2CoCheckInterfaceName(
    _In_ LPCWSTR InterfaceID,
    _In_ LPCWSTR InterfaceName)
{
    wchar_t RegistryKeyPath[64];
    if (0 != wcscpy_s(RegistryKeyPath, L"Interface\\"))
        return E_INVALIDARG;
    if (0 != wcscat_s(RegistryKeyPath, InterfaceID))
        return E_INVALIDARG;

    HKEY hKey = nullptr;
    HRESULT hr = ::MileRegCreateKey(
        HKEY_CLASSES_ROOT,
        RegistryKeyPath,
        0,
        nullptr,
        0,
        KEY_READ,
        nullptr,
        &hKey,
        nullptr);
    if (SUCCEEDED(hr))
    {
        wchar_t* InterfaceTypeName = nullptr;
        hr = M2RegQueryStringValue(&InterfaceTypeName, hKey, nullptr);
        if (SUCCEEDED(hr))
        {
            if (0 != _wcsicmp(InterfaceTypeName, InterfaceName))
            {
                hr = E_NOINTERFACE;
            }

            ::MileFreeMemory(InterfaceTypeName);
        }

        ::MileRegCloseKey(hKey);
    }

    return hr;
}

#endif

#endif // _M2_WINDOWS_BASE_EXTENDED_HELPERS_

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
 * Converts from the UTF-8 string to the UTF-16 string.
 *
 * @param UTF8String The UTF-8 string you want to convert.
 * @return A converted UTF-16 string.
 */
std::wstring M2MakeUTF16String(const std::string& UTF8String)
{
    std::wstring UTF16String;

    int UTF16StringLength = MultiByteToWideChar(
        CP_UTF8,
        0,
        UTF8String.data(),
        (int)UTF8String.size(),
        nullptr,
        0);
    if (UTF16StringLength > 0)
    {
        UTF16String.resize(UTF16StringLength);
        MultiByteToWideChar(
            CP_UTF8,
            0,
            UTF8String.data(),
            (int)UTF8String.size(),
            &UTF16String[0],
            UTF16StringLength);
    }

    return UTF16String;
}

/**
 * Converts from the UTF-16 string to the UTF-8 string.
 *
 * @param UTF16String The UTF-16 string you want to convert.
 * @return A converted UTF-8 string.
 */
std::string M2MakeUTF8String(const std::wstring& UTF16String)
{
    std::string UTF8String;

    int UTF8StringLength = WideCharToMultiByte(
        CP_UTF8,
        0,
        UTF16String.data(),
        (int)UTF16String.size(),
        nullptr,
        0,
        nullptr,
        nullptr);
    if (UTF8StringLength > 0)
    {
        UTF8String.resize(UTF8StringLength);
        WideCharToMultiByte(
            CP_UTF8,
            0,
            UTF16String.data(),
            (int)UTF16String.size(),
            &UTF8String[0],
            UTF8StringLength,
            nullptr,
            nullptr);
    }

    return UTF8String;
}

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

/**
 * Parses a command line string and returns an array of the command line
 * arguments, along with a count of such arguments, in a way that is similar to
 * the standard C run-time.
 *
 * @param CommandLine A string that contains the full command line. If this
 *                    parameter is an empty string the function returns an
 *                    array with only one empty string.
 * @return An array of the command line arguments, along with a count of such
 *         arguments.
 */
std::vector<std::wstring> M2SpiltCommandLine(
    const std::wstring& CommandLine)
{
    // Initialize the SplitArguments.
    std::vector<std::wstring> SplitArguments;

    wchar_t c = L'\0';
    int copy_character;                   /* 1 = copy char to *args */
    unsigned numslash;              /* num of backslashes seen */

    std::wstring Buffer;
    Buffer.reserve(CommandLine.size());

    /* first scan the program name, copy it, and count the bytes */
    wchar_t* p = const_cast<wchar_t*>(CommandLine.c_str());

    // A quoted program name is handled here. The handling is much simpler than
    // for other arguments. Basically, whatever lies between the leading
    // double-quote and next one, or a terminal null character is simply
    // accepted. Fancier handling is not required because the program name must
    // be a legal NTFS/HPFS file name. Note that the double-quote characters are
    // not copied, nor do they contribute to character_count.
    bool InQuotes = false;
    do
    {
        if (*p == '"')
        {
            InQuotes = !InQuotes;
            c = *p++;
            continue;
        }

        // Copy character into argument:
        Buffer.push_back(*p);

        c = *p++;
    } while (c != '\0' && (InQuotes || (c != ' ' && c != '\t')));

    if (c == '\0')
    {
        p--;
    }
    else
    {
        Buffer.resize(Buffer.size() - 1);
    }

    // Save te argument.
    SplitArguments.push_back(Buffer);

    InQuotes = false;

    // Loop on each argument
    for (;;)
    {
        if (*p)
        {
            while (*p == ' ' || *p == '\t')
                ++p;
        }

        // End of arguments
        if (*p == '\0')
            break;

        // Initialize the argument buffer.
        Buffer.clear();

        // Loop through scanning one argument:
        for (;;)
        {
            copy_character = 1;

            // Rules: 2N backslashes + " ==> N backslashes and begin/end quote
            // 2N + 1 backslashes + " ==> N backslashes + literal " N
            // backslashes ==> N backslashes
            numslash = 0;

            while (*p == '\\')
            {
                // Count number of backslashes for use below
                ++p;
                ++numslash;
            }

            if (*p == '"')
            {
                // if 2N backslashes before, start/end quote, otherwise copy
                // literally:
                if (numslash % 2 == 0)
                {
                    if (InQuotes && p[1] == '"')
                    {
                        p++; // Double quote inside quoted string
                    }
                    else
                    {
                        // Skip first quote char and copy second:
                        copy_character = 0; // Don't copy quote
                        InQuotes = !InQuotes;
                    }
                }

                numslash /= 2;
            }

            // Copy slashes:
            while (numslash--)
            {
                Buffer.push_back(L'\\');
            }

            // If at end of arg, break loop:
            if (*p == '\0' || (!InQuotes && (*p == ' ' || *p == '\t')))
                break;

            // Copy character into argument:
            if (copy_character)
            {
                Buffer.push_back(*p);
            }

            ++p;
        }

        // Save te argument.
        SplitArguments.push_back(Buffer);
    }

    return SplitArguments;
}

/**
 * Parses a command line string and get more friendly result.
 *
 * @param CommandLine A string that contains the full command line. If this
 *                    parameter is an empty string the function returns an
 *                    array with only one empty string.
 * @param OptionPrefixes One or more of the prefixes of option we want to use.
 * @param OptionParameterSeparators One or more of the separators of option we
 *                                  want to use.
 * @param ApplicationName The application name.
 * @param OptionsAndParameters The options and parameters.
 * @param UnresolvedCommandLine The unresolved command line.
 */
void M2SpiltCommandLineEx(
    const std::wstring& CommandLine,
    const std::vector<std::wstring>& OptionPrefixes,
    const std::vector<std::wstring>& OptionParameterSeparators,
    std::wstring& ApplicationName,
    std::map<std::wstring, std::wstring>& OptionsAndParameters,
    std::wstring& UnresolvedCommandLine)
{
    ApplicationName.clear();
    OptionsAndParameters.clear();
    UnresolvedCommandLine.clear();

    size_t arg_size = 0;
    for (auto& SplitArgument : M2SpiltCommandLine(CommandLine))
    {
        // We need to process the application name at the beginning.
        if (ApplicationName.empty())
        {
            // For getting the unresolved command line, we need to cumulate
            // length which including spaces.
            arg_size += SplitArgument.size() + 1;

            // Save
            ApplicationName = SplitArgument;
        }
        else
        {
            bool IsOption = false;
            size_t OptionPrefixLength = 0;

            for (auto& OptionPrefix : OptionPrefixes)
            {
                if (0 == _wcsnicmp(
                    SplitArgument.c_str(),
                    OptionPrefix.c_str(),
                    OptionPrefix.size()))
                {
                    IsOption = true;
                    OptionPrefixLength = OptionPrefix.size();
                }
            }

            if (IsOption)
            {
                // For getting the unresolved command line, we need to cumulate
                // length which including spaces.
                arg_size += SplitArgument.size() + 1;

                // Get the option name and parameter.

                wchar_t* OptionStart = &SplitArgument[0] + OptionPrefixLength;
                wchar_t* ParameterStart = nullptr;

                for (auto& OptionParameterSeparator
                    : OptionParameterSeparators)
                {
                    wchar_t* Result = wcsstr(
                        OptionStart,
                        OptionParameterSeparator.c_str());
                    if (nullptr == Result)
                    {
                        continue;
                    }

                    Result[0] = L'\0';
                    ParameterStart = Result + OptionParameterSeparator.size();

                    break;
                }

                // Save
                OptionsAndParameters[(OptionStart ? OptionStart : L"")] =
                    (ParameterStart ? ParameterStart : L"");
            }
            else
            {
                // Get the approximate location of the unresolved command line.
                // We use "(arg_size - 1)" to ensure that the program path
                // without quotes can also correctly parse.
                wchar_t* search_start =
                    const_cast<wchar_t*>(CommandLine.c_str()) + (arg_size - 1);

                // Get the unresolved command line. Search for the beginning of
                // the first parameter delimiter called space and exclude the
                // first space by adding 1 to the result.
                wchar_t* command = wcsstr(search_start, L" ") + 1;

                // Omit the space. (Thanks to wzzw.)
                while (command && *command == L' ')
                {
                    ++command;
                }

                // Save
                if (command)
                {
                    UnresolvedCommandLine = command;
                }

                break;
            }
        }
    }
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

    int UTF8StringLength = WideCharToMultiByte(
        CP_UTF8,
        0,
        PlatformString->Data(),
        static_cast<int>(PlatformString->Length()),
        nullptr,
        0,
        nullptr,
        nullptr);
    if (UTF8StringLength > 0)
    {
        UTF8String.resize(UTF8StringLength);
        WideCharToMultiByte(
            CP_UTF8,
            0,
            PlatformString->Data(),
            static_cast<int>(PlatformString->Length()),
            &UTF8String[0],
            UTF8StringLength,
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

#pragma region Module

/**
 * Retrieves the path of the executable file of the current process.
 *
 * @return If the function succeeds, the return value is the path of the
 *         executable file of the current process. If the function fails, the
 *         return value is an empty string.
 */
std::wstring M2GetCurrentProcessModulePath()
{
    std::wstring result(MAX_PATH, L'\0');
    GetModuleFileNameW(nullptr, &result[0], (DWORD)(result.capacity()));
    result.resize(wcslen(result.c_str()));
    return result;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Loads the specified module with the optimization of the mitigation of DLL
 * preloading attacks into the address space of the calling process safely. The
 * specified module may cause other modules to be loaded.
 *
 * @param ModuleHandle If the function succeeds, this parameter's value is a
 *                     handle to the loaded module. You should read the
 *                     documentation about LoadLibraryEx API for further
 *                     information.
 * @param LibraryFileName A string that specifies the file name of the module
 *                        to load. You should read the documentation about
 *                        LoadLibraryEx API for further information.
 * @param Flags The action to be taken when loading the module. You should read
 *              the documentation about LoadLibraryEx API for further
 *              information.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2LoadLibraryEx(
    _Out_ HMODULE* ModuleHandle,
    _In_ LPCWSTR LibraryFileName,
    _In_ DWORD Flags)
{
    HRESULT hr = ::MileLoadLibrary(LibraryFileName, nullptr, Flags, ModuleHandle);
    if (FAILED(hr))
    {
        if ((Flags & LOAD_LIBRARY_SEARCH_SYSTEM32) &&
            (hr == __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER)))
        {
            // In the Windows API (with some exceptions discussed in the
            // following paragraphs), the maximum length for a path is
            // MAX_PATH, which is defined as 260 characters. A local path is
            // structured in the following order: drive letter, colon,
            // backslash, name components separated by backslashes, and a
            // terminating null character. For example, the maximum path on
            // drive D is "D:\some 256-character path string" where ""
            // represents the invisible terminating null character for the
            // current system codepage.
            // MAX_PATH = 260 = wcslen(L"D:\some 256-character path string")
            // wcslen(L"C:\\Windows\\System32") = 19
            // BufferSize = 19 + 256 + 1 = 276
            // P.S. In the most cases, I don't think the length "System32" path
            // string will bigger than 19.
            const size_t BufferLength = 276;
            wchar_t Buffer[BufferLength];
            if (!wcschr(LibraryFileName, L'\\'))
            {
                if (0 == GetSystemDirectoryW(
                    Buffer,
                    static_cast<UINT>(BufferLength)))
                {
                    hr = M2GetLastHResultError();
                }
                else
                {
                    hr = StringCbCatW(Buffer, BufferLength, LibraryFileName);
                    if (SUCCEEDED(hr))
                    {
                        hr = ::MileLoadLibrary(
                            Buffer,
                            nullptr,
                            Flags & (-1 ^ LOAD_LIBRARY_SEARCH_SYSTEM32),
                            ModuleHandle);
                    }
                }
            }
        }
    }

    return hr;
}

#endif

#pragma endregion

#pragma region Environment

/**
 * Retrieves the path of the system directory.
 *
 * @param SystemFolderPath The string of the path of the system directory.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetSystemDirectory(
    std::wstring& SystemFolderPath)
{
    HRESULT hr = S_OK;

    do
    {
        UINT Length = GetSystemDirectoryW(
            nullptr,
            0);
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }

        SystemFolderPath.resize(Length - 1);

        Length = GetSystemDirectoryW(
            &SystemFolderPath[0],
            static_cast<UINT>(Length));
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }
        if (SystemFolderPath.size() != Length)
        {
            hr = E_UNEXPECTED;
            break;
        }

    } while (false);

    if (FAILED(hr))
    {
        SystemFolderPath.clear();
    }

    return hr;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Retrieves the path of the shared Windows directory on a multi-user system.
 *
 * @param WindowsFolderPath The string of the path of the shared Windows
 *                          directory on a multi-user system.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetWindowsDirectory(
    std::wstring& WindowsFolderPath)
{
    HRESULT hr = S_OK;

    do
    {
        UINT Length = GetSystemWindowsDirectoryW(
            nullptr,
            0);
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }

        WindowsFolderPath.resize(Length - 1);

        Length = GetSystemWindowsDirectoryW(
            &WindowsFolderPath[0],
            static_cast<UINT>(Length));
        if (0 == Length)
        {
            hr = M2GetLastHResultError();
            break;
        }
        if (WindowsFolderPath.size() != Length)
        {
            hr = E_UNEXPECTED;
            break;
        }

    } while (false);

    if (FAILED(hr))
    {
        WindowsFolderPath.clear();
    }

    return hr;
}

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
    // Fix for Windows Vista and Server 2008.
    if (!IsWindowsVersionOrGreater(10, 0, 0)) return -1;

    typedef INT(WINAPI * PFN_EnablePerMonitorDialogScaling)();

    HMODULE hModule = nullptr;
    PFN_EnablePerMonitorDialogScaling pFunc = nullptr;

    hModule = GetModuleHandleW(L"user32.dll");
    if (!hModule) return -1;

    if (FAILED(::MileGetProcAddress(
        hModule,
        reinterpret_cast<LPCSTR>(2577),
        reinterpret_cast<FARPROC*>(&pFunc))))
        return -1;

    return pFunc();
}

/**
 * Queries the dots per inch (dpi) of a display.
 *
 * @param hmonitor Handle of the monitor being queried.
 * @param dpiType The type of DPI being queried. Possible values are from the
 *                MONITOR_DPI_TYPE enumeration.
 * @param dpiX The value of the DPI along the X axis. This value always refers
 *             to the horizontal edge, even when the screen is rotated.
 * @param dpiY The value of the DPI along the Y axis. This value always refers
 *             to the vertical edge, even when the screen is rotated.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetDpiForMonitor.
 */
HRESULT M2GetDpiForMonitor(
    _In_ HMONITOR hmonitor,
    _In_ MONITOR_DPI_TYPE dpiType,
    _Out_ UINT* dpiX,
    _Out_ UINT* dpiY)
{
    HMODULE hModule = nullptr;
    HRESULT hr = M2LoadLibraryEx(
        &hModule,
        L"SHCore.dll",
        LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (SUCCEEDED(hr))
    {
        decltype(GetDpiForMonitor)* pFunc = nullptr;
        hr = ::MileGetProcAddress(
            hModule,
            "GetDpiForMonitor",
            reinterpret_cast<FARPROC*>(&pFunc));
        if (SUCCEEDED(hr))
        {
            hr = pFunc(hmonitor, dpiType, dpiX, dpiY);
        }

        FreeLibrary(hModule);
    }

    return hr;
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
