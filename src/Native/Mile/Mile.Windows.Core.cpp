/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Core.cpp
 * PURPOSE:   Core Implementation for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.Windows.Core.h"

#include <strsafe.h>

#pragma region Implementations for Windows (Win32 Style)

namespace
{
    /**
     * @brief The information about the Windows Overlay Filter file provider.
    */
    typedef struct _WOF_FILE_PROVIDER_EXTERNAL_INFO
    {
        WOF_EXTERNAL_INFO Wof;
        FILE_PROVIDER_EXTERNAL_INFO FileProvider;
    } WOF_FILE_PROVIDER_EXTERNAL_INFO, * PWOF_FILE_PROVIDER_EXTERNAL_INFO;

    /**
     * @brief The internal content of the file enumerator handle.
    */
    typedef struct _FILE_ENUMERATOR_OBJECT
    {
        HANDLE FileHandle;
        CRITICAL_SECTION CriticalSection;
        PFILE_ID_BOTH_DIR_INFO CurrentFileInfo;
        BYTE FileInfoBuffer[32768];
    } FILE_ENUMERATOR_OBJECT, * PFILE_ENUMERATOR_OBJECT;
}

Mile::HResultFromLastError Mile::DeviceIoControl(
    _In_ HANDLE hDevice,
    _In_ DWORD dwIoControlCode,
    _In_opt_ LPVOID lpInBuffer,
    _In_ DWORD nInBufferSize,
    _Out_opt_ LPVOID lpOutBuffer,
    _In_ DWORD nOutBufferSize,
    _Out_opt_ LPDWORD lpBytesReturned)
{
    BOOL Result = FALSE;
    OVERLAPPED Overlapped = { 0 };
    Overlapped.hEvent = ::CreateEventW(
        nullptr,
        TRUE,
        FALSE,
        nullptr);
    if (Overlapped.hEvent)
    {
        Result = ::DeviceIoControl(
            hDevice,
            dwIoControlCode,
            lpInBuffer,
            nInBufferSize,
            lpOutBuffer,
            nOutBufferSize,
            lpBytesReturned,
            &Overlapped);
        if (!Result)
        {
            if (::GetLastError() == ERROR_IO_PENDING)
            {
                Result = ::GetOverlappedResult(
                    hDevice,
                    &Overlapped,
                    lpBytesReturned,
                    TRUE);
            }
        }

        ::CloseHandle(Overlapped.hEvent);
    }
    else
    {
        ::SetLastError(ERROR_NO_SYSTEM_RESOURCES);
    }

    return Result;
}

Mile::HResultFromLastError Mile::GetNtfsCompressionAttribute(
    _In_ HANDLE FileHandle,
    _Out_ PUSHORT CompressionAlgorithm)
{
    if (!CompressionAlgorithm)
        return E_INVALIDARG;

    DWORD BytesReturned;
    return Mile::DeviceIoControl(
        FileHandle,
        FSCTL_GET_COMPRESSION,
        nullptr,
        0,
        CompressionAlgorithm,
        sizeof(*CompressionAlgorithm),
        &BytesReturned);
}

Mile::HResultFromLastError Mile::SetNtfsCompressionAttribute(
    _In_ HANDLE FileHandle,
    _In_ USHORT CompressionAlgorithm)
{
    switch (CompressionAlgorithm)
    {
    case COMPRESSION_FORMAT_NONE:
    case COMPRESSION_FORMAT_DEFAULT:
    case COMPRESSION_FORMAT_LZNT1:
        break;
    default:
        return E_INVALIDARG;
    }

    DWORD BytesReturned;
    return Mile::DeviceIoControl(
        FileHandle,
        FSCTL_SET_COMPRESSION,
        &CompressionAlgorithm,
        sizeof(CompressionAlgorithm),
        nullptr,
        0,
        &BytesReturned);
}

Mile::HResultFromLastError Mile::GetWofCompressionAttribute(
    _In_ HANDLE FileHandle,
    _Out_ PDWORD CompressionAlgorithm)
{
    if (!CompressionAlgorithm)
        return E_INVALIDARG;

    WOF_FILE_PROVIDER_EXTERNAL_INFO WofInfo = { 0 };
    DWORD BytesReturned;
    if (!Mile::DeviceIoControl(
        FileHandle,
        FSCTL_GET_EXTERNAL_BACKING,
        nullptr,
        0,
        &WofInfo,
        sizeof(WofInfo),
        &BytesReturned))
    {
        return FALSE;
    }

    *CompressionAlgorithm = WofInfo.FileProvider.Algorithm;
    return TRUE;
}

