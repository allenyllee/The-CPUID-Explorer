#pragma once
#include "bits.h"
#include "Leaves.h"


// CBasicCPU1EAX dialog

class CBasicCPU1EAX : public CLeaves
{
        DECLARE_DYNCREATE(CBasicCPU1EAX)

public:
        CBasicCPU1EAX() : CLeaves(0) { ASSERT(FALSE); }
        CBasicCPU1EAX(UINT idd);
        virtual ~CBasicCPU1EAX();

// Dialog Data

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnSetActive();
public:
   virtual BOOL OnInitDialog();

        DECLARE_MESSAGE_MAP()
    CBits c_Reserved_31_28;
    CBits x_Reserved_31_28;
    CBits c_ExtendedFamilyID;
    CBits x_ExtendedFamilyID;
    CBits c_ExtendedModelID;
    CBits x_ExtendedModelID;
    CBits c_ProcessorType;
    CBits x_ProcessorType;
    CBits c_FamilyID;
    CBits x_FamilyID;
    CBits c_Model;
    CBits x_Model;
    CBits c_SteppingID;
    CBits x_SteppingID;
    CStatic c_ExtendedFamily1Line;
    CStatic c_ExtendedFamily2Line;
    CStatic c_ExtendedFamily3Line;
    CEdit c_ComputedFamilyID;
    CStatic x_ComputedFamilyID;
    CStatic c_ComputedModel1Line;
    CStatic c_ComputedModel2Line;
    CEdit c_ComputedModel;
    CStatic x_ComputedModel;
};
