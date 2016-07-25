// BlockDiagram.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BlockDiagram.h"
#include "CPUIDRegs.h"
#include "CPUIDx86.h"
#include "CurrentProcessor.h"

// CBlockDiagram dialog

IMPLEMENT_DYNCREATE(CBlockDiagram, CPropertyPage)

CBlockDiagram::CBlockDiagram()
        : CPropertyPage(CBlockDiagram::IDD)
{
 initialized = FALSE;
}

CBlockDiagram::~CBlockDiagram()
{
}

void CBlockDiagram::DoDataExchange(CDataExchange* pDX)
{
        CPropertyPage::DoDataExchange(pDX);
        DDX_Control(pDX, IDC_CPU_REGION, c_CPURegion);
        DDX_Control(pDX, IDC_GAP1, c_Gap1);
        DDX_Control(pDX, IDC_CPU_CORE_REGION, c_CPUCoreRegion);
        DDX_Control(pDX, IDC_GAP2, c_Gap2);
        DDX_Control(pDX, IDC_L1_CACHE_REGION, c_L1CacheRegion);
        DDX_Control(pDX, IDC_LOGICAL_ADDRESS_LINES_REGION, c_LogicalAddressLinesRegion);
        DDX_Control(pDX, IDC_TLB_REGION, c_TLBRegion);
        DDX_Control(pDX, IDC_L2_CACHE_REGION, c_L2CacheRegion);
        DDX_Control(pDX, IDC_L3_CACHE_REGION, c_L3CacheRegion);
        DDX_Control(pDX, IDC_PHYSICAL_ADDRESS_LINES_REGION, c_PhysicalAddressLinesRegion);
        DDX_Control(pDX, IDC_MEMORY_REGION, c_MemoryRegion);
        DDX_Control(pDX, IDC_PREFETCH, c_PrefetchRegion); 
}


BEGIN_MESSAGE_MAP(CBlockDiagram, CPropertyPage)
    ON_WM_SIZE()
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotify)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotify)
END_MESSAGE_MAP()


// CBlockDiagram message handlers
const static BYTE L1CacheInfo[] = {
   0x06,  //    IDS_CTLB_06H            "1st-level instruction cache: 8K, 4-way set associative, 32 byte line size"
   0x08,  //    IDS_CTLB_08H            "1st-level instruction cache: 16K, 4-way set associative, 32 byte line size"
   0x0A,  //    IDS_CTLB_0AH            "1st-level data cache: 8K, 2-way set associative, 32 byte line size"
   0x0C,  //    IDS_CTLB_0CH            "1st-level data cache: 16K, 4-way set associative, 32 byte line size"
   0x2C,  //    IDS_CTLB_2CH            "1st-level data cache: 32K, 8-way asociative, 64 byte line size"
   0x30,  //    IDS_CTLB_30H            "1st-level instruction cache: 32K, 8-way set associative, 64 byte line size"
   0x60,  //    IDS_CTLB_60H            "1st-level data cache: 16K, 8-way set associative, 64 byte line size"
   0x66,  //    IDS_CTLB_66H            "1st-level data cache: 8K, 4-way set associative, 64 byte line size"
   0x67,  //    IDS_CTLB_67H            "1st-level data cache: 16K, 4-way set associative, 64 byte line size"
   0x68,  //    IDS_CTLB_68H            "1st-level data cache: 32K, 4-way set associative, 64 byte line size"
   0x00,  //    EOT
};

const static BYTE L2CacheInfo[] = {
   0x41,  //  IDS_CTLB_41H            "2nd-level cache: 128K, 4-way set associative, 32 byte line size"
   0x42,  //  IDS_CTLB_42H            "2nd-level cache: 256K, 4-way set associative, 32 byte line size"
   0x43,  //  IDS_CTLB_43H            "2nd-level cache: 512K, 4-way set associative, 32 byte line size"
   0x44,  //  IDS_CTLB_44H            "2nd-level cache: 1M, 4-way set associative, 32 byte line size"
   0x45,  //  IDS_CTLB_45H            "2nd-level cache: 2M, 4-way set associative, 32 byte line size"
   0x49,  //  IDS_CTLB_49H            "2nd-level cache: 4M, 16-way set associative, 64 byte line size"
   0x78,  //  IDS_CTLB_78H            "2nd-level cache: 128K, 8-way set associative, 64 byte line size"
   0x79,  //  IDS_CTLB_79H            "2nd-level cache: 128K, 8-way set associative, 64 byte line size, 2 lines per sector"
   0x7A,  //  IDS_CTLB_7AH            "2nd-level cache: 256K, 8-way set associative, 64 byte line size, 2 lines per sector"
   0x7B,  //  IDS_CTLB_7BH            "2nd-level cache: 512K, 8-way set associative, 64 byte line size, 2 lines per sector"
   0x7C,  //  IDS_CTLB_7CH            "2nd-level cache: 1M, 8-way set associative, 64 byte line size, 2 lines per sector"
   0x7D,  //  IDS_CTLB_7DH            "2nd-level cache: 2M, 8-way set associative, 64 byte line size"
   0x7F,  //  IDS_CTLB_7FH            "2nd-level cache: 512K, 2-way set associative, 64 byte line size"
   0x82,  //  IDS_CTLB_82H            "2nd-level cache: 256K, 8-way set associative, 32 byte line size"
   0x83,  //  IDS_CTLB_83H            "2nd-level cache: 512K, 8-way set associative, 32 byte line size"
   0x84,  //  IDS_CTLB_84H            "2nd-level cache: 1M, 8-way set associative, 32 byte line size"
   0x85,  //  IDS_CTLB_85H            "2nd-level cache: 2M, 8-way set associative, 32 byte line size"
   0x86,  //  IDS_CTLB_86H            "2nd-level cache: 512K, 4-way set associative, 64 byte line size"
   0x87,  //  IDS_CTLB_87H            "2nd-level cache: 1M, 8-way set associative, 64 byte line size"
   0x00,  //  EOT
};

