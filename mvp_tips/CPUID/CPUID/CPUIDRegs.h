#pragma once
#include "CPUIDx86.h"

/*****************************************************************************
  CPUID(0): Basic CPUID information

  EAX: Highest value for CPUID basic information
  EBX: CPU type name characters 0..3
  ECX: CPU type name characters 8..11
  EDX: CPU type name characeters 4..7

  EBX+EDX+ECX is the full CPU type name
*****************************************************************************/

/*****************************************************************************
  CPUID(1): Basic feature information

==================================================================================
  EAX: (Intel)
  
   31    28 27            20 19    16 1514 1312 11     8 7      4 3      0
  +--------+----------------+--------+----+----+--------+--------+--------+
  |########|Extended family |Extmodel|####|type|familyid| model  |stepping|
  +--------+----------------+--------+----+----+--------+--------+--------+

  EAX: (AMD)
   31    28 27            20 19    16 15    12 11     8 7      4 3      0
  +--------+----------------+--------+--------+--------+--------+--------+
  |########|Extended family |Extmodel|########|familyid| model  |stepping|
  +--------+----------------+--------+--------+--------+--------+--------+
  type:
    IDS_PROCESSOR_00B       "Original OEM processor"
    IDS_PROCESSOR_01B       "Intel Overdrive ® processor"
    IDS_PROCESSOR_10B       "Dual processor"
    IDS_PROCESSOR_11B       "Intel reserved"

  model:
    if(familyid == 0x6 || familyid == 0xF)
       computed model = model + (extended model << 4)
    else
       computed model = model;

  family:
    if(familyid == 0xF)
       computed family = familyid + extended family;
    else
       computed family = familyid;
       
==================================================================================
  EBX:

   31            24 23            16 15             8 7              0
   +----------------+----------------+----------------+----------------+
   | Initial APIC ID|LogicalProcessor|CLFLUSHLineSize |   Brand Index  |
   +----------------+----------------+----------------+----------------+
                                       in units of 8

    IDS_BRAND_INDEX_01H     "Intel ® Celeron ® processor"
    IDS_BRAND_INDEX_02H     "Intel ® Pentium ® III processor"
    IDS_BRAND_INDEX_03H     "Intel ® Pentium ® III Xeon(tm) processor\nIntel ® Celeron ® processor"
    IDS_BRAND_INDEX_04H     "Intel ® Pentium ® III processor"
    IDS_BRAND_INDEX_06H     "Mobile Intel ® Pentium ® III processor-M"
    IDS_BRAND_INDEX_07H     "Mobile Intel ® Celeron ® processor"
    IDS_BRAND_INDEX_08H     "Intel ® Pentium ® 4 processor"
    IDS_BRAND_INDEX_09H     "Intel ® Pentium ® 4 processor"
    IDS_BRAND_INDEX_0AH     "Intel ® Celeron ® processor"
    IDS_BRAND_INDEX_0BH     "Intel ® Xeon(tm) processor\nIntel ® Xeon(tm) processor MP"
    IDS_BRAND_INDEX_0CH     "Intel ® Xeon(tm) processor MP"
    IDS_BRAND_INDEX_0EH     "Mobile Intel ® Pentium ® 4 processor\nIntel ® Xeon(tm) processor"
    IDS_BRAND_INDEX_0FH     "Mobile Intel ® Celeron ® processor"
    IDS_BRAND_INDEX_11H     "Mobile Genuine Intel ® processor"
    IDS_BRAND_INDEX_12H     "Intel ® Celeron ® M processor"
    IDS_BRAND_INDEX_13H     "Mobile Intel ® Celeron ® processor"
    IDS_BRAND_INDEX_14H     "Intel ® Celeron ® processor"
    IDS_BRAND_INDEX_15H     "Mobile Genuine Intel ® processor"
    IDS_BRAND_INDEX_16H     "Intel ® Pentium ® M processor"
    IDS_BRAND_STRING_17H    "Mobile Intel ® Celeron ® processor"
    18h..FFh                reserved
==================================================================================
  ECX: Feature set (Intel)

    31                                14 13 12 11 10  9  8  7  6  5  4  3 2  1  0
   +------------------------------------+--+--+--+--+--+--+--+--+--+--+--+----+--+
   |####################################|CX|##|##|L1|##|T2|ES|##|VM|CP|MW|####|S3|
   +------------------------------------+--+--+--+--+--+--+--+--+--+--+--+----+--+
  ECX: Feature set (AMD)
    31                                14 13 12 11     8 7      4 3    1  0
   +------------------------------------+--+--+--------+--------+------+--+
   |####################################|CX|##|########|########|######|S3|
   +------------------------------------+--+--+--------+--------+------+--+

   CX - CompareAndExchange16B supported
   L1 - L1 context ID supported
   T2 - Thermal Monitor 2 supported
   ES - Enhanced SpeedStep technology
   VM - VMX technology
   CP - CPL-qualified debug store
   MW - MWAIT supported
   S3 - SSE3 supported

==================================================================================
   EDX: Extended feature bits (Intel)

     31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |PB|##|TM|HT|SS|S2|S1|FX|MM|AC|DS|##|CF|PN|P3|PT|CM|MC|PG|MT|SE|##|AP|CX|ME|PA|MS|TS|PS|DE|V8|FP|
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

   EDX: Extended feature bits (AMD)
     31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |##|##|##|HT|##|S2|S1|FX|MM|##|##|##|CF|##|P3|PT|CM|MC|PG|MT|SE|##|AP|CX|ME|PA|MS|TS|PS|DE|V8|FP|
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

    PB - Pending Break Enable
    TM - Thermal Monitor
    HT - Hyperthreading
    SS - Self-Snoop
    S2 - SSE2 extensions
    S1 - SSE extensions
    MM - MMX
    AC - ACPI
    DS - Debug Store
    CF - CFLUSH instruction
    PN - Processor serial number
    P3 - PSE36 Size extensions
    PT - Page attribute table
    CM - CMOV: Conditional move/compare instruction
    MC - Machine Check Architecture
    PG - Global PTE bit
    MT - Memory Type Range Registers
    SE - SYSENTER/SYSEXIT
    AP - APIC on-chip
    CX - CMXCHG8B
    ME - Machine Check Exception
    PA - Physical Address Extension
    MS - RDMSR/WRMSR support
    TS - TimeStamp Counter
    PS - Page Size extensions
    DE - Debugging extensions
    V8 - Virtual 8086 extensions
    FP - FPU87 on chip
*****************************************************************************/

