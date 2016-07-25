#pragma once
#include "ExtendedCPU5AMD.h"
#include "afxwin.h"

// CExtendedCPU5AMD dialog

class CExtendedCPU5EDXAMD : public CExtendedCPU5AMD
{
        DECLARE_DYNCREATE(CExtendedCPU5EDXAMD)

public:
        CExtendedCPU5EDXAMD();
        virtual ~CExtendedCPU5EDXAMD();

// Dialog Data
//        enum { IDD = IDD_CPUID_EXTENDED_5_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
};
