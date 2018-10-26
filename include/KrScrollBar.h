#ifndef _YL_KRSCROLLBAR_H_
#define _YL_KRSCROLLBAR_H_

#include "KrUIBase.h"

namespace KrUI
{

	class KrScrollBar: public KrUIBase
	{
	private:
		unsigned int m_Length = 10;
		int m_MinValue = 0;
		int m_MaxValue = 0;
	public:
		void SetMinValue(int value);
		void SetMaxValue(int value);
		int GetMinValue() const;
		int GetMaxValue() const;
		void SetLength(unsigned int length);
		unsigned int GetLength() const;

		virtual void Update() override;
	};


}// namespace KrUI

#endif