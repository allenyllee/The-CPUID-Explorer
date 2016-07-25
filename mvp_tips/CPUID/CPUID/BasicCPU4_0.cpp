
// BasicCPU4_0.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU4_0.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "CPUIDRegs.h"

// CBasicCPU4_0 dialog

IMPLEMENT_DYNCREATE(CBasicCPU4_0, CBasicCPU4_0_31)
CBasicCPU4_0::CBasicCPU4_0()
        : CBasicCPU4_0_31()
{
}

CBasicCPU4_0::~CBasicCPU4_0()
{
}

void CBasicCPU4_0::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU4_0_31::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU4_0, CBasicCPU4_0_31)
END_MESSAGE_MAP()


// CBasicCPU4_0 message handlers

BOOL CBasicCPU4_0::OnInitDialog()
    {
     CBasicCPU4_0_31::OnInitDialog();

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU4_0::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU4_0::OnSetActive()
    {
     ShowCacheParameters(0);
     return CBasicCPU4_0_31::OnSetActive();
    }
