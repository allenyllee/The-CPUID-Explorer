#pragma once

#include "Bits.h"
#include "BasicCPU1EDXCaptions.h"
// CBasicCPU1EDXCaptionsAMD dialog

class CBasicCPU1EDXCaptionsAMD : public CBasicCPU1EDXCaptions
{
        DECLARE_DYNCREATE(CBasicCPU1EDXCaptionsAMD)

public:
        CBasicCPU1EDXCaptionsAMD(CWnd* pParent = NULL);   // standard constructor
        virtual ~CBasicCPU1EDXCaptionsAMD();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EDX_CAPTIONS_AMD };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:
   CBits c_Reserved4;
   CBits x_Reserved4;
   CBits c_Reserved5;
   CBits x_Reserved5;
   
        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
};

