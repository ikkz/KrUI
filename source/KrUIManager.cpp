#include "KrCore.h"

namespace KrUI
{

	KrUIManager* KrUIManager::m_pKrUIManager = NULL;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return  KrUIManager::GetpKrUIManager()->HandleMessage(hwnd, Message, wParam, lParam);
	}


	KrUIManager* KrUIManager::GetpKrUIManager()
	{

		if (m_pKrUIManager == NULL)
			m_pKrUIManager = new KrUIManager();
		return m_pKrUIManager;
	}

	void KrUIManager::CheckWindowNum()
	{
		if (GetWindowNum() == 0) PostQuitMessage(0);
	}

	bool      KrUIManager::Initialize(HINSTANCE hInstance)
	{
		m_hInstance = hInstance;
		memset(&m_wc, 0, sizeof(m_wc));
		m_wc.cbSize = sizeof(WNDCLASSEX);
		m_wc.lpfnWndProc = WndProc;
		m_wc.hInstance = m_hInstance;
		m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		m_wc.lpszClassName = GetWindowClassName();
		m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		m_wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		if (!RegisterClassEx(&m_wc))
		{
			return false;
		}

		return true;
		//TODO
	}


	KrWindow* KrUIManager::AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height)
	{
		KrWindow* pKrWindow = new KrWindow;
		if (!pKrWindow) return NULL;
		pKrWindow->SetWindowName(lpWindowName);
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		pKrWindow->SetRect(&rect);
		pKrWindow->SetStyle(NULL);
		HWND hwnd = CreateWindow(KrUIManager::GetpKrUIManager()->GetWindowClassName(), lpWindowName, WS_VISIBLE | WS_OVERLAPPED, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, KrUIManager::GetpKrUIManager()->GetHINSTANCE(), NULL);
		pKrWindow->SetHWND(hwnd);
		// 		LONG_PTR style = GetWindowLongPtr(pKrWindow->GetHWND(), GWL_STYLE);
		// 		style = style&~WS_CAPTION&~WS_SYSMENU&~WS_SIZEBOX&~WS_BORDER;
		// 		SetWindowLongPtr(pKrWindow->GetHWND(), GWL_STYLE, style);
		// 		pKrWindow->SetStyle(style);
		m_WndVec.push_back(pKrWindow);
		return pKrWindow;
	}


	LPCWSTR KrUIManager::GetWindowClassName()
	{
		return m_lpWindowClassName;
	}


	HINSTANCE KrUIManager::GetHINSTANCE()
	{
		return m_hInstance;
	}


	int  KrUIManager::MessageLoop()
	{
		while (GetMessage(&m_msg, NULL, 0, 0) != 0)
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		return m_msg.wParam;
	}


	LRESULT   KrUIManager::HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{

		for (vector<KrWindow*>::iterator it = m_WndVec.begin(); it != m_WndVec.end(); it++)
		{
			if (hwnd == (*it)->GetHWND())
			{
				return (*it)->HandleMessage(Message, wParam, lParam);
			}
		}
		return TRUE;
	}

	KrWindow* KrUIManager::GetpKrWindow(HWND hwnd)
	{
		for (vector<KrWindow*>::iterator it = m_WndVec.begin(); it != m_WndVec.end(); it++)
		{
			if ((*it)->GetHWND() == hwnd)
			{
				return (*it);
			}
		}
		return NULL;
	}


	int KrUIManager::GetWindowNum()
	{
		return m_WndVec.size();
	}


	void KrUIManager::DeleteWindow(KrWindow* pKrWindow)
	{
		auto result = std::find(m_WndVec.begin(), m_WndVec.end(), pKrWindow);
		if (result != m_WndVec.end())
		{
			m_WndVec.erase(result);
		}
		//todo
	}


	KrUIManager::~KrUIManager()
	{
		//todo
	}



}// !KrUI