typedef union {
   struct {                      // low order
      UINT SteppingID:4;         // 3..0
      UINT ModelID:4;            // 7..4
      UINT FamilyID:4;           // 11..8
      UINT ProcessorType:2;      // 13..12
      UINT Reserved2:2;          // 15..14
      UINT ExtendedModel:4;      // 19..16
      UINT ExtendedFamily:8;     // 27..20
      UINT Reserved:4;           // 31..28
   } Intel;                      // high order

   struct {                      // low order
      UINT SteppingID:4;         // 3..0
      UINT ModelID:4;            // 7..4
      UINT FamilyID:4;           // 11..8
      UINT Reserved2:4;          // 15..12
      UINT ExtendedModel:4;      // 19..16
      UINT ExtendedFamily:8;     // 27..20
      UINT Reserved:4;           // 31..28
   } AMD;                        // high order
   UINT w;
} EAX1b;

//=============================================================================
typedef union {
   struct { // low order
      UINT BrandIndex:8;
      UINT CLFLUSHLineSize:8;
      UINT LogicalProcessors:8;
      UINT InitialAPICID:8;
   } bits;  // high order
   UINT w;
} EBX1b;

//=============================================================================
typedef union {
   struct { // low order
      UINT SSE3:1;                 // 0
      UINT Reserved1:2;            // 1..2
      UINT MWAIT:1;                // 3
      UINT CPL:1;                  // 4
      UINT VMX:1;                  // 5
      UINT Reserved2:1;            // 6
      UINT EST:1;                  // 7
      UINT TM2:1;                  // 8
      UINT Reserved3:1;            // 9
      UINT L1:1;                   // 10
      UINT Reserved4:1;            // 11
      UINT Reserved5:1;            // 12
      UINT CMPXCHG16B:1;           // 13
      UINT XPTR:1;                 // 14
      UINT Reserved6:17;           // 15..31
   } Intel;  // high order
   struct { // low order
      UINT SSE3:1;                 // 0
      UINT Reserved1:3;            // 3..1
      UINT Reserved2:4;            // 7..4
      UINT Reserved3:4;            // 11..8
      UINT Reserved5:1;            // 12
      UINT CMPXCHG16B:1;           // 13
      UINT Reserved6:18;           // 14..31
   } AMD;  // high order
   UINT w;
} ECX1b;

//=============================================================================
typedef union {
   struct { // low order
      UINT FPU:1;                  // 0
      UINT VME:1;                  // 1
      UINT DE:1;                   // 2
      UINT PSE:1;                  // 3
      UINT MSR:1;                  // 4
      UINT TSC:1;                  // 5
      UINT PAE:1;                  // 6
      UINT MCE:1;                  // 7
      UINT CX8:1;                  // 8
      UINT APIC:1;                 // 9
      UINT Reserved1:1;            // 10
      UINT SEP:1;                  // 11
      UINT MTRR:1;                 // 12
      UINT PGE:1;                  // 13
      UINT MCA:1;                  // 14
      UINT CMOV:1;                 // 15
      UINT PAT:1;                  // 16
      UINT PSE36:1;                // 17
      UINT PSN:1;                  // 18
      UINT CFLSH:1;                // 19
      UINT Reserved2:1;            // 20
      UINT DS:1;                   // 21
      UINT ACPI:1;                 // 22
      UINT MMX:1;                  // 23
      UINT FXSR:1;                 // 24
      UINT SSE:1;                  // 25
      UINT SSE2:1;                 // 26
      UINT SS:1;                   // 27
      UINT HTT:1;                  // 28
      UINT TM:1;                   // 29
      UINT Reserved3:1;            // 30
      UINT PBE:1;                  // 31
   } Intel;  // high order
   struct { // low order
      UINT FPU:1;                  // 0
      UINT VME:1;                  // 1
      UINT DE:1;                   // 2
      UINT PSE:1;                  // 3
      UINT MSR:1;                  // 4
      UINT TSC:1;                  // 5
      UINT PAE:1;                  // 6
      UINT MCE:1;                  // 7
      UINT CX8:1;                  // 8
      UINT APIC:1;                 // 9
      UINT Reserved1:1;            // 10
      UINT SEP:1;                  // 11
      UINT MTRR:1;                 // 12
      UINT PGE:1;                  // 13
      UINT MCA:1;                  // 14
      UINT CMOV:1;                 // 15
      UINT PAT:1;                  // 16
      UINT PSE36:1;                // 17
      UINT Reserved5:1;            // 18
      UINT CFLSH:1;                // 19
      UINT Reserved2:3;            // 22..20
      UINT MMX:1;                  // 23
      UINT FXSR:1;                 // 24
      UINT SSE:1;                  // 25
      UINT SSE2:1;                 // 26
      UINT Reserved4:1;            // 27
      UINT HTT:1;                  // 28
      UINT Reserved3:3;            // 31..29
   } AMD;  // high order
   UINT w;
} EDX1b;

