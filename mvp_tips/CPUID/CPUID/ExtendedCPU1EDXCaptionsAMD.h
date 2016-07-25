#pragma once

#include "Bits.h"
#include "ScrollableCaptions.h"
// CExtendedCPU1EDXCaptions dialog

class CExtendedCPU1EDXCaptionsAMD : public CScrollableCaptions
{
        DECLARE_DYNCREATE(CExtendedCPU1EDXCaptionsAMD)

public:
        CExtendedCPU1EDXCaptionsAMD(CWnd* pParent = NULL);   // standard constructor
        virtual ~CExtendedCPU1EDXCaptionsAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_1_EDX_CAPTIONS_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:
   CBits c_FPU;            // 0
   CBits c_VME;            // 1
   CBits c_DE;             // 2
   CBits c_PSE;            // 3
   CBits c_TSC;            // 4
   CBits c_MSR;            // 5
   CBits c_PAE;            // 6
   CBits c_MCE;            // 7
   CBits c_CMPXCHG8B;      // 8
   CBits c_APIC;           // 9
   CBits c_Reserved1;      // 10
   CBits c_SYSCALL_SYSRET; // 11
   CBits c_MTRR;           // 12
   CBits c_PGE;            // 13
   CBits c_MCA;            // 14
   CBits c_CMOV;           // 15
   CBits c_PAT;            // 16
   CBits c_PSE36;          // 17
   CBits c_Reserved2;      // 19..18
   CBits c_ExecuteDisable; // 20
   CBits c_Reserved3;      // 21
   CBits c_MMXExt;         // 22
   CBits c_MMX;            // 23
   CBits c_FXSR;           // 24
   CBits c_FFXSR;          // 25
   CBits c_Reserved4;      // 26
   CBits c_RDTSCP;         // 27
   CBits c_Reserved5;      // 28
   CBits c_LM;             // 29
   CBits c_ThreeDNowExt;   // 30
   CBits c_ThreeDNow;      // 31

   CBits x_FPU;            // 0
   CBits x_VME;            // 1
   CBits x_DE;             // 2
   CBits x_PSE;            // 3
   CBits x_TSC;            // 4
   CBits x_MSR;            // 5
   CBits x_PAE;            // 6
   CBits x_MCE;            // 7
   CBits x_CMPXCHG8B;      // 8
   CBits x_APIC;           // 9
   CBits x_Reserved1;      // 10
   CBits x_SYSCALL_SYSRET; // 11
   CBits x_MTRR;           // 12
   CBits x_PGE;            // 13
   CBits x_MCA;            // 14
   CBits x_CMOV;           // 15
   CBits x_PAT;            // 16
   CBits x_PSE36;          // 17
   CBits x_Reserved2;      // 19..18
   CBits x_ExecuteDisable; // 20
   CBits x_Reserved3;      // 21
   CBits x_MMXExt;         // 22
   CBits x_MMX;            // 23
   CBits x_FXSR;           // 24
   CBits x_FFXSR;          // 25
   CBits x_Reserved4;      // 26
   CBits x_RDTSCP;         // 27
   CBits x_Reserved5;      // 28
   CBits x_LM;             // 29
   CBits x_ThreeDNowExt;   // 30
   CBits x_ThreeDNow;      // 31

        DECLARE_MESSAGE_MAP()
        virtual BOOL OnInitDialog();
};

