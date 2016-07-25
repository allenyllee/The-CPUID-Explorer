// ExtendedCPU1EDXCaptions.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU1EDXCaptionsAMD.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "SetAlign.h"

// CExtendedCPU1EDXCaptions dialog

IMPLEMENT_DYNCREATE(CExtendedCPU1EDXCaptionsAMD, CScrollableCaptions)

CExtendedCPU1EDXCaptionsAMD::CExtendedCPU1EDXCaptionsAMD(CWnd* pParent /*=NULL*/)
        : CScrollableCaptions(CExtendedCPU1EDXCaptionsAMD::IDD, pParent)
{
}

CExtendedCPU1EDXCaptionsAMD::~CExtendedCPU1EDXCaptionsAMD()
{
}

/****************************************************************************
*                    CExtendedCPU1EDXCaptionsAMD::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CExtendedCPU1EDXCaptionsAMD::DoDataExchange(CDataExchange* pDX)
{
        CScrollableCaptions::DoDataExchange(pDX);
        DDX_Control(pDX, IDC_FPU_CAPTION, x_FPU);       // 0
        DDX_Control(pDX, IDC_FPU, c_FPU);               // 0
        DDX_Control(pDX, IDC_VME_CAPTION, x_VME);       // 1
        DDX_Control(pDX, IDC_VME, c_VME);               // 1
        DDX_Control(pDX, IDC_DE_CAPTION, x_DE);         // 2
        DDX_Control(pDX, IDC_DE, c_DE);                 // 2
        DDX_Control(pDX, IDC_PSE_CAPTION, x_PSE);       // 3
        DDX_Control(pDX, IDC_PSE, c_PSE);               // 3
        DDX_Control(pDX, IDC_TSC_CAPTION, x_TSC);       // 4
        DDX_Control(pDX, IDC_TSC, c_TSC);               // 4
        DDX_Control(pDX, IDC_MSR_CAPTION, x_MSR);       // 5
        DDX_Control(pDX, IDC_MSR, c_MSR);               // 5
        DDX_Control(pDX, IDC_PAE_CAPTION, x_PAE);       // 6
        DDX_Control(pDX, IDC_PAE, c_PAE);               // 6
        DDX_Control(pDX, IDC_MCE_CAPTION, x_MCE);       // 7
        DDX_Control(pDX, IDC_MCE, c_MCE);               // 7
        DDX_Control(pDX, IDC_CX8_CAPTION, x_CMPXCHG8B); // 8
        DDX_Control(pDX, IDC_CX8, c_CMPXCHG8B);         // 8
        DDX_Control(pDX, IDC_APIC_CAPTION, x_APIC);     // 9
        DDX_Control(pDX, IDC_APIC, c_APIC);             // 9
        DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);   // 10
        DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);   // 10
        DDX_Control(pDX, IDC_SYSCALL_SYSRET_CAPTION, x_SYSCALL_SYSRET);    // 11
        DDX_Control(pDX, IDC_SYSCALL_SYSRET, c_SYSCALL_SYSRET);            // 11
        DDX_Control(pDX, IDC_MTRR_CAPTION, x_MTRR);     // 12
        DDX_Control(pDX, IDC_MTRR, c_MTRR);             // 12
        DDX_Control(pDX, IDC_PGE_CAPTION, x_PGE);       // 13
        DDX_Control(pDX, IDC_PGE, c_PGE);               // 13
        DDX_Control(pDX, IDC_MCA_CAPTION, x_MCA);       // 14
        DDX_Control(pDX, IDC_MCA, c_MCA);               // 14
        DDX_Control(pDX, IDC_CMOV_CAPTION, x_CMOV);     // 15
        DDX_Control(pDX, IDC_CMOV, c_CMOV);             // 15
        DDX_Control(pDX, IDC_PAT_CAPTION, x_PAT);       // 16
        DDX_Control(pDX, IDC_PAT, c_PAT);               // 16
        DDX_Control(pDX, IDC_PSE36_CAPTION, x_PSE36);   // 17
        DDX_Control(pDX, IDC_PSE36, c_PSE36);           // 17
        DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);       // 19..18
        DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);               // 19..18
        DDX_Control(pDX, IDC_EXECUTE_DISABLE_CAPTION, x_ExecuteDisable);   // 20
        DDX_Control(pDX, IDC_EXECUTE_DISABLE, c_ExecuteDisable);           // 20
        DDX_Control(pDX, IDC_RESERVED3_CAPTION, x_Reserved3);     // 21
        DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);             // 21
        DDX_Control(pDX, IDC_MMX_EXT_CAPTION, x_MMXExt);// 22
        DDX_Control(pDX, IDC_MMX_EXT, c_MMXExt);        // 22
        DDX_Control(pDX, IDC_MMX_CAPTION, x_MMX);       // 23
        DDX_Control(pDX, IDC_MMX, c_MMX);               // 23
        DDX_Control(pDX, IDC_FXSR_CAPTION, x_FXSR);     // 24
        DDX_Control(pDX, IDC_FXSR, c_FXSR);             // 24
        DDX_Control(pDX, IDC_FFXSR_CAPTION, x_FFXSR);   // 25
        DDX_Control(pDX, IDC_FFXSR, c_FFXSR);           // 25
        DDX_Control(pDX, IDC_RESERVED4_CAPTION, x_Reserved4);     // 26
        DDX_Control(pDX, IDC_RESERVED4, c_Reserved4);             // 26
        DDX_Control(pDX, IDC_RDTSCP_CAPTION, x_RDTSCP);           // 27
        DDX_Control(pDX, IDC_RDTSCP, c_RDTSCP);                   // 27
        DDX_Control(pDX, IDC_RESERVED5_CAPTION, x_Reserved5);     // 28
        DDX_Control(pDX, IDC_RESERVED5, c_Reserved5);             // 28
        DDX_Control(pDX, IDC_LM_CAPTION, x_LM);         // 29
        DDX_Control(pDX, IDC_LM, c_LM);                 // 29
        DDX_Control(pDX, IDC_3DNOW_EXT_CAPTION, x_ThreeDNowExt);   // 30
        DDX_Control(pDX, IDC_3DNOW_EXT, c_ThreeDNowExt);           // 30
        DDX_Control(pDX, IDC_3DNOW_CAPTION, x_ThreeDNow);          // 31
        DDX_Control(pDX, IDC_3DNOW, c_ThreeDNow);                  // 31
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CExtendedCPU1EDXCaptionsAMD, CScrollableCaptions)
END_MESSAGE_MAP()


// CExtendedCPU1EDXCaptionsAMD message handlers

/****************************************************************************
*                     CExtendedCPU1EDXCaptionsAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Intiailizes the dialog
****************************************************************************/