/*****************************************************************************
  CPUID(2): Cache and TLB values (Intel only)

  EAX:
   31
   +--------+--------+--------+--------+
   |0  desc |  desc  |  desc  | count  |
   +--------+--------+--------+--------+

   EBX:
   +--------+--------+--------+--------+
   |0  desc |  desc  |  desc  |  desc  |
   +--------+--------+--------+--------+
   |1#######|########|########|########|
   +--------+--------+--------+--------+

   ECX:
   +--------+--------+--------+--------+
   |0  desc |  desc  |  desc  |  desc  |
   +--------+--------+--------+--------+
   |1#######|########|########|########|
   +--------+--------+--------+--------+

   EDX:
   +--------+--------+--------+--------+
   |0  desc |  desc  |  desc  |  desc  |
   +--------+--------+--------+--------+
   |1#######|########|########|########|
   +--------+--------+--------+--------+

    IDS_CTLB_00H            "Null descriptor"
    IDS_CTLB_01H            "Instruction TLB: 4K pages, 4-way set associative, 32 entries"
    IDS_CTLB_02H            "Instruction TLB: 4K pages, 4-way set associative, 2 entries"
    IDS_CTLB_03H            "Data TLB: 4K pages, 4-way set associative, 64 entries"
    IDS_CTLB_04H            "Data TLB: 4M pages, 4-way set associative, 8 entries"
    IDS_CTLB_06H            "1st-level instruction cache: 8K, 4-way set associative, 32 byte line size"
    IDS_CTLB_08H            "1st-level instruction cache: 16K, 4-way set associative, 32 byte line size"
    IDS_CTLB_0AH            "1st-level data cache: 8K, 2-way set associative, 32 byte line size"
    IDS_CTLB_0CH            "1st-level data cache: 16K, 4-way set associative, 32 byte line size"
    IDS_CTLB_22H            "3rd-level cache: 512K, 4-way set associative, 64-byte line size, 2 lines per sector"
    IDS_CTLB_23H            "3rd-level cache; 1M, 8-way set associative, 64 byte line size, 2 lines per sector"
    IDS_CTLB_25H            "3rd-level cache: 2M, 8-way set associative, 64 byte line size, 2 lines per sector"
    IDS_CTLB_29H            "3rd-level cache: 4M, 8-way set associative, 64 byte line size, 2 lines per sector"
    IDS_CTLB_2CH            "1st-level data cache: 32K, 8-way asociative, 64 byte line size"
    IDS_CTLB_30H            "1st-level instruction cache: 32K, 8-way set associative, 64 byte line size"
    IDS_CTLB_40H            "No 2nd-level cache, or, if processor contains a valid 2nd-level cache, no 3rd-level cache"
    IDS_CTLB_41H            "2nd-level cache: 128K, 4-way set associative, 32 byte line size"
    IDS_CTLB_42H            "2nd-level cache: 256K, 4-way set associative, 32 byte line size"
    IDS_CTLB_43H            "2nd-level cache: 512K, 4-way set associative, 32 byte line size"
    IDS_CTLB_44H            "2nd-level cache: 1M, 4-way set associative, 32 byte line size"
    IDS_CTLB_45H            "2nd-level cache: 2M, 4-way set associative, 32 byte line size"
    IDS_CTLB_46H            "3rd-level cache: 4M, 4-way set associative, 64 byte line size"
    IDS_CTLB_47H            "3rd-level cache, 8M, 8-way set associative, 64 byte line size"
    IDS_CTLB_50H            "Instruction TLB: 4K and 2M or 4M pages, 64 entries"
    IDS_CTLB_51H            "Instruction TLB: 4K and 2M or 4M pages, 128 entries"
    IDS_CTLB_52H            "Instruction TLB: 4K and 2M or 4M pages, 256 entries"
    IDS_CTLB_5BH            "Data TLB: 4K and 4M pages, 64 entries"
    IDS_CTLB_5CH            "Data TLB: 4K and 4M pages, 128 entries"
    IDS_CTLB_5DH            "Data TLB: 4K and 4M pages, 256 entries"
    IDS_CTLB_60H            "1st-level data cache: 16K, 8-way set associative, 64 byte line size"
    IDS_CTLB_66H            "1st-level data cache: 8K, 4-way set associative, 64 byte line size"
    IDS_CTLB_67H            "1st-level data cache: 16K, 4-way set associative, 64 byte line size"
    IDS_CTLB_68H            "1st-level data cache: 32K, 4-way set associative, 64 byte line size"
    IDS_CLTB_70H            "Trace cache: 12K-uOp, 8-way set associative"
    IDS_CTLB_71H            "Trace cache: 16K-uOp, 8-way set associative"
    IDS_CTLB_72H            "Trace cache: 32K-uOp, 8-way set associative"
    IDS_CTLB_78H            "2nd-level cache: 128K, 8-way set associative, 64 byte line size"
    IDS_CTLB_79H            "2nd-level cache: 128K, 8-way set associative, 64 byte line size, 2 lines per sector"
    IDS_CTLB_7AH            "2nd-level cache: 256K, 8-way set associative, 64 byte line size, 2 lines per sector"
    IDS_CTLB_7BH            "2nd-level cache: 512K, 8-way set associative, 64 byte line size, 2 lines per sector"
    IDS_CTLB_7CH            "2nd-level cache: 1M, 8-way set associative, 64 byte line size, 2 lines per sector"
    IDS_CTLB_7DH            "2nd-level cache: 2M, 8-way set associative, 64 byte line size"
    IDS_CTLB_7FH            "2nd-level cache: 512K, 2-way set associative, 64 byte line size"
    IDS_CTLB_82H            "2nd-level cache: 256K, 8-way set associative, 32 byte line size"
    IDS_CTLB_83H            "2nd-level cache: 512K, 8-way set associative, 32 byte line size"
    IDS_CTLB_84H            "2nd-level cache: 1M, 8-way set associative, 32 byte line size"
    IDS_CTLB_85H            "2nd-level cache: 2M, 8-way set associative, 32 byte line size"
    IDS_CTLB_86H            "2nd-level cache: 512K, 4-way set associative, 64 byte line size"
    IDS_CTLB_87H            "2nd-level cache: 1M, 8-way set associative, 64 byte line size"
    IDS_CTLB_B0H            "Instruction TLB: 4K pages, 4-way set associative, 128 entries"
    IDS_CTLB_B3H            "Data TLB: 4K pages, 4-way set associative, 128 entries"
    IDS_CTLB_F0H            "64-byte prefetching"
    IDS_CTLB_F1H            "128-byte prefetching"

*****************************************************************************/  

