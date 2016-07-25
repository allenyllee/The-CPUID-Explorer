// ExtendedCPU5Intel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU5Intel.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"

// CExtendedCPU5Intel dialog

IMPLEMENT_DYNCREATE(CExtendedCPU5Intel, CLeaves)
CExtendedCPU5Intel::CExtendedCPU5Intel()
        : CLeaves(CExtendedCPU5Intel::IDD)
{
}

CExtendedCPU5Intel::~CExtendedCPU5Intel()
{
}

void CExtendedCPU5Intel::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU5Intel, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU5Intel message handlers

/****************************************************************************
*                         CExtendedCPU5Intel::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU5Intel::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000005, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU5Intel::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU5Intel::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
