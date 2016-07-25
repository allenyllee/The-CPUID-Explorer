
// BasicCPU1EDX.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EDX.h"
#include "CPUIDx86.h"
#include "ColorSet.h"
#include "SetWindowBit.h"
#include "SetColor.h"
#include "ReportRegs.h"
#include "CPUIDRegs.h"
#include "msg.h"
#include "QueryCoordinates.h"

// CBasicCPU1EDX dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EDX, CScrollableCaptionsParent)
DECLARE_MESSAGE(UWM_QUERY_COORDINATES)

CBasicCPU1EDX::CBasicCPU1EDX(UINT idd)
        : CScrollableCaptionsParent(idd)
   {
   }

CBasicCPU1EDX::~CBasicCPU1EDX()
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

void CBasicCPU1EDX::DoDataExchange(CDataExchange* pDX)
{
 CScrollableCaptionsParent::DoDataExchange(pDX);
 DDX_Control(pDX, IDC_FPU, c_FPU);               // 0
 DDX_Control(pDX, IDC_VME, c_VME);               // 1
 DDX_Control(pDX, IDC_DE, c_DE);                 // 2
 DDX_Control(pDX, IDC_PSE, c_PSE);               // 3
 DDX_Control(pDX, IDC_TSC, c_TSC);               // 4
 DDX_Control(pDX, IDC_MSR, c_MSR);               // 5
 DDX_Control(pDX, IDC_PAE, c_PAE);               // 6
 DDX_Control(pDX, IDC_MCE, c_MCE);               // 7
 DDX_Control(pDX, IDC_CX8, c_CX8);               // 8
 DDX_Control(pDX, IDC_APIC, c_APIC);             // 9
 DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);   // 10
 DDX_Control(pDX, IDC_SEP, c_SEP);               // 11
 DDX_Control(pDX, IDC_MTRR, c_MTRR);             // 12
 DDX_Control(pDX, IDC_PGE, c_PGE);               // 13
 DDX_Control(pDX, IDC_MCA, c_MCA);               // 14
 DDX_Control(pDX, IDC_CMOV, c_CMOV);             // 15
 DDX_Control(pDX, IDC_PAT, c_PAT);               // 16
 DDX_Control(pDX, IDC_PSE36, c_PSE36);           // 17
 DDX_Control(pDX, IDC_CFLSH, c_CFLSH);           // 19
 DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);   // 20
 DDX_Control(pDX, IDC_MMX, c_MMX);               // 23
 DDX_Control(pDX, IDC_FXSR, c_FXSR);             // 24
 DDX_Control(pDX, IDC_SSE, c_SSE);               // 25
 DDX_Control(pDX, IDC_SSE2, c_SSE2);             // 26
 DDX_Control(pDX, IDC_HTT, c_HTT);               // 28
 DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);   // 30
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EDX, CScrollableCaptionsParent)
END_MESSAGE_MAP()


// CBasicCPU1EDX message handlers

/****************************************************************************
*                         CBasicCPU1EDX::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CBasicCPU1EDX::OnInitDialog()
    {
     CScrollableCaptionsParent::OnInitDialog();
     ColorSet colors(TRUE);
     POSITION p = colors.GetFirstColorPosition();

     SETCOLORIc(FPU, 0);           // 0
     SETCOLORIc(VME, 1);           // 1
     SETCOLORIc(DE, 2);            // 2
     SETCOLORIc(PSE, 3);           // 3
     SETCOLORIc(TSC, 4);           // 4
     SETCOLORIc(MSR, 5);           // 5
     SETCOLORIc(PAE, 6);           // 6
     SETCOLORIc(MCE, 7);           // 7
     SETCOLORIc(CX8, 8);           // 8
     SETCOLORIc(APIC, 9);          // 9
     SETRESERVEDCOLORc(Reserved1); // 10
     SETCOLORIc(SEP, 11);          // 11
     SETCOLORIc(MTRR, 12);         // 12
     SETCOLORIc(PGE, 13);          // 13
     SETCOLORIc(MCA, 14);          // 14
     SETCOLORIc(CMOV, 15);         // 15
     SETCOLORIc(PAT, 16);          // 16
     SETCOLORIc(PSE36, 17);        // 17
     //                            // 18: subclass
     SETCOLORIc(CFLSH, 19);        // 19
     SETRESERVEDCOLORc(Reserved2); // 20
     //                            // 21: subclass
     //                            // 22: subclass
     SETCOLORIc(MMX, 23);          // 23
     SETCOLORIc(FXSR, 24);         // 24
     SETCOLORIc(SSE, 25);          // 25
     SETCOLORIc(SSE2, 26);         // 26
     //                            // 27:subclass
     SETCOLORIc(HTT, 28);          // 28
     SETRESERVEDCOLORc(Reserved3); // 30
                                   // 31: subclass
     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU1EDX::OnSetActive
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the information by reading the CPU code
****************************************************************************/

BOOL CBasicCPU1EDX::OnSetActive()
    {
     CPUregs regs;
     GetAndReport(1, regs);

     EDX1b EDX;
     EDX.w = regs.EDX;

     CString s;

     
     SETWINDOWBIT(FPU, EDX, Intel);                         // 0
     SETWINDOWBIT(VME, EDX, Intel);                         // 1
     SETWINDOWBIT(DE,  EDX, Intel);                         // 2
     SETWINDOWBIT(PSE, EDX, Intel);                         // 3
     SETWINDOWBIT(TSC, EDX, Intel);                         // 4
     SETWINDOWBIT(MSR, EDX, Intel);                         // 5
     SETWINDOWBIT(PAE, EDX, Intel);                         // 6
     SETWINDOWBIT(MCE, EDX, Intel);                         // 7
     SETWINDOWBIT(CX8, EDX, Intel);                         // 8
     SETWINDOWBIT(APIC, EDX, Intel);                        // 9
     SETWINDOWBIT(Reserved1, EDX, Intel);                   // 10
     SETWINDOWBIT(SEP, EDX, Intel);                         // 11
     SETWINDOWBIT(MTRR, EDX, Intel);                        // 12
     SETWINDOWBIT(PGE, EDX, Intel);                         // 13
     SETWINDOWBIT(MCA, EDX, Intel);                         // 14
     SETWINDOWBIT(CMOV, EDX, Intel);                        // 15
     SETWINDOWBIT(PAT, EDX, Intel);                         // 16
     SETWINDOWBIT(PSE36, EDX, Intel);                       // 17
                                                            // 18: subclas
     SETWINDOWBIT(CFLSH, EDX, Intel);                       // 19
                                                            // 20: subclass
                                                            // 21: subclass
                                                            // 22: subclass
     SETWINDOWBIT(MMX, EDX, Intel);                         // 23
     SETWINDOWBIT(FXSR, EDX, Intel);                        // 24
     SETWINDOWBIT(SSE, EDX, Intel);                         // 25
     SETWINDOWBIT(SSE2, EDX, Intel);                        // 26
     SETWINDOWBIT(HTT, EDX, Intel);                         // 28
                                                            // 29: subclass
                                                            // 30: subclass
                                                            // 31: subclass
     return CScrollableCaptionsParent::OnSetActive();
    }
