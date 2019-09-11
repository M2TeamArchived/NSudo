# ![Logo](Logo.png) NSudo - A Powerful System Administration Tool

[![License](https://img.shields.io/github/license/M2Team/NSudo)](License.md)
[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)

This is the source code repository of NSudo. If you wonder to visit the NSudo 
official website, download NSudo or read the NSudo documents etc, please visit
https://m2team.github.io/NSudo.

This readme file will be the developer oriented document because this it is 
under the source code repository.

## Status dashboard

| ---- | ---- |
| AppVeyor CI | [![AppVeyor CI](https://ci.appveyor.com/api/projects/status/github/M2Team/NSudo?branch=master&svg=true)](https://ci.appveyor.com/project/MouriNaruto/nsudo) |
| Latest Version | [![Latest Version](https://img.shields.io/github/release/M2Team/NSudo.svg)](https://github.com/M2Team/NSudo/releases/latest) |
| Latest Release Downloads | [![Latest Release Downloads](https://img.shields.io/github/downloads/M2Team/NSudo/latest/total.svg)](https://github.com/M2Team/NSudo/releases/latest) |
| Total Downloads | [![Total Downloads](https://img.shields.io/github/downloads/M2Team/NSudo/total.svg)](https://github.com/M2Team/NSudo/releases) |
| FOSSA Status | [![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FM2Team%2FNSudo.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FM2Team%2FNSudo?ref=badge_shield) |

## License

The offical NSudo repository (not including third-party libraries) is **only** 
distributed under the MIT License today because we want to give the **maximum 
respect** to every NSudo users and we also hope every people treat others 
kindly. For more information about the MIT License which used in NSudo, please 
read [License.md](License.md).

## 3rd-party libraries which used

- JSON for Modern C++
  - Copyright: Niels Lohmann
  - License: https://github.com/nlohmann/json/blob/develop/LICENSE.MIT
- (Optional) VC-LTL
  - Copyright: Chuyu Team
  - License: https://github.com/Chuyu-Team/VC-LTL/blob/master/LICENSE.txt

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

- Visual Studio 2017 version 15.9 or later.
  - Install from here: http://visualstudio.com/downloads
  - You also need install ARM and ARM64 components.
- Windows 10 version 1507 SDK or later.
  - You need to change the Windows SDK version in the project properties if the
    version of Windows 10 SDK I used isn't installed on your PC.
  - You also need install ARM and ARM64 components when you installing the 
    Windows 10 Version 1703 SDK or later.
- (Optional but recommend) If you want to reduce the release mode binaries size
  for x86, x64 and ARM64 port of NSudo, you can use VC-LTL.
  - VC-LTL GitHub Repository: https://github.com/Chuyu-Team/VC-LTL
  - How to use VC-LTL to optimize NSudo binaries size:
    - Download VC-LTL binary pack from 
	  https://github.com/Chuyu-Team/VC-LTL/releases/latest.
    - Unpack the VC-LTL binary pack and double-click install.cmd in the unpack
	  folder.

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

