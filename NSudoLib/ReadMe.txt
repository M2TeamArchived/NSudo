NSudoLib - NSudo库

从NSudo 5.0开始，NSudo的核心实现部分移入NSudoLib
这样，（至少对我而言）有以下好处

1.开发NCleaner的时候，不用为了同步NSudo实现代码发愁。由于这样代码只有一份，当
  NSudo更新后，NCleaner只要把NSudo更新后的静态库和头文件拷贝过去即可。
2.方便人们（包括我）在其他用C/C++编写的应用上使用NSudo库

更新日志
NSudoLib 0.3 (2017-02-07)
转移以下API实现到NSudoLib
	M2::SuImpersonateAsSystem

NSudoLib 0.2 (2017-02-06)
转移以下API实现到NSudoLib
	M2::SuCreateLUAToken
	M2::SuDuplicateToken
	M2::SuImpersonate
	M2::SuIsLogonSid
	M2::SuOpenProcess
	M2::SuQueryCurrentProcessToken
	M2::SuQueryProcessToken
	M2::SuQuerySessionToken
	M2::SuQuerySystemProcessInformation
	M2::SuRevertImpersonate
	M2::SuSetKernelObjectIntegrityLevel
	M2::SuSetTokenAllPrivileges
	M2::SuSetTokenIntegrityLevel
	M2::SuSetTokenPrivilege
	M2::SuStartService

NSudoLib 0.1 (2017-01-29)
初始版本，立项