#include "KrButton.h"
#include "KrCore.h"
namespace KrUI
{
	KrButton::KrButton()
	{
		m_MouseDownColor = Color(9, 140, 188);
		m_MouseHoverColor = Color(60, 195, 245);
		m_MouseLeaveColor = Color(9, 163, 220);
	}

	void KrButton::SetMouseHoverColor(Color color)
	{
		m_MouseHoverColor = color;
	}
	void KrButton::SetMouseDownColor(Color color)
	{
		m_MouseDownColor = color;
	}
	void KrButton::SetMouseLeaveColor(Color color)
	{
		m_MouseLeaveColor = color;
	}
	void KrButton::SetBorderColor(Color color)
	{
		m_BorderColor = color;
	}
	Color KrButton::GetMouseHoverColor()
	{
		return m_MouseHoverColor;
	}
	Color KrButton::GetMouseDownColor()
	{
		return m_MouseDownColor;
	}
	Color KrButton::GetMouseLeaveColor()
	{
		return m_MouseLeaveColor;
	}
	Color KrButton::GetBorderColor()
	{
		return m_BorderColor;
	}
	void KrButton::UpdateDc()
	{
		if (m_bMouseDown && (m_ButtonStatus != mouse_down))
		{
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseDownColor), 0, 0, GetWidth(), GetHeight());
			m_ButtonStatus = mouse_down;
		}
		else if ((m_bMouseIn && !m_bMouseDown) && m_ButtonStatus != mouse_hover)
		{
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseHoverColor), 0, 0, GetWidth(), GetHeight());
			m_ButtonStatus = mouse_hover;
		}
		else if (((!m_bMouseDown) && (!m_bMouseIn)) && m_ButtonStatus != mouse_leave)
		{
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseLeaveColor), 0, 0, GetWidth(), GetHeight());
			m_ButtonStatus = mouse_leave;
		}
		BitBlt(m_pKrWindow->GetTempDc(), GetX(), GetY(), GetWidth(), GetHeight(), m_hDc, 0, 0, SRCCOPY);
	}
	KrButton::~KrButton()
	{
	}

	LRESULT KrButton::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}

}//!KrUI