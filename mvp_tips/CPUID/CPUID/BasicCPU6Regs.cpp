// BasicCPU6Regs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU6Regs.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"

// CBasicCPU6Regs dialog

IMPLEMENT_DYNCREATE(CBasicCPU6Regs, CLeaves)
CBasicCPU6Regs::CBasicCPU6Regs()
        : CLeaves(CBasicCPU6Regs::IDD)
{
}

CBasicCPU6Regs::~CBasicCPU6Regs()
{
}

void CBasicCPU6Regs::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_SENSOR_SUPPORTED, c_SensorSupported);
DDX_Control(pDX, IDC_SENSOR_SUPPORTED_CAPTION, x_SensorSupported);
DDX_Control(pDX, IDC_INTERRUPT_THRESHOLDS, c_InterruptThresholds);
DDX_Control(pDX, IDC_INTERRUPT_THRESHOLDS_CAPTION, x_InterruptThresholds);
DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);
DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);
DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);
DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);
DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);
DDX_Control(pDX, IDC_RESERVED3_CAPTION, x_Reserved3);
DDX_Control(pDX, IDC_ACNT_MCNT, c_ACNT_MCNT);
DDX_Control(pDX, IDC_ACNT_MCNT_CAPTION, x_ACNT_MCNT);
DDX_Control(pDX, IDC_EDX, c_EDX);
}

BEGIN_MESSAGE_MAP(CBasicCPU6Regs, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU6Regs message handlers

/****************************************************************************
*                         CBasicCPU6Regs::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CBasicCPU6Regs::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(6, regs);

    EAX6b EAX;
    EAX.w = regs.EAX;
    
    SETWINDOWBIT(SensorSupported, EAX, bits);
    SETWINDOWBIT(Reserved1, EAX, bits);

    EBX6b EBX;
    EBX.w = regs.EBX;

    SETWINDOWBIT(InterruptThresholds, EBX, bits);
    SETWINDOWBIT(Reserved2, EBX, bits);
    
    ECX6b ECX;
    ECX.w = regs.ECX;
    SETWINDOWBIT(ACNT_MCNT, ECX, bits);
    SETWINDOWBIT(Reserved3, ECX, bits);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CBasicCPU6Regs::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CBasicCPU6Regs::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    // EAX
    SETCOLOR(SensorSupported);             // 0
    SETRESERVEDCOLOR(Reserved1);           // 31..1

    // EBX
    SETCOLOR(InterruptThresholds);         // 3..0
    SETRESERVEDCOLOR(Reserved2);           // 31..4

    // ECX
    SETCOLOR(ACNT_MCNT);                   // 0
    SETRESERVEDCOLOR(Reserved3);           // 31..1

    // EDX
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
