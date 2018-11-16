#ifndef _YL_KRSCROLLBAR_H_
#define _YL_KRSCROLLBAR_H_

#include "KrUIBase.h"

namespace KrUI
{

	class KrScrollBar: public KrUIBase
	{
	public:
		enum Direction
		{
			Horizontal, Vertical
		};
	private:
		unsigned int m_Length = 10;
		int m_MinValue = 0;
		int m_MaxValue = 0;
		int m_Value = 0;
		unsigned int m_MouseDownPos;
		Direction m_Direction = Direction::Horizontal;
	public:
		bool SetMinValue(int value);
		bool SetMaxValue(int value);
		bool SetValue(int value);
		int GetMinValue() const;
		int GetMaxValue() const;
		int GetValue() const;
		void SetLength(unsigned int length);
		unsigned int GetLength() const;
		KrScrollBar::Direction GetDirection() const;
		void SetDirection(Direction direction);

		virtual void Update() override;
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	};


}// namespace KrUI

#endif