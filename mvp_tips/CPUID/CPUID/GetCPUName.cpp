#include "stdafx.h"
#include "GetCPUName.h"
#include "CurrentProcessor.h"

/****************************************************************************
*                              GetStringSegment
* Inputs:
*       UINT id: Register ID
* Result: CString
*       The string value
****************************************************************************/

static CString GetStringSegment(UINT id)
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(id, &regs);
     CStringA a((LPCSTR)&regs.EAX, 4);
     a.GetBuffer();
     a.ReleaseBuffer();
     CStringA b((LPCSTR)&regs.EBX, 4);
     b.GetBuffer();
     b.ReleaseBuffer();
     CStringA c((LPCSTR)&regs.ECX, 4);
     c.GetBuffer();
     c.ReleaseBuffer();
     CStringA d((LPCSTR)&regs.EDX, 4);
     d.GetBuffer();
     d.ReleaseBuffer();
     CString result = a + b + c + d;
     return result;
    } // GetStringSegment

/****************************************************************************
*                                 GetCPUName
* Result: CString
*       File name to use
****************************************************************************/

CString GetCPUName()
    {
     CString name;
     CPUregs regs;
     CurrentProcessor.GetCPUID(0x80000000, &regs);
     if(regs.EAX < 0x80000004)
        return _T("data");
     name = GetStringSegment(0x80000002);
     name += GetStringSegment(0x80000003);
     name += GetStringSegment(0x80000004);
     name.Trim();
     return name;
    } // GetCPUName

/****************************************************************************
*                               GetCPUTypeName
* Result: CString
*       
* Effect: 
*       The CPU Type name "GenuineIntel" or "AuthenticAMD"
****************************************************************************/

CString GetCPUTypeName()
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(0, &regs);
     
     CStringA b((LPCSTR)&regs.EBX, 4);
     CStringA c((LPCSTR)&regs.ECX, 4);
     CStringA d((LPCSTR)&regs.EDX, 4);

     CStringA name = b + d + c;
     
     return name;
    } // GetCPUTypeName
