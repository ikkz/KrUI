#include<windows.h>
#include"KrUIManager.h"
#include"KrWindow.h"

namespace KrUI{

	LPCWSTR KrWindow::GetWindowName()
	{
		return m_lpWindowName;
	}

	void KrWindow::SetWindowName(LPCWSTR lpWindowName)
	{
		if (IsCreated())SetWindowText(m_hwnd, lpWindowName);
		m_lpWindowName = lpWindowName;
	}




	HWND KrWindow::GetHWND()
	{
		return m_hwnd;
	}


	RECT* KrWindow::GetRect()
	{
		return &m_rect;
	}


	void KrWindow::SetRect(RECT* pRect)
	{
		m_rect.left = pRect->left;
		m_rect.right = pRect->right;
		m_rect.top = pRect->top;
		m_rect.bottom = pRect->bottom;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}




	void KrWindow::SetStyle(DWORD dwStyle)
	{
		m_dwStyle = dwStyle;
		if (IsCreated())SetWindowLong(m_hwnd, GWL_STYLE, dwStyle);
	}
	DWORD KrWindow::GetStyle()
	{
		return m_dwStyle;
	}


	bool KrWindow::Create()
	{
		HWND hwnd = CreateWindow(KrUIManager::GetpKrUIManager()->GetWindowClassName(), m_lpWindowName, m_dwStyle,
			m_rect.left, m_rect.top,
			m_rect.right - m_rect.left, m_rect.bottom - m_rect.top,
			NULL, NULL, KrUIManager::GetpKrUIManager()->GetHINSTANCE(), NULL);
		if (!hwnd) return false;
		m_hwnd = hwnd;
		GetWindowRect(hwnd, &m_rect);
		return true;
	}



	int KrWindow::GetX()
	{
		return m_rect.left;
	}



	int KrWindow::GetY()
	{
		return m_rect.top;
	}



	int KrWindow::GetWidth()
	{
		return m_rect.right - m_rect.left;
	}



	int KrWindow::GetHeight()
	{
		return m_rect.bottom - m_rect.top;
	}


	void KrWindow::SetX(int x)
	{
		int width = GetWidth();
		m_rect.left = x;
		m_rect.right = x + width;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::SetY(int y)
	{
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::SetWidth(int width)
	{
		m_rect.right = m_rect.left + width;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}



	void KrWindow::SetHeight(int height)
	{
		m_rect.bottom = m_rect.top + height;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::Show()
	{
		if (IsCreated())
		{
			ShowWindow(m_hwnd, SW_SHOW);
			m_bVisible = true;
		}

	}


	void KrWindow::Hide()
	{
		if (IsCreated())
		{
			ShowWindow(m_hwnd, SW_HIDE);
			m_bVisible = false;
		}

	}


	bool KrWindow::IsVisible()
	{
		return m_bVisible;
	}


	bool KrWindow::IsCreated()
	{
		if (m_hwnd==NULL)
		{
			return false;
		} 
		return true;
	}


	void KrWindow::Destroy(bool bDelete)
	{
		SendMessage(m_hwnd, WM_CLOSE, 0, 0);
		m_hwnd = NULL;
		if (bDelete)
		{
			KrUIManager::GetpKrUIManager()->DeleteWindow(this);
		}
		if (KrUIManager::GetpKrUIManager()->GetWindowNum() == 0)PostQuitMessage(0);
	}






	LRESULT  KrWindow::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case WM_DESTROY: 
		   		   	Destroy(true);
					break;
		case WM_LBUTTONDOWN:
			//SetX(0); SetY(0);
			//SetWidth(50); SetHeight(50);
// 			Hide();
// 			Sleep(5000);
// 			Show();
		//	MessageBox(m_hwnd, m_lpWindowName, m_lpWindowName, MB_OK);
			break;
		default:
			return DefWindowProc(m_hwnd, Message, wParam, lParam);
		}
		return 0;

	}


}