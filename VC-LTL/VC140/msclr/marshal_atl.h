/***
*marshal_atl.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   Marshalling classes
*
*       [Public]
*
****/

#pragma once

#ifndef _INC_MSCLR_MARSHAL_ATL
#define _INC_MSCLR_MARSHAL_ATL

#include <atlsafe.h>
#include <atlbase.h>
#include <atlstr.h>
#include <vcclr.h>
#include <atlcomcli.h>

#include <msclr\marshal.h>

namespace msclr{
        namespace interop{

template <>
inline System::String^ marshal_as(const CComBSTR& _from_object)
{
        if (_from_object.m_str == NULL)
        {
                return nullptr;
        }
        // Using PtrToStringBSTR here instead of marshal_as<String^, BSTR>() because we want to perserve the embedded NULLs
        return System::Runtime::InteropServices::Marshal::PtrToStringBSTR(System::IntPtr(_from_object.m_str));
}

template <>
inline CComBSTR marshal_as(System::String^ const& _from_object)
{
        if (_from_object == nullptr)
        {
                return CComBSTR(static_cast<const wchar_t*>(NULL));
        }
        if(_from_object->Length == 0)
        {
                return CComBSTR(static_cast<const wchar_t*>(L""));
        }

        cli::pin_ptr<const wchar_t> _pinned_ptr = PtrToStringChars(_from_object);
        return  CComBSTR( _from_object->Length, static_cast<const wchar_t *>(_pinned_ptr));
}

template <>
inline System::String^ marshal_as(const CStringA& _from_obj)
{
        return details::InternalAnsiToStringHelper(_from_obj.operator LPCSTR(), _from_obj.GetLength());
}

template <>
inline System::String^ marshal_as(const CStringW& _from_obj)
{
        // this will perserve the embedded nulls
        return details::InternalUnicodeToStringHelper(_from_obj.operator LPCWSTR(), _from_obj.GetLength());
}

template <>
inline CStringA marshal_as(System::String^ const & _from_obj)
{
        if (_from_obj == nullptr)
        {
                throw gcnew System::ArgumentNullException(_EXCEPTION_NULLPTR);
        }
        CStringA _to_obj;
        size_t _size = details::GetAnsiStringSize(_from_obj);

        //checking for overflow
        if (_size > INT_MAX)
        {
                throw gcnew System::ArgumentOutOfRangeException(_EXCEPTION_NULLPTR);
        }

        int _length = static_cast<int>(_size)-1;

        //GetBuffer() throws, so we don't need to check for NULL
        char* _dest_buf = _to_obj.GetBuffer(_length);

        details::WriteAnsiString(_dest_buf, _size, _from_obj);
        _to_obj.ReleaseBuffer(_length); // We don't want to include the NULL.  This call will set the length to _length

        return _to_obj;
}

template <>
inline CStringW marshal_as(System::String^ const & _from_obj)
{
        if (_from_obj == nullptr)
        {
                throw gcnew System::ArgumentNullException(_EXCEPTION_NULLPTR);
        }
        cli::pin_ptr<const wchar_t> _pinned_ptr = PtrToStringChars(_from_obj);
        return CStringW(static_cast<const wchar_t *>(_pinned_ptr), _from_obj->Length);
}

        } //namespace interop
} //namespace msclr

#endif  /* _INC_MSCLR_MARSHAL_ATL */
