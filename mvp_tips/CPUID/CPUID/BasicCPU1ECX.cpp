
// BasicCPU1ECX.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1ECX.h"
#include "CPUIDx86.h"
#include "SetColor.h"
#include "SetWindowBit.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "CPUIDRegs.h"
#include "FormatBinary.h"
#include "SetAlign.h"

// CBasicCPU1ECX dialog

IMPLEMENT_DYNCREATE(CBasicCPU1ECX, CLeaves)


CBasicCPU1ECX::CBasicCPU1ECX(UINT idd)
        : CLeaves(idd)
{
}

CBasicCPU1ECX::~CBasicCPU1ECX()
{
}

/****************************************************************************
*                        CBasicCPU1ECX::DoDataExchange
* Inputs:
*       CDataExchage * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CBasicCPU1ECX::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_SSE3, c_SSE3);
DDX_Control(pDX, IDC_SSE3_CAPTION, x_SSE3);
DDX_Control(pDX, IDC_CMPXCHG16B_CAPTION, x_CMPXCHG16B);
DDX_Control(pDX, IDC_CMPXCHG16B, c_CMPXCHG16B);
DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);
DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);
DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);
DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);
DDX_Control(pDX, IDC_RESERVED3_CAPTION, x_Reserved3);
DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);
DDX_Control(pDX, IDC_RESERVED5_CAPTION, x_Reserved5);
DDX_Control(pDX, IDC_RESERVED5, c_Reserved5);
DDX_Control(pDX, IDC_RESERVED6_CAPTION, x_Reserved6);
DDX_Control(pDX, IDC_RESERVED6, c_Reserved6);
DDX_Control(pDX, IDC_RESERVED6a, c_Reserved6a);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1ECX, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU1ECX message handlers

/****************************************************************************
*                         CBasicCPU1ECX::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the controls
****************************************************************************/

BOOL CBasicCPU1ECX::OnInitDialog()
    {
     CLeaves::OnInitDialog();
     ColorSet colors(TRUE);

     POSITION p;
     p = colors.GetFirstColorPosition();

     SETCOLOR(SSE3);               // 0
     SETALIGN(SSE3);               // 0

     SETRESERVEDCOLOR(Reserved1);  // 1..2
     SETALIGN(RESERVED1);

     SETRESERVEDCOLOR(Reserved2);  // 6
     SETALIGN(RESERVED2);

     SETRESERVEDCOLOR(Reserved3);  // 9
     SETALIGN(RESERVED3);

     SETRESERVEDCOLOR(Reserved5);  // 12
     SETALIGN(RESERVED5);

     SETCOLOR(CMPXCHG16B);         // 13
     SETALIGN(CMPXCHG16B);

     SETRESERVEDCOLOR(Reserved6);  // 15..31
     SETRESERVEDCOLORc(Reserved6a);
     DoAlign(IDC_RESERVED6a, IDC_RESERVED6_CAPTION);

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU1ECX::OnSetActive
* Result: void
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU1ECX::OnSetActive()
    {
     CPUregs regs;
     GetAndReport(1, regs);


     ECX1b ECX;
     ECX.w = regs.ECX;

     CString s;
     SETWINDOWBIT(SSE3, ECX, Intel);
     SETWINDOWBIT(CMPXCHG16B, ECX, Intel);

     SETWINDOWBIT(Reserved5, ECX, Intel);

     return CLeaves::OnSetActive();
    }
