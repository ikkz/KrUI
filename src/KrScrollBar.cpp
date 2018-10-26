#include "KrScrollBar.h"

namespace KrUI
{
	bool KrScrollBar::SetMinValue(int value)
	{
		if (value < m_MaxValue)
		{
			m_MinValue = value;
			this->Update();
			return true;
		}
		else
		{
			return false;
		}
	}

	bool KrScrollBar::SetMaxValue(int value)
	{
		if (value > m_MinValue)
		{
			m_MaxValue = value;
			this->Update();
			return true;
		}
		else
		{
			return false;
		}
	}

	bool KrScrollBar::SetValue(int value)
	{
		if (value >= m_MinValue && value <= m_MaxValue)
		{
			m_Value = value;
			this->Update();
		}
		else
			return false;
	}

	int KrScrollBar::GetMinValue() const
	{
		return m_MinValue;
	}

	int KrScrollBar::GetMaxValue() const
	{
		return m_MaxValue;
	}

	int KrScrollBar::GetValue() const
	{
		return m_Value;
	}

	void KrScrollBar::SetLength(unsigned int length)
	{
		if (length > 0 && length != m_Length)
		{
			m_Length = length;
			this->Update();
		}
	}

	unsigned int KrScrollBar::GetLength() const
	{
		return m_Length;
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

		KrUIBase::Update();
	}

	LRESULT KrScrollBar::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case KM_LBTNDOWN:

		default:
			break;
		}
		return KrUIBase::HandleMessage(Message, wParam, lParam);
	}
}// namespace KrUI
