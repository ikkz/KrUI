/*********************************************************
Author:MilesYang
Mail:1961464399@qq.com
CurrentTime:2018-5-3
FileName:KrMessageHandler.cpp
*********************************************************/


#include "KrMessageHandler.h"
namespace KrUI
{
	bool operator==(MSGFUNC& lhs, MSGFUNC& rhs)
	{
		return lhs.target<LRESULT(KrMessageHandler*, WPARAM, LPARAM)>() == rhs.target<LRESULT(KrMessageHandler*, WPARAM, LPARAM)>();
	}

	void KrMessageHandler::RegMsg(UINT msg, MSGFUNC proc)
	{
		m_MsgProcMap.insert(std::multimap<UINT, MSGFUNC>::value_type(msg, proc));
	}

	LRESULT KrMessageHandler::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		auto it = m_MsgProcMap.begin();
		while (it!=m_MsgProcMap.end())
		{
			if (it->second == nullptr)
			{
				it = m_MsgProcMap.erase(it);
			}else{
				++it;
			}
		}
		this->CallMsgProc(Message, wParam, lParam);
		return 0;
	}

	void KrMessageHandler::RemoveMsgProc(MSGFUNC proc)
	{
		//暂时将proc置为NULL，防止两层遍历导致的迭代器失效
		for (auto it=m_MsgProcMap.begin();it!=m_MsgProcMap.end();++it)
		{
			if (it->second == proc) it->second = nullptr;
		}
	}

	void KrMessageHandler::CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		for (auto p : m_MsgProcMap)
		{
			if (p.first == Message)
			{
				p.second(this, wParam, lParam);
			}
		}
	}

	MSGFUNC MsgFuncAdapter(std::function<void(void)> _Func)
	{
		return MsgFuncAdapterClass<void(void)>(_Func);
	}

} // namespace KrUI