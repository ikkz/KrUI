# KrUI

## 环境：
- 使用vs2015
- 使用其他编译器时（如gcc）编译时有些Gdi+的操作（比如传递&Gdiplus::SolidBrush(Color::WHITE)作为参数）会出现[Error] taking address of temporary [-fpermissive]的错误，可以使用一个中间变量来消除错误

## 项目：
- 使用Gdi+绘图
- 通过Gdiplus::Bitmap实现了类似于双缓冲的效果
- 所有的控件都由KrUI::KrUIBase派生，只需要在绘制时把内容画到KrUIBase::m_pBmp上，就可以简单的实现各种不同的控件
### 需要改的地方：
- 使用定时器来定时绘图，效率比响应WM_PAINT来绘图要低
- 很多地方都没有进行错误检查
- 鼠标拖动停靠桌面边缘时没有自动改变大小的功能
