/***
*marshal_windows.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   Marshalling classes
*
*       [Public]
*
****/

#pragma once

#ifndef _INC_MSCLR_MARSHAL_WINDOWS
#define _INC_MSCLR_MARSHAL_WINDOWS

#include <msclr\marshal.h>
#include <windows.h>
#include <comutil.h>

namespace msclr{
        namespace interop{

//--------------------------------------------------------------------------------
// Context-free conversions templates specialization for windows types
//--------------------------------------------------------------------------------

//
// for BSTR -> System::String^, please see wchar_t* -> String^ in marshal.h
//

template <>
inline System::String^ marshal_as(const _bstr_t & _from_object)
{
        BSTR _bstr = _from_object.copy(false);
        if (_bstr == NULL)
        {
                return nullptr;
        }
        // Using PtrToStringBSTR here instead of marshal_as<String^, BSTR>() because we want to perserve the embedded NULLs
        return System::Runtime::InteropServices::Marshal::PtrToStringBSTR(System::IntPtr(_bstr));
}

template <>
inline _bstr_t marshal_as(System::String^ const & _from_object)
{
        if (_from_object == nullptr)
        {
                return _bstr_t(static_cast<BSTR>(NULL));
        }

        _bstr_t _ret_bstr_t;
        cli::pin_ptr<const wchar_t> _pinned_ptr = PtrToStringChars(_from_object);
        _ret_bstr_t.Attach(::SysAllocStringLen(_pinned_ptr, _from_object->Length));
        if (!_ret_bstr_t)
        {
                throw gcnew System::InsufficientMemoryException();
        }
        return _ret_bstr_t;
}

template <>
inline System::IntPtr marshal_as(const HANDLE& _from_object)
{
        return System::IntPtr(_from_object);
}

template <class _To_Type>
inline _To_Type marshal_as(System::IntPtr _from_object);

template <>
inline HANDLE marshal_as(System::IntPtr _from_object)
{
        return static_cast<HANDLE>(_from_object.ToPointer());
}

//--------------------------------------------------------------------------------
// Context conversion templates specialization for windows types
//--------------------------------------------------------------------------------

template<>
ref class context_node<BSTR, System::String^> :
        public context_node_base
{
        private:
                System::IntPtr _ip;
        public:
                context_node(BSTR& _to_object, System::String^ from)
                {
                        _ip = System::Runtime::InteropServices::Marshal::StringToBSTR (from);
                        _to_object = static_cast<BSTR>(_ip.ToPointer());
                }

                ~context_node()
                {
                        this->!context_node();
                }

        protected:
                !context_node()
                {
                        if(_ip != System::IntPtr::Zero)
                                System::Runtime::InteropServices::Marshal::FreeBSTR(_ip);
                }
};

        } //namespace interop
} //namespace msclr

#endif  /* _INC_MSCLR_MARSHAL_WINDOWS */
