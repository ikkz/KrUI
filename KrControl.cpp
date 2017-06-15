#include<KrControl>


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
    Update();
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
	Update();
} 


void KrWindow::SetY(int y)
{
	int height=GetHeight();
	m_rect.top=y;
	m_rect.bottom=y+height;
	Update();
} 


void KrWindow::SetWidth(int width)
{
	m_rect.right=m_rect.left+width;
	Update();
} 



void KrWindow::SetHeight(int height)
{
	m_rect.bottom=m_rect.top+height;
	Update();
} 
