#include"KrUIManager.h"

namespace KrUI{

	KrUIManager* KrUIManager::m_pKrUIManager = NULL;


	LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return  KrUIManager::KrGetpKrUIManager()->KrHandleMessage(hwnd, Message, wParam, lParam);
	}


	 KrUIManager* KrUIManager::KrGetpKrUIManager()
	{
		if (m_pKrUIManager == NULL)
			m_pKrUIManager = new KrUIManager();
		return m_pKrUIManager;
	}


	bool      KrUIManager::KrInitialize(HINSTANCE hInstance)
	{
		
		m_hInstance = hInstance;
		memset(&m_wc, 0, sizeof(m_wc));
		m_wc.cbSize = sizeof(WNDCLASSEX);
		m_wc.lpfnWndProc = WndProc;
		m_wc.hInstance = m_hInstance;
		m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		m_wc.lpszClassName = KrGetWindowClassName();
		m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		m_wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&m_wc))
		{
			return false;
		}

		return true;
		//TODO
	}


	KrWindow* KrUIManager::KrAddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height)
	{
		KrWindow* pKrWindow = new KrWindow;
		if (!pKrWindow) return false;
		pKrWindow->KrSetWindowName(lpWindowName);
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		pKrWindow->KrSetRect(&rect);
		pKrWindow->KrSetStyle(NULL);
		pKrWindow->KrCreate();
		LONG_PTR style = GetWindowLongPtr(pKrWindow->KrGetHWND(), GWL_STYLE);
		style = style&~WS_CAPTION&~WS_SYSMENU&~WS_SIZEBOX&~WS_BORDER;
		SetWindowLongPtr(pKrWindow->KrGetHWND(), GWL_STYLE,style);
		m_WndList.push_back(pKrWindow);
		if (m_WndList.size()==1)
		{
			_beginthread(PaintThread, NULL, NULL);
		}
		return pKrWindow;
	}


	LPCTSTR   KrUIManager::KrGetWindowClassName()
	{
		return m_lpWindowClassName;
	}


	HINSTANCE KrUIManager::KrGetHINSTANCE()
	{
		return m_hInstance;
	}


	int  KrUIManager::KrMessageLoop()
	{
		while (GetMessage(&m_msg,NULL,0,0)!=0)
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		return m_msg.wParam;
	}


	LRESULT   KrUIManager::KrHandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		
		for (list<KrWindow*>::iterator it = m_WndList.begin(); it != m_WndList.end(); it++)
		{
			if (hwnd==(*it)->KrGetHWND())
			{
				return (*it)->KrHandleMessage(Message, wParam, lParam);
			}
		}
		return TRUE;
	}


	int KrUIManager::KrGetWindowNum()
	{
		return m_WndList.size();
	}


	void KrUIManager::KrDeleteWindow(KrWindow* pKrWindow)
	{
		m_WndList.remove(pKrWindow);
	}


	KrUIManager::~KrUIManager()
	{
		for (list<KrWindow*>::iterator it = m_WndList.begin(); it != m_WndList.end(); it++)
		{
			(*it)->KrDestroy(false);
			delete (*it);
		}
	}


















}