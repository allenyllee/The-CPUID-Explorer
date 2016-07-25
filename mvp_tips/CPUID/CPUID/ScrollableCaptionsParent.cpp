
// ScrollableCaptionsParent.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScrollableCaptionsParent.h"
#include "CPUIDx86.h"
#include "ColorSet.h"
#include "SetWindowBit.h"
#include "SetColor.h"
#include "ReportRegs.h"
#include "CPUIDRegs.h"
#include "msg.h"
#include "QueryCoordinates.h"

// CScrollableCaptionsParent dialog

IMPLEMENT_DYNCREATE(CScrollableCaptionsParent, CLeaves)
DECLARE_MESSAGE(UWM_QUERY_COORDINATES)

CScrollableCaptionsParent::CScrollableCaptionsParent(UINT idd)
        : CLeaves(idd)
   {
    c_Captions = NULL;
   }

CScrollableCaptionsParent::~CScrollableCaptionsParent()
   {
    delete c_Captions;
   }

/****************************************************************************
*                        CScrollableCaptionsParent::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Maps controls to variables
****************************************************************************/

void CScrollableCaptionsParent::DoDataExchange(CDataExchange* pDX)
{
 CLeaves::DoDataExchange(pDX);
 DDX_Control(pDX, IDC_CHILD_FRAME, c_ChildFrame);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CScrollableCaptionsParent, CLeaves)
    ON_WM_SIZE()
    ON_REGISTERED_MESSAGE(UWM_QUERY_COORDINATES, OnQueryCoordinates)
END_MESSAGE_MAP()


// CScrollableCaptionsParent message handlers

/****************************************************************************
*                        CScrollableCaptionsParent::CreateScroller
* Inputs:
*       CRuntimeClass * rtc: The runtime class of the object to create
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Creates a CScrollableCaptions subclass in the scroll area
****************************************************************************/

BOOL CScrollableCaptionsParent::CreateScroller(CRuntimeClass * rtc, UINT idd)
    {
     c_Captions = (CScrollableCaptions*)rtc->CreateObject();
     if(c_Captions == NULL)
        { /* failed */
         ASSERT(FALSE);
        } /* failed */
     else
        { /* created captions object */
         if(!c_Captions->Create(idd, this))
            { /* failed */
             ASSERT(FALSE);
            } /* failed */
         else
            { /* created dialog */
             c_Captions->SetParent(this);
             CRect rect;
             c_ChildFrame.GetWindowRect(&rect);
             ScreenToClient(&rect);
             c_Captions->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
             c_Captions->SetWindowPos(&c_ChildFrame, 0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
             c_Captions->ShowWindow(SW_SHOW);
            } /* created dialog */
        } /* created captions object */
     return TRUE;
    } // CScrollableCaptionsParent::CreateScroller

/****************************************************************************
*                         CScrollableCaptionsParent::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CScrollableCaptionsParent::OnInitDialog()
    {
     CLeaves::OnInitDialog();

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                            CScrollableCaptionsParent::OnSize
* Inputs:
*       UINT nType: type of sizing
*       int cx: New client width
*       int cy: New client height
* Result: void
*       
* Effect: 
*       Resizes the controls
****************************************************************************/

void CScrollableCaptionsParent::OnSize(UINT nType, int cx, int cy)
   {
    CLeaves::OnSize(nType, cx, cy);

    if(c_Captions->GetSafeHwnd() != NULL)
       { /* resize caption */
        CRect r;
        c_Captions->GetWindowRect(&r);
        ScreenToClient(&r);
        c_Captions->SetWindowPos(NULL, 0, 0, // ignored
                                 cx,
                                 cy - r.top,
                                 SWP_NOMOVE | SWP_NOZORDER);
       } /* resize caption */
   }

/****************************************************************************
*                      CScrollableCaptionsParent::OnQueryCoordinates
* Inputs:
*       WPARAM: (WPARAM)(UINT): ctlid to fetch
*       LPARAM: (LPARAM)(CRect *): Place to put result
* Result: (LRESULT)BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Fetches the window coordinates of the control
****************************************************************************/

LRESULT CScrollableCaptionsParent::OnQueryCoordinates(WPARAM wParam, LPARAM lParam)
    {
     CRect * r = (CRect *)lParam;

     CWnd * wnd = GetDlgItem((int)wParam);  // my GetDlgItem for 2007
     ASSERT(wnd != NULL);
     if(wnd == NULL)
        return (LRESULT)FALSE;

     wnd->GetWindowRect(r);
     return (LRESULT)TRUE;
    } // CScrollableCaptionsParent::OnQueryCoordinates
