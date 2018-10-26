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
		m_hCursor = nullptr;//设置鼠标进入后的样式
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
	Gdiplus::Color KrButton::GetMouseHoverColor() const
	{
		return m_MouseHoverColor;
	}
	Gdiplus::Color KrButton::GetMouseDownColor() const
	{
		return m_MouseDownColor;
	}
	Gdiplus::Color KrButton::GetMouseLeaveColor() const
	{
		return m_MouseLeaveColor;
	}
	Gdiplus::Color KrButton::GetBorderColor() const
	{
		return m_BorderColor;
	}
	void KrButton::Update()
	{
		if (m_bMouseIn && (!m_bMouseDown))
		{
			this->DrawMouseHoverBmp();
			this->DrawContent();
		}
		else if (m_bMouseDown&&m_bMouseIn)
		{
			this->DrawMouseDownBmp();
			this->DrawContent();
		}
		else
		{
			this->DrawMouseLeaveBmp();
			this->DrawContent();
		}
		KrUIBase::Update();
	}

	void KrButton::DrawMouseDownBmp()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseDownColor), 0, 0, GetWidth(), GetHeight());
	}
	void KrButton::DrawMouseHoverBmp()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseHoverColor), 0, 0, GetWidth(), GetHeight());
	}
	void KrButton::DrawMouseLeaveBmp()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_MouseLeaveColor), 0, 0, GetWidth(), GetHeight());
	}
	void KrButton::DrawContent()
	{
		this->m_pGraphics->DrawString(m_strName.c_str(), -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(0), static_cast<Gdiplus::REAL>(0), static_cast<Gdiplus::REAL>(GetWidth()), static_cast<Gdiplus::REAL>(GetHeight())), &m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
	}
	KrButton::~KrButton()
	{
	}

	LRESULT KrButton::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}

	void KrButton::CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case KM_MOUSEENTER:
		case KM_MOUSELEAVE:
		case KM_LBTNDOWN:
		case KM_LBTNUP:
			//TODO
			if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
		}
		return KrUIBase::CallMsgProc(Message, wParam, lParam);
	}



	//关闭按钮：
	KrCloseButton::KrCloseButton()
	{
		m_MouseDownColor = Gdiplus::Color(203, 51, 39);
		m_MouseHoverColor = Gdiplus::Color(250, 99, 87);
		//新建笔
		m_pPen = new Gdiplus::Pen(Gdiplus::Color::White, 2);

		m_Margin = 7;
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
		dynamic_cast<KrCloseButton*>(pKrMessageHandler)->m_pKrWindow->CallMsgProc(KM_WNDDELETE, wParam, lParam);
		KrUIManager::GetpKrUIManager()->DeleteWindow(dynamic_cast<KrCloseButton*>(pKrMessageHandler)->GetParantWindow());
		return 0;
	}
}//!KrUI