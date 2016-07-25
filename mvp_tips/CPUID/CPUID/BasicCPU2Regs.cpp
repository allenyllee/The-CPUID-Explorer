// BasicCPU2Regs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU2Regs.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"

// CBasicCPU2Regs dialog

IMPLEMENT_DYNCREATE(CBasicCPU2Regs, CLeaves)

#define COL_REG   0
#define COL_SEQ   1
#define COL_FIELD 2
#define COL_DESC  3
#define COL_TEXT  4


// Message map

BEGIN_MESSAGE_MAP(CBasicCPU2Regs, CLeaves)
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CBasicCPU2Regs::CBasicCPU2Regs - Constructor

CBasicCPU2Regs::CBasicCPU2Regs() :
        CLeaves(CBasicCPU2Regs::IDD)
{
}

CBasicCPU2Regs::~CBasicCPU2Regs()
   {
   }

void CBasicCPU2Regs::DoDataExchange(CDataExchange* pDX)
{
 CLeaves::DoDataExchange(pDX);
 DDX_Control(pDX, IDC_REGS2, c_Regs2);
}

/****************************************************************************
*                          CBasicCPU2Regs::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Displays the register values
****************************************************************************/

BOOL CBasicCPU2Regs::OnSetActive()
    {
     c_Regs2.DeleteAllItems();

     CPUregs regs;
     CurrentProcessor.GetCPUID(1, &regs);
     if(regs.EAX < 2)
        { /* not available */
         c_Regs2.EnableWindow(FALSE);
         return CLeaves::OnSetActive();
        } /* not available */

     GetAndReport(2, regs);

     int count = LOBYTE(LOWORD(regs.EAX));
     ShowInfo(1, _T("EAX"), _T("<7..0>"), LOBYTE(LOWORD(regs.EAX)), IDS_CPUID2_COUNT);

     for(int i = 1; i <= count; i++)
        { /* handle each iteration */
         if(i > 1)
            ShowDescriptor(i, _T("EAX"), _T("<7..0>"), LOBYTE(LOWORD(regs.EAX)), regs.EAX >= 0);
         ShowDescriptor(i, _T("EAX"), _T("<15..8>"), HIBYTE(LOWORD(regs.EAX)), regs.EAX >= 0);
         ShowDescriptor(i, _T("EAX"), _T("<23..16>"), LOBYTE(HIWORD(regs.EAX)), regs.EAX >= 0);
         ShowDescriptor(i, _T("EAX"), _T("<31..24>"), HIBYTE(HIWORD(regs.EAX)), regs.EAX >= 0);

         ShowDescriptor(i,_T("EBX"), _T("<7..0>"), LOBYTE(LOWORD(regs.EBX)), regs.EBX >= 0);
         ShowDescriptor(i, _T("EBX"), _T("<15..8>"), HIBYTE(LOWORD(regs.EBX)), regs.EBX >= 0);
         ShowDescriptor(i, _T("EBX"), _T("<23..16>"), LOBYTE(HIWORD(regs.EBX)), regs.EBX >= 0);
         ShowDescriptor(i, _T("EBX"), _T("<31..24>"), HIBYTE(HIWORD(regs.EBX)), regs.EBX >= 0);

         ShowDescriptor(i, _T("ECX"), _T("<7..0>"), LOBYTE(LOWORD(regs.ECX)), regs.ECX >= 0);
         ShowDescriptor(i, _T("ECX"), _T("<15..8>"), HIBYTE(LOWORD(regs.ECX)), regs.ECX >= 0);
         ShowDescriptor(i, _T("ECX"), _T("<23..16>"), LOBYTE(HIWORD(regs.ECX)), regs.ECX >= 0);
         ShowDescriptor(i, _T("ECX"), _T("<31..24>"), HIBYTE(HIWORD(regs.ECX)), regs.ECX >= 0);

         ShowDescriptor(i, _T("EDX"), _T("<7..0>"), LOBYTE(LOWORD(regs.EDX)), regs.EDX >= 0);
         ShowDescriptor(i, _T("EDX"), _T("<15..8>"), HIBYTE(LOWORD(regs.EDX)), regs.EDX >= 0);
         ShowDescriptor(i, _T("EDX"), _T("<23..16>"), LOBYTE(HIWORD(regs.EDX)), regs.EDX >= 0);
         ShowDescriptor(i, _T("EDX"), _T("<31..24>"), HIBYTE(HIWORD(regs.EDX)), regs.EDX >= 0);
         CurrentProcessor.GetCPUID(2, &regs); // but don't report...
        } /* handle each iteration */

     return CLeaves::OnSetActive();
    } // CBasicCPU2Regs::OnSetActive

/****************************************************************************
*                          CBasicCPU2Regs::ShowInfo
* Inputs:
*       ¶
* Result: ¶
*       ¶
* Effect: 
*       ¶
****************************************************************************/

void CBasicCPU2Regs::ShowInfo(int iter, const CString & name, const CString & bits, BYTE desc, UINT id)
    {
     CString s;
     s.LoadString(id);
     ShowInfo(iter, name, bits, desc, s);
    } // CBasicCPU2Regs::ShowInfo

