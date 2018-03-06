#include "KrEdit.h"

namespace KrUI
{

	Gdiplus::SizeF KrEdit::GetTextBounds(std::wstring strText)
	{
		Gdiplus::GraphicsPath path;
		Gdiplus::FontFamily fontfamily;
		m_pFont->GetFamily(&fontfamily);
		path.AddString(strText.c_str(), -1, &fontfamily, m_pFont->GetStyle(), m_pFont->GetSize(), Gdiplus::PointF(0, 0),
			Gdiplus::StringFormat::GenericTypographic()/*&m_StringFormat*/);
		Gdiplus::RectF bounds;
		path.GetBounds(&bounds);
		return Gdiplus::SizeF(bounds.Width, bounds.Height);
	}

	void KrEdit::SetText(std::wstring str)
	{
		m_strText = str;
		StringChange();
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
				if (wParam <= 31 || wParam == 127 || wParam == ' ')break;
				if (m_SelectTextPosFirst == m_SelectTextPosSecond)//相等时
				{
					m_strText.insert(m_SelectTextPosFirst, 1, static_cast<wchar_t>(wParam));
					m_SelectTextPosFirst++;
					m_SelectTextPosSecond++;
					StringChange();
				}
				else//不相等时
				{
					m_strText.erase(m_SelectTextPosFirst < m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond,
						(m_SelectTextPosFirst > m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond) -
						(m_SelectTextPosFirst < m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond));

					if (m_SelectTextPosFirst == (m_SelectTextPosFirst > m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond))
					{
						m_SelectTextPosFirst = m_SelectTextPosSecond;
					}
					else
					{
						m_SelectTextPosSecond = m_SelectTextPosFirst;
					}
					m_strText.insert(m_SelectTextPosFirst, 1, static_cast<wchar_t>(wParam));
					m_SelectTextPosFirst++;
					m_SelectTextPosSecond++;
					StringChange();
				}
				CallMsgProc(KM_TEXTCHANGE, lParam, wParam);
				break;
			case WM_KEYUP:
				if (m_SelectTextPosFirst == m_SelectTextPosSecond)
				{
					switch (wParam)
					{
					case VK_BACK:
						if (m_strText.size() != 0)
						{
							m_strText.erase(m_SelectTextPosFirst - 1, 1);
							m_SelectTextPosFirst--;
							m_SelectTextPosSecond--;
							StringChange();
							CallMsgProc(KM_TEXTCHANGE, lParam, wParam);
						}
						break;
					case VK_RIGHT:
						if (m_SelectTextPosFirst == m_strText.size())break;
						m_SelectTextPosFirst++;
						m_SelectTextPosSecond++;
						break;
					case VK_LEFT:
						if (m_SelectTextPosFirst == 0)break;
						m_SelectTextPosFirst--;
						m_SelectTextPosSecond--;
						break;
					case VK_DELETE:
						if (m_SelectTextPosFirst < m_strText.size())m_strText.erase(m_SelectTextPosFirst, 1);
						StringChange();
						CallMsgProc(KM_TEXTCHANGE, lParam, wParam);
						break;
					default:
						break;
					}
				}
				else
				{
					switch (wParam)
					{
					case VK_BACK:
					case VK_DELETE:
						m_strText.erase(m_SelectTextPosFirst < m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond,
							(m_SelectTextPosFirst > m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond) -
							(m_SelectTextPosFirst < m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond));

						if (m_SelectTextPosFirst == (m_SelectTextPosFirst > m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond))
						{
							m_SelectTextPosFirst = m_SelectTextPosSecond;
						}
						else
						{
							m_SelectTextPosSecond = m_SelectTextPosFirst;
						}
						StringChange();
						CallMsgProc(KM_TEXTCHANGE, lParam, wParam);
						break;
					case VK_RIGHT:
						m_SelectTextPosFirst = m_SelectTextPosFirst > m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond;
						m_SelectTextPosSecond = m_SelectTextPosFirst;
						break;
					case VK_LEFT:
						m_SelectTextPosFirst = m_SelectTextPosFirst < m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond;
						m_SelectTextPosSecond = m_SelectTextPosFirst;
						break;
					default:
						break;
					}
				}
				break;
			case WM_TIMER:
				m_Time += TIMER_INTERVAL;
				if (m_Time >= 500)
				{
					m_bShowCursor = !m_bShowCursor;
					m_Time = 0;
					//TODO
					if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
				}
				break;
			default:
				break;
			}
		}
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}

	void KrEdit::CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case KM_LBTNDOWN:
			if (m_pKrWindow != nullptr)m_pKrWindow->SetFocusedCtrl(this);
			m_SelectTextPosFirst = GetCursorPosByX(GET_X_LPARAM(lParam));
			m_SelectTextPosSecond = GetCursorPosByX(GET_X_LPARAM(lParam));
			//TODO
			if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
			break;
		case KM_LBTNUP:
			m_SelectTextPosSecond = GetCursorPosByX(GET_X_LPARAM(lParam));
			break;
		case KM_MOUSEMOVE:
			if (m_bMouseDown && m_bMouseIn)
			{
				m_SelectTextPosSecond = GetCursorPosByX(GET_X_LPARAM(lParam));
				//TODO
				if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
			}
			break;
		}
		KrUIBase::CallMsgProc(Message, wParam, lParam);
	}

	void KrEdit::Update()
	{

		//画背景:
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_BgColor), 0, 0, GetWidth(), GetHeight());
		//画选中背景
		if (m_SelectTextPosFirst != m_SelectTextPosSecond && m_pKrWindow->GetFocusedCtrl() == this)
		{
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(200, 200, 200)),
				GetXByCursorPos(m_SelectTextPosFirst < m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond),
				static_cast<int>((GetHeight() - 1.3*GetStrHeight()) / 2),
				GetXByCursorPos(m_SelectTextPosFirst > m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond) -
				GetXByCursorPos(m_SelectTextPosFirst < m_SelectTextPosSecond ? m_SelectTextPosFirst : m_SelectTextPosSecond),
				static_cast<int>(1.3*GetStrHeight())
			);
		}
		//画光标
		if (m_bShowCursor && m_pKrWindow->GetFocusedCtrl() == this && m_SelectTextPosFirst == m_SelectTextPosSecond)
		{
			m_pGraphics->DrawLine(&Gdiplus::Pen(Gdiplus::Color::Black), GetXByCursorPos(m_SelectTextPosFirst),
				static_cast<int>((GetHeight() - GetStrHeight()) / 2), GetXByCursorPos(m_SelectTextPosFirst),
				static_cast<int>((GetHeight() + GetStrHeight()) / 2));
		}
		//画文字内容:
		m_pGraphics->DrawString(m_strText.c_str(), -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(m_Margin), static_cast<Gdiplus::REAL>((GetHeight() - GetStrHeight()) / 2),
			static_cast<Gdiplus::REAL>(GetWidth() - m_Margin), static_cast<Gdiplus::REAL>(GetHeight())), Gdiplus::StringFormat::GenericTypographic()/*&m_StringFormat*/, &Gdiplus::SolidBrush(m_FontColor));
		//画边框:														// Color(21,131,221)是鼠标移动到文本框上时边框的颜色
		m_pGraphics->DrawRectangle(&Gdiplus::Pen((m_bMouseIn ? Gdiplus::Color(21, 131, 221) : m_BorderColor)),
			0, 0, GetWidth() - 1, GetHeight() - 1);
		//画到窗口Mmp上
		KrUIBase::Update();
	}

	void KrEdit::ChangeBmpSize()
	{
		KrUIBase::ChangeBmpSize();
		m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
	}

	unsigned int KrEdit::GetCursorPosByX(unsigned int x)
	{
		//  t h i s
		// | | | | |
		// 0 1 2
		//转换为文本矩形的横坐标
		if (x < (m_Margin + GetXByCursorPos(1)) / 2)return 0;
		if (x >= GetXByCursorPos(m_strText.size()))return m_strText.size();
		for (unsigned int i = 0; i <= m_strText.size(); i++)
		{
			if (x >= ((GetXByCursorPos(i - 1) + GetXByCursorPos(i)) / 2) && x <= ((GetXByCursorPos(i) + GetXByCursorPos(i + 1)) / 2)) return i;
		}
		return m_strText.size();
	}

	unsigned int KrEdit::GetXByCursorPos(unsigned int CursorPos)
	{
		if (CursorPos <= 0) return m_Margin;
		if (CursorPos > m_strText.size()) CursorPos = m_strText.size();
		return m_Margin + m_StringLength[CursorPos] + 2;
	}
	/*
	if (strText[strText.size() - 1] == L' ')
	{
		bounds.Width += (GetTextBounds(L"K R").Width - GetTextBounds(L"KR").Width);
	}
	*/
	//更新字符串长度
	void KrEdit::StringChange()
	{
		m_StringLength.clear();
		unsigned int nWidth = 0;
		for (unsigned int i = 0; i <= m_strText.size(); i++)
		{
			nWidth = static_cast<unsigned int>(GetTextBounds(m_strText.substr(0, i)).Width);
			// 			if (m_strText[i] == ' ')
			// 			{
			// 				nWidth = (i == 0 ? 0 : m_StringLength[i - 1]) + (GetTextBounds(L"K R").Width - GetTextBounds(L"KR").Width);
			// 			}
			m_StringLength.push_back(nWidth);
		}
		//TODO
		if (m_pKrWindow != nullptr)m_pKrWindow->UpdateUI(this);
	}

	unsigned int KrEdit::GetStrHeight()
	{
		Gdiplus::RectF strRc;
		m_pGraphics->MeasureString(L"KrEdit", -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(5), static_cast<Gdiplus::REAL>(0), static_cast<Gdiplus::REAL>(GetWidth()), static_cast<Gdiplus::REAL>(GetHeight())), Gdiplus::StringFormat::GenericTypographic(), &strRc);
		return  static_cast<unsigned int>(strRc.Height);
	}
	// 
	// 	void KrEdit::CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam)
	// 	{
	// 		//int x = GET_X_LPARAM(lParam) - m_rect.left;
	// 
	// 		KrUIBase::CallMsgProc(Message, wParam, lParam);
	// 	}



	KrEdit::KrEdit()
	{
		m_BgColor = Gdiplus::Color::White;
		m_BorderColor = Gdiplus::Color(170, 170, 170);
		m_FontColor = Gdiplus::Color::Black;
		delete m_pFont;
		m_pFont = new Gdiplus::Font(L"新宋体", 20, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
		//							这里使用新宋体，等宽字体防止画字符串的时候字符间距随着长度变化的问题
		//Gdi+里相同字体使用同一种StringFormat在path和bitmap上面画出来的字符串长度不一样
		//在bitmap上面画字符串时会自动调整字符间距
		m_StringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
		m_StringFormat.SetLineAlignment(Gdiplus::StringAlignmentNear);
		m_hCursor = LoadCursor(nullptr, IDC_IBEAM);//设置鼠标进入后的样式
		m_Margin = 5;
		m_SelectTextPosFirst = 0;
		m_SelectTextPosSecond = 0;
	}
}// !KrUI