#include "stdafx.h"

#include "resource.h"
#include "ErrorString.h"


/****************************************************************************
*                                 ErrorString
* Inputs:
*       DWORD err: Error code
* Result: CString
*       String message
****************************************************************************/

CString ErrorString(DWORD err)
    {
     CString Error;
     LPTSTR s;
     if(::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			err,
			0,
			(LPTSTR)&s,
			0,
			NULL) == 0)
	{ /* failed */
	 // Unknown error code %08x (%d)
	 CString fmt;
	 CString t;
	 fmt.LoadString(IDS_UNKNOWN_ERROR);
	 t.Format(fmt, err, LOWORD(err));
	 Error = t;
	} /* failed */
     else
	{ /* success */
	 LPTSTR p = _tcschr(s, _T('\r'));
	 if(p != NULL)
	    { /* lose CRLF */
	     *p = _T('\0');
	    } /* lose CRLF */
	 Error = s;
	 ::LocalFree(s);
	} /* success */
     return Error;
    } // ErrorString
