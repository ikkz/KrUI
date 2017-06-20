#ifndef _KRCONTROL_H
#define _KRCONTROL_H


#include"KrWindow.h"

namespace KrUI{

	enum KrCtrlType{kr_ctrl};


	class KrControl
	{
	private:
		LPCWSTR m_lpCtrlName;
		RECT m_rect;
		bool m_bVisible;
		map<UINT, MSGFUNC> m_MsgFuncMap;
	public:
		void	SetName(LPCWSTR lpCtrlName);//
		LPCWSTR GetName();//
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
		void    RegMsg(UINT msg, MSGFUNC func);
		void  virtual  Draw();
		bool  IsVisible();
		void  Show();
		void  Hide();
	};


}
#endif
