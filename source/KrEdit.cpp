#include "KrEdit.h"

namespace KrUI
{
	void KrEdit::UpdateDc()
	{
		//画背景颜色:
		m_pGraphics->FillRectangle(&SolidBrush(m_BgColor), 0, 0, GetWidth(), GetHeight());
		//画文字内容:
			//TODO。。。

		//画边框:
		if ((m_bMouseIn && !m_bMouseDown) && m_ButtonStatus != mouse_hover){
			m_ButtonStatus = mouse_hover;
		}else if (((!m_bMouseDown) && (!m_bMouseIn)) && m_ButtonStatus != mouse_leave){
			m_ButtonStatus = mouse_leave;
		}else if (m_bMouseDown && (m_ButtonStatus != mouse_down)){
			m_ButtonStatus = mouse_down;
		}
		m_pGraphics->DrawRectangle(&Pen((m_ButtonStatus==mouse_leave?m_BorderColor:Color(21,131,221)/*这是鼠标移动到文本框上时的颜色*/)), 0, 0, GetWidth() - 1, GetHeight() - 1);
		//画到窗口Bmp上
		m_pKrWindow->GetBmpGraphics()->DrawImage(m_pBmp, GetX(), GetY(), GetWidth(), GetHeight());
	}
	KrEdit::KrEdit()
	{
		m_BgColor = Color::White;
		m_BorderColor = Color(170, 170, 170);
	}
}// !KrUI