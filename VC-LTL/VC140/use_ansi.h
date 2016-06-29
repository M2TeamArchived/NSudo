/***
*use_ansi.h - pragmas for ANSI Standard C++ libraries
*
*	Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This header is intended to force the use of the appropriate ANSI
*       Standard C++ libraries whenever it is included.
*
*       [Public]
*
****/

#pragma once

#ifndef _USE_ANSI_CPP
#define _USE_ANSI_CPP

#ifdef _CRTBLD
#define _CRT_NOPRAGMA_LIBS
#else
#undef _CRT_NOPRAGMA_LIBS
#endif

#ifndef _CRT_NOPRAGMA_LIBS

#if !defined(_M_CEE_PURE) && !defined(MRTDLL)

#undef _DEBUG_AFFIX
#undef _IDL_AFFIX
#undef _IDL_DEFAULT
#undef _LIB_STEM

#ifdef _DEBUG
    #define _DEBUG_AFFIX "d"
    #define _IDL_DEFAULT 2
#else
    #define _DEBUG_AFFIX ""
    #define _IDL_DEFAULT 0
#endif

#if defined(_DLL) && !defined(_STATIC_CPPLIB)
    #define _LIB_STEM "msvcprt"
#else
    #define _LIB_STEM "libcpmt"

    #if _ITERATOR_DEBUG_LEVEL != _IDL_DEFAULT
        #define _IDL_AFFIX _STRINGIZE(_ITERATOR_DEBUG_LEVEL)
    #endif
#endif

#ifdef _IDL_AFFIX
#else
    #define _IDL_AFFIX ""
#endif

#pragma comment(lib, _LIB_STEM _DEBUG_AFFIX _IDL_AFFIX)

#undef _DEBUG_AFFIX
#undef _IDL_AFFIX
#undef _IDL_DEFAULT
#undef _LIB_STEM

#endif /* !defined(_M_CEE_PURE) && !defined(MRTDLL) */

#endif  /* _CRT_NOPRAGMA_LIBS */

#endif	/* _USE_ANSI_CPP */
