#include "KrEdit.h"

namespace KrUI
{
	Gdiplus::SizeF GetTextBounds(Gdiplus::Font* pfont, Gdiplus::StringFormat* sf, const wchar_t* szText)
	{
		Gdiplus::GraphicsPath path;
		Gdiplus::FontFamily fontfamily;
		pfont->GetFamily(&fontfamily);
		path.AddString(szText, -1, &fontfamily, pfont->GetStyle(), pfont->GetSize() + 3.7, Gdiplus::PointF(0, 0), sf);
		Gdiplus::RectF bounds;
		path.GetBounds(&bounds);
		return Gdiplus::SizeF(bounds.Width, bounds.Height);
	}

	void KrEdit::SetText(std::wstring str)
	{
		m_strText = str;
	}

	std::wstring KrEdit::GetText()
	{
		return m_strText;
	}

	LRESULT KrEdit::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (m_pKrWindow->GetFocusedCtrl() == this)
		{
			switch (Message)
			{
			case WM_CHAR:
				if (wParam >= 32 && wParam <= 126)//字符
				{
					m_strText += static_cast<char>(wParam);
				}
				else if (wParam == 8 && m_strText.size() != 0)//退格
				{
					m_strText.pop_back();
				}
				// 				if (wParam == 8 && m_strText.size() != 0)//退格
				// 				{
				// 					m_strText.pop_back();
				// 				}
				// 				else
				// 				{
				// 					m_strText += static_cast<wchar_t>(wParam);
				// 				}
				break;
			}
		}
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}

	void KrEdit::UpdateDc()
	{
		m_Time += TIMER_INTERVAL;
		if (m_Time >= 500)
		{
			m_bShowCursor = !m_bShowCursor;
			m_Time = 0;
		}
		//画背景:
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_BgColor), 0, 0, GetWidth(), GetHeight());
		if (m_bShowCursor&&m_pKrWindow->GetFocusedCtrl() == this&&m_SelectTextPosFirst == m_SelectTextPosSecond)
		{
			m_pGraphics->DrawLine(&Gdiplus::Pen(Gdiplus::Color::Black), GetXByCursorPos(m_SelectTextPosFirst), static_cast<int>((GetHeight() - GetStrHeight()) / 2), GetXByCursorPos(m_SelectTextPosFirst), static_cast<int>((GetHeight() + GetStrHeight()) / 2));
		}
		//m_pGraphics->DrawRectangle(&Gdiplus::Pen(Gdiplus::Color::Black), m_Margin, static_cast<int>((GetHeight() - GetStrHeight()) / 2), (int)GetTextBounds(m_pFont, &m_StringFormat, m_strText.c_str()).Width, (int)GetTextBounds(m_pFont, &m_StringFormat, m_strText.c_str()).Height);
		//画文字内容:
		m_pGraphics->DrawString(m_strText.c_str(), -1, m_pFont, Gdiplus::RectF(m_Margin, 0, GetWidth(), GetHeight()), &m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
		//画边框:
		if ((m_bMouseIn && !m_bMouseDown) && m_ButtonStatus != mouse_hover)
		{
			m_ButtonStatus = mouse_hover;
		}
		else if (((!m_bMouseDown) && (!m_bMouseIn)) && m_ButtonStatus != mouse_leave)
		{
			m_ButtonStatus = mouse_leave;
		}
		else if (m_bMouseDown && (m_ButtonStatus != mouse_down))
		{
			m_ButtonStatus = mouse_down;
		}																		// Color(21,131,221)是鼠标移动到文本框上时边框的颜色
		m_pGraphics->DrawRectangle(&Gdiplus::Pen((m_ButtonStatus == mouse_leave ? m_BorderColor : Gdiplus::Color(21, 131, 221))),
			0, 0, GetWidth() - 1, GetHeight() - 1);
		//画到窗口Mmp上
		m_pKrWindow->GetBmpGraphics()->DrawImage(m_pBmp, GetX(), GetY(), GetWidth(), GetHeight());
	}

	unsigned int KrEdit::GetCursorPosByX(unsigned int x)
	{
		//  t h i s 
		// | | | | |
		// 0 1 2
		//转换为文本矩形的横坐标
		if (x <= m_Margin) return 0;
		if (x <= (GetXByCursorPos(0) + GetXByCursorPos(1)) / 2) return 0;
		//遍历字符串列表获取长度进行比较
		for (int i = 0; i <= m_strText.size() + 1; i++)
		{
			if (x >= GetXByCursorPos(m_strText.size() + 1)) return m_strText.size() + 1;
			if (x >= (GetXByCursorPos(i - 1) + GetXByCursorPos(i)) / 2 && x <= (GetXByCursorPos(i) + GetXByCursorPos(i + 1)))
			{
				return i;
			}
		}
		return m_strText.size() + 1;
	}



	unsigned int KrEdit::GetXByCursorPos(unsigned int CursorPos)
	{
		//if (CursorPos == 0)return m_Margin;
		if (CursorPos > m_strText.size() + 1) CursorPos = m_strText.size() + 1;
		// 		SIZE size;
		// 		::GetTextExtentPoint(m_pKrWindow->GetDc, m_strText.c_str(), CursorPos, &size);
		return m_Margin + GetTextBounds(m_pFont, &m_StringFormat, m_strText.substr(0, CursorPos).c_str()).Width + 4;

		///////////////////////////////////////////////////														///
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	unsigned int KrEdit::GetStrHeight()
	{
		Gdiplus::RectF strRc;
		m_pGraphics->MeasureString(m_strText.c_str(), -1, m_pFont, Gdiplus::RectF(5, 0, GetWidth(), GetHeight()), &m_StringFormat, &strRc);
		return  strRc.Height;
	}

	void KrEdit::CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		int x = GET_X_LPARAM(lParam) - m_rect.left;
		switch (Message)
		{
		case KM_LBTNDOWN:
			m_SelectTextPosFirst = GetCursorPosByX(x);
			//std::cout << "first=" << m_SelectTextPosFirst << std::endl;
			break;
		case KM_LBTNUP:
			m_SelectTextPosSecond = GetCursorPosByX(x);
			//std::cout << "second=" << m_SelectTextPosSecond << std::endl;
			std::cout << x << std::endl;
			for (int i = 0; i <= m_strText.size(); i++)
			{
				std::cout << i << " : " << GetXByCursorPos(i) << std::endl;
			}

			break;
		}
		KrUIBase::CallMsgProc(Message, wParam, lParam);
	}

	KrEdit::KrEdit()
	{
		m_BgColor = Gdiplus::Color::White;
		m_BorderColor = Gdiplus::Color(170, 170, 170);
		m_FontColor = Gdiplus::Color::Black;
		m_StringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
		m_StringFormat.SetFormatFlags(Gdiplus::StringFormatFlags::StringFormatFlagsNoWrap);
		//m_StringFormat.SetFormatFlags(Gdiplus::StringFormatFlags::StringFormatFlagsMeasureTrailingSpaces);
		m_hCursor = LoadCursor(nullptr, IDC_IBEAM);//设置鼠标进入后的样式
		m_Margin = 0;
		m_SelectTextPosFirst = 0;
		m_SelectTextPosSecond = 0;
	}

}// !KrUI