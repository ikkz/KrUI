#ifndef KRCORE_H
#define KRCORE_H
#pragma once

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

//Í·ÎÄ¼þ
#include<list>
#include <map>
#include<windows.h>
#include<windowsx.h>
#include <gdiplus.h>
using namespace std;
using namespace Gdiplus;
#pragma comment(lib,"Gdiplus.lib")


namespace KrUI {

	enum KrCtrlType
	{
		Area,
		Control,
		Label,
		Button
	};
	typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);
	class KrWindow;

	/************************************************************************/
	/* KrUIManager                                                          */
	/************************************************************************/

	class KrUIManager
	{
	public:
		static KrUIManager* GetpKrUIManager();
		bool      Initialize(HINSTANCE hInstance);
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height);
		LPCTSTR   GetWindowClassName();
		HINSTANCE GetHINSTANCE();
		int       MessageLoop();
		LRESULT   HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		int		  GetWindowNum();
		void	  DeleteWindow(KrWindow* pKrWindow);
		void	  ReDraw();
		~KrUIManager();
	private:
		KrUIManager() { m_lpWindowClassName = L"KrUI"; }
		static KrUIManager* m_pKrUIManager;
		WNDCLASSEX      m_wc; //
		LPCWSTR         m_lpWindowClassName;//
		HINSTANCE       m_hInstance;//
		MSG				m_msg;
		list<KrWindow*>  m_WndList;//
	};



	/************************************************************************/
	/* KrWindow                                                             */
	/************************************************************************/
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



	/************************************************************************/
	/* KrControl                                                            */
	/************************************************************************/
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
		virtual void Destroy();
	};



	/************************************************************************/
	/* KrArea                                                               */
	/************************************************************************/
	class KrArea :public KrControl
	{
	private:
		list<KrControl*> m_CtrlList;
		Graphics* m_pGraphics;
		HDC    m_TempDC;
		HBITMAP m_hbmp;
	public:
		KrControl* AddControl(KrCtrlType CtrlType, LPCWSTR lpName, int x, int y, int width, int height);
		KrArea();
		void UpdateRect();
		void Show();
		void  HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		~KrArea();
		void Draw(Graphics* pGraphics);
		void Destroy();
	};



}//namespace KrUI


#endif // !KRCORE_H

