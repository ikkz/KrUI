#include "KrCore.h"
namespace KrUI
{
	enum KrCtrlType; 
	KrControl* KrArea::AddControl(KrCtrlType CtrlType, LPCWSTR lpName, int x, int y, int width, int height)
	{
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		KrControl* pKrCtrl = NULL;
		switch (CtrlType)
		{
		case Control:
			pKrCtrl = new KrControl;
			break;
		case Button:

			break;
		default:
			return NULL;
			break;
		}
		if (!pKrCtrl)return NULL;
		pKrCtrl->SetCtrlType(CtrlType);
		pKrCtrl->SetWindow(GetWindow());
		pKrCtrl->SetName(lpName);
		pKrCtrl->SetRect(&rect);
		m_CtrlList.push_back(pKrCtrl);
		return pKrCtrl;
	}

	KrArea::KrArea()
 	{
		m_TempDC = NULL;
		m_pGraphics = NULL;
		m_hbmp = NULL;
		Hide();
	}

	void KrArea::UpdateRect()
	{
		DeleteObject(m_hbmp);
		m_hbmp = CreateCompatibleBitmap(m_TempDC,  GetWidth(), GetHeight());
		SelectObject(m_TempDC, m_hbmp);
	}

	void KrArea::Show()
	{
		m_bVisible = true;
		if (m_TempDC==NULL)
		{
			m_TempDC = CreateCompatibleDC(GetWindow()->GetTempDC());
			m_pGraphics = new Graphics(m_TempDC);
			m_hbmp = CreateCompatibleBitmap(m_TempDC, GetWidth(), GetHeight());
			SelectObject(m_TempDC, m_hbmp);
			//todo
			SolidBrush sb(Color(255,0,0, 255));
			m_pGraphics->FillRectangle(&sb, 0, 0, GetWidth(), GetHeight());
		}
	}
	//
	KrArea::~KrArea()
	{
		DeleteObject(m_TempDC);
		DeleteObject(m_hbmp);
	}

	void  KrArea::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (!m_bVisible) return;

		if (KrControl::m_lpCtrlName==L"Caption"&& GET_Y_LPARAM(lParam)<=m_rect.bottom)
		{
			KrWindow* pKrWindow = GetWindow();
			switch (Message)
			{
// 			case WM_LBUTTONDOWN:
// 				pKrWindow->m_bMouseDown = true;
// 				pKrWindow->m_ptMouseDown.x = GET_X_LPARAM(lParam);
// 				pKrWindow->m_ptMouseDown.y = GET_Y_LPARAM(lParam);
// 				SetCapture(pKrWindow->m_hwnd);
// 				break;
// 			case WM_LBUTTONUP:
// 				pKrWindow->m_bMouseDown = false;
// 				ReleaseCapture();
// 				break;
// 			case WM_MOUSEMOVE:
// 				if (pKrWindow->m_bMouseDown)
// 				{
// 					pKrWindow->m_ptMouse.x = GET_X_LPARAM(lParam);
// 					pKrWindow->m_ptMouse.y = GET_Y_LPARAM(lParam);
// 					pKrWindow->SetXY(pKrWindow->m_ptMouse.x - (pKrWindow->m_ptMouseDown.x - pKrWindow->m_rect.left), pKrWindow->m_ptMouse.y - (pKrWindow->m_ptMouseDown.y - pKrWindow->m_rect.top));
// 				}
// 				break;
// 			case WM_KILLFOCUS:
// 				pKrWindow->m_bMouseDown = false;
// 				break;
// 			case KM_MOUSELEAVE:
// 				pKrWindow->m_bMouseDown = false;
// 				break;
		case WM_LBUTTONDOWN:
			SendMessage(pKrWindow->m_hwnd, WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
			//SetCapture(m_hwnd); 

			break;
		case WM_LBUTTONUP:
			ReleaseCapture();
			break;
// 		case WM_MOUSEMOVE:
// 			if (pKrWindow->m_bMouseDown)
// 			{
// 				GetWindowRect(pKrWindow->m_hwnd, &m_rect);
// 			}
			break;
			default:
				break;
			}
		}
		for (list<KrControl*>::iterator it = m_CtrlList.begin(); it != m_CtrlList.end(); it++)
		{
			(*it)->HandleMessage(Message, wParam, lParam);
		}

		map<UINT, MSGFUNC>::iterator it = m_MsgFuncMap.find(Message);
		if (it != m_MsgFuncMap.end())
		{
			(*it->second)(this, wParam, lParam);
		}
	}

	void KrArea::Draw(Graphics* pGraphics)
	{
		if (!m_bVisible) return;

		for (auto it=m_CtrlList.begin();it!=m_CtrlList.end();it++)
		{
			(*it)->Draw(m_pGraphics);
		}

// 			Image im(L"C:\\Users\\Miles\\Desktop\\vs.JPG", 0);
// 
// 			
// 
// 			pGraphics->DrawImage(&im,0,0,GetWidth(),25);
		BitBlt(pGraphics->GetHDC(), m_rect.left, m_rect.top, GetWidth(), GetHeight(), m_TempDC, 0, 0,SRCCOPY);
	}
	void KrArea::Destroy()
	{
		for (list<KrControl*>::iterator it=m_CtrlList.begin();it!=m_CtrlList.end();it++)
		{
			delete (*it);
		}
	}
}//namespace KrUI
