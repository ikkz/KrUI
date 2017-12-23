#ifndef KRCORE_H
#define KRCORE_H
#pragma once

#define _CRT_SECURE_NO_WARNINGS


#ifdef _DEBUG
#include <iostream>
#endif

#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>
#include "KrMessageHandler.h"
#include "KrUIBase.h"
#include "KrDedug.h"
using namespace std;

namespace KrUI
{
	class KrMessageHandler;
	typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
	class KrWindow;

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
		LPCWSTR m_lpName;
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