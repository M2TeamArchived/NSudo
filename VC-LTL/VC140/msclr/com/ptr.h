/***
*ptr.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   COM Wrapper for the Managed World
*
*       [Public]
*
****/

#pragma once

#if !defined (_INC_MSCLR_COM_PTR)

#ifndef __cplusplus_cli
#error ERROR: msclr libraries are not compatible with /clr:oldSyntax
#endif  /* __cplusplus_cli */

#include <vcclr.h>

#include <msclr\safebool.h>

namespace msclr
{

namespace _detail
{
    // COM::ptr::operator->() returns a smart_com_ptr instead of
    // a regular interface pointer so that a Release is done automatically
    // when the temporary is destroyed

    template<class _interface_type>
    ref class smart_com_ptr
    {
        public:
        smart_com_ptr(_interface_type * p)
        {
            ptr= p;
        }

        smart_com_ptr(smart_com_ptr % ip)
        {
            ptr = ip.ptr;
            ptr->AddRef();
        }

        _interface_type * operator ->()
        {
            return ptr;
        }

        ~smart_com_ptr()
        {
            ptr->Release();
        }

        private:
        _interface_type * ptr;
    };
} //namespace _detail


namespace com
{
    template<class _interface_type>
    ref class ptr
    {
        public:

        ptr():obj_rcw(nullptr)
        {
        }

        // Construct from interface pointer
        ptr(_interface_type * p)
        {
            obj_rcw = nullptr;
            assign(p);
        }

        // Attach to an interface pointer
        void Attach(_interface_type * _right)
        {
            if (valid())
            {
                throw gcnew System::InvalidOperationException("COM::ptr.Attach");
            }

            assign(_right);
        }

        // Assign an interface pointer
        ptr<_interface_type> % operator=(_interface_type * _right)
        {
            Attach(_right);
            return *this;
        }

        // All CreateInstance methods create an instance of a COM Object
        // by calling CoCreateInstance
        void CreateInstance(System::String ^ prog_id, LPUNKNOWN pouter, DWORD cls_context)
        {
            wchar_t * pwszprog_id = NULL;

            if(prog_id != nullptr)
            {
                pin_ptr<const __wchar_t> _pinned_ptr = PtrToStringChars( prog_id );
                pwszprog_id = _wcsdup(_pinned_ptr);
            }

            try
            {
                CreateInstance(pwszprog_id, pouter, cls_context);
            }
            finally
            {
                free(pwszprog_id);
            }
        }

        void CreateInstance(System::String ^ prog_id, LPUNKNOWN pouter)
        {
            CreateInstance(prog_id, pouter, CLSCTX_ALL);
        }

        void CreateInstance(System::String ^ prog_id)
        {
            CreateInstance(prog_id, NULL, CLSCTX_ALL);
        }

        void CreateInstance(const wchar_t* progid, LPUNKNOWN pouter, DWORD cls_context)
        {
            CLSID clsid;
            System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(
                CLSIDFromProgID(progid, &clsid));
            CreateInstance(clsid, pouter, cls_context);
        }

        void CreateInstance(const wchar_t * progid, LPUNKNOWN pouter)
        {
            CreateInstance(progid, pouter, CLSCTX_ALL);
        }

        void CreateInstance(const wchar_t * progid)
        {
            CreateInstance(progid, NULL, CLSCTX_ALL);
        }

        void CreateInstance(REFCLSID rclsid,LPUNKNOWN pouter,DWORD cls_context)
        {
            if (valid())
            {
                throw gcnew System::InvalidOperationException("COM::ptr.CreateInstance");
            }

            _interface_type * interface_ptr = NULL;

            System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(CoCreateInstance(
                        rclsid, pouter, cls_context, __uuidof(_interface_type),
                        (void**)&interface_ptr));

            if (interface_ptr)
            {
                assign(interface_ptr);
                interface_ptr->Release();
            }
        }

        void CreateInstance(REFCLSID rclsid,LPUNKNOWN pouter)
        {
            CreateInstance(rclsid, pouter, CLSCTX_ALL);
        }

        void CreateInstance(REFCLSID rclsid)
        {
            CreateInstance(rclsid, NULL, CLSCTX_ALL);
        }

        // Give up ownership of the interface pointer & return the
        // interface pointer
        _interface_type * Detach()
        {
            if(valid())
            {
                _interface_type * interface_ptr = GetInterface();
                destroy();
                return interface_ptr;
            }

            return NULL;
        }

        // Give up ownership of the interface pointer
        void Release()
        {
            if(valid())
            {
                destroy();
            }
        }

        // Operator ->() - to be used to call methods on the owned COM Object
        // We return a smart_com_ptr instead of an interface pointer so that
        // the reference is released automatically
        _detail::smart_com_ptr<_interface_type> operator->()
        {
            _detail::smart_com_ptr<_interface_type> interface_ptr(GetInterface());
            return interface_ptr;
        }

        // Return an interface pointer
        _interface_type * GetInterface()
        {
            if(!valid())
            {
                return NULL;
            }

            System::IntPtr iface_intptr = System::Runtime::InteropServices::Marshal::GetIUnknownForObject(obj_rcw);

            IUnknown * iunk = static_cast<IUnknown *>(static_cast<void*>(iface_intptr));

            _interface_type * interface_ptr = NULL;
            System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(iunk->QueryInterface(__uuidof(_interface_type), (void **)&interface_ptr));

            iunk->Release();

            interface_ptr->AddRef();
            System::Runtime::InteropServices::Marshal::Release(iface_intptr);

            return interface_ptr;
        }

        // QueryInteface & fillup up the passed it COM::ptr with the result
        template<class _other_type>
        void QueryInterface(ptr<_other_type> % other)
        {
            QueryInterface<_other_type>(__uuidof(_other_type), other);
        }

        // for use when com::ptr appears in a conditional
        operator _detail_class::_safe_bool()
        {
            return valid() ? _detail_class::_safe_true : _detail_class::_safe_false;
        }

        // for use when com::ptr appears in a conditional
        bool operator!()
        {
            return ! valid();
        }

        ~ptr()
        {
            if(valid())
            {
                destroy();
            }
        }

        private:

        void destroy()
        {
            System::Runtime::InteropServices::Marshal::ReleaseComObject(obj_rcw);
            obj_rcw = nullptr;
        }

        bool valid()
        {
            return (obj_rcw != nullptr);
        }


        void assign(_interface_type *p)
        {
            if(p)
            {
                obj_rcw = System::Runtime::InteropServices::Marshal::GetUniqueObjectForIUnknown(System::IntPtr(p));
            }
        }

        template<class _other_type>
        void QueryInterface(REFIID riid, ptr<_other_type> % other)
        {
            _detail::smart_com_ptr<_interface_type> interface_ptr(GetInterface());
            _other_type * other_ptr = NULL;

            System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(interface_ptr->QueryInterface(riid,(void **)&other_ptr));
            other.Attach(other_ptr);

            other_ptr->Release();
        }

        Object ^obj_rcw;
    };
} // namespace com

} // namespace msclr

#define _INC_MSCLR_COM_PTR
#endif  /* !defined (_INC_MSCLR_COM_PTR) */
