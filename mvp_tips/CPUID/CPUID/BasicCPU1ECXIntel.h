#pragma once
#include "bits.h"
#include "BasicCPU1ECX.h"

// CBasicCPU1ECX dialog

class CBasicCPU1ECXIntel : public CBasicCPU1ECX
{
        DECLARE_DYNCREATE(CBasicCPU1ECXIntel)

public:
        CBasicCPU1ECXIntel();
        virtual ~CBasicCPU1ECXIntel();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_ECX_INTEL };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
protected:
    CBits c_MWAIT;
    CBits x_MWAIT;
    CBits c_CPL;
    CBits x_CPL;
    CBits x_VMX;
    CBits c_VMX;
    CBits x_EST;
    CBits c_EST;
    CBits x_TM2;
    CBits c_TM2;
    CBits x_L1;
    CBits c_L1;
    CBits x_Reserved4;
    CBits c_Reserved4;
    CBits c_XPTR;
    CBits x_XPTR;
public:
    virtual BOOL OnSetActive();
protected:
    CBits c_CacheLineSize;
};
