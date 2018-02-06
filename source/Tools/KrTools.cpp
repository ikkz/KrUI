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
}