#pragma once


// CInfoDisplay

class CInfoDisplay : public CWnd
{
        DECLARE_DYNAMIC(CInfoDisplay)

public:
        CInfoDisplay();
        virtual ~CInfoDisplay();
        BOOL Create(int x, int y, LPCTSTR caption, CWnd * parent);
        void SetWindowText(LPCTSTR s);
        CInfoDisplay * ShowTip(CWnd * parent, CPoint pt, const CString & text, BOOL visible);
protected:
        DECLARE_MESSAGE_MAP()
        HFONT font;
protected:
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg LRESULT OnSetFont(WPARAM, LPARAM);
    afx_msg LRESULT OnGetFont(WPARAM, LPARAM);
protected:
    virtual void PostNcDestroy();
};


