// ExtendedCPU1EBXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU1EBXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "CurrentProcessor.h"

// CExtendedCPU1EBXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU1EBXAMD, CLeaves)

CExtendedCPU1EBXAMD::CExtendedCPU1EBXAMD()
        : CLeaves(CExtendedCPU1EBXAMD::IDD)
{
}

CExtendedCPU1EBXAMD::~CExtendedCPU1EBXAMD()
{
}

/****************************************************************************
*                     CExtendedCPU1ECXAMD::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CExtendedCPU1EBXAMD::DoDataExchange(CDataExchange* pDX)
   {
    CLeaves::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RESERVED, c_Reserved);
    DDX_Control(pDX, IDC_RESERVED_CAPTION, x_Reserved);
    DDX_Control(pDX, IDC_BRANDID, c_BrandId);
    DDX_Control(pDX, IDC_BRANDID_CAPTION, x_BrandId);
   }


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CExtendedCPU1EBXAMD, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU1EBXAMD message handlers

/****************************************************************************
*                         CExtendedCPU1EBXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU1EBXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000001, regs);

    EBX1x EBX;
    EBX.w = regs.EBX;
    
    CString s;
    s.Format(_T("%04XH"), EBX.AMD.Reserved);
    c_Reserved.SetWindowText(s);

    s.Format(_T("%04XH"), EBX.AMD.BrandId);
    c_BrandId.SetWindowText(s);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU1EBXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU1EBXAMD::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    SETCOLOR(BrandId);                // 15..0
    SETRESERVEDCOLOR(Reserved);      // 31..16

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
