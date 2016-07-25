// BasicCPU1EDXCaptions.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EDXCaptionsAMD.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "SetAlign.h"

// CBasicCPU1EDXCaptions dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EDXCaptionsAMD, CBasicCPU1EDXCaptions)

CBasicCPU1EDXCaptionsAMD::CBasicCPU1EDXCaptionsAMD(CWnd* pParent /*=NULL*/)
        : CBasicCPU1EDXCaptions(CBasicCPU1EDXCaptionsAMD::IDD, pParent)
{
}

CBasicCPU1EDXCaptionsAMD::~CBasicCPU1EDXCaptionsAMD()
{
}

/****************************************************************************
*                    CBasicCPU1EDXCaptionsAMD::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CBasicCPU1EDXCaptionsAMD::DoDataExchange(CDataExchange* pDX)
{
        CBasicCPU1EDXCaptions::DoDataExchange(pDX);
        DDX_Control(pDX, IDC_RESERVED4, c_Reserved4);
        DDX_Control(pDX, IDC_RESERVED4_CAPTION, x_Reserved4);
        DDX_Control(pDX, IDC_RESERVED5, c_Reserved5);
        DDX_Control(pDX, IDC_RESERVED5_CAPTION, x_Reserved5);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EDXCaptionsAMD, CBasicCPU1EDXCaptions)
END_MESSAGE_MAP()


// CBasicCPU1EDXCaptionsAMD message handlers


/****************************************************************************
*                     CBasicCPU1EDXCaptionsAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Intiailizes the dialog
****************************************************************************/

BOOL CBasicCPU1EDXCaptionsAMD::OnInitDialog()
    {
     CBasicCPU1EDXCaptions::OnInitDialog();

     // FPU                       // 0: superclass
     // VME                       // 1: superclass
     // DE                        // 2: superclass
     // PSE                       // 3: superclass
     // TSC                       // 4: superclass
     // MSR                       // 5: superclass
     // PAE                       // 6: superclass
     // MCE                       // 7: superclass
     // CX8                       // 8: superclass
     // APIC                      // 9: superclass
     // Reserved1                 // 10: superclass
     // SEP                       // 11: superclass
     // MTRR                      // 12: superclass
     // PGE                       // 13: superclass
     // MCA                       // 14: superclass
     // CMOV                      // 15: superclass
     // PAT                       // 16: superclass
     // PSE36                     // 17: superclass
     SETRESERVEDCOLOR(Reserved5); // 18 
     SETALIGN(RESERVED5);         // 18
     c_Reserved5.SetWindowText(_T("")); // 18
     // CFLSH                     // 19: superclass
     // Reserved2                 // 20..22 superclass
     // MMX                       // 23: superclass
     // FXSR                      // 24: superclass
     // SSE                       // 25: superclass
     // SSE2                      // 26: superclass
     SETRESERVEDCOLOR(Reserved4); // 27
     SETALIGN(RESERVED4);         // 27
     c_Reserved4.SetWindowText(_T("")); // 27
     // HTT                       // 28: superclass
     // Reserved3                 // 29..31
     return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
    }
