#pragma once

#if NDEBUG&&_DLL
#include <vcruntime_new.h>
#include <corecrt_terminate.h>

#ifdef __NOTHROW_T_DEFINED
namespace std
{
	const nothrow_t nothrow;
}
#endif

extern "C" void __fastcall _guard_check_icall(void*)
{
}

extern "C" void __std_terminate(void)
{
	terminate();
}
#endif