typedef union {
   CPUregs regs;
   BYTE descriptors[16];
} EREGS2;


/*****************************************************************************
  CPUID(3)
  EAX: Reserved
  EBX: Reserved
  ECX: Processor Serial Number <0..31>
  EDX: Processor Serial Number <63..32>

  Note that this is unsupported on all processors > Pentium III
*****************************************************************************/  

/*****************************************************************************
  CPUID(4)

  EAX:
   31        26 25                    14 13    10  9  8 7    5 4        0
  +------------+------------------------+--------+--+--+------+----------+
  | cores/pkg  | threads sharing cache-1|########|FA|SI|Level |   Type   |
  +------------+------------------------+--------+--+--+------+----------+
  FA - Fully associative                                            |
  SI - Self-initializing                                            |
                                                                    |
    +---------------------------------------------------------------+
    |
    IDS_CACHE_TYPE_01       "Data cache"
    IDS_CACHE_TYPE_02       "Instruction cache"
    IDS_CACHE_TYPE_03       "Unified (data + instruction) cache"

  EBX:
   31                22 21                12 11                     0
  +--------------------+--------------------+------------------------+
  | associativity - 1  | line partitions - 1|Coherency line size - 1 |
  +--------------------+--------------------+------------------------+

  ECX:
   31                                                               0
  +------------------------------------------------------------------+
  |                          Number of sets -1                       |
  +------------------------------------------------------------------+

  EDX: Reserved

*****************************************************************************/

typedef union {
   struct { // low order
      UINT CacheType:5;         //   4..0
      UINT CacheLevel:3;        //   7..5
      UINT SelfInitializing:1;  //      8
      UINT FullyAssociative:1;  //      9
      UINT Reserved:4;          // 13..10
      UINT ThreadsSharing:12;   // 25..14
      UINT CoresPerPackage:6;   // 31..26
   } bits;  // high order
   UINT w;
} EAX4b;

typedef union {
   struct { // low order
      UINT SystemCoherencyLineSize:12;   // 11..0
      UINT PhysicalLinePartitions:10;    // 21..12
      UINT WaysOfAssociativity:10;       // 32..22
   } bits;  // high order
   UINT w;
} EBX4b;


/*****************************************************************************
  CPUID(5)

  EAX:
   31                            16 15                             0
  +--------------------------------+--------------------------------+
  |################################|   Smallest monitor line size   |
  +--------------------------------+--------------------------------+

  EBX:
   31                            16 15                             0
  +--------------------------------+--------------------------------+
  |################################|    Largest monitor line size   |
  +--------------------------------+--------------------------------+

  ECX:
   31                                                             2  1  0
  +----------------------------------------------------------------+--+--+
  |################################################################|IB|ES|
  +----------------------------------------------------------------+--+--+
  ES: Enumeration supported beyond EAX/EBX
  IB: Interrupts supported as break events

  EDX:
   31                    20 19    16 15    12 11     8 7      4 3      0
  +------------------------+--------+--------+--------+--------+--------+
  |########################|   C4   |   C3   |   C2   |   C1   |   C0   |
  +------------------------+--------+--------+--------+--------+--------+

  Number of C0 sub C states supported using MWAIT
  Number of C1 sub C states supported using MWAIT
  Number of C2 sub C states supported using MWAIT
  Number of C3 sub C states supported using MWAIT
  Number of C4 sub C states supported using MWAIT
*****************************************************************************/  

