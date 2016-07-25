// ExtendedCPU5AMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU5AMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "FormatWithCommas.h"

// CExtendedCPU5AMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU5AMD, CLeaves)
CExtendedCPU5AMD::CExtendedCPU5AMD(UINT idd)
        : CLeaves(idd)
{
}

CExtendedCPU5AMD::~CExtendedCPU5AMD()
{
}

void CExtendedCPU5AMD::DoDataExchange(CDataExchange* pDX)
   {
    CLeaves::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_31_24, c_31_24);
    DDX_Control(pDX, IDC_31_24_CAPTION, x_31_24);
    DDX_Control(pDX, IDC_31_24_EXPLANATION, e_31_24);
    DDX_Control(pDX, IDC_23_16, c_23_16);
    DDX_Control(pDX, IDC_23_16_CAPTION, x_23_16);
    DDX_Control(pDX, IDC_23_16_EXPLANATION, e_23_16);
    DDX_Control(pDX, IDC_15_8, c_15_8);
    DDX_Control(pDX, IDC_15_8_CAPTION, x_15_8);
    DDX_Control(pDX, IDC_15_8_EXPLANATION, e_15_8);
    DDX_Control(pDX, IDC_7_0, c_7_0);
    DDX_Control(pDX, IDC_7_0_CAPTION, x_7_0);
    DDX_Control(pDX, IDC_7_0_EXPLANATION, e_7_0);
    DDX_Control(pDX, IDC_CAPTION, c_Caption);
   }


BEGIN_MESSAGE_MAP(CExtendedCPU5AMD, CLeaves)
END_MESSAGE_MAP()


// CExtendedCPU5AMD message handlers

/****************************************************************************
*                         CExtendedCPU5AMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU5AMD::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(0x80000005, regs);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU5AMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU5AMD::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    c_Caption.SetWindowText(_T(""));

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    SETCOLOR(7_0);
    SETCOLOR(15_8);
    SETCOLOR(23_16);
    SETCOLOR(31_24);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }

/****************************************************************************
*                           CExtendedCPU5AMD::FillIn
* Inputs:
*       const CacheTLBInfo & info: Cache info data decode table
*       UINT data: Data to decode
* Result: void
*       
* Effect: 
*       Decodes the information
* Notes:
*       info.D31_24
*       info.D23_16
*       info.D15_8
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

void CExtendedCPU5AMD::FillIn(const CacheTLBInfo & info, UINT data)
    {
     union {
        struct {
           UINT D7_0:8;   // 7..0
           UINT D15_8:8;  // 15..8
           UINT D23_16:8; // 23..16
           UINT D31_24:8; // 31..24
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
     FormatValue(fmt, (BYTE)V.fields.D##x, value, caption, decode);  \
     c_##x.SetWindowText(value);                                     \
     x_##x.SetWindowText(caption);                                   \
     e_##x.SetWindowText(decode);                                    \
}
//-----------------------------------------------------------------------------
     FMT(31_24);
     FMT(23_16);
     FMT(15_8);
     FMT(7_0);

    } // CExtendedCPU5AMD::FillIn

/****************************************************************************
*                        CExtendedCPU5AMD::FormatValue
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

void CExtendedCPU5AMD::FormatValue(CString fmt, BYTE data, CString & value, CString & caption, CString & decode)
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
         switch(data)
            { /* special cases */
             case 0x00:
                decode.LoadString(IDS_EXTENDED_5_ASSOCIATIVITY_RESERVED);
                break;
             case 0xFF:
                decode.LoadString(IDS_EXTENDED_5_ASSOCIATIVITY_FULL);
                break;
             default:
                { /* n-way associative */
                 CString assoc;
                 assoc.LoadString(IDS_EXTENDED_5_ASSOCIATIVITY_N_WAY);
                 decode.Format(assoc, data);
                 break;
                } /* n-way associative */
            } /* special cases */
        } /* L1 associativity */
     else
     if(s == _T("K"))
        { /* format it */
         decode = FormatWithCommas(data * 1024);
        } /* format it */
    } // CExtendedCPU5AMD::FormatValue
