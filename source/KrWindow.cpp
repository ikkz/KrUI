#include "KrCore.h"
#include "KrButton.h"
#include "KrProgressBar.h"
#include "KrList.h"
namespace KrUI
{
	KrWindow::KrWindow()
	{
		m_pKrWindow = nullptr;
		m_UIType = KrUIType::KrWindow_t;
		m_bMouseDown = false;
		m_pGraphicsDC = nullptr;
		m_hDC = NULL;
		m_CaptionColor = Gdiplus::Color(9, 163, 220);
		m_BgColor = Gdiplus::Color(240, 240, 240);
		m_CaptionHeight = 38;
		m_StringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
		m_pFocusedCtrl = nullptr;
		m_pKrWindow = nullptr;
	}
	KrUIBase* KrWindow::GetFocusedCtrl()
	{
		return m_pFocusedCtrl;
	}
	void KrWindow::SetFocusedCtrl(KrUIBase* pui)
	{
		m_pFocusedCtrl = pui;
	}
	LPCWSTR KrWindow::GetWindowName()
	{
		return m_lpName;
	}

	void KrWindow::SetWindowName(LPCWSTR lpWindowName)
	{
		if (IsCreated())SetWindowTextW(m_hwnd, lpWindowName);
		m_lpName = lpWindowName;
	}

	void KrWindow::SetHWND(HWND hwnd)
	{
		m_hwnd = hwnd;
		m_hDC = ::GetDC(hwnd);
		m_pGraphicsDC = new Gdiplus::Graphics(m_hDC);
		SetWindowTextW(m_hwnd, m_lpName);
		ChangeBmpSize();
		RegMsg(WM_SIZE, reinterpret_cast<MSGPROC>(KrWindow::SizeChange));

		//添加关闭按钮
		if (m_CaptionHeight == 0)return;
		KrUIBase* pui = new KrCloseButton;
		int Margin = dynamic_cast<KrCloseButton*>(pui)->GetMargin();
		pui->SetSize(GetWidth() - m_CaptionHeight + Margin, Margin, m_CaptionHeight - Margin * 2, m_CaptionHeight - Margin * 2);
		pui->Show();
		pui->SetType(KrCloseButton_t);
		pui->SetName(L"×");
		pui->SetParantWindow(this);
		m_UIVec.push_back(pui);


	}

	HWND KrWindow::GetHWND()
	{
		return m_hwnd;
	}

	void KrWindow::SetCaptionHeight(unsigned int ch)
	{
		if (ch > GetHeight())ch = GetHeight();
		m_CaptionHeight = ch;
	}
	unsigned int KrWindow::GetCaptionHeight()
	{
		return m_CaptionHeight;
	}

	KrButton* KrWindow::AddButton(LPCWSTR lpName, int x, int y, int width, int height)
	{
		return dynamic_cast<KrButton*>(AddControl(KrButton_t, lpName, x, y, width, height));
	}
	KrLabel* KrWindow::AddLabel(LPCWSTR lpName, int x, int y, int width, int height)
	{
		return dynamic_cast<KrLabel*>(AddControl(KrLabel_t, lpName, x, y, width, height));
	}
	KrEdit* KrWindow::AddEdit(LPCWSTR lpName, int x, int y, int width, int height)
	{
		return dynamic_cast<KrEdit*>(AddControl(KrEdit_t, lpName, x, y, width, height));
	}
	KrList* KrWindow::AddList(LPCWSTR lpName, int x, int y, int width, int height)
	{
		return dynamic_cast<KrList*>(AddControl(KrList_t, lpName, x, y, width, height));
	}
	KrProgressBar* KrWindow::AddProgressBar(LPCWSTR lpName, int x, int y, int width, int height)
	{
		return dynamic_cast<KrProgressBar*>(AddControl(KrProgressBar_t, lpName, x, y, width, height));
	}
	KrUIBase* KrWindow::AddControl(KrUIType t, LPCWSTR lpName, int x, int y, int width, int height)
	{
		KrUIBase* pui = nullptr;
		switch (t)
		{
		case KrEdit_t:
			pui = new KrEdit;
			dynamic_cast<KrEdit*>(pui)->SetText(lpName);
			break;
		case KrLabel_t:
			pui = new KrLabel(m_BgColor);
			break;
		case KrButton_t:
			pui = new KrButton;
			break;
		case KrProgressBar_t:
			pui = new KrProgressBar;
			break;
		case KrList_t:
			pui = new KrList;
			break;
		}
		if (pui == nullptr)return nullptr;
		pui->SetType(t);
		pui->SetName(lpName);
		pui->SetParantWindow(this);
		pui->SetSize(x, y, width, height);
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

	void KrWindow::SetX(unsigned int x)
	{
		KrUIBase::SetX(x);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);
	}