const static BYTE L3CacheInfo[] = {
   0x22,  //  IDS_CTLB_22H            "3rd-level cache: 512K, 4-way set associative, 64-byte line size, 2 lines per sector"
   0x23,  //  IDS_CTLB_23H            "3rd-level cache; 1M, 8-way set associative, 64 byte line size, 2 lines per sector"
   0x25,  //  IDS_CTLB_25H            "3rd-level cache: 2M, 8-way set associative, 64 byte line size, 2 lines per sector"
   0x29,  //  IDS_CTLB_29H            "3rd-level cache: 4M, 8-way set associative, 64 byte line size, 2 lines per sector"
   0x46,  //  IDS_CTLB_46H            "3rd-level cache: 4M, 4-way set associative, 64 byte line size"
   0x47,  //  IDS_CTLB_47H            "3rd-level cache, 8M, 8-way set associative, 64 byte line size"
   0x00,  //  EOT
};

const static BYTE TLBInfo[] = {
   0x01,  //     IDS_CTLB_01H            "Instruction TLB: 4K pages, 4-way set associative, 32 entries"
   0x02,  //     IDS_CTLB_02H            "Instruction TLB: 4K pages, 4-way set associative, 2 entries"
   0x03,  //     IDS_CTLB_03H            "Data TLB: 4K pages, 4-way set associative, 64 entries"
   0x04,  //     IDS_CTLB_04H            "Data TLB: 4M pages, 4-way set associative, 8 entries"
   0x05,  //     IDS_CTLB_05H            "Data TLB: 4M pages, 4-way set associative, 32 entries"
   0x50,  //     IDS_CTLB_50H            "Instruction TLB: 4K and 2M or 4M pages, 64 entries"
   0x51,  //     IDS_CTLB_51H            "Instruction TLB: 4K and 2M or 4M pages, 128 entries"
   0x52,  //     IDS_CTLB_52H            "Instruction TLB: 4K and 2M or 4M pages, 256 entries"
   0x56,  //     IDS_CTLB_56H            "Data TLB0: 4M pages, 4-way set associative, 16 entries"
   0x57,  //     IDS_CTLB_57H            "Data TLB0: 4K pages, 4-way set associative, 16 entries"
   0x5B,  //     IDS_CTLB_5BH            "Data TLB: 4K and 4M pages, 64 entries"
   0x5C,  //     IDS_CTLB_5CH            "Data TLB: 4K and 4M pages, 128 entries"
   0x5D,  //     IDS_CTLB_5DH            "Data TLB: 4K and 4M pages, 256 entries"
   0xB0,  //     IDS_CTLB_B0H            "Instruction TLB: 4K pages, 4-way set associative, 128 entries"
   0xB3,  //     IDS_CTLB_B3H            "Data TLB: 4K pages, 4-way set associative, 128 entries"
   0xB4,  //     IDS_CTLB_B4H            "Data TLB1: 4K pages, 4-way set associative, 256 entries"
   0x00,  //  EOT
};

const static BYTE TraceCacheInfo[] = {
   0x70,  //     IDS_CLTB_70H            "Trace cache: 12K-uOp, 8-way set associative"
   0x71,  //     IDS_CTLB_71H            "Trace cache: 16K-uOp, 8-way set associative"
   0x72,  //     IDS_CTLB_72H            "Trace cache: 32K-uOp, 8-way set associative"
   0x00,  // EOT
};

const static BYTE PrefetchInfo[] = {
   0xF0,  //     IDS_CTLB_F0H            "64-byte prefetching"
   0xF1,  //     IDS_CTLB_F1H            "128-byte prefetching"
   0x00,  // EOT
};

