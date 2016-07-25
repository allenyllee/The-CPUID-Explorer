// CPUIDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CPUIDDlg.h"
#include "CPUType.h"

#include "BasicCPU0.h"
#include "BasicCPU1EAXAMD.h"
#include "BasicCPU1EAXIntel.h"
#include "BasicCPU1EBX.h"
#include "BasicCPU1ECXAMD.h"
#include "BasicCPU1ECXIntel.h"
#include "BasicCPU1EDXAMD.h"
#include "BasicCPU1EDXIntel.h"
#include "BasicCPU2Regs.h"
#include "BasicCPU3Regs.h"
#include "BasicCPU4_0.h"
#include "BasicCPU4_1.h"
#include "BasicCPU4_2.h"
#include "BasicCPU4_3.h"
#include "BasicCPU4_4.h"
#include "BasicCPU4_5.h"
#include "BasicCPU4_6.h"
#include "BasicCPU5Regs.h"
#include "BasicCPU6Regs.h"
#include "BasicCPU7Regs.h"
#include "BasicCPU8Regs.h"
#include "BasicCPU9Regs.h"
#include "BasicCPU10Regs.h"

#include "ExtendedCPU0.h"
#include "ExtendedCPU1EAXAMD.h"
#include "ExtendedCPU1EBXAMD.h"
#include "ExtendedCPU1ECXAMD.h"
#include "ExtendedCPU1EDXAMD.h"
#include "ExtendedCPU1Intel.h"
#include "ExtendedCPU2.h"
#include "ExtendedCPU3.h"
#include "ExtendedCPU4.h"
#include "ExtendedCPU5Intel.h"
#include "ExtendedCPU5EAXAMD.h"
#include "ExtendedCPU5EBXAMD.h"
#include "ExtendedCPU5ECXAMD.h"
#include "ExtendedCPU5EDXAMD.h"
#include "ExtendedCPU6Intel.h"
#include "ExtendedCPU6EAXAMD.h"
#include "ExtendedCPU6EBXAMD.h"
#include "ExtendedCPU6ECXAMD.h"
#include "ExtendedCPU7Intel.h"
#include "ExtendedCPU7AMD.h"
#include "ExtendedCPU8Intel.h"
#include "ExtendedCPU8AMD.h"
#include "ExtendedCPU10AMD.h"

#include "BlockDiagram.h"

#include "WriteSpecs.h"

#include "MessagesToChildren.h"
#include "ReportRegs.h"
#include "CPUIDx86.h"
#include "CPUIDRegs.h"
#include "GetCPUName.h"
#include "ToClip.h"

#include "msg.h"

DECLARE_MESSAGE(UWM_DISABLE)

#ifdef _DEBUG
static BOOL TestPages = TRUE;
#else
static const BOOL TestPages = FALSE;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DECLARE_MESSAGE(UWM_INITIALIZE)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
        CAboutDlg();

// Dialog Data
        enum { IDD = IDD_ABOUTBOX };

        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
        DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCPUIDDlg dialog



/****************************************************************************
*                            CCPUIDDlg::CCPUIDDlg
* Inputs:
*       CWnd * parent: parent window
* Effect: 
*       Constructor
****************************************************************************/

CCPUIDDlg::CCPUIDDlg(CWnd* pParent /*=NULL*/)
        : CDialog(CCPUIDDlg::IDD, pParent)
    {
        m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    }

