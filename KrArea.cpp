#include "KrArea.h"

namespace KrUI
{
	KrControl* KrArea::AddControl(UINT iCtrlType, LPCWSTR lpName, int x, int y, int width, int height)
	{
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		KrControl* pKrCtrl = NULL;
		switch (iCtrlType)
		{
		case KR_CTRL:
			pKrCtrl = new KrControl;
			break;
		case KR_BUTTON:

			break;
		default:
			return NULL;
			break;
		}
		if (!pKrCtrl)return NULL;
		pKrCtrl->SetCtrlType(iCtrlType);
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

	}

	void KrArea::Show()
	{
		KrControl::Show();
		if (m_TempDC==NULL)
		{
			 		m_TempDC = CreateCompatibleDC(GetWindow()->GetTempDC());
			 		m_pGraphics = new Graphics(m_TempDC);
			 		m_hbmp = CreateCompatibleBitmap(m_TempDC,GetWidth(),GetHeight());
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

}//namespace KrUI