/***
*event.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   delegate_proxy_factory class
*
*       [Public]
*
****/

#pragma once

#ifndef __cplusplus_cli
#error ERROR: msclr libraries are not compatible with /clr:oldSyntax
#endif  /* __cplusplus_cli */

#include <gcroot.h>

namespace msclr {
    namespace delegate_map {
        namespace internal {

        template <typename CLASS> class delegate_proxy_factory
        {
            typedef typename CLASS::delegate_proxy_type proxy_type;
            gcroot<proxy_type^> m_gc_managed_native_delegate_proxy;

            public:
            delegate_proxy_factory() {}

            virtual ~delegate_proxy_factory()
            {
                if((proxy_type^)m_gc_managed_native_delegate_proxy != nullptr)
                {
                    m_gc_managed_native_delegate_proxy->detach();
                }
            }

            proxy_type^ get_proxy(CLASS* pNativeTarget)
            {
                if((proxy_type^)m_gc_managed_native_delegate_proxy == nullptr)
                {
                    m_gc_managed_native_delegate_proxy = gcnew proxy_type(pNativeTarget);
                }
                return (proxy_type^)m_gc_managed_native_delegate_proxy;
            }
        };

        }
    }
}


#define BEGIN_DELEGATE_MAP(CLASS)\
        ref class delegate_proxy_type;\
        msclr::delegate_map::internal::delegate_proxy_factory<CLASS> m_delegate_map_proxy;\
        \
        ref class delegate_proxy_type\
        {\
                CLASS* m_p_native_target;\
        public:\
                delegate_proxy_type(CLASS* pNativeTarget) : m_p_native_target(pNativeTarget) {}\
                void detach() { m_p_native_target = NULL; }

#define EVENT_DELEGATE_ENTRY(MEMBER,ARG0,ARG1)\
        void MEMBER(ARG0 arg0,ARG1 arg1)\
        {\
                if(m_p_native_target == NULL)\
                throw gcnew System::ArgumentNullException("Delegate call failed: Native sink was not attached or has already detached from the managed proxy (m_p_native_target == NULL). Hint: see if native sink was destructed or not constructed properly");\
                \
                m_p_native_target->MEMBER(arg0,arg1);\
        }

#define END_DELEGATE_MAP()\
        };

#define MAKE_DELEGATE(DELEGATE,MEMBER)\
        gcnew DELEGATE(m_delegate_map_proxy.get_proxy(this),&delegate_proxy_type::MEMBER)
