#include "KrList.h"

namespace KrUI
{
	KrList::KrList()
	{
		m_Position = 0;
		m_TotalHeight = 0;
		m_MouseWheelDelta = 10;
		m_FontColor = Gdiplus::Color::Black;
		m_StringFormat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentNear);
		m_StringFormat.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	}

	LRESULT KrList::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case WM_MOUSEWHEEL:
			int x = m_pKrWindow->m_ptMouse.x, y = m_pKrWindow->m_ptMouse.y;
			// 			if (m_pKrWindow != nullptr)
			// 			{
			// 				RECT rect;
			// 				GetClientRect(m_pKrWindow->GetHWND(), &rect);
			// 				POINT pt{ rect.left,rect.top };
			// 				ClientToScreen(m_pKrWindow->GetHWND(), &pt);
			// 				x = GET_X_LPARAM(lParam) - pt.x, y = GET_Y_LPARAM(lParam) - pt.y;
			if (!(x >= GetX() && y >= GetY() && x <= (GetX() + GetWidth()) && y <= (GetY() + GetHeight())))break;
			if (static_cast<int>(wParam) > 0)
			{
				if (m_Position > 0) m_Position = (m_Position - m_MouseWheelDelta) >= 0 ? (m_Position - m_MouseWheelDelta) : 0;
			}
			else
			{
				if (m_TotalHeight - m_Position >= GetHeight())m_Position = (m_Position + GetHeight() + m_MouseWheelDelta) <= m_TotalHeight ? m_Position + m_MouseWheelDelta : m_TotalHeight - GetHeight();
			}
			break;
		}
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}

	int KrList::AddItem(std::wstring wStr, int nIndex /* = -1 */, unsigned int nHeight /* = 35*/)
	{
		if (nIndex == -1)
		{
			while (nIndex == -1)
			{
				nIndex = abs(rand());
				for (auto& li : m_ListItems)
				{
					if (li.m_Index == nIndex) nIndex = -1;
				}
			}
			m_ListItems.push_back(KrListItem(wStr, nIndex, nHeight));
			m_TotalHeight += nHeight;
			return nIndex;
		}

		for (auto& li : m_ListItems)
		{
			if (li.m_Index == nIndex)return -1;
		}
		m_ListItems.push_back(KrListItem(wStr, nIndex, nHeight));
		m_TotalHeight += nHeight;
		return nIndex;
	}

	void KrList::Update()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_BgColor), 0, 0, GetWidth(), GetHeight());

		//计算需要画哪些项：
		//m_Position = 0;
		int current_total = 0, start_item = -1, end_item = -1, start_position = 0, mouse_hover_item = -1;
		for (int i = 0; i < m_ListItems.size(); i++)
		{
			//确定开始项
			if (m_Position >= current_total && m_Position <= (current_total + m_ListItems[i].m_Height))
			{
				start_item = i;
				start_position = current_total - m_Position;
			}
			if (m_pKrWindow->m_ptMouse.x >= GetX() && m_pKrWindow->m_ptMouse.y >= GetY() &&
				m_pKrWindow->m_ptMouse.x <= (GetX() + GetWidth()) && m_pKrWindow->m_ptMouse.y <= (GetY() + GetHeight()) &&
				(m_pKrWindow->m_ptMouse.y - GetY()) >= (current_total - m_Position) &&
				(m_pKrWindow->m_ptMouse.y - GetY()) <= (current_total - m_Position + m_ListItems[i].m_Height))
				mouse_hover_item = i;
			//确定结束项
			int end_position = m_Position + GetHeight();
			if (end_position >= current_total && end_position <= (current_total + m_ListItems[i].m_Height))
			{
				end_item = i;
				break;//找到结束项直接退出循环
			}
			current_total += m_ListItems[i].m_Height;
		}
		if (end_item = -1)end_item = m_ListItems.size() - 1;
		for (int i = start_item; i <= end_item; i++)
		{
			if (mouse_hover_item == i)m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(196, 218, 242)), 0, start_position, GetWidth() - 25, m_ListItems[i].m_Height);
			m_pGraphics->DrawString(m_ListItems[i].m_ItemName.c_str(), -1, m_pFont, Gdiplus::RectF(10, start_position, GetWidth() - 25, m_ListItems[i].m_Height), &m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
			m_pGraphics->DrawRectangle(&Gdiplus::Pen(m_BorderColor), 0, start_position, GetWidth() - 25, m_ListItems[i].m_Height);
			m_pGraphics->DrawLine(&Gdiplus::Pen(m_BorderColor), Gdiplus::Point(GetWidth() - 25, 0), Gdiplus::Point(GetWidth() - 25, GetHeight()));
			start_position += m_ListItems[i].m_Height;
		}
		m_pGraphics->DrawRectangle(&Gdiplus::Pen(m_BorderColor), 0, 0, GetWidth() - 1, GetHeight() - 1);
		KrUIBase::Update();
	}
}