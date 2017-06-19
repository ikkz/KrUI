#ifndef _KRCONTROL_H
#define _KRCONTROL_H


#include"KrWindow.h"

namespace KrUI{

	class KrControl
	{
	private:
		RECT m_rect;
	public:
		RECT*   GetRect();//
		void    SetRect(RECT* pRect); //
		int     GetX();//
		int     GetY();//
		int     GetWidth();//
		int     GetHeight();//
		void    SetX(int x);//
		void    SetY(int y);//
		void    SetWidth(int width);//
		void    SetHeight(int height);//
		void    Update();
	};


}
#endif
