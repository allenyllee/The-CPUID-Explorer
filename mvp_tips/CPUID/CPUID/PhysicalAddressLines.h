#pragma once

#include "Arrow.h"
// CPhysicalAddressLines

class CPhysicalAddressLines : public CArrow
{
        DECLARE_DYNAMIC(CPhysicalAddressLines)

public:
        CPhysicalAddressLines();
        virtual ~CPhysicalAddressLines();

protected:
        DECLARE_MESSAGE_MAP()
        void OnPaint();
};


