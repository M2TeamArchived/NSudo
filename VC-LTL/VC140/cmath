// cmath standard header
#pragma once
#ifndef _CMATH_
#define _CMATH_
#include <yvals.h>

#ifdef _STD_USING
 #undef _STD_USING
  #include <math.h>
 #define _STD_USING
#else /* _STD_USING */
 #include <math.h>
#endif /* _STD_USING */

 #if !defined(RC_INVOKED)

template<class _Ty>
	_Check_return_ inline _Ty _Pow_int(_Ty _Xx, int _Yx) _NOEXCEPT
	{
	unsigned int _Nx;
	if (_Yx >= 0)
		_Nx = static_cast<unsigned int>(_Yx);
	else
		_Nx = static_cast<unsigned int>(-_Yx);

	for (_Ty _Zx = static_cast<_Ty>(1); ; _Xx *= _Xx)
		{
		if ((_Nx & 1) != 0)
			_Zx *= _Xx;
		if ((_Nx >>= 1) == 0)
			return (_Yx < 0 ? static_cast<_Ty>(1) / _Zx : _Zx);
		}
	}

_Check_return_ inline double abs(_In_ double _Xx) _NOEXCEPT
	{
	return (_CSTD fabs(_Xx));
	}

_Check_return_ inline double pow(_In_ double _Xx, _In_ int _Yx) _NOEXCEPT
	{
	return (_Pow_int(_Xx, _Yx));
	}

_Check_return_ inline float abs(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD fabsf(_Xx));
	}

_Check_return_ inline float acos(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD acosf(_Xx));
	}

_Check_return_ inline float acosh(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD acoshf(_Xx));
	}

_Check_return_ inline float asin(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD asinf(_Xx));
	}

_Check_return_ inline float asinh(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD asinhf(_Xx));
	}

_Check_return_ inline float atan(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD atanf(_Xx));
	}

_Check_return_ inline float atanh(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD atanhf(_Xx));
	}

_Check_return_ inline float atan2(_In_ float _Yx, _In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD atan2f(_Yx, _Xx));
	}

_Check_return_ inline float cbrt(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD cbrtf(_Xx));
	}

_Check_return_ inline float ceil(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD ceilf(_Xx));
	}

_Check_return_ inline float copysign(_In_ float _Number,
	_In_ float _Sign) _NOEXCEPT
	{
	return (_CSTD copysignf(_Number, _Sign));
	}

_Check_return_ inline float cos(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD cosf(_Xx));
	}

_Check_return_ inline float cosh(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD coshf(_Xx));
	}

_Check_return_ inline float erf(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD erff(_Xx));
	}

_Check_return_ inline float erfc(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD erfcf(_Xx));
	}

_Check_return_ inline float exp(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD expf(_Xx));
	}

_Check_return_ inline float exp2(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD exp2f(_Xx));
	}

_Check_return_ inline float expm1(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD expm1f(_Xx));
	}

_Check_return_ inline float fabs(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD fabsf(_Xx));
	}

_Check_return_ inline float fdim(_In_ float _Xx, _In_ float _Yx) _NOEXCEPT
	{
	return (_CSTD fdimf(_Xx, _Yx));
	}

_Check_return_ inline float floor(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD floorf(_Xx));
	}

_Check_return_ inline float fma(_In_ float _Xx, _In_ float _Yx,
	_In_ float _Zx) _NOEXCEPT
	{
	return (_CSTD fmaf(_Xx, _Yx, _Zx));
	}

_Check_return_ inline float fmax(_In_ float _Xx, _In_ float _Yx) _NOEXCEPT
	{
	return (_CSTD fmaxf(_Xx, _Yx));
	}

_Check_return_ inline float fmin(_In_ float _Xx, _In_ float _Yx) _NOEXCEPT
	{
	return (_CSTD fminf(_Xx, _Yx));
	}

