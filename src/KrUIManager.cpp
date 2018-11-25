#include "KrCore.h"

namespace KrUI
{

	KrUIManager* KrUIManager::m_pKrUIManager = nullptr;

	//把消息传递给UIManager统一处理分发
	LRESULT CALLBACK KrUIManager::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return KrUIManager::Instance()->HandleMessage(hwnd, Message, wParam, lParam);
	}

	KrUIManager* KrUIManager::Instance()
	{

		if (m_pKrUIManager == nullptr)
			m_pKrUIManager = new KrUIManager();
		return m_pKrUIManager;
	}




	bool KrUIManager::Initialize(HINSTANCE hInstance)
	{
		setlocale(LC_ALL, "chs");
#ifdef _DEBUG
		//打开控制台
		AllocConsole();
		freopen("conin$", "r+t", stdin);
		freopen("conout$", "w+t", stdout);
		GetLogger().add_output(std::cout);
#endif
		m_lpWindowClassName = L"KrUI";
		m_hInstance = hInstance;
		WNDCLASSEXW wcex;
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

		//SetTimer(NULL, TIMER_ID, TIMER_INTERVAL, TimerProc);
		Gdiplus::GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, nullptr);
		KrUIManager::Instance()->GetLogger().set_loglevel(cl::LogLevel::Information);
		KRLOG << "初始化GDI+";
		if (!RegisterClassExW(&wcex))
			return false;
		KRLOG << "注册窗口类成功";
		return true;
		//TODO
	}


	KrWindow* KrUIManager::AddWindow(const std::wstring& name, int x, int y, int width, int height, DWORD dwStyle)
	{
		KrWindow* pKrWindow = AddWindow(new KrWindow, name, x, y, width, height, dwStyle);
		pKrWindow->SetCaptionHeight(0);
		return pKrWindow;
	}

	KrWindow* KrUIManager::AddWindow(const std::wstring& name, int x, int y, int width, int height)
	{
		return AddWindow(new KrWindow, name, x, y, width, height);
	}
	KrWindow* KrUIManager::AddWindow(KrWindow* pKrWindow, const std::wstring& name, int x, int y, int width, int height)
	{
		return AddWindow(pKrWindow, name, x, y, width, height, WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_MINIMIZEBOX);
	}

	KrWindow* KrUIManager::AddWindow(KrWindow* pKrWindow, const std::wstring& name, int x, int y, int width, int height, DWORD dwStyle)
	{
		if (!pKrWindow) return nullptr;
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		pKrWindow->SetRect(&rect);
		pKrWindow->SetName(name);
		HWND hwnd = CreateWindowExW(WS_EX_WINDOWEDGE, KrUIManager::Instance()->GetWindowClassName(), pKrWindow->GetName().c_str(),
			dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, m_hInstance, nullptr);
		pKrWindow->SetHWND(hwnd);
		m_WndVec.push_back(pKrWindow);
		pKrWindow->CallMsgProc(KM_CREATE, NULL, NULL);
		KRLOG << "添加窗口，name" << WideStringToString(name) << ",x:" << x << ",y:" << y << ",width:" << width << ",height:" << height;
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


	int KrUIManager::MessageLoop()
	{
		while (GetMessage(&m_msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		return static_cast<int>(m_msg.wParam);
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
		return nullptr;
	}

	cl::Logger & KrUIManager::GetLogger()
	{
		return m_Logger;
	}


	int KrUIManager::GetWindowNum() const
	{
		return static_cast<int>(m_WndVec.size());
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
		for (auto p : Instance()->m_WndVec)
		{
			if (p != nullptr)p->Update();
			//if (p->IsVisible())SendMessage(p->GetHWND(), WM_PAINT, NULL, NULL);
		}
	}

}// !KrUI