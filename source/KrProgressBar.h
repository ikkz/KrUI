#ifndef _KR_PROGRESSBAR_H
#define _KR_PROGRESSBAR_H
#pragma once
#include "KrUIBase.h"


namespace KrUI
{

	class KrProgressBar :public KrUIBase
	{
	protected:
		double m_Percentage;
	public:
		KrProgressBar();
	};

}// !namespace KrUI


#endif

