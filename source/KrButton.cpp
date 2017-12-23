#include "KrButton.h"
#include "KrCore.h"
namespace KrUI
{
	KrButton::KrButton(KrWindow* pKrWindow)
	{
		m_pKrWindow = pKrWindow;
		m_MouseDownColor = RGB(9, 140, 188);
		m_MouseHoverColor = RGB(60, 195, 245);
		m_MouseLeaveColor = RGB(9, 163, 220);
		m_hDc = CreateCompatibleDC(pKrWindow->GetDc());
	}

	void KrButton::SetMouseHoverColor(COLORREF color)
	{
		m_MouseHoverColor = color;
	}
	void KrButton::SetMouseDownColor(COLORREF color)
	{
		m_MouseDownColor = color;
	}
	void KrButton::SetMouseLeaveColor(COLORREF color)
	{
		m_MouseLeaveColor = color;
	}
	void KrButton::SetBorderColor(COLORREF color)
	{
		m_BorderColor = color;
	}
	COLORREF KrButton::GetMouseHoverColor()
	{
		return m_MouseHoverColor;
	}
	COLORREF KrButton::GetMouseDownColor()
	{
		return m_MouseDownColor;
	}
	COLORREF KrButton::GetMouseLeaveColor()
	{
		return m_MouseLeaveColor;
	}
	COLORREF KrButton::GetBorderColor()
	{
		return m_BorderColor;
	}
	void KrButton::UpdateDc()
	{

	}

}//!KrUI