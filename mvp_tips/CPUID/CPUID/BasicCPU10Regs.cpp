// BasicCPU10Regs.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU10Regs.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "SetAlign.h"
// CBasicCPU10Regs dialog

IMPLEMENT_DYNCREATE(CBasicCPU10Regs, CLeaves)
CBasicCPU10Regs::CBasicCPU10Regs()
        : CLeaves(CBasicCPU10Regs::IDD)
{
}

CBasicCPU10Regs::~CBasicCPU10Regs()
{
}

void CBasicCPU10Regs::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_VERSION_ID, c_VersionID);
DDX_Control(pDX, IDC_VERSION_ID_CAPTION, x_VersionID);
DDX_Control(pDX, IDC_COUNTERS_PER_PROCESSOR, c_GPCounters);
DDX_Control(pDX, IDC_COUNTERS_PER_PROCESSOR_CAPTION, x_GPCounters);
DDX_Control(pDX, IDC_GP_COUNTER_WIDTH, c_GPCounterWidth);
DDX_Control(pDX, IDC_GP_COUNTER_WIDTH_CAPTION, x_GPCounterWidth);
DDX_Control(pDX, IDC_EBX_VECTOR_LENGTH, c_EBXVectorLength);
DDX_Control(pDX, IDC_EBX_VECTOR_LENGTH_CAPTION, x_EBXVectorLength);
// EBX:
DDX_Control(pDX, IDC_CORE_CYCLE_NA, c_CoreCycleNA);
DDX_Control(pDX, IDC_CORE_CYCLE_NA_CAPTION, x_CoreCycleNA);
DDX_Control(pDX, IDC_INSTRUCTION_RETIRED_NA, c_InstructionRetiredNA);
DDX_Control(pDX, IDC_INSTRUCTION_RETIRED_NA_CAPTION, x_InstructionRetiredNA);
DDX_Control(pDX, IDC_REFERENCE_CYCLES_NA, c_ReferenceCyclesNA);
DDX_Control(pDX, IDC_REFERENCE_CYCLES_NA_CAPTION, x_ReferenceCyclesNA);
DDX_Control(pDX, IDC_LAST_LEVEL_CACHE_REF_NA, c_CacheReferenceNA);
DDX_Control(pDX, IDC_LAST_LEVEL_CACHE_REF_NA_CAPTION, x_CacheReferenceNA);
DDX_Control(pDX, IDC_LAST_LEVEL_CACHE_MISS_NA, c_CacheMissNA);
DDX_Control(pDX, IDC_LAST_LEVEL_CACHE_MISS_NA_CAPTION, x_CacheMissNA);
DDX_Control(pDX, IDC_BRANCH_RETIRED_NA, c_BranchRetiredNA);
DDX_Control(pDX, IDC_BRANCH_RETIRED_NA_CAPTION, x_BranchRetiredNA);
DDX_Control(pDX, IDC_BRANCH_MISPREDICT_NA, c_BranchMispredictNA);
DDX_Control(pDX, IDC_BRANCH_MISPREDICT_NA_CAPTION, x_BranchMispredictNA);
DDX_Control(pDX, IDC_RESERVED1, c_Reserved1);
DDX_Control(pDX, IDC_RESERVED1_CAPTION, x_Reserved1);
DDX_Control(pDX, IDC_FIXED_FUNCTION_COUNTERS, c_FixedFunctionCounters);
DDX_Control(pDX, IDC_FIXED_FUNCTION_COUNTERS_CAPTION, x_FixedFunctionCounters);
DDX_Control(pDX, IDC_COUNTER_WIDTH, c_CounterBitWidth);
DDX_Control(pDX, IDC_COUNTER_WIDTH_CAPTION, x_CounterBitWidth);
DDX_Control(pDX, IDC_RESERVED2, c_Reserved2);
DDX_Control(pDX, IDC_RESERVED2_CAPTION, x_Reserved2);
DDX_Control(pDX, IDC_ECX, c_ECX);
}

BEGIN_MESSAGE_MAP(CBasicCPU10Regs, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU10Regs message handlers

/****************************************************************************
*                         CBasicCPU10Regs::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CBasicCPU10Regs::OnSetActive()
   {
    CPUregs regs;
    GetAndReport(10, regs);

    EAX10b EAX;
    EAX.w = regs.EAX;
    
    // EAX
    SETWINDOWBIT(VersionID, EAX, bits);
    SETWINDOWBIT(GPCounters, EAX, bits);
    SETWINDOWBIT(GPCounterWidth, EAX, bits);
    SETWINDOWBIT(EBXVectorLength, EAX, bits);

    EBX10b EBX;
    EBX.w = regs.EBX;

    SETWINDOWBIT(CoreCycleNA, EBX, bits);
    SETWINDOWBIT(InstructionRetiredNA, EBX, bits);
    SETWINDOWBIT(ReferenceCyclesNA, EBX, bits);
    SETWINDOWBIT(CacheReferenceNA, EBX, bits);
    SETWINDOWBIT(CacheMissNA, EBX, bits);
    SETWINDOWBIT(BranchRetiredNA, EBX, bits);
    SETWINDOWBIT(BranchMispredictNA, EBX, bits);
    SETWINDOWBIT(Reserved1, EBX, bits);
    
    EDX10b EDX;
    EDX.w = regs.EDX;
    SETWINDOWBIT(FixedFunctionCounters, EDX, bits);
    SETWINDOWBIT(CounterBitWidth, EDX, bits);
    SETWINDOWBIT(Reserved2, EDX, bits);

    return CLeaves::OnSetActive();
   }

/****************************************************************************
*                         CBasicCPU10Regs::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CBasicCPU10Regs::OnInitDialog()
   {
    CLeaves::OnInitDialog();

    ColorSet colors(TRUE);

    POSITION p;
    p = colors.GetFirstColorPosition();
    // EAX
    SETCOLOR(VersionID);                   // 7..0
    SETCOLOR(GPCounters);                  // 15..8
    SETCOLOR(GPCounterWidth);              // 23..16
    SETCOLOR(EBXVectorLength);             // 31..24

    // EBX
    SETCOLOR(CoreCycleNA);                 // 0
    SETALIGN(CORE_CYCLE_NA);

    SETCOLOR(InstructionRetiredNA);        // 1
    SETALIGN(INSTRUCTION_RETIRED_NA);
    
    SETCOLOR(ReferenceCyclesNA);           // 2
    SETALIGN(REFERENCE_CYCLES_NA);
    
    SETCOLOR(CacheReferenceNA);            // 3
    SETALIGN(LAST_LEVEL_CACHE_REF_NA);

    SETCOLOR(CacheMissNA);                 // 4
    SETALIGN(LAST_LEVEL_CACHE_MISS_NA);

    SETCOLOR(BranchRetiredNA);             // 5
    SETALIGN(BRANCH_RETIRED_NA);

    SETCOLOR(BranchMispredictNA);          // 6
    SETALIGN(BRANCH_MISPREDICT_NA);

    SETRESERVEDCOLOR(Reserved1);           // 31..1

    // ECX
    SetFixedFont(c_ECX);

    // EDX
    SETCOLOR(FixedFunctionCounters);       // 4..0
    SETCOLOR(CounterBitWidth);             // 12..5
    SETRESERVEDCOLOR(Reserved2);           // 31..13


    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
