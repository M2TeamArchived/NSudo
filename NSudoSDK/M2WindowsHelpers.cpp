/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsHelpers.cpp
 * PURPOSE:   Implementation for the Windows helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "stdafx.h"

#include "M2WindowsHelpers.h"

#include <assert.h>
#include <process.h>

#pragma region Error

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastHRESULTError()
{
    return HRESULT_FROM_WIN32(GetLastError());
}

/**
 * Retrieves the calling thread's last-error code value if you can be sure that
 * the last call was failed. The last-error code is maintained on a per-thread 
 * basis. Multiple threads do not overwrite each other's last-error code.
 *
 * @return The calling thread's last-error code.
 */
DWORD M2GetLastErrorKnownFailedCall()
{
    DWORD LastError = GetLastError();
    return (LastError != ERROR_SUCCESS) ? LastError : ERROR_FUNCTION_FAILED;
}

/**
 * Retrieves the calling thread's last-error code value if you can be sure that
 * the last call was failed. The last-error code is maintained on a per-thread
 * basis. Multiple threads do not overwrite each other's last-error code.
 *
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastHRESULTErrorKnownFailedCall()
{
    return HRESULT_FROM_WIN32(M2GetLastErrorKnownFailedCall());
}

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
    const std::wstring & CommandLine,
    const std::vector<std::wstring> & OptionPrefixes,
    const std::vector<std::wstring> & OptionParameterSeparators,
    std::wstring & ApplicationName,
    std::map<std::wstring, std::wstring> & OptionsAndParameters,
    std::wstring & UnresolvedCommandLine)
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

#pragma endregion

#pragma region Performance

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

#pragma endregion

#pragma region Thread

/**
 * Creates a thread to execute within the virtual address space of the calling
 * process.
 *
 * @param lpThreadAttributes A pointer to a SECURITY_ATTRIBUTES structure that
 *                           determines whether the returned handle can be
 *                           inherited by child processes.
 * @param dwStackSize The initial size of the stack, in bytes.
 * @param lpStartAddress A pointer to the application-defined function to be
 *                       executed by the thread.
 * @param lpParameter A pointer to a variable to be passed to the thread.
 * @param dwCreationFlags The flags that control the creation of the thread.
 * @param lpThreadId A pointer to a variable that receives the thread
 *                   identifier.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CreateThread.
 */
HRESULT M2CreateThread(
    _Out_ PHANDLE lpThreadHandle,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ SIZE_T dwStackSize,
    _In_ LPTHREAD_START_ROUTINE lpStartAddress,
    _In_opt_ __drv_aliasesMem LPVOID lpParameter,
    _In_ DWORD dwCreationFlags,
    _Out_opt_ LPDWORD lpThreadId)
{
    // sanity check for lpThreadId
    assert(sizeof(DWORD) == sizeof(unsigned));

    typedef unsigned(__stdcall * routine_type)(void*);

    // _beginthreadex calls CreateThread which will set the last error
    // value before it returns.
    *lpThreadHandle = reinterpret_cast<HANDLE>(_beginthreadex(
        lpThreadAttributes,
        static_cast<unsigned>(dwStackSize),
        reinterpret_cast<routine_type>(lpStartAddress),
        lpParameter,
        dwCreationFlags,
        reinterpret_cast<unsigned*>(lpThreadId)));

    return (*lpThreadHandle) ? S_OK : M2GetLastHRESULTErrorKnownFailedCall();
}

/**
 * Retrieves the number of logical processors in the current group.
 *
 * @return The number of logical processors in the current group.
 */
DWORD M2GetNumberOfHardwareThreads()
{
    SYSTEM_INFO SystemInfo = { 0 };
    GetNativeSystemInfo(&SystemInfo);
    return SystemInfo.dwNumberOfProcessors;
}

#pragma endregion

#pragma region Memory

/**
 * Allocates a block of memory from a heap. The allocated memory is not
 * movable.
 *
 * @param lpNewMem A pointer to the allocated memory block.
 * @param hHeap A handle to the heap from which the memory will be allocated.
 * @param dwFlags The heap allocation options.
 * @param dwBytes The number of bytes to be allocated.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapAlloc.
 */
