#ifndef KRCORE_H
#define KRCORE_H
#pragma once

#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

namespace KrUI
{

	typedef LRESULT(*MSGPROC)(void* pObject, WPARAM wParam, LPARAM lParam);
	class KrWindow;

	/************************************************************************/
	/* KrMessageHandler                                                     */
	/************************************************************************/
	class KrMessageHandler
	{
	protected:
		multimap<UINT, MSGPROC> m_MsgProcMap;
	public:
		virtual void RegMsg(UINT msg, MSGPROC proc);
		virtual void RemoveMsgProc(MSGPROC proc);
		virtual	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	};

	/************************************************************************/
	/* KrUIManager                                                          */
	/************************************************************************/
	class KrUIManager
	{
	public:
		static KrUIManager* GetpKrUIManager();
		bool Initialize(HINSTANCE hInstance);
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height);
		LPCWSTR GetWindowClassName();
		HINSTANCE GetHINSTANCE();
		int MessageLoop();
		LRESULT HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		int GetWindowNum();
		void DeleteWindow(KrWindow* pKrWindow);
		KrWindow* GetpKrWindow(HWND hwnd);
		void CheckWindowNum();
		~KrUIManager();
	private:
		KrUIManager() { m_lpWindowClassName = L"KrUI"; }
		static KrUIManager* m_pKrUIManager;
		WNDCLASSEX m_wc; //
		LPCWSTR m_lpWindowClassName;//
		HINSTANCE m_hInstance;//
		MSG m_msg;
		vector<KrWindow*> m_WndVec;//
	};




	/************************************************************************/
	/* KrWindow                                                             */
	/************************************************************************/
	class KrWindow : public KrMessageHandler
	{
	private:
		LPCWSTR m_lpWindowName;
		HWND m_hwnd;
		RECT m_rect;
		DWORD m_dwStyle;
		bool m_bVisible;
		POINT m_ptMouse;
		POINT m_ptMouseDown;
		bool m_bMouseDown;
		//multimap<UINT, MSGPROC> m_MsgFuncMap;

	public:
		KrWindow();
		LPCWSTR GetWindowName();
		void SetWindowName(LPCWSTR lpWindowName);
		void SetHWND(HWND hwnd);
		HWND GetHWND();
		RECT* GetRect();
		void SetRect(RECT* pRect);
		void SetStyle(DWORD dwStyle);
		DWORD GetStyle();
		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();
		void SetX(UINT x);
		void SetY(UINT y);
		void SetXY(UINT x, UINT y);
		void SetWidth(UINT width);
		void SetHeight(UINT height);
		void Show();
		void Hide();
		bool IsVisible();
		bool IsCreated();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		//void RegMsg(UINT msg, MSGPROC proc);
	};
}//namespace KrUI

#endif // !KRCORE_H