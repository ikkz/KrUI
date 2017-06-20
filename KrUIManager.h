#ifndef _KRUIMANAGER_H
#define _KRUIMANAGER_H

#define KM_MOUSEENTER WM_APP+1
#define KM_MOUSELEAVE WM_APP+2

//控件类型
#define KR_CTRL 0




#include<list>
#include<windows.h>
#include"KrWindow.h"


using namespace std;
namespace KrUI{

	class KrWindow;
	typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);

	class KrUIManager
	{
	public:
		static KrUIManager* GetpKrUIManager();
		bool      Initialize(HINSTANCE hInstance);//
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);// 
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height);//
		LPCTSTR   GetWindowClassName();//
		HINSTANCE GetHINSTANCE();//
		int       MessageLoop();//
		LRESULT   HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);//处理消息
		int		  GetWindowNum();
		void	  DeleteWindow(KrWindow* pKrWindow);
		~KrUIManager();
	private:
		KrUIManager(){ m_lpWindowClassName = L"KrUI"; }
		static KrUIManager* m_pKrUIManager;
		WNDCLASSEX      m_wc; //
		LPCWSTR         m_lpWindowClassName;//
		HINSTANCE       m_hInstance;//
		MSG				m_msg;
		list<KrWindow*>  m_WndList;//
	};

}


#endif
