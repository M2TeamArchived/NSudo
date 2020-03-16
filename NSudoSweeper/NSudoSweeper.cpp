/*
 * PROJECT:   NSudo Sweeper
 * FILE:      NSudoSweeper.cpp
 * PURPOSE:   Implementation for NSudo Sweeper
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#include "NSudoSweeperVersion.h"

#include <atlbase.h>

#include "WTL/atlapp.h"
#include "WTL/atlcrack.h"
#include "WTL/atlctrls.h"
#include "WTL/atlframe.h"
#include "WTL/atlmisc.h"

class CMainWindow :
    public CFrameWindowImpl<CMainWindow>
{
private:
    CFont UIFont;

    CStatic ContentControl;

public:

    BEGIN_MSG_MAP(CMainWindow)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
    END_MSG_MAP()

public:

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        UNREFERENCED_PARAMETER(lpCreateStruct);

        this->SetWindowTextW(
            L"M2-Team NSudo Sweeper " NSUDO_SWEEPER_VERSION_STRING);

        this->UIFont.CreateFontW(
            20,                       // nHeight
            0,                        // nWidth
            0,                        // nEscapement
            0,                        // nOrientation
            FW_NORMAL,                // nWeight
            FALSE,                    // bItalic
            FALSE,                    // bUnderline
            0,                        // cStrikeOut
            ANSI_CHARSET,             // nCharSet
            OUT_DEFAULT_PRECIS,       // nOutPrecision
            CLIP_DEFAULT_PRECIS,      // nClipPrecision
            DEFAULT_QUALITY,          // nQuality
            DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
            L"MS Shell Dlg");

        auto x = CRect(50, 50, 300, 150);

        this->ContentControl.Create(
            this->m_hWnd,
            x,
            L"Welcome to use the brand new NSudo Sweeper!\n(Under Construction)",
            WS_CHILD | WS_VISIBLE);

        this->ContentControl.SetFont(UIFont);

        return 0;
    }

    void OnDestroy()
    {
        ::PostQuitMessage(0);
    }

public:
    CMainWindow() = default;
    ~CMainWindow() = default;
};

CAppModule _Module;

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    HRESULT hr = CoInitialize(nullptr);
    ATLASSERT(SUCCEEDED(hr));

    hr = _Module.Init(nullptr, hInstance);
    ATLASSERT(SUCCEEDED(hr));

    CMessageLoop MessageLoop;
    _Module.AddMessageLoop(&MessageLoop);

    CMainWindow MainWindow;

    if (MainWindow.CreateEx() == NULL)
    {
        ATLTRACE(_T("Main window creation failed!\n"));
        return 0;
    }

    MainWindow.ShowWindow(nShowCmd);

    int nRet = MessageLoop.Run();

    _Module.RemoveMessageLoop();

    _Module.Term();

    ::CoUninitialize();

    return nRet;
}
