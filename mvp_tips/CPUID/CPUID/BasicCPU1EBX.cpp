
// BasicCPU1EBX.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EBX.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "CPUIDRegs.h"

// CBasicCPU1EBX dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EBX, CLeaves)
CBasicCPU1EBX::CBasicCPU1EBX()
        : CLeaves(CBasicCPU1EBX::IDD)
{
}

CBasicCPU1EBX::~CBasicCPU1EBX()
{
}

void CBasicCPU1EBX::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_INITIAL_APIC_CAPTION, x_InitialAPICID);
DDX_Control(pDX, IDC_INITIAL_APIC, c_InitialAPICID);
DDX_Control(pDX, IDC_CLFLUSH_LINE_SIZE, c_CLFLUSHLineSize);
DDX_Control(pDX, IDC_CLFLUSH_LINE_SIZE_CAPTION, x_CLFLUSHLineSize);
DDX_Control(pDX, IDC_LOGICAL_PROCESSORS, c_LogicalProcessors);
DDX_Control(pDX, IDC_LOGICAL_PROCESSORS_CAPTION, x_LogicalProcessors);
DDX_Control(pDX, IDC_BRAND_INDEX_CAPTION, x_BrandIndex);
DDX_Control(pDX, IDC_BRAND_INDEX, c_BrandIndex);
DDX_Control(pDX, IDC_CACHE_LINE_SIZE, c_CacheLineSize);
DDX_Control(pDX, IDC_BRAND_INDEX_NAME, c_BrandIndexName);
}


BEGIN_MESSAGE_MAP(CBasicCPU1EBX, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU1EBX message handlers

BOOL CBasicCPU1EBX::OnInitDialog()
    {
     CLeaves::OnInitDialog();

     c_InitialAPICID.SetBkColor(RGB(128,128,128));
     x_InitialAPICID.SetBkColor(c_InitialAPICID.GetBkColor());

     c_CLFLUSHLineSize.SetBkColor(RGB(255,255,0));
     x_CLFLUSHLineSize.SetBkColor(c_CLFLUSHLineSize.GetBkColor());

     c_LogicalProcessors.SetBkColor(RGB(255,128,255));
     x_LogicalProcessors.SetBkColor(c_LogicalProcessors.GetBkColor());

     c_BrandIndex.SetBkColor(RGB(255,179,102));
     x_BrandIndex.SetBkColor(c_BrandIndex.GetBkColor());
     
     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU1EBX::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU1EBX::OnSetActive()
    {
     CPUregs regs;
     GetAndReport(1, regs);

     EBX1b EBX;
     EBX.w = regs.EBX;

     CString s;
     SETWINDOWHEX(BrandIndex, EBX,bits, 2);
     SETWINDOWBIT(LogicalProcessors, EBX, bits);
     SETWINDOWBIT(CLFLUSHLineSize, EBX, bits);

     int brand = min(EBX.bits.BrandIndex, 255);
     s.LoadString(IDS_BRAND_INDEX_BASE + brand);
     if(s.IsEmpty())
        c_BrandIndexName.ShowWindow(SW_HIDE);
     else
        c_BrandIndexName.ShowWindow(SW_SHOW);
     c_BrandIndexName.SetWindowText(s);
     

     s.Format(_T("%d"), EBX.bits.CLFLUSHLineSize * 8);
     c_CacheLineSize.SetWindowText(s);
     
     s.Format(_T("%d"), EBX.bits.InitialAPICID);
     c_InitialAPICID.SetWindowText(s);
     return CLeaves::OnSetActive();
    }
