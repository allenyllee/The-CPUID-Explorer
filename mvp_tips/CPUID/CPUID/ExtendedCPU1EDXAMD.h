#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"
#include "ScrollableCaptionsParent.h"

// CExtendedCPU1EDXAMD dialog

class CExtendedCPU1EDXAMD : public CScrollableCaptionsParent
{
        DECLARE_DYNCREATE(CExtendedCPU1EDXAMD)

public:
        CExtendedCPU1EDXAMD();
        virtual ~CExtendedCPU1EDXAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_1_EDX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
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

   CStatic c_ChildFrame;
   CScrollableCaptions * c_Captions;
   
   afx_msg void OnSize(UINT nType, int cx, int cy);
};
