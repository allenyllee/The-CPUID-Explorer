// BasicCPU9Regs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU9Regs.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CurrentProcessor.h"

// CBasicCPU9Regs dialog

IMPLEMENT_DYNCREATE(CBasicCPU9Regs, CLeaves)
CBasicCPU9Regs::CBasicCPU9Regs()
        : CLeaves(CBasicCPU9Regs::IDD)
{
}

CBasicCPU9Regs::~CBasicCPU9Regs()
{
}

void CBasicCPU9Regs::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU9Regs, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU9Regs message handlers

BOOL CBasicCPU9Regs::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(9, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CBasicCPU9Regs::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CBasicCPU9Regs::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
