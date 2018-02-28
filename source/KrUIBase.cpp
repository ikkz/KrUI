#include "KrUIBase.h"
#include "KrCore.h"
namespace KrUI
{
	RECT* KrUIBase::GetRect()
	{
		return &m_rect;
	}

	unsigned int KrUIBase::GetX()
	{
		return m_rect.left;
	}

	unsigned int KrUIBase::GetY()
	{
		return m_rect.top;
	}

	unsigned int KrUIBase::GetWidth()
	{
		return m_rect.right - m_rect.left;
	}

	unsigned int KrUIBase::GetHeight()
	{
		return m_rect.bottom - m_rect.top;
	}

	void KrUIBase::SetX(unsigned int x)
	{
		int width = GetWidth();
		m_rect.left = x;
		m_rect.right = x + width;

		this->ChangeBmpSize();
	}
	void KrUIBase::SetY(unsigned int y)
	{
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;

		this->ChangeBmpSize();
	}

	void KrUIBase::SetXY(unsigned int x, unsigned int y)
	{
		int width = GetWidth();
		int height = GetHeight();
		m_rect.left = x;
		m_rect.right = x + width;
		m_rect.top = y;
		m_rect.bottom = y + height;
		this->ChangeBmpSize();
	}

	void KrUIBase::SetWidth(unsigned int width)
	{
		m_rect.right = m_rect.left + width;
		this->ChangeBmpSize();
	}

	void KrUIBase::SetHeight(unsigned int height)
	{
		m_rect.bottom = m_rect.top + height;
		this->ChangeBmpSize();
	}

	void KrUIBase::SetSize(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		m_rect.left = x;
		m_rect.right = x + width;
		m_rect.top = y;
		m_rect.bottom = y + height;
		this->ChangeBmpSize();
	}

	bool KrUIBase::IsVisible()
	{
		return m_bVisible;
	}

	void KrUIBase::SetRect(RECT* pRect)
	{
		m_rect.left = pRect->left;
		m_rect.right = pRect->right;
		m_rect.top = pRect->top;
		m_rect.bottom = pRect->bottom;
		this->ChangeBmpSize();
	}

	void KrUIBase::ChangeBmpSize()
	{
		if (m_pKrWindow == nullptr)return;
		if (m_hBmp != NULL)
		{
			DeleteObject(m_hBmp);
		}
		m_hBmp = CreateCompatibleBitmap(m_pKrWindow->GetDc(), GetWidth(), GetHeight());
		delete m_pGraphics;
		delete m_pBmp;
		m_pBmp = new Gdiplus::Bitmap(m_hBmp, NULL);
		m_pGraphics = new Gdiplus::Graphics(m_pBmp);
		//m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
		//this->Update();
	}

	void KrUIBase::Show()
	{
		m_bVisible = true;
	}

	void KrUIBase::Hide()
	{
		m_bVisible = false;
	}

	void KrUIBase::SetDc(HDC hdc)
	{
	}

	Gdiplus::Graphics* KrUIBase::GetBmpGraphics()
	{
		return m_pGraphics;
	}

