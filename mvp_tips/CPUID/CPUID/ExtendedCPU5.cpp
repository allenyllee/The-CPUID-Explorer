// ExtendedCPU5.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU5.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"

// CExtendedCPU5 dialog

IMPLEMENT_DYNCREATE(CExtendedCPU5, CLeaves)
CExtendedCPU5::CExtendedCPU5()
        : CLeaves(CExtendedCPU5::IDD)
{
}

CExtendedCPU5::~CExtendedCPU5()
{
}

void CExtendedCPU5::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU5, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU5 message handlers

/****************************************************************************
*                         CExtendedCPU5::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU5::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000005, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU5::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU5::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
