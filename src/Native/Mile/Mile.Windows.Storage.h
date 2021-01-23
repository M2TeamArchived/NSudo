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
     * @brief Sends a control code directly to a specified device driver,
     *        causing the corresponding device to perform the corresponding
     *        operation.
     * @param hDevice A handle to the device on which the operation is to be
     *                performed. The device is typically a volume, directory,
     *                file, or stream. To retrieve a device handle, use the
     *                CreateFile function.
     * @param dwIoControlCode The control code for the operation. This value
     *                        identifies the specific operation to be performed
     *                        and the type of device on which to perform it.
     * @param lpInBuffer A pointer to the input buffer that contains the data
     *                   required to perform the operation. The format of this
     *                   data depends on the value of the dwIoControlCode
     *                   parameter. This parameter can be nullptr if
     *                   dwIoControlCode specifies an operation that does not
     *                   require input data.
     * @param nInBufferSize The size of the input buffer, in bytes.
     * @param lpOutBuffer A pointer to the output buffer that is to receive the
     *                    data returned by the operation. The format of this
     *                    data depends on the value of the dwIoControlCode
     *                    parameter. This parameter can be nullptr if
     *                    dwIoControlCode specifies an operation that does not
     *                    return data.
     * @param nOutBufferSize The size of the output buffer, in bytes.
     * @param lpBytesReturned A pointer to a variable that receives the size of
     *                        the data stored in the output buffer, in bytes.
     *                        If the output buffer is too small to receive any
     *                        data, the call fails, GetLastError returns
     *                        ERROR_INSUFFICIENT_BUFFER, and lpBytesReturned is
     *                        zero. If the output buffer is too small to hold
     *                        all of the data but can hold some entries, some
     *                        drivers will return as much data as fits. In this
     *                        case, the call fails, GetLastError returns
     *                        ERROR_MORE_DATA, and lpBytesReturned indicates
     *                        the amount of data received. Your application
     *                        should call DeviceIoControl again with the same
     *                        operation, specifying a new starting point.
     * @return If the operation completes successfully, the return value is
     *         nonzero. If the operation fails or is pending, the return value
     *         is zero. To get extended error information, call GetLastError.
     * @remark For more information, see DeviceIoControl.
    */
    BOOL DeviceIoControl(
        _In_ HANDLE hDevice,
        _In_ DWORD dwIoControlCode,
        _In_opt_ LPVOID lpInBuffer,
        _In_ DWORD nInBufferSize,
        _Out_opt_ LPVOID lpOutBuffer,
        _In_ DWORD nOutBufferSize,
        _Out_opt_ LPDWORD lpBytesReturned); 

    /**
     * @brief Gets the NTFS compression attribute.
     * @param FileHandle A handle to the file or directory on which the
     *                   operation is to be performed. To retrieve a handle,
     *                   use the CreateFile or a similar API.
     * @param CompressionAlgorithm Specifies the compression algorithm that is
     *                             used to compress this file. Currently
     *                             defined algorithms are:
     *                             COMPRESSION_FORMAT_NONE
     *                                 Uncompress the file or directory.
     *                             COMPRESSION_FORMAT_DEFAULT
     *                                 Compress the file or directory, using
     *                                 the default compression format.
     *                             COMPRESSION_FORMAT_LZNT1
     *                                 Compress the file or directory, using
     *                                 the LZNT1 compression format.
     * @return If the operation completes successfully, the return value is
     *         nonzero. If the operation fails or is pending, the return value
     *         is zero. To get extended error information, call GetLastError.
    */
    BOOL GetNtfsCompressionAttribute(
        _In_ HANDLE FileHandle,
        _Out_ PUSHORT CompressionAlgorithm);

    /**
     * @brief Sets the NTFS compression attribute.
     * @param FileHandle A handle to the file or directory on which the
     *                   operation is to be performed. To retrieve a handle,
     *                   use the CreateFile or a similar API.
     * @param CompressionAlgorithm Specifies the compression algorithm that is
     *                             used to compress this file. Currently
     *                             defined algorithms are:
     *                             COMPRESSION_FORMAT_NONE
     *                                 Uncompress the file or directory.
     *                             COMPRESSION_FORMAT_DEFAULT
     *                                 Compress the file or directory, using
     *                                 the default compression format.
     *                             COMPRESSION_FORMAT_LZNT1
     *                                 Compress the file or directory, using
     *                                 the LZNT1 compression format.
     * @return If the operation completes successfully, the return value is
     *         nonzero. If the operation fails or is pending, the return value
     *         is zero. To get extended error information, call GetLastError.
    */
    BOOL SetNtfsCompressionAttribute(
        _In_ HANDLE FileHandle,
        _In_ USHORT CompressionAlgorithm);

    /**
     * @brief Gets the Windows Overlay Filter file compression attribute.
     * @param FileHandle A handle to the file on which the operation is to be
     *                   performed. To retrieve a handle, use the CreateFile or
     *                   a similar API.
     * @param CompressionAlgorithm Specifies the compression algorithm that is
     *                             used to compress this file. Currently
     *                             defined algorithms are:
     *                             FILE_PROVIDER_COMPRESSION_XPRESS4K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 4kb chunks with
     *                                 the XPress algorithm. This algorithm is
     *                                 designed to be computationally
     *                                 lightweight, and provides for rapid
     *                                 access to data.
     *                             FILE_PROVIDER_COMPRESSION_LZX
     *                                 Indicates that the data for the file
     *                                 should be compressed in 32kb chunks with
     *                                 the LZX algorithm. This algorithm is
     *                                 designed to be highly compact, and
     *                                 provides for small footprint for
     *                                 infrequently accessed data.
     *                             FILE_PROVIDER_COMPRESSION_XPRESS8K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 8kb chunks with
     *                                 the XPress algorithm.
     *                             FILE_PROVIDER_COMPRESSION_XPRESS16K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 16kb chunks with
     *                                 the XPress algorithm.
     * @return If the operation completes successfully, the return value is
     *         nonzero. If the operation fails or is pending, the return value
     *         is zero. To get extended error information, call GetLastError.
    */
    BOOL GetWofCompressionAttribute(
        _In_ HANDLE FileHandle,
        _Out_ PDWORD CompressionAlgorithm); 

    /**
     * @brief Sets the Windows Overlay Filter file compression attribute.
     * @param FileHandle A handle to the file on which the operation is to be
     *                   performed. To retrieve a handle, use the CreateFile or
     *                   a similar API.
     * @param CompressionAlgorithm Specifies the compression algorithm that is
     *                             used to compress this file. Currently
     *                             defined algorithms are:
     *                             FILE_PROVIDER_COMPRESSION_XPRESS4K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 4kb chunks with
     *                                 the XPress algorithm. This algorithm is
     *                                 designed to be computationally
     *                                 lightweight, and provides for rapid
     *                                 access to data.
     *                             FILE_PROVIDER_COMPRESSION_LZX
     *                                 Indicates that the data for the file
     *                                 should be compressed in 32kb chunks with
     *                                 the LZX algorithm. This algorithm is
     *                                 designed to be highly compact, and
     *                                 provides for small footprint for
     *                                 infrequently accessed data.
     *                             FILE_PROVIDER_COMPRESSION_XPRESS8K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 8kb chunks with
     *                                 the XPress algorithm.
     *                             FILE_PROVIDER_COMPRESSION_XPRESS16K
     *                                 Indicates that the data for the file
     *                                 should be compressed in 16kb chunks with
     *                                 the XPress algorithm.
     * @return If the operation completes successfully, the return value is
     *         nonzero. If the operation fails or is pending, the return value
     *         is zero. To get extended error information, call GetLastError.
    */
    BOOL SetWofCompressionAttribute(
        _In_ HANDLE FileHandle,
        _In_ DWORD CompressionAlgorithm); 

    /**
     * @brief Removes the Windows Overlay Filter file compression attribute.
     * @param FileHandle A handle to the file on which the operation is to be
     *                   performed. To retrieve a handle, use the CreateFile or
     *                   a similar API.
     * @return If the operation completes successfully, the return value is
     *         nonzero. If the operation fails or is pending, the return value
     *         is zero. To get extended error information, call GetLastError.
    */
    BOOL RemoveWofCompressionAttribute(
        _In_ HANDLE FileHandle);

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
