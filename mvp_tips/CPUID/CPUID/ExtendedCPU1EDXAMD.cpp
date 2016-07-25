// ExtendedCPU1EDXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU1EDXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "CurrentProcessor.h"
#include "SetAlign.h"
#include "ExtendedCPU1EDXCaptionsAMD.h"
#include "FormatBinary.h"

// CExtendedCPU1EDXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU1EDXAMD, CScrollableCaptionsParent)

CExtendedCPU1EDXAMD::CExtendedCPU1EDXAMD()
        : CScrollableCaptionsParent(CExtendedCPU1EDXAMD::IDD)
   {
   }

CExtendedCPU1EDXAMD::~CExtendedCPU1EDXAMD()
   {
   }

/****************************************************************************
*                     CExtendedCPU1ECXAMD::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CExtendedCPU1EDXAMD::DoDataExchange(CDataExchange* pDX)
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
    DDX_Control(pDX, IDC_CX8, c_CMPXCHG8B);         // 8
    DDX_Control(pDX, IDC_APIC, c_APIC);             // 9
    DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);   // 10
    DDX_Control(pDX, IDC_SYSCALL_SYSRET, c_SYSCALL_SYSRET); // 11
    DDX_Control(pDX, IDC_MTRR, c_MTRR);             // 12
    DDX_Control(pDX, IDC_PGE, c_PGE);               // 13
    DDX_Control(pDX, IDC_MCA, c_MCA);               // 14
    DDX_Control(pDX, IDC_CMOV, c_CMOV);             // 15
    DDX_Control(pDX, IDC_PAT, c_PAT);               // 16
    DDX_Control(pDX, IDC_PSE36, c_PSE36);           // 17
    DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);   // 19..18
    DDX_Control(pDX, IDC_EXECUTE_DISABLE, c_ExecuteDisable); // 20
    DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);   // 21
    DDX_Control(pDX, IDC_MMX_EXT, c_MMXExt);        // 22
    DDX_Control(pDX, IDC_MMX, c_MMX);               // 23
    DDX_Control(pDX, IDC_FXSR, c_FXSR);             // 24
    DDX_Control(pDX, IDC_FFXSR, c_FFXSR);           // 25
    DDX_Control(pDX, IDC_RESERVED4, c_Reserved4);   // 26
    DDX_Control(pDX, IDC_RDTSCP, c_RDTSCP);         // 27
    DDX_Control(pDX, IDC_RESERVED5, c_Reserved5);   // 28
    DDX_Control(pDX, IDC_LM, c_LM);                 // 29
    DDX_Control(pDX, IDC_3DNOW_EXT, c_ThreeDNowExt);// 30
    DDX_Control(pDX, IDC_3DNOW, c_ThreeDNow);       // 31
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CExtendedCPU1EDXAMD, CScrollableCaptionsParent)
END_MESSAGE_MAP()


// CExtendedCPU1EDXAMD message handlers

/****************************************************************************
*                         CExtendedCPU1EDXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU1EDXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000001, regs);

    CString s;

    EDX1x EDX;
    EDX.w = regs.EDX;
    
    SETWINDOWBIT(FPU, EDX, AMD);                // 0
    SETWINDOWBIT(VME, EDX, AMD);                // 1
    SETWINDOWBIT(DE, EDX, AMD);                 // 2
    SETWINDOWBIT(PSE, EDX, AMD);                // 3
    SETWINDOWBIT(TSC, EDX, AMD);                // 4
    SETWINDOWBIT(MSR, EDX, AMD);                // 5
    SETWINDOWBIT(PAE, EDX, AMD);                // 6
    SETWINDOWBIT(MCE, EDX, AMD);                // 7
    SETWINDOWBIT(CMPXCHG8B, EDX, AMD);          // 8
    SETWINDOWBIT(APIC, EDX, AMD);               // 9
    SETWINDOWBIT(Reserved1, EDX, AMD);          // 10
    SETWINDOWBIT(SYSCALL_SYSRET, EDX, AMD);     // 11
    SETWINDOWBIT(MTRR, EDX, AMD);               // 12
    SETWINDOWBIT(PGE, EDX, AMD);                // 13
    SETWINDOWBIT(MCA, EDX, AMD);                // 14
    SETWINDOWBIT(CMOV, EDX, AMD);               // 15
    SETWINDOWBIT(PAT, EDX, AMD);                // 16
    SETWINDOWBIT(PSE36, EDX, AMD);              // 17
    s = FormatBinary(EDX.AMD.Reserved2, 2);
    c_Reserved2.SetWindowText(s + _T("B"));     // 19..18
    SETWINDOWBIT(ExecuteDisable, EDX, AMD);     // 20
    SETWINDOWBIT(Reserved3, EDX, AMD);          // 21
    SETWINDOWBIT(MMXExt, EDX, AMD);             // 22
    SETWINDOWBIT(MMX, EDX, AMD);                // 23
    SETWINDOWBIT(FXSR, EDX, AMD);               // 24
    SETWINDOWBIT(FFXSR, EDX, AMD);              // 25
    SETWINDOWBIT(Reserved4, EDX, AMD);          // 26
    SETWINDOWBIT(RDTSCP, EDX, AMD);             // 27
    SETWINDOWBIT(Reserved5, EDX, AMD);          // 28
    SETWINDOWBIT(LM, EDX, AMD);                 // 29
    SETWINDOWBIT(ThreeDNowExt, EDX, AMD);       // 30
    SETWINDOWBIT(ThreeDNow, EDX, AMD);          // 31

    return CScrollableCaptionsParent::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU1EDXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU1EDXAMD::OnInitDialog()
   {
    CScrollableCaptionsParent::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    SETCOLORIc(FPU, 0);                 // 0
    SETCOLORIc(VME, 1);                 // 1
    SETCOLORIc(DE,  2);                 // 2
    SETCOLORIc(PSE, 3);                 // 3
    SETCOLORIc(TSC, 4);                 // 4
    SETCOLORIc(MSR, 5);                 // 5
    SETCOLORIc(PAE, 6);                 // 6
    SETCOLORIc(MCE, 7);                 // 7
    SETCOLORIc(CMPXCHG8B, 8);           // 8
    SETCOLORIc(APIC, 9);                // 9
    SETRESERVEDCOLORc(Reserved1);       // 10
    SETCOLORIc(SYSCALL_SYSRET, 11);     // 11
    SETCOLORIc(MTRR, 12);               // 12
    SETCOLORIc(PGE, 13);                // 13
    SETCOLORIc(MCA, 14);                // 14
    SETCOLORIc(CMOV, 15);               // 15
    SETCOLORIc(PAT, 16);                // 16
    SETCOLORIc(PSE36, 17);              // 17
    SETRESERVEDCOLORc(Reserved2);       // 19..18
    SETCOLORIc(ExecuteDisable, 20);     // 20
    SETRESERVEDCOLORc(Reserved3);       // 21
    SETCOLORIc(MMXExt, 22);             // 22
    SETCOLORIc(MMX, 23);                // 23
    SETCOLORIc(FXSR, 24);               // 24
    SETCOLORIc(FFXSR, 25);              // 25
    SETRESERVEDCOLORc(Reserved4);       // 26
    SETCOLORIc(RDTSCP, 27);             // 27
    SETRESERVEDCOLORc(Reserved5);       // 28
    SETCOLORIc(LM, 29);                 // 29
    SETCOLORIc(ThreeDNowExt, 30);       // 30
    SETCOLORIc(ThreeDNow, 31);          // 31

    CreateScroller(RUNTIME_CLASS(CExtendedCPU1EDXCaptionsAMD), CExtendedCPU1EDXCaptionsAMD::IDD);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
