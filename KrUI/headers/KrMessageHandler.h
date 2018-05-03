/*********************************************************
Author:MilesYang
Mail:1961464399@qq.com
CurrentTime:2018-4-13
FileName:KrMessageHandler.h
*********************************************************/

#ifndef _KR_MESSAGEHANDLER_H
#define _KR_MESSAGEHANDLER_H
#pragma once

#include <map>
#include <windows.h>
#include <functional>

#define MSGFUNC_ARGS KrUI::KrMessageHandler* kmh, WPARAM wp, LPARAM lp
#define MSGFUNC_HEAD(_Func) LRESULT _Func (MSGFUNC_ARGS)
namespace KrUI
{
	class KrMessageHandler;
	using  MSGFUNC = std::function<LRESULT(KrMessageHandler*, WPARAM, LPARAM)>;
	bool operator==(MSGFUNC& lhs, MSGFUNC& rhs);


	//KrMessageHandler需要进行消息处理的类必须public方式继承此类
	class KrMessageHandler
	{
	protected:
		std::multimap<UINT, MSGFUNC> m_MsgProcMap;
	public:
		virtual void RegMsg(UINT msg, MSGFUNC proc);
		virtual void RemoveMsgProc(MSGFUNC proc);
		//在这里将置为NULL的proc删除，必须在子类实现的HandleMessage的结束时调用KrMessageHandler::HandleMessage
		virtual	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	};

	// 	template<typename _Fn>
	// 	class MsgFuncAdapterClass
	// 	{
	// 	private:
	// 		_Fn m_MsgFunc;
	// 	public:
	// 		MsgFuncAdapterClass(_Fn MsgFunc)
	// 		{
	// 			m_MsgFunc = MsgFunc;
	// 		}
	// 
	// 		LRESULT operator()(KrMessageHandler*, WPARAM, LPARAM)
	// 		{
	// 			m_MsgFunc();
	// 			return 0;
	// 		}
	// 
	// 	};

	template<typename _Ty>
	class MsgFuncAdapterClass
	{
	private:
		std::function<_Ty> m_MsgFunc;
	public:
		MsgFuncAdapterClass(std::function<_Ty> _Func)
		{
			m_MsgFunc = _Func;
		}
		LRESULT operator()(KrMessageHandler*, WPARAM, LPARAM)
		{
			m_MsgFunc();
			return 0;
		}
	};

	MSGFUNC MsgFuncAdapter(std::function<void(void)> _Func);

}//!KrUI
#endif


