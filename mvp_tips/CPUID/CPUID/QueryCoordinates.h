#pragma once
/****************************************************************************
*                            UWM_QUERY_COORDINATES
* Inputs:
*       WPARAM: (WPARAM)(UINT) The control ID of the control to query
*       LPARAM: (LPARAM)(CRect *): A rectangle
* Result: (LRESULT)(BOOL)
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Sets the CRect to have the screen coordinates of the control in question
****************************************************************************/

#define UWM_QUERY_COORDINATES_MSG _T("UWM_QUERY_COORDINATES-{546AB065-23E2-4e2e-AA03-AD84A326A2AE}")



