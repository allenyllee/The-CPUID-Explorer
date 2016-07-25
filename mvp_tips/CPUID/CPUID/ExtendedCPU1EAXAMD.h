#pragma once
#include "afxwin.h"
#include "BasicCPU1EAXAMD.h"

// CExtendedCPU1EAXAMD dialog

class CExtendedCPU1EAXAMD : public CBasicCPU1EAXAMD
{
        DECLARE_DYNCREATE(CExtendedCPU1EAXAMD)

public:
        CExtendedCPU1EAXAMD();
        virtual ~CExtendedCPU1EAXAMD();

// Dialog Data
//        enum { IDD = IDD_CPUID_EXTENDED_1_EAX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();
        virtual BOOL OnSetActive();
        DECLARE_MESSAGE_MAP()
};
