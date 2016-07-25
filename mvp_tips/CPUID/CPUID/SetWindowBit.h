#pragma once

#define SETWINDOWBIT(x, reg, platform) \
        { \
          CString s; \
          s.Format(_T("%d"), reg.platform.x); \
          c_##x.SetWindowText(s); \
        }

#define SETWINDOWHEX(x, reg, platform, digits) \
        { \
         CString s; \
         s.Format(_T("%0") _T(#digits) _T("XH"), reg.platform.x); \
         c_##x.SetWindowText(s); \
        }

#define SETRESERVEDBITS(x, w, reg) \
        { \
         CString s; \
         s.Format(_T("%0") _T(##w) _T("x"), reg.bits.x); \
         c_##x.SetWindowText(s); \
        }
