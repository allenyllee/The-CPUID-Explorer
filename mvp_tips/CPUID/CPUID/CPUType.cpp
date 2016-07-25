#include "stdafx.h"

#include "CPUType.h"
#include "CPUIDx86.h"
#include "CurrentProcessor.h"

/****************************************************************************
*                              CPUType::CPUType
* Effect: 
*       Constructor
****************************************************************************/

CPUType::CPUType()
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(0, &regs);
     // "Genu ineI ntel"
     // "Auth enti cAMD"
     //  EAX  EDX  ECX
     if(regs.ECX == 'letn')
        type = Intel;
     else
     if(regs.ECX == 'DMAc')
        type = AMD;
     else
        type = Unknown;
    } // CPUType::CPUType