BOOL CExtendedCPU1EDXCaptionsAMD::OnInitDialog()
    {
     CScrollableCaptions::OnInitDialog();

     ColorSet colors(TRUE);
     POSITION p = colors.GetFirstColorPosition();

     SETCOLORI(FPU, 0);                 // 0
     c_FPU.SetWindowText(_T(""));
     SETALIGN(FPU);

     SETCOLORI(VME, 1);                 // 1
     c_VME.SetWindowText(_T(""));
     SETALIGN(VME);

     SETCOLORI(DE,  2);                 // 2
     c_DE.SetWindowText(_T(""));
     SETALIGN(DE);

     SETCOLORI(PSE, 3);                 // 3
     c_PSE.SetWindowText(_T(""));
     SETALIGN(PSE);

     SETCOLORI(TSC, 4);                 // 4
     c_TSC.SetWindowText(_T(""));
     SETALIGN(TSC);

     SETCOLORI(MSR, 5);                 // 5
     c_MSR.SetWindowText(_T(""));
     SETALIGN(MSR);

     SETCOLORI(PAE, 6);                 // 6
     c_PAE.SetWindowText(_T(""));
     SETALIGN(PAE);

     SETCOLORI(MCE, 7);                 // 7
     c_MCE.SetWindowText(_T(""));
     SETALIGN(MCE);

     SETCOLORI(CMPXCHG8B, 8);           // 8
     c_CMPXCHG8B.SetWindowText(_T(""));
     SETALIGN(CX8);

     SETCOLORI(APIC, 9);                // 9
     c_APIC.SetWindowText(_T(""));
     SETALIGN(APIC);

     SETRESERVEDCOLOR(Reserved1);       // 10
     c_Reserved1.SetWindowText(_T(""));
     SETALIGN(RESERVED1);

     SETCOLORI(SYSCALL_SYSRET, 11);     // 11
     c_SYSCALL_SYSRET.SetWindowText(_T(""));
     SETALIGN(SYSCALL_SYSRET);

     SETCOLORI(MTRR, 12);               // 12
     c_MTRR.SetWindowText(_T(""));
     SETALIGN(MTRR);

     SETCOLORI(PGE, 13);                // 13
     c_PGE.SetWindowText(_T(""));
     SETALIGN(PGE);

     SETCOLORI(MCA, 14);                // 14
     c_MCA.SetWindowText(_T(""));
     SETALIGN(MCA);

     SETCOLORI(CMOV, 15);               // 15
     c_CMOV.SetWindowText(_T(""));
     SETALIGN(CMOV);

     SETCOLORI(PAT, 16);                // 16
     c_PAT.SetWindowText(_T(""));
     SETALIGN(PAT);

     SETCOLORI(PSE36, 17);              // 17
     c_PSE36.SetWindowText(_T(""));
     SETALIGN(PSE36);

     SETRESERVEDCOLOR(Reserved2);       // 19..18
     c_Reserved2.SetWindowText(_T(""));
     SETALIGN(RESERVED2);

     SETCOLORI(ExecuteDisable, 20);     // 20
     c_ExecuteDisable.SetWindowText(_T(""));
     SETALIGN(EXECUTE_DISABLE);

     SETRESERVEDCOLOR(Reserved3);       // 21
     c_Reserved3.SetWindowText(_T(""));
     SETALIGN(RESERVED3);

     SETCOLORI(MMXExt, 22);             // 22
     c_MMXExt.SetWindowText(_T(""));
     SETALIGN(MMX_EXT);

     SETCOLORI(MMX, 23);                // 23
     c_MMX.SetWindowText(_T(""));
     SETALIGN(MMX);

     SETCOLORI(FXSR, 24);               // 24
     c_FXSR.SetWindowText(_T(""));
     SETALIGN(FXSR);

     SETCOLORI(FFXSR, 25);              // 25
     c_FFXSR.SetWindowText(_T(""));
     SETALIGN(FFXSR);

     SETRESERVEDCOLOR(Reserved4);       // 26
     c_Reserved4.SetWindowText(_T(""));
     SETALIGN(RESERVED4);

     SETCOLORI(RDTSCP, 27);             // 27
     c_RDTSCP.SetWindowText(_T(""));
     SETALIGN(RDTSCP);

     SETRESERVEDCOLOR(Reserved5);       // 28
     c_Reserved5.SetWindowText(_T(""));
     SETALIGN(RESERVED5);

     SETCOLORI(LM, 29);                 // 29
     c_LM.SetWindowText(_T(""));
     SETALIGN(LM);

     SETCOLORI(ThreeDNowExt, 30);       // 30
     c_ThreeDNowExt.SetWindowText(_T(""));
     SETALIGN(3DNOW_EXT);

     SETCOLORI(ThreeDNow, 31);          // 31
     c_ThreeDNow.SetWindowText(_T(""));
     SETALIGN(3DNOW);

     SavePos();  // Save the newly-computed caption positions

     return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
    }
