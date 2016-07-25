// Arrow.cpp : implementation file
//

#include "stdafx.h"
#include "Arrow.h"


// CBlock

IMPLEMENT_DYNAMIC(CArrow, CBlock)
CArrow::CArrow()
   {
    headpercent = 0.70;
    barpercent  = 0.40;
    dir = RIGHT;
   }

CArrow::~CArrow()
{
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CArrow, CBlock)
        ON_WM_PAINT()
END_MESSAGE_MAP()

/****************************************************************************
*                           CArrow::CreateArrowPath
* Inputs:
*       CDC & dc: DC to use
* Result: void
*       
* Effect: 
*       Creates the path
****************************************************************************/

void CArrow::CreateArrowPath(CDC & dc)
    {
     /********************************
       |<------>|         headpercent
                B [1]
       +--------------+
bar    |        |\    |
percent|        | \   |
       |        |  \  |
---[3]D|--------+C  \ |
 ^     |         [2] \|
 V     |         [5] /|A [0]
---[4]E|--------+F  / |
       |        |  /  |
       |        | /   |
       |        |/    |
       +--------------+
                G [6]
     *********************************/

     CArray<CPoint, CPoint> points;
     points.SetSize(7);

     CRect r;
     GetClientRect(&r);
     if(dir == LEFT)
        { /* map left */
         dc.SetMapMode(MM_ISOTROPIC);
         dc.SetViewportExt(r.Width(), r.Height());
         dc.SetWindowOrg(r.Width(), 0);
         dc.SetWindowExt(-r.Width(), r.Height());
        } /* map left */         
     // A
     points[0].x = r.right;
     points[0].y = r.Height() / 2;

     // B
     points[1].x = (int) ((double)r.Width() * headpercent);
     points[1].y = r.top;

     // C
     int bar = (int)((double)r.Height() * barpercent);
     points[2].x = points[1].x;
     points[2].y = (r.Height() - bar) / 2;

     // D
     points[3].x = r.left;
     points[3].y = points[2].y;

     // E
     points[4].x = points[3].x;
     points[4].y = points[3].y + bar;

     // F
     points[5].x = points[1].x;
     points[5].y = points[4].y;

     // G
     points[6].x = points[5].x;
     points[6].y = r.bottom;

     dc.BeginPath();
     dc.Polyline(points.GetData(), (int)points.GetSize());
     dc.CloseFigure();
     dc.EndPath();
    } // CArrow::CreateArrowPath

/****************************************************************************
*                               CArrow::OnPaint
* Result: void
*       
* Effect: 
*       Paints the region
****************************************************************************/

void CArrow::OnPaint()
    {
     CPaintDC dc(this);
     FillBackground(dc);

     int save = dc.SaveDC();
     CreateArrowPath(dc);

     int save2 = dc.SaveDC();
     dc.SelectObject(&object);
     dc.StrokeAndFillPath();
     dc.RestoreDC(save2);

     save2 = dc.SaveDC();

     if(Rgn.GetSafeHandle() != NULL)
        Rgn.DeleteObject();

     Rgn.CreateFromPath(&dc);
     dc.RestoreDC(save2);

     dc.RestoreDC(save);
     
     dc.SetBkMode(TRANSPARENT);
     CFont * f = GetFont();
     if(f == NULL)
        f = GetParent()->GetFont();
     if(f != NULL)
        dc.SelectObject(f);
     
     CString s;
     GetWindowText(s);
     CRect r;
     GetClientRect(&r);
     dc.DrawText(s, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    } // CArrow::OnPaint

/****************************************************************************
*                            CArrow::SetDirection
* Inputs:
*       CArrow::Direction d: Desired direction
* Result: void
*       
* Effect: 
*       Sets the desired direction
****************************************************************************/

void CArrow::SetDirection(CArrow::Direction d)
    {
     if(dir == d)
        return; // no change
     dir = d;
     if(GetSafeHwnd() != NULL)
        Invalidate();
    } // CArrow::SetDirection

/****************************************************************************
*                               CArrow::QueryShowTip
* Inputs:
*       CPoint pt: Point at which mouse is sitting
* Result: void
*       
* Effect: 
*       Shows the tooltip if it is desirable
****************************************************************************/

void CArrow::QueryShowTip(CPoint pt)
    {
     if(Rgn.GetSafeHandle() != NULL)
        { /* has region */
         if(!Rgn.PtInRegion(pt))
            { /* not in region */
             CBlock::DisplayToolTip(pt, _T(""));
             return;
            } /* not in region */
        } /* has region */

     CBlock::DisplayToolTip(pt, ToolTipText);
    } // CArrow::QueryShowTip
