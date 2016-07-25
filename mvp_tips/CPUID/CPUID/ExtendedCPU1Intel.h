#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU1 dialog

class CExtendedCPU1Intel : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU1Intel)

public:
        CExtendedCPU1Intel();
        virtual ~CExtendedCPU1Intel();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_1_INTEL };

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
    CBits c_EMT64T;
    CBits x_EMT64T;
    CBits c_ExecuteDisable;
    CBits x_ExecuteDisable;
    CBits c_SYSCALL_SYSRET;
    CBits x_SYSCALL_SYSRET;

};
