# Changelog

- [简体中文](更新日志.md)

**NSudo 6.0.1801.19**
- Fix the NSudoDuplicateSessionToken function definition bug. (Thanks to mingkuang.)
- Fix bugs that cannot enable full privileges under the graphical interface. (Thanks to abbodi1406.)
- Fix bugs that cannot use static compile mode when using release configuration for x86 and x86-64 (AMD64) without VC-LTL.

**NSudo 5.3.1801.11**
- Fix a potential bug when NSudo obtaining the System Token. (Thanks to mingkuang.)
- Provide VC-LTL support for NSudo release configuration for x86 and x86-64 (AMD64). (Thanks to mingkuang.)
  - PS: Compiling NSudo with VC-LTL can reduce the NSudo's binary size.
- Maintaining documents.
