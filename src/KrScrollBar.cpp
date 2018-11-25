#include "KrCore.h"
#include "KrScrollBar.h"
#include <iostream>

namespace KrUI
{

	void KrScrollBar::SetPercentage(double percent)
	{
		if (percent < 0.0)percent = 0;
		if (percent > 1.0) percent = 1;
		m_Percentage = percent;
		KRLOG << percent;
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
				if (m_Direction == Horizontal)
				{
					m_MouseDownPos = GET_X_LPARAM(lParam) - GetX();
					if (m_MouseDownPos > (GetWidth() - m_SliderLength) * m_Percentage && m_MouseDownPos < (GetWidth() - m_SliderLength) * m_Percentage + m_SliderLength)
						m_MouseCaptured = true;
				}
				else
				{
					m_MouseDownPos = GET_Y_LPARAM(lParam) - GetY();
					if (m_MouseDownPos > (GetHeight() - m_SliderLength) * m_Percentage && m_MouseDownPos < (GetHeight() - m_SliderLength) * m_Percentage + m_SliderLength)
						m_MouseCaptured = true;
				}
				if (m_MouseCaptured)KRLOG << "mouse captured.pos:" << m_MouseDownPos;
			}
			break;
		case WM_LBUTTONUP:
			m_MouseCaptured = false;
		case WM_MOUSEMOVE:
			if (m_MouseCaptured)
			{
				//KRLOG << "mouse move.";
				if (m_Direction == Horizontal)
				{
					SetPercentage((m_Percentage * (GetWidth() - m_SliderLength) + GET_X_LPARAM(lParam) - GetX() + m_MouseDownPos) / (GetWidth() - m_SliderLength));
				}
				else
				{
					SetPercentage((m_Percentage*(GetHeight() - m_SliderLength) + GET_Y_LPARAM(lParam) - GetY() + m_MouseDownPos) / (GetHeight() - m_SliderLength));
				}
			}
			break;
		default:
			break;
		}
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}
}// namespace KrUI
