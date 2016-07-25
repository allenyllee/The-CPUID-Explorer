#pragma once
#include "bits.h"
#include "Leaves.h"
#include "ScrollableCaptions.h"

// CBasicCPU1EDX dialog

class CScrollableCaptionsParent : public CLeaves
{
        DECLARE_DYNCREATE(CScrollableCaptionsParent)

public:
    CScrollableCaptionsParent() : CLeaves(0) { ASSERT(FALSE); }
    CScrollableCaptionsParent(UINT idd);
    virtual ~CScrollableCaptionsParent();

// Dialog Data
//enum { IDD = IDD_CPUID_BASIC_1_EDX };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnQueryCoordinates(WPARAM, LPARAM);
    BOOL CreateScroller(CRuntimeClass * rtc, UINT idd);
protected:
    CStatic c_ChildFrame;
    
    CScrollableCaptions * c_Captions;
    afx_msg void OnSize(UINT nType, int cx, int cy);
};
