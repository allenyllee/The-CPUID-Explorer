#pragma once

#include "Block.h"
#include "Arrow.h"
#include "CPUCoreRegion.h"
#include "LogicalAddressLines.h"
#include "PhysicalAddressLines.h"
#include "CacheTLBInfo.h"
// CBlockDiagram dialog

class CBlockDiagram : public CPropertyPage
{
        DECLARE_DYNCREATE(CBlockDiagram)

public:
        CBlockDiagram();
        virtual ~CBlockDiagram();

// Dialog Data
        enum { IDD = IDD_BLOCK_DIAGRAM };

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        static void GetCPUID2Descriptors(CByteArray & b);
        void ComputeLayout();
        BOOL initialized;
        void ComputeCacheTLBInformation(CCacheTLBInfo & ctl, const BYTE* descriptors);
        static BOOL QueryL3();
        static BOOL QueryPrefetch();

        DECLARE_MESSAGE_MAP()
protected:
        CArrow c_PrefetchRegion;
        CBlock c_CPURegion;
        CBlock c_Gap1;
        CCPUCoreRegion c_CPUCoreRegion;
        CBlock c_Gap2;
        CCacheTLBInfo c_L1CacheRegion;
        CLogicalAddressLines c_LogicalAddressLinesRegion;
        CCacheTLBInfo c_TLBRegion;
        CCacheTLBInfo c_L2CacheRegion;
        CCacheTLBInfo c_L3CacheRegion;
        CPhysicalAddressLines c_PhysicalAddressLinesRegion;
        CBlock c_MemoryRegion;
protected:
   virtual BOOL OnInitDialog();
   afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
   void ComputeExtendedL1Information(CCacheTLBInfo & region);
   void ComputeExtendedL2Information(CCacheTLBInfo & region);
   void ComputeExtendedTLBInformation(CCacheTLBInfo & region);
   void ComputePrefetchInformation();

   BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);

   BOOL FormatExtendedTLBInfo(UINT assoc, UINT count, CString & shortDesc, UINT shortFmt, CString & longDesc, UINT longFmt);
   BOOL FormatL1CacheInfo(UINT CacheSize, UINT Associativity, UINT LinesPerTag, UINT LineSize, CString & LongDesc, UINT LongFmt, CString & ShortDesc, UINT ShortFmt );
   BOOL FormatL2CacheInfo(UINT CacheSize, UINT Associativity, UINT LinesPerTag, UINT LineSize, CString & LongDesc, UINT LongFmt, CString & ShortDesc, UINT ShortFmt );
   BOOL GetShortAssociativity(UINT assoc, CString & way);
   BOOL GetLongAssociativity(UINT assoc, CString & way);
   BOOL GetShortL2Associativity(UINT assoc, CString & way);
   BOOL GetLongL2Associativity(UINT assoc, CString & way);
public:
    virtual BOOL OnSetActive();
protected:
    virtual void PostNcDestroy();
};
