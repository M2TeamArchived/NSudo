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
    std::vector<HANDLE> CompletedSignals;

    auto ExitHandler = Mile::ScopeExitTaskHandler([&]()
    {
        for (HANDLE CompletedSignal : CompletedSignals)
        {
            ::CloseHandle(CompletedSignal);
        }
    });

    try
    {
        winrt::init_apartment(
            winrt::apartment_type::single_threaded);

        winrt::AppInstallManager AppInstallManager;
        winrt::IVectorView<winrt::AppInstallItem> InstallList =
            AppInstallManager.SearchForAllUpdatesAsync().get();
        for (winrt::AppInstallItem InstallItem : InstallList)
        {
            Context->WriteLine(
                Context,
                Mile::FormatUtf16String(
                    L"Update: %s",
                    InstallItem.PackageFamilyName().c_str()).c_str());

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

                Context->WriteLine(
                    Context,
                    Mile::FormatUtf16String(
                        L"%s: Update completed.",
                        sender.PackageFamilyName().c_str()).c_str());

                ::SetEvent(CompletedSignal);
            });

            InstallItem.StatusChanged([Context](
                winrt::AppInstallItem const& sender,
                winrt::IInspectable const& args)
            {
                Mile::UnreferencedParameter(args);

                Context->WriteLine(
                    Context,
                    Mile::FormatUtf16String(
                        L"%s: Update progress %.0f%%.",
                        sender.PackageFamilyName().c_str(),
                        sender.GetCurrentStatus().PercentComplete()).c_str());
            });
        }

        if (CompletedSignals.empty())
        {
            Context->WriteLine(
                Context,
                L"All your trusted apps and games from Microsoft Store have "
                L"the latest updates.");
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

        winrt::uninit_apartment();
    }
    catch (winrt::hresult_error const& ex)
    {
        hr = static_cast<HRESULT>(ex.code());
    }

    ::MoPrivatePrintFinalResult(Context, hr, nullptr);

    return hr;
}
