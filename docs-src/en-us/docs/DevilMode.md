### NSudo Devil Mode

NSudo Devil Mode is a elegant solution for developers who want to bypass the 
file and registry access checks. It hooks some file and registry Windows NT 
kernel system calls via Microsoft Detours, so developers only need to load 
NSudoDM.dll into their apps before enjoy it.

NSudo Devil Mode only needs Administrator privilege. So developers need to run 
their apps as Administrator if they want to use it.

As the creator of NSudo project, I think NSudo Devil Mode may replace tools 
similar as NSudo in the most cases. NSudo 8.0 will support run apps as NSudo 
Devil Mode, and Dism++ God Mode will be refactored with NSudo Devil Mode. So 
NSudo will be more professional in the future because I don't want to make 
NSudo is replaced by NSudo Devil Mode, lol.

## Why I create the NSudo Devil Mode

NSudo Shared Library is hard for developers to integrate it because it expose a
lot of details about Windows security model and looks like a low level library.
I don't think only providing NSudo Shared Library is good for developers who 
want to bypass the file and registry access checks. So I have created the NSudo
Devil Mode.

## Origin of NSudo Devil Mode

NSudo Devil Mode is based on the Dism++ God Mode or call it "Dism++ 春哥附体" 
via Chinese. I have refactored the implementations of Dism++ God Mode, add some
new features and make its source code available in NSudo's GitHub repository.

## The list of hooked Windows NT kernel system calls

| Name                  | Origin                                         |
|-----------------------|------------------------------------------------|
| NtCreateKey           | Dism++ God Mode.                               |
| NtCreateKeyTransacted | NSudo Devil Mode.                              |
| NtOpenKey             | Dism++ God Mode. Extended in NSudo Devil Mode. |
| NtOpenKeyTransacted   | NSudo Devil Mode.                              |
| NtOpenKeyEx           | Dism++ God Mode.                               |
| NtOpenKeyTransactedEx | NSudo Devil Mode.                              |
| NtCreateFile          | Dism++ God Mode.                               |
| NtOpenFile            | Dism++ God Mode.                               |

## How to use NSudo Devil Mode

You can enable it via LoadLibrary and disable it via FreeLibrary. Here is a 
demo code.

```
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
