#ifndef KRUIBASE_H
#define KRUIBASE_H

#pragma once
#include "KrMessageHandler.h"
#include "KrDefine.h"
#include <windows.h>
#include <gdiplus.h>
//using namespace Gdiplus;
namespace KrUI
{
	class KrWindow;
	enum KrUIType{KrWindow_t,KrButton_t,KrCloseButton_t,KrLabel_t,KrEdit_t};
	enum Button_Status { mouse_down, mouse_leave, mouse_hover };
	class KrUIBase :public KrMessageHandler
	{
	protected:
		LPCWSTR m_Name;
		RECT m_rect;
		bool m_bVisible;
		Gdiplus::Bitmap* m_pBmp;
		Gdiplus::Graphics* m_pGraphics;
		KrUIType m_UIType;
		KrWindow* m_pKrWindow;
		HBITMAP m_hBmp;
		Gdiplus::StringFormat m_StringFormat;
		Gdiplus::Font* m_pFont;
		Gdiplus::Color m_FontColor;
		Gdiplus::Color m_BorderColor;
		Gdiplus::Color m_BgColor;
		bool m_bMouseIn;
		bool m_bMouseDown;
	public:
		KrUIBase();
		~KrUIBase();
		void SetType(KrUIType ut);
		KrUIType GetType();
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
		virtual void SetParantWindow(KrWindow* pKrWindow);
		KrWindow* GetParantWindow();
		void SetFontColor(Gdiplus::Color color);
		Gdiplus::Color GetFontColor();
		Gdiplus::Color GetBgColor();
		void SetBgColor(Gdiplus::Color c);
		virtual void UpdateDc()=0;
		virtual void ChangeBmpSize();
		Gdiplus::Graphics* GetBmpGraphics();
		virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
		void SetName(LPCWSTR name);
		LPCWSTR GetName();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		void SetFont(const WCHAR* fontfamily,Gdiplus::REAL emSize);
	};

}//!KrUI

#endif

