#ifndef KREDIT_H
#define  KREDIT_H
#pragma once

#include "KrCore.h"
#include "KrUIBase.h"
#include <string>
//using namespace std;
/*
标准的Edit需要实现的一些特征
	1.文本显示
	2.光标闪烁（设置定时器画竖线）
	3.根据鼠标的点击位置设置光标的位置
	4.拖动鼠标选中文本（此时光标要隐藏）
	5.响应键盘事件
		输入字符时
			有文本被选中时进行替换
			没有文本被选中时对光标位置插入字符
		输入回车和delete时
			有文本被选中时进行选中文本的删除
			没有文本被选中时对光标位置前后删除字符
	6.画字符时，把文本分成三个部分画：文本+selectstart+文本+selectend+文本，

*/
namespace KrUI
{

	class KrEdit:public KrUIBase
	{
	public:
		KrEdit();
	protected:
		std::string m_strText;
		virtual void UpdateDc();
		Button_Status m_ButtonStatus;
	};


}
#endif


