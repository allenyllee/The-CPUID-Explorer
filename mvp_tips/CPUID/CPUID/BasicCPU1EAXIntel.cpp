// BasicCPU1EAXIntel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU1EAXIntel.h"
#include "FormatBinary.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "CPUIDRegs.h"
#include "SetColor.h"

// CBasicCPU1EAX dialog

IMPLEMENT_DYNCREATE(CBasicCPU1EAXIntel, CBasicCPU1EAX)

CBasicCPU1EAXIntel::CBasicCPU1EAXIntel()
        : CBasicCPU1EAX(CBasicCPU1EAXIntel::IDD)
{
}

CBasicCPU1EAXIntel::~CBasicCPU1EAXIntel()
{
}

void CBasicCPU1EAXIntel::DoDataExchange(CDataExchange* pDX)
{
CBasicCPU1EAX::DoDataExchange(pDX);
DDX_Control(pDX, IDC_RESERVED_15_14, c_Reserved_15_14);
DDX_Control(pDX, IDC_RESERVED_15_14_CAPTION, x_Reserved_15_14);
DDX_Control(pDX, IDC_PROCESSOR_TYPE, c_ProcessorType);
DDX_Control(pDX, IDC_PROCESSOR_TYPE_CAPTION, x_ProcessorType);
DDX_Control(pDX, IDC_PROCESSOR_TYPE_STRING, c_ProcessorTypeString);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU1EAXIntel, CBasicCPU1EAX)
END_MESSAGE_MAP()


// CBasicCPU1EAX message handlers

/****************************************************************************
*                       CBasicCPU1EAXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the controls unique to the AMD display
****************************************************************************/

BOOL CBasicCPU1EAXIntel::OnInitDialog()
    {
     CBasicCPU1EAX::OnInitDialog();

     SETRESERVEDCOLOR(Reserved_15_14);

     c_ProcessorType.SetBkColor(RGB(128,255,0));
     x_ProcessorType.SetBkColor(c_ProcessorType.GetBkColor());

     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                      CBasicCPU1EAXIntel::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports status
****************************************************************************/

BOOL CBasicCPU1EAXIntel::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(1, regs);

    EAX1b EAX;
    EAX.w = regs.EAX;

    CString s;
    s.Format(_T("%XH"), EAX.Intel.ExtendedModel);
    c_ExtendedModelID.SetWindowText(s);

    s = FormatBinary(EAX.Intel.Reserved2, 2);
    c_Reserved_15_14.SetWindowText(s + _T("B"));

    s = FormatBinary(EAX.Intel.ProcessorType, 2);
    c_ProcessorType.SetWindowText(s + _T("B"));

    s.LoadString(IDS_PROCESSOR_00B + EAX.Intel.ProcessorType);
    c_ProcessorTypeString.SetWindowText(s);

    return CBasicCPU1EAX::OnSetActive();
   }

