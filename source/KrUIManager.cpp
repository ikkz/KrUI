#include "KrCore.h"

namespace KrUI
{

	KrUIManager* KrUIManager::m_pKrUIManager = NULL;

	//把消息传递给UIManager统一处理分发
	LRESULT CALLBACK KrUIManager::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
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
#ifdef _DEBUG
		//打开控制台
		AllocConsole();
		freopen("conin$", "r+t", stdin);
		freopen("conout$", "w+t", stdout);

#endif
		m_lpWindowClassName = L"KrUI";
		m_hInstance = hInstance;
		WNDCLASSEX wcex;
		memset(&wcex, 0, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_hInstance;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
		wcex.lpszClassName = GetWindowClassName();
		wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

		SetTimer(NULL, TIMER_ID, TIMER_INTERVAL, TimerProc);
		Gdiplus::GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);

		if (!RegisterClassEx(&wcex))
			return false;
		return true;
		//TODO
	}



	KrWindow* KrUIManager::AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height)
	{
		return AddWindow(new KrWindow, lpWindowName, x, y, width, height);
	}

	KrWindow* KrUIManager::AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height)
	{
		if (!pKrWindow) return nullptr;
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		pKrWindow->SetRect(&rect);
		pKrWindow->SetWindowName(lpWindowName);
		HWND hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, KrUIManager::GetpKrUIManager()->GetWindowClassName(), lpWindowName,
			WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_MINIMIZEBOX, rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, m_hInstance, nullptr);
		//SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER | WS_MINIMIZEBOX);
		pKrWindow->SetHWND(hwnd);
		pKrWindow->SetWindowName(lpWindowName);
		m_WndVec.push_back(pKrWindow);
		pKrWindow->CallMsgProc(KM_CREATE, NULL, NULL);
		return pKrWindow;
	}

	LPCWSTR KrUIManager::GetWindowClassName()
	{
		return m_lpWindowClassName;
	}


	HINSTANCE KrUIManager::GetHINSTANCE()
	{
		return m_hInstance;
	}


	int  KrUIManager::MessageLoop()
	{
		while (GetMessage(&m_msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		return m_msg.wParam;
	}


	LRESULT   KrUIManager::HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		for (std::vector<KrWindow*>::iterator it = m_WndVec.begin(); it != m_WndVec.end(); ++it)
		{
			if (hwnd == (*it)->GetHWND())
			{
				return (*it)->HandleMessage(Message, wParam, lParam);
			}
		}
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}

	KrWindow* KrUIManager::GetpKrWindow(HWND hwnd)
	{
		for (std::vector<KrWindow*>::iterator it = m_WndVec.begin(); it != m_WndVec.end(); ++it)
		{
			if ((*it)->GetHWND() == hwnd)
				return (*it);
		}
		return NULL;
	}


	int KrUIManager::GetWindowNum()
	{
		return m_WndVec.size();
	}


	void KrUIManager::DeleteWindow(KrWindow* pKrWindow)
	{
		auto it = m_WndVec.begin();
		while (it != m_WndVec.end())
		{
			if ((*it) == pKrWindow)
			{
				it = m_WndVec.erase(it);
				SendMessage(pKrWindow->GetHWND(), WM_CLOSE, NULL, NULL);
				pKrWindow = nullptr;
				//delete pKrWindow;
			}
			else
			{
				++it;
			}
		}
		if (GetWindowNum() == 0)
		{
			//关闭控制台
#ifdef _DEBUG
			fclose(stdin);
			fclose(stdout);
#endif
			PostQuitMessage(0);
		}
		//todo
	}


	KrUIManager::~KrUIManager()
	{
		KillTimer(NULL, TIMER_ID);
		Gdiplus::GdiplusShutdown(m_pGdiToken);
		//todo
	}
	//typedef VOID(CALLBACK* TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
	void  KrUIManager::TimerProc(HWND hWnd, UINT nMsg, UINT_PTR nTimerid, DWORD dwTime)
	{
		for (auto p : GetpKrUIManager()->m_WndVec)
		{
			p->Update();
			//if (p->IsVisible())SendMessage(p->GetHWND(), WM_PAINT, NULL, NULL);
		}
	}

}// !KrUI