HRESULT M2HeapAlloc(
    _Out_ PVOID* lpNewMem,
    _In_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ SIZE_T dwBytes)
{
    *lpNewMem = HeapAlloc(hHeap, dwFlags, dwBytes);
    return *lpNewMem ? S_OK : __HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
}

/**
 * Reallocates a block of memory from a heap. This function enables you to
 * resize a memory block and change other memory block properties. The
 * allocated memory is not movable.
 *
 * @param lpNewMem A pointer to the allocated memory block.
 * @param hHeap A handle to the heap from which the memory is to be
 *              reallocated.
 * @param dwFlags The heap reallocation options.
 * @param lpMem A pointer to the block of memory that the function reallocates.
 * @param dwBytes The new size of the memory block, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 * @remark For more information, see HeapReAlloc.
 */
HRESULT M2HeapReAlloc(
    _Out_ PVOID* lpNewMem,
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem,
    _In_ SIZE_T dwBytes)
{
    *lpNewMem = HeapReAlloc(hHeap, dwFlags, lpMem, dwBytes);
    return *lpNewMem ? S_OK : __HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
}

/**
 * Frees a memory block allocated from a heap by the M2HeapAlloc and
 * M2HeapReAlloc function.
 *
 * @param hHeap A handle to the heap whose memory block is to be freed.
 * @param dwFlags The heap free options.
 * @param lpMem A pointer to the memory block to be freed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapFree.
 */
HRESULT M2HeapFree(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem)
{
    if (!HeapFree(hHeap, dwFlags, lpMem))
        return M2GetLastHRESULTErrorKnownFailedCall();

    return S_OK;
}

/**
 * Allocates a block of memory from the default heap of the calling process.
 * The allocated memory will be initialized to zero. The allocated memory is
 * not movable.
 *
 * @param AllocatedMemoryBlock A pointer to the allocated memory block.
 * @param MemoryBlockSize The number of bytes to be allocated.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2AllocMemory(
    _Out_ PVOID* AllocatedMemoryBlock,
    _In_ SIZE_T MemoryBlockSize)
{
    return M2HeapAlloc(
        AllocatedMemoryBlock,
        GetProcessHeap(),
        HEAP_ZERO_MEMORY,
        MemoryBlockSize);
}

/**
 * Reallocates a block of memory from the default heap of the calling process.
 * If the reallocation request is for a larger size, the additional region of
 * memory beyond the original size be initialized to zero. This function
 * enables you to resize a memory block and change other memory block
 * properties. The allocated memory is not movable.
 *
 * @param NewAllocatedMemoryBlock A pointer to the allocated memory block.
 * @param OldAllocatedMemoryBlock A pointer to the block of memory that the
 *                                function reallocates. This pointer is
 *                                returned by an earlier call to the
 *                                M2AllocMemory or M2ReAllocMemory function.
 * @param NewMemoryBlockSize The new size of the memory block, in bytes. A
 *                           memory block's size can be increased or decreased
 *                           by using this function.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 */
HRESULT M2ReAllocMemory(
    _Out_ PVOID* NewAllocatedMemoryBlock,
    _In_ PVOID OldAllocatedMemoryBlock,
    _In_ SIZE_T NewMemoryBlockSize)
{
    return M2HeapReAlloc(
        NewAllocatedMemoryBlock,
        GetProcessHeap(),
        HEAP_ZERO_MEMORY,
        OldAllocatedMemoryBlock,
        NewMemoryBlockSize);
}

