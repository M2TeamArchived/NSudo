/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoEnableMicrosoftUpdate.cpp
 * PURPOSE:   Implementation for Enable Microsoft Update
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <NSudoContext.h>

#include <Mile.Windows.h>

#include <wuapi.h>

EXTERN_C HRESULT WINAPI MoEnableMicrosoftUpdate(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = ::CoInitializeEx(
        nullptr,
        COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (hr.IsSucceeded())
    {
        IUpdateServiceManager2* pUpdateServiceManager2 = nullptr;

        hr = ::CoCreateInstance(
            CLSID_UpdateServiceManager,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_IUpdateServiceManager2,
            reinterpret_cast<LPVOID*>(&pUpdateServiceManager2));
        if (hr.IsSucceeded())
        {
            BSTR ClientApplicationID = ::SysAllocString(L"My App");
            if (ClientApplicationID)
            {
                hr = pUpdateServiceManager2->put_ClientApplicationID(
                    ClientApplicationID);

                ::SysFreeString(ClientApplicationID);
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }

            if (hr.IsSucceeded())
            {
                BSTR serviceID = ::SysAllocString(
                    L"7971f918-a847-4430-9279-4a52d1efe18d");
                BSTR authorizationCabPath = ::SysAllocString(L"");
                if (serviceID && authorizationCabPath)
                {
                    DWORD flags = 0x0;
                    flags |= AddServiceFlag::asfAllowPendingRegistration;
                    flags |= AddServiceFlag::asfAllowOnlineRegistration;
                    flags |= AddServiceFlag::asfRegisterServiceWithAU;

                    IUpdateServiceRegistration* pResult = nullptr;

                    hr = pUpdateServiceManager2->AddService2(
                        serviceID,
                        flags,
                        authorizationCabPath,
                        &pResult);

                    ::SysFreeString(serviceID);
                    ::SysFreeString(authorizationCabPath);
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                }
            }
        }

        ::CoUninitialize();
    }

    Context->WriteLine(
        Context,
        Mile::GetHResultMessage(hr).c_str());

    return hr;
}
