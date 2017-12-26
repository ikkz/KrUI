#ifndef KRBUTTON_H
#define  KRBUTTON_H
#pragma once
#include "KrUIBase.h"
#include "KrMessageHandler.h"
namespace KrUI
{
	class KrWindow;
	class KrButton :public KrUIBase
	{
	public:
		KrButton(KrWindow* pKrWindow);
		~KrButton();
		void SetMouseHoverColor(COLORREF color);
		void SetMouseDownColor(COLORREF color);
		void SetMouseLeaveColor(COLORREF color);
		void SetBorderColor(COLORREF color);
		COLORREF GetMouseHoverColor();
		COLORREF GetMouseDownColor();
		COLORREF GetMouseLeaveColor();
		COLORREF GetBorderColor();
		void UpdateDc();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	protected:
		COLORREF m_MouseHoverColor;
		COLORREF m_MouseDownColor;
		COLORREF m_MouseLeaveColor;
		COLORREF m_BorderColor;
	};


}//!KrUI

#endif

