#include "KrUIManager.h"
#include "KrWindow.h"

using namespace KrUI;
KrUIManager* pUI = KrUIManager::GetpKrUIManager();
/*typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);*/

LRESULT OnBtnUP(void* pObject, WPARAM wParam, LPARAM lParam)
{
	::MessageBox(NULL, L"LBTNUP", L"MsgGetted", MB_OK);//
	return 0;
}

//入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	pUI->Initialize(hInstance);//初始化
	KrWindow* pWnd = pUI->AddWindow(L"caption", 400, 300, 500, 400);//添加窗口
	pWnd->Show();//显示窗口
	pWnd->RegMsg(WM_LBUTTONUP, OnBtnUP);//消息注册
	return pUI->MessageLoop();//进入消息循环
}