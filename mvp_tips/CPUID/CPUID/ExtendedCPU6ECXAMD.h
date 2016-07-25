#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU6ECXAMD dialog

class CExtendedCPU6ECXAMD : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU6ECXAMD)

public:
        CExtendedCPU6ECXAMD();
        virtual ~CExtendedCPU6ECXAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_6_ECX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        class CacheTLBInfo {
            public:
               CacheTLBInfo(UINT d4, UINT d3, UINT d2, UINT d1, UINT c) {
                  D31_16 = d4; D15_12 = d3; D11_8 = d2; D7_0 = d1; caption = c; }
               UINT D31_16;
               UINT D15_12;
               UINT D11_8;
               UINT D7_0;
               UINT caption;
        };
        void FormatValue(CString fmt, UINT data, CString & value, CString & caption, CString & decode);
        void FillIn(const CacheTLBInfo & info, UINT data);
        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   CBits c_31_16;
   CBits x_31_16;
   CBits e_31_16;
   CBits c_15_12;
   CBits x_15_12;
   CBits e_15_12;
   CBits c_11_8;
   CBits x_11_8;
   CBits e_11_8;
   CBits c_7_0;
   CBits x_7_0;
   CBits e_7_0;
   CStatic c_Caption;
};
