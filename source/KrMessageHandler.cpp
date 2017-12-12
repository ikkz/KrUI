#include "KrCore.h"

namespace KrUI
{
	void KrMessageHandler::RegMsg(UINT msg, MSGPROC proc)
	{
		m_MsgProcMap.insert(multimap<UINT, MSGPROC>::value_type(msg, proc));
	}

	LRESULT KrMessageHandler::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{

		auto it = m_MsgProcMap.begin();
		while (it!=m_MsgProcMap.end())
		{
			if (it->second == NULL)
			{
				it = m_MsgProcMap.erase(it);
			}else{
				it++;
			}
		}
		return 0;
	}

	void KrMessageHandler::RemoveMsgProc(MSGPROC proc)
	{
		//暂时将proc置为NULL，防止两层遍历导致的迭代器失效
		for (auto it=m_MsgProcMap.begin();it!=m_MsgProcMap.end();it++)
		{
			if (it->second == proc) it->second = NULL;
		}
	}
} // namespace KrUI