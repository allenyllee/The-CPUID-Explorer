// BasicCPU8Regs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU8Regs.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CurrentProcessor.h"

// CBasicCPU8Regs dialog

IMPLEMENT_DYNCREATE(CBasicCPU8Regs, CLeaves)
CBasicCPU8Regs::CBasicCPU8Regs()
        : CLeaves(CBasicCPU8Regs::IDD)
{
}

CBasicCPU8Regs::~CBasicCPU8Regs()
{
}

void CBasicCPU8Regs::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU8Regs, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU8Regs message handlers

BOOL CBasicCPU8Regs::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(8, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CBasicCPU8Regs::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CBasicCPU8Regs::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
