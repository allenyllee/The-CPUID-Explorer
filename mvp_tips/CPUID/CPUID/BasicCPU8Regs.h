#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CBasicCPU8Regs dialog

class CBasicCPU8Regs : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU8Regs)

public:
        CBasicCPU8Regs();
        virtual ~CBasicCPU8Regs();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_8 };

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
