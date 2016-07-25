#pragma once

#include "InfoDisplay.h"
// CBlock

class CBlock : public CStatic
{
        DECLARE_DYNAMIC(CBlock)

public:
        CBlock();
        virtual ~CBlock();
        void SetBkColor(COLORREF c);
        COLORREF GetBkColor();
        void SetObjectColor(COLORREF color);
        COLORREF GetObjectColor();
        void SetGap(int n) { gap = n; if(GetSafeHwnd() != NULL) Invalidate(); }
        int GetGape() { return gap; }
protected:
        CBrush bkgnd;
        CBrush object;
        int gap;
        CString text;  // display text

        //----------------------------------------------------------------
        // Simulated tooltip support
        //----------------------------------------------------------------
public:
        void SetToolTipText(LPCTSTR s) { ToolTipText = s; }
        void SetToolTipText(UINT id) { CString s; s.LoadString(id); SetToolTipText(s); }
protected:
        CPoint GetMessagePos();
        CInfoDisplay * infoDisplay;
        CString ToolTipText; // desired tooltip text (for default handler)
        virtual void ShowTip(CPoint pt);
        virtual void QueryShowTip(CPoint pt) { } // implement in subclasses
        void DisplayToolTip(CPoint pt, const CString & text, BOOL visible = TRUE);
        //----------------------------------------------------------------

        void ComputeBlocks(CArray<CRect, CRect> & blocks, int nBlocks);
        void SetBrushColor(CBrush & br, COLORREF c);
        COLORREF GetBrushColor(CBrush & br);
        void FillBackground(CDC & dc);

protected: // Message handlers        
        DECLARE_MESSAGE_MAP()
        afx_msg void OnPaint();
        afx_msg LRESULT OnSetText(WPARAM, LPARAM);
        afx_msg LRESULT OnGetText(WPARAM, LPARAM);
        afx_msg LRESULT OnGetTextLength(WPARAM, LPARAM);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnDestroy();
        afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
};


