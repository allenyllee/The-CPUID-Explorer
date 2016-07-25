// BasicCPU0.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU0.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "GetCPUName.h"

// CBasicCPU0 dialog

IMPLEMENT_DYNCREATE(CBasicCPU0, CLeaves)
CBasicCPU0::CBasicCPU0()
        : CLeaves(CBasicCPU0::IDD)
{
}

CBasicCPU0::~CBasicCPU0()
{
}

void CBasicCPU0::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
DDX_Control(pDX, IDC_CPU_TYPENAME, c_CPUTypeName);
}


BEGIN_MESSAGE_MAP(CBasicCPU0, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU0 message handlers

/****************************************************************************
*                           CBasicCPU0::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Does a CPUID(0) and displays the result
****************************************************************************/

BOOL CBasicCPU0::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0, regs);

    CString s;
    s.Format(_T("%d"), regs.EAX);
    c_EAX.SetWindowText(s);

    CStringA b((LPCSTR)&regs.EBX, 4);
    s = _T("\"") + b +_T("\"");
    c_EBX.SetWindowText(s);

    CStringA c((LPCSTR)&regs.ECX, 4);
    s = _T("\"") + c + _T("\"");
    c_ECX.SetWindowText(s);

    CStringA d((LPCSTR)&regs.EDX, 4);
    s = _T("\"") + d + _T("\"");
    c_EDX.SetWindowText(s);


    CString name = GetCPUTypeName();
    
    c_CPUTypeName.SetWindowText(name);
    return CLeaves::OnSetActive();
   }

BOOL CBasicCPU0::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
