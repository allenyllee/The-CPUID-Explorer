// ExtendedCPU8.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU8.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "FormatMagnitude.h"

// CExtendedCPU8 dialog

IMPLEMENT_DYNCREATE(CExtendedCPU8, CLeaves)
CExtendedCPU8::CExtendedCPU8(UINT idd)
        : CLeaves(idd)
{
}

CExtendedCPU8::~CExtendedCPU8()
{
}

void CExtendedCPU8::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
#ifdef _DEBUG_PRINTOUT
DDX_Control(pDX, IDC_SPIN_PHYSICAL, c_SpinPhysical);
#endif
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_EDX, c_EDX);
DDX_Control(pDX, IDC_PHYSICAL_ADDRESS_BITS, c_PhysicalAddressBits);
DDX_Control(pDX, IDC_PHYSICAL_ADDRESS_BITS_CAPTION, x_PhysicalAddressBits);
DDX_Control(pDX, IDC_VIRTUAL_ADDRESS_BITS, c_VirtualAddressBits);
DDX_Control(pDX, IDC_VIRTUAL_ADDRESS_BITS_CAPTION, x_VirtualAddressBits);
DDX_Control(pDX, IDC_RESERVED, c_Reserved);
DDX_Control(pDX, IDC_RESERVED_CAPTION, x_Reserved);
DDX_Control(pDX, IDC_PHYSICAL_VALUE, c_PhysicalValue);
DDX_Control(pDX, IDC_VIRTUAL_VALUE, c_VirtualValue);
}


BEGIN_MESSAGE_MAP(CExtendedCPU8, CLeaves)
ON_WM_VSCROLL()
END_MESSAGE_MAP()

// CExtendedCPU8 message handlers

/****************************************************************************
*                         CExtendedCPU8::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU8::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000008, regs);

    EAX8x EAX;
    EAX.w = regs.EAX;
    
    SETWINDOWBIT(PhysicalAddressBits, EAX, bits);
    SETWINDOWBIT(Reserved, EAX, bits);
    SETWINDOWBIT(VirtualAddressBits, EAX, bits);

    CString s = FormatMagnitude(EAX.bits.PhysicalAddressBits);
    c_PhysicalValue.SetWindowText(s);
    
    s = FormatMagnitude(EAX.bits.VirtualAddressBits);
    c_VirtualValue.SetWindowText(s);
    
#ifdef _DEBUG_PRINTOUT
    c_SpinPhysical.EnableWindow(TRUE);
#endif

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU8::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU8::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    SETCOLOR(PhysicalAddressBits);         // 7..0
    SETCOLOR(VirtualAddressBits);          // 15..8
    SETRESERVEDCOLOR(Reserved);            // 31..16

#ifdef _DEBUG_PRINTOUT
    c_SpinPhysical.SetRange(0, 64);
    c_SpinPhysical.SetPos(32);
    c_SpinPhysical.ShowWindow(SW_SHOW);
    c_SpinPhysical.EnableWindow(TRUE);
#endif

    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }

/****************************************************************************
*                          CExtendedCPU8::OnVScroll
* Inputs:
*       ¶
* Result: void
*       
* Effect: 
*       Handles the spin control
****************************************************************************/

void CExtendedCPU8::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar)
    {
#ifdef _DEBUG_PRINTOUT
     int n = c_SpinPhysical.GetPos();
     CString s = FormatMagnitude(n);
     c_PhysicalValue.SetWindowText(s);
#endif     
    } // CExtendedCPU8::OnVScroll
