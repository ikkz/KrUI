#ifndef _KR_CORE_H
#define _KR_CORE_H
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define TIMER_ID 1
#define TIMER_INTERVAL 100
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
#include "KrProgressBar.h"
#include "KrList.h"
#include "Tools/KrTools.h"

namespace KrUI
{
	class KrMessageHandler;
	class KrUIBase;
	typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
	class KrWindow;

	static Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	static ULONG_PTR m_pGdiToken;

	class KrUIManager
	{
	public:
		static KrUIManager* GetpKrUIManager();
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
		static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT_PTR nTimerid, DWORD dwTime);
		bool Initialize(HINSTANCE hInstance);
		KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height);
		KrWindow* AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height);
		KrWindow* KrUIManager::AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);
		KrWindow* AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);
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
		std::vector<KrWindow*> m_WndVec;//
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
		Gdiplus::Color m_CaptionColor;
		HDC m_hDC;
		Gdiplus::Graphics* m_pGraphicsDC;
		std::vector<KrUIBase*> m_UIVec;
		KrUIBase* m_pFocusedCtrl;
	public:
		friend class KrButton;
		friend class KrCloseButton;
		friend class KrLabel;
		friend class KrEdit;
		friend class KrList;

		KrWindow();
		static LRESULT SizeChange(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
		LPCWSTR GetWindowName();
		void SetWindowName(LPCWSTR lpWindowName);
		void SetHWND(HWND hwnd);
		HWND GetHWND();
		void SetStyle(DWORD dwStyle);
		DWORD GetStyle();

		virtual void SetRect(RECT* pRect);
		virtual void SetX(unsigned int x);
		virtual void SetY(unsigned int y);
		virtual void SetXY(unsigned int x, unsigned int y);
		virtual void SetWidth(unsigned int width);
		virtual void SetHeight(unsigned int height);
		virtual void Show();
		virtual void Hide();
		virtual void Update();
		virtual void ChangeBmpSize();
		virtual void Draw();//自定义绘制的窗口重写此方法
		KrUIBase* GetFocusedCtrl();
		void SetFocusedCtrl(KrUIBase* pui);
		HDC GetDc();
		bool IsCreated();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		KrUIBase* AddControl(KrUIType t, LPCWSTR lpName, int x, int y, int width, int height);
		void RemoveControl(KrUIBase* pui);
		void SetCaptionHeight(unsigned int ch);
		unsigned int GetCaptionHeight();
	};
}//namespace KrUI

#endif // !KRCORE_H