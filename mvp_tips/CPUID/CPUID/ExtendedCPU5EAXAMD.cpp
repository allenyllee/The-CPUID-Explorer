// ExtendedCPU5EAXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU5EAXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"

// CExtendedCPU5EAXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU5EAXAMD, CExtendedCPU5AMD)
CExtendedCPU5EAXAMD::CExtendedCPU5EAXAMD()
        :  CExtendedCPU5AMD(CExtendedCPU5EAXAMD::IDD)
{
}

CExtendedCPU5EAXAMD::~CExtendedCPU5EAXAMD()
{
}

void CExtendedCPU5EAXAMD::DoDataExchange(CDataExchange* pDX)
{
  CExtendedCPU5AMD::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU5EAXAMD, CExtendedCPU5AMD)
END_MESSAGE_MAP()


// CExtendedCPU5EAXAMD message handlers

/****************************************************************************
*                         CExtendedCPU5EAXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU5EAXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000005, regs);

    FillIn(CacheTLBInfo(IDS_EXTENDED_5_EAX_31_24,
                        IDS_EXTENDED_5_EAX_23_16,
                        IDS_EXTENDED_5_EAX_15_8,
                        IDS_EXTENDED_5_EAX_7_0,
                        IDS_EXTENDED_5_EAX_CAPTION), regs.EAX);
    return CExtendedCPU5AMD::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU5EAXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU5EAXAMD::OnInitDialog()
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
