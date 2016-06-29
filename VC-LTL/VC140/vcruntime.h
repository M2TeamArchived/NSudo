//
// vcruntime.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Declarations used throughout the VCRuntime library.
//
// Note on use of "deprecate":
//
// Various places in this header and other headers use
// __declspec(deprecate) or macros that have the term DEPRECATE in them.
// We use "deprecate" here ONLY to signal the compiler to emit a warning
// about these items. The use of "deprecate" should NOT be taken to imply
// that any standard committee has deprecated these functions from the
// relevant standards.  In fact, these functions are NOT deprecated from
// the standard.
//
// Full details can be found in our documentation by searching for
// "Security Enhancements in the CRT".
//
#ifndef _UCRT
    #define _UCRT
#endif

// The _CRTIMP macro is not used in the VCRuntime or the CoreCRT anymore, but
// there is a lot of existing code that declares CRT functions using this macro,
// and if we remove its definition, we break that existing code.  It is thus
// defined here only for compatibility.
#ifndef _CRTIMP
    #define _VCRT_DEFINED_CRTIMP
    #if defined CRTDLL && defined _CRTBLD
        #define _CRTIMP __declspec(dllexport)
    #else
        #ifdef _DLL
            #define _CRTIMP __declspec(dllimport)
        #else
            #define _CRTIMP
        #endif
    #endif
#endif

#ifndef _VCRUNTIME_H
#define _VCRUNTIME_H

#include <sal.h>
#include <vadefs.h>

// All C headers have a common prologue and epilogue, to enclose the header in
// an extern "C" declaration when the header is #included in a C++ translation
// unit and to push/pop the packing.
#if defined __cplusplus

    #define _CRT_BEGIN_C_HEADER            \
        __pragma(pack(push, _CRT_PACKING)) \
        extern "C" {

    #define _CRT_END_C_HEADER \
        }                     \
        __pragma(pack(pop))

#elif defined __midl

    #define _CRT_BEGIN_C_HEADER                         \
        cpp_quote("__pragma(pack(push, _CRT_PACKING))") \
        cpp_quote("extern \"C\" {")

    #define _CRT_END_C_HEADER            \
        cpp_quote("}")                   \
        cpp_quote("__pragma(pack(pop))")

#else

    #define _CRT_BEGIN_C_HEADER            \
        __pragma(pack(push, _CRT_PACKING))

    #define _CRT_END_C_HEADER \
        __pragma(pack(pop))

#endif

_CRT_BEGIN_C_HEADER



#ifndef _HAS_EXCEPTIONS
    #define _HAS_EXCEPTIONS 1 // Predefine as 0 to disable exceptions
#endif



#define _CRT_STRINGIZE_(x) #x
#define _CRT_STRINGIZE(x) _CRT_STRINGIZE_(x)

#define _CRT_WIDE_(s) L ## s
#define _CRT_WIDE(s) _CRT_WIDE_(s)

#define _CRT_CONCATENATE_(a, b) a ## b
#define _CRT_CONCATENATE(a, b)  _CRT_CONCATENATE_(a, b)

#define _CRT_UNPARENTHESIZE_(...) __VA_ARGS__
#define _CRT_UNPARENTHESIZE(...)  _CRT_UNPARENTHESIZE_ __VA_ARGS__



#ifndef _VCRTIMP
    #if defined _CRTIMP && !defined _VCRT_DEFINED_CRTIMP
        #define _VCRTIMP _CRTIMP
    #elif defined _VCRT_BUILD && defined CRTDLL
        #define _VCRTIMP __declspec(dllexport)
    #elif defined _CORECRT_BUILD
        #define _VCRTIMP
    #elif defined _DLL
        #define _VCRTIMP __declspec(dllimport)
    #else
        #define _VCRTIMP
    #endif
#endif

#ifndef _MRTIMP
    #if defined MRTDLL && defined _CRTBLD
        #if !defined _M_CEE_PURE
            #define _MRTIMP __declspec(dllexport)
        #else
            #define _MRTIMP
        #endif
    #else
        #define _MRTIMP __declspec(dllimport)
    #endif
#endif



#ifdef _M_CEE_PURE
    #define _VCRTIMP_PURE
#elif (defined _VCRT_BUILD || defined _CRTBLD) && defined MRTDLL
    #define _VCRTIMP_PURE
#else
    #define _VCRTIMP_PURE _VCRTIMP
#endif

// Definitions of calling conventions used code sometimes compiled as managed
#if defined _M_CEE_PURE || defined MRTDLL
    #define __CLRCALL_OR_CDECL __clrcall
    #define __CLR_OR_THIS_CALL __clrcall
#else
    #define __CLRCALL_OR_CDECL __cdecl
    #define __CLR_OR_THIS_CALL
#endif

