/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.PiConsole.cpp
 * PURPOSE:   Implementation for Portable Interactive Console (Pi Console)
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.PiConsole.h"

#include <CommCtrl.h>

#include <cstdint>

namespace
{
    struct PiConsoleInformation
    {
        SIZE_T Size;
        int WindowDpi;
        int InputEditHeight;
        HANDLE InputSignal;
        HWND InputEdit;
        HWND OutputEdit;
        HWND FocusedEdit;
        CRITICAL_SECTION OperationLock;
    };

    PiConsoleInformation* PiConsoleGetInformation(
        _In_ HWND WindowHandle)
    {
        PiConsoleInformation* ConsoleInformation =
            reinterpret_cast<PiConsoleInformation*>(
                ::GetWindowLongPtrW(WindowHandle, GWLP_USERDATA));
        if (ConsoleInformation)
        {
            if (ConsoleInformation->Size == sizeof(PiConsoleInformation))
            {
                return ConsoleInformation;
            }
        }

        return nullptr;
    }

    void PiConsoleSetFocus(
        _In_ HWND WindowHandle)
    {
        PiConsoleInformation* ConsoleInformation =
            ::PiConsoleGetInformation(WindowHandle);
        if (ConsoleInformation)
        {
            int& InputEditHeight = ConsoleInformation->InputEditHeight;
            HWND& FocusedEdit = ConsoleInformation->FocusedEdit;
            HWND& InputEdit = ConsoleInformation->InputEdit;
            HWND& OutputEdit = ConsoleInformation->OutputEdit;
            FocusedEdit = (InputEditHeight != 0)
                ? InputEdit
                : OutputEdit;
            ::SetForegroundWindow(FocusedEdit);
            ::SetFocus(FocusedEdit) ? 'Y' : 'N';
        }
    }

    void PiConsoleRefreshLayout(
        _In_ HWND WindowHandle)
    {
        RECT ClientRect;
        if (::GetClientRect(WindowHandle, &ClientRect))
        {
            std::int16_t ClientWidth = static_cast<std::int16_t>(
                ClientRect.right - ClientRect.left);
            std::int16_t ClientHeight = static_cast<std::int16_t>(
                ClientRect.bottom - ClientRect.top);

            ::SendMessageW(
                WindowHandle,
                WM_SIZE,
                SIZE_RESTORED,
                (ClientHeight << 16) | ClientWidth);

            ::PiConsoleSetFocus(WindowHandle);
        }
    }

    void PiConsoleChangeFont(
        _In_ HWND WindowHandle,
        _In_ int FontSize)
    {
        PiConsoleInformation* ConsoleInformation =
            ::PiConsoleGetInformation(WindowHandle);
        if (ConsoleInformation)
        {
            HFONT FontHandle = ::CreateFontW(
                -::MulDiv(
                    FontSize,
                    ConsoleInformation->WindowDpi,
                    USER_DEFAULT_SCREEN_DPI),
                0,
                0,
                0,
                FW_NORMAL,
                false,
                false,
                false,
                DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,
                CLIP_CHARACTER_PRECIS,
                CLEARTYPE_NATURAL_QUALITY,
                FF_MODERN,
                L"MS Shell Dlg");
            if (FontHandle)
            {
                ::SendMessageW(
                    WindowHandle,
                    WM_SETFONT,
                    reinterpret_cast<WPARAM>(FontHandle),
                    TRUE);

                ::SendMessageW(
                    ConsoleInformation->InputEdit,
                    WM_SETFONT,
                    reinterpret_cast<WPARAM>(FontHandle),
                    TRUE);

                ::SendMessageW(
                    ConsoleInformation->OutputEdit,
                    WM_SETFONT,
                    reinterpret_cast<WPARAM>(FontHandle),
                    TRUE);

                ::DeleteObject(FontHandle);
            }
        }
    }

    void PiConsoleSetTextCursorPositionToEnd(
        _In_ HWND EditControlHandle)
    {
        int TextLength = ::GetWindowTextLengthW(
            EditControlHandle);

        ::SendMessageW(
            EditControlHandle,
            EM_SETSEL,
            static_cast<WPARAM>(TextLength),
            static_cast<LPARAM>(TextLength));
    }

    void PiConsoleAppendString(
        _In_ HWND EditControlHandle,
        _In_ LPCWSTR Content)
    {
        ::PiConsoleSetTextCursorPositionToEnd(
            EditControlHandle);

        ::SendMessageW(
            EditControlHandle,
            EM_REPLACESEL,
            FALSE,
            reinterpret_cast<LPARAM>(Content));

        ::PiConsoleSetTextCursorPositionToEnd(
            EditControlHandle);
    }
}

