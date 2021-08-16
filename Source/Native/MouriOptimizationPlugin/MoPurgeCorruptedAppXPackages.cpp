/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeCorruptedAppXPackages.cpp
 * PURPOSE:   Implementation for Purge Corrupted AppX Packages
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Management.Deployment.h>

#include <vector>

namespace winrt
{
    using namespace Windows::ApplicationModel;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
    using namespace Windows::Management::Deployment;
    using namespace Windows::Storage;
}

EXTERN_C HRESULT WINAPI MoPurgeCorruptedAppXPackages(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    bool ApartmentInitialized = false;

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

        try
        {
            winrt::init_apartment();
            ApartmentInitialized = true;

            std::vector<winrt::hstring> CorruptedPackages;

            winrt::PackageManager PackageManager;
            for (winrt::Package Package : PackageManager.FindPackages())
            {
                try
                {
                    if (Package.InstalledLocation())
                    {
                        continue;
                    }
                }
                catch (...)
                {

                }

                CorruptedPackages.push_back(Package.Id().FullName());
            }

            if (CorruptedPackages.empty())
            {
                ::MoPrivateWriteLine(
                    Context,
                    Context->GetTranslation(
                        Context,
                        "MoPurgeCorruptedAppXPackages_NoPackagesText"));
            }
            else
            {
                for (winrt::hstring const& CorruptedPackage : CorruptedPackages)
                {
                    if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
                    {
                        ::MoPrivateWriteLine(
                            Context,
                            Context->GetTranslation(
                                Context,
                                "DetectedText"),
                            CorruptedPackage.c_str());
                    }
                    else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
                    {
                        try
                        {
                            winrt::DeploymentResult Result =
                                PackageManager.RemovePackageAsync(
                                    CorruptedPackage).get();

                            winrt::check_hresult(
                                Result.ExtendedErrorCode());

                            ::MoPrivateWriteLine(
                                Context,
                                Context->GetTranslation(
                                    Context,
                                    "RemovedText"),
                                CorruptedPackage.c_str());
                        }
                        catch (winrt::hresult_error const& ex)
                        {
                            ::MoPrivateWriteErrorMessage(
                                Context,
                                static_cast<HRESULT>(ex.code()),
                                L"%s(%s)",
                                L"PackageManager::RemovePackageAsync",
                                CorruptedPackage.c_str());
                        }

                    }
                }
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            hr = static_cast<HRESULT>(ex.code());
        }

    } while (false);

    if (ApartmentInitialized)
    {
        winrt::uninit_apartment();
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
