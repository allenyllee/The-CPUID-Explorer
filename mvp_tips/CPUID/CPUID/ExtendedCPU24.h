#pragma once
#include "Leaves.h"
#include "afxwin.h"

// CExtendedCPU2 dialog

class CExtendedCPU24 : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU24)

public:
        CExtendedCPU24();
        virtual ~CExtendedCPU24();

// Dialog Data
        enum { IDD = IDD_CPUID_EXTENDED_2_4 };

protected:
        void Nullify(CString & s);
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
    void ShowExtendedCPU(UINT reg);
    CString GetSegment(UINT seg);
    CEdit c_EAX;
    CEdit c_EBX;
    CEdit c_ECX;
    CEdit c_EDX;
    CEdit c_ProcessorBrandSegment;
    CEdit c_ProcessorBrandName;
    CEdit c_BrandSegment2;
    CEdit c_BrandSegment3;
    CEdit c_BrandSegment4;
    CEdit c_BrandName;

};