/**
 * Frees a memory block allocated from a heap by the M2AllocMemory and
 * M2ReAllocMemory function.
 *
 * @param AllocatedMemoryBlock A pointer to the memory block to be freed. This
 * pointer is returned by the M2AllocMemory or M2ReAllocMemory function. If
 * this pointer is nullptr, the behavior is undefined.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2FreeMemory(
    _In_ PVOID AllocatedMemoryBlock)
{
    return M2HeapFree(GetProcessHeap(), 0, AllocatedMemoryBlock);
}

#pragma endregion

#pragma region AccessToken

/**
 * Enables or disables privileges in the specified access token. Enabling or
 * disabling privileges in an access token requires TOKEN_ADJUST_PRIVILEGES
 * access.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token. If the
 *                    PreviousState parameter is not NULL, the handle must also
 *                    have TOKEN_QUERY access.
 * @param DisableAllPrivileges Specifies whether the function disables all of
 *                             the token's privileges. If this value is TRUE,
 *                             the function disables all privileges and ignores
 *                             the NewState parameter. If it is FALSE, the
 *                             function modifies privileges based on the
 *                             information pointed to by the NewState
 *                             parameter.
 * @param NewState A pointer to a TOKEN_PRIVILEGES structure that specifies an
 *                 array of privileges and their attributes. If
 *                 DisableAllPrivileges is TRUE, the function ignores this
 *                 parameter.
 * @param BufferLength Specifies the size, in bytes, of the buffer pointed to
 *                     by the PreviousState parameter. This parameter can be
 *                     zero if the PreviousState parameter is NULL.
 * @param PreviousState A pointer to a buffer that the function fills with a
 *                      TOKEN_PRIVILEGES structure that contains the previous
 *                      state of any privileges that the function modifies.
 *                      This parameter can be NULL.
 * @param ReturnLength A pointer to a variable that receives the required size,
 *                     in bytes, of the buffer pointed to by the PreviousState
 *                     parameter. This parameter can be NULL if PreviousState
 *                     is NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see AdjustTokenPrivileges.
 */
HRESULT M2AdjustTokenPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ BOOL DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ DWORD BufferLength,
    _Out_opt_ PTOKEN_PRIVILEGES PreviousState,
    _Out_opt_ PDWORD ReturnLength)
{
    BOOL Result = AdjustTokenPrivileges(
        TokenHandle,
        DisableAllPrivileges,
        NewState,
        BufferLength,
        PreviousState,
        ReturnLength);

    DWORD LastError = GetLastError();

    if (!Result && LastError == ERROR_SUCCESS)
        LastError = ERROR_FUNCTION_FAILED;

    return HRESULT_FROM_WIN32(LastError);
}