/****************************************************************************
*                          CCPUIDDlg::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CCPUIDDlg::DoDataExchange(CDataExchange* pDX)
{
 CDialog::DoDataExchange(pDX);
 DDX_Control(pDX, IDC_LEAVES, c_Tabs);
 DDX_Control(pDX, IDC_EAX_INPUT, c_EAXIn);
 DDX_Control(pDX, IDC_EAX, c_EAX);
 DDX_Control(pDX, IDC_EBX, c_EBX);
 DDX_Control(pDX, IDC_ECX, c_ECX);
 DDX_Control(pDX, IDC_EDX, c_EDX);
 DDX_Control(pDX, IDC_CPU0, c_CPU0);
 DDX_Control(pDX, IDC_CPU1, c_CPU1);
 DDX_Control(pDX, IDC_CPU2, c_CPU2);
 DDX_Control(pDX, IDC_CPU3, c_CPU3);
 DDX_Control(pDX, IDC_CPU4, c_CPU4);
 DDX_Control(pDX, IDC_CPU5, c_CPU5);
 DDX_Control(pDX, IDC_CPU6, c_CPU6);
 DDX_Control(pDX, IDC_CPU7, c_CPU7);
 DDX_Control(pDX, IDC_CPU_CAPTION, x_CPU);
 DDX_Control(pDX, IDC_TOCLIP, c_ToClip);
}

#define DECLARE_CPUS()          \
    const static struct {       \
       CButton & button;        \
       DWORD_PTR bitmask;       \
    } ProcessorBits[] = {       \
       { c_CPU0, 0x00000001},   \
       { c_CPU1, 0x00000002},   \
       { c_CPU2, 0x00000004},   \
       { c_CPU3, 0x00000008},   \
       { c_CPU4, 0x00000010},   \
       { c_CPU5, 0x00000020},   \
       { c_CPU6, 0x00000040},   \
       { c_CPU7, 0x00000080},   \
    };


BEGIN_MESSAGE_MAP(CCPUIDDlg, CDialog)
        ON_WM_SYSCOMMAND()
        ON_WM_PAINT()
        ON_WM_QUERYDRAGICON()
        ON_REGISTERED_MESSAGE(UWM_EAX_IN, OnEAXIn)
        ON_REGISTERED_MESSAGE(UWM_EAX_EBX, OnEAXEBX)
        ON_REGISTERED_MESSAGE(UWM_ECX_EDX, OnECXEDX)
        ON_CONTROL_RANGE(BN_CLICKED, IDC_CPU0, IDC_CPU7, OnBnClickedCPU)
        //}}AFX_MSG_MAP
    ON_WM_CLOSE()
    ON_WM_NCHITTEST()
    ON_WM_SIZE()
    ON_WM_INITMENUPOPUP()
    ON_BN_CLICKED(IDC_TOCLIP, OnBnClickedToClip)
END_MESSAGE_MAP()


// CCPUIDDlg message handlers

/****************************************************************************
*                          CCPUIDDlg::RemoveAllPages
* Result: void
*       
* Effect: 
*       Deletes all the pages
****************************************************************************/

void CCPUIDDlg::RemoveAllPages()
    {
     while(c_Tabs.GetItemCount() > 0)
        c_Tabs.RemovePage(0);
    } // CCPUIDDlg::RemoveAllPages

/****************************************************************************
*                           CCPUIDDlg::AddAllPages
* Result: void
*       
* Effect: 
*       Adds all the pages required
****************************************************************************/

