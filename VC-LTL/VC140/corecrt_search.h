//
// corecrt_search.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Declarations of functions for sorting and searching.  These declarations are
// split out so that they may be included by both <stdlib.h> and <search.h>.
// <stdlib.h> does not include <search.h> to avoid introducing conflicts with
// other user headers named <search.h>.
//
#pragma once

#include <corecrt.h>
#include <stddef.h>

_CRT_BEGIN_C_HEADER



#if __STDC_WANT_SECURE_LIB__

    _Check_return_
    _ACRTIMP void* __cdecl bsearch_s(
        _In_                                               void const* _Key,
        _In_reads_bytes_(_NumOfElements * _SizeOfElements) void const* _Base,
        _In_                                               rsize_t     _NumOfElements,
        _In_                                               rsize_t     _SizeOfElements,
        _In_ int (__cdecl* _PtFuncCompare)(void*, void const*, void const*),
        _In_opt_                                           void*       _Context
        );

    _ACRTIMP void __cdecl qsort_s(
        _Inout_updates_bytes_(_NumOfElements * _SizeOfElements) void*   _Base,
        _In_                                                    rsize_t _NumOfElements,
        _In_                                                    rsize_t _SizeOfElements,
        _In_ int (__cdecl* _PtFuncCompare)(void*, void const*, void const*),
        _In_opt_                                                void*   _Context
        );

#endif // __STDC_WANT_SECURE_LIB__



_Check_return_
_ACRTIMP void* __cdecl bsearch(
    _In_                                               void const* _Key,
    _In_reads_bytes_(_NumOfElements * _SizeOfElements) void const* _Base,
    _In_                                               size_t      _NumOfElements,
    _In_                                               size_t      _SizeOfElements,
    _In_ int (__cdecl* _PtFuncCompare)(void const*, void const*)
    );

_ACRTIMP void __cdecl qsort(
    _Inout_updates_bytes_(_NumOfElements * _SizeOfElements) void*  _Base,
    _In_                                                    size_t _NumOfElements,
    _In_                                                    size_t _SizeOfElements,
    _In_ int (__cdecl* _PtFuncCompare)(void const*, void const*)
    );

_Check_return_
_ACRTIMP void* __cdecl _lfind_s(
    _In_                                                  void const*   _Key,
    _In_reads_bytes_((*_NumOfElements) * _SizeOfElements) void const*   _Base,
    _Inout_                                               unsigned int* _NumOfElements,
    _In_                                                  size_t        _SizeOfElements,
    _In_ int (__cdecl* _PtFuncCompare)(void*, void const*, void const*), 
    _In_                                                  void*         _Context
    );

_Check_return_
_ACRTIMP void* __cdecl _lfind(
    _In_                                                  void const*   _Key,
    _In_reads_bytes_((*_NumOfElements) * _SizeOfElements) void const*   _Base,
    _Inout_                                               unsigned int* _NumOfElements,
    _In_                                                  unsigned int  _SizeOfElements,
    _In_ int (__cdecl* _PtFuncCompare)(void const*, void const*)
    );

_Check_return_
_ACRTIMP void* __cdecl _lsearch_s(
    _In_                                                        void const*   _Key,
    _Inout_updates_bytes_((*_NumOfElements ) * _SizeOfElements) void*         _Base,
    _Inout_                                                     unsigned int* _NumOfElements,
    _In_                                                        size_t        _SizeOfElements,
    _In_ int (__cdecl* _PtFuncCompare)(void*, void const*, void const*),
    _In_                                                        void*         _Context
    );

_Check_return_
_ACRTIMP void* __cdecl _lsearch(
    _In_                                                        void const*   _Key,
    _Inout_updates_bytes_((*_NumOfElements ) * _SizeOfElements) void*         _Base,
    _Inout_                                                     unsigned int* _NumOfElements,
    _In_                                                        unsigned int  _SizeOfElements,
    _In_ int (__cdecl* _PtFuncCompare)(void const*, void const*)
    );



