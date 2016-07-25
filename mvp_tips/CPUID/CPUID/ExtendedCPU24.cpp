// ExtendedCPU24.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU24.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"

// CExtendedCPU24 dialog

IMPLEMENT_DYNCREATE(CExtendedCPU24, CLeaves)
CExtendedCPU24::CExtendedCPU24()
        : CLeaves(CExtendedCPU24::IDD)
{
}

CExtendedCPU24::~CExtendedCPU24()
{
}

void CExtendedCPU24::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EAX, c_EAX);
DDX_Control(pDX, IDC_EBX, c_EBX);
DDX_Control(pDX, IDC_ECX, c_ECX);
DDX_Control(pDX, IDC_EDX, c_EDX);
DDX_Control(pDX, IDC_CPU_TYPENAME, c_ProcessorBrandSegment);
DDX_Control(pDX, IDC_BRAND_SEGMENT2, c_BrandSegment2);
DDX_Control(pDX, IDC_BRAND_SEGMENT3, c_BrandSegment3);
DDX_Control(pDX, IDC_BRAND_SEGMENT4, c_BrandSegment4);
DDX_Control(pDX, IDC_BRAND_NAME, c_BrandName);
}


BEGIN_MESSAGE_MAP(CExtendedCPU24, CLeaves)
END_MESSAGE_MAP()


/****************************************************************************
*                         CExtendedCPU24::GetSegment
* Inputs:
*       UINT seg: Segment to read
* Result: CString
*       Text segment
****************************************************************************/

CString CExtendedCPU24::GetSegment(UINT seg)
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(seg, &regs);

     return CString((LPCSTR)&regs.EAX, 4) +
            CString((LPCSTR)&regs.EBX, 4) +
            CString((LPCSTR)&regs.ECX, 4) +
            CString((LPCSTR)&regs.EDX, 4);
    } // CExtendedCPU24::GetSegment

/****************************************************************************
*                           CExtendedCPU24::Nullify
* Inputs:
*       CString & s: String to deal with
* Result: void
*       
* Effect: 
*       Replaces \0 bytes in the string with \\0
****************************************************************************/

void CExtendedCPU24::Nullify(CString & s)
    {
     int n = s.GetLength();
     // This handles the case of detected the \0 character
     s.GetBuffer();
     s.ReleaseBuffer();
     // Now add a \0 as a text string

     int count = n - s.GetLength();
     for(int i = 0; i < count; i++)
        s += _T("\\0");
    } // CExtendedCPU24::Nullify

/****************************************************************************
*                       CExtendedCPU24::ShowExtendedCPU
* Inputs:
*       UINT reg: ID of desired segment
* Result: void
*       
* Effect: 
*       Shows the information
****************************************************************************/

void CExtendedCPU24::ShowExtendedCPU(UINT reg)
    {
     CPUregs regs;
     GetAndReport(reg, regs);
     
     CString s;

     CStringA a((LPCSTR)&regs.EAX, 4);
     Nullify(a);
     s = _T("\"") + a + _T("\"");
     c_EAX.SetWindowText(s);

     CStringA b((LPCSTR)&regs.EBX, 4);
     Nullify(b);
     s = _T("\"") + b + _T("\"");
     c_EBX.SetWindowText(s);

     CStringA c((LPCSTR)&regs.ECX, 4);
     Nullify(c);
     s = _T("\"") + c + _T("\"");
     c_ECX.SetWindowText(s);

     CStringA d((LPCSTR)&regs.EDX, 4);
     Nullify(d);

     s = _T("\"") + d + _T("\"");
     c_EDX.SetWindowText(s);

     CStringA name = _T("\"") + a + b + c + d + _T("\"");
     c_ProcessorBrandSegment.SetWindowText(name);

     CString seg = GetSegment(0x80000002);
     c_BrandSegment2.SetWindowText(seg);

     CString BrandName = seg;

     seg = GetSegment(0x80000003);
     c_BrandSegment3.SetWindowText(seg);
     BrandName += seg;

     seg = GetSegment(0x80000004);
     c_BrandSegment4.SetWindowText(seg);
     BrandName += seg;

     c_BrandName.SetWindowText(BrandName);
    } // CExtendedCPU24::ShowExtendedCPU


/****************************************************************************
*                         CExtendedCPU24::OnSetActive
* Result: void
*       
* Effect: 
*       Called to activate page
****************************************************************************/


BOOL CExtendedCPU24::OnSetActive()
   {
    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU24::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU24::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    SetFixedFont(c_EAX);
    SetFixedFont(c_EBX);
    SetFixedFont(c_ECX);
    SetFixedFont(c_EDX);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