void CCPUIDDlg::AddAllPages()
    {
     //****************************************************************
     // Add the pages
     //****************************************************************
     UINT_PTR pageindex;
        
//-----------------------------------------------------------------------------
#define ADDPAGE(x)                                         \
      {                                                    \
       CString name;                                       \
       name.LoadString(IDS_##x);                           \
       pageindex = c_Tabs.AddPage(name, C##x::IDD, C##x::IDD, RUNTIME_CLASS(C##x)); \
       pagecount++;                                        \
       if(pageindex >= 0)                                  \
         { /* success */                                   \
          CWnd * page = c_Tabs.GetPage(pageindex);         \
          page->SendMessage(UWM_INITIALIZE, (WPARAM)this); \
         } /* success */                                   \
       else                                                \
          ASSERT(FALSE);                                   \
      }
//-----------------------------------------------------------------------------
#define DISABLELASTPAGE()                            \
        if(pageindex >= 0)                           \
           { /* disable */                           \
            CWnd * page = c_Tabs.GetPage(pageindex); \
            page->SendMessage(UWM_DISABLE);          \
           } /* disable */
//-----------------------------------------------------------------------------

        CPUType type;
        
        UINT_PTR pagecount = 0;
        //****************************************************************
        // Block Diagram
        //****************************************************************
        ADDPAGE(BlockDiagram);

        //****************************************************************
        // CPUID(0)
        //****************************************************************
        ADDPAGE(BasicCPU0);

        //****************************************************************
        // CPUID(1):EAX
        //****************************************************************
        switch(type.type)
           { /* type */
            case CPUType::AMD:
               ADDPAGE(BasicCPU1EAXAMD);
               break;
            case CPUType::Intel:
               ADDPAGE(BasicCPU1EAXIntel);
               break;
           } /* type */

        //****************************************************************
        // CPUID(1):EBX
        //****************************************************************
        ADDPAGE(BasicCPU1EBX);

        //****************************************************************
        // CPUID(1):ECX
        //****************************************************************
        switch(type.type)
           { /* type */
            case CPUType::AMD:
                  ADDPAGE(BasicCPU1ECXAMD);
                  break;
            case CPUType::Intel:
                  ADDPAGE(BasicCPU1ECXIntel);
                  break;
           } /* type */

        //****************************************************************
        // CPUID(1):EDX
        //****************************************************************

        switch(type.type)
           { /* type */
            case CPUType::AMD:
                  ADDPAGE(BasicCPU1EDXAMD);
                  break;
            case CPUType::Intel:
                  ADDPAGE(BasicCPU1EDXIntel);
                  break;
           } /* type */ 

        //****************************************************************
        // CPUID(2)
        //****************************************************************
        { /* CPU2Regs? */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 2)
            { /* can add 2 */
             ADDPAGE(BasicCPU2Regs);
             if(regs.EAX < 2)
                DISABLELASTPAGE();
            } /* can add 2 */
        } /* CPU2Regs? */

        //****************************************************************
        // CPUID(3)
        // Add this page only if
        //    The maximum CPUID value is > 2
        //    The PSN bit is set
        //****************************************************************
        { /* CPU3regs? */
         CPUregs regs;

         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 3)
            { /* 3 or greater */
             CPUregs regs3;
             CurrentProcessor.GetCPUID(1, &regs3);

             EDX1b EDX;
             EDX.w = regs3.EDX;
            
             if(TestPages || EDX.Intel.PSN)
                { /* has psn */
                 ADDPAGE(BasicCPU3Regs);
                 if(TestPages && (!EDX.Intel.PSN || regs.EAX < 3))
                    DISABLELASTPAGE();
                } /* has psn */
            } /* 3 or greater */
        } /* CPU3regs? */

        //****************************************************************
        // CPUID(4,n): Deterministic Cache Parameters
        //****************************************************************

        { /* CPU4 */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 4)
            { /* has page 4 */
             CPUregs regs4;
            
#define AddCPU4(n)                            \
            {                                 \
             BOOL HasCache = regs.EAX >= 4 && CBasicCPU4_0_31::GetCacheParameters(n, &regs4); \
             if(TestPages || HasCache)        \
                { /* CPU4_##n */              \
                ADDPAGE(BasicCPU4_##n);       \
                if(!HasCache)                 \
                   DISABLELASTPAGE();         \
               } /* CPU4_##n */               \
            }

             AddCPU4(0);
             AddCPU4(1);
             AddCPU4(2);
             AddCPU4(3);
             AddCPU4(4);
             AddCPU4(5);
             AddCPU4(6);
            } /* has page 4 */
        } /* CPU4 */

        //****************************************************************
        // CPUID(5): Monitor/MWAIT leaf
        //****************************************************************
        
        { /* CPUID(5) */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 5)
            { /* has page 5 */
             ADDPAGE(BasicCPU5Regs);
             if(TestPages && regs.EAX < 5)
                DISABLELASTPAGE();
            } /* has page 5 */
        } /* CPUID(5) */

        //****************************************************************
        // CPUID(6): Thermal and power management leaf
        //****************************************************************

        { /* CPUID(6) */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 6)
            { /* has page 6 */
             ADDPAGE(BasicCPU6Regs);
             if(TestPages && regs.EAX < 6)
                DISABLELASTPAGE();
            } /* has page 6 */
        } /* CPUID(6) */

        //****************************************************************
        // CPUID(7): Undefined
        //****************************************************************

        { /* CPUID(7) */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 7)
            { /* has page 7 */
             ADDPAGE(BasicCPU7Regs);
             if(TestPages && regs.EAX < 7)
                DISABLELASTPAGE();
            } /* has page 7 */
        } /* CPUID(7) */

        //****************************************************************
        // CPUID(8): Undeinfed leaf
        //****************************************************************

        { /* CPUID(8) */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 8)
            { /* has page 8 */
             ADDPAGE(BasicCPU8Regs);
             if(TestPages && regs.EAX < 8)
                DISABLELASTPAGE();
            } /* has page 8 */
        } /* CPUID(8) */

        //****************************************************************
        // CPUID(9): Undefined leaf
        //****************************************************************

        { /* CPUID(9) */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 9)
            { /* has page 9 */
             ADDPAGE(BasicCPU9Regs);
             if(TestPages && regs.EAX < 9)
                DISABLELASTPAGE();
            } /* has page 9 */
        } /* CPUID(9) */

        //****************************************************************
        // CPUID(10): Architecture performance monitoring
        //****************************************************************

        { /* CPUID(10) */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0, &regs);
         if(TestPages || regs.EAX >= 10)
            { /* has page 10 */
             ADDPAGE(BasicCPU10Regs);
             if(TestPages && regs.EAX < 6)
                DISABLELASTPAGE();
            } /* has page 10 */
        } /* CPUID(10) */

        //****************************************************************
        //                     EXTENDED CPUID FIELDS
        //****************************************************************

        //****************************************************************
        // CPUID(0x80000000)
        //****************************************************************
        ADDPAGE(ExtendedCPU0);

        //****************************************************************
        // CPUID(0x80000001)
        //****************************************************************
        { /* CPUID(0x80000001 */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0x80000000, &regs);

         if(TestPages || regs.EAX >= 0x80000001)
            { /* add it */
             switch(type.type)
                { /* type */
                 case CPUType::AMD:
                       ADDPAGE(ExtendedCPU1EAXAMD);
                       ADDPAGE(ExtendedCPU1EBXAMD);
                       ADDPAGE(ExtendedCPU1ECXAMD);
                       ADDPAGE(ExtendedCPU1EDXAMD);
                    break;
                 case CPUType::Intel:
                       ADDPAGE(ExtendedCPU1Intel);
                    break;
                } /* type */
             if(TestPages && regs.EAX < 0x80000001)
                DISABLELASTPAGE();
            } /* add it */
        } /* CPUID(0x80000001 */         

        //****************************************************************
        // CPUID(0x80000002..0x80000004)
        //****************************************************************
        { /* 0x80000002..0x800000004 */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0x80000000, &regs);

         if(TestPages || regs.EAX >= 0x80000002)
            ADDPAGE(ExtendedCPU2);
         if(TestPages && regs.EAX < 0x80000002)
            DISABLELASTPAGE();

         if(TestPages || regs.EAX >= 0x80000003)
            ADDPAGE(ExtendedCPU3);
         if(TestPages && regs.EAX < 0x80000003)
            DISABLELASTPAGE();

         if(TestPages || regs.EAX >= 0x80000004)
            ADDPAGE(ExtendedCPU4);
         if(TestPages && regs.EAX < 0x80000004)
            DISABLELASTPAGE();
        } /* 0x80000002..0x800000004 */

        //****************************************************************
        // CPUID(0x80000005):
        //****************************************************************

        { /* 0x80000005 */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0x80000000, &regs);

         if(TestPages || regs.EAX >= 0x80000005)
            { /* 5 or better */
             switch(type.type)
                { /* type */
                 case CPUType::AMD:
                       ADDPAGE(ExtendedCPU5EAXAMD);
                       if(regs.EAX < 0x80000005)
                          DISABLELASTPAGE();
                       ADDPAGE(ExtendedCPU5EBXAMD);
                       if(regs.EAX < 0x80000005)
                          DISABLELASTPAGE();
                       ADDPAGE(ExtendedCPU5ECXAMD);
                       if(regs.EAX < 0x80000005)
                          DISABLELASTPAGE();
                       ADDPAGE(ExtendedCPU5EDXAMD);
                       if(regs.EAX < 0x80000005)
                          DISABLELASTPAGE();
                       break;
                 case CPUType::Intel:
                       ADDPAGE(ExtendedCPU5Intel);
                       if(regs.EAX < 0x80000005)
                          DISABLELASTPAGE();
                       break;
                } /* type */
            } /* 5 or better */
        } /* 0x80000005 */

        //****************************************************************
        // CPUID(0x80000006):
        //****************************************************************

        { /* 0x80000006 */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0x80000000, &regs);
          
         if(TestPages || regs.EAX >= 0x80000006)
            { /* 7 or better */
             switch(type.type)
                { /* type */
                 case CPUType::AMD:
                       ADDPAGE(ExtendedCPU6EAXAMD);
                       ADDPAGE(ExtendedCPU6EBXAMD);
                       ADDPAGE(ExtendedCPU6ECXAMD);
                    break;
                 case CPUType::Intel:
                       ADDPAGE(ExtendedCPU6Intel);
                       break;
                } /* type */
             if(TestPages && regs.EAX < 0x80000006)
                DISABLELASTPAGE();
            } /* 7 or better */
        } /* 0x80000006 */

        //****************************************************************
        // CPUID(0x80000007)
        //****************************************************************
        { /* 0x80000007 */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0x80000000, &regs);

         if(TestPages || regs.EAX >= 0x80000007)
            { /* 7 or better */
             switch(type.type)
                { /* type */
                 case CPUType::AMD:
                       ADDPAGE(ExtendedCPU7AMD);
                       break;
                 case CPUType::Intel:
                       ADDPAGE(ExtendedCPU7Intel);
                       break;
                } /* type */
             if(TestPages && regs.EAX < 0x80000007)
                DISABLELASTPAGE();
            } /* 7 or better */
        } /* 0x80000007 */

        //****************************************************************
        // CPUID(0x80000008)
        //****************************************************************
        { /* 0x8000008 */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0x80000000, &regs);

         if(TestPages || regs.EAX >= 0x80000008)
            { /* 8 or better */
             switch(type.type)
                { /* type */
                 case CPUType::AMD:
                       ADDPAGE(ExtendedCPU8AMD);
                       break;
                 case CPUType::Intel:
                       ADDPAGE(ExtendedCPU8Intel);
                       break;
                } /* type */
             if(TestPages && regs.EAX < 0x80000008)
                DISABLELASTPAGE();
            } /* 8 or better */
        } /* 0x8000008 */

        //****************************************************************
        // CPUID(0x8000000A)
        //****************************************************************
        { /* 0x800000A */
         CPUregs regs;
         CurrentProcessor.GetCPUID(0x80000000, &regs);
         BOOL disabled = FALSE;

         if(TestPages || regs.EAX >= 0x8000000A)
            { /* 10 or better */
             switch(type.type)
                { /* type */
                 case CPUType::AMD:
                    { /* AMD */
                     CPUregs regs2;
                     CurrentProcessor.GetCPUID(0x80000001, &regs2);
                     ECX1x ECX;
                     ECX.w = regs2.ECX;
                     
                     BOOL SVM = ECX.AMD.SVM;
                     
                     if(TestPages || SVM)
                        ADDPAGE(ExtendedCPU10AMD);
                     disabled = !SVM;
                    } /* AMD */
                 break;
                 case CPUType::Intel:
                 break;
                } /* type */
             if(TestPages && (regs.EAX < 0x8000000A || disabled))
                DISABLELASTPAGE();
            } /* 10 or better */
        } /* 0x800000A */
        
     
        //****************************************************************
        c_Tabs.SetRedraw(TRUE);
        //----------------------------------------------------------------+
        // This appears to be entirely gratuitous. However, it actually   |
        // fixes a bug in the CTabCtrl where the number of tab rows       |
        // displayed is incorrect. By forcing a resize, it is redrawn     |
        // correctly                                                      |
        //----------------------------------------------------------------+
        CRect tr;                                                      // |
        c_Tabs.GetWindowRect(&tr);                                     // |
        ScreenToClient(&tr);                                           // |
        tr.bottom++;                                                   // |
        c_Tabs.MoveWindow(&tr);                                        // |
        //----------------------------------------------------------------+
    } // CCPUIDDlg::AddAllPages

