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
		unsigned int m_MouseDownPos;
		Direction m_Direction = Direction::Horizontal;
		double m_Percentage = 0.0;
		unsigned int m_SliderLength = 10;
		Gdiplus::Color m_SliderColor;
	public:
		void SetPercentage(double percent);
		double GetPercentage() const;
		void SetMovableLength(unsigned int length);
		unsigned int GetMovableLength() const;
		KrScrollBar::Direction GetDirection() const;
		void SetDirection(Direction direction);

		virtual void Update() override;
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	};


}// namespace KrUI

#endif