Mile::HResultFromLastError Mile::SetWofCompressionAttribute(
    _In_ HANDLE FileHandle,
    _In_ DWORD CompressionAlgorithm)
{
    switch (CompressionAlgorithm)
    {
    case FILE_PROVIDER_COMPRESSION_XPRESS4K:
    case FILE_PROVIDER_COMPRESSION_LZX:
    case FILE_PROVIDER_COMPRESSION_XPRESS8K:
    case FILE_PROVIDER_COMPRESSION_XPRESS16K:
        break;
    default:
        return E_INVALIDARG;
    }

    WOF_FILE_PROVIDER_EXTERNAL_INFO WofInfo = { 0 };

    WofInfo.Wof.Version = WOF_CURRENT_VERSION;
    WofInfo.Wof.Provider = WOF_PROVIDER_FILE;

    WofInfo.FileProvider.Version = FILE_PROVIDER_CURRENT_VERSION;
    WofInfo.FileProvider.Flags = 0;
    WofInfo.FileProvider.Algorithm = CompressionAlgorithm;

    DWORD BytesReturned;
    return Mile::DeviceIoControl(
        FileHandle,
        FSCTL_SET_EXTERNAL_BACKING,
        &WofInfo,
        sizeof(WofInfo),
        nullptr,
        0,
        &BytesReturned);
}

Mile::HResultFromLastError Mile::RemoveWofCompressionAttribute(
    _In_ HANDLE FileHandle)
{
    DWORD BytesReturned;
    return Mile::DeviceIoControl(
        FileHandle,
        FSCTL_DELETE_EXTERNAL_BACKING,
        nullptr,
        0,
        nullptr,
        0,
        &BytesReturned);
}

Mile::HResult Mile::GetCompactOsDeploymentState(
    _Out_ PDWORD DeploymentState)
{
    if (DeploymentState)
    {
        return E_INVALIDARG;
    }

    HKEY hKey = nullptr;

    Mile::HResult hr = Mile::HResult::FromWin32(::RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        L"System\\Setup",
        0,
        KEY_READ | KEY_WOW64_64KEY,
        &hKey));
    if (hr.IsSucceeded())
    {
        DWORD Type = 0;
        DWORD Data = FALSE;
        DWORD Length = sizeof(DWORD);

        hr = Mile::HResult::FromWin32(::RegQueryValueExW(
            hKey,
            L"Compact",
            nullptr,
            &Type,
            reinterpret_cast<LPBYTE>(&Data),
            &Length));
        if (hr.IsSucceeded() && Type == REG_DWORD)
        {
            *DeploymentState = Data;
        }

        ::RegCloseKey(hKey);
    }

    return hr;
}

Mile::HResult Mile::SetCompactOsDeploymentState(
    _In_ DWORD DeploymentState)
{
    HKEY hKey = nullptr;

    Mile::HResult hr = Mile::HResult::FromWin32(::RegCreateKeyExW(
        HKEY_LOCAL_MACHINE,
        L"System\\Setup",
        0,
        nullptr,
        0,
        KEY_WRITE | KEY_WOW64_64KEY,
        nullptr,
        &hKey,
        nullptr));
    if (hr.IsSucceeded())
    {
        hr = Mile::HResult::FromWin32(::RegSetValueExW(
            hKey,
            L"Compact",
            0,
            REG_DWORD,
            reinterpret_cast<CONST BYTE*>(&DeploymentState),
            sizeof(DWORD)));

        ::RegCloseKey(hKey);
    }

    return hr;
}

Mile::HResult Mile::CreateFileEnumerator(
    _Out_ Mile::PFILE_ENUMERATOR_HANDLE FileEnumeratorHandle,
    _In_ HANDLE FileHandle)
{
    if (FileEnumeratorHandle)
    {
        return E_INVALIDARG;
    }

    if (!FileHandle || FileHandle == INVALID_HANDLE_VALUE)
    {
        return E_INVALIDARG;
    }

    PFILE_ENUMERATOR_OBJECT Object = reinterpret_cast<PFILE_ENUMERATOR_OBJECT>(
        Mile::HeapMemory::Allocate(sizeof(FILE_ENUMERATOR_OBJECT)));
    if (!Object)
    {
        return E_OUTOFMEMORY;
    }

    Object->FileHandle = FileHandle;
    Mile::CriticalSection::Initialize(&Object->CriticalSection);
    *FileEnumeratorHandle = Object;

    return S_OK;
}

