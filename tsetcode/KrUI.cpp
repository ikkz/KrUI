#include "source/KrCore.h"
KrUI::KrUIManager* pUM = KrUI::KrUIManager::GetpKrUIManager();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!pUM->Initialize(hInstance)) return 0;//出屎化
	KrUI::KrWindow* pWnd = pUM->AddWindow(L"这不是一个窗口", 100, 100, 350, 200);//添加窗口
	KrUI::KrButton* pBtn = dynamic_cast<KrUI::KrButton*>(pWnd->AddControl(KrUI::KrUIType::KrButton_t, L"这才不是按钮", 100, 50, 150, 25));
	KrUI::KrEdit* pEdit = dynamic_cast<KrUI::KrEdit*>(pWnd->AddControl(KrUI::KrUIType::KrEdit_t, L"一二三四五六七八九十", 100, 100, 200, 25));
	KrUI::KrProgressBar* pProgressBar = dynamic_cast<KrUI::KrProgressBar*>(pWnd->AddControl(KrUI::KrUIType::KrProgressBar_t, L"", 100, 150, 200, 20));
	pProgressBar->SetPercentage(100);
	return pUM->MessageLoop();
}