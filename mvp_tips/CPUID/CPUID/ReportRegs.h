#pragma once
#include "msg.h"
#include "CurrentProcessor.h"

/****************************************************************************
*                                 UWM_EAX_IN
* Inputs:
*       WPARAM: unused
*       LPARAM: input value in EAX to CPUID
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Shows the EAX value 
****************************************************************************/

#define UWM_EAX_IN_MSG _T("UWM_EAX_IN-{D4B0824E-A936-49de-9C86-CC401C2E8D7D}")


/****************************************************************************
*                                 UWM_EAX_EBX
* Inputs:
*       WPARAM: EAX value
*       LPARAM: EBX value
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Updates the display of EAX and EBX
****************************************************************************/

#define UWM_EAX_EBX_MSG _T("UWM_EAX_EBX-{D4B0824E-A936-49de-9C86-CC401C2E8D7D}")

/****************************************************************************
*                                 UWM_ECX_EDX
* Inputs:
*       WPARAM: ECX value
*       LPARAM: EDX value
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Updates the display of ECX and EDX
****************************************************************************/

#define UWM_ECX_EDX_MSG _T("UWM_ECX_EDX-{D4B0824E-A936-49de-9C86-CC401C2E8D7D}")




DECLARE_MESSAGE(UWM_EAX_IN)
DECLARE_MESSAGE(UWM_EAX_EBX)
DECLARE_MESSAGE(UWM_ECX_EDX)

#define REPORT_REGS(id, regs) \
   {                                                              \
    AfxGetMainWnd()->SendMessage(UWM_EAX_IN, 0, (LPARAM)id);      \
    AfxGetMainWnd()->SendMessage(UWM_EAX_EBX, regs.EAX, regs.EBX);\
    AfxGetMainWnd()->SendMessage(UWM_ECX_EDX, regs.ECX, regs.EDX);\
   }

#define GetAndReport(id, regs)                        \
   {                                                  \
    CurrentProcessor.GetCPUID(id, &regs);             \
    REPORT_REGS(id, regs);                            \
   }
