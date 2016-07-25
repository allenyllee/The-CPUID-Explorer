#pragma once

#include "Bits.h"
#include "BasicCPU1EDXCaptions.h"
// CBasicCPU1EDXCaptions dialog

class CBasicCPU1EDXCaptionsIntel : public CBasicCPU1EDXCaptions
{
        DECLARE_DYNCREATE(CBasicCPU1EDXCaptionsIntel)

public:
        CBasicCPU1EDXCaptionsIntel(CWnd* pParent = NULL);   // standard constructor
        virtual ~CBasicCPU1EDXCaptionsIntel();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EDX_CAPTIONS_INTEL };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:
        CBits x_PSN;            // 18
        CBits c_PSN;            // 18
        CBits x_DS;             // 21
        CBits c_DS;             // 21
        CBits x_ACPI;           // 22
        CBits c_ACPI;           // 22
        CBits x_SS;             // 27
        CBits c_SS;             // 27
        CBits x_TM;             // 29
        CBits c_TM;             // 29
        CBits x_PBE;            // 31
        CBits c_PBE;

        DECLARE_MESSAGE_MAP()
        virtual BOOL OnInitDialog();
};

