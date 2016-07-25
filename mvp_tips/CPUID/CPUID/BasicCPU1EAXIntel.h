#pragma once
#include "bits.h"
#include "BasicCPU1EAX.h"

// CBasicCPU1EAXIntel dialog

class CBasicCPU1EAXIntel : public CBasicCPU1EAX
{
        DECLARE_DYNCREATE(CBasicCPU1EAXIntel)

public:
        CBasicCPU1EAXIntel();
        virtual ~CBasicCPU1EAXIntel();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EAX_INTEL };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnSetActive();
public:
   virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
    CBits c_Reserved_15_14;
    CBits x_Reserved_15_14;
    CBits c_ProcessorType;
    CBits x_ProcessorType;
    CEdit c_ProcessorTypeString;
};
