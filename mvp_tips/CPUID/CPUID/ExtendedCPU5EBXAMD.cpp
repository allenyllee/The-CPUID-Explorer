// ExtendedCPU5EBXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU5EBXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"

// CExtendedCPU5EBXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU5EBXAMD, CExtendedCPU5AMD)
CExtendedCPU5EBXAMD::CExtendedCPU5EBXAMD()
        :  CExtendedCPU5AMD(CExtendedCPU5EBXAMD::IDD)
{
}

CExtendedCPU5EBXAMD::~CExtendedCPU5EBXAMD()
{
}

void CExtendedCPU5EBXAMD::DoDataExchange(CDataExchange* pDX)
{
  CExtendedCPU5AMD::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU5EBXAMD, CExtendedCPU5AMD)
END_MESSAGE_MAP()


// CExtendedCPU5EBXAMD message handlers

/****************************************************************************
*                         CExtendedCPU5EBXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU5EBXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000005, regs);

    FillIn(CacheTLBInfo(IDS_EXTENDED_5_EBX_31_24,
                        IDS_EXTENDED_5_EBX_23_16,
                        IDS_EXTENDED_5_EBX_15_8,
                        IDS_EXTENDED_5_EBX_7_0,
                        IDS_EXTENDED_5_EBX_CAPTION), regs.EBX);
    return CExtendedCPU5AMD::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU5EBXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU5EBXAMD::OnInitDialog()
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
