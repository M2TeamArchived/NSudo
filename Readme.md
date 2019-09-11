# ![Logo](Logo.png) NSudo - A Powerful System Administration Tool

[![AppVeyor](https://ci.appveyor.com/api/projects/status/github/M2Team/NSudo?branch=master&svg=true)](https://ci.appveyor.com/project/MouriNaruto/nsudo)
[![Latest release](https://img.shields.io/github/release/M2Team/NSudo.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Latest release downloads](https://img.shields.io/github/downloads/M2Team/NSudo/latest/total.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Total downloads](https://img.shields.io/github/downloads/M2Team/NSudo/total.svg)](https://github.com/M2Team/NSudo/releases)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](License.md)
[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FM2Team%2FNSudo.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FM2Team%2FNSudo?ref=badge_shield)

![Screenshot](docs-src/Screenshot.png)

- Languages
  - [English](Readme.md)
  - [简体中文](自述.md)
  - [繁體中文](說明.md)
- [About](#about)
  - [Prototype](#prototype)
  - [Third-party introduction](#third-party-introduction)
  - [System requirements](#system-requirements)
- [Usage](#usage)
  - [Quick Start](#quick-start)
  - [Command Line](#command-line)
  - [Shortcut List](#shortcut-list)
- [Documents](#documents)
  - [Changelog](#changelog)
  - [Relevant People](#relevant-people)
  - [Code of Conduct](#code-of-conduct)
  - [Contributing to NSudo](#contributing-to-nsudo)
- Git source repositories
  - [GitHub (Main)](https://github.com/M2Team/NSudo)
  - [Gitee (Mirror)](https://gitee.com/M2-Team/NSudo)
- Communities
  - [GitHub](https://github.com/M2Team/NSudo/issues)
  - [MDL](https://forums.mydigitallife.net/threads/59268/)
  - [52pojie](https://www.52pojie.cn/thread-847059-1-1.html)
- Contact
  - [E-mail](mailto:Mouri_Naruto@Outlook.com)

## About

### Prototype

NSudo is based on SuperCMD by Raymai97. Visit
[here](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "here") for more
information about SuperCMD.

### Third-party introduction

- MajorGeeks: https://www.majorgeeks.com/files/details/nsudo.html
- softpedia.com: https://www.softpedia.com/get/Tweak/System-Tweak/NSudo.shtml
- TrishTech.com: https://www.trishtech.com/2018/11/nsudo-run-programs-with-full-privileges-in-windows/
- Wilders Security Forums: https://www.wilderssecurity.com/threads/396818

### System requirements

- Supported OS Version: Windows NT 6.0 or later
- Supported CPU Architecture: x86, x86-64(AMD64), ARM, ARM64

## Usage

### Quick Start

Please go to the [CPU Architecture] folder and click NSudo.exe. Follow the
prompts. For example, if you want to use 64-bit NSudo on your Intel or AMD
device, you need to go to the x64 folder and click NSudoG.exe

### Command Line

```
Format: NSudo [ Options and parameters ] Command line or ShortCut Command

Options:

-U:[ Option ] Create a process with specified user option.
Available options:
    T TrustedInstaller
    S System
    C Current User
    P Current Process
    D Current Process (Drop right)
PS: This is a mandatory parameter.

-P:[ Option ] Create a process with specified privilege option.
Available options:
    E Enable All Privileges
    D Disable All Privileges
PS: If you want to use the default privileges to create a process, please do
not include the "-P" parameter.

-M:[ Option ] Create a process with specified Integrity Level option.
Available options:
    S System
    H High
    M Medium
    L Low
PS: If you want to use the default Integrity Level to create a process, please
do not include the "-M" parameter.

-Priority:[ Option ] Create a process with specified [rocess priority option.
Available options:
    Idle
    BelowNormal
    Normal
    AboveNormal
    High
    RealTime
PS: If you want to use the default Process Priority to create a process, please
do not include the "-Priority" parameter.

-ShowWindowMode:[ Option ] Create a process with specified window mode option.
Available options:
    Show
    Hide
    Maximize
    Minimize
PS: If you want to use the default window mode to create a process, please do
not include the "-ShowWindowMode" parameter.

-Wait Make NSudo wait for the created process to end before exiting.
PS: If you don't want to wait, please do not include the "-Wait" parameter.

-CurrentDirectory:[ DirectoryPath ] Set the current directory for the process.
PS: If you want to use the NSudo's current directory, please do not include the
"-CurrentDirectory" parameter.

-UseCurrentConsole Create a process with the current console window.
PS: If you want to create a process with the new console window, please do not
include the "-UseCurrentConsole" parameter.

-Version Show version information of NSudo.

-? Show this content.
-H Show this content.
-Help Show this content.

Context Menu:
  -Install   Copy NSudo to the Windows directory and add the context menu.
  -Uninstall Remove NSudo in the Windows directory and the context menu.

PS:
    1. All NSudo command arguments is case-insensitive.
    2. You can use the "/" or "--" override "-" and use the "=" override ":" in
       the command line parameters.  For example, "/U:T" and "-U=T" are
       equivalent.
    3. To ensure the best experience, NSudoC does not support context menu.

Example:
    If you want to run Command Prompt with TrustedInstaller, enable all
    privileges and the default Integrity Level.
        NSudo -U:T -P:E cmd
```

Example：If you want to run Command Prompt with TrustedInstaller, enable all
privileges and the default Integrity Level:

> NSudo -U:T -P:E cmd

Starting from NSudo 5.0.1708.16, the command line nested quotes is supported.
For example:

> NSudo -U:T cmd /c "dir "C:\Program Files" & pause"

### Shortcut List

You can edit NSudo.json to custom the Shortcut list, here are the demo
(NSudo.json in the NSudo.exe's folder):

```
{
  "ShortCutList_V2": {

    "Command Prompt": "cmd",
    "PowerShell": "powershell",
    "PowerShell ISE": "powershell_ise",
    "Edit Hosts": "notepad %windir%\\System32\\Drivers\\etc\\hosts"
  }
}
```

## Documents

### Changelog

**NSudo 7.0.1904.3**

- Update JSON for Modern C++ to 3.5.0.
- Use FILE instead of std::ifstream to reduce the memory usage and binary size.
- Merge NSudo.exe to NSudoG.exe.
- Use new compiler options to reduce the binary size.
- Update to Visual Studio 2019.

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
  read "https://github.com/Project-Nagisa/Nagisa/blob/master/Changelog.md")
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
    these files in https://github.com/M2Team/NSudo/tree/master/NSudoSDK
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

### Relevant People

Please read [Relevant People](People.md)

### Code of Conduct

Please read [Code of Conduct](CODE_OF_CONDUCT.md)

### Contributing to NSudo

Please read [Contributing to NSudo](CONTRIBUTING.md)
