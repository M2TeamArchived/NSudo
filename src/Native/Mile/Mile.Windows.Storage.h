/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Storage.h
 * PURPOSE:   Storage Definition for Windows
 *
 * LICENSE:   Apache-2.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS_STORAGE
#define MILE_WINDOWS_STORAGE

#if (defined(__cplusplus) && __cplusplus >= 201703L)
#elif (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
#else
#error "[Mile] You should use a C++ compiler with the C++17 standard."
#endif

#include <Windows.h>

namespace Mile::Windows::Storage
{
    /**
     * @brief The definition of the file enumerator handle.
    */
    typedef void* FILE_ENUMERATOR_HANDLE;

    /**
     * @brief The information about a found file or directory queried from the
     *        file enumerator.
    */
    typedef struct _FILE_ENUMERATOR_INFORMATION
    {
        FILETIME CreationTime;
        FILETIME LastAccessTime;
        FILETIME LastWriteTime;
        FILETIME ChangeTime;
        UINT64 FileSize;
        UINT64 AllocationSize;
        DWORD FileAttributes;
        DWORD EaSize;
        LARGE_INTEGER FileId;
        WCHAR ShortName[16];
        WCHAR FileName[256];
    } FILE_ENUMERATOR_INFORMATION, * PFILE_ENUMERATOR_INFORMATION;

    /**
     * @brief Creates a file enumerator handle for searching a directory for a
     *        file or subdirectory with a name.
     * @param FileHandle The handle of the file to be searched a directory for
     *                   a file or subdirectory with a name. This handle must
     *                   be opened with the appropriate permissions for the
     *                   requested change. This handle should not be a pipe
     *                   handle.
     * @return If the function succeeds, the return value is a file enumerator
     *         handle used in a subsequent call to QueryFileEnumerator or
     *         CloseFileEnumerator. If the function fails, the return value is
     *         nullptr. To get extended error information, call GetLastError.
    */
    FILE_ENUMERATOR_HANDLE CreateFileEnumerator(
        _In_ HANDLE FileHandle);

    /**
     * @brief Closes a file enumerator handle opened by CreateFileEnumerator.
     * @param FileEnumeratorHandle The file enumerator handle.
     * @return If the function succeeds, the return value is nonzero. If the
     *         function fails, the return value is zero. To get extended error
     *         information, call GetLastError.
    */
    BOOL CloseFileEnumerator(
        _In_ FILE_ENUMERATOR_HANDLE FileEnumeratorHandle);

    /**
     * @brief Starts or continues a file search from a file enumerator handle.
     * @param FileEnumeratorHandle The file enumerator handle.
     * @param FileEnumeratorInformation A pointer to the
     *                                  FILE_ENUMERATOR_INFORMATION structure
     *                                  that receives information about a found
     *                                  file or directory.
     * @return If the function succeeds, the return value is nonzero and the
     *         FileEnumeratorInformation parameter contains information about
     *         the next file or directory found. If the function fails, the
     *         return value is zero and the contents of
     *         FileEnumeratorInformation are indeterminate. To get extended
     *         error information, call the GetLastError function. If the
     *         function fails because no more matching files can be found,
     *         the GetLastError function returns ERROR_NO_MORE_FILES.
    */
    BOOL QueryFileEnumerator(
        _In_ FILE_ENUMERATOR_HANDLE FileEnumeratorHandle,
        _Out_ PFILE_ENUMERATOR_INFORMATION FileEnumeratorInformation);
}

#endif // !MILE_WINDOWS_STORAGE
