# Режим без ограничений NSudo

Режим без ограничений NSudo - это элегантное решение для разработчиков, 
которые хотят обойти проверки доступа к файлам и реестру. Он подключает некоторые 
системные вызовы ядра Windows NT к файлам и реестру через Microsoft Detours, поэтому 
разработчикам нужно только загрузить NSudoDM.dll в свои приложения, прежде чем пользоваться ими.

Режим без ограничений NSudo требует только привилегии администратора. Поэтому разработчикам 
необходимо запускать свои приложения от имени администратора, если они хотят его использовать.

Как создатель проекта NSudo, я думаю, что режим без ограничений NSudo может 
заменить инструменты, подобные NSudo, в большинстве случаев. NSudo 8.0 будет поддерживать 
запуск приложений в режиме без ограничений NSudo, а режим без ограничений Dism++ будет перенесён с 
режимом без ограничений NSudo. Так что NSudo будет более профессиональным ПО в будущем, 
потому что я не хочу, чтобы NSudo был заменён режимом без ограничений NSudo, хаха.

## Почему я создал режим без ограничений NSudo

Разработчикам трудно интегрировать общую библиотеку NSudo, поскольку она раскрывает
много деталей о модели безопасности Windows и выглядит как библиотека низкого уровня.
Я не думаю, что только предоставление общей библиотеки NSudo подходит разработчикам, которые 
хотят обойти проверки доступа к файлам и реестру. Поэтому я создал режим без ограничений NSudo.

## Происхождение режима без ограничений NSudo

Режим без ограничений NSudo основан на режиме без ограничений Dism++ 
или по-китайски "Dism++ 春哥附体". Я перенёс режим без ограничений Dism++, добавил
несколько новых возможностей и сделал его исходный код доступным в репозитории NSudo на GitHub.

## Список подключенных системных вызовов ядра Windows NT

| Имя                   | Происхождение                                  |
|-----------------------|------------------------------------------------|
| NtCreateKey           | Режим без ограничений Dism++                   |
| NtCreateKeyTransacted | Режим без ограничений NSudo                    |
| NtOpenKey             | Режим без ограничений Dism++. Расширен в режиме без ограничений NSudo. |
| NtOpenKeyTransacted   | Режим без ограничений NSudo                    |
| NtOpenKeyEx           | Режим без ограничений Dism++                   |
| NtOpenKeyTransactedEx | Режим без ограничений NSudo                    |
| NtCreateFile          | Режим без ограничений Dism++                   |
| NtOpenFile            | Режим без ограничений Dism++                   |

## Как использовать режим без ограничений NSudo

Вы можете включить его через LoadLibrary и отключить через FreeLibrary. 
Вот демонстрационный код.

```csharp
using System;
using System.IO;
using System.Runtime.InteropServices;

namespace Demo
{
    class Program
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode)]
        static extern IntPtr LoadLibrary(string lpLibFileName);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool FreeLibrary(IntPtr hLibModule);

        static void Main(string[] args)
        {
            IntPtr NSudoDevilModeModuleHandle = LoadLibrary(
                @"E:\GitHub\M2Team\NSudo\Output\Release\x64\NSudoDevilMode.dll");

            {
                DirectoryInfo Folder = new DirectoryInfo(
                @"C:\System Volume Information");

                foreach (FileInfo File in Folder.GetFiles())
                {
                    Console.WriteLine(File.FullName);
                }
            }

            FreeLibrary(NSudoDevilModeModuleHandle);

            {
                DirectoryInfo Folder = new DirectoryInfo(
                @"C:\System Volume Information");

                foreach (FileInfo File in Folder.GetFiles())
                {
                    Console.WriteLine(File.FullName);
                }
            }

            Console.ReadKey();
        }
    }
}
```
