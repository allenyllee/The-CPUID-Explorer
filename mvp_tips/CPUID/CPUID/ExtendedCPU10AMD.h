#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CExtendedCPU10AMD dialog

class CExtendedCPU10AMD : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU10AMD)

public:
        CExtendedCPU10AMD();
        virtual ~CExtendedCPU10AMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_10_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   CEdit c_EBX;
   CEdit c_ECX;
   CEdit c_EDX;
};
