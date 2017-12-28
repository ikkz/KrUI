// KrUI.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "KrUI.h"
#include "source/KrCore.h"
#include <windows.h>

using namespace KrUI;


//typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);


LRESULT wnd_click1(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	cout << "enter" << endl;
#endif // _DEBUG

	return 0;
}
LRESULT wnd_click2(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	cout << "leave" << endl;
#endif // _DEBUG
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	KrUIManager* p = KrUI::KrUIManager::GetpKrUIManager();
	if (!p->Initialize(hInstance))
	{
		return 0;
	}

	KrWindow* pw = p->AddWindow(L"hhh", 300,300, 500, 300, WS_CAPTION | WS_BORDER | WS_VISIBLE | WS_OVERLAPPED);
	pw->Show();
	KrButton* pb = dynamic_cast<KrButton*>(pw->AddControl(KrButton_t, L"hhh", 0, 0, 250, 300));
	pb->RegMsg(KM_MOUSELEAVE, wnd_click2);
	pb->RegMsg(KM_MOUSEENTER, wnd_click1);
	//pw->RemoveMsgProc(wnd_click1);
	return p->MessageLoop();
}
