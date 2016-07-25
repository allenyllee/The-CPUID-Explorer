#pragma once
#include "Leaves.h"


// CBasicCPU2Regs : Property page dialog

class CBasicCPU2Regs : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU2Regs)

// Constructors
public:
        CBasicCPU2Regs();
        virtual ~CBasicCPU2Regs();
// Dialog Data
        enum { IDD = IDD_CPUID_BASIC_2_REGS };

// Implementation
protected:
        virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

// Message maps
protected:
        DECLARE_MESSAGE_MAP()
protected:
           CListCtrl c_Regs2;
           void ShowDescriptor(int iter, const CString & reg, const CString & field, BYTE desc, BOOL reserved);
           void ShowInfo(int iter, const CString & name, const CString & bits, BYTE desc, const CString & text);
           void ShowInfo(int iter, const CString & name, const CString & bits, BYTE desc, const UINT id);

public:
   virtual BOOL OnSetActive();
protected:
   afx_msg void OnSize(UINT nType, int cx, int cy);
   virtual BOOL OnInitDialog();
};
