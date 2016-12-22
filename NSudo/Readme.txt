NSudo - 一个强大的系统管理工具

注意：NSudo基于raymai97的超级命令提示符，关于raymai97的超级命令提示符，请参阅 这里

Notice: NSudo is based on SuperCMD by Raymai97.Visit here for more information about SuperCMD

使用方法 Usage

双击  NSudo.bat  自动打开相应架构的 NSudo ，根据提示操作即可

命令行选项 Command Line Options

使用 NSudo.exe -? 可以显示和这里一样的内容
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


例子：以TrustedInstaller权限，启用所有特权，完整性默认运行命令提示符 NSudo -U:T -P:E cmd  关于常用列表的自定义,可以使用记事本等工具编辑ShortCutList.ini；格式如下
[标题]
 CommandLine=命令行

PS：NSudo已经支持调用当前程序目录下的可执行文件啦！ 

举个例子：我要建立一个标题为"记事本",命令行为"c:\windows\system32\notepad.exe"的项目，可以这样做
[记事本]
CommandLine=c:\windows\system32\notepad.exe

或
[记事本]
CommandLine=%SYSTEMROOT%\notepad.exe

甚至
[记事本]
CommandLine=notepad

如果要使用引号嵌套的话；请加转义符，例如： NSudo -u:t "cmd /c ren \"E:\班级视频 《ONE》\d.txt\" x.exe" 


开源许可协议 Open Source License

本工具使用MIT协议，任何人都可以修改我（们）的工具（希望起一个好听的名字，因为那已经不是我（们）的工具）。协议内容参见
https://github.com/M2Team/NSudo/blob/master/License.md


更新日志 Changelogs

参见 https://github.com/M2Team/NSudo/blob/master/Changelog.md


捐赠 Donate

如果您想捐赠此项目，请使用 支付宝 Alipay 向我们的帐号  wxh32lkk@live.cn  进行付款。你们的捐赠是我（们）开发的动力（之一，还有我们的爱好~）。


交流 Communication

如果碰到什么问题，可以在NSudo官方群（QQ群： 466078631 ）探讨


感谢名单（排名不分先后） Thankslist

SuperCMD作者(NSudo原型): raymai97
VC-LTL作者及团队(NSudo 4.0开始所用C运行时):mingkuang(初雨团队)
Process Hacker作者(NSudo 4.0使用的Native API头文件定义的源头):Wen Jia Liu
捐赠: boyangpangzi,cjy__05,mhxkx,NotePad,tangmigoId,wondersnefu,xy137425740,月光光
繁体中文翻译: Eugene Wang J.y
日语翻译: Microsoft_Mars
Readme和Changelog: Bill
开发工作: 20011010wo，4071E95D-A09B-4AA3-8008，Microsoft_Mars
命名者: Microsoft_Mars 和 Mouri_Naruto
精神支持 O(∩_∩)O~: こうさか ほのか (a Japanese anime “Love Live” character)
M2-Team 成员: 20011010wo, Bill, hortz, Eugene Wang J.y, Microsoft_Mars, Mouri_Naruto


第三方库 3rd-party library

1.VC-LTL
项目首页：https://github.com/Chuyu-Team/VC-LTL
介绍和授权：
VC LTL 是一个开源的第三方修改VC库，大家都可以免费，无条件，甚至是用于商业环境。
本库基于VC140修改，所以也同样适用Common Public License协议。
但我也希望如果你可以在程序的说明文件中声明下，使用了此库，来使更多人受益。
——mingkuang

2.Process Hacker的PHNT库
项目首页：http://processhacker.sourceforge.net/
介绍和授权：
PHNT这是一个非常全的Native API定义库；我通过邮件获取了作者许可

附作者的回复（也许我是第一个询问许可的人）：
Nevertheless some say that headers cannot be copyrighted and have copied phnt
  verbatim anyway without asking me. So do what you will...

PS：我对该库进行了大幅度修改
（去除了内核模式定义和整合了头文件，而且对里面的宏进行了标准化处理）

为了对Process Hacker的作者Wen Jia Liu表示感谢，我会把我的整理成果单独发在github
不会有任何协议限制；如果你想感激的话，就请感谢Process Hacker作者的大度吧
 
附整理成果（单独的NativeAPI定义）
https://github.com/Chuyu-Team/NativeLib

附整理成果（NSudoSDK）
https://github.com/M2Team/NSudo/blob/master/NSudoSDK/M2.Native.hpp
https://github.com/M2Team/NSudo/blob/master/NSudoSDK/M2.WinSta.hpp


MDL论坛根据地 MDL Post

http://forums.mydigitallife.info/threads/59268-M2-Team-NSudo-(New-Version-4-0)

更新日志 Changelog

https://github.com/M2Team/NSudo/blob/master/Changelog.md


Have a good time -- M2-Team参上