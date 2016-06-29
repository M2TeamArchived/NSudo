/***
*marshal.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   Marshalling classes
*
*       [Public]
*
****/

#pragma once

#ifndef _INC_MSCLR_MARSHAL
#define _INC_MSCLR_MARSHAL

#using <system.dll>

#include <sal.h>
#include <windows.h>
#include <vcclr.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <memory>

#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "oleaut32.lib")

#pragma warning(push)
#pragma warning(error : 4996)

namespace msclr{
        namespace interop{

namespace details
{
#define _EXCEPTION_GREATER_THAN_INT_MAX "Size of string exceeds INT_MAX."
#define _EXCEPTION_NULLPTR "NULLPTR is not supported for this conversion."
#define _EXCEPTION_MB2WC "Conversion from MultiByte to WideChar failed.  Please check the content of the string and/or locale settings."
#define _EXCEPTION_WC2MB "Conversion from WideChar to MultiByte failed.  Please check the content of the string and/or locale settings."

        // helper class to allocate/deallocate a buffer with new[]/delete[]
        template <class T>
        class char_buffer
        {
        public:
                explicit char_buffer(size_t _size)
                {
                        _ptr = new T[_size];
                }

                ~char_buffer()
                {
                        delete [] _ptr;
                }

                T *get() const
                {
                        return _ptr;
                }

                T* release()
                {
                        T *_ret_value = _ptr;
                        _ptr = NULL;
                        return _ret_value;
                }

        private:
                // no copy constructor nor operator=
                char_buffer(const char_buffer&);
                char_buffer& operator=(const char_buffer&);

                T *_ptr;
        };

        inline _Check_return_ size_t GetAnsiStringSize(System::String^ _str)
        {
                size_t _size = 0;
                cli::pin_ptr<const wchar_t> _pinned_ptr = PtrToStringChars(_str);

                _size = ::WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, _pinned_ptr, _str->Length, NULL, 0, NULL,NULL);
                if (_size == 0 && _str->Length != 0)
                {
                        throw gcnew System::ArgumentException(_EXCEPTION_WC2MB);
                }
                // adding 1 for terminating nul
                _size+=1;
                return _size;
        }

        inline void WriteAnsiString(_Out_writes_all_(_size) _Post_z_ char* _buf, size_t _size, System::String^ _str)
        {
                cli::pin_ptr<const wchar_t> _pinned_ptr = PtrToStringChars(_str);

                //checking for overflow
                if (_size > INT_MAX)
                {
                        // this should never happen if _size was returned by GetAnsiStringSize()
                        throw gcnew System::ArgumentOutOfRangeException(_EXCEPTION_GREATER_THAN_INT_MAX);
                }
                size_t _written = ::WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, _pinned_ptr, _str->Length, _buf, static_cast<int>(_size) ,NULL,NULL);
                if( _written >= _size ||
                                (_written == 0 && _size != 1)) // allowing empty string
                {
                        throw gcnew System::ArgumentException(_EXCEPTION_WC2MB);
                }
                _buf[_written] = '\0';
        }

        inline _Check_return_ size_t GetUnicodeStringSize(_In_reads_z_(_count+1) const char* _str, size_t _count)
        {
                size_t _size = 0;
                if (_count > INT_MAX)
                {
                        throw gcnew System::ArgumentOutOfRangeException(_EXCEPTION_GREATER_THAN_INT_MAX);
                }
                _size = ::MultiByteToWideChar(CP_THREAD_ACP, 0, _str, static_cast<int>(_count), NULL, 0);

                if (_size == 0 && _count != 0)
                {
                        throw gcnew System::ArgumentException(_EXCEPTION_MB2WC);
                }
                //adding 1 for terminating nul
                _size+=1;
                return _size;
        }

        inline void WriteUnicodeString(_Out_writes_all_(_size) _Post_z_ wchar_t* _dest, size_t _size, _In_reads_bytes_(_count)const char* _src, size_t _count)
        {
                //checking for overflow
                if (_size > INT_MAX || _count > INT_MAX)
                {
                        throw gcnew System::ArgumentOutOfRangeException(_EXCEPTION_GREATER_THAN_INT_MAX);
                }

                size_t _written = ::MultiByteToWideChar(CP_THREAD_ACP, 0, _src, static_cast<int>(_count), _dest, static_cast<int>(_size));
                if( _written >= _size ||
                                (_written == 0 && _size != 1)) // allowing empty string
                {
                        throw gcnew System::ArgumentException(_EXCEPTION_MB2WC);
                }
                _dest[_written] = L'\0';
        }

