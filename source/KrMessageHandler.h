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

namespace KrUI
{
	class KrMessageHandler;
	using  MSGFUNC = std::function<LRESULT(KrMessageHandler*, WPARAM, LPARAM)>;
	bool operator==(MSGFUNC& lhs, MSGFUNC& rhs);


	//KrMessageHandler��Ҫ������Ϣ����������public��ʽ�̳д���
	class KrMessageHandler
	{
	protected:
		std::multimap<UINT, MSGFUNC> m_MsgProcMap;
	public:
		virtual void RegMsg(UINT msg, MSGFUNC proc);
		virtual void RemoveMsgProc(MSGFUNC proc);
		//�����ｫ��ΪNULL��procɾ��������������ʵ�ֵ�HandleMessage�Ľ���ʱ����KrMessageHandler::HandleMessage
		virtual	LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	};
}//!KrUI
#endif