Mile::HResultFromLastError Mile::CloseFileEnumerator(
    _In_ Mile::FILE_ENUMERATOR_HANDLE FileEnumeratorHandle)
{
    if (!FileEnumeratorHandle)
    {
        ::SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    PFILE_ENUMERATOR_OBJECT Object =
        reinterpret_cast<PFILE_ENUMERATOR_OBJECT>(FileEnumeratorHandle);

    Mile::CriticalSection::Delete(&Object->CriticalSection);

    return Mile::HeapMemory::Free(Object);
}

Mile::HResultFromLastError Mile::QueryFileEnumerator(
    _In_ Mile::FILE_ENUMERATOR_HANDLE FileEnumeratorHandle,
    _Out_ Mile::PFILE_ENUMERATOR_INFORMATION FileEnumeratorInformation)
{
    if ((!FileEnumeratorHandle) || (!FileEnumeratorInformation))
    {
        ::SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    BOOL Result = FALSE;

    PFILE_ENUMERATOR_OBJECT Object =
        reinterpret_cast<PFILE_ENUMERATOR_OBJECT>(FileEnumeratorHandle);

    Mile::CriticalSection::Enter(&Object->CriticalSection);

    if (!Object->CurrentFileInfo)
    {
        Object->CurrentFileInfo =
            reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(Object->FileInfoBuffer);

        Result = ::GetFileInformationByHandleEx(
            Object->FileHandle,
            FILE_INFO_BY_HANDLE_CLASS::FileIdBothDirectoryRestartInfo,
            Object->CurrentFileInfo,
            sizeof(Object->FileInfoBuffer));
    }
    else if (!Object->CurrentFileInfo->NextEntryOffset)
    {
        Object->CurrentFileInfo =
            reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(Object->FileInfoBuffer);

        Result = ::GetFileInformationByHandleEx(
            Object->FileHandle,
            FILE_INFO_BY_HANDLE_CLASS::FileIdBothDirectoryInfo,
            Object->CurrentFileInfo,
            sizeof(Object->FileInfoBuffer));
    }
    else
    {
        Object->CurrentFileInfo = reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(
            reinterpret_cast<ULONG_PTR>(Object->CurrentFileInfo)
            + Object->CurrentFileInfo->NextEntryOffset);
    }

    if (Result)
    {
        PFILE_ID_BOTH_DIR_INFO CurrentFileInfo = Object->CurrentFileInfo;

        FileEnumeratorInformation->CreationTime.dwLowDateTime =
            CurrentFileInfo->CreationTime.LowPart;
        FileEnumeratorInformation->CreationTime.dwHighDateTime =
            CurrentFileInfo->CreationTime.HighPart;

        FileEnumeratorInformation->LastAccessTime.dwLowDateTime =
            CurrentFileInfo->LastAccessTime.LowPart;
        FileEnumeratorInformation->LastAccessTime.dwHighDateTime =
            CurrentFileInfo->LastAccessTime.HighPart;

        FileEnumeratorInformation->LastWriteTime.dwLowDateTime =
            CurrentFileInfo->LastWriteTime.LowPart;
        FileEnumeratorInformation->LastWriteTime.dwHighDateTime =
            CurrentFileInfo->LastWriteTime.HighPart;

        FileEnumeratorInformation->ChangeTime.dwLowDateTime =
            CurrentFileInfo->ChangeTime.LowPart;
        FileEnumeratorInformation->ChangeTime.dwHighDateTime =
            CurrentFileInfo->ChangeTime.HighPart;

        FileEnumeratorInformation->FileSize =
            CurrentFileInfo->EndOfFile.QuadPart;

        FileEnumeratorInformation->AllocationSize =
            CurrentFileInfo->AllocationSize.QuadPart;

        FileEnumeratorInformation->FileAttributes =
            CurrentFileInfo->FileAttributes;

        FileEnumeratorInformation->EaSize =
            CurrentFileInfo->EaSize;

        FileEnumeratorInformation->FileId =
            CurrentFileInfo->FileId;

        ::StringCbCopyNW(
            FileEnumeratorInformation->ShortName,
            sizeof(FileEnumeratorInformation->ShortName),
            CurrentFileInfo->ShortName,
            CurrentFileInfo->ShortNameLength);

        ::StringCbCopyNW(
            FileEnumeratorInformation->FileName,
            sizeof(FileEnumeratorInformation->FileName),
            CurrentFileInfo->FileName,
            CurrentFileInfo->FileNameLength);
    }

    Mile::CriticalSection::Leave(&Object->CriticalSection);

    return Result;
}

#pragma endregion

#pragma region Implementations for Windows (C++ Style)

std::wstring Mile::GetHResultMessage(
    HResult const& Value)
{
    std::wstring Message{ L"Failed to get formatted message." };

    LPWSTR RawMessage = nullptr;
    DWORD RawMessageSize = ::FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        Value,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>(&RawMessage),
        0,
        nullptr);
    if (RawMessageSize)
    {
        Message = std::wstring(RawMessage, RawMessageSize);

        ::LocalFree(RawMessage);
    }

    return Message;
}

std::wstring Mile::ToUtf16String(
    std::string const& Utf8String)
{
    std::wstring Utf16String;

    int Utf16StringLength = ::MultiByteToWideChar(
        CP_UTF8,
        0,
        Utf8String.c_str(),
        static_cast<int>(Utf8String.size()),
        nullptr,
        0);
    if (Utf16StringLength > 0)
    {
        Utf16String.resize(Utf16StringLength);
        Utf16StringLength = ::MultiByteToWideChar(
            CP_UTF8,
            0,
            Utf8String.c_str(),
            static_cast<int>(Utf8String.size()),
            &Utf16String[0],
            Utf16StringLength);
        Utf16String.resize(Utf16StringLength);
    }

    return Utf16String;
}

std::string Mile::ToUtf8String(
    std::wstring const& Utf16String)
{
    std::string Utf8String;

    int Utf8StringLength = ::WideCharToMultiByte(
        CP_UTF8,
        0,
        Utf16String.data(),
        static_cast<int>(Utf16String.size()),
        nullptr,
        0,
        nullptr,
        nullptr);
    if (Utf8StringLength > 0)
    {
        Utf8String.resize(Utf8StringLength);
        Utf8StringLength = ::WideCharToMultiByte(
            CP_UTF8,
            0,
            Utf16String.data(),
            static_cast<int>(Utf16String.size()),
            &Utf8String[0],
            Utf8StringLength,
            nullptr,
            nullptr);
        Utf8String.resize(Utf8StringLength);
    }

    return Utf8String;
}

std::wstring Mile::GetSystemDirectoryW()
{
    std::wstring Path;

    UINT Length = ::GetSystemDirectoryW(nullptr, 0);
    if (Length)
    {
        Path.resize(Length);
        Length = ::GetSystemDirectoryW(&Path[0], Length);
        Path.resize(Length);
    }

    return Path;
}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

std::wstring Mile::GetWindowsDirectoryW()
{
    std::wstring Path;

    UINT Length = ::GetSystemWindowsDirectoryW(nullptr, 0);
    if (Length)
    {
        Path.resize(Length);
        Length = ::GetSystemWindowsDirectoryW(&Path[0], Length);
        Path.resize(Length);
    }

    return Path;
}

#endif

std::wstring Mile::ExpandEnvironmentStringsW(
    std::wstring const& SourceString)
{
    std::wstring DestinationString;

    UINT Length = ::ExpandEnvironmentStringsW(
        SourceString.c_str(),
        nullptr,
        0);
    if (Length)
    {
        DestinationString.resize(Length);
        Length = ::ExpandEnvironmentStringsW(
            SourceString.c_str(),
            &DestinationString[0],
            Length);
        DestinationString.resize(Length);
    }

    return DestinationString;
}

std::wstring Mile::GetCurrentProcessModulePath()
{
    // 32767 is the maximum path length without the terminating null character.
    std::wstring Path(32767, L'\0');
    Path.resize(::GetModuleFileNameW(
        nullptr, &Path[0], static_cast<DWORD>(Path.size())));
    return Path;
}

std::vector<std::wstring> Mile::SpiltCommandLine(
    std::wstring const& CommandLine)
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
    // be a legal NTFS/HPFS file name. Note that the double-quote characters
    // are not copied, nor do they contribute to character_count.
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

void Mile::SpiltCommandLineEx(
    std::wstring const& CommandLine,
    std::vector<std::wstring> const& OptionPrefixes,
    std::vector<std::wstring> const& OptionParameterSeparators,
    std::wstring& ApplicationName,
    std::map<std::wstring, std::wstring>& OptionsAndParameters,
    std::wstring& UnresolvedCommandLine)
{
    ApplicationName.clear();
    OptionsAndParameters.clear();
    UnresolvedCommandLine.clear();

    size_t arg_size = 0;
    for (auto& SplitArgument : Mile::SpiltCommandLine(CommandLine))
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

#pragma endregion
