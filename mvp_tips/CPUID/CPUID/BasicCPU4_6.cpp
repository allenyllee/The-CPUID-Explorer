
// BasicCPU4_6.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU4_6.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "CPUIDRegs.h"

// CBasicCPU4_6 dialog

IMPLEMENT_DYNCREATE(CBasicCPU4_6, CBasicCPU4_0_31)
CBasicCPU4_6::CBasicCPU4_6()
        : CBasicCPU4_0_31()
{
}

CBasicCPU4_6::~CBasicCPU4_6()
{
}

void CBasicCPU4_6::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU4_0_31::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU4_6, CBasicCPU4_0_31)
END_MESSAGE_MAP()


// CBasicCPU4_6 message handlers

BOOL CBasicCPU4_6::OnInitDialog()
    {
     CBasicCPU4_0_31::OnInitDialog();

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU4_6::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU4_6::OnSetActive()
    {
     ShowCacheParameters(6);
     return CBasicCPU4_0_31::OnSetActive();
    }
