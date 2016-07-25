// ExtendedCPU5EDXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU5EDXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"

// CExtendedCPU5EDXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU5EDXAMD, CExtendedCPU5AMD)
CExtendedCPU5EDXAMD::CExtendedCPU5EDXAMD()
        :  CExtendedCPU5AMD(CExtendedCPU5EDXAMD::IDD)
{
}

CExtendedCPU5EDXAMD::~CExtendedCPU5EDXAMD()
{
}

void CExtendedCPU5EDXAMD::DoDataExchange(CDataExchange* pDX)
{
  CExtendedCPU5AMD::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU5EDXAMD, CExtendedCPU5AMD)
END_MESSAGE_MAP()


// CExtendedCPU5EDXAMD message handlers

/****************************************************************************
*                         CExtendedCPU5EDXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU5EDXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000005, regs);

    FillIn(CacheTLBInfo(IDS_EXTENDED_5_EDX_31_24,
                        IDS_EXTENDED_5_EDX_23_16,
                        IDS_EXTENDED_5_EDX_15_8,
                        IDS_EXTENDED_5_EDX_7_0,
                        IDS_EXTENDED_5_EDX_CAPTION), regs.EDX);
    return CExtendedCPU5AMD::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU5EDXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU5EDXAMD::OnInitDialog()
   {
    CExtendedCPU5AMD::OnInitDialog();

    c_Caption.SetWindowText(_T(""));

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    SETCOLOR(7_0);
    SETCOLOR(15_8);
    SETCOLOR(23_16);
    SETCOLOR(31_24);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
