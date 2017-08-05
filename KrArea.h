#ifndef KRAREA_H
#define KRAREA_H
#pragma once
#include "KrUIManager.h"
#include "KrControl.h"
#include "KrWindow.h"
using namespace Gdiplus;
using namespace KrUI;
namespace KrUI
{
	class KrControl;
	class KrArea:public KrControl
	{
	private:
		list<KrControl*> m_CtrlList;
		Graphics* m_pGraphics;
		HDC    m_TempDC;
		HBITMAP m_hbmp;
	public:
		KrControl* AddControl(KrCtrlType CtrlType, LPCWSTR lpName, int x, int y, int width, int height);
		KrArea();
		void UpdateRect();
		void Show();
		void  HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		~KrArea();
		void Draw(Graphics* pGraphics);
	};








}//namespace KrUI

#endif //KRAREA_H
