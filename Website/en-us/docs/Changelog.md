# Changelog

**NSudo 9.0 Preview 2 (vNext, >= 9.0.2683.0)**

- Improve documents and website. (Thanks to 青春永不落幕 and Flex Zhong.)

**NSudo 9.0 Preview 1 (9.0.2676.0)**

- Fixed an issue "GUI doesn't start in operating systems language" mentioned in
  https://github.com/M2Team/NSudo/issues/66. (Thanks to Steve.)
- Fixed an issue when getting the SYSTEM access token. (Thanks to _kod0k and 
  DennyAmaro.)
- Implement the infrastructure of NSudo context plugin and interactive console.
  (Thanks to Legna and Microsoft_Mars.)
  - Warning: The ABI of NSudo context plugin won't be stable until NSudo 9.0 
    final version released. It's still under construction. 
- Introduce the Mouri Optimization Plugin as the NSudo context plugin example. 
  (Thanks to Legna, mingkuang, Microsoft_Mars, sdtzsf and abbodi1406.) 
  Here are the supported features in Mouri Optimization Plugin:
  - Perform defrag for memory via swapping most contents from the physical 
    memory to the page file.
  - Enable the "Receive updates for other Microsoft products when you update 
    Windows" option in Windows Update.
  - Manage the CompactOS feature.
  - Purge the web cache in the Chromium-based applications, including Chrome, 
    Chromium-based Edge, Electron-based applications, etc.
  - Purge the corrupted AppX packages.
  - Purge the cache in the Delivery Optimization.
  - Purge the web cache in the Gecko-based applications, including Firefox, 
    Waterfox, Pale Moon, etc.
  - Purge the cache in the NuGet safely.
  - Purge the cache in the Package Cache folder safely.
  - Purge the system restore points.
  - Purge the web cache in the Trident based applications, including Internet 
    Explorer, Legacy Edge, MSHTML based applications, Edge WebView based 
    applications, etc.
  - Purge the cache in the Visual Studio Code.
  - Purge the cache in the Visual Studio Installer safely.
  - Purge the Windows Event Log.
  - Update the apps from Microsoft Store.
- Update to VC-LTL 5.0.1-Beta4 (Cooperate with mingkuang.).

**NSudo 8.2**

- Add the Current User (Elevated) mode support. (Advised by xspeed1989.)
- Fix the blocking bug when using NSudo under Windows Service context. (Thanks 
  to xspeed1989.)
