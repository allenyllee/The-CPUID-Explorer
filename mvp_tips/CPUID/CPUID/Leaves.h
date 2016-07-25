#pragma once


// CLeaves dialog

class CLeaves : public CPropertyPage
{
        DECLARE_DYNAMIC(CLeaves)

public:
        CLeaves(UINT idd);
        virtual ~CLeaves();

// Dialog Data
//        enum { IDD = IDD_LEAVES };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
protected:
    void DoAlign(UINT ctlid, UINT textid);
    virtual void SetFixedFont(CWnd & wnd);
    CFont font;
    virtual BOOL OnInitDialog();
    afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
    afx_msg LRESULT OnDisable(WPARAM, LPARAM);
    virtual void PostNcDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
    CStatic c_Platform;
};

/****************************************************************************
*                                 UWM_DISABLE
* Inputs:
*       WPARAM: ignored
*       LPARAM: ignored
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Disables all controls in the page
****************************************************************************/

#define UWM_DISABLE_MSG _T("UWM_DISABLE-{546AB065-23E2-4e2e-AA03-AD84A326A2AE}")
