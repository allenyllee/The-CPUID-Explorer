// ScrollableCaptions.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScrollableCaptions.h"
#include "msg.h"
#include "QueryCoordinates.h"

// CScrollableCaptions dialog
DECLARE_MESSAGE(UWM_QUERY_COORDINATES)

IMPLEMENT_DYNAMIC(CScrollableCaptions, CDialog)

CScrollableCaptions::CScrollableCaptions(UINT idd, CWnd* pParent /*=NULL*/)
        : CDialog(idd, pParent)
   {
   }

CScrollableCaptions::~CScrollableCaptions()
   {
   }

/****************************************************************************
*                    CScrollableCaptions::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CScrollableCaptions::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        DDX_Control(pDX, IDC_PLATFORM, c_Platform);
}

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CScrollableCaptions, CDialog)
        ON_WM_VSCROLL()
        ON_WM_SIZE()
END_MESSAGE_MAP()


// CScrollableCaptions message handlers

/****************************************************************************
*                        CScrollableCaptions::SavePos
* Result: void
*       
* Effect: 
*       Saves the x,y points for the top left corner of the window
****************************************************************************/

void CScrollableCaptions::SavePos()
    {
     for(CWnd * wnd = GetWindow(GW_CHILD); wnd != NULL; wnd = wnd->GetWindow(GW_HWNDNEXT))
        { /* capture original */
         CRect r;
         wnd->GetWindowRect(&r);
         ScreenToClient(&r);
         CPoint pt(r.left, r.top);
         ::SetWindowLong(wnd->m_hWnd, GWL_USERDATA, POINTTOPOINTS(pt));
        } /* capture original */
    } // CScrollableCaptions::SavePos

/****************************************************************************
*                      CScrollableCaptions::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Sets the scrolling parameter
****************************************************************************/

BOOL CScrollableCaptions::OnInitDialog()
    {
     CDialog::OnInitDialog();

     //*****************************************************************************
     // Controls are adjusted from their nominal start position based on the
     // scroll position.  To do this, the initial start coordinates are stored in
     // the GWL_USERDATA field
     //*****************************************************************************
     SavePos();

     //*****************************************************************************

     SetScrollParameters();

     SetPlatformLabel();

     return TRUE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
    }

/****************************************************************************
*                    CScrollableCaptions::SetPlatformLabel
* Result: void
*       
* Effect: 
*       Sets the platform label
****************************************************************************/

void CScrollableCaptions::SetPlatformLabel()
    {
     if(c_Platform.GetSafeHwnd() == NULL)
        return; // still initializing
     
     CRect platform;
     c_Platform.GetWindowRect(&platform);
     ScreenToClient(&platform);

     CRect c;
     GetClientRect(&c);
     c_Platform.SetWindowPos(NULL, c.left, c.bottom - platform.Height(),
                             0, 0,
                             SWP_NOSIZE | SWP_NOZORDER);
    } // CScrollableCaptions::SetPlatformLabel

/****************************************************************************
*                      CScrollableCaptions::OnVScroll
* Inputs:
*       UINT nSBCode: Scroll code
*       UINT nPos: Scroll position for thumb operations
*       CScrollBar * pScrollBar: unused
* Result: void
*       
* Effect: 
*       Scrolls the controls within the page
****************************************************************************/

void CScrollableCaptions::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
    {
     int pos = GetScrollPos(SB_VERT);
     CRect r;

     bottom->GetWindowRect(&r);  // choose some control, this is as good as any
     ScreenToClient(&r);

     switch(nSBCode)
        { /* sbcode */
         case SB_PAGEUP:
            pos -= r.Height();
            break;
         case SB_PAGEDOWN:
            pos += r.Height();
            break;
         case SB_LINEUP:
            pos--;
            break;
         case SB_LINEDOWN:
            pos++;
            break;
         case SB_THUMBTRACK:
            pos = nPos;
            break;
        } /* sbcode */
     if(pos < 0)
        pos = 0;

     HDWP wndpos = ::BeginDeferWindowPos(72); // 32-bit displays, no more than 2 per bit + spares

     for(CWnd * wnd = GetWindow(GW_CHILD); wnd != NULL; wnd = wnd->GetWindow(GW_HWNDNEXT))
        { /* scan windows */
         if(wnd == &c_Platform)
            continue;

         LONG L = ::GetWindowLong(wnd->m_hWnd, GWL_USERDATA);
         POINTS pt = MAKEPOINTS(L);
         int y = pt.y - pos;
         //TRACE("OnVScroll: [%d] (x=%d y=%d)\n", wnd->GetDlgCtrlID(), pt.x, y);
         CRect wp;
         wnd->GetWindowRect(&wp);
         wndpos = ::DeferWindowPos(wndpos, wnd->m_hWnd, NULL, pt.x, y, 0, 0, // ignored
                        SWP_NOSIZE | SWP_NOZORDER);
        } /* scan windows */

     ::EndDeferWindowPos(wndpos);

     SetScrollPos(SB_VERT, pos);

     SetPlatformLabel();
     CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
    }

