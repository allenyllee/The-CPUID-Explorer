#pragma once
#include "bits.h"
#include "Leaves.h"

// CBasicCPU1ECX dialog

class CBasicCPU1ECX : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU1ECX)

public:
        CBasicCPU1ECX() : CLeaves(0) { ASSERT(FALSE); }
        CBasicCPU1ECX(UINT idd);
        virtual ~CBasicCPU1ECX();

// Dialog Data
//        enum { IDD = IDD_CPUID_BASIC_1_ECX };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
protected:
    CBits x_SSE3;
    CBits c_SSE3;
    CBits x_CMPXCHG16B;
    CBits c_CMPXCHG16B;
    CBits x_Reserved1;
    CBits c_Reserved1;
    CBits x_Reserved2;
    CBits c_Reserved2;
    CBits x_Reserved3;
    CBits c_Reserved3;
    CBits x_Reserved5;
    CBits c_Reserved5;
    CBits x_Reserved6;
    CBits c_Reserved6;
    CBits c_Reserved6a;
public:
    virtual BOOL OnSetActive();
protected:
    CBits c_CacheLineSize;
};
