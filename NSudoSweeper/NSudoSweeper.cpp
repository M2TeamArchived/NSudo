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

#include "NSudoSweeperVersion.h"

#include <atlbase.h>

#include "WTL/atlapp.h"
#include "WTL/atlcrack.h"
#include "WTL/atlctrls.h"
#include "WTL/atlframe.h"
#include "WTL/atlmisc.h"

CAppModule _Module;

class CMainWindow :
    public CFrameWindowImpl<CMainWindow>,
    public CUpdateUI<CMainWindow>,
    public CMessageFilter,
    public CIdleHandler
{
private:

    CFont UIFont;

    CStatic ContentControl;

    CListViewCtrl ItemList;

    CMenu WindowMenu;
    CMenu HelpMenu;

private:



private:

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
            L"Segoe UI");

        auto x = CRect(50, 50, 300, 180);

        this->ContentControl.Create(
            this->m_hWnd,
            x,
            L"Welcome to use the brand new NSudo Sweeper!\n(Under Construction)\n"
            L"欢迎使用全新的 NSudo Sweeper！\n（施工中）",
            WS_CHILD | WS_VISIBLE);

        this->ContentControl.SetFont(UIFont);

        auto y = CRect(50, 200, 600, 300);

        this->ItemList.Create(
            this->m_hWnd,
            y,
            nullptr,
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL);

        this->ItemList.SetExtendedListViewStyle(
            LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);



        this->ItemList.EnableGroupView(TRUE);

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


        this->ItemList.SetColumnWidth(0, LVSCW_AUTOSIZE);
        this->ItemList.SetColumnWidth(1, LVSCW_AUTOSIZE);

        
        this->HelpMenu.CreatePopupMenu();
        this->HelpMenu.AppendMenuW(MF_STRING | MF_ENABLED, 2000, L"&Content");
        this->HelpMenu.AppendMenuW(MF_STRING | MF_ENABLED, 2001, L"&About");
     
        this->WindowMenu.CreateMenu();
        this->WindowMenu.AppendMenuW(MF_STRING | MF_ENABLED, HelpMenu, L"&Help");

        this->SetMenu(WindowMenu);
        
        return 0;
    }

    void OnDestroy()
    {
        ::PostQuitMessage(0);
    }

private:

    virtual BOOL PreTranslateMessage(MSG* pMsg)
    {
        return CFrameWindowImpl<CMainWindow>::PreTranslateMessage(pMsg);
    }

    virtual BOOL OnIdle()
    {
        this->UIUpdateToolBar();
        return FALSE;
    }

    BEGIN_MSG_MAP(CMainWindow)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
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

    if (!MainWindow.Create())
    {
        return ::HRESULT_FROM_WIN32(::GetLastError());
    }

    MainWindow.ShowWindow(nShowCmd);
    MainWindow.UpdateWindow();

    CMessageLoop MessageLoop;

    MessageLoop.AddMessageFilter(&MainWindow);
    MessageLoop.AddIdleHandler(&MainWindow);

    _Module.AddMessageLoop(&MessageLoop);

    int nRet = MessageLoop.Run();

    _Module.RemoveMessageLoop();

    _Module.Term();

    ::CoUninitialize();

    return nRet;
}
