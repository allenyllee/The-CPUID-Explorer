#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CBasicCPU9Regs dialog

class CBasicCPU9Regs : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU9Regs)

public:
        CBasicCPU9Regs();
        virtual ~CBasicCPU9Regs();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_9 };

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
};
