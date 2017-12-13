#ifndef KRCORE_H
#define KRCORE_H
#pragma once

#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>
#include "KrDedug.h"
using namespace std;

namespace KrUI
{
	class KrMessageHandler;
	typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
	class KrWindow;

	/************************************************************************/
	/* KrMessageHandler                                                     */
	/*需要进行消息处理的类必须public方式继承此类								*/
	/************************************************************************/
	class KrMessageHandler
	{
	protected:
		multimap<UINT, MSGPROC> m_MsgProcMap;
	public:
		virtual void RegMsg(UINT msg, MSGPROC proc);
		virtual void RemoveMsgProc(MSGPROC proc);
		//在这里将置为NULL的proc删除，必须在子类实现的HandleMessage的结束时调用KrMessageHandler::HandleMessage
		virtual	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	};

	class KrUIBase
	{
	protected:
		RECT m_rect;
		bool m_bVisible;
	public:
		virtual RECT* GetRect();
		virtual void SetRect(RECT* pRect);
		virtual int GetX();
		virtual int GetY();
		virtual int GetWidth();
		virtual int GetHeight();
		virtual void SetX(UINT x);
		virtual void SetY(UINT y);
		virtual void SetXY(UINT x, UINT y);
		virtual void SetWidth(UINT width);
		virtual void SetHeight(UINT height);
		virtual void Show();
		virtual void Hide();
		virtual bool IsVisible();
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
	class KrWindow : public KrMessageHandler ,public KrUIBase
	{
	private:
		LPCWSTR m_lpWindowName;
		HWND m_hwnd;
		DWORD m_dwStyle;
		POINT m_ptMouse;
		POINT m_ptMouseDown;
		bool m_bMouseDown;
	public:
		KrWindow();
		LPCWSTR GetWindowName();
		void SetWindowName(LPCWSTR lpWindowName);
		void SetHWND(HWND hwnd);
		HWND GetHWND();
		void SetStyle(DWORD dwStyle);
		DWORD GetStyle();

		virtual void SetRect(RECT* pRect);
		virtual void SetX(UINT x);
		virtual void SetY(UINT y);
		virtual void SetXY(UINT x, UINT y);
		virtual void SetWidth(UINT width);
		virtual void SetHeight(UINT height);
		virtual void Show();
		virtual void Hide();

		bool IsCreated();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		//void RegMsg(UINT msg, MSGPROC proc);
	};
}//namespace KrUI

#endif // !KRCORE_H