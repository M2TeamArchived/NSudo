//
// eh.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// User-includable header for exception handling.
//
#pragma once
#define _INC_EH

#include <corecrt_terminate.h>

#ifndef RC_INVOKED

_CRT_BEGIN_C_HEADER

// unexpected_handler is the standard name; unexpected_function is defined for
// source compatibility.
typedef void (__CRTDECL* unexpected_handler )();
typedef void (__CRTDECL* unexpected_function)();

#ifdef _M_CEE
    typedef void (__clrcall* __unexpected_function_m)();
    typedef void (__clrcall* __unexpected_handler_m)();
#endif

struct _EXCEPTION_POINTERS;

#ifdef __cplusplus
    
    _VCRTIMP __declspec(noreturn) void __cdecl unexpected() throw(...);

    #ifndef _M_CEE_PURE

        _VCRTIMP unexpected_handler __cdecl set_unexpected(
            _In_opt_ unexpected_handler _NewUnexpectedHandler
            ) throw();

        _VCRTIMP unexpected_handler __cdecl _get_unexpected();

        typedef void (__cdecl* _se_translator_function)(unsigned int, struct _EXCEPTION_POINTERS*);

        _VCRTIMP _se_translator_function __cdecl _set_se_translator(
            _In_opt_ _se_translator_function _NewSETranslator
            );

    #endif

    class type_info;

    _VCRTIMP int __cdecl _is_exception_typeof(
        _In_ type_info const&     _Type,
        _In_ _EXCEPTION_POINTERS* _ExceptionPtr
        );

    _VCRTIMP bool __cdecl __uncaught_exception();
    _VCRTIMP int  __cdecl __uncaught_exceptions();

#endif

_CRT_END_C_HEADER

#endif // RC_INVOKED
