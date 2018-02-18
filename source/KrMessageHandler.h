#ifndef _KR_MESSAGEHANDLER_H
#define _KR_MESSAGEHANDLER_H
#pragma once

#include <windows.h>
#include <map>

namespace KrUI
{
	class KrMessageHandler;
	typedef LRESULT(*MSGPROC) (KrMessageHandler* pKrMessageHandler, WPARAM wParam, LPARAM lParam);
	/************************************************************************/
	/* KrMessageHandler                                                     */
	/*需要进行消息处理的类必须public方式继承此类								*/
	/************************************************************************/
	class KrMessageHandler
	{
	protected:
		std::multimap<UINT, MSGPROC> m_MsgProcMap;
	public:
		virtual void RegMsg(UINT msg, MSGPROC proc);
		virtual void RemoveMsgProc(MSGPROC proc);
		//在这里将置为NULL的proc删除，必须在子类实现的HandleMessage的结束时调用KrMessageHandler::HandleMessage
		virtual	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
		virtual void CallMsgProcFinal(UINT Message, WPARAM wParam, LPARAM lParam);
	};
}//!KrUI
#endif