#ifdef _M_CEE_PURE
    #define __CLRCALL_PURE_OR_CDECL __clrcall
#else
    #define __CLRCALL_PURE_OR_CDECL __cdecl
#endif

#define __CRTDECL __CLRCALL_PURE_OR_CDECL

// Definitions of common __declspecs
#define _VCRT_NOALIAS __declspec(noalias)
#define _VCRT_RESTRICT __declspec(restrict)

#if _MSC_VER >= 1900 && !defined __EDG__ && !defined _VCRT_BUILD
    #define _VCRT_ALLOCATOR __declspec(allocator)
#else
    #define _VCRT_ALLOCATOR
#endif

#if defined _M_CEE && defined _M_X64
    #define _VCRT_JIT_INTRINSIC __declspec(jitintrinsic)
#else
    #define _VCRT_JIT_INTRINSIC
#endif

#ifdef __midl
    #define _VCRT_ALIGN(x)
#else
    #define _VCRT_ALIGN(x) __declspec(align(x))
#endif

#ifndef _CONST_RETURN
    #ifdef __cplusplus
        #define _CRT_CONST_CORRECT_OVERLOADS
        #define _CONST_RETURN  const
    #else
      #define _CONST_RETURN
    #endif
#endif

// For backwards compatibility
#define _WConst_return _CONST_RETURN

// Definitions of common types
#ifdef _WIN64
    typedef unsigned __int64 size_t;
    typedef __int64          ptrdiff_t;
    typedef __int64          intptr_t;
#else
    typedef unsigned int     size_t;
    typedef int              ptrdiff_t;
    typedef int              intptr_t;
#endif

// Indicate that these common types are defined
#ifndef _SIZE_T_DEFINED
    #define _SIZE_T_DEFINED
#endif

#ifndef _PTRDIFF_T_DEFINED
    #define _PTRDIFF_T_DEFINED
#endif

#ifndef _INTPTR_T_DEFINED
    #define _INTPTR_T_DEFINED
#endif

// Provide a typedef for wchar_t for use under /Zc:wchar_t-
#ifndef _WCHAR_T_DEFINED
    #define _WCHAR_T_DEFINED
    typedef unsigned short wchar_t;
#endif

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

#if defined _M_X64 || defined _M_ARM || defined _M_ARM64
    #define _UNALIGNED __unaligned
#else
    #define _UNALIGNED
#endif

#ifdef __cplusplus
    extern "C++"
    {
        template <typename _CountofType, size_t _SizeOfArray>
        char (*__countof_helper(_UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
            
        #define __crt_countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)
    }
#else
    #define __crt_countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

// See note on use of "deprecate" at the top of this file
#define _CRT_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))

#if defined _CRT_SECURE_NO_DEPRECATE && !defined _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_INSECURE_DEPRECATE
    #ifdef _CRT_SECURE_NO_WARNINGS
        #define _CRT_INSECURE_DEPRECATE(_Replacement)
    #else
        #define _CRT_INSECURE_DEPRECATE(_Replacement) _CRT_DEPRECATE_TEXT(    \
            "This function or variable may be unsafe. Consider using "        \
            #_Replacement                                                     \
            " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " \
            "See online help for details.")
    #endif
#endif

#if defined _CRT_SECURE_DEPRECATE_MEMORY && !defined _CRT_SECURE_WARNINGS_MEMORY
    #define _CRT_SECURE_WARNINGS_MEMORY
#endif

#ifndef _CRT_INSECURE_DEPRECATE_MEMORY
    #ifndef _CRT_SECURE_WARNINGS_MEMORY
        #define _CRT_INSECURE_DEPRECATE_MEMORY(_Replacement)
    #else
        #define _CRT_INSECURE_DEPRECATE_MEMORY(_Replacement) \
            _CRT_INSECURE_DEPRECATE(_Replacement)
    #endif
#endif



#define _CRT_WARNING(description)                   \
    message("" __FILE__ "(" _CRT_STRINGIZE(__LINE__) ") : warning CRT0000 : " _CRT_STRINGIZE(description))



#if !defined _M_CEE && !defined __midl
    void __cdecl __security_init_cookie(void);

    #ifdef _M_IX86
        void __fastcall __security_check_cookie(_In_ uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure(void);
    #else  /* _M_IX86 */
        void __cdecl __security_check_cookie(_In_ uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure(_In_ uintptr_t _StackCookie);
    #endif
#endif
        
extern uintptr_t __security_cookie;
 
#ifndef _VCRT_BUILD
    #define __vcrt_malloc_normal(_Size) malloc(_Size)
    #define __vcrt_calloc_normal(_Count, _Size) calloc(_Count, _Size)
    #define __vcrt_free_normal(_Memory) free(_Memory)
#endif

_CRT_END_C_HEADER

#endif // _VCRUNTIME_H
