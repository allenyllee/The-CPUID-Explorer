/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 15-Feb-07 | Created change log
* 15-Feb-07 | REQ #001: 64-bit awareness
* 15-Feb-07 | REQ #002: Handle dialogs with no controls or no active controls
* 15-Feb-07 | REQ #003: Generate virtual OnSetActive/OnKillActive calls
* 15-Feb-07 | REQ #004: ASSERT(FALSE) when creation errors occur
* 16-Feb-07 | REQ #005: ASSERT(FALSE) on out of range errors
*****************************************************************************/
#include "stdafx.h"
#include "TabView.h"
#include "resource.h"
#include "msg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//********************************
// Messages Sent
//********************************
DECLARE_MESSAGE(UWM_TAB_RESIZING)
DECLARE_MESSAGE(UWM_QUERY_GETMINMAXINFO)
//********************************
// Messages Received
//********************************
//********************************
// Messages Sent & Received
//********************************

/////////////////////////////////////////////////////////////////////////////
// CTabView implementation

IMPLEMENT_DYNCREATE (CTabView, CTabCtrl)

BEGIN_MESSAGE_MAP (CTabView, CTabCtrl)
        //{{AFX_MSG_MAP(CTabView)
        ON_WM_SIZE ()
        ON_WM_DESTROY ()
        ON_WM_SETFOCUS ()
        ON_WM_KILLFOCUS ()
        ON_WM_NCHITTEST()
        ON_WM_SETCURSOR()
        ON_WM_GETMINMAXINFO()
        //}}AFX_MSG_MAP
        ON_NOTIFY_REFLECT (TCN_SELCHANGING, OnSelChanging)
        ON_NOTIFY_REFLECT (TCN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()

/****************************************************************************
*                             CTabView::CTabView
* Effect: 
*       Constructor
*       Loads the left-drag cursor
****************************************************************************/

CTabView::CTabView()
     : CTabCtrl()
    {
     //LeftCursor = AfxGetApp()->LoadCursor(IDC_LEFT_DRAG);
    } // CTabView::CTabView

/****************************************************************************
*                             CTabView::~CTabView
* Effect: 
*       Destructor
****************************************************************************/

CTabView::~CTabView()
    {
     ::DestroyCursor(LeftCursor);
    } // CTabView::~CTabView

/****************************************************************************
*                          CTabView::PreCreateWindow
* Inputs:
*       CREATESTRUCT & cs: parameters for creation
* Result: BOOL
*       Value from superclass
* Effect: 
*       Forces common controls to be initialized.
****************************************************************************/

BOOL CTabView::PreCreateWindow (CREATESTRUCT& cs) 
   {
    //
    // Make sure the common controls library is initialized.
    //
    ::InitCommonControls ();
    //return CCtrlView::PreCreateWindow (cs);
    return CTabCtrl::PreCreateWindow(cs);
   }

/////////////////////////////////////////////////////////////////////////////
// Public interface

/****************************************************************************
*                              CTabView::AddPage
* Inputs:
*       LPCTSTR pszTitle: Page title
*       int nPageID: Page ID
*       LPCTSTR pszTemplateName: Dialog template name, or MAKEINTRESOURCE of
*               dialog template ID
*       CRuntimeClass * rtc: Runtime class of dialog
* Result: INT_PTR
*       Index of page that was added
* Effect: 
*       Adds the new page using the specified dialog and tab name
****************************************************************************/

INT_PTR CTabView::AddPage (LPCTSTR pszTitle, int nPageID, LPCTSTR pszTemplateName, CRuntimeClass * rtc)// REQ #001
   {
    // This fixes a semi-bug in Windows; see KB article Q145501

    ModifyStyleEx(0, WS_EX_CONTROLPARENT);
    
    //
    // Verify that the dialog template is compatible with CTabView
    // (debug builds only). If your app asserts here, make sure the dialog
    // resource you're adding to the view is a borderless child window and
    // is not marked visible.
    //
    DWORD inputstyle = GetDialogStyle(pszTemplateName);
#ifdef _DEBUG //----------------------------------------------------------------+
    if (pszTemplateName != NULL)                                             // |
       {                                                                     // |
        BOOL bResult = CheckDialogTemplate (pszTemplateName);                // |
        ASSERT (bResult);                                                    // |
       }                                                                     // |
#endif //-----------------------------------------------------------------------+
    //
    // Add a page to the tab control.
    //
    TC_ITEM item;
    item.mask = TCIF_TEXT;
    item.pszText = (LPTSTR) pszTitle;
    int nIndex = GetTabCtrl ().GetItemCount ();
        
    if (GetTabCtrl ().InsertItem (nIndex, &item) == -1)
       { /* failed */                                               // REQ #004
        ASSERT(FALSE);                                              // REQ #004
        return -1;
       } /* failed */                                               // REQ #004

    //
    // Add controls to the page.
    //
    if (pszTemplateName == NULL)
       {
        //
        // Not much to do if pszTemplateName is NULL.
        //
        INT_PTR nArrayIndex = m_pPages.Add (NULL);                  // REQ #001
        ASSERT (nIndex == nArrayIndex);

        nArrayIndex = m_nPageIDs.Add (nPageID);
        ASSERT (nIndex == nArrayIndex);

        OnInitPage (nIndex, nPageID);
        m_hFocusWnd.Add (NULL);
       }
    else
       {
        //
        // Create a modeless dialog box.
        //
        CPropertyPage * pDialog = (CPropertyPage *)rtc->CreateObject(); // REQ #003
        
        if (pDialog == NULL)
           {
            GetTabCtrl ().DeleteItem (nIndex);
            ASSERT(FALSE);                                          // REQ #004
            return -1;
           }

        if (!pDialog->Create (pszTemplateName, this))
           {
            GetTabCtrl ().DeleteItem (nIndex);
            pDialog->DestroyWindow ();
            //delete pDialog;
            ASSERT(FALSE);                                          // REQ #004
            return -1;
           }
        DWORD dlgstyle = pDialog->GetStyle();
        if((inputstyle & WS_VSCROLL) == WS_VSCROLL && (dlgstyle & WS_VSCROLL) != WS_VSCROLL)
                    pDialog->ModifyStyle(0, WS_VSCROLL);
        //
        // Record the address of the dialog object and the page ID.
        //
        INT_PTR nArrayIndex = m_pPages.Add (pDialog);               // REQ #001
        ASSERT (nIndex == nArrayIndex);

        nArrayIndex = m_nPageIDs.Add (nPageID);
        ASSERT (nIndex == nArrayIndex);

        //
        // Size and position the dialog box within the view.
        //
        pDialog->SetParent (this); // Just to be sure

        CRect rect;
        GetClientRect (&rect);

        if (rect.Width () > 0 && rect.Height () > 0)
           ResizeDialog (nIndex, rect.Width (), rect.Height ());

        //
        // Initialize the page.
        //
        if (OnInitPage (nIndex, nPageID))
           { /* initialized */
            //
            // Make the first control in the dialog is the one that
            // receives the input focus when the page is displayed.
            //
            CWnd * top = pDialog->GetTopWindow ();                  // REQ #002
            HWND hwndFocus = NULL;                                  // REQ #002
            if(top != NULL)                                         // REQ #002
                { /* has controls */                                // REQ #002
                 hwndFocus = top->m_hWnd;                           // REQ #002
                } /* has controls */                                // REQ #002
            nArrayIndex = m_hFocusWnd.Add (hwndFocus);
            ASSERT (nIndex == nArrayIndex);
           } /* initialized */
        else
           {
            //
            // Make the control that currently has the input focus is the one
            // that receives the input focus when the page is displayed.
            //
            m_hFocusWnd.Add (::GetFocus ());
           }

        //
        // If this is the first page added to the view, make it visible.
        //
        if (nIndex == 0)
           { /* first */
            pDialog->OnSetActive();                                 // REQ #003
            pDialog->ShowWindow (SW_SHOW);
           } /* first */
       }
    return nIndex;
   }

/****************************************************************************
*                              CTabView::AddPage
* Inputs:
*       LPCTSTR pszTitle: Tab name
*       int nPageID: Page ID
*       int nTempateID: Template ID, dialog resource number
*       CRuntimeClass * rtc: Runtime class for creation
* Result: INT_PTR
*       Page index
* Effect: 
*       Converts the dialog ID to a MAKEINTRESOURCE then calls the
*       lower-level routine
****************************************************************************/

INT_PTR CTabView::AddPage (LPCTSTR pszTitle, int nPageID, int nTemplateID, CRuntimeClass * rtc)// REQ #001
   {
    return AddPage (pszTitle, nPageID, MAKEINTRESOURCE (nTemplateID), rtc);
   }

/****************************************************************************
*                              CTabView::AddPage
* Inputs:
*       UINT title: String table entry for title
*       int nPageID: ID of page
*       int TemplateID: ID of dialog template
*       CRuntimeClass * rtc: Runtime class designator
* Result: INT_PTR
*       Index of page added
* Effect: 
*       Adds a new page to the control
*       Converts the title string ID to a string and calls the underlying
*       function.
****************************************************************************/

INT_PTR CTabView::AddPage(UINT title, int nPageID, int nTemplateID, CRuntimeClass * rtc) // REQ #001
    {
     CString s;
     s.LoadString(title);
     return AddPage(s, nPageID, nTemplateID, rtc);
    } // CTabView::AddPage

/****************************************************************************
*                            CTabView::RemovePage
* Inputs:
*       int nIndex: Index of page to be removed
* Result: BOOL
*       TRUE if successful
*       FALSE if index is out of range
* Effect: 
*       Removes the page from the tab control
****************************************************************************/

BOOL CTabView::RemovePage (INT_PTR nIndex)                          // REQ #001
   {
    if (nIndex >= GetTabCtrl ().GetItemCount ())
       return FALSE;

    //
    // Notify derived classes that the page is being destroyed.
    //
    OnDestroyPage (nIndex, m_nPageIDs[nIndex]);

    //
    // Switch pages if the page being deleted is the current page and it's
    // not the only remaining page.
    //
    INT_PTR nCount = GetTabCtrl ().GetItemCount ();                 // REQ #001
    if (nCount > 1 && nIndex == GetTabCtrl ().GetCurSel ())
       {
        INT_PTR nPage = nIndex + 1;                                 // REQ #001
        if (nPage >= nCount)
           nPage = nCount - 2;
        ActivatePage (nPage);
       }

    //
    // Remove the page from the tab control.
    //
    GetTabCtrl ().DeleteItem ((int)nIndex);

    //
    // Destroy the dialog (if any) that represents the page.
    //
    CPropertyPage* pDialog = (CPropertyPage *)m_pPages[nIndex];     // REQ #003
    if (pDialog != NULL)
       {
        pDialog->DestroyWindow ();      
        //delete pDialog;
       }

    //
    // Clean up, repaint, and return.
    //
    m_pPages.RemoveAt (nIndex);
    m_hFocusWnd.RemoveAt (nIndex);
    m_nPageIDs.RemoveAt (nIndex);
    Invalidate ();
    return TRUE;
   }

/****************************************************************************
*                           CTabView::GetPageCount
* Result: INT_PTR
*       The number of pages in the tab control
****************************************************************************/

INT_PTR CTabView::GetPageCount ()                                   // REQ #001
   {
    return GetTabCtrl().GetItemCount ();
   }

/****************************************************************************
*                           CTabView::GetPageTitle
* Inputs:
*       INT_PTR nIndex: Index of page
*       CString & strTitle: Title string to be set
* Result: BOOL
*       TRUE if successful
*       FALSE in index out of range
* Effect: 
*       ¶
****************************************************************************/

BOOL CTabView::GetPageTitle (INT_PTR nIndex, CString &strTitle)     // REQ #001
   {
    if (nIndex >= GetTabCtrl ().GetItemCount ())
       return FALSE;

    TCHAR szTitle[1024];

    TC_ITEM item;
    item.mask = TCIF_TEXT;
    item.pszText = szTitle;
    item.cchTextMax = sizeof szTitle / sizeof (TCHAR);

    if (!GetTabCtrl ().GetItem ((int)nIndex, &item))
       return FALSE;

    strTitle = item.pszText;
    return TRUE;
   }

/****************************************************************************
*                           CTabView::GetPageTitle
* Inputs:
*       CWnd * page: Page
*       CString & title: Place to put title
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Sets the title string to hold the page title
****************************************************************************/

BOOL CTabView::GetPageTitle(CWnd * wnd, CString & title)
    {
     INT_PTR n = GetIndex(wnd);                                     // REQ #001
     if(n < 0)
        return FALSE;
     return GetPageTitle(n, title);
    } // CTabView::GetPageTitle

/****************************************************************************
*                           CTabView::SetPageTitle
* Inputs:
*       INT_PTR nIndex: Index of page whose title is to be set      // REQ #001
*       LPCTSTR pszTitle: new title string to set
* Result: BOOL
*       TRUE if successful
*       FALSE if index out of range
* Effect: 
*       Sets the page title to the value supplied
****************************************************************************/

BOOL CTabView::SetPageTitle (INT_PTR nIndex, LPCTSTR pszTitle)      // REQ #001
   {
    if (nIndex >= GetTabCtrl ().GetItemCount ())
       return FALSE;

    TC_ITEM item;
    item.mask = TCIF_TEXT;
    item.pszText = (LPTSTR) pszTitle;
        
    BOOL bResult = GetTabCtrl ().SetItem ((int)nIndex, &item);
    if (bResult)
       Invalidate ();
    return bResult;
   }

/****************************************************************************
*                             CTabView::GetPageID
* Inputs:
*       INT_PTR nIndex: Index of page
* Result: int
*       The ID of the page, -1 if the value nIndex is out of range
****************************************************************************/

int CTabView::GetPageID (INT_PTR nIndex)                            // REQ #001
   {
    if (nIndex >= GetTabCtrl ().GetItemCount ())
       return -1;

    return m_nPageIDs[nIndex];
   }

/****************************************************************************
*                             CTabView::SetPageID
* Inputs:
*       INT_PTR nIndex: Index of page
*       int nPageID: new page ID to set
* Result: int
*       -1 i the nIndex value is out of range
*       otherwise, the previous page ID
* Effect: 
*       Changes the page ID of the page
****************************************************************************/

int CTabView::SetPageID (INT_PTR nIndex, int nPageID)               // REQ #001
   {
    if (nIndex >= GetTabCtrl ().GetItemCount ())
       return -1;

    int nOldPageID = m_nPageIDs[nIndex];
    m_nPageIDs[nIndex] = nPageID;
    return nOldPageID;
   }

/****************************************************************************
*                           CTabView::ActivatePage
* Inputs:
*       INT_PTR nIndex: Index of page to activate
* Result: BOOL
*       TRUE if activated
*       FALSE if nIndex is out of rnage
* Effect: 
*       Activates the page
* Notes:
*       This retains the control that has the focus, so the control will
*       get the focus when it is reactivated
****************************************************************************/

BOOL CTabView::ActivatePage (INT_PTR nIndex)                        // REQ #001
   {
    if (nIndex >= GetTabCtrl ().GetItemCount ())
       return FALSE;

    //
    // Do nothing if the specified page is already active.
    //
    if (nIndex == GetTabCtrl ().GetCurSel ())
       return TRUE;

    //
    // Deactivate the current page.
    //
    INT_PTR nOldIndex = GetTabCtrl ().GetCurSel ();                 // REQ #001

    if (nIndex != -1)
       {
        CPropertyPage * pDialog = (CPropertyPage *)m_pPages[nOldIndex]; // REQ #003
        if (pDialog != NULL)
           {
            m_hFocusWnd[nOldIndex] = ::GetFocus ();
            pDialog->ShowWindow (SW_HIDE);
            pDialog->OnKillActive();                                // REQ #003
           }
       }

    //
    // Activate the new one.
    //
    GetTabCtrl ().SetCurSel ((int)nIndex);
    CPropertyPage* pDialog = (CPropertyPage *)m_pPages[nIndex];     // REQ #003

    if (pDialog != NULL)
       {
        ::SetFocus (m_hFocusWnd[nIndex]);
        CRect rect;
        GetClientRect (&rect);
        ResizeDialog ((int)nIndex, rect.Width (), rect.Height ());
        pDialog->OnSetActive();                                     // REQ #003
        pDialog->ShowWindow (SW_SHOW);
       }
    return TRUE;
   }

/****************************************************************************
*                           CTabView::GetActivePage
* Result: INT_PTR
*       
* Effect: 
*       Returns the index of the page which is currently active
****************************************************************************/

INT_PTR CTabView::GetActivePage ()                                  // REQ #001
   {
    return GetTabCtrl ().GetCurSel ();
   }

/****************************************************************************
*                              CTabView::GetPage
* Inputs:
*       INT_PTR nIndex: Index of page
* Result: CWnd *
*       The window reference for the specified page, or NULL if nIndex is
*       out of range
****************************************************************************/

CWnd* CTabView::GetPage (INT_PTR nIndex)                            // REQ #001
   {
    ASSERT(nIndex >= 0);                                      if (nIndex < 0 || nIndex >= GetTabCtrl ().GetItemCount ())
       return NULL;
           // REQ #005

    return (CWnd*) m_pPages[nIndex];
   }

/****************************************************************************
*                           CTabView::GetPageIndex
* Inputs:
*       int nPageID: ID of a page
* Result: INT_PTR
*       Index of the page
*       -1 if there are no pages or the nPageID is not found
****************************************************************************/

INT_PTR CTabView::GetPageIndex (int nPageID)                        // REQ #001
   {
    INT_PTR nCount = GetTabCtrl ().GetItemCount ();                 // REQ #001
    if (nCount == 0)
       return -1;

    for (INT_PTR i = 0; i < nCount; i++)                            // REQ #001
       {
        if (m_nPageIDs[i] == nPageID)
           return i;
       }

    return -1;
   }

/////////////////////////////////////////////////////////////////////////////
// Private helper functions

/****************************************************************************
*                          CTabView::GetDialogStyle
* Inputs:
*       LPCTSTR pszTemplateName: Name of template
* Result: DWORD
*       The style bits from the template
****************************************************************************/

DWORD CTabView::GetDialogStyle(LPCTSTR pszTemplateName)
    {
     ASSERT (pszTemplateName != NULL);
     HINSTANCE hInstance = AfxFindResourceHandle (pszTemplateName, RT_DIALOG);
     HRSRC hResource = ::FindResource (hInstance, pszTemplateName, RT_DIALOG);

     if (hResource == NULL)
        return FALSE; // Resource doesn't exist

     HGLOBAL hTemplate = LoadResource (hInstance, hResource);
     ASSERT (hTemplate != NULL);

    //
    // Get the dialog's style bits.
    //
     DLGTEMPLATEEX* pTemplate = (DLGTEMPLATEEX*) LockResource (hTemplate);

    // Pick up the style. Note that there are two different structures depending
    // on the 'signature' field of the template. 0xFFFF means it is a DLGTEMPLATEEX
    // and anything else is a conventional DLGTEMPLATE
     DWORD dwStyle;
     if (pTemplate->signature == 0xFFFF)
        dwStyle = pTemplate->style;
     else
        dwStyle = ((DLGTEMPLATE*) pTemplate)->style;

     UnlockResource (hTemplate);
     FreeResource (hTemplate);

     return dwStyle;
    } // CTabView::GetDialogStyle

#ifdef _DEBUG //----------------------------------------------------------------+
BOOL CTabView::CheckDialogTemplate (LPCTSTR pszTemplateName)                 // |
   {                                                                         // |
    //                                                                       // |
    // Verify that the dialog resource exists.                               // |
    //                                                                       // |
    ASSERT (pszTemplateName != NULL);                                        // |
    HINSTANCE hInstance = AfxFindResourceHandle (pszTemplateName, RT_DIALOG);// |
    HRSRC hResource = ::FindResource (hInstance, pszTemplateName, RT_DIALOG);// |
                                                                             // |
    if (hResource == NULL)                                                   // |
       return FALSE; // Resource doesn't exist                               // |
                                                                             // |
    HGLOBAL hTemplate = LoadResource (hInstance, hResource);                 // |
    ASSERT (hTemplate != NULL);                                              // |
                                                                             // |
    //                                                                       // |
    // Get the dialog's style bits.                                          // |
    //                                                                       // |
    DLGTEMPLATEEX* pTemplate = (DLGTEMPLATEEX*) LockResource (hTemplate);    // |
                                                                             // |
    // Pick up the style. Note that there are two different structures depending
    // on the 'signature' field of the template. 0xFFFF means it is a DLGTEMPLATEEX
    // and anything else is a conventional DLGTEMPLATE                       // |
    DWORD dwStyle;                                                           // |
    if (pTemplate->signature == 0xFFFF)                                      // |
       dwStyle = pTemplate->style;                                           // |
    else                                                                     // |
       dwStyle = ((DLGTEMPLATE*) pTemplate)->style;                          // |
                                                                             // |
    UnlockResource (hTemplate);                                              // |
    FreeResource (hTemplate);                                                // |
                                                                             // |
    //                                                                       // |
    // Verify that the dialog is an invisible child window.                  // |
    //                                                                       // |
    if (dwStyle & WS_VISIBLE)                                                // |
       return FALSE; // WS_VISIBLE flag is set                               // |
                                                                             // |
    if (!(dwStyle & WS_CHILD))                                               // |
       return FALSE; // WS_CHILD flag isn't set                              // |
                                                                             // |
    //                                                                       // |
    // Verify that the dialog has no border and no title bar.                // |
    //                                                                       // |
    if (dwStyle & (WS_BORDER | WS_THICKFRAME | DS_MODALFRAME))               // |
       return FALSE; // One or more border flags are set                     // |
                                                                             // |
    if (dwStyle & WS_CAPTION)                                                // |
       return FALSE; // WS_CAPTION flag is set                               // |
                                                                             // |
    return TRUE;                                                             // |
   }                                                                         // |
#endif //-----------------------------------------------------------------------+

void CTabView::ResizeDialog (INT_PTR nIndex, int cx, int cy)        // REQ #001
   {
    if (nIndex != -1)
       {
        CPropertyPage* pDialog = (CPropertyPage*)m_pPages[nIndex];  // REQ #003

        if (pDialog != NULL)
           {
            CRect rect;
            GetTabCtrl ().GetItemRect ((int)nIndex, &rect);

            int x;
            int y;
            int nWidth;
            int nHeight;
            DWORD dwStyle = GetTabCtrl ().GetStyle ();

            if (dwStyle & TCS_VERTICAL)
               { // Vertical tabs
                int nTabWidth =
                               rect.Width () * GetTabCtrl ().GetRowCount ();
                x = (dwStyle & TCS_RIGHT) ? 4 : nTabWidth + 4;
                y = 4;
                nWidth = cx - nTabWidth - 8;
                nHeight = cy - 8;
               }
            else
               { // Horizontal tabs
                int nTabHeight =
                                rect.Height () * GetTabCtrl ().GetRowCount ();
                x = 4;
                y = (dwStyle & TCS_BOTTOM) ? 4 : nTabHeight + 4;
                nWidth = cx - 8;
                nHeight = cy - nTabHeight - 8;
                // We want to allow scrolling
                pDialog->GetWindowRect(&OriginalWindowSize);
               }
            pDialog->SetWindowPos (NULL, x, y, nWidth, nHeight, SWP_NOZORDER);
           }
       }
   }

/////////////////////////////////////////////////////////////////////////////
// Overridables

BOOL CTabView::OnInitPage (INT_PTR nIndex, int nPageID)             // REQ #001
   {
    //
    // Override in derived class to initialize pages.
    //
    return TRUE;
   }

void CTabView::OnActivatePage (INT_PTR nIndex, int nPageID)         // REQ #001
   {
    //
    // Override in derived class to respond to page activations.
    //
   }

void CTabView::OnDeactivatePage (INT_PTR nIndex, int nPageID)       // REQ #001
   {
    //
    // Override in derived class to respond to page deactivations.
    //
   }

void CTabView::OnDestroyPage (INT_PTR nIndex, int nPageID)          // REQ #001
   {
    //
    // Override in derived class to free resources.
    //
   }

/////////////////////////////////////////////////////////////////////////////
// Message handlers

void CTabView::OnSize (UINT nType, int cx, int cy)
   {
    //
    // When the view's size changes, resize the dialog (if any) shown in the
    // view to prevent the dialog from clipping the view's inside border.
    //
    //CCtrlView::OnSize (nType, cx, cy);
    CTabCtrl::OnSize (nType, cx, cy);
    ResizeDialog (GetTabCtrl ().GetCurSel (), cx, cy);
    GetParent()->SendMessage(UWM_TAB_RESIZING, (WPARAM)cx, (LPARAM)cy);
   }

void CTabView::OnSelChanging (NMHDR* pNMHDR, LRESULT* pResult)
   {
    //
    // Notify derived classes that the selection is changing.
    //
    INT_PTR nIndex = GetTabCtrl ().GetCurSel ();                    // REQ #001
    if (nIndex == -1)
       return;

    OnDeactivatePage (nIndex, m_nPageIDs[nIndex]);

    //
    // Save the input focus and hide the old page.
    //
    CPropertyPage* pDialog = (CPropertyPage *)m_pPages[nIndex];     // REQ #003

    if (pDialog != NULL)
       {
        m_hFocusWnd[nIndex] = ::GetFocus ();
        pDialog->OnKillActive();                                    // REQ #003
        pDialog->ShowWindow (SW_HIDE);
       }
    *pResult = 0;
   }

void CTabView::OnSelChange (NMHDR* pNMHDR, LRESULT* pResult)
   {
    INT_PTR nIndex = GetTabCtrl ().GetCurSel ();                    // REQ #001
    if (nIndex == -1)
       return;
    
    //
    // Show the new page.
    //
    CPropertyPage * pDialog = (CPropertyPage *)m_pPages[nIndex];    // REQ #003

    if (pDialog != NULL)
       {
        ::SetFocus (m_hFocusWnd[nIndex]);
        CRect rect;
        GetClientRect (&rect);
        ResizeDialog (nIndex, rect.Width (), rect.Height ());
        pDialog->OnSetActive();                                     // REQ #003
        pDialog->ShowWindow (SW_SHOW);
       }

    //
    // Notify derived classes that the selection has changed.
    //
    OnActivatePage (nIndex, m_nPageIDs[nIndex]);
    *pResult = 0;
   }

void CTabView::OnSetFocus (CWnd* pOldWnd) 
   {
    //CCtrlView::OnSetFocus (pOldWnd);
    CTabCtrl::OnSetFocus (pOldWnd);
        
    //
    // Set the focus to a control on the current page.
    //
    INT_PTR nIndex = GetTabCtrl ().GetCurSel ();                    // REQ #001
    if (nIndex != -1)
       ::SetFocus (m_hFocusWnd[nIndex]);        
   }

void CTabView::OnKillFocus (CWnd* pNewWnd) 
   {
    //CCtrlView::OnKillFocus (pNewWnd);
    CTabCtrl::OnKillFocus (pNewWnd);
        
    //
    // Save the HWND of the control that holds the input focus.
    //
    INT_PTR nIndex = GetTabCtrl ().GetCurSel ();                    // REQ #001
    if (nIndex != -1)
       m_hFocusWnd[nIndex] = ::GetFocus ();     
   }

void CTabView::OnDestroy () 
   {
    INT_PTR nCount = m_pPages.GetSize ();                           // REQ #001

    //
    // Destroy dialogs and delete dialog objects.
    //
    if (nCount > 0)
       {
        for (INT_PTR i = nCount - 1; i >= 0; i--)                   // REQ #001
           {
            OnDestroyPage (i, m_nPageIDs[i]);
            CPropertyPage* pDialog = (CPropertyPage *)m_pPages[i];  // REQ #003
            if (pDialog != NULL)
               {
                pDialog->DestroyWindow ();
                //delete pDialog;
               }
           }
       }
    
    //
    // Clean up the internal arrays.
    //
    m_pPages.RemoveAll ();
    m_hFocusWnd.RemoveAll ();
    m_nPageIDs.RemoveAll ();

    //CCtrlView::OnDestroy ();
    CTabCtrl::OnDestroy ();
   }

/****************************************************************************
*                             CTabView::GetIndex
* Inputs:
*       CWnd * wnd: Window handle of page
* Result: INT_PTR
*       Index value, -1 if not found
****************************************************************************/

INT_PTR CTabView::GetIndex(CWnd * wnd)                              // REQ #001
    {
     for(INT_PTR i = 0; i < m_pPages.GetSize(); i++)                // REQ #001
        { /* search */
         if(wnd == m_pPages[i])
            return i;
        } /* search */
     return -1;
    } // CTabView::GetIndex

/****************************************************************************
*                            CTabView::OnNcHitTest
* Inputs:
*       CPoint point: Point, in screen coordinates
* Result: UINT
*       HT* codes
* Effect: 
*       If the cursor is on the left margin of the control returns
*       HTLEFT
****************************************************************************/

UINT CTabView::OnNcHitTest(CPoint point) 
   {
    UINT result = CTabCtrl::OnNcHitTest(point);
    CRect r;
    GetWindowRect(&r);
    if(point.x == r.left || point.x == r.left + 1)
       return HTLEFT;

    if(point.y == r.bottom -2 || point.y == r.bottom - 1|| point.y == r.bottom)
       return HTBOTTOM;
    return result;
   }

/****************************************************************************
*                            CTabView::OnSetCursor
* Inputs:
*       CWnd * pWnd: Window reference
*       UINT nHitTest: Hit-test code from OnNcHitTest
*       UINT message: Message being processed
* Result: BOOL
*       TRUE if set to the <-||-> cursor
*       whatever the superclass returns otherwise
* Effect: 
*       Sets the cursor to the left-drag cursor if appropriate
****************************************************************************/

BOOL CTabView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
   {
    if(nHitTest == HTLEFT)
       { /* at left */
        ::SetCursor(LeftCursor);
        return TRUE;
       } /* at left */
        
    return CTabCtrl::OnSetCursor(pWnd, nHitTest, message);
   }


/****************************************************************************
*                          CTabView::OnGetMinMaxInfo
* Inputs:
*       MINMAXINFO FAR * lpMMI: Dragging structure
* Result: void
*       
* Effect: 
*       Limits the size of the drag so that it cannot be dragged below
*       a size that allows the full parent set of controls to be displayed
****************************************************************************/

void CTabView::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
   {
    CTabCtrl::OnGetMinMaxInfo(lpMMI);
    // TODO: Add your message handler code here and/or call default
        
    GetParent()->SendMessage(UWM_QUERY_GETMINMAXINFO, (WPARAM)lpMMI, (LPARAM)m_hWnd);
   }
