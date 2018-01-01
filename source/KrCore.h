#ifndef KRCORE_H
#define KRCORE_H
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define TIMER_ID 1
#define TIMER_INTERVAL 60
#ifdef _DEBUG
#include <iostream>
#endif

#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>
#include <gdiplus.h>

#pragma comment(lib,"gdiplus.lib")
#include "KrMessageHandler.h"
#include "KrUIBase.h"
#include "KrDefine.h"
#include "KrButton.h"
#include "KrLabel.h"
#include "KrEdit.h"

using namespace std;
using namespace Gdiplus;


namespace KrUI
{
	class KrMessageHandler;
	class KrUIBase;
	typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
	class KrWindow;

	static GdiplusStartupInput m_gdiplusStartupInput;
	static ULONG_PTR m_pGdiToken;

	class KrUIManager
	{
	public:
		static KrUIManager* GetpKrUIManager();
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);
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
		~KrUIManager();
	private:
		KrUIManager() { m_lpWindowClassName = L"KrUI"; }
		static KrUIManager* m_pKrUIManager;
		LPCWSTR m_lpWindowClassName;//
		HINSTANCE m_hInstance;//
		MSG m_msg;
		vector<KrWindow*> m_WndVec;//
	};





	class KrWindow :public KrUI::KrUIBase
	{
	private:
		LPCWSTR m_lpName;
		HWND m_hwnd;
		DWORD m_dwStyle;
		POINT m_ptMouse;
		UINT m_CaptionHeight;
		POINT m_ptMouseDown;
		bool m_bMouseDown;
		Color m_CaptionColor;
		HDC m_hDC;
		Graphics* m_pGraphicsDC;
		vector<KrUIBase*> m_UIVec;
	public:
		KrWindow();
		static LRESULT SizeChange(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
		LPCWSTR GetWindowName();
		void SetWindowName(LPCWSTR lpWindowName);
		void SetHWND(HWND hwnd);
		HWND GetHWND();
		void SetStyle(DWORD dwStyle);
		DWORD GetStyle();
		friend class KrButton;
		friend class KrCloseButton;
		friend class KrLabel;
		virtual void SetRect(RECT* pRect);
		virtual void SetX(UINT x);
		virtual void SetY(UINT y);
		virtual void SetXY(UINT x, UINT y);
		virtual void SetWidth(UINT width);
		virtual void SetHeight(UINT height);
		virtual void Show();
		virtual void Hide();
		virtual void UpdateDc();
		virtual void ChangeBmpSize();
		HDC GetDc();
		bool IsCreated();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		KrUIBase* AddControl(KrUIType t, LPCWSTR lpName, int x, int y, int width, int height);
		void RemoveControl(KrUIBase* pui);
	};
}//namespace KrUI

#endif // !KRCORE_H