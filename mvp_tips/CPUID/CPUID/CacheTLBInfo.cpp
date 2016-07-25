// CacheTLBInfo.cpp : implementation file
//

#include "stdafx.h"
#include "CacheTLBInfo.h"


// CCacheTLBInfo

IMPLEMENT_DYNAMIC(CCacheTLBInfo, CBlock)

/****************************************************************************
*                               CCacheTLBInfo::CCacheTLBInfo
* Effect: 
*       Constructor
****************************************************************************/

CCacheTLBInfo::CCacheTLBInfo()
   {
   }

CCacheTLBInfo::~CCacheTLBInfo()
{
}


/****************************************************************************
*                                  Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CCacheTLBInfo, CBlock)
    ON_WM_PAINT()
END_MESSAGE_MAP()

/****************************************************************************
*                               CCacheTLBInfo::OnPaint
* Result: void
*       
* Effect: 
*       Draws the contents
****************************************************************************/

void CCacheTLBInfo::OnPaint()
    {
     CPaintDC dc(this); // device context for painting

     FillBackground(dc);

     CRect r;
     GetClientRect(&r);

     { /* draw TLBs */
      int save = dc.SaveDC();
      int nBlocks = (int)descriptors.GetSize();
      CArray<CRect, CRect>blocks;
      ComputeBlocks(blocks, nBlocks);

      CFont * f = GetFont();
      if(f != NULL)
         dc.SelectObject(f);
      
      dc.SelectObject(&object);
      for(int i = 0; i < blocks.GetSize(); i++)
         { /* show each */
          dc.Rectangle(&blocks[i]);
          dc.SetBkMode(TRANSPARENT);

          CString s;
          GetWindowText(s);
          s = _T(" ") + s;
          dc.DrawText(s, &blocks[i], DT_TOP | DT_LEFT);
          
          s = descriptors[i].GetShortVersion();
          dc.DrawText(s, &blocks[i], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
         } /* show each */
     } /* draw TLBs */

     // Do not call CBlock::OnPaint() for painting messages
    }

/****************************************************************************
*                         CCacheTLBInfo::QueryShowTip
* Inputs:
*       CPoint pt: Client coordinates of cursor
* Result: void
*       
* Effect: 
*       Shows the tooltip
****************************************************************************/

void CCacheTLBInfo::QueryShowTip(CPoint pt)
    {
     int nBlocks = (int)descriptors.GetSize();
     CArray<CRect, CRect>blocks;
     ComputeBlocks(blocks, nBlocks);

     CPoint pos = GetMessagePos();
     ScreenToClient(&pos);

     CString TipText;
     
     for(int i = 0; i < blocks.GetSize(); i++)
        { /* scan blocks */
         if(blocks[i].PtInRect(pos))
            { /* found it */
             TipText = descriptors[i].GetLongVersion();
             break;
            } /* found it */
        } /* scan blocks */

     DisplayToolTip(pt, TipText, TRUE);
    } // CCacheTLBInfo::QueryShowTip