/*****************************************************************************

+--CPURegion
|
|   CPUCoreRegion
|   |        L1CacheRegion
|   |        |        LogicalAddressLinesRegion
|   |        |        |        TLBRegion
|   |        |        |        |        L2CacheRegion
|   |        |        |        |        |        L3CacheRegion
|   |        |        |        |        |        |        PhysicalAddressLinesRegion
|   |        |        |        |        |        |        |        MemoryRegion
|   |        |        |        |        |        |        |        |
|   |        |        |        |        |        |        |        V
+->+|========|========|=======+|        |        |        |       +----------------+
   ||        |   3    |       ||        |        |        |       |       3        |
   |V        v        v       |V        V        V        V       |                |
   +--------+--------+--------+--------+--------+--------+--------+                |
   |    1   |    1   |    1   |    1   |    1   |    1   |    1   |                |
   |        |        |        |        |        |        |        |                |
   |        |        |        |        |        |        |        |                |
   |     80%|     80%|    80% |    80% |     80%|     80%|     80%|            100%|
   |        |        |        |        |        |        |        |                |
   |        |        |        |        |        |        |        |                |
   |        |        |        |        |        |        |        |                |
   |        |        |        |        |        |        |        |                |
   |        |        |        |        |        |        |        |                |
   |        |        |        |        |        |        |        |                |
   |        +--------+--------+--------+--------+--------+--------+                |
   |                          |                                   |                |
   |                          |                                   |                |
   +==========================+                                   +----------------+


****************************************************************************/  

/*****************************************************************************
  Regions structure
*****************************************************************************/  
#define BD_CENTER  0x00
#define BD_TOP     0x01
#define BD_BOTTOM  0x02

#define DECLARE_REGIONS()                        \
                                                 \
const struct {                                   \
   CStatic & wnd;                                \
   UINT units;                                   \
   UINT percent;                                 \
   UINT overlap;                                 \
   UINT align;   /* BD_*   */                    \
   BOOL (*query)();                              \
} Regions[] = {                                  \
  /* wnd                          units  %  ovl    align */ \
   { c_CPURegion,                   69,100, 6, BD_CENTER},  \
   { c_Gap1,                         2, 80, 0, BD_CENTER},  \
   { c_CPUCoreRegion,               15, 80, 0, BD_CENTER},  \
   { c_Gap2,                         2, 80, 0, BD_CENTER},  \
   { c_PrefetchRegion,              40, 10, 2, BD_BOTTOM, QueryPrefetch}, \
   { c_L1CacheRegion,               35, 80, 0, BD_CENTER},  \
   { c_LogicalAddressLinesRegion,   15, 50, 0, BD_CENTER},  \
   { c_TLBRegion,                   40, 80, 0, BD_CENTER},  \
   { c_L2CacheRegion,               40, 80, 0, BD_CENTER},  \
   { c_L3CacheRegion,               35, 80, 0, BD_CENTER, QueryL3},  \
   { c_PhysicalAddressLinesRegion,  15, 50, 0, BD_CENTER},  \
   { c_MemoryRegion,                30,100, 0, BD_CENTER}   \
};


/****************************************************************************
*                            GetCPUID2Descriptors
* Inputs:
*       CByteArray & data: Place to put data
* Result: void
*       
* Effect: 
*       Reads the CPUID(2) data
****************************************************************************/

void CBlockDiagram::GetCPUID2Descriptors(CByteArray & data)
    {
     EREGS2 eregs;

     data.SetSize(0);

     CurrentProcessor.GetCPUID(2, &eregs.regs);
     if(eregs.descriptors[0] == 0x00)
         { /* AMD64 */
          return; // has no CPUID(2) descriptors
         } /* AMD64 */
     ASSERT(eregs.descriptors[0] == 0x01); // Unsupported for now: needing to call CPUID(2) more than once
     for(int i = 1; i < sizeof(eregs.descriptors); i++)
        if(eregs.descriptors[i] != 0x00)
           data.Add(eregs.descriptors[i]);

    } // CBlockDiagram::GetCPUID2Descriptors

/****************************************************************************
*                     CBlockDiagram::GetLongAssociativity
* Inputs:
*       UINT assoc: Associative mode
*       CString & way: Place to format description
* Result: BOOL
*       TRUE if successful, FALSE if error
* Effect: 
*       "Direct mapped"
*       "Fully associative"
*       "%d-way associative"
****************************************************************************/

BOOL CBlockDiagram::GetLongAssociativity(UINT assoc, CString & way)
    {
     switch(assoc)
        { /* assoc */
         case 0:  // reserved
            return FALSE;  // no information
         case 1:
            way.LoadString(IDS_DIRECT_MAPPED_LONG);
            break;
         case 0xFF:
            way.LoadString(IDS_FULLY_ASSOCIATIVE_LONG);
            break;
         default:
            { /* n-way */
             CString t;
             t.LoadString(IDS_NWAY_LONG);
             way.Format(t, assoc);
            } /* n-way */
            break;
        } /* assoc */
     return TRUE;
    } // CBlockDiagram::GetLongAssociativity

