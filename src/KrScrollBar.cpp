#include "KrScrollBar.h"
#include <iostream>

namespace KrUI
{

	void KrScrollBar::SetPercentage(double percent)
	{
		if (percent < 0.0)percent = 0;
		if (percent > 1.0) percent = 1;
		m_Percentage = percent;
		this->Update();
	}

	double KrScrollBar::GetPercentage() const
	{
		return m_Percentage;
	}

	void KrScrollBar::SetMovableLength(unsigned int length)
	{
		length = length > (m_Direction == Horizontal ? GetWidth() : GetHeight()) ? (m_Direction == Horizontal ? GetWidth() : GetHeight()) : length;
		m_SliderLength = length;
		this->Update();
	}

	unsigned int KrScrollBar::GetMovableLength() const
	{
		return m_SliderLength;
	}

	KrScrollBar::Direction KrScrollBar::GetDirection() const
	{
		return m_Direction;
	}

	void KrScrollBar::SetDirection(Direction direction)
	{
		m_Direction = direction;
		m_MouseDownPos = 0;
		this->Update();
	}

	void KrScrollBar::Update()
	{
		m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_BgColor), 0, 0, GetWidth(), GetHeight());
		switch (m_Direction)
		{
		case KrUI::KrScrollBar::Horizontal:
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_SliderColor), static_cast<INT>((GetWidth() - m_SliderLength) * m_Percentage), 0, m_SliderLength, GetHeight());
			break;
		case KrUI::KrScrollBar::Vertical:
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_SliderColor), 0, static_cast<INT>((GetHeight() - m_SliderLength) * m_Percentage), GetWidth(), m_SliderLength);
			break;
		default:
			break;
		}
		KrUIBase::Update();
	}

	LRESULT KrScrollBar::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case WM_LBUTTONDOWN:
			if (m_bMouseIn)
			{
				m_MouseDownPos = m_Direction == Horizontal ? GET_X_LPARAM(lParam) : GET_Y_LPARAM(lParam);
				std::cout << "mouse down.\n";
			}
			break;
		case WM_MOUSEMOVE:
			if (m_bMouseDown)
			{
				std::cout << "mouse move.\n";
				if (m_Direction == Horizontal)
				{
					SetPercentage(GetPercentage() + (GET_X_LPARAM(lParam) - static_cast<int>(m_MouseDownPos)) / static_cast<double>(GetWidth() - m_SliderLength));
				}
				else
				{
					SetPercentage(GetPercentage() + (GET_Y_LPARAM(lParam) - static_cast<int>(m_MouseDownPos)) / static_cast<double>(GetHeight() - m_SliderLength));
				}
			}
			break;
		default:
			break;
		}
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}
}// namespace KrUI
