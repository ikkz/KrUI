#include"KrControl.h"

namespace KrUI{

	KrControl::KrControl()
	{
		m_type = KR_CTRL;
		m_bVisible = false;
		m_bMouseIn = false;
	}


	void KrControl::SetCtrlType(KrCtrlType type)
{
		m_type = type;
	}
	UINT    KrControl::GetCtrlType()
	{
		return m_type;
	}


	void KrControl::SetWindow(KrWindow* pKrWindow)
	{
		m_pKrWindow = pKrWindow;
	}

	KrWindow* KrControl::GetWindow()
	{
		return m_pKrWindow;
	}

	RECT* KrControl::GetRect()
	{
		return &m_rect;
	}


	void KrControl::SetRect(RECT* pRect)
	{
		m_rect.left = pRect->left;
		m_rect.right = pRect->right;
		m_rect.top = pRect->top;
		m_rect.bottom = pRect->bottom;
		UpdateRect();
	}



	int KrControl::GetX()
	{
		return m_rect.left;
	}



	int KrControl::GetY()
	{
		return m_rect.top;
	}



	int KrControl::GetWidth()
	{
		return m_rect.right - m_rect.left;
	}



	int KrControl::GetHeight()
	{
		return m_rect.bottom - m_rect.top;
	}


	void KrControl::SetX(int x)
	{
		int width = GetWidth();
		m_rect.left = x;
		m_rect.right = x + width;
		UpdateRect();
	}


	void KrControl::SetY(int y)
	{
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		UpdateRect();
	}


	void KrControl::SetWidth(int width)
	{
		m_rect.right = m_rect.left + width;
		UpdateRect();
	}



	void KrControl::SetHeight(int height)
	{
		m_rect.bottom = m_rect.top + height;
		UpdateRect();
	}



	void	KrControl::SetName(LPCWSTR lpCtrlName)
	{
		m_lpCtrlName = lpCtrlName;
	}

	LPCWSTR KrControl::GetName()
	{
		return m_lpCtrlName;
	}


	void    KrControl::RegMsg(UINT msg, MSGFUNC func)
	{
		map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.find(msg);
		if (it != m_MsgFuncMap.end())
		{
			it->second=func;
		}
		m_MsgFuncMap.insert(map<UINT, MSGFUNC>::value_type(msg, func));

	}


	bool KrControl::IsVisible()
	{
		return m_bVisible;
	}


	void KrControl::Hide()
	{
		m_bVisible = false;
	}

	void KrControl::Show()
	{
		m_bVisible = true;
	}


	void KrControl::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
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
				CallMsgFunc(KM_BEFORE_MOUSEENTER, wParam, lParam);
				CallMsgFunc(KM_MOUSEENTER, wParam, lParam);
				CallMsgFunc(KM_AFTER_MOUSEENTER, wParam, lParam);
			}
			else if (m_bMouseIn == true && bMouseIn == false)
			{
				//SendMessage(m_pKrWindow->GetHWND(), KM_MOUSELEAVE, NULL, NULL);
				CallMsgFunc(KM_BEFORE_MOUSELEAVE, wParam, lParam);
				CallMsgFunc(KM_MOUSELEAVE, wParam, lParam);
				CallMsgFunc(KM_AFTER_MOUSELEAVE, wParam, lParam);
			}
			m_bMouseIn = bMouseIn;
			break;
		}
		case WM_LBUTTONDOWN:
		{	POINT ptMouse;
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
			BOOL bMouseIn = PtInRect(&m_rect, ptMouse);
			if (bMouseIn)
			{
				CallMsgFunc(KM_BEFORE_LBTNDOWN, wParam, lParam);
				CallMsgFunc(KM_LBTNDOWN, wParam, lParam);
				CallMsgFunc(KM_AFTER_LBTNDOWN, wParam, lParam);
			}
			break;
		}
		case WM_LBUTTONUP:
		{	POINT ptMouse;
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
			BOOL bMouseIn = PtInRect(&m_rect, ptMouse);
			if (bMouseIn)
			{
				CallMsgFunc(KM_BEFORE_LBTNUP, wParam, lParam);
				CallMsgFunc(KM_LBTNUP, wParam, lParam);
				CallMsgFunc(KM_AFTER_LBTNUP, wParam, lParam);
			}
			break;
		}
		default:
			CallMsgFunc(Message, wParam, lParam);
			break;
		}
	}

	void  KrControl::CallMsgFunc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.find(Message);
		if (it != m_MsgFuncMap.end())
		{
			(*it->second)(this, wParam, lParam);
		}
	}

	void KrControl::UpdateRect()
	{

	}

	void KrControl::Draw(Graphics* pGraphics)
	{

	}
}//namespace KrUI