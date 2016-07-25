// PhysicalAddressLines.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PhysicalAddressLines.h"

#include "CPUIDx86.h"
#include "CPUIDregs.h"
#include "CurrentProcessor.h"
// CBlock

IMPLEMENT_DYNAMIC(CPhysicalAddressLines, CBlock)

CPhysicalAddressLines::CPhysicalAddressLines()
   {
   }

CPhysicalAddressLines::~CPhysicalAddressLines()
{
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CPhysicalAddressLines, CBlock)
    ON_WM_PAINT()
END_MESSAGE_MAP()

/****************************************************************************
*                        CPhysicalAddressLines::OnPaint
* Result: void
*       
* Effect: 
*       Computes the correct number for the Physical address lines and
*       calls the superclass OnPaint handler
****************************************************************************/

void CPhysicalAddressLines::OnPaint()
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(0x80000000, &regs);
     if(regs.EAX < 0x80000008)
        { /* unknown */
         SetWindowText(_T(""));
         SetToolTipText(IDS_PA_UNSPECIFIED);
        } /* unknown */
     else
        { /* has it */
         CurrentProcessor.GetCPUID(0x80000008, &regs);
         EAX8x EAX;
         EAX.w = regs.EAX;
         CString s;
         s.Format(_T("%d"), EAX.bits.PhysicalAddressBits);
         SetWindowText(s);
         SetToolTipText(IDS_80000008_EAX_PAB);
        } /* has it */
     CArrow::OnPaint();
    } // CPhysicalAddressLines::OnPaint
