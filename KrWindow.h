#ifndef KRWINDOW_H
#define KRWINDOW_H
#pragma once

#include <list>
#include <map>
#include<windows.h>
#include "KrControl.h"
#include "KrUIManager.h"
#include "KrArea.h"
#include <gdiplus.h>

using namespace std;
using namespace Gdiplus;
using namespace KrUI;
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

		HDC    m_DC;
		HDC    m_TempDC;
		HBITMAP m_hbmp;
		Graphics* m_pGraphics;

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
		void	Destroy();//
		int     GetX();//
		int     GetY();//
		int     GetWidth();//
		int     GetHeight();//
		void    SetX(UINT x);//
		void    SetY(UINT y);//
		void	SetXY(UINT x, UINT y);//
		void    SetWidth(UINT width);//
		void    SetHeight(UINT height);//
		void    Show();//
		void    Hide();//
		bool    IsVisible();//
		bool	IsCreated();//
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		void    RegMsg(UINT msg, MSGFUNC func);
		KrControl* AddControl(KrCtrlType CtrlType, LPCWSTR lpName, int x, int y, int width, int height);

		void    ReDraw(RECT* pRect);

		HDC		GetTempDC();
	};



}//namespace KrUI

#endif// !KRWINDOW_H
