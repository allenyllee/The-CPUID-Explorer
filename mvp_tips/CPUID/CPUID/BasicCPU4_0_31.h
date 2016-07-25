#pragma once
#include "bits.h"
#include "Leaves.h"
#include "CPUIDRegs.h"
#include "CPUIDx86.h"

// CBasicCPU4_1_4 dialog

class CBasicCPU4_0_31 : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU4_0_31)

public:
        CBasicCPU4_0_31();
        virtual ~CBasicCPU4_0_31();
        static BOOL GetCacheParameters(UINT L, CPUregs * regs);
// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_4_0_31 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        void ShowCacheParameters(UINT L);
        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
    CPUregs regs;

protected:
// EAX:
   CBits c_CacheType;
   CBits x_CacheType;
   CEdit c_CacheTypeValue;
   CBits c_CacheLevel;
   CBits x_CacheLevel;
   CBits c_SelfInitializing;
   CBits x_SelfInitializing;
   CBits c_FullyAssociative;
   CBits x_FullyAssociative;
   CBits c_Reserved;
   CBits x_Reserved;
   CBits c_ThreadsSharing;
   CBits x_ThreadsSharing;
   CStatic c_ThreadsSharingValue;
   CBits c_CoresPerPackage;
   CBits x_CoresPerPackage;
   CStatic c_CoresPerPackageValue;
// EBX:
   CBits c_SystemCoherencyLineSize;
   CBits x_SystemCoherencyLineSize;
   CStatic c_SystemCoherencyLineSizeValue;
   CBits c_PhysicalLinePartitions;
   CBits x_PhysicalLinePartitions;
   CStatic c_PhysicalLinePartitionsValue;
   CBits c_WaysOfAssociativity;
   CBits x_WaysOfAssociativity;
   CStatic c_WaysOfAssociativityValue;
// ECX:
   CBits c_NumberOfSets;
   CBits x_NumberOfSets;
   CStatic c_NumberOfSetsValue;
public:
    virtual BOOL OnSetActive();
};
