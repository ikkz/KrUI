#ifndef _KR_EDIT_H
#define  _KR_EDIT_H
#pragma once

#include "KrCore.h"
#include "KrUIBase.h"
#include <string>


namespace KrUI
{
	class KrEdit :public KrUIBase
	{
	public:
		KrEdit();
		void SetText(std::wstring str);
		std::wstring GetText();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		unsigned int GetCursorPosByX(unsigned int x);
		unsigned int GetXByCursorPos(unsigned int CursorPos);
		unsigned int GetStrHeight();
		virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
		Gdiplus::SizeF GetTextBounds(std::wstring strText);
		void StringChange();
	protected:
		std::wstring m_strText;
		virtual void Update();
		Mouse_Status m_MouseStatus;
		bool m_bShowCursor;
		unsigned int m_Margin;
		unsigned int m_Time;
		unsigned int m_SelectTextPosFirst;
		unsigned int m_SelectTextPosSecond;
		std::vector<unsigned int> m_StringLength;
	};
}
#endif
