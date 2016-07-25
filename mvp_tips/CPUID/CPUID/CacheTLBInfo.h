#pragma once


// CCacheTLBInfo

#include "Block.h"

class CCacheTLBInfo : public CBlock
{
        DECLARE_DYNAMIC(CCacheTLBInfo)

public:
        CCacheTLBInfo();
        virtual ~CCacheTLBInfo();
        //void AddDescriptor(UINT id) { descriptors.Add(TextDescriptor(id)); }
        void Reset() { descriptors.SetSize(0); }
        void Add(UINT id) { descriptors.Add(TextDescriptor(id)); }
        void Add(LPCTSTR L, LPCTSTR S) { descriptors.Add(TextDescriptor(L, S)); }
protected:
        DECLARE_MESSAGE_MAP()
        class TextDescriptor { 
            public:
               TextDescriptor(UINT id) { ID = id; }
               TextDescriptor() { ID = 0; }
               TextDescriptor(LPCTSTR L, LPCTSTR S) { ID = 0; ShortDesc = S; LongDesc = L; }
               CString GetLongVersion() { CString s;
                                          if(ID == 0)
                                              return LongDesc;
                                          s.LoadString(ID);
                                          int n = s.Find(_T("\n"));
                                          if(n < 0)
                                             return s;
                                          else
                                             return s.Left(n);
               }
               CString GetShortVersion() { CString s;
                                           if(ID == 0)
                                              return ShortDesc;
                                           s.LoadString(ID);
                                           int n = s.Find(_T("\n"));
                                           if(n < 0)
                                              return s;
                                           else
                                              return s.Mid(n + 1);
               }
            protected:
               UINT ID;
               CString ShortDesc;
               CString LongDesc;
        };
        CArray<TextDescriptor, TextDescriptor&> descriptors;
        afx_msg void OnPaint();
//        afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
        virtual void QueryShowTip(CPoint pt);
};