HWND Mile::PiConsole::Create(
    _In_ HINSTANCE InstanceHandle,
    _In_ HICON WindowIconHandle,
    _In_ LPCWSTR WindowTitle,
    _In_ DWORD ShowWindowMode)
{
    HWND OutputWindowHandle = nullptr;
    HANDLE CompletedEventHandle = nullptr;
    HANDLE WindowThreadHandle = nullptr;

    auto ExitHandler = Mile::ScopeExitTaskHandler([&]()
    {
        if (WindowThreadHandle)
        {
            ::CloseHandle(WindowThreadHandle);
        }

        if (CompletedEventHandle)
        {
            ::CloseHandle(CompletedEventHandle);
        }
    });

    auto WindowCallback = [](
        _In_ HWND hWnd,
        _In_ UINT uMsg,
        _In_ WPARAM wParam,
        _In_ LPARAM lParam) -> LRESULT
    {
        switch (uMsg)
        {
        case WM_SETFOCUS:
        {
            ::PiConsoleSetFocus(hWnd);
            break;
        }
        case WM_ACTIVATE:
        {
            if (LOWORD(wParam) != WA_INACTIVE)
            {
                ::PiConsoleSetFocus(hWnd);
            }

            break;
        }
        case WM_SIZE:
        {
            PiConsoleInformation* ConsoleInformation =
                ::PiConsoleGetInformation(hWnd);
            if (ConsoleInformation)
            {
                int RealInputEditHeight = ::MulDiv(
                    ConsoleInformation->InputEditHeight,
                    ConsoleInformation->WindowDpi,
                    USER_DEFAULT_SCREEN_DPI);

                if (ConsoleInformation->InputEdit)
                {
                    ::SetWindowPos(
                        ConsoleInformation->InputEdit,
                        nullptr,
                        0,
                        HIWORD(lParam) - RealInputEditHeight,
                        LOWORD(lParam),
                        ConsoleInformation->InputEditHeight,
                        0);
                }

                if (ConsoleInformation->OutputEdit)
                {
                    ::SetWindowPos(
                        ConsoleInformation->OutputEdit,
                        nullptr,
                        0,
                        0,
                        LOWORD(lParam),
                        HIWORD(lParam) - RealInputEditHeight,
                        0);
                }

            }

            ::UpdateWindow(hWnd);

            break;
        }
        case WM_DPICHANGED:
        {
            PiConsoleInformation* ConsoleInformation =
                ::PiConsoleGetInformation(hWnd);
            if (ConsoleInformation)
            {
                ConsoleInformation->WindowDpi = HIWORD(wParam);
            }

            ::PiConsoleChangeFont(hWnd, 16);

            auto lprcNewScale = reinterpret_cast<RECT*>(lParam);

            ::SetWindowPos(
                hWnd,
                nullptr,
                lprcNewScale->left,
                lprcNewScale->top,
                lprcNewScale->right - lprcNewScale->left,
                lprcNewScale->bottom - lprcNewScale->top,
                SWP_NOZORDER | SWP_NOACTIVATE);

            ::UpdateWindow(hWnd);

            break;
        }
        case WM_DESTROY:
        {
            ::PostQuitMessage(0);
            break;
        }
        default:
            return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    };

    CompletedEventHandle = ::CreateEventExW(
        nullptr,
        nullptr,
        0,
        EVENT_ALL_ACCESS);
    if (!CompletedEventHandle)
    {
        return nullptr;
    }

    WindowThreadHandle = Mile::CreateThread([&]()
    {
        bool Result = false;
        HWND WindowHandle = nullptr;
        PiConsoleInformation* ConsoleInformation = nullptr;

        auto WindowThreadExitHandler = Mile::ScopeExitTaskHandler([&]()
        {
            if (!Result)
            {
                ::SetEvent(CompletedEventHandle);
            }

            if (WindowHandle)
            {
                ::DestroyWindow(WindowHandle);
            }

            if (ConsoleInformation)
            {
                Mile::CriticalSection::Delete(
                    &ConsoleInformation->OperationLock);

                if (ConsoleInformation->InputSignal)
                {
                    ::SetEvent(ConsoleInformation->InputSignal);
                    ::CloseHandle(ConsoleInformation->InputSignal);
                }

                if (ConsoleInformation->InputEdit)
                {
                    ::DestroyWindow(ConsoleInformation->InputEdit);
                }

                if (ConsoleInformation->OutputEdit)
                {
                    ::DestroyWindow(ConsoleInformation->OutputEdit);
                }

                Mile::HeapMemory::Free(ConsoleInformation);
                ConsoleInformation = nullptr;
            }
        });

        ConsoleInformation = reinterpret_cast<PiConsoleInformation*>(
            Mile::HeapMemory::Allocate(sizeof(PiConsoleInformation)));
        if (!ConsoleInformation)
        {
            return;
        }

        ConsoleInformation->Size = sizeof(PiConsoleInformation);
        ConsoleInformation->InputEditHeight = 0;

        Mile::CriticalSection::Initialize(
            &ConsoleInformation->OperationLock);

        ConsoleInformation->InputSignal = ::CreateEventExW(
            nullptr,
            nullptr,
            CREATE_EVENT_INITIAL_SET,
            EVENT_ALL_ACCESS);
        if (!ConsoleInformation->InputSignal)
        {
            return;
        }

        Mile::EnablePerMonitorDialogScaling();

        WNDCLASSEXW WindowClass;
        WindowClass.cbSize = sizeof(WNDCLASSEX);
        WindowClass.style = CS_HREDRAW | CS_VREDRAW;
        WindowClass.lpfnWndProc = WindowCallback;
        WindowClass.cbClsExtra = 0;
        WindowClass.cbWndExtra = 0;
        WindowClass.hInstance = InstanceHandle;
        WindowClass.hIcon = WindowIconHandle;
        WindowClass.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
        WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        WindowClass.lpszMenuName = nullptr;
        WindowClass.lpszClassName = L"MilePiConsoleWindow";
        WindowClass.hIconSm = WindowIconHandle;

        if (!::RegisterClassExW(&WindowClass))
        {
            return;
        }

        WindowHandle = ::CreateWindowExW(
            WS_EX_APPWINDOW | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT,
            WindowClass.lpszClassName,
            WindowTitle,
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
            CW_USEDEFAULT,
            0,
            640,
            400,
            nullptr,
            nullptr,
            WindowClass.hInstance,
            nullptr);
        if (!WindowHandle)
        {
            return;
        } 

        ::SetWindowLongPtrW(
            WindowHandle,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(ConsoleInformation));

        Mile::EnableChildWindowDpiMessage(WindowHandle);

        RECT ClientRectangle;
        if (!::GetClientRect(WindowHandle, &ClientRectangle))
        {
            return;
        }

        int xDPI = USER_DEFAULT_SCREEN_DPI;
        int yDPI = USER_DEFAULT_SCREEN_DPI;
        if (S_OK != Mile::GetDpiForMonitor(
            ::MonitorFromWindow(WindowHandle, MONITOR_DEFAULTTONEAREST),
            MDT_EFFECTIVE_DPI,
            reinterpret_cast<UINT*>(&xDPI),
            reinterpret_cast<UINT*>(&yDPI)))
        {
            xDPI = ::GetDeviceCaps(::GetDC(WindowHandle), LOGPIXELSX);
            yDPI = ::GetDeviceCaps(::GetDC(WindowHandle), LOGPIXELSY);
        }
        ConsoleInformation->WindowDpi = xDPI;

        int RealInputEditHeight = ::MulDiv(
            ConsoleInformation->InputEditHeight,
            ConsoleInformation->WindowDpi,
            USER_DEFAULT_SCREEN_DPI);

        ConsoleInformation->OutputEdit = ::CreateWindowExW(
            0,
            L"Edit",
            L"",
            ES_MULTILINE | ES_READONLY | WS_VSCROLL | WS_CHILD | WS_VISIBLE,
            0,
            0,
            ClientRectangle.right,
            ClientRectangle.bottom - RealInputEditHeight,
            WindowHandle,
            nullptr,
            WindowClass.hInstance,
            nullptr);
        if (!ConsoleInformation->OutputEdit)
        {
            return;
        }

        ConsoleInformation->InputEdit = ::CreateWindowExW(
            0,
            L"Edit",
            L"",
            ES_READONLY | WS_CHILD | WS_VISIBLE,
            0,
            ClientRectangle.bottom - RealInputEditHeight,
            ClientRectangle.right,
            RealInputEditHeight,
            WindowHandle,
            nullptr,
            WindowClass.hInstance,
            nullptr);
        if (!ConsoleInformation->InputEdit)
        {
            return;
        }

        ::PiConsoleChangeFont(WindowHandle, 16);

        ::ShowWindow(WindowHandle, ShowWindowMode);
        ::UpdateWindow(WindowHandle);

        OutputWindowHandle = WindowHandle;
        ::SetEvent(CompletedEventHandle);
        Result = true;

        MSG Message;
        while (::GetMessageW(&Message, nullptr, 0, 0))
        {
            if (Message.message == WM_KEYDOWN && Message.wParam == VK_RETURN)
            {
                ::SetEvent(ConsoleInformation->InputSignal);
            }
            else if (Message.message == WM_KEYDOWN && Message.wParam == VK_TAB)
            {
                int& InputEditHeight = ConsoleInformation->InputEditHeight;
                HWND& FocusedEdit = ConsoleInformation->FocusedEdit;
                HWND& InputEdit = ConsoleInformation->InputEdit;
                HWND& OutputEdit = ConsoleInformation->OutputEdit;
                FocusedEdit =
                    ((FocusedEdit != InputEdit) && (InputEditHeight != 0))
                    ? InputEdit
                    : OutputEdit;
                ::SetFocus(FocusedEdit);
            }

            ::TranslateMessage(&Message);
            ::DispatchMessageW(&Message);
        }
    });
    if (!WindowThreadHandle)
    {
        return nullptr;
    }

    ::WaitForSingleObjectEx(CompletedEventHandle, INFINITE, FALSE);

    return OutputWindowHandle;
}

void Mile::PiConsole::PrintMessage(
    _In_ HWND WindowHandle,
    _In_ LPCWSTR Content)
{
    PiConsoleInformation* ConsoleInformation =
        ::PiConsoleGetInformation(WindowHandle);
    if (ConsoleInformation)
    {
        Mile::AutoRawCriticalSectionTryLock Guard(
            ConsoleInformation->OperationLock);

        ::PiConsoleAppendString(
            ConsoleInformation->OutputEdit,
            Content);
    }
}

LPWSTR Mile::PiConsole::GetInput(
    _In_ HWND WindowHandle,
    _In_ LPCWSTR InputPrompt)
{
    bool Result = false;
    wchar_t* InputBuffer = nullptr;
    PiConsoleInformation* ConsoleInformation = nullptr;

    auto ExitHandler = Mile::ScopeExitTaskHandler([&]()
    {
        if (ConsoleInformation)
        {
            ConsoleInformation->InputEditHeight = 0;
            ::PiConsoleRefreshLayout(WindowHandle);

            ::SendMessageW(
                ConsoleInformation->InputEdit,
                EM_SETREADONLY,
                TRUE,
                0);
            ::SetWindowTextW(
                ConsoleInformation->InputEdit,
                L"");
            ::SendMessageW(
                ConsoleInformation->InputEdit,
                EM_SETCUEBANNER,
                TRUE,
                0);
        }

        if (!Result)
        {
            if (InputBuffer)
            {
                Mile::HeapMemory::Free(InputBuffer);
                InputBuffer = nullptr;
            }
        }
    });

    ConsoleInformation = ::PiConsoleGetInformation(WindowHandle);
    if (!ConsoleInformation)
    {
        return nullptr;
    }

    Mile::AutoRawCriticalSectionTryLock Guard(
        ConsoleInformation->OperationLock);

    ::SendMessageW(
        ConsoleInformation->InputEdit,
        EM_SETCUEBANNER,
        TRUE,
        reinterpret_cast<LPARAM>(InputPrompt));
    ::SendMessageW(
        ConsoleInformation->InputEdit,
        EM_SETREADONLY,
        FALSE,
        0);

    if (!::ResetEvent(
        ConsoleInformation->InputSignal))
    {
        return nullptr;
    }

    ConsoleInformation->InputEditHeight = 24;
    ::PiConsoleRefreshLayout(WindowHandle);

    ::WaitForSingleObjectEx(
        ConsoleInformation->InputSignal,
        INFINITE,
        FALSE);

    int TextLength = ::GetWindowTextLengthW(
        ConsoleInformation->InputEdit);
    if (TextLength)
    {
        InputBuffer = reinterpret_cast<wchar_t*>(
            Mile::HeapMemory::Allocate((TextLength + 1) * sizeof(wchar_t)));
        if (InputBuffer)
        {
            Result = ::GetWindowTextW(
                ConsoleInformation->InputEdit,
                InputBuffer,
                TextLength + 1);
        }
    }

    return InputBuffer;
}
