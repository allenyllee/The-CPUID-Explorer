
// BasicCPU1EDX.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EDXIntel.h"
#include "CPUIDx86.h"
#include "ColorSet.h"
#include "SetWindowBit.h"
#include "SetColor.h"
#include "ReportRegs.h"
#include "CPUIDRegs.h"
#include "FormatBinary.h"
#include "CurrentProcessor.h"

// CBasicCPU1EDX dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EDXIntel, CBasicCPU1EDX)

CBasicCPU1EDXIntel::CBasicCPU1EDXIntel()
        : CBasicCPU1EDX(CBasicCPU1EDXIntel::IDD)
   {
   }

CBasicCPU1EDXIntel::~CBasicCPU1EDXIntel()
   {
   }

/****************************************************************************
*                        CBasicCPU1EDXIntel::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Maps controls to variables
****************************************************************************/

void CBasicCPU1EDXIntel::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU1EDX::DoDataExchange(pDX);
 DDX_Control(pDX, IDC_PSN, c_PSN);               // 18
 DDX_Control(pDX, IDC_DS, c_DS);                 // 21
 DDX_Control(pDX, IDC_ACPI, c_ACPI);             // 22
 DDX_Control(pDX, IDC_SS, c_SS);                 // 27
 DDX_Control(pDX, IDC_TM, c_TM);                 // 29
 DDX_Control(pDX, IDC_PBE, c_PBE);               // 31

 DDX_Control(pDX, IDC_CHILD_FRAME, c_ChildFrame);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EDXIntel, CBasicCPU1EDX)
END_MESSAGE_MAP()


// CBasicCPU1EDXIntel message handlers

/****************************************************************************
*                         CBasicCPU1EDXIntel::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CBasicCPU1EDXIntel::OnInitDialog()
    {
     CBasicCPU1EDX::OnInitDialog();
     ColorSet colors(TRUE);
     POSITION p = colors.GetFirstColorPosition();

     SETCOLORIc(PSN, 18);                   // 18
     SETCOLORIc(DS, 21);                    // 21
     SETCOLORIc(ACPI, 22);                  // 22
     SETCOLORIc(SS, 27);                    // 27
     SETCOLORIc(TM, 29);                    // 29
     SETCOLORIc(PBE, 31);                   // 31

     CreateScroller(RUNTIME_CLASS(CBasicCPU1EDXCaptionsIntel), CBasicCPU1EDXCaptionsIntel::IDD);
     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU1EDXIntel::OnSetActive
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the information by reading the CPU code
****************************************************************************/

BOOL CBasicCPU1EDXIntel::OnSetActive()
    {
     CPUregs regs;
     GetAndReport(1, regs);

     EDX1b EDX;
     EDX.w = regs.EDX;

     CString s;

     SETWINDOWBIT(PSN, EDX, Intel);                         // 18
     SETWINDOWBIT(Reserved2, EDX, Intel);                   // 20
     SETWINDOWBIT(DS, EDX, Intel);                          // 21
     SETWINDOWBIT(ACPI, EDX, Intel);                        // 22
     SETWINDOWBIT(SS, EDX, Intel);                          // 27
     SETWINDOWBIT(TM, EDX, Intel);                          // 29
     SETWINDOWBIT(PBE, EDX, Intel);                         // 31

     return CBasicCPU1EDX::OnSetActive();
    }
