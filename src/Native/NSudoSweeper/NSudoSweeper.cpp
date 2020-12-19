/*
 * PROJECT:   NSudo Sweeper
 * FILE:      NSudoSweeper.cpp
 * PURPOSE:   Implementation for NSudo Sweeper
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Mile.Windows.h>

#include "Mile.Project.Properties.h"

#include "NSudoSweeperCore.h"

#define _ATL_NO_AUTOMATIC_NAMESPACE
#include <atlbase.h>
#include <atlwin.h>

#define _WTL_NO_AUTOMATIC_NAMESPACE
#define _ATL_NO_OPENGL
#include "WTL/atlapp.h"
#include "WTL/atlcrack.h"
#include "WTL/atlctrls.h"
#include "WTL/atlframe.h"
#include "WTL/atlmisc.h"

 // 开启子窗体DPI消息(至少Win10)
inline BOOL EnableChildWindowDpiMessage(
    _In_ HWND hWnd,
    _In_ BOOL bEnable)
{
    // Fix for Windows Vista and Server 2008.
    if (!IsWindowsVersionOrGreater(10, 0, 0)) return -1;

    typedef BOOL(WINAPI* PFN_EnableChildWindowDpiMessage)(HWND, BOOL);

    PFN_EnableChildWindowDpiMessage pEnableChildWindowDpiMessage =
        (PFN_EnableChildWindowDpiMessage)GetProcAddress(
            GetModuleHandleW(L"user32.dll"), "EnableChildWindowDpiMessage");

    if (pEnableChildWindowDpiMessage)
        return pEnableChildWindowDpiMessage(hWnd, bEnable);
    return -1;
}

WTL::CAppModule _Module;

class CMainWindow :
    public WTL::CFrameWindowImpl<CMainWindow>,
    public WTL::CUpdateUI<CMainWindow>,
    public WTL::CMessageFilter,
    public WTL::CIdleHandler
{
private:

    bool Initialized = false;

    UINT m_nDpiX = USER_DEFAULT_SCREEN_DPI;
    UINT m_nDpiY = USER_DEFAULT_SCREEN_DPI;

    WTL::CFont UIFont;

    WTL::CListViewCtrl ItemList;

    WTL::CStatic ContentControl;

    WTL::CButton ScanButton;
    WTL::CButton CleanUpButton;

   

    WTL::CMenu WindowMenu;
    WTL::CMenu HelpMenu;

private:

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        UNREFERENCED_PARAMETER(lpCreateStruct);

        EnableChildWindowDpiMessage(this->m_hWnd, TRUE);

        if (S_OK != ::MileGetDpiForMonitor(
            MonitorFromWindow(this->m_hWnd, MONITOR_DEFAULTTONEAREST),
            MDT_EFFECTIVE_DPI,
            reinterpret_cast<UINT*>(&this->m_nDpiX),
            reinterpret_cast<UINT*>(&this->m_nDpiY)))
        {
            this->m_nDpiX = WTL::CDC(this->GetDC()).GetDeviceCaps(LOGPIXELSX);
            this->m_nDpiY = WTL::CDC(this->GetDC()).GetDeviceCaps(LOGPIXELSY);
        }

        this->SetWindowTextW(
            L"M2-Team NSudo Sweeper " MILE_PROJECT_VERSION_STRING);

        this->UIFont.CreateFontW(
            MulDiv(20, m_nDpiY, USER_DEFAULT_SCREEN_DPI), // nHeight
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
            L"Segoe UI");

        this->HelpMenu.CreatePopupMenu();
        this->HelpMenu.AppendMenuW(MF_STRING | MF_ENABLED, 2001, L"&About");

        this->WindowMenu.CreateMenu();
        this->WindowMenu.AppendMenuW(MF_STRING | MF_ENABLED, 1001, L"&File");
        this->WindowMenu.AppendMenuW(MF_STRING | MF_ENABLED, HelpMenu, L"&Help");

        this->SetMenu(WindowMenu);

        CRect ClientRectangle;

        this->GetClientRect(ClientRectangle);

        CRect ItemListPosition = CRect(
            ClientRectangle.left + 4,
            ClientRectangle.top + 4,
            ClientRectangle.right - 4,
            ClientRectangle.bottom - 128);

        this->ItemList.Create(
            this->m_hWnd,
            ItemListPosition,
            nullptr,
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | WS_TABSTOP);
        this->ItemList.SetExtendedListViewStyle(
            LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
        this->ItemList.EnableGroupView(TRUE);

        CSize ButtonSize = CSize(96, 32);

        CRect ContentControlPosition = CRect(
            ClientRectangle.left + 4,
            ClientRectangle.bottom - 128 + 4,
            ClientRectangle.right - 4,
            ClientRectangle.bottom - 4 - ButtonSize.cy - 4);
        this->ContentControl.Create(
            this->m_hWnd,
            ContentControlPosition,
            L"Welcome to use the brand new NSudo Sweeper!\n(Under Construction)\n"
            L"欢迎使用全新的 NSudo Sweeper！\n（施工中）",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP);
        this->ContentControl.SetFont(UIFont);

        CRect ScanButtonPosition = CRect(
            ClientRectangle.right - 4 - ButtonSize.cx - 4 - ButtonSize.cx,
            ClientRectangle.bottom - 4 - ButtonSize.cy,
            ClientRectangle.right - 4 - ButtonSize.cx - 4,
            ClientRectangle.bottom - 4);
        this->ScanButton.Create(
            this->m_hWnd,
            ScanButtonPosition,
            L"Scan",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON);
        this->ScanButton.SetFont(UIFont);
        this->ScanButton.SetFocus();

        CRect CleanUpButtonPosition = CRect(
            ClientRectangle.right - 4 - ButtonSize.cx,
            ClientRectangle.bottom - 4 - ButtonSize.cy,
            ClientRectangle.right - 4,
            ClientRectangle.bottom - 4);
        this->CleanUpButton.Create(
            this->m_hWnd,
            CleanUpButtonPosition,
            L"Clean Up",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON);
        this->CleanUpButton.SetFont(UIFont);

        

        







        LVGROUP GroupInfo;

        GroupInfo.cbSize = LVGROUP_V5_SIZE;
        GroupInfo.mask = LVGF_HEADER | LVGF_GROUPID;
        GroupInfo.pszHeader = const_cast<LPWSTR>(L"Windows Specific");
        GroupInfo.iGroupId = 0;


        this->ItemList.AddGroup(&GroupInfo);

        this->ItemList.AddColumn(L"Name", 0);
        this->ItemList.AddColumn(L"Description", 1);



        LVITEMW ItemInfo = { 0 };

        ItemInfo.mask = LVIF_TEXT | LVIF_GROUPID;
        ItemInfo.pszText = const_cast<LPWSTR>(L"Compact OS");
        ItemInfo.iItem = 0;
        ItemInfo.iSubItem = 0;
        ItemInfo.iGroupId = 0;

        this->ItemList.InsertItem(&ItemInfo);

        ItemInfo.mask = LVIF_TEXT;
        ItemInfo.pszText = const_cast<LPWSTR>(L"Use Wof Compression to compress the system drive");
        ItemInfo.iItem = 0;
        ItemInfo.iSubItem = 1;
        ItemInfo.iGroupId = 0;

        this->ItemList.SetItem(&ItemInfo);

        ItemInfo.mask = LVIF_TEXT | LVIF_GROUPID;
        ItemInfo.pszText = const_cast<LPWSTR>(L"Temporary Folder");
        ItemInfo.iItem = 1;
        ItemInfo.iSubItem = 0;
        ItemInfo.iGroupId = 0;

        this->ItemList.InsertItem(&ItemInfo);


        for (int i = 2; i < 100; ++i)
        {
            ItemInfo.mask = LVIF_TEXT | LVIF_GROUPID;
            ItemInfo.pszText = const_cast<LPWSTR>(L"Test");
            ItemInfo.iItem = i;
            ItemInfo.iSubItem = 0;
            ItemInfo.iGroupId = 0;

            this->ItemList.InsertItem(&ItemInfo);

            ItemInfo.mask = LVIF_TEXT;
            ItemInfo.pszText = const_cast<LPWSTR>(L"Description of Test");
            ItemInfo.iItem = i;
            ItemInfo.iSubItem = 1;
            ItemInfo.iGroupId = 0;

            this->ItemList.SetItem(&ItemInfo);
        }


        this->ItemList.SetColumnWidth(0, LVSCW_AUTOSIZE);
        this->ItemList.SetColumnWidth(1, LVSCW_AUTOSIZE);

        Initialized = true;
        
        return 0;
    }

    void OnSize(UINT nType, CSize size)
    {
        UNREFERENCED_PARAMETER(nType);
        UNREFERENCED_PARAMETER(size);

        if (!Initialized)
        {
            return;
        }

        CRect ClientRectangle;

        this->GetClientRect(ClientRectangle);

        CRect ItemListPosition = CRect(
            ClientRectangle.left + MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.top + MulDiv(4, m_nDpiY, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.right - MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.bottom - MulDiv(128, m_nDpiY, USER_DEFAULT_SCREEN_DPI));

        this->ItemList.MoveWindow(ItemListPosition);
        this->ItemList.RedrawWindow();

        CSize ButtonSize = CSize(96, 32);

        CRect CleanUpButtonPosition = CRect(
            ClientRectangle.right - MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI) - MulDiv(ButtonSize.cx, m_nDpiX, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.bottom - MulDiv(4, m_nDpiY, USER_DEFAULT_SCREEN_DPI) - MulDiv(ButtonSize.cy, m_nDpiY, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.right - MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.bottom - MulDiv(4, m_nDpiY, USER_DEFAULT_SCREEN_DPI));

        this->CleanUpButton.MoveWindow(CleanUpButtonPosition);
        this->CleanUpButton.RedrawWindow();

        CRect ScanButtonPosition = CRect(
            ClientRectangle.right - MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI) - MulDiv(ButtonSize.cx, m_nDpiX, USER_DEFAULT_SCREEN_DPI) - MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI) - MulDiv(ButtonSize.cx, m_nDpiX, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.bottom - MulDiv(4, m_nDpiY, USER_DEFAULT_SCREEN_DPI) - MulDiv(ButtonSize.cy, m_nDpiY, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.right - MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI) - MulDiv(ButtonSize.cx, m_nDpiX, USER_DEFAULT_SCREEN_DPI) - MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.bottom - MulDiv(4, m_nDpiY, USER_DEFAULT_SCREEN_DPI));
        this->ScanButton.MoveWindow(ScanButtonPosition);
        this->ScanButton.RedrawWindow();

        CRect ContentControlPosition = CRect(
            ClientRectangle.left + MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.bottom - MulDiv(128, m_nDpiY, USER_DEFAULT_SCREEN_DPI) + MulDiv(4, m_nDpiY, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.right - MulDiv(4, m_nDpiX, USER_DEFAULT_SCREEN_DPI),
            ClientRectangle.bottom - MulDiv(4, m_nDpiY, USER_DEFAULT_SCREEN_DPI) - MulDiv(ButtonSize.cy, m_nDpiY, USER_DEFAULT_SCREEN_DPI) - MulDiv(4, m_nDpiY, USER_DEFAULT_SCREEN_DPI));
        this->ContentControl.MoveWindow(ContentControlPosition);
        this->ContentControl.RedrawWindow();

    }

    void OnDpiChanged(UINT nDpiX, UINT nDpiY, PRECT pRect)
    {
        UNREFERENCED_PARAMETER(nDpiX);
        UNREFERENCED_PARAMETER(nDpiY);
        UNREFERENCED_PARAMETER(pRect);

        this->m_nDpiX = nDpiX;
        this->m_nDpiY = nDpiY;

        this->UIFont.CreateFontW(
            MulDiv(20, m_nDpiY, USER_DEFAULT_SCREEN_DPI), // nHeight
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
            L"Segoe UI");

        this->ItemList.SetColumnWidth(0, LVSCW_AUTOSIZE);
        this->ItemList.SetColumnWidth(1, LVSCW_AUTOSIZE);

        this->CleanUpButton.SetFont(UIFont);
        this->ScanButton.SetFont(UIFont);
        this->ContentControl.SetFont(UIFont);

        this->MoveWindow(pRect);

        
    }

    void OnDestroy()
    {
        ::PostQuitMessage(0);
    }

    HBRUSH OnCtlColorStatic(WTL::CDCHandle dc, WTL::CStatic wndStatic)
    {
        UNREFERENCED_PARAMETER(wndStatic);

        dc.SetTextColor(RGB(0, 0, 0));
        dc.SetBkColor(RGB(255, 255, 255));

        return dc.GetCurrentBrush();
    }

private:

    virtual BOOL PreTranslateMessage(MSG* pMsg)
    {
        if (this->IsDialogMessageW(pMsg))
        {
            return TRUE;
        }

        return CFrameWindowImpl<CMainWindow>::PreTranslateMessage(pMsg);
    }

    virtual BOOL OnIdle()
    {
        this->UIUpdateToolBar();
        return FALSE;
    }

    BEGIN_MSG_MAP(CMainWindow)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_DPICHANGED(OnDpiChanged)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_CTLCOLORSTATIC(OnCtlColorStatic)
    END_MSG_MAP()

    BEGIN_UPDATE_UI_MAP(CMainWindow)

    END_UPDATE_UI_MAP()

public:
    CMainWindow() = default;
    ~CMainWindow() = default;
};

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    HRESULT hr = ::CoInitialize(nullptr);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = _Module.Init(nullptr, hInstance);
    if (FAILED(hr))
    {
        return hr;
    }

    CMainWindow MainWindow;

    CRect WindowRectangle = CRect(0, 0, 600, 450);

    if (!MainWindow.Create(nullptr, WindowRectangle))
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    MainWindow.CenterWindow();
    MainWindow.ShowWindow(nShowCmd);
    MainWindow.UpdateWindow();

    WTL::CMessageLoop MessageLoop;

    MessageLoop.AddMessageFilter(&MainWindow);
    MessageLoop.AddIdleHandler(&MainWindow);

    _Module.AddMessageLoop(&MessageLoop);

    int nRet = MessageLoop.Run();

    _Module.RemoveMessageLoop();

    _Module.Term();

    ::CoUninitialize();

    return nRet;
}
