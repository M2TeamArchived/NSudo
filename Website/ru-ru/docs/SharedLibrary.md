# Общая библиотека NSudo

## Функция NSudoCreateProcess

Создаёт новый процесс и его основной поток.

### Прототип на C/C++

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

### Параметр UserModeType

Значение из перечислимого типа NSUDO_USER_MODE_TYPE, которое идентифицирует пользовательский
режим.

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

### Параметр PrivilegesModeType

Значение из перечислимого типа NSUDO_PRIVILEGES_MODE_TYPE, которое идентифицирует
режим привилегий.

```cpp
typedef enum class _NSUDO_PRIVILEGES_MODE_TYPE
{
    DEFAULT,
    ENABLE_ALL_PRIVILEGES,
    DISABLE_ALL_PRIVILEGES
} NSUDO_PRIVILEGES_MODE_TYPE, *PNSUDO_PRIVILEGES_MODE_TYPE;
```

### Параметр MandatoryLabelType

Значение из перечислимого типа NSUDO_MANDATORY_LABEL_TYPE, которое идентифицирует
обязательную метку.

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

### Параметр ProcessPriorityClassType

Значение из перечислимого типа NSUDO_PROCESS_PRIORITY_CLASS_TYPE, которое 
идентифицирует класс приоритета процесса.

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

### Параметр ShowWindowModeType

Значение из перечислимого типа NSUDO_SHOW_WINDOW_MODE_TYPE, которое идентифицирует 
режим ShowWindow.

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

### Параметр WaitInterval

Интервал время ожидания для процесса, в миллисекундах. 

### Параметр CreateNewConsole

Если этот параметр равен TRUE, новый процесс будет иметь новую консоль, вместо того 
чтобы наследовать консоль своего родителя (по умолчанию).

### Параметр CommandLine

Командная строка, которая должна быть выполнена. Максимальная длина этой 
строки составляет 32 тыс. символов, часть имени модуля в CommandLine ограничена 
MAX_PATH символами.

### Параметр CurrentDirectory

Полный путь к текущему каталогу для процесса. Строка также может указывать UNC-путь.
Если этот параметр равен nullptr, новый процесс будет иметь тот же текущий диск
и каталог, что и вызывающий процесс. (Эта возможность предусмотрена в основном
для оболочек, которым необходимо запустить приложение и указать его
начальный диск и рабочий каталог.)

### Обратное значение

HRESULT. При успешном выполнении функции возвращаемое значение равно S_OK.

## C# API

Загрузите сборку M2.NSudo в свой проект, и вы узнаете, как её использовать.

### Пример

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
