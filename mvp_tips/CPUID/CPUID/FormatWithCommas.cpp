#include "stdafx.h"
#include "FormatWithCommas.h"


/****************************************************************************
*                              FormatWithCommas
* Inputs:
*       UINT n: Value to format
* Result: CString
*       value formatted with commas
****************************************************************************/

CString FormatWithCommas(UINT n)
    {
     CString s;
     s.Format(_T("%d"), n);

     NUMBERFMT NumberFormat;
     NumberFormat.NumDigits = 0;
     NumberFormat.LeadingZero = 1;
     //--------------------------------
     // TODO: support indic grouping
     NumberFormat.Grouping = 3;
     //--------------------------------
     NumberFormat.lpDecimalSep = _T("."); // not actually used, doesn't need to be localized
     //--------------------------------
     // LOCALE_SMONTHOUSANDSEP
     CString smonthousandsep_data;
     LCID lcid = LOCALE_SYSTEM_DEFAULT;
     { /* get LOCALE_SMONTHOUSANDSEP */
      LPTSTR p = smonthousandsep_data.GetBuffer(5);
      VERIFY(::GetLocaleInfo(lcid, LOCALE_SMONTHOUSANDSEP, p, 5));
      smonthousandsep_data.ReleaseBuffer();
     } /* get LOCALE_SMONTHOUSANDSEP */
     NumberFormat.lpThousandSep = (LPTSTR)(LPCTSTR)smonthousandsep_data;
     //--------------------------------
     NumberFormat.NegativeOrder = 0;
     // LOCALE_IPOSSIGNPOSN
     VERIFY(::GetLocaleInfo(lcid, LOCALE_IPOSSIGNPOSN | LOCALE_RETURN_NUMBER, (LPTSTR)&NumberFormat.NegativeOrder, sizeof(DWORD)));
     //--------------------------------

     CString Number;
     { /* GetNumberFormat */
      int length = ::GetNumberFormat(lcid, 0, s, &NumberFormat, NULL, 0);
      if(length == 0)
         { /* error */
          DWORD err = ::GetLastError();
          ASSERT(FALSE);
          return s;
         } /* error */
      else
         { /* valid length */
          LPTSTR p = Number.GetBuffer(length);
          if(::GetNumberFormat(lcid, 0, s, &NumberFormat, p, length) == 0)
             { /* failed */
              DWORD err = ::GetLastError();
              Number.ReleaseBuffer();
              ASSERT(FALSE);
              return s;
             } /* failed */
          Number.ReleaseBuffer();
         } /* valid length */
     } /* GetNumberFormat */

     return Number;
    } // FormatWithCommas
