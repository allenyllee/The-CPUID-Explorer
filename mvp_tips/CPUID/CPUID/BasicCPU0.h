#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CBasicCPU0 dialog

class CBasicCPU0 : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU0)

public:
        CBasicCPU0();
        virtual ~CBasicCPU0();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_0 };

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
