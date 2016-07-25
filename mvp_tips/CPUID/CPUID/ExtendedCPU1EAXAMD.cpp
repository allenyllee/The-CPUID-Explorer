// ExtendedCPU1EAXAMD.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ExtendedCPU1EAXAMD.h"
#include "CPUIDx86.h"
#include "ReportRegs.h"
#include "SetWindowBit.h"
#include "ColorSet.h"
#include "SetColor.h"
#include "CPUIDRegs.h"
#include "CurrentProcessor.h"

// CExtendedCPU1EAXAMD dialog

IMPLEMENT_DYNCREATE(CExtendedCPU1EAXAMD, CBasicCPU1EAXAMD)

CExtendedCPU1EAXAMD::CExtendedCPU1EAXAMD()
        : CBasicCPU1EAXAMD()
{
}

CExtendedCPU1EAXAMD::~CExtendedCPU1EAXAMD()
{
}

/****************************************************************************
*                     CExtendedCPU1ECXAMD::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CExtendedCPU1EAXAMD::DoDataExchange(CDataExchange* pDX)
{
 CBasicCPU1EAXAMD::DoDataExchange(pDX);
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CExtendedCPU1EAXAMD, CBasicCPU1EAXAMD)
END_MESSAGE_MAP()


// CExtendedCPU1EAXAMD message handlers

/****************************************************************************
*                         CExtendedCPU1EAXAMD::OnSetActive
* Result: BOOL
*       
* Effect: 
*       Reports the registers
****************************************************************************/

BOOL CExtendedCPU1EAXAMD::OnSetActive()
   {
    return CBasicCPU1EAXAMD::OnSetActive();
   }

/****************************************************************************
*                         CExtendedCPU1EAXAMD::OnInitDialog
* Result: BOOL
*       TRUE, always
* Effect: 
*       Initializes the dialog
****************************************************************************/

BOOL CExtendedCPU1EAXAMD::OnInitDialog()
   {
    CBasicCPU1EAXAMD::OnInitDialog();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
   }
