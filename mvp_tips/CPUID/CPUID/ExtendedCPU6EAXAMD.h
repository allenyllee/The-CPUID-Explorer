#pragma once
#include "ExtendedCPU6AMD.h"
#include "afxwin.h"

// CExtendedCPU6EAXAMD dialog

class CExtendedCPU6EAXAMD : public CExtendedCPU6AMD
{
        DECLARE_DYNCREATE(CExtendedCPU6EAXAMD)

public:
        CExtendedCPU6EAXAMD();
        virtual ~CExtendedCPU6EAXAMD();

// Dialog Data
//        enum { IDD = IDD_CPUID_EXTENDED_6_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
};
