// Leaves.cpp : implementation file
//

#include "stdafx.h"
#include "CPUID.h"
#include "Leaves.h"
#include "msg.h"
#include ".\leaves.h"

DECLARE_MESSAGE(UWM_DISABLE)

// CLeaves dialog

IMPLEMENT_DYNAMIC(CLeaves, CPropertyPage)
CLeaves::CLeaves(UINT idd)
        : CPropertyPage(idd)
{
}

CLeaves::~CLeaves()
{
}

void CLeaves::DoDataExchange(CDataExchange* pDX)
{
        CPropertyPage::DoDataExchange(pDX);
        if(GetDlgItem(IDC_PLATFORM) != NULL)
           DDX_Control(pDX, IDC_PLATFORM, c_Platform);
}


BEGIN_MESSAGE_MAP(CLeaves, CPropertyPage)
       ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotify)
       ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotify)
       ON_REGISTERED_MESSAGE(UWM_DISABLE, OnDisable)
       ON_WM_SIZE()
END_MESSAGE_MAP()


// CLeaves message handlers

/****************************************************************************
*                            CLeaves::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Enables tooltips
****************************************************************************/

BOOL CLeaves::OnInitDialog()
    {
    CPropertyPage::OnInitDialog();

    EnableToolTips();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
    }

/****************************************************************************
*                         CLeaves::OnToolTipNotify
* Inputs:
*       UINT id: Control ID
*       NMHDR * pNMHDR:
*       LRESULT * pResult:
* Result: BOOL
*       TRUE if handled
*       FALSE if not
* Effect: 
*       Handles tooltip notifications
* Notes:
* typedef struct {
*      NMHDR     hdr;        // required for all WM_NOTIFY messages
*      // typedef struct tagNMHDR {
*      //    HWND hwndFrom;
*      //    UINT idFrom;
*      //    UINT code;
*      // } NMHDR;
*      LPTSTR    lpszText;   // see below
*      TCHAR     szText[80]; // buffer for tool tip text
*      HINSTANCE hinst;      // see below
*      UINT      uflags;     // flag indicating how to interpret the 
*                            // idFrom member of the NMHDR structure
*                            // that is included in the structure
*     } TOOLTIPTEXT, FAR *LPTOOLTIPTEXT;
*
****************************************************************************/

BOOL CLeaves::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
   {
    CWnd * wnd = CWnd::FromHandle((HWND)pNMHDR->idFrom);

    if(wnd->SendMessage( WM_NOTIFY, pNMHDR->idFrom, (LPARAM)pNMHDR))
       return TRUE;

    return FALSE;
   } // CLeaves::OnToolTipNotify

/****************************************************************************
*                             CLeaves::OnDisable
* Inputs:
*       WPARAM: ignored
*       LPARAM: ignored
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Disables all controls in the page
****************************************************************************/

LRESULT CLeaves::OnDisable(WPARAM, LPARAM)
    {
     for(CWnd * wnd = GetWindow(GW_CHILD); wnd != NULL; wnd = wnd->GetWindow(GW_HWNDNEXT))
        wnd->EnableWindow(FALSE);
     return 0;
    } // CLeaves::OnDisable

/****************************************************************************
*                           CLeaves::PostNcDestroy
* Result: void
*       
* Effect: 
*       deletes the object
****************************************************************************/

void CLeaves::PostNcDestroy()
    {
     CPropertyPage::PostNcDestroy();

     delete this;
    } // CLeaves::PostNcDestroy

/****************************************************************************
*                            CLeaves::SetFixedFont
* Inputs:
*       CWnd & wnd: Window to set
* Result: void
*       
* Effect: 
*       Sets a fixed font
****************************************************************************/

void CLeaves::SetFixedFont(CWnd & wnd)
    {
     if(font.GetSafeHandle() == NULL)
        { /* create font */
         CFont * f;
         f = GetFont();
         ASSERT(f != NULL);

         LOGFONT lf;
         f->GetLogFont(&lf);
         StringCchCopy(lf.lfFaceName, sizeof(lf.lfFaceName)/sizeof(TCHAR), _T("Courier New"));

         lf.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
         font.CreateFontIndirect(&lf);
        } /* create font */

     wnd.SetFont(&font);
    } // CLeaves::SetFixedFont

/****************************************************************************
*                               CLeaves::DoAlign
* Inputs:
*       UINT ctlid: Control id of control to align to
*       UINT textid: Control id of caption
* Result: void
*       
* Effect: 
*       Aligns the controls
****************************************************************************/

void CLeaves::DoAlign(UINT ctlid, UINT textid)
    {
     /*****************************************************************************
                                      +----+
                                      |    |<---C
                                      |    |
                                      :    :
                T                     :    :
                |                     |    | 
                V                     |    |
             +-----------------------------+
             |                        |    |  Note vertical control overlaps horizontal control
             +------------------------+----+
     ******************************************************************************/
     CRect C;
     CWnd * ctl = GetDlgItem(ctlid);
     ASSERT(ctl != NULL);
     if(ctl == NULL)
        return;

     ctl->GetWindowRect(&C);

     CRect T;
     CWnd * text = GetDlgItem(textid);
     ASSERT(text != NULL);
     if(text == NULL)
        return;
     text->GetWindowRect(&T);

     C.bottom = T.bottom;
     ctl->SetWindowPos(NULL,
                       0, 0,  // no move
                       C.Width(), C.Height(),
                       SWP_NOMOVE | SWP_NOZORDER);
    } // CLeaves::DoAlign

/****************************************************************************
*                               CLeaves::OnSize
* Inputs:
*       UINT nType: Type of resize
*       int cx: New width
*       int cy: New height
* Result: void
*       
* Effect: 
*       If the c_Platform control is specified, makes sure it stays in the
*       lower left corner of the window   
****************************************************************************/

void CLeaves::OnSize(UINT nType, int cx, int cy)
    {
     CPropertyPage::OnSize(nType, cx, cy);

     if(c_Platform.GetSafeHwnd() != NULL)
        { /* move it */
         CRect platform;
         c_Platform.GetWindowRect(&platform);
         ScreenToClient(&platform);

         CRect c;
         GetClientRect(&c);
         c_Platform.SetWindowPos(NULL, c.left, c.bottom - platform.Height(),
                                 0, 0,
                                 SWP_NOSIZE | SWP_NOZORDER);
        } /* move it */
    }
