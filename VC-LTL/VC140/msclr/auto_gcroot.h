/***
*auto_gcroot.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   automatic resource management, like std::auto_ptr which can be used
*           to embed a virtual handle into a native type
*
*       [Public]
*
****/

#pragma once

#if !defined (_INC_MSCLR_AUTO_GCROOT)

#ifndef __cplusplus_cli
#error ERROR: msclr libraries are not compatible with /clr:oldSyntax
#endif  /* __cplusplus_cli */

#include <vcclr.h>
#include <msclr\safebool.h>
#include <algorithm>

namespace msclr
{

// Forward Declaration
template<typename _element_type>
class auto_gcroot;

namespace _detail
{

// _auto_gcroot_ref is a proxy reference for auto_gcroot copying.
// auto_gcroot's copy constructor takes a non-const reference
// because it must assume ownership from the source. But this
// makes it impossible for auto_gcroot to be returned by value,
// because temporary objects cannot be bound to non-const
// references. Instead, a conversion to _auto_gcroot_ref is provided,
// and an auto_gcroot can be initialized from an _auto_gcroot_ref.

    template<typename _element_type>
    struct _auto_gcroot_ref
    {
        // construct from compatible auto_gcroot
        _auto_gcroot_ref( auto_gcroot<_element_type> & ref )
            : m_ref( ref )
        {
        }

        // reference to constructor argument
        auto_gcroot<_element_type> & m_ref;

    };

} // namespace detail

// wrap a resource to enforce strict ownership and ensure proper cleanup
template<typename _element_type>
class auto_gcroot
{
private:
    // disallow explicit comparisons to _safe_bool
    bool operator==( _detail_class::_safe_bool ) const;
    bool operator!=( _detail_class::_safe_bool ) const;

public:

    // Constructors

    // construct from object pointer
    auto_gcroot( _element_type _ptr = nullptr )
        : m_ptr( _ptr )
    {
    }

    // construct by assuming pointer from _right auto_gcroot
    auto_gcroot( auto_gcroot<_element_type> & _right )
            : m_ptr( _right.release() )
    {
    }

    // construct by assuming pointer from _right _detail::_auto_gcroot_ref
    auto_gcroot( _detail::_auto_gcroot_ref<_element_type> _right )
        : m_ptr( _right.m_ref.release() )
    {
    }

    template<typename _other_type>
    auto_gcroot( auto_gcroot<_other_type> & _right )
        : m_ptr( _right.release() )
    {
    }

    auto_gcroot<_element_type> & attach(_element_type _right)
    {
        reset(_right);
        return *this;
    }

    // assign compatible _right
    auto_gcroot<_element_type> & attach(
        auto_gcroot<_element_type> & _right )
    {
        reset( _right.release() );
        return *this;
    }

    // assign compatible _right.ref
    auto_gcroot<_element_type> & attach(
        _detail::_auto_gcroot_ref<_element_type> & _right )
    {
        reset( _right.m_ref.release() );
        return *this;
    }

    template<typename _other_type>
    auto_gcroot<_element_type> & attach(
    auto_gcroot<_other_type> & _right )
    {
        reset( _right.release() );
        return *this;
    }

    auto_gcroot<_element_type> & operator=(_element_type _right)
    {
        return attach(_right);
    }

    // assign compatible _right
    auto_gcroot<_element_type> & operator=(
        auto_gcroot<_element_type> & _right )
    {
        return attach(_right);
    }

    // assign compatible _right.ref
    auto_gcroot<_element_type> & operator=(
        _detail::_auto_gcroot_ref<_element_type> & _right )
    {
        return attach(_right);
    }

    template<typename _other_type>
    auto_gcroot<_element_type> & operator=(
    auto_gcroot<_other_type> & _right )
    {
        return attach(_right);
    }

    _element_type get() const
    {
        return m_ptr;
    }

    // return pointer to class object (assume pointer)
    _element_type operator->() const
    {
        return m_ptr;
    }

    // for use when auto_gcroot appears in a conditional
    operator _detail_class::_safe_bool() const
    {
        return valid() ? _detail_class::_safe_true : _detail_class::_safe_false;
    }

    // for use when auto_gcroot appears in a conditional
    bool operator!() const
    {
        return ! valid();
    }

    // convert to compatible _detail::_auto_gcroot_ref
    operator _detail::_auto_gcroot_ref<_element_type>()
    {
        return _detail::_auto_gcroot_ref<_element_type>( *this );
    }

    template<typename _other_type>
    operator auto_gcroot<_other_type>()
    {
        return auto_gcroot<_other_type>( *this );
    }

    template<typename _other_type>
    operator _detail::_auto_gcroot_ref<_other_type>()
    {
        return _detail::_auto_gcroot_ref<_other_type>( *this );
    }

    void swap( auto_gcroot<_element_type> & _right )
    {
        m_ptr.swap( _right.m_ptr );
    }

    void reset( _element_type _new_ptr = nullptr )
    {
        if( _element_type(m_ptr) != _new_ptr )
        {
            if( valid() )
            {
                delete _element_type(m_ptr);
            }
            m_ptr = _new_ptr;
        }
    }

    _element_type release()
    {
        _element_type _tmp_ptr = m_ptr;
        m_ptr = nullptr;
        return _tmp_ptr;
    }

    // destroy the object
    ~auto_gcroot()
    {
        if( valid() )
        {
            delete _element_type(m_ptr);
        }
    }

private:

    bool valid() const
    {
        // see if the managed resource is in the invalid state.
        return _element_type(m_ptr) != nullptr;
    }

    // the wrapped object
    gcroot<_element_type> m_ptr;
};

// swap the contents of two auto_gcroot objects
template<typename _element_type>
void swap( auto_gcroot<_element_type> & _left,
           auto_gcroot<_element_type> & _right )
{
    _left.swap( _right );
}

} // namespace msclr

#define _INC_MSCLR_AUTO_GCROOT

#endif  /* !defined (_INC_MSCLR_AUTO_GCROOT) */
