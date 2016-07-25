#pragma once
#include "bits.h"
#include "ScrollableCaptionsParent.h"
#include "BasicCPU1EDXCaptions.h"

// CBasicCPU1EDX dialog

class CBasicCPU1EDX : public CScrollableCaptionsParent
{
        DECLARE_DYNCREATE(CBasicCPU1EDX)

public:
    CBasicCPU1EDX() : CScrollableCaptionsParent(0) { ASSERT(FALSE); }
    CBasicCPU1EDX(UINT idd);
    virtual ~CBasicCPU1EDX();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EDX };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
protected:
    CBits c_FPU;                // 0
    CBits c_VME;                // 1
    CBits c_DE;                 // 2
    CBits c_PSE;                // 3
    CBits c_TSC;                // 4
    CBits c_MSR;                // 5
    CBits c_PAE;                // 6
    CBits c_MCE;                // 7
    CBits c_CX8;                // 8
    CBits c_APIC;               // 9
    CBits c_Reserved1;          // 10
    CBits c_SEP;                // 11
    CBits c_MTRR;               // 12
    CBits c_PGE;                // 13
    CBits c_MCA;                // 14
    CBits c_CMOV;               // 15
    CBits c_PAT;                // 16
    CBits c_PSE36;              // 17
    CBits c_CFLSH;              // 19
    CBits c_Reserved2;          // 20 (Intel) 20..22 (AMD)
    CBits c_MMX;                // 23
    CBits c_FXSR;               // 24
    CBits c_SSE;                // 25
    CBits c_SSE2;               // 26
    CBits c_HTT;                // 28
    CBits c_Reserved3;          // 30 (Intel) 31..29 (AMD)
};
