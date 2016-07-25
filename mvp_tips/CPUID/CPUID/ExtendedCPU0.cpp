// ExtendedCPU0.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU0.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CurrentProcessor.h"

// CExtendedCPU0 dialog

IMPLEMENT_DYNCREATE(CExtendedCPU0, CLeaves)
CExtendedCPU0::CExtendedCPU0()
        : CLeaves(CExtendedCPU0::IDD)
{
}

CExtendedCPU0::~CExtendedCPU0()
{
}

void CExtendedCPU0::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU0, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU0 message handlers

/****************************************************************************
*                         CExtendedCPU0::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU0::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000000, regs);

    CString s;
    s.Format(_T("%08x"), regs.EAX);
    c_EAX.SetWindowText(s);
    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU0::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU0::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