	void KrUIBase::SetName(std::wstring name)
	{
		m_strName = name;
		if (m_pGraphics != nullptr)
		{
			SetPaintStatus(Paint_Status::part);
		}
	}
	std::wstring KrUIBase::GetName()
	{
		return m_strName;
	}
	LRESULT KrUIBase::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		LPARAM new_lparam;
		new_lparam = MAKELONG(GET_X_LPARAM(lParam) - m_rect.left, GET_Y_LPARAM(lParam) - m_rect.top);
		//对原来的消息进行一些转换成为KM
		switch (Message)
		{
		case WM_MOUSEMOVE:
		{
			POINT ptMouse;
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
			bool bMouseIn = PtInRect(&m_rect, ptMouse) ? true : false;
			if (m_bMouseIn == false && bMouseIn == true)
			{
				//SendMessage(m_pKrWindow->GetHWND(), KM_MOUDEENTER, NULL, NULL);
				m_bMouseIn = bMouseIn;
				this->CallMsgProc(KM_MOUSEENTER, wParam, new_lparam);
			}
			else if (m_bMouseIn == true && bMouseIn == false)
			{
				m_bMouseIn = bMouseIn;
				this->CallMsgProc(KM_MOUSELEAVE, wParam, new_lparam);
			}
			this->CallMsgProc(KM_MOUSEMOVE, wParam, new_lparam);

			break;
		}
		case WM_LBUTTONDOWN:
		{
			m_bMouseDown = true;
			POINT ptMouse;
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
			//BOOL bMouseIn = PtInRect(&m_rect, ptMouse);
			if (m_bMouseIn)
			{
				this->CallMsgProc(KM_LBTNDOWN, wParam, new_lparam);
			}
			break;
		}
		case WM_LBUTTONUP:
		{
			m_bMouseDown = false;
			POINT ptMouse;
			ptMouse.x = GET_X_LPARAM(lParam);
			ptMouse.y = GET_Y_LPARAM(lParam);
			if (m_bMouseIn)
			{
				this->CallMsgProc(KM_LBTNUP, wParam, new_lparam);
			}
			break;
		}
		default:
			break;
		}
		return KrMessageHandler::HandleMessage(Message, wParam, lParam);
	}
	KrUIBase::KrUIBase()
	{
		m_bMouseIn = false;
		m_pBmp = nullptr;
		m_pGraphics = nullptr;
		m_pKrWindow = nullptr;
		m_hBmp = NULL;
		m_bVisible = true;
		m_StringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
		m_StringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		m_pFont = new Gdiplus::Font(L"微软雅黑", 16, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
		m_FontColor = Gdiplus::Color(255, 255, 255);
		m_BorderColor = Gdiplus::Color(24, 132, 218);
		m_BgColor = Gdiplus::Color::White;
		m_hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_Ps = Paint_Status::all;
	}
	KrUIBase::~KrUIBase()
	{
		delete m_pGraphics;
		delete m_pBmp;
		DeleteObject(m_hBmp);
	}

	Paint_Status KrUIBase::GetPaintStatus()
	{
		return m_Ps;
	}
	void KrUIBase::SetPaintStatus(Paint_Status ps)
	{
		m_Ps = ps;
		if (m_pKrWindow != nullptr)
		{
			this->Update();
			m_pKrWindow->Update();
		}
	}

	void KrUIBase::SetParantWindow(KrWindow* pKrWindow)
	{
		if ((!m_pKrWindow) && (pKrWindow))
		{
			m_pKrWindow = pKrWindow;
			m_hBmp = CreateCompatibleBitmap(m_pKrWindow->GetDc(), GetWidth(), GetHeight());
			m_pBmp = new Gdiplus::Bitmap(m_hBmp, NULL);
			m_pGraphics = new Gdiplus::Graphics(m_pBmp);
			//m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
		}
	}

	void KrUIBase::CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (m_bVisible)
		{
			switch (Message)
			{
			case KM_MOUSEENTER:
				if (m_pKrWindow != nullptr&&m_hCursor != nullptr)
				{

#ifdef _WIN64
					SetClassLong(m_pKrWindow->GetHWND(), (-12), reinterpret_cast<LONG>(m_hCursor));
#else
					SetClassLong(m_pKrWindow->GetHWND(), GCL_HCURSOR, reinterpret_cast<LONG>(m_hCursor));
#endif
				}
				break;
			case KM_MOUSELEAVE:
				if (m_pKrWindow != nullptr&&m_hCursor != nullptr)
				{
#ifdef _WIN64
					SetClassLong(m_pKrWindow->GetHWND(), (-12), reinterpret_cast<LONG>(LoadCursor(nullptr, IDC_ARROW)));
#else
					SetClassLong(m_pKrWindow->GetHWND(), GCL_HCURSOR, reinterpret_cast<LONG>(LoadCursor(nullptr, IDC_ARROW)));
#endif

			}
				break;
			case KM_LBTNUP:
				m_bMouseDown = false;
				if (m_pKrWindow != nullptr)
				{
					m_pKrWindow->SetFocusedCtrl(this);
				}
		}
// 			for (auto p : m_MsgProcMap)
// 			{
// 				if (p.first == Message)
// 				{
// 					p.second(this, wParam, lParam);
// 				}
// 			}
	}

		KrMessageHandler::CallMsgProc(Message, wParam, lParam);
}

	void KrUIBase::SetType(KrUIType ut)
	{
		m_UIType = ut;
	}
	KrUIType KrUIBase::GetType()
	{
		return m_UIType;
	}

	KrWindow* KrUIBase::GetParantWindow()
	{
		return m_pKrWindow;
	}

	void KrUIBase::SetFontColor(Gdiplus::Color color)
	{
		m_FontColor = color;
	}
	Gdiplus::Color KrUIBase::GetFontColor()
	{
		return m_FontColor;
	}
	void KrUIBase::SetFont(const WCHAR* fontfamily, Gdiplus::REAL emSize)
	{
		delete m_pFont;
		m_pFont = new Gdiplus::Font(fontfamily, emSize);
	}

	Gdiplus::Font* KrUIBase::GetFont()
	{
		return m_pFont;
	}

	Gdiplus::Color KrUIBase::GetBgColor()
	{
		return m_BgColor;
	}

	void KrUIBase::SetBgColor(Gdiplus::Color c)
	{
		m_BgColor = c;
	}
	void KrUIBase::Update()
	{
		m_pKrWindow->GetBmpGraphics()->DrawImage(m_pBmp, static_cast<int>(GetX()), GetY(), GetWidth(), GetHeight());
	}

	void KrUIBase::SetAlignment(Gdiplus::StringAlignment align)
	{
		m_StringFormat.SetAlignment(align);
	}
	void KrUIBase::SetLineAlignment(Gdiplus::StringAlignment align)
	{
		m_StringFormat.SetLineAlignment(align);
	}
}// namespace KrUI