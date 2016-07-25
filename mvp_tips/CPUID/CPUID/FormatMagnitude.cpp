#include "stdafx.h"
#include "FormatMagnitude.h"

const static ULONGLONG kilo = 1024;
const static ULONGLONG mega = kilo * 1024;
const static ULONGLONG giga = mega * 1024;
const static ULONGLONG tera = giga * 1024;
const static ULONGLONG peta = tera * 1024;
const static ULONGLONG exa  = peta * 1024;

/****************************************************************************
*                               FormatMagnitude
* Inputs:
*       UINT AddressBits:
* Result: CString
*       Scaled value
****************************************************************************/

CString FormatMagnitude(UINT AddressBits)
    {
     CString s;

     ULONGLONG AddressMax = ((LONGLONG)1) << AddressBits;

     if(AddressBits == 64)
        s.Format(_T("%I64dEB"), ((((ULONGLONG)1) << 63) / exa) * 2);
     else
        s = FormatScaled(AddressMax);
     return s;
    } // CExtendedCPU8::FormatMagnitude


/****************************************************************************
*                                FormatScaled
* Inputs:
*       ULONGLONG AddressMax: Maximum value
* Result: CString
*       The value expressed in "MB", "KB", etc.
****************************************************************************/

CString FormatScaled(ULONGLONG AddressMax)
    {
     CString s;

     if(AddressMax / exa > 0)
        s.Format(_T("%I64d EB"), AddressMax / exa);
     else
     if(AddressMax / peta > 0)
        s.Format(_T("%I64d PB"), AddressMax / peta);
     else
     if(AddressMax / tera > 0)
        s.Format(_T("%I64d TB"), AddressMax / tera);
     else
     if(AddressMax / giga > 0)
        s.Format(_T("%I64d GB"), AddressMax / giga);
     else
     if(AddressMax / mega > 0)
        s.Format(_T("%I64d MB"), AddressMax / mega);
     else
     if(AddressMax / kilo > 0)
        s.Format(_T("%I64d KB"), AddressMax / kilo);
     else
        s.Format(_T("%I64d B"), AddressMax);

     return s;
    } // FormatScaled
