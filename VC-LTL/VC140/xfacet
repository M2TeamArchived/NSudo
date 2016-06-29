// xfacet internal header
#pragma once
#ifndef _XFACET_
#define _XFACET_
#ifndef RC_INVOKED
#include <yvals.h>

 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
 #pragma push_macro("new")
 #undef new

// This must be as small as possible, because its contents are
// injected into the msvcprt.lib and msvcprtd.lib import libraries.
// Do not include or define anything else here.
// In particular, basic_string must not be included here.

_STD_BEGIN
	// CLASS _Facet_base
class _CRTIMP2_PURE _Facet_base
	{	// code for reference counting a facet
public:
	virtual __CLR_OR_THIS_CALL ~_Facet_base() _NOEXCEPT
		{	// ensure that derived classes can be destroyed properly
		}

	// increment use count
	virtual void __CLR_OR_THIS_CALL _Incref() = 0;

	// decrement use count
	virtual _Facet_base * __CLR_OR_THIS_CALL _Decref() = 0;
	};

 #if defined(_M_CEE)
void __CLRCALL_OR_CDECL _Facet_Register_m(_Facet_base *);

 #else /* defined(_M_CEE) */
void __CLRCALL_OR_CDECL _Facet_Register(_Facet_base *);
 #endif /* defined(_M_CEE) */
_STD_END
 #pragma pop_macro("new")
 #pragma warning(pop)
 #pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _XFACET_ */

 /*
 * Copyright (c) by P.J. Plauger. All rights reserved.
  * Consult your license regarding permissions and restrictions.
V6.50:0009 */
