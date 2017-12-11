// KrUI.cpp : 定义应用程序的入口点。
//

#include "KrUI.h"
#include "KrCore.h"
#include <windows.h>

using namespace KrUI;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	KrUIManager* p=KrUI::KrUIManager::GetpKrUIManager();
	p->Initialize(hInstance);
	KrWindow* pw = p->AddWindow(L"hhh", 0, 0, 500, 300);
	pw->Show();
	p->AddWindow(L"hhh", 0, 0, 500, 300)->Show();
	return p->MessageLoop();
}