/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoUpdateAppXPackages.cpp
 * PURPOSE:   Implementation for Update AppX Packages
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Store.Preview.InstallControl.h>

#include <vector>

namespace winrt
{
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
    using namespace Windows::ApplicationModel::Store::Preview::InstallControl;
}

EXTERN_C HRESULT WINAPI MoUpdateAppXPackages(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    bool ApartmentInitialized = false;
    std::vector<HANDLE> CompletedSignals;

    try
    {
        winrt::init_apartment();
        ApartmentInitialized = true;

        winrt::AppInstallManager AppInstallManager;
        winrt::IVectorView<winrt::AppInstallItem> InstallList =
            AppInstallManager.SearchForAllUpdatesAsync().get();
        for (winrt::AppInstallItem InstallItem : InstallList)
        {
            ::MoPrivateWriteLine(
                Context,
                Context->GetTranslation(
                    Context,
                    "MoUpdateAppXPackages_UpdateText"),
                InstallItem.PackageFamilyName().c_str());

            HANDLE CompletedSignal = ::CreateEventExW(
                nullptr,
                nullptr,
                0,
                EVENT_ALL_ACCESS);
            if (!CompletedSignal)
            {
                winrt::throw_last_error();
            }

            CompletedSignals.push_back(CompletedSignal);

            InstallItem.Completed([Context, CompletedSignal](
                winrt::AppInstallItem const& sender,
                winrt::IInspectable const& args)
            {
                Mile::UnreferencedParameter(args);

                try
                {
                    ::MoPrivateWriteLine(
                        Context,
                        Context->GetTranslation(
                            Context,
                            "MoUpdateAppXPackages_UpdateCompletedText"),
                        sender.PackageFamilyName().c_str());
                }
                catch (...)
                {

                }

                ::SetEvent(CompletedSignal);
            });

            InstallItem.StatusChanged([Context](
                winrt::AppInstallItem const& sender,
                winrt::IInspectable const& args)
            {
                Mile::UnreferencedParameter(args);

                try
                {
                    ::MoPrivateWriteLine(
                        Context,
                        Context->GetTranslation(
                            Context,
                            "MoUpdateAppXPackages_UpdateProgressText"),
                        sender.PackageFamilyName().c_str(),
                        sender.GetCurrentStatus().PercentComplete());
                }
                catch (...)
                {

                }
            });
        }

        if (CompletedSignals.empty())
        {
            ::MoPrivateWriteLine(
                Context,
                Context->GetTranslation(
                    Context,
                    "MoUpdateAppXPackages_NoUpdatesNoticeText"));
        }
        else
        {
            ::WaitForMultipleObjectsEx(
                static_cast<DWORD>(CompletedSignals.size()),
                &CompletedSignals[0],
                TRUE,
                INFINITE,
                FALSE);
        }
    }
    catch (winrt::hresult_error const& ex)
    {
        hr = static_cast<HRESULT>(ex.code());
    }

    for (HANDLE CompletedSignal : CompletedSignals)
    {
        ::CloseHandle(CompletedSignal);
    }

    if (ApartmentInitialized)
    {
        winrt::uninit_apartment();
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
