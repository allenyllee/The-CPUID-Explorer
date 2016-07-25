// ExtendedCPU8Intel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU8Intel.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "FormatMagnitude.h"

// CExtendedCPU8Intel dialog

IMPLEMENT_DYNCREATE(CExtendedCPU8Intel, CExtendedCPU8)
CExtendedCPU8Intel::CExtendedCPU8Intel()
        : CExtendedCPU8(CExtendedCPU8Intel::IDD)
{
}

CExtendedCPU8Intel::~CExtendedCPU8Intel()
{
}

void CExtendedCPU8Intel::DoDataExchange(CDataExchange* pDX)
{
CExtendedCPU8::DoDataExchange(pDX);
DDX_Control(pDX, IDC_ECX, c_ECX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU8Intel, CExtendedCPU8)
END_MESSAGE_MAP()

// CExtendedCPU8Intel message handlers

/****************************************************************************
*                         CExtendedCPU8Intel::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU8Intel::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000008, regs);


    return CExtendedCPU8::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU8Intel::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU8Intel::OnInitDialog()
   {
    CExtendedCPU8::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
