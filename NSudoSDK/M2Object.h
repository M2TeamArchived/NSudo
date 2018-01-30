/******************************************************************************
Project: M2-Team Common Library
Description: Definition for the M2::CObject class
File Name: M2Object.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_OBJECT_
#define _M2_OBJECT_

#include <Windows.h>

namespace M2
{
	// The implementation of smart object.
	template<typename TObject, typename TObjectDefiner>
	class CObject
	{
	protected:
		TObject m_Object;
	public:
		CObject(TObject Object = TObjectDefiner::GetInvalidValue()) : 
			m_Object(Object)
		{

		}

		~CObject()
		{
			this->Close();
		}

		TObject* operator&()
		{
			return &this->m_Object;
		}

		TObject operator=(TObject Object)
		{
			if (Object != this->m_Object)
			{
				this->Close();
				this->m_Object = Object;
			}
			return (this->m_Object);
		}

		operator TObject()
		{
			return this->m_Object;
		}

		// Check the object is vaild or not.
		bool IsInvalid()
		{
			return (this->m_Object == TObjectDefiner::GetInvalidValue());
		}

		// Detach the object.
		TObject Detach()
		{
			TObject Object = this->m_Object;
			this->m_Object = TObjectDefiner::GetInvalidValue();
			return Object;
		}

		// Close the object.
		void Close()
		{
			if (!this->IsInvalid())
			{
				TObjectDefiner::Close(this->m_Object);
				this->m_Object = TObjectDefiner::GetInvalidValue();
			}
		}

		TObject operator->() const
		{
			return this->m_Object;
		}
	};

	// The handle definer for HANDLE object.
	struct CHandleDefiner
	{
		static inline HANDLE GetInvalidValue()
		{
			return INVALID_HANDLE_VALUE;
		}

		static inline void Close(HANDLE Object)
		{
			CloseHandle(Object);
		}
	};

	typedef CObject<HANDLE, CHandleDefiner> CHandle;

	// The handle definer for Com object.
	template<typename TComObject>
	struct CComObjectDefiner
	{
		static inline TComObject GetInvalidValue()
		{
			return nullptr;
		}

		static inline void Close(TComObject Object)
		{
			Object->Release();
		}
	};

	template<typename TComObject>
	class CComObject : public CObject<TComObject, CComObjectDefiner<TComObject>>
	{

	};
}

#endif // _M2_OBJECT_
