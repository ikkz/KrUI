#ifndef _KRWINDOW_H
#define _KRWINDOW_H



#include<windows.h>

namespace KrUI{

	class KrWindow
	{
	private:
		LPCWSTR  m_lpWindowName;//
		HWND    m_hwnd;//
		RECT    m_rect;// 
		DWORD   m_dwStyle;//
		bool    m_bVisible;
		bool	m_bDefultWindow;
	public:
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

	};

}

#endif
