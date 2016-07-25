
// BasicCPU4_2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU4_2.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "CPUIDRegs.h"

// CBasicCPU4_2 dialog

IMPLEMENT_DYNCREATE(CBasicCPU4_2, CBasicCPU4_0_31)
CBasicCPU4_2::CBasicCPU4_2()
        : CBasicCPU4_0_31()
{
}

CBasicCPU4_2::~CBasicCPU4_2()
{
}

void CBasicCPU4_2::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU4_0_31::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU4_2, CBasicCPU4_0_31)
END_MESSAGE_MAP()


// CBasicCPU4_2 message handlers

BOOL CBasicCPU4_2::OnInitDialog()
    {
     CBasicCPU4_0_31::OnInitDialog();

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU4_2::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU4_2::OnSetActive()
    {
     ShowCacheParameters(2);
     return CBasicCPU4_0_31::OnSetActive();
    }
