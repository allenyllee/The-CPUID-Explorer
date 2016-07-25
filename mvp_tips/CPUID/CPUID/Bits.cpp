// Bits.cpp : implementation file
//

#include "stdafx.h"
#include "Bits.h"

// CBits

IMPLEMENT_DYNAMIC(CBits, CStatic)
CBits::CBits()
{
}

CBits::~CBits()
{
}


BEGIN_MESSAGE_MAP(CBits, CStatic)
    ON_WM_CTLCOLOR_REFLECT()
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotify)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotify)
END_MESSAGE_MAP()



// CBits message handlers


/****************************************************************************
*                               CBits::CtlColor
* Inputs:
*       CDC * pDC:
*       UINT nCtlColor: unused
* Result: HBRUSH
*       Background brush
* Effect: 
*       Sets the background brush and transparent mode
****************************************************************************/

HBRUSH CBits::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
    {
     pDC->SetBkMode(TRANSPARENT);

     return brush;
    }

/****************************************************************************
*                              CBits::SetBkColor
* Inputs:
*       COLORREF c: Color
* Result: void
*       
* Effect: 
*       Sets the background color
****************************************************************************/

void CBits::SetBkColor(COLORREF c)
    {
     if(brush.GetSafeHandle() != NULL)
        brush.DeleteObject();
     bkgnd = c;
     brush.CreateSolidBrush(c);
     if(m_hWnd != NULL)
        Invalidate();
    } // CBits::SetBkColor

/****************************************************************************
*                             CBits::SetTextColor
* Inputs:
*       COLORREF c: Color
* Result: void
*       
* Effect: 
*       Sets the text color
****************************************************************************/

void CBits::SetTextColor(COLORREF c)
    {
     text = c;
     if(m_hWnd != NULL)
        Invalidate();
    } // CBits::SetTextColor

/****************************************************************************
*                          CBits::PreSubclassWindow
* Result: void
*       
* Effect: 
*       Captures the bit position (for the flyover help)
****************************************************************************/

void CBits::PreSubclassWindow()
    {
     GetWindowText(Help);

     CStatic::PreSubclassWindow();
    }

/****************************************************************************
*                         CBits::OnToolTipNotify
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

BOOL CBits::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
    {
     // need to handle both ANSI and UNICODE versions of the message
     TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
     TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;

     CString TipText;

     UINT_PTR nID = pNMHDR->idFrom;

     if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
         pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
        {
         // idFrom is actually the HWND of the tool
         nID = ::GetDlgCtrlID((HWND)nID);
        }

     if (nID != 0) // will be zero on a separator
        TipText = _T("<") + Help + _T(">");

     if (pNMHDR->code == TTN_NEEDTEXTA)
        { /* ANSI tip */
         CStringA tip(TipText);
         StringCchCopyA(pTTTA->szText, sizeof(pTTTA->szText), tip);
        } /* ANSI tip */
     else
        { /* Unicode tip */
         CStringW tip(TipText);
         StringCchCopyW(pTTTW->szText, sizeof(pTTTW->szText)/sizeof(WCHAR), tip);
        } /* Unicode tip */
     *pResult = 0;
        
     return FALSE;
    } // CBits::OnToolTipNotify
