# NSudo 共享庫

## NSudoCreateProcess 函數

創建一個新進程和對應的主線程。

### C/C++ 函數原型

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

### UserModeType 參數

一個類型爲 NSUDO_USER_MODE_TYPE 枚舉類型的值, 用以表示用戶類別。

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

### PrivilegesModeType 參數

一個類型爲 NSUDO_PRIVILEGES_MODE_TYPE 枚舉類型的值, 用以表示特權類型。

```cpp
typedef enum class _NSUDO_PRIVILEGES_MODE_TYPE
{
    DEFAULT,
    ENABLE_ALL_PRIVILEGES,
    DISABLE_ALL_PRIVILEGES
} NSUDO_PRIVILEGES_MODE_TYPE, *PNSUDO_PRIVILEGES_MODE_TYPE;
```

### MandatoryLabelType 參數

一個類型爲 NSUDO_MANDATORY_LABEL_TYPE 枚舉類型的值, 用以表示完整性標籤。

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

### ProcessPriorityClassType 參數

一個類型爲 NSUDO_PROCESS_PRIORITY_CLASS_TYPE 枚舉類型的值, 用以表示進程優先級。

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

### ShowWindowModeType 參數

一個類型爲 NSUDO_SHOW_WINDOW_MODE_TYPE 枚舉類型的值, 用以表示顯示窗口模式。

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

### WaitInterval 參數

等待創建的進程的時間 (毫秒)。

### CreateNewConsole 參數

如果這個參數設爲 TRUE, 新進程則在新的控制檯窗口運行, 否則則直接在父進程對應的控
制臺窗口運行 (默認設定)。

### CommandLine 參數

要執行的命令行, 對應的字符串最大長度爲 32k 即 32768 字符, 命令行所執行的應用的
路徑被限制爲 MAX_PATH 即 260 字符。

### CurrentDirectory 參數

用來指定進程的當前目錄, 需要使用完整路徑。可以使用 UNC 路徑。如果該參數爲
nullptr, 新進程將使用調用該函數的進程所使用的當前路徑。

### 返回值

HRESULT 類型。如果函數調用成功, 則返回值爲 S_OK。

## C# 接口

在你的項目中加載 M2.NSudo 程序集, 你就會知曉其用法。

### 代碼示例

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