/****************************************************************************
*                          CCPUIDDlg::EnableAffinity
* Inputs:
*       ¶
* Result: ¶
*       ¶
* Effect: 
*       ¶
****************************************************************************/

void CCPUIDDlg::EnableAffinity()
    {
     DECLARE_CPUS();

     if(CurrentProcessor.IsEmpty())
        { /* enable */
         DWORD_PTR pmask; // current process mask
         DWORD_PTR smask; // system affinity mask
         ::GetProcessAffinityMask(::GetCurrentProcess(), &pmask, &smask);

         for(int i = 0; i < sizeof(ProcessorBits)/sizeof(ProcessorBits[0]); i++)
            { /* check each */
             ProcessorBits[i].button.EnableWindow((ProcessorBits[i].bitmask & smask) ? TRUE : FALSE);
            } /* check each */

         if(smask == 0x00000001)
            { /* uniprocessor */
             c_CPU0.EnableWindow(FALSE); // only one CPU, no options
             x_CPU.EnableWindow(FALSE);
            } /* uniprocessor */
         else
            { /* multiprocessor */
             x_CPU.EnableWindow(TRUE);
            } /* multiprocessor */

         CheckRadioButton(IDC_CPU0, IDC_CPU7, IDC_CPU0);
        } /* enable */
     else
        { /* reading data */
         for(int i = 0; i < sizeof(ProcessorBits)/sizeof(ProcessorBits[0]); i++)
            { /* check each */
             ProcessorBits[i].button.EnableWindow(FALSE);
            } /* check each */
         CheckRadioButton(IDC_CPU0, IDC_CPU7, IDC_CPU0);
         x_CPU.EnableWindow(FALSE);
        } /* reading data */

     SelectAffinity();
    } // CCPUIDDlg::EnableAffinity

