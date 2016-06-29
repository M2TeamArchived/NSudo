// codecvt standard header
#pragma once
#ifndef _CODECVT_
#define _CODECVT_
#ifndef RC_INVOKED
#include <locale>
#include <cwchar>

 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
 #pragma push_macro("new")
 #undef new

 #pragma warning(disable: 6326)

_STD_BEGIN
#define _LITTLE_FIRST	1
#define _BIG_FIRST		2
#define _BYTES_PER_WORD	4

enum codecvt_mode {
	consume_header = 4,
	generate_header = 2,
	little_endian = 1};

typedef _CSTD mbstate_t _Statype;

		// TEMPLATE CLASS codecvt_utf8
template<class _Elem,
	unsigned long _Mymax = 0x10ffff,
	codecvt_mode _Mymode = (codecvt_mode)0>
	class codecvt_utf8
	: public codecvt<_Elem, char, _Statype>
	{	// facet for converting between _Elem and UTF-8 byte sequences
public:
	typedef codecvt<_Elem, char, _Statype> _Mybase;
	typedef typename _Mybase::result result;
	typedef char _Byte;
	typedef _Elem intern_type;
	typedef _Byte extern_type;
	typedef _Statype state_type;

	explicit codecvt_utf8(size_t _Refs = 0)
		: _Mybase(_Refs)
		{	// construct with ref count
		}

	virtual __CLR_OR_THIS_CALL ~codecvt_utf8() _NOEXCEPT
		{	// destroy the object
		}

protected:
	virtual result __CLR_OR_THIS_CALL do_in(_Statype& _State,
		const _Byte *_First1, const _Byte *_Last1, const _Byte *& _Mid1,
		_Elem *_First2, _Elem *_Last2, _Elem *& _Mid2) const
		{	// convert bytes [_First1, _Last1) to [_First2, _Last)
		char *_Pstate = (char *)&_State;
		_Mid1 = _First1;
		_Mid2 = _First2;

		for (; _Mid1 != _Last1 && _Mid2 != _Last2; )
			{	// convert a multibyte sequence
			unsigned char _By = (unsigned char)*_Mid1;
			unsigned long _Ch;
			int _Nextra;

			if (_By < 0x80)
				_Ch = _By, _Nextra = 0;
			else if (_By < 0xc0)
				{	// 0x80-0xdf not first byte
				++_Mid1;
				return (_Mybase::error);
				}
			else if (_By < 0xe0)
				_Ch = _By & 0x1f, _Nextra = 1;
			else if (_By < 0xf0)
				_Ch = _By & 0x0f, _Nextra = 2;
			else if (_By < 0xf8)
				_Ch = _By & 0x07, _Nextra = 3;
			else
				_Ch = _By & 0x03, _Nextra = _By < 0xfc ? 4 : 5;

			if (_Nextra == 0)
				++_Mid1;
			else if (_Last1 - _Mid1 < _Nextra + 1)
				break;	// not enough input
			else
				for (++_Mid1; 0 < _Nextra; --_Nextra, ++_Mid1)
					if ((_By = (unsigned char)*_Mid1) < 0x80 || 0xc0 <= _By)
						return (_Mybase::error);	// not continuation byte
					else
						_Ch = _Ch << 6 | (_By & 0x3f);

			if (*_Pstate == 0)
				{	// first time, maybe look for and consume header
				*_Pstate = 1;

				if ((_Mymode & consume_header) != 0 && _Ch == 0xfeff)
					{	// drop header and retry
					result _Ans = do_in(_State, _Mid1, _Last1, _Mid1,
						_First2, _Last2, _Mid2);

					if (_Ans == _Mybase::partial)
						{	// roll back header determination
						*_Pstate = 0;
						_Mid1 = _First1;
						}
					return (_Ans);
					}
				}

			if (_Mymax < _Ch)
				return (_Mybase::error);	// code too large
			*_Mid2++ = (_Elem)_Ch;
			}

		return (_First1 == _Mid1 ? _Mybase::partial : _Mybase::ok);
		}

	virtual result __CLR_OR_THIS_CALL do_out(_Statype& _State,
		const _Elem *_First1, const _Elem *_Last1, const _Elem *& _Mid1,
		_Byte *_First2, _Byte *_Last2, _Byte *& _Mid2) const
		{	// convert [_First1, _Last1) to bytes [_First2, _Last)
		char *_Pstate = (char *)&_State;
		_Mid1 = _First1;
		_Mid2 = _First2;

		for (; _Mid1 != _Last1 && _Mid2 != _Last2; )
			{	// convert and put a wide char
			_Byte _By;
			int _Nextra;
			unsigned long _Ch = (unsigned long)*_Mid1;

			if (_Mymax < _Ch)
				return (_Mybase::error);

			if (_Ch < 0x0080)
				_By = (_Byte)_Ch, _Nextra = 0;
			else if (_Ch < 0x0800)
				_By = (_Byte)(0xc0 | _Ch >> 6), _Nextra = 1;
			else if (_Ch < 0x00010000)
				_By = (_Byte)(0xe0 | _Ch >> 12), _Nextra = 2;
			else if (_Ch < 0x00200000)
				_By = (_Byte)(0xf0 | _Ch >> 18), _Nextra = 3;
			else if (_Ch < 0x04000000)
				_By = (_Byte)(0xf8 | _Ch >> 24), _Nextra = 4;
			else
				_By = (_Byte)(0xfc | (_Ch >> 30 & 0x03)), _Nextra = 5;

			if (*_Pstate == 0)
				{	// first time, maybe generate header
				*_Pstate = 1;
				if ((_Mymode & generate_header) == 0)
					;
				else if (_Last2 - _Mid2 < 3 + 1 + _Nextra)
					return (_Mybase::partial);	// not enough room for both
				else
					{	// prepend header
					*_Mid2++ = (_Byte)(unsigned char)0xef;
					*_Mid2++ = (_Byte)(unsigned char)0xbb;
					*_Mid2++ = (_Byte)(unsigned char)0xbf;
					}
				}

			if (_Last2 - _Mid2 < 1 + _Nextra)
				break;	// not enough room for output

			++_Mid1;
			for (*_Mid2++ = _By; 0 < _Nextra; )
				*_Mid2++ = (_Byte)((_Ch >> 6 * --_Nextra & 0x3f) | 0x80);
			}
		return (_First1 == _Mid1 ? _Mybase::partial : _Mybase::ok);
		}

	virtual result __CLR_OR_THIS_CALL do_unshift(_Statype&,
		_Byte *_First2, _Byte *, _Byte *& _Mid2) const
		{	// generate bytes to return to default shift state
		_Mid2 = _First2;
		return (_Mybase::ok);
		}

	virtual int __CLR_OR_THIS_CALL do_length(_Statype& _State, const _Byte *_First1,
		const _Byte *_Last1, size_t _Count) const _THROW0()
		{	// return min(_Count, converted length of bytes [_First1, _Last1))
		size_t _Wchars = 0;
		_Statype _Mystate = _State;

		for (; _Wchars < _Count && _First1 != _Last1; )
			{	// convert another wide character
			const _Byte *_Mid1;
			_Elem *_Mid2;
			_Elem _Ch;

			switch (do_in(_Mystate, _First1, _Last1, _Mid1,
				&_Ch, &_Ch + 1, _Mid2))
				{	// test result of single wide-char conversion
			case _Mybase::noconv:
				return ((int)(_Wchars + (_Last1 - _First1)));

			case _Mybase::ok:
				if (_Mid2 == &_Ch + 1)
					++_Wchars;	// replacement do_in might not convert one
				_First1 = _Mid1;
				break;

			default:
				return ((int)_Wchars);	// error or partial
				}
			}

		return ((int)_Wchars);
		}

	virtual bool __CLR_OR_THIS_CALL do_always_noconv() const _THROW0()
		{	// return true if conversions never change input
		return (false);
		}

	virtual int __CLR_OR_THIS_CALL do_max_length() const _THROW0()
		{	// return maximum length required for a conversion
		return ((_Mymode & (consume_header | generate_header)) != 0
			? 9 : 6);
		}

	virtual int __CLR_OR_THIS_CALL do_encoding() const _THROW0()
		{	// return length of code sequence (from codecvt)
		return ((_Mymode & (consume_header | generate_header)) != 0
			? -1 : 0);	// -1 => state dependent, 0 => varying length
		}
	};

		// TEMPLATE CLASS codecvt_utf16
