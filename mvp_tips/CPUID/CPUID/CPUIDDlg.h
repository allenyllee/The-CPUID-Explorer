// CPUIDDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "TabView.h"
#include "afxwin.h"

// CCPUIDDlg dialog
class CCPUIDDlg : public CDialog
{
// Construction
public:
        CCPUIDDlg(CWnd* pParent = NULL);        // standard constructor

// Dialog Data
        enum { IDD = IDD_CPUID_DIALOG };

        protected:
        virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support


// Implementation
protected:
        HICON m_hIcon;
        CFont font;
        CString caption;
        
        // Generated message map functions
        virtual BOOL OnInitDialog();
        afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
        afx_msg void OnPaint();
        afx_msg HCURSOR OnQueryDragIcon();
        afx_msg LRESULT OnEAXIn(WPARAM, LPARAM);
        afx_msg LRESULT OnEAXEBX(WPARAM, LPARAM);
        afx_msg LRESULT OnECXEDX(WPARAM, LPARAM);
        DECLARE_MESSAGE_MAP()
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnClose();
    afx_msg UINT OnNcHitTest(CPoint point);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedCPU(UINT id);
    afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
    afx_msg void OnBnClickedToClip();
    void SelectAffinity();
    void AddAllPages();
    void RemoveAllPages();
    void EnableAffinity();
    void RedoPages();
    
protected:
    CTabView c_Tabs;
protected:
    CButton c_CPU0;
    CButton c_CPU1;
    CButton c_CPU2;
    CButton c_CPU3;
    CButton c_CPU4;
    CButton c_CPU5;
    CButton c_CPU6;
    CButton c_CPU7;

    CButton x_CPU;
    
    CEdit c_EAXIn;
    CEdit c_EAX;
    CEdit c_EBX;
    CEdit c_ECX;
    CEdit c_EDX;
    CButton c_ToClip;
};
