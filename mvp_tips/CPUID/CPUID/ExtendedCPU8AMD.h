#pragma once
#include "ExtendedCPU8.h"
#include "afxwin.h"

// CExtendedCPU8AMD dialog

class CExtendedCPU8AMD : public CExtendedCPU8
{
        DECLARE_DYNCREATE(CExtendedCPU8AMD)

public:
        CExtendedCPU8AMD();
        virtual ~CExtendedCPU8AMD();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_8_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
   CBits c_NC;
   CBits x_NC;
   CBits c_Reserved2;
   CBits x_Reserved2;
   CBits c_Reserved3;
   CBits x_Reserved3;
   CBits c_ApicIdCoreIdSize;
   CBits x_ApicIdCoreIdSize;
   CEdit c_ActualCores;
};
