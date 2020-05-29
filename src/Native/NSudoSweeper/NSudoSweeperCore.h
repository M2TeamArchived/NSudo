/*
 * PROJECT:   NSudo Sweeper
 * FILE:      NSudoSweeperCore.h
 * PURPOSE:   NSudo Sweeper Core Definition  for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef NSUDO_SWEEPER_CORE

#include <Windows.h>

/**
 * The message used to report the progress.
 *
 * @param A pointer to a DWORD type variable that receives the reported
 *        progress.
 */
#define NSUDO_SWEEPER_PROGRESS_MESSAGE 0x00000001

/**
 * A user-defined function that NSudo Sweeper API uses to report something.
 *
 * @param Message The message.
 * @param Parameter A pointer to the additional message information. The
 *                  contents of this parameter depend on the value of the
 *                  Message parameter.
 * @param UserData User defined custom data.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
typedef HRESULT(WINAPI* NSudoSweeperCallback)(
    _In_ DWORD Message,
    _In_opt_ LPVOID Parameter,
    _In_opt_ LPVOID UserData);

/**
 * The NSudo Sweeper cleanup handler.
 *
 * @param Configuration A TOML configuration string that holds the information
 *                      about the cleanup handler.
 * @param SessionRootPath An absolute path with end of the backslash to the
 *                        root directory of a Windows image which you want to
 *                        operate. You can only use backslashes in this name.
 *                        For example, you can use "C:\\" and "C:\\Image\\". If
 *                        the pointer is NULL, the function will operate the
 *                        online Windows image.
 * @param EstimatedFreedSize A pointer to a variable that receives the size the
 *                           cleanup handler can free. If the pointer is NULL,
 *                           the cleanup handler will start cleaning.
 * @param Callback A pointer to a user-defined NSudoSweeperCallback.
 * @param UserData User defined custom data used by the Callback parameter.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
typedef HRESULT(WINAPI* NSudoSweeperCleanupHandler)(
    _In_ LPCWSTR Configuration,
    _In_opt_ LPCWSTR SessionRootPath,
    _Out_opt_ PUINT64 EstimatedFreedSize,
    _In_opt_ NSudoSweeperCallback Callback,
    _In_opt_ LPVOID UserData);

/**
 * Checks the root path whether is associate with an online Windows image.
 *
 * @param SessionRootPath An absolute path with end of the backslash to the
 *                        root directory of a Windows image which you want to
 *                        operate. You can only use backslashes in this name.
 *                        For example, you can use "C:\\" and "C:\\Image\\". If
 *                        the pointer is NULL, the function will operate the
 *                        online Windows image.
 * @return Returns TRUE if the root path is associate with an online Windows
 *         image. Otherwise, returns FALSE.
 */
BOOL WINAPI NSudoSweeperIsOnlineImage(
    _In_ LPCWSTR SessionRootPath);

/**
 * The NSudo Sweeper System Restore Point cleanup handler.
 *
 * @param Configuration A TOML configuration string that holds the information
 *                      about the cleanup handler.
 * @param SessionRootPath An absolute path with end of the backslash to the
 *                        root directory of a Windows image which you want to
 *                        operate. You can only use backslashes in this name.
 *                        For example, you can use "C:\\" and "C:\\Image\\". If
 *                        the pointer is NULL, the function will operate the
 *                        online Windows image.
 * @param EstimatedFreedSize A pointer to a variable that receives the size the
 *                           cleanup handler can free. If the pointer is NULL,
 *                           the cleanup handler will start cleaning.
 * @param Callback A pointer to a user-defined NSudoSweeperCallback.
 * @param UserData User defined custom data used by the Callback parameter.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI NSudoSweeperSystemRestorePointCleanupHandler(
    _In_ LPCWSTR Configuration,
    _In_opt_ LPCWSTR SessionRootPath,
    _Out_opt_ PUINT64 EstimatedFreedSize,
    _In_opt_ NSudoSweeperCallback Callback,
    _In_opt_ LPVOID UserData);

#endif // !NSUDO_SWEEPER_CORE
