// BasicCPU1EAXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EAXAMD.h"
#include "FormatBinary.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CPUIDRegs.h"
#include "SetColor.h"

// CBasicCPU1EAX dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EAXAMD, CBasicCPU1EAX)
CBasicCPU1EAXAMD::CBasicCPU1EAXAMD()
        : CBasicCPU1EAX(CBasicCPU1EAXAMD::IDD)
{
}

CBasicCPU1EAXAMD::~CBasicCPU1EAXAMD()
{
}

void CBasicCPU1EAXAMD::DoDataExchange(CDataExchange* pDX)
{
CBasicCPU1EAX::DoDataExchange(pDX);
DDX_Control(pDX, IDC_RESERVED_15_12, c_Reserved_15_12);
DDX_Control(pDX, IDC_RESERVED_15_12_CAPTION, x_Reserved_15_12);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EAXAMD, CBasicCPU1EAX)
END_MESSAGE_MAP()

// CBasicCPU1EAXAMD message handlers

/****************************************************************************
*                       CBasicCPU1EAXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the controls unique to the AMD display
****************************************************************************/

BOOL CBasicCPU1EAXAMD::OnInitDialog()
    {
     CBasicCPU1EAX::OnInitDialog();

     SETRESERVEDCOLOR(Reserved_15_12);

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                       CBasicCPU1EAXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports status
****************************************************************************/

BOOL CBasicCPU1EAXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(1, regs);

    EAX1b EAX;
    EAX.w = regs.EAX;

    CString s;
    s = FormatBinary(EAX.AMD.Reserved2, 4);
    c_Reserved_15_12.SetWindowText(s + _T("B"));

    return CBasicCPU1EAX::OnSetActive();
   }

