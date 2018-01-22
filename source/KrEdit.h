#ifndef _KR_EDIT_H
#define  _KR_EDIT_H
#pragma once

#include "KrCore.h"
#include "KrUIBase.h"
#include <string>
//using namespace std;
/*
��׼���������Ҫʵ�ֵ�һЩ����
	1.�ı���ʾ
	2.�����˸�����ö�ʱ�������ߣ�
	3.�������ĵ��λ�����ù���λ��
	4.�϶����ѡ���ı�����ʱ���Ҫ���أ�
	5.��Ӧ�����¼�
		:�����ַ�ʱ
			1���ı���ѡ��ʱ�����滻
			2û���ı���ѡ��ʱ�Թ��λ�ò����ַ�
		:����س���deleteʱ
			3���ı���ѡ��ʱ����ѡ���ı���ɾ��
			4û���ı���ѡ��ʱ�Թ��λ��ǰ��ɾ���ַ�
	6.���ַ�ʱ�����ı��ֳ��������ֻ����ı�+selectstart+�ı�+selectend+�ı���
	7.֧���������뷨ʱ�������뷨��λ��

	����̫���˾�д������....
	3   4   5.1   5.3   6  7����д��
*/
namespace KrUI
{
	class KrEdit :public KrUIBase
	{
	public:
		KrEdit();
		void SetText(std::wstring str);
		std::wstring GetText();
		LRESULT HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);
		unsigned int GetCursorPosByX(unsigned int x);
		unsigned int GetXByCursorPos(unsigned int CursorPos);
		unsigned int GetStrHeight();
		virtual void CallMsgProc(UINT Message, WPARAM wParam, LPARAM lParam);
		Gdiplus::SizeF GetTextBounds(const wchar_t* szText);
		void StringChange();
	protected:
		std::wstring m_strText;
		virtual void Update();
		Mouse_Status m_ButtonStatus;
		bool m_bShowCursor;
		unsigned int m_Margin;
		unsigned int m_Time;
		unsigned int m_SelectTextPosFirst;
		unsigned int m_SelectTextPosSecond;
		std::vector<unsigned int> m_StringLength;
	};
}
#endif