	void KrWindow::SetY(unsigned int y)
	{
		KrUIBase::SetY(y);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);
	}

	void KrWindow::SetXY(unsigned int x, unsigned int y)
	{
		KrUIBase::SetXY(x, y);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);
	}

	void KrWindow::SetWidth(unsigned int width)
	{
		KrUIBase::SetWidth(width);
		if (IsCreated())MoveWindow(m_hwnd, m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, TRUE);
	}

	void KrWindow::SetHeight(unsigned int height)
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
			return false;
		return true;
	}

	LRESULT  KrWindow::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case WM_MOUSEMOVE:
		{
			m_ptMouse.x = GET_X_LPARAM(lParam);
			m_ptMouse.y = GET_Y_LPARAM(lParam);
		}
		break;
		case WM_CREATE:
			SetClassLong(m_hwnd, GCL_STYLE, GetClassLong(m_hwnd, GCL_STYLE) | CS_DROPSHADOW);
			break;
		case WM_LBUTTONDOWN:
			if (GET_Y_LPARAM(lParam) < static_cast<int>(m_CaptionHeight))
			{
				SendMessage(m_hwnd, WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
			}
			break;
		case WM_LBUTTONUP:
			if (GET_Y_LPARAM(lParam) < static_cast<int>(m_CaptionHeight))
			{
				ReleaseCapture();
			}
			break;

		case WM_DESTROY:
			//本窗口被销毁时，检查程序是否存在窗口
			KrUIManager::GetpKrUIManager()->DeleteWindow(this);
			break;
		case WM_MOVE:
		case WM_SIZE:
			GetWindowRect(m_hwnd, GetRect());
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(this->GetHWND(), &ps);
			Update();
			EndPaint(this->GetHWND(), &ps);
		}
		break;
		case WM_KILLFOCUS:
			m_pFocusedCtrl = nullptr;
			break;
		}
		//调用窗口消息处理函数
		CallMsgProc(Message, wParam, lParam);
		//传递消息给控件
		for (auto p : m_UIVec)
		{
			if (p != nullptr&&p->IsVisible())
			{
				dynamic_cast<KrMessageHandler*>(p)->HandleMessage(Message, wParam, lParam);
			}
		}
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
		//DeleteObject(m_hDC);
		//m_pGraphicsDC = new Graphics(::GetDC(m_hwnd));

		delete m_pGraphicsDC;
		m_pGraphicsDC = new Gdiplus::Graphics(m_hDC);

		m_pGraphics = new Gdiplus::Graphics(m_pBmp);
		//m_pGraphicsDC->Clear(Color(255, 255, 255));
	}

	// 	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
	// 	{
	// 		UINT num = 0; // number of image encoders
	// 		UINT size = 0; // size of the image encoder array in bytes
	// 		Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;
	// 		Gdiplus::GetImageEncodersSize(&num, &size);
	// 		if (size == 0)
	// 			return -1; // Failure
	// 		pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	// 		if (pImageCodecInfo == NULL)
	// 			return -1; // Failure
	// 		GetImageEncoders(num, size, pImageCodecInfo);
	// 		for (UINT j = 0; j < num; ++j)
	// 		{
	// 			if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
	// 			{
	// 				*pClsid = pImageCodecInfo[j].Clsid;
	// 				free(pImageCodecInfo);
	// 				return j; // Success- 87 -
	// 			}
	// 		}
	// 		free(pImageCodecInfo);
	// 		return -1; // Failure
	// 	}

	void KrWindow::Update()
	{
		if (m_bVisible && (m_pBmp != nullptr))
		{
			m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_BgColor), 0, 0, m_pBmp->GetWidth(), m_pBmp->GetHeight());
			if (m_CaptionHeight > 0)
			{
				m_pGraphics->FillRectangle(&Gdiplus::SolidBrush(m_CaptionColor), 0, 0, m_pBmp->GetWidth(), m_CaptionHeight);
				m_pGraphics->DrawString((WCHAR*)m_lpName, -1, m_pFont, Gdiplus::RectF(static_cast<Gdiplus::REAL>(10), static_cast<Gdiplus::REAL>(0), static_cast<Gdiplus::REAL>(m_pBmp->GetWidth() - 10), static_cast<Gdiplus::REAL>(m_CaptionHeight)), &m_StringFormat, &Gdiplus::SolidBrush(m_FontColor));
			}
			this->Draw();
			for (auto p : m_UIVec)
			{
				if (p != nullptr&&p->IsVisible())
				{

					p->Update();
				}
			}
			if (m_CaptionHeight > 0)m_pGraphics->DrawRectangle(&Gdiplus::Pen(m_BorderColor, 1), 0, 0, GetWidth() - 1, GetHeight() - 1);
			m_pGraphicsDC->DrawImage(m_pBmp, 0, 0, GetWidth(), GetHeight());
		}
	}

	void KrWindow::RemoveControl(KrUIBase* pui)
	{
		for (auto& p : m_UIVec)
		{
			if (p == pui)
			{
				delete p;
				p = nullptr;
			}
		}
	}

	void KrWindow::Draw()
	{
	}

	//定义默认消息处理函数，注册在SetHWND中
	LRESULT KrWindow::SizeChange(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam)
	{
		KrWindow* pKw = dynamic_cast<KrWindow*>(pKrMessageHandler);
		pKw->ChangeBmpSize();
		lParam = 0;
		for (auto p : pKw->m_UIVec)
		{
			if (p->GetType() == KrCloseButton_t)
			{
				dynamic_cast<KrCloseButton*>(p)->SetButtonStatus(mouse_hover);
			}
		}
		return 0;
	}
} //!KrUI