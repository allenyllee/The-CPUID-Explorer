// ExtendedCPU5ECXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU5ECXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"

// CExtendedCPU5ECXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU5ECXAMD, CExtendedCPU5AMD)
CExtendedCPU5ECXAMD::CExtendedCPU5ECXAMD()
        :  CExtendedCPU5AMD(CExtendedCPU5ECXAMD::IDD)
{
}

CExtendedCPU5ECXAMD::~CExtendedCPU5ECXAMD()
{
}

void CExtendedCPU5ECXAMD::DoDataExchange(CDataExchange* pDX)
{
  CExtendedCPU5AMD::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU5ECXAMD, CExtendedCPU5AMD)
END_MESSAGE_MAP()


// CExtendedCPU5ECXAMD message handlers

/****************************************************************************
*                         CExtendedCPU5ECXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU5ECXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000005, regs);

    FillIn(CacheTLBInfo(IDS_EXTENDED_5_ECX_31_24,
                        IDS_EXTENDED_5_ECX_23_16,
                        IDS_EXTENDED_5_ECX_15_8,
                        IDS_EXTENDED_5_ECX_7_0,
                        IDS_EXTENDED_5_ECX_CAPTION), regs.ECX);
    return CExtendedCPU5AMD::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU5ECXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU5ECXAMD::OnInitDialog()
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
