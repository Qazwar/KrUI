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
	/*��Ҫ������Ϣ����������public��ʽ�̳д���								*/
	/************************************************************************/
	class KrMessageHandler
	{
	protected:
		std::multimap<UINT, MSGPROC> m_MsgProcMap;
	public:
		virtual void RegMsg(UINT msg, MSGPROC proc);
		virtual void RemoveMsgProc(MSGPROC proc);
		//�����ｫ��ΪNULL��procɾ��������������ʵ�ֵ�HandleMessage�Ľ���ʱ����KrMessageHandler::HandleMessage
		virtual	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
		virtual void CallMsgProcFinal(UINT Message, WPARAM wParam, LPARAM lParam);
	};
}//!KrUI
#endif


