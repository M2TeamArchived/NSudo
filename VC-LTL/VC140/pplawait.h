/***
* ==++==
*
* Copyright (c) Microsoft Corporation. All rights reserved.
*
* ==--==
* =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
*
* pplawait.h
*
* Await Compiler Support for Parallel Patterns Library - PPL Tasks
*
* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#pragma once

#ifndef _PPLAWAIT_H
#define _PPLAWAIT_H

#include <experimental/resumable>
#include <ppltasks.h>
#include <allocators>
#include <type_traits>
#include <ppltaskscheduler.h>

#define __resumable

namespace std
{
    namespace experimental
    {
        template <typename _Ty, typename... _Whatever>
        struct coroutine_traits<concurrency::task<_Ty>, _Whatever...>
        {
            struct promise_type
            {
                auto get_return_object() const
                {
                    return concurrency::create_task(_M_tce);
                }

                bool initial_suspend() const { return (false); }

                bool final_suspend() const { return (false); }

                void return_value(const _Ty &_Val)
                {
                    _M_tce.set(_Val);
                }

                void set_exception(const exception_ptr &_Ptr)
                {
                    _M_tce.set_exception(_Ptr);
                }
            private:
                concurrency::task_completion_event<_Ty> _M_tce;
            };
        };

        template <typename... _Whatever>
        struct coroutine_traits<concurrency::task<void>, _Whatever...>
        {
            struct promise_type
            {
                auto get_return_object() const
                {
                    return concurrency::create_task(_M_tce);
                }

                bool initial_suspend() const { return (false); }

                bool final_suspend() const { return (false); }

                void return_void()
                {
                    _M_tce.set();
                }

                void set_exception(const exception_ptr &_Ptr)
                {
                    _M_tce.set_exception(_Ptr);
                }
            private:
                concurrency::task_completion_event<void> _M_tce;
            };
        };


        namespace details {
            namespace awaitabletraitsimpl
            {
                template <typename _Ty>
                inline bool _TryAwaitReady(_Ty & _Obj, decltype(std::declval<_Ty>().await_ready(), 0), int)
                {
                    return _Obj.await_ready();
                }
                template <typename _Ty>
                inline bool _TryAwaitReady(_Ty & _Obj, decltype(await_ready(std::declval<_Ty>()), 0), ...)
                {
                    return await_ready(_Obj);
                }

                template <typename _Ty, typename _Handle>
                inline void _TryAwaitSuspend(_Ty & _Obj, _Handle _Hnd, decltype(std::declval<_Ty>().await_suspend(std::declval<_Handle>()), 0), int)
                {
                    _Obj.await_suspend(_Hnd);
                }
                template <typename _Ty, typename _Handle>
                inline void _TryAwaitSuspend(_Ty & _Obj, _Handle _Hnd, decltype(await_suspend(std::declval<_Ty>(), std::declval<_Handle>()), 0), ...)
                {
                    await_suspend(_Obj, _Hnd);
                }

                template <typename _Ty>
                inline auto _TryAwaitResume(_Ty & _Obj, decltype(std::declval<_Ty>().await_resume(), 0), int)
                {
                    return _Obj.await_resume();
                }
                template <typename _Ty>
                inline auto _TryAwaitResume(_Ty & _Obj, decltype(await_resume(std::declval<_Ty>()), 0), ...)
                {
                    return await_resume(_Obj);
                }

                template <typename _Ty>
                inline std::true_type _TryAwaitable(_Ty,
                    decltype(_TryAwaitReady(std::declval<std::decay_t<_Ty>>(), 0, 0), _TryAwaitSuspend(std::declval<std::decay_t<_Ty>>(), std::experimental::resumable_handle<>(), 0, 0), _TryAwaitResume(std::declval<std::decay_t<_Ty>>(), 0, 0), 0));
                inline std::false_type _TryAwaitable(...);

            }
        }

        // Traits for
        //   1. detecting a type whether satisfy awaitable contract requirement
        //   2. invoking its awaitable contract methods

        template <typename _Ty>
        struct awaitable_traits : public decltype(details::awaitabletraitsimpl::_TryAwaitable(std::declval<_Ty>(), 0))
        {
            static bool invoke_await_ready(_Ty & _Obj)
            {
                return details::awaitabletraitsimpl::_TryAwaitReady(_Obj, 0, 0);
            }

            template <typename _Handle>
            static void invoke_await_suspend(_Ty &_Obj, _Handle _Hnd)
            {
                details::awaitabletraitsimpl::_TryAwaitSuspend(_Obj, _Hnd, 0, 0);
            }

            static auto invoke_await_resume(_Ty &_Obj)
            {
                return details::awaitabletraitsimpl::_TryAwaitResume(_Obj, 0, 0);
            }
        };

        template <typename _Ty>
        using is_awaitable = awaitable_traits<_Ty>;

        template <typename _Ty>
        using is_awaitable_t = typename awaitable_traits<_Ty>::type;

    }
}

namespace Concurrency
{
    // PPLTask awaitable extension

    template <class _Ty>
    bool await_ready(const task<_Ty> & _Task)
    {
        return _Task.is_done();
    }

    template <class _Ty, typename _Handle>
    void await_suspend(task<_Ty> & _Task, _Handle _ResumeCb)
    {
        _Task.then([_ResumeCb](task<_Ty>&)
        {
            _ResumeCb();
        }, task_continuation_context::get_current_winrt_context());
    }

    template <class _Ty>
    auto await_resume(const task<_Ty> & _Task)
    {
        return _Task.get();
    }


    class await_resume_context
    {
        class ThreadpoolContext
        {
            details::_Threadpool_chore _M_chore;
            static void __cdecl _ChoreCallback(void *_TpTask)
            {
                auto _Context = static_cast<ThreadpoolContext*>(_TpTask);
                _Context->_M_func();
                details::_Release_chore(&_Context->_M_chore);
            }
            std::function<void()> _M_func;
        public:
            template <typename _Handle>
            void _CallInContext(_Handle _Hnd)
            {
                _M_func = _Hnd;
                _M_chore._M_callback = &ThreadpoolContext::_ChoreCallback;
                _M_chore._M_data = this;
                details::_Schedule_chore(&_M_chore);
            }

            ThreadpoolContext()
            {
                _M_chore._M_work = nullptr;
            }

            ~ThreadpoolContext()
            {
                // Release chore multiple times is fine
                details::_Release_chore(&_M_chore);
            }
        };

        details::_ContextCallback _M_context;
        ThreadpoolContext _M_defaultContext;

    public:
        static await_resume_context current()
        {
            await_resume_context _Context;
            _Context._M_context = details::_ContextCallback::_CaptureCurrent();
            return _Context;
        }

        static await_resume_context any()
        {
             return await_resume_context{};
        }

        template <typename _Ty>
        class _CallbackChain
        {
            _Ty _M_awaitable;
            await_resume_context * _M_contextPtr;
        public:

            _CallbackChain(const _Ty &_Awaitable, await_resume_context *_ContextPtr) : _M_awaitable(_Awaitable), _M_contextPtr(_ContextPtr) { }

            bool await_ready() { return false; }

            template <typename _Handle>
            void await_suspend(_Handle _Hnd)
            {
                awaitable_traits<_Ty>::invoke_await_suspend(_M_awaitable, [=] {
                    if (_M_contextPtr->_M_context == details::_ContextCallback())
                    {
                        _M_contextPtr->_M_defaultContext._CallInContext([=] {
                            _Hnd();
                        });
                    }
                    else
                    {
                        _M_contextPtr->_M_context._CallInContext([=] {
                            _Hnd();
                        });
                    }
                });
            }

            auto await_resume()
            {
                return awaitable_traits<_Ty>::invoke_await_resume(_M_awaitable);
            }
        };

        class _Callback
        {
            await_resume_context * _M_contextPtr;
        public:

            _Callback(await_resume_context * _ContextPtr) : _M_contextPtr(_ContextPtr) { }

            bool await_ready() { return false; }

            template <typename _Handle>
            void await_suspend(_Handle _Hnd)
            {
                if (_M_contextPtr->_M_context == details::_ContextCallback())
                {
                    _M_contextPtr->_M_defaultContext._CallInContext([=] {
                        _Hnd();
                    });
                }
                else
                {
                    _M_contextPtr->_M_context._CallInContext([=] {
                        _Hnd();
                    });
                }

            }

            void await_resume() { }
        };

        template <typename _Ty>
        auto get_awaitable(_Ty _Awaitable)
        {
            return _CallbackChain<std::decay_t<_Ty>>(_Awaitable, this);
        }

        auto get_awaitable()
        {
            return _Callback(this);
        }
    };
}

#ifdef __cplusplus_winrt

// WinRT IAsync(Operation|Action) awaitable extension

namespace Windows
{
    namespace Foundation
    {
        inline bool await_ready(IAsyncInfo^ _Task)
        {
            return _Task->Status >= AsyncStatus::Completed;
        }

        template <typename _Handle>
        void await_suspend(IAsyncAction^ _Task, _Handle _ResumeCb)
        {
            _Task->Completed = ref new AsyncActionCompletedHandler(
                [_ResumeCb](IAsyncAction^, AsyncStatus) { _ResumeCb(); }, CallbackContext::Same);
        }

        template <typename _Ty, typename _Handle>
        void await_suspend(IAsyncOperation<_Ty>^ _Task, _Handle _ResumeCb)
        {
            _Task->Completed = ref new AsyncOperationCompletedHandler<_Ty>(
                [_ResumeCb](IAsyncOperation<_Ty>^, AsyncStatus) { _ResumeCb(); }, CallbackContext::Same);
        }

        template <typename _Pr, typename _Handle>
        void await_suspend(IAsyncActionWithProgress<_Pr>^ _Task, _Handle _ResumeCb)
        {
            _Task->Completed = ref new AsyncActionWithProgressCompletedHandler<_Pr>(
                [_ResumeCb](IAsyncActionWithProgress<_Pr>^, AsyncStatus) { _ResumeCb(); }, CallbackContext::Same);
        }

        template <typename _Ty, typename _Pr, typename _Handle>
        void await_suspend(IAsyncOperationWithProgress<_Ty, _Pr>^ _Task, _Handle _ResumeCb)
        {
            _Task->Completed = ref new AsyncOperationWithProgressCompletedHandler<_Ty, _Pr>(
                [_ResumeCb](IAsyncOperationWithProgress<_Ty, _Pr>^, AsyncStatus) { _ResumeCb(); }, CallbackContext::Same);
        }

        inline void await_resume(Windows::Foundation::IAsyncAction^ _Task)
        {
            _Task->GetResults();
        }

        template <typename _Ty>
        _Ty await_resume(Windows::Foundation::IAsyncOperation<_Ty>^ _Task)
        {
            return _Task->GetResults();
        }

        template <typename _Pr>
        void await_resume(Windows::Foundation::IAsyncActionWithProgress<_Pr>^ _Task)
        {
            _Task->GetResults();
        }

        template <typename _Ty, typename _Pr>
        _Ty await_resume(Windows::Foundation::IAsyncOperationWithProgress<_Ty, _Pr>^ _Task)
        {
            return _Task->GetResults();
        }
    }
}

#endif // __cplusplus_winrt
#endif // _PPLAWAIT_H
