/*
 * PROJECT:   NSudo Software Development Kit
 * FILE:      NSudoContextPluginHost.h
 * PURPOSE:   Implementation for NSudo context plugin host
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "NSudoContextPluginHost.h"

#include <Mile.PiConsole.h>

#include "toml.hpp"

/**
 * @brief Gets the NSudo private context.
 * @param Context The NSudo context.
 * @return The NSudo private context.
*/
PNSUDO_CONTEXT_PRIVATE NSudoContextGetPrivate(
    _In_ PNSUDO_CONTEXT Context)
{
    PNSUDO_CONTEXT_PRIVATE PrivateContext =
        reinterpret_cast<PNSUDO_CONTEXT_PRIVATE>(Context);
    if (PrivateContext)
    {
        if (PrivateContext->Size == sizeof(NSUDO_CONTEXT_PRIVATE))
        {
            return PrivateContext;
        }
    }

    return nullptr;
}

/**
 * @brief Gets NSudo version information.
 * @param Context The NSudo context.
 * @param Version The NSudo version information.
*/
VOID WINAPI NSudoContextGetNSudoVersion(
    _In_ PNSUDO_CONTEXT Context,
    _Out_ PNSUDO_VERSION Version)
{
    Mile::UnreferencedParameter(Context);

    if (Version)
    {
        Version->Major = 9;
        Version->Minor = 0;
        Version->Patch = 0;
        Version->Revision = 0;
        Version->Tag = L"Preview 1";
    }
}

/**
 * @brief Gets the module handle of the context plugin.
 * @param Context The NSudo context.
 * @return The module handle of the context plugin.
*/
HMODULE WINAPI NSudoContextGetContextPluginModuleHandle(
    _In_ PNSUDO_CONTEXT Context)
{
    PNSUDO_CONTEXT_PRIVATE PrivateContext = ::NSudoContextGetPrivate(Context);

    if (PrivateContext)
    {
        return PrivateContext->ModuleHandle;
    }

    return nullptr;
}

/**
 * @brief Gets the command line arguments for the context plugin.
 * @param Context The NSudo context.
 * @return The command line arguments for the context plugin.
*/
LPCWSTR WINAPI NSudoContextGetContextPluginCommandArguments(
    _In_ PNSUDO_CONTEXT Context)
{
    PNSUDO_CONTEXT_PRIVATE PrivateContext = ::NSudoContextGetPrivate(Context);

    if (PrivateContext)
    {
        return PrivateContext->CommandArguments;
    }

    return nullptr;
}

/**
 * @brief Frees a memory block allocated from methods in PNSUDO_CONTEXT.
 * @param Context The NSudo context.
 * @param Block A pointer to the memory block to be freed.
*/
VOID WINAPI NSudoContextFree(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPVOID Block)
{
    UNREFERENCED_PARAMETER(Context);

    Mile::HeapMemory::Free(Block);
}

/**
 * @brief Writes the specified string value to the NSudo user interface.
 * @param Context The NSudo context.
 * @param Value The value to write.
*/
VOID WINAPI NSudoContextWrite(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCWSTR Value)
{
    PNSUDO_CONTEXT_PRIVATE PrivateContext = ::NSudoContextGetPrivate(Context);

    if (PrivateContext)
    {
        if (PrivateContext->ConsoleMode)
        {
            std::string CurrentCodePageString = Mile::ToConsoleString(Value);

            DWORD NumberOfCharsWritten = 0;
            ::WriteFile(
                PrivateContext->ConsoleOutputHandle,
                CurrentCodePageString.c_str(),
                static_cast<DWORD>(CurrentCodePageString.size()),
                &NumberOfCharsWritten,
                nullptr);
        }
        else
        {
            Mile::PiConsole::PrintMessage(
                PrivateContext->PiConsoleWindowHandle,
                Value);
        }
    }
}

/**
 * @brief Writes the specified string value, followed by the current line
 *        terminator, to NSudo user interface.
 * @param Context The NSudo context.
 * @param Value The value to write.
*/
VOID WINAPI NSudoContextWriteLine(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCWSTR Value)
{
    if (Context)
    {
        Context->Write(
            Context,
            Mile::FormatUtf16String(L"%s\r\n", Value).c_str());
    }
}

