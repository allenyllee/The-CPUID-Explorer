// ExtendedCPU7Intel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU7Intel.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"

// CExtendedCPU7Intel dialog

IMPLEMENT_DYNCREATE(CExtendedCPU7Intel, CLeaves)
CExtendedCPU7Intel::CExtendedCPU7Intel()
        : CLeaves(CExtendedCPU7Intel::IDD)
{
}

CExtendedCPU7Intel::~CExtendedCPU7Intel()
{
}

void CExtendedCPU7Intel::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU7Intel, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU7Intel message handlers

BOOL CExtendedCPU7Intel::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000007, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU7Intel::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU7Intel::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
