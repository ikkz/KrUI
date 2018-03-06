#ifndef _KR_CHECKBOX_H_
#define _KR_CHECKBOX_H_
#pragma once

#include "KrList.h"
#define PROPORTION (0.5)

namespace KrUI
{
	class KrCheckBox :public KrList
	{
	public:
		KrCheckBox(Gdiplus::Color c);
		virtual void DrawItem(unsigned int item_index, int start_position);
		virtual void ItemChange();
	};


}//! namespace KrUI




#endif

