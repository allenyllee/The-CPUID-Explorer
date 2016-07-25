// ExtendedCPU6EAXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU6EAXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"

// CExtendedCPU6EAXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU6EAXAMD, CExtendedCPU6AMD)
CExtendedCPU6EAXAMD::CExtendedCPU6EAXAMD()
        :  CExtendedCPU6AMD(CExtendedCPU6EAXAMD::IDD)
{
}

CExtendedCPU6EAXAMD::~CExtendedCPU6EAXAMD()
{
}

void CExtendedCPU6EAXAMD::DoDataExchange(CDataExchange* pDX)
{
  CExtendedCPU6AMD::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU6EAXAMD, CExtendedCPU6AMD)
END_MESSAGE_MAP()


// CExtendedCPU6EAXAMD message handlers

/****************************************************************************
*                         CExtendedCPU6EAXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU6EAXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000006, regs);

    FillIn(CacheTLBInfo(IDS_EXTENDED_6_EAX_31_28,
                        IDS_EXTENDED_6_EAX_27_16,
                        IDS_EXTENDED_6_EAX_15_12,
                        IDS_EXTENDED_6_EAX_11_0,
                        IDS_EXTENDED_6_EAX_CAPTION), regs.EAX);
    return CExtendedCPU6AMD::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU6EAXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU6EAXAMD::OnInitDialog()
   {
    CExtendedCPU6AMD::OnInitDialog();

    c_Caption.SetWindowText(_T(""));

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    SETCOLOR(11_0);
    SETCOLOR(15_12);
    SETCOLOR(27_16);
    SETCOLOR(31_28);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
