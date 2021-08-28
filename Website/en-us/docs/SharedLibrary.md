# NSudo Shared Library

## NSudoCreateProcess function

Creates a new process and its primary thread.

### C/C++ prototype

```cpp
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
```

### UserModeType parameter

A value from the NSUDO_USER_MODE_TYPE enumerated type that identifies the user
mode.

```cpp
typedef enum class _NSUDO_USER_MODE_TYPE
{
    DEFAULT,
    TRUSTED_INSTALLER,
    SYSTEM,
    CURRENT_USER,
    CURRENT_PROCESS,
    CURRENT_PROCESS_DROP_RIGHT
} NSUDO_USER_MODE_TYPE, *PNSUDO_USER_MODE_TYPE;
```

### PrivilegesModeType parameter

A value from the NSUDO_PRIVILEGES_MODE_TYPE enumerated type that identifies the
privileges mode.

```cpp
typedef enum class _NSUDO_PRIVILEGES_MODE_TYPE
{
    DEFAULT,
    ENABLE_ALL_PRIVILEGES,
    DISABLE_ALL_PRIVILEGES
} NSUDO_PRIVILEGES_MODE_TYPE, *PNSUDO_PRIVILEGES_MODE_TYPE;
```

### MandatoryLabelType parameter

A value from the NSUDO_MANDATORY_LABEL_TYPE enumerated type that identifies the
mandatory label.

```cpp
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
```

### ProcessPriorityClassType parameter

A value from the NSUDO_PROCESS_PRIORITY_CLASS_TYPE enumerated type that 
identifies the process priority class.

```cpp
typedef enum class _NSUDO_PROCESS_PRIORITY_CLASS_TYPE
{
    IDLE,
    BELOW_NORMAL,
    NORMAL,
    ABOVE_NORMAL,
    HIGH,
    REALTIME,
} NSUDO_PROCESS_PRIORITY_CLASS_TYPE, *PNSUDO_PROCESS_PRIORITY_CLASS_TYPE;
```

### ShowWindowModeType parameter

A value from the NSUDO_SHOW_WINDOW_MODE_TYPE enumerated type that identifies 
the ShowWindow mode.

```cpp
typedef enum class _NSUDO_SHOW_WINDOW_MODE_TYPE
{
    DEFAULT,
    SHOW,
    HIDE,
    MAXIMIZE,
    MINIMIZE,
} NSUDO_SHOW_WINDOW_MODE_TYPE, *PNSUDO_SHOW_WINDOW_MODE_TYPE;
```

### WaitInterval parameter

The time-out interval for waiting the process, in milliseconds. 

### CreateNewConsole parameter

If this parameter is TRUE, the new process has a new console, instead of 
inheriting its parent's console (the default).

### CommandLine parameter

The command line to be executed. The maximum length of this string is 32K 
characters, the module name portion of CommandLine is limited to MAX_PATH 
characters.

### CurrentDirectory parameter

The full path to the current directory for the process. The string can also
specify a UNC path. If this parameter is nullptr, the new process will the same
current drive and directory as the calling process. (This feature is provided
primarily for shells that need to start an application and specify its initial
drive and working directory.)

### Return value

HRESULT. If the function succeeds, the return value is S_OK.

## C# API

Load the M2.NSudo assembly to your project, you will know the usage.

### Example

```csharp
using System;

namespace M2.NSudo.Demo
{
    class Program
    {
        static void Main(string[] args)
        {
            NSudoInstance instance = new NSudoInstance();

            instance.CreateProcess(
                NSUDO_USER_MODE_TYPE.TRUSTED_INSTALLER,
                NSUDO_PRIVILEGES_MODE_TYPE.ENABLE_ALL_PRIVILEGES,
                NSUDO_MANDATORY_LABEL_TYPE.SYSTEM,
                NSUDO_PROCESS_PRIORITY_CLASS_TYPE.NORMAL,
                NSUDO_SHOW_WINDOW_MODE_TYPE.DEFAULT,
                0,
                true,
                "cmd",
                null);

            Console.ReadKey();
        }
    }
}
```