_Check_return_ inline float fmod(_In_ float _Xx, _In_ float _Yx) _NOEXCEPT
	{
	return (_CSTD fmodf(_Xx, _Yx));
	}

_Check_return_ inline float frexp(_In_ float _Xx, _Out_ int* _Yx) _NOEXCEPT
	{
	return (_CSTD frexpf(_Xx, _Yx));
	}

_Check_return_ inline float hypot(_In_ float _Xx, _In_ float _Yx) _NOEXCEPT
	{
	return (_CSTD hypotf(_Xx, _Yx));
	}

_Check_return_ inline int ilogb(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD ilogbf(_Xx));
	}

_Check_return_ inline float ldexp(_In_ float _Xx, _In_ int _Yx) _NOEXCEPT
	{
	return (_CSTD ldexpf(_Xx, _Yx));
	}

_Check_return_ inline float lgamma(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD lgammaf(_Xx));
	}

_Check_return_ inline long long llrint(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD llrintf(_Xx));
	}

_Check_return_ inline long long llround(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD llroundf(_Xx));
	}

_Check_return_ inline float log(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD logf(_Xx));
	}

_Check_return_ inline float log10(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD log10f(_Xx));
	}

_Check_return_ inline float log1p(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD log1pf(_Xx));
	}

_Check_return_ inline float log2(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD log2f(_Xx));
	}

_Check_return_ inline float logb(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD logbf(_Xx));
	}

_Check_return_ inline long lrint(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD lrintf(_Xx));
	}

_Check_return_ inline long lround(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD lroundf(_Xx));
	}

_Check_return_ inline float modf(_In_ float _Xx, _Out_ float* _Yx) _NOEXCEPT
	{
	return (_CSTD modff(_Xx, _Yx));
	}

_Check_return_ inline float nearbyint(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD nearbyintf(_Xx));
	}

_Check_return_ inline float nextafter(_In_ float _Xx, _In_ float _Yx) _NOEXCEPT
	{
	return (_CSTD nextafterf(_Xx, _Yx));
	}

_Check_return_ inline float nexttoward(_In_ float _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD nexttowardf(_Xx, _Yx));
	}

_Check_return_ inline float pow(_In_ float _Xx,
	_In_ float _Yx) _NOEXCEPT
	{
	return (_CSTD powf(_Xx, _Yx));
	}

_Check_return_ inline float pow(_In_ float _Xx, _In_ int _Yx) _NOEXCEPT
	{
	return (_Pow_int(_Xx, _Yx));
	}

_Check_return_ inline float remainder(_In_ float _Xx, _In_ float _Yx) _NOEXCEPT
	{
	return (_CSTD remainderf(_Xx, _Yx));
	}

_Check_return_ inline float remquo(_In_ float _Xx, _In_ float _Yx,
	_Out_ int *_Zx) _NOEXCEPT
	{
	return (_CSTD remquof(_Xx, _Yx, _Zx));
	}

_Check_return_ inline float rint(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD rintf(_Xx));
	}

_Check_return_ inline float round(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD roundf(_Xx));
	}

_Check_return_ inline float scalbln(_In_ float _Xx, _In_ long _Yx) _NOEXCEPT
	{
	return (_CSTD scalblnf(_Xx, _Yx));
	}

_Check_return_ inline float scalbn(_In_ float _Xx, _In_ int _Yx) _NOEXCEPT
	{
	return (_CSTD scalbnf(_Xx, _Yx));
	}

_Check_return_ inline float sin(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD sinf(_Xx));
	}

_Check_return_ inline float sinh(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD sinhf(_Xx));
	}

_Check_return_ inline float sqrt(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD sqrtf(_Xx));
	}

_Check_return_ inline float tan(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD tanf(_Xx));
	}

_Check_return_ inline float tanh(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD tanhf(_Xx));
	}

_Check_return_ inline float tgamma(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD tgammaf(_Xx));
	}

