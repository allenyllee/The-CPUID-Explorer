
// BasicCPU4_1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU4_1.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "CPUIDRegs.h"

// CBasicCPU4_1 dialog

IMPLEMENT_DYNCREATE(CBasicCPU4_1, CBasicCPU4_0_31)
CBasicCPU4_1::CBasicCPU4_1()
        : CBasicCPU4_0_31()
{
}

CBasicCPU4_1::~CBasicCPU4_1()
{
}

void CBasicCPU4_1::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU4_0_31::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU4_1, CBasicCPU4_0_31)
END_MESSAGE_MAP()


// CBasicCPU4_1 message handlers

BOOL CBasicCPU4_1::OnInitDialog()
    {
     CBasicCPU4_0_31::OnInitDialog();

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU4_1::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU4_1::OnSetActive()
    {
     ShowCacheParameters(1);
     return CBasicCPU4_0_31::OnSetActive();
    }
