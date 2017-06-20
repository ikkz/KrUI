#ifndef _KRUIMANAGER_H
#define _KRUIMANAGER_H




#define KM_BEFORE_MOUSEENTER WM_APP+1
#define KM_MOUSEENTER WM_APP+2
#define KM_AFTER_MOUSEENTER WM_APP+3

#define KM_BEFORE_MOUSELEAVE WM_APP+4
#define KM_MOUSELEAVE WM_APP+5
#define KM_AFTER_MOUSELEAVE WM_APP+6

#define KM_BEFORE_LBTNDOWN WM_APP+7
#define KM_LBTNDOWN WM_LBUTTONDOWN
#define KM_AFTER_LBTNDOWN WM_APP+8

#define KM_BEFORE_LBTNUP WM_APP+9
#define KM_LBTNUP WM_LBUTTONDOWN
#define KM_AFTER_LBTNUP WM_APP+10


// #define WM_MOUSEFIRST                   0x0200
// #define WM_MOUSEMOVE                    0x0200
// #define WM_LBUTTONDOWN                  0x0201
// #define WM_LBUTTONUP                    0x0202
// #define WM_LBUTTONDBLCLK                0x0203
// #define WM_RBUTTONDOWN                  0x0204
// #define WM_RBUTTONUP                    0x0205
// #define WM_RBUTTONDBLCLK                0x0206
// #define WM_MBUTTONDOWN                  0x0207
// #define WM_MBUTTONUP                    0x0208
// #define WM_MBUTTONDBLCLK                0x0209

//控件类型
#define KR_CTRL 1
#define KR_LABEL 2
#define KR_BUTTON 3


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
