#ifndef KRAREA_H
#define KRAREA_H
#include "KrControl.h"
using namespace Gdiplus;

namespace KrUI
{
	class KrArea:public KrControl
	{
	private:
		list<KrControl*> m_CtrlList;
		Graphics* m_pGraphics;
		HDC    m_TempDC;
		HBITMAP m_hbmp;
	public:
		KrControl* AddControl(UINT iCtrlType, LPCWSTR lpName, int x, int y, int width, int height);
		KrArea();
		void UpdateRect();
		void Show();
		void  HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		~KrArea();
	};








}//namespace KrUI

#endif //KRAREA_H
