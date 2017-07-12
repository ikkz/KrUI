#include "KrUIManager.h"
#include "KrWindow.h"

using namespace KrUI;
KrUIManager* pUI = KrUIManager::KrGetpKrUIManager();
/*typedef LRESULT(*MSGFUNC)(void* pObject, WPARAM wParam, LPARAM lParam);*/


/*
LRESULT name(void* pObject, WPARAM wParam, LPARAM lParam)
{
}
*/


LRESULT func1(void* pObject, WPARAM wParam, LPARAM lParam)
{
	MessageBox(((KrControl*)pObject)->KrGetWindow()->KrGetHWND(), L"Êó±ê½øÈë", ((KrControl*)pObject)->KrGetName(), MB_OK);
	return true;
}
LRESULT func2(void* pObject, WPARAM wParam, LPARAM lParam)
{
	MessageBox(((KrControl*)pObject)->KrGetWindow()->KrGetHWND(), L"mouseclick", ((KrControl*)pObject)->KrGetName(), MB_OK);
	KrUIManager::KrGetpKrUIManager()->KrAddWindow(L"haha", 50, 50, 300, 300)->KrShow();
	return true;
}


KrControl* pCtrl;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	pUI->KrInitialize(hInstance);
	KrWindow* pWnd = pUI->KrAddWindow(L"caption", 400, 300, 500, 400);
	pWnd->KrShow();

    pCtrl=pWnd->KrAddControl(KR_CTRL, L"ctrl", 50, 50, 50, 50);
	pCtrl->KrRegMsg(KM_LBTNDOWN, func2);
	//pCtrl->RegMsg(KM_MOUSELEAVE, func2);
	return pUI->KrMessageLoop();
}