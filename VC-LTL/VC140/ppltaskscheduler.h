/***
* ==++==
*
* Copyright (c) Microsoft Corporation. All rights reserved.
*
* ==--==
* =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
*
* taskscheduler.h
*
* Parallel Patterns Library - Internal threadpool
*
* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#pragma once

#include <crtdefs.h>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)

namespace Concurrency { namespace details {
    typedef void(__cdecl *_Threadpool_callback)(void*);

    struct _Threadpool_chore
    {
        void *_M_work; // Windows::System::Threading::WorkItemHandler^ or PTP_M_work
        _Threadpool_callback _M_callback;
        void *_M_data;

        _Threadpool_chore(_Threadpool_callback _Callback, void *_Data) : _M_work(nullptr), _M_callback(_Callback), _M_data(_Data) {}
        _Threadpool_chore() : _M_work(nullptr), _M_callback(nullptr), _M_data(nullptr) {}
    };

    _CRTIMP2 int __cdecl _Schedule_chore(_Threadpool_chore*);
    _CRTIMP2 void __cdecl _Release_chore(_Threadpool_chore*);
    _CRTIMP2 int __cdecl _Reschedule_chore(const _Threadpool_chore*);


    class _Threadpool_task
    {
        _Threadpool_chore _M_chore;

        static void __cdecl _Callback(void *_TpTask)
        {
            static_cast<_Threadpool_task*>(_TpTask)->_Invoke();
        }

    public:

        _Threadpool_task(): _M_chore{&_Callback, this} {}

        virtual void _Invoke() throw() = 0;

        virtual ~_Threadpool_task()
        {
            _Release_chore(&_M_chore);
        }

        void _Schedule()
        {
            _Schedule_chore(&_M_chore);
        }

        void _Reschedule() const
        {
            _Reschedule_chore(&_M_chore);
        }

        bool _Is_scheduled() const throw()
        {
            return _M_chore._M_work != nullptr;
        }
    };
} }

#pragma warning(pop)
#pragma pack(pop)
