
// BasicCPU1ECXIntel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1ECXIntel.h"
#include "CPUIDx86.h"
#include "SetColor.h"
#include "SetWindowBit.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "CPUIDRegs.h"
#include "FormatBinary.h"
#include "SetAlign.h"

// CBasicCPU1ECXIntel dialog

IMPLEMENT_DYNCREATE(CBasicCPU1ECXIntel, CBasicCPU1ECX)


CBasicCPU1ECXIntel::CBasicCPU1ECXIntel()
        : CBasicCPU1ECX(CBasicCPU1ECXIntel::IDD)
{
}

CBasicCPU1ECXIntel::~CBasicCPU1ECXIntel()
{
}

/****************************************************************************
*                        CBasicCPU1ECXIntel::DoDataExchange
* Inputs:
*       CDataExchage * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CBasicCPU1ECXIntel::DoDataExchange(CDataExchange* pDX)
{
CBasicCPU1ECX::DoDataExchange(pDX);

DDX_Control(pDX, IDC_XPTR, c_XPTR);
DDX_Control(pDX, IDC_XPTR_CAPTION, x_XPTR);

DDX_Control(pDX, IDC_MWAIT_CAPTION, x_MWAIT);
DDX_Control(pDX, IDC_MWAIT, c_MWAIT);

DDX_Control(pDX, IDC_CPL, c_CPL);
DDX_Control(pDX, IDC_CPL_CAPTION, x_CPL);

DDX_Control(pDX, IDC_VMX, c_VMX);
DDX_Control(pDX, IDC_VMX_CAPTION, x_VMX);

DDX_Control(pDX, IDC_EST_CAPTION, x_EST);
DDX_Control(pDX, IDC_EST, c_EST);

DDX_Control(pDX, IDC_TM2_CAPTION, x_TM2);
DDX_Control(pDX, IDC_TM2, c_TM2);

DDX_Control(pDX, IDC_L1, c_L1);
DDX_Control(pDX, IDC_L1_CAPTION, x_L1);

DDX_Control(pDX, IDC_RESERVED4_CAPTION, x_Reserved4);
DDX_Control(pDX, IDC_RESERVED4, c_Reserved4);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1ECXIntel, CBasicCPU1ECX)
END_MESSAGE_MAP()


// CBasicCPU1ECXIntel message handlers

/****************************************************************************
*                         CBasicCPU1ECXIntel::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the controls
****************************************************************************/

BOOL CBasicCPU1ECXIntel::OnInitDialog()
    {
     CBasicCPU1ECX::OnInitDialog();
     ColorSet colors(TRUE);

     POSITION p;
     p = colors.GetFirstColorPosition();

     //SETCOLOR(SSE3);               // 0
     //SETALIGN(SSE3);               // 0

     SETRESERVEDCOLOR(Reserved1);  // 1..2
     SETALIGN(RESERVED1);

     SETCOLOR(MWAIT);              // 3
     SETALIGN(MWAIT);

     SETCOLOR(CPL);                // 4
     SETALIGN(CPL);

     SETCOLOR(VMX);                // 5
     SETALIGN(VMX);
     
     SETRESERVEDCOLOR(Reserved2);  // 6
     SETALIGN(RESERVED2);

     SETCOLOR(EST);                // 7
     SETALIGN(EST);
     
     SETCOLOR(TM2);                // 8
     SETALIGN(TM2);

     SETCOLOR(L1);                 // 10
     SETALIGN(L1);

     SETRESERVEDCOLOR(Reserved4);  // 11
     SETALIGN(RESERVED4);

     //SETCOLOR(CMPXCHG16B);       // 13
     //SETALIGN(CMPXCHG16B);
     
     SETCOLOR(XPTR);               // 14
     SETALIGN(XPTR);
     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU1ECXIntel::OnSetActive
* Result: void
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU1ECXIntel::OnSetActive()
    {
     CPUregs regs;
     GetAndReport(1, regs);


     ECX1b ECX;
     ECX.w = regs.ECX;

     CString s;
     SETWINDOWBIT(XPTR, ECX, Intel); // 14
     SETWINDOWBIT(MWAIT, ECX, Intel);
     SETWINDOWBIT(CPL, ECX, Intel);
     SETWINDOWBIT(VMX, ECX, Intel);
     SETWINDOWBIT(EST, ECX, Intel);
     SETWINDOWBIT(TM2, ECX, Intel);
     SETWINDOWBIT(L1, ECX, Intel);

     s = FormatBinary(ECX.Intel.Reserved1, 2);
     c_Reserved1.SetWindowText(s + _T("B"));

     SETWINDOWBIT(Reserved2, ECX, Intel);

     SETWINDOWBIT(Reserved3, ECX, Intel);

     SETWINDOWBIT(Reserved4, ECX, Intel);

     s.Format(_T("%018dB"), ECX.Intel.Reserved6);
     c_Reserved6.SetWindowText(s);

     s.Format(_T("%017dB"), ECX.Intel.Reserved6);
     c_Reserved6.SetWindowText(s);

     return CBasicCPU1ECX::OnSetActive();
    }
