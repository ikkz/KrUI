#include"KrControl.h"

namespace KrUI{

	KrControl::KrControl()
	{
		m_type = KR_CTRL;
		m_bVisible = false;
		m_bMouseIn = false;
	}


	void    KrControl::KrSetCtrlType(UINT type)
	{
		m_type = type;
	}
	UINT    KrControl::KrGetCtrlType()
	{
		return m_type;
	}


	void KrControl::KrSetWindow(KrWindow* pKrWindow)
	{
		m_pKrWindow = pKrWindow;
	}

	KrWindow* KrControl::KrGetWindow()
	{
		return m_pKrWindow;
	}

	RECT* KrControl::KrGetRect()
	{
		return &m_rect;
	}


	void KrControl::KrSetRect(RECT* pRect)
	{
		m_rect.left = pRect->left;
		m_rect.right = pRect->right;
		m_rect.top = pRect->top;
		m_rect.bottom = pRect->bottom;
		KrDraw();
	}



	int KrControl::KrGetX()
	{
		return m_rect.left;
	}



	int KrControl::KrGetY()
	{
		return m_rect.top;
	}



	int KrControl::KrGetWidth()
	{
		return m_rect.right - m_rect.left;
	}



	int KrControl::KrGetHeight()
	{
		return m_rect.bottom - m_rect.top;
	}


	void KrControl::KrSetX(int x)
	{
		int width = KrGetWidth();
		m_rect.left = x;
		m_rect.right = x + width;
		KrDraw();
	}


	void KrControl::KrSetY(int y)
	{
		int height = KrGetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		KrDraw();
	}


	void KrControl::KrSetWidth(int width)
	{
		m_rect.right = m_rect.left + width;
		KrDraw();
	}



	void KrControl::KrSetHeight(int height)
	{
		m_rect.bottom = m_rect.top + height;
		KrDraw();
	}



	void	KrControl::KrSetName(LPCWSTR lpCtrlName)
	{
		m_lpCtrlName = lpCtrlName;
	}

	LPCWSTR KrControl::KrGetName()
	{
		return m_lpCtrlName;
	}


	void    KrControl::KrRegMsg(UINT msg, MSGFUNC func)
	{
		for (map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.begin(); it != m_MsgFuncMap.end(); ++it)
		{
			if (it->first == msg)
			{
				it->second = func;
			}
		}
		m_MsgFuncMap.insert(map<UINT, MSGFUNC>::value_type(msg, func));

	}


	bool KrControl::KrIsVisible()
	{
		return m_bVisible;
	}


	void KrControl::KrHide()
	{
		m_bVisible = false;
	}

	void KrControl::KrShow()
	{
		m_bVisible = true;
	}


	void KrControl::KrHandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case WM_MOUSEMOVE:
		{
							 POINT ptMouse;
							 ptMouse.x = GET_X_LPARAM(lParam);
							 ptMouse.y = GET_Y_LPARAM(lParam);
							 BOOL bMouseIn = PtInRect(&m_rect, ptMouse);
							 if (m_bMouseIn == false && bMouseIn == TRUE)
							 {
								 //SendMessage(m_pKrWindow->GetHWND(), KM_MOUDEENTER, NULL, NULL);
								 KrCallMsgFunc(KM_BEFORE_MOUSEENTER, wParam, lParam);
								 KrCallMsgFunc(KM_MOUSEENTER, wParam, lParam);
								 KrCallMsgFunc(KM_AFTER_MOUSEENTER, wParam, lParam);
							 }
							 else if (m_bMouseIn == true && bMouseIn == false)
							 {
								 //SendMessage(m_pKrWindow->GetHWND(), KM_MOUSELEAVE, NULL, NULL);
								 KrCallMsgFunc(KM_BEFORE_MOUSELEAVE, wParam, lParam);
								 KrCallMsgFunc(KM_MOUSELEAVE, wParam, lParam);
								 KrCallMsgFunc(KM_AFTER_MOUSELEAVE, wParam, lParam);
							 }
							 m_bMouseIn = bMouseIn;
							 break;
		}
		case WM_LBUTTONDOWN:
		{					POINT ptMouse;
							ptMouse.x = GET_X_LPARAM(lParam);
							ptMouse.y = GET_Y_LPARAM(lParam);
							BOOL bMouseIn = PtInRect(&m_rect, ptMouse);
							if (bMouseIn)
							{
								KrCallMsgFunc(KM_BEFORE_LBTNDOWN, wParam, lParam);
								KrCallMsgFunc(KM_LBTNDOWN, wParam, lParam);
								KrCallMsgFunc(KM_AFTER_LBTNDOWN, wParam, lParam);
							}
							   break;
		}
		case WM_LBUTTONUP:
		{					POINT ptMouse;
							ptMouse.x = GET_X_LPARAM(lParam);
							ptMouse.y = GET_Y_LPARAM(lParam);
							BOOL bMouseIn = PtInRect(&m_rect, ptMouse);
							if (bMouseIn)
							{
								KrCallMsgFunc(KM_BEFORE_LBTNUP, wParam, lParam);
								KrCallMsgFunc(KM_LBTNUP, wParam, lParam);
								KrCallMsgFunc(KM_AFTER_LBTNUP, wParam, lParam);
							}
							 break;
		}
		default:
			KrCallMsgFunc(Message, wParam, lParam);
			break;
		}
	}

	void  KrControl::KrCallMsgFunc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.find(Message);
		if (it != m_MsgFuncMap.end())
		{
			(*it->second)(this, wParam, lParam);
		}
	}

	void KrControl::KrDraw()
	{

	}


}