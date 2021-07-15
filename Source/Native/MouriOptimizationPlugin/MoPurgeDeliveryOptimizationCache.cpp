/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeDeliveryOptimizationCache.cpp
 * PURPOSE:   Implementation for Purge Delivery Optimization Cache
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

namespace
{
    MIDL_INTERFACE("6692fd56-3b9b-433a-ac04-3ffb442556dd")
        IDeliveryOptimizationCleanup: public IUnknown
    {
        virtual HRESULT STDMETHODCALLTYPE GetCacheSize(
            _Out_ PUINT64 CacheSize) = 0;

        virtual HRESULT STDMETHODCALLTYPE DeleteCache() = 0;
    };

    MIDL_INTERFACE("6692fd56-3b9b-433a-ac04-3ffb442556dd")
        IDeliveryOptimizationMgrInternal: public IUnknown
    {
        virtual HRESULT STDMETHODCALLTYPE SetUserToken() = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCacheSize(
            _Out_ PUINT64 CacheSize) = 0;

        virtual HRESULT STDMETHODCALLTYPE DeleteCache() = 0;

        virtual HRESULT STDMETHODCALLTYPE SetSwarmPinned(
            _In_ LPCWSTR SwarmName,
            _In_ BOOL Pinned) = 0;

        virtual HRESULT STDMETHODCALLTYPE SetExpiration(
            _In_ UINT64 ExpirationTime,
            _In_opt_ LPCWSTR SwarmName) = 0;

        virtual HRESULT STDMETHODCALLTYPE DeleteSwarms(
            _In_ LPCWSTR SwarmName,
            _In_ BOOL Forced) = 0;
    };
}

EXTERN_C HRESULT WINAPI MoPurgeDeliveryOptimizationCache(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    IUnknown* pInterface = nullptr;

    do
    {
        DWORD PurgeMode = ::MoPrivateParsePurgeMode(Context);
        if (PurgeMode == 0)
        {
            hr = Mile::HResult::FromWin32(ERROR_CANCELLED);
            break;
        }

        if (PurgeMode != MO_PRIVATE_PURGE_MODE_SCAN &&
            PurgeMode != MO_PRIVATE_PURGE_MODE_PURGE)
        {
            hr = E_NOINTERFACE;
            break;
        }

        const wchar_t DeliveryOptimizationCLSID[] =
            L"{5B99FA76-721C-423C-ADAC-56D03C8A8007}";
        const wchar_t DeliveryOptimizationIID[] =
            L"{6692FD56-3B9B-433A-AC04-3FFB442556DD}";

        hr = Mile::CoCreateInstanceByString(
            DeliveryOptimizationCLSID,
            0,
            CLSCTX_LOCAL_SERVER,
            DeliveryOptimizationIID,
            reinterpret_cast<LPVOID*>(&pInterface));
        if (hr.IsFailed())
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"Mile::CoCreateInstanceByString");
            break;
        }

        IDeliveryOptimizationCleanup* pCleanup = nullptr;
        IDeliveryOptimizationMgrInternal* pMgrInternal = nullptr;

        if (Mile::CoCheckInterfaceName(
            DeliveryOptimizationIID,
            L"IDeliveryOptimizationCleanup").IsSucceeded())
        {
            pCleanup = reinterpret_cast<IDeliveryOptimizationCleanup*>(
                pInterface);
        }
        else if (Mile::CoCheckInterfaceName(
            DeliveryOptimizationIID,
            L"IDeliveryOptimizationMgrInternal").IsSucceeded())
        {
            pMgrInternal = reinterpret_cast<IDeliveryOptimizationMgrInternal*>(
                pInterface);
        }
        else
        {
            hr = E_NOINTERFACE;
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"Mile::CoCheckInterfaceName");
            break;
        }

        if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
        {
            UINT64 CacheSize = 0;
            if (pCleanup)
            {
                hr = pCleanup->GetCacheSize(&CacheSize);
            }
            else if (pMgrInternal)
            {
                hr = pMgrInternal->GetCacheSize(&CacheSize);
            }
            else
            {
                hr = E_FAIL;
            }

            if (hr.IsSucceeded())
            {
                ::MoPrivatePrintPurgeScanResult(Context, CacheSize);
            }
            else
            {
                if (pCleanup)
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"IDeliveryOptimizationCleanup::GetCacheSize");
                }
                else if (pMgrInternal)
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"IDeliveryOptimizationMgrInternal::GetCacheSize");
                }
            }
        }
        else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
        {
            if (pCleanup)
            {
                hr = pCleanup->DeleteCache();
            }
            else if (pMgrInternal)
            {
                hr = pMgrInternal->DeleteCache();
            }
            else
            {
                hr = E_FAIL;
            }

            if (hr.IsFailed())
            {
                if (pCleanup)
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"IDeliveryOptimizationCleanup::DeleteCache");
                }
                else if (pMgrInternal)
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"IDeliveryOptimizationMgrInternal::DeleteCache");
                }
            }
        }

    } while (false);

    if (pInterface)
    {
        pInterface->Release();
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
