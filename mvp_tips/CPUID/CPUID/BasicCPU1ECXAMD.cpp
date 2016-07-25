
// BasicCPU1ECXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1ECXAMD.h"
#include "CPUIDx86.h"
#include "SetColor.h"
#include "SetWindowBit.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "CPUIDRegs.h"
#include "FormatBinary.h"
#include "SetAlign.h"
// CBasicCPU1ECXAMD dialog

IMPLEMENT_DYNCREATE(CBasicCPU1ECXAMD, CBasicCPU1ECX)


CBasicCPU1ECXAMD::CBasicCPU1ECXAMD()
        : CBasicCPU1ECX(CBasicCPU1ECXAMD::IDD)
{
}

CBasicCPU1ECXAMD::~CBasicCPU1ECXAMD()
{
}

/****************************************************************************
*                        CBasicCPU1ECXAMD::DoDataExchange
* Inputs:
*       CDataExchage * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CBasicCPU1ECXAMD::DoDataExchange(CDataExchange* pDX)
   {
    CBasicCPU1ECX::DoDataExchange(pDX);
   }

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1ECXAMD, CBasicCPU1ECX)
END_MESSAGE_MAP()


// CBasicCPU1ECXAMD message handlers

/****************************************************************************
*                         CBasicCPU1ECXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the controls
****************************************************************************/

BOOL CBasicCPU1ECXAMD::OnInitDialog()
    {
     CBasicCPU1ECX::OnInitDialog();

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU1ECXAMD::OnSetActive
* Result: void
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU1ECXAMD::OnSetActive()
    {
     CPUregs regs;
     GetAndReport(1, regs);


     ECX1b ECX;
     ECX.w = regs.ECX;

     CString s;

     s = FormatBinary(ECX.AMD.Reserved1, 3);
     c_Reserved1.SetWindowText(s + _T("B"));

     s = FormatBinary(ECX.AMD.Reserved2, 4);
     c_Reserved2.SetWindowText(s + _T("B"));

     s = FormatBinary(ECX.AMD.Reserved3, 4);
     c_Reserved3.SetWindowText(s + _T("B"));

     s.Format(_T("%018dB"), ECX.Intel.Reserved6);
     c_Reserved6.SetWindowText(s);

     return CBasicCPU1ECX::OnSetActive();
    }
