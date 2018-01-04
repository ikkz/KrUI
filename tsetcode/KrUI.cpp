#include "source/KrCore.h"
using namespace KrUI;
KrUIManager* p = KrUI::KrUIManager::GetpKrUIManager();
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!p->Initialize(hInstance))return 0;
	KrWindow* pw = p->AddWindow(L"这不是一个窗口", 100, 100, 350, 200);
	pw->Show();
	KrButton* pb = dynamic_cast<KrButton*>(pw->AddControl(KrButton_t, L"这才不是按钮", 100, 50, 150, 25));
	pb->Show();
	KrEdit* pb1 = dynamic_cast<KrEdit*>(pw->AddControl(KrEdit_t, L"瞎jb填反正也不显示", 100, 100, 150, 25));
	pb1->SetText(L"这也不是文本框");
	pb1->Show();
	KrLabel* pl1 = dynamic_cast<KrLabel*>(pw->AddControl(KrLabel_t, L"这个当然也不是标签", 100, 150, 200, 25));
	pl1->Show();
	return p->MessageLoop();
}