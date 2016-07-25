#pragma once
#include "bits.h"
#include "BasicCPU4_0_31.h"


// CBasicCPU4_1 dialog

class CBasicCPU4_1 : public CBasicCPU4_0_31
{
        DECLARE_DYNCREATE(CBasicCPU4_1)

public:
        CBasicCPU4_1();
        virtual ~CBasicCPU4_1();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_4_0_31 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
        virtual BOOL OnInitDialog();
public:
    virtual BOOL OnSetActive();
};
