#include "KrRadio.h"

namespace KrUI
{
	KrRadio::KrRadio(Gdiplus::Color c)
	{
		m_BgColor = c;
		m_BorderColor = c;
		m_ScrollBarRect.Width = 0;
	}
	void KrRadio::DrawItem(unsigned int item_index, int start_position)
	{
		if (m_pGraphics != nullptr)m_pGraphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
		int item_height = m_ListItems[item_index].m_Height;
		m_pGraphics->DrawEllipse(&Gdiplus::Pen(&Gdiplus::SolidBrush(Gdiplus::Color::Blue)),
			Gdiplus::Rect(static_cast<int>((1 - PROPORTION)*item_height / 2), static_cast<int>(start_position + (1 - PROPORTION)*item_height / 2), static_cast<int>(PROPORTION*item_height), static_cast<int>(PROPORTION*item_height)));
		//如果这一项处于选中状态时
		for (auto si : m_SelectedItems)
		{
			if (si == item_index)
			{
				m_pGraphics->FillEllipse(&Gdiplus::SolidBrush(Gdiplus::Color(0, 120, 215)),
					Gdiplus::RectF(static_cast<Gdiplus::REAL>((1 - (PROPORTION - 0.25))*item_height / 2 - 1), static_cast<Gdiplus::REAL>(start_position + (1 - (PROPORTION - 0.25))*item_height / 2 - 1), static_cast<Gdiplus::REAL>((PROPORTION - 0.25)*item_height), static_cast<Gdiplus::REAL>((PROPORTION - 0.25)*item_height)));
				break;
			}
		}
		//画文字内容
		m_pGraphics->DrawString(m_ListItems[item_index].m_ItemName.c_str(), -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(m_ListItems[item_index].m_Height),
			static_cast<Gdiplus::REAL>(start_position), static_cast<Gdiplus::REAL>(GetWidth() - m_ScrollBarRect.Width), static_cast<Gdiplus::REAL>(m_ListItems[item_index].m_Height)),
			&m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
		if (m_pGraphics != nullptr)m_pGraphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeDefault);
		//画边框
		//m_pGraphics->DrawRectangle(&Gdiplus::Pen(m_BorderColor), 0, start_position, GetWidth() - m_ScrollBarRect.Width, m_ListItems[item_index].m_Height);
	}
	void KrRadio::ItemChange()
	{
		SetHeight(m_TotalHeight);
		KrList::ItemChange();
	}
}