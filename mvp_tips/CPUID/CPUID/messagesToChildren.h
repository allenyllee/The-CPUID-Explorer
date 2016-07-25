// These messages are sent by the main dialog to the child dialogs to indicate
// changes in the user-selected options

/****************************************************************************
*                               UWM_REFRESH
* Inputs:
*       WPARAM: ignored
*       LPARAM: ignored
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Sends a notification to the child window to recompute the code based
*       on the latest settings
****************************************************************************/

#define UWM_REFRESH_MSG _T("UWM_REFRESH-{96B9AB6C-F310-49d3-8EE3-B7702C0A1CF3}")


/****************************************************************************
*                               UWM_INITIALIZE
* Inputs:
*       WPARAM: (WPARAM)(CWnd *) window to use for  messages
*       LPARAM: ignored
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Initializes the TabParent field of the superclass
****************************************************************************/

#define UWM_INITIALIZE_MSG _T("UWM_INITIALIZE-{96B9AB6C-F310-49d3-8EE3-B7702C0A1CF3}")
