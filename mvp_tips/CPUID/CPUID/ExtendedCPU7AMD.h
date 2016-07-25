#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU7AMD dialog

class CExtendedCPU7AMD : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU7AMD)

public:
        CExtendedCPU7AMD();
        virtual ~CExtendedCPU7AMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_7_AMD };

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
    CBits c_TS;
    CBits x_TS;
    CBits c_FID;
    CBits x_FID;
    CBits c_VID;
    CBits x_VID;
    CBits c_TTP;
    CBits x_TTP;
    CBits c_TM;
    CBits x_TM;
    CBits c_STC;
    CBits x_STC;
    CBits c_Reserved1;
    CBits x_Reserved1;
    CBits c_TSCInvariant;
    CBits x_TSCInvariant;
    CBits c_Reserved2;
    CBits x_Reserved2;
};
