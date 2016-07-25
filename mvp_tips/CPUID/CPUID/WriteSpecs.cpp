#include "stdafx.h"
#include "resource.h"

#include "WriteSpecs.h"

#include "CPUIDx86.h"
#include "BasicCPU4_0_31.h"
#include "ErrorString.h"
#include "GetCPUName.h"

/****************************************************************************
*                                 WriteCPUID
* Inputs:
*       UINT EAX: Input EAX value
*       UINT ECX: Input ECX value
*       CPUregs * regs: Output registers
* Result: void
*       
* Effect: 
*       Writes the CPUID:CPUID block
* Notes:
*       <CPUID:CPUID EAX="val" ECX="val">
*           <CPUID:EAX value="0x00000000"/>
*           <CPUID:EBX value="0x00000000"/>
*           <CPUID:ECX value="0x00000000"/>
*           <CPUID:EDX value="0x00000000"/>
*       </CPUID:CPUID>
*
* The ECX value will not be written out if it is 0
****************************************************************************/

static void WriteCPUID(CStdioFile & f, UINT EAX, UINT ECX, CPUregs * regs)
    {
     CString s;
     //****************************************************************
     //   <CPUID:CPUID EAX="0xn" ECX="0xn">
     //****************************************************************
     s.Format(_T("   <CPUID:CPUID EAX=\"0x%x\""), EAX);
     f.WriteString(s);
     if(ECX != 0)
        { /* output ECX */
         s.Format(_T(" ECX=\"0x%x\""), ECX);
         f.WriteString(s);
        } /* output ECX */
     f.WriteString(_T(">\n"));

//------------------------------------------------------------------------------
#define FORMATREG(reg) {                                                        \
     s.Format(_T("     <CPUID:") #reg _T(" value=\"0x%08x\" />\n"), regs->reg); \
     f.WriteString(s);                                                          \
}
//------------------------------------------------------------------------------

     FORMATREG(EAX);
     FORMATREG(EBX);
     FORMATREG(ECX);
     FORMATREG(EDX);
     //****************************************************************
     // </CPUID:CPUID>
     //****************************************************************
     f.WriteString(_T("   </CPUID:CPUID>\n"));

    } // WriteCPUID


/****************************************************************************
*                                 WriteSpecs
* Result: void
*       
* Effect: 
*       Writes an XML file of all known CPUID values
****************************************************************************/

void WriteSpecs()
    {
     CString filename = GetCPUName();
     CString filter;
     filter.LoadString(IDS_FILTER);
     CString ext;
     ext.LoadString(IDS_DEFAULT_EXTENSION);

     CFileDialog dlg(FALSE, // save-as
                     ext, // default extension
                     filename,
                     OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                     filter);
     if(dlg.DoModal() != IDOK)
        return;

     CStdioFile f;
     if(!f.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite))
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
         return;
        } /* open failed */
     f.WriteString(_T("<?xml version \"1.0\"?>\n"));
     f.WriteString(_T("<CPUID:id name=\"") + GetCPUName() + _T("\"/>\n"));
     f.WriteString(_T("<CPUID:block>\n"));

     CPUregs regs;
     GetCPUID(0, &regs);

     for(UINT i = 0; i <= min(regs.EAX, 255); i++)
        { /* read each basic */
         CPUregs regs2;
         switch(i)
            { /* special cases */
             case 4:
                { /* cache information */
                 for(int n = 0; ; n++)
                    { /* scan each */
                     regs2.ECX = n;
                     GetCPUID(i, &regs2);
                     BOOL HasCache = CBasicCPU4_0_31::GetCacheParameters(n, &regs2);
                     if(!HasCache)
                        break;
                     WriteCPUID(f, i, n, &regs2);
                    } /* scan each */
                } /* cache information */
                break;
             default:
                GetCPUID(i, &regs2);
                WriteCPUID(f, i, 0, &regs2);
                break;
            } /* special cases */
        } /* read each basic */

     GetCPUID(0x80000000, &regs);
     for(UINT i = 0x80000000; i <= regs.EAX; i++)
        { /* read each extended */
         CPUregs regs2;
         GetCPUID(i, &regs2);
         WriteCPUID(f, i, 0, &regs2);
        } /* read each extended */

     f.WriteString(_T("</CPUID:block>\n"));
     f.Close();
    } // WriteSpecs
