/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 15-Feb-07 | Created change log
* 15-Feb-07 | REQ #001: 64-bit awareness
*****************************************************************************/
#if !defined(AFX_TABVIEW_H__04D55FB9_752E_4FC1_AFB9_C9E3CFBEFB9B__INCLUDED_)
#define AFX_TABVIEW_H__04D55FB9_752E_4FC1_AFB9_C9E3CFBEFB9B__INCLUDED_

#pragma once

//#include "ChildDialog.h"
#include "msg.h"

//#ifdef _DEBUG
#pragma pack (push, 1)

class CTabImageList;

typedef struct
   {
    WORD dlgVer;
    WORD signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    WORD cDlgItems;
    short x;
    short y;
    short cx;
    short cy;
   } DLGTEMPLATEEX;

#pragma pack (pop)
//#endif // _DEBUG


/****************************************************************************
*                           UMW_QUERY_GETMINMAXINFO
* Inputs:
*       WPARAM: (WPARAM)(MINMAXINFO *) The MINMAXINFO structure for this window
*       LPARAM: (LPARAM)(HWND) the window sending the message
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Queries the parent so the window will not stretch into the parent
*       area
****************************************************************************/

#define UWM_QUERY_GETMINMAXINFO_MSG _T("UWM_QUERY_GETMINMAXINFO-{F9C16269-8943-4830-BEB5-5A46A91C3145}")

/////////////////////////////////////////////////////////////////////////////
// CTabView declaration

class CTabView : public /* CCtrlView */ CTabCtrl
   {
   DECLARE_DYNCREATE (CTabView)

    public:
      CTabView();
      virtual ~CTabView();

      CTabCtrl& GetTabCtrl () const { return *(CTabCtrl*) this; }

      INT_PTR AddPage (LPCTSTR pszTitle, int nPageID, LPCTSTR pszTemplateName, CRuntimeClass * rtc);// REQ #001
      INT_PTR AddPage (LPCTSTR pszTitle, int nPageID, int nTemplateID, CRuntimeClass * rtc); // REQ #001
      INT_PTR AddPage (UINT title, int nPageID, int nTemplateID, CRuntimeClass * rtc); // REQ #001

      BOOL RemovePage (INT_PTR nIndex);                             // REQ #001
      INT_PTR GetPageCount ();                                      // REQ #001

      BOOL GetPageTitle (INT_PTR nIndex, CString& strTitle);        // REQ #001
      BOOL GetPageTitle(CWnd * wnd, CString & title);
      BOOL SetPageTitle (INT_PTR nIndex, LPCTSTR pszTitle);         // REQ #001

      int GetPageID (INT_PTR nIndex);                               // REQ #001
      int SetPageID (INT_PTR nIndex, int nPageID);                  // REQ #001

      BOOL ActivatePage (INT_PTR nIndex);                           // REQ #001
      INT_PTR GetActivePage ();                                     // REQ #001
      CWnd* GetPage (INT_PTR nIndex);                               // REQ #001

      INT_PTR GetPageIndex (int nPageID);                           // REQ #001
      void GetOriginalWindowSize(CRect & r) { r = OriginalWindowSize; }
      INT_PTR GetIndex(CWnd * wnd);                                 // REQ #001

    protected: // Data
       CTypedPtrArray<CObArray, CDialog*> m_pPages;
       CArray<HWND, HWND> m_hFocusWnd;
       CArray<int, int> m_nPageIDs;
       HCURSOR LeftCursor;
    protected: // Virtual methods
       virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
       virtual BOOL OnInitPage (INT_PTR nIndex, int nPageID);       // REQ #001
       virtual void OnActivatePage (INT_PTR nIndex, int nPageID);   // REQ #001
       virtual void OnDeactivatePage (INT_PTR nIndex, int nPageID); // REQ #001
       virtual void OnDestroyPage (INT_PTR nIndex, int nPageID);    // REQ #001
    protected: // Data
       CRect OriginalWindowSize;
    protected: // Methods
#ifdef _DEBUG
       BOOL CheckDialogTemplate (LPCTSTR pszTemplateName);
#endif // _DEBUG
       DWORD GetDialogStyle( LPCTSTR pszTemplateName);
       void ResizeDialog (INT_PTR nIndex, int cx, int cy);          // REQ #001

        //{{AFX_MSG(CTabView)
       afx_msg void OnSize (UINT nType, int cx, int cy);
       afx_msg void OnDestroy ();
       afx_msg void OnSetFocus (CWnd* pOldWnd);
       afx_msg void OnKillFocus (CWnd* pNewWnd);
       afx_msg UINT OnNcHitTest(CPoint point);
       afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
       afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
        //}}AFX_MSG
       afx_msg void OnSelChanging (NMHDR* pNMHDR, LRESULT* pResult);
       afx_msg void OnSelChange (NMHDR* pNMHDR, LRESULT* pResult);

       DECLARE_MESSAGE_MAP()
   };


/****************************************************************************
*                              UWM_TAB_RESIZING
* Inputs:
*       WPARAM: (WPARAM)(int)cx: New width of control
*       LPARAM: (LPARAM)(int)cy: New height of control
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Notifies the parent that the dialog has resized
****************************************************************************/

#define UWM_TAB_RESIZING_MSG _T("UWM_TAB_RESIZING-{6A871387-D6D9-49c6-B2C8-34B9F9B17347}")

#endif // !defined(AFX_TABVIEW_H__04D55FB9_752E_4FC1_AFB9_C9E3CFBEFB9B__INCLUDED_)
