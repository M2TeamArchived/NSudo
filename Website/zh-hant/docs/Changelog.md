﻿# 變更紀錄

**NSudo 8.2**

- 添加當前用戶 (提權) 模式支持 (由 xspeed1989 建議)
- 修復在 Windows 服務上下文使用 NSudo 遇到的阻礙性問題 (感謝 xspeed1989)
- 改善數處實現
- 修復在 NSudo 不支持的語言設置下界面顯示中文的問題 (感謝 rlesch)(#56)
- 升級 Mile.Cpp 到最新版本
  - 從 Mile.Project 升級到 Mile.Project.VisualStudio 最新版本 
  - 將 Mile.Windows.TrustedLibraryLoader 與 Mile.Platform.Windows 升級到 
    Mile.Library 最新版本 
  - 升級 VC-LTL 到最新版本 
- 升級 Windows Template Library (WTL) 到 10.0.10320
- 移除 ARM32 支持
  - 理由: https://mourinaruto.github.io/2021/05/17/Drop-ARM32-support-on-the-Windows-platform/
- 改善數處文檔相關的實現
  - 改善項目網站體驗 (由 青春永不落幕 貢獻) 
  - 改善碼雲體驗
  - 使用 GitHub Actions 部署項目網站
- Add German Language. (由 Steve 貢獻)
- 移除一些試驗性實現, 包括 NSudo Sweeper
- 添加日誌支持

**NSudo 8.0 Update 1 (8.0.1)**

- 更新意大利語翻譯 (由 garf02 貢獻)
- 使用 NuGet 包版本 VC-LTL 替代獨立版 VC-LTL (感謝 mingkuang)
- 創建 NSudo Sweeper 項目 (實驗性)
- 使用 Windows Template Library (WTL) 構建界面
- 改善項目網站實現 (由  青春永不落幕 貢獻)
- 整理整個項目
- 添加 Mile、Mile.Project、MINT 子項目使 NSudo 實現更加模塊化
- 改善 AppVeyor 和 GitHub Action 連續集成的支持 (感謝 mingkuang)
- 添加一鍵編譯腳本
- 升級 VC-LTL 到 4.1.1-Beta7
- 修復在 Windows 10 Build 21277 下崩潰的問題 (感謝 jgtoy)
- NSudo .NET 互操作庫採用 .NET 5.0 編譯

**NSudo 6.2.1812.31**

- 添加法語翻譯 (由 Thomas Dubreuil 貢獻)
- 使用 JSON for Modern C++ 替代 RapidJSON 以符合 C++17 規範
- 改善使用者介面體驗 (感謝 Lenny)
- 修復上下文選單錯誤 (感謝 Thomas Dubreuil 和 龍魂)
- 修復命令列解析器錯誤 (感謝 wzzw)
- 添加繁體中文翻譯 (由 羅宇凡 貢獻)

**NSudo 6.1.1811.18**

- 把 NSudoC 與 NSudoG 合併入 NSudo
- 為 ARM 和 ARM64 的 Release 二進位檔案編譯配置添加 VC-LTL 支援, 並移除 VC-LTL
  4.0 之前版本的支援 (大力感謝 mingkuang)
- 添加以下新的命令列選項
  - CurrentDirectory (由 testtest322 建議)
  - Help
  - H
  - Priority (由 testtest322 建議)
  - ShowWindowMode (由 testtest322 建議)
  - UseCurrentConsole
  - Version
  - Wait (由 testtest322、wzzw 和 Domagoj Smolčić 建議)
- 移除一些未文件化的命令列使用方式
- 改進數個實現
  - 重構命令列解析器
  - 引入新式建立處理序前端
  - 使用 ATL 實現主視窗
  - 修復上下文選單 Bug (感謝 Thomas Dubreuil)
- 更新授權的著作權所有者
- 移除文件中的捐贈連結

**NSudo 6.0.1804.5**

- 修復在 Windows Vista 和 Server 2008 下崩潰的問題 (感謝 hydra79545)
- 與 M2-Team UWP 項目共享實現 (詳情請閱讀
  「[https://github.com/Project-Nagisa/Nagisa/blob/master/Changelog.md](https://github.com/Project-Nagisa/Nagisa/blob/master/Changelog.md)」)
- 移除無用實現
- 改進 NSudoStartService 函數的實現
- 使用 RapidJSON 替代 JSON for Modern C++ 以減小二進位檔案大小

**NSudo 6.0.1802.2 v2**

- 修復點選執行按鈕只彈出命令提示字元的問題。 (感謝 AeonX)

**NSudo 6.0.1802.2**

- 修復多個 Bug 和改善多個實現
- 增加兩個獨立的可執行檔案用於不同情況
  - NSudoC.exe
    - 純命令列版本, 子系統設置為「控制台」
    - 在控制台下執行良好, 但是在非控制台處理序調用會出現黑色控制台視窗
    - 為了保證最佳體驗, NSudoC 不支援上下文選單
  - NSudoG.exe
    - 純命令列版本, 子系統設置為「Windows」
    - 可以靜默執行, 沒有黑色控制台視窗
- NSudo 將通過 M2MessageDialog 而不是 TaskDialog 顯示資訊
  - 理由
    - 因為可以使用縱向滾動條, NSudo 可以在出錯時提供更加詳細的內容
    - 你可以複製對話方塊里的內容
    - 支援 Windows 講述人, 於是可以使用 CapsLock+H 讓講述人讀取對話方塊內容
    - 比 TaskDialog 的字型更大
  - M2MessageDialog 特性
    - 在 Windows 10 Build 10240 或之後版本完全支援 Per-Monitor DPI Aware
    - 完全支援 Windows 朗讀程式
    - 你可以使用縱向滾動條並且可以複製裡面的內容
    - 比 TaskDialog 的字型更大
    - 你可以按 Enter 鍵關閉對話方塊
  - 如果你想在你的項目使用 M2MessageDialog, 請從此處下載以下檔案: 
    [https://github.com/M2Team/NSudo/tree/master/NSudoSDK](https://github.com/M2Team/NSudo/tree/master/NSudoSDK)
    - M2DPIScaling.cpp
    - M2DPIScaling.h
    - M2MessageDialog.cpp
    - M2MessageDialog.h
    - M2MessageDialogResource.h
    - M2MessageDialogResource.rc
- 移除繁體中文和日語的翻譯, 因為翻譯內容已經過時而且我不懂怎麼用
- 升級 JSON for Modern C++ 到 3.0.1
- 右鍵選單
  - 增加多語言描述
  - 為所有項目添加「開啓全部特權」選項
- 更新命令列幫助和文件

**NSudo 6.0.1801.19**

- 修復 NSudoDuplicateSessionToken 函數定義 Bug (感謝 mingkuang)
- 修復在圖形介面下無法啓用全部特權的 Bug (感謝 abbodi1406)
- 修復沒有 VC-LTL 時 x86 和 x86-64(AMD64)的 Release 編譯配置未採用靜態編譯的 Bug

**NSudo 5.3.1801.11**

- 修復獲取 System 令牌函數的一個潛在 Bug (感謝 mingkuang)
- 對 x86 和 x86-64(AMD64)的 Release 編譯配置提供 VC-LTL 庫支援 (感謝 mingkuang)
  - PS: 把 NSudo 和 VC-LTL 一起使用可以減小 NSudo 二進位檔案的體積
- 整理文件

**NSudo 5.2 (5.2.1709.8 - 5.2.1710.26)**

- 整理程式碼, 修復若干 Bugs
- 更新文件, 增加英文自述
- 添加對 ARM 和 ARM64 平台的支援 (感謝 fcharlie)
- 優化命令列解析
- 添加右鍵選單支援
  - 使用 /Install 或 -Install 參數添加右鍵選單 (命令列參數大小寫不敏感)
  - 使用 /Uninstall 或 -Uninstall 參數移除右鍵選單 (命令列參數大小寫不敏感)

**NSudo 5.1 (5.0.1708.9 - 5.1.1708.19)**

- 修復批次檔案調用 NSudo 後批次變量不生效的問題 (感謝 羋員外)
- 令 NSudo 在帶有命令列的狀態下也能自動請求管理員權限 (感謝 鳶一雨音)
- 更換新圖示, 順便解決在 Windows Vista 之前版本系統上不顯示 NSudo 圖示的問題
   (PS: NSudo 最低要求依舊是 Windows Vista)
- 改進命令列解析 (感謝 鳶一雨音)
- 更新原始程式碼授權的著作權 (對說辭進行了優化)和更新感謝名單 (新增人士)

**NSudo 5.0 (4.4.1705.28 - 5.0.1707.31)**

- 使用新的獲取會話 ID 方法解決在 Server 系統的遠程桌面會話上使用 NSudo 執行應用可能無
  法顯示介面的問題 (感謝 sebus)
- 更新文件和授權協議以符合實際情況
- 移除 VC-LTL (由 fcharlie 建議), 理由如下: 
  - 雖然二進位檔案大小增加 80KB, 但原始程式碼大小縮小 57.6MB
  - 原始程式碼大小縮小後, NSudo 的雲編譯速度大幅提升
  - 可以少屏蔽大量編譯警告
- 使用 NSudoSDK 項目代替 M2-SDK 項目
- 改進版本定義頭檔案
- 編譯器啓用 SDL 檢查、調整編譯輸出目錄和更新 CI 編譯配置檔案
- 調整並優化程式碼(感謝 fcharlie 的建議)
- .gitignore 檔案更新(由 fcharlie 實現)
- 完全使用 MSDN 文件化 API 實現 NSudoAPI.h 以方便人們調用
- 與 Nagisa 項目共用 m2base.h
- 整理屏蔽的警告, 該版本 NSudo 屏蔽了以下警告實現 /W4 /WX 編譯
  - C4505 未引用的本地函數已移除(等級 4)
- NSudo 快捷列表檔案格式從 ini 遷移到 json 並更新列表內容
- 處理序建立時添加環境塊以改善兼容性
- 把 Windows XP 控件支援聲明和 Per-Monitor DPI Aware V1 支援移入清單檔案
- 在清單檔案添加兼容性 GUID 定義和 Per-Monitor DPI Aware V2 支援
- 修復當未在瀏覽視窗選擇檔案的情況下命令列文本框出現""的問題

**NSudo 4.4.1705.19**

- 適配最新版 M2-SDK
- 適配最新版 VC-LTL
- 修改編譯選項
- 使用 git 子模組機制 (由 myfreeer 實現)
- 配置 AppVeyor (由 myfreeer 提供靈感)
- 開始使用 AppVeyor 自動編譯
- 更新 M2-SDK 和 VC-LTL 子模組
- 命令列解析從 main 函數拆分
- 修復升級 VC-LTL 後出現的編譯警告 (有空會 pull fix 到 VC-LTL)
- 版本號重新由自己而不是 CI 編譯服務控制
- 整理解決方案佈局

**NSudo 4.3.1703.25**

- 32 位版本取消對 SSE 和 SSE2 指令集的依賴 (為了保證完美的兼容性)
- 移除 NTIShell, NSudo.AppContainer, MiniFM 子項目
- NSudoSDK 完全被 M2-SDK 和 M2.NSudo.h 替代
- 關於介面佈局調整
- 子系統設置調整為 Windows 子系統 (為了不再彈出黑框)
- 優化程式碼, 減少全局變量
- System 令牌副本建立函數移除會話 ID 參數 (因為現實情況只能使用當前會話 ID)
- 使用舊版應用調用方式 (即使用 cmd, 解決無法調用帶參數應用的問題)
- 優化在 UI 自動化工具 (例如講述人等讀屏軟件)上的使用體驗
- 「執行」按鈕被設為默認按鈕以提升使用體驗
- 優化多語言資源以減小體積
- 修復 UI 標題欄沒有圖示的問題
- 為 UI 增加最小化按鈕
- 修複數個庫函數返回值 Bug
- 修複數個命令列解析 Bug
- 修復 UI 圖示的 DPI 縮放問題
- 開始使用 Visual Studio 2017 編譯
- 移除 NSudo-GUI 項目
- 程式碼不再包含 M2-SDK 和 VC-LTL 的內容, 需要單獨從 github 克隆

**NSudo 4.2**

- 引入新 NSudoSDK API 並且對已有 NSudoSDK API 進行改善
- 優化程式碼, 以減少 Windows API 調用次數
- 修復不帶任何參數情況下可能的奔潰問題
- 修復控制台部分不能在非管理員權限顯示命令列幫助的問題
- 基於 ShellExecute 自建調用宿主, 以去除對 cmd.exe 的依賴
- 引入 NTIShell (相當於 NSudo 1.0)重製版, 作為 NSudoSDK 的一個示例
- 更改 MiniFM 圖示

**NSudo 4.1**

- 修復命令列使用-U:D 導致程序奔潰的問題
- 更正命令列的 NSudoC 殘餘描述 (感謝 NotePad)
- 支援檔案拖拽 (感謝 NotePad)

**NSudo 4.0**

- 重寫程式碼, 提供 NSudoSDK, 使程式碼容易使用在其他項目上
- 命令列下新增"/"前綴參數支援,例如: NSudo /U:T /P:E cmd (感謝 th1r5bvn23)
- 支援默認參數, 即以 TrustedInstaller 令牌且開啓全部特權執行 (感謝 老九)
- 在默認快捷命令列表加入 host 編輯
- 增加 NSudo 和 MiniFM 的 Per-Monitor DPI Aware 支援
- 採用 VC-LTL 大幅度減小程序體積 (感謝 mingkuang)
- 更改圖示 (感謝 20011010wo)
- 精簡並優化主介面 (感謝 kCaRhC 卡殼, さくら)
- 使用 TaskDialog 替代 MessageBox
- 對關於介面進行調整, 並在關於介面加入命令列幫助
- 修復彈出檔案不存在的問題
- 修復命令列解析的一個潛在 Bug
- 緩解 NSudo 圖形介面的空格問題 (瀏覽功能自動給命令列加引號)
- 消除在編譯時的警告(/Wall 和/WX 兩個參數同時使用)

**NSudo 2016.1**

- 修復 TrustedInstaller 下執行程序介面不顯示問題 (感謝 abbodi1406)
- 修復命令列解析的漏洞和 UI 錯誤 (感謝 imadlatch)
- 整理程式碼, 提升可讀性
- 當前目錄設為 NSudo 所在目錄 (未來會更加靈活)
- ShortCut 實現無限項目
- 新增簡易檔案管理器小工具 (感謝 20011010wo)

**NSudo 2016**

- 支援多語言 (程序內含簡中, 繁中, 英文, 日文)
- 命令列處理重寫
- 實現程式碼全部重構; 效率更高

**NSudo 3.2 Fix1**

- 優化程序邏輯; 減少無用程式碼
- 命令列版和圖形版二合一

**NSudo 3.2**

- 修復無法使用帶有空格的路徑的問題
- NSudo 和 NSudoC 單檔案化
- 增加 NSudo.bat 方便新手準確調用與電腦架構相符的 NSudo 版本
- NSudoSDK 增加靜態庫 (用 NSudo SDK 開發的工具可以實現單檔案)
- 編譯平台採用 Visual Studio 2015 + Windows 10 SDK

**NSudo 3.1 Debug**

- 修復 UI 的 ComboBox 不能輸入太長文字的問題
- 修復某些情況下不能使用的問題 (由於開發機 Windows10 的 Bug 而導致誤認為那種方式可
  行)
- 增加真正的令牌降權 (除了 cmd 會誤顯示管理員外; 其他的會將其看作普通用戶)
- 增加命令列版本
- 增加常用列表自定義功能

**NSudo 3.0 R2**

- 修復不能打開其他被系統關聯檔案的 Bug
- SDK 的頭檔案改進: 增加#pragma comment(lib,"NSudoAPI.lib")

**NSudo 3.0**

- 支援外部應用調用 (很抱歉讓一些人等太久)
- 增加了常用調用列表 (暫時不支援自定義; 未來 3.1 會加入)
- 加入了降權功能 (當然, 是完美降權到 UAC 未提權前。當然原理不是用獲取 explorer 令牌
  和建立計劃任務)
- 支援對權限令牌的自定義
- 介面的完全重構 (相對於 2.x 來說)
- 程式碼優化 (相對於 NSudo 3.0 M1 來說)
- 加入 NSudo SDK
- 原生 64 位版本
- 實現了調用外部程序無視 WOW64 重定向的方法 (NSudoCreateProcess)
- WinPE 支援 (雖然沒起多大作用)

**NSudo 2.1**

- 實現自動開啓所有權限 Token
- 對 cmd 的調用使用絕對路徑, 估計可以避免一些不必要的 Bug
- 優化原始程式碼

**NSudo 2.0**

- 程式碼全部使用 C++ Win32 SDK 重寫 (程序從 692KB 縮小到 92KB)
- 提供獲取權限的選項
- 提供命令列參數模式
- 更換了圖示

**NSudo 1.2**

- 未公開發佈 (估計還是在修復 SessionID 問題)

**NSudo 1.1**

- 修復 SessionID 問題
- 32 位和 64 位版本合體 (根據架構確定執行那個架構的命令提示字元, 採用 SysNative 目錄
   (64 位 Vista 開始有的重定向)調用 64 位 cmd)

**NTIShell 1.0**

- 根據 raymai97 的超級命令提示字元製作的第一個版本
