#include "KrUIManager.h"
#include "KrWindow.h"

using namespace KrUI;
KrUIManager* pUI = KrUIManager::GetpKrUIManager();
/*typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);*/

LRESULT OnBtnUP(void* pObject, WPARAM wParam, LPARAM lParam)
{
	((KrWindow*)pObject)->Destroy();
	return 0;
}

//入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	pUI->Initialize(hInstance);//初始化
	KrWindow* pWnd = pUI->AddWindow(L"caption", 400, 300, 500, 400);//添加窗口
	pWnd->Show();//显示窗口
	KrControl* pA=pWnd->AddControl(Area, L"body", 0, 0, pWnd->GetWidth(), pWnd->GetHeight());
	pA->RegMsg(WM_LBUTTONDOWN, OnBtnUP);
	return pUI->MessageLoop();//进入消息循环
}