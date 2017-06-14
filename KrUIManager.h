#include<list>
#include<windows>



class KrUIManager
{
	public:
		bool Initialize(HINSTANCE hInstance);//
		KrWindow* CreateWindow(LPCTSTR lpWindowName,int x,int y,int width,int height,DWORD dwStyle);//
		KrWindow* CreateWindow(LPCTSTR lpWindowName,int x,int y,int width,int height);//
		LPCTSTR GetWindowClassName();//
		
		
	private:
		WNDCLASSEX m_wc; 
		LPCTSTR m_lpWindowClassName="KrUI";
		HINSTANCE m_hInstance;
		list<KrWindow*> m_WndList;
	
}


