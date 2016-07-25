#include "stdafx.h"
#include "CPUIDx86.h"


/****************************************************************************
*                                  GetCPUID
* Inputs:
*       UINT code: Code to set
*       CPUregs * regs: Register set
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Issues a CPUID instruction
* Notes:
*       The INPUT value in regs->ECX is always loaded into ECX, although
*       this only has meaning for the CPUID(4) call
****************************************************************************/

BOOL CDECL GetCPUID(UINT code, CPUregs * regs)
    {
#if 0    // do not bother to check for now
#if defined(_M_IX86) && !defined(_WIN64)  // the following code applies only to 32-bit x86 systems
#define EFLAGS_CP 0x00200000
     DWORD flags;
     _asm {
        pushfd
        or DWORD PTR[ESP], EFLAGS_CP  // Set CP bit
        popfd 
        pushfd
        pop eax
        mov flags, eax
     }

     if(!(flags & EFLAGS_CP))
        { /* cannot set it */
         return FALSE;
        } /* cannot set it */
#endif // x86 && Win64
#endif // omitting this for now

     DWORD EAXval;
     DWORD EBXval;
     DWORD ECXval;
     DWORD EDXval;

     // This is always set, but it is only interesting for the
     // CPUID(4) value
     ECXval = regs->ECX;

#if defined(_M_IX86) && !defined(_WIN64)
     __asm {
        mov eax, code;
        mov ecx, ECXval;
        CPUID;
        mov EAXval, EAX;
        mov EBXval, EBX;
        mov ECXval, ECX;
        mov EDXval, EDX;
     }

     regs->EAX = EAXval;
     regs->EBX = EBXval;
     regs->ECX = ECXval;
     regs->EDX = EDXval;
     return TRUE;
#else
#error "64-bit mode not currently supported for CPUID"
     return FALSE;
#endif
    } // GetCPUID
