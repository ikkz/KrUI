# KrUI

## 环境：
- 使用vs2017
- 生成的exe请右键属性在兼容性中禁止高DPI自动缩放

## 使用方法（以vs2017为例）：
- 在vs中新建空项目
- 下载source文件夹并copy到上述空项目的代码目录下
- 在空项目里新建一个.cpp源文件
- 在源文件里敲如下代码：
```
#include "source/KrCore.h"//包含头文件
KrUI::KrUIManager* pUM = KrUI::KrUIManager::GetpKrUIManager();//获取ui管理器的唯一实例
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)//入口函数固定写法
{
	if (!pUM->Initialize(hInstance)) return 0;//初始化
  //在这里可以添加窗口和控件等
	return pUM->MessageLoop();//进入消息循环
}
```
- 然后是添加窗口，提供了一下几个重载函数：
```
KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height);//1
KrWindow* AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height);//2
KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);//3
KrWindow* AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);//4
//1.创建一个默认的窗口
//2.如果在窗口上有额外的绘图，则需要public方式继承KrWindow类，并重写虚函数Draw()，然后在2的第一个参数传入继承类的指针
//3.(4.)创建的默认窗口目前还没有做到和Windows默认窗口一致的行为（比如sizebox，鼠标拖动到屏幕边缘自动调整大小和窗口阴影的特点），如果需要Windows默认窗口提供的这些功能，则要用34方法来创建窗口，最后一个参数传入你想要的窗口风格（同CreateWindow），然后还必须调用KrWindow::SetCaptionHeight来去掉默认的标题栏和边框
```
- 添加控件，提供以下函数：
```
enum KrUIType { KrWindow_t, KrButton_t, KrCloseButton_t, KrLabel_t, KrEdit_t, KrProgressBar_t, KrList_t };
KrUIBase* AddControl(KrUIType t, LPCWSTR lpName, int x, int y, int width, int height);
KrButton* AddButton(LPCWSTR lpName, int x, int y, int width, int height);
KrLabel* AddLabel(LPCWSTR lpName, int x, int y, int width, int height);
KrEdit* AddEdit(LPCWSTR lpName, int x, int y, int width, int height);
KrList* AddList(LPCWSTR lpName, int x, int y, int width, int height);
KrProgressBar* AddProgressBar(LPCWSTR lpName, int x, int y, int width, int height);
//以上函数都可以根据名字知道功能，其中后几个函数是第一个函数的简化，免去了实际使用时的dynamic_cast
```
- 注册消息响应函数：
```
typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
void RegMsg(UINT msg, MSGPROC proc);
/*第一个参数为需要接收的消息，可以使用WM_开头的未经过处理的消息，也可以使用KM_开头的经过处理的消息，比如鼠标的坐标均转换成了相对于此控件的坐标，并且新增了一些比较方便的消息
第二个参数为消息响应函数的地址，必须按照声明的格式来编写，其中pKrMessageHandler表示的是这个消息对应的控件，处理完成return 0;即可
*/
```
