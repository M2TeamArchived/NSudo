# 使用方法

## 快速入門

請開啟【CPU 架構】目錄，然後按兩下 NSudo.exe. 根據提示操作即可。例如，如果你想
在你的 Intel 或 AMD 設備上使用 64 位 NSudo，你首先需要開啟的是 x64 目錄，然後按兩
下 NSudoG.exe。

## 命令列選項

```
格式: NSudo [ 選項與參數 ] 命令列執行或常用任務名

選項:

-U:[ 選項 ] 以指定使用者選項建立處理程序。
可用選項：
    T TrustedInstaller
    S System
    C 當前使用者
    P 當前處理程序
    D 當前處理程序 (降權)
PS：這是一個必須被包含的參數。

-P:[ 選項 ] 以指定特殊權限選項建立處理程序。
可用選項：
    E 啓用全部特殊權限
    D 禁用所有特殊權限
PS：如果想以默認特殊權限選項建立處理程序，請不要包含「-P」參數。

-M:[ 選項 ] 以指定完整性選項建立處理程序。
可用選項：
    S 系統
    H 高
    M 中
    L 低
PS：如果想以默認完整性選項建立處理程序的話，請不要包含「-M」參數。

-Priority:[ 選項 ] 以指定處理程序優先級選項建立處理程序。
可用選項：
    Idle 低
    BelowNormal 低於正常
    Normal 正常
    AboveNormal 高於正常
    High 高
    RealTime 實時
PS：如果想以默認處理序優先權選項建立處理程序，請不要包含「-Priority」參數。

-ShowWindowMode:[ 選項 ] 以指定視窗模式選項建立處理程序。
可用選項：
    Show 顯示視窗
    Hide 隱藏視窗
    Maximize 最大化
    Minimize 最小化
PS：如果想以默認視窗模式選項建立處理程序的話，請不要包含「-ShowWindowMode」參數。

-Wait 令 NSudo 等待建立的處理程序結束後再退出。
PS：如果不想等待，請不要包含「-Wait」參數。

-CurrentDirectory:[ 目錄路徑 ] 設置處理程序的的當前目錄。
PS：如果你想用 NSudo 的當前目錄，請不要包含「-CurrentDirectory」參數。

-UseCurrentConsole 使用當前控制台視窗建立處理程序。
PS：如果你想在新控制台視窗建立處理程序，請不要包含「-UseCurrentConsole」參數。

-Version 顯示 NSudo 版本資訊。

-? 顯示該內容。
-H 顯示該內容。
-Help 顯示該內容。

上下文清單管理：
  -Install   把NSudo複製到Windows目錄並且添加上下文清單。
  -Uninstall 移除在Windows目錄的NSudo和上下文清單。

PS：
    1. 所有的NSudo命令列參數不區分大小寫。
    2. 可以在命令列參數中使用 "/" 或 "--" 代替 "-" 和使用 "=" 代替 ":"。例如
       "/U:T" 和 "-U=T" 是等價的。
    3. 為了保證最佳體驗，NSudoC不支持上下文清單。

例子：
    以TrustedInstaller權限，啓用所有特殊權限，完整性默認執行命令提示字元
        NSudo -U:T -P:E cmd
```

例子：以 TrustedInstaller 權限，啓用所有特殊權限，完整性默認執行命令提示字元：

> NSudo -U:T -P:E cmd

從 NSudo 5.0.1708.16 開始命令列支持嵌套引號，例如：

> NSudo -U:T cmd /c "dir "C:\Program Files" & pause"

## 常用列表

關於常用列表的自訂,可以使用記事本等工具編輯 NSudo.json。你可以照著示例的做法添
加你的自訂項目：

```
{
  "ShortCutList_V2": {
    "命令提示字元": "cmd",
    "PowerShell": "powershell",
    "PowerShell ISE": "powershell_ise",
    "Hosts編輯": "notepad %windir%\\System32\\Drivers\\etc\\hosts"
  }
}
```
