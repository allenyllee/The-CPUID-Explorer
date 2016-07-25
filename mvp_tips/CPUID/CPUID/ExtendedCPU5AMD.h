#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU5AMD dialog

class CExtendedCPU5AMD : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU5AMD)

public:
    CExtendedCPU5AMD() : CLeaves(0) { ASSERT(FALSE); }
        CExtendedCPU5AMD(UINT idd);
        virtual ~CExtendedCPU5AMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_5_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        class CacheTLBInfo {
            public:
               CacheTLBInfo(UINT d4, UINT d3, UINT d2, UINT d1, UINT c) {
                  D31_24 = d4; D23_16 = d3; D15_8 = d2; D7_0 = d1; caption = c; }
               UINT D31_24;
               UINT D23_16;
               UINT D15_8;
               UINT D7_0;
               UINT caption;
        };
        void FormatValue(CString fmt, BYTE data, CString & value, CString & caption, CString & decode);
        void FillIn(const CacheTLBInfo & info, UINT data);
        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   CBits c_31_24;
   CBits x_31_24;
   CBits e_31_24;
   CBits c_23_16;
   CBits x_23_16;
   CBits e_23_16;
   CBits c_15_8;
   CBits x_15_8;
   CBits e_15_8;
   CBits c_7_0;
   CBits x_7_0;
   CBits e_7_0;
   CStatic c_Caption;
};
