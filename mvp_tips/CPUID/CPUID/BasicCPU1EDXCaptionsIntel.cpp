// BasicCPU1EDXCaptions.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EDXCaptionsIntel.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "SetAlign.h"

// CBasicCPU1EDXCaptions dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EDXCaptionsIntel, CBasicCPU1EDXCaptions)

CBasicCPU1EDXCaptionsIntel::CBasicCPU1EDXCaptionsIntel(CWnd* pParent /*=NULL*/)
        : CBasicCPU1EDXCaptions(CBasicCPU1EDXCaptionsIntel::IDD, pParent)
{
}

CBasicCPU1EDXCaptionsIntel::~CBasicCPU1EDXCaptionsIntel()
{
}

/****************************************************************************
*                    CBasicCPU1EDXCaptionsIntel::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CBasicCPU1EDXCaptionsIntel::DoDataExchange(CDataExchange* pDX)
{
        CBasicCPU1EDXCaptions::DoDataExchange(pDX);
        DDX_Control(pDX, IDC_PSN_CAPTION, x_PSN);       // 18
        DDX_Control(pDX, IDC_PSN, c_PSN);               // 18
        DDX_Control(pDX, IDC_DS_CAPTION, x_DS);         // 21
        DDX_Control(pDX, IDC_DS, c_DS);                 // 21
        DDX_Control(pDX, IDC_ACPI_CAPTION, x_ACPI);     // 22
        DDX_Control(pDX, IDC_ACPI, c_ACPI);             // 22
        DDX_Control(pDX, IDC_SS_CAPTION, x_SS);         // 27
        DDX_Control(pDX, IDC_SS, c_SS);                 // 27
        DDX_Control(pDX, IDC_TM_CAPTION, x_TM);         // 29
        DDX_Control(pDX, IDC_TM, c_TM);                 // 29
        DDX_Control(pDX, IDC_PBE_CAPTION, x_PBE);       // 31
        DDX_Control(pDX, IDC_PBE, c_PBE);               // 31
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EDXCaptionsIntel, CBasicCPU1EDXCaptions)
END_MESSAGE_MAP()


// CBasicCPU1EDXCaptionsIntel message handlers

/****************************************************************************
*                     CBasicCPU1EDXCaptionsIntel::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Intiailizes the dialog
****************************************************************************/

BOOL CBasicCPU1EDXCaptionsIntel::OnInitDialog()
    {
     CBasicCPU1EDXCaptions::OnInitDialog();

     ColorSet colors(TRUE);
     POSITION p = colors.GetFirstColorPosition();

     // FPU                // 0: superclass
     // VME                // 1: superclass
     // DE                 // 2: superclass
     // PSE                // 3: superclass
     // TSC                // 4: superclass
     // MSR                // 5: superclass
     // PAE                // 6: superclass
     // MCE                // 7: superclass
     // CX8                // 8: superclass
     // APIC               // 9: superclass
     // Reserved1          // 10: superclass
     // SEP                // 11: superclass
     // MTRR               // 12: superclass
     // PGE                // 13: superclass
     // MCA                // 14: superclass
     // CMOV               // 15: superclass
     // PAT                // 16: superclass
     // PSE36              // 17: superclass
     
     SETCOLORI(PSN, 18);   // 18
     SETALIGN(PSN);        // 18
     c_PSN.SetWindowText(_T("")); // 18
     
     // CFLSH              // 19: superclass
     // Reserved2          // 20: superclass

     SETCOLORI(DS, 21);    // 21
     SETALIGN(DS);         // 21
     c_DS.SetWindowText(_T("")); // 21

     SETCOLORI(ACPI, 22);  // 22
     SETALIGN(ACPI);       // 22
     c_ACPI.SetWindowText(_T("")); // 22

     // MMX                // 23: superclass
     // FXSR               // 24: superclass
     // SSE                // 25: superclass
     // SSE2               // 26: superclass

     SETCOLORI(SS, 27);    // 27
     SETALIGN(SS);         // 27
     c_SS.SetWindowText(_T("")); // 27

     // HTT                // 28: superclass

     SETCOLORI(TM, 29);    // 29
     SETALIGN(TM);         // 29
     c_TM.SetWindowText(_T("")); // 29

     // Reserved3          // 30: superclass
     
     SETCOLORI(PBE, 31);   // 31
     SETALIGN(PBE);        // 31
     c_PBE.SetWindowText(_T("")); //

     return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
    }
