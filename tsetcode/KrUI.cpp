#include "source/KrCore.h"
KrUI::KrUIManager* pUM = KrUI::KrUIManager::GetpKrUIManager();
KrUI::KrWindow* pWnd = nullptr;
KrUI::KrButton* pBtn = nullptr;
KrUI::KrList* pList = nullptr;
KrUI::KrEdit* pEdit = nullptr;
KrUI::KrRadio* pRadio = nullptr;
KrUI::KrCheckBox* pCheckBox = nullptr;
KrUI::KrProgressBar* pProgressBar = nullptr;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!pUM->Initialize(hInstance)) return 0;
	pWnd = pUM->AddWindow(L"这不是一个窗口", 100, 100, 700, 700);
	pBtn = pWnd->AddButton(L"这才不是按钮", 100, 50, 200, 35);
	pEdit = pWnd->AddEdit(L"12323443", 100, 100, 200, 35);
	pProgressBar = pWnd->AddProgressBar(L"", 100, 150, 200, 30);
	pProgressBar->SetPercentage(50);
	pList = pWnd->AddList(L"", 100, 200, 200, 400);
	pList->SetMultiSelectable(true);
	pRadio = pWnd->AddRadio(L"", 350, 200, 200, 400);
	pCheckBox = pWnd->AddCheckBox(L"", 350, 400, 200, 400);
	for (int i = 0; i < 20; i++) pList->AddItem(std::to_wstring(i));
	for (int i = 0; i < 5; i++)
	{
		pCheckBox->AddItem(std::to_wstring(i));
		pRadio->AddItem(std::to_wstring(i));
	}

	return pUM->MessageLoop();
}
