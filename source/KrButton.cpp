#include "KrButton.h"
#include "KrCore.h"
#include "KrDefine.h"
namespace KrUI
{

	//通用按钮：
	KrButton::KrButton()
	{
		m_MouseDownColor = Gdiplus::Color(9, 140, 188);
		m_MouseHoverColor = Gdiplus::Color(60, 195, 245);
		m_MouseLeaveColor = Gdiplus::Color(9, 163, 220);
		m_hCursor = LoadCursor(nullptr, IDC_HAND);//设置鼠标进入后的样式
	}

	void KrButton::SetMouseHoverColor(Gdiplus::Color color)
	{
		m_MouseHoverColor = color;
	}
	void KrButton::SetMouseDownColor(Gdiplus::Color color)
	{
		m_MouseDownColor = color;
	}
	void KrButton::SetMouseLeaveColor(Gdiplus::Color color)
	{
		m_MouseLeaveColor = color;
	}
	void KrButton::SetBorderColor(Gdiplus::Color color)
	{
		m_BorderColor = color;
	}
	Gdiplus::Color KrButton::GetMouseHoverColor()
	{
		return m_MouseHoverColor;
	}
	Gdiplus::Color KrButton::GetMouseDownColor()
	{
		return m_MouseDownColor;
	}
	Gdiplus::Color KrButton::GetMouseLeaveColor()
	{
		return m_MouseLeaveColor;
	}
	Gdiplus::Color KrButton::GetBorderColor()
	{
		return m_BorderColor;
	}
	void KrButton::Update()
	{
		//m_pGraphics->DrawImage(m_pKrWindow->m_pBmp, 0, 0, GetX(), GetY(), GetWidth(), GetHeight(), Gdiplus::Unit::UnitPixel);
		if ((m_bMouseIn && !m_bMouseDown) && m_ButtonStatus != mouse_hover)
		{
			this->DrawMouseHoverBmp();
			this->DrawContent();
		}
		else if (((!m_bMouseDown) && (!m_bMouseIn)) && m_ButtonStatus != mouse_leave)
		{
			this->DrawMouseLeaveBmp();
			this->DrawContent();
		}
		else if (m_bMouseDown && (m_ButtonStatus != mouse_down))
		{
			this->DrawMouseDownBmp();
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
		this->m_pGraphics->DrawString((WCHAR*)m_Name, -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(0), static_cast<Gdiplus::REAL>(0), static_cast<Gdiplus::REAL>(GetWidth()), static_cast<Gdiplus::REAL>(GetHeight())), &m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
	}
	KrButton::~KrButton()
	{
	}

	void KrButton::SetButtonStatus(Mouse_Status bs)
	{
		m_ButtonStatus = bs;
	}
	LRESULT KrButton::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}


	//关闭按钮：
	KrCloseButton::KrCloseButton()
	{
		m_MouseDownColor = Gdiplus::Color(203, 51, 39);
		m_MouseHoverColor = Gdiplus::Color(250, 99, 87);
		//新建笔
		m_pPen = new Gdiplus::Pen(Gdiplus::Color::White, 2);

		m_Margin = 5;
		m_StringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
		m_StringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		RegMsg(KM_LBTNDOWN, KrCloseButton::DestroyKrWindow);
	}

	KrCloseButton::~KrCloseButton()
	{
		delete m_pPen;
	}

	UINT KrCloseButton::GetMargin()
	{
		return m_Margin;
	}
	void KrCloseButton::DrawContent()
	{
		m_rect.left = m_pKrWindow->GetWidth() - m_pKrWindow->m_CaptionHeight + m_Margin;
		m_rect.top = m_Margin;
		m_rect.right = m_pKrWindow->GetWidth() - m_Margin;
		m_rect.bottom = m_pKrWindow->m_CaptionHeight - m_Margin;
		// 		Gdiplus::Font* pfont = m_pFont;
		// 		m_pFont = new Gdiplus::Font(L"宋体", 14, Gdiplus::FontStyleBold);
		// 		//KrButton::DrawContent();
		// 
		// 		//this->m_pGraphics->DrawString(L"∫", -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(0), static_cast<Gdiplus::REAL>(0), static_cast<Gdiplus::REAL>(GetWidth()), static_cast<Gdiplus::REAL>(GetHeight())), &m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
		// 
		// 		delete m_pFont;
		// 		m_pFont = pfont;

		m_pGraphics->DrawLine(m_pPen, 3, 3, GetWidth() - 6, GetHeight() - 6);
		m_pGraphics->DrawLine(m_pPen, 3, GetHeight() - 6, GetWidth() - 6, 3);
	}

	LRESULT KrCloseButton::DestroyKrWindow(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam)
	{
		return SendMessage(dynamic_cast<KrCloseButton*>(pKrMessageHandler)->GetParantWindow()->GetHWND(), WM_CLOSE, wParam, lParam);
	}
}//!KrUI