#ifndef _KRWINDOW_H
#define _KRWINDOW_H

#include <list>
#include <map>
#include<windows.h>
#include "KrControl.h"
#include "KrUIManager.h"

using namespace std;

namespace KrUI{

	class KrControl;
	class KrWindow
	{
	private:
		LPCWSTR  m_lpWindowName;//
		HWND    m_hwnd;//
		RECT    m_rect;// 
		DWORD   m_dwStyle;//
		bool    m_bVisible;//
		POINT  m_ptMouse;
		POINT  m_ptMouseDown;
		bool   m_bMouseDown;
		map<UINT, MSGFUNC> m_MsgFuncMap;//
		list<KrControl*> m_CtrlList;
	public:
		KrWindow();
		LPCWSTR  GetWindowName();//
		void    SetWindowName(LPCWSTR lpWindowName);//
		HWND    GetHWND();//
		RECT*   GetRect();//
		void    SetRect(RECT* pRect); //
		void    SetStyle(DWORD dwStyle);//
		DWORD	GetStyle();//
		bool    Create();//
		void    Destroy(bool bDelete);//
		int     GetX();//
		int     GetY();//
		int     GetWidth();//
		int     GetHeight();//
		void    SetX(int x);//
		void    SetY(int y);//
		void    SetWidth(int width);//
		void    SetHeight(int height);//
		void    Show();//
		void    Hide();//
		bool    IsVisible();//
		bool	IsCreated();//
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		void    RegMsg(UINT msg, MSGFUNC func);
		KrControl* AddControl(UINT iCtrlType, LPCWSTR lpName, int x, int y, int width, int height);

		void    ReDraw(RECT* pRect);
		~KrWindow();
	};

}//namespace KrUI

#endif
