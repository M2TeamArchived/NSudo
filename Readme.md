# ![Logo](Logo.png) NSudo - System Administration Toolkit

[![AppVeyor CI](https://ci.appveyor.com/api/projects/status/github/M2Team/NSudo?branch=master&svg=true)](https://ci.appveyor.com/project/MouriNaruto/nsudo)
[![Latest Version](https://img.shields.io/github/release/M2Team/NSudo.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Latest Release Downloads](https://img.shields.io/github/downloads/M2Team/NSudo/latest/total.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Total Downloads](https://img.shields.io/github/downloads/M2Team/NSudo/total.svg)](https://github.com/M2Team/NSudo/releases)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](License.md)
[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FM2Team%2FNSudo.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FM2Team%2FNSudo?ref=badge_shield)

[简体中文](Readme.zh-CN.md)

This is the source code repository of NSudo. If you wonder to visit the NSudo 
official website, download NSudo or read the NSudo documents etc, please visit
https://m2team.github.io/NSudo.

This readme file will be the developer oriented document because this it is 
under the source code repository.

## 2021 Development Roadmap

- [ ] Add Current User (Elevated) Mode.
  - [x] Implemented in NSudo Shared Library.
  - [ ] Implemented in NSudo Launcher.
- [ ] Use wxWidgets to implement the UI.
- [ ] TOML-based environment configuration file.
- [ ] Add more APIs to NSudo Shared Library.
- [ ] Export PDF directly from the offical website.
- [ ] Improve the Gitee mirror experience.
  - [x] Translate the readme in the source tree root.
  - [ ] Synchronizing automatically when commits pushed.

## Relevant People

Please read [People.md](People.md).

## Code of Conduct

Please read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

## Contributing to NSudo

### How to become a contributor

- Direct contributions
  - **Create pull requests directly.**
  - Please send e-mails to Mouri_Naruto@Outlook.com if you have any
    questions.
- Feedback suggestions and bugs.
  - We use GitHub issues to track bugs and features.
  - For bugs and general issues please 
    [file a new issue](https://github.com/M2Team/NSudo/issues/new).

### Code contribution guidelines

#### Prerequisites

- Visual Studio 2017 Version 15.9 or later.
  - You also need install ARM64 components (MSVC Toolchain and ATL/MFC) if you
    want to compile ARM64 version of NSudo.
- Windows 10 Version 1507 SDK or later.
  - You also need install ARM64 components when you installing the Windows 10
    Version 1703 SDK or later and you want to compile ARM64 version of NSudo.

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
- The license of the file is
  [permissive](https://en.wikipedia.org/wiki/Permissive_free_software_licence).
- The license of the file is left intact.
- The contribution is correctly attributed in the [License](License.md)
  file in the repository, as needed.

### How to update documents.

Refer to https://github.com/M2Team/NSudo/pull/29.

To build new docs, you'll need to have [Node.js](https://nodejs.org) and 
[Yarn](https://yarnpkg.com) installed on your system, and run `build.bat` in
`src/Documents`.

Docs will be built into `docs`, where GitHub Pages treated as site root. So be
sure to commit `docs` changes.

Docs engine is based on [VuePress](https://v1.vuepress.vuejs.org).
