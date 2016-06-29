// xlocmes internal header (from <locale>)
#pragma once
#ifndef _XLOCMES_
#define _XLOCMES_
#ifndef RC_INVOKED
#include <xiosbase>

 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
 #pragma push_macro("new")
 #undef new

_STD_BEGIN
		// STRUCT messages_base
 #pragma warning(push)
 #pragma warning(disable: 4275)

struct messages_base
	: public locale::facet
	{	// base class for messages
	typedef int catalog;

	explicit messages_base(size_t _Refs = 0)
		: locale::facet(_Refs)
		{	// default constructor
		}
	};

 #pragma warning(pop)

		// TEMPLATE CLASS messages
template<class _Elem>
	class messages
		: public messages_base
	{	// facet for obtaining messages from a catalog
public:
	typedef _Elem char_type;
	typedef basic_string<_Elem, char_traits<_Elem>, allocator<_Elem> >
		string_type;

	catalog open(const string& _Catname, const locale& _Loc) const
		{	// open catalog
		return (do_open(_Catname, _Loc));
		}

	string_type get(catalog _Catval, int _Set, int _Message,
		const string_type& _Dflt) const
		{	// get message from set in catalog
		return (do_get(_Catval, _Set, _Message, _Dflt));
		}

	void close(catalog _Catval) const
		{	// close catalog
		do_close(_Catval);
		}

	__PURE_APPDOMAIN_GLOBAL _CRTIMP2_PURE static locale::id id;	// unique facet id

	explicit messages(size_t _Refs = 0)
		: messages_base(_Refs)
		{	// construct from current locale
		_BEGIN_LOCINFO(_Lobj)
			_Init(_Lobj);
		_END_LOCINFO()
		}

	messages(const _Locinfo& _Lobj, size_t _Refs = 0)
		: messages_base(_Refs)
		{	// construct from specified locale
		_Init(_Lobj);
		}

	static size_t _Getcat(const locale::facet **_Ppf = 0,
		const locale *_Ploc = 0)
		{	// return locale category mask and construct standard facet
		if (_Ppf != 0 && *_Ppf == 0)
			*_Ppf = new messages<_Elem>(
				_Locinfo(_Ploc->c_str()));
		return (_X_MESSAGES);
		}

protected:
	messages(const char *_Locname, size_t _Refs = 0)
		: messages_base(_Refs)
		{	// construct from specified locale
		_BEGIN_LOCINFO(_Lobj(_Locname))
			_Init(_Lobj);
		_END_LOCINFO()
		}

	virtual __CLR_OR_THIS_CALL ~messages() _NOEXCEPT
		{	// destroy the object
		}

	void _Init(const _Locinfo&)
		{	// initialize from _Locinfo object (do nothing)
		}

	virtual catalog __CLR_OR_THIS_CALL do_open(const string&, const locale&) const
		{	// open catalog (do nothing)
		return (-1);
		}

	virtual string_type __CLR_OR_THIS_CALL do_get(catalog, int, int,
		const string_type& _Dflt) const
		{	// get message from set in catalog (return default)
		return (_Dflt);
		}

	virtual void __CLR_OR_THIS_CALL do_close(catalog) const
		{	// close catalog (do nothing)
		}
	};

		// STATIC messages::id OBJECT
template<class _Elem>
	__PURE_APPDOMAIN_GLOBAL locale::id messages<_Elem>::id;

		// TEMPLATE CLASS messages_byname
template<class _Elem>
	class messages_byname
		: public messages<_Elem>
	{	// messages for named locale
public:
	explicit messages_byname(const char *_Locname, size_t _Refs = 0)
		: messages<_Elem>(_Locname, _Refs)
		{	// construct for named locale
		}

	explicit messages_byname(const string& _Str, size_t _Refs = 0)
		: messages<_Elem>(_Str.c_str(), _Refs)
		{	// construct for named locale
		}

protected:
	virtual __CLR_OR_THIS_CALL ~messages_byname() _NOEXCEPT
		{	// destroy the object
		}
	};

 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

  #if !defined(_CRTBLD) || defined(__FORCE_INSTANCE)
template __PURE_APPDOMAIN_GLOBAL locale::id messages<char>::id;
template __PURE_APPDOMAIN_GLOBAL locale::id messages<wchar_t>::id;
  #endif /* !defined(_CRTBLD) || defined(__FORCE_INSTANCE) */

  #ifdef __FORCE_INSTANCE
template __PURE_APPDOMAIN_GLOBAL locale::id messages<unsigned short>::id;
  #endif /* __FORCE_INSTANCE */
 #endif /* defined(_DLL_CPPLIB) etc. */
_STD_END
 #pragma pop_macro("new")
 #pragma warning(pop)
 #pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _XLOCMES_ */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0009 */
