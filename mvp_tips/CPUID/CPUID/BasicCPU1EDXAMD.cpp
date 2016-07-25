
// BasicCPU1EDX.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EDXAMD.h"
#include "CPUIDx86.h"
#include "ColorSet.h"
#include "SetWindowBit.h"
#include "SetColor.h"
#include "ReportRegs.h"
#include "CPUIDRegs.h"
#include "FormatBinary.h"

// CBasicCPU1EDXAMD dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EDXAMD, CBasicCPU1EDX)


CBasicCPU1EDXAMD::CBasicCPU1EDXAMD()
        : CBasicCPU1EDX(CBasicCPU1EDXAMD::IDD)
   {
   }

CBasicCPU1EDXAMD::~CBasicCPU1EDXAMD()
   {
   }

/****************************************************************************
*                        CBasicCPU1EDX::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Maps controls to variables
****************************************************************************/

void CBasicCPU1EDXAMD::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU1EDX::DoDataExchange(pDX);

 DDX_Control(pDX, IDC_RESERVED4, c_Reserved4);
 DDX_Control(pDX, IDC_RESERVED5, c_Reserved5);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EDXAMD, CBasicCPU1EDX)
END_MESSAGE_MAP()

// CBasicCPU1EDXAMD message handlers

/****************************************************************************
*                        CBasicCPU1EDXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CBasicCPU1EDXAMD::OnInitDialog()
    {
     CBasicCPU1EDX::OnInitDialog();
     ColorSet colors(TRUE);
     POSITION p = colors.GetFirstColorPosition();

     CreateScroller(RUNTIME_CLASS(CBasicCPU1EDXCaptionsAMD), CBasicCPU1EDXCaptionsAMD::IDD);

     SETRESERVEDCOLORc(Reserved5); // 18
     SETRESERVEDCOLORc(Reserved4); // 27

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                       CBasicCPU1EDXAMD::OnSetActive
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the information by reading the CPU code
****************************************************************************/

BOOL CBasicCPU1EDXAMD::OnSetActive()
    {
     CPUregs regs;
     GetAndReport(1, regs);

     EDX1b EDX;
     EDX.w = regs.EDX;

     CString s;

     SETWINDOWBIT(Reserved5, EDX, AMD);         // 18

     s = FormatBinary(EDX.AMD.Reserved2, 3);    // 22..20
     c_Reserved2.SetWindowText(s + _T("B"));              
     
     SETWINDOWBIT(Reserved4, EDX, AMD);         // 27

     s = FormatBinary(EDX.AMD.Reserved3, 3);    // 31..29
     c_Reserved3.SetWindowText(s + _T("B"));
     
     return CBasicCPU1EDX::OnSetActive();
    }
