# KrUI

- 采用DirectUI思想，所有控件均无句柄
- 使用GDI+绘制
- 实现了窗口和控件的双缓冲绘制
## 环境：
- 使用vs2017
- 生成的exe请右键属性在兼容性中禁止高DPI自动缩放
## Demo：
- [RememberWord](https://github.com/cildhdi/RememberWord)

## 使用方法（以vs2017为例）：
- 在vs中新建空项目，并在项目属性中设置使用Unicode字符集
- 下载KrUI文件夹并copy到上述空项目的代码目录下
- 在空项目里新建一个main.cpp源文件：
```c++
#include "KrUI/KrUI.h"
//选择静态库版本
#ifdef _DEBUG
#pragma comment(lib,"KrUI/Debug/KrUI.lib")
#else
#pragma comment(lib,"KrUI/Release/KrUI.lib")
#endif

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
	pWnd = pUM->AddWindow(L"一个窗口", 100, 100, 700, 700, WS_OVERLAPPEDWINDOW);
	pBtn = pWnd->AddButton(L"Button", 100, 50, 150, 35);
	pBtn->RegMsg(KM_CLICK, click);//传入函数

	pBtn1 = pWnd->AddButton(L"Button1", 300, 50, 150, 35);
	pBtn1->RegMsg(KM_CLICK, [](MSGFUNC_ARGS)-> LRESULT
	{
		MessageBoxW(nullptr, L"you clicked the button", L"tip", MB_OK); 
		return 0;
	});//传入lambda表达式

	pBtn2 = pWnd->AddButton(L"Button2", 500, 50, 150, 35);
	pBtn2->RegMsg(KM_CLICK, KrUI::MsgFuncAdapter([]()
	{
		MessageBoxW(nullptr, L"you clicked the button", L"tip", MB_OK);
	}));//不关心参数就使用适配器传入void(void)的lambda表达式
	//只要是callable的对象，比如重载了operator()的struct/class，均可以作为参数传入

	pEdit = pWnd->AddEdit(L"单行编辑", 100, 100, 200, 35);

	pProgressBar = pWnd->AddProgressBar(L"", 100, 150, 200, 30);
	pProgressBar->SetPercentage(24);
	pList = pWnd->AddList(L"", 100, 200, 200, 400);
	pList->SetMultiSelectable(false);
	pRadio = pWnd->AddRadio(L"", 350, 200, 200, 400);
	pCheckBox = pWnd->AddCheckBox(L"", 350, 400, 200, 400);
	for (int i = 0; i < 20; i++)
		pList->AddItem(L"ListItem_" + std::to_wstring(i));
	for (int i = 0; i < 5; i++)
	{
		pCheckBox->AddItem(L"CheckBoxItem_" + std::to_wstring(i));
		pRadio->AddItem(L"RadioItem_" + std::to_wstring(i));
	}
	pWnd->Show();
	return pUM->MessageLoop();
}
```
## 具体说明
- 添加窗口，提供了一下几个重载函数：
```c++
KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height);//1
KrWindow* AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height);//2
KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);//3
KrWindow* AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);//4
//1.创建一个默认的窗口
//2.如果在窗口上有额外的绘图，则需要public方式继承KrWindow类，并重写虚函数Draw()，然后在2的第一个参数传入继承类的指针
//3.(4.)创建的默认窗口目前还没有做到和Windows默认窗口一致的行为（比如sizebox，鼠标拖动到屏幕边缘自动调整大小和窗口阴影的特点），如果需要Windows默认窗口提供的这些功能，则要用34方法来创建窗口，最后一个参数传入你想要的窗口风格
```
- 添加控件，提供以下函数：
```c++
KrUIBase* AddControl(KrUIType t, LPCWSTR lpName, int x, int y, int width, int height);
KrButton* AddButton(LPCWSTR lpName, int x, int y, int width, int height);
KrLabel* AddLabel(LPCWSTR lpName, int x, int y, int width, int height);
KrEdit* AddEdit(LPCWSTR lpName, int x, int y, int width, int height);
KrList* AddList(LPCWSTR lpName, int x, int y, int width, int height);
KrProgressBar* AddProgressBar(LPCWSTR lpName, int x, int y, int width, int height);
KrRadio* AddRadio(LPCWSTR lpName, int x, int y, int width, int height);
KrCheckBox* AddCheckBox(LPCWSTR lpName, int x, int y, int width, int height);
//后几个函数是第一个函数的简化，免去了实际使用时的dynamic_cast
```
- 注册消息响应函数：
```c++
typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
void RegMsg(UINT msg, MSGPROC proc);
/*第一个参数为需要接收的消息，可以使用WM_开头的未经过处理的消息，也可以使用KM_开头的经过处理的消息，比如鼠标的坐标均转换成了相对于此控件的坐标，并且新增了一些比较方便的消息
第二个参数为消息响应函数的地址，必须按照声明的格式来编写，其中pKrMessageHandler表示的是这个消息对应的控件，处理完成return 0;即可
*/
```
## Classes:
类图如下所示：
![](http://img04.sogoucdn.com/app/a/100520146/828e108ecc3ea634c3cf383449a6dfbe)
