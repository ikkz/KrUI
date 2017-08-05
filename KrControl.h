#ifndef KRCONTROL_H
#define KRCONTROL_H
#pragma once
#include "KrWindow.h"
#include "KrUIManager.h"
#include<windowsx.h>
#include <gdiplus.h>
#include <map>
using namespace std;
using namespace Gdiplus;

namespace KrUI{


	class KrWindow;
	typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);
	enum KrCtrlType;
	//不可直接使用此类！！！请使用其派生类！！！
	class KrControl
	{
	protected:
		UINT      m_type;
		KrWindow* m_pKrWindow;
		LPCWSTR m_lpCtrlName;
		RECT m_rect;
		bool m_bVisible;
		bool m_bMouseIn;
		map<UINT, MSGFUNC> m_MsgFuncMap;
	public:
		KrControl();
		void SetCtrlType(KrCtrlType type);
		UINT    GetCtrlType();
		void    SetWindow(KrWindow* pKrWindow);//
		KrWindow* GetWindow();
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
		bool  IsVisible();
		virtual void  Show();
		void  Hide();
		virtual void  HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		void  CallMsgFunc(UINT Message, WPARAM wParam, LPARAM lParam);
		virtual void  UpdateRect();
		virtual void Draw(Graphics* pGraphics);
	};


}//namespace KrUI

#endif// !KRCONTROL_H
