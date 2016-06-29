/***
*appdomain.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   Utitily for cross App Domain Calls
*
*       [Public]
*
****/

#pragma once

#if !defined (_INC_MSCLR_APPDOMAIN)

#ifndef __cplusplus_cli
#error ERROR: msclr libraries require /clr and are not compatible with /clr:oldSyntax
#endif  /* __cplusplus_cli */

#ifdef _M_CEE_PURE
#error ERROR: msclr appdomain helpers can only be used in mixed mode. Use a cross-domain delegate in pure mode
#endif  /* _M_CEE_PURE */
#include <mscoree.h>
#include <crtdbg.h>

#if defined (_M_IX86)
#define _MSCLR_STDCALL_DISTINCT 1
#elif defined (_M_X64)
#define _MSCLR_STDCALL_DISTINCT 0
#elif defined (_M_ARM) || defined (_M_ARM64)
#define _MSCLR_STDCALL_DISTINCT 0
#else  /* defined (_M_ARM) */
#error Need to add setting for different CPU
#endif  /* defined (_M_ARM) */

namespace msclr
{

namespace _detail
{

/* helper functions */

inline
void validate(HRESULT hr)
{
    _ASSERT(SUCCEEDED(hr));
    if (FAILED(hr))
    {
        System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(hr);
    }
}

inline
System::Guid FromGUID(GUID const & guid)
{
   return System::Guid( guid.Data1, guid.Data2, guid.Data3,
                        guid.Data4[ 0 ], guid.Data4[ 1 ],
                        guid.Data4[ 2 ], guid.Data4[ 3 ],
                        guid.Data4[ 4 ], guid.Data4[ 5 ],
                        guid.Data4[ 6 ], guid.Data4[ 7 ] );
}

inline
ICLRRuntimeHost *get_clr_runtime_host(void)
{
    using System::Runtime::InteropServices::RuntimeEnvironment;

    // Throws HR exception on failure.
    ICLRRuntimeHost *pClrHost = NULL;
    pClrHost = reinterpret_cast<ICLRRuntimeHost*>(
        RuntimeEnvironment::GetRuntimeInterfaceAsIntPtr(
            FromGUID(CLSID_CLRRuntimeHost), FromGUID(IID_ICLRRuntimeHost)).ToPointer());

    return pClrHost;
}

/* callback struct */

/* __stdcall version */

#if _MSCLR_STDCALL_DISTINCT

template <typename RetType>
struct callback_stdcall_struct0
{
    RetType (__stdcall *func)();
    RetType retValue;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct0 *pcs = (callback_stdcall_struct0*)cookie;
        pcs->retValue = pcs->func();
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1>
struct callback_stdcall_struct1
{
    RetType (__stdcall *func)(ArgType1);
    RetType retValue;
    ArgType1 arg1;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct1 *pcs = (callback_stdcall_struct1*)cookie;
        pcs->retValue = pcs->func(pcs->arg1);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2>
struct callback_stdcall_struct2
{
    RetType (__stdcall *func)(ArgType1, ArgType2);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct2 *pcs = (callback_stdcall_struct2*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3>
struct callback_stdcall_struct3
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct3 *pcs = (callback_stdcall_struct3*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
struct callback_stdcall_struct4
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct4 *pcs = (callback_stdcall_struct4*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
struct callback_stdcall_struct5
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct5 *pcs = (callback_stdcall_struct5*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
struct callback_stdcall_struct6
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct6 *pcs = (callback_stdcall_struct6*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
struct callback_stdcall_struct7
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct7 *pcs = (callback_stdcall_struct7*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
struct callback_stdcall_struct8
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct8 *pcs = (callback_stdcall_struct8*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
struct callback_stdcall_struct9
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct9 *pcs = (callback_stdcall_struct9*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10>
struct callback_stdcall_struct10
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct10 *pcs = (callback_stdcall_struct10*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11>
struct callback_stdcall_struct11
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct11 *pcs = (callback_stdcall_struct11*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12>
struct callback_stdcall_struct12
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct12 *pcs = (callback_stdcall_struct12*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13>
struct callback_stdcall_struct13
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct13 *pcs = (callback_stdcall_struct13*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14>
struct callback_stdcall_struct14
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;
    ArgType14 arg14;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct14 *pcs = (callback_stdcall_struct14*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13, pcs->arg14);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14, typename ArgType15>
struct callback_stdcall_struct15
{
    RetType (__stdcall *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;
    ArgType14 arg14;
    ArgType15 arg15;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_struct15 *pcs = (callback_stdcall_struct15*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13, pcs->arg14, pcs->arg15);
        hr = S_OK;
        return hr;
    }
};

struct callback_stdcall_void_struct0
{
    void (__stdcall *func)();

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct0 *pcs = (callback_stdcall_void_struct0*)cookie;
        pcs->func();
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1>
struct callback_stdcall_void_struct1
{
    void (__stdcall * func)(ArgType1);
    ArgType1 arg1;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct1 *pcs = (callback_stdcall_void_struct1*)cookie;
        pcs->func(pcs->arg1);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2>
struct callback_stdcall_void_struct2
{
    void (__stdcall * func)(ArgType1, ArgType2);
    ArgType1 arg1;
    ArgType2 arg2;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct2 *pcs = (callback_stdcall_void_struct2*)cookie;
        pcs->func(pcs->arg1, pcs->arg2);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3>
struct callback_stdcall_void_struct3
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct3 *pcs = (callback_stdcall_void_struct3*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
struct callback_stdcall_void_struct4
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct4 *pcs = (callback_stdcall_void_struct4*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
struct callback_stdcall_void_struct5
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct5 *pcs = (callback_stdcall_void_struct5*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
struct callback_stdcall_void_struct6
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct6 *pcs = (callback_stdcall_void_struct6*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
struct callback_stdcall_void_struct7
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct7 *pcs = (callback_stdcall_void_struct7*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
struct callback_stdcall_void_struct8
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct8 *pcs = (callback_stdcall_void_struct8*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
struct callback_stdcall_void_struct9
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct9 *pcs = (callback_stdcall_void_struct9*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10>
struct callback_stdcall_void_struct10
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct10 *pcs = (callback_stdcall_void_struct10*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11>
struct callback_stdcall_void_struct11
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct11 *pcs = (callback_stdcall_void_struct11*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12>
struct callback_stdcall_void_struct12
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct12 *pcs = (callback_stdcall_void_struct12*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13>
struct callback_stdcall_void_struct13
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct13 *pcs = (callback_stdcall_void_struct13*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14>
struct callback_stdcall_void_struct14
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;
    ArgType14 arg14;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct14 *pcs = (callback_stdcall_void_struct14*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13, pcs->arg14);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14, typename ArgType15>
struct callback_stdcall_void_struct15
{
    void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;
    ArgType14 arg14;
    ArgType15 arg15;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_stdcall_void_struct15 *pcs = (callback_stdcall_void_struct15*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13, pcs->arg14, pcs->arg15);
        hr = S_OK;
        return hr;
    }
};

#endif  /* _MSCLR_STDCALL_DISTINCT */

/* __cdecl version */

template <typename RetType>
struct callback_cdecl_struct0
{
    RetType (__cdecl *func)();
    RetType retValue;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct0 *pcs = (callback_cdecl_struct0*)cookie;
        pcs->retValue = pcs->func();
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1>
struct callback_cdecl_struct1
{
    RetType (__cdecl *func)(ArgType1);
    RetType retValue;
    ArgType1 arg1;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct1 *pcs = (callback_cdecl_struct1*)cookie;
        pcs->retValue = pcs->func(pcs->arg1);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2>
struct callback_cdecl_struct2
{
    RetType (__cdecl *func)(ArgType1, ArgType2);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct2 *pcs = (callback_cdecl_struct2*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3>
struct callback_cdecl_struct3
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct3 *pcs = (callback_cdecl_struct3*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
struct callback_cdecl_struct4
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct4 *pcs = (callback_cdecl_struct4*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
struct callback_cdecl_struct5
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct5 *pcs = (callback_cdecl_struct5*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
struct callback_cdecl_struct6
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct6 *pcs = (callback_cdecl_struct6*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
struct callback_cdecl_struct7
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct7 *pcs = (callback_cdecl_struct7*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
struct callback_cdecl_struct8
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct8 *pcs = (callback_cdecl_struct8*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
struct callback_cdecl_struct9
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct9 *pcs = (callback_cdecl_struct9*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10>
struct callback_cdecl_struct10
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct10 *pcs = (callback_cdecl_struct10*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11>
struct callback_cdecl_struct11
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct11 *pcs = (callback_cdecl_struct11*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12>
struct callback_cdecl_struct12
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct12 *pcs = (callback_cdecl_struct12*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13>
struct callback_cdecl_struct13
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct13 *pcs = (callback_cdecl_struct13*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14>
struct callback_cdecl_struct14
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;
    ArgType14 arg14;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct14 *pcs = (callback_cdecl_struct14*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13, pcs->arg14);
        hr = S_OK;
        return hr;
    }
};

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14, typename ArgType15>
struct callback_cdecl_struct15
{
    RetType (__cdecl *func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15);
    RetType retValue;
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;
    ArgType14 arg14;
    ArgType15 arg15;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_struct15 *pcs = (callback_cdecl_struct15*)cookie;
        pcs->retValue = pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13, pcs->arg14, pcs->arg15);
        hr = S_OK;
        return hr;
    }
};

struct callback_cdecl_void_struct0
{
    void (__cdecl *func)();

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct0 *pcs = (callback_cdecl_void_struct0*)cookie;
        pcs->func();
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1>
struct callback_cdecl_void_struct1
{
    void (__cdecl * func)(ArgType1);
    ArgType1 arg1;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct1 *pcs = (callback_cdecl_void_struct1*)cookie;
        pcs->func(pcs->arg1);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2>
struct callback_cdecl_void_struct2
{
    void (__cdecl * func)(ArgType1, ArgType2);
    ArgType1 arg1;
    ArgType2 arg2;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct2 *pcs = (callback_cdecl_void_struct2*)cookie;
        pcs->func(pcs->arg1, pcs->arg2);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3>
struct callback_cdecl_void_struct3
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct3 *pcs = (callback_cdecl_void_struct3*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
struct callback_cdecl_void_struct4
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct4 *pcs = (callback_cdecl_void_struct4*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
struct callback_cdecl_void_struct5
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct5 *pcs = (callback_cdecl_void_struct5*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
struct callback_cdecl_void_struct6
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct6 *pcs = (callback_cdecl_void_struct6*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
struct callback_cdecl_void_struct7
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct7 *pcs = (callback_cdecl_void_struct7*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
struct callback_cdecl_void_struct8
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct8 *pcs = (callback_cdecl_void_struct8*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
struct callback_cdecl_void_struct9
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct9 *pcs = (callback_cdecl_void_struct9*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10>
struct callback_cdecl_void_struct10
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct10 *pcs = (callback_cdecl_void_struct10*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11>
struct callback_cdecl_void_struct11
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct11 *pcs = (callback_cdecl_void_struct11*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12>
struct callback_cdecl_void_struct12
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct12 *pcs = (callback_cdecl_void_struct12*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13>
struct callback_cdecl_void_struct13
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct13 *pcs = (callback_cdecl_void_struct13*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14>
struct callback_cdecl_void_struct14
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;
    ArgType14 arg14;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct14 *pcs = (callback_cdecl_void_struct14*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13, pcs->arg14);
        hr = S_OK;
        return hr;
    }
};

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14, typename ArgType15>
struct callback_cdecl_void_struct15
{
    void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15);
    ArgType1 arg1;
    ArgType2 arg2;
    ArgType3 arg3;
    ArgType4 arg4;
    ArgType5 arg5;
    ArgType6 arg6;
    ArgType7 arg7;
    ArgType8 arg8;
    ArgType9 arg9;
    ArgType10 arg10;
    ArgType11 arg11;
    ArgType12 arg12;
    ArgType13 arg13;
    ArgType14 arg14;
    ArgType15 arg15;

    static HRESULT __stdcall callback(void *cookie)
    {
        HRESULT hr = E_FAIL;
        if (cookie == NULL)
        {
            return hr;
        }
        callback_cdecl_void_struct15 *pcs = (callback_cdecl_void_struct15*)cookie;
        pcs->func(pcs->arg1, pcs->arg2, pcs->arg3, pcs->arg4, pcs->arg5, pcs->arg6, pcs->arg7, pcs->arg8, pcs->arg9, pcs->arg10, pcs->arg11, pcs->arg12, pcs->arg13, pcs->arg14, pcs->arg15);
        hr = S_OK;
                return hr;
        }
};

} // namespace _detail

/* __stdcall version */
#if _MSCLR_STDCALL_DISTINCT

template <typename RetType>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)())
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct0<RetType> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1), ArgType1 arg1)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct1<RetType, ArgType1> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2), ArgType1 arg1, ArgType2 arg2)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct2<RetType, ArgType1, ArgType2> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct3<RetType, ArgType1, ArgType2, ArgType3> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct4<RetType, ArgType1, ArgType2, ArgType3, ArgType4> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct5<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct6<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct7<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct8<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct9<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct10<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct11<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct12<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct13<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13, ArgType14 arg14)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct14<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;
    cs.arg14 = arg14;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14, typename ArgType15>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13, ArgType14 arg14, ArgType15 arg15)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_struct15<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;
    cs.arg14 = arg14;
    cs.arg15 = arg15;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)())
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct0 cs;

    // fill up the callback_stdcall_struct
    cs.func = func;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1), ArgType1 arg1)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct1<ArgType1> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2), ArgType1 arg1, ArgType2 arg2)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct2<ArgType1, ArgType2> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct3<ArgType1, ArgType2, ArgType3> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct4<ArgType1, ArgType2, ArgType3, ArgType4> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct5<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct6<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct7<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct8<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct9<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct10<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct11<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct12<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct13<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13, ArgType14 arg14)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct14<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;
    cs.arg14 = arg14;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14, typename ArgType15>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__stdcall * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13, ArgType14 arg14, ArgType15 arg15)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_stdcall_void_struct15<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15> cs;

    // fill up the callback_stdcall_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;
    cs.arg14 = arg14;
    cs.arg15 = arg15;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

#endif  /* _MSCLR_STDCALL_DISTINCT */

/* __cdecl version */

template <typename RetType>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)())
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct0<RetType> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1), ArgType1 arg1)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct1<RetType, ArgType1> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2), ArgType1 arg1, ArgType2 arg2)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct2<RetType, ArgType1, ArgType2> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct3<RetType, ArgType1, ArgType2, ArgType3> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct4<RetType, ArgType1, ArgType2, ArgType3, ArgType4> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct5<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct6<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct7<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct8<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct9<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct10<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct11<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct12<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct13<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13, ArgType14 arg14)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct14<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;
    cs.arg14 = arg14;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

template <typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14, typename ArgType15>
RetType inline call_in_appdomain(DWORD dwAppDomainId, RetType (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13, ArgType14 arg14, ArgType15 arg15)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_struct15<RetType, ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;
    cs.arg14 = arg14;
    cs.arg15 = arg15;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);

    return cs.retValue;
}

void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)())
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct0 cs;

    // fill up the callback_cdecl_struct
    cs.func = func;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1), ArgType1 arg1)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct1<ArgType1> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2), ArgType1 arg1, ArgType2 arg2)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct2<ArgType1, ArgType2> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct3<ArgType1, ArgType2, ArgType3> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct4<ArgType1, ArgType2, ArgType3, ArgType4> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct5<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct6<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct7<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct8<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct9<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct10<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct11<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct12<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct13<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13, ArgType14 arg14)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct14<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;
    cs.arg14 = arg14;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

template <typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9, typename ArgType10, typename ArgType11, typename ArgType12, typename ArgType13, typename ArgType14, typename ArgType15>
void inline call_in_appdomain(DWORD dwAppDomainId, void (__cdecl * func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15), ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9, ArgType10 arg10, ArgType11 arg11, ArgType12 arg12, ArgType13 arg13, ArgType14 arg14, ArgType15 arg15)
{
    ICLRRuntimeHost *pClrHost = _detail::get_clr_runtime_host();
    _detail::callback_cdecl_void_struct15<ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9, ArgType10, ArgType11, ArgType12, ArgType13, ArgType14, ArgType15> cs;

    // fill up the callback_cdecl_struct
    cs.func = func;
    cs.arg1 = arg1;
    cs.arg2 = arg2;
    cs.arg3 = arg3;
    cs.arg4 = arg4;
    cs.arg5 = arg5;
    cs.arg6 = arg6;
    cs.arg7 = arg7;
    cs.arg8 = arg8;
    cs.arg9 = arg9;
    cs.arg10 = arg10;
    cs.arg11 = arg11;
    cs.arg12 = arg12;
    cs.arg13 = arg13;
    cs.arg14 = arg14;
    cs.arg15 = arg15;

    // call the function
    HRESULT hr = pClrHost->ExecuteInAppDomain(dwAppDomainId, &cs.callback, &cs);
    pClrHost->Release();
    _detail::validate(hr);
}

} // namespace msclr

#define _INC_MSCLR_APPDOMAIN

#endif  /* !defined (_INC_MSCLR_APPDOMAIN) */
