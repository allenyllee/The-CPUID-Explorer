// ExtendedCPU10AMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU10AMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "FormatMagnitude.h"

// CExtendedCPU10AMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU10AMD, CLeaves)
CExtendedCPU10AMD::CExtendedCPU10AMD()
        : CLeaves(CExtendedCPU10AMD::IDD)
{
}

CExtendedCPU10AMD::~CExtendedCPU10AMD()
{
}

void CExtendedCPU10AMD::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU10AMD, CLeaves)
END_MESSAGE_MAP()

// CExtendedCPU10AMD message handlers

/****************************************************************************
*                         CExtendedCPU10AMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU10AMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x8000000A, regs);


    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU10AMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU10AMD::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
