#pragma once
#include "ExtendedCPU8.h"
#include "afxwin.h"

// CExtendedCPU8Intel dialog

class CExtendedCPU8Intel : public CExtendedCPU8
{
        DECLARE_DYNCREATE(CExtendedCPU8Intel)

public:
        CExtendedCPU8Intel();
        virtual ~CExtendedCPU8Intel();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_8_INTEL };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   CEdit c_ECX;
};
