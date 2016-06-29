/* xkeycheck.h internal header */
#pragma once
#ifndef _XKEYCHECK_H
#define _XKEYCHECK_H
#ifndef RC_INVOKED

#ifndef _ALLOW_KEYWORD_MACROS

 #if !defined(__cplusplus)

  #if defined(auto)	/* check C keywords */  \
	|| defined(break) \
	|| defined(case) \
	|| defined(char) \
	|| defined(const) \
	|| defined(continue) \
	|| defined(default) \
	|| defined(do) \
	|| defined(double) \
	|| defined(else) \
	|| defined(enum) \
	|| defined(extern) \
	|| defined(float) \
	|| defined(for) \
	|| defined(goto) \
	|| defined(if) \
	|| defined(inline) \
	|| defined(int) \
	|| defined(long) \
	|| defined(register) \
	|| defined(restrict) \
	|| defined(return) \
	|| defined(short) \
	|| defined(signed) \
	|| defined(sizeof) \
	|| defined(static) \
	|| defined(struct) \
	|| defined(switch) \
	|| defined(typedef) \
	|| defined(union) \
	|| defined(unsigned) \
	|| defined(void) \
	|| defined(volatile) \
	|| defined(while) \
	|| defined(_Bool) \
	|| defined(_Complex) \
	|| defined(_Imaginary)

   #define auto EMIT WARNING C4005
   #define break EMIT WARNING C4005
   #define case EMIT WARNING C4005
   #define char EMIT WARNING C4005
   #define const EMIT WARNING C4005
   #define continue EMIT WARNING C4005
   #define default EMIT WARNING C4005
   #define do EMIT WARNING C4005
   #define double EMIT WARNING C4005
   #define else EMIT WARNING C4005
   #define enum EMIT WARNING C4005
   #define extern EMIT WARNING C4005
   #define float EMIT WARNING C4005
   #define for EMIT WARNING C4005
   #define goto EMIT WARNING C4005
   #define if EMIT WARNING C4005
   #define inline EMIT WARNING C4005
   #define int EMIT WARNING C4005
   #define long EMIT WARNING C4005
   #define register EMIT WARNING C4005
   #define restrict EMIT WARNING C4005
   #define return EMIT WARNING C4005
   #define short EMIT WARNING C4005
   #define signed EMIT WARNING C4005
   #define sizeof EMIT WARNING C4005
   #define static EMIT WARNING C4005
   #define struct EMIT WARNING C4005
   #define switch EMIT WARNING C4005
   #define typedef EMIT WARNING C4005
   #define union EMIT WARNING C4005
   #define unsigned EMIT WARNING C4005
   #define void EMIT WARNING C4005
   #define volatile EMIT WARNING C4005
   #define while EMIT WARNING C4005
   #define _Bool EMIT WARNING C4005
   #define _Complex EMIT WARNING C4005
   #define _Imaginary EMIT WARNING C4005

   #error The C Standard Library forbids macroizing keywords. Enable warning C4005 to find the forbidden macro.
  #endif /* defined... */

 #else /* __cplusplus is defined */

  #if defined(alignas)	/* check C++ keywords */ \
	|| defined(alignof) \
	|| defined(asm) \
	|| defined(auto) \
	|| defined(bool) \
	|| defined(break) \
	|| defined(case) \
	|| defined(catch) \
	|| defined(char) \
	|| defined(char16_t) \
	|| defined(char32_t) \
	|| defined(class) \
	|| defined(const) \
	|| defined(const_cast) \
	|| defined(constexpr) \
	|| defined(continue) \
	|| defined(decltype) \
	|| defined(default) \
	|| defined(delete) \
	|| defined(do) \
	|| defined(double) \
	|| defined(dynamic_cast) \
	|| defined(else) \
	|| defined(enum) \
	|| defined(explicit) \
	|| defined(export) \
	|| defined(extern) \
	|| defined(false) \
	|| defined(float) \
	|| defined(for) \
	|| defined(friend) \
	|| defined(goto) \
	|| defined(if) \
	|| defined(inline) \
	|| defined(int) \
	|| defined(long) \
	|| defined(mutable) \
	|| defined(namespace) \
	|| defined(new) && defined(_ENFORCE_BAN_OF_MACRO_NEW) \
	|| defined(noexcept) \
	|| defined(nullptr) \
	|| defined(operator) \
	|| defined(private) \
	|| defined(protected) \
	|| defined(public) \
	|| defined(register) \
	|| defined(reinterpret_cast) \
	|| defined(return) \
	|| defined(short) \
	|| defined(signed) \
	|| defined(sizeof) \
	|| defined(static) \
	|| defined(static_assert) \
	|| defined(static_cast) \
	|| defined(struct) \
	|| defined(switch) \
	|| defined(template) \
	|| defined(this) \
	|| defined(thread_local) \
	|| defined(throw) \
	|| defined(true) \
	|| defined(try) \
	|| defined(typedef) \
	|| defined(typeid) \
	|| defined(typename) \
	|| defined(union) \
	|| defined(unsigned) \
	|| defined(using) \
	|| defined(virtual) \
	|| defined(void) \
	|| defined(volatile) \
	|| defined(wchar_t) \
	|| defined(while) \
	|| defined(final)		/* check "identifiers with special meaning" */ \
	|| defined(override)	/* (also known as context-sensitive keywords) */ \
	|| defined(carries_dependency)	/* check attribute-tokens */ \
	|| defined(noreturn)

   #define alignas EMIT WARNING C4005
   #define alignof EMIT WARNING C4005
   #define asm EMIT WARNING C4005
   #define auto EMIT WARNING C4005
   #define bool EMIT WARNING C4005
   #define break EMIT WARNING C4005
   #define case EMIT WARNING C4005
   #define catch EMIT WARNING C4005
   #define char EMIT WARNING C4005
   #define char16_t EMIT WARNING C4005
   #define char32_t EMIT WARNING C4005
   #define class EMIT WARNING C4005
   #define const EMIT WARNING C4005
   #define const_cast EMIT WARNING C4005
   #define constexpr EMIT WARNING C4005
   #define continue EMIT WARNING C4005
   #define decltype EMIT WARNING C4005
   #define default EMIT WARNING C4005
   #define delete EMIT WARNING C4005
   #define do EMIT WARNING C4005
   #define double EMIT WARNING C4005
   #define dynamic_cast EMIT WARNING C4005
   #define else EMIT WARNING C4005
   #define enum EMIT WARNING C4005
   #define explicit EMIT WARNING C4005
   #define export EMIT WARNING C4005
   #define extern EMIT WARNING C4005
   #define false EMIT WARNING C4005
   #define float EMIT WARNING C4005
   #define for EMIT WARNING C4005
   #define friend EMIT WARNING C4005
   #define goto EMIT WARNING C4005
   #define if EMIT WARNING C4005
   #define inline EMIT WARNING C4005
   #define int EMIT WARNING C4005
   #define long EMIT WARNING C4005
   #define mutable EMIT WARNING C4005
   #define namespace EMIT WARNING C4005
   #ifdef _ENFORCE_BAN_OF_MACRO_NEW
    #define new EMIT WARNING C4005
   #endif /* _ENFORCE_BAN_OF_MACRO_NEW */
   #define noexcept EMIT WARNING C4005
   #define nullptr EMIT WARNING C4005
   #define operator EMIT WARNING C4005
   #define private EMIT WARNING C4005
   #define protected EMIT WARNING C4005
   #define public EMIT WARNING C4005
   #define register EMIT WARNING C4005
   #define reinterpret_cast EMIT WARNING C4005
   #define return EMIT WARNING C4005
   #define short EMIT WARNING C4005
   #define signed EMIT WARNING C4005
   #define sizeof EMIT WARNING C4005
   #define static EMIT WARNING C4005
   #define static_assert EMIT WARNING C4005
   #define static_cast EMIT WARNING C4005
   #define struct EMIT WARNING C4005
   #define switch EMIT WARNING C4005
   #define template EMIT WARNING C4005
   #define this EMIT WARNING C4005
   #define thread_local EMIT WARNING C4005
   #define throw EMIT WARNING C4005
   #define true EMIT WARNING C4005
   #define try EMIT WARNING C4005
   #define typedef EMIT WARNING C4005
   #define typeid EMIT WARNING C4005
   #define typename EMIT WARNING C4005
   #define union EMIT WARNING C4005
   #define unsigned EMIT WARNING C4005
   #define using EMIT WARNING C4005
   #define virtual EMIT WARNING C4005
   #define void EMIT WARNING C4005
   #define volatile EMIT WARNING C4005
   #define wchar_t EMIT WARNING C4005
   #define while EMIT WARNING C4005
   #define final EMIT WARNING C4005
   #define override EMIT WARNING C4005
   #define carries_dependency EMIT WARNING C4005
   #define noreturn EMIT WARNING C4005

   #error The C++ Standard Library forbids macroizing keywords. Enable warning C4005 to find the forbidden macro.
  #endif /* defined... */
 #endif /* defined(__cplusplus) */

#endif /* _ALLOW_KEYWORD_MACROS */

#endif /* RC_INVOKED */
#endif /* _XKEYCHECK_H */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0009 */