/****************************************************************************
*                           CCPUIDDlg::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the data
****************************************************************************/

BOOL CCPUIDDlg::OnInitDialog()
   {
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
       { /* modify system menu */
        CString MenuName;
        //********************************
        // About...
        //********************************
        BOOL sep = FALSE;
//-----------------------------------------------------------------------------
#define ADDSYSMENU(id) {                                              \
                        MenuName.LoadString(IDS_##id);                \
                        if(!MenuName.IsEmpty())                       \
                           { /* add it */                             \
                            if(!sep)                                  \
                               pSysMenu->AppendMenu(MF_SEPARATOR);    \
                            sep = TRUE;                               \
                            pSysMenu->AppendMenu(MF_STRING, IDM_##id, MenuName); \
                           } /* add it */                             \
                       }
//-----------------------------------------------------------------------------

        ADDSYSMENU(ABOUTBOX);
        sep = FALSE; // force new separator
        ADDSYSMENU(WRITESPECS);
        ADDSYSMENU(READSPECS);
        ADDSYSMENU(CLOSESPECS);
#ifdef _DEBUG
        ADDSYSMENU(TESTMODE);
#endif
       } /* modify system menu */

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);                 // Set big icon
    SetIcon(m_hIcon, FALSE);                // Set small icon

    // TODO: Add extra initialization here
    GetWindowText(caption);
        
    CFont * f;
    f = c_EAX.GetFont();

    LOGFONT lf;
    f->GetLogFont(&lf);
    StringCchCopy(lf.lfFaceName, sizeof(lf.lfFaceName)/sizeof(TCHAR), _T("Courier New"));

    lf.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
    font.CreateFontIndirect(&lf);

    EnableToolTips();

    c_EAXIn.SetFont(&font);
    c_EAX.SetFont(&font);
    c_EBX.SetFont(&font);
    c_ECX.SetFont(&font);
    c_EDX.SetFont(&font);

    //****************************************************************
    // EFLAGS
    //  31                            21
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |  |  |  |  |  |  |  |  |  |  |CP|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    // |           |           |           |           |           |           |           |           |
    // |           |           |       2   |           |           |           |           |           |
    // CP - CPUID present
        
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
        AfxMessageBox(IDS_CPUID_NOT_SUPPORTED);
        return TRUE;
       } /* cannot set it */

    HBITMAP bmp;
    bmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
                               MAKEINTRESOURCE(IDB_COPY),
                               IMAGE_BITMAP,
                               0, 0,
                               LR_LOADMAP3DCOLORS);
    c_ToClip.SetBitmap(bmp);

    RedoPages();
    
    return TRUE;  // return TRUE  unless you set the focus to a control
   }

