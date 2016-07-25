#include "stdafx.h"
#include "resource.h"
#include "ReadSpecs.h"
#include "ErrorString.h"
#include "GetCPUName.h"

/****************************************************************************
*                               Specs::ReadLine
* Inputs:
*       CStrig & s: String to be filled in
* Result: BOOL
*       TRUE if successful
*       FALSE if EOF
* Effect: 
*       Reads a non-empty line from the file, and trims all leading and
*       trailing whitespace from it.
****************************************************************************/

BOOL Specs::ReadLine(CString & s)
    {
     while(TRUE)
        { /* read line */
         if(!f.ReadString(s))
            return FALSE;
         line++;
         s.Trim();
         if(!s.IsEmpty())
            return TRUE;
        } /* read line */
    } // Specs::ReadLine

/****************************************************************************
*                               Specs:ReadValue
* Inputs:
*       CString & s: String to read, of the form [= "value"]
*       ULONG & value
* Result: void
*       
* Effect: 
*       ¶
****************************************************************************/

void Specs::ReadValue(CString & s, ULONG & value)
    {
     // = "value"...
     s.Trim();
     if(s.Left(1) != _T("="))
        throw new SyntaxError(IDS_ERROR_EXPECTED_EQUAL);
     s = s.Mid(1);
     s.Trim();
     // "value" ...
     if(s.Left(1) != _T("\""))
        throw new SyntaxError(IDS_ERROR_EXPECTED_QUOTE);
     s = s.Mid(1);
     s.Trim();
     // 0xnnnnnn" ...
     LPTSTR stopper;

     value = _tcstoul(s, &stopper, 0); // base 0 allows recognzing 0x and decimal both
     if(*stopper != _T('\"'))
        throw new SyntaxError(IDS_ERROR_EXPECTED_QUOTE);
     
     int delta = (int)(stopper - (LPCTSTR)s);  // compute how far away the quote is
     s = s.Mid(delta + 1);
     s.Trim();
     // ...
    } // Specs:ReadValue

/****************************************************************************
*                            Specs::ReadCPUIDreg
* Input:
*       CString s: String that contains <CPUID:CPUID declaration
*       CPUIDinfo & info: Element to be filled in
* Result: void
*       
* Throws:
*       SyntaxError
* Effect: 
*       Reads a CPUID:CPUID component
****************************************************************************/

