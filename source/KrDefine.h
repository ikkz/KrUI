
#define OUTPUTLASTERROR(x) cout<<#x<<": "<<GetLastError()<<endl

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

#define KM_MOUSEENTER (WM_USER+1)
#define KM_MOUSELEAVE (WM_USER+2)
#define KM_LBTNUP (WM_USER+3)
#define KM_LBTNDOWN (WM_USER+4)
#define KM_CLICK KM_LBTNUP
#define KM_MOUSEMOVE (WM_USER+5)
#define KM_TEXTCHANGE (WM_USER+6)

