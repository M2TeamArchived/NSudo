/*
 * PROJECT:   NSudo Shared Library
 * FILE:      NSudoAPI.h
 * PURPOSE:   Definition for NSudo Shared Library
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef NSUDO_API
#define NSUDO_API

#ifndef __cplusplus
#error "[NSudoAPI] You should use a C++ compiler."
#endif

#include <Windows.h>

/**
* Contains values that specify the type of user mode.
*/
typedef enum class _NSUDO_USER_MODE_TYPE
{
    DEFAULT,
    TRUSTED_INSTALLER,
    SYSTEM,
    CURRENT_USER,
    CURRENT_PROCESS,
    CURRENT_PROCESS_DROP_RIGHT,
    CURRENT_USER_ELEVATED, // Since NSudo 8.0.2
} NSUDO_USER_MODE_TYPE, *PNSUDO_USER_MODE_TYPE;

/**
* Contains values that specify the type of privileges mode.
*/
typedef enum class _NSUDO_PRIVILEGES_MODE_TYPE
{
    DEFAULT,
    ENABLE_ALL_PRIVILEGES,
    DISABLE_ALL_PRIVILEGES
} NSUDO_PRIVILEGES_MODE_TYPE, *PNSUDO_PRIVILEGES_MODE_TYPE;

/**
 * Contains values that specify the type of mandatory label.
 */
typedef enum class _NSUDO_MANDATORY_LABEL_TYPE
{
    UNTRUSTED,
    LOW,
    MEDIUM,
    MEDIUM_PLUS,
    HIGH,
    SYSTEM,
    PROTECTED_PROCESS,
} NSUDO_MANDATORY_LABEL_TYPE, *PNSUDO_MANDATORY_LABEL_TYPE;

/**
 * Contains values that specify the type of process priority class.
 */
typedef enum class _NSUDO_PROCESS_PRIORITY_CLASS_TYPE
{
    IDLE,
    BELOW_NORMAL,
    NORMAL,
    ABOVE_NORMAL,
    HIGH,
    REALTIME,
} NSUDO_PROCESS_PRIORITY_CLASS_TYPE, *PNSUDO_PROCESS_PRIORITY_CLASS_TYPE;

/**
* Contains values that specify the type of ShowWindow mode.
*/
typedef enum class _NSUDO_SHOW_WINDOW_MODE_TYPE
{
    DEFAULT,
    SHOW,
    HIDE,
    MAXIMIZE,
    MINIMIZE,
} NSUDO_SHOW_WINDOW_MODE_TYPE, *PNSUDO_SHOW_WINDOW_MODE_TYPE;

/**
 * Creates a new process and its primary thread.
 *
 * @param UserModeType A value from the NSUDO_USER_MODE_TYPE enumerated type
 *                     that identifies the user mode.
 * @param PrivilegesModeType A value from the NSUDO_PRIVILEGES_MODE_TYPE
 *                           enumerated type that identifies the privileges
 *                           mode.
 * @param MandatoryLabelType A value from the NSUDO_MANDATORY_LABEL_TYPE
 *                           enumerated type that identifies the mandatory
 *                           label.
 * @param ProcessPriorityClassType A value from the
 *                                 NSUDO_PROCESS_PRIORITY_CLASS_TYPE enumerated
 *                                 type that identifies the process priority
 *                                 class.
 * @param ShowWindowModeType A value from the NSUDO_SHOW_WINDOW_MODE_TYPE
 *                           enumerated type that identifies the ShowWindow
 *                           mode.
 * @param WaitInterval The time-out interval for waiting the process, in
 *                     milliseconds. 
 * @param CreateNewConsole If this parameter is TRUE, the new process has a new
 *                         console, instead of inheriting its parent's console
 *                         (the default).
 * @param CommandLine The command line to be executed. The maximum length of
 *                    this string is 32K characters, the module name portion of
 *                    CommandLine is limited to MAX_PATH characters.
 * @param CurrentDirectory The full path to the current directory for the
 *                         process. The string can also specify a UNC path. If
 *                         this parameter is nullptr, the new process will
 *                         the same current drive and directory as the calling
 *                         process. (This feature is provided primarily for
 *                         shells that need to start an application and specify
 *                         its initial drive and working directory.)
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI NSudoCreateProcess(
    _In_ NSUDO_USER_MODE_TYPE UserModeType,
    _In_ NSUDO_PRIVILEGES_MODE_TYPE PrivilegesModeType,
    _In_ NSUDO_MANDATORY_LABEL_TYPE MandatoryLabelType,
    _In_ NSUDO_PROCESS_PRIORITY_CLASS_TYPE ProcessPriorityClassType,
    _In_ NSUDO_SHOW_WINDOW_MODE_TYPE ShowWindowModeType,
    _In_ DWORD WaitInterval,
    _In_ BOOL CreateNewConsole,
    _In_ LPCWSTR CommandLine,
    _In_opt_ LPCWSTR CurrentDirectory);

#endif
