/* xthrcommon.h -- common header for C/C++ threads libraries */
#pragma once
#ifndef _THR_XTHRCOMMON_H
#define _THR_XTHRCOMMON_H
#ifndef RC_INVOKED
#include <yvals.h>

 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
 #pragma push_macro("new")
 #undef new

 #if defined(_THREAD_CHECK) || defined(_DEBUG)
  #define _THREAD_CHECKX	1

 #else /* defined(_THREAD_CHECK) || defined(_DEBUG) */
  #define _THREAD_CHECKX	0
 #endif /* defined(_THREAD_CHECK) || defined(_DEBUG) */

 #pragma warning(disable: 4511 4512)

_EXTERN_C

  #pragma warning(disable:4115 4100 4097 4245)

 #if defined(__EDG__) \
	|| defined(_X86_EMUL) && defined(_WIN32_WCE) && 420 == _WIN32_WCE \
	|| defined(_X86_) && defined(_WIN32_WCE) && 300 <= _WIN32_WCE
  #define _STDCALL
 #else /* defined(_X86_EMUL) etc. */
  #define _STDCALL	__stdcall
 #endif /* defined(_X86_EMUL) etc. */

typedef unsigned int _Thrd_id_t;
typedef struct
	{	/* thread identifier for Win32 */
	void *_Hnd;	/* Win32 HANDLE */
	_Thrd_id_t _Id;
	} _Thrd_imp_t;

#define _Thr_val(thr) thr._Id
#define _Thr_set_null(thr) (thr._Hnd = 0, thr._Id = 0)
#define _Thr_is_null(thr) (thr._Id == 0)

typedef unsigned int (_STDCALL *_Thrd_callback_t)(void *);

 /* Size and alignment for _Mtx_internal_imp_t and _Cnd_internal_imp_t */
 #ifdef _CRT_WINDOWS
  #ifdef _WIN64
  #define _Mtx_internal_imp_size		32
  #define _Mtx_internal_imp_alignment	8
  #define _Cnd_internal_imp_size		16
  #define _Cnd_internal_imp_alignment	8
  #else /* _WIN64 */
  #define _Mtx_internal_imp_size		20
  #define _Mtx_internal_imp_alignment	4
  #define _Cnd_internal_imp_size		8
  #define _Cnd_internal_imp_alignment	4
  #endif /* _WIN64 */
 #else /* _CRT_WINDOWS */
 #ifdef _WIN64
  #define _Mtx_internal_imp_size		80
  #define _Mtx_internal_imp_alignment	8
  #define _Cnd_internal_imp_size		72
  #define _Cnd_internal_imp_alignment	8
 #else /* _WIN64 */
  #define _Mtx_internal_imp_size		48
  #define _Mtx_internal_imp_alignment	4
  #define _Cnd_internal_imp_size		40
  #define _Cnd_internal_imp_alignment	4
 #endif /* _WIN64 */
 #endif /* _CRT_WINDOWS */

typedef struct _Mtx_internal_imp_t *_Mtx_imp_t;

typedef struct _Cnd_internal_imp_t *_Cnd_imp_t;
typedef int _Tss_imp_t;

	/* internal */
_CRTIMP2_PURE void __cdecl _Thrd_abort(const char *);
_CRTIMP2_PURE int __cdecl _Thrd_start(_Thrd_imp_t *, _Thrd_callback_t, void *);
void _Tss_destroy(void);

 #if _THREAD_CHECKX
  #define _THREAD_QUOTX(x)	#x
  #define _THREAD_QUOT(x)	_THREAD_QUOTX(x)
	/* CAUTION -- some compilers require this all one one line: */
  #define _THREAD_ASSERT(expr, msg)	((expr) \
	? (void)0 : _Thrd_abort(__FILE__ "(" _THREAD_QUOT(__LINE__) "): " msg))

 #else /* _THREAD_CHECKX */
  #define _THREAD_ASSERT(expr, msg)	((void)0)
 #endif	/* _THREAD_CHECKX */

_END_EXTERN_C

/*	platform-specific properties */
  #define _THREAD_EMULATE_TSS	1
  #define _THR_ADDR
  #define _THR_INDIR
  #define _THR_NOINDIR(x)	*(x)

  #define _TSS_USE_MACROS	0
  #define _TSS_DTOR_ITERATIONS_IMP	4

 #pragma pop_macro("new")
 #pragma warning(pop)
 #pragma pack(pop)
#endif /* RC_INVOKED */
#endif	/* _THR_XTHRCOMMON_H */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * (c) Copyright William E. Kempf 2001
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright
 * notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting
 * documentation. William E. Kempf makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0009 */
