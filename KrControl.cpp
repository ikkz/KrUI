#include"KrControl.h"

namespace KrUI{

	void    KrControl::SetCtrlType(UINT type)
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
		Draw();
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
		Draw();
	}


	void KrControl::SetY(int y)
	{
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		Draw();
	}


	void KrControl::SetWidth(int width)
	{
		m_rect.right = m_rect.left + width;
		Draw();
	}



	void KrControl::SetHeight(int height)
	{
		m_rect.bottom = m_rect.top + height;
		Draw();
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
		for (map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.begin(); it != m_MsgFuncMap.end(); ++it)
		{
			if (it->first == msg)
			{
				it->second = func;
			}
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
		if (Message==WM_MOUSEMOVE)
		{
			POINT ptMouse;
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
			bool bMouseIn = PtInRect(&m_rect, ptMouse);
			if (m_bMouseIn == false && bMouseIn == true)
			{
				//SendMessage(m_pKrWindow->GetHWND(), KM_MOUDEENTER, NULL, NULL);
				CallMsgFunc(KM_MOUSEENTER, wParam, lParam);
			}
			else if (m_bMouseIn == true && bMouseIn == false)
			{
				//SendMessage(m_pKrWindow->GetHWND(), KM_MOUSELEAVE, NULL, NULL);
				CallMsgFunc(KM_MOUSELEAVE, wParam, lParam);
			}
			m_bMouseIn = bMouseIn;
		}
		CallMsgFunc(Message, wParam, lParam);
		
	}

	void  KrControl::CallMsgFunc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		for (map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.begin(); it != m_MsgFuncMap.end(); it++)
		{
			if (it->first == Message)
			{
				it->second(this, wParam, lParam);
			}
		}
	}

	void KrControl::Draw()
	{

	}


}