# ![Logo](Logo.png) NSudo - 系统管理工具包

[![AppVeyor CI](https://ci.appveyor.com/api/projects/status/github/M2Team/NSudo?branch=master&svg=true)](https://ci.appveyor.com/project/MouriNaruto/nsudo)
[![Latest Version](https://img.shields.io/github/release/M2Team/NSudo.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Latest Release Downloads](https://img.shields.io/github/downloads/M2Team/NSudo/latest/total.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Total Downloads](https://img.shields.io/github/downloads/M2Team/NSudo/total.svg)](https://github.com/M2Team/NSudo/releases)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](License.md)
[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FM2Team%2FNSudo.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FM2Team%2FNSudo?ref=badge_shield)

[English](Readme.md)

这里是 NSudo 的源代码仓库。如果你想访问 NSudo 的官方网站、下载 NSudo 或者阅读
NSudo 的文档等, 请转到 https://nsudo.m2team.org。

本自述文件仅面向开发者, 毕竟隶属于源代码仓库下。

## 2021 Development Roadmap

- [x] 添加当前用户 (提权) 模式
  - [x] 在 NSudo Shared Library 实现
  - [x] 在 NSudo Launcher 实现
- [ ] 使用 wxWidgets 实现用户界面
- [ ] 基于 TOML 的环境配置文件
- [ ] 在 NSudo Shared Library 中添加更多 API
- [ ] 官方网站支持导出 PDF
- [ ] 改善码云镜像体验
  - [x] 对代码仓库根目录的自述文件进行本地化
  - [ ] 实现自动同步

## 相关人士

请参阅 [People.md](People.md)。

## 行为准则

请参阅 [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)。

## 向 NSudo 贡献

### 如何成为贡献者

- 直接贡献
  - **请直接创建 Pull Requests。**
  - 如有疑惑, 请发送邮件到 Mouri_Naruto@Outlook.com 以进行讨论。
- 反馈建议和问题
  - 我们使用 GitHub Issues 跟踪问题和建议。
  - 对于问题和建议, 请[创建新 Issue](https://github.com/M2Team/NSudo/issues/new).

### 代码贡献参考

#### 构建前置条件

- Visual Studio 2017 Version 15.9 及之后版本。
  - 如果你要编译 ARM64 版本的 NSudo 还需要勾选 ARM64 版本的 MSVC 编译工具链和 
    ATL/MFC 组件。
- Windows 10 Version 1507 SDK 及之后版本。
  - 如果你使用的是 Windows 10 Version 1703 SDK 及之后版本且你要编译 ARM64 
    版本的 NSudo 还需要勾选 ARM64 的相关组件。

#### 编译 NSudo 的所有目标

运行 `Source/Native` 目录下的 `BuildAllTargets.bat`。

#### 如何修改和调试 NSudo

运行 `Source/Native` 目录下的 `NSudo.sln`。

#### 代码风格和规范

- C++: [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
- C#: 遵循 .NET Core 团队的 [C# coding style](https://github.com/dotnet/corefx/blob/master/Documentation/coding-guidelines/coding-style.md)

所有编程语言的实现都需要遵循代码树下 [.editorconfig](https://editorconfig.org/)
文件的设定, 许多 IDE 都对该文件有内置或者插件支持。

#### 使用其他项目的文件

如果 PR 中包含其他项目的文件, 需要遵循下述规定:
* 该文件的许可证必须为
  [宽松许可](https://en.wikipedia.org/wiki/Permissive_free_software_licence).
* 该文件的许可证必须标明。
* 项目的引用必须正确标注在 [许可证](License.md) 文件中。

### 如何更新文档

请参阅 https://github.com/M2Team/NSudo/pull/29。

如要编译文档, 你需要在你的开发环境下安装 [Node.js](https://nodejs.org) 和 
[Yarn](https://yarnpkg.com) 后运行 `Website` 目录下的 `build.bat`。

文档引擎基于 [VuePress](https://v1.vuepress.vuejs.org) 构建。
