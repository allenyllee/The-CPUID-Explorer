// BasicCPU3Regs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU3Regs.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CurrentProcessor.h"

// CBasicCPU3Regs dialog

IMPLEMENT_DYNCREATE(CBasicCPU3Regs, CLeaves)
CBasicCPU3Regs::CBasicCPU3Regs()
        : CLeaves(CBasicCPU3Regs::IDD)
{
}

CBasicCPU3Regs::~CBasicCPU3Regs()
{
}

void CBasicCPU3Regs::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
DDX_Control(pDX, IDC_PSN, c_PSN);
}


BEGIN_MESSAGE_MAP(CBasicCPU3Regs, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU3Regs message handlers

/****************************************************************************
*                         CBasicCPU3Regs::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CBasicCPU3Regs::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(3, regs);

    CString s;
    s.Format(_T("%08x"), regs.EAX);
    c_EAX.SetWindowText(s);

    s.Format(_T("%08x"), regs.EBX);
    c_EBX.SetWindowText(s);

    s.Format(_T("%08x"), regs.ECX);
    c_ECX.SetWindowText(s);

    s.Format(_T("%08x"), regs.EDX);
    c_EDX.SetWindowText(s);

    
    s.Format(_T("%08X:%08X"), regs.ECX, regs.EDX);
    c_PSN.SetWindowText(s);
    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                        CBasicCPU3Regs::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Intializes the dialog
****************************************************************************/

BOOL CBasicCPU3Regs::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);
    SetFixedFont(c_PSN);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
