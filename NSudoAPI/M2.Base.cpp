/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2.Base.cpp
 * PURPOSE:   Implementation for M2-Team Common Library Base C++ Wrapper
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "M2.Base.h"

 /**
  * @remark You can read the definition for this function in "M2.Base.h".
  */
M2::Base::CUnknown::CUnknown()
    : m_ReferenceCount(1)
{
    // Do nothing.
}

/**
 * @remark You can read the definition for this function in "M2.Base.h".
 */
IUnknown* M2::Base::CUnknown::QueryIUnknown()
{
    this->AddRef();
    return static_cast<IUnknown*>(this);
}

/**
 * @remark You can read the definition for this function in "M2.Base.h".
 */
ULONG STDMETHODCALLTYPE M2::Base::CUnknown::AddRef()
{
    return ::InterlockedIncrement(&this->m_ReferenceCount);
}

/**
 * @remark You can read the definition for this function in "M2.Base.h".
 */
ULONG STDMETHODCALLTYPE M2::Base::CUnknown::Release()
{
    ULONG count = ::InterlockedDecrement(&this->m_ReferenceCount);

    if (count == 0)
    {
        delete this;
    }

    return count;
}

/**
 * @remark You can read the definition for this function in "M2.Base.h".
 */
HRESULT STDMETHODCALLTYPE M2::Base::CUnknown::QueryInterface(
    _In_ REFIID InterfaceId,
    _Out_ PVOID* Object)
{
    if (::IsEqualIID(InterfaceId, __uuidof(IUnknown)))
    {
        *Object = this->QueryIUnknown();
        return S_OK;
    }
    else
    {
        *Object = nullptr;
        return E_NOINTERFACE;
    }
}
