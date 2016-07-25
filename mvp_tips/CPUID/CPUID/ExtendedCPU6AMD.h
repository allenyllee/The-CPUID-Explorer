#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU6AMD dialog

class CExtendedCPU6AMD : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU6AMD)

public:
    CExtendedCPU6AMD() : CLeaves(0) { ASSERT(FALSE); }
        CExtendedCPU6AMD(UINT idd);
        virtual ~CExtendedCPU6AMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_6_EABX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        class CacheTLBInfo {
            public:
               CacheTLBInfo(UINT d4, UINT d3, UINT d2, UINT d1, UINT c) {
                  D31_28 = d4; D27_16 = d3; D15_12 = d2; D11_0 = d1; caption = c; }
               UINT D31_28;
               UINT D27_16;
               UINT D15_12;
               UINT D11_0;
               UINT caption;
        };
        void FormatValue(CString fmt, UINT data, CString & value, CString & caption, CString & decode);
        void FillIn(const CacheTLBInfo & info, UINT data);
        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   CBits c_31_28;
   CBits x_31_28;
   CBits e_31_28;
   CBits c_27_16;
   CBits x_27_16;
   CBits e_27_16;
   CBits c_15_12;
   CBits x_15_12;
   CBits e_15_12;
   CBits c_11_0;
   CBits x_11_0;
   CBits e_11_0;
   CStatic c_Caption;
};
