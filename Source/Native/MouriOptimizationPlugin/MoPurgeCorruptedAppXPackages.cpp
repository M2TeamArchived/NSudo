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
#include <string>

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
    std::vector<std::wstring> CorruptedPackages;

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
            winrt::init_apartment(
                winrt::apartment_type::single_threaded);

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

                CorruptedPackages.push_back(Package.Id().FullName().c_str());
            }

            if (CorruptedPackages.empty())
            {
                Context->WriteLine(
                    Context,
                    L"No corrupted packages were found.");
            }
            else
            {
                for (std::wstring const& CorruptedPackage : CorruptedPackages)
                {
                    if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
                    {
                        Context->WriteLine(
                            Context,
                            Mile::FormatUtf16String(
                                L"Corrupted packages found: %s.",
                                CorruptedPackage.c_str()).c_str());
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

                            Context->WriteLine(
                                Context,
                                Mile::FormatUtf16String(
                                    L"Corrupted packages removed: %s.",
                                    CorruptedPackage.c_str()).c_str());
                        }
                        catch (winrt::hresult_error const& ex)
                        {
                            ::MoPrivatePrintFinalResult(
                                Context,
                                static_cast<HRESULT>(ex.code()),
                                Mile::FormatUtf16String(
                                    L"PackageManager::RemovePackageAsync(%s)",
                                    CorruptedPackage.c_str()).c_str());
                        }
                        
                    }
                }
            }

            winrt::uninit_apartment();
        }
        catch (winrt::hresult_error const& ex)
        {
            hr = static_cast<HRESULT>(ex.code());
        }

    } while (false);

    ::MoPrivatePrintFinalResult(Context, hr, nullptr);

    return hr;
}
