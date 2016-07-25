#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CExtendedCPU7Intel dialog

class CExtendedCPU7Intel : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU7Intel)

public:
        CExtendedCPU7Intel();
        virtual ~CExtendedCPU7Intel();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_7_INTEL };

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