        inline System::String^ InternalAnsiToStringHelper(_In_reads_z_(_count+1)const char* _src, size_t _count)
        {
                size_t _size = details::GetUnicodeStringSize(_src, _count);
                if (_size > INT_MAX || _size <=0 )
                {
                        throw gcnew System::ArgumentOutOfRangeException(_EXCEPTION_GREATER_THAN_INT_MAX);
                }
                details::char_buffer<wchar_t> _wchar_buf(_size);
                if (_wchar_buf.get() == NULL)
                {
                        throw gcnew System::InsufficientMemoryException();
                }

                details::WriteUnicodeString(_wchar_buf.get(), _size, _src, _count);

                return gcnew System::String(_wchar_buf.get(), 0, static_cast<int>(_size)-1);
        }

        inline System::String^ InternalUnicodeToStringHelper(_In_reads_z_(_count+1)const wchar_t* _src, size_t _count)
        {
                if (_count > INT_MAX)
                {
                        throw gcnew System::ArgumentOutOfRangeException(_EXCEPTION_GREATER_THAN_INT_MAX);
                }

                return gcnew System::String(_src, 0 ,static_cast<int>(_count));
        }
} // namespace details

//--------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------

template <class _To_Type, class _From_Type,
         bool _Needs_Context = context_node<_To_Type,_From_Type>::_Needs_Context>
class error_reporting_helper;

ref class context_node_base;

template<class _To_Type>
inline _To_Type marshal_as(_In_z_ const char  _from_object[])
{
        const char* _ptr = _from_object;
        return marshal_as<_To_Type, const char *>(_ptr);
}

template<class _To_Type>
inline _To_Type marshal_as(_In_z_ const wchar_t  _from_object[])
{
        const wchar_t* _ptr = _from_object;
        return marshal_as<_To_Type, const wchar_t*>(_ptr);
}

template<class _To_Type, class _From_Type>
ref class context_node;

ref class marshal_context;

template <class _To_Type, class _From_Type>
inline _To_Type marshal_as(const _From_Type&);

//--------------------------------------------------------------------------------
// Context-free conversion generic templates
//--------------------------------------------------------------------------------

template <class _To_Type, class _From_Type>
class error_reporting_helper<_To_Type, _From_Type, /* _Needs_Context */ false>
{
        public:
                __declspec(deprecated("This conversion is not supported by the library or the header file needed for this conversion is not included.  Please refer to the documentation on 'How to: Extend the Marshaling Library' for adding your own marshaling method."))
                static _To_Type marshal_as(const _From_Type& _from_object)
                {
                        return _This_conversion_is_not_supported;
                }
};

template <class _To_Type, class _From_Type>
class error_reporting_helper<_To_Type, _From_Type, /* _Needs_Context */ true>
{
        public:
                __declspec(deprecated("This conversion requires a marshal_context.  Please use a marshal_context for this conversion."))
                static _To_Type marshal_as(const _From_Type& _from_object)
                {
                        return _This_conversion_requires_a_context;
                }
};

template <class _To_Type, class _From_Type>
inline _To_Type marshal_as(const _From_Type& _from_object)
{
        return error_reporting_helper<_To_Type, _From_Type>::marshal_as(_from_object);
}

//--------------------------------------------------------------------------------
// Context conversion generic templates
//--------------------------------------------------------------------------------

ref class context_node_base
{
        public:
                static const bool _Needs_Context= true;
};

template<class _To_Type, class _From_Type>
ref class context_node : public context_node_base
{
        public:
                static const bool _Needs_Context= false;
};

