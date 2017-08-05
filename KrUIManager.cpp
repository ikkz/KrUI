#include"KrUIManager.h"

namespace KrUI{
	
	KrUIManager* KrUIManager::m_pKrUIManager = NULL;


	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;


	LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return  KrUIManager::GetpKrUIManager()->HandleMessage(hwnd, Message, wParam, lParam);
	}


	 KrUIManager* KrUIManager::GetpKrUIManager()
	{
		if (m_pKrUIManager == NULL)
			m_pKrUIManager = new KrUIManager();
		return m_pKrUIManager;
	}


	bool      KrUIManager::Initialize(HINSTANCE hInstance)
	{
		//注册窗口类
		m_hInstance = hInstance;
		memset(&m_wc, 0, sizeof(m_wc));
		m_wc.cbSize = sizeof(WNDCLASSEX);
		m_wc.lpfnWndProc = WndProc;
		m_wc.hInstance = m_hInstance;
		m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_wc.hbrBackground =GetStockBrush(WHITE_BRUSH);
		m_wc.lpszClassName = GetWindowClassName();
		m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		m_wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		if (!RegisterClassEx(&m_wc))
		{
			return false;
		}

		//初始化gdi+
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		return true;
		//TODO
	}


	KrWindow* KrUIManager::AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height)
	{
		KrWindow* pKrWindow = new KrWindow;
		if (!pKrWindow) return false;
		pKrWindow->SetWindowName(lpWindowName);
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		pKrWindow->SetRect(&rect);
		pKrWindow->SetStyle(NULL);
		pKrWindow->Create();
		LONG_PTR style = GetWindowLongPtr(pKrWindow->GetHWND(), GWL_STYLE);
		style = style&~WS_CAPTION&~WS_SYSMENU&~WS_SIZEBOX&~WS_BORDER;
		SetWindowLongPtr(pKrWindow->GetHWND(), GWL_STYLE,style);
		m_WndList.push_back(pKrWindow);
		return pKrWindow;
	}


	LPCTSTR   KrUIManager::GetWindowClassName()
	{
		return m_lpWindowClassName;
	}


	HINSTANCE KrUIManager::GetHINSTANCE()
	{
		return m_hInstance;
	}


	int  KrUIManager::MessageLoop()
	{
		while (GetMessage(&m_msg,NULL,0,0)!=0)
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		GdiplusShutdown(gdiplusToken);
		return m_msg.wParam;
	}


	LRESULT   KrUIManager::HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{

		for (list<KrWindow*>::iterator it = m_WndList.begin(); it != m_WndList.end(); it++)
		{
			if (hwnd==(*it)->GetHWND())
			{
				return (*it)->HandleMessage(Message, wParam, lParam);
			}
		}
		return TRUE;
	}


	int KrUIManager::GetWindowNum()
	{
		return m_WndList.size();
	}


	void KrUIManager::DeleteWindow(KrWindow* pKrWindow)
	{
		m_WndList.remove(pKrWindow);
	}


	KrUIManager::~KrUIManager()
	{
// 		for (list<KrWindow*>::iterator it = m_WndList.begin(); it != m_WndList.end(); it++)
// 		{
// 			(*it)->Destroy();
// 			delete (*it);
// 		}
	}


















}