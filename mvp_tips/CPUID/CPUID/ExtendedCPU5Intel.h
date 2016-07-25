#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CExtendedCPU5Intel dialog

class CExtendedCPU5Intel : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU5Intel)

public:
        CExtendedCPU5Intel();
        virtual ~CExtendedCPU5Intel();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_5_INTEL };

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
    CEdit c_CPUTypeName;
};
