#include "KrUIManager.h"
#include "KrWindow.h"

using namespace KrUI;
KrUIManager* pUI = KrUIManager::GetpKrUIManager();
/*typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);*/


/*
LRESULT name(void* pObject, WPARAM wParam, LPARAM lParam)
{
}
*/


LRESULT func1(void* pObject, WPARAM wParam, LPARAM lParam)
{
	MessageBox(((KrControl*)pObject)->GetWindow()->GetHWND(), L"鼠标进入", ((KrControl*)pObject)->GetName(), MB_OK);
	return true;
}
LRESULT func2(void* pObject, WPARAM wParam, LPARAM lParam)
{
	MessageBox(((KrControl*)pObject)->GetWindow()->GetHWND(), L"鼠标点击", ((KrControl*)pObject)->GetName(), MB_OK);
	KrUIManager::GetpKrUIManager()->AddWindow(L"haha", 50, 50, 300, 300)->Show();
	return true; 
}


KrControl* pCtrl;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	pUI->Initialize(hInstance);
	KrWindow* pWnd = pUI->AddWindow(L"caption", 400, 300, 500, 400);
	pWnd->Show();

    pCtrl=pWnd->AddControl(KR_CTRL, L"ctrl", 50, 50, 50, 50);
	pCtrl->RegMsg(WM_LBUTTONDOWN, func2);

	//pCtrl->RegMsg(KM_MOUSELEAVE, func2);
	return pUI->MessageLoop();
}