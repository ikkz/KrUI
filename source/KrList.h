#pragma once
#ifndef _KR_LIST_H_
#define _KR_LIST_H_
#include "KrCore.h"
#include "KrUIBase.h"
#include <string>
#include <vector>
namespace KrUI
{

	class KrList : public KrUIBase
	{
	public:
		KrList();
		int AddItem(std::wstring wStr, int nIndex = -1, unsigned int nHeight = 35);
		virtual void Update();
		virtual LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	private:
		struct KrListItem
		{
			unsigned int m_Index;
			std::wstring m_ItemName;
			unsigned int m_Height;
			KrListItem(std::wstring wStr, unsigned int Index, unsigned int Height) : m_ItemName(wStr), m_Index(Index), m_Height(Height) {}
		};
		unsigned int m_Position;
		std::vector<KrListItem> m_ListItems;
		unsigned int m_TotalHeight;
		unsigned int m_MouseWheelDelta;
	};
}

#endif
