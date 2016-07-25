// ExtendedCPU6AMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU6AMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"

// CExtendedCPU6AMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU6AMD, CLeaves)
CExtendedCPU6AMD::CExtendedCPU6AMD(UINT idd)
        : CLeaves(idd)
{
}

CExtendedCPU6AMD::~CExtendedCPU6AMD()
{
}

void CExtendedCPU6AMD::DoDataExchange(CDataExchange* pDX)
   {
    CLeaves::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_31_28, c_31_28);
    DDX_Control(pDX, IDC_31_28_CAPTION, x_31_28);
    DDX_Control(pDX, IDC_31_28_EXPLANATION, e_31_28);
    DDX_Control(pDX, IDC_27_16, c_27_16);
    DDX_Control(pDX, IDC_27_16_CAPTION, x_27_16);
    DDX_Control(pDX, IDC_27_16_EXPLANATION, e_27_16);
    DDX_Control(pDX, IDC_15_12, c_15_12);
    DDX_Control(pDX, IDC_15_12_CAPTION, x_15_12);
    DDX_Control(pDX, IDC_15_12_EXPLANATION, e_15_12);
    DDX_Control(pDX, IDC_11_0, c_11_0);
    DDX_Control(pDX, IDC_11_0_CAPTION, x_11_0);
    DDX_Control(pDX, IDC_11_0_EXPLANATION, e_11_0);
    DDX_Control(pDX, IDC_CAPTION, c_Caption);
   }


BEGIN_MESSAGE_MAP(CExtendedCPU6AMD, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU6AMD message handlers

/****************************************************************************
*                         CExtendedCPU6AMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU6AMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000006, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU6AMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU6AMD::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    c_Caption.SetWindowText(_T(""));

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    SETCOLOR(11_0);
    SETCOLOR(15_12);
    SETCOLOR(27_16);
    SETCOLOR(31_28);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }

/****************************************************************************
*                           CExtendedCPU6AMD::FillIn
* Inputs:
*       const CacheTLBInfo & info: Cache info data decode table
*       UINT data: Data to decode
* Result: void
*       
* Effect: 
*       Decodes the information
* Notes:
*       info.D31_28
*       info.D27_16
*       info.D15_12
*       info.D11_0
*       info.caption
*
*       The format strings are
*       ...caption...\nformat\ncode
*                              |
*                              A - use associativity decode
*                              N - no decode
*                              K - decode as KB
****************************************************************************/

void CExtendedCPU6AMD::FillIn(const CacheTLBInfo & info, UINT data)
    {
     union {
        struct {
           UINT D11_0:12;   // 11..0
           UINT D15_12:4;   // 15..12
           UINT D27_16:12;  // 27..16
           UINT D31_28:4;   // 31..28
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
     FMT(31_28);
     FMT(27_16);
     FMT(15_12);
     FMT(11_0);

    } // CExtendedCPU6AMD::FillIn

/****************************************************************************
*                        CExtendedCPU6AMD::FormatValue
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

void CExtendedCPU6AMD::FormatValue(CString fmt, UINT data, CString & value, CString & caption, CString & decode)
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
    } // CExtendedCPU6AMD::FormatValue