typedef union {
   struct { // low order
      UINT SmallestMonitorLineSize:16;  // 15..0
      UINT Reserved2:16;                // 31..16
   } bits;  // high order
   UINT w;
} EAX5b;

typedef union {
   struct { // low order
      UINT LargestMonitorLineSize:16;   // 15..0
      UINT Reserved1:16;                // 31..16
   } bits;  // high order
   UINT w;
} EBX5b;

typedef union {
   struct { // low order
      UINT MWAITEnumerationSupported:1;  // 0
      UINT InterruptsAsBreakEvents:1;    // 1
      UINT Reserved3:30;                 // 31..2
   } bits;
   UINT w;
} ECX5b;

typedef union {
   struct { // low order
      UINT C0:4;                        // 0..3
      UINT C1:4;                        // 4..7
      UINT C2:4;                        // 8..11
      UINT C3:4;                        // 15..12
      UINT C4:4;                        // 19..16
      UINT Reserved4:12;                // 31..29
   } bits;  // high order
   UINT w;
} EDX5b;

/*****************************************************************************
  CPUID(6): Thermal and power management

  EAX:

   31                                                           1  0
  +--------------------------------------------------------------+--+
  |##############################################################|DS|
  +--------------------------------------------------------------+--+
  DS - Digital Temperature Sensor supporte

  EBX:

   31                                                           1  0
  +--------------------------------------------------------+--------+
  |########################################################| thcnt  |
  +--------------------------------------------------------+--------+
  thcnt - Number of interrupt thresholds in temperature sensor


  ECX:

   31                                                           1  0
  +--------------------------------------------------------------+--+
  |##############################################################|EC|
  +--------------------------------------------------------------+--+
  EC - ECNT/MCNT supported

*****************************************************************************/
typedef union {
   struct {                      // low order
      UINT SensorSupported:1;    // 0
      UINT Reserved1:31;         // 31..1
   } bits;                       // high order
   UINT w;
} EAX6b;

typedef union {
   struct {                      // low order
      UINT InterruptThresholds:4;// 3..0
      UINT Reserved2:26;         // 31..4
   } bits;                       // high order
   UINT w;
} EBX6b;

typedef union {
   struct {                      // low order
      UINT ACNT_MCNT:1;          // 0
      UINT Reserved3:31;         // 31..1
   } bits;                       // high order
   UINT w;
} ECX6b;

/*****************************************************************************
  CPUID(10): Performance monitoring

  EAX:
   31            24 23            16 15             8 7              0
  +----------------+----------------+----------------+----------------+
  | EBX vector len |  GP bit width  |    counters    |   version ID   |
  +----------------+----------------+----------------+----------------+

  EBX:
   31                                           7  6  5  4  3  2  1  0
  +----------------------------------------------+--+--+--+--+--+--+--+
  |##############################################|BM|BI|CM|CR|RC|IR|CC|
  +----------------------------------------------+--+--+--+--+--+--+--+

  CC - Core cycle event not available
  IR - Instruction retired event not available
  RC - Reference Cycles event not available
  CR - Last level cache reference event not available
  CM - Last-level cache-misses event not available
  BI - Branch Instruction retired event not available
  BM - Branch Mispredict retired event not available

  ECX: Reserved

  EDX:
   31                                 13 12               5 4        0
  +-------------------------------------+------------------+----------+
  |#####################################| width of counters| counters |
  +-------------------------------------+------------------+----------+

*****************************************************************************/

typedef union {
   struct { // low order
      UINT VersionID:8;         // 7..0
      UINT GPCounters:8;        // 15..8
      UINT GPCounterWidth:8;    // 23..16
      UINT EBXVectorLength:8;   // 31..24
   } bits;  // high order
   UINT w;
} EAX10b;

typedef union {
   struct { // low order
      UINT CoreCycleNA:1;            // 0
      UINT InstructionRetiredNA:1;   // 1
      UINT ReferenceCyclesNA:1;      // 2
      UINT CacheReferenceNA:1;       // 3
      UINT CacheMissNA:1;            // 4
      UINT BranchRetiredNA:1;        // 5
      UINT BranchMispredictNA:1;     // 6
      UINT Reserved1:25;             // 31..7
   } bits;  // high order
   UINT w;
} EBX10b;

typedef union {
   struct { // low order
      UINT FixedFunctionCounters:5;    // 4..0
      UINT CounterBitWidth:8;          // 12..5
      UINT Reserved2:19;               // 31..13
   } bits;  // high order
   UINT w;
} EDX10b;

/*****************************************************************************
  CPUID(0x80000000): Extended CPUID 0

  EAX: Maximum value of Extended CPUID that can be issued
  EBX: Reserved
  ECX: Reserved
  EDX: Reserved

*****************************************************************************/

