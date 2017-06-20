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
	MessageBox(((KrControl*)pObject)->GetWindow()->GetHWND(), L"鼠标JINGRUQIAN", ((KrControl*)pObject)->GetName(), MB_OK);
	return true;
}


KrControl* pCtrl;


LRESULT func3(void* pObject, WPARAM wParam, LPARAM lParam)
{
	Rectangle(pCtrl->GetWindow()->GetKrDC(), pCtrl->GetRect()->left, pCtrl->GetRect()->top, pCtrl->GetRect()->right, pCtrl->GetRect()->bottom);
	return true;
}



LRESULT func4(void* pObject, WPARAM wParam, LPARAM lParam)
{
	Rectangle(pCtrl->GetWindow()->GetKrDC(), 100,50,50,50);
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	pUI->Initialize(hInstance);
	KrWindow* pWnd = pUI->AddWindow(L"caption", CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT);
	pWnd->Show();

    pCtrl=pWnd->AddControl(KR_CTRL, L"ctrl", 50, 50, 50, 50);
	pWnd->RegMsg(WM_LBUTTONDOWN, func3);
	pCtrl->RegMsg(KM_MOUSEENTER, func1);
	pCtrl->RegMsg(KM_BEFORE_MOUSEENTER, func2);
	//pCtrl->RegMsg(KM_MOUSELEAVE, func2);
	return pUI->MessageLoop();
}