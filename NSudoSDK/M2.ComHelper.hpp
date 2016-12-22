#pragma once

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#endif

namespace M2
{

#define COM_INTERFACE_ENTRY(Interface) \
	if (__uuidof(Interface) == riid) \
	{ \
		*ppvObject = (Interface*)this; \
		AddRef(); \
		return S_OK; \
	}

#define COM_INTERFACE_MAP_BEGIN \
	__forceinline HRESULT InternalQueryInterface( \
		REFIID riid, \
		void __RPC_FAR *__RPC_FAR *ppvObject) \
	{

#define COM_INTERFACE_MAP_END \
	COM_INTERFACE_ENTRY(IUnknown); \
	return E_NOINTERFACE; \
	}

	// 单线程COM对象模板类
	template <class BaseClass, class Interface>
	class CComObject : public Interface
	{
	private:
		ULONG m_ulRef;

	public:
		// 构造函数
		CComObject() :m_ulRef(1)
		{
		}

		// 析构函数
		virtual ~CComObject()
		{
		}

		// 查询接口
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(
			REFIID riid,
			void __RPC_FAR *__RPC_FAR *ppvObject)
		{
			return ((BaseClass*)this)->InternalQueryInterface(riid, ppvObject);
		}

		// 增加引用计数
		virtual ULONG STDMETHODCALLTYPE AddRef()
		{
			return InterlockedIncrement(&m_ulRef);
		}

		// 释放引用计数
		virtual ULONG STDMETHODCALLTYPE Release()
		{
			ULONG dwRet = InterlockedDecrement(&m_ulRef);

			// 如果释放计数后等于0释放自身
			if (dwRet == 0) 
				delete (BaseClass*)this;

			// 否则返回当前计数
			return dwRet;
		}
	};
}

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif