
#include"KrWindow.h"

namespace KrUI{
// 
// 
// 	LRESULT redraw(void* pObj, WPARAM wParam, LPARAM lParam)
// 	{
// 		((KrWindow*)pObj)->KrReDraw(NULL);
// 		return 0;
// 	}
// 


	KrWindow::KrWindow()
	{
		m_bVisible = false;
	//	KrRegMsg(WM_MOUSEMOVE, redraw);
		m_bMouseDown = false;
	}



	LPCWSTR KrWindow::KrGetWindowName()
	{
		return m_lpWindowName;
	}

	void KrWindow::KrSetWindowName(LPCWSTR lpWindowName)
	{
		if (KrIsCreated())SetWindowText(m_hwnd, lpWindowName);
		m_lpWindowName = lpWindowName;
	}




	HWND KrWindow::KrGetHWND()
	{
		return m_hwnd;
	}


	RECT* KrWindow::KrGetRect()
	{
		return &m_rect;
	}


	void KrWindow::KrSetRect(RECT* pRect)
	{
		m_rect.left = pRect->left;
		m_rect.right = pRect->right;
		m_rect.top = pRect->top;
		m_rect.bottom = pRect->bottom;
		if (KrIsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}




	void KrWindow::KrSetStyle(DWORD dwStyle)
	{
		m_dwStyle = dwStyle;
		if (KrIsCreated())SetWindowLong(m_hwnd, GWL_STYLE, dwStyle);
	}
	DWORD KrWindow::KrGetStyle()
	{
		return m_dwStyle;
	}


	bool KrWindow::KrCreate()
	{
		HWND hwnd = CreateWindow(KrUIManager::KrGetpKrUIManager()->KrGetWindowClassName(), m_lpWindowName, m_dwStyle,
			m_rect.left, m_rect.top,
			m_rect.right - m_rect.left, m_rect.bottom - m_rect.top,
			NULL, NULL, KrUIManager::KrGetpKrUIManager()->KrGetHINSTANCE(), NULL);
		if (!hwnd) return false;
		m_hwnd = hwnd;
		GetWindowRect(hwnd, &m_rect);
		return true;
	}



	int KrWindow::KrGetX()
	{
		return m_rect.left;
	}



	int KrWindow::KrGetY()
	{
		return m_rect.top;
	}



	int KrWindow::KrGetWidth()
	{
		return m_rect.right - m_rect.left;
	}



	int KrWindow::KrGetHeight()
	{
		return m_rect.bottom - m_rect.top;
	}


	void KrWindow::KrSetX(int x)
	{
		int width = KrGetWidth();
		m_rect.left = x;
		m_rect.right = x + width;
		if (KrIsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::KrSetY(int y)
	{
		int height = KrGetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		if (KrIsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::KrSetWidth(int width)
	{
		m_rect.right = m_rect.left + width;
		if (KrIsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}



	void KrWindow::KrSetHeight(int height)
	{
		m_rect.bottom = m_rect.top + height;
		if (KrIsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::KrShow()
	{
		if (KrIsCreated())
		{
			ShowWindow(m_hwnd, SW_SHOW);
			m_bVisible = true;
		}

	}


	void KrWindow::KrHide()
	{
		if (KrIsCreated())
		{
			ShowWindow(m_hwnd, SW_HIDE);
			m_bVisible = false;
		}

	}


	bool KrWindow::KrIsVisible()
	{
		return m_bVisible;
	}


	bool KrWindow::KrIsCreated()
	{
		if (m_hwnd==NULL)
		{
			return false;
		} 
		return true;
	}


	void KrWindow::KrDestroy(bool bDelete)
	{
		SendMessage(m_hwnd, WM_CLOSE, 0, 0);
		m_hwnd = NULL;
		if (bDelete)
		{
			KrUIManager::KrGetpKrUIManager()->KrDeleteWindow(this);
		}
		if (KrUIManager::KrGetpKrUIManager()->KrGetWindowNum() == 0)PostQuitMessage(0);
	}


	void    KrWindow::KrRegMsg(UINT msg, MSGFUNC func)
	{
		map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.find(msg);
		if (it != m_MsgFuncMap.end())
		{
			it->second = func;
		}
		m_MsgFuncMap.insert(map<UINT, MSGFUNC>::value_type(msg, func));
	}


	LRESULT  KrWindow::KrHandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		
		for (list<KrControl*>::iterator it = m_CtrlList.begin(); it != m_CtrlList.end();it++)
		{
			 (*it)->KrHandleMessage(Message, wParam, lParam);
		}

		map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.find(Message);
		if (it!=m_MsgFuncMap.end())
		{
			(*it->second)(this, wParam, lParam);
		}
		switch (Message)
		{
		
		case WM_LBUTTONDOWN:
			ReleaseCapture();
			SendMessage(m_hwnd, WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
			break;
		case WM_MOUSEMOVE:
			if (m_bMouseDown)
			{
				GetWindowRect(m_hwnd, &m_rect);
			}
			break;
// 		case WM_LBUTTONDOWN:
// 			m_bMouseDown = true;
// 			m_ptMouseDown.x = GET_X_LPARAM(lParam);
// 			m_ptMouseDown.y = GET_Y_LPARAM(lParam);
// 			break;
// 		case WM_LBUTTONUP:
// 			m_bMouseDown = false;
// 			break;
// 		case WM_MOUSEMOVE:
// 			if (m_bMouseDown)
// 			{
// 				m_ptMouse.x = GET_X_LPARAM(lParam);
// 				m_ptMouse.y = GET_Y_LPARAM(lParam);
// 				KrSetX(m_ptMouse.x - (m_ptMouseDown.x - m_rect.left));
// 				KrSetY(m_ptMouse.y - (m_ptMouseDown.y - m_rect.top));
// 			}
// 			break;
// 		case WM_MOUSELEAVE:
// 
// 			if (m_bMouseDown)
// 			{
// 				GetCursorPos(&m_ptMouse);
// 				m_ptMouse.x = m_ptMouse.x - m_rect.left;
// 				m_ptMouse.y = m_ptMouse.y - m_rect.top;
// 				KrSetX(m_ptMouse.x - (m_ptMouseDown.x - m_rect.left));
// 				KrSetY(m_ptMouse.y - (m_ptMouseDown.y - m_rect.top));
// 			}

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(m_hwnd, &ps);
			KrReDraw(&ps.rcPaint);
			EndPaint(m_hwnd, &ps);
			break;
		}
		case WM_DESTROY: 
			KrDestroy(true);
			break;
		default:
			return DefWindowProc(m_hwnd, Message, wParam, lParam);
		}

		return 0;
	}


	KrControl* KrWindow::KrAddControl(UINT iCtrlType, LPCWSTR lpName, int x, int y, int width, int height)
	{
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		KrControl* pKrCtrl = NULL;
		switch (iCtrlType)
		{
		case KR_CTRL:
			pKrCtrl = new KrControl;
			break;
		case KR_BUTTON:

			break;
		default:
			return NULL;
			break;
		}
		if (!pKrCtrl)return NULL;
		pKrCtrl->KrSetCtrlType(iCtrlType);
		pKrCtrl->KrSetWindow(this);
		pKrCtrl->KrSetName(lpName);
		pKrCtrl->KrSetRect(&rect);
		m_CtrlList.push_back(pKrCtrl);
		return pKrCtrl;
	}

	KrWindow::~KrWindow()
	{
		for (list<KrControl*>::iterator it = m_CtrlList.begin(); it != m_CtrlList.end(); it++)
		{
			delete (*it);
		}
	}

	void KrWindow::KrReDraw(RECT* pRect)
	{
		if (m_bVisible)
		{
			//画背景


			//画标题（包括最大化最小化关闭按钮）


			//画边框
			
			//		MessageBox(m_hwnd, L"收到WM_PAINT", L"消息", MB_OK);
			//画控件
		}

	}



}