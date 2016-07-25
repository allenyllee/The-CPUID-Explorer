#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CExtendedCPU5 dialog

class CExtendedCPU5 : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU5)

public:
        CExtendedCPU5();
        virtual ~CExtendedCPU5();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_5 };

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