template<class _Elem,
	unsigned long _Mymax = 0x10ffff,
	codecvt_mode _Mymode = (codecvt_mode)0>
	class codecvt_utf16
	: public codecvt<_Elem, char, _Statype>
	{	// facet for converting between _Elem and UTF-16 multibyte sequences
	enum {_Bytes_per_word = 2};
public:
	typedef codecvt<_Elem, char, _Statype> _Mybase;
	typedef typename _Mybase::result result;
	typedef char _Byte;
	typedef _Elem intern_type;
	typedef _Byte extern_type;
	typedef _Statype state_type;

	explicit codecvt_utf16(size_t _Refs = 0)
		: _Mybase(_Refs)
		{	// construct with ref count
		}

	virtual __CLR_OR_THIS_CALL ~codecvt_utf16() _NOEXCEPT
		{	// destroy the object
		}

protected:
	virtual result __CLR_OR_THIS_CALL do_in(_Statype& _State,
		const _Byte *_First1, const _Byte *_Last1, const _Byte *& _Mid1,
		_Elem *_First2, _Elem *_Last2, _Elem *& _Mid2) const
		{	// convert bytes [_First1, _Last1) to [_First2, _Last)
		char *_Pstate = (char *)&_State;
		_Mid1 = _First1;
		_Mid2 = _First2;

		for (; _Bytes_per_word <= _Last1 - _Mid1 && _Mid2 != _Last2; )
			{	// convert a multibyte sequence
			unsigned char *_Ptr = (unsigned char *)_Mid1;
			unsigned long _Ch;
			unsigned short _Ch0, _Ch1;

			if (*_Pstate == _LITTLE_FIRST)
				_Ch0 = (unsigned short)(_Ptr[1] << 8 | _Ptr[0]);
			else if (*_Pstate == _BIG_FIRST)
				_Ch0 = (unsigned short)(_Ptr[0] << 8 | _Ptr[1]);
			else
				{	// no header seen yet, try preferred mode
				unsigned char _Default_endian = (_Mymode & little_endian) != 0
					? _LITTLE_FIRST : _BIG_FIRST;

				if ((_Mymode & little_endian) != 0)
					_Ch0 = (unsigned short)(_Ptr[1] << 8 | _Ptr[0]);
				else
					_Ch0 = (unsigned short)(_Ptr[0] << 8 | _Ptr[1]);
				if ((_Mymode & consume_header) == 0
					|| (_Ch0 != 0xfeff && _Ch0 != 0xfffe))
					*_Pstate = _Default_endian;
				else
					{	// consume header, fixate on endianness, and retry
					_Mid1 += _Bytes_per_word;
					*_Pstate = (char)(_Ch0 == 0xfeff
						? _Default_endian
						: (unsigned char)(3 - _Default_endian));
					result _Ans = do_in(_State, _Mid1, _Last1, _Mid1,
						_First2, _Last2, _Mid2);

					if (_Ans == _Mybase::partial)
						{	// not enough bytes, roll back header
						*_Pstate = 0;
						_Mid1 = _First1;
						}
					return (_Ans);
					}
				}

			if (_Ch0 < 0xd800 || 0xdc00 <= _Ch0)
				{	// one word, consume bytes
				_Mid1 += _Bytes_per_word;
				_Ch = _Ch0;
				}
			else if (_Last1 - _Mid1 < 2 * _Bytes_per_word)
				break;
			else
				{	// get second word
				if (*_Pstate == _LITTLE_FIRST)
					_Ch1 = (unsigned short)(_Ptr[3] << 8 | _Ptr[2]);
				else
					_Ch1 = (unsigned short)(_Ptr[2] << 8 | _Ptr[3]);

				if (_Ch1 < 0xdc00 || 0xe000 <= _Ch1)
					return (_Mybase::error);

				_Mid1 += 2 * _Bytes_per_word;
				_Ch = (unsigned long)(_Ch0 - 0xd800 + 0x0040) << 10
					| (_Ch1 - 0xdc00);
				}

			if (_Mymax < _Ch)
				return (_Mybase::error);	// code too large
			*_Mid2++ = (_Elem)_Ch;
			}

		return (_First1 == _Mid1 ? _Mybase::partial : _Mybase::ok);
		}

	virtual result __CLR_OR_THIS_CALL do_out(_Statype& _State,
		const _Elem *_First1, const _Elem *_Last1, const _Elem *& _Mid1,
		_Byte *_First2, _Byte *_Last2, _Byte *& _Mid2) const
		{	// convert [_First1, _Last1) to bytes [_First2, _Last)
		char *_Pstate = (char *)&_State;
		_Mid1 = _First1;
		_Mid2 = _First2;

		if (*_Pstate == 0)
			{	// determine endianness once, maybe generate header
			*_Pstate = (_Mymode & little_endian) != 0
				? _LITTLE_FIRST : _BIG_FIRST;
			if ((_Mymode & generate_header) == 0)
				;
			else if (_Last2 - _Mid2 < 3 * _Bytes_per_word)
				return (_Mybase::partial);	// not enough room for all
			else if (*_Pstate == _LITTLE_FIRST)
				{	// put header LS byte first
				*_Mid2++ = (_Byte)(unsigned char)0xff;
				*_Mid2++ = (_Byte)(unsigned char)0xfe;
				}
			else
				{	// put header MS byte first
				*_Mid2++ = (_Byte)(unsigned char)0xfe;
				*_Mid2++ = (_Byte)(unsigned char)0xff;
				}
			}

		for (; _Mid1 != _Last1 && _Bytes_per_word <= _Last2 - _Mid2; )
			{	// convert and put a wide char
			bool _Extra = false;
			unsigned long _Ch = (unsigned long)*_Mid1++;

			if ((_Mymax < 0x10ffff ? _Mymax : 0x10ffff) < _Ch)
				return (_Mybase::error);	// value too large
			else if (_Ch <= 0xffff)
				{	// one word, can't be code for first of two
				if (0xd800 <= _Ch && _Ch < 0xdc00)
					return (_Mybase::error);
				}
			else if (_Last2 - _Mid2 < 2 * _Bytes_per_word)
				{	// not enough room for two-word output, back up
				--_Mid1;
				return (_Mybase::partial);
				}
			else
				_Extra = true;

			if (*_Pstate == _LITTLE_FIRST)
				if (!_Extra)
					{	// put a single word LS byte first
					*_Mid2++ = (_Byte)_Ch;
					*_Mid2++ = (_Byte)(_Ch >> 8);
					}
				else
					{	// put a pair of words LS byte first
					unsigned short _Ch0 = (unsigned short)(0xd800
						| (unsigned short)(_Ch >> 10) - 0x0040);
					*_Mid2++ = (_Byte)_Ch0;
					*_Mid2++ = (_Byte)(_Ch0 >> 8);

					_Ch0 = (unsigned short)(0xdc00
						| ((unsigned short)_Ch & 0x03ff));
					*_Mid2++ = (_Byte)_Ch0;
					*_Mid2++ = (_Byte)(_Ch0 >> 8);
					}
			else
				if (!_Extra)
					{	// put a single word MS byte first
					*_Mid2++ = (_Byte)(_Ch >> 8);
					*_Mid2++ = (_Byte)_Ch;
					}
				else
					{	// put a pair of words MS byte first
					unsigned short _Ch0 = (unsigned short)(0xd800
						| (unsigned short)(_Ch >> 10) - 0x0040);
					*_Mid2++ = (_Byte)(_Ch0 >> 8);
					*_Mid2++ = (_Byte)_Ch0;

					_Ch0 = (unsigned short)(0xdc00
						| ((unsigned short)_Ch & 0x03ff));
					*_Mid2++ = (_Byte)(_Ch0 >> 8);
					*_Mid2++ = (_Byte)_Ch0;
					}
			}

		return (_First1 == _Mid1 ? _Mybase::partial : _Mybase::ok);
		}

	virtual result __CLR_OR_THIS_CALL do_unshift(_Statype&,
		_Byte *_First2, _Byte *, _Byte *& _Mid2) const
		{	// generate bytes to return to default shift state
		_Mid2 = _First2;
		return (_Mybase::ok);
		}

	virtual int __CLR_OR_THIS_CALL do_length(_Statype& _State, const _Byte *_First1,
		const _Byte *_Last1, size_t _Count) const _THROW0()
		{	// return min(_Count, converted length of bytes [_First1, _Last1))
		size_t _Wchars = 0;
		_Statype _Mystate = _State;

		for (; _Wchars < _Count && _First1 != _Last1; )
			{	// convert another wide char
			const _Byte *_Mid1;
			_Elem *_Mid2;
			_Elem _Ch;

			switch (do_in(_Mystate, _First1, _Last1, _Mid1,
				&_Ch, &_Ch + 1, _Mid2))
				{	// test result of single wide-char conversion
			case _Mybase::noconv:
				return ((int)(_Wchars + (_Last1 - _First1)));

			case _Mybase::ok:
				if (_Mid2 == &_Ch + 1)
					++_Wchars;	// replacement do_in might not convert one
				_First1 = _Mid1;
				break;

			default:
				return ((int)_Wchars);	// error or partial
				}
			}

		return ((int)_Wchars);
		}

	virtual bool __CLR_OR_THIS_CALL do_always_noconv() const _THROW0()
		{	// return true if conversions never change input
		return (false);
		}

	virtual int __CLR_OR_THIS_CALL do_max_length() const _THROW0()
		{	// return maximum length required for a conversion
		return ((_Mymode & (consume_header | generate_header)) != 0
			? 3 * _Bytes_per_word : 6 * _Bytes_per_word);
		}

	virtual int __CLR_OR_THIS_CALL do_encoding() const _THROW0()
		{	// return length of code sequence (from codecvt)
		return ((_Mymode & (consume_header | generate_header)) != 0
			? -1 : 0);	// -1 => state dependent, 0 => varying length
		}
	};

		// CLASS codecvt_utf8_utf16
