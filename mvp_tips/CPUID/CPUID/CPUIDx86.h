#pragma once

typedef struct {
   ULONG EAX;
   ULONG EBX;
   ULONG ECX;
   ULONG EDX;
} CPUregs;

BOOL CDECL GetCPUID(UINT type, CPUregs * regs);
