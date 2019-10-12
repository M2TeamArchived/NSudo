/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2.Base.h
 * PURPOSE:   Definition for M2-Team Common Library Base C++ Wrapper
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef M2_BASE
#define M2_BASE

#ifndef __cplusplus
#error "[M2.NSudo] You should use a C++ compiler."
#endif

#include <Windows.h>

namespace M2
{
    namespace Base
    {
        //*************************************************************************
    // COM对象模板
    // COM Object Template
    //*************************************************************************

#define M2_BASE_COM_INTERFACE_ENTRY(Interface) \
	if (::IsEqualIID(InterfaceId, __uuidof(Interface))) \
	{ \
        this->AddRef(); \
		*Object = static_cast<Interface*>(this); \
		return S_OK; \
	}

#define M2_BASE_COM_INTERFACE_MAP_BEGIN \
	FORCEINLINE HRESULT InternalQueryInterface( \
		_In_ REFIID InterfaceId, \
        _Out_ PVOID* Object) \
	{

#define M2_BASE_COM_INTERFACE_MAP_END \
	M2_BASE_COM_INTERFACE_ENTRY(IUnknown); \
    \
    *Object = nullptr; \
	return E_NOINTERFACE; \
	}

        /**
         * Base class to implement IUnknown. You can choose to derive your COM
         * classes from this class, or simply implement IUnknown in each of
         * your classes.
         */
        template <class TBaseClass, class TInterface>
        class CComClass : public TInterface
        {
        private:

            /*
             * The reference count for this object. Initialized to 1 in the
             * constructor.
             */
            LONG m_ReferenceCount;

        public:

            /**
             * Constructor for an instance of the CComClass class. This simply
             * initializes the reference count of the object to 1. The caller
             * is expected to call Release() if it wants to delete the object
             * once it has been allocated.
             *
             * @remark The constructor is protected to ensure that only the
             *         subclasses of CComClass can create and destroy instances.
             */
            CComClass() :
                m_ReferenceCount(1)
            {
            }

            /**
             * The destructor MUST be virtual. Since any instance of a CComClass
             * derived class should only be deleted from within the Release
             * method of CComClass class, the destructor MUST be virtual or only
             * CComClass::~CComClass will get invoked on deletion.
             *
             * @remark The destructor is protected to ensure that only the
             *         subclasses of CComClass can create and destroy instances.
             */
            virtual ~CComClass() = default;

            /**
             * This method provides the basic support for query interface on
             * CComClass. If the interface requested is IUnknown it references
             * the object and returns an interface pointer. Otherwise it
             * returns an error.
             *
             * @param InterfaceId The IID being requested.
             * @param Object A location to store the interface pointer to
             *               return.
             * @return S_OK or E_NOINTERFACE.
             */
            virtual HRESULT STDMETHODCALLTYPE QueryInterface(
                _In_ REFIID InterfaceId,
                _Out_ PVOID* Object)
            {
                return static_cast<TBaseClass*>(this)->InternalQueryInterface(
                    InterfaceId, Object);
            }

            /**
             * This method adds one to the object's reference count.
             *
             * @return The new reference count. The caller should only use this
             *         for debugging as the object's actual reference count can
             *         change while the caller examines the return value.
             */
            virtual ULONG STDMETHODCALLTYPE AddRef()
            {
                return ::InterlockedIncrement(&this->m_ReferenceCount);
            }

            /**
             * This method subtracts one to the object's reference count. If
             * the count goes to zero, this method deletes the object.
             *
             * @return The new reference count. If the caller uses this value
             *         it should only be to check for zero (i.e. this call
             *         caused or will cause deletion) or non-zero (i.e. some
             *         other call may have caused deletion, but this one
             *         didn't).
             */
            virtual ULONG STDMETHODCALLTYPE Release()
            {
                ULONG Count = ::InterlockedDecrement(&this->m_ReferenceCount);

                if (Count == 0)
                {
                    delete this;
                }

                return Count;
            }
        };
    }
}

#endif
