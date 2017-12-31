#ifndef KRUIBASE_H
#define KRUIBASE_H

#pragma once
#include "KrMessageHandler.h"
#include "KrDefine.h"
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
namespace KrUI
{
	class KrWindow;
	enum KrUIType{KrWindow_t,KrButton_t,KrCloseButton_t,KrLabel_t};
	class KrUIBase :public KrMessageHandler
	{
	protected:
		LPCWSTR m_Name;
		RECT m_rect;
		bool m_bVisible;
		Gdiplus::Bitmap* m_pBmp;
		Graphics* m_pGraphics;
		KrUIType m_UIType;
		KrWindow* m_pKrWindow;
		HBITMAP m_hBmp;
		StringFormat m_StringFormat;
		Font* m_pFont;
		Color m_FontColor;
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
		void SetFontColor(Color color);
		Color GetFontColor();
		virtual void UpdateDc()=0;
		virtual void ChangeBmpSize();
		Graphics* GetBmpGraphics();
		virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
		void SetName(LPCWSTR name);
		LPCWSTR GetName();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	};

}//!KrUI

#endif

