
// BasicCPU4_3.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU4_3.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "CPUIDRegs.h"

// CBasicCPU4_3 dialog

IMPLEMENT_DYNCREATE(CBasicCPU4_3, CBasicCPU4_0_31)
CBasicCPU4_3::CBasicCPU4_3()
        : CBasicCPU4_0_31()
{
}

CBasicCPU4_3::~CBasicCPU4_3()
{
}

void CBasicCPU4_3::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU4_0_31::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU4_3, CBasicCPU4_0_31)
END_MESSAGE_MAP()


// CBasicCPU4_3 message handlers

BOOL CBasicCPU4_3::OnInitDialog()
    {
     CBasicCPU4_0_31::OnInitDialog();

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU4_3::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU4_3::OnSetActive()
    {
     ShowCacheParameters(3);
     return CBasicCPU4_0_31::OnSetActive();
    }