/****************************************************************************
*                 CScrollableCaptions::SetScrollParameters
* Result: void
*       
* Effect: 
*       Sets the scrollbar parameters
****************************************************************************/

void CScrollableCaptions::SetScrollParameters()
    {
     CWnd * w = GetWindow(GW_CHILD); // see if any children
     if(w == NULL)
        return; // if no children, we're still in initialization

     SCROLLINFO info;
     info.cbSize = sizeof(SCROLLINFO);
     info.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
     
     info.nPos = 0;

     int maxY = 0;
     int minY = INT_MAX;
     
     bottom = NULL;

     for(CWnd * wnd = GetWindow(GW_CHILD); wnd != NULL; wnd = wnd->GetWindow(GW_HWNDNEXT))
        { /* scan windows */
         CRect r;
         wnd->GetWindowRect(&r);
         ScreenToClient(&r);
         minY = min(minY, r.top);
         maxY = max(maxY, r.bottom);
         if(maxY == r.bottom)
            bottom = wnd;
        } /* scan windows */

     CRect c;
     GetClientRect(&c);
     info.nMin = minY;
     info.nMax = maxY;

     TRACE("(1) minY %d, maxY %d, c.Height() %d, info.nMax = %d\n", minY, maxY, c.Height(), info.nMax);

     // Handle case where all controls fit on the window
     if(info.nMax < 0)
         info.nMax = info.nMin;
     info.nPage = c.Height();

     ASSERT(bottom != NULL);

     if(bottom->GetSafeHwnd() != NULL)
        { /* adjust for windows */
         CRect text;
         bottom->GetWindowRect(&text); // any window will do, they are all the same height
         ScreenToClient(&text);
         info.nMax += c.Height() - text.Height();
         TRACE("Adjusted info.nMax += %d - %d\n", c.Height(), text.Height());
        } /* adjust for windows */


     TRACE("(2): info.nMin %d, info.nMax %d, c.Height() %d, info.nMax = %d\n", info.nMin, info.nMax, c.Height());
     SetScrollInfo(SB_VERT, &info);
    } // CScrollableCaptions::SetScrollParameters

/****************************************************************************
*                        CScrollableCaptions::OnSize
* Inputs:
*       UINT nType: Type of resize
*       int cx: New client width
*       int cy: New client height
* Result: void
*       
* Effect: 
*       Resizes the client area
****************************************************************************/

void CScrollableCaptions::OnSize(UINT nType, int cx, int cy)
    {
     CDialog::OnSize(nType, cx, cy);

     SetScrollParameters();

     SetPlatformLabel();
    }

/****************************************************************************
*                       CScrollableCaptions::DoAlign
* Inputs:
*       UINT ctlid: Control ID of reference caption and vertical bar
*       UINT textid: Control ID of text
* Result: void
*       
* Effect: 
*       Aligns the edges of the vertical control with the parent control and with
*       the bottom of the horizontal control
* Notes:
*       The purpose of this code is to force the screen coordinates of the
*       scrollable entity to align to the screen coordinates of the
*       referenced entity, which is in a different dialog.  Because of the
*       roundoff errors in DBU-to-pixel mappings, there can be an off-by-one
*       error which looks really ugly.
*
*       Who says I'm obsessive-compusive?  
****************************************************************************/

void CScrollableCaptions::DoAlign(UINT ctlid, UINT textid)
    {
     CRect r;
     BOOL b = (BOOL)GetParent()->SendMessage(UWM_QUERY_COORDINATES, ctlid, (LPARAM)&r);
     ASSERT(b);
     if(!b)
        return;
     
     TRACE("DoAlign: Parent [%d] (L=%d T=%d R=%d B=%d)\n", ctlid, r.left, r.top, r.right, r.bottom);
     
     /******************************************************************************
                   +----+
                   |    |
                   |    |
                   |    |  Parent object: coordinates in r
                   |    |
                   +----+
                    +----+
                    |    |  
                    |    |  
                    |    |  Local object: coordinates in L
                    |    |  
                    +----+
     ******************************************************************************/

     CWnd * wnd = GetDlgItem(ctlid); // Well, my second GetDlgItem for 2007 (but they tend to come in pairs)
     ASSERT(wnd != NULL);   
     if(wnd == NULL)
        return;
     CRect L;
     wnd->GetWindowRect(&L);

     L.left = r.left;
     L.right = r.right;

     CWnd * caption = GetDlgItem(textid);
     ASSERT(caption != NULL);
     if(caption != NULL)
        { /* force vertical alignment */
         CRect C;
         caption->GetWindowRect(&C);
         L.bottom = C.bottom;
        } /* force vertical alignment */

     ScreenToClient(&L);
     wnd->SetWindowPos(NULL,
                       L.left, L.top,
                       L.Width(), L.Height(),
                       SWP_NOZORDER | SWP_NOACTIVATE);
     wnd->Invalidate();
    } // CScrollableCaptions::DoAlign
