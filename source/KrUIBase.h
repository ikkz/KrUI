#ifndef KRUIBASE_H
#define KRUIBASE_H

#pragma once

#include <windows.h>
namespace KrUI
{
	class KrUIBase
	{
	protected:
		RECT m_rect;
		bool m_bVisible;
	public:
		virtual RECT* GetRect();
		virtual void SetRect(RECT* pRect);
		virtual int GetX();
		virtual int GetY();
		virtual int GetWidth();
		virtual int GetHeight();
		virtual void SetX(UINT x);
		virtual void SetY(UINT y);
		virtual void SetXY(UINT x, UINT y);
		virtual void SetWidth(UINT width);
		virtual void SetHeight(UINT height);
		virtual void Show();
		virtual void Hide();
		virtual bool IsVisible();
	};

}//!KrUI

#endif

