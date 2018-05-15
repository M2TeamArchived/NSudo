# NSudo - A Powerful System Administration Tool

[![appveyor.badge]][appveyor.link] 
[![release.badge]][release.link]
[![latestdownloads.badge]][latestdownloads.link]
[![totaldownloads.badge]][totaldownloads.link]
[![license.badge]][license.link]
[![donate.badge]][donate.link]

- [简体中文](自述.md)

- Notice: NSudo is based on SuperCMD by Raymai97.Visit 
  [here](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "here") for more 
  information about SuperCMD.

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
Format: NSudo [ -U ] [ -P ] [ -M ] Command line or ShortCut Command

-U:[ T | S | C | P | D ] User
    T TrustedInstaller
    S System
    C Current User
    P Current Process
    D Current Process (Drop right)

-P:[ E | D ] Privilege
    E Enable All Privileges
    D Disable All Privileges
PS:
    If you want to use the default privileges, please do not include the "-P"
    parameter.

-M:[ S | H | M | L ] Integrity Level
    S System
    H High
    M Medium
    L Low
PS:
    If you want to use the default Integrity Level, please do not include the 
    "-M" parameter.

-? Show this content

Context Menu:
  -Install   Copy NSudo to the Windows directory and add the context menu.
  -Uninstall Remove NSudo in the Windows directory and the context menu. 

PS:
    1. All NSudo command arguments is case-insensitive.
    2. You can use the "/" override "-" in the command line parameters. For 
       example, "/U:T" and "-U:T" are equivalent.
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
- RapidJSON
  - Copyright: Tencent and Milo Yip
  - License: https://github.com/Tencent/rapidjson/blob/master/license.txt
- (Optional) VC-LTL
  - Copyright: Chuyu Team
  - License: https://github.com/Chuyu-Team/VC-LTL/blob/master/LICENSE.txt

## Changelogs
See [Changelog.md](Changelog.md) for more details.

## Relevant People 
See [People.md](People.md) for more details.

## Git Repositories
- GitHub Repository
  - The main repository, contains source code of NSudo >= 4.0
  - https://github.com/M2Team/NSudo
- GitHub Repository 
  - The history repository, contains source code of NSudo < 4.0
  - https://github.com/MouriNaruto/NSudo-Legacy-Repository
- OSChina Repository 
  - The mirror repository, contains source code of NSudo >= 4.0
  - https://git.oschina.net/Mouri_Naruto/NSudo

## The way to compile NSudo Source Code
- If you need to compile NSudo, you need to install Visual Studio 2017 first.
- You need to change the Windows SDK version in the project properties if the 
  version of Windows 10 SDK I used isn't installed on your PC. You also need 
  install ARM and ARM64 components when you installing the Windows 10 Version 
  1703 SDK or later.
- (Optional) If you want to reduce the release mode binaries size for x86, x64
  and ARM64 port of NSudo, you can use VC-LTL.
  - VC-LTL GitHub Repository: https://github.com/Chuyu-Team/VC-LTL
  - How to use VC-LTL to optimize NSudo binaries size:
    * Clone VC-LTL repo.
    * Double-click install.cmd in the VC-LTL repo.
    * Compile NSudo by Visual Studio 2017.
- I hope these infomation can help you.

## Communication
- MDL Post: https://forums.mydigitallife.net/threads/59268/
- QQ Group: 466078631
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
[donate.badge]: https://img.shields.io/badge/PayPal-Donate-blue.svg
[donate.link]: https://www.paypal.me/MouriNaruto
