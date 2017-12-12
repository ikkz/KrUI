#include "KrCore.h"

namespace KrUI
{
	KrWindow::KrWindow()
	{
		m_bMouseDown = false;
	}


	LPCWSTR KrWindow::GetWindowName()
	{
		return m_lpWindowName;
	}

	void KrWindow::SetWindowName(LPCWSTR lpWindowName)
	{
		if (IsCreated())SetWindowTextW(m_hwnd, lpWindowName);
		m_lpWindowName = lpWindowName;
	}

	void KrWindow::SetHWND(HWND hwnd)
	{
		m_hwnd = hwnd;
	}


	HWND KrWindow::GetHWND()
	{
		return m_hwnd;
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






	void KrWindow::SetX(UINT x)
	{
		int width = GetWidth();
		m_rect.left = x;
		m_rect.right = x + width;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::SetY(UINT y)
	{
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}

	void KrWindow::SetXY(UINT x, UINT y)
	{
		int width = GetWidth();
		m_rect.left = x;
		m_rect.right = x + width;
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);
	}



	void KrWindow::SetWidth(UINT width)
	{
		m_rect.right = m_rect.left + width;
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}


	void KrWindow::SetHeight(UINT height)
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
		if (m_hwnd == NULL)
		{
			return false;
		}
		return true;
	}





	// 	void KrWindow::RegMsg(UINT msg, MSGPROC proc)
	// 	{
	// 		m_MsgProcMap.insert(multimap<UINT, MSGPROC>::value_type(msg, proc));
	// 	}

	// 	void KrWindow::RemoveMsgProc(MSGPROC proc)
	// 	{
	// 		auto ret = m_MsgProcMap.end();
	// 		//不安全，上层存在m_MsgFuncMap的遍历
	// 		for (auto it = m_MsgProcMap.begin(); it != m_MsgProcMap.end(); it++)
	// 		{
	// 			if (*it->second==proc)
	// 			{
	// 				ret = it;
	// 			}
	// 		}
	// 		m_MsgProcMap.erase(ret);
	// 	}

	LRESULT  KrWindow::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{

		switch (Message)
		{
		case WM_DESTROY:
			//本窗口被销毁时，检查程序是否存在窗口
			KrUIManager::GetpKrUIManager()->DeleteWindow(this);
			KrUIManager::GetpKrUIManager()->CheckWindowNum();
			break;
		default:
			break;
		}

		// 		for (list<KrControl*>::iterator it = m_CtrlVec.begin(); it != m_CtrlVec.end(); it++)
		// 		{
		// 			(*it)->HandleMessage(Message, wParam, lParam);
		// 		}
		// 

		for (auto p : m_MsgProcMap)
		{
			if (p.first == Message) (p.second)(this, wParam, lParam);
		}
		KrMessageHandler::HandleMessage(Message, wParam, lParam);
		return DefWindowProc(m_hwnd, Message, wParam, lParam);
	}


} //!KrUI
