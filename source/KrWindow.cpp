#include "KrCore.h"
#include "KrButton.h"
namespace KrUI
{
	KrWindow::KrWindow()
	{
		m_pKrWindow = nullptr;
		m_UIType = KrUIType::KrWindow_t;
		m_bMouseDown = false;
		m_pGraphicsDC = nullptr;
		m_CaptionColor = Color(9, 163, 220);
		m_CaptionHeight = 30;
		m_StringFormat.SetAlignment(StringAlignmentNear);
	}

	LPCWSTR KrWindow::GetWindowName()
	{
		return m_lpName;
	}

	void KrWindow::SetWindowName(LPCWSTR lpWindowName)
	{
		if (IsCreated())SetWindowText(m_hwnd, lpWindowName);
		m_lpName = lpWindowName;
	}

	void KrWindow::SetHWND(HWND hwnd)
	{
		m_hwnd = hwnd;
		m_hDC = ::GetDC(hwnd);
		m_pGraphicsDC = new Graphics(m_hDC);
		SetWindowText(m_hwnd, m_lpName);
		ChangeBmpSize();
		AddControl(KrCloseButton_t, L"×", 0, 0, 0, 0);
	}

	HWND KrWindow::GetHWND()
	{
		return m_hwnd;
	}

	KrUIBase* KrWindow::AddControl(KrUIType t, LPCWSTR lpName, int x, int y, int width, int height)
	{
		KrUIBase* pui = nullptr;
		switch (t)
		{
		case KrUI::KrButton_t:
			pui = new KrButton;
			pui->SetSize(x, y, width, height);
			break;
		case KrUI::KrCloseButton_t:
			pui = new KrCloseButton;
			int m_Margin = 5;
			pui->SetSize(GetWidth() - m_CaptionHeight + m_Margin, m_Margin, m_CaptionHeight - m_Margin * 2,m_CaptionHeight - m_Margin * 2);
// 			pui = new KrButton;
// 			int m_Margin = 5;
// 			pui->SetSize(GetWidth() - m_CaptionHeight + m_Margin, m_Margin, m_CaptionHeight - m_Margin * 2,m_CaptionHeight - m_Margin * 2);
 			pui->Show();
// 			pui = new KrCloseButton;
//  			pui->Show();
 			break;
		}
		if (pui == nullptr)return nullptr;
		pui->SetType(t);
		pui->SetName(lpName);
		pui->SetParantWindow(this);
		m_UIVec.push_back(pui);
		return pui;
	}

	void KrWindow::SetRect(RECT* pRect)
	{
		KrUIBase::SetRect(pRect);
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
		KrUIBase::SetX(x);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}

	void KrWindow::SetY(UINT y)
	{
		KrUIBase::SetY(y);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);

	}

	void KrWindow::SetXY(UINT x, UINT y)
	{
		KrUIBase::SetXY(x, y);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);
	}

	void KrWindow::SetWidth(UINT width)
	{
		KrUIBase::SetWidth(width);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);
	}

	void KrWindow::SetHeight(UINT height)
	{
		KrUIBase::SetHeight(height);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);
	}

	void KrWindow::Show()
	{
		if (IsCreated())
		{
			ShowWindow(m_hwnd, SW_SHOW);
			KrUIBase::Show();
			UpdateWindow(m_hwnd);
		}
	}

	void KrWindow::Hide()
	{
		if (IsCreated())
		{
			ShowWindow(m_hwnd, SW_HIDE);
			KrUIBase::Hide();
		}
	}

	bool KrWindow::IsCreated()
	{
		if (m_hwnd == NULL)
		{
			return false;
		}
		return true;
	}

	LRESULT  KrWindow::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{


		case WM_LBUTTONDOWN:
			if (GET_Y_LPARAM(lParam)<m_CaptionHeight)
			{
				SendMessage(m_hwnd, WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
				//SetCapture(m_hwnd);
			}
			break;
		case WM_LBUTTONUP:
			if (GET_Y_LPARAM(lParam) < m_CaptionHeight)
			{
				ReleaseCapture();
			}

			break;

		case WM_PAINT:
			UpdateDc();
			break;
		case WM_DESTROY:
			//本窗口被销毁时，检查程序是否存在窗口
			KrUIManager::GetpKrUIManager()->DeleteWindow(this);
			break;
		case WM_MOVE:
		case WM_SIZE:
			GetWindowRect(m_hwnd, GetRect());
			UpdateDc();
			break;
		}
		//调用窗口消息处理函数
		CallMsgProc(Message, wParam, lParam);
		//传递消息给控件
		for (auto p : m_UIVec)
		{
			if (p->IsVisible())
			{
				dynamic_cast<KrMessageHandler*>(p)->HandleMessage(Message, wParam, lParam);
			}
		}
		//
		KrUIBase::HandleMessage(Message, wParam, lParam);
		return DefWindowProc(m_hwnd, Message, wParam, lParam);
	}

	HDC KrWindow::GetDc()
	{
		return m_hDC;
	}

	void KrWindow::ChangeBmpSize()
	{
		if (m_hBmp != NULL)
		{
			DeleteObject(m_hBmp);
		}
		m_hBmp = CreateCompatibleBitmap(m_hDC, GetWidth(), GetHeight());
		delete m_pGraphics;
		delete m_pBmp;
		m_pBmp = new Gdiplus::Bitmap(m_hBmp, NULL);
		m_pGraphics = new Graphics(m_pBmp);
	}


	void KrWindow::UpdateDc()
	{
		if (m_bVisible && (m_pBmp != NULL))
		{
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(Color(255, 255, 255)), 0, 0, GetWidth(), GetHeight());
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_CaptionColor), 0, 0, GetWidth(), m_CaptionHeight);
			m_pGraphics->DrawString((WCHAR*)m_lpName, -1, m_pFont, RectF(10, 0, GetWidth() - 10, m_CaptionHeight), &m_StringFormat, &SolidBrush(Color(255, 255, 255)));
			for (auto p : m_UIVec)
			{
				if (p->IsVisible())
				{
					p->UpdateDc();
				}

			}
			m_pGraphicsDC->DrawImage(m_pBmp,0,0);
		}
	}
} //!KrUI
