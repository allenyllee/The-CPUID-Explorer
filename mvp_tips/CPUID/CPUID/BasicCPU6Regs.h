#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CBasicCPU6Regs dialog

class CBasicCPU6Regs : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU6Regs)

public:
        CBasicCPU6Regs();
        virtual ~CBasicCPU6Regs();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_6 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   CBits c_SensorSupported;
   CBits x_SensorSupported;
   CBits c_InterruptThresholds;
   CBits x_InterruptThresholds;
   CBits c_ACNT_MCNT;
   CBits x_ACNT_MCNT;
   CBits c_Reserved1;
   CBits c_Reserved2;
   CBits c_Reserved3;
   CBits x_Reserved1;
   CBits x_Reserved2;
   CBits x_Reserved3;
   CEdit c_EDX;
};
