# NSudo - 系統管理工具包

![螢幕擷取畫面](./Screenshot.png)

## 注：成爲 NSudo 的贊助者

我是一個非計算機科班出身的軟件開發者，今年畢業後會在一家自動駕駛初創公司工作。
由於未來的工作中涉及到的主要是 linux 平臺開發，而我現在的個人項目主要是爲 
Windows 平臺而設計，所以我希望能通過他人的捐贈繼續維持自己維護個人工具的熱情。

Patreon: [https://www.patreon.com/MouriNaruto](https://www.patreon.com/MouriNaruto)

愛發電: [https://afdian.net/@MouriNaruto](https://afdian.net/@MouriNaruto)

- 如果我達到了每個月 1000 美元的目標，我將會每年更新兩個大版本。
- 如果我達到了每個月 2000 美元的目標，我會爲 NSudo 二進制添加 EV 代碼簽名證書。

感謝支持。

毛利

## 關於

### Prototype

注意：NSudo 基於 raymai97 的 SuperCMD，請參閱
[這裡](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "這裡") 以獲取更多關於
SuperCMD 的信息。

### 特性列表

- 以 MIT 許可證發行
- 提供 x86, x86-64, ARM, ARM64 二進制
- 支持 Windows Vista 及之後版本
- 使用初雨團隊的 VC-LTL 和 libkcrt 以獲取更小的二進制體積
- 使用 C++17，但在大部分情況下只使用核心語言特性
- NSudo Launcher
  - 以 TrustedInstaller 訪問令牌運行程序
  - 以 System 訪問令牌運行程序
  - 以當前用戶的訪問令牌運行程序
    - 注：如果用戶賬戶控制即 UAC 沒有被禁用，則該模式的權限與標準用戶等價
  - 以當前進程的訪問令牌運行程序
    - 注：該模式的權限與提升後的用戶等價
  - 以當前進程 LUA 模式的訪問令牌運行程序
    - 注：該模式的權限與標準用戶等價且該實現和 Internet Explorer 瀏覽器中的 
      iertutil.dll 中的對應實現一致
  - 支持以指定的特權設置運行程序
    - 注：啓用全部特權, 禁用所有特權
  - 支持以指定的完整性級別運行程序
    - 注：系統、高、中、低
  - 支持以指定的進程優先級運行程序
    - 注：低、低於正常、正常、高於正常、高、實時
  - 支持以指定的窗口模式運行程序
    - 注：顯示窗口、隱藏窗口、最大化、最小化
  - 支持進程創建後並等待其運行結束
  - 支持以指定的當前目錄運行程序
  - 支持在當前控制檯窗口下運行程序
  - 支持快捷方式列表
    - 注：你可以通過編輯 NSudo.json 的方式定製
  - 支持多種命令行風格
  - 多語言支持
    - 注：簡體中文、繁體中文、英語、法語、意大利語、西班牙語
  - 完整的高 DPI 支持
    - 注：和 Windows 外殼 (conhost.exe) 的實現一樣完美，在 Windows 10 Build 
      10240 及之後版本有完整的 Per-Monitor DPI-Aware 支持和在 Windows Vista 到
      Windows 8.1 之間的版本有完整的 System DPI-Aware 支持
  - 完整的無障礙訪問支持
    - 注：你可以在 Windows 講述人下順暢的使用 NSudo Launcher
  - 高性能
    - 注：因爲其實現不需要創建 Windows 服務和 Windows 服務進程
  - 爲開發者提供 C APIs 和 .Net Core 互操作支持
- NSudo 惡魔模式
  - 對於希望無視管理員權限的進程下的文件和註冊表訪問判斷的開發者而言是最優雅的
    解決方案
  - 使用 Microsoft Detours 庫對 API 進行掛鉤以保證最大兼容
  - 其二進制僅依賴了 ntdll.dll 的以函數名導出的 API

### 使用了 NSudo 的第三方項目

- MSMG ToolKit
- Sledgehammer (WUMT Wrapper Script)
- Dism++

### 系統要求

- 支持的系統版本：Windows NT 6.0 及之後版本
- 支持的處理器架構：x86, x86-64(AMD64), ARM, ARM64

### 第三方介紹

- MajorGeeks: [https://www.majorgeeks.com/files/details/nsudo.html](https://www.majorgeeks.com/files/details/nsudo.html)
- softpedia.com: [https://www.softpedia.com/get/Tweak/System-Tweak/NSudo.shtml](https://www.softpedia.com/get/Tweak/System-Tweak/NSudo.shtml)
- TrishTech.com: [https://www.trishtech.com/2018/11/nsudo-run-programs-with-full-privileges-in-windows/](https://www.trishtech.com/2018/11/nsudo-run-programs-with-full-privileges-in-windows/)
- Wilders Security Forums: [https://www.wilderssecurity.com/threads/396818](https://www.wilderssecurity.com/threads/396818)

## 使用方法

### 快速入門

請開啟【CPU 架構】目錄，然後按兩下 NSudo.exe. 根據提示操作即可。例如，如果你想
在你的 Intel 或 AMD 設備上使用 64 位 NSudo，你首先需要開啟的是 x64 目錄，然後按兩
下 NSudoG.exe。
