/*********************************************************
Author:MilesYang
Mail:1961464399@qq.com
CurrentTime:2018-4-13
FileName:KrLabel.h
*********************************************************/

#ifndef _KR_LABEL_H
#define _KR_LABEL_H
#pragma once

#include "KrButton.h"

namespace KrUI
{
	class KrLabel :public KrButton
	{
	public:
		KrLabel(Gdiplus::Color bgcolor);
	};
}// !namespace KrUI

#endif // !KRLABEL_H



