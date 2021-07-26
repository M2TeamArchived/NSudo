/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MouriOptimizationPlugin.h
 * PURPOSE:   Private definition for Mouri Optimization Plugin
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MOURI_OPTIMIZATION_PLUGIN
#define MOURI_OPTIMIZATION_PLUGIN

#include <Mile.Windows.h>
#include <NSudoContextPlugin.h>

#include <vector>
#include <string>

/**
 * @brief Writes the formatted data, followed by the current line terminator,
 *        to the NSudo user interface.
 * @param Context The NSudo context.
 * @param Format Format-control string.
 * @param ... Optional arguments to be formatted.
*/
void MoPrivateWriteLine(
    _In_ PNSUDO_CONTEXT Context,
    _In_z_ _Printf_format_string_ wchar_t const* const Format,
    ...);

/**
 * @brief Writes the error message to the NSudo user interface.
 * @param Context The NSudo context.
 * @param hr The HResult object containing the error code.
 * @param Format Format-control string.
 * @param ... Optional arguments to be formatted.
*/
void MoPrivateWriteErrorMessage(
    _In_ PNSUDO_CONTEXT Context,
    _In_ Mile::HResult const& hr,
    _In_z_ _Printf_format_string_ wchar_t const* const Format,
    ...);

/**
 * @brief Writes the final result to the NSudo user interface.
 * @param Context The NSudo context.
 * @param hr The HResult object containing the error code.
*/
void MoPrivateWriteFinalResult(
    _In_ PNSUDO_CONTEXT Context,
    _In_ Mile::HResult const& hr);

/**
 * @brief Prints the pruge scan result to the NSudo user interface.
 * @param Context The NSudo context.
 * @param ByteSize The numeric byte size value to be converted.
*/
void MoPrivatePrintPurgeScanResult(
    _In_ PNSUDO_CONTEXT Context,
    _In_ std::uint64_t ByteSize);

#define MO_PRIVATE_PURGE_MODE_SCAN    1
#define MO_PRIVATE_PURGE_MODE_PURGE   2
#define MO_PRIVATE_PURGE_MODE_QUERY   3
#define MO_PRIVATE_PURGE_MODE_ENABLE  4
#define MO_PRIVATE_PURGE_MODE_DISABLE 5

/**
 * @brief Parses the purge mode from context plugin command arguments or the
 *        user input.
 * @param Context The NSudo context.
 * @return The purge mode, it can be zero or one of the following values.
 *         MO_PRIVATE_PURGE_MODE_SCAN
 *             Do scanning.
 *         MO_PRIVATE_PURGE_MODE_PURGE
 *             Do purging.
*/
DWORD MoPrivateParsePurgeMode(
    _In_ PNSUDO_CONTEXT Context);

/**
 * @brief Enables backup and restore privilege to the access token that
 *        impersonates the security context of the calling process. The
 *        token is assigned to the calling thread.
 * @param PreviousContextTokenHandle The previous access token that
 *                                   impersonates the security context
 *                                   of the calling thread for restoring
 *                                   by SetThreadToken.
 * @return An HResult object containing the error code.
*/
Mile::HResult MoPrivateEnableBackupRestorePrivilege(
    _Out_ PHANDLE PreviousContextTokenHandle);

/**
 * @brief Gets user profile path list for the local computer.
 * @return The user profile path list for the local computer.
*/
std::vector<std::wstring> MoPrivateGetProfilePathList();

/**
 * @brief Creates or opens a file, directory or drive with long path support.
 *        The function returns a handle that can be used to access the file,
 *        directory or drive depending on the flags and attributes specified.
 * @param lpFileName The name of the file or device to be created or opened.
 *                   You may use either forward slashes (/) or backslashes ()
 *                   in this name.
 * @param dwDesiredAccess The requested access to the file or device, which can
 *                        be summarized as read, write, both or neither zero).
 * @param dwShareMode The requested sharing mode of the file or device, which
 *                    can be read, write, both, delete, all of these, or none
 *                    (refer to the following table). Access requests to
 *                    attributes or extended attributes are not affected by
 *                    this flag.
 * @param lpSecurityAttributes A pointer to a SECURITY_ATTRIBUTES structure
 *                             that contains two separate but related data
 *                             members: an optional security descriptor, and a
 *                             Boolean value that determines whether the
 *                             returned handle can be inherited by child
 *                             processes. This parameter can be NULL.
 * @param dwCreationDisposition An action to take on a file or device that
 *                              exists or does not exist.
 * @param dwFlagsAndAttributes The file or device attributes and flags,
 *                             FILE_ATTRIBUTE_NORMAL being the most common
 *                             default value for files.
 * @param hTemplateFile A valid handle to a template file with the GENERIC_READ
 *                      access right. The template file supplies file
 *                      attributes and extended attributes for the file that is
 *                      being created. This parameter can be NULL.
 * @return If the function succeeds, the return value is an open handle to
 *         the specified file, directory or drive. If the function fails,
 *         the return value is INVALID_HANDLE_VALUE. To get extended error
 *         information, call GetLastError.
 * @remark For more information, see CreateFileW.
*/
HANDLE MoPrivateCreateFile(
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile);

/**
 * @brief Tests for the existence of the file or directory.
 * @param FilePath The path of the file or directory for testing.
 * @return Nonzero if the found file. Otherwise zero.
*/
BOOL MoPrivateIsFileExist(
    _In_ LPCWSTR FilePath);

/**
 * @brief Splits the traditional DOS path string by the directory separator character.
 * @param String The traditional DOS path string you want to split.
 * @return The split result of the traditional DOS path string.
*/
std::vector<std::wstring> MoPrivateSplitPathString(
    std::wstring const& String);

/**
 * @brief Removes an existing file.
 * @param Context The NSudo context.
 * @param RootPath The existing file you want to remove.
 * @param UsedSpace If nullptr, the function will in the purge mode. If
 *                  non-nullptr, the function will in the scan mode and
 *                  accumulate the value of used space for the directory.
*/
void MoPrivateRemoveFileWorker(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCWSTR FilePath,
    _Inout_opt_ PUINT64 UsedSpace);

/**
 * @brief Empties an existing directory.
 * @param Context The NSudo context.
 * @param RootPath The existing directory you want to empty.
 * @param UsedSpace If nullptr, the function will in the purge mode. If
 *                  non-nullptr, the function will in the scan mode and
 *                  accumulate the value of used space for the directory.
*/
void MoPrivateEmptyDirectoryWorker(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCWSTR RootPath,
    _Inout_opt_ PUINT64 UsedSpace);

/**
 * @brief Removes an existing directory.
 * @param Context The NSudo context.
 * @param RootPath The existing directory you want to remove.
 * @param UsedSpace If nullptr, the function will in the purge mode. If
 *                  non-nullptr, the function will in the scan mode and
 *                  accumulate the value of used space for the directory.
*/
void MoPrivateRemoveDirectoryWorker(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCWSTR RootPath,
    _Inout_opt_ PUINT64 UsedSpace);

#endif // !MOURI_OPTIMIZATION_PLUGIN