/**
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the function
 *                              retrieves.
 * @param TokenInformation A pointer to a buffer the function fills with the
 *                         requested information.
 * @param TokenInformationLength Specifies the size, in bytes, of the buffer
 *                               pointed to by the TokenInformation parameter.
 * @param ReturnLength A pointer to a variable that receives the number of
 *                     bytes needed for the buffer pointed to by the
 *                     TokenInformation parameter.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
HRESULT M2GetTokenInformation(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_opt_ LPVOID TokenInformation,
    _In_ DWORD TokenInformationLength,
    _Out_ PDWORD ReturnLength)
{
    if (GetTokenInformation(
        TokenHandle,
        TokenInformationClass,
        TokenInformation,
        TokenInformationLength,
        ReturnLength))
    {
        return S_OK;
    }

    return M2GetLastHRESULTErrorKnownFailedCall();
}

/**
 * Opens the access token associated with a process.
 *
 * @param TokenHandle A pointer to a handle that identifies the newly opened
 *                    access token when the function returns.
 * @param TokenSource The source information of access token associated with a
 *                    process.
 * @param DesiredAccess Specifies an access mask that specifies the requested
 *                      types of access to the access token. These requested
 *                      access types are compared with the discretionary access
 *                      control list (DACL) of the token to determine which
 *                      accesses are granted or denied.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2OpenProcessToken(
    _Out_ PHANDLE TokenHandle,
    _In_ PM2_PROCESS_ACCESS_TOKEN_SOURCE TokenSource,
    _In_ DWORD DesiredAccess)
{
    *TokenHandle = INVALID_HANDLE_VALUE;

    if (!TokenSource)
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);

    HANDLE ProcessHandle = INVALID_HANDLE_VALUE;

    switch (TokenSource->Type)
    {
    case M2_PROCESS_TOKEN_SOURCE_TYPE::Current:
        ProcessHandle = GetCurrentProcess();
        break;
    case M2_PROCESS_TOKEN_SOURCE_TYPE::Handle:
        ProcessHandle = TokenSource->ProcessHandle;
        break;
    case M2_PROCESS_TOKEN_SOURCE_TYPE::ProcessId:
        ProcessHandle = OpenProcess(
            MAXIMUM_ALLOWED, FALSE, TokenSource->ProcessId);
        if (!ProcessHandle)
            return M2GetLastHRESULTErrorKnownFailedCall();
        break;
    default:
        return __HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);
    }

    if (OpenProcessToken(ProcessHandle, DesiredAccess, TokenHandle))
        return S_OK;

    return M2GetLastHRESULTErrorKnownFailedCall();
}

/**
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param OutputInformation A pointer to a buffer the function fills with the
 *                          requested information. When you have finished using
 *                          the information, free it by calling the
 *                          M2FreeMemory function. You should also set the
 *                          pointer to NULL.
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the function
 *                              retrieves.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
HRESULT M2GetTokenInformation(
    _Out_ PVOID* OutputInformation,
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass)
{
    *OutputInformation = nullptr;

    DWORD Length = 0;

    HRESULT hr = M2GetTokenInformation(
        TokenHandle,
        TokenInformationClass,
        nullptr,
        0,
        &Length);
    if (hr == __HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
    {
        hr = M2AllocMemory(OutputInformation, Length);
        if (SUCCEEDED(hr))
        {
            hr = M2GetTokenInformation(
                TokenHandle,
                TokenInformationClass,
                *OutputInformation,
                Length,
                &Length);
            if (FAILED(hr))
            {
                hr = M2FreeMemory(*OutputInformation);
            }
        }
    }

    return hr;
}

#pragma endregion

#pragma region COM

/**
 * Creates a single uninitialized object of the class associated with a
 * specified CLSID.
 *
 * @param lpszCLSID The string representation of the CLSID.
 * @param pUnkOuter If NULL, indicates that the object is not being created as
 *                  part of an aggregate. If non-NULL, pointer to the aggregate
 *                  object's IUnknown interface (the controlling IUnknown).
 * @param dwClsContext Context in which the code that manages the newly created
 *                     object will run. The values are taken from the
 *                     enumeration CLSCTX.
 * @param lpszIID A pointer to the string representation of the IID.
 * @param ppv Address of pointer variable that receives the interface pointer
 *            requested in riid. Upon successful return, *ppv contains the
 *            requested interface pointer. Upon failure, *ppv contains NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CoCreateInstance.
 */
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

#pragma endregion

#pragma region File

