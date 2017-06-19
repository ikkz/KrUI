#include"KrControl.h"
#include<windows.h>


namespace KrUI{

	RECT* KrControl::GetRect()
	{
		return &m_rect;
	}


	void KrControl::SetRect(RECT* pRect)
	{
		m_rect.left = pRect->left;
		m_rect.right = pRect->right;
		m_rect.top = pRect->top;
		m_rect.bottom = pRect->bottom;
		Update();
	}



	int KrControl::GetX()
	{
		return m_rect.left;
	}



	int KrControl::GetY()
	{
		return m_rect.top;
	}



	int KrControl::GetWidth()
	{
		return m_rect.right - m_rect.left;
	}



	int KrControl::GetHeight()
	{
		return m_rect.bottom - m_rect.top;
	}


	void KrControl::SetX(int x)
	{
		int width = GetWidth();
		m_rect.left = x;
		m_rect.right = x + width;
		Update();
	}


	void KrControl::SetY(int y)
	{
		int height = GetHeight();
		m_rect.top = y;
		m_rect.bottom = y + height;
		Update();
	}


	void KrControl::SetWidth(int width)
	{
		m_rect.right = m_rect.left + width;
		Update();
	}



	void KrControl::SetHeight(int height)
	{
		m_rect.bottom = m_rect.top + height;
		Update();
	}


	void    KrControl::Update()
	{

	}



}