# NSudo - 一个强大的系统管理工具

[![Build status](https://ci.appveyor.com/api/projects/status/gaxfn27d0yjmt8q7?svg=true)](https://ci.appveyor.com/project/MouriNaruto/nsudo)

> 注意：NSudo基于raymai97的超级命令提示符，关于raymai97的超级命令提示符，请参阅 [这里](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "这里")

> Notice: NSudo is based on SuperCMD by Raymai97.Visit [here](http://bbs.pcbeta.com/viewthread-1508863-1-1.html "here") for more information about SuperCMD

## 使用方法 Usage
双击 ```NSudo.bat``` 自动打开相应架构的 NSudo ，根据提示操作即可

## 命令行选项 Command Line Options
> 使用 NSudo.exe -? 可以显示和这里一样的内容

```
格式: NSudo [ -U ] [ -P ] [ -M ] 命令行或常用任务名
  -U:[ T | S | C | P | D ] 用户
        T TrustedInstaller
        S System
        C 当前用户
        P 当前进程
        D 当前进程(降权)

  -P:[ E | D ] 特权
        E 启用全部特权
        D 禁用所有特权
        PS: 如果想以默认特权方式的话，请不要包含-P参数

  -M:[ S | H | M | L ] 完整性
        S 系统
        H 高
        M 中
        L 低
        PS: 如果想以默认完整性方式的话，请不要包含-M参数

  -? 显示该内容

  例子：以TrustedInstaller权限，启用所有特权，完整性默认运行命令提示符
                NSudo -U:T -P:E cmd
```

例子：以TrustedInstaller权限，启用所有特权，完整性默认运行命令提示符```NSudo -U:T -P:E cmd```

关于常用列表的自定义,可以使用记事本等工具编辑NSudo.json。你可以照着示例的做法添加你的自定义项目：
```
{
  "ShortCutList_V2": {
    "命令提示符": "cmd",
    "PowerShell": "powershell",
    "PowerShell ISE": "powershell_ise",
    "Hosts编辑": "notepad %windir%\\System32\\Drivers\\etc\\hosts"
  }
}
```

从 NSudo 5.0.1708.16 开始命令行支持嵌套引号，例如：```NSudo -U:T cmd /c "dir "C:\Program Files" & pause"```

## 许可协议 License
NSudo使用The MIT License发行，详情参见 https://github.com/M2Team/NSudo/blob/master/LICENSE

第三方库名称        | 开发者        | 许可协议
--------------------|---------------|-----------------
JSON for Modern C++ | Niels Lohmann | The MIT License

## 更新日志 Changelogs
参见 https://github.com/M2Team/NSudo/blob/master/Changelog.md

## 捐赠 Donate
如果您想捐赠此项目，请使用 [支付宝 Alipay](https://alipay.com) 向我们的帐号  ```wxh32lkk@live.cn``` 进行付款。你们的捐赠是我（们）开发的动力（之一，还有我们的爱好~）。

## 下载 Download
[![Latest Release](https://img.shields.io/github/release/M2Team/NSudo.svg)](https://github.com/M2Team/NSudo/releases/latest)
[![Download](https://img.shields.io/github/downloads/M2Team/NSudo/total.svg)](https://github.com/M2Team/NSudo/releases/latest)

## MDL论坛根据地 MDL Post
http://forums.mydigitallife.info/threads/59268-M2-Team-NSudo-(New-Version-4-0)

## 交流 Communication
如果碰到什么问题，可以在NSudo官方群（QQ群：```466078631```）探讨

## 感谢名单 Thanks
参见 https://github.com/M2Team/NSudo/blob/master/Thanks.txt

## Have a good time -- M2-Team参上
