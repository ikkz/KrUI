#include "KrCore.h"

namespace KrUI
{
	void KrMessageHandler::RegMsg(UINT msg, MSGPROC proc)
	{
		m_MsgProcMap.insert(multimap<UINT, MSGPROC>::value_type(msg, proc));
	}

	LRESULT KrMessageHandler::HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	void KrMessageHandler::RemoveMsgProc(MSGPROC proc)
	{

	}
} // namespace KrUI