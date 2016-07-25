#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CBasicCPU7Regs dialog

class CBasicCPU7Regs : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU7Regs)

public:
        CBasicCPU7Regs();
        virtual ~CBasicCPU7Regs();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_7 };

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
