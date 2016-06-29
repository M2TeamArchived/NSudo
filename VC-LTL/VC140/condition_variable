// condition_variable standard header
#pragma once
#ifndef _CONDITION_VARIABLE_
#define _CONDITION_VARIABLE_
#ifndef RC_INVOKED
#include <thr/xthread>
#include <mutex>
#include <chrono>
#include <memory>

 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
 #pragma push_macro("new")
 #undef new

 #ifdef _M_CEE
  #error <condition_variable> is not supported when compiling with /clr or /clr:pure.
 #endif /* _M_CEE */

_STD_BEGIN
class condition_variable_any
	{	// class for waiting for conditions with any kind of mutex
public:
	condition_variable_any()
		{	// construct
		_Myptr = _STD make_shared<mutex>();
		_Cnd_init_in_situ(_Mycnd());
		}

	~condition_variable_any() _NOEXCEPT
		{	// destroy
		_Cnd_destroy_in_situ(_Mycnd());
		}

	condition_variable_any(const condition_variable_any&) = delete;
	condition_variable_any& operator=(const condition_variable_any&) = delete;

	void notify_one() _NOEXCEPT
		{	// wake up one waiter
		_Myptr->lock();
		_Cnd_signalX(_Mycnd());
		_Myptr->unlock();
		}

	void notify_all() _NOEXCEPT
		{	// wake up all waiters
		_Myptr->lock();
		_Cnd_broadcastX(_Mycnd());
		_Myptr->unlock();
		}

	template<class _Mutex>
		void wait(_Mutex& _Xtrnl)
		{	// wait for signal
		shared_ptr<mutex> _Ptr = _Myptr;	// immune to *this destruction
		_Ptr->lock();
		_Xtrnl.unlock();
		_Cnd_waitX(_Mycnd(), _Ptr->_Mymtx());
		_Ptr->unlock();
		_Xtrnl.lock();
		}

	template<class _Mutex,
		class _Predicate>
		void wait(_Mutex& _Xtrnl, _Predicate _Pred)
		{	// wait for signal and check predicate
		while (!_Pred())
			wait(_Xtrnl);
		}

	template<class _Lock,
		class _Rep,
		class _Period>
		_Cv_status wait_for(
			_Lock& _Lck,
			const chrono::duration<_Rep, _Period>& _Rel_time)
		{	// wait for duration
		stdext::threads::xtime _Tgt = _To_xtime(_Rel_time);
		return (wait_until(_Lck, &_Tgt));
		}

	template<class _Lock,
		class _Rep,
		class _Period,
		class _Predicate>
		bool wait_for(
			_Lock& _Lck,
			const chrono::duration<_Rep, _Period>& _Rel_time,
			_Predicate _Pred)
		{	// wait for signal with timeout and check predicate
		while (!_Pred())
			if (wait_for(_Lck, _Rel_time) == cv_status::timeout)
				return (_Pred());
		return (true);
		}

	template<class _Lock,
		class _Clock,
		class _Duration>
		_Cv_status wait_until(
			_Lock& _Lck,
			const chrono::time_point<_Clock, _Duration>& _Abs_time)
		{	// wait until time point
		typename chrono::time_point<_Clock, _Duration>::duration
			_Rel_time = _Abs_time - _Clock::now();
		return (wait_for(_Lck, _Rel_time));
		}

	template<class _Lock,
		class _Clock,
		class _Duration,
		class _Predicate>
		bool wait_until(
			_Lock& _Lck,
			const chrono::time_point<_Clock, _Duration>& _Abs_time,
			_Predicate _Pred)
		{	// wait for signal with timeout and check predicate
		while (!_Pred())
			if (wait_until(_Lck, _Abs_time) == cv_status::timeout)
				return (_Pred());
		return (true);
		}

	template<class _Mutex>
		_Cv_status wait_until(
			_Mutex& _Xtrnl,
			const xtime *_Abs_time)
		{	// wait for signal with timeout
		shared_ptr<mutex> _Ptr = _Myptr;	// immune to *this destruction
		_Ptr->lock();
		_Xtrnl.unlock();
		int _Res = _Cnd_timedwaitX(_Mycnd(),
			_Ptr->_Mymtx(), _Abs_time);
		_Ptr->unlock();
		_Xtrnl.lock();
		return (_Res == _Thrd_timedout
			? cv_status::timeout : cv_status::no_timeout);
		}

	template<class _Mutex,
		class _Predicate>
		bool wait_until(
			_Mutex& _Xtrnl,
			const xtime *_Abs_time,
			_Predicate _Pred)
		{	// wait for signal with timeout and check predicate
		while (!_Pred())
			if (wait_until(_Xtrnl, _Abs_time) == cv_status::timeout)
				return (_Pred());
		return (true);
		}

private:
	shared_ptr<mutex> _Myptr;

	aligned_storage<_Cnd_internal_imp_size,
		_Cnd_internal_imp_alignment>::type _Cnd_storage;

	_Cnd_t _Mycnd() _NOEXCEPT
		{	// get pointer to _Cnd_internal_imp_t inside _Cnd_storage
		return (reinterpret_cast<_Cnd_t>(&_Cnd_storage));
		}
	};

inline void notify_all_at_thread_exit(condition_variable& _Cnd,
	unique_lock<mutex> _Lck)
	{	// register _Cnd for release at thread exit
	_Cnd._Register(_Lck, 0);
	}
_STD_END
 #pragma pop_macro("new")
 #pragma warning(pop)
 #pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _CONDITION_VARIABLE_ */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0009 */
