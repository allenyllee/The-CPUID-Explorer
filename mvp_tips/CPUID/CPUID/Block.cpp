// Block.cpp : implementation file
//

#include "stdafx.h"
#include "Block.h"


// CBlock

IMPLEMENT_DYNAMIC(CBlock, CStatic)

/****************************************************************************
*                               CBlock::CBlock
* Effect: 
*       Constructor
****************************************************************************/

CBlock::CBlock()
   {
    bkgnd.CreateSolidBrush(RGB(255, 255, 255));
    object.CreateSolidBrush(RGB(255, 255, 0));

    gap = ::GetSystemMetrics(SM_CYHSCROLL) / 2;

    infoDisplay = NULL;
   }

CBlock::~CBlock()
{
}


/****************************************************************************
*                                  Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBlock, CStatic)
    ON_WM_PAINT()
    ON_MESSAGE(WM_SETTEXT, OnSetText)
    ON_MESSAGE(WM_GETTEXT, OnGetText)
    ON_MESSAGE(WM_GETTEXTLENGTH, OnGetTextLength)
    ON_WM_MOUSEMOVE()
    ON_WM_DESTROY()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/****************************************************************************
*                           CBlock::FillBackground
* Inputs:
*       CDC & dc: DC to use
* Result: void
*       
* Effect: 
*       Fills the background
****************************************************************************/

void CBlock::FillBackground(CDC & dc)
    {
     int save = dc.SaveDC();
     CRect r;
     GetClientRect(&r);

     dc.SelectObject(&bkgnd);
     dc.SelectStockObject(NULL_PEN);
     dc.Rectangle(&r);
     dc.RestoreDC(save);
     
    } // CBlock::FillBackground

/****************************************************************************
*                               CBlock::OnPaint
* Result: void
*       
* Effect: 
*       Draws the contents
****************************************************************************/

void CBlock::OnPaint()
    {
     CPaintDC dc(this); // device context for painting

     FillBackground(dc);

     CRect r;
     GetClientRect(&r);

     CFont * f = GetFont();
     if(f != NULL)
        dc.SelectObject(f);

     CString s;
     GetWindowText(s);
     dc.SetBkMode(TRANSPARENT);
     dc.DrawText(s, &r, DT_TOP | DT_WORDBREAK);
     // Do not call CStatic::OnPaint() for painting messages
    }

/****************************************************************************
*                            CBlock::SetBrushColor
* Inputs:
*       CBrush & br: Brush to set
*       COLORREF color: Desired color
* Result: void
*       
* Effect: 
*       Sets the brush color
****************************************************************************/

void CBlock::SetBrushColor(CBrush & br, COLORREF color)
    {
     if(br.GetSafeHandle() != NULL)
        br.DeleteObject();

     br.CreateSolidBrush(color);
     if(GetSafeHwnd() != NULL)
        Invalidate();
    } // CBlock::SetBrushColor

/****************************************************************************
*                            CBlock::GetBrushColor
* Inputs:
*       CBrush & r: Brush to report on
* Result: COLORREF
*       The color of the brush
*       Default color if the brush is not real
****************************************************************************/

COLORREF CBlock::GetBrushColor(CBrush & br)
    {
     if(br.GetSafeHandle() == NULL)
        return RGB(255, 255, 255);

     LOGBRUSH LB;
     bkgnd.GetLogBrush(&LB);
     return LB.lbColor;
     
    } // CBlock::GetBrushColor

/****************************************************************************
*                             CBlock::SetBkColor
* Inputs:
*       COLORREF c: Color to set
* Result: void
*       
* Effect: 
*       Sets the color
****************************************************************************/

void CBlock::SetBkColor(COLORREF c)
    {
     SetBrushColor(bkgnd, c);
    } // CBlock::SetBkColor

/****************************************************************************
*                             CBlock::GetBkColor
* Result: COLORREF
*       Color of background
****************************************************************************/

COLORREF CBlock::GetBkColor()
    {
     return GetBrushColor(bkgnd);
    } // CBlock::GetBkColor

/****************************************************************************
*                           CBlock::SetObjectColor
* Inputs:
*       COLOREF color: Color to set
* Result: void
*       
* Effect: 
*       Sets the object color
****************************************************************************/

void CBlock::SetObjectColor(COLORREF c)
    {
     SetBrushColor(object, c);
    } // CBlock::SetObjectColor

/****************************************************************************
*                            CBlock::ComputeBlocks
* Inputs:
*       CArray<CRect, CRect> & blocks: Place to put blocks computed
*       int nBlocks: Number of blocks to compute
* Result: void
*       
* Effect: 
*       Computes the area to hold nBlocks.

****************************************************************************/

