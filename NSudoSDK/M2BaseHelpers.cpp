/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2BaseHelpers.cpp
 * PURPOSE:   Implementation for the basic helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "stdafx.h"

#ifdef _M2_BASE_HELPERS_

#include <Windows.h>

#include "M2BaseHelpers.h"

#include <string>

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
        size_t nLength = _vscwprintf(Format, ArgList) + 1;

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
 * Retrieves the number of milliseconds that have elapsed since the system was
 * started.
 *
 * @return The number of milliseconds.
 */
ULONGLONG M2GetTickCount()
{
    LARGE_INTEGER Frequency = { 0 }, PerformanceCount = { 0 };

    if (QueryPerformanceFrequency(&Frequency))
    {
        if (QueryPerformanceCounter(&PerformanceCount))
        {
            return (PerformanceCount.QuadPart * 1000 / Frequency.QuadPart);
        }
    }

    return GetTickCount64();
}

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
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastError()
{
    return __HRESULT_FROM_WIN32(GetLastError());
}

/**
 * Retrieves the address of an exported function or variable from the specified
 * dynamic-link library (DLL).
 *
 * @param lpProcAddress The address of the exported function or variable.
 * @param hModule A handle to the DLL module that contains the function or
 *                variable. The LoadLibrary, LoadLibraryEx, LoadPackagedLibrary
 *                or GetModuleHandle function returns this handle. This
 *                function does not retrieve addresses from modules that were
 *                loaded using the LOAD_LIBRARY_AS_DATAFILE flag. For more
 *                information, see LoadLibraryEx.
 * @param lpProcName The function or variable name, or the function's ordinal
 *                   value. If this parameter is an ordinal value, it must be
 *                   in the low-order word; the high-order word must be zero.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetProcAddress(
    _Out_ FARPROC& lpProcAddress,
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName)
{
    lpProcAddress = GetProcAddress(hModule, lpProcName);
    return (nullptr != lpProcAddress) ? S_OK : M2GetLastError();
}

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
                while (*command == L' ')
                {
                    ++command;
                }

                // Save
                UnresolvedCommandLine = command;

                break;
            }
        }
    }
}

#endif // _M2_BASE_HELPERS_
