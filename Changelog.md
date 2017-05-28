# 改进日志 Changelog

**NSudo 4.4.1705.28**
- 更新 Readme.md（感谢 myfreeer 大力帮忙）
- 更新 ShortCutList.ini（由 myfreeer 实现）
- 更新 appveyor.yml
- 使用新的获取会话ID方法尝试解决在Server系统的远程桌面会话上使用NSudo运行应用可能无法显示界面的问题（感谢 sebus）

**NSudo 4.4.1705.19**
- 更新M2-SDK和VC-LTL子模块
- 命令行解析从main函数拆分
- 修复升级VC-LTL后出现的编译警告（有空会pull fix到VC-LTL）
- 版本号重新由自己而不是CI编译服务控制
- 整理解决方案布局

**NSudo 4.4.1705.0**
- 开始使用AppVeyor自动编译

**NSudo 4.4.1704.29**
- 适配最新版M2-SDK
- 适配最新版VC-LTL
- 修改编译选项
- 使用git子模块机制（由 myfreeer 实现）
- 配置AppVeyor（由 myfreeer 提供灵感）

**NSudo 4.3.1703.25**
- 开始使用Visual Studio 2017编译
- 移除NSudo-GUI项目
- 代码不再包含M2-SDK和VC-LTL的内容，需要单独从github克隆

**NSudo 4.3.1703.18**
- 修复数个库函数返回值Bug
- 修复数个命令行解析Bug
- 修复UI图标的DPI缩放问题

**NSudo 4.3.1703.13**
- System令牌副本创建函数移除会话ID参数（因为现实情况只能使用当前会话ID）
- 使用旧版应用调用方式（即使用cmd，解决无法调用带参数应用的问题）
- 优化在UI自动化工具（例如讲述人等读屏软件）上的使用体验
- “运行”按钮被设为默认按钮以提升使用体验
- 优化多语言资源以减小体积
- 修复UI标题栏没有图标的问题
- 为UI增加最小化按钮

**NSudo 4.3.1703.8**
- 32位版本取消对SSE和SSE2指令集的依赖（为了保证完美的兼容性）
- 移除NTIShell, NSudo.AppContainer, MiniFM子项目
- NSudoSDK完全被M2-SDK和M2.NSudo.h替代
- 关于界面布局调整
- 子系统设置调整为Windows子系统（为了不再弹出黑框）
- 优化代码，减少全局变量

**NSudo 4.2**
- 引入新NSudoSDK API并且对已有NSudoSDK API进行改善
- 优化代码，以减少Windows API调用次数
- 修复不带任何参数情况下可能的奔溃问题
- 修复控制台部分不能在非管理员权限显示命令行帮助的问题
- 基于ShellExecute自建调用宿主，以去除对cmd.exe的依赖
- 引入NTIShell（相当于NSudo 1.0）重制版，作为NSudoSDK的一个示例
- 更改MiniFM图标

**NSudo 4.1**
- 修复命令行使用-U:D导致程序奔溃的问题
- 更正命令行的NSudoC残余描述（感谢NotePad）
- 支持文件拖拽（感谢NotePad）

**NSudo 4.0**
- 重写代码，提供NSudoSDK，使代码容易使用在其他项目上
- 命令行下新增"/"前缀参数支持,例如: NSudo /U:T /P:E cmd (感谢 th1r5bvn23)
- 支持默认参数，即以TrustedInstaller令牌且开启全部特权运行 (感谢 老九)
- 在默认快捷命令列表加入host编辑
- 增加NSudo和MiniFM的Per-Monitor DPI Aware支持
- 采用VC-LTL大幅度减小程序体积
- 更改图标（感谢20011010wo）
- 精简并优化主界面（感谢 kCaRhC卡壳，さくら）
- 使用TaskDialog替代MessageBox
- 对关于界面进行调整，并在关于界面加入命令行帮助
- 修复弹出文件不存在的问题
- 修复命令行解析的一个潜在Bug
- 缓解NSudo图形界面的空格问题（浏览功能自动给命令行加引号）
- 消除在编译时的警告(/Wall和/WX两个参数同时使用)

**NSudo 2016.1**
- 修复TrustedInstaller下运行程序界面不显示问题（感谢abbodi1406）
- 修复命令行解析的漏洞和UI错误（感谢imadlatch）
- 整理代码，提升可读性
- 当前目录设为NSudo所在目录（未来会更加灵活）
- ShortCut实现无限项目
- 新增简易文件管理器小工具（感谢20011010wo）

**NSudo 2016**
- 支持多语言（程序内含简中，繁中，英文，日文）
- 命令行处理重写
- 实现代码全部重构；效率更高

**NSudo 3.2 Fix1**
- 优化程序逻辑；减少无用代码
- 命令行版和图形版二合一

**NSudo 3.2**
- 修复无法使用带有空格的路径的问题
- NSudo和NSudoC单文件化
- 增加NSudo.bat方便新手准确调用与电脑架构相符的NSudo版本
- NSudoSDK增加静态库（用NSudo SDK开发的工具可以实现单文件）
- 编译平台采用Visual Studio 2015 + Windows 10 SDK

**NSudo 3.1 Debug**
- 修复UI的ComboBox不能输入太长文字的问题
- 修复某些情况下不能使用的问题（由于开发机Windows10的Bug而导致误认为那种方式可行）
- 增加真正的令牌降权（除了cmd会误显示管理员外；其他的会将其看作普通用户）
- 增加命令行版本
- 增加常用列表自定义功能

**NSudo 3.0 R2**
- 修复不能打开其他被系统关联文件的Bug
- SDK的头文件改进：增加#pragma comment(lib,"NSudoAPI.lib")

**NSudo 3.0**
- 支持外部应用调用（很抱歉让一些人等太久）
- 增加了常用调用列表（暂时不支持自定义；未来3.1会加入）
- 加入了降权功能（当然，是完美降权到UAC未提权前。当然原理不是用获取explorer令牌和创建计划任务）
- 支持对权限令牌的自定义
- 界面的完全重构（相对于2.x来说）
- 代码优化（相对于NSudo 3.0 M1来说）
- 加入NSudo SDK
- 原生64位版本
- 实现了调用外部程序无视WOW64重定向的方法（NSudoCreateProcess）
- WinPE支持（虽然没起多大作用）

**NSudo 2.1**
- 实现自动开启所有权限Token
- 对cmd的调用使用绝对路径，估计可以避免一些不必要的Bug
- 优化程序代码

**NSudo 2.0**
- 代码全部使用C++ Win32 SDK重写（程序从692KB缩小到92KB）
- 提供获取权限的选项
- 提供命令行参数模式
- 更换了图标

**NSudo 1.2**
- 未公开发布（估计还是在修复SessionID问题）

**NSudo 1.1**
- 修复SessionID问题
- 32位和64位版本合体（根据架构确定运行那个架构的命令提示符，采用SysNative目录（64位Vista开始有的重定向）调用64位cmd）

**NTIShell 1.0**
- 根据raymai97的超级命令提示符制作的第一个版本