void CBlock::ComputeBlocks(CArray<CRect, CRect> & blocks, int nBlocks)
    {
     if(nBlocks == 0)
         return;

     TRACE("----------------------------------------------------------------\n");
     CRect r;
     GetClientRect(&r);

     TRACE("gap = %d\n", gap);

     int gaps = nBlocks - 1;
     TRACE("gaps = %d\n", gaps);
     
     int availableHeight = r.Height() - (gaps * gap);
     TRACE("availableHeight=%d\n", availableHeight);

     int height = availableHeight / nBlocks;
     TRACE("height = %d\n", height);

     height = min(r.Height() / 4, height);
     TRACE("constrained height = %d\n", height);

     int topToBottom = (height * nBlocks) + (gap * gaps);
     TRACE("top-to-bottom space = %d\n", topToBottom);

     int top = (r.Height() - topToBottom) / 2;
     TRACE("top = %d\n", top);

     blocks.SetSize(0);
     for(int i = 0; i < nBlocks; i++)
        { /* draw processors */
         CRect bk(r.left, top, r.right, top + height);
         TRACE("[%d] left=%d top=%d right=%d, bottom=%d\n", i, bk.left, bk.top, bk.right, bk.bottom);
         blocks.Add(bk);
         top += height + gap;
        } /* draw processors */
     TRACE("----------------------------------------------------------------\n");
    } // CBlock::ComputeBlocks

/****************************************************************************
*                              CBlock::OnSetText
* Inputs:
*       WPARAM: Ignored
*       LPARAM: (LPARAM)(LPCTSTR)
* Result: LRESULT
*       TRUE, always
* Effect: 
*       Sets the text string for this control
* Notes:
*       This is required because there is a reliability problem with
*       static text controls (they redraw themselves without sending
*       WM_PAINT, a clear bug in the OS) and other forms of static
*       controls such as rectangles and frames will not hold text
****************************************************************************/

LRESULT CBlock::OnSetText(WPARAM, LPARAM lParam)
    {
     text = (LPCTSTR)lParam;
     return TRUE;
    } // CBlock::OnSetText

/****************************************************************************
*                              CBlock::OnGetText
* Inputs:
*       WPARAM: number of TCHARs available
*       LPARAM: (LPARAM)(LPTSTR) pointer to buffer
* Result: LRESULT
*       Number of TCHARs copied, not counting the terminal NUL
* Effect: 
*       Copies the characters to the buffer
****************************************************************************/

LRESULT CBlock::OnGetText(WPARAM wParam, LPARAM lParam)
    {
     LPTSTR end;
     size_t sizeRemaining;
     StringCchCopyEx((LPTSTR)lParam,    // target
                     wParam,            // size of target
                     (LPCTSTR)text,     // source
                     &end,
                     &sizeRemaining,
                     0);

     if(sizeRemaining != NULL)
        return wParam - 1;
     else
        return text.GetLength();
    } // CBlock::OnGetText

/****************************************************************************
*                           CBlock::OnGetTextLength
* Inputs:
*       WPARAM: unused
*       LPARAM: unused
* Result: LRESULT
*       Number of TCHARs in string
****************************************************************************/

LRESULT CBlock::OnGetTextLength(WPARAM, LPARAM)
    {
     return text.GetLength();
    } // CBlock::OnGetTextLength

/****************************************************************************
*                             CBlock::OnMouseMove
* Inputs:
*       UINT nFlags:
*       CPoint point:
* Result: void
*       
* Effect: 
*       Implements a workable tooltip mechanism, one not subject to the
*       numerous design failures of the built-in tooltip mechanism
****************************************************************************/

void CBlock::OnMouseMove(UINT nFlags, CPoint point)
    {
     ShowTip(point);
     CStatic::OnMouseMove(nFlags, point);
    }

/****************************************************************************
*                              CBlock::OnDestroy
* Result: void
*       
* Effect: 
*       Deletes the infoDisplay window
****************************************************************************/

void CBlock::OnDestroy()
    {
     CStatic::OnDestroy();

     if(infoDisplay != NULL)
        infoDisplay->DestroyWindow();
    }

/****************************************************************************
*                               CBlock::ShowTip
* Inputs:
*       CPoint pt: Point
* Result: void
*       
* Effect: 
*       If the point is something that can be shown, show the tooltip
****************************************************************************/

void CBlock::ShowTip(CPoint pt)
    {
     QueryShowTip(pt);
    } // CBlock::ShowTip

/****************************************************************************
*                           CBlock::DisplayToolTip
* Inputs:
*       CPoint pt: Place to display it
*       const CString & text: Text to display
* Result: void
*       
* Effect: 
*       Shows the tooltip text
****************************************************************************/

void CBlock::DisplayToolTip(CPoint pt, const CString & text, BOOL visible)
    {
     infoDisplay = infoDisplay->ShowTip(this, pt, text, visible);
    } // CBlock::DisplayToolTip

/****************************************************************************
*                            CBlock::OnMouseLeave
* Inputs:
*       WPARAM: ignored
*       LPARAM: ignored
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Handles the mouse leaving the window
****************************************************************************/

LRESULT CBlock::OnMouseLeave(WPARAM, LPARAM)
    {
     if(infoDisplay != NULL)
        infoDisplay->DestroyWindow();
     infoDisplay = NULL;
     return 0;
    } // CBlock::OnMouseLeave

/****************************************************************************
*                            CBlock::GetMessagePos
* Result: CPoint
*       Message position
****************************************************************************/

CPoint CBlock::GetMessagePos()
    {
     DWORD rawpos = ::GetMessagePos();
     POINTS pos16 = MAKEPOINTS(rawpos);
     return CPoint(pos16.x, pos16.y);
    } // CBlock::GetMessagePos