/****************************************************************************
*                          CBasicCPU2Regs::ShowInfo
* Inputs:
*       int iter: Iteration count
*       const CString & name: Name of register
*       const CString & bits: Bit range
*       BYTE desc: Descriptor value
*       const CString & text: Text to display for description
* Result: void
*       
* Effect: 
*       Creates a line in the display
****************************************************************************/

void CBasicCPU2Regs::ShowInfo(int iter, const CString & name, const CString & bits, BYTE desc, const CString & text)
    {
     int n = c_Regs2.InsertItem(c_Regs2.GetItemCount(), name);
     c_Regs2.SetItemText(n, COL_FIELD, bits);

     CString s;
     s.Format(_T("%d"), iter);
     c_Regs2.SetItemText(n, COL_SEQ, s);
     
     s.Format(_T("%02XH"), desc);
     c_Regs2.SetItemText(n, COL_DESC, s);

     c_Regs2.SetItemText(n, COL_TEXT, text);
     
    } // CBasicCPU2Regs::ShowInfo

/****************************************************************************
*                         CBasicCPU2Regs::ShowDescriptor
* Inputs:
*       int iter: Iteration count
*       const CString & name: Name of register
*       const CString & bits: Bit range
*       BYTE desc: Descriptor value
*       BOOL valid: TRUE if register value is valid
* Result: void
*       
* Effect: 
*       Adds the elements to the listbox
****************************************************************************/

void CBasicCPU2Regs::ShowDescriptor(int iter, const CString & name, const CString & bits, BYTE desc, BOOL valid)
    {
     CString s;
     if(!valid)
        { /* reserved value */
         s.LoadString(IDS_CTLB_RESERVED);
        } /* reserved value */
     else
        { /* real desc */
         /*
           Reg  | field  | desc | meaning
         */

         s.LoadString(IDS_CTLB_00H + desc);
         if(s.IsEmpty())
            s.LoadString(IDS_CTLB_UNUSED);
         else
            { /* get long description */
             int n = s.Find(_T("\n"));
             if(n >= 0)
                s = s.Left(n);
            } /* get long description */
        } /* real desc */
     ShowInfo(iter, name, bits, desc, s);
    } // CBasicCPU2Regs::ShowDescriptor

/****************************************************************************
*                          CBasicCPU2Regs::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the control
****************************************************************************/

BOOL CBasicCPU2Regs::OnInitDialog()
    {
     CLeaves::OnInitDialog();

     CClientDC dc(&c_Regs2);
#define FUDGE (3 * ::GetSystemMetrics(SM_CXSIZEFRAME))

     CString r(_T("EAX"));
     CString s;
     s.LoadString(IDS_REG);
     c_Regs2.InsertColumn(COL_REG, s, LVCFMT_CENTER, max(dc.GetTextExtent(s).cx, dc.GetTextExtent(r).cx) + FUDGE);

     CString n(_T("0"));
     s.LoadString(IDS_ITER);
     c_Regs2.InsertColumn(COL_SEQ, s, LVCFMT_CENTER, max(dc.GetTextExtent(s).cx, dc.GetTextExtent(n).cx) + FUDGE);
    
     CString f(_T("<00..00>"));
     s.LoadString(IDS_FIELD);
     c_Regs2.InsertColumn(COL_FIELD, s, LVCFMT_RIGHT, max(dc.GetTextExtent(s).cx, dc.GetTextExtent(f).cx) + FUDGE);
    
     CString t(_T("00H"));
     s.LoadString(IDS_DESC);
     c_Regs2.InsertColumn(COL_DESC, s, LVCFMT_RIGHT,  max(dc.GetTextExtent(s).cx, dc.GetTextExtent(t).cx) + FUDGE);

     CRect c;
     c_Regs2.GetClientRect(&c);
     int w = 0;
     for(int i = 0; i < COL_TEXT - 1; i++)
        w += c_Regs2.GetColumnWidth(i);

     s.LoadString(IDS_TEXT);
     c_Regs2.InsertColumn(COL_TEXT, s, LVCFMT_LEFT, c.Width() - w);

     c_Regs2.ModifyStyleEx(0, LVS_EX_FULLROWSELECT);
     return TRUE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
    }

/****************************************************************************
*                             CBasicCPU2Regs::OnSize
* Inputs:
*       UINT nType: type of resize
*       int cx: New client width
*       int cy: New client height
* Result: void
*       
* Effect: 
*       Resizes the controls
****************************************************************************/

void CBasicCPU2Regs::OnSize(UINT nType, int cx, int cy)
    {
     CLeaves::OnSize(nType, cx, cy);

     if(c_Regs2.GetSafeHwnd() != NULL)
        { /* resize it */
         CRect r;
         c_Regs2.GetWindowRect(&r);
         ScreenToClient(&r);
         c_Regs2.SetWindowPos(NULL, 0, 0, cx, cy - r.top, SWP_NOMOVE | SWP_NOZORDER);
        } /* resize it */
    }
