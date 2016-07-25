// ExtendedCPU6ECXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU6ECXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "FormatWithCommas.h"
#include "FormatMagnitude.h"

// CExtendedCPU6ECXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU6ECXAMD, CLeaves)
CExtendedCPU6ECXAMD::CExtendedCPU6ECXAMD()
: CLeaves(CExtendedCPU6ECXAMD::IDD)
{
}

CExtendedCPU6ECXAMD::~CExtendedCPU6ECXAMD()
{
}

void CExtendedCPU6ECXAMD::DoDataExchange(CDataExchange* pDX)
   {
    CLeaves::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_31_16, c_31_16);
    DDX_Control(pDX, IDC_31_16_CAPTION, x_31_16);
    DDX_Control(pDX, IDC_31_16_EXPLANATION, e_31_16);
    DDX_Control(pDX, IDC_15_12, c_15_12);
    DDX_Control(pDX, IDC_15_12_CAPTION, x_15_12);
    DDX_Control(pDX, IDC_15_12_EXPLANATION, e_15_12);
    DDX_Control(pDX, IDC_11_8, c_11_8);
    DDX_Control(pDX, IDC_11_8_CAPTION, x_11_8);
    DDX_Control(pDX, IDC_11_8_EXPLANATION, e_11_8);
    DDX_Control(pDX, IDC_7_0, c_7_0);
    DDX_Control(pDX, IDC_7_0_CAPTION, x_7_0);
    DDX_Control(pDX, IDC_7_0_EXPLANATION, e_7_0);
    DDX_Control(pDX, IDC_CAPTION, c_Caption);
   }


BEGIN_MESSAGE_MAP(CExtendedCPU6ECXAMD, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU6ECXAMD message handlers

/****************************************************************************
*                         CExtendedCPU6ECXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU6ECXAMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000006, regs);

    FillIn(CacheTLBInfo(IDS_EXTENDED_6_ECX_31_16,
                        IDS_EXTENDED_6_ECX_15_12,
                        IDS_EXTENDED_6_ECX_11_8,
                        IDS_EXTENDED_6_ECX_7_0,
                        IDS_EXTENDED_6_ECX_CAPTION), regs.ECX);


    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU6ECXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU6ECXAMD::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    c_Caption.SetWindowText(_T(""));

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    SETCOLOR(7_0);
    SETCOLOR(11_8);
    SETCOLOR(15_12);
    SETCOLOR(31_16);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }

/****************************************************************************
*                           CExtendedCPU6ECXAMD::FillIn
* Inputs:
*       const CacheTLBInfo & info: Cache info data decode table
*       UINT data: Data to decode
* Result: void
*       
* Effect: 
*       Decodes the information
* Notes:
*       info.D31_16
*       info.D15_12
*       info.D11_8
*       info.D7_0
*       info.caption
*
*       The format strings are
*       ...caption...\nformat\ncode
*                              |
*                              A - use associativity decode
*                              N - no decode
*                              K - decode as KB
****************************************************************************/

void CExtendedCPU6ECXAMD::FillIn(const CacheTLBInfo & info, UINT data)
    {
     union {
        struct {
           UINT D7_0:8;     // 7..0
           UINT D11_8:4;    // 11..8
           UINT D15_12:4;   // 15..12
           UINT D31_16:16;  // 31..16
        } fields;
        UINT w;
     } V;

     V.w = data;

     CString label;
     label.LoadString(info.caption);
     c_Caption.SetWindowText(label);

     CString fmt;

     CString value;
     CString caption;
     CString decode;

//-----------------------------------------------------------------------------
#define FMT(x) {                                                     \
     fmt.LoadString(info.D##x);                                      \
     FormatValue(fmt, (UINT)V.fields.D##x, value, caption, decode);  \
     c_##x.SetWindowText(value);                                     \
     x_##x.SetWindowText(caption);                                   \
     e_##x.SetWindowText(decode);                                    \
}
//-----------------------------------------------------------------------------
     FMT(31_16);
     FMT(15_12);
     FMT(11_8);
     FMT(7_0);

    } // CExtendedCPU6ECXAMD::FillIn

/****************************************************************************
*                        CExtendedCPU6ECXAMD::FormatValue
* Inputs:
*       CString fmt: Format string
*       BYTE data:
*       CString & value:
*       CString & caption:
*       CString & decode:
* Result: void
*       
* Effect: 
*       Decodes the values
****************************************************************************/

void CExtendedCPU6ECXAMD::FormatValue(CString fmt, UINT data, CString & value, CString & caption, CString & decode)
    {
     // caption \n%...\ndecode

     CString s;
     int n = fmt.Find(_T("\n"));
     caption = fmt.Left(n);
     s = fmt.Mid(n + 1);
     // %...\ndecode
     CString numfmt;
     n = s.Find(_T("\n"));
     numfmt = s.Left(n);
     s = s.Mid(n + 1);
     // decode

     value.Format(numfmt, data);
     // handle decode here
     decode = _T("");
     if(s == _T("A"))
        { /* L1 associativity */
         decode.LoadString(IDS_L2_ASSOCIATIVITY_00H + data);
        } /* L1 associativity */
     else
     if(s == _T("K"))
        { /* KB */
         decode = FormatWithCommas(data * 1024);
         CString t = FormatScaled(data * 1024);
         decode += _T(" (") + t + _T(")");
        } /* KB */
    } // CExtendedCPU6ECXAMD::FormatValue