/****************************************************************************
*                       CBlockDiagram::GetShortAssociativity
* Inputs:
*       UINT assoc: Associative mode
*       CString & way: Place to format description
* Result: BOOL
*       TRUE if successful, FALSE if error
* Effect: 
*       "dir"
*       "full"
*       "%dw"
****************************************************************************/

BOOL CBlockDiagram::GetShortAssociativity(UINT assoc, CString & way)
    {
     switch(assoc)
        { /* assoc */
         case 0:  // reserved
            return FALSE;  // no information
         case 1:
            way.LoadString(IDS_DIRECT_MAPPED_SHORT);
            break;
         case 0xFF:
            way.LoadString(IDS_FULLY_ASSOCIATIVE_SHORT);
            break;
         default:
            { /* n-way */
             CString t;
             t.LoadString(IDS_NWAY_SHORT);
             way.Format(t, assoc);
            } /* n-way */
            break;
        } /* assoc */
     return TRUE;
    } // CBlockDiagram::GetAssociativity

/****************************************************************************
*                  CBlockDiagram::ComputeCacheTLBInformation
* Inputs:
*       CCacheTLBInfo & block: Block to fill
*       const BYTE * RelevantDescriptors: Array of relevant descriptors
* Result: void
*       
* Effect: 
*       Computes an array of descriptors which are IDS_ resource numbers
*       to use for the short form and the long form (hover help)
****************************************************************************/

void CBlockDiagram::ComputeCacheTLBInformation(CCacheTLBInfo & region, const BYTE * RelevantDescriptors)
    {
     CByteArray descriptors;
     GetCPUID2Descriptors(descriptors);

     // For every descriptor that is in 'descriptors', add its information to the 
     for(int i = 0; i < descriptors.GetSize(); i++)
        { /* see if present */
         if(strchr((LPCSTR)RelevantDescriptors, descriptors[i]))
            { /* relevant */
             region.Add(IDS_CTLB_00H + descriptors[i]);
            } /* relevant */
        } /* see if present */
    } // CBlockDiagram::ComputeCacheTLBInformation

/****************************************************************************
*                    CBlockDiagram::FormatExtendedTLBInfo
* Inputs:
*       UINT assoc:
*       UINT count:
*       CString & shortDesc
*       UINT ShortFmt:
*       CString & LongDesc:
*       UINT LongFmt:
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       ¶
****************************************************************************/

BOOL CBlockDiagram::FormatExtendedTLBInfo(UINT assoc, UINT count, CString & shortDesc, UINT shortFmt, CString & longDesc, UINT longFmt)
    {
     CString fmt;
     fmt.LoadString(shortFmt); // [I|D] 2M+4M×%s×%d
     
     CString way;

     if(!GetShortAssociativity(assoc, way))
        return FALSE;

     shortDesc.Format(fmt, way, count);

     fmt.LoadString(longFmt); // [Instruction|Data] 2M+4M pages, %s, %d entries

     GetLongAssociativity(assoc, way);

     longDesc.Format(fmt, way, count);
     
     return TRUE;
    } // CBlockDiagram::FormatExtendedTLBInfo

/****************************************************************************
*                CBlockDiagram::ComputeExtendedTLBInformation
* Inputs:
*       CCacheTLBInfo & region: Region to update/add
* Result: void
*       
* Effect: 
*       If available adds TLB information from the extended registers
* Notes:
*       CPUID(5):EAX
*               +--------+--------+--------+--------+
*               |D 2M ass|D 2M cnt|I 2M ass|I 2M cnt|
*               +--------+--------+--------+--------+
*                       |   |             |  |   
*               D 2M+4M×%dw×%d    I 2M+4M×%d×%d
*               IDS_FMT_SHORT_2M_TLBD      IDS_FMT_SHORT_2M_TLBI
*
*               IDS_FMT_LONG_2M_TLBD: Data TLB, 2M+4M  pages, %s associative, %d entries
*               IDS_FMT_LONG_2M_TLBI: Instruction TLB, 2M+4M pages, %s associative, %d entries
*        CPUID(5):EBX
*               +--------+--------+--------+--------+
*               |D 4K ass|D 4K cnt|I 4K ass|I 4K cnt|
*               +--------+--------+--------+--------+
*                      |   |              |  |   
*                D 4K×%dw×%d     I 2M+4M×%d×%d
*               IDS_FMT_SHORT_4K_TLBD      IDS_FMT_SHORT_4K_TLBI
*               IDS_FMT_LONG_4K_TLBD: Data TLB, 4K pages, %s associative, %d entries
*               IDS_FMT_LONG_4K_TLBI: Instruction TLB, 4K pages, %s associative, %d entries
****************************************************************************/

