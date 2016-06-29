// cfenv standard header
#pragma once
#ifndef _CFENV_
#define _CFENV_
#include <yvals.h>

#ifdef _STD_USING
 #undef _STD_USING
  #include <fenv.h>
 #define _STD_USING

#else /* _STD_USING */
 #include <fenv.h>
#endif /* _STD_USING */

 #if _GLOBAL_USING && !defined(RC_INVOKED)
_STD_BEGIN
using _CSTD fegetround; using _CSTD fesetround;

  #if !defined(_M_CEE) || defined(_CRTBLD)
using _CSTD feclearexcept; using _CSTD fegetenv; using _CSTD fegetexceptflag;
using _CSTD feholdexcept; using _CSTD fenv_t; using _CSTD fesetenv;
using _CSTD fesetexceptflag; using _CSTD fetestexcept; using _CSTD fexcept_t;
  #endif /* !defined(_M_CEE) || defined(_CRTBLD) */

  #if !defined(_M_CEE) && !defined(_CRTBLD)
using _CSTD feraiseexcept; using _CSTD feupdateenv;
  #endif /* !defined(_M_CEE) && !defined(_CRTBLD) */
_STD_END
 #endif /* _GLOBAL_USING */

#endif /* _CFENV_ */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0009 */
