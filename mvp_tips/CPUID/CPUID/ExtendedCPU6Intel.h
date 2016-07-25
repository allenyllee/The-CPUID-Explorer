#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU6Intel dialog

class CExtendedCPU6Intel : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU6Intel)

public:
        CExtendedCPU6Intel();
        virtual ~CExtendedCPU6Intel();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_6 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
    CEdit c_EAX;
    CEdit c_EBX;
    CEdit c_EDX;
    CEdit c_L2Decoded;
    CStatic c_CacheSizeValue;
    CBits c_CacheSize;
    CBits x_CacheSize;
    CBits c_Associativity;
    CBits x_Associativity;
    CBits c_Reserved1;
    CBits x_Reserved1;
    CBits c_LineSize;
    CBits x_LineSize;

};
