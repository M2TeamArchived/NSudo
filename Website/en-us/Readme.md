# NSudo | System Administration Toolkit

![Screenshot](./Screenshot.png)

## Note: Become the sponsor of NSudo

Patreon: [https://www.patreon.com/MouriNaruto](https://www.patreon.com/MouriNaruto)

爱发电: [https://afdian.net/@MouriNaruto](https://afdian.net/@MouriNaruto)

- If I have reached the "$1,000 per month" goal, I will release 2 major 
  releases in a year.
- If I have reached the "$2,000 per month" goal, I will obtain an extended 
  validation (EV) code signing certificate and use it for signing the projects
  binaries.

Thanks for your support.

Kenji Mouri

## About

### Prototype

NSudo Launcher is based on SuperCMD by Raymai97. Visit
[here](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "here") for more
information about SuperCMD.

NSudo Devil Mode is based on the Dism++ God Mode, with new features and several
improvements.

### Features

- Distributed under the MIT License.
- Provide the x86, x86-64, ARM64 binaries.
- Support Windows Vista and later.
- Using VC-LTL and libkcrt from Chuyu Team for smaller binary size.
- Using C++17, but only use core language features in the most cases.
- NSudo Launcher
  - Launch programs with TrustedInstaller access token.
  - Launch programs with System access token.
  - Launch programs with current user access token.
    - Note: If the User Account Control has not been disabled, the privilege of
      this mode is similar to the standard user.
  - Launch programs with current process access token.
    - Note: The privilege of this mode is similar to the elevated user.
  - Launch programs with current process access token with the LUA restriction.
    - Note: The privilege of this mode is similar to the standard user. And the 
      implementation is similar to the iertutil.dll's from the Internet 
      Explorer.
  - Support launching programs with the specified privileges option.
    - Note: "Enable All Privileges" and "Disable All Privileges".
  - Support launching programs with the specified mandatory level (or integrity
    level) option.
    - Note: "System", "High", "Medium" and "Low".
  - Support launching programs with the specified process priority option.
    - Note: "Idle", "BelowNormal", "Normal", "AboveNormal", "High" and 
      "RealTime".
  - Support launching programs with the specified window mode option.
    - Note: "Show", "Hide", "Maximize" and "Minimize".
  - Support waiting for the created process to end before exiting.
  - Support launching programs with the specified current directory.
  - Support launching programs with the current console window.
  - Support shortcut list.
    - Note: You can custom it via editing NSudo.json.
  - Support multiple command line style.
  - Support multi-languages.
    - Note: Chinese Simplified, Chinese Traditional, English, French, German,
      Italian and Spanish.
  - Full High DPI Support.
    - Note: As good as the implementation from Windows Shell (conhost.exe), 
      with the full Per-Monitor DPI-Aware support under Windows 10 Build 10240 
      and later version and full System DPI-Aware support under Windows Vista 
      to Windows 8.1.
  - Full accessibility support.
    - Note: You can use NSudo Launcher with Windows Narrator smoothly.
  - High performance.
    - Note: Because it don't need to create the windows service and the windows
      service process.
  - Provide C APIs and .Net Core bindings for developers.
- NSudo Devil Mode
  - The most elegant solution for developers who want to bypass the file and 
    registry access checks for the process with the Administrator privilege.
  - Hook APIs via the Microsoft Detours library for the maximum compatibility.
  - The binary only depend on the exported named APIs from ntdll.dll.

### Third-party projects which uses NSudo

- MSMG ToolKit
- Sledgehammer (WUMT Wrapper Script)
- Dism++

### System requirements

- Supported OS Version: Windows NT 6.0 or later
- Supported CPU Architecture: x86, x86-64(AMD64), ARM, ARM64

### Third-party introduction

- HowToDoNinja: [https://howtodoninja.com/how-to/nsudo-run-programs-with-full-admin-privileges-windows/](https://howtodoninja.com/how-to/nsudo-run-programs-with-full-admin-privileges-windows/)
- MajorGeeks: [https://www.majorgeeks.com/files/details/nsudo.html](https://www.majorgeeks.com/files/details/nsudo.html)
- softpedia.com: [https://www.softpedia.com/get/Tweak/System-Tweak/NSudo.shtml](https://www.softpedia.com/get/Tweak/System-Tweak/NSudo.shtml)
- TrishTech.com: [https://www.trishtech.com/2018/11/nsudo-run-programs-with-full-privileges-in-windows/](https://www.trishtech.com/2018/11/nsudo-run-programs-with-full-privileges-in-windows/)
- Wilders Security Forums: [https://www.wilderssecurity.com/threads/396818](https://www.wilderssecurity.com/threads/396818)

## Usage

### Quick Start for NSudo Launcher

Please go to the [CPU Architecture] folder and click NSudoLG.exe. Follow the
prompts. For example, if you want to use 64-bit NSudo on your Intel or AMD
device, you need to go to the x64 folder and click NSudoLG.exe
