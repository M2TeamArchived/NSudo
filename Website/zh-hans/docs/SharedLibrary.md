# NSudo 共享库

## NSudoCreateProcess 函数

创建一个新进程和对应的主线程。

### C/C++ 函数原型

```
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

### UserModeType 参数

一个类型为 NSUDO_USER_MODE_TYPE 枚举类型的值, 用以表示用户类别。

```
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

### PrivilegesModeType 参数

一个类型为 NSUDO_PRIVILEGES_MODE_TYPE 枚举类型的值, 用以表示特权类型。

```
typedef enum class _NSUDO_PRIVILEGES_MODE_TYPE
{
    DEFAULT,
    ENABLE_ALL_PRIVILEGES,
    DISABLE_ALL_PRIVILEGES
} NSUDO_PRIVILEGES_MODE_TYPE, *PNSUDO_PRIVILEGES_MODE_TYPE;
```

### MandatoryLabelType 参数

一个类型为 NSUDO_MANDATORY_LABEL_TYPE 枚举类型的值, 用以表示完整性标签。

```
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

### ProcessPriorityClassType 参数

一个类型为 NSUDO_PROCESS_PRIORITY_CLASS_TYPE 枚举类型的值, 用以表示进程优先级。

```
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

### ShowWindowModeType 参数

一个类型为 NSUDO_SHOW_WINDOW_MODE_TYPE 枚举类型的值, 用以表示显示窗口模式。

```
typedef enum class _NSUDO_SHOW_WINDOW_MODE_TYPE
{
    DEFAULT,
    SHOW,
    HIDE,
    MAXIMIZE,
    MINIMIZE,
} NSUDO_SHOW_WINDOW_MODE_TYPE, *PNSUDO_SHOW_WINDOW_MODE_TYPE;
```

### WaitInterval 参数

等待创建的进程的时间 (毫秒)。

### CreateNewConsole 参数

如果这个参数设为 TRUE, 新进程则在新的控制台窗口运行, 否则则直接在父进程对应的控
制台窗口运行 (默认设定)。

### CommandLine 参数

要执行的命令行, 对应的字符串最大长度为 32k 即 32768 字符, 命令行所执行的应用的
路径被限制为 MAX_PATH 即 260 字符。

### CurrentDirectory 参数

用来指定进程的当前目录, 需要使用完整路径。可以使用 UNC 路径。如果该参数为
nullptr, 新进程将使用调用该函数的进程所使用的当前路径。

### 返回值

HRESULT 类型。如果函数调用成功, 则返回值为 S_OK。

## C# 接口

在你的项目中加载 M2.NSudo 程序集, 你就会知晓其用法。

### 代码示例

```
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
