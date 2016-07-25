#include ".\basiccpu1eax.h"

// BasicCPU1EAX.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EAX.h"
#include "FormatBinary.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CPUIDRegs.h"
#include "SetColor.h"

// CBasicCPU1EAX dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EAX, CLeaves)
CBasicCPU1EAX::CBasicCPU1EAX(UINT idd)
        : CLeaves(idd)
{
}

CBasicCPU1EAX::~CBasicCPU1EAX()
{
}

void CBasicCPU1EAX::DoDataExchange(CDataExchange* pDX)
{
 CLeaves::DoDataExchange(pDX);
 DDX_Control(pDX, IDC_RESERVED_32_28, c_Reserved_31_28);
 DDX_Control(pDX, IDC_RESERVED_32_28_CAPTION, x_Reserved_31_28);
 DDX_Control(pDX, IDC_EXTENDED_CPU_ID, c_ExtendedFamilyID);
 DDX_Control(pDX, IDC_EXTENDED_CPU_ID_CAPTION, x_ExtendedFamilyID);
 DDX_Control(pDX, IDC_EXTENDED_MODEL_ID, c_ExtendedModelID);
 DDX_Control(pDX, IDC_EXTENDED_MODEL_ID_CAPTION, x_ExtendedModelID);
 DDX_Control(pDX, IDC_FAMILY_ID, c_FamilyID);
 DDX_Control(pDX, IDC_FAMILY_ID_CAPTION, x_FamilyID);
 DDX_Control(pDX, IDC_MODEL, c_Model);
 DDX_Control(pDX, IDC_MODEL_CAPTION, x_Model);
 DDX_Control(pDX, IDC_STEPPING_ID, c_SteppingID);
 DDX_Control(pDX, IDC_STEPPING_ID_CAPTION, x_SteppingID);
 DDX_Control(pDX, IDC_EXTENDED_FAMILY_1, c_ExtendedFamily1Line);
 DDX_Control(pDX, IDC_EXTENDED_FAMILY_2, c_ExtendedFamily2Line);
 DDX_Control(pDX, IDC_EXTENDED_FAMILY_3, c_ExtendedFamily3Line);
 DDX_Control(pDX, IDC_COMPUTED_FAMILY_ID, c_ComputedFamilyID);
 DDX_Control(pDX, IDC_COMPUTED_FAMILY_ID_CAPTION, x_ComputedFamilyID);
 DDX_Control(pDX, IDC_COMPUTED_MODEL_1, c_ComputedModel1Line);
 DDX_Control(pDX, IDC_COMPUTED_MODEL_2, c_ComputedModel2Line);
 DDX_Control(pDX, IDC_COMPUTED_MODEL, c_ComputedModel);
 DDX_Control(pDX, IDC_COMPUTED_MODEL_CAPTION, x_ComputedModel);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EAX, CLeaves)
END_MESSAGE_MAP()


/****************************************************************************
*                       CBasicCPU1EAX::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the controls unique to the AMD display
****************************************************************************/

BOOL CBasicCPU1EAX::OnInitDialog()
    {
     CLeaves::OnInitDialog();

     SETRESERVEDCOLOR(Reserved_31_28);

     c_ExtendedFamilyID.SetBkColor(RGB(255,255,0));
     x_ExtendedFamilyID.SetBkColor(c_ExtendedFamilyID.GetBkColor());

     c_ExtendedModelID.SetBkColor(RGB(255,128,255));
     x_ExtendedModelID.SetBkColor(c_ExtendedModelID.GetBkColor());

     c_FamilyID.SetBkColor(c_ExtendedFamilyID.GetBkColor());
     x_FamilyID.SetBkColor(c_FamilyID.GetBkColor());

     c_Model.SetBkColor(c_ExtendedModelID.GetBkColor());
     x_Model.SetBkColor(c_Model.GetBkColor());

     c_SteppingID.SetBkColor(RGB(255,179,102));
     x_SteppingID.SetBkColor(c_SteppingID.GetBkColor());
     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                         CBasicCPU1EAX::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports status
****************************************************************************/

BOOL CBasicCPU1EAX::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(1, regs);

    EAX1b EAX;
    EAX.w = regs.EAX;
    CString s;
    s= FormatBinary(EAX.Intel.Reserved, 4);
    c_Reserved_31_28.SetWindowText(s+_T("B"));

    s.Format(_T("%XH"), EAX.Intel.ExtendedFamily);
    c_ExtendedFamilyID.SetWindowText(s);

    //****************************************************************
    // Special computation: Extended family
    //****************************************************************
    if(EAX.Intel.FamilyID == 0x0F)
       { /* extended family ID */
        UINT ComputedFamily = EAX.Intel.FamilyID + EAX.Intel.ExtendedFamily;
        
        s.Format(_T("%04XH"), ComputedFamily);
        c_ComputedFamilyID.SetWindowText(s);

        c_ComputedFamilyID.ShowWindow(SW_SHOW);
        x_ComputedFamilyID.ShowWindow(SW_SHOW);
        c_ExtendedFamily1Line.ShowWindow(SW_SHOW);
        c_ExtendedFamily2Line.ShowWindow(SW_SHOW);
        c_ExtendedFamily3Line.ShowWindow(SW_SHOW);
       } /* extended family ID */
    else
       { /* not extended */
        c_ComputedFamilyID.ShowWindow(SW_HIDE);
        x_ComputedFamilyID.ShowWindow(SW_HIDE);
        c_ExtendedFamily1Line.ShowWindow(SW_HIDE);
        c_ExtendedFamily2Line.ShowWindow(SW_HIDE);
        c_ExtendedFamily3Line.ShowWindow(SW_HIDE);
       } /* not extended */

    //****************************************************************

    s.Format(_T("%XH"), EAX.Intel.ExtendedModel);
    c_ExtendedModelID.SetWindowText(s);

    //****************************************************************
    // Special computation: Computed model
    //****************************************************************

    if(EAX.Intel.FamilyID == 0x06 || EAX.Intel.FamilyID == 0x0F)
       { /* extended model */
        UINT ComputedModel = EAX.Intel.ModelID + (EAX.Intel.ExtendedModel << 4);

        s.Format(_T("%04XH"), ComputedModel);
        c_ComputedModel.SetWindowText(s);

        c_ComputedModel1Line.ShowWindow(SW_SHOW);
        c_ComputedModel2Line.ShowWindow(SW_SHOW);
        c_ComputedModel.ShowWindow(SW_SHOW);
        x_ComputedModel.ShowWindow(SW_SHOW);
       } /* extended model */
    else
       { /* not extended model */
        c_ComputedModel1Line.ShowWindow(SW_HIDE);
        c_ComputedModel2Line.ShowWindow(SW_HIDE);
        c_ComputedModel.ShowWindow(SW_HIDE);
        x_ComputedModel.ShowWindow(SW_HIDE);
       } /* not extended model */

    s.Format(_T("%XH"), EAX.Intel.FamilyID);
    c_FamilyID.SetWindowText(s);

    s.Format(_T("%XH"), EAX.Intel.ModelID);
    c_Model.SetWindowText(s);

    s.Format(_T("%d"), EAX.Intel.SteppingID);
    c_SteppingID.SetWindowText(s);
    
    return CLeaves::OnSetActive();
   }