void Specs::ReadCPUIDreg(CString s, CPUIDinfo & info)
    {
     // Input: Current line which is of the form
     //<CPUID:CPUID EAX="value" ECX="value">
     if(s.Right(1) != _T(">"))
        throw new SyntaxError(IDS_ERROR_MISSING_RIGHT_POINTY);
     s = s.Mid(12);
     s = s.Trim();
     // EAX = "value" ECX = "value" >
     if(s.Left(3) != _T("EAX"))
        throw new SyntaxError(IDS_ERROR_EXPECTED_EAX_VALUE);
     s = s.Mid(3);
     ReadValue(s, info.EAX);

     // ECX = "value" >
     // >
     if(s == _T(">"))
        { /* no ECX */
         info.ECX = 0;
        } /* no ECX */
     else
        { /* has ECX */
         if(s.Left(3) != _T("ECX"))
            throw new SyntaxError(IDS_ERROR_EXPECTED_ECX_VALUE);
         s = s.Mid(3);
         s.Trim();
         // = "value">
         ReadValue(s, info.ECX);
         if(s != _T(">"))
            throw new SyntaxError(IDS_ERROR_MISSING_RIGHT_POINTY);
        } /* has ECX */
     // Now read the blocks of registers
     // <CPUID:EAX value="value" />
     // <CPUID:EBX value="value" />
     // <CPUID:ECX value="value" />
     // <CPUID:EDX value="value" />
     DWORD Saw = 0;

#define SawEAX 0x01
#define SawEBX 0x02
#define SawECX 0x04
#define SawEDX 0x08
#define SawAll (SawEAX | SawEBX | SawECX | SawEDX)
     while(TRUE)
        { /* scan regs */
         ReadLine(s);

         ULONG * value;
         if(s.Left(10) == _T("<CPUID:EAX"))
            { /* EAX */
             value = &info.regs.EAX;
             Saw |= SawEAX;
            } /* EAX */
         else
         if(s.Left(10) == _T("<CPUID:EBX"))
            { /* EBX */
             value = &info.regs.EBX;
             Saw |= SawEBX;
            } /* EBX */
         else
         if(s.Left(10) == _T("<CPUID:ECX"))
            { /* ECX */
             value = &info.regs.ECX;
             Saw |= SawECX;
            } /* ECX */
         else
         if(s.Left(10) == _T("<CPUID:EDX"))
            { /* EDX */
             value = &info.regs.EDX;
             Saw |= SawEDX;
            } /* EDX */
         else
         if(s == _T("</CPUID:CPUID>"))
            break;
         else
            throw new SyntaxError(IDS_ERROR_EXPECTED_CPUID_EXX);

         s = s.Mid(10);
         s.Trim();
         // value = "value" />
         if(s.Left(5) != _T("value"))
            throw new SyntaxError(IDS_ERROR_EXPECTED_VALUE_KEYWORD);
         s = s.Mid(5);
         s.Trim();
         // = "value" />
         ReadValue(s, *value);
         // />
         if(s != _T("/>"))
            throw new SyntaxError(IDS_ERROR_EXPECTED_SLASH_POINTY);
        } /* scan regs */

     if(Saw != SawAll)
        { /* missing reg */
         if( (Saw & SawEAX) == 0)
            throw new SyntaxError(IDS_ERROR_MISSING_EAX);
         else
         if( (Saw & SawEBX) == 0)
            throw new SyntaxError(IDS_ERROR_MISSING_EBX);
         else
         if( (Saw & SawECX) == 0)
            throw new SyntaxError(IDS_ERROR_MISSING_ECX);
         else
         if( (Saw & SawEDX) == 0)
            throw new SyntaxError(IDS_ERROR_MISSING_EDX);
        } /* missing reg */
    } // Specs::ReadCPUIDreg

/****************************************************************************
*                              Specs::ReadBlock
* Result: void
*
* Throws:
*       SyntaxError
* Effect: 
*       Reads a <CPUID:block> block
****************************************************************************/

void Specs::ReadBlock()
    {
     while(TRUE)
        { /* read block */
         CString s;
         ReadLine(s);
         if(s == _T("</CPUID:block>"))
            return; // successful read!
         if(s.Left(12) == _T("<CPUID:CPUID"))
            { /* got it */
             CPUIDinfo info;
             ReadCPUIDreg(s, info);
             values.Add(info);
            } /* got it */
         else
            throw new SyntaxError(IDS_ERROR_EXPECTED_CPUID_CPUID);
        } /* read block */
    } // Specs::ReadBlock

/****************************************************************************
*                               Specs::ReadFile
* Result: void
*       
* Effect: 
*       Reads the file
****************************************************************************/

void Specs::ReadFile()
    {
    //****************************************************************
    // <?xml version "1.0"?>
    //****************************************************************

     CString s;
     line = 0;
     if(!ReadLine(s))
        throw new SyntaxError(IDS_ERROR_EOF);

     if(s.Left(2) == _T("<?"))
        { /* header */
         if(!ReadLine(s))
            throw new SyntaxError(IDS_ERROR_EOF);
        } /* header */

    //****************************************************************
    // <CPUID:id name="...name..."/>
    //****************************************************************
    // If found, this is ignored
    if(s.Left(9) == _T("<CPUID:id"))
       { /* ignore id */
        if(!ReadLine(s))
           throw new SyntaxError(IDS_ERROR_EOF);
       } /* ignore id */

    //****************************************************************
    // <CPUID:block>
    //****************************************************************
     if(s == _T("<CPUID:block>"))
        { /* read block */
         Reset();
         ReadBlock();
        } /* read block */
     else
        { /* missing CPUID:block */
         throw new SyntaxError(IDS_ERROR_MISSING_CPUID_BLOCK);
         Reset();
        } /* missing CPUID:block */
    } // Specs::ReadFile

