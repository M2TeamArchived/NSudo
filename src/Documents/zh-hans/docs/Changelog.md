# 更新日志

**NSudo 8.0**

- 精简二进制体积
  - 使用 FILE 而不是 std::ifstream
  - 使用新的编译器选项
  - NSudo 合并入 NSudoG
  - 优化图标资源
  - 使用 jsmn 而不是 JSON for Modern C++.
- NSudo 更名为 NSudo Launcher（NSudoLG.exe 和 NSudoLC.exe）
- 移除上下文支持，因为 [https://github.com/Thdub/NSudo_Installer](https://github.com/Thdub/NSudo_Installer) 体验更好
- 添加意大利语翻译（由 garf02 贡献）
- 添加西班牙语翻译（由 Miguel Obando 贡献）
- 遵循语义化版本规范
- 改善数个代码和文档方面的实现
- 添加为开发者设计的相关设施
  - 添加 NSudo Shared Library 且带有 C/C++ 和 .Net 互操作支持
  - 添加 NSudo Devil Mode (NSudoDM).
  - 添加 Mouri Internal Library Essentials (Mile).
- 编译本项目需要注意的变更事项
  - Visual Studio 已经升级到 2019
  - Windows 10 SDK 已经升级到最新
  - 改善对 AppVeyor CI 和 GitHub Actions CI 的支持（感谢 Margen67）

**NSudo 6.2.1812.31**

- 添加法语翻译（由 Thomas Dubreuil 贡献）
- 使用 JSON for Modern C++ 替代 RapidJSON 以符合 C++17 规范
- 改善图形界面用户体验（感谢 Lenny）
- 修复上下文菜单 Bug（感谢 Thomas Dubreuil 和 龍魂）
- 修复命令行解析器 Bug（感谢 wzzw）
- 添加繁体中文翻译（由 罗宇凡 贡献）

**NSudo 6.1.1811.18**

- 把 NSudoC 与 NSudoG 合并入 NSudo
- 为 ARM 和 ARM64 的 Release 二进制编译配置添加 VC-LTL 支持，并移除 VC-LTL 4.0
  之前版本的支持（大力感谢 mingkuang）
- 添加以下新的命令行选项
  - CurrentDirectory（由 testtest322 建议）
  - Help
  - H
  - Priority（由 testtest322 建议）
  - ShowWindowMode（由 testtest322 建议）
  - UseCurrentConsole
  - Version
  - Wait（由 testtest322、wzzw 和 Domagoj Smolčić 建议）
- 移除一些未文档化的命令行使用方式
- 改进数个实现
  - 重构命令行解析器
  - 引入新式创建进程前端
  - 使用 ATL 实现主窗口
  - 修复上下文菜单 Bug（感谢 Thomas Dubreuil）
- 更新许可的版权所有者
- 在文档移除捐赠链接

**NSudo 6.0.1804.5**

- 修复在 Windows Vista 和 Server 2008 下崩溃的问题（感谢 hydra79545）
- 与 M2-Team UWP 项目共享实现（详情请阅读
  “[https://github.com/Project-Nagisa/Nagisa/blob/master/Changelog.md](https://github.com/Project-Nagisa/Nagisa/blob/master/Changelog.md)”）
- 移除无用实现
- 改进 NSudoStartService 函数的实现
- 使用 RapidJSON 替代 JSON for Modern C++ 以减小二进制大小

**NSudo 6.0.1802.2 v2**

- 修复点击运行按钮只弹出命令提示符的问题。（感谢 AeonX）

**NSudo 6.0.1802.2**

- 修复多个 Bug 和改善多个实现
- 增加两个独立的可执行文件用于不同情况
  - NSudoC.exe
    - 纯命令行版本，子系统设置为“控制台”
    - 在控制台下运行良好，但是在非控制台进程调用会出现黑色控制台窗口
    - 为了保证最佳体验，NSudoC 不支持上下文菜单
  - NSudoG.exe
    - 纯命令行版本，子系统设置为“Windows”
    - 可以静默运行，没有黑色控制台窗口
- NSudo 将通过 M2MessageDialog 而不是 TaskDialog 显示信息
  - 理由
    - 因为可以使用纵向滚动条，NSudo 可以在出错时提供更加详细的内容
    - 你可以复制对话框里的内容
    - 支持 Windows 讲述人，于是可以使用 CapsLock+H 让讲述人读取对话框内容
    - 比 TaskDialog 的字体更大
  - M2MessageDialog 特性
    - 在 Windows 10 Build 10240 或之后版本完全支持 Per-Monitor DPI Aware
    - 完全支持 Windows 讲述人
    - 你可以使用纵向滚动条并且可以复制里面的内容
    - 比 TaskDialog 的字体更大
    - 你可以按 Enter 键关闭对话框
  - 如果你想在你的项目使用 M2MessageDialog，请从此处下载以下文件：
    [https://github.com/M2Team/NSudo/tree/master/NSudoSDK](https://github.com/M2Team/NSudo/tree/master/NSudoSDK)
    - M2DPIScaling.cpp
    - M2DPIScaling.h
    - M2MessageDialog.cpp
    - M2MessageDialog.h
    - M2MessageDialogResource.h
    - M2MessageDialogResource.rc
- 移除繁体中文和日语的翻译，因为翻译内容已经过时而且我不懂怎么用
- 升级 JSON for Modern C++ 到 3.0.1
- 右键菜单
  - 增加多语言描述
  - 为所有项目添加“开启全部特权”选项
- 更新命令行帮助和文档

**NSudo 6.0.1801.19**

- 修复 NSudoDuplicateSessionToken 函数定义 Bug（感谢 mingkuang）
- 修复在图形界面下无法启用全部特权的 Bug（感谢 abbodi1406）
- 修复没有 VC-LTL 时 x86 和 x86-64(AMD64)的 Release 编译配置未采用静态编译的 Bug

**NSudo 5.3.1801.11**

- 修复获取 System 令牌函数的一个潜在 Bug（感谢 mingkuang）
- 对 x86 和 x86-64(AMD64)的 Release 编译配置提供 VC-LTL 库支持（感谢 mingkuang）
  - PS：把 NSudo 和 VC-LTL 一起使用可以减小 NSudo 二进制的体积
- 整理文档

**NSudo 5.2 (5.2.1709.8 - 5.2.1710.26)**

- 整理代码，修复若干 Bugs
- 更新文档，增加英文自述
- 添加对 ARM 和 ARM64 平台的支持（感谢 fcharlie）
- 优化命令行解析
- 添加右键菜单支持
  - 使用 /Install 或 -Install 参数添加右键菜单（命令行参数大小写不敏感）
  - 使用 /Uninstall 或 -Uninstall 参数移除右键菜单（命令行参数大小写不敏感）

**NSudo 5.1 (5.0.1708.9 - 5.1.1708.19)**

- 修复批处理调用 NSudo 后批处理变量不生效的问题（感谢 芈员外）
- 令 NSudo 在带有命令行的状态下也能自动请求管理员权限（感谢 鸢一雨音）
- 更换新图标，顺便解决在 Windows Vista 之前版本系统上不显示 NSudo 图标的问题
  （PS：NSudo 最低要求依旧是 Windows Vista）
- 改进命令行解析（感谢 鸢一雨音）
- 更新源代码许可的版权（对说辞进行了优化）和更新感谢名单（新增人士）

**NSudo 5.0 (4.4.1705.28 - 5.0.1707.31)**

- 使用新的获取会话 ID 方法解决在 Server 系统的远程桌面会话上使用 NSudo 运行应用可能无
  法显示界面的问题（感谢 sebus）
- 更新文档和许可协议以符合实际情况
- 移除 VC-LTL（由 fcharlie 建议），理由如下：
  - 虽然二进制大小增加 80KB，但源代码大小缩小 57.6MB
  - 源代码大小缩小后，NSudo 的云编译速度大幅提升
  - 可以少屏蔽大量编译警告
- 使用 NSudoSDK 项目代替 M2-SDK 项目
- 改进版本定义头文件
- 编译器启用 SDL 检查、调整编译输出目录和更新 CI 编译配置文件
- 调整并优化代码(感谢 fcharlie 的建议)
- .gitignore 文件更新(由 fcharlie 实现)
- 完全使用 MSDN 文档化 API 实现 NSudoAPI.h 以方便人们调用
- 与 Nagisa 项目共用 m2base.h
- 整理屏蔽的警告，该版本 NSudo 屏蔽了以下警告实现 /W4 /WX 编译
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
- 使用 git 子模块机制（由 myfreeer 实现）
- 配置 AppVeyor（由 myfreeer 提供灵感）
- 开始使用 AppVeyor 自动编译
- 更新 M2-SDK 和 VC-LTL 子模块
- 命令行解析从 main 函数拆分
- 修复升级 VC-LTL 后出现的编译警告（有空会 pull fix 到 VC-LTL）
- 版本号重新由自己而不是 CI 编译服务控制
- 整理解决方案布局

**NSudo 4.3.1703.25**

- 32 位版本取消对 SSE 和 SSE2 指令集的依赖（为了保证完美的兼容性）
- 移除 NTIShell, NSudo.AppContainer, MiniFM 子项目
- NSudoSDK 完全被 M2-SDK 和 M2.NSudo.h 替代
- 关于界面布局调整
- 子系统设置调整为 Windows 子系统（为了不再弹出黑框）
- 优化代码，减少全局变量
- System 令牌副本创建函数移除会话 ID 参数（因为现实情况只能使用当前会话 ID）
- 使用旧版应用调用方式（即使用 cmd，解决无法调用带参数应用的问题）
- 优化在 UI 自动化工具（例如讲述人等读屏软件）上的使用体验
- “运行”按钮被设为默认按钮以提升使用体验
- 优化多语言资源以减小体积
- 修复 UI 标题栏没有图标的问题
- 为 UI 增加最小化按钮
- 修复数个库函数返回值 Bug
- 修复数个命令行解析 Bug
- 修复 UI 图标的 DPI 缩放问题
- 开始使用 Visual Studio 2017 编译
- 移除 NSudo-GUI 项目
- 代码不再包含 M2-SDK 和 VC-LTL 的内容，需要单独从 github 克隆

**NSudo 4.2**

- 引入新 NSudoSDK API 并且对已有 NSudoSDK API 进行改善
- 优化代码，以减少 Windows API 调用次数
- 修复不带任何参数情况下可能的奔溃问题
- 修复控制台部分不能在非管理员权限显示命令行帮助的问题
- 基于 ShellExecute 自建调用宿主，以去除对 cmd.exe 的依赖
- 引入 NTIShell（相当于 NSudo 1.0）重制版，作为 NSudoSDK 的一个示例
- 更改 MiniFM 图标

**NSudo 4.1**

- 修复命令行使用-U:D 导致程序奔溃的问题
- 更正命令行的 NSudoC 残余描述（感谢 NotePad）
- 支持文件拖拽（感谢 NotePad）

**NSudo 4.0**

- 重写代码，提供 NSudoSDK，使代码容易使用在其他项目上
- 命令行下新增"/"前缀参数支持,例如: NSudo /U:T /P:E cmd (感谢 th1r5bvn23)
- 支持默认参数，即以 TrustedInstaller 令牌且开启全部特权运行 (感谢 老九)
- 在默认快捷命令列表加入 host 编辑
- 增加 NSudo 和 MiniFM 的 Per-Monitor DPI Aware 支持
- 采用 VC-LTL 大幅度减小程序体积（感谢 mingkuang）
- 更改图标（感谢 20011010wo）
- 精简并优化主界面（感谢 kCaRhC 卡壳，さくら）
- 使用 TaskDialog 替代 MessageBox
- 对关于界面进行调整，并在关于界面加入命令行帮助
- 修复弹出文件不存在的问题
- 修复命令行解析的一个潜在 Bug
- 缓解 NSudo 图形界面的空格问题（浏览功能自动给命令行加引号）
- 消除在编译时的警告(/Wall 和/WX 两个参数同时使用)

**NSudo 2016.1**

- 修复 TrustedInstaller 下运行程序界面不显示问题（感谢 abbodi1406）
- 修复命令行解析的漏洞和 UI 错误（感谢 imadlatch）
- 整理代码，提升可读性
- 当前目录设为 NSudo 所在目录（未来会更加灵活）
- ShortCut 实现无限项目
- 新增简易文件管理器小工具（感谢 20011010wo）

**NSudo 2016**

- 支持多语言（程序内含简中，繁中，英文，日文）
- 命令行处理重写
- 实现代码全部重构；效率更高

**NSudo 3.2 Fix1**

- 优化程序逻辑；减少无用代码
- 命令行版和图形版二合一

**NSudo 3.2**

- 修复无法使用带有空格的路径的问题
- NSudo 和 NSudoC 单文件化
- 增加 NSudo.bat 方便新手准确调用与电脑架构相符的 NSudo 版本
- NSudoSDK 增加静态库（用 NSudo SDK 开发的工具可以实现单文件）
- 编译平台采用 Visual Studio 2015 + Windows 10 SDK

**NSudo 3.1 Debug**

- 修复 UI 的 ComboBox 不能输入太长文字的问题
- 修复某些情况下不能使用的问题（由于开发机 Windows10 的 Bug 而导致误认为那种方式可
  行）
- 增加真正的令牌降权（除了 cmd 会误显示管理员外；其他的会将其看作普通用户）
- 增加命令行版本
- 增加常用列表自定义功能

**NSudo 3.0 R2**

- 修复不能打开其他被系统关联文件的 Bug
- SDK 的头文件改进：增加#pragma comment(lib,"NSudoAPI.lib")

**NSudo 3.0**

- 支持外部应用调用（很抱歉让一些人等太久）
- 增加了常用调用列表（暂时不支持自定义；未来 3.1 会加入）
- 加入了降权功能（当然，是完美降权到 UAC 未提权前。当然原理不是用获取 explorer 令牌
  和创建计划任务）
- 支持对权限令牌的自定义
- 界面的完全重构（相对于 2.x 来说）
- 代码优化（相对于 NSudo 3.0 M1 来说）
- 加入 NSudo SDK
- 原生 64 位版本
- 实现了调用外部程序无视 WOW64 重定向的方法（NSudoCreateProcess）
- WinPE 支持（虽然没起多大作用）

**NSudo 2.1**

- 实现自动开启所有权限 Token
- 对 cmd 的调用使用绝对路径，估计可以避免一些不必要的 Bug
- 优化程序代码

**NSudo 2.0**

- 代码全部使用 C++ Win32 SDK 重写（程序从 692KB 缩小到 92KB）
- 提供获取权限的选项
- 提供命令行参数模式
- 更换了图标

**NSudo 1.2**

- 未公开发布（估计还是在修复 SessionID 问题）

**NSudo 1.1**

- 修复 SessionID 问题
- 32 位和 64 位版本合体（根据架构确定运行那个架构的命令提示符，采用 SysNative 目录
  （64 位 Vista 开始有的重定向）调用 64 位 cmd）

**NTIShell 1.0**

- 根据 raymai97 的超级命令提示符制作的第一个版本
