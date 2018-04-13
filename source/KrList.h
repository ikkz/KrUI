/*********************************************************
Author:MilesYang
Mail:1961464399@qq.com
CurrentTime:2018-4-13
FileName:KrList.h
*********************************************************/

#pragma once
#ifndef _KR_LIST_H_
#define _KR_LIST_H_
//#include "KrCore.h"
#include "KrUIBase.h"
#include <string>
#include <vector>
namespace KrUI
{
	struct KrListItem
	{
		unsigned int m_Index;
		std::wstring m_ItemName;
		unsigned int m_Height;
		bool m_bSelected;
		KrListItem(std::wstring wStr, unsigned int Index, unsigned int Height) : m_ItemName(wStr), m_Index(Index), m_Height(Height), m_bSelected(false) {}
	};

	class KrList : public KrUIBase
	{
	public:
		KrList();
		int AddItem(std::wstring wStr, int nIndex = -1, unsigned int nHeight = 35);
		//删除所有为wStr的项
		int RemoveItem(std::wstring wStr);
		bool RemoveItem(int nIndex);
		virtual void DrawItem(unsigned int item_index, int start_position);
		//未选中时return KrListItem{ L"",0,0 }
		void SetMultiSelectable(bool bMultiSelectable);
		//KrListItem GetSelectedItem();
		std::vector<KrListItem> GetSelectedItems();
		virtual void Update();
		virtual void ItemChange();
		void SelectAllItems(bool b);
		virtual LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		void SetPosition(int position);
	protected:
		bool m_bMultiSelectable;
		unsigned int m_Position;
		std::vector<KrListItem> m_ListItems;
		unsigned int m_TotalHeight;
		unsigned int m_MouseWheelDelta;
		Gdiplus::Rect m_ScrollBarRect;
		unsigned int m_MouseHoverItem;
		int m_MouseDownOnScrollBarPos;
	};
}

#endif
