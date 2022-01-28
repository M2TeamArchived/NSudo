/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoQueryLicenseInformation.cpp
 * PURPOSE:   Implementation for Query License Information
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <WbemIdl.h>
#pragma comment(lib, "wbemuuid.lib")

EXTERN_C HRESULT WINAPI MoQueryLicenseInformation(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = ::CoInitializeEx(
        nullptr,
        COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (hr.IsSucceeded())
    {
        hr = ::CoInitializeSecurity(
            nullptr,
            -1,
            nullptr,
            nullptr,
            RPC_C_AUTHN_LEVEL_DEFAULT,
            RPC_C_IMP_LEVEL_IMPERSONATE,
            nullptr,
            EOAC_NONE,
            nullptr);
        if (hr.IsSucceeded())
        {
            IWbemLocator* pWbemLocator = nullptr;
            hr = ::CoCreateInstance(
                CLSID_WbemLocator,
                nullptr,
                CLSCTX_INPROC_SERVER,
                IID_IWbemLocator,
                reinterpret_cast<LPVOID*>(&pWbemLocator));
            if (hr.IsSucceeded())
            {
                /*Result += L"TinyMSLicenseViewer " PROJECT_VERSION_STRING "\r\n";
                Result += L"\xA9 M2-Team. All rights reserved.\r\n\r\n";
                Result += L"========以下是本机上微软产品的授权情况========\r\n";
                Result += L"\r\n";


                IWbemServices* pWbemServices = nullptr;
                hr = pWbemLocator->ConnectServer(
                    L"root\\CIMV2",
                    nullptr,
                    nullptr,
                    nullptr,
                    0,
                    nullptr,
                    nullptr,
                    &pWbemServices);
                if (hr.IsSucceeded())
                {

                }
                else
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"CoCreateInstance");
                }


                const wchar_t* strQuery[2] =
                {
                    L"SELECT * FROM SoftwareLicensingProduct WHERE PartialProductKey <> null",
                    L"SELECT * FROM OfficeSoftwareProtectionProduct WHERE PartialProductKey <> null"
                };

                const wchar_t* LicenseStatusText[7] =
                {
                    L"未经授权",
                    L"已授权",
                    L"初始宽限期",
                    L"附加宽限期(KMS 许可证过期或硬件超出允许期限)",
                    L"非正版宽限期",
                    L"通知",
                    L"延长的宽限期"
                };

                hr = CoSetProxyBlanket(
                    WbemServices,
                    RPC_C_AUTHN_WINNT,
                    RPC_C_AUTHZ_NONE,
                    nullptr,
                    RPC_C_AUTHN_LEVEL_CALL,
                    RPC_C_IMP_LEVEL_IMPERSONATE,
                    nullptr,
                    EOAC_NONE);
                if (FAILED(hr)) return hr;

                for (size_t i = 0; i < sizeof(QuerySource) / sizeof(*QuerySource); ++i)
                {
                    std::wstring QueryString;

                    QueryString += L"SELECT * FROM ";
                    QueryString += std::wstring(QuerySource[i]);
                    QueryString += L" WHERE PartialProductKey <> null";

                    M2::CComObject<IEnumWbemClassObject*> SLPEnumerator;

                    hr = WbemServices->ExecQuery(
                        L"WQL",
                        const_cast<BSTR>(QueryString.c_str()),
                        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                        nullptr,
                        &SLPEnumerator);
                    if (FAILED(hr)) continue;

                    for (;;)
                    {
                        M2::CComObject<IWbemClassObject*> SLPClassObject;
                        ULONG uReturn = 0;
                        VARIANT vtDescription, vtLicenseStatus;

                        SLPEnumerator->Next(
                            WBEM_INFINITE,
                            1,
                            &SLPClassObject,
                            &uReturn);

                        if (0 == uReturn) break;

                        SLPClassObject->Get(
                            L"Name",
                            0,
                            &vtDescription,
                            nullptr,
                            nullptr);
                        SLPClassObject->Get(
                            L"LicenseStatus",
                            0,
                            &vtLicenseStatus,
                            nullptr,
                            nullptr);


                        Result += vtDescription.bstrVal;
                        Result += L"\r\n";
                        Result += LicenseStatusText[vtLicenseStatus.lVal];
                        Result += L"\r\n";
                        Result += L"\r\n";

                        VariantClear(&vtDescription);
                        VariantClear(&vtLicenseStatus);
                    }
                }*/

            }
            else
            {
                ::MoPrivateWriteErrorMessage(
                    Context,
                    hr,
                    L"CoCreateInstance");
            }
        }
        else
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"CoInitializeSecurity");
        }

        ::CoUninitialize();
    }
    else
    {
        ::MoPrivateWriteErrorMessage(
            Context,
            hr,
            L"CoInitializeEx");
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
