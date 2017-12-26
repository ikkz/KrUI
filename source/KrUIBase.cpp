#include "KrUIBase.h"

namespace KrUI
{
	RECT* KrUIBase::GetRect()
	{
		return &m_rect;
	}


	int KrUIBase::GetX()
	{
		return m_rect.left;
	}


	int KrUIBase::GetY()
	{
		return m_rect.top;
	}



	int KrUIBase::GetWidth()
	{
		return m_rect.right - m_rect.left;
	}



	int KrUIBase::GetHeight()
	{
		return m_rect.bottom - m_rect.top;
	}


	void KrUIBase::SetX(UINT x)
	{
		int width = GetWidth();
		m_rect.left = x;
		m_rect.right = x + width;

	}
	void KrUIBase::SetY(UINT y)
	{
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;

	}

	void KrUIBase::SetXY(UINT x, UINT y)
	{
		int width = GetWidth();
		int height = GetHeight();
		m_rect.left = x;
		m_rect.right = x + width;
		m_rect.top = y;
		m_rect.bottom = y + height;
	}

	void KrUIBase::SetWidth(UINT width)
	{
		m_rect.right = m_rect.left + width;
	}

	void KrUIBase::SetHeight(UINT height)
	{
		m_rect.bottom = m_rect.top + height;
	}

	void KrUIBase::SetSize(UINT x, UINT y, UINT width, UINT height)
	{
		m_rect.left = x;
		m_rect.right = x + width;
		m_rect.top = y;
		m_rect.bottom = y + height;
	}


	bool KrUIBase::IsVisible()
	{
		return m_bVisible;
	}

	void KrUIBase::SetRect(RECT* pRect)
	{
		m_rect.left = pRect->left;
		m_rect.right = pRect->right;
		m_rect.top = pRect->top;
		m_rect.bottom = pRect->bottom;
	}


	void KrUIBase::Show()
	{
		m_bVisible = true;
	}

	void KrUIBase::Hide()
	{
		m_bVisible = false;
	}

	void KrUIBase::SetDc(HDC hdc)
	{
		m_hDc = hdc;
	}

	HDC KrUIBase::GetDc()
	{
		return m_hDc;
	}

	void KrUIBase::SetName(LPCWSTR name)
	{
		m_Name = name;
	}
	LPCWSTR KrUIBase::GetName()
	{
		return m_Name;
	}
	LRESULT KrUIBase::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
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
				CallMsgProc(KM_MOUSEENTER, wParam, lParam);
			}
			else if (m_bMouseIn == true && bMouseIn == false)
			{
				//SendMessage(m_pKrWindow->GetHWND(), KM_MOUSELEAVE, NULL, NULL);
				CallMsgProc(KM_MOUSELEAVE, wParam, lParam);
			}
			m_bMouseIn = bMouseIn;
			break;
		}
		case WM_LBUTTONDOWN:
		{
			POINT ptMouse;
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
			BOOL bMouseIn = PtInRect(&m_rect, ptMouse);
			if (bMouseIn)
			{
				CallMsgProc(KM_LBTNDOWN, wParam, lParam);
			}
			break;
		}
		case WM_LBUTTONUP:
		{
			POINT ptMouse;
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
			BOOL bMouseIn = PtInRect(&m_rect, ptMouse);
			if (bMouseIn)
			{
				CallMsgProc(KM_LBTNUP, wParam, lParam);
			}
			break;
		}
		default:
			break;
		}
		return KrMessageHandler::HandleMessage(Message, wParam, lParam);
	}
	KrUIBase::KrUIBase()
	{
		m_bMouseIn = false;
	}
}// namespace KrUI