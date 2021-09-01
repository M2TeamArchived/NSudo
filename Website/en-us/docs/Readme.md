# Usage

## Quick Start

Please go to the [CPU Architecture] folder and click NSudo.exe. Follow the
prompts. For example, if you want to use 64-bit NSudo on your Intel or AMD
device, you need to go to the x64 folder and click NSudoG.exe

## Command Line

``` batch
Format: NSudoL [ Options and parameters ] Command line or ShortCut Command

Options:

-U:[ Option ] Create a process with specified user option.
Available options:
    T TrustedInstaller
    S System
    C Current User
    E Current User (Elevated)
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

-Priority:[ Option ] Create a process with specified process priority option.
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

-Wait Make NSudo Launcher wait for the created process to end before exiting.
PS: If you don't want to wait, please do not include the "-Wait" parameter.

-CurrentDirectory:[ DirectoryPath ] Set the current directory for the process.
PS: If you want to use the NSudo Launcher's current directory, please do not 
include the "-CurrentDirectory" parameter.

-UseCurrentConsole Create a process with the current console window.
PS: If you want to create a process with the new console window, please do not 
include the "-UseCurrentConsole" parameter.

-Version Show version information of NSudo Launcher.

-? Show this content.
-H Show this content.
-Help Show this content.

Please use https://github.com/Thdub/NSudo_Installer for context menu management.

PS:
    1. All NSudo Launcher command arguments is case-insensitive.
    2. You can use the "/" or "--" override "-" and use the "=" override ":" in
       the command line parameters.  For example, "/U:T" and "-U=T" are 
       equivalent.
    3. To ensure the best experience, NSudoLC does not support context menu.

Example:
    If you want to run Command Prompt with TrustedInstaller, enable all 
    privileges and the default Integrity Level.
        NSudoL -U:T -P:E cmd
```

Example: If you want to run Command Prompt with TrustedInstaller, enable all
privileges and the default Integrity Level:

``` batch
NSudo -U:T -P:E cmd
```

Starting from NSudo 5.0.1708.16, the command line nested quotes is supported.
For example:

``` batch
NSudo -U:T cmd /c "dir "C:\Program Files" & pause"
```

## Shortcut List

You can edit NSudo.json to custom the Shortcut list, here are the demo
(NSudo.json in the NSudo.exe's folder):

```json
{
  "ShortCutList_V2": {

    "Command Prompt": "cmd",
    "PowerShell": "powershell",
    "PowerShell ISE": "powershell_ise",
    "Edit Hosts": "notepad %windir%\\System32\\Drivers\\etc\\hosts"
  }
}
```
