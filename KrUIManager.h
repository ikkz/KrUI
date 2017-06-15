#include<list>
#include<windows>
#include<KrWindow>


class KrUIManager
{
	public:
		static KrUIManager* GetpKrUIManager();
		bool      Initialize(HINSTANCE hInstance);//
		KrWindow* AddWindow(LPCTSTR lpWindowName,int x,int y,int width,int height,DWORD dwStyle);// 
		KrWindow* AddWindow(LPCTSTR lpWindowName,int x,int y,int width,int height);//
		LPCTSTR   GetWindowClassName();//
		HINSTANCE GetHINSTANCE();//
		int       MessageLoop();//
		LRESULT   HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);//处理消息
	private:
		KrUIManager(){}
		static KrUIManager* m_pKrUIManager;
		WNDCLASSEX      m_wc; //
		LPCTSTR         m_lpWindowClassName="KrUI";//
		HINSTANCE       m_hInstance;//
		list<KrWindow*> m_WndList;//
	
		
}


enum MouseStatus{out,up,down};