## NSudo协议

NSudo使用MIT协议发行

```
The MIT License (MIT)

Copyright (c) 2016 M2-Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```

除此之外，我（们）只要求别冒用我（们）的身份发布衍生品即可

如果想在Readme感激我（们）的话；我（们）会非常高兴的


但也有例外（引用的第三方成果）

首先NSudo使用了VC-LTL库，协议如下

VC LTL 是一个开源的第三方修改VC库，大家都可以免费，无条件，甚至是用于商业环境。
本库基于VC140修改，所以也同样适用Common Public License协议。
但我也希望如果你可以在程序的说明文件中声明下，使用了此库，来使更多人受益。
——mingkuang

其次NSudoSDK使用了Process Hacker的PHNT库；

于是我通过邮件联系了作者（如果这信有语法错误，请包涵）

PS：该邮件的中文只是我为了方便你们理解而加上去的
```
Dear wj32

I find the phnt lib when I was searching for information about Native API a few days ago.
几天前我在查找Native API有关资料时发现了PHNT库

I modify it and want to add it into my open source project which is distributed under The MIT License.
我修改了它并想添加到使用了MIT协议的开源项目中

But the Process Hacker is distributed under the GNU GPL version 3. So I want to ask you for the permission.
但是Process Hacker使用GNU GPL version 3发行，所以我想请求你的许可

I will add your permission text into the readme of my project
我将会在项目的Readme加入你的许可内容

I am looking forward to hearing from you.
期待你的来信

Yours,Mouri
```

作者回复 + 个人的理解（我也问了我的三个朋友，他们也觉得可以这样理解）
```
I'm not clear on the copyright status of API headers, 
but sorry I will not relicense such a big part of the project under MIT.
我不清楚API头文件的版权状态，但我不会以MIT协议重新发布PHNT项目

Nevertheless some say that headers cannot be copyrighted and have copied
 phnt verbatim anyway without asking me. So do what you will...
不过一些人说头文件不能被版权保护且他们并未通知我就直接搬来使用；
所以，你做你想做的吧……
```

鉴于此（So do what you will...）

由于对作者的感激；也出于想方便众人的考量

我（们）在以下使用到PHNT库成果的头文件不做任何的开源协议限制

```
NSudo代码根/NSudoSDK/M2.Native.hpp
NSudo代码根/M2.WinSta.hpp
```

随便你们用，当然如果可以的话，

希望你们可以安利（宣传）下Process Hacker项目

这是一个非常不错的进程查看器

里面拥有除了微软外最齐全的ring3模式的Native API定义（即PHNT库）

如果你们只要纯粹的Native API定义的话，请参考这里 

https://github.com/Chuyu-Team/NativeLib

这个库我也会随时更新



## NSudo License

The NSudo project is distributed under The MIT License.

```
The MIT License (MIT)

Copyright (c) 2016 M2-Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
In additons, 

I/We don't prohibit that you release the 3rd-NSudo by using my/our name. 

I/We hope you can rename it, because it's not my/our tools.

I/We would be very happy if you want to thank me/us in Readme.


Exceptions (The 3rd-Party License)

First of all, NSudo uses the VC-LTL. Here are the VC-LTL license.
```
VC LTL 是一个开源的第三方修改VC库，大家都可以免费，无条件，甚至是用于商业环境。
本库基于VC140修改，所以也同样适用Common Public License协议。
但我也希望如果你可以在程序的说明文件中声明下，使用了此库，来使更多人受益。
——mingkuang
```

Then, NSudo uses the PHNT lib in Process Hacker.

I/We contact the author via e-mail. 

(If there is a syntax error in this letter, please ignore them) 
```
Dear wj32

I find the phnt lib when I was searching for information about Native API a few
 days ago. I modify it and want to add it into my open source project which is
  distributed under The MIT License. But the Process Hacker is distributed
  under the GNU GPL version 3. So I want to ask you for the permission.
I will add your permission text into the readme of my project
I am looking forward to hearing from you.

Yours,Mouri
```

The author answered
```
I'm not clear on the copyright status of API headers, 
but sorry I will not relicense such a big part of the project under MIT.
Nevertheless some say that headers cannot be copyrighted and have copied 
phnt verbatim anyway without asking me. So do what you will...
```

For that reason（So do what you will...）,

I/We want to thank for the author and want to give others convenience.

I/We don't distributed the following headers under any license.

```
NSudo Source Root/NSudoSDK/M2.Native.hpp
NSudo Source Root/M2.WinSta.hpp
```

So do what you will...

I/We hope you can introduce the Process Hacker to others if you can.

Process Hacker is a good process list viewer.

It have the best 3rd-party Native API definations (the PHNT lib)

If you only want to get the Native API definations, you can go to

https://github.com/Chuyu-Team/NativeLib

I will update the NativeLib project it if in need.