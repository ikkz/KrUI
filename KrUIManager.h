#include<list>
#include<windows>



class KrUIManager
{
	public:
		bool      Initialize(HINSTANCE hInstance);//ui管理器初始化 
		KrWindow* AddWindow(LPCTSTR lpWindowName,int x,int y,int width,int height,DWORD dwStyle);//添加窗口 
		KrWindow* AddWindow(LPCTSTR lpWindowName,int x,int y,int width,int height);//添加窗口 
		LPCTSTR   GetWindowClassName();//获取窗口类名 
		HINSTANCE GetHINSTANCE();//获取程序实例 
		void      CreateWindow(); 
		void      MsgLoop();
	private:
		WNDCLASSEX      m_wc; //窗口类 
		LPCTSTR         m_lpWindowClassName="KrUI";//类名 
		HINSTANCE       m_hInstance;//实例句柄 
		list<KrWindow*> m_WndList;//窗口列表 
	
}