/**
 * Retrieves file system attributes for a specified file or directory.
 *
 * @param FileHandle A handle to the file that contains the information to be
 *                   retrieved. This handle should not be a pipe handle.
 * @param FileAttributes The attributes of the specified file or directory.
 *                       For a list of attribute values and their descriptions,
 *                       see File Attribute Constants. If the function fails,
 *                       the return value is INVALID_FILE_ATTRIBUTES.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetFileAttributes(
    _In_ HANDLE FileHandle,
    _Out_ PDWORD FileAttributes)
{
    FILE_BASIC_INFO BasicInfo;

    if (GetFileInformationByHandleEx(
        FileHandle,
        FileBasicInfo,
        &BasicInfo,
        sizeof(FILE_BASIC_INFO)))
    {
        *FileAttributes = BasicInfo.FileAttributes;
        return S_OK;
    }
    else
    {
        *FileAttributes = INVALID_FILE_ATTRIBUTES;
        return M2GetLastHRESULTErrorKnownFailedCall();
    }
}

/**
 * Sets the attributes for a file or directory.
 *
 * @param FileHandle A handle to the file for which to change information. This
 *                   handle must be opened with the appropriate permissions for
 *                   the requested change. This handle should not be a pipe
 *                   handle.
 * @param FileAttributes The file attributes to set for the file. This
 *                       parameter can be one or more values, combined using
 *                       the bitwise - OR operator. However, all other values
 *                       override FILE_ATTRIBUTE_NORMAL. For more information,
 *                       see the SetFileAttributes function.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2SetFileAttributes(
    _In_ HANDLE FileHandle,
    _In_ DWORD FileAttributes)
{
    FILE_BASIC_INFO BasicInfo = { 0 };
    BasicInfo.FileAttributes =
        FileAttributes & (
            FILE_SHARE_READ |
            FILE_SHARE_WRITE |
            FILE_SHARE_DELETE |
            FILE_ATTRIBUTE_ARCHIVE |
            FILE_ATTRIBUTE_TEMPORARY |
            FILE_ATTRIBUTE_OFFLINE |
            FILE_ATTRIBUTE_NOT_CONTENT_INDEXED |
            FILE_ATTRIBUTE_NO_SCRUB_DATA) |
        FILE_ATTRIBUTE_NORMAL;

    if (SetFileInformationByHandle(
        FileHandle,
        FileBasicInfo,
        &BasicInfo,
        sizeof(FILE_BASIC_INFO)))
    {
        return S_OK;
    }
    else
    {
        return M2GetLastHRESULTErrorKnownFailedCall();
    }
}

/**
 * Retrieves the size of the specified file.
 *
 * @param FileHandle A handle to the file that contains the information to be
 *                   retrieved. This handle should not be a pipe handle.
 * @param FileSize A pointer to a ULONGLONG value that receives the file size,
 *                 in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             GENERIC_READ | SYNCHRONIZE,
 *             FILE_SHARE_READ,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2GetFileSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG FileSize)
{
    FILE_STANDARD_INFO StandardInfo;

    if (GetFileInformationByHandleEx(
        FileHandle,
        FileStandardInfo,
        &StandardInfo,
        sizeof(FILE_STANDARD_INFO)))
    {
        *FileSize = static_cast<ULONGLONG>(
            StandardInfo.EndOfFile.QuadPart);
        return S_OK;
    }
    else
    {
        *FileSize = 0;
        return M2GetLastHRESULTErrorKnownFailedCall();
    }
}

/**
 * Retrieves the amount of space that is allocated for the file.
 *
 * @param FileHandle A handle to the file that contains the information to be
 *                   retrieved. This handle should not be a pipe handle.
 * @param AllocationSize A pointer to a ULONGLONG value that receives the
 *                       amount of space that is allocated for the file, in
 *                       bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             GENERIC_READ | SYNCHRONIZE,
 *             FILE_SHARE_READ,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2GetFileAllocationSize(
    _In_ HANDLE FileHandle,
    _Out_ PULONGLONG AllocationSize)
{
    FILE_STANDARD_INFO StandardInfo;

    if (GetFileInformationByHandleEx(
        FileHandle,
        FileStandardInfo,
        &StandardInfo,
        sizeof(FILE_STANDARD_INFO)))
    {
        *AllocationSize = static_cast<ULONGLONG>(
            StandardInfo.AllocationSize.QuadPart);
        return S_OK;
    }
    else
    {
        *AllocationSize = 0;
        return M2GetLastHRESULTErrorKnownFailedCall();
    }
}

/**
 * Deletes an existing file.
 *
 * @param FileHandle The handle of the file to be deleted.. This handle must be
 *                   opened with the appropriate permissions for the requested
 *                   change. This handle should not be a pipe handle.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             SYNCHRONIZE | DELETE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
 *             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2DeleteFile(
    _In_ HANDLE FileHandle)
{
    FILE_DISPOSITION_INFO DispostionInfo;
    DispostionInfo.DeleteFile = TRUE;

    if (SetFileInformationByHandle(
        FileHandle,
        FileDispositionInfo,
        &DispostionInfo,
        sizeof(FILE_DISPOSITION_INFO)))
    {
        return S_OK;
    }
    else
    {
        return M2GetLastHRESULTErrorKnownFailedCall();
    }
}

/**
 * Deletes an existing file, even the file have the readonly attribute.
 *
 * @param FileHandle The handle of the file to be deleted.. This handle must be
 *                   opened with the appropriate permissions for the requested
 *                   change. This handle should not be a pipe handle.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark The way to get a file handle for this operation:
 *         HANDLE hFile = CreateFileW(
 *             lpFileName,
 *             SYNCHRONIZE | DELETE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
 *             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
 *             nullptr,
 *             OPEN_EXISTING,
 *             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
 *             nullptr);
 */
