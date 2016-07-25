#pragma once
#include "Leaves.h"
#include "afxwin.h"
#include "Bits.h"

// CExtendedCPU8 dialog

class CExtendedCPU8 : public CLeaves
{
        DECLARE_DYNCREATE(CExtendedCPU8)

public:
        CExtendedCPU8() : CLeaves(0) { ASSERT(FALSE);}
        CExtendedCPU8(UINT idd);
        virtual ~CExtendedCPU8();

// Dialog Data
//        enum { IDD = IDD_CPUID_EXTENDED_8 };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar);

        DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnSetActive();
protected:
#ifdef _DEBUG_PRINTOUT
    CSpinButtonCtrl c_SpinPhysical;
#endif
    CEdit c_EBX;
    CEdit c_EDX;
    CBits c_PhysicalAddressBits;
    CBits x_PhysicalAddressBits;
    CBits c_VirtualAddressBits;
    CBits x_VirtualAddressBits;
    CBits c_Reserved;
    CBits x_Reserved;
    CStatic c_VirtualValue;
    CStatic c_PhysicalValue;

};
