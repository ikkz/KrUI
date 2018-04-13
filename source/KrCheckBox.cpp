/*********************************************************
Author:MilesYang
Mail:1961464399@qq.com
CurrentTime:2018-4-13
FileName:KrCheckBox.cpp
*********************************************************/

#include "KrCheckBox.h"

namespace KrUI
{
	KrCheckBox::KrCheckBox(Gdiplus::Color c)
	{
		m_BgColor = c;
		m_BorderColor = c;
		m_ScrollBarRect.Width = 0;
		m_bMultiSelectable = true;
	}
	void KrCheckBox::DrawItem(unsigned int item_index, int start_position)
	{
		if (m_pGraphics != nullptr)m_pGraphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
		int item_height = m_ListItems[item_index].m_Height;
		m_pGraphics->DrawRectangle(&Gdiplus::Pen(&Gdiplus::SolidBrush(Gdiplus::Color::Blue)),
			Gdiplus::Rect(static_cast<int>((1 - PROPORTION)*item_height / 2), static_cast<int>(start_position + (1 - PROPORTION)*item_height / 2), static_cast<int>(PROPORTION*item_height), static_cast<int>(PROPORTION*item_height)));
		//如果这一项处于选中状态时
		if (m_ListItems[item_index].m_bSelected)
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(0, 120, 215)),
				Gdiplus::RectF(static_cast<Gdiplus::REAL>((1 - (PROPORTION - 0.2))*item_height / 2 - 1), static_cast<Gdiplus::REAL>(start_position + (1 - (PROPORTION - 0.2))*item_height / 2 - 1), static_cast<Gdiplus::REAL>((PROPORTION - 0.2)*item_height), static_cast<Gdiplus::REAL>((PROPORTION - 0.2)*item_height)));

		//画文字内容
		m_pGraphics->DrawString(m_ListItems[item_index].m_ItemName.c_str(), -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(m_ListItems[item_index].m_Height),
			static_cast<Gdiplus::REAL>(start_position), static_cast<Gdiplus::REAL>(GetWidth() - m_ScrollBarRect.Width), static_cast<Gdiplus::REAL>(m_ListItems[item_index].m_Height)),
			&m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
		if (m_pGraphics != nullptr)m_pGraphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeDefault);
		//画边框
		//m_pGraphics->DrawRectangle(&Gdiplus::Pen(m_BorderColor), 0, start_position, GetWidth() - m_ScrollBarRect.Width, m_ListItems[item_index].m_Height);
	}
	void KrCheckBox::ItemChange()
	{
		SetHeight(m_TotalHeight);
		KrList::ItemChange();
	}
}