![Logo](Logo.png)
# NSudo - A Powerful System Administration Tool

[![appveyor.badge]][appveyor.link] 
[![release.badge]][release.link]
[![latestdownloads.badge]][latestdownloads.link]
[![totaldownloads.badge]][totaldownloads.link]
[![license.badge]][license.link]

- [简体中文](自述.md)

![Screenshot](Screenshot.png)

- Notice: NSudo is based on SuperCMD by Raymai97.Visit 
  [here](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "here") for more 
  information about SuperCMD.

## Introduction
I will give you some thirdparty introduction links because I am not good at 
English.
- MajorGeeks: https://www.majorgeeks.com/files/details/nsudo.html
- softpedia.com: https://www.softpedia.com/get/Tweak/System-Tweak/NSudo.shtml
- TrishTech.com: https://www.trishtech.com/2018/11/nsudo-run-programs-with-full-privileges-in-windows/
- Wilders Security Forums: https://www.wilderssecurity.com/threads/396818

## System Requirements
- Supported OS Version: Windows NT 6.0 or later
- Supported CPU Architecture: x86, x86-64(AMD64), ARM, ARM64

## Usage
- Please go to the [CPU Architecture] folder and click NSudo.exe. Follow the 
  prompts.
  - For example, if you want to use 64-bit NSudo on your Intel or AMD device,
    you need to go to the x64 folder and click NSudo.exe

## Command Line Options
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
privileges and the default Integrity Level
> NSudo -U:T -P:E cmd

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
Starting from NSudo 5.0.1708.16, the command line nested quotes is supported. 
For example: 
> NSudo -U:T cmd /c "dir "C:\Program Files" & pause"

## 3rd-party libraries which used
- JSON for Modern C++
  - Copyright: Niels Lohmann
  - License: https://github.com/nlohmann/json/blob/develop/LICENSE.MIT
- (Optional) VC-LTL
  - Copyright: Chuyu Team
  - License: https://github.com/Chuyu-Team/VC-LTL/blob/master/LICENSE.txt

## Changelogs
See [Changelog.md](Changelog.md) for more details.

## Relevant People 
See [People.md](People.md) for more details.

## Git Repositories
- GitHub (Main)
  - https://github.com/M2Team/NSudo
- OSChina (Mirrors)
  - https://gitee.com/M2-Team/NSudo

## The way to compile NSudo
- If you need to compile NSudo, you need to install Visual Studio 2017 first.
- You need to change the Windows SDK version in the project properties if the 
  version of Windows 10 SDK I used isn't installed on your PC. You also need 
  install ARM and ARM64 components when you installing the Windows 10 Version 
  1703 SDK or later.
- (Optional) If you want to reduce the release mode binaries size for x86, x64
  and ARM64 port of NSudo, you can use VC-LTL.
  - VC-LTL GitHub Repository: https://github.com/Chuyu-Team/VC-LTL
  - How to use VC-LTL to optimize NSudo binaries size:
    - Download VC-LTL binary pack from 
	  https://github.com/Chuyu-Team/VC-LTL/releases/latest.
    - Unpack the VC-LTL binary pack and double-click install.cmd in the unpack
	  folder.
    - Compile NSudo by Visual Studio 2017.
- I hope these infomation can help you.

## Communication
- MDL Post: https://forums.mydigitallife.net/threads/59268/
- E-mail: Mouri_Naruto@Outlook.com

## Have a good time -- M2-Team

[appveyor.badge]: https://ci.appveyor.com/api/projects/status/github/M2Team/NSudo?branch=master&svg=true
[appveyor.link]: https://ci.appveyor.com/project/MouriNaruto/nsudo
[release.badge]: https://img.shields.io/github/release/M2Team/NSudo.svg
[release.link]: https://github.com/M2Team/NSudo/releases/latest
[latestdownloads.badge]: https://img.shields.io/github/downloads/M2Team/NSudo/latest/total.svg
[latestdownloads.link]: https://github.com/M2Team/NSudo/releases/latest
[totaldownloads.badge]: https://img.shields.io/github/downloads/M2Team/NSudo/total.svg
[totaldownloads.link]: https://github.com/M2Team/NSudo/releases
[license.badge]: https://img.shields.io/github/license/M2Team/NSudo.svg
[license.link]: LICENSE
