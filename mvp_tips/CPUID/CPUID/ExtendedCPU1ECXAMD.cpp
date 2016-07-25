// ExtendedCPU1ECXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU1ECXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "CurrentProcessor.h"
#include "SetAlign.h"

// CExtendedCPU1ECXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU1ECXAMD, CLeaves)

CExtendedCPU1ECXAMD::CExtendedCPU1ECXAMD()
        : CLeaves(CExtendedCPU1ECXAMD::IDD)
   {
   }

CExtendedCPU1ECXAMD::~CExtendedCPU1ECXAMD()
   {
   }

/****************************************************************************
*                     CExtendedCPU1ECXAMD::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CExtendedCPU1ECXAMD::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);

DDX_Control(pDX, IDC_CMP_LEGACY, c_CmpLegacy);
DDX_Control(pDX, IDC_CMP_LEGACY_CAPTION, x_CmpLegacy);
DDX_Control(pDX, IDC_RESERVED5, c_Reserved5);
DDX_Control(pDX, IDC_RESERVED5_CAPTION, x_Reserved5);
DDX_Control(pDX, IDC_LAHF_SAHF, c_LAHF_SAHF);
DDX_Control(pDX, IDC_LAHF_SAHF_CAPTION, x_LAHF_SAHF);
DDX_Control(pDX, IDC_RESERVED6, c_Reserved6);
DDX_Control(pDX, IDC_RESERVED6_CAPTION, x_Reserved6);
DDX_Control(pDX, IDC_SVM, c_SVM);
DDX_Control(pDX, IDC_SVM_CAPTION, x_SVM);
DDX_Control(pDX, IDC_ALT_MOV_CR8, c_AltMovCr8);
DDX_Control(pDX, IDC_ALT_MOV_CR8_CAPTION, x_AltMovCr8);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CExtendedCPU1ECXAMD, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU1ECXAMD message handlers

/****************************************************************************
*                         CExtendedCPU1ECXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU1ECXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000001, regs);

    CString s;

    ECX1x ECX;
    ECX.w = regs.ECX;

    SETWINDOWBIT(LAHF_SAHF, ECX, AMD);
    SETWINDOWBIT(CmpLegacy, ECX, AMD);
    SETWINDOWBIT(SVM, ECX, AMD);
    SETWINDOWBIT(Reserved6, ECX, AMD);
    SETWINDOWBIT(AltMovCr8, ECX, AMD);
    SETWINDOWBIT(Reserved5, ECX, AMD);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU1ECXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU1ECXAMD::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();

    // ECX
    SETCOLOR(LAHF_SAHF);                // 0
    SETALIGN(LAHF_SAHF);
    SETCOLOR(CmpLegacy);                // 1
    SETALIGN(CMP_LEGACY);
    SETCOLOR(SVM);                      // 2
    SETALIGN(SVM);
    SETRESERVEDCOLOR(Reserved6);        // 3
    SETALIGN(RESERVED6);
    SETCOLOR(AltMovCr8);                // 4
    SETALIGN(ALT_MOV_CR8);
    SETRESERVEDCOLOR(Reserved5);        // 31..1

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
