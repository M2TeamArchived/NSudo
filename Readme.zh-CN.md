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
  - [创建新 Issue](https://github.com/M2Team/NSudo/issues/new).

### 代码贡献参考

#### Prerequisites

- Visual Studio 2017 version 15.9 or later.
  - Install from here: http://visualstudio.com/downloads
  - You also need install ARM and ARM64 components.
- Windows 10 version 1507 SDK or later.
  - You need to change the Windows SDK version in the project properties if the
    version of Windows 10 SDK I used isn't installed on your PC.
  - You also need install ARM and ARM64 components when you installing the 
    Windows 10 Version 1703 SDK or later.

#### How to build all targets of NSudo

Run `BuildAllTargets.bat` in `src/Native`.

#### How to modify or debugging NSudo

Open `NSudo.sln` in `src/Native`.

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

### How to update documents.

Refer to https://github.com/M2Team/NSudo/pull/29.

To build new docs, you'll need to have [Node.js](https://nodejs.org) and 
[Yarn](https://yarnpkg.com) installed on your system, and run `build.bat` in
`src/Documents`.

Docs will be built into `docs`, where GitHub Pages treated as site root. So be
sure to commit `docs` changes.

CI/CD is not included in this PR, so manual build is required after every docs
update. `yarn dev` runs a local hot-reload-enabled docs server for easier 
debugging.

Docs engine is based on [VuePress](https://v1.vuepress.vuejs.org).
