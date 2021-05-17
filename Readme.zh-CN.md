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
NSudo 的文档等，请转到 https://m2team.github.io/NSudo.

本自述文件仅面向开发者，毕竟隶属于源代码仓库下。

## 2021 Development Roadmap

- [ ] Add Current User (Elevated) Mode.
  - [x] Implemented in NSudo Shared Library.
  - [ ] Implemented in NSudo Launcher.
- [ ] Use wxWidgets to implement the UI.
- [ ] TOML-based environment configuration file.
- [ ] Add more APIs to NSudo Shared Library.
- [ ] Export PDF directly from the offical website.
- [ ] Improve the Gitee mirror experience.

## 行为准则

请参阅 [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)。

## 向 NSudo 贡献

### 如何成为贡献者

- 直接贡献
  - **请直接创建 Pull Requests。**
  - 如有疑惑，请发送邮件到 Mouri_Naruto@Outlook.com 以进行讨论。
- 反馈建议和问题
  - 我们使用 GitHub Issues 跟踪问题和建议。
  - 对于问题和建议，请[创建新 Issue](https://github.com/M2Team/NSudo/issues/new).

### 代码贡献参考

#### 构建前置条件

- Visual Studio 2017 Version 15.9 及之后版本。
  - 如果你要编译 ARM64 版本的 NSudo 还需要勾选 ARM64 版本的 MSVC 编译工具链和 
    ATL/MFC 组件。
- Windows 10 Version 1507 SDK 及之后版本。
  - 如果你使用的是 Windows 10 Version 1703 SDK 及之后版本且你要编译 ARM64 
    版本的 NSudo 还需要勾选 ARM64 的相关组件。

#### 编译 NSudo 的所有目标

运行 `src/Native` 目录下的 `BuildAllTargets.bat`。

#### 如何修改和调试 NSudo

运行 `src/Native` 目录下的 `NSudo.sln`。

#### Code style and conventions

- C++: [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
- C#: Follow the .NET Core team's [C# coding style](https://github.com/dotnet/corefx/blob/master/Documentation/coding-guidelines/coding-style.md)

For all languages respect the [.editorconfig](https://editorconfig.org/) file 
specified in the source tree. Many IDEs natively support this or can with a 
plugin.

#### Copying files from other projects

The following rules must be followed for PRs that include files from another 
project:
* The license of the file is
[permissive](https://en.wikipedia.org/wiki/Permissive_free_software_licence).
* The license of the file is left intact.
* The contribution is correctly attributed in the [Readme](Readme.md)
file in the repository, as needed.

### 如何更新文档

请参阅 https://github.com/M2Team/NSudo/pull/29。

如要编译文档，你需要在你的开发环境下安装 [Node.js](https://nodejs.org) 和 
[Yarn](https://yarnpkg.com) 后运行 `src/Documents` 目录下的 `build.bat`。

构建的新文档将会放在 `docs` 目录下且 GitHub Pages 将该目录视为站点的根目录。

文档引擎基于 [VuePress](https://v1.vuepress.vuejs.org) 构建。
