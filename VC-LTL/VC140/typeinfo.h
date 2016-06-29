/***
*typeinfo.h - Defines the type_info structure and exceptions used for RTTI
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines the type_info structure and exceptions used for
*       Runtime Type Identification.
*
*       [Public]
*
****/

#pragma once

#include <typeinfo>

#if defined(__RTTI_OLDNAMES) && (!defined(_CRTBLD) || !defined(_TICORE))

    // Synonyms for legacy code
    using std::bad_cast;
    using std::bad_typeid;

    typedef type_info Type_info;
    typedef bad_cast Bad_cast;
    typedef bad_typeid Bad_typeid;

#endif  /* __RTTI_OLDNAMES */
