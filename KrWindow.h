#include<windows>


class KrWindow
{
	private:
		LPCTSTR m_lpWindowName;
		HWND m_hwnd;
		RECT m_rect;
		DWORD m_dwStyle;
	public:
		LPCTSTR GetWindowName();//
		void SetWindowName(LPCTSTR lpWindowName);//
		HWND GetHWND();//
		void SetHWND(HWND hwnd);//
		RECT* GetRect();//
		void SetRect(RECT* pRect); //

 		void SetStyle(DWORD dwStyle);//
}



