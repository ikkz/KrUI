#include<windows>


class KrWindow
{
	private:
		LPCTSTR m_lpWindowName;//窗口名称 
		HWND m_hwnd=NULL;//窗口句柄 
		RECT m_rect;//窗口矩形 
		DWORD m_dwStyle;//窗口风格 
	public:
		LPCTSTR GetWindowName();//获取窗口名称 
		void SetWindowName(LPCTSTR lpWindowName);//设置窗口名称 
		HWND GetHWND();//获取窗口句柄 
		RECT* GetRect();//获取窗口矩形 
		void SetRect(RECT* pRect); //设置窗口矩形 
 		void SetStyle(DWORD dwStyle);//设置窗口风格 
 		bool Create();//创建真实窗口 
 		int GetX();//
 		int GetY();//
 		int GetWidth();//
 		int GetHeight;//
 		void SetX(int x);//
 		void SetY(int y);//
 		void SetWidth(int width);//
 		void SetHeight(int height);//
}



