// BasicCPU1EDXCaptions.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EDXCaptions.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "msg.h"
#include "QueryCoordinates.h"
#include "SetAlign.h"

// CBasicCPU1EDXCaptions dialog

DECLARE_MESSAGE(UWM_QUERY_COORDINATES)

IMPLEMENT_DYNCREATE(CBasicCPU1EDXCaptions, CScrollableCaptions)

CBasicCPU1EDXCaptions::CBasicCPU1EDXCaptions(UINT idd, CWnd* pParent /*=NULL*/)
        : CScrollableCaptions(idd, pParent)
{
}

CBasicCPU1EDXCaptions::~CBasicCPU1EDXCaptions()
{
}

/****************************************************************************
*                    CBasicCPU1EDXCaptions::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CBasicCPU1EDXCaptions::DoDataExchange(CDataExchange* pDX)
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
        DDX_Control(pDX, IDC_CX8_CAPTION, x_CX8);       // 8
        DDX_Control(pDX, IDC_CX8, c_CX8);               // 8
        DDX_Control(pDX, IDC_APIC_CAPTION, x_APIC);     // 9
        DDX_Control(pDX, IDC_APIC, c_APIC);             // 9
        DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);   // 10
        DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);   // 10
        DDX_Control(pDX, IDC_SEP_CAPTION, x_SEP);       // 11
        DDX_Control(pDX, IDC_SEP, c_SEP);               // 11
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
        DDX_Control(pDX, IDC_CFLSH_CAPTION, x_CFLSH);   // 19
        DDX_Control(pDX, IDC_CFLSH, c_CFLSH);           // 19
        DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);   // 20
        DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);   // 20
        DDX_Control(pDX, IDC_MMX_CAPTION, x_MMX);       // 23
        DDX_Control(pDX, IDC_MMX, c_MMX);               // 23
        DDX_Control(pDX, IDC_FXSR_CAPTION, x_FXSR);     // 24
        DDX_Control(pDX, IDC_FXSR, c_FXSR);             // 24
        DDX_Control(pDX, IDC_SSE_CAPTION, x_SSE);       // 25
        DDX_Control(pDX, IDC_SSE, c_SSE);               // 25
        DDX_Control(pDX, IDC_SSE2_CAPTION, x_SSE2);     // 26
        DDX_Control(pDX, IDC_SSE2, c_SSE2);             // 26
        DDX_Control(pDX, IDC_HTT_CAPTION, x_HTT);       // 28
        DDX_Control(pDX, IDC_HTT, c_HTT);               // 28
        DDX_Control(pDX, IDC_RESERVED3_CAPTION, x_Reserved3);   // 30
        DDX_Control(pDX, IDC_RESERVED3, c_Reserved3);   // 30
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EDXCaptions, CScrollableCaptions)
END_MESSAGE_MAP()


// CBasicCPU1EDXCaptions message handlers

/****************************************************************************
*                     CBasicCPU1EDXCaptions::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Intiailizes the dialog
****************************************************************************/

BOOL CBasicCPU1EDXCaptions::OnInitDialog()
    {
     CScrollableCaptions::OnInitDialog();

     ColorSet colors(TRUE);
     POSITION p = colors.GetFirstColorPosition();

     SETCOLORI(FPU, 0);    // 0
     SETALIGN(FPU);        // 0
     c_FPU.SetWindowText(_T("")); // 0
     
     SETCOLORI(VME, 1);    // 1
     SETALIGN(VME);        // 1
     c_VME.SetWindowText(_T("")); // 1
     
     SETCOLORI(DE, 2);     // 2
     SETALIGN(DE);         // 2
     c_DE.SetWindowText(_T("")); // 2
     
     SETCOLORI(PSE, 3);    // 3
     SETALIGN(PSE);        // 3
     c_PSE.SetWindowText(_T("")); // 3

     SETCOLORI(TSC, 4);    // 4
     SETALIGN(TSC);        // 4
     c_TSC.SetWindowText(_T("")); // 4

     SETCOLORI(MSR, 5);    // 5
     SETALIGN(MSR);        // 5
     c_MSR.SetWindowText(_T("")); // 5

     SETCOLORI(PAE, 6);    // 6
     SETALIGN(PAE);        // 6
     c_PAE.SetWindowText(_T("")); // 6

     SETCOLORI(MCE, 7);    // 7
     SETALIGN(MCE);        // 7
     c_MCE.SetWindowText(_T("")); // 7

     SETCOLORI(CX8, 8);    // 8
     SETALIGN(CX8);        // 8
     c_CX8.SetWindowText(_T("")); // 8

     SETCOLORI(APIC, 9);   // 9
     SETALIGN(APIC);       // 9
     c_APIC.SetWindowText(_T("")); // 9

     SETRESERVEDCOLOR(Reserved1); // 10
     SETALIGN(RESERVED1);  // 10
     c_Reserved1.SetWindowText(_T("")); // 10

     SETCOLORI(SEP, 11);   // 11
     SETALIGN(SEP);        // 11
     c_SEP.SetWindowText(_T("")); // 11
     
     SETCOLORI(MTRR, 12);  // 12
     SETALIGN(MTRR);       // 12
     c_MTRR.SetWindowText(_T("")); // 12

     SETCOLORI(PGE, 13);   // 13
     SETALIGN(PGE);        // 13
     c_PGE.SetWindowText(_T("")); // 13

     SETCOLORI(MCA, 14);   // 14
     SETALIGN(MCA);        // 14
     c_MCA.SetWindowText(_T("")); // 14

     SETCOLORI(CMOV, 15);  // 15
     SETALIGN(CMOV);       // 15
     c_CMOV.SetWindowText(_T("")); // 15

     SETCOLORI(PAT, 16);   // 16
     SETALIGN(PAT);        // 16
     c_PAT.SetWindowText(_T("")); // 16

     SETCOLORI(PSE36, 17); // 17
     SETALIGN(PSE36);      // 17
     c_PSE36.SetWindowText(_T("")); // 17
                           // 18: subclass
     
     SETCOLORI(CFLSH, 19); // 19
     SETALIGN(CFLSH);      // 19
     c_CFLSH.SetWindowText(_T("")); // 19

     SETRESERVEDCOLOR(Reserved2); // 20
     SETALIGN(RESERVED2);  // 20
     c_Reserved2.SetWindowText(_T("")); // 20

                           // 21: subclass
                           // 22: subclass
     
     SETCOLORI(MMX, 23);   // 23
     SETALIGN(MMX);        // 23
     c_MMX.SetWindowText(_T("")); // 23 

     SETCOLORI(FXSR, 24);  // 24
     SETALIGN(FXSR);       // 24
     c_FXSR.SetWindowText(_T("")); // 24

     SETCOLORI(SSE, 25);   // 25
     SETALIGN(SSE);        // 25
     c_SSE.SetWindowText(_T("")); // 25

     SETCOLORI(SSE2, 26);  // 26
     SETALIGN(SSE2);       // 26
     c_SSE2.SetWindowText(_T("")); // 26
                           // 27: subclass
     
     SETCOLORI(HTT, 28);   // 28
     SETALIGN(HTT);        // 28
     c_HTT.SetWindowText(_T("")); // 28

                           // 29: subclass
     
     SETRESERVEDCOLOR(Reserved3); // 30
     SETALIGN(RESERVED3);  // 30
     c_Reserved3.SetWindowText(_T("")); // 30

                           // 31: subclass
     
     SavePos();  // save the newly-computed positions
     
     return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
    }
