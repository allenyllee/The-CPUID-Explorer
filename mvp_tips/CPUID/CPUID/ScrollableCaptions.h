#pragma once


// CScrollableCaptions dialog

class CScrollableCaptions : public CDialog
{
        DECLARE_DYNAMIC(CScrollableCaptions)

public:
        CScrollableCaptions() { ASSERT(FALSE); }
        CScrollableCaptions(UINT idd, CWnd* pParent = NULL);   // standard constructor
        virtual ~CScrollableCaptions();
        void SavePos();

// Dialog Data
//      enum { IDD = IDD_SCROLLABLECAPTIONS };

protected:
        virtual BOOL OnInitDialog();
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        void SetScrollParameters();
        void DoAlign(UINT ctlid, UINT textid);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        void SetPlatformLabel();

        CWnd * bottom; // bottommost window (actually, any window would do...)

        CStatic c_Platform;
        DECLARE_MESSAGE_MAP()
};
