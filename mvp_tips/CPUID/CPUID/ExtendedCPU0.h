#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CExtendedCPU0 dialog

class CExtendedCPU0 : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU0)

public:
        CExtendedCPU0();
        virtual ~CExtendedCPU0();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_0 };

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
