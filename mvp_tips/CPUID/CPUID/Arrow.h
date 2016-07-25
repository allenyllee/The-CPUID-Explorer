#pragma once

#include "Block.h"
// CArrow

class CArrow : public CBlock
{
        DECLARE_DYNAMIC(CArrow)

public:
        CArrow();
        virtual ~CArrow();
        typedef enum  { LEFT=0, RIGHT } Direction;
        void SetDirection(Direction d);
protected:
        CRgn Rgn;
        void CreateArrowPath(CDC & dc);
        virtual void QueryShowTip(CPoint pt);
        double headpercent;
        double barpercent;
        afx_msg void OnPaint();
        Direction dir;
        DECLARE_MESSAGE_MAP()
};