/*****************************************************************************
  CPUID(0x80000001): Extended CPUID 1

==================================================================================
  EAX:
  Extended Processor Signature and Feature Bits

  +----------------------------------------------------------------+
  |????????????????????????????????????????????????????????????????|
  +----------------------------------------------------------------+

==================================================================================
  EBX: Reserved (Intel)

  EBX: (AMD)
   31                          16 15                             0
  +------------------------------+--------------------------------+
  |##############################|          BrandID               |
  +------------------------------+--------------------------------+

==================================================================================
  ECX: Intel

   31                                                           1  0
  +--------------------------------------------------------------+--+
  |##############################################################|LS|
  +--------------------------------------------------------------+--+

  LS- LAHF/SAHF Available (64 bit)

  ECX: AMD
  
   31                                                  4  3  2  1  0
  +--------------------------------------------------+--+--+--+--+--+
  |##################################################|AM|##|SV|CL|LS|
  +--------------------------------------------------+--+--+--+--+--+

  CL - CmpLegacy - Core Multiprocessor Legacy mode
  SV - SVM - Secure Virtual Machine
  AM - AltMovCR8 - LOCK MOV CR0 == MOV CR8
  
==================================================================================
  EDX: (Intel)
   31 30 29 28                   21 20 19                   12 11 10                             0
  +-----+--+-----------------------+--+-----------------------+--+--------------------------------+
  |#####|EM|#######################|ED|#######################|SY|################################|
  +-----+--+-----------------------+--+-----------------------+--+--------------------------------+
  EM - EMT64 available
  ED - Execute Disable available
  SY - SYSCALL/SYSRET available (64-bit)
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
  +--+--+--+--+--+--+--+--+--+--+--+--+-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |3D|3X|LM|##|RD|##|FF|FX|MM|MX|##|NX|#####|P3|PT|CM|MC|PG|MT|SE|##|AP|CX|ME|PA|MS|TS|PS|DE|V8|FP|
  +--+--+--+--+--+--+--+--+--+--+--+--+-----+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

  3D - 3DNow!(tm) support
  3X - 3DNow!(tm) extensions
  LM - Long mode
  RD - RSTSCP
  FF - FFXSR
  FX - FXSR
  MM - MMX instructions
  MX - MMX Extensions
  NX - No Execute (Execute Disabled)
  P3 - PSE36 extensions
  PT - Page attribute table
  CM - CMOV: Conditional move/compare instruction
  MC - Machine Check Architecture
  PG - Global PTE bit
  MT - Memory Type Range Registers
  SE - SYSENTER/SYSEXIT
  AP - APIC on-chip
  CX - CMXCHG8B
  ME - Machine Check Exception
  PA - Physical Address Extension
  MS - RDMSR/WRMSR support
  TS - TimeStamp Counter
  PS - Page Size extensions
  DE - Debugging extensions
  V8 - Virtual 8086 extensions
  FP - FPU87 on chip
*****************************************************************************/

typedef union {
   struct { // low order
      UINT Reserved;          // 31..0
   } Intel; // high order
   struct { // low order
      UINT BrandId:16;        // 15..0
      UINT Reserved:16;       // 31..16
   } AMD;
   UINT w;
} EBX1x;

typedef union {
   struct { // low order
      UINT LAHF_SAHF:1;       // 0
      UINT Reserved5:31;      // 31..1
   } Intel;  // high order
   struct { // low order
      UINT LAHF_SAHF:1;       // 0
      UINT CmpLegacy:1;       // 1
      UINT SVM:1;             // 2
      UINT Reserved6:1;       // 3
      UINT AltMovCr8:1;       // 4
      UINT Reserved5:26;      // 31..5
   } AMD; // high order
   UINT w;
} ECX1x;

//=============================================================================
typedef union {
   struct {  // low order
      UINT Reserved1:11;     // 0..10
      UINT SYSCALL_SYSRET:1; // 11
      UINT Reserved2:8;      // 19..12
      UINT ExecuteDisable:1; // 20
      UINT Reserved3:8;      // 28..21
      UINT EMT64T:1;         // 29
      UINT Reserved4:2;      // 30..31
   } Intel;   // high order

   struct { // low order
      UINT FPU:1;            // 0
      UINT VME:1;            // 1
      UINT DE:1;             // 2
      UINT PSE:1;            // 3
      UINT TSC:1;            // 4
      UINT MSR:1;            // 5
      UINT PAE:1;            // 6
      UINT MCE:1;            // 7
      UINT CMPXCHG8B:1;      // 8
      UINT APIC:1;           // 9
      UINT Reserved1:1;      // 10
      UINT SYSCALL_SYSRET:1; // 11
      UINT MTRR:1;           // 12
      UINT PGE:1;            // 13
      UINT MCA:1;            // 14
      UINT CMOV:1;           // 15
      UINT PAT:1;            // 16
      UINT PSE36:1;          // 17
      UINT Reserved2:2;      // 19..18
      UINT ExecuteDisable:1; // 20
      UINT Reserved3:1;      // 21
      UINT MMXExt:1;         // 22
      UINT MMX:1;            // 23
      UINT FXSR:1;           // 24
      UINT FFXSR:1;          // 25
      UINT Reserved4:1;      // 26
      UINT RDTSCP:1;         // 27
      UINT Reserved5:1;      // 28
      UINT LM:1;             // 29
      UINT ThreeDNowExt:1;   // 30
      UINT ThreeDNow:1;      // 31
   } AMD;   // high order
   UINT w;
} EDX1x;