void CBlockDiagram::ComputeExtendedTLBInformation(CCacheTLBInfo & region)
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(0x80000000, &regs);
     if(regs.EAX < 0x80000005)
        return;  // no extended information

     CurrentProcessor.GetCPUID(0x80000005, &regs);

     EAX5x EAX;
     EAX.w = regs.EAX;

     CString ShortDesc;
     CString LongDesc;
     if(FormatExtendedTLBInfo(EAX.AMD.DataAssoc, EAX.AMD.DataCount,
                              ShortDesc, IDS_FMT_SHORT_2M_TLBD,
                              LongDesc,  IDS_FMT_LONG_2M_TLBD))
        { /* got extended */
         region.Add(LongDesc, ShortDesc);
        } /* got extended */
     if(FormatExtendedTLBInfo(EAX.AMD.InstAssoc, EAX.AMD.InstCount,
                              ShortDesc, IDS_FMT_SHORT_2M_TLBI,
                              LongDesc,  IDS_FMT_LONG_2M_TLBI))
        { /* got extended */
         region.Add(LongDesc, ShortDesc);
        } /* got extended */

     EBX5x EBX;
     EBX.w = regs.EBX;

     if(FormatExtendedTLBInfo(EBX.AMD.DataAssoc, EBX.AMD.DataCount,
                              ShortDesc, IDS_FMT_SHORT_4K_TLBD,
                              LongDesc,  IDS_FMT_LONG_4K_TLBD))
        { /* got extended */
         region.Add(LongDesc, ShortDesc);
        } /* got extended */
     if(FormatExtendedTLBInfo(EBX.AMD.InstAssoc, EBX.AMD.InstCount,
                              ShortDesc, IDS_FMT_SHORT_4K_TLBI,
                              LongDesc,  IDS_FMT_LONG_4K_TLBI))
        { /* got extended */
         region.Add(LongDesc, ShortDesc);
        } /* got extended */
    } // CBlockDiagram::ComputeExtendedTLBInformation

/****************************************************************************
*                      CBlockDiagram::FormatL1CacheInfo
* Inputs:
*       UINT CacheSize: Cache size in Kb
*       UINT Associativity: Cache associativity
*       UINT LinesPerTag: Lines per tag
*       UINT LineSize: Cache line size
*       CString & LongDesc:
*       UINT LongFmt:
*       CString & ShortDesc:
*       UINT ShortFmt:
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Computes L1 information
****************************************************************************/

BOOL CBlockDiagram::FormatL1CacheInfo(UINT CacheSize, UINT Associativity, UINT LinesPerTag, UINT LineSize, CString & LongDesc, UINT LongFmt, CString & ShortDesc, UINT ShortFmt )
    {
     // 1st level data cache, %dK, %s, %d byte line size
     // D %dK×%s×%D
     // 1st level instruction cache, %dK, %s, %d byte line size
     // I %dK×%s×%D
     CString assoc;
     if(!GetShortAssociativity(Associativity, assoc))
        return FALSE;
     CString fmt;
     fmt.LoadString(ShortFmt);
     ShortDesc.Format(fmt, CacheSize, assoc, LineSize);

     if(!GetLongAssociativity(Associativity, assoc))
        return FALSE;
     fmt.LoadString(LongFmt);
     LongDesc.Format(fmt, CacheSize, assoc, LineSize);

     return TRUE;
    } // CBlockDiagram::FormatL1CacheInfo

/****************************************************************************
*                 CBlockDiagram::ComputeExtendedL1Information
* Inputs:
*       CCacheTLBInfo & region: Region to update/add
* Result: void
*       
* Effect: 
*       If extended info exists, adds L1 cache info
****************************************************************************/

void CBlockDiagram::ComputeExtendedL1Information(CCacheTLBInfo & region)
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(0x80000000, &regs);
     if(regs.EAX < 0x80000005)
        return;  // no extended information

     CurrentProcessor.GetCPUID(0x80000005, &regs);

     CString ShortDesc;
     CString LongDesc;

     ECX5x ECX;
     ECX.w = regs.ECX;

     if(FormatL1CacheInfo(ECX.AMD.CacheSize, ECX.AMD.Associativity,
                          ECX.AMD.LinesPerTag, ECX.AMD.LineSize,
                          LongDesc, IDS_FMT_L1_DATA_LONG,
                          ShortDesc, IDS_FMT_L1_DATA_SHORT))
        { /* add it */
         region.Add(LongDesc, ShortDesc);
        } /* add it */

     EDX5x EDX;
     EDX.w = regs.EDX;

     if(FormatL1CacheInfo(EDX.AMD.CacheSize, EDX.AMD.Associativity,
                          EDX.AMD.LinesPerTag, EDX.AMD.LineSize,
                          LongDesc, IDS_FMT_L1_INST_LONG,
                          ShortDesc,IDS_FMT_L1_INST_SHORT))
        { /* add it */
         region.Add(LongDesc, ShortDesc);
        } /* add it */
    } // CBlockDiagram::ComputeExtendedL1Information

