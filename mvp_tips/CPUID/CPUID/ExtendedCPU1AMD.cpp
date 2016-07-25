// ExtendedCPU1AMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU1AMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "CurrentProcessor.h"

// CExtendedCPU1AMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU1AMD, CLeaves)

CExtendedCPU1AMD::CExtendedCPU1AMD()
        : CLeaves(CExtendedCPU1AMD::IDD)
{
}

CExtendedCPU1AMD::~CExtendedCPU1AMD()
{
}

void CExtendedCPU1AMD::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);

DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);
DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);
DDX_Control(pDX, IDC_SYSCALL_SYSRET, c_SYSCALL_SYSRET);
DDX_Control(pDX, IDC_SYSCALL_SYSRET_CAPTION, x_SYSCALL_SYSRET);
DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);
DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);
DDX_Control(pDX, IDC_EXECUTE_DISABLE, c_ExecuteDisable);
DDX_Control(pDX, IDC_EXECUTE_DISABLE_CAPTION, x_ExecuteDisable);
DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);
DDX_Control(pDX, IDC_RESERVED3_CAPTION, x_Reserved3);
DDX_Control(pDX, IDC_LM, c_LM);
DDX_Control(pDX, IDC_LM_CAPTION, x_LM);
DDX_Control(pDX, IDC_RESERVED4, c_Reserved4);
DDX_Control(pDX, IDC_RESERVED4_CAPTION, x_Reserved4);
DDX_Control(pDX, IDC_CMP_LEGACY, c_CmpLegacy);
DDX_Control(pDX, IDC_CMP_LEGACY_CAPTION, x_CmpLegacy);
DDX_Control(pDX, IDC_RESERVED5, c_Reserved5);
DDX_Control(pDX, IDC_RESERVED5_CAPTION, x_Reserved5);
DDX_Control(pDX, IDC_LAHF_SAHF, c_LAHF_SAHF);
DDX_Control(pDX, IDC_LAHF_SAHF_CAPTION, x_LAHF_SAHF);
DDX_Control(pDX, IDC_RESERVED6, c_Reserved6);
DDX_Control(pDX, IDC_RESERVED6_CAPTION, x_Reserved6);
DDX_Control(pDX, IDC_SVM, c_SVM);
DDX_Control(pDX, IDC_SVM_CAPTION, x_SVM);
DDX_Control(pDX, IDC_ALT_MOV_CR8, c_AltMovCr8);
DDX_Control(pDX, IDC_ALT_MOV_CR8_CAPTION, x_AltMovCr8);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CExtendedCPU1AMD, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU1AMD message handlers

/****************************************************************************
*                         CExtendedCPU1AMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU1AMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000001, regs);

    CString s;
    s.Format(_T("%08X"), regs.EAX);
    c_EAX.SetWindowText(s);

    ECX1x ECX;
    ECX.w = regs.ECX;

    SETWINDOWBIT(LAHF_SAHF, ECX, AMD);
    SETWINDOWBIT(CmpLegacy, ECX, AMD);
    SETWINDOWBIT(SVM, ECX, AMD);
    SETWINDOWBIT(Reserved6, ECX, AMD);
    SETWINDOWBIT(AltMovCr8, ECX, AMD);
    SETWINDOWBIT(Reserved5, ECX, AMD);

    EDX1x EDX;
    EDX.w = regs.EDX;
    
    SETWINDOWBIT(Reserved1, EDX, AMD);
    SETWINDOWBIT(SYSCALL_SYSRET, EDX, AMD);
    SETWINDOWBIT(Reserved2, EDX, AMD);
    SETWINDOWBIT(ExecuteDisable, EDX, AMD);
    SETWINDOWBIT(Reserved3, EDX, AMD);
    SETWINDOWBIT(LM, EDX, AMD);
    SETWINDOWBIT(Reserved4, EDX, AMD);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU1AMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU1AMD::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    // ECX
    SETCOLOR(LAHF_SAHF);                // 0
    SETCOLOR(CmpLegacy);                // 1
    SETCOLOR(SVM);                      // 2
    SETRESERVEDCOLOR(Reserved6);        // 3
    SETCOLOR(AltMovCr8);                // 4
    SETRESERVEDCOLOR(Reserved5);        // 31..1

    // EDX
    SETRESERVEDCOLOR(Reserved1);        // 10..0
    SETCOLOR(SYSCALL_SYSRET);           // 11
    SETRESERVEDCOLOR(Reserved2);        // 19..12
    SETCOLOR(ExecuteDisable);           // 20
    SETRESERVEDCOLOR(Reserved3);        // 28..21
    SETCOLOR(LM);                       // 29
    SETRESERVEDCOLOR(Reserved4);        // 31..30

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
