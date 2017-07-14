
#include"KrWindow.h"
#include <windows.h>
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

		m_DC = NULL;
		m_TempDC = NULL;
		m_hbmp = NULL;
	}



	LPCWSTR KrWindow::GetWindowName()
	{
		return m_lpWindowName;
	}

	void KrWindow::SetWindowName(LPCWSTR lpWindowName)
	{
		if (IsCreated())SetWindowText(m_hwnd, lpWindowName);
		m_lpWindowName = lpWindowName;
	}




	HWND KrWindow::GetHWND()
	{
		return m_hwnd;
	}


	RECT* KrWindow::GetRect()
	{
		return &m_rect;
	}


	void KrWindow::SetRect(RECT* pRect)
	{
		m_rect.left = pRect->left;
		m_rect.right = pRect->right;
		m_rect.top = pRect->top;
		m_rect.bottom = pRect->bottom;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}




	void KrWindow::SetStyle(DWORD dwStyle)
	{
		m_dwStyle = dwStyle;
		if (IsCreated())SetWindowLong(m_hwnd, GWL_STYLE, dwStyle);
	}
	DWORD KrWindow::GetStyle()
	{
		return m_dwStyle;
	}


	bool KrWindow::Create()
	{
		HWND hwnd = CreateWindow(KrUIManager::GetpKrUIManager()->GetWindowClassName(), m_lpWindowName, m_dwStyle,
			m_rect.left, m_rect.top,m_rect.right - m_rect.left, m_rect.bottom - m_rect.top,
			NULL, NULL, KrUIManager::GetpKrUIManager()->GetHINSTANCE(), NULL);
		if (!hwnd) return false;
		m_hwnd = hwnd;
		GetWindowRect(hwnd, &m_rect);

		m_DC = GetDC(m_hwnd);
		m_TempDC = CreateCompatibleDC(m_DC);
		m_hbmp = CreateCompatibleBitmap(m_TempDC,GetWidth(),GetHeight());
		SelectObject(m_TempDC, m_hbmp);

		m_pGraphics = new Graphics(m_TempDC);

		return true;
	}



	int KrWindow::GetX()
	{
		return m_rect.left;
	}



	int KrWindow::GetY()
	{
		return m_rect.top;
	}



	int KrWindow::GetWidth()
	{
		return m_rect.right - m_rect.left;
	}



	int KrWindow::GetHeight()
	{
		return m_rect.bottom - m_rect.top;
	}


	void KrWindow::SetX(int x)
	{
		int width = GetWidth();
		m_rect.left = x;
		m_rect.right = x + width;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::SetY(int y)
	{
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::SetWidth(int width)
	{
		m_rect.right = m_rect.left + width;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}



	void KrWindow::SetHeight(int height)
	{
		m_rect.bottom = m_rect.top + height;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::Show()
	{
		if (IsCreated())
		{
			ShowWindow(m_hwnd, SW_SHOW);
			m_bVisible = true;
		}

	}


	void KrWindow::Hide()
	{
		if (IsCreated())
		{
			ShowWindow(m_hwnd, SW_HIDE);
			m_bVisible = false;
		}

	}


	bool KrWindow::IsVisible()
	{
		return m_bVisible;
	}


	bool KrWindow::IsCreated()
	{
		if (m_hwnd==NULL)
		{
			return false;
		} 
		return true;
	}


	void KrWindow::Destroy(bool bDelete)
	{
		SendMessage(m_hwnd, WM_CLOSE, 0, 0);
		m_hwnd = NULL;

		DeleteObject(m_DC);
		DeleteObject(m_TempDC);
		DeleteObject(m_hbmp);
		m_DC = NULL;
		m_TempDC = NULL;
		m_hbmp = NULL;

		if (bDelete)
		{
			KrUIManager::GetpKrUIManager()->DeleteWindow(this);
		}
		if (KrUIManager::GetpKrUIManager()->GetWindowNum() == 0)PostQuitMessage(0);
	}


	void    KrWindow::RegMsg(UINT msg, MSGFUNC func)
	{
		map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.find(msg);
		if (it != m_MsgFuncMap.end())
		{
			it->second = func;
		}
		m_MsgFuncMap.insert(map<UINT, MSGFUNC>::value_type(msg, func));
	}


	LRESULT  KrWindow::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		
		for (list<KrControl*>::iterator it = m_CtrlList.begin(); it != m_CtrlList.end();it++)
		{
			 (*it)->HandleMessage(Message, wParam, lParam);
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
		case WM_SIZE:
			GetWindowRect(m_hwnd, &m_rect);

			DeleteObject(m_hbmp);
			m_hbmp = CreateCompatibleBitmap(m_TempDC, GetWidth(), GetHeight());
			SelectObject(m_TempDC, m_hbmp);

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

// 		case WM_PAINT:
// 		{
// 			PAINTSTRUCT ps;
// 			HDC dc = BeginPaint(m_hwnd, &ps);
// 			ReDraw(&ps.rcPaint);
// 			EndPaint(m_hwnd, &ps);
// 			break;
// 		}
		case WM_DESTROY: 
			Destroy(true);
			break;
		default:
			return DefWindowProc(m_hwnd, Message, wParam, lParam);
		}

		return 0;
	}


	KrControl* KrWindow::AddControl(UINT iCtrlType, LPCWSTR lpName, int x, int y, int width, int height)
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
		pKrCtrl->SetCtrlType(iCtrlType);
		pKrCtrl->SetWindow(this);
		pKrCtrl->SetName(lpName);
		pKrCtrl->SetRect(&rect);
		m_CtrlList.push_back(pKrCtrl);
		return pKrCtrl;
	}

	KrWindow::~KrWindow()
	{
		for (list<KrControl*>::iterator it = m_CtrlList.begin(); it != m_CtrlList.end(); it++)
		{
			delete (*it);
		}

		DeleteObject(m_DC);
		DeleteObject(m_TempDC);
		m_DC = NULL;
		m_TempDC = NULL;

	}

	void KrWindow::ReDraw(RECT* pRect)
	{
		if (m_bVisible)
		{
			//画背景


			//画标题（包括最大化最小化关闭按钮）


			//画边框

			//		MessageBox(m_hwnd, L"收到WM_PAINT", L"消息", MB_OK);
			//画控件
			if (pRect!=NULL)
			{
				BitBlt(m_DC, pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top, m_TempDC, pRect->left, pRect->top, SRCCOPY);
			}
			else
			{
				BitBlt(m_DC, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, m_TempDC, m_rect.left, m_rect.top, SRCCOPY);
			}
		}

	}



}