/*****************************************************************************
  CPUID(0x80000002)
  CPUID(0x80000003)
  CPUID(0x80000004)

  48 8-bit characters representing the brand string, terminated by a \0
  character in position 48
  
                                         0x80000002  0x80000003 0x80000004
  EAX: Processor brand string characters       0..3      16..19     32..36
  EBX: Processor brand string characters       4..7      20..23     37..40
  ECX: Processor brand string characters      8..11      24..27     41..44
  EDX: Processor brand string characters     12..15      28..31     45..48
  

  // 0x80000004:EDX will typically be (for Intel)
  \0zHM  "MHz"
  \0zHG  "GHz"
  \0zHT  "THz"
  and the characters before it will be the speed, e.g.,
  1113MHz
  1.10GHz

  (note there is no guarantee that there are only 4 characters here; the
  algorithm is to count backward over digits and decimal points until a
  non-digit, non-decimal point is encountered)
*****************************************************************************/

/*****************************************************************************
  CPUID(0x80000005)
  Intel:
    EAX: Reserved
    EBX: Reserved
    ECX: Reserved
    EDX: Reserved
  AMD:
    EAX:
     31            24 23            16 15             8 7              0
    +----------------+----------------+----------------+----------------+
    | D 2M+4M assoc  | D 2M+4M count  | I 2M+4M assoc  | I 2M+4M count  |
    +----------------+----------------+----------------+----------------+
    EBX:
     31            24 23            16 15             8 7              0
    +----------------+----------------+----------------+----------------+
    | D 4K assoc     | D 4K count     | I 4K assoc     | I 4K count     |
    +----------------+----------------+----------------+----------------+
    ECX:
     31            24 23            16 15             8 7              0
    +----------------+----------------+----------------+----------------+
    | D L1 size (KB) | D L1 assoc     | D L1 lines/tag | D L1 line size |
    +----------------+----------------+----------------+----------------+
    EDX:
     31            24 23            16 15             8 7              0
    +----------------+----------------+----------------+----------------+
    | I L1 size (KB) | I L1 assoc     | I L1 lines/tag | I L1 line size |
    +----------------+----------------+----------------+----------------+
             |
             00 reserved
             01 direct mapped
             02..FE n-way mapping
             FF fully associative
    
*****************************************************************************/
typedef union { // 2M+4M page TLB info
   struct { // low order
      UINT Reserved:32;     // 31..0
   } Intel;
   struct { // low order
      UINT InstCount:8;    // 7..0
      UINT InstAssoc:8;    // 15..8
      UINT DataCount:8;    // 23..16
      UINT DataAssoc:8;    // 31..24
   } AMD;
   UINT w;
} EAX5x;

typedef union { // 4K page TLB info
   struct { // low order
      UINT Reserved:32;     // 31..0
   } Intel;
   struct { // low order
      UINT InstCount:8;    // 7..0
      UINT InstAssoc:8;    // 15..8
      UINT DataCount:8;    // 23..16
      UINT DataAssoc:8;    // 31..24
   } AMD;
   UINT w;
} EBX5x;

typedef union { // L1 data cache info
   struct { // low order
      UINT Reserved:32;     // 31..0
   } Intel;
   struct { // low order
      UINT LineSize:8;     // 7..0
      UINT LinesPerTag:8;  // 15..8
      UINT Associativity:8;// 23..16
      UINT CacheSize:8;    // 31..24
   } AMD;
   UINT w;
} ECX5x;

typedef union { // L1 instruction cache info
   struct { // low order
      UINT Reserved:32;     // 31..0
   } Intel;
   struct { // low order
      UINT LineSize:8;     // 7..0
      UINT LinesPerTag:8;  // 15..8
      UINT Associativity:8;// 23..16
      UINT CacheSize:8;    // 31..24
   } AMD;
   UINT w;
} EDX5x;

/*****************************************************************************
  CPUID(0x80000006)

  Intel:

  EAX: Reserved
  EBX: Reserved
  ECX:
   31                          16 15    12 11     8 7              0
  +------------------------------+--------+--------+----------------+
  |    Cache size in 1K units    |L2 Assoc|########|  CacheLineSize |
  +------------------------------+--------+--------+----------------+
                                  |
                                  |
                                  IDS_L2_ASSOCIATIVITY_00H "Disabled"
                                  IDS_L2_ASSOCIATIVITY_01H "Direct mapped"
                                  IDS_L2_ASSOCIATIVITY_02H "2-way associative"
                                  IDS_L2_ASSOCIATIVITY_04H "4-way associative"
                                  IDS_L2_ASSOCIATIVITY_06H "8-way associative"
                                  IDS_L2_ASSOCIATIVITY_08H "16-way associative"
                                  IDS_L2_ASSOCIATIVITY_0FH "Fully associative"
                                
   AMD:
  EAX:  L2 TLB parameters, 2M/4M pages

   31    28 27                    16 15    12 11                      0
  +--------+------------------------+--------+-------------------------+
  |D assoc |      D size            |I assoc | I size                  |
  +--------+------------------------+--------+-------------------------+
       |                             |
       +-----------------------------+
                                     |
                                     00 reserved
                                     01 direct mapped
                                     02..FE n-way mapping
                                     FF fully associative
  EBX:  L2 TLB parameters, 4K pages

   31    28 27                    16 15    12 11                      0
  +--------+------------------------+--------+-------------------------+
  |D assoc |      D size            |I assoc | I size                  |
  +--------+------------------------+--------+-------------------------+
       |                             |
       +-----------------------------+
                                     |
                                     00 reserved
                                     01 direct mapped
                                     02..FE n-way mapping
                                     FF fully associative
  ECX: L2 cache parameters
   31                             16 15    12 11     8 7              0
  +---------------------------------+--------+--------+----------------+
  |      Cache size in 1K units     |L2 Assoc|  LPT   |  CacheLineSize |
  +---------------------------------+--------+--------+----------------+
                                      |
                                      |
                                      IDS_L2_ASSOCIATIVITY_00H "Disabled"
                                      IDS_L2_ASSOCIATIVITY_01H "Direct mapped"
                                      IDS_L2_ASSOCIATIVITY_02H "2-way associative"
                                      IDS_L2_ASSOCIATIVITY_04H "4-way associative"
                                      IDS_L2_ASSOCIATIVITY_06H "8-way associative"
                                      IDS_L2_ASSOCIATIVITY_08H "16-way associative"
                                      IDS_L2_ASSOCIATIVITY_0FH "Fully associative"
   LPT - Lines Per Tag
   
   EDX: Reserved
*****************************************************************************/

