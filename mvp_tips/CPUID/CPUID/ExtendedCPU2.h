#pragma once
#include "ExtendedCPU24.h"
#include "afxwin.h"

// CExtendedCPU2 dialog

class CExtendedCPU2 : public CExtendedCPU24
{
        DECLARE_DYNCREATE(CExtendedCPU2)

public:
        CExtendedCPU2();
        virtual ~CExtendedCPU2();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_2_4 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:

};
