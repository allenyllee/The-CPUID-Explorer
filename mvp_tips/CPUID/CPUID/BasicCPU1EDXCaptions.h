#pragma once

#include "Bits.h"
#include "ScrollableCaptions.h"
// CBasicCPU1EDXCaptions dialog

class CBasicCPU1EDXCaptions : public CScrollableCaptions
{
        DECLARE_DYNCREATE(CBasicCPU1EDXCaptions)

public:
        CBasicCPU1EDXCaptions() { ASSERT(FALSE); }
        CBasicCPU1EDXCaptions(UINT id, CWnd* pParent = NULL);   // standard constructor
        virtual ~CBasicCPU1EDXCaptions();

// Dialog Data
//enum { IDD = IDD_CPUID_BASIC_1_EDX_CAPTIONS };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:
        CBits x_FPU;            // 0
        CBits c_FPU;            // 0
        CBits x_VME;            // 1
        CBits c_VME;            // 1
        CBits x_DE;             // 2
        CBits c_DE;             // 2
        CBits x_PSE;            // 3
        CBits c_PSE;            // 3
        CBits x_TSC;            // 4
        CBits c_TSC;            // 4
        CBits x_MSR;            // 5
        CBits c_MSR;            // 5
        CBits x_PAE;            // 6
        CBits c_PAE;            // 6
        CBits x_MCE;            // 7
        CBits c_MCE;            // 7
        CBits x_CX8;            // 8
        CBits c_CX8;            // 8
        CBits x_APIC;           // 9
        CBits c_APIC;           // 9
        CBits x_Reserved1;      // 10
        CBits c_Reserved1;      // 10
        CBits x_SEP;            // 11
        CBits c_SEP;            // 11
        CBits x_MTRR;           // 12
        CBits c_MTRR;           // 12
        CBits x_PGE;            // 13
        CBits c_PGE;            // 13
        CBits x_MCA;            // 14
        CBits c_MCA;            // 14
        CBits x_CMOV;           // 15
        CBits c_CMOV;           // 15
        CBits x_PAT;            // 16
        CBits c_PAT;            // 16
        CBits x_PSE36;          // 17
        CBits c_PSE36;          // 17
        CBits x_PSN;            // 18
        CBits c_PSN;            // 18
        CBits x_CFLSH;          // 19
        CBits c_CFLSH;          // 19
        CBits x_Reserved2;      // 20
        CBits c_Reserved2;      // 20
        CBits x_MMX;            // 23
        CBits c_MMX;            // 23
        CBits x_FXSR;           // 24
        CBits c_FXSR;           // 24
        CBits x_SSE;            // 25
        CBits c_SSE;            // 25
        CBits x_SSE2;           // 26
        CBits c_SSE2;           // 26
        CBits x_HTT;            // 28
        CBits c_HTT;            // 28
        CBits x_Reserved3;      // 30
        CBits c_Reserved3;      // 30

        DECLARE_MESSAGE_MAP()

    virtual BOOL OnInitDialog();
};

