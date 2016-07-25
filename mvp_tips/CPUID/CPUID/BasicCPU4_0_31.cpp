
// BasicCPU4_0_31.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BasicCPU4_0_31.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "CPUIDRegs.h"
#include "ColorSet.h"
#include "SetColor.h"

// CBasicCPU4_0_31 dialog

IMPLEMENT_DYNCREATE(CBasicCPU4_0_31, CLeaves)
CBasicCPU4_0_31::CBasicCPU4_0_31()
        : CLeaves(CBasicCPU4_0_31::IDD)
{
}

CBasicCPU4_0_31::~CBasicCPU4_0_31()
{
}

/****************************************************************************
*                       CBasicCPU4_0_31::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds the controls
****************************************************************************/

void CBasicCPU4_0_31::DoDataExchange(CDataExchange* pDX)
{
CLeaves::DoDataExchange(pDX);
DDX_Control(pDX, IDC_CACHE_TYPE, c_CacheType);
DDX_Control(pDX, IDC_CACHE_TYPE_CAPTION, x_CacheType);
DDX_Control(pDX, IDC_CACHE_TYPE_VALUE, c_CacheTypeValue);
DDX_Control(pDX, IDC_CACHE_LEVEL, c_CacheLevel);
DDX_Control(pDX, IDC_CACHE_LEVEL_CAPTION, x_CacheLevel);
DDX_Control(pDX, IDC_SELF_INITIALIZING, c_SelfInitializing);
DDX_Control(pDX, IDC_SELF_INITIALIZING_CAPTION, x_SelfInitializing);
DDX_Control(pDX, IDC_FULLY_ASSOCIATIVE, c_FullyAssociative);
DDX_Control(pDX, IDC_FULLY_ASSOCIATIVE_CAPTION, x_FullyAssociative);
DDX_Control(pDX, IDC_RESERVED, c_Reserved);
DDX_Control(pDX, IDC_RESERVED_CAPTION, x_Reserved);
DDX_Control(pDX, IDC_THREADS_SHARING, c_ThreadsSharing);
DDX_Control(pDX, IDC_THREADS_SHARING_CAPTION, x_ThreadsSharing);
DDX_Control(pDX, IDC_THREADS_SHARING_VALUE, c_ThreadsSharingValue);
DDX_Control(pDX, IDC_CORES_PER_PACKAGE_CAPTION, x_CoresPerPackage);
DDX_Control(pDX, IDC_CORES_PER_PACKAGE, c_CoresPerPackage);
DDX_Control(pDX, IDC_CORES_PER_PACKAGE_VALUE, c_CoresPerPackageValue);
// EBX:
DDX_Control(pDX, IDC_SYSTEM_COHERENCY_LINE_SIZE, c_SystemCoherencyLineSize);
DDX_Control(pDX, IDC_SYSTEM_COHERENCY_LINE_SIZE_CAPTION, x_SystemCoherencyLineSize);
DDX_Control(pDX, IDC_SYSTEM_COHERENCY_LINE_SIZE_VALUE, c_SystemCoherencyLineSizeValue);
DDX_Control(pDX, IDC_PHYSICAL_LINE_PARTITIONS, c_PhysicalLinePartitions);
DDX_Control(pDX, IDC_PHYSICAL_LINE_PARTITIONS_CAPTION, x_PhysicalLinePartitions);
DDX_Control(pDX, IDC_PHYSICAL_LINE_PARTITIONS_VALUE, c_PhysicalLinePartitionsValue);
DDX_Control(pDX, IDC_WAYS_OF_ASSOCIATIVITY, c_WaysOfAssociativity);
DDX_Control(pDX, IDC_WAYS_OF_ASSOCIATIVITY_CAPTION, x_WaysOfAssociativity);
DDX_Control(pDX, IDC_WAYS_OF_ASSOCIATiVITY_VALUE, c_WaysOfAssociativityValue);
// ECX:
DDX_Control(pDX, IDC_NUMBER_OF_SETS, c_NumberOfSets);
DDX_Control(pDX, IDC_NUMBER_OF_SETS_CAPTION, x_NumberOfSets);
DDX_Control(pDX, IDC_NUMBER_OF_SETS_VALUE, c_NumberOfSetsValue);
}

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CBasicCPU4_0_31, CLeaves)
END_MESSAGE_MAP()


// CBasicCPU4_0_31 message handlers

/****************************************************************************
*                        CBasicCPU4_0_31::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Intitializes the controls
****************************************************************************/

