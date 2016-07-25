#pragma once
#include "CPUIDx86.h"

class Specs {
    public:
       BOOL Read();
       BOOL IsEmpty() { return values.GetSize() == 0; }
       void Close();
       BOOL GetCPUID(UINT n, CPUregs * regs);
       void Dump();
    protected:
       
       //****************************************************************
       class SyntaxError : public CException {
           public:
              SyntaxError(UINT n) { error = n;}
              CString GetMessage() {
                 CString s;
                 s.LoadString(error);
                 return s;
              }
           protected:
              UINT error;
       };

       //****************************************************************
       class CPUIDinfo {
           public:
              CPUIDinfo() { EAX = 0; ECX = 0; regs.EAX = regs.EBX = regs.ECX = regs.EDX = 0; }
              ULONG EAX; // Input value
              ULONG ECX; // Input value
              CPUregs regs; // Output values
       };
       //****************************************************************
       // Parser routines
       void ReadFile();
       BOOL ReadLine(CString & s);
       void ReadBlock();
       void ReadValue(CString & s, ULONG & value);
       void ReadCPUIDreg(CString s, CPUIDinfo & info) ;
       //****************************************************************
       void Reset();
       CArray<CPUIDinfo, CPUIDinfo> values;
       UINT line;
       CStdioFile f;
};
