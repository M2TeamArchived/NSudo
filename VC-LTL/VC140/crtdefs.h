//
// crtdefs.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Declarations used across the Visual C++ Libraries.  The lack of #pragma once
// is deliberate.
//
#include <vcruntime.h>
#include <corecrt.h>



//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// CRT DLL Export/Import Macros
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#ifndef _CRTIMP_PURE
    #if defined _M_CEE_PURE || defined _STATIC_CPPLIB
        #define _CRTIMP_PURE
    #elif defined MRTDLL && defined _CRTBLD
        #define _CRTIMP_PURE
    #else
        #define _CRTIMP_PURE _CRTIMP
    #endif
#endif

#ifndef _CRTIMP2
    #if defined CRTDLL2 && defined _CRTBLD
        #define _CRTIMP2 __declspec(dllexport)
    #else
        #if defined _DLL && !defined _STATIC_CPPLIB
            #define _CRTIMP2 __declspec(dllimport)
        #else
            #define _CRTIMP2
        #endif
    #endif
#endif

#ifndef _CONCRTIMP
    #if defined CONCRTDLL && defined _CRTBLD
        #define _CONCRTIMP __declspec(dllexport)
    #else
        #if defined _DLL && !defined _STATIC_CPPLIB
            #define _CONCRTIMP __declspec(dllimport)
        #else
            #define _CONCRTIMP
        #endif
    #endif
#endif

#ifndef _MRTIMP2
    #if defined CRTDLL2 && defined _CRTBLD
        #define _MRTIMP2 __declspec(dllexport)
    #elif defined MRTDLL && defined _CRTBLD
        #define _MRTIMP2 _MRTIMP
    #else
        #if defined _DLL && !defined _STATIC_CPPLIB
            #define _MRTIMP2 __declspec(dllimport)
        #else
            #define _MRTIMP2
        #endif
    #endif
#endif