/**
 * @brief Reads the next line of characters from the user input.
 * @param Context The NSudo context.
 * @param InputPrompt The prompt you want to notice to the user.
 * @return The next line of characters from the user input. If the return
 *         value is not nullptr, you should use PNSUDO_CONTEXT::Free method
 *         to release.
*/
LPCWSTR WINAPI NSudoContextReadLine(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCWSTR InputPrompt)
{
    PNSUDO_CONTEXT_PRIVATE PrivateContext = ::NSudoContextGetPrivate(Context);

    if (PrivateContext)
    {
        if (PrivateContext->ConsoleMode)
        {
            wchar_t* InputBuffer = nullptr;
            DWORD PreviousConsoleMode = 0;

            do
            {
                if (!::GetConsoleMode(
                    PrivateContext->ConsoleInputHandle,
                    &PreviousConsoleMode))
                {
                    break;
                }

                if (!::SetConsoleMode(
                    PrivateContext->ConsoleInputHandle,
                    ENABLE_LINE_INPUT |
                    ENABLE_PROCESSED_INPUT |
                    ENABLE_ECHO_INPUT))
                {
                    break;
                }

                std::wstring Result;

                for (;;)
                {
                    wchar_t CurrentChar = L'\0';
                    DWORD NumberOfCharsRead = 0;

                    if (!::ReadConsoleW(
                        PrivateContext->ConsoleInputHandle,
                        reinterpret_cast<LPVOID>(&CurrentChar),
                        1,
                        &NumberOfCharsRead,
                        nullptr))
                    {
                        break;
                    }

                    if (CurrentChar == '\r')
                    {
                        continue;
                    }
                    else if (CurrentChar == '\n')
                    {
                        break;
                    }
                    else
                    {
                        Result.push_back(CurrentChar);
                    }
                }

                std::size_t InputResultLength =
                    (Result.size() + 1) * sizeof(wchar_t);
                InputBuffer = reinterpret_cast<wchar_t*>(
                    Mile::HeapMemory::Allocate(InputResultLength));
                if (InputBuffer)
                {
                    std::memcpy(
                        InputBuffer,
                        Result.c_str(),
                        InputResultLength);
                }

                Result = Result;

            } while (false);

            ::SetConsoleMode(
                PrivateContext->ConsoleInputHandle,
                PreviousConsoleMode);

            return InputBuffer;
        }
        else
        {
            return Mile::PiConsole::GetInput(
                PrivateContext->PiConsoleWindowHandle,
                InputPrompt);
        }
    }

    return nullptr;
}

/**
 * @brief Gets the translated string.
 * @param Context The NSudo context.
 * @param Name The UTF-8 name of the translated string.
 * @return The translated string.
*/
LPCWSTR WINAPI NSudoContextGetTranslation(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCSTR Name)
{
    PNSUDO_CONTEXT_PRIVATE PrivateContext = ::NSudoContextGetPrivate(Context);
    if (PrivateContext)
    {
        return PrivateContext->Translations[Name].c_str();
    }

    return L"";
}


EXTERN_C VOID WINAPI NSudoContextFillFunctionTable(
    _In_ PNSUDO_CONTEXT Context)
{
    if (Context)
    {
        Context->GetNSudoVersion =
            ::NSudoContextGetNSudoVersion;
        Context->GetContextPluginModuleHandle =
            ::NSudoContextGetContextPluginModuleHandle;
        Context->GetContextPluginCommandArguments =
            ::NSudoContextGetContextPluginCommandArguments;
        Context->Free =
            ::NSudoContextFree;
        Context->Write =
            ::NSudoContextWrite;
        Context->WriteLine =
            ::NSudoContextWriteLine;
        Context->ReadLine =
            ::NSudoContextReadLine;
        Context->GetTranslation =
            ::NSudoContextGetTranslation;
    }
}

EXTERN_C HRESULT WINAPI NSudoContextExecutePlugin(
    _In_ PNSUDO_CONTEXT Context,
    _In_ LPCWSTR PluginModuleName,
    _In_ LPCSTR PluginEntryPointName,
    _In_ LPCWSTR CommandArguments)
{
    if (!Context || !PluginModuleName || !PluginEntryPointName)
    {
        return E_INVALIDARG;
    }

    PNSUDO_CONTEXT_PRIVATE PrivateContext = nullptr;
    HMODULE ModuleHandle = nullptr;
    NSUDO_CONTEXT_PLUGIN_ENTRY_POINT_TYPE EntryPointFunction = nullptr;
    HRESULT EntryPointResult = S_OK;

    auto ExitHandler = Mile::ScopeExitTaskHandler([&]()
    {
        if (ModuleHandle)
        {
            ::FreeLibrary(ModuleHandle);
        }
    });

    PrivateContext = ::NSudoContextGetPrivate(Context);
    if (!PrivateContext)
    {
        return E_NOINTERFACE;
    }

    ModuleHandle = Mile::LoadLibraryFromSystem32(PluginModuleName);
    if (!ModuleHandle)
    {
        return E_NOINTERFACE;
    }

    EntryPointFunction = reinterpret_cast<NSUDO_CONTEXT_PLUGIN_ENTRY_POINT_TYPE>(
        ::GetProcAddress(ModuleHandle, PluginEntryPointName));
    if (!EntryPointFunction)
    {
        return E_NOINTERFACE;
    }

    PrivateContext->ModuleHandle = ModuleHandle;
    PrivateContext->CommandArguments = CommandArguments;
    Mile::RESOURCE_INFO ResourceInfo = { 0 };
    if (SUCCEEDED(Mile::LoadResource(
        &ResourceInfo,
        PrivateContext->ModuleHandle,
        L"Translations",
        MAKEINTRESOURCEW(1))))
    {
        try
        {
            toml::table Translations = toml::parse(std::string(
                reinterpret_cast<const char*>(ResourceInfo.Pointer),
                ResourceInfo.Size));
            for (auto const& Translation : Translations)
            {
                PrivateContext->Translations.emplace(std::make_pair(
                    Translation.first,
                    Mile::ToUtf16String(
                        Translation.second.value_or<std::string>(""))));
            }
        }
        catch (...)
        {

        }
    }

    EntryPointResult = EntryPointFunction(&PrivateContext->PublicContext);

    PrivateContext->ModuleHandle = nullptr;
    PrivateContext->CommandArguments = nullptr;
    PrivateContext->Translations.clear();

    return EntryPointResult;
}
