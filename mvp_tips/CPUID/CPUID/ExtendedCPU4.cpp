// ExtendedCPU4.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU4.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"

// CExtendedCPU4 dialog

IMPLEMENT_DYNCREATE(CExtendedCPU4, CExtendedCPU24)
CExtendedCPU4::CExtendedCPU4()
        : CExtendedCPU24()
{
}

CExtendedCPU4::~CExtendedCPU4()
{
}

void CExtendedCPU4::DoDataExchange(CDataExchange* pDX)
{
 CExtendedCPU24::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtendedCPU4, CExtendedCPU24)
END_MESSAGE_MAP()


// CExtendedCPU4 message handlers

BOOL CExtendedCPU4::OnSetActive()
   {
    ShowExtendedCPU(0x80000004);
    return CExtendedCPU24::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU4::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU4::OnInitDialog()
   {
    CExtendedCPU24::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
