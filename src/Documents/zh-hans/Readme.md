# NSudo - 系统管理工具包

![屏幕截图](./Screenshot.png)

## 注：成为 NSudo 的赞助者

我是一个非计算机科班出身的软件开发者，今年毕业后会在一家自动驾驶初创公司工作。
由于未来的工作中涉及到的主要是 linux 平台开发，而我现在的个人项目主要是为 
Windows 平台而设计，所以我希望能通过他人的捐赠继续维持自己维护个人工具的热情。

Patreon: [https://www.patreon.com/MouriNaruto](https://www.patreon.com/MouriNaruto)

爱发电: [https://afdian.net/@MouriNaruto](https://afdian.net/@MouriNaruto)

- 如果我达到了每个月 1000 美元的目标，我将会每年更新两个大版本。
- 如果我达到了每个月 2000 美元的目标，我会为 NSudo 二进制添加 EV 代码签名证书。

感谢支持。

毛利

## 关于

### 原型

注意：NSudo 基于 raymai97 的超级命令提示符，请参阅
[这里](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "这里") 以获取更多关于
超级命令提示符的信息。

### 特性列表

- 以 MIT 许可证发行
- 提供 x86, x86-64, ARM, ARM64 二进制
- 支持 Windows Vista 及之后版本
- 使用初雨团队的 VC-LTL 和 libkcrt 以获取更小的二进制体积
- 使用 C++17，但在大部分情况下只使用核心语言特性
- NSudo Launcher
  - 以 TrustedInstaller 访问令牌运行程序
  - 以 System 访问令牌运行程序
  - 以当前用户的访问令牌运行程序
    - 注：如果用户账户控制即 UAC 没有被禁用，则该模式的权限与标准用户等价
  - 以当前进程的访问令牌运行程序
    - 注：该模式的权限与提升后的用户等价
  - 以当前进程 LUA 模式的访问令牌运行程序
    - 注：该模式的权限与标准用户等价且该实现和 Internet Explorer 浏览器中的 
      iertutil.dll 中的对应实现一致
  - 支持以指定的特权设置运行程序
    - 注：启用全部特权, 禁用所有特权
  - 支持以指定的完整性级别运行程序
    - 注：系统、高、中、低
  - 支持以指定的进程优先级运行程序
    - 注：低、低于正常、正常、高于正常、高、实时
  - 支持以指定的窗口模式运行程序
    - 注：显示窗口、隐藏窗口、最大化、最小化
  - 支持进程创建后并等待其运行结束
  - 支持以指定的当前目录运行程序
  - 支持在当前控制台窗口下运行程序
  - 支持快捷方式列表
    - 注：你可以通过编辑 NSudo.json 的方式定制
  - 支持多种命令行风格
  - 多语言支持
    - 注：简体中文、繁体中文、英语、法语、意大利语、西班牙语
  - 完整的高 DPI 支持
    - 注：和 Windows 外壳 (conhost.exe) 的实现一样完美，在 Windows 10 Build 
      10240 及之后版本有完整的 Per-Monitor DPI-Aware 支持和在 Windows Vista 到
      Windows 8.1 之间的版本有完整的 System DPI-Aware 支持
  - 完整的无障碍访问支持
    - 注：你可以在 Windows 讲述人下顺畅的使用 NSudo Launcher
  - 高性能
    - 注：因为其实现不需要创建 Windows 服务和 Windows 服务进程
  - 为开发者提供 C APIs 和 .Net Core 互操作支持
- NSudo 恶魔模式
  - 对于希望无视管理员权限的进程下的文件和注册表访问判断的开发者而言是最优雅的
    解决方案
  - 使用 Microsoft Detours 库对 API 进行挂钩以保证最大兼容
  - 其二进制仅依赖了 ntdll.dll 的以函数名导出的 API

### 使用了 NSudo 的第三方项目

- MSMG ToolKit
- Sledgehammer (WUMT Wrapper Script)
- Dism++

### 系统要求

- 支持的系统版本：Windows NT 6.0 及之后版本
- 支持的处理器架构：x86, x86-64(AMD64), ARM, ARM64

### 第三方介绍

- HowToDoNinja: [https://howtodoninja.com/how-to/nsudo-run-programs-with-full-admin-privileges-windows/](https://howtodoninja.com/how-to/nsudo-run-programs-with-full-admin-privileges-windows/)
- MajorGeeks: [https://www.majorgeeks.com/files/details/nsudo.html](https://www.majorgeeks.com/files/details/nsudo.html)
- softpedia.com: [https://www.softpedia.com/get/Tweak/System-Tweak/NSudo.shtml](https://www.softpedia.com/get/Tweak/System-Tweak/NSudo.shtml)
- TrishTech.com: [https://www.trishtech.com/2018/11/nsudo-run-programs-with-full-privileges-in-windows/](https://www.trishtech.com/2018/11/nsudo-run-programs-with-full-privileges-in-windows/)
- Wilders Security Forums: [https://www.wilderssecurity.com/threads/396818](https://www.wilderssecurity.com/threads/396818)

## 使用方法

### 快速上手

请打开【CPU 架构】目录，然后双击 NSudo.exe. 根据提示操作即可。例如，如果你想在
你的 Intel 或 AMD 设备上使用 64 位 NSudo，你首先需要打开的是 x64 目录，然后双击
NSudoG.exe。
