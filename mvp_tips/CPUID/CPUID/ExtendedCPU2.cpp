// ExtendedCPU2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU2.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"

// CExtendedCPU2 dialog

IMPLEMENT_DYNCREATE(CExtendedCPU2, CExtendedCPU24)
CExtendedCPU2::CExtendedCPU2()
        : CExtendedCPU24()
{
}

CExtendedCPU2::~CExtendedCPU2()
{
}

void CExtendedCPU2::DoDataExchange(CDataExchange* pDX)
{
 CExtendedCPU24::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU2, CExtendedCPU24)
END_MESSAGE_MAP()


// CExtendedCPU2 message handlers

BOOL CExtendedCPU2::OnSetActive()
   {
    ShowExtendedCPU(0x80000002);
    return CExtendedCPU24::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU2::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU2::OnInitDialog()
   {
    CExtendedCPU24::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