_Check_return_ inline float trunc(_In_ float _Xx) _NOEXCEPT
	{
	return (_CSTD truncf(_Xx));
	}

_Check_return_ inline long double abs(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD fabsl(_Xx));
	}

_Check_return_ inline long double acos(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD acosl(_Xx));
	}

_Check_return_ inline long double acosh(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD acoshl(_Xx));
	}

_Check_return_ inline long double asin(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD asinl(_Xx));
	}

_Check_return_ inline long double asinh(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD asinhl(_Xx));
	}

_Check_return_ inline long double atan(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD atanl(_Xx));
	}

_Check_return_ inline long double atanh(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD atanhl(_Xx));
	}

_Check_return_ inline long double atan2(_In_ long double _Yx,
	_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD atan2l(_Yx, _Xx));
	}

_Check_return_ inline long double cbrt(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD cbrtl(_Xx));
	}

_Check_return_ inline long double ceil(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD ceill(_Xx));
	}

_Check_return_ inline long double copysign(_In_ long double _Number,
	_In_ long double _Sign) _NOEXCEPT
	{
	return (_CSTD copysignl(_Number, _Sign));
	}

_Check_return_ inline long double cos(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD cosl(_Xx));
	}

_Check_return_ inline long double cosh(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD coshl(_Xx));
	}

_Check_return_ inline long double erf(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD erfl(_Xx));
	}

_Check_return_ inline long double erfc(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD erfcl(_Xx));
	}

_Check_return_ inline long double exp(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD expl(_Xx));
	}

_Check_return_ inline long double exp2(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD exp2l(_Xx));
	}

_Check_return_ inline long double expm1(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD expm1l(_Xx));
	}

_Check_return_ inline long double fabs(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD fabsl(_Xx));
	}

_Check_return_ inline long double fdim(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD fdiml(_Xx, _Yx));
	}

_Check_return_ inline long double floor(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD floorl(_Xx));
	}

_Check_return_ inline long double fma(_In_ long double _Xx,
	_In_ long double _Yx, _In_ long double _Zx) _NOEXCEPT
	{
	return (_CSTD fmal(_Xx, _Yx, _Zx));
	}

_Check_return_ inline long double fmax(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD fmaxl(_Xx, _Yx));
	}

_Check_return_ inline long double fmin(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD fminl(_Xx, _Yx));
	}

_Check_return_ inline long double fmod(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD fmodl(_Xx, _Yx));
	}

_Check_return_ inline long double frexp(_In_ long double _Xx,
	_Out_ int* _Yx) _NOEXCEPT
	{
	return (_CSTD frexpl(_Xx, _Yx));
	}

_Check_return_ inline long double hypot(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD hypotl(_Xx, _Yx));
	}

_Check_return_ inline int ilogb(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD ilogbl(_Xx));
	}

_Check_return_ inline long double ldexp(_In_ long double _Xx,
	_In_ int _Yx) _NOEXCEPT
	{
	return (_CSTD ldexpl(_Xx, _Yx));
	}

_Check_return_ inline long double lgamma(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD lgammal(_Xx));
	}

_Check_return_ inline long long llrint(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD llrintl(_Xx));
	}

_Check_return_ inline long long llround(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD llroundl(_Xx));
	}

_Check_return_ inline long double log(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD logl(_Xx));
	}

_Check_return_ inline long double log10(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD log10l(_Xx));
	}

_Check_return_ inline long double log1p(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD log1pl(_Xx));
	}

_Check_return_ inline long double log2(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD log2l(_Xx));
	}

_Check_return_ inline long double logb(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD logbl(_Xx));
	}

_Check_return_ inline long lrint(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD lrintl(_Xx));
	}

_Check_return_ inline long lround(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD lroundl(_Xx));
	}

_Check_return_ inline long double modf(_In_ long double _Xx,
	_Out_ long double* _Yx) _NOEXCEPT
	{
	return (_CSTD modfl(_Xx, _Yx));
	}

