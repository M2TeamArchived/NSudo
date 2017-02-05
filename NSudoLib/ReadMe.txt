NSudoLib - NSudo库

从NSudo 5.0开始，NSudo的核心实现部分移入NSudoLib
这样，（至少对我而言）有以下好处

1.开发NCleaner的时候，不用为了同步NSudo实现代码发愁。由于这样代码只有一份，当
  NSudo更新后，NCleaner只要把NSudo更新后的静态库和头文件拷贝过去即可。
2.方便人们（包括我）在其他用C/C++编写的应用上使用NSudo库

更新日志

NSudoLib 0.1 (2017-01-29)
初始版本，立项