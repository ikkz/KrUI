#ifndef _KRUIMANAGER_H
#define _KRUIMANAGER_H


#include<list.h>
#include<windows.h>
#include"KrWindow.h"


class KrUIManager
{
	public:
		static KrUIManager* GetpKrUIManager();
		bool      Initialize(HINSTANCE hInstance);//
		KrWindow* AddWindow(LPCSTR lpWindowName,int x,int y,int width,int height,DWORD dwStyle);// 
		KrWindow* AddWindow(LPCSTR lpWindowName,int x,int y,int width,int height);//
		LPCTSTR   GetWindowClassName();//
		HINSTANCE GetHINSTANCE();//
		int       MessageLoop();//
		LRESULT   HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);//处理消息
	private:
		KrUIManager(){m_lpWindowClassName="KrUI";}
		static KrUIManager* m_pKrUIManager;
		WNDCLASSEX      m_wc; //
		LPCSTR         m_lpWindowClassName;//
		HINSTANCE       m_hInstance;//
		list<KrWindow*> m_WndList;//
	
		
}

#endif
