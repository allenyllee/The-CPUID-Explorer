// ExtendedCPU7AMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU7AMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "SetAlign.h"

// CExtendedCPU7AMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU7AMD, CLeaves)
CExtendedCPU7AMD::CExtendedCPU7AMD()
        : CLeaves(CExtendedCPU7AMD::IDD)
{
}

CExtendedCPU7AMD::~CExtendedCPU7AMD()
{
}

void CExtendedCPU7AMD::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_TS, c_TS);
DDX_Control(pDX, IDC_TS_CAPTION, x_TS);
DDX_Control(pDX, IDC_FID, c_FID);
DDX_Control(pDX, IDC_FID_CAPTION, x_FID);
DDX_Control(pDX, IDC_VID, c_VID);
DDX_Control(pDX, IDC_VID_CAPTION, x_VID);
DDX_Control(pDX, IDC_TTP, c_TTP);
DDX_Control(pDX, IDC_TTP_CAPTION, x_TTP);
DDX_Control(pDX, IDC_TM, c_TM);
DDX_Control(pDX, IDC_TM_CAPTION, x_TM);
DDX_Control(pDX, IDC_STC, c_STC);
DDX_Control(pDX, IDC_STC_CAPTION, x_STC);
DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);
DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);
DDX_Control(pDX, IDC_TSC_INVARIANT, c_TSCInvariant);
DDX_Control(pDX, IDC_TSC_INVARIANT_CAPTION, x_TSCInvariant);
DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);
DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);
}


BEGIN_MESSAGE_MAP(CExtendedCPU7AMD, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU7AMD message handlers

BOOL CExtendedCPU7AMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000007, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU7AMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU7AMD::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);

    SETCOLOR(TS);     // 0
    SETALIGN(TS);     // 0
    SETCOLOR(FID);    // 1
    SETALIGN(FID);    // 1
    SETCOLOR(VID);    // 2
    SETALIGN(VID);    // 2
    SETCOLOR(TTP);    // 3
    SETALIGN(TTP);    // 3
    SETCOLOR(TM);     // 4
    SETALIGN(TM);     // 4
    SETCOLOR(STC);    // 5
    SETALIGN(STC);    // 5
    
    SETRESERVEDCOLOR(Reserved1); // 7..6
    SETALIGN(RESERVED1);

    SETCOLOR(TSCInvariant);     // 8
    SETALIGN(TSC_INVARIANT);    // 8

    SETRESERVEDCOLOR(Reserved2); // 31..9

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
