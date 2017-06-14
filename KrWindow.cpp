#include<KrWindow.h>


LPCTSTR KrWindow::GetWindowName()
{
	return m_lpWindowName;
}


void KrWindow::SetWindowName(LPCTSTR lpWindowName)
{
	SetWindowText(m_hwnd,lpWindowName);
	m_lpWindowName=lpWindowName;
}


HWND KrWindow::GetHWND()
{
	return m_hwnd;
}


RECT* KrWindow::GetRect()
{
	return &m_rect;
}


void KrWindow::SetRect(RECT* pRect)
{ 
	MoveWindow(m_hwnd,pRect->left,pRect->top,pRect->right-pRect->left,pRect->bottom-pRect->top,TRUE);
	m_rect.left=pRect->left;
	m_rect.right=pRect->right;
	m_rect.top=pRect->top;
	m_rect.bottom=pRect->bottom;
}



void KrWindow::SetStyle(DWORD dwStyle)
{
	m_dwStyle=dwStyle;
	SetWindowLong(hWnd, GWL_STYLE,dwStyle); 
}


bool KrWindow::Create()
{
	HWND hwnd = CreateWindow(ui.GetWindowClassName(),m_lpWindowName,m_dwStyle,
							rect.left,rect.top,
							rect.right-rect.left,rect.bottom-rect.top,
							NULL,NULL,ui.GetHINSTANCE(),NULL);
	if(!hwnd) return false;
	m_hwnd=hwnd;
	return true;
}



int KrWindow::GetX()
{
	return m_rect.left;
}



int KrWindow::GetY()
{
	return m_rect.top;
}



int KrWindow::GetWidth()
{
	return m_rect.right-m_rect.left;
}



int KrWindow::GetHeight()
{
	return m_rect.bottom-m_rect.top;
}


void KrWindow::SetX(int x)
{
	RECT rect;
	rect=*GetRect();
	rect.left=x;
	m_rect.left=x;
	SetRect(&rect);
} 


void KrWindow::SetY(int y)
{
	RECT rect;
	rect=*GetRect();
	rect.top=y;
	m_rect.top=y;
	SetRect(&rect);
} 


void KrWindow::SetWidth(int width)
{
	RECT rect;
	rect=*GetRect();
	rect.right=rect.left+width;
	m_rect.right=rect.right;
	SetRect(&rect);
} 



void KrWindow::SetHeight(int height)
{
	RECT rect;
	rect=*GetRect();
	rect.bottom=rect.top+height;
	m_rect.bottom=rect.bottom;
	SetRect(&rect);
} 


void KrWindow::Show()
{
	ShowWindow(m_hwnd,SW_SHOW);
	m_bVisible=true;
}


void KrWindow::Hide()
{
	ShowWindow(m_hwnd,SW_HIDE);
	m_bVisible=false;
}


bool IsVisible()
{
	return m_bVisible;
}