typedef union { // 2M and 4M TLB parameters
   struct {
      UINT Reserved:32;      // 31..0
   } Intel;

   struct { // low order
      UINT InstCount:12;     // 11..0
      UINT InstAssoc:4;      // 15..12
      UINT DataCount:12;     // 27..16
      UINT DataAssoc:4;      // 31..28
   } AMD;   // high order
   UINT w;
} EAX6x;

typedef union { // 4K TLB parameters
   struct {
      UINT Reserved:32;      // 31..0
   } Intel;

   struct { // low order
      UINT InstCount:12;     // 11..0
      UINT InstAssoc:4;      // 15..12
      UINT DataCount:12;     // 27..16
      UINT DataAssoc:4;      // 31..28
   } AMD;   // high order
   UINT w;
} EBX6x;

typedef union {
   struct { // low order
      UINT LineSize:8;        // 7..0
      UINT Reserved1:4;       // 11..8
      UINT Associativity:4;   // 15..12
      UINT CacheSize:16;      // 31..16
   } Intel; // high order
   struct { // low order
      UINT LineSize:8;        // 7..0
      UINT LinesPerTag:4;     // 11.8
      UINT Associativity:4;   // 15..12
      UINT CacheSize:16;      // 31..16
   } AMD;   // high order
   UINT w;
} ECX6x;

/*****************************************************************************
  CPUID(0x80000007) (Intel)

  Intel:

  EAX: Reserved
  EBX: Reserved
  ECX: Reserved
  EDX: Reserved

  AMD:

  EAX: Reserved
  EBX: Reserved
  ECX: Reserved
  
   31                                           9  8 7  6  5  4  3  2  1  0
  +----------------------------------------------+--+----+--+--+--+--+--+--+
  |##############################################|TI|####|ST|TM|TT|VI|FI|TS|
  +----------------------------------------------+--+----+--+--+--+--+--+--+
  TI - TSC Invariant
  ST - Software Thermal Control
  TM - Harware Thermal Control
  TT - ThermaTrip supported
  VI - Voltage ID supported
  FI - Frequency ID supported
  TS - Temperature Sensor

*****************************************************************************/

typedef union {
   struct { // low order
      UINT TS:1;           // 0
      UINT FID:1;          // 1
      UINT VID:1;          // 2
      UINT TTP:1;          // 3
      UINT TM:1;           // 4
      UINT STC:1;          // 5
      UINT Reserved1:2;    // 7..6
      UINT TSCInvariant:1; // 8
      UINT Reserved2:23;   // 31..9
   } AMD;  // high order
   UINT w;
} EDX7x;

/*****************************************************************************
  CPUID(0x80000008)

  EAX:
   31                          16 15              8 7              0
  +------------------------------+-----------------+----------------+
  |##############################|VirtualMemoryBits|PhysicalMemoryBi|
  +------------------------------+-----------------+----------------+

  EBX: Reserved
  ECX: Reserved (Intel)
  EDX: Reserved

  ECX:
   31                            16 15    12 11     8 7              0
  +--------------------------------+--------+--------+----------------+
  |################################| AICIDS |########|      NC        |
  +--------------------------------+--------+--------+----------------+
  AICIDS - APicIdCoreIdSize
  NC - Number of CPU cores - 1

  if(ECX.AMD.ApicIdCoreIdSize == 0)
      ActualCores = ECX.AMD.NC;
  else
      ActualCores = 1<<ECX.AMD.ApicIdCoreIdSize;
      
*****************************************************************************/  

typedef union {
   struct { // low order
      UINT PhysicalAddressBits:8;   // 7..0
      UINT VirtualAddressBits:8;    // 15..8
      UINT Reserved:16;             // 31..16
   } bits; // high order
   UINT w;
} EAX8x;

typedef union {
   struct { // low order
      UINT NC:8;                // 7..0
      UINT Reserved2:4;         // 11..8
      UINT ApicIdCoreIdSize:4;  // 15..12
      UINT Reserved3:16;        // 31..16
   } AMD;   // high order
   UINT w;
} ECX8x;

/*****************************************************************************
  CPUID(0x8000000A)

  EAX:
   31                                             8 7              0
  +------------------------------------------------+----------------+
  |################################################|  SVM revision  |
  +------------------------------------------------+----------------+

  EBX: NASID

  ECX: Reserved

  EDX: Reserved
  
*****************************************************************************/  

typedef union {
   struct { // low order
      UINT SVMRev:8;     // 7..0
      UINT Reserved:24;  // 31..8
   } AMD;   // high order
   UINT w;
} EAX10x;