/****************************************************************************
*                    CBlockDiagram::GetLongL2Associativity
* Inputs:
*       UINT assoc: Associativity
*       CString & way: Place to put way
* Result: BOOL
*       TRUE if successful
*       FALSE if error
****************************************************************************/

BOOL CBlockDiagram::GetLongL2Associativity(UINT assoc, CString & way)
    {
     if(assoc == 0)
        return FALSE;

     way.LoadString(IDS_L2_ASSOCIATIVITY_00H + assoc);
     return !way.IsEmpty();
    } // CBlockDiagram::GetLongL2Associativity

/****************************************************************************
*                    CBlockDiagram::GetShortL2Associativity
* Inputs:
*       UINT assoc: Associativity
*       CString & way: Place to put way
* Result: BOOL
*       TRUE if successful
*       FALSE if error
****************************************************************************/

BOOL CBlockDiagram::GetShortL2Associativity(UINT assoc, CString & way)
    {
     if(assoc == 0)
        return FALSE;

     way.LoadString(IDS_L2_SHORT_ASSOCIATIVITY_00H + assoc);
     return !way.IsEmpty();
    } // CBlockDiagram::GetLongL2Associativity

/****************************************************************************
*                      CBlockDiagram::FormatL2CacheInfo
* Inputs:
*       UINT CacheSize: Cache size in Kb
*       UINT Associativity: Cache associativity
*       UINT LinesPerTag: Lines per tag
*       UINT LineSize: Cache line size
*       CString & LongDesc:
*       UINT LongFmt:
*       CString & ShortDesc:
*       UINT ShortFmt:
* Result: BOOL
*       TRUE if successful
*       FALSE if no cache info
* Effect: 
*       ¶
****************************************************************************/

BOOL CBlockDiagram::FormatL2CacheInfo(UINT CacheSize, UINT Associativity, UINT LinesPerTag, UINT LineSize, CString & LongDesc, UINT LongFmt, CString & ShortDesc, UINT ShortFmt)
    {
     CString assoc;

     if(!GetShortL2Associativity(Associativity, assoc))
        return FALSE;

     CString fmt;
     fmt.LoadString(ShortFmt); // %dK×%s×%d
     
     ShortDesc.Format(fmt, CacheSize, assoc, LineSize);

     if(!GetLongL2Associativity(Associativity, assoc))
        return FALSE;

     fmt.LoadString(LongFmt);
     LongDesc.Format(fmt, CacheSize, assoc, LineSize);
     
     return TRUE;
    } // CBlockDiagram::FormatL2CacheInfo

/****************************************************************************
*                 CBlockDiagram::ComputeExtendedL2Information
* Inputs:
*       CCacheTLBInfo & region: 
* Result: void
*       
* Effect: 
*       Computes the L2 information
****************************************************************************/

void CBlockDiagram::ComputeExtendedL2Information(CCacheTLBInfo & region)
    {
     CPUregs regs;
     CurrentProcessor.GetCPUID(0x80000000, &regs);
     if(regs.EAX < 0x80000006)
        return;  // no extended information

     CurrentProcessor.GetCPUID(0x80000006, &regs);

     CString ShortDesc;
     CString LongDesc;

     ECX6x ECX;
     ECX.w = regs.ECX;

     if(FormatL2CacheInfo(ECX.AMD.CacheSize, ECX.AMD.Associativity, ECX.AMD.LinesPerTag, ECX.AMD.LineSize,
                          LongDesc, IDS_FMT_L2_LONG,
                          ShortDesc, IDS_FMT_L2_SHORT))
        { /* add it */
         region.Add(LongDesc, ShortDesc);
        } /* add it */
    } // CBlockDiagram::ComputeExtendedL2Information

/****************************************************************************
*                  CBlockDiagram::ComputePrefetchInformation
* Result: void
*       
* Effect: 
*       Computes the prefetch information
****************************************************************************/

void CBlockDiagram::ComputePrefetchInformation()
    {
     if(QueryPrefetch())
        { /* has prefetch data */
         CByteArray descriptors;
         GetCPUID2Descriptors(descriptors);
         
         if(descriptors.GetSize() == 0)
            return;
         
         for(int i = 0; i < descriptors.GetSize(); i++)
            { /* scan it */
             LPSTR p = strchr((LPCSTR)PrefetchInfo, descriptors[i]);
             if(p != NULL)
                { /* got it */
                // String is extended to be "NNN-byte prefetching"
                 CString s;
                 s.LoadString(IDS_CTLB_00H + descriptors[i]);
                 int n = _ttoi(s);
                 ASSERT(n != 0);
                 if(n != 0)
                    { /* has value */
                     CString d;
                     d.Format(_T("%d"), n);
                     c_PrefetchRegion.SetWindowText(d);
                    } /* has value */
                 c_PrefetchRegion.SetToolTipText(s);
                } /* got it */
            } /* scan it */
        } /* has prefetch data */
     
    } // CBlockDiagram::ComputePrefetchInformation