HRESULT M2DeleteFileIgnoreReadonlyAttribute(
    _In_ HANDLE FileHandle)
{
    HRESULT hr = S_OK;
    DWORD OldAttribute = 0;

    // Save old attributes.
    hr = M2GetFileAttributes(
        FileHandle,
        &OldAttribute);
    if (!SUCCEEDED(hr)) return hr;

    // Remove readonly attribute.
    hr = M2SetFileAttributes(
        FileHandle,
        OldAttribute & (-1 ^ FILE_ATTRIBUTE_READONLY));
    if (!SUCCEEDED(hr)) return hr;

    // Delete the file.
    hr = M2DeleteFile(FileHandle);
    if (!SUCCEEDED(hr))
    {
        // Restore attributes if failed.
        hr = M2SetFileAttributes(
            FileHandle,
            OldAttribute);
    }

    return hr;
}

#pragma endregion

#pragma region Module

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
    _Out_ FARPROC* lpProcAddress,
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName)
{
    *lpProcAddress = GetProcAddress(hModule, lpProcName);
    return (!*lpProcAddress) ? S_OK : M2GetLastHRESULTErrorKnownFailedCall();
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

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Loads the specified module with the optimization of the mitigation of DLL
 * preloading attacks into the address space of the calling process safely. The
 * specified module may cause other modules to be loaded.
 *
 * @param phLibModule A handle to the loaded module.
 * @param lpLibFileName A string that specifies the file name of the module to
 *                      load.
 * @param hFile This parameter is reserved for future use. It must be NULL.
 * @param dwFlags The action to be taken when loading the module.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see LoadLibraryEx.
 */
HRESULT M2LoadLibrary(
    _Out_ HMODULE* phLibModule,
    _In_ LPCWSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags)
{
    *phLibModule = LoadLibraryExW(lpLibFileName, hFile, dwFlags);
    return *phLibModule ? S_OK : M2GetLastHRESULTErrorKnownFailedCall();
}

/**
 * Obtain the best matching resource with the specified type and name in the
 * specified module.
 *
 * @param lpResourceInfo The resource info which contains the pointer and size.
 * @param hModule A handle to the module whose portable executable file or an
 *                accompanying MUI file contains the resource. If this
 *                parameter is NULL, the function searches the module used to
 *                create the current process.
 * @param lpType The resource type. Alternately, rather than a pointer, this
 *               parameter can be MAKEINTRESOURCE(ID), where ID is the integer
 *               identifier of the given resource type.
 * @param lpName The name of the resource. Alternately, rather than a pointer,
 *               this parameter can be MAKEINTRESOURCE(ID), where ID is the
 *               integer identifier of the resource.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2LoadResource(
    _Out_ PM2_RESOURCE_INFO lpResourceInfo,
    _In_opt_ HMODULE hModule,
    _In_ LPCWSTR lpType,
    _In_ LPCWSTR lpName)
{
    if (!lpResourceInfo)
        return E_INVALIDARG;

    lpResourceInfo->Size = 0;
    lpResourceInfo->Pointer = nullptr;

    HRSRC ResourceFind = FindResourceExW(
        hModule, lpType, lpName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    if (!ResourceFind)
        return M2GetLastHRESULTErrorKnownFailedCall();

    lpResourceInfo->Size = SizeofResource(hModule, ResourceFind);

    HGLOBAL ResourceLoad = LoadResource(hModule, ResourceFind);
    if (!ResourceLoad)
        return M2GetLastHRESULTErrorKnownFailedCall();

    lpResourceInfo->Pointer = LockResource(ResourceLoad);

    return S_OK;
}

#endif

#pragma endregion

#pragma region Registry
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Creates the specified registry key. If the key already exists, the function
 * opens it. Note that key names are not case sensitive.
 *
 * @param hKey A handle to an open registry key.
 * @param lpSubKey The name of a subkey that this function opens or creates
 * @param Reserved This parameter is reserved and must be zero.
 * @param lpClass The user-defined class type of this key.
 * @param dwOptions This parameter can be one of the following values:
 *                  REG_OPTION_BACKUP_RESTORE, REG_OPTION_CREATE_LINK,
 *                  REG_OPTION_NON_VOLATILE, REG_OPTION_VOLATILE.
 * @param samDesired A mask that specifies the access rights for the key to be
 *                   created.
 * @param lpSecurityAttributes A pointer to a SECURITY_ATTRIBUTES structure
 *                             that determines whether the returned handle can
 *                             be inherited by child processes.
 * @param phkResult A pointer to a variable that receives a handle to the
 *                  opened or created key.
 * @param lpdwDisposition A pointer to a variable that receives one of the
 *                        following disposition values.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegCreateKeyEx.
 */
HRESULT M2RegCreateKey(
    _In_ HKEY hKey,
    _In_ LPCWSTR lpSubKey,
    _Reserved_ DWORD Reserved,
    _In_opt_ LPWSTR lpClass,
    _In_ DWORD dwOptions,
    _In_ REGSAM samDesired,
    _In_opt_ CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _Out_ PHKEY phkResult,
    _Out_opt_ LPDWORD lpdwDisposition)
{
    return HRESULT_FROM_WIN32(RegCreateKeyExW(
        hKey,
        lpSubKey,
        Reserved,
        lpClass,
        dwOptions,
        samDesired,
        lpSecurityAttributes,
        phkResult,
        lpdwDisposition));
}

/**
 * Retrieves the type and data for the specified value name associated with an
 * open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the registry value.
 * @param lpReserved This parameter is reserved and must be NULL.
 * @param lpType A pointer to a variable that receives a code indicating the
 *              type of data stored in the specified value.
 * @param lpData A pointer to a buffer that receives the value's data.
 * @param lpcbData A pointer to a variable that specifies the size of the
 *                 buffer pointed to by the lpData parameter, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegQueryValueEx.
 */
HRESULT M2RegQueryValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ LPDWORD lpReserved,
    _Out_opt_ LPDWORD lpType,
    _Out_opt_ LPBYTE lpData,
    _Inout_opt_ LPDWORD lpcbData)
{
    return HRESULT_FROM_WIN32(RegQueryValueExW(
        hKey,
        lpValueName,
        lpReserved,
        lpType,
        lpData,
        lpcbData));
}

