// CPUCoreRegion.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CPUCoreRegion.h"

#include "CPUIDx86.h"
#include "CPUIDregs.h"
#include "CurrentProcessor.h"
#include "GetCPUName.h"
// CCPUCoreRegion

IMPLEMENT_DYNAMIC(CCPUCoreRegion, CBlock)

/****************************************************************************
*                       CCPUCoreRegion::CCPUCoreRegion
* Effect: 
*       Constructor
****************************************************************************/

CCPUCoreRegion::CCPUCoreRegion()
{
}

CCPUCoreRegion::~CCPUCoreRegion()
{
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CCPUCoreRegion, CBlock)
    ON_WM_PAINT()
END_MESSAGE_MAP()

/****************************************************************************
*                        CCPUCoreRegion::ComputeNProcs
* Result: int
*       Number of logical processors
****************************************************************************/

int CCPUCoreRegion::ComputeNProcs()
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(1, &regs);
     EBX1b EBX;
     EBX.w = regs.EBX;

     int nprocs = EBX.bits.LogicalProcessors;
     if(nprocs == 0)
        nprocs = 1;
     return nprocs;
    } // CCPUCoreRegion::ComputeNProcs

/****************************************************************************
*                           CCPUCoreRegion::OnPaint
* Result: void
*       
* Effect: 
*       Paints the CPU core blocks
****************************************************************************/

void CCPUCoreRegion::OnPaint()
    {
     CPaintDC dc(this);
     FillBackground(dc);
     
     // Draw the CPUs.  The CPUs will not exceed 25% of the height of the CPU
     // region, and will be centered vertically

     // CPUID(1):EBX.LogicalProcessors
     //
     { /* draw processors */
      int save = dc.SaveDC();

      CArray<CRect, CRect> blocks;
      int nprocs = ComputeNProcs();

      ComputeBlocks(blocks, nprocs);

      dc.SelectObject(&object);

      CFont * f = GetFont();
      if(f == NULL)
         f = GetParent()->GetFont();
      if(f != NULL)
         dc.SelectObject(f);
      
      for(int i = 0; i < blocks.GetSize(); i++)
         { /* draw each */
          dc.Rectangle(&blocks[i]);
          dc.SetBkMode(TRANSPARENT);
          CString s;
          s.Format(_T("CPU%d"), i);
          dc.DrawText(s, &blocks[i], DT_VCENTER | DT_CENTER | DT_SINGLELINE); 
         } /* draw each */
      dc.RestoreDC(save);
     } /* draw processors */

    } // CCPUCoreRegion::OnPaint

/****************************************************************************
*                          CCPUCoreRegion::QueryShowTip
* Inputs:
*       CPoint pt: Place where mouse is
* Result: void
*       
* Effect: 
*       If in tooltip area, displays tip
****************************************************************************/

void CCPUCoreRegion::QueryShowTip(CPoint pt)
    {
     CArray<CRect, CRect> blocks;
     int nprocs = ComputeNProcs();

     ComputeBlocks(blocks, nprocs);
     CPoint pos = GetMessagePos();
     ScreenToClient(&pos);

     CString TipText;
     TipText = GetCPUName();

     TipText += _T("\n");

     // Family <family> Model <model> Stepping <stepping>, <typename>
     CString typefmt;
     typefmt.LoadString(IDS_FMT_CPU_TYPE);
     // Family %d Model %d Stepping %d, %s
     CString s;
     int family;
     int model;

     CPUregs regs;
     CurrentProcessor.GetCPUID(1, &regs);
     EAX1b EAX;
     EAX.w = regs.EAX;

     if(EAX.Intel.FamilyID == 0x0F)
        { /* extended family id */
         family = EAX.Intel.FamilyID + EAX.Intel.ExtendedFamily;
        } /* extended family id */
     else
        { /* short family */
         family = EAX.Intel.FamilyID;
        } /* short family */

     if(EAX.Intel.FamilyID == 0x06 || EAX.Intel.FamilyID == 0x0F)
        { /* extended mode */
         model = EAX.Intel.ModelID + (EAX.Intel.ExtendedModel << 4);
        } /* extended mode */
     else
        { /*  short model */
         model = EAX.Intel.ModelID;
        } /*  short model */

     s.Format(typefmt, family, model, EAX.Intel.SteppingID, GetCPUTypeName());
     TipText += s;
     
     DisplayToolTip(pt, TipText, TRUE);
     
    } // CCPUCoreRegion::QueryShowTip
