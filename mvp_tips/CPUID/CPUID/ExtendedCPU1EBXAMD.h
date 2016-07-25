#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU1EBXAMD dialog

class CExtendedCPU1EBXAMD : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU1EBXAMD)

public:
        CExtendedCPU1EBXAMD();
        virtual ~CExtendedCPU1EBXAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_1_EBX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
    CBits c_Reserved;
    CBits x_Reserved;
    CBits c_BrandId;
    CBits x_BrandId;
};
