#include "KrEdit.h"

namespace KrUI
{

	Gdiplus::SizeF KrEdit::GetTextBounds(const wchar_t* szText)
	{
		Gdiplus::GraphicsPath path;
		Gdiplus::FontFamily fontfamily;
		m_pFont->GetFamily(&fontfamily);
// 		path.AddString(szText, -1, &fontfamily, m_pFont->GetStyle(), m_pFont->GetSize(), Gdiplus::PointF(0, 0),
// 			Gdiplus::StringFormat::GenericTypographic()/*&m_StringFormat*/);
		path.AddString(szText,-1, &fontfamily, m_pFont->GetStyle(), m_pFont->GetSize(), Gdiplus::PointF(0, 0),
			Gdiplus::StringFormat::GenericTypographic()/*&m_StringFormat*/);
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
					m_SelectTextPosFirst++;
					m_SelectTextPosSecond++;
				}
				else if (wParam == 8 && m_strText.size() != 0)//退格
				{
					m_strText.pop_back();
					m_SelectTextPosFirst--;
					m_SelectTextPosSecond--;
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
		//画光标
		if (m_bShowCursor && m_pKrWindow->GetFocusedCtrl() == this && m_SelectTextPosFirst == m_SelectTextPosSecond)
		{
			m_pGraphics->DrawLine(&Gdiplus::Pen(Gdiplus::Color::Black), GetXByCursorPos(m_SelectTextPosFirst) + 2,//把光标向后移动一个像素
				static_cast<int>((GetHeight() - GetStrHeight()) / 2), GetXByCursorPos(m_SelectTextPosFirst) + 2,
				static_cast<int>((GetHeight() + GetStrHeight()) / 2));
		}
		//框选文字
		//m_pGraphics->DrawRectangle(&Gdiplus::Pen(Gdiplus::Color::Black), m_Margin, static_cast<int>((GetHeight() - GetStrHeight()) / 2),
		//	GetXByCursorPos(m_SelectTextPosFirst) - m_Margin, GetStrHeight());
		//画文字内容:
 		m_pGraphics->DrawString(m_strText.c_str(), -1, m_pFont, Gdiplus::RectF(m_Margin, (GetHeight() - GetStrHeight()) / 2,
 			GetWidth() - m_Margin, GetHeight()), Gdiplus::StringFormat::GenericTypographic()/*&m_StringFormat*/, &Gdiplus::SolidBrush(m_FontColor));
	
// 		Gdiplus::GraphicsPath path;
// 		Gdiplus::FontFamily fontfamily;
// 		m_pFont->GetFamily(&fontfamily);
// 		// 		path.AddString(szText, -1, &fontfamily, m_pFont->GetStyle(), m_pFont->GetSize(), Gdiplus::PointF(0, 0),
// 		// 			Gdiplus::StringFormat::GenericTypographic()/*&m_StringFormat*/);
// 		path.AddString(m_strText.c_str(), -1, &fontfamily, m_pFont->GetStyle(), m_pFont->GetSize(), Gdiplus::PointF(0, 0),
// 			Gdiplus::StringFormat::GenericTypographic()/*&m_StringFormat*/);
// 		m_pGraphics->DrawPath(&Gdiplus::Pen(Gdiplus::Color::Black), &path);

		
		//m_pGraphics->DrawString(m_strText.c_str(), -1, m_pFont, Gdiplus::PointF(m_Margin, (GetHeight() - GetStrHeight()) / 2),&Gdiplus::SolidBrush(m_FontColor));
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
		if (x < (m_Margin + GetXByCursorPos(1)) / 2)return 0;
		for (int i = 0; i <= m_strText.size(); i++)
		{
			if (x >= ((GetXByCursorPos(i - 1) + GetXByCursorPos(i)) / 2) && x <= ((GetXByCursorPos(i) + GetXByCursorPos(i + 1)) / 2)) return i;
		}
		return m_strText.size();
	}

	unsigned int KrEdit::GetXByCursorPos(unsigned int CursorPos)
	{
		if (CursorPos <= 0) return m_Margin;
		return m_Margin + GetTextBounds(m_strText.substr(0, CursorPos).c_str()).Width;
	}

	unsigned int KrEdit::GetStrHeight()
	{
		Gdiplus::RectF strRc;
		m_pGraphics->MeasureString(L"KrEdit", -1, m_pFont, Gdiplus::RectF(5, 0, GetWidth(), GetHeight()), Gdiplus::StringFormat::GenericTypographic(), &strRc);
		return  strRc.Height;
	}

	void KrEdit::CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		int x = GET_X_LPARAM(lParam) - m_rect.left;
		switch (Message)
		{
		case KM_LBTNDOWN:
			m_SelectTextPosFirst = GetCursorPosByX(x);
			break;
		case KM_LBTNUP:
			m_SelectTextPosSecond = GetCursorPosByX(x);
			break;
		case WM_MOUSEMOVE:
			if (m_bMouseDown) m_SelectTextPosSecond = GetCursorPosByX(x);
			break;
		}
		KrUIBase::CallMsgProc(Message, wParam, lParam);
	}

	KrEdit::KrEdit()
	{
		m_BgColor = Gdiplus::Color::White;
		m_BorderColor = Gdiplus::Color(170, 170, 170);
		m_FontColor = Gdiplus::Color::Black;
		delete m_pFont;
		m_pFont = new Gdiplus::Font(L"新宋体", 14, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
		//							这里使用新宋体，等宽字体防止画字符串的时候字符间距随着长度变化的问题
		m_StringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
		m_StringFormat.SetLineAlignment(Gdiplus::StringAlignmentNear);
		m_hCursor = LoadCursor(nullptr, IDC_IBEAM);//设置鼠标进入后的样式
		m_Margin = 5;
		m_SelectTextPosFirst = 0;
		m_SelectTextPosSecond = 0;
	}
}// !KrUI