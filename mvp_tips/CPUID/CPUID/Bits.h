#pragma once


// CBits

class CBits : public CStatic
{
        DECLARE_DYNAMIC(CBits)

public:
        CBits();
        void SetBkColor(COLORREF c);
        void SetTextColor(COLORREF c);
        COLORREF GetBkColor() { return bkgnd; }
        COLORREF GetTextColor() { return text; }
        virtual ~CBits();

protected:
        DECLARE_MESSAGE_MAP()
        COLORREF bkgnd;
        COLORREF text;
        CBrush brush;
        CString Help;
protected:
    afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
    afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
    virtual void PreSubclassWindow();
};


