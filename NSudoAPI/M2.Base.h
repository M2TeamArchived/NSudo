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
        /**
         * Base class to implement IUnknown. You can choose to derive your COM
         * classes from this class, or simply implement IUnknown in each of
         * your classes.
         */
        class CUnknown : public IUnknown
        {

            /*
             * Private data members and methods. These are only accessible by
             * the methods of this class.
             */
        private:

            /*
             * The reference count for this object. Initialized to 1 in the
             * constructor.
             */
            LONG m_ReferenceCount;


            /*
             * Protected data members and methods. These are accessible by the
             * subclasses but not by other classes.
             */
        protected:

            /**
             * Constructor for an instance of the CUnknown class. This simply
             * initializes the reference count of the object to 1. The caller
             * is expected to call Release() if it wants to delete the object
             * once it has been allocated.
             *
             * @remark The constructor is protected to ensure that only the
             *         subclasses of CUnknown can create and destroy instances.
             */
            CUnknown();

            /**
             * The destructor MUST be virtual. Since any instance of a CUnknown
             * derived class should only be deleted from within the Release
             * method of CUnknown class, the destructor MUST be virtual or only
             * CUnknown::~CUnknown will get invoked on deletion.
             *
             * @remark The destructor is protected to ensure that only the
             *         subclasses of CUnknown can create and destroy instances.
             */
            virtual ~CUnknown() = default;

            /*
             * Public Methods. These are accessible by any class.
             */
        public:

            /**
             * This helper method references the object and returns a pointer
             * to the object's IUnknown interface. This allows other methods to
             * convert a CUnknown pointer into an IUnknown pointer without a
             * typecast and without calling QueryInterface and dealing with the
             * return value.
             *
             * @return A pointer to the object's IUnknown interface.
             */
            IUnknown* QueryIUnknown();


            /*
             * COM IUnknown interface methods.
             */
        public:

            /**
             * This method adds one to the object's reference count.
             *
             * @return The new reference count. The caller should only use this
             *         for debugging as the object's actual reference count can
             *         change while the caller examines the return value.
             */
            virtual ULONG STDMETHODCALLTYPE AddRef();

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
            virtual ULONG STDMETHODCALLTYPE Release();

            /**
             * This method provides the basic support for query interface on
             * CUnknown. If the interface requested is IUnknown it references
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
                _Out_ PVOID* Object);

        };
    }
}

#endif
