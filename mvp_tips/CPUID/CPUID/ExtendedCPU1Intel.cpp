// ExtendedCPU1Intel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU1Intel.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "CurrentProcessor.h"

// CExtendedCPU1Intel dialog

IMPLEMENT_DYNCREATE(CExtendedCPU1Intel, CLeaves)
CExtendedCPU1Intel::CExtendedCPU1Intel()
        : CLeaves(CExtendedCPU1Intel::IDD)
{
}

CExtendedCPU1Intel::~CExtendedCPU1Intel()
{
}

void CExtendedCPU1Intel::DoDataExchange(CDataExchange* pDX)
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
DDX_Control(pDX, IDC_EMT64T, c_EMT64T);
DDX_Control(pDX, IDC_EMT64T_CAPTION, x_EMT64T);
DDX_Control(pDX, IDC_RESERVED4, c_Reserved4);
DDX_Control(pDX, IDC_RESERVED4_CAPTION, x_Reserved4);

DDX_Control(pDX, IDC_RESERVED5, c_Reserved5);
DDX_Control(pDX, IDC_RESERVED5_CAPTION, x_Reserved5);
DDX_Control(pDX, IDC_LAHF_SAHF, c_LAHF_SAHF);
DDX_Control(pDX, IDC_LAHF_SAHF_CAPTION, x_LAHF_SAHF);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CExtendedCPU1Intel, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU1Intel message handlers

/****************************************************************************
*                         CExtendedCPU1Intel::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU1Intel::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000001, regs);

    CString s;
    s.Format(_T("%08X"), regs.EAX);
    c_EAX.SetWindowText(s);

    ECX1x ECX;
    ECX.w = regs.ECX;

    SETWINDOWBIT(LAHF_SAHF, ECX, Intel);
    SETWINDOWBIT(Reserved5, ECX, Intel);

    EDX1x EDX;
    EDX.w = regs.EDX;
    
    SETWINDOWBIT(Reserved1, EDX, Intel);
    SETWINDOWBIT(SYSCALL_SYSRET, EDX, Intel);
    SETWINDOWBIT(Reserved2, EDX, Intel);
    SETWINDOWBIT(ExecuteDisable, EDX, Intel);
    SETWINDOWBIT(Reserved3, EDX, Intel);
    SETWINDOWBIT(EMT64T, EDX, Intel);
    SETWINDOWBIT(Reserved4, EDX, Intel);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU1Intel::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU1Intel::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    // ECX
    SETCOLOR(LAHF_SAHF);                // 0
    SETRESERVEDCOLOR(Reserved5);        // 31..1

    // EDX
    SETRESERVEDCOLOR(Reserved1);        // 10..0
    SETCOLOR(SYSCALL_SYSRET);           // 11
    SETRESERVEDCOLOR(Reserved2);        // 19..12
    SETCOLOR(ExecuteDisable);           // 20
    SETRESERVEDCOLOR(Reserved3);        // 28..21
    SETCOLOR(EMT64T);                   // 29
    SETRESERVEDCOLOR(Reserved4);        // 31..30

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
