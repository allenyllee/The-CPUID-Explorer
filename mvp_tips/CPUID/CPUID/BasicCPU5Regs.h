#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CBasicCPU5Regs dialog

class CBasicCPU5Regs : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU5Regs)

public:
        CBasicCPU5Regs();
        virtual ~CBasicCPU5Regs();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_5 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   CBits c_SmallestMonitorLineSize;
   CBits x_SmallestMonitorLineSize;
   CBits c_LargestMonitorLineSize;
   CBits x_LargestMonitorLineSize;
   CBits c_Reserved1;
   CBits x_Reserved1;
   CBits c_Reserved2;
   CBits x_Reserved2;
   CBits c_Reserved3;
   CBits x_Reserved3;
   CBits c_Reserved4;
   CBits x_Reserved4;
   CBits c_InterruptsAsBreakEvents;
   CBits x_InterruptsAsBreakEvents;
   CBits c_MWAITEnumerationSupported;
   CBits x_MWAITEnumerationSupported;
   CBits c_C0;
   CBits x_C0;
   CBits c_C1;
   CBits x_C1;
   CBits c_C2;
   CBits x_C2;
   CBits c_C3;
   CBits x_C3;
   CBits c_C4;
   CBits x_C4;
   
};
