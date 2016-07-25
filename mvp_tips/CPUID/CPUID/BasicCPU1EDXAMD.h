#pragma once
#include "bits.h"
#include "BasicCPU1EDX.h"
#include "BasicCPU1EDXCaptionsAMD.h"

// CBasicCPU1EDX dialog

class CBasicCPU1EDXAMD : public CBasicCPU1EDX
{
        DECLARE_DYNCREATE(CBasicCPU1EDXAMD)

public:
        CBasicCPU1EDXAMD();
        virtual ~CBasicCPU1EDXAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EDX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
protected:
    CBits c_Reserved5;          // 18
    CBits c_Reserved4;          // 27
};
