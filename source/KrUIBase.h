#ifndef KRUIBASE_H
#define KRUIBASE_H

#pragma once

#include <windows.h>
namespace KrUI
{
	class KrWindow;
	enum KrUIType{KrWindow_t,KrButton_t};
	class KrUIBase
	{
	protected:
		LPCWSTR m_Name;
		RECT m_rect;
		bool m_bVisible;
		HDC m_hDc;
		KrUIType m_UIType;
		KrWindow* m_pKrWindow;
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
		virtual void SetSize(UINT x, UINT y, UINT width, UINT height);
		virtual void Show();
		virtual void Hide();
		virtual bool IsVisible();
		virtual void SetDc(HDC hdc);
		virtual HDC GetDc();
		virtual void UpdateDc()=0;
		void SetName(LPCWSTR name);
		LPCWSTR GetName();
	};

}//!KrUI

#endif

