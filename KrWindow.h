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
		HDC    m_hDC;
		COLORREF m_DefaultColor;
		UINT    m_BorderWidth;
		HPEN   m_hPen;
	public:
		KrWindow();
		LPCWSTR  KrGetWindowName();//
		void    KrSetWindowName(LPCWSTR lpWindowName);//
		HWND    KrGetHWND();//
		RECT*   KrGetRect();//
		void    KrSetRect(RECT* pRect); //
		void    KrSetStyle(DWORD dwStyle);//
		DWORD	KrGetStyle();//
		bool    KrCreate();//
		void    KrDestroy(bool bDelete);//
		int     KrGetX();//
		int     KrGetY();//
		int     KrGetWidth();//
		int     KrGetHeight();//
		void    KrSetX(int x);//
		void    KrSetY(int y);//
		void    KrSetWidth(int width);//
		void    KrSetHeight(int height);//
		void    KrShow();//
		void    KrHide();//
		bool    KrIsVisible();//
		bool	KrIsCreated();//
		LRESULT KrHandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		void    KrRegMsg(UINT msg, MSGFUNC func);
		KrControl* KrAddControl(UINT iCtrlType, LPCWSTR lpName, int x, int y, int width, int height);

		HDC      KrGetDC();
		void    KrReDraw(RECT* pRect);
		void	KrSetDefaultColor(COLORREF color);
		void	KrSetBorderWidth(UINT BorderWidth);
		void	KrSelectPen(HPEN hPen);

		~KrWindow();
	};

}//namespace KrUI

#endif
