#pragma once
#include "bits.h"
#include "BasicCPU1ECX.h"

// CBasicCPU1ECXAMD dialog

class CBasicCPU1ECXAMD : public CBasicCPU1ECX
{
        DECLARE_DYNCREATE(CBasicCPU1ECXAMD)

public:
        CBasicCPU1ECXAMD();
        virtual ~CBasicCPU1ECXAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_ECX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
protected:
public:
    virtual BOOL OnSetActive();
protected:
    CBits c_CacheLineSize;
};