- Improve several implementations.
- Fix the issue that the UI is Chinese when NSudo is running under an 
  unsupported language setting. (Thanks to rlesch.)(#56)
- Update to the latest Mile.Cpp packages.
  - Update Mile.Project to the latest Mile.Project.VisualStudio.
  - Merge Mile.Windows.TrustedLibraryLoader and Mile.Platform.Windows to the 
    latest Mile.Library.
  - Update to the latest VC-LTL. 
- Update Windows Template Library (WTL) to 10.0.10320 Release.
- Remove ARM32 support.
  - Reason: https://forums.mydigitallife.net/threads/59268/page-28#post-1660432
- Make several improvements in the documentation.
  - Improve the website. (Contributed by 青春永不落幕.) 
  - Improve the Gitee experience.
  - Use GitHub Actions to deploy the website.
- Add German Language. (Contributed by Steve.)
- Remove some experiment implementations, including NSudo Sweeper.
- Add logging support.

**NSudo 8.0 Update 1 (8.0.1)**

- Update Italian translation. (Contributed by garf02.)
- Use VC-LTL NuGet package edition instead of standalone edition. (Thanks to mingkuang.)
- Create NSudo Sweeper (experiment).
- Use Windows Template Library (WTL) to build the UI.
- Improve the website. (Contributed by 青春永不落幕.)
- Reorganize the whole project.
- Add Mile, Mile.Project, MINT to the project for making NSudo more modularize.
- Improve the AppVeyor and GitHub Action CI support. (Thanks to mingkuang.)
- Add build all targets script.
- Update VC-LTL to 4.1.1-Beta7.
- Fix the crash bug under the Windows 10 Build 21277. (Thanks to jgtoy.)
- Update to .NET 5.0 for NSudo .NET Wrapper.

**NSudo 8.0**

- Reduce the binary size.
  - Use FILE instead of std::ifstream.
  - Use new compiler options.
  - Merge NSudo to NSudoG.
  - Optimize the icon resource.
  - Use jsmn instead of JSON for Modern C++.
- Rename NSudo itself to NSudo Launcher. (NSudoLG.exe and NSudoLC.exe)
- Remove context menu support because you can use 
  [https://github.com/Thdub/NSudo_Installer](https://github.com/Thdub/NSudo_Installer)
  for better experience.
- Add Itlian Language. (Contributed by garf02.)
- Add Spanish Language. (Contributed by Miguel Obando.)
- Use the Semantic Versioning format.
- Improve several implementations and documents.
- Add implementations for developers.
  - Add NSudo Shared Library with C/C++ and .Net interoperability support.
  - Add NSudo Devil Mode (NSudoDM).
  - Add Mouri Internal Library Essentials (Mile).
- Noticeable things about compiling this project.
  - Update to Visual Studio 2019.
  - Update to the newest Windows 10 SDK.
  - Improve AppVeyor CI and GitHub Actions CI support. (Thanks to Margen67.)

**NSudo 6.2.1812.31**

- Add French translations. (Contributed by Thomas Dubreuil.)
- Use JSON for Modern C++ instead of RapidJSON to conform to C++17.
- Improve the GUI experience. (Thanks to Lenny.)
- Fix context menu bug. (Thanks to Thomas Dubreuil and 龍魂.)
- Fix the command line parser bug. (Thanks to wzzw.)
- Add Traditional Chinese translations. (Contributed by Luo Yufan.)

**NSudo 6.1.1811.18**

- Merge NSudoC and NSudoG projects to NSudo project.
- Add VC-LTL 4.0 or later support for NSudo release configuration for ARM and
  ARM64 and drop the earlier version of VC-LTL support. (Huge thanks to
  mingkuang.)
- Add the following options in the command line usage.
  - CurrentDirectory (Suggested by testtest322.)
  - Help
  - H
  - Priority (Suggested by testtest322.)
  - ShowWindowMode (Suggested by testtest322.)
  - UseCurrentConsole
  - Version
  - Wait (Suggested by testtest322, wzzw and Domagoj Smolčić)
- Remove some undocumented command line usage.
- Improve several implementations.
  - Refactoring the command line parser.
  - Introduce the new frontend of process creation.
  - Using ATL to implement the main window.
  - Fix the context menu bug. (Thanks to Thomas Dubreuil.)
- Update copyright of license.
- Remove donation link in the documents.

**NSudo 6.0.1804.5**

- Fix a bug which can cause crash on Windows Vista and Server 2008.
  (Thanks to hydra79545.)
- Share source code with M2-Team UWP projects. (For more information, please
  read "[https://github.com/Project-Nagisa/Nagisa/blob/master/Changelog.md](https://github.com/Project-Nagisa/Nagisa/blob/master/Changelog.md)")
- Remove useless implementations.
- Improve the implementation for NSudoStartService function.
- Use RapidJSON instead of JSON for Modern C++ to reduce the binary size.

**NSudo 6.0.1802.2 v2**

- Fix always opens a command prompt window after click the run button.
  (Thanks to AeonX.)

**NSudo 6.0.1802.2**

- Fix several bugs and improve several implementations.
- Add two standalone executable files used in different situations.
  - NSudoC.exe
    - The pure command line version and subsystem setting is "Console".
    - Work well in the console, but it has a black console window if you call
      it in the non-Console processes.
    - To ensure the best experience, NSudoC does not support context menu.
  - NSudoG.exe
    - The pure command line version and subsystem setting is "Windows"
    - It can run silently, without a black console window.
- NSudo will show the message via the M2MessageDialog instead of TaskDialog.
  - Reasons
    - NSudo can provide more detail infomation when error because of it have
      vertical scroll bar.
    - You can copy the content in the message dialog.
    - Support using by the Windows Narrator, so you can use CapsLock+H to read
      the content by the Windows Narrator.
    - The font size is larger than the TaskDialog.
  - Features of M2MessageDialog
    - Fully support Per-Monitor DPI Aware in Windows 10 Build 10240 or later.
    - Fully support Windows Narrator.
    - You can use the vertical scroll bar and copy the content.
    - The font size is larger than the TaskDialog.
    - You can press Enter to close the message dialog.
  - If you want to use the M2MessageDialog in your project, please download
    these files in [https://github.com/M2Team/NSudo/tree/master/NSudoSDK](https://github.com/M2Team/NSudo/tree/master/NSudoSDK)
    - M2DPIScaling.cpp
    - M2DPIScaling.h
    - M2MessageDialog.cpp
    - M2MessageDialog.h
    - M2MessageDialogResource.h
    - M2MessageDialogResource.rc
- Remove Traditional Chinese and Japanese translation because the translation
  is out of date and I don't know how to use.
- Update JSON for Modern C++ to 3.0.1.
- Context Menu
  - Add multilingual descriptions.
  - Add "Enable All Privileges" options for all item in the context menu.
- Update the command line help and documents.

**NSudo 6.0.1801.19**

- Fix the NSudoDuplicateSessionToken function definition bug.
  (Thanks to mingkuang.)
- Fix bugs that cannot enable full privileges under the graphical interface.
  (Thanks to abbodi1406.)
- Fix bugs that cannot use static compile mode when using release configuration
  for x86 and x86-64 (AMD64) without VC-LTL.

**NSudo 5.3.1801.11**

- Fix a potential bug when NSudo obtaining the System Token.
  (Thanks to mingkuang.)
- Provide VC-LTL support for NSudo release configuration for x86 and x86-64
  (AMD64). (Thanks to mingkuang.)
  - PS: Compiling NSudo with VC-LTL can reduce the NSudo's binary size.
- Maintaining documents.

**NSudo 5.2 (5.2.1709.8 - 5.2.1710.26)**

- 整理代码, 修复若干 Bugs
- 更新文档, 增加英文自述
- 添加对 ARM 和 ARM64 平台的支持 (感谢 fcharlie) 
- 优化命令行解析
- 添加右键菜单支持
  - 使用 /Install 或 -Install 参数添加右键菜单 (命令行参数大小写不敏感) 
  - 使用 /Uninstall 或 -Uninstall 参数移除右键菜单 (命令行参数大小写不敏感) 

**NSudo 5.1 (5.0.1708.9 - 5.1.1708.19)**

- 修复批处理调用 NSudo 后批处理变量不生效的问题 (感谢 芈员外) 
- 令 NSudo 在带有命令行的状态下也能自动请求管理员权限 (感谢 鸢一雨音) 
- 更换新图标, 顺便解决在 Windows Vista 之前版本系统上不显示 NSudo 图标的问题
   (PS: NSudo 最低要求依旧是 Windows Vista) 
- 改进命令行解析 (感谢 鸢一雨音) 
- 更新源代码许可的版权 (对说辞进行了优化) 和更新感谢名单 (新增人士) 

**NSudo 5.0 (4.4.1705.28 - 5.0.1707.31)**

- 使用新的获取会话 ID 方法解决在 Server 系统的远程桌面会话上使用 NSudo 运行应用可能无
  法显示界面的问题 (感谢 sebus) 
- 更新文档和许可协议以符合实际情况
- 移除 VC-LTL (由 fcharlie 建议), 理由如下: 
  - 虽然二进制大小增加 80KB, 但源代码大小缩小 57.6MB
  - 源代码大小缩小后, NSudo 的云编译速度大幅提升
  - 可以少屏蔽大量编译警告
- 使用 NSudoSDK 项目代替 M2-SDK 项目
- 改进版本定义头文件
- 编译器启用 SDL 检查、调整编译输出目录和更新 CI 编译配置文件
- 调整并优化代码(感谢 fcharlie 的建议)
- .gitignore 文件更新(由 fcharlie 实现)
- 完全使用 MSDN 文档化 API 实现 NSudoAPI.h 以方便人们调用
- 与 Nagisa 项目共用 m2base.h
- 整理屏蔽的警告, 该版本 NSudo 屏蔽了以下警告实现 /W4 /WX 编译
  - C4505 未引用的本地函数已移除(等级 4)
- NSudo 快捷列表文件格式从 ini 迁移到 json 并更新列表内容
- 进程创建时添加环境块以改善兼容性
- 把 Windows XP 控件支持声明和 Per-Monitor DPI Aware V1 支持移入清单文件
- 在清单文件添加兼容性 GUID 定义和 Per-Monitor DPI Aware V2 支持
- 修复当未在浏览窗口选择文件的情况下命令行文本框出现""的问题

**NSudo 4.4.1705.19**

- 适配最新版 M2-SDK
- 适配最新版 VC-LTL
- 修改编译选项
- 使用 git 子模块机制 (由 myfreeer 实现) 
- 配置 AppVeyor (由 myfreeer 提供灵感) 
- 开始使用 AppVeyor 自动编译
- 更新 M2-SDK 和 VC-LTL 子模块
- 命令行解析从 main 函数拆分
- 修复升级 VC-LTL 后出现的编译警告 (有空会 pull fix 到 VC-LTL) 
- 版本号重新由自己而不是 CI 编译服务控制
- 整理解决方案布局

**NSudo 4.3.1703.25**

- 32 位版本取消对 SSE 和 SSE2 指令集的依赖 (为了保证完美的兼容性) 
- 移除 NTIShell, NSudo.AppContainer, MiniFM 子项目
- NSudoSDK 完全被 M2-SDK 和 M2.NSudo.h 替代
- 关于界面布局调整
- 子系统设置调整为 Windows 子系统 (为了不再弹出黑框) 
- 优化代码, 减少全局变量
- System 令牌副本创建函数移除会话 ID 参数 (因为现实情况只能使用当前会话 ID) 
- 使用旧版应用调用方式 (即使用 cmd, 解决无法调用带参数应用的问题) 
- 优化在 UI 自动化工具 (例如讲述人等读屏软件) 上的使用体验
-  "运行" 按钮被设为默认按钮以提升使用体验
- 优化多语言资源以减小体积
- 修复 UI 标题栏没有图标的问题
- 为 UI 增加最小化按钮
- 修复数个库函数返回值 Bug
- 修复数个命令行解析 Bug
- 修复 UI 图标的 DPI 缩放问题
- 开始使用 Visual Studio 2017 编译
- 移除 NSudo-GUI 项目
- 代码不再包含 M2-SDK 和 VC-LTL 的内容, 需要单独从 github 克隆

**NSudo 4.2**

- 引入新 NSudoSDK API 并且对已有 NSudoSDK API 进行改善
- 优化代码, 以减少 Windows API 调用次数
- 修复不带任何参数情况下可能的奔溃问题
- 修复控制台部分不能在非管理员权限显示命令行帮助的问题
- 基于 ShellExecute 自建调用宿主, 以去除对 cmd.exe 的依赖
- 引入 NTIShell (相当于 NSudo 1.0) 重制版, 作为 NSudoSDK 的一个示例
- 更改 MiniFM 图标

**NSudo 4.1**

- 修复命令行使用-U:D 导致程序奔溃的问题
- 更正命令行的 NSudoC 残余描述 (感谢 NotePad) 
- 支持文件拖拽 (感谢 NotePad) 

**NSudo 4.0**

- 重写代码, 提供 NSudoSDK, 使代码容易使用在其他项目上
- 命令行下新增"/"前缀参数支持,例如: NSudo /U:T /P:E cmd (感谢 th1r5bvn23)
- 支持默认参数, 即以 TrustedInstaller 令牌且开启全部特权运行 (感谢 老九)
- 在默认快捷命令列表加入 host 编辑
- 增加 NSudo 和 MiniFM 的 Per-Monitor DPI Aware 支持
- 采用 VC-LTL 大幅度减小程序体积 (感谢 mingkuang) 
- 更改图标 (感谢 20011010wo) 
- 精简并优化主界面 (感谢 kCaRhC 卡壳, さくら) 
- 使用 TaskDialog 替代 MessageBox
- 对关于界面进行调整, 并在关于界面加入命令行帮助
- 修复弹出文件不存在的问题
- 修复命令行解析的一个潜在 Bug
- 缓解 NSudo 图形界面的空格问题 (浏览功能自动给命令行加引号) 
- 消除在编译时的警告(/Wall 和/WX 两个参数同时使用)

**NSudo 2016.1**

- 修复 TrustedInstaller 下运行程序界面不显示问题 (感谢 abbodi1406) 
- 修复命令行解析的漏洞和 UI 错误 (感谢 imadlatch) 
- 整理代码, 提升可读性
- 当前目录设为 NSudo 所在目录 (未来会更加灵活) 
- ShortCut 实现无限项目
- 新增简易文件管理器小工具 (感谢 20011010wo) 

**NSudo 2016**

- 支持多语言 (程序内含简中, 繁中, 英文, 日文) 
- 命令行处理重写
- 实现代码全部重构; 效率更高

**NSudo 3.2 Fix1**

- 优化程序逻辑; 减少无用代码
- 命令行版和图形版二合一

**NSudo 3.2**

- 修复无法使用带有空格的路径的问题
- NSudo 和 NSudoC 单文件化
- 增加 NSudo.bat 方便新手准确调用与电脑架构相符的 NSudo 版本
- NSudoSDK 增加静态库 (用 NSudo SDK 开发的工具可以实现单文件) 
- 编译平台采用 Visual Studio 2015 + Windows 10 SDK

**NSudo 3.1 Debug**

- 修复 UI 的 ComboBox 不能输入太长文字的问题
- 修复某些情况下不能使用的问题 (由于开发机 Windows10 的 Bug 而导致误认为那种方式可
  行) 
- 增加真正的令牌降权 (除了 cmd 会误显示管理员外; 其他的会将其看作普通用户) 
- 增加命令行版本
- 增加常用列表自定义功能

**NSudo 3.0 R2**

- 修复不能打开其他被系统关联文件的 Bug
- SDK 的头文件改进: 增加#pragma comment(lib,"NSudoAPI.lib")

**NSudo 3.0**

- 支持外部应用调用 (很抱歉让一些人等太久) 
- 增加了常用调用列表 (暂时不支持自定义; 未来 3.1 会加入) 
- 加入了降权功能 (当然, 是完美降权到 UAC 未提权前。当然原理不是用获取 explorer 令牌
  和创建计划任务) 
- 支持对权限令牌的自定义
- 界面的完全重构 (相对于 2.x 来说) 
- 代码优化 (相对于 NSudo 3.0 M1 来说) 
- 加入 NSudo SDK
- 原生 64 位版本
- 实现了调用外部程序无视 WOW64 重定向的方法 (NSudoCreateProcess) 
- WinPE 支持 (虽然没起多大作用) 

**NSudo 2.1**

- 实现自动开启所有权限 Token
- 对 cmd 的调用使用绝对路径, 估计可以避免一些不必要的 Bug
- 优化程序代码

**NSudo 2.0**

- 代码全部使用 C++ Win32 SDK 重写 (程序从 692KB 缩小到 92KB) 
- 提供获取权限的选项
- 提供命令行参数模式
- 更换了图标

**NSudo 1.2**

- 未公开发布 (估计还是在修复 SessionID 问题) 

**NSudo 1.1**

- 修复 SessionID 问题
- 32 位和 64 位版本合体 (根据架构确定运行那个架构的命令提示符, 采用 SysNative 目录
   (64 位 Vista 开始有的重定向) 调用 64 位 cmd) 

**NTIShell 1.0**

- 根据 raymai97 的超级命令提示符制作的第一个版本