// Managed search routines
#if defined __cplusplus && defined _M_CEE
extern "C++"
{
    #if __STDC_WANT_SECURE_LIB__

        _Check_return_
        void* __clrcall bsearch_s(
                _In_                                               void const* _Key,
                _In_reads_bytes_(_NumOfElements * _SizeOfElements) void const* _Base,
                _In_                                               rsize_t     _NumOfElements,
                _In_                                               rsize_t     _SizeOfElements,
                _In_ int (__clrcall* _PtFuncCompare)(void*, void const*, void const*),
                _In_                                               void*       _Context);

        void __clrcall qsort_s(
                _Inout_updates_bytes_(_NumOfElements * _SizeOfElements) void*   _Base,
                _In_                                                    rsize_t _NumOfElements,
                _In_                                                    rsize_t _SizeOfElements,
                _In_ int (__clrcall* _PtFuncCompare)(void*, void const*, void const*),
                _In_                                                    void*   _Context);

    #endif // __STDC_WANT_SECURE_LIB__

    _Check_return_
    void* __clrcall bsearch(
        _In_                                               void const* _Key,
        _In_reads_bytes_(_NumOfElements * _SizeOfElements) void const* _Base,
        _In_                                               size_t _NumOfElements,
        _In_                                               size_t _SizeOfElements,
        _In_ int (__clrcall* _PtFuncCompare)(void const*, void const*)
        );

    _Check_return_
    void* __clrcall _lfind_s(
        _In_                                               void const*   _Key,
        _In_reads_bytes_(_NumOfElements * _SizeOfElements) void const*   _Base,
        _Inout_                                            unsigned int* _NumOfElements,
        _In_                                               size_t        _SizeOfElements,
        _In_ int (__clrcall* _PtFuncCompare)(void*, void const*, void const*),
        _In_                                               void*         _Context
        );

    _Check_return_
    void* __clrcall _lfind(
        _In_                                                  void const*   _Key,
        _In_reads_bytes_((*_NumOfElements) * _SizeOfElements) void const*   _Base,
        _Inout_                                               unsigned int* _NumOfElements,
        _In_                                                  unsigned int  _SizeOfElements,
        _In_ int (__clrcall* _PtFuncCompare)(void const*, void const*)
        );

    _Check_return_
    void* __clrcall _lsearch_s(
        _In_                                                  void const*   _Key,
        _In_reads_bytes_((*_NumOfElements) * _SizeOfElements) void*         _Base,
        _In_                                                  unsigned int* _NumOfElements,
        _In_                                                  size_t        _SizeOfElements,
        _In_ int (__clrcall* _PtFuncCompare)(void*, void const*, void const*),
        _In_                                                  void*         _Context
        );

    _Check_return_
    void* __clrcall _lsearch(
        _In_                                                       void const*   _Key,
        _Inout_updates_bytes_((*_NumOfElements) * _SizeOfElements) void*         _Base,
        _Inout_                                                    unsigned int* _NumOfElements,
        _In_                                                       unsigned int  _SizeOfElements,
        _In_ int (__clrcall* _PtFuncCompare)(void const*, void const*)
        );

    void __clrcall qsort(
        _Inout_updates_bytes_(_NumOfElements * _SizeOfElements) void*  _Base,
        _In_                                                    size_t _NumOfElements,
        _In_                                                    size_t _SizeOfElements,
        _In_ int (__clrcall* _PtFuncCompare)(void const*, void const*)
        );
}
#endif // defined __cplusplus && defined _M_CEE



#if !__STDC__

    _Check_return_ _CRT_NONSTDC_DEPRECATE(_lfind)
    _ACRTIMP void* __cdecl lfind(
        _In_                                                  void const*   _Key,
        _In_reads_bytes_((*_NumOfElements) * _SizeOfElements) void const*   _Base,
        _Inout_                                               unsigned int* _NumOfElements,
        _In_                                                  unsigned int  _SizeOfElements,
        _In_ int (__cdecl* _PtFuncCompare)(void const*, void const*)
        );

    _Check_return_ _CRT_NONSTDC_DEPRECATE(_lsearch)
    _ACRTIMP void* __cdecl lsearch(
        _In_                                                       void const*   _Key,
        _Inout_updates_bytes_((*_NumOfElements) * _SizeOfElements) void*         _Base,
        _Inout_                                                    unsigned int* _NumOfElements,
        _In_                                                       unsigned int  _SizeOfElements,
        _In_ int (__cdecl* _PtFuncCompare)(void const*, void const*)
        );

#endif // !__STDC__



_CRT_END_C_HEADER