/**
 * Retrieves the type and data for the specified value name associated with an
 * open registry key.
 *
 * @param hKey A handle to an open registry key.
 * @param lpValueName The name of the value to be set.
 * @param Reserved This parameter is reserved and must be zero.
 * @param dwType The type of data pointed to by the lpData parameter.
 * @param lpData The data to be stored.
 * @param cbData The size of the information pointed to by the lpData
 *               parameter, in bytes.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see RegSetValueEx.
 */
HRESULT M2RegSetValue(
    _In_ HKEY hKey,
    _In_opt_ LPCWSTR lpValueName,
    _Reserved_ DWORD Reserved,
    _In_ DWORD dwType,
    _In_opt_ CONST BYTE* lpData,
    _In_ DWORD cbData)
{
    return HRESULT_FROM_WIN32(RegSetValueExW(
        hKey,
        lpValueName,
        Reserved,
        dwType,
        lpData,
        cbData));
}

#endif
#pragma endregion

#pragma region Service
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

/**
 * Starts a service if not started and retrieves the current status of the
 * specified service.
 *
 * @param lpServiceName The name of the service to be started. This is the name
 *                      specified by the lpServiceName parameter of the
 *                      CreateService function when the service object was
 *                      created, not the service display name that is shown by
 *                      user interface applications to identify the service.
 *                      The maximum string length is 256 characters. The
 *                      service control manager database preserves the case of
 *                      the characters, but service name comparisons are always
 *                      case insensitive. Forward-slash (/) and backslash ()
 *                      are invalid service name characters.
 * @param lpServiceStatus Contains process status information for a service.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2StartService(
    _In_ LPCWSTR lpServiceName,
    _Out_ LPSERVICE_STATUS_PROCESS lpServiceStatus)
{
    memset(lpServiceStatus, 0, sizeof(LPSERVICE_STATUS_PROCESS));

    M2::CServiceHandle hSCM;
    M2::CServiceHandle hService;

    DWORD nBytesNeeded = 0;
    DWORD nOldCheckPoint = 0;
    ULONGLONG nLastTick = 0;
    bool bStartServiceWCalled = false;

    hSCM = OpenSCManagerW(
        nullptr,
        nullptr,
        SC_MANAGER_CONNECT);
    if (!hSCM)
        return M2GetLastHRESULTErrorKnownFailedCall();

    hService = OpenServiceW(
        hSCM,
        lpServiceName,
        SERVICE_QUERY_STATUS | SERVICE_START);
    if (!hService)
        return M2GetLastHRESULTErrorKnownFailedCall();

    while (QueryServiceStatusEx(
        hService,
        SC_STATUS_PROCESS_INFO,
        reinterpret_cast<LPBYTE>(lpServiceStatus),
        sizeof(SERVICE_STATUS_PROCESS),
        &nBytesNeeded))
    {
        if (SERVICE_STOPPED == lpServiceStatus->dwCurrentState)
        {
            // Failed if the service had stopped again.
            if (bStartServiceWCalled)
                return E_FAIL;

            if (!StartServiceW(hService, 0, nullptr))
                return M2GetLastHRESULTErrorKnownFailedCall();

            bStartServiceWCalled = true;
        }
        else if (
            SERVICE_STOP_PENDING == lpServiceStatus->dwCurrentState ||
            SERVICE_START_PENDING == lpServiceStatus->dwCurrentState)
        {
            ULONGLONG nCurrentTick = GetTickCount64();

            if (!nLastTick)
            {
                nLastTick = nCurrentTick;
                nOldCheckPoint = lpServiceStatus->dwCheckPoint;

                // Same as the .Net System.ServiceProcess, wait 250ms.
                SleepEx(250, FALSE);
            }
            else
            {
                // Check the timeout if the checkpoint is not increased.
                if (lpServiceStatus->dwCheckPoint <= nOldCheckPoint)
                {
                    ULONGLONG nDiff = nCurrentTick - nLastTick;
                    if (nDiff > lpServiceStatus->dwWaitHint)
                    {
                        return __HRESULT_FROM_WIN32(ERROR_TIMEOUT);
                    }
                }

                // Continue looping.
                nLastTick = 0;
            }
        }
        else
        {
            break;
        }
    }

    return S_OK;
}

#endif
#pragma endregion

#pragma region Environment

/**
 * Expands environment-variable strings and replaces them with the values
 * defined for the current user.
 *
 * @param ExpandedString The expanded string.
 * @param VariableName The environment-variable string you need to expand.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2ExpandEnvironmentStrings(
    std::wstring& ExpandedString,
    const std::wstring& VariableName)
{
    HRESULT hr = S_OK;

    do
    {
        DWORD Length = ExpandEnvironmentStringsW(
            VariableName.c_str(),
            nullptr,
            0);
        if (0 == Length)
        {
            hr = M2GetLastHRESULTErrorKnownFailedCall();
            break;
        }

        ExpandedString.resize(Length - 1);

        Length = ExpandEnvironmentStringsW(
            VariableName.c_str(),
            &ExpandedString[0],
            static_cast<DWORD>(ExpandedString.size() + 1));
        if (0 == Length)
        {
            hr = M2GetLastHRESULTErrorKnownFailedCall();
            break;
        }
        if (ExpandedString.size() != Length - 1)
        {
            hr = E_UNEXPECTED;
            break;
        }

    } while (false);

    if (FAILED(hr))
    {
        ExpandedString.clear();
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
            hr = M2GetLastHRESULTErrorKnownFailedCall();
            break;
        }

        WindowsFolderPath.resize(Length - 1);

        Length = GetSystemWindowsDirectoryW(
            &WindowsFolderPath[0],
            static_cast<UINT>(Length));
        if (0 == Length)
        {
            hr = M2GetLastHRESULTErrorKnownFailedCall();
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

#endif

#pragma endregion
