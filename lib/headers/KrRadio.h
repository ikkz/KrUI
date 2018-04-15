/*********************************************************
Author:MilesYang
Mail:1961464399@qq.com
CurrentTime:2018-4-13
FileName:KrRadio.h
*********************************************************/

#ifndef _KR_RADIO_H_
#define _KR_RADIO_H_
#pragma once

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

