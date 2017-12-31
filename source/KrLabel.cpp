#include "KrLabel.h"

namespace KrUI
{

	KrLabel::KrLabel(Color bgcolor)
	{
		m_MouseDownColor = bgcolor;
		m_MouseHoverColor = bgcolor;
		m_MouseLeaveColor = bgcolor;
		m_FontColor = Color(0, 0, 0);
		m_StringFormat.SetAlignment(StringAlignmentNear);
		m_StringFormat.SetAlignment(StringAlignmentNear);
	}


}// !namespace KrUI