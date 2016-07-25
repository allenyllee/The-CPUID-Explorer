// ExtendedCPU6Intel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU6Intel.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "FormatWithCommas.h"

// CExtendedCPU6Intel dialog

IMPLEMENT_DYNCREATE(CExtendedCPU6Intel, CLeaves)
CExtendedCPU6Intel::CExtendedCPU6Intel()
        : CLeaves(CExtendedCPU6Intel::IDD)
{
}

CExtendedCPU6Intel::~CExtendedCPU6Intel()
{
}

void CExtendedCPU6Intel::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_EDX, c_EDX);
DDX_Control(pDX, IDC_CACHE_SIZE, c_CacheSize);
DDX_Control(pDX, IDC_CACHE_SIZE_CAPTION, x_CacheSize);
DDX_Control(pDX, IDC_L2_ASSOCIATIVITY, c_Associativity);
DDX_Control(pDX, IDC_L2_ASSOCIATIVITY_CAPTION, x_Associativity);
DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);
DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);
DDX_Control(pDX, IDC_CACHE_LINE_SIZE, c_LineSize);
DDX_Control(pDX, IDC_CACHE_LINE_SIZE_CAPTION, x_LineSize);
DDX_Control(pDX, IDC_L2_DECODED, c_L2Decoded);
DDX_Control(pDX, IDC_CACHE_SIZE_VALUE, c_CacheSizeValue);
}


BEGIN_MESSAGE_MAP(CExtendedCPU6Intel, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU6Intel message handlers

/****************************************************************************
*                         CExtendedCPU6Intel::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU6Intel::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000006, regs);

    ECX6x ECX;
    ECX.w = regs.ECX;
    
    SETWINDOWBIT(LineSize, ECX, Intel);
    SETWINDOWBIT(Reserved1, ECX, Intel);
    SETWINDOWHEX(Associativity, ECX, Intel, 2);
    SETWINDOWBIT(CacheSize, ECX, Intel);

    CString s;
    //    s.Format(_T("%d"), ECX.bits.CacheSize * 1024);
    s = FormatWithCommas(ECX.Intel.CacheSize * 1024);
    c_CacheSizeValue.SetWindowText(s);
    
    s.LoadString(IDS_L2_ASSOCIATIVITY_00H + ECX.Intel.Associativity);
    if(s.IsEmpty())
       c_L2Decoded.ShowWindow(SW_HIDE);
    else
       { /* has value */
        c_L2Decoded.SetWindowText(s);
        c_L2Decoded.ShowWindow(SW_SHOW);
       } /* has value */
    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU6Intel::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU6Intel::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    SETCOLOR(LineSize);                 // 7..0
    SETRESERVEDCOLOR(Reserved1);        // 11..8
    SETCOLOR(Associativity);            // 15..12
    SETCOLOR(CacheSize);                // 31..16

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
