#include "stdafx.h"
#include "ColorSet.h"

static const COLORREF initcolors[] = {
   RGB(255, 179, 102),   // Light orange
   RGB(255, 255,   0),   // yellow
   RGB(177, 255, 100),   // Light green
   RGB(255, 128, 192),   // light magenta
   RGB(  0, 255, 255),   // Cyan
   RGB(255, 166, 166),   // pink
   RGB(176,  98, 255),   // light purple
   RGB(255, 255, 128),   // Light yellow
   RGB(128, 128, 255),   // steel blue
};

ColorSet colors(initcolors, sizeof(initcolors)/sizeof(initcolors[0]));

