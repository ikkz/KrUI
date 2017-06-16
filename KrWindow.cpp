#include<windows.h>
#include"KrUIManager.h"
#include"KrWindow.h"



LPCSTR KrWindow::GetWindowName()
{
	return m_lpWindowName;
}

void KrWindow::SetWindowName(LPCSTR lpWindowName)
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
	m_rect.left=pRect->left;
	m_rect.right=pRect->right;
	m_rect.top=pRect->top;
	m_rect.bottom=pRect->bottom;
	UpdateRect();
}

void KrWindow::UpdateRect()
{
	MoveWindow(m_hwnd,m_rect.left,m_rect.top,m_rect.right-m_rect.left,m_rect.bottom-m_rect.top,TRUE);	
}

void KrWindow::SetStyle(DWORD dwStyle)
{
	m_dwStyle=dwStyle;
	SetWindowLong(m_hwnd, GWL_STYLE,dwStyle); 
}


bool KrWindow::Create()
{
	HWND hwnd = CreateWindow(KrUIManager::GetpKrUIManager()->GetWindowClassName(),m_lpWindowName,m_dwStyle,
							m_rect.left,m_rect.top,
							m_rect.right-m_rect.left,m_rect.bottom-m_rect.top,
							NULL,NULL,KrUIManager::GetpKrUIManager()->GetHINSTANCE(),NULL);
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
	int width=GetWidth();
	m_rect.left=x;
	m_rect.right=x+width;
	UpdateRect();
} 


void KrWindow::SetY(int y)
{
	int height=GetHeight();
	m_rect.top=y;
	m_rect.bottom=y+height;
	UpdateRect();
} 


void KrWindow::SetWidth(int width)
{
	m_rect.right=m_rect.left+width;
	UpdateRect();
} 



void KrWindow::SetHeight(int height)
{
	m_rect.bottom=m_rect.top+height;
	UpdateRect();
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


bool KrWindow::IsVisible()
{
	return m_bVisible;
}


bool KrWindow::IsCreated()
{
	return m_hwnd;
}


void KrWindow::Destroy()
{
	SendMessage(m_hwnd,WM_CLOSE,0,0);
	m_hwnd=NULL;
}





