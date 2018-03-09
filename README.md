# KrUI
![ui](http://img04.sogoucdn.com/app/a/100520146/c0bcbe59a184833f0370b3e3431faaef)
- 采用DirectUI思想，所有控件均无句柄
- 使用GDI+绘制
- 实现了窗口和控件的双缓冲绘制
## 环境：
- 使用vs2017
- 生成的exe请右键属性在兼容性中禁止高DPI自动缩放
## Demo：
- [RememberWord](https://github.com/cildhdi/RememberWord)

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
```
typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
void RegMsg(UINT msg, MSGPROC proc);
/*第一个参数为需要接收的消息，可以使用WM_开头的未经过处理的消息，也可以使用KM_开头的经过处理的消息，比如鼠标的坐标均转换成了相对于此控件的坐标，并且新增了一些比较方便的消息
第二个参数为消息响应函数的地址，必须按照声明的格式来编写，其中pKrMessageHandler表示的是这个消息对应的控件，处理完成return 0;即可
*/
```
## Classes:
类图如下所示：
![](http://img04.sogoucdn.com/app/a/100520146/828e108ecc3ea634c3cf383449a6dfbe)
### KrMessageHandler
```
//所有的能够响应消息的类都必须继承自这个类
class KrMessageHandler
{
protected:
	//使用mutimap来保存消息和对应的一个或者多个处理函数
	std::multimap<UINT, MSGPROC> m_MsgProcMap;
public:
	//注册消息
	virtual void RegMsg(UINT msg, MSGPROC proc);
	//在这个函数里把proc置为NULL
	virtual void RemoveMsgProc(MSGPROC proc);
	//在这里将置为NULL的proc删除，必须在子类实现的HandleMessage的结束时调用KrMessageHandler::HandleMessage
	virtual	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	//调用消息处理函数
	virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
};
```
### KrUIBase
```
//所有的界面元素都继承此类
class KrUIBase :public KrMessageHandler
{
protected:
	std::wstring m_strName;
	RECT m_rect;
	bool m_bVisible;
	//保存自己的位图
	Gdiplus::Bitmap* m_pBmp;
	HBITMAP m_hBmp;
	//上述位图对应的Graphics
	Gdiplus::Graphics* m_pGraphics;
	KrUIType m_UIType;
	//父窗口，本身是窗口的话就为nullptr
	KrWindow* m_pKrWindow;
	//画字符串的时候使用的格式
	Gdiplus::StringFormat m_StringFormat;
	Gdiplus::Font* m_pFont;
	Gdiplus::Color m_FontColor;
	Gdiplus::Color m_BorderColor;
	Gdiplus::Color m_BgColor;
	bool m_bMouseIn;
	bool m_bMouseDown;
	//鼠标在这个元素范围内时的形状
	HCURSOR m_hCursor;
public:
	KrUIBase();
	~KrUIBase();
	void SetType(KrUIType ut);
	KrUIType GetType();
	//下面这些声明为虚函数，有些子类需要重写来做一些额外的事情
	virtual RECT* GetRect();
	virtual void SetRect(RECT* pRect);
	virtual unsigned int GetX();
	virtual unsigned int GetY();
	virtual unsigned int GetWidth();
	virtual unsigned int GetHeight();
	virtual void SetX(unsigned int x);
	virtual void SetY(unsigned int y);
	virtual void SetXY(unsigned int x, unsigned int y);
	virtual void SetWidth(unsigned int width);
	virtual void SetHeight(unsigned int height);
	virtual void SetSize(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	virtual void Show();
	virtual void Hide();
	virtual bool IsVisible();
	virtual void SetDc(HDC hdc);
	virtual void SetParantWindow(KrWindow* pKrWindow);
	KrWindow* GetParantWindow();
	void SetFontColor(Gdiplus::Color color);
	Gdiplus::Color GetFontColor();
	Gdiplus::Color GetBgColor();
	void SetBgColor(Gdiplus::Color c);
	//界面更新函数，被调用时需要根据当前状态更新自己的界面
	virtual void Update();
	//改变元素位图的大小
	virtual void ChangeBmpSize();
	Gdiplus::Graphics* GetBmpGraphics();
	virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	virtual void SetName(std::wstring name);
	std::wstring GetName();
	virtual LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	void SetFont(const WCHAR* fontfamily, Gdiplus::REAL emSize);
	Gdiplus::Font* GetFont();
	//设置字符串横向纵向格式
	void SetAlignment(Gdiplus::StringAlignment align);
	void SetLineAlignment(Gdiplus::StringAlignment align);
};
```
### KrUIManager
```
//通过KrUIManager管理Window，Window管理控件
class KrUIManager
{
public:
	//获取KrUIManager的唯一实例
	static KrUIManager* GetpKrUIManager();
	//这个函数把收到的消息全部转发到这个类里来分发给子窗口
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	//定时调用的函数，用来绘图
	static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT_PTR nTimerid, DWORD dwTime);
	//相关的初始化
	bool Initialize(HINSTANCE hInstance);
	KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height);
	KrWindow* AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height);
	KrWindow* AddWindow(LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);
	KrWindow* AddWindow(KrWindow* pKrWindow, LPCWSTR lpWindowName, int x, int y, int width, int height, DWORD dwStyle);
	LPCWSTR GetWindowClassName();
	HINSTANCE GetHINSTANCE();
	//WinMain里return 这个函数
	int MessageLoop();
	LRESULT HandleMessage(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	//获取当前窗口的数量
	int GetWindowNum();
	void DeleteWindow(KrWindow* pKrWindow);
	//根据句柄获取对应的KrWinodw*
	KrWindow* GetpKrWindow(HWND hwnd);
	~KrUIManager();
private:
	KrUIManager() { m_lpWindowClassName = L"KrUI"; }
	static KrUIManager* m_pKrUIManager;
	LPCWSTR m_lpWindowClassName;//
	HINSTANCE m_hInstance;//
	MSG m_msg;
	//保存窗口
	std::vector<KrWindow*> m_WndVec;
};
```
### KrWindow
```
class KrWindow :public KrUI::KrUIBase
{
private:
	LPCWSTR m_lpName;
	HWND m_hwnd;
	DWORD m_dwStyle;
	POINT m_ptMouse;
	//标题栏的高度，为0时没有默认的标题栏和边框
	UINT m_CaptionHeight;
	POINT m_ptMouseDown;
	bool m_bMouseDown;
	Gdiplus::Color m_CaptionColor;
	HDC m_hDC;
	Gdiplus::Graphics* m_pGraphicsDC;
	//保存控件
	std::vector<KrUIBase*> m_UIVec;
	//标识当前窗口里哪个控件获得了焦点
	KrUIBase* m_pFocusedCtrl;
public:
	friend class KrButton;
	friend class KrCloseButton;
	friend class KrLabel;
	friend class KrEdit;
	friend class KrList;

	KrWindow();
	static LRESULT SizeChange(KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
	LPCWSTR GetWindowName();
	void SetWindowName(LPCWSTR lpWindowName);
	void SetHWND(HWND hwnd);
	HWND GetHWND();
	void SetStyle(DWORD dwStyle);
	DWORD GetStyle();

	virtual void SetRect(RECT* pRect);
	virtual void SetX(unsigned int x);
	virtual void SetY(unsigned int y);
	virtual void SetXY(unsigned int x, unsigned int y);
	virtual void SetWidth(unsigned int width);
	virtual void SetHeight(unsigned int height);
	virtual void Show();
	virtual void Hide();
	virtual void Update();
	virtual void ChangeBmpSize();
	virtual void Draw();//自定义绘制的窗口重写此方法
	KrUIBase* GetFocusedCtrl();
	void SetFocusedCtrl(KrUIBase* pui);
	HDC GetDc();
	//窗口是否已经创建成功
	bool IsCreated();
	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	KrUIBase* AddControl(KrUIType t, LPCWSTR lpName, int x, int y, int width, int height);
	KrButton* AddButton(LPCWSTR lpName, int x, int y, int width, int height);
	KrLabel* AddLabel(LPCWSTR lpName, int x, int y, int width, int height);
	KrEdit* AddEdit(LPCWSTR lpName, int x, int y, int width, int height);
	KrList* AddList(LPCWSTR lpName, int x, int y, int width, int height);
	KrProgressBar* AddProgressBar(LPCWSTR lpName, int x, int y, int width, int height);
	void RemoveControl(KrUIBase* pui);
	void SetCaptionHeight(unsigned int ch);
	unsigned int GetCaptionHeight();
};
```
### KrButton
```
class KrButton :public KrUIBase
{
public:
	KrButton();
	~KrButton();
	void SetMouseHoverColor(Gdiplus::Color color);
	void SetMouseDownColor(Gdiplus::Color color);
	void SetMouseLeaveColor(Gdiplus::Color color);
	void SetBorderColor(Gdiplus::Color color);
	Gdiplus::Color GetMouseHoverColor();
	Gdiplus::Color GetMouseDownColor();
	Gdiplus::Color GetMouseLeaveColor();
	Gdiplus::Color GetBorderColor();
	//以下声明为虚函数，方便以后图片按钮的编写
	virtual void DrawMouseDownBmp();
	virtual void DrawMouseHoverBmp();
	virtual void DrawMouseLeaveBmp();
	virtual void DrawContent();
	virtual void Update();
	virtual void SetName(std::wstring name);
	void SetButtonStatus(Mouse_Status bs);
	virtual LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
protected:
	Gdiplus::Color m_MouseHoverColor;
	Gdiplus::Color m_MouseDownColor;
	Gdiplus::Color m_MouseLeaveColor;
	Gdiplus::Color m_BorderColor;
	Mouse_Status m_ButtonStatus;
};
//其他成员应该很好理解
```
### KrLabel
```
//继承自KrButton，构造函数里把不同鼠标状态的背景设置成透明，并且设置两种字符串格式都为Near
class KrLabel :public KrButton
{
public:
	KrLabel(Gdiplus::Color bgcolor);
};
```
### KrEdit
```
class KrEdit :public KrUIBase
{
public:
	KrEdit();
	void SetText(std::wstring str);
	std::wstring GetText();
	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	//根据鼠标横坐标获取光标的位置
	unsigned int GetCursorPosByX(unsigned int x);
	//根据光标的位置获取横坐标
	unsigned int GetXByCursorPos(unsigned int CursorPos);
	//获取字符串高度
	unsigned int GetStrHeight();
	virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	virtual void ChangeBmpSize();
	//获取字符串的宽高
	Gdiplus::SizeF GetTextBounds(std::wstring strText);
	//更新字符串长度数组
	void StringChange();
protected:
	std::wstring m_strText;
	virtual void Update();
	Mouse_Status m_MouseStatus;
	bool m_bShowCursor;
	unsigned int m_Margin;
	unsigned int m_Time;
	//选中文本的起始结束位置
	unsigned int m_SelectTextPosFirst;
	unsigned int m_SelectTextPosSecond;
	//保存了当前文本每个字符串长度的数组
	std::vector<unsigned int> m_StringLength;
};
```
### KrProgressBar
```
class KrProgressBar :public KrUIBase
{
protected:
	//进度条百分数（0-100）
	unsigned int m_Percentage;
	//互斥量
	std::mutex m_PercentageMutex;
	//进度条颜色
	Gdiplus::Color m_ForeColor;
public:
	KrProgressBar();
	void SetForeColor(Gdiplus::Color c);
	Gdiplus::Color GetForeColor();
	void SetPercentage(unsigned int Percentage);
	unsigned int GetPercentage();
	virtual void Update();
};
```
### KrList
```
//列表项结构
struct KrListItem
{
	unsigned int m_Index;
	std::wstring m_ItemName;
	unsigned int m_Height;
	KrListItem(std::wstring wStr, unsigned int Index, unsigned int Height) : m_ItemName(wStr), m_Index(Index), m_Height(Height) {}
};

class KrList : public KrUIBase
{
public:
	KrList();
	int AddItem(std::wstring wStr, int nIndex = -1, unsigned int nHeight = 35);
	//删除所有为wStr的项
	int RemoveItem(std::wstring wStr);
	bool RemoveItem(int nIndex);
	//没有选中时return KrListItem{ L"",0,0 }
	KrListItem GetSelectedItem();
	virtual void Update();
	virtual LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
	void SetPosition(int position);
private:
	//表示列表绘制开始的位置
	unsigned int m_Position;
	std::vector<KrListItem> m_ListItems;
	//完整列表的高度
	unsigned int m_TotalHeight;
	//鼠标滚轮一次的高度改变量
	unsigned int m_MouseWheelDelta;
	//滚动条的Rect
	Gdiplus::Rect m_ScrollBarRect;
	//当前鼠标停留的那一项
	unsigned int m_MouseHoverItem;
	//选中的那一项
	unsigned int m_SelectedItem;
	//鼠标在滚动条上按下时相对滚动条顶部的位置
	int m_MouseDownOnScrollBarPos;
};
```
