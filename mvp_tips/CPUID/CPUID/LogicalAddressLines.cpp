// LogicalAddressLines.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LogicalAddressLines.h"

#include "CPUIDx86.h"
#include "CPUIDregs.h"
#include "CurrentProcessor.h"
// CBlock

IMPLEMENT_DYNAMIC(CLogicalAddressLines, CBlock)

CLogicalAddressLines::CLogicalAddressLines()
   {
   }

CLogicalAddressLines::~CLogicalAddressLines()
{
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CLogicalAddressLines, CBlock)
    ON_WM_PAINT()
END_MESSAGE_MAP()

/****************************************************************************
*                        CLogicalAddressLines::OnPaint
* Result: void
*       
* Effect: 
*       Computes the correct number for the logical address lines and
*       calls the superclass OnPaint handler
****************************************************************************/

void CLogicalAddressLines::OnPaint()
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(0x80000000, &regs);
     if(regs.EAX < 0x80000008)
        { /* unknown */
         SetWindowText(_T("32"));
         SetToolTipText(IDS_UNKNOWN_LOGICAL);
        } /* unknown */
     else
        { /* has it */
         CurrentProcessor.GetCPUID(0x80000008, &regs);
         EAX8x EAX;
         EAX.w = regs.EAX;
         CString s;
         s.Format(_T("%d"), EAX.bits.VirtualAddressBits);
         SetToolTipText(IDS_80000008_EAX_VAB);
         SetWindowText(s);
        } /* has it */
     CArrow::OnPaint();
    } // CLogicalAddressLines::OnPaint
