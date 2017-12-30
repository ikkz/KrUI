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
	cout << "button enter" << endl;
#endif // _DEBUG

	return 0;
}
LRESULT wnd_click2(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	cout << "button down" << endl;
#endif // _DEBUG
	MessageBox(NULL, L"button click", L"tip", MB_OK);
	return 0;
}

LRESULT wnd_click4(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	cout << "button leave" << endl;
#endif // _DEBUG

	return 0;
}
LRESULT wnd_click3(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam)
{
	KrButton* pb = dynamic_cast<KrButton*>(pKrMessageHandler);
	pb->SetX(pb->GetX() + 20);

#ifdef _DEBUG
	cout << "button up" << endl;
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

	KrWindow* pw = p->AddWindow(L"hhh",50, 300, 500, 300);
	pw->Show();

	KrButton* pb = dynamic_cast<KrButton*>(pw->AddControl(KrButton_t, L"按钮", 60, 60, 100, 25));
	pb->RegMsg(KM_LBTNUP, wnd_click2);
	pb->RegMsg(KM_MOUSEENTER, wnd_click1);
	pb->RegMsg(KM_MOUSELEAVE, wnd_click4);
	pb->RegMsg(KM_LBTNUP, wnd_click3);
	pb->Show();
	KrButton* pb1 = dynamic_cast<KrButton*>(pw->AddControl(KrButton_t, L"按钮2", 200, 60, 100, 25));
	pb1->RegMsg(KM_LBTNUP, wnd_click2);
	pb1->RegMsg(KM_MOUSEENTER, wnd_click1);
	pb1->RegMsg(KM_MOUSELEAVE, wnd_click4);
	pb1->RegMsg(KM_LBTNUP, wnd_click3);
	pb1->Show();
	//pw->RemoveMsgProc(wnd_click1);
	return p->MessageLoop();
}
