#include "KrTools.h"

namespace KrUI
{
	Gdiplus::SizeF GetTextSize(std::wstring strText, Gdiplus::Font* pFont, Gdiplus::Rect rect)
	{
		Gdiplus::GraphicsPath path;
		Gdiplus::FontFamily fontfamily;
		pFont->GetFamily(&fontfamily);
		path.AddString(strText.c_str(), -1, &fontfamily, pFont->GetStyle(), pFont->GetSize(), rect,
			Gdiplus::StringFormat::GenericTypographic()/*&m_StringFormat*/);
		Gdiplus::RectF bounds;
		path.GetBounds(&bounds);
		return Gdiplus::SizeF(bounds.Width, bounds.Height);
	}


	bool WCharStringToUTF8String(const std::wstring &wstr, std::string &u8str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		u8str = conv.to_bytes(wstr);
		return true;
	}

	bool UTF8StringToWCharString(const std::string &u8str, std::wstring &wstr)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
		wstr = conv.from_bytes(u8str);
		return true;
	}

	std::string WideStringToString(std::wstring wStr)
	{
		if (wStr.size() == 0)
		{
			return "";
		}

		char *pszBuf = NULL;
		int needBytes = WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), -1, NULL, 0, NULL, NULL);
		if (needBytes > 0)
		{
			pszBuf = new char[needBytes + 1];
			ZeroMemory(pszBuf, (needBytes + 1) * sizeof(char));
			WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), -1, pszBuf, needBytes, NULL, NULL);
		}
		std::string str = pszBuf;
		delete[] pszBuf;
		return str;
	}

	std::wstring StringToWideString(std::string str)
	{
		if (str.size() == 0)
		{
			return L"";
		}

		wchar_t *pszBuf = NULL;
		int needWChar = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		if (needWChar > 0)
		{
			pszBuf = new wchar_t[needWChar + 1];
			ZeroMemory(pszBuf, (needWChar + 1) * sizeof(wchar_t));
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pszBuf, needWChar);
		}
		std::wstring wStr = pszBuf;
		delete[] pszBuf;
		return wStr;
	}
}