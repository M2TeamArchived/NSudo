/***
*safebool.h - types and constants for implementing the "smart bool" idiom.
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   Prefer _safe_bool to an implicit conversion to bool. When a
*           type is implicitly convertible to bool, it is also implicitly
*           convertible to any integral type, and this is often not
*           desired.  Instead, provide a conversion to _safe_bool, which
*           is really a pointer to a member function on a dummy struct.
*           This pointer can be evaluated in Boolean context, but it will
*           never be converted to an integral type.
*
*       [Public]
*
****/

#pragma once

#if !defined (_INC_MSCLR_SAFEBOOL)

#ifndef __cplusplus_cli
#error ERROR: msclr libraries are not compatible with /clr:oldSyntax
#endif  /* __cplusplus_cli */

namespace msclr
{

value class _detail_class
{
public:
    value class dummy_struct
    {
    public:
        static initonly System::String^ dummy_string = "";
    };
    typedef System::String^ _safe_bool;
    static _safe_bool const _safe_true  = dummy_struct::dummy_string;
    static _safe_bool const _safe_false = nullptr;
};

}


#define _INC_MSCLR_SAFEBOOL

#endif  /* !defined (_INC_MSCLR_SAFEBOOL) */
