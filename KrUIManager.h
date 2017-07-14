/************************************************************************/
/*                                                                      */
/************************************************************************/





#ifndef KRUIMANAGER_H
#define KRUIMANAGER_H



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
#include <gdiplus.h>

using namespace std;
using namespace Gdiplus;
#pragma comment(lib,"Gdiplus.lib")


namespace KrUI{



	class KrWindow;
	typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);

	class KrUIManager
	{
	public:
		static KrUIManager* GetpKrUIManager();
			//获取唯一uimanager
		bool      Initialize(HINSTANCE hInstance);
			//初始化，hInstance:应用程序实例句柄
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);
			// 添加窗口，dwStyle:窗口风格
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height);
			//添加窗口
		LPCTSTR   GetWindowClassName();
			//获取窗口类名
		HINSTANCE GetHINSTANCE();
			//获取应用程序实例句柄
		int       MessageLoop();
			//进入消息循环
		LRESULT   HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			//处理消息
		int		  GetWindowNum();
			//获取窗口个数
		void	  DeleteWindow(KrWindow* pKrWindow);
			//删除窗口
		void	  ReDraw();
			//重绘
		~KrUIManager();
			//析构
	private:
		KrUIManager(){ m_lpWindowClassName = L"KrUI"; }
		static KrUIManager* m_pKrUIManager;
		WNDCLASSEX      m_wc; //
		LPCWSTR         m_lpWindowClassName;//
		HINSTANCE       m_hInstance;//
		MSG				m_msg;
		list<KrWindow*>  m_WndList;//
	};



}//namespace KrUI

#endif// !KRUIMANAGER_H
