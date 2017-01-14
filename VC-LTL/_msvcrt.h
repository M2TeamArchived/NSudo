#pragma once

#if NDEBUG&&_DLL

#pragma comment(linker, "/nodefaultlib:msvcrt.lib")
#pragma comment(linker, "/nodefaultlib:msvcprt.lib")

//#pragma comment(lib,"ntdllp.lib")
#pragma comment(lib,"msvcrt_vista.lib")
#pragma comment(lib,"msvcrt_140.lib")

#define _NO_CRT_STDIO_INLINE
//extern "C" void __fastcall _guard_check_icall(void*);

#endif