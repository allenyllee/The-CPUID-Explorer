// BasicCPU7Regs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU7Regs.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CurrentProcessor.h"

// CBasicCPU7Regs dialog

IMPLEMENT_DYNCREATE(CBasicCPU7Regs, CLeaves)
CBasicCPU7Regs::CBasicCPU7Regs()
        : CLeaves(CBasicCPU7Regs::IDD)
{
}

CBasicCPU7Regs::~CBasicCPU7Regs()
{
}

void CBasicCPU7Regs::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU7Regs, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU7Regs message handlers

BOOL CBasicCPU7Regs::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(7, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CBasicCPU7Regs::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CBasicCPU7Regs::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
