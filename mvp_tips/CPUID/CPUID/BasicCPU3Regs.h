#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CBasicCPU3Regs dialog

class CBasicCPU3Regs : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU3Regs)

public:
        CBasicCPU3Regs();
        virtual ~CBasicCPU3Regs();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_3 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
    CEdit c_EAX;
    CEdit c_EBX;
    CEdit c_ECX;
    CEdit c_EDX;
    CEdit c_PSN;

};