ref class marshal_context
{
        internal:
                //The list of objects that need to be cleaned up. Basically all those that have a destructor
                System::Collections::Generic::LinkedList <Object^> _clean_up_list;

                template<class _To_Type, class _From_Type, bool _Needs_Context>
                ref class internal_marshaler;

                template<class _To_Type, class _From_Type>
                ref class internal_marshaler<_To_Type, _From_Type, true>
                {
                        public:
                        // This is a supported context conversation.
                        // Convert and added it to the list of cleanup
                        static inline _To_Type marshal_as(const _From_Type& _from, System::Collections::Generic::LinkedList<Object^>% _clean_up_list)
                        {
                                typedef context_node<_To_Type, _From_Type> _cn;

                                _To_Type _to_object;
                                //Create a context node and assign marshalling result to the 'to' variable
                                _cn^ _obj = gcnew _cn(_to_object, _from);
                                _clean_up_list.AddLast(_obj);
                                return _to_object;
                        };
                };

                template<class _To_Type, class _From_Type>
                ref class internal_marshaler<_To_Type, _From_Type, false>
                {
                        public:
                        // This is not a supported context conversation.
                        // This maybe a context-free conversation or a unsupported converstaion.
                        // Both cases will be handed by the Marshal_as object.
                        static inline _To_Type marshal_as(const _From_Type& _from, System::Collections::Generic::LinkedList<Object^>% _clean_up_list)
                        {
                                (_clean_up_list); // not using this variable intentionally
                                return ::msclr::interop::marshal_as<_To_Type, _From_Type>(_from);
                        };
                };

        public:
                template<class _To_Type, class _From_Type>
                inline _To_Type marshal_as(const _From_Type& _from)
                {
                        typedef context_node<_To_Type, _From_Type> _cn;
                        return internal_marshaler<_To_Type, _From_Type, _cn::_Needs_Context>::marshal_as(_from, _clean_up_list);
                }

                template<class _To_Type, class _From_Type>
                inline _To_Type marshal_as(_From_Type^ _from)
                {
                        typedef context_node<_To_Type, _From_Type^> _cn;
                        return internal_marshaler<_To_Type, _From_Type^, _cn::_Needs_Context>::marshal_as(_from, _clean_up_list);
                }

                // special case marshal_as() that doesn't fit the usual marshal_as<To,From>() templates
                template<class _To_Type>
                inline _To_Type marshal_as(_In_z_ const char _from[])
                {
                        typedef context_node<_To_Type, const char *> _cn;
                        return internal_marshaler<_To_Type, const char*, _cn::_Needs_Context>::marshal_as(_from, _clean_up_list);
                }

                template<class _To_Type>
                inline _To_Type marshal_as(_In_z_ const wchar_t _from[])
                {
                        typedef context_node<_To_Type, const wchar_t *> _cn;
                        return internal_marshaler<_To_Type, const wchar_t*, _cn::_Needs_Context>::marshal_as(_from, _clean_up_list);
                }

                template<class _To_Type>
                inline _To_Type marshal_as(System::IntPtr _from)
                {
                        return ::msclr::interop::marshal_as<_To_Type>(_from);
                }

        marshal_context()
        {};

        ~marshal_context()
        {
                for each(Object^ _obj in _clean_up_list)
                        delete _obj;
        }
};

//--------------------------------------------------------------------------------
// Context-free conversions templates specialization for basic types
//--------------------------------------------------------------------------------

template <>
inline System::String^ marshal_as(_In_z_ const char * const & _from_object)
{
        if (!_from_object)
        {
                return nullptr;
        }
        return details::InternalAnsiToStringHelper(_from_object, strlen(_from_object));
}

template<>
inline System::String^ marshal_as(_In_z_ char * const & _from_object)
{
        return marshal_as<System::String^, const char *>(_from_object);
}

template <>
inline System::String^ marshal_as(_In_z_ const wchar_t* const & _from_object)
{
        if (_from_object == NULL)
        {
                return nullptr;
        }
        return gcnew System::String(_from_object);
}

// Note: BSTR and wchar_t* are actually typedef alias.  Therefore, we can not define the
// conversion BSTR -> System::String^.  BSTR actually will use this function.
template <>
inline System::String^ marshal_as(_In_z_ wchar_t* const& _from_object)
{
        return marshal_as<System::String^, const wchar_t *>(_from_object);
}

//--------------------------------------------------------------------------------
// Context conversion templates specialization for basic types
//--------------------------------------------------------------------------------

template<>
ref class context_node<const char*, System::String^> :
        public context_node_base
{
        private:
                char* _ptr;
        public:
                context_node(_Outref_result_maybenull_ _Post_z_  const char*& _to_object, System::String^ _from_object)
                {
                        _ptr = NULL;
                        if (_from_object == nullptr)
                        {
                                _to_object =nullptr;
                                return;
                        }

                        size_t _size = details::GetAnsiStringSize(_from_object);

                        details::char_buffer<char> _char_buf(_size);
                        if (_char_buf.get() == NULL)
                        {
                                throw gcnew System::InsufficientMemoryException();
                        }

                        details::WriteAnsiString(_char_buf.get(), _size, _from_object);

                        _ptr = _char_buf.release();
                        _to_object = _ptr;
                }

                ~context_node()
                {
                        this->!context_node();
                }

        protected:
                !context_node()
                {
                        delete [] _ptr;
                }
};


template<>
ref class context_node<const wchar_t*, System::String^> :
        public context_node_base
{
        private:
                System::IntPtr _ip;
        public:
                context_node(_Outref_ _Post_z_  const wchar_t*& _to_object, System::String^ _from_object)
                {
                        _ip = System::Runtime::InteropServices::Marshal::StringToHGlobalUni (_from_object);
                        _to_object = static_cast<wchar_t*>(_ip.ToPointer());
                }

                ~context_node()
                {
                        this->!context_node();
                }

        protected:
                !context_node()
                {
                        if(_ip != System::IntPtr::Zero)
                                System::Runtime::InteropServices::Marshal::FreeHGlobal(_ip);
                }
};

        } //namespace interop
} //namespace msclr

#pragma warning(pop) // error:4996
#endif  /* _INC_MSCLR_MARSHAL */
