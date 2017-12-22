#ifndef KRMESSAGEHANDLER_H
#define KRMESSAGEHANDLER_H
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
	};
}//!KrUI
#endif


