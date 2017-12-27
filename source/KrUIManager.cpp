#include "KrCore.h"

namespace KrUI
{

	KrUIManager* KrUIManager::m_pKrUIManager = NULL;

	//把消息传递给UIManager统一处理分发
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
		if (!RegisterClassEx(&wcex))
		{
			return false;
		}
		return true;
		//TODO
	}


	KrWindow* KrUIManager::AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height)
	{

		return AddWindow(lpWindowName, x, y, width, height, WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER/*WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS | WS_THICKFRAME | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX*/);
	}


	KrWindow* KrUIManager::AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle)
	{
		KrWindow* pKrWindow = new KrWindow;
		if (!pKrWindow) return NULL;
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		pKrWindow->SetRect(&rect);
		pKrWindow->SetWindowName(lpWindowName);
		HWND hwnd = CreateWindow(KrUIManager::GetpKrUIManager()->GetWindowClassName(), lpWindowName, dwStyle, rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, m_hInstance, nullptr);
		SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER);
		pKrWindow->SetHWND(hwnd);
		pKrWindow->SetWindowName(lpWindowName);
		pKrWindow->SetDc(GetDC(hwnd));
		m_WndVec.push_back(pKrWindow);
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
		while (GetMessage(&m_msg, NULL, 0, 0) != 0)
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		return m_msg.wParam;
	}


	LRESULT   KrUIManager::HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{

		for (vector<KrWindow*>::iterator it = m_WndVec.begin(); it != m_WndVec.end(); ++it)
		{
			if (hwnd == (*it)->GetHWND())
			{
				return (*it)->HandleMessage(Message, wParam, lParam);
			}
		}
		return TRUE;
	}

	KrWindow* KrUIManager::GetpKrWindow(HWND hwnd)
	{
		for (vector<KrWindow*>::iterator it = m_WndVec.begin(); it != m_WndVec.end(); ++it)
		{
			if ((*it)->GetHWND() == hwnd)
			{
				return (*it);
			}
		}
		return NULL;
	}


	int KrUIManager::GetWindowNum()
	{
		return m_WndVec.size();
	}


	void KrUIManager::DeleteWindow(KrWindow* pKrWindow)
	{
		auto result = std::find(m_WndVec.begin(), m_WndVec.end(), pKrWindow);
		if (result != m_WndVec.end())
		{
			m_WndVec.erase(result);
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
		//todo
	}



}// !KrUI