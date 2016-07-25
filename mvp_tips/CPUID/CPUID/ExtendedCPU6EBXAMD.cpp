// ExtendedCPU6EBXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU6EBXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"

// CExtendedCPU6EBXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU6EBXAMD, CExtendedCPU6AMD)
CExtendedCPU6EBXAMD::CExtendedCPU6EBXAMD()
        :  CExtendedCPU6AMD(CExtendedCPU6EBXAMD::IDD)
{
}

CExtendedCPU6EBXAMD::~CExtendedCPU6EBXAMD()
{
}

void CExtendedCPU6EBXAMD::DoDataExchange(CDataExchange* pDX)
{
  CExtendedCPU6AMD::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU6EBXAMD, CExtendedCPU6AMD)
END_MESSAGE_MAP()


// CExtendedCPU6EBXAMD message handlers

/****************************************************************************
*                         CExtendedCPU6EBXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU6EBXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000006, regs);

    FillIn(CacheTLBInfo(IDS_EXTENDED_6_EBX_31_28,
                        IDS_EXTENDED_6_EBX_27_16,
                        IDS_EXTENDED_6_EBX_15_12,
                        IDS_EXTENDED_6_EBX_11_0,
                        IDS_EXTENDED_6_EBX_CAPTION), regs.EBX);
    return CExtendedCPU6AMD::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU6EBXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU6EBXAMD::OnInitDialog()
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
