#include "KrButton.h"
#include "KrCore.h"
namespace KrUI
{

	//通用按钮：
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
		//m_pGraphics->DrawImage(m_pKrWindow->m_pBmp, 0, 0, GetX(), GetY(), GetWidth(), GetHeight(), Gdiplus::Unit::UnitPixel);
		if (m_bMouseDown && (m_ButtonStatus != mouse_down))
		{
			DrawMouseDownBmp();
			DrawContent();
		}
		else if ((m_bMouseIn && !m_bMouseDown) && m_ButtonStatus != mouse_hover)
		{
			DrawMouseHoverBmp();
			DrawContent();
		}
		else if (((!m_bMouseDown) && (!m_bMouseIn)) && m_ButtonStatus != mouse_leave)
		{
			DrawMouseLeaveBmp();
			DrawContent();
		}
		m_pKrWindow->GetBmpGraphics()->DrawImage(m_pBmp, GetX(), GetY(), GetWidth(), GetHeight());
	}

	void KrButton::DrawMouseDownBmp()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseDownColor), 0, 0, GetWidth(), GetHeight());
		m_ButtonStatus = mouse_down;
	}
	void KrButton::DrawMouseHoverBmp()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseHoverColor), 0, 0, GetWidth(), GetHeight());
		m_ButtonStatus = mouse_hover;
	}
	void KrButton::DrawMouseLeaveBmp()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseLeaveColor), 0, 0, GetWidth(), GetHeight());
		m_ButtonStatus = mouse_leave;
	}
	void KrButton::DrawContent()
	{
		m_pGraphics->DrawString((WCHAR*)m_Name, -1, &Font(L"宋体", 10), RectF(0, 0, GetWidth(), GetHeight()), &m_StringFormat, &SolidBrush(Color(255, 255, 255)));
	}
	KrButton::~KrButton()
	{
	}

	LRESULT KrButton::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}


//关闭按钮：
	KrCloseButton::KrCloseButton()
	{
		m_MouseDownColor = Color(203, 51, 39);
		m_MouseHoverColor = Color(250, 99, 87);
		m_Margin = 5;
	}

	void KrCloseButton::DrawContent()
	{
		SetSize(m_pKrWindow->GetWidth() - m_pKrWindow->m_CaptionHeight + m_Margin, m_Margin, m_pKrWindow->m_CaptionHeight - m_Margin * 2, m_pKrWindow->m_CaptionHeight - m_Margin * 2);
		// 		switch (m_ButtonStatus)
		// 		{
		// 		case KrUI::mouse_leave:
		// 
		// 			break;
		// 		case KrUI::mouse_down:
		// 		case KrUI::mouse_hover:
		// 
		// 			break;
		// 		default:
		// 			break;
		//m_pGraphics->DrawLine(&Pen(Color::White), 3, 3, GetX() - 3, GetY() - 3);
		//m_pGraphics->DrawLine(&Pen(Color::White), 3, GetY() - 3, GetX() - 3, 3);
	}

	void KrCloseButton::UpdateDc()
	{
// 		//m_pGraphics->DrawImage(m_pKrWindow->m_pBmp, 0, 0, GetX(), GetY(), GetWidth(), GetHeight(), Gdiplus::Unit::UnitPixel);
// 		if (m_bMouseDown && (m_ButtonStatus != mouse_down))
// 		{
// 			cout << "down" << endl;
// 
// 			DrawMouseDownBmp();
// 			DrawContent();
// 
// 		}
// 		else if ((m_bMouseIn && !m_bMouseDown) && m_ButtonStatus != mouse_hover)
// 		{
// 			cout << "hover" << endl;
// 			DrawMouseHoverBmp();
// 			DrawContent();
// 		}
// 		else if (((!m_bMouseDown) && (!m_bMouseIn)) && m_ButtonStatus != mouse_leave)
// 		{
// 			cout << "leave" << endl;
// 			DrawMouseLeaveBmp();
// 			DrawContent();
// 		}
// 		m_pKrWindow->GetBmpGraphics()->DrawImage(m_pBmp, GetX(), GetY(), GetWidth(), GetHeight());
		KrButton::UpdateDc();
	}
}//!KrUI