/****************************************************************************
*                         CBlockDiagram::OnSetActive
* Result: BOOL
*       Superclass return value
* Effect: 
*       Computes the layout of the objects
****************************************************************************/

BOOL CBlockDiagram::OnSetActive()
    {
     c_TLBRegion.Reset();
     ComputeCacheTLBInformation(c_TLBRegion, TLBInfo);
     ComputeExtendedTLBInformation(c_TLBRegion);

     c_L1CacheRegion.Reset();
     ComputeCacheTLBInformation(c_L1CacheRegion, L1CacheInfo);
     ComputeExtendedL1Information(c_L1CacheRegion);

     c_L2CacheRegion.Reset();
     ComputeCacheTLBInformation(c_L2CacheRegion, L2CacheInfo);
     ComputeExtendedL2Information(c_L2CacheRegion);

     ComputeLayout();

     ComputePrefetchInformation();
     return CPropertyPage::OnSetActive();
    }

/****************************************************************************
*                         CBlockDiagram::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes controls
****************************************************************************/

BOOL CBlockDiagram::OnInitDialog()
    {
     CPropertyPage::OnInitDialog();

     // TODO:  Add extra initialization here

     c_CPURegion.ModifyStyle(WS_BORDER, 0, SWP_DRAWFRAME);

     c_CPURegion.SetBkColor(RGB(102, 255, 51));
     
     c_CPUCoreRegion.SetBkColor(c_CPURegion.GetBkColor());
     c_CPUCoreRegion.SetObjectColor(RGB(255, 153, 51));
     
     c_PrefetchRegion.SetBkColor(c_CPURegion.GetBkColor());
     c_PrefetchRegion.SetDirection(CArrow::LEFT);

     c_LogicalAddressLinesRegion.SetBkColor(c_CPURegion.GetBkColor());
     c_LogicalAddressLinesRegion.SetObjectColor(RGB(255, 255, 0));

     c_PhysicalAddressLinesRegion.SetBkColor(::GetSysColor(COLOR_3DFACE));
     c_PhysicalAddressLinesRegion.SetObjectColor(RGB(255,255,0));

     c_L1CacheRegion.SetBkColor(c_CPURegion.GetBkColor());
     c_L1CacheRegion.SetObjectColor(RGB(102, 204, 255));

     c_L2CacheRegion.SetBkColor(::GetSysColor(COLOR_3DFACE));
     c_L2CacheRegion.SetObjectColor(RGB(255, 153, 204));

     c_TLBRegion.SetBkColor(::GetSysColor(COLOR_3DFACE));
     c_TLBRegion.SetObjectColor(RGB(182, 224, 227));
     c_TLBRegion.SetGap(0);

     // TODO: L3 caching

     EnableTrackingToolTips(TRUE);

     initialized = TRUE;
     return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
    }

/****************************************************************************
*                        CBlockDiagram::ComputeLayout
* Result: void
*       
* Effect: 
*       Computes the layout of the components
****************************************************************************/

