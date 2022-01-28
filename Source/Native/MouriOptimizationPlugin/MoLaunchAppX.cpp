/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoLaunchAppX.cpp
 * PURPOSE:   Implementation for Launch AppX
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <shobjidl.h>

namespace
{
    static bool ParseCommandArguments(
        _In_ PNSUDO_CONTEXT Context,
        std::wstring& UserModelId,
        std::wstring& Arguments)
    {
        std::wstring RawArguments =
            std::wstring(Context->GetContextPluginCommandArguments(Context));

        std::vector<std::wstring> SplitedArguments =
            Mile::SpiltCommandArguments(RawArguments);
        if (SplitedArguments.empty())
        {
            return false;
        }

        UserModelId = SplitedArguments[0];

        if (SplitedArguments.size() > 1)
        {
            // Get the approximate location of the unresolved command line.
            // // We use "(arg_size - 1)" to ensure that the program path
            // without quotes can also correctly parse.
            wchar_t* search_start = const_cast<wchar_t*>(RawArguments.c_str());
            search_start += UserModelId.size();

            // Get the unresolved command line. Search for the beginning of
            // the first parameter delimiter called space and exclude the
            // first space by adding 1 to the result.
            wchar_t* command = ::wcsstr(search_start, L" ") + 1;

            // Omit the space. (Thanks to wzzw.)
            while (command && *command == L' ')
            {
                ++command;
            }

            Arguments = std::wstring(command);
        }

        return true;
    }
}

EXTERN_C HRESULT WINAPI MoLaunchAppX(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    bool ApartmentInitialized = false;
    IApplicationActivationManager* pApplicationActivationManager = nullptr;

    do
    {
        hr = ::CoInitializeEx(
            nullptr,
            COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (hr.IsFailed())
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"CoInitializeEx");
            break;
        }
        ApartmentInitialized = true;

        std::wstring UserModelId;
        std::wstring Arguments;
        if (!::ParseCommandArguments(Context, UserModelId, Arguments))
        {
            ::MoPrivateWriteLine(
                Context,
                Context->GetTranslation(Context, "ModeText"),
                Context->GetTranslation(Context, "CanceledModeText"));
            hr = Mile::HResult::FromWin32(ERROR_CANCELLED);
            break;
        }

        hr = ::CoCreateInstance(
            CLSID_ApplicationActivationManager,
            nullptr,
            CLSCTX_LOCAL_SERVER,
            IID_IApplicationActivationManager,
            reinterpret_cast<LPVOID*>(&pApplicationActivationManager));
        if (hr.IsFailed())
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"CoCreateInstance");
            break;
        }

        // This call ensures that the app is launched as the foreground window.
        hr = ::CoAllowSetForegroundWindow(
            pApplicationActivationManager,
            nullptr);
        if (hr.IsFailed())
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"CoAllowSetForegroundWindow");
            break;
        }

        DWORD dwProcessId = 0;
        // Launch the app
        hr = pApplicationActivationManager->ActivateApplication(
            UserModelId.c_str(),
            Arguments.c_str(),
            AO_NONE,
            &dwProcessId);
        if (hr.IsFailed())
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"IApplicationActivationManager::ActivateApplication");
        }

    } while (false);

    if (pApplicationActivationManager)
    {
        pApplicationActivationManager->Release();
    }

    if (ApartmentInitialized)
    {
        ::CoUninitialize();
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
