# NSudo - A Powerful System Administration Tool

[![appveyor.badge]][appveyor.link] 
[![release.badge]][release.link]
[![latestdownloads.badge]][latestdownloads.link]
[![totaldownloads.badge]][totaldownloads.link]
[![license.badge]][license.link]
[![donate.badge]][donate.link]

- [简体中文](自述.md)

- Notice: NSudo is based on SuperCMD by Raymai97.Visit [here](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "here") for more information about SuperCMD.

## Usage
Double click the NSudo.bat, it will start the NSudo according to the CPU architecture. Follow the prompts.

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
  PS: If you want to use the default privileges, please do not include the -P parameter.

  -M:[ S | H | M | L ] Integrity Level
  S System
  H High
  M Medium
  L Low
  PS: If you want to use the default Integrity Level, please do not include the -M parameter

  -? Show this content

  Example：If you want to run Command Prompt with TrustedInstaller, enable all privileges and the default Integrity Level
  NSudo -U:T -P:E cmd
```
Example：If you want to run Command Prompt with TrustedInstaller, enable all privileges and the default Integrity Level
> NSudo -U:T -P:E cmd

You can edit NSudo.json to custom the Shortcut list, here are the demo (NSudo.json in the NSudo.exe's folder):
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
Starting from NSudo 5.0.1708.16, the command line nested quotes is supported. For example: 
> NSudo -U:T cmd /c "dir "C:\Program Files" & pause"

## System Requirements
- Supported OS Version: Windows NT 6.0 or later
- Supported CPU Architecture: x86, x86-64(AMD64), ARM, ARM64

## 3rd-party libraries which used
Name                          | Developer     | License
------------------------------|---------------|-----------------
JSON for Modern C++           | Niels Lohmann | The MIT License

## Changelogs
See [Changelog.md](Changelog.md) for more details.

## Relevant People 
See [People.md](People.md) for more details.

## Git Repositories
- GitHub Repository (The main repository, contains source code of NSudo >= 4.0)
  - https://github.com/M2Team/NSudo
- GitHub Repository (The history repository, contains source code of NSudo < 4.0)
  - https://github.com/MouriNaruto/NSudo-Legacy-Repository
- OSChina Repository (The mirror repository, contains source code of NSudo >= 4.0) 
  - https://git.oschina.net/Mouri_Naruto/NSudo

## Communication
- MDL Post : https://forums.mydigitallife.net/threads/nsudo-a-powerful-system-administration-tool.59268/
- QQ Group : 466078631

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
