#pragma once
#ifndef _KR_EDIT_H_
#define _KR_EDIT_H_
#include "../KrCore.h"
#include <string>
#include <windows.h>
#include <codecvt>
namespace KrUI
{

	Gdiplus::SizeF GetTextSize(std::wstring strText, Gdiplus::Font* pFont, Gdiplus::Rect rect);
	bool WCharStringToUTF8String(const std::wstring &wstr, std::string &u8str);
	bool UTF8StringToWCharString(const std::string &u8str, std::wstring &wstr);
	std::wstring StringToWideString(std::string src);
	std::string WideStringToString(std::wstring src);

}// namespace KrUI

#endif