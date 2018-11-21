#include "KrUI.h"

//一些控件的指针声明，也可以使用面向对象的方式组织
KrUI::KrUIManager* pUM = KrUI::KrUIManager::GetpKrUIManager();
KrUI::KrWindow* pWnd = nullptr;
KrUI::KrButton* pBtn = nullptr;
KrUI::KrButton* pBtn1 = nullptr;
KrUI::KrButton* pBtn2 = nullptr;
KrUI::KrList* pList = nullptr;
KrUI::KrEdit* pEdit = nullptr;
KrUI::KrRadio* pRadio = nullptr;
KrUI::KrCheckBox* pCheckBox = nullptr;
KrUI::KrProgressBar* pProgressBar = nullptr;
KrUI::KrScrollBar* pScrollBar = nullptr;

//点击事件响应函数
MSGFUNC_HEAD(click)//展开即 LRESULT click (KrUI::KrMessageHandler* kmh,WPARAM wp,LPARAM lp)
{
	MessageBoxW(nullptr, L"you clicked the button", L"tip", MB_OK);
	return 0;
}



//主函数入口
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//初始化
	if (!pUM->Initialize(hInstance)) return 0;
	pWnd = pUM->AddWindow(std::wstring(L"kfldsjf"), 100, 100, 700, 700);
	pBtn = pWnd->AddButton(L"Button", 100, 50, 150, 35);
	pBtn->RegMsg(KM_CLICK, click);
	pBtn->SetMouseLeaveColor(Gdiplus::Color::Gray);
	pBtn->SetBorderColor(Gdiplus::Color::Black);
	pBtn->SetBorderWidth(0.5);
	pBtn1 = pWnd->AddButton(L"Button1", 300, 50, 150, 35);
	pBtn1->RegMsg(KM_CLICK, [](MSGFUNC_ARGS)-> LRESULT
	{
		MessageBoxW(nullptr, L"you clicked the button", L"tip", MB_OK);
		return 0;
	});//传入lambda表达式

	pBtn2 = pWnd->AddButton(L"Button2", 500, 50, 150, 35);
	pBtn2->RegMsg(KM_CLICK, KrUI::MsgFuncAdapter([&]()
	{
		pBtn2->SetX(pBtn2->GetX() + 10);
	}));//不关心参数就使用适配器传入void(void)的lambda表达式
		//只要是callable的对象，比如重载了operator()的struct/class，均可以作为参数传入

	pEdit = pWnd->AddEdit(L"单行编辑", 100, 100, 200, 35);
	pEdit->RegMsg(KM_TEXTCHANGE, [](MSGFUNC_ARGS) 
	{
		pBtn->SetName(pEdit->GetText());
		return 0;
	});
	pProgressBar = pWnd->AddProgressBar(L"", 100, 150, 200, 30);
	pProgressBar->SetPercentage(24);

	pList = pWnd->AddList(L"", 100, 200, 200, 400);
	pList->SetMultiSelectable(false);
	for (int i = 0; i < 20; i++)
		pList->AddItem(L"ListItem_" + std::to_wstring(i));

	pRadio = pWnd->AddRadio(L"", 350, 200, 200, 400);
	pCheckBox = pWnd->AddCheckBox(L"", 350, 400, 200, 400);

	pScrollBar = pWnd->AddScrollBar(L"", 400, 150, 200, 35);

	for (int i = 0; i < 5; i++)
	{
		pCheckBox->AddItem(L"CheckBoxItem_" + std::to_wstring(i));
		pRadio->AddItem(L"RadioItem_" + std::to_wstring(i));
	}
	pWnd->Show();
	return pUM->MessageLoop();
}
