#include<KrWindow.h>


LPCTSTR KrWindow::GetWindowName()
{
	return m_lpWindowName;
}


void KrWindow::SetWindowName(LPCTSTR lpWindowName)
{
	m_lpWindowName=lpWindowName;
}


HWND KrWindow::GetHWND()
{
	return m_hwnd;
}


void KrWindow::SetHWND(HWND hwnd)
{
	m_hwnd=hwnd;
}


RECT* KrWindow::GetRect()
{
	return &m_rect;
}


void KrWindow::SetRect(RECT* pRect)
{
	m_rect.left=pRect->left;
	m_rect.right=pRect->right;
	m_rect.top=pRect->top;
	m_rect.bottom=pRect->bottom;
}




void KrWindow::SetStyle(DWORD dwStyle)
{
	m_dwStyle=dwStyle;
}















