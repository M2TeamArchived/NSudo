# Changelog

- [简体中文](更新日志.md)

**NSudo 6.1.1810.28**
- Remove donation link in the documents.
- Improve several implementations.
- Update to Windows 10, version 1809 SDK.
- Using ATL to implement the main window. 
- Fix the context menu bug. (Thanks to Thomas Dubreuil.)
- Fix several bugs in the command line parser.
- Add "Priority" option in the command line usage. (Suggested by testtest322.)
- Add "CurrentDirectory" option in the command line usage. (Suggested by testtest322.)

**NSudo 6.1.1808.16**
- Merge NSudoC and NSudoG projects to NSudo project.
- Update copyright of license.
- Add VC-LTL 4.0 or later support for NSudo release configuration for ARM and 
  ARM64 and drop the earlier version of VC-LTL support. (Huge thanks to 
  mingkuang.)
- Refactoring the command line parser.
- Add "Wait" option in the command line usage. (Suggested by testtest322, wzzw
  and Domagoj Smolčić)
- Add "Help" and "Version" option in the command line usage.

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
