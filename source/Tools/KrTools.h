#pragma once
#ifndef _KR_EDIT_H_
#define _KR_EDIT_H_
#include "../KrCore.h"
namespace KrUI
{

	Gdiplus::SizeF GetTextSize(std::wstring strText, Gdiplus::Font* pFont, Gdiplus::Rect rect);


}// namespace KrUI

#endif