BOOL CBasicCPU4_0_31::OnInitDialog()
    {
     CLeaves::OnInitDialog();
     ColorSet colors(TRUE);

     POSITION p;
     p = colors.GetFirstColorPosition();

     SETCOLOR(CacheType);
     SETCOLOR(CacheLevel);
     SETCOLOR(SelfInitializing);
     SETCOLOR(FullyAssociative);
     SETRESERVEDCOLOR(Reserved);
     SETCOLOR(ThreadsSharing);
     SETCOLOR(CoresPerPackage);
     SETCOLOR(SystemCoherencyLineSize);
     SETCOLOR(PhysicalLinePartitions);
     SETCOLOR(WaysOfAssociativity);
     SETCOLOR(NumberOfSets);
     return TRUE;  // return TRUE unless you set the focus to a control
    }

/****************************************************************************
*                     CBasicCPU4_0_31::GetCacheParameters
* Inputs:
*       UINT L: Level
*       CPUregs * regs: Register set
* Result: BOOL
*       TRUE if regs are valid
*       FALSE if there is no cache at that level
* Effect: 
*       Fetches the cache parameters
****************************************************************************/

/* static */ BOOL CBasicCPU4_0_31::GetCacheParameters(UINT L, CPUregs * regs)
    {
     regs->ECX = L;
     CurrentProcessor.GetCPUID(4, regs);
     EAX4b EAX;
     EAX.w = regs->EAX;
     if(EAX.bits.CacheType == 0)
        return FALSE;   // no more cache infos
     return TRUE;
    } // CBasicCPU4_0_31::GetCacheParameters

/****************************************************************************
*                       CBasicCPU4_0_31::ShowCacheParameters
* Inputs:
*       UINT L: Level of cache
* Result: void
*       
* Effect: 
*       Retrieves and displays the cache parameters
****************************************************************************/

void CBasicCPU4_0_31::ShowCacheParameters(UINT L)
    {
     CPUregs regs;
     if(!GetCacheParameters(L, &regs))
        return;
     
    } // CBasicCPU4_0_31::ShowCacheParameters

/****************************************************************************
*                         CBasicCPU4_0_31::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the status
****************************************************************************/

BOOL CBasicCPU4_0_31::OnSetActive()
    {
     CPUregs regs;
     CString s;

     regs.ECX = 1;
     GetAndReport(4, regs);

     // EAX:
     EAX4b EAX;
     EAX.w = regs.EAX;

     SETWINDOWBIT(CacheType, EAX, bits);
     s.LoadString(IDS_CACHE_TYPE_00 + EAX.bits.CacheType);
     c_CacheTypeValue.SetWindowText(s);
     
     SETWINDOWBIT(CacheLevel, EAX, bits);
     SETWINDOWBIT(SelfInitializing, EAX, bits);
     SETWINDOWBIT(FullyAssociative, EAX, bits);
     SETWINDOWBIT(Reserved, EAX, bits);

     SETWINDOWBIT(ThreadsSharing, EAX, bits);
     s.Format(_T("%d"), EAX.bits.ThreadsSharing + 1);
     c_ThreadsSharingValue.SetWindowText(s);
     
     SETWINDOWBIT(CoresPerPackage, EAX, bits);
     s.Format(_T("%d"), EAX.bits.CoresPerPackage + 1);
     c_CoresPerPackageValue.SetWindowText(s);

     // EBX:
     EBX4b EBX;
     EBX.w = regs.EBX;
     SETWINDOWBIT(SystemCoherencyLineSize, EBX, bits);
     s.Format(_T("%d"), EBX.bits.SystemCoherencyLineSize + 1);
     c_SystemCoherencyLineSizeValue.SetWindowText(s);

     SETWINDOWBIT(PhysicalLinePartitions, EBX, bits);
     s.Format(_T("%d"), EBX.bits.PhysicalLinePartitions + 1);
     c_PhysicalLinePartitionsValue.SetWindowText(s);

     SETWINDOWBIT(WaysOfAssociativity, EBX, bits);
     s.Format(_T("%d"), EBX.bits.WaysOfAssociativity + 1);
     c_WaysOfAssociativityValue.SetWindowText(s);

     // ECX:
     s.Format(_T("%d"), regs.ECX);
     c_NumberOfSets.SetWindowText(s);
     s.Format(_T("%d"), regs.ECX + 1);
     c_NumberOfSetsValue.SetWindowText(s);
     return CLeaves::OnSetActive();
    }
