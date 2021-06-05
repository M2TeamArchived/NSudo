# NSudo 惡魔模式

NSudo 惡魔模式 (NSudo Devil Mode) 是爲想無視文件和註冊表操作權限檢查的開發者
量身定做的一個用起來還算優雅的解決方案。

其原理是使用開源的 Microsoft Detours 庫對 Windows NT 內核的文件和註冊表相關的
系統調用進行 Inline Hook 以傳入選項讓開發者基本不用修改自己的實現也能充分的利用
管理員權限所提供的特權, 這也使得開發者只需要把 NSudo 惡魔模式的動態鏈接庫加載入
自己的以管理員身份運行的應用進程的地址空間內即可啓用 NSudo 惡魔模式。

由於 NSudo 惡魔模式可以在大部分情況下替代類似 NSudo 的工具, 於是 NSudo 未來的
功能會變得更加專業向。畢竟作爲 NSudo 的作者的我可不希望 NSudo 就這麼輕易地被
替代掉。當然, 由於 NSudo 惡魔模式屬於 Dism++ 春哥附體的後續版本 (畢竟我也是 
Dism++ 的其中一位開發者, 這麼說還是有依據的), 於是未來 Dism++ 的春哥附體的實現
會被替換成 NSudo 惡魔模式以幫助我更好的重構 Dism++ 的實現。當然, NSudo 也會支持
以惡魔模式運行應用。

## NSudo 惡魔模式的起源、命名和意義

正如上文所說, NSudo 惡魔模式屬於 Dism++ 春哥附體的後續版本, 而且你也能在本文中
瞭解 NSudo 惡魔模式和 Dism++ 春哥附體的區別。

命名爲 NSudo 惡魔模式的靈感來源是《入間同學入魔了》的被蛋爺改造過的擁有四個檔位
的入間手中的 "惡食戒指" 。

最開始聽到 MSMG Toolkit 的作者希望我能提供 NSudo 的 SDK 方便他進行二次開發時, 
我試着做了基於 COM 接口的 NSudo Shared Library 即 NSudoAPI, 但是由於 NSudoAPI 
暴露的細節太多, 如果不是對 Windows 安全特性足夠了解的開發者是很難駕馭的。於是
我覺得得換個方向, 於是就做了 NSudo 惡魔模式。

## NSudo 惡魔模式掛鉤的 Windows NT 內核系統調用列表

| 名稱                  | 起源                          |
|-----------------------|-------------------------------|
| NtCreateKey           | Dism++ 春哥附體               |
| NtCreateKeyTransacted | NSudo 惡魔模式                |
| NtOpenKey             | Dism++ 春哥附體, 並增強了效果 |
| NtOpenKeyTransacted   | NSudo 惡魔模式                |
| NtOpenKeyEx           | Dism++ 春哥附體               |
| NtOpenKeyTransactedEx | NSudo 惡魔模式                |
| NtCreateFile          | Dism++ 春哥附體               |
| NtOpenFile            | Dism++ 春哥附體               |

## 如何使用 NSudo 惡魔模式

調用 LoadLibrary 加載 NSudo 惡魔模式的動態鏈接庫以啓用 NSudo 惡魔模式, 調用 
FreeLibrary 釋放 NSudo 惡魔模式的動態鏈接庫的 HMODULE 句柄即可禁用 NSudo 
惡魔模式。

當然, 你的應用需要在管理員權限下運行, 相對於原本要求 SYSTEM 和 TrustedInstaller
權限的情況下其實好了不少。 

注: 如果你有本事把 NSudo 惡魔模式遠程注入到以管理員或者更高權限的進程內 (譬如 
7-Zip), 也能爲該進程賦能 (無視文件和註冊表的權限)。

下面提供一個使用 C# 編寫的測試用例。 (遍歷 C:\System Volume Information 目錄
的內容, 當啓用 NSudo 惡魔模式的情況下可以正常顯示, 禁用後會拋出文件夾拒絕訪問
的異常。) 

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

## NSudo 惡魔模式的技術內幕

啓用 SeBackupPrivilege 和 SeRestorePrivilege 是前提條件, 但是你也需要在創建文件
或註冊表句柄的時候傳入對應的選項, 否則是不生效的。

首先說明一點, 那就是 Windows 內核當發現調用者上下文爲 SYSTEM 令牌的時候, 據 
Microsoft 文檔描述是爲了提升 Windows 的性能會自動忽略掉大部分訪問檢查, 畢竟很多
Windows 系統關鍵組件運行在 SYSTEM 令牌上下文下面, 對於 Windows 用戶模式而言, 
SYSTEM 令牌是至高無上的, 所以訪問檢查沒必要做, 做了也提升不了安全性反而降低了
效率。所以這也是爲什麼除了 SYSTEM 令牌上下文外的其他令牌都需要啓用相關特權 + 
創建文件和註冊表句柄的 API 傳入對應選項才能忽略掉相關訪問檢查。

我用一個最簡單的例子來說明減少不需要的內核級訪問檢查的好處, 那就是在 Windows 
AppContainer 下運行的代碼, 由於會多出一個額外的內核級訪問檢查 (用 IDA 分析 
ntoskrnl.exe, 然後用 F5 查看相關函數可以發現, 其實就是多出了一個分支和寥寥數行
實現), 大概會比在 AppContainer 外運行會損失 15% 的性能  (這也可以說明越底層的
實現越需要重視性能問題)。Windows AppContainer 是 Windows 8 開始提供的用戶模式
沙盒, 主要用在商店應用和瀏覽器的沙盒上面。

Windows 的大部分內部使用了創建文件和註冊表句柄的 API 並沒有傳入對應的選項, 於是
就出現了普通管理員下即使開啓了這兩個特權有些目錄照樣還是無法進行增刪查改。而 
NSudo 惡魔模式通過 Inline Hook 對 Windows 用戶模式的系統調用層進行掛鉤以
智能傳入相關選項, 這也是 NSudo 惡魔模式能在非 SYSTEM 的但擁有這兩個特權的
令牌上下文下繞過文件和註冊表訪問判斷的緣由。

Windows 用戶模式系統調用層指的是 ntdll.dll 導出的前綴爲 Nt 或 Zw 的 API, 
Windows 用戶模式下的 API 最終全會調用這部分以通過軟中斷陷阱門或者系統調用指令
進入內核模式完成最終操作。

智能, 指的是隻有當前進程令牌上下文能夠啓用  SeBackupPrivilege 和 
SeRestorePrivilege 的時候, 纔會傳入對應選項。畢竟如果這兩個特權沒有開啓的話, 
傳入了相關選項是會返回錯誤的, 這也是爲什麼 Windows 相關實現並沒有傳入的原因。

當然 NSudo 惡魔模式爲了對調用者更加透明和符合最小權限原則, 在初始化的時候首先會
創建一份當前進程令牌的模擬令牌副本, 然後對該副本開啓這兩個特權。在 Hook 中, 
會先備份當前線程上下文的令牌, 接着替換成模擬令牌副本 (或者用 Microsoft 文檔的
稱法是模擬令牌上下文), 傳入相關選項調用原 API 後再恢復爲原來線程上下文的令牌。
 (實現細節請參考在 NSudo 代碼倉庫的 NSudo 惡魔模式的源代碼) 

我說的有些囉嗦, 請見諒, 希望對你有幫助。
