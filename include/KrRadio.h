#ifndef _KR_RADIO_H_
#define _KR_RADIO_H_

#include "KrList.h"
#define PROPORTION (0.5)

namespace KrUI
{
	class KrRadio :public KrList
	{
	public:
		KrRadio(Gdiplus::Color c);
		virtual void DrawItem(unsigned int item_index, int start_position);
		virtual void ItemChange();
	};


}//! namespace KrUI




#endif

