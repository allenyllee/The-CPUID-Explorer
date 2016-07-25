#pragma once
#include "bits.h"
#include "BasicCPU1EDX.h"
#include "BasicCPU1EDXCaptionsIntel.h"

// CBasicCPU1EDXIntel dialog

class CBasicCPU1EDXIntel : public CBasicCPU1EDX
{
        DECLARE_DYNCREATE(CBasicCPU1EDXIntel)

public:
        CBasicCPU1EDXIntel();
        virtual ~CBasicCPU1EDXIntel();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EDX_INTEL };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
protected:
    CBits c_PSN;                // 18
    CBits c_DS;                 // 21
    CBits c_ACPI;               // 22
    CBits c_SS;                 // 27
    CBits c_TM;                 // 29
    CBits c_Reserved3;          // 30
    CBits c_PBE;                // 31

};
