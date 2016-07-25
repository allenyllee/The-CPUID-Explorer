// BasicCPU5Regs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU5Regs.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CPUIDregs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CurrentProcessor.h"

// CBasicCPU5Regs dialog

IMPLEMENT_DYNCREATE(CBasicCPU5Regs, CLeaves)
CBasicCPU5Regs::CBasicCPU5Regs()
        : CLeaves(CBasicCPU5Regs::IDD)
{
}

CBasicCPU5Regs::~CBasicCPU5Regs()
{
}

void CBasicCPU5Regs::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_LARGEST_MONITOR_LINE_SIZE, c_LargestMonitorLineSize);
DDX_Control(pDX, IDC_LARGEST_MONITOR_LINE_SIZE_CAPTION, x_LargestMonitorLineSize);
DDX_Control(pDX, IDC_SMALLEST_MONITOR_LINE_SIZE, c_SmallestMonitorLineSize);
DDX_Control(pDX, IDC_SMALLEST_MONITOR_LINE_SIZE_CAPTION, x_SmallestMonitorLineSize);
DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);
DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);
DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);
DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);
DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);
DDX_Control(pDX, IDC_RESERVED3_CAPTION, x_Reserved3);
DDX_Control(pDX, IDC_RESERVED4, c_Reserved4);
DDX_Control(pDX, IDC_RESERVED4_CAPTION, x_Reserved4);
DDX_Control(pDX, IDC_INTERRUPTS_AS_BREAK_EVENTS, c_InterruptsAsBreakEvents);
DDX_Control(pDX, IDC_INTERRUPTS_AS_BREAK_EVENTS_CAPTION, x_InterruptsAsBreakEvents);
DDX_Control(pDX, IDC_MWAIT_ENUMERATION_SUPPORTED, c_MWAITEnumerationSupported);
DDX_Control(pDX, IDC_MWAIT_ENUMERATION_SUPPORTED_CAPTION, x_MWAITEnumerationSupported);
DDX_Control(pDX, IDC_C0, c_C0);
DDX_Control(pDX, IDC_C0_CAPTION, x_C0);
DDX_Control(pDX, IDC_C1, c_C1);
DDX_Control(pDX, IDC_C1_CAPTION, x_C1);
DDX_Control(pDX, IDC_C2, c_C2);
DDX_Control(pDX, IDC_C2_CAPTION, x_C2);
DDX_Control(pDX, IDC_C3, c_C3);
DDX_Control(pDX, IDC_C3_CAPTION, x_C3);
DDX_Control(pDX, IDC_C4, c_C4);
DDX_Control(pDX, IDC_C4_CAPTION, x_C4);

}


BEGIN_MESSAGE_MAP(CBasicCPU5Regs, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU5Regs message handlers

/****************************************************************************
*                         CBasicCPU5Regs::OnSetActive
* Result: void
*       
* Effect: 
*       Reports the register values
****************************************************************************/

BOOL CBasicCPU5Regs::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(5, regs);

    EAX5b EAX;
    EAX.w = regs.EAX;
    
    SETWINDOWBIT(SmallestMonitorLineSize, EAX, bits);
    SETWINDOWBIT(Reserved2, EAX, bits);

    EBX5b EBX;
    EBX.w = regs.EBX;

    SETWINDOWBIT(LargestMonitorLineSize, EBX, bits);
    SETWINDOWBIT(Reserved1, EBX, bits);

    ECX5b ECX;
    ECX.w = regs.ECX;

    SETWINDOWBIT(MWAITEnumerationSupported, ECX, bits);
    SETWINDOWBIT(InterruptsAsBreakEvents, ECX, bits);
    SETWINDOWBIT(Reserved3, ECX, bits);

    EDX5b EDX;
    EDX.w = regs.EDX;

    SETWINDOWBIT(C0, EDX, bits);
    SETWINDOWBIT(C1, EDX, bits);
    SETWINDOWBIT(C2, EDX, bits);
    SETWINDOWBIT(C3, EDX, bits);
    SETWINDOWBIT(C4, EDX, bits);
    SETWINDOWBIT(Reserved4, EDX, bits);
    
    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                        CBasicCPU5Regs::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Intializes the dialog
****************************************************************************/

BOOL CBasicCPU5Regs::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p = colors.GetFirstColorPosition();

    SETCOLOR(LargestMonitorLineSize);
    SETCOLOR(SmallestMonitorLineSize);
    SETRESERVEDCOLOR(Reserved1);
    SETRESERVEDCOLOR(Reserved2);
    SETRESERVEDCOLOR(Reserved3);
    SETCOLOR(InterruptsAsBreakEvents);
    SETCOLOR(MWAITEnumerationSupported);

    SETCOLOR(C0);
    SETCOLOR(C1);
    SETCOLOR(C2);
    SETCOLOR(C3);
    SETCOLOR(C4);
    SETRESERVEDCOLOR(Reserved4);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