/****************************************************************************
*                                  Specs::Read
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Reads the specfications into 
****************************************************************************/

BOOL Specs::Read()
   {
    BOOL result = FALSE;
    CString filter;
    filter.LoadString(IDS_FILTER);
    CString ext;
    ext.LoadString(IDS_DEFAULT_EXTENSION);

    CFileDialog dlg(TRUE, // open
                    ext, // default extension
                    NULL,  // no default filename
                    0,     // no flags
                    filter);

    if(dlg.DoModal() != IDOK)
       return FALSE;
    
    if(!f.Open(dlg.GetPathName(), CFile::modeRead))
       { /* open failed */
        DWORD err = ::GetLastError();
        CString openerror;
        openerror.LoadString(IDS_OPEN_ERROR);
        CString s;
        s.Format(_T("%s\n%s\n%s"),
                 openerror,
                 dlg.GetPathName(),
                 ErrorString(err));
        AfxMessageBox(s, MB_ICONERROR | MB_OK);
        return FALSE;
       } /* open failed */

    try
       { /* try */
        ReadFile();
        result = TRUE;
       } /* try */
    catch(SyntaxError * e)
       { /* got error */
        // TODO: Syntax error
        //       file: <filename>
        //       line: <line>
        //       error: <string>
        CString msg;
        CString fmt;
        fmt.LoadString(IDS_SYNTAX_ERROR);
        
        msg.Format(fmt, dlg.GetPathName(), line, e->GetMessage());
        AfxMessageBox(msg, MB_ICONERROR | MB_OK);
        e->Delete();
        result = FALSE;
       } /* got error */

    f.Close();
    return result;
   } // Specs::Read

/****************************************************************************
*                                Specs::Reset
* Result: void
*       
* Effect: 
*       Clears the array of data
****************************************************************************/

void Specs::Reset()
    {
     values.SetSize(0);
    } // Specs::Reset

/****************************************************************************
*                                 Specs::Dump
* Result: void
*       
* Effect: 
*       Trace output of the current Specs array
****************************************************************************/

void Specs::Dump()
    {
#ifdef _DEBUG
     for(INT_PTR i = 0; i < values.GetSize(); i++)
        { /* show it */
         if(values[i].ECX == 0)
            TRACE("CPUID(0x%x)  [%d]\n", values[i].EAX, i);
         else
            TRACE("CPUID(0x%x, %d) [%d]\n", values[i].EAX, values[i].ECX, i);
         TRACE("   EAX=0x%08x\n", values[i].regs.EAX);
         TRACE("   EBX=0x%08x\n", values[i].regs.EBX);
         TRACE("   ECX=0x%08x\n", values[i].regs.ECX);
         TRACE("   EDX=0x%08x\n", values[i].regs.EDX);
        } /* show it */
#endif
    } // Specs::Dump

/****************************************************************************
*                               Specs::GetCPUID
* Inputs:
*       UINT id: Register to read
*       CPUregs * regs: Register set
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       If the specs are empty, returns an actual GetCPUID call, otherwise
*       returns the value from the specs.
****************************************************************************/

BOOL Specs::GetCPUID(UINT id, CPUregs * regs)
    {
     if(IsEmpty())
        return ::GetCPUID(id, regs);

     for(INT_PTR i = 0; i < values.GetSize(); i++)
        { /* search for value */
         switch(id)
            { /* handle special cases */
             case 4:
                if(values[i].EAX == id && values[i].ECX == regs->ECX)
                   { /* found id,n */
                    *regs = values[i].regs;
                    return TRUE;
                   } /* found id,n */
                break;
             default:
                if(values[i].EAX == id)
                   { /* found it */
                    *regs = values[i].regs;
                    return TRUE;
                   } /* found it */
                break;
            } /* handle special cases */
        } /* search for value */

     regs->EAX = regs->EBX = regs->ECX = regs->EDX = 0;
     return FALSE;
    } // Specs::GetCPUID

/****************************************************************************
*                                Specs::Close
* Result: void
*       
* Effect: 
*       "Closes" the specs
****************************************************************************/

void Specs::Close()
    {
     Reset();
    } // Specs::Close
