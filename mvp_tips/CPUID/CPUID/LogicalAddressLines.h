#pragma once

#include "Arrow.h"
// CLogicalAddressLines

class CLogicalAddressLines : public CArrow
{
        DECLARE_DYNAMIC(CLogicalAddressLines)

public:
        CLogicalAddressLines();
        virtual ~CLogicalAddressLines();

protected:
        DECLARE_MESSAGE_MAP()
        void OnPaint();
};