_Check_return_ inline long double nearbyint(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD nearbyintl(_Xx));
	}

_Check_return_ inline long double nextafter(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD nextafterl(_Xx, _Yx));
	}

_Check_return_ inline long double nexttoward(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD nexttowardl(_Xx, _Yx));
	}

_Check_return_ inline long double pow(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD powl(_Xx, _Yx));
	}

_Check_return_ inline long double pow(_In_ long double _Xx,
	_In_ int _Yx) _NOEXCEPT
	{
	return (_Pow_int(_Xx, _Yx));
	}

_Check_return_ inline long double remainder(_In_ long double _Xx,
	_In_ long double _Yx) _NOEXCEPT
	{
	return (_CSTD remainderl(_Xx, _Yx));
	}

_Check_return_ inline long double remquo(_In_ long double _Xx,
	_In_ long double _Yx, _Out_ int *_Zx) _NOEXCEPT
	{
	return (_CSTD remquol(_Xx, _Yx, _Zx));
	}

_Check_return_ inline long double rint(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD rintl(_Xx));
	}

_Check_return_ inline long double round(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD roundl(_Xx));
	}

_Check_return_ inline long double scalbln(_In_ long double _Xx,
	_In_ long _Yx) _NOEXCEPT
	{
	return (_CSTD scalblnl(_Xx, _Yx));
	}

_Check_return_ inline long double scalbn(_In_ long double _Xx,
	_In_ int _Yx) _NOEXCEPT
	{
	return (_CSTD scalbnl(_Xx, _Yx));
	}

_Check_return_ inline long double sin(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD sinl(_Xx));
	}

_Check_return_ inline long double sinh(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD sinhl(_Xx));
	}

_Check_return_ inline long double sqrt(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD sqrtl(_Xx));
	}

_Check_return_ inline long double tan(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD tanl(_Xx));
	}

_Check_return_ inline long double tanh(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD tanhl(_Xx));
	}

_Check_return_ inline long double tgamma(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD tgammal(_Xx));
	}

_Check_return_ inline long double trunc(_In_ long double _Xx) _NOEXCEPT
	{
	return (_CSTD truncl(_Xx));
	}

 #endif /* RC_INVOKED */

#ifdef _STD_USING
 #undef _STD_USING
  #include <xtgmath.h>
 #define _STD_USING
#else /* _STD_USING */
 #include <xtgmath.h>
#endif /* _STD_USING */

 #if _GLOBAL_USING && !defined(RC_INVOKED)
_STD_BEGIN
using _CSTD abs; using _CSTD acos; using _CSTD asin;
using _CSTD atan; using _CSTD atan2; using _CSTD ceil;
using _CSTD cos; using _CSTD cosh; using _CSTD exp;
using _CSTD fabs; using _CSTD floor; using _CSTD fmod;
using _CSTD frexp; using _CSTD ldexp; using _CSTD log;
using _CSTD log10; using _CSTD modf; using _CSTD pow;
using _CSTD sin; using _CSTD sinh; using _CSTD sqrt;
using _CSTD tan; using _CSTD tanh;

using _CSTD acosf; using _CSTD asinf;
using _CSTD atanf; using _CSTD atan2f; using _CSTD ceilf;
using _CSTD cosf; using _CSTD coshf; using _CSTD expf;
using _CSTD fabsf; using _CSTD floorf; using _CSTD fmodf;
using _CSTD frexpf; using _CSTD ldexpf; using _CSTD logf;
using _CSTD log10f; using _CSTD modff; using _CSTD powf;
using _CSTD sinf; using _CSTD sinhf; using _CSTD sqrtf;
using _CSTD tanf; using _CSTD tanhf;

