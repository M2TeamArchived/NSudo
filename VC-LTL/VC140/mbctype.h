//
// mbctype.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Functions and macros for MBCS character classification and conversion.
//
#pragma once
#define _INC_MBCTYPE

#include <corecrt.h>
#include <ctype.h>

_CRT_BEGIN_C_HEADER



// This declaration allows the user access the _mbctype[] look-up array.
_Check_return_ _ACRTIMP unsigned char* __cdecl __p__mbctype(void);
_Check_return_ _ACRTIMP unsigned char* __cdecl __p__mbcasemap(void);

#ifdef _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY
    #ifndef _CORECRT_BUILD
        extern unsigned char _mbctype[];
        extern unsigned char _mbcasemap[];
    #endif
#else
    #define _mbctype   (__p__mbctype())
    #define _mbcasemap (__p__mbcasemap())
#endif



// Bit masks for MBCS character types:
#define _MS     0x01 // MBCS single-byte symbol
#define _MP     0x02 // MBCS punctuation
#define _M1     0x04 // MBCS 1st (lead) byte
#define _M2     0x08 // MBCS 2nd byte

#define _SBUP   0x10 // SBCS upper char
#define _SBLOW  0x20 // SBCS lower char

// Byte types
#define _MBC_SINGLE    0  // Valid single byte char
#define _MBC_LEAD      1  // Lead byte
#define _MBC_TRAIL     2  // Trailing byte
#define _MBC_ILLEGAL (-1) // Illegal byte

#define _KANJI_CP   932

// _setmbcp parameter defines:
#define _MB_CP_SBCS    0
#define _MB_CP_OEM    -2
#define _MB_CP_ANSI   -3
#define _MB_CP_LOCALE -4

// Multibyte control routines:
_ACRTIMP int __cdecl _setmbcp(_In_ int _CodePage);
_ACRTIMP int __cdecl _getmbcp(void);



//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Multibyte Character Classification and Conversion Functions
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
_Check_return_ _DCRTIMP int __cdecl _ismbbkalnum(_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbkana  (_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbkpunct(_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbkprint(_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbalpha (_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbpunct (_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbblank (_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbalnum (_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbprint (_In_ unsigned int _C);
_Check_return_ _DCRTIMP int __cdecl _ismbbgraph (_In_ unsigned int _C);

_Check_return_ _DCRTIMP int __cdecl _ismbbkalnum_l(_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbkana_l  (_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbkpunct_l(_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbkprint_l(_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbalpha_l (_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbpunct_l (_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbblank_l (_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbalnum_l (_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbprint_l (_In_ unsigned int _C, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbgraph_l (_In_ unsigned int _C, _In_opt_ _locale_t _Locale);

// BEGIN _MBLEADTRAIL_DEFINED
_When_(_Ch == 0, _Post_equal_to_(0))
_Check_return_ _DCRTIMP int __cdecl _ismbblead (_In_ unsigned int _Ch);
_Check_return_ _DCRTIMP int __cdecl _ismbbtrail(_In_ unsigned int _Ch);

_When_(_Ch == 0, _Post_equal_to_(0))
_Check_return_ _DCRTIMP int __cdecl _ismbblead_l (_In_ unsigned int _Ch, _In_opt_ _locale_t _Locale);
_Check_return_ _DCRTIMP int __cdecl _ismbbtrail_l(_In_ unsigned int _Ch, _In_opt_ _locale_t _Locale);

_Check_return_
_DCRTIMP int __cdecl _ismbslead(
    _In_reads_z_(_Pos - _String + 1) unsigned char const* _String,
    _In_z_                           unsigned char const* _Pos
    );

_Check_return_
_DCRTIMP int __cdecl _ismbslead_l(
    _In_reads_z_(_Pos - _String + 1) unsigned char const* _String,
    _In_z_                           unsigned char const* _Pos,
    _In_opt_                         _locale_t            _Locale
    );

_Check_return_
_ACRTIMP int __cdecl _ismbstrail(
    _In_reads_z_(_Pos - _String + 1) unsigned char const* _String,
    _In_z_                           unsigned char const* _Pos
    );

_Check_return_
_ACRTIMP int __cdecl _ismbstrail_l(
    _In_reads_z_(_Pos - _String + 1) unsigned char const* _String,
    _In_z_                           unsigned char const* _Pos,
    _In_opt_                         _locale_t            _Locale
    );
// END _MBLEADTRAIL_DEFINED



//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Unsynchronized Macro Forms of Some Classification Functions
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#if defined _CRT_DISABLE_PERFCRIT_LOCKS && !defined _DLL
    #define _ismbbkalnum(_c) ((_mbctype+1)[(unsigned char)(_c)] & (_MS      ))
    #define _ismbbkprint(_c) ((_mbctype+1)[(unsigned char)(_c)] & (_MS | _MP))
    #define _ismbbkpunct(_c) ((_mbctype+1)[(unsigned char)(_c)] & (_MP      ))

    #define _ismbbalnum(_c)  (((_pctype)[(unsigned char)(_c)] & (_ALPHA | _DIGIT                  )) || _ismbbkalnum(_c))
    #define _ismbbalpha(_c)  (((_pctype)[(unsigned char)(_c)] & (_ALPHA                           )) || _ismbbkalnum(_c))
    #define _ismbbgraph(_c)  (((_pctype)[(unsigned char)(_c)] & (_PUNCT | _ALPHA | _DIGIT         )) || _ismbbkprint(_c))
    #define _ismbbprint(_c)  (((_pctype)[(unsigned char)(_c)] & (_BLANK | _PUNCT | _ALPHA | _DIGIT)) || _ismbbkprint(_c))
    #define _ismbbpunct(_c)  (((_pctype)[(unsigned char)(_c)] & (_PUNCT                           )) || _ismbbkpunct(_c))
    #define _ismbbblank(_c)  (((_c) == '\t') ? _BLANK : (_pctype)[(unsigned char)(_c)] & _BLANK)

    #define _ismbblead(_c)   ((_mbctype+1)[(unsigned char)(_c)] & _M1)
    #define _ismbbtrail(_c)  ((_mbctype+1)[(unsigned char)(_c)] & _M2)

    #define _ismbbkana(_c)   ((_mbctype+1)[(unsigned char)(_c)] & (_MS | _MP))
#endif

_CRT_END_C_HEADER
