#pragma once
#include "bits.h"
#include "BasicCPU1EAX.h"

// CBasicCPU1EAXAMD dialog

class CBasicCPU1EAXAMD : public CBasicCPU1EAX
{
        DECLARE_DYNCREATE(CBasicCPU1EAXAMD)

public:
        CBasicCPU1EAXAMD();
        virtual ~CBasicCPU1EAXAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EAX_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnSetActive();
public:
   virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
    CBits c_Reserved_15_12;
    CBits x_Reserved_15_12;
};