using _CSTD acosl; using _CSTD asinl;
using _CSTD atanl; using _CSTD atan2l; using _CSTD ceill;
using _CSTD cosl; using _CSTD coshl; using _CSTD expl;
using _CSTD fabsl; using _CSTD floorl; using _CSTD fmodl;
using _CSTD frexpl; using _CSTD ldexpl; using _CSTD logl;
using _CSTD log10l; using _CSTD modfl; using _CSTD powl;
using _CSTD sinl; using _CSTD sinhl; using _CSTD sqrtl;
using _CSTD tanl; using _CSTD tanhl;

using _CSTD float_t; using _CSTD double_t;

using _CSTD acosh; using _CSTD asinh; using _CSTD atanh;
using _CSTD cbrt; using _CSTD erf; using _CSTD erfc;
using _CSTD expm1; using _CSTD exp2;
using _CSTD hypot; using _CSTD ilogb; using _CSTD lgamma;
using _CSTD log1p; using _CSTD log2; using _CSTD logb;
using _CSTD llrint; using _CSTD lrint; using _CSTD nearbyint;
using _CSTD rint; using _CSTD llround; using _CSTD lround;
using _CSTD fdim; using _CSTD fma; using _CSTD fmax; using _CSTD fmin;
using _CSTD round; using _CSTD trunc;
using _CSTD remainder; using _CSTD remquo;
using _CSTD copysign; using _CSTD nan; using _CSTD nextafter;
using _CSTD scalbn; using _CSTD scalbln;
using _CSTD nexttoward; using _CSTD tgamma;

using _CSTD acoshf; using _CSTD asinhf; using _CSTD atanhf;
using _CSTD cbrtf; using _CSTD erff; using _CSTD erfcf;
using _CSTD expm1f; using _CSTD exp2f;
using _CSTD hypotf; using _CSTD ilogbf; using _CSTD lgammaf;
using _CSTD log1pf; using _CSTD log2f; using _CSTD logbf;
using _CSTD llrintf; using _CSTD lrintf; using _CSTD nearbyintf;
using _CSTD rintf; using _CSTD llroundf; using _CSTD lroundf;
using _CSTD fdimf; using _CSTD fmaf; using _CSTD fmaxf; using _CSTD fminf;
using _CSTD roundf; using _CSTD truncf;
using _CSTD remainderf; using _CSTD remquof;
using _CSTD copysignf; using _CSTD nanf;
using _CSTD nextafterf; using _CSTD scalbnf; using _CSTD scalblnf;
using _CSTD nexttowardf; using _CSTD tgammaf;

using _CSTD acoshl; using _CSTD asinhl; using _CSTD atanhl;
using _CSTD cbrtl; using _CSTD erfl; using _CSTD erfcl;
using _CSTD expm1l; using _CSTD exp2l;
using _CSTD hypotl; using _CSTD ilogbl; using _CSTD lgammal;
using _CSTD log1pl; using _CSTD log2l; using _CSTD logbl;
using _CSTD llrintl; using _CSTD lrintl; using _CSTD nearbyintl;
using _CSTD rintl; using _CSTD llroundl; using _CSTD lroundl;
using _CSTD fdiml; using _CSTD fmal; using _CSTD fmaxl; using _CSTD fminl;
using _CSTD roundl; using _CSTD truncl;
using _CSTD remainderl; using _CSTD remquol;
using _CSTD copysignl; using _CSTD nanl;
using _CSTD nextafterl; using _CSTD scalbnl; using _CSTD scalblnl;
using _CSTD nexttowardl; using _CSTD tgammal;

using _CSTD fpclassify; using _CSTD signbit;
using _CSTD isfinite; using _CSTD isinf;
using _CSTD isnan; using _CSTD isnormal;
using _CSTD isgreater; using _CSTD isgreaterequal;
using _CSTD isless; using _CSTD islessequal;
using _CSTD islessgreater; using _CSTD isunordered;
_STD_END
 #endif /* _GLOBAL_USING */

#endif /* _CMATH_ */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0009 */
