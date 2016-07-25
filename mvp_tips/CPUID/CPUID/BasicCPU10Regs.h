#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CBasicCPU10Regs dialog

class CBasicCPU10Regs : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU10Regs)

public:
        CBasicCPU10Regs();
        virtual ~CBasicCPU10Regs();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_10 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   // EAX
   CBits c_VersionID;
   CBits x_VersionID;
   CBits c_GPCounters;
   CBits x_GPCounters;
   CBits c_GPCounterWidth;
   CBits x_GPCounterWidth;
   CBits c_EBXVectorLength;
   CBits x_EBXVectorLength;
   // EBX
   CBits c_CoreCycleNA;
   CBits x_CoreCycleNA;
   CBits c_InstructionRetiredNA;
   CBits x_InstructionRetiredNA;
   CBits c_ReferenceCyclesNA;
   CBits x_ReferenceCyclesNA;
   CBits c_CacheReferenceNA;
   CBits x_CacheReferenceNA;
   CBits c_CacheMissNA;
   CBits x_CacheMissNA;
   CBits c_BranchRetiredNA;
   CBits x_BranchRetiredNA;
   CBits c_BranchMispredictNA;
   CBits x_BranchMispredictNA;
   CBits c_Reserved1;
   CBits x_Reserved1;
   // ECX:
   CEdit c_ECX;
   // EDX:
   CBits c_FixedFunctionCounters;
   CBits x_FixedFunctionCounters;
   CBits c_CounterBitWidth;
   CBits x_CounterBitWidth;
   CBits c_Reserved2;
   CBits x_Reserved2;
};
