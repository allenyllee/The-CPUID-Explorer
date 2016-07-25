#include "stdafx.h"
#include "FormatBinary.h"

/****************************************************************************
*                                FormatBinary
* Inputs:
*       UINT n: Value to format
*       UINT w: Width to format
* Result: CString
*       n formatted as binary to w bits
****************************************************************************/

CString FormatBinary(UINT n, UINT w)
   {
    CString s;

    for(UINT i = 0; i < w; i++)
       { /* format bits */
        s = ((n & 1) ? _T("1") : _T("0")) + s;
        n >>= 1;
       } /* format bits */
    return s;
   } // FormatBinary
