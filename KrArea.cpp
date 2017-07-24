#include "KrArea.h"

namespace KrUI
{
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
		case KrCtrlType::Control:
			pKrCtrl = new KrControl;
			break;
		case KrCtrlType::Button:

			break;
		default:
			return NULL;
			break;
		}
		if (!pKrCtrl)return NULL;
		pKrCtrl->SetCtrlType(CtrlType);
		pKrCtrl->SetWindow(NULL);
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
			 		m_hbmp = CreateCompatibleBitmap(m_TempDC,GetWidth(),GetHeight());
					SelectObject(m_TempDC, m_hbmp);
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

	}
}//namespace KrUI