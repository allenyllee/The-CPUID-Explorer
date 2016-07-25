#pragma once


// CCPUIDBasic1Captions dialog

class CCPUIDBasic1Captions : public CDialog
{
        DECLARE_DYNAMIC(CCPUIDBasic1Captions)

public:
        CCPUIDBasic1Captions(CWnd* pParent = NULL);   // standard constructor
        virtual ~CCPUIDBasic1Captions();

// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_1_EDX_CAPTIONS };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
public:
    DECLARE_MESSAGE_MAP()
};
