#pragma once

#include "Block.h"
// CCPUCoreRegion

class CCPUCoreRegion : public CBlock
{
        DECLARE_DYNAMIC(CCPUCoreRegion)

public:
        CCPUCoreRegion();
        virtual ~CCPUCoreRegion();
protected:
        DECLARE_MESSAGE_MAP()
        int ComputeNProcs();
        virtual void QueryShowTip(CPoint pt);
        afx_msg void OnPaint();
};