void CBlockDiagram::ComputeLayout()
    {
     if(!initialized)
        return;
     DECLARE_REGIONS();
     
     int count = 0;
     for(int i = 0; i < sizeof(Regions) / sizeof(Regions[0]); i++)
        { /* count regions */
         //ASSERT(Regions[i].overlap != 0 ? Regions[i].query == NULL : TRUE);
         if(Regions[i].query == NULL)
            count += Regions[i].units - Regions[i].overlap;
         else
            count += (Regions[i].query() ? Regions[i].units : 0);
        } /* count regions */

     TRACE("region count=%d\n",count);
     CRect r;
     GetClientRect(&r);
     double unit = (double)r.Width() / (double)count;  // number of units of width across
     TRACE("width = %d unit = %g result = %g\n", r.Width(), unit, unit * count);

     int left = r.left;
     for(int i = 0; i < sizeof(Regions) / sizeof(Regions[0]); i++)
        { /* lay out windows */
         if(Regions[i].query != NULL)
            { /* see if skip */
             if(!Regions[i].query())
                { /* not present */
                 Regions[i].wnd.ShowWindow(SW_HIDE);
                 continue;
                } /* not present */
             else
                { /* is present */
                 Regions[i].wnd.ShowWindow(SW_SHOW);
                } /* is present */
            } /* see if skip */

         int width;

         //----------------------------------------------------------------
         // If it is the rightmost element, simply expand it to fill the
         // rest of the available space
         if(i < (sizeof(Regions) / sizeof(Regions[0])) - 1)
            width = (int)(unit * Regions[i].units);
         else
            width = r.right - left; // last one fills out area
         //----------------------------------------------------------------
         int height;
         int top;
         
         if(Regions[i].align == BD_CENTER)
            { /* center vertically */
             height = (r.Height() * Regions[i].percent) / 100;
             top = r.top + (r.Height() - height) / 2;
            } /* center vertically */
         else
         if(Regions[i].align == BD_BOTTOM)
            { /* at bottom */
             height = (r.Height() * Regions[i].percent) / 100;
             top = r.bottom - height;
            } /* at bottom */
         else
         if(Regions[i].align == BD_TOP)
            { /* at top */
             height = (r.Height() * Regions[i].percent) / 100;
             top = 0;
            } /* at top */
         else
            { /* unknown */
             ASSERT(FALSE);
             height = (r.Height() * Regions[i].percent) / 100;
             top = 0;
            } /* unknown */

         Regions[i].wnd.SetWindowPos(NULL, left, top, width, height, SWP_NOZORDER);

         if(Regions[i].overlap == 0)
            left = left + width;
         Regions[i].wnd.Invalidate();
        } /* lay out windows */
    } // CBlockDiagram::ComputeLayout

/****************************************************************************
*                            CBlockDiagram::OnSize
* Inputs:
*       UINT nType:
*       int cx: New width
*       int cy: New height
* Result: void
*       
* Effect: 
*       Recomputes the layout of the components
****************************************************************************/

void CBlockDiagram::OnSize(UINT nType, int cx, int cy)
    {
     CPropertyPage::OnSize(nType, cx, cy);

     ComputeLayout();
    }

/****************************************************************************
*                        CBlockDiagram::QueryPrefetch
* Result: BOOL
*       TRUE if the prefetch data is available
*       FALSE if it is not
* Effect: 
*       Queries the prefetch data
****************************************************************************/

/* static */ BOOL CBlockDiagram::QueryPrefetch()
    {
     CByteArray descriptors;
     GetCPUID2Descriptors(descriptors);

     if(descriptors.GetSize() == 0)
        return FALSE;

     for(int i = 1; i < descriptors.GetSize(); i++)
        if(strchr((LPCSTR)PrefetchInfo, descriptors[i]) != NULL)
           return TRUE;
     return FALSE;
    } // CBlockDiagram::QueryPrefetch

/****************************************************************************
*                           CBlockDiagram::QueryL3
* Result: BOOL
*       TRUE if there is an L3 cache
*       FALSE if there is no L3 cache
****************************************************************************/

/* static */ BOOL CBlockDiagram::QueryL3()
    {
     CByteArray descriptors;
     GetCPUID2Descriptors(descriptors);

     if(descriptors.GetSize() == 0)
         return FALSE;

     for(int i = 0; L3CacheInfo[i] != 0x00; i++)
        if(strchr((LPCSTR)descriptors.GetData(), L3CacheInfo[i]))
           return TRUE;
     return FALSE;
    } // CBlockDiagram::QueryL3

/****************************************************************************
*                        CBlockDiagram::PostNcDestroy
* Result: void
*       
* Effect: 
*       Deletes the object
****************************************************************************/

void CBlockDiagram::PostNcDestroy()
    {
     CPropertyPage::PostNcDestroy();
     delete this;
    }

/****************************************************************************
*                       CBlockDiagram::OnToolTipNotify
* Inputs:
*       UINT id: Control ID
*       NMHDR * pNMHDR:
*       LRESULT * pResult:
* Result: BOOL
*       TRUE if handled
*       FALSE if not
* Effect: 
*       Supplies the tooltip text
* Notes:
* typedef struct {
*      NMHDR     hdr;        // required for all WM_NOTIFY messages
*      // typedef struct tagNMHDR {
*      //    HWND hwndFrom;
*      //    UINT idFrom;
*      //    UINT code;
*      // } NMHDR;
*      LPTSTR    lpszText;   // see below
*      TCHAR     szText[80]; // buffer for tool tip text
*      HINSTANCE hinst;      // see below
*      UINT      uflags;     // flag indicating how to interpret the 
*                            // idFrom member of the NMHDR structure
*                            // that is included in the structure
*     } TOOLTIPTEXT, FAR *LPTOOLTIPTEXT;
****************************************************************************/

BOOL CBlockDiagram::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
    {
     CWnd * wnd = CWnd::FromHandle((HWND)pNMHDR->idFrom);

     if(wnd->SendMessage( WM_NOTIFY, pNMHDR->idFrom, (LPARAM)pNMHDR))
        return TRUE;

     return FALSE;
    } // CBlockDiagram::OnToolTipNotify
