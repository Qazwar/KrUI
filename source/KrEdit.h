#ifndef KREDIT_H
#define  KREDIT_H
#pragma once

#include "KrCore.h"
#include "KrUIBase.h"
#include <string>
//using namespace std;
/*
��׼��Edit��Ҫʵ�ֵ�һЩ����
	1.�ı���ʾ
	2.�����˸�����ö�ʱ�������ߣ�
	3.�������ĵ��λ�����ù���λ��
	4.�϶����ѡ���ı�����ʱ���Ҫ���أ�
	5.��Ӧ�����¼�
		�����ַ�ʱ
			���ı���ѡ��ʱ�����滻
			û���ı���ѡ��ʱ�Թ��λ�ò����ַ�
		����س���deleteʱ
			���ı���ѡ��ʱ����ѡ���ı���ɾ��
			û���ı���ѡ��ʱ�Թ��λ��ǰ��ɾ���ַ�
	6.���ַ�ʱ�����ı��ֳ��������ֻ����ı�+selectstart+�ı�+selectend+�ı���

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


