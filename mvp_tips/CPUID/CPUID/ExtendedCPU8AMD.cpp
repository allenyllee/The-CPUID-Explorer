// ExtendedCPU8AMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU8AMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "FormatMagnitude.h"

// CExtendedCPU8AMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU8AMD, CExtendedCPU8)
CExtendedCPU8AMD::CExtendedCPU8AMD()
        : CExtendedCPU8(CExtendedCPU8AMD::IDD)
{
}

CExtendedCPU8AMD::~CExtendedCPU8AMD()
{
}

void CExtendedCPU8AMD::DoDataExchange(CDataExchange* pDX)
{
CExtendedCPU8::DoDataExchange(pDX);
DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);
DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);
DDX_Control(pDX, IDC_NCORES, c_NC);
DDX_Control(pDX, IDC_NCORES_CAPTION, x_NC);
DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);
DDX_Control(pDX, IDC_RESERVED3_CAPTION, x_Reserved3);
DDX_Control(pDX, IDC_APIC_ID_CORE_ID_SIZE, c_ApicIdCoreIdSize);
DDX_Control(pDX, IDC_APIC_ID_CORE_ID_SIZE_CAPTION, x_ApicIdCoreIdSize);
DDX_Control(pDX, IDC_ACTUAL_CORES, c_ActualCores);
}


BEGIN_MESSAGE_MAP(CExtendedCPU8AMD, CExtendedCPU8)
END_MESSAGE_MAP()

// CExtendedCPU8AMD message handlers

/****************************************************************************
*                         CExtendedCPU8AMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU8AMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000008, regs);

    ECX8x ECX;
    ECX.w = regs.ECX;

    SETWINDOWBIT(NC, ECX, AMD);
    SETWINDOWBIT(Reserved2, ECX, AMD);
    SETWINDOWBIT(Reserved3, ECX, AMD);
    SETWINDOWBIT(ApicIdCoreIdSize, ECX, AMD);

    UINT cores;
    if(ECX.AMD.ApicIdCoreIdSize == 0)
       { /* legacy dual-core */
        cores = ECX.AMD.NC + 1;
       } /* legacy dual-core */
    else
       { /* newer dual-core */
        cores = 1 << ECX.AMD.ApicIdCoreIdSize;
       } /* newer dual-core */

    CString s;
    s.Format(_T("%d"), cores);
    c_ActualCores.SetWindowText(s);
    
    return CExtendedCPU8::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU8AMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU8AMD::OnInitDialog()
   {
    CExtendedCPU8::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    // ECX:
    SETRESERVEDCOLOR(Reserved2);                // 31..16
    SETCOLOR(ApicIdCoreIdSize);                 // 15..12
    SETRESERVEDCOLOR(Reserved3);                // 11..8
    SETCOLOR(NC);                               // 7..0

    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