/****************************************************************************
*                            CCPUIDDlg::RedoPages
* Result: void
*       
* Effect: 
*       Redoes all the pages
****************************************************************************/

void CCPUIDDlg::RedoPages()
    {
     c_Tabs.SetRedraw(FALSE);
     RemoveAllPages();
     AddAllPages();
     EnableAffinity();
    } // CCPUIDDlg::RedoPages

/****************************************************************************
*                           CCPUIDDlg::OnSysCommand
* Inputs:
*       UINT nID:
*       LPAram lParam:
* Result: void
*       
* Effect: 
*       Handles system menu, in particular, AboutBox
****************************************************************************/

void CCPUIDDlg::OnSysCommand(UINT nID, LPARAM lParam)
   {
    switch(nID & 0xFFF0)
       { /* decode command  */
        case IDM_ABOUTBOX:
           {
            CAboutDlg dlgAbout;
            dlgAbout.DoModal();
           }
           break;
        case IDM_READSPECS:
           CurrentProcessor.Read();
           if(!CurrentProcessor.IsEmpty())
              { /* succeeded */
               CString title;
               title = caption + _T(" - ") + GetCPUName();
               SetWindowText(title);
               CurrentProcessor.Dump();
              } /* succeeded */

           RedoPages();
           break;
#ifdef _DEBUG
        case IDM_TESTMODE:
           TestPages = !TestPages;
           RedoPages();
           break;
#endif
        case IDM_WRITESPECS:
           WriteSpecs();
           break;
        case IDM_CLOSESPECS:
           CurrentProcessor.Close();
           SetWindowText(caption);
           RedoPages();
           break;
        default:
           CDialog::OnSysCommand(nID, lParam);
       } /* decode command  */
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCPUIDDlg::OnPaint() 
   {
    if (IsIconic())
       {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
       }
    else
       {
        CDialog::OnPaint();
       }
   }

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCPUIDDlg::OnQueryDragIcon()
   {
    return static_cast<HCURSOR>(m_hIcon);
   }

/****************************************************************************
*                             CCPUIDDlg::OnCancel
* Result: void
*       
* Effect: 
*       Does nothingk, keeps ESC translation from closing dialog
****************************************************************************/

void CCPUIDDlg::OnCancel()
    {
    }

/****************************************************************************
*                               CCPUIDDlg::OnOK
* Result: void
*       
* Effect: 
*       Does nothing; keeps <enter> from closing dialog
****************************************************************************/

void CCPUIDDlg::OnOK()
    {
    }

/****************************************************************************
*                             CCPUIDDlg::OnClose
* Result: void
*       
* Effect: 
*       Forces [x] box to actually close the dialog
****************************************************************************/

void CCPUIDDlg::OnClose()
    {
     CDialog::OnOK();
    }

/****************************************************************************
*                           CCPUIDDlg::OnNcHitTest
* Inputs:
*       ¶
* Result: UINT
*       Test result (HT???? value)
* Effect: 
*       Forces left-and-right resizing events to be ignored
****************************************************************************/

UINT CCPUIDDlg::OnNcHitTest(CPoint point)
    {
     UINT hit = CDialog::OnNcHitTest(point);

     switch(hit)
        { /* hit */
         case HTNOWHERE:
         case HTCLIENT:
         case HTCAPTION:
         case HTSYSMENU:
         case HTGROWBOX:
         case HTMENU:
         case HTHSCROLL:
         case HTVSCROLL:
         case HTMINBUTTON:
         case HTMAXBUTTON:
            break;
         case HTLEFT:
         case HTRIGHT:
            hit = HTNOWHERE;
            break;
         case HTTOP:
         case HTBOTTOM:
            break;
         case HTTOPLEFT:
         case HTTOPRIGHT:
            hit = HTTOP;
            break;
         case HTBOTTOMLEFT:
         case HTBOTTOMRIGHT:
            hit = HTBOTTOM;
            break;
         case HTBORDER:
            break;
         case HTCLOSE:
         case HTHELP:
            break;
        } /* hit */
     return hit;
    }

/****************************************************************************
*                              CCPUIDDlg::OnSize
* Inputs:
*       UINT nType: Resize type
*       int cx: New client width
*       int cy: New client heigth
* Result: void
*       
* Effect: 
*       Resets the tab window to fill the area.
****************************************************************************/

void CCPUIDDlg::OnSize(UINT nType, int cx, int cy)
    {
     CDialog::OnSize(nType, cx, cy);

     if(c_Tabs.GetSafeHwnd() != NULL)
        { /* resize tabs */
         CRect r;
         c_Tabs.GetWindowRect(&r);
         ScreenToClient(&r);
         c_Tabs.SetWindowPos(NULL,
                             0, 0, // no change
                             cx - r.left, cy - r.top,
                             SWP_NOMOVE | SWP_NOZORDER);
        } /* resize tabs */
    }

/****************************************************************************
*                             CCPUIDDlg::OnEAXIn
* Inputs:
*       WPARAM: ignored
*       LPARAM: EAX input value to CPUID
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Sets the EAXIn value
****************************************************************************/

LRESULT CCPUIDDlg::OnEAXIn(WPARAM, LPARAM lParam)
    {
     CString s;
     s.Format(_T("%08x"), lParam);
     c_EAXIn.SetWindowText(s);
     return 0;
    } // CCPUIDDlg::OnEAXIn

/****************************************************************************
*                             CCPUIDDlg::OnEAXEBX
* Inputs:
*       WPARAM: EAX
*       LPARAM: EBX
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Displays EAX, EBX
****************************************************************************/

LRESULT CCPUIDDlg::OnEAXEBX(WPARAM wParam, LPARAM lParam)
    {
     CString s;
     s.Format(_T("%08x"), wParam);
     c_EAX.SetWindowText(s);
     s.Format(_T("%08x"), lParam);
     c_EBX.SetWindowText(s);
     return 0;
    } // CCPUIDDlg::OnEAXEBX

/****************************************************************************
*                             CCPUIDDlg::OnECXEDX
* Inputs:
*       WPARAM: ECX
*       LPARAM: EDX
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Displays ECX, EDX
****************************************************************************/

LRESULT CCPUIDDlg::OnECXEDX(WPARAM wParam, LPARAM lParam)
    {
     CString s;
     s.Format(_T("%08x"), wParam);
     c_ECX.SetWindowText(s);
     s.Format(_T("%08x"), lParam);
     c_EDX.SetWindowText(s);
     return 0;
    } // CCPUIDDlg::OnECXEDX

/****************************************************************************
*                          CCPUIDDlg::SelectAffinity
* Result: void
*       
* Effect: 
*       Sets the thread affinity to the processor selected by the radio button
****************************************************************************/

void CCPUIDDlg::SelectAffinity()
    {
     DECLARE_CPUS();
     
     for(int i = 0; i < sizeof(ProcessorBits)/sizeof(ProcessorBits[0]); i++)
        { /* set affinity */
         if(ProcessorBits[i].button.GetCheck() == BST_CHECKED)
            { /* found it */
             ::SetThreadAffinityMask(::GetCurrentThread(), ProcessorBits[i].bitmask);
             break;
            } /* found it */
        } /* set affinity */
    } // CCPUIDDlg::SelectAffinity

/****************************************************************************
*                         CCPUIDDlg::OnBnClickedCPU
* Result: void
*       
* Effect: 
*       Sets the affinity mask
****************************************************************************/

void CCPUIDDlg::OnBnClickedCPU(UINT id)
    {
     SelectAffinity();
    } // CCPUIDDlg::OnBnClickedCPU0

/****************************************************************************
*                         CCPUIDDlg::OnInitMenuPopup
* Inputs:
*       CMenu * pPopupMenu: ignored
*       UINT nIndex: ignored
*       BOOL bSysMenu: ignored
* Result: void
*       
* Effect: 
*       Enables the Close and Write menu items
****************************************************************************/

void CCPUIDDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
    {
     CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

     if(CurrentProcessor.IsEmpty())
        pPopupMenu->EnableMenuItem(IDM_WRITESPECS, MF_BYCOMMAND | MF_ENABLED);
     else
        pPopupMenu->EnableMenuItem(IDM_WRITESPECS, MF_BYCOMMAND | MF_GRAYED);

     if(TestPages)
        pPopupMenu->CheckMenuItem(IDM_TESTMODE, MF_BYCOMMAND | MF_CHECKED);
     else
        pPopupMenu->CheckMenuItem(IDM_TESTMODE, MF_BYCOMMAND | MF_UNCHECKED);
    }

/****************************************************************************
*                        CCPUIDDlg::OnBnClickedToClip
* Result: void
*       
* Effect: 
*       Copies the active tab to the clipboard
****************************************************************************/

void CCPUIDDlg::OnBnClickedToClip()
    {
     INT_PTR pg = c_Tabs.GetActivePage();
     CWnd * wnd = c_Tabs.GetPage(pg);
     toClipboard(wnd, TRUE);
    } // CCPUIDDlg::OnBnClickedToClip
