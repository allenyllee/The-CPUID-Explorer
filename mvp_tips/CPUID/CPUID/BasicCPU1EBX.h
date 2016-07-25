#pragma once
#include "bits.h"
#include "Leaves.h"


// CBasicCPU1EBX dialog

class CBasicCPU1EBX : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU1EBX)

public:
        CBasicCPU1EBX();
        virtual ~CBasicCPU1EBX();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EBX };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
protected:
    CBits x_InitialAPICID;
    CBits c_InitialAPICID;
    CBits c_CLFLUSHLineSize;
    CBits x_CLFLUSHLineSize;
    CBits c_LogicalProcessors;
    CBits x_LogicalProcessors;
    CBits x_BrandIndex;
    CBits c_BrandIndex;
    CBits c_CacheLineSize;
    CEdit c_BrandIndexName;
public:
    virtual BOOL OnSetActive();
};
