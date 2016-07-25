// ExtendedCPU3.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU3.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"

// CExtendedCPU3 dialog

IMPLEMENT_DYNCREATE(CExtendedCPU3, CExtendedCPU24)
CExtendedCPU3::CExtendedCPU3()
        : CExtendedCPU24()
{
}

CExtendedCPU3::~CExtendedCPU3()
{
}

void CExtendedCPU3::DoDataExchange(CDataExchange* pDX)
{
 CExtendedCPU24::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU3, CExtendedCPU24)
END_MESSAGE_MAP()


// CExtendedCPU3 message handlers

BOOL CExtendedCPU3::OnSetActive()
   {
    ShowExtendedCPU(0x80000003);
    return CExtendedCPU24::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU3::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU3::OnInitDialog()
   {
    CExtendedCPU24::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
