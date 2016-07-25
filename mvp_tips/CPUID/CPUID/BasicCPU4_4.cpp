
// BasicCPU4_4.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU4_4.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "CPUIDRegs.h"

// CBasicCPU4_4 dialog

IMPLEMENT_DYNCREATE(CBasicCPU4_4, CBasicCPU4_0_31)
CBasicCPU4_4::CBasicCPU4_4()
        : CBasicCPU4_0_31()
{
}

CBasicCPU4_4::~CBasicCPU4_4()
{
}

void CBasicCPU4_4::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU4_0_31::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBasicCPU4_4, CBasicCPU4_0_31)
END_MESSAGE_MAP()


// CBasicCPU4_4 message handlers

BOOL CBasicCPU4_4::OnInitDialog()
    {
     CBasicCPU4_0_31::OnInitDialog();

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU4_4::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU4_4::OnSetActive()
    {
     ShowCacheParameters(4);
     return CBasicCPU4_0_31::OnSetActive();
    }