template<class _Elem,
	unsigned long _Mymax = 0x10ffff,
	codecvt_mode _Mymode = (codecvt_mode)0>
	class codecvt_utf8_utf16
	: public codecvt<_Elem, char, _Statype>
	{	// facet for converting between UTF-16 _Elem and UTF-8 byte sequences
public:
	typedef codecvt<_Elem, char, _Statype> _Mybase;
	typedef typename _Mybase::result result;
	typedef char _Byte;
	typedef _Elem intern_type;
	typedef _Byte extern_type;
	typedef _Statype state_type;

	static_assert(sizeof (unsigned short) <= sizeof (state_type),
		"state_type too small");

	explicit codecvt_utf8_utf16(size_t _Refs = 0)
		: _Mybase(_Refs)
		{	// construct with ref count
		}

	virtual __CLR_OR_THIS_CALL ~codecvt_utf8_utf16() _NOEXCEPT
		{	// destroy the object
		}

protected:
	virtual result __CLR_OR_THIS_CALL do_in(_Statype& _State,
		const _Byte *_First1, const _Byte *_Last1, const _Byte *& _Mid1,
		_Elem *_First2, _Elem *_Last2, _Elem *& _Mid2) const
		{	// convert bytes [_First1, _Last1) to [_First2, _Last2)
		unsigned short *_Pstate = (unsigned short *)&_State;
		_Mid1 = _First1;
		_Mid2 = _First2;

		for (; _Mid1 != _Last1 && _Mid2 != _Last2; )
			{	// convert a multibyte sequence
			unsigned char _By = (unsigned char)*_Mid1;
			unsigned long _Ch;
			int _Nextra, _Nskip;

			if (*_Pstate <= 1)
				;	// no leftover word
			else if (_By < 0x80 || 0xc0 <= _By)
				return (_Mybase::error);	// not continuation byte
			else
				{	// deliver second half of two-word value
				++_Mid1;
				*_Mid2++ = (_Elem)(*_Pstate | (_By & 0x3f));
				*_Pstate = 1;
				continue;
				}

			if (_By < 0x80)
				_Ch = _By, _Nextra = 0;
			else if (_By < 0xc0)
				{	// 0x80-0xdf not first byte
				++_Mid1;
				return (_Mybase::error);
				}
			else if (_By < 0xe0)
				_Ch = _By & 0x1f, _Nextra = 1;
			else if (_By < 0xf0)
				_Ch = _By & 0x0f, _Nextra = 2;
			else if (_By < 0xf8)
				_Ch = _By & 0x07, _Nextra = 3;
			else
				_Ch = _By & 0x03, _Nextra = _By < 0xfc ? 4 : 5;

			_Nskip = _Nextra < 3 ? 0 : 1;	// leave a byte for 2nd word
			_First1 = _Mid1;	// roll back point

			if (_Nextra == 0)
				++_Mid1;
			else if (_Last1 - _Mid1 < _Nextra + 1 - _Nskip)
				break;	// not enough input
			else
				for (++_Mid1; _Nskip < _Nextra; --_Nextra, ++_Mid1)
					if ((_By = (unsigned char)*_Mid1) < 0x80 || 0xc0 <= _By)
						return (_Mybase::error);	// not continuation byte
					else
						_Ch = _Ch << 6 | (_By & 0x3f);
			if (0 < _Nskip)
				_Ch <<= 6;	// get last byte on next call

			if ((_Mymax < 0x10ffff ? _Mymax : 0x10ffff) < _Ch)
				return (_Mybase::error);	// value too large
			else if (0xffff < _Ch)
				{	// deliver first half of two-word value, save second word
				unsigned short _Ch0 =
					(unsigned short)(0xd800 | (_Ch >> 10) - 0x0040);

				*_Mid2++ = (_Elem)_Ch0;
				*_Pstate = (unsigned short)(0xdc00 | (_Ch & 0x03ff));
				continue;
				}

			if (_Nskip == 0)
				;
			else if (_Mid1 == _Last1)
				{	// not enough bytes, noncanonical value
				_Mid1 = _First1;
				break;
				}
			else if ((_By = (unsigned char)*_Mid1++) < 0x80 || 0xc0 <= _By)
				return (_Mybase::error);	// not continuation byte
			else
				_Ch |= _By & 0x3f;	// complete noncanonical value

			if (*_Pstate == 0)
				{	// first time, maybe look for and consume header
				*_Pstate = 1;

				if ((_Mymode & consume_header) != 0 && _Ch == 0xfeff)
					{	// drop header and retry
					result _Ans = do_in(_State, _Mid1, _Last1, _Mid1,
						_First2, _Last2, _Mid2);

					if (_Ans == _Mybase::partial)
						{	// roll back header determination
						*_Pstate = 0;
						_Mid1 = _First1;
						}
					return (_Ans);
					}
				}

			*_Mid2++ = (_Elem)_Ch;
			}

		return (_First1 == _Mid1 ? _Mybase::partial : _Mybase::ok);
		}

	virtual result __CLR_OR_THIS_CALL do_out(_Statype& _State,
		const _Elem *_First1, const _Elem *_Last1, const _Elem *& _Mid1,
		_Byte *_First2, _Byte *_Last2, _Byte *& _Mid2) const
		{	// convert [_First1, _Last1) to bytes [_First2, _Last)
		unsigned short *_Pstate = (unsigned short *)&_State;
		_Mid1 = _First1;
		_Mid2 = _First2;

		for (; _Mid1 != _Last1 && _Mid2 != _Last2; )
			{	// convert and put a wide char
			unsigned long _Ch;
			unsigned short _Ch1 = (unsigned short)*_Mid1;
			bool _Save = false;

			if (1 < *_Pstate)
				{	// get saved MS 11 bits from *_Pstate
				if (_Ch1 < 0xdc00 || 0xe000 <= _Ch1)
					return (_Mybase::error);	// bad second word
				_Ch = (*_Pstate << 10) | (_Ch1 - 0xdc00);
				}
			else if (0xd800 <= _Ch1 && _Ch1 < 0xdc00)
				{	// get new first word
				_Ch = (_Ch1 - 0xd800 + 0x0040) << 10;
				_Save = true;	// put only first byte, rest with second word
				}
			else
				_Ch = _Ch1;	// not first word, just put it

			_Byte _By;
			int _Nextra;

			if (_Ch < 0x0080)
				_By = (_Byte)_Ch, _Nextra = 0;
			else if (_Ch < 0x0800)
				_By = (_Byte)(0xc0 | _Ch >> 6), _Nextra = 1;
			else if (_Ch < 0x10000)
				_By = (_Byte)(0xe0 | _Ch >> 12), _Nextra = 2;
			else
				_By = (_Byte)(0xf0 | _Ch >> 18), _Nextra = 3;

			int _Nput = _Nextra < 3 ? _Nextra + 1 : _Save ? 1 : 3;

			if (_Last2 - _Mid2 < _Nput)
				break;	// not enough room, even without header
			else if (*_Pstate != 0 || (_Mymode & generate_header) == 0)
				;	// no header to put
			else if (_Last2 - _Mid2 < 3 + _Nput)
				break;	// not enough room for header + output
			else
				{	// prepend header
				*_Mid2++ = (_Byte)(unsigned char)0xef;
				*_Mid2++ = (_Byte)(unsigned char)0xbb;
				*_Mid2++ = (_Byte)(unsigned char)0xbf;
				}

			++_Mid1;
			if (_Save || _Nextra < 3)
				{	// put first byte of sequence, if not already put
				*_Mid2++ = _By;
				--_Nput;
				}
			for (; 0 < _Nput; --_Nput)
				*_Mid2++ = (_Byte)((_Ch >> 6 * --_Nextra & 0x3f) | 0x80);

			*_Pstate = (unsigned short)(_Save ? _Ch >> 10 : 1);
			}

		return (_First1 == _Mid1 ? _Mybase::partial : _Mybase::ok);
		}

	virtual result __CLR_OR_THIS_CALL do_unshift(_Statype& _State,
		_Byte *_First2, _Byte *, _Byte *& _Mid2) const
		{	// generate bytes to return to default shift state
		unsigned short *_Pstate = (unsigned short *)&_State;
		_Mid2 = _First2;

		return (1 < *_Pstate
			? _Mybase::error : _Mybase::ok);	// fail if trailing first word
		}

	virtual int __CLR_OR_THIS_CALL do_length(_Statype& _State, const _Byte *_First1,
		const _Byte *_Last1, size_t _Count) const _THROW0()
		{	// return min(_Count, converted length of bytes [_First1, _Last1))
		size_t _Wchars = 0;
		_Statype _Mystate = _State;

		for (; _Wchars < _Count && _First1 != _Last1; )
			{	// convert another wide character
			const _Byte *_Mid1;
			_Elem *_Mid2;
			_Elem _Ch;

			switch (do_in(_Mystate, _First1, _Last1, _Mid1,
				&_Ch, &_Ch + 1, _Mid2))
				{	// test result of single wide-char conversion
			case _Mybase::noconv:
				return ((int)(_Wchars + (_Last1 - _First1)));

			case _Mybase::ok:
				if (_Mid2 == &_Ch + 1)
					++_Wchars;	// replacement do_in might not convert one
				_First1 = _Mid1;
				break;

			default:
				return ((int)_Wchars);	// error or partial
				}
			}

		return ((int)_Wchars);
		}

	virtual bool __CLR_OR_THIS_CALL do_always_noconv() const _THROW0()
		{	// return true if conversions never change input
		return (false);
		}

	virtual int __CLR_OR_THIS_CALL do_max_length() const _THROW0()
		{	// return maximum length required for a conversion
		return ((_Mymode & consume_header) != 0 ? 9	// header + max input
			: (_Mymode & generate_header) != 0 ? 7	// header + max output
			: 6);	// 6-byte max input sequence, no 3-byte header
		}

	virtual int __CLR_OR_THIS_CALL do_encoding() const _THROW0()
		{	// return length of code sequence (from codecvt)
		return (0);	// 0 => varying length
		}
	};
_STD_END
 #pragma pop_macro("new")
 #pragma warning(pop)
 #pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _CODECVT_ */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0009 */
