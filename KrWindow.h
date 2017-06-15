#include<windows>


class KrWindow
{
	private:
		LPCTSTR m_lpWindowName;//
		HWND    m_hwnd=NULL;//
		RECT    m_rect;// 
		DWORD   m_dwStyle;//
		bool    m_bVisible=false;
	public:
		LPCTSTR GetWindowName();//
		void    SetWindowName(LPCTSTR lpWindowName);//
		HWND    GetHWND();//
		RECT*   GetRect();//
		void    SetRect(RECT* pRect); //
		void    UpdateRect();//
 		void    SetStyle(DWORD dwStyle);//
 		bool    Create();//
		void    Destroy();//仅仅将窗口从内存中清除，不从list中将窗口删除
 		int     GetX();//
 		int     GetY();//
 		int     GetWidth();//
 		int     GetHeight();//
 		void    SetX(int x);//
 		void    SetY(int y);//
 		void    SetWidth(int width);//
 		void    SetHeight(int height);//
 		void    Show();//
 		void    Hide();//
 		bool    IsVisible();//
		bool	IsCreated();//
		
}



