/***
*marshal_cppstd.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   Marshalling classes
*
*       [Public]
*
****/

#pragma once

#ifndef _INC_MSCLR_MARSHAL_CPPSTD
#define _INC_MSCLR_MARSHAL_CPPSTD

#include <string>
#include <vector>
#include <vcclr.h>

#include "marshal.h"

namespace msclr{
        namespace interop{

template <>
inline System::String^ marshal_as(const std::string& _from_obj)
{
        return details::InternalAnsiToStringHelper(_from_obj.c_str(), _from_obj.length());
}

template <>
inline std::string marshal_as(System::String^ const & _from_obj)
{
        if (_from_obj == nullptr)
        {
                throw gcnew System::ArgumentNullException(_EXCEPTION_NULLPTR);
        }
        std::string _to_obj;
        size_t _size = details::GetAnsiStringSize(_from_obj);

        if (_size > 1)
        {
                // -1 because resize will automatically +1 for the NULL
                _to_obj.resize(_size-1);
                char *_dest_buf = &(_to_obj[0]);

                details::WriteAnsiString(_dest_buf, _size, _from_obj);
        }

        return _to_obj;
}

template <>
inline System::String^ marshal_as(const std::wstring& _from_obj)
{
        return details::InternalUnicodeToStringHelper(_from_obj.c_str(), _from_obj.length());
}

template <>
inline std::wstring marshal_as(System::String^ const & _from_obj)
{
        if(_from_obj != nullptr)
        {
                cli::pin_ptr<const wchar_t> _pinned_ptr = PtrToStringChars(_from_obj);
                std::wstring _to_obj(static_cast<const wchar_t *>(_pinned_ptr), _from_obj->Length);

                return _to_obj;
        }
        else
        {
                throw gcnew System::ArgumentNullException(_EXCEPTION_NULLPTR);
        }
}

        } //namespace interop
} //namespace msclr

#endif  /* _INC_MSCLR_MARSHAL_CPPSTD */
