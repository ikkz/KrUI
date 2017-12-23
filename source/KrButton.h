#ifndef KRBUTTON_H
#define  KRBUTTON_H
#pragma once
#include "KrUIBase.h"
#include "KrMessageHandler.h"
namespace KrUI
{
	class KrWindow;
	class KrButton :public KrUIBase,public KrMessageHandler
	{
	public:
		KrButton(KrWindow* pKrWindow);
		void SetMouseHoverColor(COLORREF color);
		void SetMouseDownColor(COLORREF color);
		void SetMouseLeaveColor(COLORREF color);
		void SetBorderColor(COLORREF color);
		COLORREF GetMouseHoverColor();
		COLORREF GetMouseDownColor();
		COLORREF GetMouseLeaveColor();
		COLORREF GetBorderColor();
		void UpdateDc();
	protected:
		COLORREF m_MouseHoverColor;
		COLORREF m_MouseDownColor;
		COLORREF m_MouseLeaveColor;
		COLORREF m_BorderColor;
	};


}//!KrUI

#endif

