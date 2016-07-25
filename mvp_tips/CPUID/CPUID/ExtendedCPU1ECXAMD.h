#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU1ECXAMD dialog

class CExtendedCPU1ECXAMD : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU1ECXAMD)

public:
        CExtendedCPU1ECXAMD();
        virtual ~CExtendedCPU1ECXAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_1_ECX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
    CEdit c_EAX;
    CEdit c_EBX;
    CBits c_Reserved1;
    CBits x_Reserved1;
    CBits c_Reserved2;
    CBits x_Reserved2;
    CBits c_Reserved3;
    CBits x_Reserved3;
    CBits c_Reserved4;
    CBits x_Reserved4;
    CBits c_Reserved5;
    CBits x_Reserved5;
    CBits c_LAHF_SAHF;
    CBits x_LAHF_SAHF;
    CBits c_LM;
    CBits x_LM;
    CBits c_ExecuteDisable;
    CBits x_ExecuteDisable;
    CBits c_SYSCALL_SYSRET;
    CBits x_SYSCALL_SYSRET;
    CBits c_CmpLegacy;
    CBits x_CmpLegacy;
    CBits c_SVM;
    CBits x_SVM;
    CBits c_AltMovCr8;
    CBits x_AltMovCr8;
    CBits c_Reserved6;
    CBits x_Reserved6;
};
