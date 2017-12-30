#include "KrButton.h"
#include "KrCore.h"
#include "KrDefine.h"
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
			this->DrawMouseDownBmp();
			this->DrawContent();
		}
		else if ((m_bMouseIn && !m_bMouseDown) && m_ButtonStatus != mouse_hover)
		{
			this->DrawMouseHoverBmp();
			this->DrawContent();
		}
		else if (((!m_bMouseDown) && (!m_bMouseIn)) && m_ButtonStatus != mouse_leave)
		{
			this->DrawMouseLeaveBmp();
			this->DrawContent();
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
		this->m_pGraphics->DrawString((WCHAR*)m_Name, -1,m_pFont, RectF(0, 0, GetWidth(), GetHeight()), &m_StringFormat, &SolidBrush(Color(255, 255, 255)));
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
		RegMsg(KM_LBTNDOWN, KrCloseButton::DestroyKrWindow);
	}
	
	void KrCloseButton::DrawContent()
	{
		m_rect.left = m_pKrWindow->GetWidth() - m_pKrWindow->m_CaptionHeight + m_Margin;
		m_rect.top = m_Margin;
		m_rect.right = m_pKrWindow->GetWidth() - m_Margin;
		m_rect.bottom = m_pKrWindow->m_CaptionHeight - m_Margin;
		Font* pfont = m_pFont;
		m_pFont = new Font(L"宋体",14,FontStyleBold);
		KrButton::DrawContent();
		delete m_pFont;
		m_pFont = pfont;
	}

	LRESULT KrCloseButton::DestroyKrWindow(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam)
	{
		return SendMessage(dynamic_cast<KrCloseButton*>(pKrMessageHandler)->GetParantWindow()->GetHWND(), WM_DESTROY, wParam, lParam);
	}
}//!KrUI